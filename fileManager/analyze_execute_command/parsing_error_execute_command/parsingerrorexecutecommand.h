#ifndef PARSINGERROREXECUTECOMMAND_H
#define PARSINGERROREXECUTECOMMAND_H

#include <QMap>
#include <QString>

#include "define.h"
#include "analyze_execute_command/analizediraction.h"
#include "../repository/irepository.h"
#include <boost/function.hpp>

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

    // начало выполнения команды
    virtual void        StartExecuteCommand() = 0;
    // конец выполнения команды
    virtual void        EndExecuteCommand() = 0;

    struct Error
    {
        // команда, при которой возникла ошибка
        const QString executeCommand;
        // репозиторий, в котором возникла ошибка
        const IRepository* const repository;
        Error(const QString& execute, const IRepository* repository):
            executeCommand(execute)
          , repository(repository)
        {}

        bool operator < (const Error& error1) const
        {
            return this->executeCommand < error1.executeCommand;
        }
    };

    // описание ошибки для вьювера
    struct ErrorDescriptionView
    {
        // текстовое описание ошибки(заголовок)
        QString errorDescription;
    };

    /** @brief мэп описаловок ошибок для вьювера */
    QMap<ErrorType, ErrorDescriptionView> errorDescriptionView;

    /** @brief мэп функций-callback-ов для возможных решений ошибок */
    QMap <ErrorType, boost::function<void (const QString& file)> > funcErrorSolution;
};

}
#endif // PARSINGERROREXECUTECOMMAND_H
