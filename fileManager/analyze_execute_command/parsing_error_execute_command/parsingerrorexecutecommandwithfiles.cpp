#include "parsingerrorexecutecommandwithfiles.h"
#include "facadeapplication.h"

using namespace AnalyzeCommand;
//----------------------------------------------------------------------------------------/
ParsingErrorExecuteCommandWithFiles::ParsingErrorExecuteCommandWithFiles():
    ParsingErrorExecuteCommand()
{}
//----------------------------------------------------------------------------------------/
void ParsingErrorExecuteCommandWithFiles::AddFileWithError(  const QString& file, const QString& error
                                                           , const QString& description
                                                           , const IRepository* repository)

{
    const ErrorType id = GetIdError(error);
    if(errorFilesLastSession.contains(id))
    {
        mapAnalizeDir& oldMapDescription = errorFilesLastSession[id];
        const Error curError(description, repository);
        if(oldMapDescription.contains(curError))
        {
            AnalizeDirOnActionPrivate& oldAnalizeCommand = oldMapDescription[curError];
            oldAnalizeCommand.filesMustToBeAction[file] = "";
        }
        else
        {
            // создаем новый список, началось выполнение новой команды
            AnalizeDirOnActionPrivate newAnalizeCommand;
            newAnalizeCommand.filesMustToBeAction[file] = "";
            oldMapDescription[curError] = newAnalizeCommand;
        }
    }
    else
    {
        // создаем новый мэп с новым мэпом ошибкb
        AnalizeDirOnActionPrivate newAnalizeCommand;
        newAnalizeCommand.filesMustToBeAction[file] = "";
        mapAnalizeDir mapForDescription;
        Error curError(description, repository);
        mapForDescription[curError] = newAnalizeCommand;
        errorFilesLastSession[id] = mapForDescription;
    }
}
//----------------------------------------------------------------------------------------/
bool ParsingErrorExecuteCommandWithFiles::IsFileWithError(const QString& file) const
{
    if(errorFiles.empty())
        return false;

    for(auto it = errorFiles.begin(); it != errorFiles.end(); ++it)
    {
        const mapAnalizeDir& mapAnalizeDir = *it;
        for(auto analizeDir = mapAnalizeDir.begin(); analizeDir != mapAnalizeDir.end(); ++analizeDir )
        {        
            if(analizeDir->IsFindFileOnDirAction(file))
            {
                // интересующий файл есть в списке, если над ним не были выполнения действия,
                // то значит этот файл с ошибкой
                if(!analizeDir->IsWasActionForFile(file))
                    return true;
            }
        }
    }

    return false;
}
//----------------------------------------------------------------------------------------/
void ParsingErrorExecuteCommandWithFiles::StartExecuteCommand()
{
    errorFilesLastSession.clear();
}
//----------------------------------------------------------------------------------------/
void ParsingErrorExecuteCommandWithFiles::EndExecuteCommand()
{
//    FacadeApplication::getInstance()->systemTray->SendErrorToView("fddddfdfdf", errorFilesLastSession.begin()->)
    for(auto it = errorFilesLastSession.begin(); it != errorFilesLastSession.end(); ++it)
    {
        const QString desc = "Ffff";
        for(auto itError = it.value().begin(); itError != it.value().end(); ++itError)
        {
            FacadeApplication::getInstance()->GetSystemTray()->SendErrorToView(desc, desc);
        }

    }
    AddFileWithError(errorFilesLastSession);
    errorFilesLastSession.clear();
}
//----------------------------------------------------------------------------------------/
void ParsingErrorExecuteCommandWithFiles::AddFileWithError(const QMap<ErrorType, mapAnalizeDir> &mapSession)
{
    for(QMap<ParsingErrorExecuteCommand::ErrorType, mapAnalizeDir>::const_iterator it = mapSession.begin();
        it != mapSession.end(); ++it)
    {
        const ErrorType id = it.key();
        const mapAnalizeDir& newMapDescription = it.value();
        if(errorFiles.contains(id))
        {
            mapAnalizeDir& oldMapDescription = errorFiles[id];
            for(QMap<ParsingErrorExecuteCommand::Error, AnalizeDirOnActionPrivate>::const_iterator itDesc = newMapDescription.begin();
                itDesc != newMapDescription.end(); ++itDesc)
            {
                const Error& curError = itDesc.key();
                if(oldMapDescription.contains(curError))
                {
                    // у нас уже есть мэп этой ошибки, добавляем в список ошибку
                    AnalizeDirOnActionPrivate& oldAnalizeCommand = oldMapDescription[curError];
                    const AnalizeDirOnActionPrivate& newAnalizeCommand = itDesc.value();

                    std::copy(newAnalizeCommand.filesMustToBeAction.begin(), newAnalizeCommand.filesMustToBeAction.end(),
                              oldAnalizeCommand.filesMustToBeAction.begin());
                }
                else
                {
                    // создаем новый список, началось выполнение новой команды
                    const AnalizeDirOnActionPrivate& newAnalizeCommand = itDesc.value();
                    oldMapDescription[curError] = newAnalizeCommand;
                }
            }
        }
        else
        {
            // у нас нет этой ошибки, добавляем
            errorFiles[id] = newMapDescription;
        }
    }
}
//----------------------------------------------------------------------------------------/
bool ParsingErrorExecuteCommandWithFiles::ModificationErrorGettingContentFile(const QStringList &lastWasActionFiles)
{
    if(errorFiles.empty())
        return false;

    // если файлы, над которыми были выполнены действия за сессию, имеются в векторе ошибок, то фиксируем,
    // что файл был удачно получен, и в будущем должен будет очищен из вектора ошибок
    for(auto it = errorFiles.begin(); it != errorFiles.end(); ++it)
    {
        mapAnalizeDir& mapAnalizeDir = *it;
        for(auto analizeDir = mapAnalizeDir.begin(); analizeDir != mapAnalizeDir.end(); ++analizeDir )
        {
            for(const QString& file : lastWasActionFiles)
            {
                if(analizeDir->IsFindFileOnDirAction(file))
                {
                    analizeDir->filesWasAction[file] = "";
                }
            }
        }
    }
    bool wasModification = false;

    // модифицируем список ошибок, в зависимости от хода выполнения команды
    for(auto it = errorFiles.begin(); it != errorFiles.end(); ++it)
    {
        mapAnalizeDir& mapAnalizeDir = *it;
        for(auto analizeDir = mapAnalizeDir.begin(); analizeDir != mapAnalizeDir.end(); ++analizeDir )
        {
            QStringList listDirs = analizeDir->ListAllDirOfFile(analizeDir->filesWasAction);
            for(QString& dir : listDirs)
            {
                if(analizeDir->WasActionForAllFileDirOnDir(analizeDir->filesWasAction, dir))
                {
#ifdef DEBUG
                    printf("Was union directory with error: %s\n", dir.toStdString().c_str());
#endif
                    wasModification = true;
                }
            }
        }
    }
    return wasModification;
}
//----------------------------------------------------------------------------------------/

