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
    const QString       GetResourcePathDirectoryView(const QMimeType& type);
    const QString       GetResourcePathPropertyFile(const QMimeType& type);


private:
    static boost::shared_ptr<ResourceGenerator> instance;
    ResourceGenerator();

    /** @brief Генерация ресурсов */
    void                GenerateResource();

    /** @brief Генерация ресурсов иконок
        @param pathCurTheme - путь, где располагаются ресурсы по текущей теме
    */
    void                GenerateResourceIconsDirectoryView(const boost::filesystem::path& pathCurTheme);

    /** @brief Генерация ресурсов иконок в указанных путях для всех типов mimetype-ов *
     *  @param paths - пути, где ищем инконки
     *  @param pathToIconsDirectoryView - мэп, куда сохраняем результаты
     */
    void                GenerateResourceIconsForAllMimeTypes(const QVector<boost::filesystem::path> &paths, QMap<QString, QString>& pathToIconsDirectoryView);

    /** @brief размер иконок для отображения в проводнике(по умолчанию 48*48) */
    const QSize         sizeIcons;
    /** @brief размер иконок для отображения в свойствах файла(по умолчанию 128*128) */
    const QSize         sizeIconsPropertyFile;


    /** @brief список поддиректорий, где ищем иконки */
    QStringList         subPathSearchIcons;

    /** @brief список всех зарегистрированных mimetype-ов */
    const QList<QMimeType> listAllMimeType;
    /** @brief список полных путей для всех mimeType-ов иконок DirectoryView + папки(размер фиксированный, 48*48) */
    QMap<QString, QString> pathToIconsDirectoryView;
    /** @brief список полных путей для всех mimeType-ов иконок для PropertyFile + папки(размер фиксированный, 128*128) */
    QMap<QString, QString> pathToIconsPropertyFile;

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
    void                GenerateListPathInCurTheme(const boost::filesystem::path& pathCurrentTheme, QVector<boost::filesystem::path>& pathSearch, const QSize& sizeIcons) const;
};

#endif // RESOURCEGENERATOR_H
