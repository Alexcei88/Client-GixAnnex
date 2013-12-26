#include "analyzeexecutecommandget.h"
#include "utils/utils.h"

using namespace AnalyzeCommand;
using namespace Utils;


//----------------------------------------------------------------------------------------/
AnalyzeExecuteCommandGet::AnalyzeExecuteCommandGet(FacadeAnalyzeCommand &facadeAnalyzeCommand, bool autocall):
    AnalyzeExecuteCommand(facadeAnalyzeCommand)
  , autocall(autocall)
{}
//----------------------------------------------------------------------------------------/
void AnalyzeExecuteCommandGet::StartGetContentFile(const QString& file)
{
    if(!autocall)
        facadeAnalyzeCommand.StartGetContentFile(CatDirFile(pathExecuteCommand, file));
}
//----------------------------------------------------------------------------------------/
void AnalyzeExecuteCommandGet::EndGetContentFile(const QString&file)
{
    if(!autocall)
        facadeAnalyzeCommand.EndGetContentFile(CatDirFile(pathExecuteCommand, file));
}
//----------------------------------------------------------------------------------------/
void AnalyzeExecuteCommandGet::ErrorGetContentFile(const QString& file, const QString& error)
{
    if(!autocall)
        facadeAnalyzeCommand.ErrorGetContentFile(CatDirFile(pathExecuteCommand, file), error);
}
//----------------------------------------------------------------------------------------/

