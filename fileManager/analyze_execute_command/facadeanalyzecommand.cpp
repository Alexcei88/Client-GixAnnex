#include "facadeanalyzecommand.h"
#include "utils/utils.h"
#include "analizediraction.h"

// std stuff
#include <iostream>
#include <assert.h>

using namespace AnalyzeCommand;
using namespace Utils;

//----------------------------------------------------------------------------------------/
FacadeAnalyzeCommand::FacadeAnalyzeCommand():
    atomicFlagExecuteCommand(new std::atomic_flag(ATOMIC_FLAG_INIT))
  , gettingContentFileQueue(new AnalizeDirOnActionPrivate())

{}
//----------------------------------------------------------------------------------------/
FacadeAnalyzeCommand::~FacadeAnalyzeCommand()
{
    delete atomicFlagExecuteCommand;
}
//----------------------------------------------------------------------------------------/
void FacadeAnalyzeCommand::SetCurrentPathRepository(const QString& currentPath)
{
    currentPathRepository.setPath(currentPath);
}
//----------------------------------------------------------------------------------------/
void FacadeAnalyzeCommand::AddGetContentFileQueue(const QString& file)
{
    AtomicLock flag(atomicFlagExecuteCommand);
    Q_UNUSED(flag)
    gettingContentFileQueue->filesMustToBeAction << file;
}
//----------------------------------------------------------------------------------------/
void FacadeAnalyzeCommand::StartGetContentFile(const QString& file)
{
    AtomicLock flag(atomicFlagExecuteCommand);
    Q_UNUSED(flag)

    gettingContentFile = file;
}
//----------------------------------------------------------------------------------------/
void FacadeAnalyzeCommand::EndGetContentFile(const QString& file)
{
    AtomicLock flag(atomicFlagExecuteCommand);
    Q_UNUSED(flag)

    // если список заданий не пустой, то фиксиурем, что было выполнено действие
    if(!gettingContentFileQueue->filesMustToBeAction.isEmpty())
        gettingContentFileQueue->filesWasAction << file;

    assert(!gettingContentFile.isEmpty());
    gettingContentFile = "";
}
//----------------------------------------------------------------------------------------/
void FacadeAnalyzeCommand::ErrorGetContentFile(const QString& file, const QString& error)
{
    AtomicLock flag(atomicFlagExecuteCommand);
    Q_UNUSED(flag)

    // если список заданий не пустой, то фиксиурем, что было выполнено действие
    if(!gettingContentFileQueue->filesMustToBeAction.isEmpty())
        gettingContentFileQueue->filesWasAction << file;

    assert(!gettingContentFile.isEmpty());
    gettingContentFile = "";   

    // помещаем файл в вектор ошибок
    if(errorGettingContentFile.contains(file))
        errorGettingContentFile.remove(file);

    errorGettingContentFile[file] = error;
}
//----------------------------------------------------------------------------------------/
bool FacadeAnalyzeCommand::IsGettingContentFileDir(const QString& file) const
{
    AtomicLock flag(atomicFlagExecuteCommand);
    Q_UNUSED(flag)

    const QString fullPathFile = CatDirFile(currentPathRepository.path(), file);
    if(DirContainsFile(fullPathFile, gettingContentFile))
    {
        return true;
    }
    if(gettingContentFileQueue->IsFindFileOnDirAction(fullPathFile))
    {
        if(!gettingContentFileQueue->IsWasActionForFile(fullPathFile))
        {
            return true;
        }
    }
    return false;
}
//----------------------------------------------------------------------------------------/
bool FacadeAnalyzeCommand::IsErrorGettingContentFileDir(const QString& file) const
{
    AtomicLock flag(atomicFlagExecuteCommand);
    Q_UNUSED(flag)

    for(auto iterator = errorGettingContentFile.constBegin(); iterator != errorGettingContentFile.constEnd(); ++iterator)
    {
        if(DirContainsFile(CatDirFile(currentPathRepository.path(), file), iterator.key()))
        {
            return true;
        }
    }
    return false;
}
//----------------------------------------------------------------------------------------/
void FacadeAnalyzeCommand::StartDropContentFile(const QString& file)
{
    AtomicLock flag(atomicFlagExecuteCommand);
    Q_UNUSED(flag)

    droppingContentFile = file;
}
//----------------------------------------------------------------------------------------/
void FacadeAnalyzeCommand::AddDropContentFileQueue(const QString& file)
{
    AtomicLock flag(atomicFlagExecuteCommand);
    Q_UNUSED(flag)

//    droppingContentFileQueue.push_back(file);
}
//----------------------------------------------------------------------------------------/
void FacadeAnalyzeCommand::EndDropContentFile(const QString& file)
{
    AtomicLock flag(atomicFlagExecuteCommand);
    Q_UNUSED(flag)

    Q_UNUSED(file);
    assert(!droppingContentFile.isEmpty());
    droppingContentFile = "";
}
//----------------------------------------------------------------------------------------/
void FacadeAnalyzeCommand::ErrorDropContentFile(const QString& file, const QString& error)
{
    AtomicLock flag(atomicFlagExecuteCommand);
    Q_UNUSED(flag)

    assert(!droppingContentFile.isEmpty());
    droppingContentFile = "";

    // помещаем файл в вектор ошибок
    if(errorDroppingContentFile.contains(file))
        errorDroppingContentFile.remove(file);

    errorDroppingContentFile[file] = error;
}
//----------------------------------------------------------------------------------------/
bool FacadeAnalyzeCommand::IsDroppingContentFileDir(const QString& file) const
{
    AtomicLock flag(atomicFlagExecuteCommand);
    Q_UNUSED(flag)

    if(DirContainsFile(CatDirFile(currentPathRepository.path(), file), droppingContentFile))
    {
        return true;
    }
    return false;
}
//----------------------------------------------------------------------------------------/
bool FacadeAnalyzeCommand::IsErrorDroppingContentFileDir(const QString& file) const
{
    AtomicLock flag(atomicFlagExecuteCommand);
    Q_UNUSED(flag)

    for(auto iterator = errorDroppingContentFile.constBegin(); iterator != errorDroppingContentFile.constEnd(); ++iterator)
    {
        if(DirContainsFile(CatDirFile(currentPathRepository.path(), file), iterator.key()))
        {
            return true;
        }
    }
    return false;
}
//----------------------------------------------------------------------------------------/
void FacadeAnalyzeCommand::ModificationAllListFiles()
{
    // gettingContentFileQueue
    ModificationListFiles(gettingContentFileQueue.get());
}
//----------------------------------------------------------------------------------------/
bool FacadeAnalyzeCommand::DirContainsFile(const QString& dir, const QString& file) const
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
void FacadeAnalyzeCommand::ModificationListFiles(AnalizeDirOnActionPrivate* listFiles)
{
    // захватываем атомарный флаг
    atomicFlagExecuteCommand->test_and_set(std::memory_order_acquire);

    // делаем копию списков, будем работать с ними, после модификации обновим списки
    QStringList filesMustToBeAction = listFiles->filesMustToBeAction;
    QStringList filesWasAction = listFiles->filesWasAction;

    // освобождаем флаг
    atomicFlagExecuteCommand->clear(std::memory_order_release);

    // 1
    QStringList listDirs = AnalizeDirOnActionPrivate::ListAllDirOfFile(filesMustToBeAction);
    for(QString& dir : listDirs)
    {
        if(AnalizeDirOnActionPrivate::WasActionForAllFileDirOnDir(filesMustToBeAction, dir))
        {
        #ifdef DEBUG
            printf("Was union directory: %s", dir.toStdString().c_str());
        #endif
        }
    }

    // 2
    listDirs = AnalizeDirOnActionPrivate::ListAllDirOfFile(filesWasAction);
    for(QString& dir : listDirs)
    {
        if(AnalizeDirOnActionPrivate::WasActionForAllFileDirOnDir(filesWasAction, dir))
        {
        #ifdef DEBUG
            printf("Was union directory: %s", dir.toStdString().c_str());
        #endif
        }
    }

    AtomicLock flag(atomicFlagExecuteCommand);
    Q_UNUSED(flag)

    listFiles->filesMustToBeAction = filesMustToBeAction;
    listFiles->filesWasAction = filesWasAction;
}
//----------------------------------------------------------------------------------------/

