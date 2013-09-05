#ifndef IPARSINGCOMMANDOUT_H
#define IPARSINGCOMMANDOUT_H

#include <iostream>
#include <QStringList>
#include <QRegExp>

class IParsingCommandOut
{
public:
    IParsingCommandOut();
    virtual ~IParsingCommandOut();

    /** @brief действия перед запуском команды */
    virtual void        SetParamBeforeStartCommand();

    /**
     * @brief слот, в который будут поступать данные со стандартного потока вывода при выполнении команды
     * @param listData - список данных, заполненный согласно протоколу парсинга каждой команды
     * @return 0 - нет ошибок
     */
    void                GetNewDataStdOut();

    /** @brief действия по окончанию выполнения команды */
    virtual void        SetParamAfterEndCommand(int exitCode);

    /** @brief функция парсинга, у каждого класса будет своя реализация */
    virtual void        ParsingData() const = 0;

    /** @brief взятие данных после парсинга по требованию */
    virtual QStringList GetParsingData() const;

protected:
    /** @brief список данных, поступивших на входной поток данных */
    QStringList         dataStdOut;

    /** @brief список обработанных парсингом данных */
    QStringList         dataAfterParsing;

    /** @brief команда стартовала */
    bool                commandStart;
    /** @brief команда завершилась */
    bool                commandEnd;
    /** @brief код завершения процесса 0 - нет ошибок, иначе с ошибкой */
    int                 exitCodeCommand;

signals:
    // сигнал, которым сообщаем, что новые данные готовы после парсинга
    void                readyNewDataStdOut() {};

};
#endif // IPARSINGCOMMANDOUT_H
