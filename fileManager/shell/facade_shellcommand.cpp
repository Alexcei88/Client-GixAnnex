#include "facade_shellcommand.h"
#include "shelltask.h"

// Qt stuff
#include <QMap>
#include <QStringList>
#include <QThreadPool>


QStringList FacadeShellCommand::listCommandPriorityLow;
QStringList FacadeShellCommand::listCommandPriorityHigh;
QQueue<FacadeShellCommand::SDescriptionCommand> FacadeShellCommand::queueComanndPriorityLow;
QQueue<FacadeShellCommand::SDescriptionCommand> FacadeShellCommand::queueComanndPriorityHigh;
std::unique_ptr<FacadeShellCommand::SDescriptionCommand> FacadeShellCommand::currentCommand;
QMutex FacadeShellCommand::mutex;

//----------------------------------------------------------------------------------------/
void FacadeShellCommand::InitClass()
{
    // заполняем список команд
    // с низким приоритетом
    listCommandPriorityLow << "get" << "drop" << "git rm" << "direct" << "indirect";
    // с высоким приоритетом
    listCommandPriorityHigh << "clone" << "sync" << "whereis" << "rm";
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
            SDescriptionCommand* command = new SDescriptionCommand;
            command->task = currentTask,
            command->repository = repository;

            currentCommand.reset(command);
            QThreadPool::globalInstance()->start(currentTask);
        }
    }
    else
    {
        // команда с низким приоритетом
        if(QThreadPool::globalInstance()->activeThreadCount() == 1)
        {
            SDescriptionCommand command;
            command.task = currentTask,
            command.repository = repository;

            // помещаем в очередь команд
            queueComanndPriorityLow.push_back(command);
        }
        else
        {
            SDescriptionCommand* command = new SDescriptionCommand;
            command->task = currentTask,
            command->repository = repository;

            currentCommand.reset(command);
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

        SDescriptionCommand* command = new SDescriptionCommand;
        command->task = nextCommand.task,
        command->repository = nextCommand.repository;
        currentCommand.reset(command);

        QThreadPool::globalInstance()->start(nextCommand.task);
    }
    else if(!queueComanndPriorityLow.isEmpty())
    {
        // берем команду с низким приоритетом и запускаем
        SDescriptionCommand nextCommand = queueComanndPriorityLow.first();
        queueComanndPriorityLow.removeFirst();

        SDescriptionCommand* command = new SDescriptionCommand;
        command->task = nextCommand.task,
        command->repository = nextCommand.repository;
        currentCommand.reset(command);

        QThreadPool::globalInstance()->start(nextCommand.task);
    }
    mutex.unlock();
}
//----------------------------------------------------------------------------------------/
void FacadeShellCommand::ClearCommandForRepository(const IRepository* repository)
{
    // ищем в командах с низким приоритетом
    QQueue<SDescriptionCommand>::iterator it;
    do
    {
        it = std::find(queueComanndPriorityLow.begin(), queueComanndPriorityLow.end(), repository);
        if(it != queueComanndPriorityLow.end())
              it = queueComanndPriorityLow.erase(it);
    }
    while(it != queueComanndPriorityLow.end());

    // с высоким приоритетом
    do
    {
        it = std::find(queueComanndPriorityHigh.begin(), queueComanndPriorityHigh.end(), repository);
        if(it != queueComanndPriorityHigh.end())
              it = queueComanndPriorityHigh.erase(it);
    }
    while(it != queueComanndPriorityHigh.end());
}
//----------------------------------------------------------------------------------------/
bool FacadeShellCommand::IsExecuteCommandForRepository(const IRepository* repository)
{
    if(currentCommand && currentCommand->repository == repository)
        return true;
    else
        return false;
}
//----------------------------------------------------------------------------------------/




