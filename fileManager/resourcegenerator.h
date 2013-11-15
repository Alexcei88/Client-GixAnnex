#ifndef RESOURCEGENERATOR_H
#define RESOURCEGENERATOR_H

/*
 * Генератор ресурсов для различных тем(поддержка пока тока Linux)
*/
// Qt Stuff
#include <QMimeType>
#include <QMap>
#include <QSize>
#include <QStringList>

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
    void                GenerateResourceIconsDirectoryView(const boost::filesystem::path& pathCurTheme);
    /** @brief размер иконок для отображения(по умолчанию 48*48) */
    const QSize sizeIcons;
    /** @brief список поддиректорий, где ищем иконки */
    QStringList subPathSearchIcons;
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

    /** @brief формирование списка поддиректорий в текущем пути темы в системе в зависимости
     *  от требуемого размера и списка поддиректорий
    */
    void                GenerateListPathInCurTheme(const boost::filesystem::path& pathCurrentTheme, QVector<boost::filesystem::path>& pathSearch) const;
};

#endif // RESOURCEGENERATOR_H
