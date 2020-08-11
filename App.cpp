//----------------------------------------------------------------------------------------------------------------------
#include <iostream>
//----------------------------------------------------------------------------------------------------------------------
#include "App.h"
//----------------------------------------------------------------------------------------------------------------------
namespace Argus
{
//----------------------------------------------------------------------------------------------------------------------
App::App() : _cmdParser(*this) {}
//----------------------------------------------------------------------------------------------------------------------
void App::process()
{
  printHint();
  while (readAndParseCommand());
}
//----------------------------------------------------------------------------------------------------------------------
void App::printHint()
{
  std::cout << "Argus magick tool 1.0.0" << std::endl;
  std::cout << "Usage: argus-magick-tool" << std::endl;
  std::cout << R"(Type "help" or "h" for more information.)" <<  std::endl;
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
void App::onCmd(const Command & cmd)
{
  _cmdProcessor.onCmd(cmd);
}
//----------------------------------------------------------------------------------------------------------------------
void App::onHelpCmd() const
{
  std::cout << "Commands: " << std::endl << std::endl;
  std::cout << "help, h:       print this message" << std::endl;
  std::cout << std::endl;
  std::cout << "load, ld:      load <name> <filename> " << std::endl;
  std::cout << "               loads image from file" << std::endl;
  std::cout << "               <name> - key value provides image in other commands" << std::endl;
  std::cout << "               <filename> - file path to be loaded" << std::endl;
  std::cout << std::endl;
  std::cout << "store, s:      store <name> <filename> " << std::endl;
  std::cout << "               stores image in file" << std::endl;
  std::cout << "               <name> - key value to get image" << std::endl;
  std::cout << "               <filename> - file path to save image to" << std::endl;
  std::cout << std::endl;
  std::cout << "blur:          blur <from_name> <to_name> <size>" << std::endl;
  std::cout << "               apply blur effect to image" << std::endl;
  std::cout << "               <from_name> - key value to get image to be blured" << std::endl;
  std::cout << "               <to_name> - key value to put resulting image" << std::endl;
  std::cout << "               <size> - blur algorithm radius value" << std::endl;
  std::cout << std::endl;
  std::cout << "resize:        resize <from_name> <to_name> <new_width> <new_height>" << std::endl;
  std::cout << "               resizes image" << std::endl;
  std::cout << "               <from_name> - key value to get image to be resized" << std::endl;
  std::cout << "               <to_name> - key value to put resulting image" << std::endl;
  std::cout << "               <new_width> - new width size to resize <from_name>" << std::endl;
  std::cout << "               <new_height> - new height size to resize <from_name>" << std::endl;
  std::cout << std::endl;
  std::cout << "display:       display <name>" << std::endl;
  std::cout << "               display image <name>" << std::endl;
  std::cout << std::endl;
  std::cout << "exit, quit, q: terminate program execution" << std::endl;
  std::cout << std::endl;
}
//----------------------------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------------------------
