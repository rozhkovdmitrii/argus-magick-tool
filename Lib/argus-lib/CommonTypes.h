
#ifndef CommonTypesH
#define CommonTypesH

#include <string>
#include <map>
#include <Magick++.h>

namespace Argus
{
typedef std::map<std::string, Magick::Image> ImageMap;
typedef std::optional<Magick::Image> OptionalImage;

class Command
{
public:
  virtual ~Command() {}
  
  virtual void operator()(ImageMap & imageMap) const = 0;
  virtual std::string toString() const = 0;
};


class ICommandParserHandler
{
public:
  virtual ~ICommandParserHandler() {}
  virtual void onCmd(const Command & cmd) = 0;
};

}

#endif //CommonTypesH
