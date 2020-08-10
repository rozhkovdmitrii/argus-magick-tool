//----------------------------------------------------------------------------------------------------------------------
#include <iostream>
#include <array>
//----------------------------------------------------------------------------------------------------------------------
#include "App.h"
//----------------------------------------------------------------------------------------------------------------------
namespace Argus
{
//----------------------------------------------------------------------------------------------------------------------
App::App() : _cmdParser(_cmdProcessor) {}
//----------------------------------------------------------------------------------------------------------------------
int App::process()
{
  printHint();
  while (readAndParseCommand());
  return 0;
}
//----------------------------------------------------------------------------------------------------------------------
void App::printHint()
{
  std::cout << "Argus magick tool 1.0.0" << std::endl;
  std::cout << "Type \"help\" or \"h\" for more information." <<  std::endl;
}
//----------------------------------------------------------------------------------------------------------------------
bool App::readAndParseCommand()
{
  std::cout << "> ";
  std::string line;
  std::getline(std::cin, line);
  
  return _cmdParser.parseCmdLine(line);
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
