#include "Log.h"
#include "ExceptionStream.h"
//----------------------------------------------------------------------------------------------------------------------
#include "Commands.h"
//----------------------------------------------------------------------------------------------------------------------
namespace Argus
{
//----------------------------------------------------------------------------------------------------------------------
LoadCommand::LoadCommand(const std::string & dstImageName, const std::string & srcFile) : _dstImageName(dstImageName), _srcFile(srcFile) {}
//----------------------------------------------------------------------------------------------------------------------
void LoadCommand::operator()(ImageMap & imageMap) const
{
  auto hint = imageMap.lower_bound(_dstImageName);
  if (hint != imageMap.end() && hint->first == _dstImageName)
  {
    RD_LOG(INF) << "image: \"" << _dstImageName << "\" already exists - will be overwritten";
    hint->second.read(_srcFile);
  }
  else
  {
    imageMap.emplace_hint(hint, ImageMap::value_type(_dstImageName, Magick::Image(_srcFile)));
  }
}
//----------------------------------------------------------------------------------------------------------------------
std::string LoadCommand::toString() const
{
  std::ostringstream oss;
  oss << "LoadCommand: imageName: \"" << _dstImageName << "\", fileName: \"" << _srcFile << "\"";
  return oss.str();
}
//----------------------------------------------------------------------------------------------------------------------
StoreCommand::StoreCommand(const std::string & srcImageName, const std::string & dstFile) : _srcImageName(srcImageName), _dstFile(dstFile) {}
//----------------------------------------------------------------------------------------------------------------------
void StoreCommand::operator()(ImageMap & imageMap) const
{
  auto it = imageMap.find(_srcImageName);
  if (it == imageMap.end())
    RD_THROW(std::logic_error) << "failed to store image: \"" << _srcImageName << "\" - not found";
  it->second.write(_dstFile);
}
//----------------------------------------------------------------------------------------------------------------------
std::string StoreCommand::toString() const
{
  std::ostringstream oss;
  oss << "StoreCommand: imageName: \"" << _srcImageName << "\", fileName: \"" << _dstFile << "\"";
  return oss.str();
}
//----------------------------------------------------------------------------------------------------------------------
DisplayCommand::DisplayCommand(const std::string & imageName) : _imageName(imageName) {}
//----------------------------------------------------------------------------------------------------------------------
void DisplayCommand::operator()(ImageMap & imageMap) const
{
  auto it = imageMap.find(_imageName);
  if (it == imageMap.end())
    RD_THROW(std::logic_error) << "failed to display image: \"" << _imageName << "\" - not found";
  it->second.display();
}
//----------------------------------------------------------------------------------------------------------------------
std::string DisplayCommand::toString() const
{
  std::ostringstream oss;
  oss << "DisplayCommand: imageName: \"" << _imageName << "\"";
  return oss.str();
}
//----------------------------------------------------------------------------------------------------------------------
BlurCommand::BlurCommand(const std::string & srcImageName, const std::string & dstImageName, int blurSize) :
  _srcImageName(srcImageName),
  _dstImageName(dstImageName),
  _blurSize(blurSize)
{
}
//----------------------------------------------------------------------------------------------------------------------
void BlurCommand::operator()(ImageMap & imageMap) const
{
  auto it = imageMap.find(_srcImageName);
  if (it == imageMap.end())
    RD_THROW(std::logic_error) << "Failed to blur, srcImage not found by name: \"" << _srcImageName << "\"";
  
  auto hint = imageMap.lower_bound(_dstImageName);
  if (hint != imageMap.end() && hint->first == _dstImageName)
    RD_LOG(INF) << "image: \"" << _dstImageName << "\" already exists - will be overwritten";
  else
    hint = imageMap.emplace_hint(hint, ImageMap::value_type(_dstImageName, Magick::Image()));
  
  hint->second = it->second;
  hint->second.blur(_blurSize);
}
//----------------------------------------------------------------------------------------------------------------------
std::string BlurCommand::toString() const
{
  std::ostringstream oss;
  oss << "BlurCommand: srcImageName: \"" << _srcImageName << "\", dstImageName: \"" << _dstImageName << "\", blurSize: " << _blurSize;
  return oss.str();
}
//----------------------------------------------------------------------------------------------------------------------
ResizeCommand::ResizeCommand(const std::string & srcImageName, const std::string & dstImageName, int newWidht, int newHeight) :
  _srcImageName(srcImageName), _dstImageName(dstImageName), _newWidth(newWidht), _newHeight(newHeight)
{
}
//----------------------------------------------------------------------------------------------------------------------
void ResizeCommand::operator()(ImageMap & imageMap) const
{
  auto it = imageMap.find(_srcImageName);
  if (it == imageMap.end())
    RD_THROW(std::logic_error) << "Failed to blur, srcImage not found by name: \"" << _srcImageName << "\"";
  auto hint = imageMap.lower_bound(_dstImageName);
  if (hint != imageMap.end() && hint->first == _dstImageName)
    RD_LOG(INF) << "image: \"" << _dstImageName << "\" already exists - will be overwritten";
  else
    hint = imageMap.emplace_hint(hint, ImageMap::value_type(_dstImageName, Magick::Image()));
  
  hint->second = it->second;
  hint->second.resize(Magick::Geometry(_newWidth, _newHeight));
}
//----------------------------------------------------------------------------------------------------------------------
std::string ResizeCommand::toString() const
{
  std::ostringstream oss;
  oss << "ResizeCommand: srcImageName: \"" << _srcImageName << "\", dstImageName: \"" << _dstImageName
      << "\", newWidth: " << _newWidth << ", newHeight: " << _newHeight;
  return oss.str();
}
//----------------------------------------------------------------------------------------------------------------------
}