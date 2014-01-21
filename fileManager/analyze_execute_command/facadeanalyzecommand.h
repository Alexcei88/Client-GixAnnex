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

// boost stuff
#include <boost/function.hpp>
#include <boost/bind.hpp>

/*
 * КЛАСС ФАСАД, В КОТОРОМ СОБИРАЕТСЯ ВСЯ ИНФА ДЛЯ АНАЛИЗА ПО ХОДУ ВЫПОЛНЕНИЯ КОМАНД
*/

namespace AnalyzeCommand
{

class AnalizeDirOnActionPrivate;
class AnalyzeExecuteCommand;
class AnalyzeExecuteCommandGet;
class AnalyzeExecuteCommandDrop;

class FacadeAnalyzeCommand
{
public:
    FacadeAnalyzeCommand();
    ~FacadeAnalyzeCommand();

    /** @brief Установка текущего пути репозитория */
    void                SetCurrentPathRepository(const QString& currentPath);

    /** @brief Установка текущей команды, которая выполняется */
    void                SetCurrentExecuteCommand(AnalyzeExecuteCommand* command);
    /** @brief Сброс текущей команд */
    void                ResetCurrentExecuteCommand();

    //-------------------  GET  ----------------------------------------------/
    /** @brief Добавить команду в список команд , на которых дано задание за скачивание */
    void                AddGetContentFileQueue(AnalyzeExecuteCommandGet *commandGet);
    /** @brief Удалить команду из списка команд, на которых дано задание за скачивание */
    void                RemoveGetContentFileQueue(AnalyzeExecuteCommandGet *commandGet);
    /** @brief Идет ли в текущей директории(или сам текущий файл) получение контента в текущий момент времени */
    bool                IsGettingContentFileDir(const QString& file) const;
    /** @brief Есть ли ошибка получения контента в текущей директории(или сам текущий файл) в текущий момент времени */
    bool                IsErrorGettingContentFileDir(const QString& file) const;

    //-------------------  DROP  ---------------------------------------------/
    /** @brief Добавить файл в очередь файлов, на которых дано задание на удаление */
    void                AddDropContentFileQueue(const QString& file);
    /** @brief Началось удаление файла */
    void                StartDropContentFile(const QString& file);
    /** @brief Закончилось удаление файла */
    void                EndDropContentFile(const QString& file, const bool lock = true);
    /** @brief Закончилось удаление файла с ошибкой  */
    void                ErrorDropContentFile(const QString& file, const QString& error);
    /** @brief идет ли в текущей директории(или сам текущий файл) удаление контента в текущий момент времени */
    bool                IsDroppingContentFileDir(const QString& file) const;
    /** @brief есть ли ошибка получения контента в текущей директории(или сам текущий файл) в текущий момент времени */
    bool                IsErrorDroppingContentFileDir(const QString& file) const;

    /** @brief функция выполнения дополнительных действий в классах анализа хода выполнения команд у текущей команды
     * данную функцию дергать только из потока синхронизации иконок либо по окончании команды, тк она может быть математически затратной
     * \details например, объединение списка файлов в одну директорию(и наоборот)
    */
    void                ExecuteAddActionForAnalizeCommand();

    /** @brief функция чистки списка команд на удаление контента
     * данную функцию дергать по окончании выполнения команды
    */
    void                ClearListDroppingContentFile(const QString& fileEndAction = "");

    // атомарный флаг для потоков, выполняющий команды во threadPool
    static std::atomic_flag* atomicFlagExecuteCommand;

private:

    Q_DISABLE_COPY(FacadeAnalyzeCommand)

    //-------------------  GET  ----------------------------------------------/
    /** @brief список на классы анализа хода выполнения команды get */
    QList<AnalyzeExecuteCommandGet*> listCommandGet;

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
    bool                ModificationListFiles(  AnalizeDirOnActionPrivate* listFiles, boost::function<void (const QStringList&)> addFunc = 0
                                              , const QString& lastFile = "", const QString& currentFileQueue = ""
                                              , const bool end = false) const;

    /** @brief Чистка списка файлов в вспом классах AnalizeDirOnActionPrivate */
    void                ClearListFiles(AnalizeDirOnActionPrivate* listFiles, const QString& fileEndAction = "") const;

    /** @brief Текущий путь в репозитории */
    QDir                currentPathRepository;

    // в качестве служебных целей
    mutable QFileInfo   fileInfo;

    /** @brief Указатель на команду, которая сейчас выполняется */
    AnalyzeExecuteCommand* currentAnalyzeExecuteCommand;

};

}

#endif // FACADEANALYZECOMMAND_H
