#ifndef IANALYZEEXECUTECOMMANDGET_H
#define IANALYZEEXECUTECOMMANDGET_H

// Qt stuff
#include <QList>
#include <QString>
#include <QFileInfo>

#include "analyzeexecutecommand.h"
#include "define.h"

namespace AnalyzeCommand
{

class FacadeAnalyzeCommand;
class AnalizeDirOnActionPrivate;

class AnalyzeExecuteCommandGet: public AnalyzeExecuteCommand
{
public:
    // mode - режим запуска команды, true - автоматический, false - ручной
    AnalyzeExecuteCommandGet(FacadeAnalyzeCommand& facadeAnalyzeCommand, const bool mode);

    virtual void        StartExecuteCommand() override;
    virtual void        EndExecuteCommand(const bool wasExecute = true) override;
    virtual void        ExecuteAddActionForAnalizeExecuteCommand() override;

    void                StartGetContentFile(const QString&file);
    void                EndGetContentFile(const QString& file);
    void                ErrorGetContentFile(const QString&file, const QString&error);

    void                SetPathGetContent(const QString& file);

    /** @brief Идет ли в текущей директории(или сам файл) получение контента в текущий момент времени */
    bool                IsGettingContentFileDir(const QString& currentPath, const QString& file) const;
    /** @brief Есть ли ошибка получения контента в текущей директории(или сам текущий файл) в текущий момент времени */
    static bool         IsErrorGettingContentFileDir(const QString& currentPath, const QString& file);

private:
    // режим запуска команды
    const bool          modeStart;

    /** @brief файл/директория, для которой запущена команда */
    QString             fileGetContent;
    /** @brief файл/директория, на которые дано задание на скачивание */
    boost::shared_ptr<AnalizeDirOnActionPrivate> gettingContentFileQueue;
    /** @brief файл/директория, скачивание которых завершилось неудачей */
    static boost::shared_ptr<AnalizeDirOnActionPrivate> errorGettingContentFile;
    /** @brief файл, который сейчас скачивается */
    QString             gettingContentFile;
    /** @brief Последний файл, который скачивается */
    QString             lastGettingContentFile;
    /** @brief Список файлов, скаченные за текущую сессию
     * (сессия- период между вызовами функции ExecuteAddActionForAnalizeExecuteCommand */
    static QStringList  lastGettingContentFiles;

    /** @brief Перебирает рекурсивно все файлы в переданном пути,
     *  если у файла есть уже контент, то послыает сигнал, что контент уже получен */
    void                ForeachFilesHaveContentAlready(const QString& path) const;
    /** @brief Модификация списка файлов GettingContentFile */
    bool                ModificationGettingContentFileQueue();
    /** @brief Модификация списка файлов ErrorGettingContentFile */
    static bool         ModificationErrorGettingContentFile();

    // в качестве служебных целей
    mutable QFileInfo   fileInfo;

};
}

#endif // IANALYZEEXECUTECOMMANDGET_H
