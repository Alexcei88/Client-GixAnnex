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
    AnalyzeExecuteCommandDrop(FacadeAnalyzeCommand& facadeAnalyzeCommand, bool autocall = false);

    void                StartDropContentFile(const QString& file);
    void                EndDropContentFile(const QString& file);
    void                ErrorDropContentFile(const QString& file, const QString& error);

private:
    // флаг, означающий, запущена команда пользователем или вызвана автоматически
    // несколько разное поведение будет
    bool                autocall;
};

}

#endif // ANALYZEEXECUTECOMMANDDROP_H
