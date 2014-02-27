#include "analyzeexecutecommandcopy.h"
#include "facadeanalyzecommand.h"
#include "utils/utils.h"
#include "analizediraction.h"
#include "facadeapplication.h"

// boost stuff
#include <boost/make_shared.hpp>

using namespace Utils;
using namespace AnalyzeCommand;
QStringList AnalyzeExecuteCommandCopy::lastCopyingContentFiles;

//----------------------------------------------------------------------------------------/
AnalyzeExecuteCommandCopy::AnalyzeExecuteCommandCopy(FacadeAnalyzeCommand& facadeAnalyzeCommand, const bool& from, const bool& modeStart):
    AnalyzeExecuteCommand(facadeAnalyzeCommand)
  , modeStart(modeStart)
  , from(from)
{
    copyingContentFileQueue = boost::make_shared<AnalizeDirOnActionPrivate>();
    lastCopyingContentFiles.clear();

    FacadeApplication::getInstance()->IncreaseCountCommandThreadSyncIcons();
    FacadeApplication::getInstance()->ReleaseThreadSyncIcons();
}
//----------------------------------------------------------------------------------------/
AnalyzeExecuteCommandCopy::~AnalyzeExecuteCommandCopy()
{
    FacadeApplication::getInstance()->DecreaseCountCommandThreadSyncIcons();
}
//----------------------------------------------------------------------------------------/
void AnalyzeExecuteCommandCopy::StartExecuteCommand()
{
    AnalyzeExecuteCommand::StartExecuteCommand();
    if(from && !modeStart)
    {
        // определяем файлы, у которых уже есть контент
    }
}
//----------------------------------------------------------------------------------------/
void AnalyzeExecuteCommandCopy::EndExecuteCommand(const bool wasExecute)
{

}
//----------------------------------------------------------------------------------------/
void AnalyzeExecuteCommandCopy::ExecuteAddActionForAnalizeExecuteCommand()
{
    AtomicLock flag(atomicFlagExecuteCommand);
    Q_UNUSED(flag);

    ModificationCopyingContentFileQueue();

    lastCopyingContentFiles.clear();
}
//----------------------------------------------------------------------------------------/
void AnalyzeExecuteCommandCopy::StartCopyContentFile(const QString&file)
{
    AtomicLock flag(atomicFlagExecuteCommand);
    Q_UNUSED(flag);

    copyingContentFile = CatDirFile(pathExecuteCommand, file);
}
//----------------------------------------------------------------------------------------/
void AnalyzeExecuteCommandCopy::EndCopyContentFile(const QString& file)
{
    AtomicLock flag(atomicFlagExecuteCommand);
    Q_UNUSED(flag);

    copyingContentFile = "";
    const QString fullPathFile = CatDirFile(pathExecuteCommand, file);
    lastCopyingContentFile = fullPathFile;
    lastCopyingContentFiles << fullPathFile;

    copyingContentFileQueue->filesWasAction[fullPathFile] = "";
}
//----------------------------------------------------------------------------------------/
void AnalyzeExecuteCommandCopy::ErrorCopyContentFile(const QString&file, const QString&error)
{
    // здесь нужно связывать с классом get-content и разделять from и get
}
//----------------------------------------------------------------------------------------/
void AnalyzeExecuteCommandCopy::SetPathCopyContent(const QString& file)
{
    fileCopyContent = file;
    if(!modeStart)
        copyingContentFileQueue->filesMustToBeAction[file] = "";
}
//----------------------------------------------------------------------------------------/
bool AnalyzeExecuteCommandCopy::IsCopyingContentFileDir(const QString& currentPath, const QString& file) const
{
    const QString fullPathFile = CatDirFile(currentPath, file);
    if(FacadeAnalyzeCommand::DirContainsFile(fullPathFile, copyingContentFile))
    {
        return true;
    }
    if(modeStart)
        return false;

    if(copyingContentFileQueue->IsFindFileOnDirAction(fullPathFile))
    {
        return !copyingContentFileQueue->IsWasActionForFile(fullPathFile);
    }
    return false;
}
//----------------------------------------------------------------------------------------/
void AnalyzeExecuteCommandCopy::ForeachFilesHaveContentAlready(const QString& path)
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
        // файл, или пустая символическая ссылка
        if(fileInfo.isFile())
        {
            return;
        }
        else
        {
            AtomicLock flag(atomicFlagExecuteCommand);
            Q_UNUSED(flag);

            // посылаем сигнал, что контент уже удален
            lastCopyingContentFiles << path;
            // помещаем в вектор файлов/директорий, над которыми действия выполнять не нужно(они уже выполнены)
            copyingContentFileQueue->filesNotNeedAction[path] = "";
        }
    }
}
//----------------------------------------------------------------------------------------/
bool AnalyzeExecuteCommandCopy::ModificationCopyingContentFileQueue()
{
    if(modeStart)
        return false;

    bool wasModification = false;

    //-------------------------------------------------------------------------/
    // filesWasAction
    //-------------------------------------------------------------------------/

    // модифицируем список, в зависимости от хода выполнения команды
    QStringList listDirs = copyingContentFileQueue->ListAllDirOfFile(copyingContentFileQueue->filesWasAction);
    if(!endCommand)
    {
        // если не конец операции, то удаляем из списка если есть fileDropContent в списке
        listDirs.removeOne(fileCopyContent);
    }

    // если список файлов, над которыми было выполнено дейтсвие содержит строку fileDropContent, то дальше значит делать ничего не нужно
    //(команда выполнена над всеми файлами в директории, на которую дано задание. Модификацию списка болше делать незачем)
    if(copyingContentFileQueue->filesWasAction.contains(fileCopyContent))
        return wasModification;

    for(QString& dir : listDirs)
    {
        if(copyingContentFileQueue->EndActionForDir(dir, lastCopyingContentFile))
        {
            copyingContentFileQueue->UnionAllFileDirOnDir(copyingContentFileQueue->filesWasAction, dir);
        #ifdef DEBUG
            printf("Was union directory: %s\n", dir.toStdString().c_str());
        #endif
            wasModification = true;
        }
    }

    //-------------------------------------------------------------------------/
    // filesNotNeedAction
    //-------------------------------------------------------------------------/

    listDirs = copyingContentFileQueue->ListAllDirOfFile(copyingContentFileQueue->filesNotNeedAction);
    if(!endCommand)
    {
        // если не конец операции, то удаляем из списка если есть fileDropContent в списке
        listDirs.removeOne(fileCopyContent);
    }

    // если список файлов, над которыми было выполнено дейтсвие содержит строку fileDropContent, то дальше значит делать ничего не нужно
    //(команда выполнена над всеми файлами в директории, на которую дано задание. Модификацию списка болше делать незачем)
    if(copyingContentFileQueue->filesNotNeedAction.contains(fileCopyContent))
        return wasModification;


    for(QString& dir : listDirs)
    {
        if(copyingContentFileQueue->WasActionForAllFileDirOnDir(copyingContentFileQueue->filesNotNeedAction, dir))
        {
            copyingContentFileQueue->UnionAllFileDirOnDir(copyingContentFileQueue->filesNotNeedAction, dir);
        #ifdef DEBUG
            printf("Was union directory: %s\n", dir.toStdString().c_str());
        #endif
            wasModification = true;
        }
    }

    return wasModification;
}
//----------------------------------------------------------------------------------------/
