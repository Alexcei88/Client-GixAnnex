#include "preferencesapplication.h"

// Qt stuff
#include <QDir>
#include <QFile>
#include <QDomDocument>
#include <QTextStream>

std::unique_ptr<PreferencesApplication> PreferencesApplication::instance;
//----------------------------------------------------------------------------------------/
PreferencesApplication::PreferencesApplication()
{}
//----------------------------------------------------------------------------------------/
PreferencesApplication* PreferencesApplication::GetInstance()
{
    if(!instance.get())
    {
        instance.reset(new PreferencesApplication());
    }
    return instance.get();
}
//----------------------------------------------------------------------------------------/
bool PreferencesApplication::GetDirectMode() const
{
    return true;
}
//----------------------------------------------------------------------------------------/
const QString PreferencesApplication::GetPathToFileConfigApp() const
{
    // в linux путь следующий: homeDirecoty/ganxrc.xml
    const QString fileName = "ganxrc.xml";
    const QString fullPath = QDir::homePath() + "/" + fileName;
    // есть ли уже файл
    if(!QFile::exists(fullPath))
        // создаем пустой конфигурационный файл
        GenerateEmptyFileConfigApp(fullPath);

    return fullPath;
}
//----------------------------------------------------------------------------------------/
void PreferencesApplication::GenerateEmptyFileConfigApp(const QString file) const
{
    QFile fileRepoConfig(file);
    if (fileRepoConfig.open(QIODevice::WriteOnly | QIODevice::Append))
    {
        printf("Will generate empty config app file");

        QDomDocument doc;
        doc.setContent(QString("<?xml version=\'1.0\' encoding=\'UTF-8\'?>\n<app-options>\n</app-options>"));
        fileRepoConfig.reset();
        QTextStream(&fileRepoConfig) << doc.toString();
        fileRepoConfig.close();
    }
}
//----------------------------------------------------------------------------------------/



