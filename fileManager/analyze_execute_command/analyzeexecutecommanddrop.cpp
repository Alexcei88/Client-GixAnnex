#include "analyzeexecutecommanddrop.h"
#include "facadeanalyzecommand.h"
#include "utils/utils.h"
#include "analizediraction.h"

// boost stuff
#include <boost/make_shared.hpp>

using namespace AnalyzeCommand;
using namespace Utils;

boost::shared_ptr<AnalizeDirOnActionPrivate> AnalyzeExecuteCommandDrop::errorDroppingContentFile = boost::make_shared<AnalizeDirOnActionPrivate>();
QStringList AnalyzeExecuteCommandDrop::lastDroppingContentFiles;

//----------------------------------------------------------------------------------------/
AnalyzeExecuteCommandDrop::AnalyzeExecuteCommandDrop(FacadeAnalyzeCommand &facadeAnalyzeCommand, const bool mode):
    AnalyzeExecuteCommand(facadeAnalyzeCommand)
  , modeStart(mode)
{
    droppingContentFileQueue = boost::make_shared<AnalizeDirOnActionPrivate>();
    lastDroppingContentFiles.clear();
}
//----------------------------------------------------------------------------------------/
void AnalyzeExecuteCommandDrop::StartExecuteCommand()
{
    AnalyzeExecuteCommand::StartExecuteCommand();
    // определяем файлы, у которого контента уже нет
    if(!modeStart)
    {
        AtomicLock flag(atomicFlagExecuteCommand);
        Q_UNUSED(flag);

        ForeachFilesNoContentAlready(fileDropContent);
    }
}
//----------------------------------------------------------------------------------------/
void AnalyzeExecuteCommandDrop::EndExecuteCommand(const bool wasExecute)
{
    AnalyzeExecuteCommand::EndExecuteCommand(wasExecute);
    // сообщаем фасаду, что команда выполнена
    facadeAnalyzeCommand.RemoveDropContentFileQueue(this);

    AtomicLock flag(atomicFlagExecuteCommand);
    Q_UNUSED(flag);

    // очищаем список errorDroppingContent
    errorDroppingContentFile->ClearListAction(errorDroppingContentFile->filesWasAction, errorDroppingContentFile->filesMustToBeAction);
}
//----------------------------------------------------------------------------------------/
void AnalyzeExecuteCommandDrop::ExecuteAddActionForAnalizeExecuteCommand()
{
    AtomicLock flag(atomicFlagExecuteCommand);
    Q_UNUSED(flag);

    if(!modeStart)
    {
        ModificationErrorDroppingContentFile();
        ModificationDroppingContentFileQueue();
    }
    lastDroppingContentFiles.clear();
}
//----------------------------------------------------------------------------------------/
void AnalyzeExecuteCommandDrop::StartDropContentFile(const QString& file)
{
    AtomicLock flag(atomicFlagExecuteCommand);
    Q_UNUSED(flag);

    droppingContentFile = CatDirFile(pathExecuteCommand, file);
}
//----------------------------------------------------------------------------------------/
void AnalyzeExecuteCommandDrop::EndDropContentFile(const QString& file)
{
    AtomicLock flag(atomicFlagExecuteCommand);
    Q_UNUSED(flag);

    droppingContentFile = "";
    const QString fullPathFile = CatDirFile(pathExecuteCommand, file);
    lastDroppingContentFile = fullPathFile;
    lastDroppingContentFiles << fullPathFile;

    if(!modeStart)
        droppingContentFileQueue->filesWasAction[fullPathFile] = "";
}
//----------------------------------------------------------------------------------------/
void AnalyzeExecuteCommandDrop::ErrorDropContentFile(const QString& file, const QString& error)
{
    AtomicLock flag(atomicFlagExecuteCommand);
    Q_UNUSED(flag);

    droppingContentFile = "";
    const QString fullPathFile = CatDirFile(pathExecuteCommand, file);
    if(!modeStart)
        droppingContentFileQueue->filesWasAction[fullPathFile] = "";

    // помещаем файл в класс ошибок
    if(!errorDroppingContentFile->filesMustToBeAction.contains(fullPathFile))
        errorDroppingContentFile->filesMustToBeAction[fullPathFile] = error;
}
//----------------------------------------------------------------------------------------/
void AnalyzeExecuteCommandDrop::SetPathDropContent(const QString &file)
{
    fileDropContent = file;
    if(!modeStart)
        droppingContentFileQueue->filesMustToBeAction[file] = "";
}
//----------------------------------------------------------------------------------------/
bool AnalyzeExecuteCommandDrop::IsDroppingContentFileDir(const QString &currentPath, const QString &file) const
{
    const QString fullPathFile = CatDirFile(currentPath, file);
    if(FacadeAnalyzeCommand::DirContainsFile(fullPathFile, droppingContentFile))
    {
        return true;
    }
    if(modeStart)
        return false;

    if(droppingContentFileQueue->IsFindFileOnDirAction(fullPathFile))
    {
        return !droppingContentFileQueue->IsWasActionForFile(fullPathFile);
    }
    return false;
}
//----------------------------------------------------------------------------------------/
bool AnalyzeExecuteCommandDrop::IsErrorDroppingContentFileDir(const QString &currentPath, const QString &file)
{
    const QString fullPathFile = CatDirFile(currentPath, file);
    if(errorDroppingContentFile->IsFindFileOnDirAction(fullPathFile))
    {
        return !errorDroppingContentFile->IsWasActionForFile(fullPathFile);
    }
    return false;
}
//----------------------------------------------------------------------------------------/
void AnalyzeExecuteCommandDrop::ForeachFilesNoContentAlready(const QString& path)
{
    QDir dir(path);
    dir.setFilter(QDir::NoDotAndDotDot | QDir::AllDirs | QDir::Files | QDir::System);

    QFileInfo fileInfo(path);

    if(fileInfo.isDir())
    {
        QStringList list = dir.entryList();
        for(QString& str : list)
        {
            ForeachFilesNoContentAlready(Utils::CatDirFile(path, str));
        }
    }
    else
    {
        // файл, или пустая символическая ссылка
        if(fileInfo.isFile())
        {
            return;
        }
        else
        {
            // посылаем сигнал, что контент уже удален
            lastDroppingContentFile = path;
            lastDroppingContentFiles << path;

            droppingContentFileQueue->filesWasAction[path] = "";
        }
    }
}
//----------------------------------------------------------------------------------------/
bool AnalyzeExecuteCommandDrop::ModificationDroppingContentFileQueue()
{
    if(modeStart)
        return false;

    bool wasModification = false;

    // модифицируем список, в зависимости от хода выполнения команды
    QStringList listDirs = droppingContentFileQueue->ListAllDirOfFile(droppingContentFileQueue->filesWasAction);
    if(!endCommand)
    {
        // если не конец операции, то удаляем из списка если есть fileDropContent в списке
        listDirs.removeOne(fileDropContent);
    }

    // если список файлов, над которыми было выполнено дейтсвие содержит строку fileDropContent, то дальше значит делать ничего не нужно
    //(команда выполнена над всеми файлами в директории, на которую дано задание. Модификацию списка болше делать незачем)
    if(droppingContentFileQueue->filesWasAction.contains(fileDropContent))
        return wasModification;

    for(QString& dir : listDirs)
    {
        if(droppingContentFileQueue->EndActionForDir(dir, lastDroppingContentFile))
        {
            droppingContentFileQueue->UnionAllFileDirOnDir(droppingContentFileQueue->filesWasAction, dir);
        #ifdef DEBUG
            printf("Was union directory: %s\n", dir.toStdString().c_str());
        #endif
            wasModification = true;
        }
    }
    return wasModification;
}
//----------------------------------------------------------------------------------------/
bool AnalyzeExecuteCommandDrop::ModificationErrorDroppingContentFile()
{
    if(errorDroppingContentFile->filesMustToBeAction.isEmpty())
        return false;

    // если файлы, которыйбыли получены за сессию, имеются в векторе ошибок, то фиксируем,
    // что файл был удачно получен, и в будущем должен будет очищен из вектора ошибок
    for(QString& file : lastDroppingContentFiles)
    {
        if(errorDroppingContentFile->IsFindFileOnDirAction(file))
        {
            errorDroppingContentFile->filesWasAction[file] = "";
        }
    }
    bool wasModification = false;
    // модифицируем список, в зависимости от хода выполнения команды
    QStringList listDirs = errorDroppingContentFile->ListAllDirOfFile(errorDroppingContentFile->filesWasAction);
    QMap<QString, QString> listFilesNotWasAction;
    for(QString& dir : listDirs)
    {
        if(errorDroppingContentFile->WasActionForAllFileDirOnDir(errorDroppingContentFile->filesWasAction, listFilesNotWasAction, dir))
        {
#ifdef DEBUG
            printf("Was union directory: %s\n", dir.toStdString().c_str());
#endif
            wasModification = true;
        }
    }
    return wasModification;
}
//----------------------------------------------------------------------------------------/

