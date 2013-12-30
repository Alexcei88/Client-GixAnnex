#include "analyzeexecutecommanddrop.h"

#include "utils/utils.h"
using namespace AnalyzeCommand;
using namespace Utils;

//----------------------------------------------------------------------------------------/

AnalyzeExecuteCommandDrop::AnalyzeExecuteCommandDrop(FacadeAnalyzeCommand &facadeAnalyzeCommand):
    AnalyzeExecuteCommand(facadeAnalyzeCommand)
{}
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
void AnalyzeExecuteCommandDrop::EndExecuteCommand(const bool wasExecute)
{
    AnalyzeExecuteCommand::EndExecuteCommand(wasExecute);
}
//----------------------------------------------------------------------------------------/

