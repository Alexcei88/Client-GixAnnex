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
     * если над всеми, то модифицирует список файлов, объединяя список файлов одной диреткории просто в одну в директорию
     * @param filesWasAction - список файлов и директорий, над которыми выполнены действия
     * @param filesNotWasAction - список файлов и директорий, над которыми не выполнены действия
     * @param dir - путь к директории, в которое проверяем эти файлы
     * @return true - над всеми, поэтому можем список заменить одной директорией
     *         false - не над всеми */
    bool                WasActionForAllFileDirOnDir(  QStringList &filesWasAction
                                                    , QStringList& filesNotWasAction
                                                    , const QString& dir) const;

    /** @brief Объединение списка файлов/директорий  в одну директорию */
    void                UnionAllFileDirOnDir(QStringList& files, const QString& dir) const;

    /** @brief По имеющемуся списку файлов возвращает список корневых директорий */
    QStringList         ListAllDirOfFile(const QStringList &files) const;

    /** @brief Проверяет, была ли выполнена вся работа над данной директорией
    * @param dir - проверяемая директория
    * @param lastFileAction - последний файл, над которым была выполнена работа
    * @return true - да, работа над директорией была выполнена
    *         false - нет, работа в данной директории еще ведеться
    */
    bool                EndActionForDir(const QString& dir, const QString& lastFileAction) const;

    /** @brief Чистка списков файлов/директорий
        @param filesWasAction - список файлов, над которыми были выполнены действия
        @param filesMustToBeAction - список файлов, над которым нужно выполнить действия
        @param fileEndAction - файл, над которым закончилось выполняться действие
    */
    void                ClearListAction(QStringList& filesWasAction, QStringList& filesMustToBeAction, const QString fileEndAction = "");

    /** @brief спиcок файлов/директорий, над которыми было выполнено действие */
    QStringList         filesWasAction;
    /** @brief список файлов/директорий, над которыми нужно выполнить действия */
    QStringList         filesMustToBeAction;

private:
    // служебные классы
    mutable QDir        dirService;
    mutable QFileInfo   fileInfo;
};

}

#endif // ANALIZEDIR_H
