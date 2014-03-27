#ifndef ANALYZEEXECUTECOMMAND_H
#define ANALYZEEXECUTECOMMAND_H

// std stuff
#include <atomic>

// Qt stuff
#include <QString>
#include <QDir>

namespace AnalyzeCommand
{
class FacadeAnalyzeCommand;

class AnalyzeExecuteCommand
{
public:
    AnalyzeExecuteCommand(FacadeAnalyzeCommand& facadeAnalyzeCommand);
    AnalyzeExecuteCommand(FacadeAnalyzeCommand& facadeAnalyzeCommand, const QString& pathExecuteCommand);

    virtual ~AnalyzeExecuteCommand();

    /** @brief Начало выполнения команды */
    virtual void        StartExecuteCommand();

    /** @brief Завершение выполнения команды
     *  @param Была ли запущена команда(может процесс с командой не смогли создать и она не была выполнена)
    */
    virtual void        EndExecuteCommand(const bool wasExecute = true);

    /** @brief Установка пути, откуда запущена команда */
    inline void         SetPathExecuteCommand(const QString& path) { pathExecuteCommand = path; }
    inline const QString& GetDescriptionCommand() const { return description; }

    /** @brief Функция, которая выполняет доп действия индивидуальные для каждой команды */
    virtual void        ExecuteAddActionForAnalizeExecuteCommand() { }

protected:
    /** @brief Фасад, управляющий анализом выполнения команд */
    FacadeAnalyzeCommand& facadeAnalyzeCommand;
    /** @brief Путь откуда была запущена команда */
    QString             pathExecuteCommand;

    // атомарный флаг для потоков, выполняющий команды во threadPool
    std::atomic_flag*   atomicFlagExecuteCommand;

    bool                startCommand;
    bool                endCommand;

    /** @brief описание команды */
    QString             description;

};
}

#endif // ANALYZEEXECUTECOMMAND_H
