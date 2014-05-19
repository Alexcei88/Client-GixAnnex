#ifndef PARSINGERROREXECUTECOMMANDWITHFILES_H
#define PARSINGERROREXECUTECOMMANDWITHFILES_H

#include "parsingerrorexecutecommand.h"

namespace AnalyzeCommand
{
class ParsingErrorExecuteCommandWithFiles : public ParsingErrorExecuteCommand
{
    typedef QMap<ParsingErrorExecuteCommand::Error, AnalizeDirOnActionPrivate> mapAnalizeDir;

public:
    ParsingErrorExecuteCommandWithFiles();

    /** @brief Добавление файла с ошибкой
        @param file - полный путь к файлу
        @param error - строка с ошибкой
        @param description - описание ошибки
    */
    void                AddFileWithError(  const QString& file, const QString& error
                                         , const QString& description
                                         , const IRepository* repository);

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

    // начало выполнения новой команды
    virtual void        StartExecuteCommand();
    // конец выполнения команды
    virtual void        EndExecuteCommand();
private:

    /** @brief Мэп файлов ошибок с идентификаторами
        @details каждый вид ошибок содержит список ошибок, который идентифицируется строкой-описания
    */
    QMap <ErrorType, mapAnalizeDir> errorFiles;

    /** @brief Мэп файлов ошибок за последнюю сессию */
    QMap <ErrorType, mapAnalizeDir> errorFilesLastSession;

    /** @brief Добавление файла с ошибкой
        @param file - полный путь к файлу
        @param error - строка с ошибкой
        @param description - описание ошибки
    */
    void                AddFileWithError(const QMap <ErrorType, mapAnalizeDir>& mapSession);

};
}

#endif // PARSINGERROREXECUTECOMMANDWITHFILES_H
