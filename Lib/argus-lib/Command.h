#ifndef CommandH
#define CommandH

#include <optional>
#include <filesystem>
#include <Magick++.h>
#include <CommonTypes.h>
#include <string>

namespace Argus
{


class LoadCommand : public Command
{
public:
  LoadCommand(const std::string & imageName, const std::string & fileName);
  virtual void operator()(ImageMap & imageMap) const override;
  std::string toString() const override;
private:
  const std::string _imageName;
  const std::string _fileName;
};

class StoreCommand : public Command
{
public:
  StoreCommand(const std::string & imageName, const std::string & fileName);
  virtual void operator()(ImageMap & imageMap) const override;
  std::string toString() const override;
  
private:
  const std::string _imageName;
  const std::string _fileName;
};

class DisplayCommand : public Command
{
public:
  DisplayCommand(const std::string & imageName);
  virtual void operator()(ImageMap & imageMap) const override;
  std::string toString() const override;
  
private:
  const std::string _imageName;
};

}

#endif //CommandH
