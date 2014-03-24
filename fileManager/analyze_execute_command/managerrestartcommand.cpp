#include "managerrestartcommand.h"
#include "repository/irepository.h"

using namespace AnalyzeCommand;

//----------------------------------------------------------------------------------------/
ManagerRestartCommand::ManagerRestartCommand(IRepository* repository, QObject *parent):
    QObject(parent)
  , repository(repository)
{}
//----------------------------------------------------------------------------------------/
GANN_DEFINE::RESULT_EXEC_PROCESS ManagerRestartCommand::setDirectMode(const QVariant& mode)
{
    return repository->SetDirectMode(mode.toBool());
}
//----------------------------------------------------------------------------------------/

//----------------------------------------------------------------------------------------/
