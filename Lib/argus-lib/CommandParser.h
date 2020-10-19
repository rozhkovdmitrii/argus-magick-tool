//----------------------------------------------------------------------------------------------------------------------
// CommandParser - provides lexical command line analysis and creates appropriate commands
// Created by Rozhkov Dmitrii rozhkovdmitrii@yandex.ru for Argus-soft on 09.08.2020.
//----------------------------------------------------------------------------------------------------------------------
#ifndef CommandParserH
#define CommandParserH
//----------------------------------------------------------------------------------------------------------------------
namespace Argus
{
//----------------------------------------------------------------------------------------------------------------------
class ICommandParserHandler;
//----------------------------------------------------------------------------------------------------------------------
class CommandParser : protected rozhkovdmitrii::LoggedObject
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
  bool checkIfDisplayCmd(const std::string & cmdLine) const;
  
  bool getIntValueFromString(const std::string & numStr, int & num) const;
};
}
//----------------------------------------------------------------------------------------------------------------------
#endif //CommandParserH
