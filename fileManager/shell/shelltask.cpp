#include "shelltask.h"
#include "define.h"
#include "tshell.h"
#include "../parsing_command_out/iparsingcommandout.h"

using namespace GANN_DEFINE;
//----------------------------------------------------------------------------------------/
ShellTask::ShellTask(const QString& strCommand, IParsingCommandOut* parsingCommand, const TShell* shell):
    command(strCommand)
  , parsingCommand(parsingCommand)
  , shell(shell)
{
}
//----------------------------------------------------------------------------------------/
void ShellTask::run()
{
    RESULT_EXEC_PROCESS result = shell->ExecuteProcess(command, parsingCommand);
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


