#ifndef FACADEANALYZECOMMAND_H
#define FACADEANALYZECOMMAND_H

// Qt stuff
#include <QString>
#include <QList>
#include <QMap>
#include <QDir>

// std stuff
#include <atomic>


#include "define.h"
/*
 * КЛАСС ФАСАД, В КОТОРОМ СОБИРАЕТСЯ ВСЯ ИНФА ПО АНАЛИЗУ ВЫПОЛНЕНИЯ КОМАНДЫ
*/

namespace AnalyzeCommand
{

class AnalizeDirOnActionPrivate;

class FacadeAnalyzeCommand
{
public:
    FacadeAnalyzeCommand();
    ~FacadeAnalyzeCommand();

    /** @brief Установка текущего пути репозитория */
    void                SetCurrentPathRepository(const QString& currentPath);

    //-------------------  GET  ----------------------------------------------/
    /** @brief Добавить файл в очередь файлов, на которых дано задание за скачивание */
    void                AddGetContentFileQueue(const QString& file);
    /** @brief Началось скачивание файла */
    void                StartGetContentFile(const QString& file);
    /** @brief Закончилось скачивание файла */
    void                EndGetContentFile(const QString& file);
    /** @brief Закончилось скачивание файла с ошибкой  */
    void                ErrorGetContentFile(const QString& file, const QString& error);
    /** @brief идет ли в текущей директории(или сам текущий файл) получение контента в текущий момент времени */
    bool                IsGettingContentFileDir(const QString& file) const;
    /** @brief есть ли ошибка получения контента в текущей директории(или сам текущий файл) в текущий момент времени */
    bool                IsErrorGettingContentFileDir(const QString& file) const;

    //-------------------  DROP  ---------------------------------------------/
    /** @brief Добавить файл в очередь файлов, на которых дано задание на удаление */
    void                AddDropContentFileQueue(const QString& file);
    /** @brief Началось удаление файла */
    void                StartDropContentFile(const QString& file);
    /** @brief Закончилось удаление файла */
    void                EndDropContentFile(const QString& file);
    /** @brief Закончилось удаление файла с ошибкой  */
    void                ErrorDropContentFile(const QString& file, const QString& error);
    /** @brief идет ли в текущей директории(или сам текущий файл) удаление контента в текущий момент времени */
    bool                IsDroppingContentFileDir(const QString& file) const;
    /** @brief есть ли ошибка получения контента в текущей директории(или сам текущий файл) в текущий момент времени */
    bool                IsErrorDroppingContentFileDir(const QString& file) const;

    /** @brief функция модификации списка файлов в вспомогательных классах AnalizeDirAction
     * данную функцию дергать только из потока синхронизации иконок, тк она может быть математически затратной
     * \details например, объединение списка файлов в одну директорию(и наоборот)
    */
    void                ModificationAllListFiles();

private:

    Q_DISABLE_COPY(FacadeAnalyzeCommand)

    //-------------------  GET  ----------------------------------------------/
    /** @brief файлы/директории, на которые дано задание на скачивание */
    boost::shared_ptr<AnalizeDirOnActionPrivate> gettingContentFileQueue;
    /** @brief файл, который сейчас скачивается */
    QString             gettingContentFile;

#warning MUST_TO_BE_REFACTORING
    // вектор, содержащий файлы, которые не удалось скачать(ключ - имя файла, значение - причина ошибки)
    // нужно тоже объединят в более крупные стуктуры данных(в папки)
    // а то слишком слишком много памяти будет съедать
    QMap<QString, QString> errorGettingContentFile;

    //-------------------  DROP  ---------------------------------------------/
    /** @brief файлы/директории, на которые дано задание на удаление */
    boost::shared_ptr<AnalizeDirOnActionPrivate> droppingContentFileQueue;
    /** @brief файл, который сейчас удаляется */
    QString             droppingContentFile;
    /** @brief вектор, содержащий файлы, которые не удалось удалить
     *  (ключ - имя файла, значение - причина ошибки)
     */
    QMap<QString, QString> errorDroppingContentFile;

    /** @brief Содержит ли директория файл(в том числе и в поддиректориях) */
    bool                DirContainsFile(const QString& dir, const QString& file) const;

    /** @brief Модификация списка файлов в вспом классах AnalizeDirOnActionPrivate */
    void                ModificationListFiles(AnalizeDirOnActionPrivate *listFiles);

    /** @brief Текущий путь в репозитории */
    QDir                currentPathRepository;

    // в качестве служебных целей
    mutable QFileInfo   fileInfo;

    // атомарный флаг для потоков, выполняющий команды во threadPool
    std::atomic_flag*   atomicFlagExecuteCommand;

};

}

#endif // FACADEANALYZECOMMAND_H
