#include <regex>
//----------------------------------------------------------------------------------------------------------------------
#include "Log.h"
#include "Commands.h"
//----------------------------------------------------------------------------------------------------------------------
#include "CommandParser.h"
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
    RD_LOG(INF) << "quit ...";
    return false;
  }
  if (checkIfLoadCmd(cmdLine)   || checkIfStoreCmd(cmdLine) || checkIfBlurCmd(cmdLine) ||
      checkIfResizeCmd(cmdLine) || checkIfHelpCmd(cmdLine)  || checkIfDisplayCmd(cmdLine))
    return true;
  else
    RD_LOG(WRN) << "Failed to parse command: \"" << cmdLine << "\"";
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
  int blurSize;
  if (!getIntValueFromString(match[3].str(), blurSize))
  {
    RD_LOG(WRN) << "Failed to read blurRadius from: \"" << match[3].str() << "\"";
    return false;
  }
  _handler.onCmd(BlurCommand(match[1].str(), match[2].str(), blurSize));
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
  _handler.onCmd(ResizeCommand(match[1].str(), match[2].str(), newWidth, newHeight));
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
    RD_LOG(WRN) << "Failed to get number from: \"" << numStr << "\", " << e.what();
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
  _handler.onHelpCmd();
  return true;
}
//----------------------------------------------------------------------------------------------------------------------
bool CommandParser::checkIfDisplayCmd(const std::string & cmdLine) const
{
  static const std::regex displayCmdRegex(R"(^\s*display\s+(\w+)\s*$)");
  std::smatch match;
  if (!std::regex_match(cmdLine, match, displayCmdRegex))
    return false;
  _handler.onCmd(DisplayCommand(match[1].str()));
  return true;
}
//----------------------------------------------------------------------------------------------------------------------
}