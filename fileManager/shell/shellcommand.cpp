#include "shellcommand.h"

// parsing stuff
#include "../parsing_command_out/parsingcommandclone.h"
#include "../parsing_command_out/parsingcommandwhereis.h"
#include "../parsing_command_out/parsingcommandget.h"

//----------------------------------------------------------------------------------------/
ShellCommand::ShellCommand():
     shell(TShell::GetInstance())
    ,baseCommand("git-annex ")
{
    receiverParsing.resize(COUNT_TYPE_COMMAND);
    // инициализация массива соот классами парсинга
    receiverParsing[INIT_REPO]  = new ParsingCommandClone();
    receiverParsing[CLONE_REPO] = new ParsingCommandClone();
    receiverParsing[ADD_FILE]   = new ParsingCommandClone();
    receiverParsing[GET_CONTENT] = new ParsingCommandClone();
    receiverParsing[WHEREIS_COMMAND] = new ParsingCommandClone();

}
//----------------------------------------------------------------------------------------/
ShellCommand::~ShellCommand()
{
    TShell::RemoveInstance();
    foreach (IParsingCommandOut* receiver, receiverParsing)
    {
        delete receiver;
        receiver = 0l;
    }
}
//----------------------------------------------------------------------------------------/
RESULT_EXEC_PROCESS ShellCommand::InitRepositories(const QString& nameRepo)
{
    const QString strCommand = baseCommand + "init " + nameRepo;
    return shell->ExecuteProcess(strCommand, receiverParsing[INIT_REPO]);
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
    RESULT_EXEC_PROCESS result = shell->ExecuteProcess(strCommand, receiverParsing[CLONE_REPO]);
    QStringList parsingData = receiverParsing[CLONE_REPO]->GetParsingData();
    if(result != NO_ERROR)
        return result;
    if(!parsingData.empty())
        return  IGNORE_COMMAND;
    folderClone = parsingData.at(0);
}
//----------------------------------------------------------------------------------------/
RESULT_EXEC_PROCESS ShellCommand::AddFile(const QString& path)
{
    const QString strCommand = baseCommand + "add " + path;
    return shell->ExecuteProcess(strCommand, receiverParsing[ADD_FILE]);
}
//----------------------------------------------------------------------------------------/
RESULT_EXEC_PROCESS ShellCommand::GetContentFile(const QString& path)
{
    const QString strCommand = baseCommand + "get " + path;
//    return shell->ExecuteProcess(strCommand);
}
//----------------------------------------------------------------------------------------/
RESULT_EXEC_PROCESS ShellCommand::DropContentFile(const QString& path)
{
    const QString strCommand = baseCommand + "drop " + path;
//    return shell->ExecuteProcess(strCommand);
}
//----------------------------------------------------------------------------------------/
RESULT_EXEC_PROCESS ShellCommand::RemoveFile(const QString& path)
{
    const QString strCommand = "git rm" + path;
//    return shell->ExecuteProcess(strCommand);
}
//----------------------------------------------------------------------------------------/
RESULT_EXEC_PROCESS ShellCommand::Sync()
{
    const QString strCommand = baseCommand + "sync";
//    return shell->ExecuteProcess(strCommand);
}
//----------------------------------------------------------------------------------------/
RESULT_EXEC_PROCESS ShellCommand::WhereisFiles(const QString& path, QString& result)
{
    const QString strCommand = baseCommand + "whereis " + path;
//    return shell->ExecuteProcess(strCommand);
}
//----------------------------------------------------------------------------------------/
