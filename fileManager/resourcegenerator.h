#ifndef RESOURCEGENERATOR_H
#define RESOURCEGENERATOR_H

/*
 * Генератор ресурсов для различных тем(поддержка пока тока Linux)
*/
// Qt Stuff
#include <QList>
#include <QMimeType>
#include <QMap>

// boost stuff
#include <boost/shared_ptr.hpp>
#include <boost/filesystem.hpp>

class ResourceGenerator
{
public:
    static ResourceGenerator* getInstance();
    ~ResourceGenerator();
    const QString       GetResourcePath(const QMimeType& type);

private:
    static boost::shared_ptr<ResourceGenerator> instance;
    ResourceGenerator();

    void                GenerateResource();
    // список всех зарегистрированных mimetype-ов
    const QList<QMimeType> listAllMimeType;
    // список полных путей для всех mimeType-ов иконок DirectoryView(размер фиксированный, 48*48)
    QMap<QString, QString> pathToIconsDirectoryView;

    /** @brief поиск файла в директории(и в его поддиректориях)
        @param dirPath - в этом каталоге
        @param fileName - искать такое имя
        @param pathFound - разместить путь здесь, если найдено
        @return false - не найдено, true - найдено
    */
    bool                FindFile(const boost::filesystem::path& dirPath, const std::string &fileName, boost::filesystem::path& pathFound);
};

#endif // RESOURCEGENERATOR_H
