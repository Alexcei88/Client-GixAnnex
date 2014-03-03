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

std::atomic_flag* FacadeAnalyzeCommand::atomicFlagExecuteCommand = new std::atomic_flag(ATOMIC_FLAG_INIT);
QFileInfo FacadeAnalyzeCommand::fileInfo;
//----------------------------------------------------------------------------------------/
FacadeAnalyzeCommand::FacadeAnalyzeCommand():
    repository(0l)
{}
//----------------------------------------------------------------------------------------/
FacadeAnalyzeCommand::FacadeAnalyzeCommand(IRepository* repository):
    repository(repository)
{}
//----------------------------------------------------------------------------------------/
FacadeAnalyzeCommand::~FacadeAnalyzeCommand()
{
    delete atomicFlagExecuteCommand;
    atomicFlagExecuteCommand = 0l;
}
//----------------------------------------------------------------------------------------/
void FacadeAnalyzeCommand::SetCurrentPathRepository(const QString& currentPath)
{
    AtomicLock flag(atomicFlagExecuteCommand);
    Q_UNUSED(flag);

    currentPathRepository.setPath(currentPath);
}
//----------------------------------------------------------------------------------------/
void FacadeAnalyzeCommand::SetCurrentExecuteCommand(AnalyzeExecuteCommand* command)
{
    AtomicLock flag(atomicFlagExecuteCommand);
    Q_UNUSED(flag);

    currentAnalyzeExecuteCommand = command;
}
//----------------------------------------------------------------------------------------/
void FacadeAnalyzeCommand::ResetCurrentExecuteCommand()
{
    AtomicLock flag(atomicFlagExecuteCommand);
    Q_UNUSED(flag);

    currentAnalyzeExecuteCommand = nullptr;
    // запускаем следующуйю команду, если она там есть
    FacadeShellCommand::getInstance()->TryStartNextcommand();
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
    AtomicLock flag(atomicFlagExecuteCommand);
    Q_UNUSED(flag);

    listCommandGet.push_back(commandGet);
}
//----------------------------------------------------------------------------------------/
void FacadeAnalyzeCommand::RemoveGetContentFileQueue(AnalyzeExecuteCommandGet *commandGet)
{
    AtomicLock flag(atomicFlagExecuteCommand);
    Q_UNUSED(flag);

    auto it = std::find(listCommandGet.begin(), listCommandGet.end(), commandGet);
    assert(it != listCommandGet.end());
    listCommandGet.erase(it);
}
//----------------------------------------------------------------------------------------/
bool FacadeAnalyzeCommand::IsGettingContentFileDir(const QString& file) const
{
    AtomicLock flag(atomicFlagExecuteCommand);
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
    AtomicLock flag(atomicFlagExecuteCommand);
    Q_UNUSED(flag);

    return AnalyzeExecuteCommandGet::IsErrorGettingContentFileDir(currentPathRepository.path(), file);
}
//----------------------------------------------------------------------------------------/
void FacadeAnalyzeCommand::AddDropContentFileQueue(AnalyzeExecuteCommandDrop *commandDrop)
{
    AtomicLock flag(atomicFlagExecuteCommand);
    Q_UNUSED(flag);

    listCommandDrop.push_back(commandDrop);
}
//----------------------------------------------------------------------------------------/
void FacadeAnalyzeCommand::RemoveDropContentFileQueue(AnalyzeExecuteCommandDrop *commandDrop)
{
    AtomicLock flag(atomicFlagExecuteCommand);
    Q_UNUSED(flag);

    auto it = std::find(listCommandDrop.begin(), listCommandDrop.end(), commandDrop);
    assert(it != listCommandDrop.end());
    listCommandDrop.erase(it);
}
//----------------------------------------------------------------------------------------/
bool FacadeAnalyzeCommand::IsDroppingContentFileDir(const QString& file) const
{
    AtomicLock flag(atomicFlagExecuteCommand);
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
    AtomicLock flag(atomicFlagExecuteCommand);
    Q_UNUSED(flag);

    return AnalyzeExecuteCommandDrop::IsErrorDroppingContentFileDir(currentPathRepository.path(), file);
}
//----------------------------------------------------------------------------------------/
void FacadeAnalyzeCommand::ErrorChangeDirectMode()
{
    if(repository)
    {
        repository->OnErrorChangeDirectMode("fffff");
    }
}
//----------------------------------------------------------------------------------------/
void FacadeAnalyzeCommand::ChangeDirectMode(const bool& mode)
{
    if(repository)
    {
        repository->OnChangeDirectMode(mode);
    }
}
//----------------------------------------------------------------------------------------/
void FacadeAnalyzeCommand::ExecuteAddActionForAnalizeCommand()
{
    if(currentAnalyzeExecuteCommand)
    {
        currentAnalyzeExecuteCommand->ExecuteAddActionForAnalizeExecuteCommand();
    }
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
