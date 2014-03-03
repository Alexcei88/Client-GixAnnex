#include "facade_shellcommand.h"
#include "shelltask.h"

// Qt stuff
#include <QMap>
#include <QStringList>
#include <QThreadPool>


std::unique_ptr<FacadeShellCommand> FacadeShellCommand::instance;
QStringList FacadeShellCommand::listCommandPriorityLow;
QStringList FacadeShellCommand::listCommandPriorityHigh;
QQueue<FacadeShellCommand::SDescriptionCommand> FacadeShellCommand::queueComanndPriorityLow;
QQueue<FacadeShellCommand::SDescriptionCommand> FacadeShellCommand::queueComanndPriorityHigh;
QMutex FacadeShellCommand::mutex;

//----------------------------------------------------------------------------------------/
FacadeShellCommand::FacadeShellCommand()
{}
//----------------------------------------------------------------------------------------/
FacadeShellCommand* FacadeShellCommand::getInstance()
{
    if(instance.get())
    {
        instance.reset(new FacadeShellCommand());
        InitClass();
    }
    return instance.get();
}
//----------------------------------------------------------------------------------------/
void FacadeShellCommand::InitClass()
{
    // заполняем список команд с низким приоритетом
    listCommandPriorityLow << "get" << "drop" << "remove";

    listCommandPriorityHigh << "clone" << "sync" << "whereis";
}
//----------------------------------------------------------------------------------------/
void FacadeShellCommand::TryStartNextcommand(const QString& baseNameCommand, ShellTask* currentTask,
                                             const IRepository* repository)
{
    mutex.lock();
    if(listCommandPriorityHigh.contains(baseNameCommand))
    {
        // команда с высоким приоритетом
        if(QThreadPool::globalInstance()->activeThreadCount() == 1)
        {
            // помещаем в очередь команд
            SDescriptionCommand command;
            command.task = currentTask,
            command.repository = repository;
            queueComanndPriorityHigh.push_back(command);
        }
        else
        {
            // сразу же выполняем ее
            QThreadPool::globalInstance()->start(currentTask);
        }
    }
    else
    {
        // команда с низким приоритетом
        if(QThreadPool::globalInstance()->activeThreadCount() == 1)
        {
            // помещаем в очередь команд
            SDescriptionCommand command;
            command.task = currentTask,
            command.repository = repository;
            queueComanndPriorityLow.push_back(command);
        }
        else
        {
            QThreadPool::globalInstance()->start(currentTask);
        }
    }
    mutex.unlock();
}
//----------------------------------------------------------------------------------------/
void FacadeShellCommand::TryStartNextcommand()
{
    mutex.lock();
    if(!queueComanndPriorityHigh.isEmpty())
    {
        // очередь комманд с высоким приоритетом не пуста, запускаем эти команды в первую очередь
        SDescriptionCommand nextCommand = queueComanndPriorityHigh.first();
        queueComanndPriorityHigh.removeFirst();
        QThreadPool::globalInstance()->start(nextCommand.task);
    }
    else if(!queueComanndPriorityLow.isEmpty())
    {
        // берем команду с низким приоритетом и запускаем
        SDescriptionCommand nextCommand = queueComanndPriorityLow.first();
        queueComanndPriorityLow.removeFirst();
        QThreadPool::globalInstance()->start(nextCommand.task);
    }
    mutex.unlock();
}
//----------------------------------------------------------------------------------------/
void FacadeShellCommand::ClearCommandForRepostory(const IRepository* repoitory)
{
    //
}
//----------------------------------------------------------------------------------------/




