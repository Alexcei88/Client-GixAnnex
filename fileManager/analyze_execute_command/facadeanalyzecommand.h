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
 * КЛАСС ФАСАД, В КОТОРОМ СОБИРАЕТСЯ ВСЯ ИНФА ДЛЯ АНАЛИЗА ПО ХОДУ ВЫПОЛНЕНИЯ КОМАНД
*/

class IRepository;

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
    FacadeAnalyzeCommand(IRepository* repository);

    ~FacadeAnalyzeCommand();

    /** @brief Установка текущего пути репозитория */
    void                SetCurrentPathRepository(const QString& currentPath);
    /** @brief Установка текущей команды, которая выполняется */
    void                SetCurrentExecuteCommand(AnalyzeExecuteCommand* command);
    /** @brief Сброс текущей команды */
    void                ResetCurrentExecuteCommand();

    //-------------------  CLONE ---------------------------------------------/
    /** @brief Окончание клонирования репозитория
        @param information - поле, которое содержит информацию, название поддиректории куда скопирован
        репозиторий, в случаи же ошибки, причину ошибки
    */
    void                EndCloneRepository(const bool& successfully, const QString& information) const;
    /** @brief Инициализация репозитория */
    void                InitNewRepository() const;

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
    /** @brief Добавить команду в список команд , на которых дано задание за скачивание */
    void                AddDropContentFileQueue(AnalyzeExecuteCommandDrop *commandDrop);
    /** @brief Удалить команду из списка команд, на которых дано задание за скачивание */
    void                RemoveDropContentFileQueue(AnalyzeExecuteCommandDrop *commandDrop);
    /** @brief идет ли в текущей директории(или сам текущий файл) удаление контента в текущий момент времени */
    bool                IsDroppingContentFileDir(const QString& file) const;
    /** @brief есть ли ошибка получения контента в текущей директории(или сам текущий файл) в текущий момент времени */
    bool                IsErrorDroppingContentFileDir(const QString& file) const;

    //-------------------  CHANGE DIRECT MODE --------------------------------/
    void                ErrorChangeDirectMode();
    void                ChangeDirectMode(const bool& mode);

    /** @brief функция выполнения дополнительных действий в классах анализа хода выполнения команд у текущей команды
     * данную функцию дергать только из потока синхронизации иконок либо по окончании команды, тк она может быть математически затратной
     * \details например, объединение списка файлов в одну директорию(и наоборот)
    */
    void                ExecuteAddActionForAnalizeCommand();

    /** @brief Содержит ли директория файл(в том числе и в поддиректориях) */
    static bool         DirContainsFile(const QString& dir, const QString& file);

    // атомарный флаг для потоков, выполняющий команды во threadPool
    static std::unique_ptr<std::atomic_flag> atomicFlagExecuteCommand;

    /** @brief Возвращает константный указатель на класс репозитория, с которым фасад работает */
    inline const IRepository* GetRepository() { return repository; }

private:

    Q_DISABLE_COPY(FacadeAnalyzeCommand)

    /** @brief Cписок на классы анализа хода выполнения команды get */
    QList<AnalyzeExecuteCommandGet*> listCommandGet;
    /** @brief Cписок на классы анализа хода выполнения команды drop */
    QList<AnalyzeExecuteCommandDrop*> listCommandDrop;

    /** @brief Текущий путь в репозитории */
    QDir                currentPathRepository;

    /** @brief Указатель на команду, которая сейчас выполняется */
    AnalyzeExecuteCommand* currentAnalyzeExecuteCommand;

    // в качестве служебных целей
    static QFileInfo    fileInfo;
    // репозиторий, с которым работает данный класс
    IRepository*        repository;
};

}
#endif // FACADEANALYZECOMMAND_H
