#include "facadeanalyzecommand.h"
#include "analyzeexecutecommandclone.h"

using namespace AnalyzeCommand;

//----------------------------------------------------------------------------------------/
AnalyzeExecuteCommandClone::AnalyzeExecuteCommandClone(FacadeAnalyzeCommand& facadeAnalyzeCommand):
    AnalyzeExecuteCommand(facadeAnalyzeCommand)
  , wasError(false)
{}
//----------------------------------------------------------------------------------------/
void AnalyzeExecuteCommandClone::EndExecuteCommand(const bool wasExecute)
{
    AnalyzeExecuteCommand::EndExecuteCommand(wasExecute);
    // посылаем сигнал, что клонирование завершено в заданную папку
    wasError ? facadeAnalyzeCommand.EndCloneRepository(false, reasonError) : facadeAnalyzeCommand.EndCloneRepository(true, folder);
}
//----------------------------------------------------------------------------------------/
void AnalyzeExecuteCommandClone::SetFolderToClone(const QString& path)
{
    folder = path;
    wasError = false;
}
//----------------------------------------------------------------------------------------/
void AnalyzeExecuteCommandClone::ErrorFolderToClone(const QString& error)
{
    wasError = true;
    reasonError = error;
}
//----------------------------------------------------------------------------------------/

