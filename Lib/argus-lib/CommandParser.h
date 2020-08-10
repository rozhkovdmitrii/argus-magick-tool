#ifndef CommandParserH
#define CommandParserH
//----------------------------------------------------------------------------------------------------------------------
#include <string>
#include "CommonTypes.h"
//----------------------------------------------------------------------------------------------------------------------
namespace Argus
{


//----------------------------------------------------------------------------------------------------------------------
class CommandParser
{
public:
  CommandParser(ICommandParserHandler & handler);
  
  bool parseCmdLine(const std::string & cmdLine);

private:
  
  ICommandParserHandler & _handler;
  
  bool checkIfLoadCmd(const std::string & cmdLine);
  bool checkIfStoreCmd(const std::string & cmdLine);
  bool checkIfBlurCmd(const std::string & cmdLine);
  bool checkIfResizeCmd(const std::string & cmdLine);
  bool checkIfQuitCmd(const std::string & cmdLine) const;
  bool checkIfHelpCmd(const std::string & cmdLine);
  static bool getIntValueFromString(const std::string & numStr, int & num);
};
}
//----------------------------------------------------------------------------------------------------------------------
#endif //CommandParserH
