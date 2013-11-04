#ifndef RESOURCEGENERATOR_H
#define RESOURCEGENERATOR_H

/*
 * Генератор ресурсов для различных тем(поддержка пока тока Linux)
*/
// Qt Stuff
#include <QList>
#include <QMimeType>
#include <QMap>
#include <QSize>

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

    /** @brief Генерация ресурсов */
    void                GenerateResource();

    /** @brief Генерация ресурсов для иконок
        @param pathCurTheme - путь, где располагаются ресурсы по текущей теме
        @param pathGeneralTheme - путь, где располагаются общие ресурсы
        @param size - требуемый размер картинки, по умолчанию 48*48
    */
    void                GenerateResourceIconsDirectoryView(const boost::filesystem::path& pathCurTheme
                                                            , const QSize size = QSize(48, 48)
                                                            );

    // список всех зарегистрированных mimetype-ов
    const QList<QMimeType> listAllMimeType;
    // список полных путей для всех mimeType-ов иконок DirectoryView(размер фиксированный, 48*48)
    QMap<QString, QString> pathToIconsDirectoryView;

    /** @brief текущая имя темы в системе */
    QString             currentThemeName;

    /** @brief поиск файла в директории(и в его поддиректориях)
        @param dirPath - в этом каталоге
        @param fileName - искать такое имя
        @param pathFound - разместить путь здесь, если найдено
        @return false - не найдено, true - найдено
    */
    bool                FindFile(const boost::filesystem::path& dirPath, const std::string &fileName, boost::filesystem::path& pathFound);

    /** @brief поиск файла в директории(и в его поддиректориях)
        @param dirPath - в этом каталоге
        @param fileName - искать такое имя
        @param pathFound - вектор номеров, где нашли такие пути
        @return false - не найдено, true - найдено
    */
    bool                FindFile(const boost::filesystem::path& dirPath, const std::string &fileName, std::vector<boost::filesystem::path>& pathFound);
};

#endif // RESOURCEGENERATOR_H
