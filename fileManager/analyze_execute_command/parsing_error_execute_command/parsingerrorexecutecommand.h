#ifndef PARSINGERROREXECUTECOMMAND_H
#define PARSINGERROREXECUTECOMMAND_H

#include <QMap>
#include <QString>

#include "define.h"
#include "analyze_execute_command/analizediraction.h"

namespace AnalyzeCommand
{
    // базовый класс для парсинга ошибок, получаемых при выполнении команд
    // будет разделять все ошибки каждой команды на категории ошибок
    // и предлагать возможные решения, если таковы существуют

class ParsingErrorExecuteCommand
{
public:
    ParsingErrorExecuteCommand();
    virtual ~ParsingErrorExecuteCommand();

protected:

    // перечисление всех типов ошибок
    enum class ErrorType: int {
        UNKNOW_ERROR = -1,
        GET_UNAVAIBLE_CONTENT = 0,
        DROP_HAVE_CONTENT_COUNT_MINIMUM = 10
    };

    /** @brief возвращает идентификатор ошибки
        @param error - строка с ошибкой
    */
    virtual ErrorType   GetIdError(const QString& error) const;

    /** @brief заполняет текстовые описания для идентификации ошибок */
    virtual void        FillErrorIdDescription() = 0;

    /** @brief мэп строковых идентификаторов ошибок */
    QMap <ErrorType, QString> errorIdDescription;

private:

    /** @brief мэп функции-решений для каждой ошибки */
    QMap <ErrorType, int>     funcSolution;

};

}
#endif // PARSINGERROREXECUTECOMMAND_H
