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
    TRACE(INF) << "Command performed: " << cmd.toString();
  } catch (const Magick::Exception & e)
  {
    TRACE(WRN) << "Unexpected Magick++ error: " << e.what() << " while command was being processed: " << cmd.toString();
  } catch (const std::logic_error & e)
  {
    TRACE(WRN) << "Unexpected logic error: " << e.what() << " while command being was processed: " << cmd.toString();
  }
}
//----------------------------------------------------------------------------------------------------------------------
}