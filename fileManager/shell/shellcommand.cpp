#include "shellcommand.h"
#include "shelltask.h"
#include "../repository/irepository.h"
#include "utils/utils.h"
#include "../analyze_execute_command/facadeanalyzecommand.h"

// parsing stuff
#include "../parsing_command_out/parsingcommandclone.h"
#include "../parsing_command_out/parsingcommandwhereis.h"
#include "../parsing_command_out/parsingcommandget.h"
#include "../parsing_command_out/parsingcommanddrop.h"
#include "../parsing_command_out/parsingcommandempty.h"
#include "../parsing_command_out/parsingcommanddirectmode.h"

// analize stuff
#include "../analyze_execute_command/analyzeexecutecommandget.h"
#include "../analyze_execute_command/analyzeexecutecommanddrop.h"

// Qt stuff
#include <QThreadPool>
#include <QRunnable>

using namespace GANN_DEFINE;
using namespace AnalyzeCommand;

//----------------------------------------------------------------------------------------/
ShellCommand::ShellCommand():
    baseCommand("git-annex -j ")
{}
//----------------------------------------------------------------------------------------/
ShellCommand::~ShellCommand(){}
//----------------------------------------------------------------------------------------/
RESULT_EXEC_PROCESS ShellCommand::InitRepositories(const QString& nameRepo)
{
    const QString strCommand = baseCommand + "init " + nameRepo;
    boost::shared_ptr<IParsingCommandOut> receiverParsing(new ParsingCommandEmpty());
    ShellTask* shellTask = new ShellTask(strCommand, localURL, receiverParsing);
    QThreadPool::globalInstance()->start(shellTask);
    // ждем окончания клонирования репозитория
    QThreadPool::globalInstance()->waitForDone();
    RESULT_EXEC_PROCESS codeError = receiverParsing->GetCodeError();
    return codeError;
}
//----------------------------------------------------------------------------------------/
void ShellCommand::SetWorkingDirectory(const QString& localURL)
{
    this->localURL = localURL;
}
//----------------------------------------------------------------------------------------/
RESULT_EXEC_PROCESS ShellCommand::CloneRepositories(const QString& remoteURL, QString& folderClone, FacadeAnalyzeCommand *facade)
{
    const QString strCommand = "git clone " + remoteURL;
    boost::shared_ptr<AnalyzeExecuteCommand> analizeCommand(new AnalyzeExecuteCommand(*facade));
    analizeCommand->SetPathExecuteCommand(localURL);
    boost::shared_ptr<IParsingCommandOut> receiverParsing(new ParsingCommandClone(analizeCommand));
    ShellTask* shellTask = new ShellTask(strCommand, localURL, receiverParsing);

    QThreadPool::globalInstance()->start(shellTask);
    // ждем окончания клонирования репозитория
    QThreadPool::globalInstance()->waitForDone();

    RESULT_EXEC_PROCESS codeError = receiverParsing->GetCodeError();
    if(codeError != NO_ERROR)
        return codeError;

//    QStringList parsingData = receiverParsing->GetParsingData();
    // иначе нет ошибок
//    folderClone = parsingData.at(0);
    return NO_ERROR;
}
//----------------------------------------------------------------------------------------/
RESULT_EXEC_PROCESS ShellCommand::WatchRepository(const QString& path, const bool start) const
{
    const QString paramCommand = start ? "" : " --stop";
    const QString strCommand = baseCommand + "watch " + paramCommand;
    boost::shared_ptr<IParsingCommandOut> receiverParsing(new ParsingCommandEmpty());
#if 0
    TShell shell;
    shell.SetWorkingDirectory(path);
    shell.ExecuteProcess(path, receiverParsing);
#else
    ShellTask* shellTask = new ShellTask(strCommand, path, receiverParsing);
    QThreadPool::globalInstance()->start(shellTask);
    // ждем окончания выполнения команды
    QThreadPool::globalInstance()->waitForDone();
#endif
    return NO_ERROR;
}
//----------------------------------------------------------------------------------------/
RESULT_EXEC_PROCESS ShellCommand::AddFile(const QString& path) const
{
    const QString strCommand = baseCommand + "add " + path;
    return NO_ERROR;
//    return shell->ExecuteProcess(strCommand, receiverParsing[ADD_FILE]);
}
//----------------------------------------------------------------------------------------/
RESULT_EXEC_PROCESS ShellCommand::GetContentFile(const QString& path, FacadeAnalyzeCommand* facade, const bool mode) const
{
    const QString strCommand = baseCommand + "get " + path;
    boost::shared_ptr<AnalyzeExecuteCommandGet> analizeCommand(new AnalyzeExecuteCommandGet(*facade, mode));
    analizeCommand->SetPathExecuteCommand(localURL);
    analizeCommand->SetPathGetContent(Utils::CatDirFile(localURL, path));
    facade->AddGetContentFileQueue(analizeCommand.get());

    boost::shared_ptr<IParsingCommandOut> receiverParsing(new ParsingCommandGet(analizeCommand));
    ShellTask* shellTask = new ShellTask(strCommand, localURL, receiverParsing);
    QThreadPool::globalInstance()->start(shellTask);
    return NO_ERROR;
}
//----------------------------------------------------------------------------------------/
RESULT_EXEC_PROCESS ShellCommand::DropContentFile(const QString& path, FacadeAnalyzeCommand* facade, const bool mode) const
{
    const QString strCommand = baseCommand + "drop " + path;
    const QString fullPathFile = Utils::CatDirFile(localURL, path);
    boost::shared_ptr<AnalyzeExecuteCommandDrop> analizeCommand(new AnalyzeExecuteCommandDrop(*facade));
    analizeCommand->SetPathDropContent(fullPathFile);
    analizeCommand->SetPathExecuteCommand(localURL);

    if(!mode)
    {
        facade->AddDropContentFileQueue(fullPathFile);
    }
    boost::shared_ptr<IParsingCommandOut> receiverParsing(new ParsingCommandDrop(analizeCommand));
    ShellTask* shellTask = new ShellTask(strCommand, localURL, receiverParsing);
    QThreadPool::globalInstance()->start(shellTask);
    return NO_ERROR;
}
//----------------------------------------------------------------------------------------/
RESULT_EXEC_PROCESS ShellCommand::RemoveFile(const QString& path, const bool recursive) const
{
    QString strCommand = "git rm " + path;
    // рекурсивное удаление
    if(recursive)
        strCommand += " -r";

    boost::shared_ptr<IParsingCommandOut> receiverParsing(new ParsingCommandEmpty());
    ShellTask* shellTask = new ShellTask(strCommand, localURL, receiverParsing);

    QThreadPool::globalInstance()->start(shellTask);
    return NO_ERROR;
}
//----------------------------------------------------------------------------------------/
RESULT_EXEC_PROCESS ShellCommand::Sync() const
{    
    const QString strCommand = baseCommand + "sync";
    boost::shared_ptr<IParsingCommandOut> receiverParsing(new ParsingCommandEmpty());
    ShellTask* shellTask = new ShellTask(strCommand, localURL, receiverParsing);

    QThreadPool::globalInstance()->start(shellTask);
    return NO_ERROR;
}
//----------------------------------------------------------------------------------------/
RESULT_EXEC_PROCESS ShellCommand::WhereisFiles(const QString& path, FacadeAnalyzeCommand* facade) const
{
    const QString strCommand = baseCommand + "whereis " + path;
    boost::shared_ptr<IParsingCommandOut> receiverParsing(new ParsingCommandEmpty());
    ShellTask* shellTask = new ShellTask(strCommand, localURL, receiverParsing);

    QThreadPool::globalInstance()->start(shellTask);
    return NO_ERROR;
}
//----------------------------------------------------------------------------------------/
RESULT_EXEC_PROCESS ShellCommand::SetDirectMode(const bool& direct, FacadeAnalyzeCommand* facade) const
{
    const QString strCommand = baseCommand + (direct ? " direct" : " indirect");
    boost::shared_ptr<AnalyzeExecuteCommand> analizeCommand(new AnalyzeExecuteCommand(*facade));
    analizeCommand->SetPathExecuteCommand(localURL);
    boost::shared_ptr<IParsingCommandOut> receiverParsing(new ParsingCommandDirectMode(analizeCommand));
    ShellTask* shellTask = new ShellTask(strCommand, localURL, receiverParsing);

    QThreadPool::globalInstance()->start(shellTask);
    return NO_ERROR;
}
//----------------------------------------------------------------------------------------/
RESULT_EXEC_PROCESS ShellCommand::FindFileInPath(const QString &path, FacadeAnalyzeCommand* facade) const
{

}
//----------------------------------------------------------------------------------------/
