#include "facadeanalyzecommand.h"
#include "../repository/irepository.h"
#include "facadeapplication.h"
#include "utils/utils.h"
#include "analizediraction.h"
#include "analyzeexecutecommandget.h"
#include "analyzeexecutecommanddrop.h"
#include "../shell/facade_shellcommand.h"

// std stuff
#include <iostream>
#include <assert.h>

using namespace AnalyzeCommand;
using namespace Utils;

std::unique_ptr<std::atomic_flag> FacadeAnalyzeCommand::atomicFlagExecuteCommand =
        std::unique_ptr<std::atomic_flag>(new std::atomic_flag(ATOMIC_FLAG_INIT));
QFileInfo FacadeAnalyzeCommand::fileInfo;
//----------------------------------------------------------------------------------------/
FacadeAnalyzeCommand::FacadeAnalyzeCommand(IRepository* repository):
    repository(repository)
  , managerRestartCommand(new ManagerRestartCommand(repository))
{}
//----------------------------------------------------------------------------------------/
FacadeAnalyzeCommand::~FacadeAnalyzeCommand()
{}
//----------------------------------------------------------------------------------------/
void FacadeAnalyzeCommand::SetCurrentPathRepository(const QString& currentPath)
{
    AtomicLock flag(atomicFlagExecuteCommand.get());
    Q_UNUSED(flag);

    currentPathRepository.setPath(currentPath);
}
//----------------------------------------------------------------------------------------/
void FacadeAnalyzeCommand::SetCurrentExecuteCommand(AnalyzeExecuteCommand* command)
{
    AtomicLock flag(atomicFlagExecuteCommand.get());
    Q_UNUSED(flag);

    currentAnalyzeExecuteCommand = command;
}
//----------------------------------------------------------------------------------------/
void FacadeAnalyzeCommand::ResetCurrentExecuteCommand()
{
    AtomicLock flag(atomicFlagExecuteCommand.get());
    Q_UNUSED(flag);

    currentAnalyzeExecuteCommand = nullptr;
    // запускаем следующую команду, если она там есть
    FacadeShellCommand::TryStartNextCommand();
}
//----------------------------------------------------------------------------------------/
void FacadeAnalyzeCommand::EndCloneRepository(const bool& successfully, const QString& information) const
{
    FacadeApplication::getInstance()->EndCloneRepository(successfully, information);
}
//----------------------------------------------------------------------------------------/
void FacadeAnalyzeCommand::InitNewRepository() const
{
    FacadeApplication::getInstance()->InitNewRepository();
}
//----------------------------------------------------------------------------------------/
void FacadeAnalyzeCommand::AddGetContentFileQueue(AnalyzeExecuteCommandGet* commandGet)
{
    AtomicLock flag(atomicFlagExecuteCommand.get());
    Q_UNUSED(flag);

    listCommandGet.push_back(commandGet);
}
//----------------------------------------------------------------------------------------/
void FacadeAnalyzeCommand::RemoveGetContentFileQueue(AnalyzeExecuteCommandGet *commandGet)
{
    AtomicLock flag(atomicFlagExecuteCommand.get());
    Q_UNUSED(flag);

    auto it = std::find(listCommandGet.begin(), listCommandGet.end(), commandGet);
    if(it != listCommandGet.end())
        listCommandGet.erase(it);
}
//----------------------------------------------------------------------------------------/
bool FacadeAnalyzeCommand::IsGettingContentFileDir(const QString& file) const
{
    AtomicLock flag(atomicFlagExecuteCommand.get());
    Q_UNUSED(flag);

    for(AnalyzeExecuteCommandGet* command : listCommandGet)
    {
        if(command->IsGettingContentFileDir(currentPathRepository.path(), file))
            return true;
    }
    return false;
}
//----------------------------------------------------------------------------------------/
bool FacadeAnalyzeCommand::IsErrorGettingContentFileDir(const QString& file) const
{
    AtomicLock flag(atomicFlagExecuteCommand.get());
    Q_UNUSED(flag);

    return AnalyzeExecuteCommandGet::IsErrorGettingContentFileDir(currentPathRepository.path(), file);
}
//----------------------------------------------------------------------------------------/
void FacadeAnalyzeCommand::AddDropContentFileQueue(AnalyzeExecuteCommandDrop *commandDrop)
{
    AtomicLock flag(atomicFlagExecuteCommand.get());
    Q_UNUSED(flag);

    listCommandDrop.push_back(commandDrop);
}
//----------------------------------------------------------------------------------------/
void FacadeAnalyzeCommand::RemoveDropContentFileQueue(AnalyzeExecuteCommandDrop *commandDrop)
{
    AtomicLock flag(atomicFlagExecuteCommand.get());
    Q_UNUSED(flag);

    auto it = std::find(listCommandDrop.begin(), listCommandDrop.end(), commandDrop);
    if(it != listCommandDrop.end())
        listCommandDrop.erase(it);
}
//----------------------------------------------------------------------------------------/
bool FacadeAnalyzeCommand::IsDroppingContentFileDir(const QString& file) const
{
    AtomicLock flag(atomicFlagExecuteCommand.get());
    Q_UNUSED(flag);

    for(AnalyzeExecuteCommandDrop* command : listCommandDrop)
    {
        if(command->IsDroppingContentFileDir(currentPathRepository.path(), file))
            return true;
    }
    return false;
}
//----------------------------------------------------------------------------------------/
bool FacadeAnalyzeCommand::IsErrorDroppingContentFileDir(const QString& file) const
{
    AtomicLock flag(atomicFlagExecuteCommand.get());
    Q_UNUSED(flag);

    return AnalyzeExecuteCommandDrop::IsErrorDroppingContentFileDir(currentPathRepository.path(), file);
}
//----------------------------------------------------------------------------------------/
void FacadeAnalyzeCommand::ErrorChangeDirectMode()
{
    if(repository)
        repository->OnErrorChangeDirectMode("fffff");
}
//----------------------------------------------------------------------------------------/
void FacadeAnalyzeCommand::ChangeDirectMode(const bool& mode)
{
    if(repository)
        repository->OnChangeDirectMode(mode);
}
//----------------------------------------------------------------------------------------/
void FacadeAnalyzeCommand::ExecuteAddActionForAnalizeCommand()
{
    if(currentAnalyzeExecuteCommand)
        currentAnalyzeExecuteCommand->ExecuteAddActionForAnalizeExecuteCommand();
}
//----------------------------------------------------------------------------------------/
bool FacadeAnalyzeCommand::ReStartCommand(const QString& command, const QVariant arg0)
{
    const QMetaObject* metaObject = managerRestartCommand->metaObject();
    std::cout<<metaObject->methodCount()<<std::endl;
    for(int i = metaObject->methodOffset(); i < metaObject->methodCount(); ++i)
    {
        std::cout<<QString::fromLatin1(metaObject->method(i).name()).toStdString()<<std::endl;
    }

    QMetaObject::invokeMethod(managerRestartCommand.get(), "setDirectMode", Q_ARG(QVariant, arg0));
}
//----------------------------------------------------------------------------------------/
bool FacadeAnalyzeCommand::DirContainsFile(const QString& dir, const QString& file)
{
    fileInfo.setFile(dir);
    if(fileInfo.isFile() || fileInfo.isSymLink())
        return dir == file;
    else
    {
        const QString dir_ = dir + "/";
        return file.startsWith(dir_);
    }
}
//----------------------------------------------------------------------------------------/
