#include <iostream>
#include "Command.h"

namespace Argus
{


LoadCommand::LoadCommand(const std::string & imageName, const std::string & fileName) : _imageName(imageName), _fileName(fileName) {}

void LoadCommand::operator()(ImageMap & imageMap) const
{
  auto hint = imageMap.lower_bound(_imageName);
  if (hint != imageMap.end() && hint->first == _imageName)
  {
    std::cout << "image: " << _imageName << " already exists - ignore command" << std::endl;
    return;
  }
  auto it = imageMap.emplace_hint(hint, ImageMap::value_type(_imageName, Magick::Image()));
  it->second.read(_fileName);
}

std::string LoadCommand::toString() const
{
  std::ostringstream oss;
  oss << "LoadCommand: imageName: " << _imageName << ", fileName: " << _fileName;
  return oss.str();
}

StoreCommand::StoreCommand(const std::string & imageName, const std::string & fileName) : _imageName(imageName), _fileName(fileName) {}

void StoreCommand::operator()(ImageMap & imageMap) const
{
  auto it = imageMap.find(_imageName);
  if (it == imageMap.end())
  {
    std::cout << "failed to store image: " << _imageName << " - not found" << std::endl;
    return;
  }
  it->second.write(_fileName);
}

std::string StoreCommand::toString() const
{
  std::ostringstream oss;
  oss << "StoreCommand: imageName: " << _imageName << ", fileName: " << _fileName;
  return oss.str();
}

DisplayCommand::DisplayCommand(const std::string & imageName) : _imageName(imageName) {}

void DisplayCommand::operator()(ImageMap & imageMap) const
{
  auto it = imageMap.find(_imageName);
  if (it == imageMap.end())
  {
    std::cout << "failed to display image: " << _imageName << " - not found" << std::endl;
    return;
  }
  it->second.display();
}

std::string DisplayCommand::toString() const
{
  std::ostringstream oss;
  oss << "DisplayCommand: imageName: " << _imageName;
  return oss.str();
}
}