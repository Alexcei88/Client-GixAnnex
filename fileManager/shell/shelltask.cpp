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
    static TShell shell;
    shell.SetWorkingDirectory(localURL);
    parsingCommand->SetShell(&shell);
    RESULT_EXEC_PROCESS result = shell.ExecuteProcess(command, parsingCommand.get());

    if(result != NO_ERROR)
    {
//        return result;
    }
    RESULT_EXEC_PROCESS codeError = parsingCommand->GetCodeError();
    if(codeError != NO_ERROR)
    {
//        return codeError;
    }
}
//----------------------------------------------------------------------------------------/


