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
    AnalyzeExecuteCommandGet(FacadeAnalyzeCommand& facadeAnalyzeCommand, bool autosync = false);

    void                StartGetContentFile(const QString&file);
    void                EndGetContentFile(const QString& file);
    void                ErrorGetContentFile(const QString&file, const QString&error);
private:
    // флаг, означающий, запущена команда пользователем или вызвана автоматически
    // несколько разное поведение будет
    bool                autosync;

};
}

#endif // IANALYZEEXECUTECOMMANDGET_H
