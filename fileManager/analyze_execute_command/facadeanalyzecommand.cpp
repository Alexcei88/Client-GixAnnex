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
    Q_UNUSED(flag);

    gettingContentFileQueue->filesMustToBeAction << file;
}
//----------------------------------------------------------------------------------------/
void FacadeAnalyzeCommand::StartGetContentFile(const QString& file)
{
    AtomicLock flag(atomicFlagExecuteCommand);
    Q_UNUSED(flag);

    gettingContentFile = file;
}
//----------------------------------------------------------------------------------------/
void FacadeAnalyzeCommand::EndGetContentFile(const QString& file, const bool lock)
{
    if(lock)
    {
        AtomicLock flag(atomicFlagExecuteCommand);
        Q_UNUSED(flag);
    }

    gettingContentFile = "";
    // запоминаем последний файл, контент которого получаем
    lastGettingContent = file;
    // если список заданий не пустой, то фиксируем, что было выполнено действие
    if(!gettingContentFileQueue->filesMustToBeAction.isEmpty())
    {
        if(!lock)
        {
            if(gettingContentFileQueue->filesWasAction.contains(file))
                return;
        }
        gettingContentFileQueue->filesWasAction << file;
    }
}
//----------------------------------------------------------------------------------------/
void FacadeAnalyzeCommand::ErrorGetContentFile(const QString& file, const QString& error)
{
    AtomicLock flag(atomicFlagExecuteCommand);
    Q_UNUSED(flag);

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
    Q_UNUSED(flag);

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
    Q_UNUSED(flag);

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
void FacadeAnalyzeCommand::AddDropContentFileQueue(const QString& file)
{
    AtomicLock flag(atomicFlagExecuteCommand);
    Q_UNUSED(flag);

    droppingContentFileQueue->filesMustToBeAction << file;
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
        droppingContentFileQueue->filesWasAction << file;
    }
}
//----------------------------------------------------------------------------------------/
void FacadeAnalyzeCommand::ErrorDropContentFile(const QString& file, const QString& error)
{
    AtomicLock flag(atomicFlagExecuteCommand);
    Q_UNUSED(flag);

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
void FacadeAnalyzeCommand::ModificationAllListFiles()
{
    // gettingContentFileQueue
    boost::function<void (const QStringList&)> haveContentWhileGettingContent;
    haveContentWhileGettingContent = boost::bind(&FacadeAnalyzeCommand::IsHavingContentFileWhileGettingContent, this, _1);

    ModificationListFiles(gettingContentFileQueue.get(), haveContentWhileGettingContent, lastGettingContent, currentGettingContentFileQueue);

    // droppingContentFileQueue
    boost::function<void (const QStringList&)> haveContentWhileDroppingContent;
    haveContentWhileDroppingContent = boost::bind(&FacadeAnalyzeCommand::IsNotHavingContentFileWhileDroppingContent, this, _1);

    ModificationListFiles(droppingContentFileQueue.get());
}
//----------------------------------------------------------------------------------------/
void FacadeAnalyzeCommand::ClearListGettingContentFile(const QString& fileEndAction)
{
    // просматриваем весь список файлов, над которыми не было выполнено действие в заданной директории
    while(ModificationListFiles(gettingContentFileQueue.get(), 0, "", currentGettingContentFileQueue, true))
    {

    }
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
        if(listFiles->EndActionForDir(dir, listDirs, lastFile))
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
void FacadeAnalyzeCommand::IsHavingContentFileWhileGettingContent(const QStringList& listFile)
{
    QFileInfo fileInfo;
    for(const QString& file: listFile)
    {
        fileInfo.setFile(file);
        // если это директория, то пропускаем
        if(fileInfo.isDir())
            continue;

        if(fileInfo.isFile())
        {
            // посылаем сигнал, что файл уже получен
            EndGetContentFile(file, false);
        }
        else
        { // эта пустая символическая ссылка, ничего не делаем
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
        // если это директория, то пропускаем
        if(fileInfo.isDir())
            continue;

        if(fileInfo.isFile())
        {}
        else
        {
            // посылаем сигнал о том, что контент у файла уже удален
            EndDropContentFile(file, false);
        }
    }
}
//----------------------------------------------------------------------------------------/

