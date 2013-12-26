#include "analyzeexecutecommandget.h"
#include "utils/utils.h"

using namespace AnalyzeCommand;
using namespace Utils;


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
        facadeAnalyzeCommand.StartGetContentFile(catDirFile(pathExecuteCommand, file));
}
//----------------------------------------------------------------------------------------/
void AnalyzeExecuteCommandGet::EndGetContentFile(const QString&file)
{
    if(!autosync)
        facadeAnalyzeCommand.EndGetContentFile(catDirFile(pathExecuteCommand, file));
}
//----------------------------------------------------------------------------------------/
void AnalyzeExecuteCommandGet::ErrorGetContentFile(const QString& file, const QString& error)
{
    if(!autosync)
        facadeAnalyzeCommand.ErrorGetContentFile(catDirFile(pathExecuteCommand, file), error);
}
//----------------------------------------------------------------------------------------/

