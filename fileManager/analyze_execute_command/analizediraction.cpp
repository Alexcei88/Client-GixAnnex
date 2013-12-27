#include "analizediraction.h"

using namespace AnalyzeCommand;

QDir AnalizeDirOnAction::dirService;
QFileInfo AnalizeDirOnAction::fileInfo;

//----------------------------------------------------------------------------------------/
AnalizeDirOnAction::AnalizeDirOnAction(const QString &dir):
    dir(new QDir(dir))
{
    dirService.setFilter(QDir::Dirs | QDir::Files | QDir::NoDotAndDotDot);
    assert(this->dir->exists());
}
//----------------------------------------------------------------------------------------/
void AnalizeDirOnAction::WasActionForFile(const QString& file)
{

}
//----------------------------------------------------------------------------------------/
bool AnalizeDirOnAction::IsWasActionForFile(const QString& file) const
{
    return false;
}
//----------------------------------------------------------------------------------------/
bool AnalizeDirOnAction::WasActionForAllFileDirOnDir(QStringList& files, const QString& dir)
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

    // если размеры векторов не совпадают, то сразу же возвращаем false
    for(QString &str : listFile)
    {
        if(!files.contains(str))
            return false;
    }

    // Да, можно заменить список файлов на просто одну директорию
    for(QString &str : listFile)
    {
        files.removeOne(str);
    }
    files << dir;
    return true;
}
//----------------------------------------------------------------------------------------/
QStringList AnalizeDirOnAction::ListAllDirOfFile(const QStringList& files)
{
    QStringList listRet;
    QString addDir;
    // у каждого файла определяем корневой каталог
    for(const QString &str : files)
    {
        fileInfo.setFile(str);
#ifdef DEBUG
        assert(fileInfo.exists());
#endif
        if(fileInfo.isFile() || fileInfo.isSymLink())
        {
            addDir = fileInfo.absoluteDir();
            listRet << addDir;
        }
        else
        {
            // это директория
            addDir = fileInfo.absoluteDir();
            listRet << addDir;
        }
    }
    return listRet;
}
//----------------------------------------------------------------------------------------/
