#ifndef TFILESYSTEM_H
#define TFILESYSTEM_H

#include <QDir>

class TFileSystem
{
public:
    TFileSystem();
    TFileSystem(const QString& path);

    // переход в директорию
    bool        Cd(const QString& path) const;
    void        SetPath(const QString& path) const;
    // переход на одину ровень выше
    bool        CdUp() const;

private:
    const QDir directory;
};

#endif // TFILESYSTEM_H
