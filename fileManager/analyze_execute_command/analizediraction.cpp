#include "analizediraction.h"
#include "utils/utils.h"

using namespace AnalyzeCommand;

QDir AnalizeDirOnActionPrivate::dirService;
QFileInfo AnalizeDirOnActionPrivate::fileInfo;

//----------------------------------------------------------------------------------------/
AnalizeDirOnActionPrivate::AnalizeDirOnActionPrivate()
{
    dirService.setFilter(QDir::Dirs | QDir::Files | QDir::NoDotAndDotDot | QDir::System);
}
//----------------------------------------------------------------------------------------/
AnalizeDirOnActionPrivate::AnalizeDirOnActionPrivate(const QString &dir)
{
    dirService.setFilter(QDir::Dirs | QDir::Files | QDir::NoDotAndDotDot | QDir::System);
    filesMustToBeAction << dir;
}
//----------------------------------------------------------------------------------------/
bool AnalizeDirOnActionPrivate::IsFindFileOnDirAction(const QString& file) const
{
    for(const QString& str : filesMustToBeAction)
    {
        fileInfo.setFile(file);

#ifdef DEBUG
        if(!fileInfo.isSymLink())
            assert(fileInfo.exists());
#endif
        if(fileInfo.isFile() || fileInfo.isSymLink())
        {
            fileInfo.setFile(str);
#ifdef DEBUG
            if(!fileInfo.isSymLink())
                assert(fileInfo.exists());
#endif
            // ищем файл в файле или в директории
            if(fileInfo.isFile() || fileInfo.isSymLink())
            {
               // ищем файл в файле(то есть должны названия совпдать
               if(file == str)
                   return true;
            }
            else
            {
                const QString dir_ = str + "/";
                // ищем файл в директории
                if(file.startsWith(dir_))
                    return true;
            }
        }
        else
        {
            fileInfo.setFile(str);
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
                const QString dir_ = str + "/";
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
    for(const QString& str : filesWasAction)
    {
        fileInfo.setFile(file);
#ifdef DEBUG
            if(!fileInfo.isSymLink())
                assert(fileInfo.exists());
#endif

        if(fileInfo.isFile() || fileInfo.isSymLink())
        {
            fileInfo.setFile(str);
#ifdef DEBUG
            if(!fileInfo.isSymLink())
                assert(fileInfo.exists());
#endif
            // ищем файл в файле или в директории
            if(fileInfo.isFile() || fileInfo.isSymLink())
            {
               // ищем файл в файле(то есть должны названия совпдать
               if(file == str)
                   return true;
            }
            else
            {
                const QString dir_ = str + "/";
                // ищем файл в директории
                if(file.startsWith(dir_))
                    return true;
            }
        }
        else
        {
            fileInfo.setFile(str);
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
                const QString dir_ = str + "/";

                // ищем директорию в директории
                if(file_.startsWith(dir_))
                    return true;
            }
        }
    }
    return false;
}
//----------------------------------------------------------------------------------------/
bool AnalizeDirOnActionPrivate::WasActionForAllFileDirOnDir(QStringList& files, const QString& dir)
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

    for(QString &str : listFile)
    {
        if(!files.contains(Utils::CatDirFile(dir, str)))
            return false;
    }

    // Да, можно заменить список файлов на просто одну директорию
    for(QString &str : listFile)
    {
        if(!files.removeOne(Utils::CatDirFile(dir, str)))
        {
            std::printf("%s: Remove from list files return false", __FUNCTION__);
            assert(0);
        }
    }
    if(!files.contains(dir))
        files << dir;
    return true;
}
//----------------------------------------------------------------------------------------/
QStringList AnalizeDirOnActionPrivate::ListAllDirOfFile(const QStringList& files)
{
    QStringList listRet;
    QString addDir;
    // у каждого файла определяем корневой каталог
    for(const QString &str : files)
    {
        fileInfo.setFile(str);
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
void AnalizeDirOnActionPrivate::ClearListAction(QStringList& filesWasAction, QStringList& filesMustToBeAction, const QString fileEndAction)
{
    if(!fileEndAction.isEmpty())
    {
        // удаляем данную директорию из списков, если есть
        if(filesWasAction.contains(fileEndAction))
            filesWasAction.removeOne(fileEndAction);
        if(filesMustToBeAction.contains(fileEndAction))
            filesMustToBeAction.removeOne(fileEndAction);
    }
    // начинаем просматривать списки
    for(QString& fileWasAction : filesWasAction)
    {
        if(filesMustToBeAction.contains(fileWasAction))
        {
            // удаляем из обоих списков данные файлы
            filesMustToBeAction.removeOne(fileWasAction);
            filesWasAction.removeOne(fileWasAction);
        }
    }
}
//----------------------------------------------------------------------------------------/
