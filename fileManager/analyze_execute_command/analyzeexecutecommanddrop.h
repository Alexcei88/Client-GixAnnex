#ifndef ANALYZEEXECUTECOMMANDDROP_H
#define ANALYZEEXECUTECOMMANDDROP_H

// Qt stuff
#include <QList>

#include "analyzeexecutecommand.h"

namespace AnalyzeCommand
{

class FacadeAnalyzeCommand;

class AnalyzeExecuteCommandDrop: public AnalyzeExecuteCommand
{
public:
    AnalyzeExecuteCommandDrop(FacadeAnalyzeCommand& facadeAnalyzeCommand);

    virtual void        StartExecuteCommand() override;
    virtual void        EndExecuteCommand(const bool wasExecute = true) override;

    void                StartDropContentFile(const QString& file);
    void                EndDropContentFile(const QString& file);
    void                ErrorDropContentFile(const QString& file, const QString& error);
    inline void         SetPathDropContent(const QString& file) { fileDropContent = file; }

private:
    // файл/директория, которую удаляем командой
    QString             fileDropContent;

    /** @brief перебирает рекурсивно все файлы в переданном пути,
     *  если у файла есть уже контент, то послыает сигнал, что контент уже получен */
    void                ForeachFilesNoContentAlready(const QString& path) const;
};

}

#endif // ANALYZEEXECUTECOMMANDDROP_H
