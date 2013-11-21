#include "shelltask.h"
#include "define.h"
#include "tshell.h"
#include "../parsing_command_out/iparsingcommandout.h"
#include "../parsing_command_out/parsingcommandempty.h"

using namespace GANN_DEFINE;
//----------------------------------------------------------------------------------------/
ShellTask::ShellTask(const QString strCommand, const QString localURL, boost::shared_ptr<IParsingCommandOut> parsingCommand):
    command(strCommand)
  , localURL(localURL)
  , parsingCommand(parsingCommand)
{}
//----------------------------------------------------------------------------------------/
void ShellTask::run()
{
    TShell shell;
    shell.SetWorkingDirectory(localURL);
    parsingCommand->SetShell(&shell);
    shell.ExecuteProcess(command, parsingCommand.get());
}
//----------------------------------------------------------------------------------------/


