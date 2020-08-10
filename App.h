//----------------------------------------------------------------------------------------------------------------------
// App - aggregates Argus challenge routines in one
// Created by Rozhkov Dmitrii rozhkovdmitrii@yandex.ru for Argus-soft on 09.08.2020.
//----------------------------------------------------------------------------------------------------------------------
#ifndef AppH
#define AppH
//----------------------------------------------------------------------------------------------------------------------
#include "CommandProcessor.h"
#include "CommandParser.h"
//----------------------------------------------------------------------------------------------------------------------
namespace Argus
{
class App
{
public:
  App();
  int process();

private:
  CommandProcessor _cmdProcessor;
  CommandParser _cmdParser;
  static void printHint();
  bool readAndParseCommand();
};
}
//----------------------------------------------------------------------------------------------------------------------
#endif //AppH
