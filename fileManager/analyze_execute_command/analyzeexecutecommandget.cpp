#include "analyzeexecutecommandget.h"
#include "utils/utils.h"

using namespace AnalyzeCommand;
using namespace Utils;


//----------------------------------------------------------------------------------------/
AnalyzeExecuteCommandGet::AnalyzeExecuteCommandGet(FacadeAnalyzeCommand &facadeAnalyzeCommand):
    AnalyzeExecuteCommand(facadeAnalyzeCommand)
{}
//----------------------------------------------------------------------------------------/
void AnalyzeExecuteCommandGet::StartGetContentFile(const QString& file)
{
    std::cout<<"StartGet: "<<file.toStdString()<<std::endl;
    facadeAnalyzeCommand.StartGetContentFile(CatDirFile(pathExecuteCommand, file));
}
//----------------------------------------------------------------------------------------/
void AnalyzeExecuteCommandGet::EndGetContentFile(const QString&file)
{
    std::cout<<"StopGet: "<<file.toStdString()<<std::endl;
    facadeAnalyzeCommand.EndGetContentFile(CatDirFile(pathExecuteCommand, file));
}
//----------------------------------------------------------------------------------------/
void AnalyzeExecuteCommandGet::ErrorGetContentFile(const QString& file, const QString& error)
{
    facadeAnalyzeCommand.ErrorGetContentFile(CatDirFile(pathExecuteCommand, file), error);
}
//----------------------------------------------------------------------------------------/

