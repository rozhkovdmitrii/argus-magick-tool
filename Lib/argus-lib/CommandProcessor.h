//----------------------------------------------------------------------------------------------------------------------
// App - aggregates Argus challenge routines in one
// Created by Rozhkov Dmitrii rozhkovdmitrii@yandex.ru for Argus-soft on 09.08.2020.
//----------------------------------------------------------------------------------------------------------------------
#ifndef CommandProcessorH
#define CommandProcessorH

#include "CommonTypes.h"
//----------------------------------------------------------------------------------------------------------------------
namespace Argus
{
//----------------------------------------------------------------------------------------------------------------------
class CommandProcessor : public ICommandParserHandler
{
public:
  // ICommandParserHandler
  void onCmd(const Command & cmd) override;
  
private:
  ImageMap _imageMap;
};
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
#endif //CommandProcessorH
