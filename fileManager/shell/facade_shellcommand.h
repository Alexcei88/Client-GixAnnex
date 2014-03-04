#ifndef FACADE_SHELLCOMMAND_H
#define FACADE_SHELLCOMMAND_H

#include <memory>

#include <QObject>
#include <QQueue>
#include <QMutex>

/****************************************
 * КЛАСС, УПРАВЛЯЮЩИЙ ЗАПУСКОМ КОМАНД
 * УСЛОВИЕ: БОЛЬШЕ ОДНОЙ КОМАНДЫ С ВЫСОКИМ ПРИОРИТЕТРОВ НЕ ЗАПУСКАЕМ
 */

class ShellTask;
class IRepository;

class FacadeShellCommand
{
public:
    /** @brief пытается запустить переданную команду(если удачно, то запускает ее, иначе
         добавляет ее в очередь)
        @param baseNameCommand - базовое имя команды(например, get, drop...)
        @param currentTask - текущая команда
    */
    static void         TryStartNextcommand(const QString& baseNameCommand, ShellTask* currentTask,
                                        const IRepository* repository);

    /** @brief Пытается запустить команду из очереди, если они там есть */
    static void         TryStartNextcommand();

    /** @brief Очищает список команд для заданного репозитория, мы их не запускаем */
    static void         ClearCommandForRepository(const IRepository* repository);

    /** @brief Выполняется ли команда у данного репозитория */
    static bool         IsExecuteCommandForRepository(const IRepository* repository);

private:

    Q_DISABLE_COPY(FacadeShellCommand);

    struct SDescriptionCommand
    {
        // задача
        ShellTask* task;
        // репозиторий, откуда запускаем
        const IRepository* repository;

        bool operator ==(const IRepository* repository)
        {
            if(this->repository == repository) return true;
            else return false;
        }
    };

    /** @brief список команд с низким приоритетом */
    static QStringList  listCommandPriorityLow;

    /** @brief список команд с высоким приоритетом */
    static QStringList  listCommandPriorityHigh;

    /** @brief очереди для запуска команд */
    static QQueue<SDescriptionCommand>  queueComanndPriorityLow;
    static QQueue<SDescriptionCommand>  queueComanndPriorityHigh;

    /** @brief очереди для запуска команд */
    static std::unique_ptr<SDescriptionCommand> currentCommand;

    /** @brief мьютекс для многопоточности */
    static QMutex       mutex;

    static void         InitClass();

};

#endif // FACADE_SHELLCOMMAND_H
