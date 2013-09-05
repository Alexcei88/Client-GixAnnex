#ifndef IPARSINGCOMMANDOUT_H
#define IPARSINGCOMMANDOUT_H

#include <iostream>
#include <QStringList>

class TShell;

class IParsingCommandOut
{
public:
    IParsingCommandOut();
    virtual ~IParsingCommandOut();

    /**
     * @brief GetNewDataStdOut - слот, в который будут поступать данные со стандартного потока вывода при выполнении команды
     * @param listData - список данных, заполненный согласно протоколу парсинга каждой команды
     * @return 0 - нет ошибок
     */
    void    GetNewDataStdOut();

};
#endif // IPARSINGCOMMANDOUT_H
