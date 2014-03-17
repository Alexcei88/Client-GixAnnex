#include "analyzeexecutecommandget.h"
#include "analizediraction.h"
#include "facadeanalyzecommand.h"
#include "facadeapplication.h"
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

    FacadeApplication::getInstance()->IncreaseCountCommandThreadSyncIcons();
    FacadeApplication::getInstance()->ReleaseThreadSyncIcons();
}
//----------------------------------------------------------------------------------------/
AnalyzeExecuteCommandGet::~AnalyzeExecuteCommandGet()
{
    // удаляем из очереди команду, если она еще не была удалена
    facadeAnalyzeCommand.RemoveGetContentFileQueue(this);
    FacadeApplication::getInstance()->DecreaseCountCommandThreadSyncIcons();
}
//----------------------------------------------------------------------------------------/
void AnalyzeExecuteCommandGet::StartExecuteCommand()
{
    AnalyzeExecuteCommand::StartExecuteCommand();

    if(!modeStart)
    {
        // определеяем файлы, у которого контент уже получен
        ForeachFilesHaveContentAlready(fileGetContent);
    }
}
//----------------------------------------------------------------------------------------/
void AnalyzeExecuteCommandGet::EndExecuteCommand(const bool wasExecute)
{
    AnalyzeExecuteCommand::EndExecuteCommand(wasExecute);
    // сообщаем фасаду, что команда выполнена
    facadeAnalyzeCommand.RemoveGetContentFileQueue(this);

    AtomicLock flag(atomicFlagExecuteCommand);
    Q_UNUSED(flag);

    // очищаем список errorGettingContent
    errorGettingContentFile->ClearListAction(errorGettingContentFile->filesWasAction, errorGettingContentFile->filesMustToBeAction,
                                             errorGettingContentFile->filesNotNeedAction
                                             );
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

    if(!modeStart)
        gettingContentFileQueue->filesWasAction[fullPathFile] = "";
}
//----------------------------------------------------------------------------------------/
void AnalyzeExecuteCommandGet::ErrorGetContentFile(const QString& file, const QString& error)
{
    AtomicLock flag(atomicFlagExecuteCommand);
    Q_UNUSED(flag);

    gettingContentFile = "";
    const QString fullPathFile = CatDirFile(pathExecuteCommand, file);
    if(!modeStart)
        gettingContentFileQueue->filesWasAction[fullPathFile] = "";

    // помещаем файл в класс ошибок
    if(!errorGettingContentFile->filesMustToBeAction.contains(fullPathFile))
        errorGettingContentFile->filesMustToBeAction[fullPathFile] = error;
}
//----------------------------------------------------------------------------------------/
void AnalyzeExecuteCommandGet::SetPathGetContent(const QString& file)
{
    fileGetContent = file;
    if(!modeStart)
        gettingContentFileQueue->filesMustToBeAction[file] = "";
}
//----------------------------------------------------------------------------------------/
bool AnalyzeExecuteCommandGet::IsGettingContentFileDir(const QString& currentPath, const QString& file) const
{
    const QString fullPathFile = CatDirFile(currentPath, file);
    if(FacadeAnalyzeCommand::DirContainsFile(fullPathFile, gettingContentFile))
    {
        return true;
    }
    if(modeStart)
        return false;

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
void AnalyzeExecuteCommandGet::ForeachFilesHaveContentAlready(const QString& path)
{
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
            AtomicLock flag(atomicFlagExecuteCommand);
            Q_UNUSED(flag);

            // посылаем сигнал, что файл уже получен
            lastGettingContentFiles << path;

            gettingContentFileQueue->filesNotNeedAction[path] = "";
        }
        else
        {
            // эта пустая символическая ссылка, ничего не делаем и прекращаем просмотр директории
            return;
        }
    }
}
//----------------------------------------------------------------------------------------/
bool AnalyzeExecuteCommandGet::ModificationGettingContentFileQueue()
{
    if(modeStart)
        return false;

    bool wasModification = false;

    //-------------------------------------------------------------------------/
    // filesWasAction
    //-------------------------------------------------------------------------/

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

    //-------------------------------------------------------------------------/
    // filesNotNeedAction
    //-------------------------------------------------------------------------/

    listDirs = gettingContentFileQueue->ListAllDirOfFile(gettingContentFileQueue->filesNotNeedAction);
    if(!endCommand)
    {
        // если не конец операции, то удаляем из списка если есть fileDropContent в списке
        listDirs.removeOne(fileGetContent);
    }

    // если список файлов, над которыми было выполнено дейтсвие содержит строку fileDropContent, то дальше значит делать ничего не нужно
    //(команда выполнена над всеми файлами в директории, на которую дано задание. Модификацию списка болше делать незачем)
    if(gettingContentFileQueue->filesNotNeedAction.contains(fileGetContent))
        return wasModification;

    for(QString& dir : listDirs)
    {
        if(gettingContentFileQueue->WasActionForAllFileDirOnDir(gettingContentFileQueue->filesNotNeedAction, dir))
        {
            gettingContentFileQueue->UnionAllFileDirOnDir(gettingContentFileQueue->filesNotNeedAction, dir);
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
    for(QString& dir : listDirs)
    {
        if(errorGettingContentFile->WasActionForAllFileDirOnDir(errorGettingContentFile->filesWasAction, dir))
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




