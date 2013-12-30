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

    void                StartGetContentFile(const QString&file);
    void                EndGetContentFile(const QString& file);
    void                ErrorGetContentFile(const QString&file, const QString&error);
    inline void         SetPathGetContent(const QString& file) { fileGetContent = file; }

private:
    // файл/директория, которую скачиваем командой
    QString             fileGetContent;
};
}

#endif // IANALYZEEXECUTECOMMANDGET_H
