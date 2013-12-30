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

    void                StartDropContentFile(const QString& file);
    void                EndDropContentFile(const QString& file);
    void                ErrorDropContentFile(const QString& file, const QString& error);
    inline void         SetPathDropContent(const QString& file) { fileDropContent = file; }
    void                EndExecuteCommand(const bool wasExecute = true);

private:
    // файл/директория, которую удаляем командой
    QString             fileDropContent;

};

}

#endif // ANALYZEEXECUTECOMMANDDROP_H
