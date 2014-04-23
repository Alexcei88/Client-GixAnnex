#ifndef PARSINGERROREXECUTECOMMANDWITHFILES_H
#define PARSINGERROREXECUTECOMMANDWITHFILES_H

#include "parsingerrorexecutecommand.h"

namespace AnalyzeCommand
{
typedef QMap<QString, QList<AnalizeDirOnActionPrivate> > mapListAnalizeDir;

class ParsingErrorExecuteCommandWithFiles : public ParsingErrorExecuteCommand
{
public:
    ParsingErrorExecuteCommandWithFiles();

    /** @brief Добавление файла с ошибкой
        @param file - полный путь к файлу
        @param error - строка с ошибкой
    */
    void                AddFileWithError(const QString& file, const QString& error, const QString& description);

    /** @brief Есть ли заданный файл в векторе ошибок
        @param file - полный путь к файлу
        @return true/false
    */
    bool                IsFileWithError(const QString& file) const;

    /** @brief Модификация списка файлов с ошибками
        @param lastWasActionFiles - список файлов, над которыми были выполнены действия
        в последнюю сессию
        @return
    */
    bool                ModificationErrorGettingContentFile(const QStringList& lastWasActionFiles);

private:

    /** @brief Мэп файлов ошибок с идентификаторами
        @details каждый вид ошибок содержит список ошибок, который идентифицируется названием файла
    */
    QMap <ErrorType, QMap<QString, QList<AnalizeDirOnActionPrivate> > > errorFiles;

};
}

#endif // PARSINGERROREXECUTECOMMANDWITHFILES_H
