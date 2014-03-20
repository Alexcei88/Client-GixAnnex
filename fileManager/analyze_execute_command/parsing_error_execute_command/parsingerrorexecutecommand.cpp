#include "parsingerrorexecutecommand.h"
#include "analyze_execute_command/analizediraction.h"

// std stuff
#include <algorithm>

using namespace AnalyzeCommand;

//----------------------------------------------------------------------------------------/
ParsingErrorExecuteCommand::ParsingErrorExecuteCommand()
{
    //FillErrorIdDescription();
}
//----------------------------------------------------------------------------------------/
ParsingErrorExecuteCommand::~ParsingErrorExecuteCommand()
{}
//----------------------------------------------------------------------------------------/
ParsingErrorExecuteCommand::ErrorType ParsingErrorExecuteCommand::GetIdError(const QString& error) const
{
    if(auto it = std::find(errorIdDescription.begin(), errorIdDescription.end(), error) != errorIdDescription.end())
    {
        const QString string_(it);
        // мы нашли ошибку среди зарегестрированных
        return errorIdDescription.key(string_);
    }
    else {
//        return static_cast<ParsingErrorExecuteCommand>(-1);
    }
}
//----------------------------------------------------------------------------------------/
void ParsingErrorExecuteCommand::AddFileWithError(const QString& file, const QString& error, const QString &description)
{
    const ErrorType id = GetIdError(error);
    if(errorFiles.contains(id))
    {
        mapListAnalizeDir& oldMapDescription = errorFiles[id];
        if(oldMapDescription.contains(description))
        {
            QList<AnalizeDirOnActionPrivate>& list = oldMapDescription[description];
            AnalizeDirOnActionPrivate& oldAnalizeCommand = list.back();
            oldAnalizeCommand.filesMustToBeAction[file] = "";
        }
        else {
            // создаем новый список с новой описаловкой
            QList<AnalizeDirOnActionPrivate> listAnalizeFiles;
            AnalizeDirOnActionPrivate newAnalizeCommand;
            newAnalizeCommand.filesMustToBeAction[file] = "";
            listAnalizeFiles.push_back(newAnalizeCommand);
            oldMapDescription[description] = listAnalizeFiles;
        }
    }
    else
    {
        // создаем новый мэп с новым мэпом списков ошибок
        QList<AnalizeDirOnActionPrivate> listAnalizeFiles;
        AnalizeDirOnActionPrivate newAnalizeCommand;
        newAnalizeCommand.filesMustToBeAction[file] = "";
        listAnalizeFiles.push_back(newAnalizeCommand);
        mapListAnalizeDir mapForDescription;
        mapForDescription[description] = listAnalizeFiles;
        errorFiles[id] = mapForDescription;
    }
}
//----------------------------------------------------------------------------------------/

