#ifndef ANALIZEDIR_H
#define ANALIZEDIR_H

/*
 * КЛАСС АНАЛИЗА ДИРЕКТОРИИ(ИЛИ ФАЙЛА)
 * При создании класса передаем директорию, в которой мы должны выполнить действия
 * Метод
*/

#include <QString>
#include <QDir>

namespace AnalyzeCommand
{

class AnalizeDirOnAction
{
public:
    AnalizeDirOnAction(const QString& dir);

    /** @brief Говорим, что была выполнена работа над  файлом */
    void            WasActionOnFile(const QString& file);

    /** @brief Была ли выполнена работа над файлом/директорией*/
    bool            IsWasActionOnFile(const QString& file) const;

private:
//    const QDir      path;
};

}

#endif // ANALIZEDIR_H
