#include "shellcommand.h"
#include "shelltask.h"
#include "../repository/irepository.h"

// parsing stuff
#include "../parsing_command_out/parsingcommandclone.h"
#include "../parsing_command_out/parsingcommandwhereis.h"
#include "../parsing_command_out/parsingcommandget.h"
#include "../parsing_command_out/parsingcommanddrop.h"
#include "../parsing_command_out/parsingcommandempty.h"

#include <QThreadPool>

using namespace GANN_DEFINE;
//----------------------------------------------------------------------------------------/
ShellCommand::ShellCommand():
    baseCommand("git-annex ")
{}
//----------------------------------------------------------------------------------------/
ShellCommand::~ShellCommand(){}
//----------------------------------------------------------------------------------------/
RESULT_EXEC_PROCESS ShellCommand::InitRepositories(const QString& nameRepo, const TShell *shell)
{
    const QString strCommand = baseCommand + "init " + nameRepo;
    boost::shared_ptr<IParsingCommandOut> receiverParsing(new ParsingCommandEmpty(shell));
    return shell->ExecuteProcess(strCommand, receiverParsing.get());
}
//----------------------------------------------------------------------------------------/
RESULT_EXEC_PROCESS ShellCommand::SetWorkingDirectory(const QString &localURL, const TShell* shell)
{
    shell->SetWorkingDirectory(localURL);
    return NO_ERROR;
}
//----------------------------------------------------------------------------------------/
RESULT_EXEC_PROCESS ShellCommand::CloneRepositories(const QString& remoteURL, QString& folderClone, const boost::shared_ptr<TShell> shell, IRepository *repository)
{
    const QString strCommand = "git clone " + remoteURL;
    boost::shared_ptr<IParsingCommandOut> receiverParsing(new ParsingCommandClone(shell.get(), repository));
    ShellTask* shellTask = new ShellTask(strCommand, receiverParsing, shell);

    QThreadPool::globalInstance()->start(shellTask);
    // ждем окончания клонирования репозитория
    QThreadPool::globalInstance()->waitForDone();

    RESULT_EXEC_PROCESS codeError = receiverParsing->GetCodeError();
    if(codeError != NO_ERROR)
        return codeError;

    QStringList parsingData = receiverParsing->GetParsingData();
    // иначе нет ошибок
    folderClone = parsingData.at(0);
    return NO_ERROR;
}
//----------------------------------------------------------------------------------------/
RESULT_EXEC_PROCESS ShellCommand::AddFile(const QString& path, const boost::shared_ptr<TShell> shell) const
{
    const QString strCommand = baseCommand + "add " + path;
//    return shell->ExecuteProcess(strCommand, receiverParsing[ADD_FILE]);
}
//----------------------------------------------------------------------------------------/
RESULT_EXEC_PROCESS ShellCommand::GetContentFile(const QString& path, const boost::shared_ptr<TShell> shell, IRepository* repository) const
{
    const QString strCommand = baseCommand + "get " + path;
    boost::shared_ptr<IParsingCommandOut> receiverParsing(new ParsingCommandGet(shell.get(), repository));
    ShellTask* shellTask = new ShellTask(strCommand, receiverParsing, shell);

    QThreadPool::globalInstance()->start(shellTask);
    return NO_ERROR;
}
//----------------------------------------------------------------------------------------/
RESULT_EXEC_PROCESS ShellCommand::DropContentFile(const QString& path, const boost::shared_ptr<TShell> shell, IRepository* repository) const
{
    const QString strCommand = baseCommand + "drop " + path;
    boost::shared_ptr<IParsingCommandOut> receiverParsing(new ParsingCommandDrop(shell.get(), repository));
    ShellTask* shellTask = new ShellTask(strCommand, receiverParsing, shell);

    QThreadPool::globalInstance()->start(shellTask);
    return NO_ERROR;
}
//----------------------------------------------------------------------------------------/
RESULT_EXEC_PROCESS ShellCommand::RemoveFile(const QString& path, const boost::shared_ptr<TShell> shell) const
{
#if 0
    const QString strCommand = "git rm" + path;
    boost::shared_ptr<IParsingCommandOut> receiverParsing(new ParsingCommandGet(shell.get()));
    ShellTask* shellTask = new ShellTask(strCommand, receiverParsing, shell);

    QThreadPool::globalInstance()->start(shellTask);
    return NO_ERROR;
//    return shell->ExecuteProcess(strCommand);
#endif
}
//----------------------------------------------------------------------------------------/
RESULT_EXEC_PROCESS ShellCommand::Sync(const boost::shared_ptr<TShell> shell) const
{    
#if 0
    const QString strCommand = baseCommand + "sync";
    boost::shared_ptr<IParsingCommandOut> receiverParsing(new ParsingCommandGet(shell.get()));
    ShellTask* shellTask = new ShellTask(strCommand, receiverParsing, shell);

    QThreadPool::globalInstance()->start(shellTask);
    return NO_ERROR;
#endif
//    return shell->ExecuteProcess(strCommand);
}
//----------------------------------------------------------------------------------------/
RESULT_EXEC_PROCESS ShellCommand::WhereisFiles(const QString& path, const boost::shared_ptr<TShell> shell) const
{
#if 0
    const QString strCommand = baseCommand + "whereis " + path;
    boost::shared_ptr<IParsingCommandOut> receiverParsing(new ParsingCommandGet(shell.get()));
    ShellTask* shellTask = new ShellTask(strCommand, receiverParsing, shell);

    QThreadPool::globalInstance()->start(shellTask);
    return NO_ERROR;
#endif
//    return shell->ExecuteProcess(strCommand);
}
//----------------------------------------------------------------------------------------/
RESULT_EXEC_PROCESS ShellCommand::PullRepositories(const boost::shared_ptr<TShell> shell) const
{
#if 0
    const QString strCommand = "git pull";
    boost::shared_ptr<IParsingCommandOut> receiverParsing(new ParsingCommandGet(shell.get()));
    ShellTask* shellTask = new ShellTask(strCommand, receiverParsing, shell);

    QThreadPool::globalInstance()->start(shellTask);
#endif
}
//----------------------------------------------------------------------------------------/

