#include "parsingerrorexecutecommandwithfiles.h"

using namespace AnalyzeCommand;
//----------------------------------------------------------------------------------------/
ParsingErrorExecuteCommandWithFiles::ParsingErrorExecuteCommandWithFiles():
    ParsingErrorExecuteCommand()
{}
//----------------------------------------------------------------------------------------/
void ParsingErrorExecuteCommandWithFiles::AddFileWithError(const QString& file, const QString& error, const QString &description)
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
bool ParsingErrorExecuteCommandWithFiles::IsFileWithError(const QString& file) const
{
    if(errorFiles.empty())
        return false;

    for(auto it = errorFiles.begin(); it != errorFiles.end(); ++it)
    {
        const mapListAnalizeDir& mapAnalizeDir = *it;
        for(auto analizeDir = mapAnalizeDir.begin(); analizeDir != mapAnalizeDir.end(); ++analizeDir )
        {
            const QList<AnalizeDirOnActionPrivate>& listAnalizeDir = *analizeDir;
            for(QList<AnalizeDirOnActionPrivate>::const_iterator itList = listAnalizeDir.begin(); itList != listAnalizeDir.end(); ++itList)
            {
                if(itList->IsFindFileOnDirAction(file))
                {
                    // интересующий файл есть в списке, если над ним не были выполнения действия,
                    // то значит этот файл с ошибкой
                    if(!itList->IsWasActionForFile(file))
                        return true;
                }
            }
        }
    }
    return false;
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
        mapListAnalizeDir& mapAnalizeDir = *it;
        for(auto analizeDir = mapAnalizeDir.begin(); analizeDir != mapAnalizeDir.end(); ++analizeDir )
        {
            QList<AnalizeDirOnActionPrivate>& listAnalizeDir = *analizeDir;
            for(QList<AnalizeDirOnActionPrivate>::iterator itList = listAnalizeDir.begin(); itList != listAnalizeDir.end(); ++itList)
            {
                for(const QString& file : lastWasActionFiles)
                {
                    if(itList->IsFindFileOnDirAction(file))
                    {
                        itList->filesWasAction[file] = "";
                    }
                }
            }
        }
    }
    bool wasModification = false;

    // модифицируем список ошибок, в зависимости от хода выполнения команды
    for(auto it = errorFiles.begin(); it != errorFiles.end(); ++it)
    {
        mapListAnalizeDir& mapAnalizeDir = *it;
        for(auto analizeDir = mapAnalizeDir.begin(); analizeDir != mapAnalizeDir.end(); ++analizeDir )
        {
            QList<AnalizeDirOnActionPrivate>& listAnalizeDir = *analizeDir;
            for(QList<AnalizeDirOnActionPrivate>::iterator itList = listAnalizeDir.begin(); itList != listAnalizeDir.end(); ++itList)
            {
                QStringList listDirs = itList->ListAllDirOfFile(itList->filesWasAction);
                for(QString& dir : listDirs)
                {
                    if(itList->WasActionForAllFileDirOnDir(itList->filesWasAction, dir))
                    {
#ifdef DEBUG
                        printf("Was union directory with error: %s\n", dir.toStdString().c_str());
#endif
                        wasModification = true;
                    }
                }

            }
        }
    }
    return wasModification;
}
//----------------------------------------------------------------------------------------/

