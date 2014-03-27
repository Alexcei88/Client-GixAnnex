#ifndef ANALIZEEXECUTECOMMANDInfo_H
#define ANALIZEEXECUTECOMMANDInfo_H

#include "analyzeexecutecommand.h"

#include <QVariantMap>

namespace AnalyzeCommand
{

class FacadeAnalyzeCommand;

class AnalizeExecuteCommandInfo : public AnalyzeExecuteCommand
{
public:
    AnalizeExecuteCommandInfo(FacadeAnalyzeCommand& facadeAnalizeCommand);
    void                SetInfoRepository(const QVariantMap& values);
    void                WasErrorGetInfoRepository();
};
}
#endif // ANALIZEEXECUTECOMMANDInfo_H
