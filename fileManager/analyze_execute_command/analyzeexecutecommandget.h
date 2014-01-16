#ifndef IANALYZEEXECUTECOMMANDGET_H
#define IANALYZEEXECUTECOMMANDGET_H

// Qt stuff
#include <QList>
#include <QString>

#include "analyzeexecutecommand.h"

namespace AnalyzeCommand
{

class FacadeAnalyzeCommand;

class AnalyzeExecuteCommandGet: public AnalyzeExecuteCommand
{
public:
    AnalyzeExecuteCommandGet(FacadeAnalyzeCommand& facadeAnalyzeCommand);

    virtual void        StartExecuteCommand() override;
    virtual void        EndExecuteCommand(const bool wasExecute = true) override;

    void                StartGetContentFile(const QString&file);
    void                EndGetContentFile(const QString& file);
    void                ErrorGetContentFile(const QString&file, const QString&error);
    inline void         SetPathGetContent(const QString& file) { fileGetContent = file; }

private:
    /** @brief файл/директория, откуда запущена команда */
    QString             fileGetContent;
    /** @brief перебирает рекурсивно все файлы в переданном пути,
     *  если у файла есть уже контент, то послыает сигнал, что контент уже получен */
    void                ForeachFilesHaveContentAlready(const QString& path) const;

};
}

#endif // IANALYZEEXECUTECOMMANDGET_H
