#include "shellcommand.h"

//----------------------------------------------------------------------------------------/
ShellCommand::ShellCommand():
    baseCommand("git-annex ")
{
    shell = boost::make_shared<TShell>();
}
//----------------------------------------------------------------------------------------/
RESULT_EXEC_PROCESS ShellCommand::InitRepositories(const QString& nameRepo)
{
    const QString strCommand = baseCommand + "init " + nameRepo;
    return shell->ExecuteProcess(strCommand);
}
//----------------------------------------------------------------------------------------/
RESULT_EXEC_PROCESS ShellCommand::CD(const QString &localURL)
{
    const QString strCommand = "cd " + localURL;
    return shell->ExecuteProcess(strCommand);
}
//----------------------------------------------------------------------------------------/
RESULT_EXEC_PROCESS ShellCommand::CloneRepositories(const QString& remoteURL, const QString &localURL)
{
    const QString strCommand = "git clone " + remoteURL +" localURL";
    return shell->ExecuteProcess(strCommand);
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

