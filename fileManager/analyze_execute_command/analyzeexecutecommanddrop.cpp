#include "analyzeexecutecommanddrop.h"

#include "utils/utils.h"
using namespace AnalyzeCommand;
using namespace Utils;

//----------------------------------------------------------------------------------------/

AnalyzeExecuteCommandDrop::AnalyzeExecuteCommandDrop(FacadeAnalyzeCommand &facadeAnalyzeCommand):
    AnalyzeExecuteCommand(facadeAnalyzeCommand)
{}
//----------------------------------------------------------------------------------------/
void AnalyzeExecuteCommandDrop::StartExecuteCommand()
{
    AnalyzeExecuteCommand::StartExecuteCommand();
    // определяем файлы, у которого контента уже нет
    ForeachFilesNoContentAlready(fileDropContent);
}
//----------------------------------------------------------------------------------------/
void AnalyzeExecuteCommandDrop::EndExecuteCommand(const bool wasExecute)
{
    AnalyzeExecuteCommand::EndExecuteCommand(wasExecute);
    // чистим списки
//    facadeAnalyzeCommand.ClearListDroppingContentFile(fileDropContent);
}
//----------------------------------------------------------------------------------------/
void AnalyzeExecuteCommandDrop::StartDropContentFile(const QString& file)
{
    facadeAnalyzeCommand.StartDropContentFile(CatDirFile(pathExecuteCommand, file));
}
//----------------------------------------------------------------------------------------/
void AnalyzeExecuteCommandDrop::EndDropContentFile(const QString& file)
{
    facadeAnalyzeCommand.EndDropContentFile(CatDirFile(pathExecuteCommand, file));
}
//----------------------------------------------------------------------------------------/
void AnalyzeExecuteCommandDrop::ErrorDropContentFile(const QString& file, const QString& error)
{
    facadeAnalyzeCommand.ErrorDropContentFile(CatDirFile(pathExecuteCommand, file), error);
}
//----------------------------------------------------------------------------------------/
void AnalyzeExecuteCommandDrop::ForeachFilesNoContentAlready(const QString& path) const
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
        }
        else
        {
            // посылаем сигнал, что контент уже удален
            facadeAnalyzeCommand.EndDropContentFile(path);
        }
    }
}
//----------------------------------------------------------------------------------------/

