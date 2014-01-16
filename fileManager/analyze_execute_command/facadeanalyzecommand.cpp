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
    gettingContentFileQueue(new AnalizeDirOnActionPrivate())
  , droppingContentFileQueue(new AnalizeDirOnActionPrivate())
  , atomicFlagExecuteCommand(new std::atomic_flag(ATOMIC_FLAG_INIT))
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
    flag;

    gettingContentFileQueue->filesMustToBeAction << file;
}
//----------------------------------------------------------------------------------------/
void FacadeAnalyzeCommand::StartGetContentFile(const QString& file)
{
    AtomicLock flag(atomicFlagExecuteCommand);
    flag;

    gettingContentFile = file;
}
//----------------------------------------------------------------------------------------/
void FacadeAnalyzeCommand::EndGetContentFile(const QString& file)
{
    AtomicLock flag(atomicFlagExecuteCommand);
    flag;

    // если список заданий не пустой, то фиксируем, что было выполнено действие
    if(!gettingContentFileQueue->filesMustToBeAction.isEmpty())
        gettingContentFileQueue->filesWasAction << file;

    gettingContentFile = "";
}
//----------------------------------------------------------------------------------------/
void FacadeAnalyzeCommand::ErrorGetContentFile(const QString& file, const QString& error)
{
    AtomicLock flag(atomicFlagExecuteCommand);
    flag;

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
    flag;

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
    flag;

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
    flag;

    droppingContentFile = file;
}
//----------------------------------------------------------------------------------------/
void FacadeAnalyzeCommand::AddDropContentFileQueue(const QString& file)
{
    AtomicLock flag(atomicFlagExecuteCommand);
    flag;

    droppingContentFileQueue->filesMustToBeAction << file;
}
//----------------------------------------------------------------------------------------/
void FacadeAnalyzeCommand::EndDropContentFile(const QString& file)
{
    AtomicLock flag(atomicFlagExecuteCommand);
    flag;

    // если список заданий не пустой, то фиксируем, что было выполнено действие
    if(!droppingContentFileQueue->filesMustToBeAction.isEmpty())
        droppingContentFileQueue->filesWasAction << file;

    droppingContentFile = "";
}
//----------------------------------------------------------------------------------------/
void FacadeAnalyzeCommand::ErrorDropContentFile(const QString& file, const QString& error)
{
    AtomicLock flag(atomicFlagExecuteCommand);
    flag;

    // если список заданий не пустой, то фиксируем, что было выполнено действие
    if(!droppingContentFileQueue->filesMustToBeAction.isEmpty())
        droppingContentFileQueue->filesWasAction << file;

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
    flag;

    const QString fullPathFile = CatDirFile(currentPathRepository.path(), file);
    if(DirContainsFile(fullPathFile, droppingContentFile))
    {
        return true;
    }
    if(droppingContentFileQueue->IsFindFileOnDirAction(fullPathFile))
    {
        if(!droppingContentFileQueue->IsWasActionForFile(fullPathFile))
        {
            return true;
        }
    }
    return false;
}
//----------------------------------------------------------------------------------------/
bool FacadeAnalyzeCommand::IsErrorDroppingContentFileDir(const QString& file) const
{
    AtomicLock flag(atomicFlagExecuteCommand);
    flag;

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

    // droppingContentFileQueu e
    ModificationListFiles(droppingContentFileQueue.get());
}
//----------------------------------------------------------------------------------------/
void FacadeAnalyzeCommand::ClearListGettingContentFile(const QString& fileEndAction)
{
    while(ModificationListFiles(gettingContentFileQueue.get())) {}
    ClearListFiles(gettingContentFileQueue.get(), fileEndAction);
}
//----------------------------------------------------------------------------------------/
void FacadeAnalyzeCommand::ClearListDroppingContentFile(const QString& fileEndAction)
{
    while(ModificationListFiles(droppingContentFileQueue.get())) {}
    ClearListFiles(droppingContentFileQueue.get(), fileEndAction);
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
bool FacadeAnalyzeCommand::ModificationListFiles(AnalizeDirOnActionPrivate* listFiles, boost::function<const QStringList&>* addFunc) const
{
    AtomicLock flag(atomicFlagExecuteCommand);
    flag;

    bool wasModification = false;
    if(listFiles->filesMustToBeAction.empty() && listFiles->filesWasAction.isEmpty())
    {
        return wasModification;
    }

    // 1
    QStringList listDirs = listFiles->ListAllDirOfFile(listFiles->filesMustToBeAction);
    QStringList listFilesNotWasAction;
    for(QString& dir : listDirs)
    {
        if(listFiles->WasActionForAllFileDirOnDir(listFiles->filesMustToBeAction, listFilesNotWasAction, dir))
        {
        #ifdef DEBUG
            printf("Was union directory: %s\n", dir.toStdString().c_str());
        #endif
            wasModification = true;
        }
        else
        {
            if(addFunc)
            {
                // выполняем дополнительнные действия по списку, по которому не было выполнено действие
//                (*addFunc)(listFilesNotWasAction);
            }
        }
    }

    // 2
    listDirs = listFiles->ListAllDirOfFile(listFiles->filesWasAction);
    listFilesNotWasAction.clear();
    for(QString& dir : listDirs)
    {
        if(listFiles->WasActionForAllFileDirOnDir(listFiles->filesWasAction, listFilesNotWasAction, dir))
        {
        #ifdef DEBUG
            printf("Was union directory: %s\n", dir.toStdString().c_str());
        #endif
            wasModification = true;
        }
        else
        {
            // выполним действия
            if(addFunc)
            {
                // выполняем дополнительные действия со списком, по которому не было выполнено действие
//                (*addFunc)(listFilesNotWasAction);
            }

        }
    }

    return wasModification;
}
//----------------------------------------------------------------------------------------/
void FacadeAnalyzeCommand::ClearListFiles(AnalizeDirOnActionPrivate* listFiles, const QString& fileEndAction) const
{
    AtomicLock flag(atomicFlagExecuteCommand);
    flag;

    if(listFiles->filesMustToBeAction.empty() && listFiles->filesWasAction.isEmpty())
    {
        return;
    }

    listFiles->ClearListAction(listFiles->filesWasAction, listFiles->filesMustToBeAction, fileEndAction);
}
//----------------------------------------------------------------------------------------/
void FacadeAnalyzeCommand::IsHavingContentFileWhileGettingContent(const QStringList& listFile)
{
    QFileInfo fileInfo;
    for(const QString& file: listFile)
    {
        fileInfo.setFile(file);
#ifdef DEBUG
        assert("В списке файлов не должно быть директории!!! Это ошибка" && fileInfo.isDir());
#endif
        if(fileInfo.isFile())
        {
            // посылаем сигнал, что файл уже получен
            EndGetContentFile(file);
        }
        else
        {
            // эта пустая символическая ссылка, ничего не делаем
        }
    }
}
//----------------------------------------------------------------------------------------/
void FacadeAnalyzeCommand::IsNotHavingContentFileWhileDroppingContent(const QStringList& listFile)
{
    QFileInfo fileInfo;
    for(const QString& file: listFile)
    {
        fileInfo.setFile(file);
#ifdef DEBUG
        assert("В списке файлов не должно быть директории!!! Это ошибка" && fileInfo.isDir());
#endif
        if(fileInfo.isFile())
        {}
        else
        {
            // посылаем сигнал о том, что контент у файла уже удален
            EndDropContentFile(file);
        }
    }
}
//----------------------------------------------------------------------------------------/

