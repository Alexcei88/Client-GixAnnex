#include "tfilesystem.h"

//----------------------------------------------------------------------------------------/
TFileSystem::TFileSystem()
{
    directory.setPath(QDir::current());
}
//----------------------------------------------------------------------------------------/
TFileSystem::TFileSystem(const QString& path)
{
    directory.setPath(path);
}
//----------------------------------------------------------------------------------------/
bool TFileSystem::Cd(const QString &path) const
{
    return directory.cd(path);
}
//----------------------------------------------------------------------------------------/
bool TFileSystem::CdUp() const
{
    return directory.cdUp();
}
//----------------------------------------------------------------------------------------/
void TFileSystem::SetPath(const QString &path) const
{
    return directory.setPath(path);
}
//----------------------------------------------------------------------------------------/


