#ifndef MANAGERRESTARTCOMMAND_H
#define MANAGERRESTARTCOMMAND_H

// Qt stuff
#include <QObject>
#include "define.h"

class IRepository;

namespace AnalyzeCommand
{
    // класс обертка для перезапуска команд репозитория
    // будут вызываться слоты через invokeMethod, что решит
    // вопрос синхронизации непотокозащищенного класса IRepository

class ManagerRestartCommand : public QObject
{
    Q_OBJECT
public:
    ManagerRestartCommand(IRepository* repository, QObject* parent = 0);

public slots:

    GANN_DEFINE::RESULT_EXEC_PROCESS setDirectMode(const bool& mode);

private:
    IRepository*        repository;
};

}
#endif // MANAGERRESTARTCOMMAND_H
