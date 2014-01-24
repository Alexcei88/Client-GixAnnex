#ifndef ANALYZEEXECUTECOMMANDDROP_H
#define ANALYZEEXECUTECOMMANDDROP_H

// Qt stuff
#include <QList>

#include "analyzeexecutecommand.h"
#include "define.h"

namespace AnalyzeCommand
{

class FacadeAnalyzeCommand;
class AnalizeDirOnActionPrivate;

class AnalyzeExecuteCommandDrop: public AnalyzeExecuteCommand
{
public:
    AnalyzeExecuteCommandDrop(FacadeAnalyzeCommand& facadeAnalyzeCommand, const bool mode);

    virtual void        StartExecuteCommand() override;
    virtual void        EndExecuteCommand(const bool wasExecute = true) override;
    virtual void        ExecuteAddActionForAnalizeExecuteCommand() override;

    void                StartDropContentFile(const QString& file);
    void                EndDropContentFile(const QString& file);
    void                ErrorDropContentFile(const QString& file, const QString& error);

    void                SetPathDropContent(const QString& file);

    /** @brief Идет ли в текущей директории(или сам файл) удаление контента в текущий момент времени */
    bool                IsDroppingContentFileDir(const QString& currentPath, const QString& file) const;
    /** @brief Есть ли ошибка получения контента в текущей директории(или сам файл) в текущий момент времени */
    static bool         IsErrorDroppingContentFileDir(const QString& currentPath, const QString& file);

private:
    // режим запуска команды
    const bool          modeStart;

    /** @brief файл/директория, которую удаляем командой */
    QString             fileDropContent;
    /** @brief файлы/директории, на которые дано задание на удаление */
    boost::shared_ptr<AnalizeDirOnActionPrivate> droppingContentFileQueue;
    /** @brief файл/директория, удаление которых завершилось неудачей */
    static boost::shared_ptr<AnalizeDirOnActionPrivate> errorDroppingContentFile;
    /** @brief файл, который сейчас удаляется */
    QString             droppingContentFile;
    /** @brief Последний файл, который удалился */
    QString             lastDroppingContentFile;
    /** @brief Список файлов, удаленные за текущую сессию
     * (сессия- период между вызовами функции ExecuteAddActionForAnalizeExecuteCommand */
    static QStringList  lastDroppingContentFiles;

    /** @brief перебирает рекурсивно все файлы в переданном пути,
     *  если у файла уже нет контента, то послылаем сигнал, что контент уже удален */
    void                ForeachFilesNoContentAlready(const QString& path);
    /** @brief Модификация списка файлов DroppingContentFile */
    bool                ModificationDroppingContentFileQueue();
    /** @brief Модификация списка файлов ErrorDroppingContentFile */
    static bool         ModificationErrorDroppingContentFile();

    // в качестве служебных целей
    mutable QFileInfo   fileInfo;
};

}

#endif // ANALYZEEXECUTECOMMANDDROP_H
