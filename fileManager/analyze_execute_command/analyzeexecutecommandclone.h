#ifndef ANALIZEEXECUTECOMMANDCLONE_H
#define ANALIZEEXECUTECOMMANDCLONE_H

#include "analyzeexecutecommand.h"

namespace AnalyzeCommand
{
class FacadeAnalyzeCommand;

class AnalyzeExecuteCommandClone: public AnalyzeExecuteCommand
{
public:
    AnalyzeExecuteCommandClone(FacadeAnalyzeCommand& facadeAnalyzeCommand);
    virtual void        EndExecuteCommand(const bool wasExecute = true);

    void                SetFolderToClone(const QString& path);
    void                ErrorFolderToClone(const QString& error);

private:
    /** @brief папка, куда идет клонирование репозитория */
    QString             folder;
    /** @brief была ли ошибка */
    bool                wasError;
    /** @brief Причина ошибки */
    QString             reasonError;


};
}

#endif // ANALIZEEXECUTECOMMANDCLONE_H
