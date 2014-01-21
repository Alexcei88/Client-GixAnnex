#include "analizediraction.h"
#include "utils/utils.h"

using namespace AnalyzeCommand;

//----------------------------------------------------------------------------------------/
AnalizeDirOnActionPrivate::AnalizeDirOnActionPrivate()
{
    dirService.setFilter(QDir::Dirs | QDir::Files | QDir::NoDotAndDotDot | QDir::System);
}
//----------------------------------------------------------------------------------------/
AnalizeDirOnActionPrivate::AnalizeDirOnActionPrivate(const QString &dir)
{
    dirService.setFilter(QDir::Dirs | QDir::Files | QDir::NoDotAndDotDot | QDir::System);
    filesMustToBeAction[dir] = "";
}
//----------------------------------------------------------------------------------------/
bool AnalizeDirOnActionPrivate::IsFindFileOnDirAction(const QString& file) const
{
    for(QMap<QString, QString>::const_iterator str = filesMustToBeAction.begin(); str != filesMustToBeAction.end(); ++str)
    {
        fileInfo.setFile(file);

#ifdef DEBUG
        if(!fileInfo.isSymLink())
            assert(fileInfo.exists());
#endif
        if(fileInfo.isFile() || fileInfo.isSymLink())
        {
            fileInfo.setFile(str.key());
#ifdef DEBUG
            if(!fileInfo.isSymLink())
                assert(fileInfo.exists());
#endif
            // ищем файл в файле или в директории
            if(fileInfo.isFile() || fileInfo.isSymLink())
            {
               // ищем файл в файле(то есть должны названия совпдать
               if(file == str.key())
                   return true;
            }
            else
            {
                const QString dir_ = str.key() + "/";
                // ищем файл в директории
                if(file.startsWith(dir_))
                    return true;
            }
        }
        else
        {
            fileInfo.setFile(str.key());
#ifdef DEBUG
            if(!fileInfo.isSymLink())
                assert(fileInfo.exists());
#endif
            // ищем директорию в файле или в директории
            if(fileInfo.isFile() || fileInfo.isSymLink())
            {
                // ищем файл в директории
                const QString dir_ = file + "/";
                // ищем файл в директории
                if(file.startsWith(dir_))
                    return true;
            }
            else
            {
                const QString file_ = file + "/";
                const QString dir_ = str.key() + "/";
                // ищем директорию в директории
                if(file_.startsWith(dir_))
                    return true;
            }
        }
    }
    return false;
}
//----------------------------------------------------------------------------------------/
bool AnalizeDirOnActionPrivate::IsWasActionForFile(const QString& file) const
{
    for(QMap<QString, QString>::const_iterator str = filesWasAction.begin(); str != filesWasAction.end(); ++str)
    {
        fileInfo.setFile(file);
#ifdef DEBUG
            if(!fileInfo.isSymLink())
                assert(fileInfo.exists());
#endif

        if(fileInfo.isFile() || fileInfo.isSymLink())
        {
            fileInfo.setFile(str.key());
#ifdef DEBUG
            if(!fileInfo.isSymLink())
                assert(fileInfo.exists());
#endif
            // ищем файл в файле или в директории
            if(fileInfo.isFile() || fileInfo.isSymLink())
            {
               // ищем файл в файле(то есть должны названия совпдать
               if(file == str.key())
                   return true;
            }
            else
            {
                const QString dir_ = str.key() + "/";
                // ищем файл в директории
                if(file.startsWith(dir_))
                    return true;
            }
        }
        else
        {
            fileInfo.setFile(str.key());
#ifdef DEBUG
            if(!fileInfo.isSymLink())
                assert(fileInfo.exists());
#endif
            // ищем директорию в файле или в директории
            if(fileInfo.isFile() || fileInfo.isSymLink())
            {
                // ищем файл в директории
                const QString dir_ = file + "/";
                // ищем файл в директории
                if(file.startsWith(dir_))
                    return true;
            }
            else
            {
                const QString file_ = file + "/";
                const QString dir_ = str.key() + "/";

                // ищем директорию в директории
                if(file_.startsWith(dir_))
                    return true;
            }
        }
    }
    return false;
}
//----------------------------------------------------------------------------------------/
bool AnalizeDirOnActionPrivate::WasActionForAllFileDirOnDir(QMap<QString, QString> &filesWasAction,
                                                            QMap<QString, QString> &filesNotWasAction,
                                                            const QString &dir) const
{
    dirService.setPath(dir);
    if(!dirService.exists())
    {
#ifdef DEBUG
        assert(0);
#endif
        return false;
    }
    QStringList listFile = dirService.entryList();
    if(listFile.isEmpty())
        return false;

    bool replace = true;
    for(QString &str : listFile)
    {
        if(!filesWasAction.contains(Utils::CatDirFile(dir, str)))
        {
            filesNotWasAction[Utils::CatDirFile(dir, str)] = "";
            replace = false;
        }
    }

    if(replace)
    {
        // Да, можно заменить список файлов на просто одну директорию
        for(QString &str : listFile)
        {
            if(!filesWasAction.remove(Utils::CatDirFile(dir, str)))
            {
                std::printf("%s: Remove from list files return false", __FUNCTION__);
                assert(0);
            }
        }
        if(!filesWasAction.contains(dir))
            filesWasAction[dir] = "";
    }
    return replace;
}
//----------------------------------------------------------------------------------------/
void AnalizeDirOnActionPrivate::UnionAllFileDirOnDir(QMap<QString, QString> &files, const QString &dir) const
{
    // Да, можно заменить список файлов на просто одну директорию
    dirService.setPath(dir);
    if(!dirService.exists())
    {
#ifdef DEBUG
        assert(0);
#endif
        return;
    }

    QStringList listFile = dirService.entryList();
    for(QString &str : listFile)
    {
        if(!files.remove(Utils::CatDirFile(dir, str)))
        {
//            std::printf("%s: Remove from list files return false", __FUNCTION__);
//            assert(0);
        }
    }
    if(!files.contains(dir))
        files[dir] = "";
}
//----------------------------------------------------------------------------------------/
QStringList AnalizeDirOnActionPrivate::ListAllDirOfFile(const QMap<QString, QString> &files) const
{
    QStringList listRet;
    QString addDir;
    // у каждого файла определяем корневой каталог
    for(QMap<QString, QString>::const_iterator str = files.begin(); str != files.end(); ++str)
    {
        fileInfo.setFile(str.key());
#ifdef DEBUG
        if(!fileInfo.isSymLink())
            assert(fileInfo.exists());
#endif
        addDir = fileInfo.absoluteDir().path();
        if(!listRet.contains(addDir))
            listRet << addDir;
    }
    return listRet;
}
//----------------------------------------------------------------------------------------/
bool AnalizeDirOnActionPrivate::EndActionForDir(const QString& dir, const QString& lastFileAction) const
{
    if(lastFileAction.isEmpty())
        return true;

    fileInfo.setFile(lastFileAction);
//    const QString lastPath = fileInfo.absoluteDir().path();
    QString dir_ = dir + "/";
    if(lastFileAction.startsWith(dir_))
    {
        return false;
//        for(QString& curDir : allDirs)
//        {
//            // если проверяемая директория dir является поддиректорией одной из директорий

//        }
    }
    else
    {
        // да, работу в проверяемой директории уже закончили
        return true;
    }
}
//----------------------------------------------------------------------------------------/
void AnalizeDirOnActionPrivate::ClearListAction(QMap<QString, QString>& filesWasAction, QMap<QString, QString>& filesMustToBeAction, const QString fileEndAction)
{
    if(!fileEndAction.isEmpty())
    {
        // удаляем данную директорию из списков, если есть
        if(filesWasAction.contains(fileEndAction))
            filesWasAction.remove(fileEndAction);
        if(filesMustToBeAction.contains(fileEndAction))
            filesMustToBeAction.remove(fileEndAction);
    }
    // начинаем просматривать списки на содержание идентичных файлов
    for(QMap<QString, QString>::const_iterator fileWasAction = filesWasAction.begin(); fileWasAction != filesWasAction.end(); fileWasAction++)
    {
        if(filesMustToBeAction.contains(fileWasAction.key()))
        {
            // удаляем из обоих списков данные файлы
            filesMustToBeAction.remove(fileWasAction.key());
            filesWasAction.remove(fileWasAction.key());
        }
    }
}
//----------------------------------------------------------------------------------------/
