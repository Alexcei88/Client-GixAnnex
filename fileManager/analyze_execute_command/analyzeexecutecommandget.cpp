#include "analyzeexecutecommandget.h"


using namespace AnalyzeCommand;

//----------------------------------------------------------------------------------------/
AnalyzeExecuteCommandGet::AnalyzeExecuteCommandGet(FacadeAnalyzeCommand &facadeAnalyzeCommand, bool autosync):
    AnalyzeExecuteCommand(facadeAnalyzeCommand)
  , autosync(autosync)
{

}
//----------------------------------------------------------------------------------------/
void AnalyzeExecuteCommandGet::StartGetContentFile(const QString& file)
{
    if(!autosync)
        facadeAnalyzeCommand.StartGetContentFile(file);
}
//----------------------------------------------------------------------------------------/
void AnalyzeExecuteCommandGet::EndGetContentFile(const QString&file)
{
    if(!autosync)
        facadeAnalyzeCommand.EndGetContentFile(file);
}
//----------------------------------------------------------------------------------------/
void AnalyzeExecuteCommandGet::ErrorGetContentFile(const QString& file, const QString& error)
{
    if(!autosync)
        facadeAnalyzeCommand.ErrorGetContentFile(file, error);
}
//----------------------------------------------------------------------------------------/

