#ifndef ANALIZEEXECUTECOMMANDSTATUS_H
#define ANALIZEEXECUTECOMMANDSTATUS_H

#include "analyzeexecutecommand.h"

#include <QVariantMap>

namespace AnalyzeCommand
{

class FacadeAnalyzeCommand;

class AnalizeExecuteCommandStatus : public AnalyzeExecuteCommand
{
public:
    AnalizeExecuteCommandStatus(FacadeAnalyzeCommand& facadeAnalizeCommand);
    void                SetStatusRepository(const QVariantMap& values);
    void                WasErrorGetStatusRepository();
};
}
#endif // ANALIZEEXECUTECOMMANDSTATUS_H
