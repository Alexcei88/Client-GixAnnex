#ifndef SHELLCOMMAND_H
#define SHELLCOMMAND_H

#include "tshell.h"


class ShellCommand
{
public:
    enum TYPE_COMMAND
    {
        INIT_REPO = 0
       ,CLONE_REPO = 1
       ,ADD_FILE = 2
       ,GET_CONTENT = 3
       ,WHEREIS_COMMAND = 4
        // всего различных парсингов
       ,COUNT_TYPE_COMMAND
    };

    ShellCommand();
    ~ShellCommand();

    // 1. Инициализация репозитория
    GANN_DEFINE::RESULT_EXEC_PROCESS InitRepositories(const QString& nameRepo);

    /**
     @brief SetWorkingDirectory - смена рабочего каталога
     @return 0 - нет ошибок
    */
    GANN_DEFINE::RESULT_EXEC_PROCESS SetWorkingDirectory(const QString& localURL);

    /**
    @brief Clone Repositories - клонирование репозитория
    @param folderClone - папка, куда будет скопирован репозиторий
    @return 0 - нет ошибок
    */
    GANN_DEFINE::RESULT_EXEC_PROCESS CloneRepositories(const QString& remoteURL, QString &folderClone);

    // 2. Добавление каталога/файла в репозиторий
    GANN_DEFINE::RESULT_EXEC_PROCESS AddFile(const QString& path) const;
    // 3. закачать контент у файлов((директории)
    GANN_DEFINE::RESULT_EXEC_PROCESS GetContentFile(const QString& path) const;
    // 4. удалить контент у файлов((директории)
    GANN_DEFINE::RESULT_EXEC_PROCESS DropContentFile(const QString& path) const;
    // 5. Удалить файл(директорию) из репозитория вместе с контентом
    GANN_DEFINE::RESULT_EXEC_PROCESS RemoveFile(const QString& path) const;
    // 6. Синхронизация с главным репозиторием
    GANN_DEFINE::RESULT_EXEC_PROCESS Sync() const;
    // 7. оказывает местонахождение файла в других репозиториях
    GANN_DEFINE::RESULT_EXEC_PROCESS WhereisFiles(const QString& path) const;

    /**
    @brief Pull Repositories - послать изменения в удаленный репозитрий
    @return 0 - нет ошибок
    */
    GANN_DEFINE::RESULT_EXEC_PROCESS PullRepositories() const;

private:
    const TShell*  shell;
    const QString  baseCommand;
    // массив векторов, которые будут выполнять парсинг текста со стандартного потока вывода, во время выполнения команды
    std::vector<IParsingCommandOut*> receiverParsing;

};

#endif // SHELLCOMMAND_H
