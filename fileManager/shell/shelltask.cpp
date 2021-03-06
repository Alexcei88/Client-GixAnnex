#include "shelltask.h"
#include "define.h"
#include "tshell.h"
#include "../parsing_command_out/iparsingcommandout.h"
#include "../parsing_command_out/parsingcommandempty.h"

using namespace GANN_DEFINE;
//----------------------------------------------------------------------------------------/
ShellTask::ShellTask(const QString& strCommand, const QString localURL, boost::shared_ptr<IParsingCommandOut> parsingCommand):
    command(strCommand)
  , parsingCommand(parsingCommand)
  , localURL(localURL)
  , shell(nullptr)
{}
//----------------------------------------------------------------------------------------/
ShellTask::~ShellTask()
{
    if(shell)
    {
        shell->TerminateProcess();
        delete shell;
        shell = nullptr;
    }
}
//----------------------------------------------------------------------------------------/
void ShellTask::run()
{
    shell = new TShell;
    shell->SetWorkingDirectory(localURL);
    parsingCommand->SetShell(shell);
    shell->ExecuteProcess(command, parsingCommand.get());
}
//----------------------------------------------------------------------------------------/
void ShellTask::TerminateProcess()
{
    shell->TerminateProcess();
}
//----------------------------------------------------------------------------------------/


