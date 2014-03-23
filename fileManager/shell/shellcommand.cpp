#include "shellcommand.h"
#include "shelltask.h"
#include "../repository/irepository.h"
#include "utils/utils.h"
#include "../analyze_execute_command/facadeanalyzecommand.h"
#include "facade_shellcommand.h"

// parsing stuff
#include "../parsing_command_out/parsingcommandclone.h"
#include "../parsing_command_out/parsingcommandwhereis.h"
#include "../parsing_command_out/parsingcommandget.h"
#include "../parsing_command_out/parsingcommanddrop.h"
#include "../parsing_command_out/parsingcommandempty.h"
#include "../parsing_command_out/parsingcommanddirectmode.h"
#include "../parsing_command_out/parsingcommandstatus.h"

// analize stuff
#include "../analyze_execute_command/analyzeexecutecommandget.h"
#include "../analyze_execute_command/analyzeexecutecommanddrop.h"
#include "../analyze_execute_command/analyzeexecutecommandclone.h"
#include "../analyze_execute_command/analyzeexecutecommandinit.h"
#include "../analyze_execute_command/analyzeexecutecommandchangedirectmode.h"
#include "../analyze_execute_command/analizeexecutecommandstatus.h"

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
RESULT_EXEC_PROCESS ShellCommand::InitRepositories(const QString& nameRepo, FacadeAnalyzeCommand *facade)
{
    const QString strCommand = baseCommand + "init " + nameRepo;
    boost::shared_ptr<AnalyzeExecuteCommandInit> analizeCommand(new AnalyzeExecuteCommandInit(*facade));
    boost::shared_ptr<IParsingCommandOut> receiverParsing(new ParsingCommandEmpty(analizeCommand));
    ShellTask* shellTask = new ShellTask(strCommand, localURL, receiverParsing);
    QThreadPool::globalInstance()->start(shellTask);
    return NO_ERROR;
}
//----------------------------------------------------------------------------------------/
void ShellCommand::SetWorkingDirectory(const QString& localURL)
{
    this->localURL = localURL;
}
//----------------------------------------------------------------------------------------/
RESULT_EXEC_PROCESS ShellCommand::CloneRepositories(const QString& remoteURL, const QString localURL, FacadeAnalyzeCommand *facade)
{
    const QString strCommand = "git clone " + remoteURL;
    boost::shared_ptr<AnalyzeExecuteCommandClone> analizeCommand(new AnalyzeExecuteCommandClone(*facade));
    analizeCommand->SetPathExecuteCommand(localURL);
    boost::shared_ptr<IParsingCommandOut> receiverParsing(new ParsingCommandClone(analizeCommand));
    ShellTask* shellTask = new ShellTask(strCommand, localURL, receiverParsing);
    FacadeShellCommand::TryStartNextCommand("clone", shellTask, facade->GetRepository());
    return NO_ERROR;
}
//----------------------------------------------------------------------------------------/
RESULT_EXEC_PROCESS ShellCommand::WatchRepository(const QString& path, const bool start) const
{
    const QString paramCommand = start ? "" : " --stop";
    const QString strCommand = baseCommand + "watch " + paramCommand;
    boost::shared_ptr<IParsingCommandOut> receiverParsing(new ParsingCommandEmpty());
    ShellTask* shellTask = new ShellTask(strCommand, path, receiverParsing);
    QThreadPool::globalInstance()->start(shellTask);
    // ждем окончания выполнения команды
    QThreadPool::globalInstance()->waitForDone();
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
    FacadeShellCommand::TryStartNextCommand("get", shellTask, facade->GetRepository());
    return NO_ERROR;
}
//----------------------------------------------------------------------------------------/
RESULT_EXEC_PROCESS ShellCommand::DropContentFile(const QString& path, FacadeAnalyzeCommand* facade, const bool mode) const
{
    const QString strCommand = baseCommand + "drop " + path;
    const QString fullPathFile = Utils::CatDirFile(localURL, path);
    boost::shared_ptr<AnalyzeExecuteCommandDrop> analizeCommand(new AnalyzeExecuteCommandDrop(*facade, mode));
    analizeCommand->SetPathDropContent(fullPathFile);
    analizeCommand->SetPathExecuteCommand(localURL);
    facade->AddDropContentFileQueue(analizeCommand.get());

    boost::shared_ptr<IParsingCommandOut> receiverParsing(new ParsingCommandDrop(analizeCommand));
    ShellTask* shellTask = new ShellTask(strCommand, localURL, receiverParsing);
    FacadeShellCommand::TryStartNextCommand("drop", shellTask, facade->GetRepository());
    return NO_ERROR;
}
//----------------------------------------------------------------------------------------/
RESULT_EXEC_PROCESS ShellCommand::RemoveFile(const QString& path, const bool mode, const bool recursive) const
{  

    assert(0);
#if 0
    if(!mode)
    {
        QString strCommand = "git rm " + path;
        // рекурсивное удаление
        if(recursive)
            strCommand += " -r";

        boost::shared_ptr<IParsingCommandOut> receiverParsing(new ParsingCommandEmpty());
        ShellTask* shellTask = new ShellTask(strCommand, localURL, receiverParsing);

        FacadeShellCommand::TryStartNextCommand("git rm", shellTask, facade->GetRepository());
    }
    // физическое удаление файла(директории)
    QString strCommand = "rm " + path;
    // рекурсивное удаление
    if(recursive)
        strCommand += " -r";

    strCommand +=" -f";

    boost::shared_ptr<IParsingCommandOut> receiverParsing(new ParsingCommandEmpty());
    ShellTask* shellTask = new ShellTask(strCommand, localURL, receiverParsing);
    FacadeShellCommand::TryStartNextCommand("rm", shellTask, facade->GetRepository());
    return NO_ERROR;
#endif
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
    boost::shared_ptr<AnalyzeExecuteCommandChangeDirectMode> analizeCommand(new AnalyzeExecuteCommandChangeDirectMode(*facade));
    analizeCommand->SetPathExecuteCommand(localURL);
    boost::shared_ptr<IParsingCommandOut> receiverParsing(new ParsingCommandDirectMode(analizeCommand));

    ShellTask* shellTask = new ShellTask(strCommand, localURL, receiverParsing);
    FacadeShellCommand::TryStartNextCommand(direct ? " direct" : " indirect", shellTask, facade->GetRepository());
    return NO_ERROR;
}
//----------------------------------------------------------------------------------------/
RESULT_EXEC_PROCESS ShellCommand::FindFileInPath(const QString &path, FacadeAnalyzeCommand* facade) const
{
    Q_UNUSED(path);
    Q_UNUSED(facade);
    return NO_ERROR;
}
//----------------------------------------------------------------------------------------/
GANN_DEFINE::RESULT_EXEC_PROCESS ShellCommand::CopyFileToOtherRepository(const QString& file, const QString& nameRepository)
{
    assert(0);
}
//----------------------------------------------------------------------------------------/
GANN_DEFINE::RESULT_EXEC_PROCESS ShellCommand::MoveFileToOtherRepository(const QString& file, const QString& nameRepository)
{
    assert(0);
}
//----------------------------------------------------------------------------------------/
GANN_DEFINE::RESULT_EXEC_PROCESS ShellCommand::GetStatusRepository(FacadeAnalyzeCommand* facade) const
{
    const QString strCommand = baseCommand + " status";
    boost::shared_ptr<AnalizeExecuteCommandStatus> analizeCommand(new AnalizeExecuteCommandStatus(*facade));
    analizeCommand->SetPathExecuteCommand(localURL);
    boost::shared_ptr<IParsingCommandOut> receiverParsing(new ParsingCommandStatus(analizeCommand));

    ShellTask* shellTask = new ShellTask(strCommand, localURL, receiverParsing);
    FacadeShellCommand::TryStartNextCommand("status", shellTask, facade->GetRepository());
    return NO_ERROR;
}
//----------------------------------------------------------------------------------------/


