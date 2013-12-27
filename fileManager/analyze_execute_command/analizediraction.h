#ifndef ANALIZEDIR_H
#define ANALIZEDIR_H

/*
 * КЛАСС АНАЛИЗА ДИРЕКТОРИИ(ИЛИ ФАЙЛА)
 * При создании класса передаем директорию, в которой мы должны выполнить действия
 * Метод
*/

#include "define.h"

// Qt Stuff
#include <QString>
#include <QList>
#include <QDir>

namespace AnalyzeCommand
{

class AnalizeDirOnAction
{
public:
    AnalizeDirOnAction(const QString& dir);

    /** @brief Говорим, что была выполнена работа над  файлом */
    void            WasActionForFile(const QString& file);

    /** @brief Была ли выполнена работа над файлом/директорией */
    bool            IsWasActionForFile(const QString& file) const;

    /** @brief проверяет, над всеми ли файлами/директориями была выполнена работа в текущей директории
     * если над всеми, то модифицирует список файлов, добавляя директорию
     * @param pathListFileDir - список файлов и директорий, над которыми выполнены действия
     * @param pathDir - путь к директории, в которое проверяем эти файлы
     * @return true - над всеми, поэтому можем список заменить одной директорией
     *         false - не над всеми */
    static bool     WasActionForAllFileDirOnDir(QStringList &files, const QString& dir);

    /** @brief по имеющемуся списку файлов возвращает список возможных директорий */
    static QStringList ListAllDirOfFile(const QStringList &files);

private:
    // служебные классы
    static QDir      dirService;
    static QFileInfo fileInfo;

    // начальная директория
    const boost::shared_ptr<const QDir> dir;
};

}

#endif // ANALIZEDIR_H
