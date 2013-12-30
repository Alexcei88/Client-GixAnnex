#ifndef IANALYZEEXECUTECOMMAND_H
#define IANALYZEEXECUTECOMMAND_H

#include "facadeanalyzecommand.h"

/* КЛАСС ДЛЯ АНАЛИЗА ХОДА ВЫПОЛНЕНИЯ КОМАНДЫ */

namespace AnalyzeCommand
{
class AnalyzeExecuteCommand
{
public:
    AnalyzeExecuteCommand(FacadeAnalyzeCommand& facadeAnalyzeCommand);
    AnalyzeExecuteCommand(FacadeAnalyzeCommand& facadeAnalyzeCommand, const QString& pathExecuteCommand);

    /** @brief Начало выполнения команды */
    void                StartExecuteCommand();

    /** @brief Остановка выполнения команды
     *  @param Была ли запущена команда(может процесс с командой не смогли создать и она не была выполнена)
    */
    void                EndExecuteCommand(const bool wasExecute = true);
    /** @brief Установка пути, откуда запущена команда */
    void                SetPathExecuteCommand(const QString& path);

protected:
    /** @brief фасад, управляющий анализом выполнения команд */
    FacadeAnalyzeCommand& facadeAnalyzeCommand;
    // путь относительно корня репозитория, откуда была запущена команда
    QString             pathExecuteCommand;

private:
    bool                startCommand;
    bool                endCommand;

};
}

#endif // IANALYZEEXECUTECOMMAND_H
