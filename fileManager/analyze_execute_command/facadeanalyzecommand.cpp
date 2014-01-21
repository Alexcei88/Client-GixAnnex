#include "facadeanalyzecommand.h"
#include "utils/utils.h"
#include "analizediraction.h"
#include "analyzeexecutecommandget.h"
#include "analyzeexecutecommanddrop.h"

// std stuff
#include <iostream>
#include <assert.h>

using namespace AnalyzeCommand;
using namespace Utils;

std::atomic_flag* FacadeAnalyzeCommand::atomicFlagExecuteCommand = new std::atomic_flag(ATOMIC_FLAG_INIT);
//----------------------------------------------------------------------------------------/
FacadeAnalyzeCommand::FacadeAnalyzeCommand():
    droppingContentFileQueue(new AnalizeDirOnActionPrivate())
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
void FacadeAnalyzeCommand::AddDropContentFileQueue(const QString& file)
{
    AtomicLock flag(atomicFlagExecuteCommand);
    Q_UNUSED(flag);

    droppingContentFileQueue->filesMustToBeAction[file] = "";
}
//----------------------------------------------------------------------------------------/
void FacadeAnalyzeCommand::StartDropContentFile(const QString& file)
{
    AtomicLock flag(atomicFlagExecuteCommand);
    Q_UNUSED(flag);

    droppingContentFile = file;
}
//----------------------------------------------------------------------------------------/
void FacadeAnalyzeCommand::EndDropContentFile(const QString& file, const bool lock)
{
    if(lock)
    {
        AtomicLock flag(atomicFlagExecuteCommand);
        Q_UNUSED(flag);
    }

    droppingContentFile = "";
    // если список заданий не пустой, то фиксируем, что было выполнено действие
    if(!droppingContentFileQueue->filesMustToBeAction.isEmpty())
    {
        if(!lock)
        {
            // если режим без блокировки, то проверка не содержит ли список эти данные
            if(droppingContentFileQueue->filesWasAction.contains(file))
                return;
        }
//        droppingContentFileQueue->filesWasAction << file;
    }
}
//----------------------------------------------------------------------------------------/
void FacadeAnalyzeCommand::ErrorDropContentFile(const QString& file, const QString& error)
{
    AtomicLock flag(atomicFlagExecuteCommand);
    Q_UNUSED(flag);

    // если список заданий не пустой, то фиксируем, что было выполнено действие
//    if(!droppingContentFileQueue->filesMustToBeAction.isEmpty())
//        droppingContentFileQueue->filesWasAction << file;

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
    Q_UNUSED(flag);

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
    Q_UNUSED(flag);

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
void FacadeAnalyzeCommand::ExecuteAddActionForAnalizeCommand()
{
    if(currentAnalyzeExecuteCommand)
    {
        currentAnalyzeExecuteCommand->ExecuteAddActionForAnalizeExecuteCommand();
    }
//    ModificationListFiles(gettingContentFileQueue.get(), haveContentWhileGettingContent, lastGettingContent, currentGettingContentFileQueue);

//    ModificationListFiles(droppingContentFileQueue.get());
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
bool FacadeAnalyzeCommand::ModificationListFiles(  AnalizeDirOnActionPrivate *listFiles, boost::function<void (const QStringList&)> addFunc
                                                 , const QString& lastFile, const QString& currentFileQueue
                                                 , const bool end) const
{
    AtomicLock flag(atomicFlagExecuteCommand);
    Q_UNUSED(flag);

    bool wasModification = false;
    if(listFiles->filesMustToBeAction.empty() && listFiles->filesWasAction.isEmpty())
    {
        return wasModification;
    }

    // модифицируем список, в зависимости от хода выполнения команды
    QStringList listDirs = listFiles->ListAllDirOfFile(listFiles->filesWasAction);
    if(!end)
    {
        // если не конец операции, то удаляем из списка если есть currentFileQueue
        listDirs.removeOne(currentFileQueue);
    }
    else
    {}

    // если список файлов, над которыми было выполнено дейтсвие содержит строку currentFileQueue, то дальше значит делать ничего не нужно
    //(команда выполнена над всеми файлами в директории, на которую дано задание. Модификацию списка болше делать незачем)
    if(listFiles->filesWasAction.contains(currentFileQueue))
        return false;

    QStringList listFilesNotWasAction;
    for(QString& dir : listDirs)
    {
        std::cout<<"dir = "<<dir.toStdString()<<std::endl;
        //if(listFiles->WasActionForAllFileDirOnDir(listFiles->filesWasAction, listFilesNotWasAction, dir))
        if(listFiles->EndActionForDir(dir, lastFile))
        {
            listFiles->UnionAllFileDirOnDir(listFiles->filesWasAction, dir);
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
                // выполняем дополнительные действия со списком файлов, по которому не было выполнено действие
//                addFunc(listFilesNotWasAction);
            }
        }
        listFilesNotWasAction.clear();
    }
    return wasModification;
}
//----------------------------------------------------------------------------------------/
void FacadeAnalyzeCommand::ClearListFiles(AnalizeDirOnActionPrivate* listFiles, const QString& fileEndAction) const
{
    AtomicLock flag(atomicFlagExecuteCommand);
    Q_UNUSED(flag);

    if(listFiles->filesMustToBeAction.empty() && listFiles->filesWasAction.isEmpty())
    {
        return;
    }

    listFiles->ClearListAction(listFiles->filesWasAction, listFiles->filesMustToBeAction, fileEndAction);
}
//----------------------------------------------------------------------------------------/

