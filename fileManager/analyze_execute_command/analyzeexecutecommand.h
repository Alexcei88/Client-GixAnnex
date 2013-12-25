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

    /** @brief Начало выполнения команды */
    void                StartExecuteCommand();
    /** @brief Остановка выполнения команды */
    void                EndExecuteCommand();
    /** @brief Установка пути, откуда запущен бонус */
    void                SetPathExecuteCommand(const QString& path);



protected:
    /** @brief фасад, управляющий анализом выполнения команд */
    FacadeAnalyzeCommand& facadeAnalyzeCommand;
    // путь относительно корня репозитория, откуда была запущена команда
    QString             pathExecuteCommand;



private:
    bool startCommand;
    bool endCommand;

};
}

#endif // IANALYZEEXECUTECOMMAND_H
