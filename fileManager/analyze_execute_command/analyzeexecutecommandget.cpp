#include "analyzeexecutecommandget.h"
#include "analizediraction.h"
#include "facadeanalyzecommand.h"
#include "utils/utils.h"

// boost stuff
#include <boost/make_shared.hpp>

using namespace AnalyzeCommand;
using namespace Utils;

boost::shared_ptr<AnalizeDirOnActionPrivate> AnalyzeExecuteCommandGet::errorGettingContentFile = boost::make_shared<AnalizeDirOnActionPrivate>();
QStringList AnalyzeExecuteCommandGet::lastGettingContentFiles;

//----------------------------------------------------------------------------------------/
AnalyzeExecuteCommandGet::AnalyzeExecuteCommandGet(FacadeAnalyzeCommand &facadeAnalyzeCommand, const bool mode):
    AnalyzeExecuteCommand(facadeAnalyzeCommand)
  , modeStart(mode)
{
    gettingContentFileQueue = boost::make_shared<AnalizeDirOnActionPrivate>();
    lastGettingContentFiles.clear();
}
//----------------------------------------------------------------------------------------/
void AnalyzeExecuteCommandGet::StartExecuteCommand()
{
    AnalyzeExecuteCommand::StartExecuteCommand();
}
//----------------------------------------------------------------------------------------/
void AnalyzeExecuteCommandGet::EndExecuteCommand(const bool wasExecute)
{
    AnalyzeExecuteCommand::EndExecuteCommand(wasExecute);
    // сообщаем фасаду, что команда выполнена
    facadeAnalyzeCommand.RemoveGetContentFileQueue(this);
    // очищаем список errorGettingContent
    errorGettingContentFile->ClearListAction(errorGettingContentFile->filesWasAction, errorGettingContentFile->filesMustToBeAction);
}
//----------------------------------------------------------------------------------------/
void AnalyzeExecuteCommandGet::ExecuteAddActionForAnalizeExecuteCommand()
{
    AtomicLock flag(atomicFlagExecuteCommand);
    Q_UNUSED(flag);

    if(!modeStart)
    {
        ModificationErrorGettingContentFile();
        ModificationGettingContentFileQueue();
    }
    lastGettingContentFiles.clear();
}
//----------------------------------------------------------------------------------------/
void AnalyzeExecuteCommandGet::StartGetContentFile(const QString& file)
{
    AtomicLock flag(atomicFlagExecuteCommand);
    Q_UNUSED(flag);

    gettingContentFile = CatDirFile(pathExecuteCommand, file);
}
//----------------------------------------------------------------------------------------/
void AnalyzeExecuteCommandGet::EndGetContentFile(const QString&file)
{
    AtomicLock flag(atomicFlagExecuteCommand);
    Q_UNUSED(flag);

    gettingContentFile = "";
    const QString fullPathFile = CatDirFile(pathExecuteCommand, file);
    lastGettingContentFile = fullPathFile;
    lastGettingContentFiles << fullPathFile;

    if(!gettingContentFileQueue->filesMustToBeAction.isEmpty())
    {
        gettingContentFileQueue->filesWasAction[fullPathFile] = "";
    }   
}
//----------------------------------------------------------------------------------------/
void AnalyzeExecuteCommandGet::ErrorGetContentFile(const QString& file, const QString& error)
{
    AtomicLock flag(atomicFlagExecuteCommand);
    Q_UNUSED(flag);

    const QString fullPathFile = CatDirFile(pathExecuteCommand, file);
    // если список заданий не пустой, то фиксиурем, что было выполнено действие
    if(!gettingContentFileQueue->filesMustToBeAction.isEmpty())
        gettingContentFileQueue->filesWasAction[fullPathFile] = "";

    gettingContentFile = "";

    // помещаем файл в класс ошибок
    if(!errorGettingContentFile->filesMustToBeAction.contains(fullPathFile))
        errorGettingContentFile->filesMustToBeAction[fullPathFile] = error;
}
//----------------------------------------------------------------------------------------/
void AnalyzeExecuteCommandGet::SetPathGetContent(const QString& file)
{
    fileGetContent = file;
    gettingContentFileQueue->filesMustToBeAction[file] = "";
}
//----------------------------------------------------------------------------------------/
bool AnalyzeExecuteCommandGet::IsGettingContentFileDir(const QString& currentPath, const QString& file) const
{
    const QString fullPathFile = CatDirFile(currentPath, file);
    if(DirContainsFile(fullPathFile, gettingContentFile))
    {
        return true;
    }
    if(gettingContentFileQueue->IsFindFileOnDirAction(fullPathFile))
    {
        return !gettingContentFileQueue->IsWasActionForFile(fullPathFile);
    }
    return false;
}
//----------------------------------------------------------------------------------------/
bool AnalyzeExecuteCommandGet::IsErrorGettingContentFileDir(const QString& currentPath, const QString& file)
{
    const QString fullPathFile = CatDirFile(currentPath, file);
    if(errorGettingContentFile->IsFindFileOnDirAction(fullPathFile))
    {
        return !errorGettingContentFile->IsWasActionForFile(fullPathFile);
    }
    return false;
}
//----------------------------------------------------------------------------------------/
void AnalyzeExecuteCommandGet::ForeachFilesHaveContentAlready(const QString& path) const
{
    return;
    QDir dir(path);
    dir.setFilter(QDir::NoDotAndDotDot | QDir::AllDirs | QDir::Files | QDir::System);

    QFileInfo fileInfo(path);

    if(fileInfo.isDir())
    {
        QStringList list = dir.entryList();
        for(QString& str : list)
        {
            ForeachFilesHaveContentAlready(Utils::CatDirFile(path, str));
        }
    }
    else
    {
        // файл
        if(fileInfo.isFile())
        {
            // посылаем сигнал, что файл уже получен
//            EndGetContentFile(path);
        }
        else
        {
            // эта пустая символическая ссылка, ничего не делаем
        }
    }
}
//----------------------------------------------------------------------------------------/
bool AnalyzeExecuteCommandGet::DirContainsFile(const QString& dir, const QString& file) const
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
bool AnalyzeExecuteCommandGet::ModificationGettingContentFileQueue()
{
    bool wasModification = false;
    if(gettingContentFileQueue->filesMustToBeAction.empty() && gettingContentFileQueue->filesWasAction.isEmpty())
        return wasModification;

    // модифицируем список, в зависимости от хода выполнения команды
    QStringList listDirs = gettingContentFileQueue->ListAllDirOfFile(gettingContentFileQueue->filesWasAction);
    if(!endCommand)
    {
        // если не конец операции, то удаляем из списка если есть fileGetContent
        listDirs.removeOne(fileGetContent);
    }

    // если список файлов, над которыми было выполнено дейтсвие содержит строку fileGetContent, то дальше значит делать ничего не нужно
    //(команда выполнена над всеми файлами в директории, на которую дано задание. Модификацию списка болше делать незачем)
    if(gettingContentFileQueue->filesWasAction.contains(fileGetContent))
        return wasModification;

    for(QString& dir : listDirs)
    {
        if(gettingContentFileQueue->EndActionForDir(dir, lastGettingContentFile))
        {
            gettingContentFileQueue->UnionAllFileDirOnDir(gettingContentFileQueue->filesWasAction, dir);
        #ifdef DEBUG
            printf("Was union directory: %s\n", dir.toStdString().c_str());
        #endif
            wasModification = true;
        }
    }
    return wasModification;
}
//----------------------------------------------------------------------------------------/
bool AnalyzeExecuteCommandGet::ModificationErrorGettingContentFile()
{
    if(errorGettingContentFile->filesMustToBeAction.isEmpty())
        return false;
    // если файлы, которыйбыли получены за сессию, имеются в векторе ошибок, то фиксируем,
    // что файл был удачно получен, и в будущем должен будет очищен из вектора ошибок
    for(QString& file : lastGettingContentFiles)
    {
        if(errorGettingContentFile->IsFindFileOnDirAction(file))
        {
            errorGettingContentFile->filesWasAction[file] = "";
        }
    }
    bool wasModification = false;
    // модифицируем список, в зависимости от хода выполнения команды
    QStringList listDirs = errorGettingContentFile->ListAllDirOfFile(errorGettingContentFile->filesWasAction);
    QMap<QString, QString> listFilesNotWasAction;
    for(QString& dir : listDirs)
    {
        if(errorGettingContentFile->WasActionForAllFileDirOnDir(errorGettingContentFile->filesWasAction, listFilesNotWasAction, dir))
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




