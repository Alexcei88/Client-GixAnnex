#include "shellcommand.h"

//----------------------------------------------------------------------------------------/
ShellCommand::ShellCommand():
    baseCommand("git-annex ")
{
    shell = boost::make_shared<TShell>();
}
//----------------------------------------------------------------------------------------/
int ShellCommand::InitRepositories(const QString& nameRepo)
{
    const QString strCommand = baseCommand + "init " + nameRepo;
    return shell->ExecuteProcess(strCommand);
}
//----------------------------------------------------------------------------------------/
int ShellCommand::AddFile(const QString& path)
{
    const QString strCommand = baseCommand + "add " + path;
    return shell->ExecuteProcess(strCommand);
}
//----------------------------------------------------------------------------------------/
int ShellCommand::GetContentFile(const QString& path)
{
    const QString strCommand = baseCommand + "get " + path;
    return shell->ExecuteProcess(strCommand);
}
//----------------------------------------------------------------------------------------/
int ShellCommand::DropContentFile(const QString& path)
{
    const QString strCommand = baseCommand + "drop " + path;
    return shell->ExecuteProcess(strCommand);
}
//----------------------------------------------------------------------------------------/
int ShellCommand::RemoveFile(const QString& path)
{
    const QString strCommand = "git rm" + path;
    return shell->ExecuteProcess(strCommand);
}
//----------------------------------------------------------------------------------------/
int ShellCommand::Sync()
{
    const QString strCommand = baseCommand + "sync";
    return shell->ExecuteProcess(strCommand);

}
//----------------------------------------------------------------------------------------/
int ShellCommand::WhereisFiles(const QString& path, QString& result)
{
    const QString strCommand = baseCommand + "whereis " + path;
    return shell->ExecuteProcess(strCommand);
}
//----------------------------------------------------------------------------------------/

