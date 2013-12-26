#include "analyzeexecutecommanddrop.h"

#include "utils/utils.h"
using namespace AnalyzeCommand;
using namespace Utils;

//----------------------------------------------------------------------------------------/

AnalyzeExecuteCommandDrop::AnalyzeExecuteCommandDrop(FacadeAnalyzeCommand &facadeAnalyzeCommand, bool autocall):
    AnalyzeExecuteCommand(facadeAnalyzeCommand)
  , autocall(autocall)
{}
//----------------------------------------------------------------------------------------/
void AnalyzeExecuteCommandDrop::StartDropContentFile(const QString& file)
{
    if(!autocall)
        facadeAnalyzeCommand.StartDropContentFile(CatDirFile(pathExecuteCommand, file));
}
//----------------------------------------------------------------------------------------/
void AnalyzeExecuteCommandDrop::EndDropContentFile(const QString& file)
{
    if(!autocall)
        facadeAnalyzeCommand.EndDropContentFile(CatDirFile(pathExecuteCommand, file));
}
//----------------------------------------------------------------------------------------/
void AnalyzeExecuteCommandDrop::ErrorDropContentFile(const QString& file, const QString& error)
{
    if(!autocall)
        facadeAnalyzeCommand.ErrorDropContentFile(CatDirFile(pathExecuteCommand, file), error);
}
//----------------------------------------------------------------------------------------/

