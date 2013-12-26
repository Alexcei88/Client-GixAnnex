#ifndef FACADEANALYZECOMMAND_H
#define FACADEANALYZECOMMAND_H

#include <QString>
#include <QList>
#include <QMap>
#include <QDir>

/*
 * КЛАСС ФАСАД, В КОТОРОМ СОБИРАЕТСЯ ВСЯ ИНФА ПО АНАЛИЗУ ВЫПОЛНЕНИЯ КОМАНДЫ
*/

namespace AnalyzeCommand
{

class FacadeAnalyzeCommand
{
public:
    FacadeAnalyzeCommand();

    /** @brief Установка текущего пути репозитория */
    void                SetCurrentPathRepository(const QString& currentPath);


    //-------------------  GET  ----------------------------------------------/
    /** @brief Добавить файл в очередь файлов, на которых дано задание за скачивание */
    void                AddGetContentFileQueue(const QString& file);
    void                StartGetContentFile(const QString& file);
    void                EndGetContentFile(const QString& file);
    void                ErrorGetContentFile(const QString& file, const QString& error);
    /** @brief идет ли в текущей директории(или сам текущий файл) получение контента в текущий момент времени */
    bool                IsGettingContentFileDir(const QString& file) const;
    /** @brief есть ли ошибка получения контента в текущей директории(или сам текущий файл) в текущий момент времени */
    bool                IsErrorGettingContentFileDir(const QString& file) const;

    //-------------------  DROP  ---------------------------------------------/
    /** @brief Добавить файл в очередь файлов, на которых дано задание на удаление */
    void                AddDropContentFileQueue(const QString& file);
    void                StartDropContentFile(const QString& file);
    void                EndDropContentFile(const QString& file);
    void                ErrorDropContentFile(const QString& file, const QString& error);
    /** @brief идет ли в текущей директории(или сам текущий файл) удаление контента в текущий момент времени */
    bool                IsDroppingContentFileDir(const QString& file) const;
    /** @brief есть ли ошибка получения контента в текущей директории(или сам текущий файл) в текущий момент времени */
    bool                IsErrorDroppingContentFileDir(const QString& file) const;

private:
    // вектор, содержащий файлы/директории, на которые дано задание на скачивание
    QList<QString>      gettingContentFilQueue;
    // файл, который сейчас скачивается
    QString             gettingContentFile;
    // вектор, содержащий файлы, которые не удалось скачать(ключ - имя файла, значение - причина ошибки)
    QMap<QString, QString> errorGettingContentFile;

    // вектор, содержащий файлы, которые сейчас удаляются(или дано задание на удаление)
    QList<QString>      droppingContentFileQueue;
    // файл, который сейчас удаляется
    QString             droppingContentFile;
    // вектор, содержащий файлы, которые не удалось удалить(ключ - имя файла, значение - причина ошибки)
    QMap<QString, QString> errorDroppingContentFile;

    /** @brief Содержит ли директория файл в поддиректориях */
    bool                DirContainsFile(const QString& dir, const QString& file) const;

    /** @brief Текущий путь в репозитории */
    QDir                currentPathRepository;



};

}

#endif // FACADEANALYZECOMMAND_H
