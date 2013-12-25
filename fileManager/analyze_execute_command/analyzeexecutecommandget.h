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

    void                OnStartGetContentFile(const QString&);
    void                OnEndGetContentFile(const QString&);
    void                OnErrorGetContentFile(const QString&, const QString&);

};
}

#endif // IANALYZEEXECUTECOMMANDGET_H
