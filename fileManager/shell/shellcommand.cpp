#include "shellcommand.h"

//----------------------------------------------------------------------------------------/
ShellCommand::ShellCommand():
     baseCommand("git-annex ")
    ,shell(TShell::GetInstance())
{
}
//----------------------------------------------------------------------------------------/
ShellCommand::~ShellCommand()
{
    TShell::RemoveInstance();
}
//----------------------------------------------------------------------------------------/
RESULT_EXEC_PROCESS ShellCommand::InitRepositories(const QString& nameRepo)
{
    const QString strCommand = baseCommand + "init " + nameRepo;
    return shell->ExecuteProcess(strCommand);
}
//----------------------------------------------------------------------------------------/
RESULT_EXEC_PROCESS ShellCommand::SetWorkingDirectory(const QString &localURL)
{
    shell->SetWorkingDirectory(localURL);
    return NO_ERROR;
}
//----------------------------------------------------------------------------------------/
RESULT_EXEC_PROCESS ShellCommand::CloneRepositories(const QString& remoteURL, QString& folderClone)
{
    QStringList stdOut;
    const QString strCommand = "git clone " + remoteURL;
    RESULT_EXEC_PROCESS result = shell->ExecuteProcess(strCommand, stdOut);
    if(result != NO_ERROR)
        return result;
}
//----------------------------------------------------------------------------------------/
RESULT_EXEC_PROCESS ShellCommand::AddFile(const QString& path)
{
    const QString strCommand = baseCommand + "add " + path;
    return shell->ExecuteProcess(strCommand);
}
//----------------------------------------------------------------------------------------/
RESULT_EXEC_PROCESS ShellCommand::GetContentFile(const QString& path)
{
    const QString strCommand = baseCommand + "get " + path;
    return shell->ExecuteProcess(strCommand);
}
//----------------------------------------------------------------------------------------/
RESULT_EXEC_PROCESS ShellCommand::DropContentFile(const QString& path)
{
    const QString strCommand = baseCommand + "drop " + path;
    return shell->ExecuteProcess(strCommand);
}
//----------------------------------------------------------------------------------------/
RESULT_EXEC_PROCESS ShellCommand::RemoveFile(const QString& path)
{
    const QString strCommand = "git rm" + path;
    return shell->ExecuteProcess(strCommand);
}
//----------------------------------------------------------------------------------------/
RESULT_EXEC_PROCESS ShellCommand::Sync()
{
    const QString strCommand = baseCommand + "sync";
    return shell->ExecuteProcess(strCommand);

}
//----------------------------------------------------------------------------------------/
RESULT_EXEC_PROCESS ShellCommand::WhereisFiles(const QString& path, QString& result)
{
    const QString strCommand = baseCommand + "whereis " + path;
    return shell->ExecuteProcess(strCommand);
}
//----------------------------------------------------------------------------------------/

