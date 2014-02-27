#ifndef ANALYZEEXECUTECOMMANDCOPY_H
#define ANALYZEEXECUTECOMMANDCOPY_H

#include "analyzeexecutecommand.h"
#include "define.h"

// Класс copy будет разновидностью команды get(

namespace AnalyzeCommand
{
class FacadeAnalyzeCommand;
class AnalizeDirOnActionPrivate;

class AnalyzeExecuteCommandCopy: public AnalyzeExecuteCommand
{
public:
    AnalyzeExecuteCommandCopy(FacadeAnalyzeCommand& facadeAnalyzeCommand, const bool& from, const bool& modeStart);
    ~AnalyzeExecuteCommandCopy();

    virtual void        StartExecuteCommand();
    virtual void        EndExecuteCommand(const bool wasExecute = true);
    virtual void        ExecuteAddActionForAnalizeExecuteCommand();

    void                StartCopyContentFile(const QString&file);
    void                EndCopyContentFile(const QString& file);
    void                ErrorCopyContentFile(const QString&file, const QString&error);

    void                SetPathCopyContent(const QString& file);

    /** @brief Идет ли в текущей директории(или сам файл) получение контента в текущий момент времени */
    bool                IsCopyingContentFileDir(const QString& currentPath, const QString& file) const;
private:
    /** @brief файл/директория, для которой запущена команда */
    QString             fileCopyContent;
    /** @brief файл/директория, на которые дано задание на копирование */
    boost::shared_ptr<AnalizeDirOnActionPrivate> copyingContentFileQueue;
    /** @brief файл, который сейчас копируется */
    QString             copyingContentFile;
    /** @brief Последний файл, который скачивался */
    QString             lastCopyingContentFile;
    /** @brief Список файлов, скопированные за текущую сессию
     * (сессия- период между вызовами функции ExecuteAddActionForAnalizeExecuteCommand */
    static QStringList  lastCopyingContentFiles;

    /** @brief Перебирает рекурсивно все файлы в переданном пути,
     *  для анализа, нужно ли выполнять действия над файлами в дирекории*/
    void                ForeachFilesHaveContentAlready(const QString& path);
    /** @brief Модификация списка файлов CopyingContentFile */
    bool                ModificationCopyingContentFileQueue();

    // в качестве служебных целей
    mutable QFileInfo   fileInfo;

    // автоматический(или ручной вызов
    const bool          modeStart;
    // режим копирования(from или to)
    const bool          from;

};
}

#endif // ANALYZEEXECUTECOMMANDCOPY_H
