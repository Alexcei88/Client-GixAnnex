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

typedef QMap<QString, QList<AnalizeDirOnActionPrivate> > mapListAnalizeDir;

class ParsingErrorExecuteCommand
{
public:
    ParsingErrorExecuteCommand();
    virtual ~ParsingErrorExecuteCommand();

    /** @brief добавление файла с ошибкой
        @param file - файл
        @param error - строка с ошибкой
    */
    void                AddFileWithError(const QString& file, const QString& error, const QString& description);

protected:

    // перечисление типов ошибок, будет определяться в производных классах
    enum class ErrorType: int;

    /** @brief возвращает идентификатор ошибки
        @param error - строка с ошибкой
    */
    virtual ErrorType   GetIdError(const QString& error) const;

    /** @brief заполняет текстовые описания для идентификации ошибок */
    virtual void        FillErrorIdDescription() = 0;

    /** @brief мэп строковых идентификаторов ошибок */
    QMap <ErrorType, QString> errorIdDescription;

private:
    /** @brief мэп файлов ошибок с идентификаторами
        @details каждый вид ошибок содержит список ошибок, который идентифицируется строкой описания
    */
    QMap <ErrorType, QMap<QString, QList<AnalizeDirOnActionPrivate> > > errorFiles;

    /** @brief мэп функции-решений для каждой ошибки */
    QMap <ErrorType, int>     funcSolution;

};

}
#endif // PARSINGERROREXECUTECOMMAND_H
