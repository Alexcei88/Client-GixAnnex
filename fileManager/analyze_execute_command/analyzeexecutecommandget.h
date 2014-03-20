#ifndef IANALYZEEXECUTECOMMANDGET_H
#define IANALYZEEXECUTECOMMANDGET_H

// Qt stuff
#include <QList>
#include <QString>
#include <QFileInfo>

// our stuff
#include "analyzeexecutecommand.h"
#include "define.h"

namespace AnalyzeCommand
{

class FacadeAnalyzeCommand;
class AnalizeDirOnActionPrivate;
class ParsingErrorExecuteCommandGet;

class AnalyzeExecuteCommandGet: public AnalyzeExecuteCommand
{
public:
    // mode - режим запуска команды, true - автоматический, false - ручной
    AnalyzeExecuteCommandGet(FacadeAnalyzeCommand& facadeAnalyzeCommand, const bool mode);
    ~AnalyzeExecuteCommandGet();

    virtual void        StartExecuteCommand();
    virtual void        EndExecuteCommand(const bool wasExecute = true);
    virtual void        ExecuteAddActionForAnalizeExecuteCommand();

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
    /** @brief класс анализа сообщений об ошибках */
    static boost::shared_ptr<ParsingErrorExecuteCommandGet> errorGettingContentFile;

    /** @brief файл, который сейчас скачивается */
    QString             gettingContentFile;
    /** @brief Последний файл, который скачивается */
    QString             lastGettingContentFile;
    /** @brief Список файлов, скаченные за текущую сессию
     * (сессия- период между вызовами функции ExecuteAddActionForAnalizeExecuteCommand */
    static QStringList  lastGettingContentFiles;

    /** @brief Перебирает рекурсивно все файлы в переданном пути,
     *  если у файла есть уже контент, то посылает сигнал, что контент уже получен */
    void                ForeachFilesHaveContentAlready(const QString& path);
    /** @brief Модификация списка файлов GettingContentFile */
    bool                ModificationGettingContentFileQueue();
    /** @brief Модификация списка файлов ErrorGettingContentFile */
    static bool         ModificationErrorGettingContentFile();

    // в качестве служебных целей
    mutable QFileInfo   fileInfo;

};
}

#endif // IANALYZEEXECUTECOMMANDGET_H
