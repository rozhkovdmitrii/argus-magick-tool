#include <iostream>
#include <string>
#include <regex>
//----------------------------------------------------------------------------------------------------------------------
#include "CommandParser.h"
#include "CommonTypes.h"
#include "Command.h"
//----------------------------------------------------------------------------------------------------------------------
namespace Argus
{
//----------------------------------------------------------------------------------------------------------------------
CommandParser::CommandParser(ICommandParserHandler & handler) : _handler(handler)
{
}
//----------------------------------------------------------------------------------------------------------------------
bool CommandParser::parseCmdLine(const std::string & cmdLine)
{
  if (checkIfQuitCmd(cmdLine))
  {
    std::cout << "quit ..." << std::endl;
    return false;
  }
  if (checkIfLoadCmd(cmdLine)   || checkIfStoreCmd(cmdLine) || checkIfBlurCmd(cmdLine) ||
      checkIfResizeCmd(cmdLine) || checkIfHelpCmd(cmdLine))
    return true;
  else
    std::cerr << "Failed to parse sequential command: " << cmdLine << std::endl;
  return true;
}
//----------------------------------------------------------------------------------------------------------------------
bool CommandParser::checkIfLoadCmd(const std::string & cmdLine)
{
  static const std::regex loadCmdRegex(R"(^\s*(?:load|ld)\s+(\w+)\s+(.+)\s*$)");
  std::smatch match;
  if (!std::regex_match(cmdLine, match, loadCmdRegex))
    return false;
  
  _handler.onCmd(LoadCommand(match[1].str(), match[2].str()));
  return true;
}
//----------------------------------------------------------------------------------------------------------------------
bool CommandParser::checkIfStoreCmd(const std::string & cmdLine)
{
  static const std::regex storeCmdRegex(R"(\s*(?:store|s)\s+(\w+)\s+(.+)\s*$)");
  std::smatch match;
  if (!std::regex_match(cmdLine, match, storeCmdRegex))
    return false;
  
  _handler.onCmd(StoreCommand(match[1].str(), match[2].str()));
  return true;
}
//----------------------------------------------------------------------------------------------------------------------
bool CommandParser::checkIfBlurCmd(const std::string & cmdLine)
{
  static const std::regex blurCmdRegex(R"(^\s*blur\s+(\w+)\s+(\w+)\s+(\d+)\s*$)");
  std::smatch match;
  if (!std::regex_match(cmdLine, match, blurCmdRegex))
    return false;
  int blurRadius;
  if (!getIntValueFromString(match[3].str(), blurRadius))
    return false;
  //_handler.onBlurCmd(match[1].str(), match[2].str(), blurRadius);
  return true;
}
//----------------------------------------------------------------------------------------------------------------------
bool CommandParser::checkIfResizeCmd(const std::string & cmdLine)
{
  static const std::regex resizeCmdRegex(R"(^\s*resize\s+(\w+)\s+(\w+)\s+(\d+)\s+(\d+)\s*$)");
  std::smatch match;
  if (!std::regex_match(cmdLine, match, resizeCmdRegex))
    return false;
  int newWidth;
  if (!getIntValueFromString(match[3].str(), newWidth))
    return false;
  int newHeight;
  if (!getIntValueFromString(match[4].str(), newHeight))
    return false;
  //_handler.onResizeCmd(match[1].str(), match[2].str(), newWidth, newHeight);
  return true;
}
//----------------------------------------------------------------------------------------------------------------------
bool CommandParser::getIntValueFromString(const std::string & numStr, int & num)
{
  try {
    num = std::stoi(numStr);
  }
  catch(const std::logic_error & e)
  {
    std::cerr << "Failed to get number from: \"" << numStr << "\", " << e.what() << std::endl;
    return false;
  }
  return true;
}
//----------------------------------------------------------------------------------------------------------------------
bool CommandParser::checkIfQuitCmd(const std::string & cmdLine) const
{
  static const std::regex quitCmdRegex(R"(^\s*(:?exit|quit|q)\s*$)");
  return std::regex_match(cmdLine, quitCmdRegex);
}
//----------------------------------------------------------------------------------------------------------------------
bool CommandParser::checkIfHelpCmd(const std::string & cmdLine)
{
  static const std::regex helpCmdRegex(R"(^\s*(:?help|h)\s*$)");
  if (!std::regex_match(cmdLine, helpCmdRegex))
    return false;
  //_handler.onHelpCmd();
  return true;
}
//----------------------------------------------------------------------------------------------------------------------
}