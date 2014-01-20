#include "analyzeexecutecommandget.h"
#include "utils/utils.h"

using namespace AnalyzeCommand;
using namespace Utils;

//----------------------------------------------------------------------------------------/
AnalyzeExecuteCommandGet::AnalyzeExecuteCommandGet(FacadeAnalyzeCommand &facadeAnalyzeCommand, const bool mode):
    AnalyzeExecuteCommand(facadeAnalyzeCommand)
  , modeStart(mode)
{}
//----------------------------------------------------------------------------------------/
void AnalyzeExecuteCommandGet::StartExecuteCommand()
{
    AnalyzeExecuteCommand::StartExecuteCommand();
    // перебираем файлы, может уже есть у кого-то контент
    ForeachFilesHaveContentAlready(Utils::CatDirFile(pathExecuteCommand, fileGetContent));
    // передаем, что начинается выполняться скачивание файла/директории
    facadeAnalyzeCommand.SetCurrentGettingContentFileQueue(fileGetContent);
}
//----------------------------------------------------------------------------------------/
void AnalyzeExecuteCommandGet::EndExecuteCommand(const bool wasExecute)
{
    AnalyzeExecuteCommand::EndExecuteCommand(wasExecute);
    // чистим списки
    facadeAnalyzeCommand.ClearListGettingContentFile(fileGetContent);
    // передаем, что скачивание файла/директории закончилось
    facadeAnalyzeCommand.SetCurrentGettingContentFileQueue("");
}
//----------------------------------------------------------------------------------------/
void AnalyzeExecuteCommandGet::StartGetContentFile(const QString& file)
{
    facadeAnalyzeCommand.StartGetContentFile(CatDirFile(pathExecuteCommand, file));
}
//----------------------------------------------------------------------------------------/
void AnalyzeExecuteCommandGet::EndGetContentFile(const QString&file)
{
    facadeAnalyzeCommand.EndGetContentFile(CatDirFile(pathExecuteCommand, file));
}
//----------------------------------------------------------------------------------------/
void AnalyzeExecuteCommandGet::ErrorGetContentFile(const QString& file, const QString& error)
{
    facadeAnalyzeCommand.ErrorGetContentFile(CatDirFile(pathExecuteCommand, file), error);
}
//----------------------------------------------------------------------------------------/
void AnalyzeExecuteCommandGet::ForeachFilesHaveContentAlready(const QString& path) const
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
            // посылаем сигнал, что файл уже получен
            facadeAnalyzeCommand.EndGetContentFile(path);
        }
        else
        {
            // эта пустая символическая ссылка, ничего не делаем
        }
    }
}
//----------------------------------------------------------------------------------------/


