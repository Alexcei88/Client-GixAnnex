#include "shellcommand.h"

// parsing stuff
#include "../parsing_command_out/parsingcommandclone.h"
#include "../parsing_command_out/parsingcommandwhereis.h"
#include "../parsing_command_out/parsingcommandget.h"

using namespace GANN_DEFINE;
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
    if(result != NO_ERROR)
        return result;

    RESULT_EXEC_PROCESS codeError = receiverParsing[CLONE_REPO]->GetCodeError();
    if(codeError != NO_ERROR)
        return codeError;

    QStringList parsingData = receiverParsing[CLONE_REPO]->GetParsingData();
    // иначе нет ошибок
    folderClone = parsingData.at(0);
}
//----------------------------------------------------------------------------------------/
RESULT_EXEC_PROCESS ShellCommand::AddFile(const QString& path) const
{
    const QString strCommand = baseCommand + "add " + path;
    return shell->ExecuteProcess(strCommand, receiverParsing[ADD_FILE]);
}
//----------------------------------------------------------------------------------------/
RESULT_EXEC_PROCESS ShellCommand::GetContentFile(const QString& path) const
{
    const QString strCommand = baseCommand + "get " + path;

#if 0
    RESULT_EXEC_PROCESS result = shell->ExecuteProcess(strCommand, receiverParsing[GET_CONTENT]);
    if(result != NO_ERROR)
        return result;
    RESULT_EXEC_PROCESS codeError = receiverParsing[GET_CONTENT]->GetCodeError();

    if(codeError != NO_ERROR)
        return codeError;
    return result;
#else
    GetContentTask* task = new GetContentTask(strCommand, receiverParsing[GET_CONTENT]);
    GetContentTask* task1 = new GetContentTask(strCommand, receiverParsing[GET_CONTENT]);

    QThreadPool::globalInstance()->setMaxThreadCount(1);
    QThreadPool::globalInstance()->start(task);
    QThreadPool::globalInstance()->start(task1);
#endif
}
//----------------------------------------------------------------------------------------/
RESULT_EXEC_PROCESS ShellCommand::DropContentFile(const QString& path) const
{
    const QString strCommand = baseCommand + "drop " + path;
    RESULT_EXEC_PROCESS result = shell->ExecuteProcess(strCommand, receiverParsing[GET_CONTENT]);
    if(result != NO_ERROR)
        return result;
    RESULT_EXEC_PROCESS codeError = receiverParsing[GET_CONTENT]->GetCodeError();

    if(codeError != NO_ERROR)
        return codeError;

    return result;
}
//----------------------------------------------------------------------------------------/
RESULT_EXEC_PROCESS ShellCommand::RemoveFile(const QString& path) const
{
    const QString strCommand = "git rm" + path;
//    return shell->ExecuteProcess(strCommand);
}
//----------------------------------------------------------------------------------------/
RESULT_EXEC_PROCESS ShellCommand::Sync() const
{
    const QString strCommand = baseCommand + "sync";
//    return shell->ExecuteProcess(strCommand);
}
//----------------------------------------------------------------------------------------/
RESULT_EXEC_PROCESS ShellCommand::WhereisFiles(const QString& path) const
{
    const QString strCommand = baseCommand + "whereis " + path;
//    return shell->ExecuteProcess(strCommand);
}
//----------------------------------------------------------------------------------------/
RESULT_EXEC_PROCESS ShellCommand::PullRepositories() const
{
    const QString strCommand = "git pull";

}
//----------------------------------------------------------------------------------------/

