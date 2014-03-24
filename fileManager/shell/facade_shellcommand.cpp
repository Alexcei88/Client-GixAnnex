#include "facade_shellcommand.h"
#include "shelltask.h"

// Qt stuff
#include <QMap>
#include <QStringList>
#include <QThreadPool>
#include <QMutexLocker>


std::unique_ptr<FacadeShellCommand> FacadeShellCommand::instance(new FacadeShellCommand());
QStringList FacadeShellCommand::listCommandPriorityLow;
QStringList FacadeShellCommand::listCommandPriorityHigh;
QQueue<FacadeShellCommand::SDescriptionCommand> FacadeShellCommand::queueComanndPriorityLow;
QQueue<FacadeShellCommand::SDescriptionCommand> FacadeShellCommand::queueComanndPriorityHigh;
std::unique_ptr<FacadeShellCommand::SDescriptionCommand> FacadeShellCommand::currentCommand;
QMutex FacadeShellCommand::mutex;

//----------------------------------------------------------------------------------------/
FacadeShellCommand::FacadeShellCommand(QObject *parent): QObject(parent)
{}
//----------------------------------------------------------------------------------------/
void FacadeShellCommand::InitClass()
{
    // заполняем список команд
    // с низким приоритетом
    listCommandPriorityLow << "get" << "drop" << "git rm"
                           << "direct" << "indirect"
                              ;
    // с высоким приоритетом
    listCommandPriorityHigh << "clone" << "sync" << "whereis" << "rm"
                            << "Info";
}
//----------------------------------------------------------------------------------------/
FacadeShellCommand* FacadeShellCommand::GetInstance()
{
    assert(instance);
    return instance.get();
}
//----------------------------------------------------------------------------------------/
void FacadeShellCommand::TryStartNextCommand(const QString& baseNameCommand, ShellTask* currentTask,
                                             const IRepository* repository)
{
    QMutexLocker locker(&mutex);
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
}
//----------------------------------------------------------------------------------------/
void FacadeShellCommand::TryStartNextCommand()
{
    QMutexLocker locker(&mutex);

    // сообщаем, что команда завершилась
    emit instance->FinishWaitCommand();

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
    else
    {
        // больше команд нет, сбрасываем указатель
        currentCommand.reset();
    }
}
//----------------------------------------------------------------------------------------/
void FacadeShellCommand::ClearCommandForRepository(const IRepository* repository)
{
    QMutexLocker locker(&mutex);
    // ищем в командах с низким приоритетом
    QQueue<SDescriptionCommand>::iterator it;
    do
    {
        it = std::find(queueComanndPriorityLow.begin(), queueComanndPriorityLow.end(), repository);
        if(it != queueComanndPriorityLow.end())
        {
              // перед удалением указателя чистим еще и таск(тк задача не выполнялась)
              delete it->task;
              it = queueComanndPriorityLow.erase(it);
        }
    }
    while(it != queueComanndPriorityLow.end());

    // с высоким приоритетом
    do
    {
        it = std::find(queueComanndPriorityHigh.begin(), queueComanndPriorityHigh.end(), repository);
        if(it != queueComanndPriorityHigh.end())
        {
            // перед удалением указателя чистим еще и таск(тк задача не выполнялась)
            delete it->task;
            it = queueComanndPriorityHigh.erase(it);
        }
    }
    while(it != queueComanndPriorityHigh.end());
}
//----------------------------------------------------------------------------------------/
bool FacadeShellCommand::IsExecuteCommandForRepository(const IRepository* repository)
{
    QMutexLocker locker(&mutex);
    if(currentCommand && currentCommand->repository == repository)
        return true;
    else
        return false;
}
//----------------------------------------------------------------------------------------/



