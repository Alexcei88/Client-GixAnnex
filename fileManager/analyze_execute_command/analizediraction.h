#ifndef ANALIZEDIR_H
#define ANALIZEDIR_H

/*
 * КЛАСС АНАЛИЗА ДИРЕКТОРИИ(ИЛИ ФАЙЛА)
 * При создании класса передаем директорию, в которой мы должны выполнить действия
 * Метод
*/

#include "define.h"

// Qt Stuff
#include <QStringList>
#include <QList>
#include <QDir>

namespace AnalyzeCommand
{

class AnalizeDirOnActionPrivate
{
public:
    AnalizeDirOnActionPrivate();
    AnalizeDirOnActionPrivate(const QString& dir);

    /** @brief Найден ли данный файл(директория) в списках файлов, над которыми нужно выполнить действия */
    bool                IsFindFileOnDirAction(const QString& file) const;

    /** @brief Была ли выполнена работа над файлом/директорией */
    bool                IsWasActionForFile(const QString& file) const;

    /** @brief Проверяет, над всеми ли файлами/директориями была выполнена работа в текущей директории
     * если над всеми, то модифицирует список файлов, объединяя просто в директорию
     * @param pathListFileDir - список файлов и директорий, над которыми выполнены действия
     * @param pathDir - путь к директории, в которое проверяем эти файлы
     * @return true - над всеми, поэтому можем список заменить одной директорией
     *         false - не над всеми */
    bool                WasActionForAllFileDirOnDir(QStringList &files, const QString& dir);

    /** @brief По имеющемуся списку файлов возвращает список корневых директорий */
    QStringList         ListAllDirOfFile(const QStringList &files);

    /** @brief Чистка списков файлов/директорий
        @param filesWasAction - список файлов, над которыми были выполнены действия
        @param filesMustToBeAction - список файлов, над которым нужно выполнить действия
        @param fileEndAction - файл, над которым закончилось выполняться действие
    */
    void                ClearListAction(QStringList& filesWasAction, QStringList& filesMustToBeAction, const QString fileEndAction = "");

    // спиcок файлов/директорий, над которыми было выполнено действие
    QStringList         filesWasAction;
    // список файлов/директорий, над которыми нужно выполнить действия
    QStringList         filesMustToBeAction;

private:
    // служебные классы
    mutable QDir        dirService;
    mutable QFileInfo   fileInfo;

};

}

#endif // ANALIZEDIR_H
