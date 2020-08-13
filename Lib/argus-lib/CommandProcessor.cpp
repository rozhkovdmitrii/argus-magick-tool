#include "Log.h"
//----------------------------------------------------------------------------------------------------------------------
#include "CommandProcessor.h"
//----------------------------------------------------------------------------------------------------------------------
namespace Argus
{
void CommandProcessor::onCmd(const ICommand & cmd)
{
  try
  {
    cmd(_imageMap);
    RD_LOG(INF) << "Command performed: " << cmd.toString();
  } catch (const Magick::Exception & e)
  {
    RD_LOG(WRN) << "Unexpected Magick++ error: " << e.what();
    RD_LOG(WRN) << "Command: " << cmd.toString();
  } catch (const std::logic_error & e)
  {
    RD_LOG(WRN) << "Unexpected logic error: " << e.what();
    RD_LOG(WRN) << "Command: " << cmd.toString();
  }
}
//----------------------------------------------------------------------------------------------------------------------
}