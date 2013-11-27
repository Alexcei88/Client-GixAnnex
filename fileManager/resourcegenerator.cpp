#include "resourcegenerator.h"

// Qt stuff
#include <QFile>
#include <QMimeDatabase>
#include <QIcon>
#include <QRegExp>

// iniparser stuff
#include "iniparser/iniparser.h"


using namespace boost::filesystem;

ResourceGenerator* ResourceGenerator::instance = 0l;
//----------------------------------------------------------------------------------------/
ResourceGenerator::ResourceGenerator() :
    sizeIcons(48, 48)
  , sizeIconsPropertyFile(128, 128)
  , listAllMimeType(QMimeDatabase().allMimeTypes())
{
    currentThemeName = QIcon::themeName();
    subPathSearchIcons.push_back("mimetypes");
    subPathSearchIcons.push_back("places");
    GenerateResource();
}
//----------------------------------------------------------------------------------------/
ResourceGenerator::~ResourceGenerator()
{}
//----------------------------------------------------------------------------------------/
ResourceGenerator* ResourceGenerator::getInstance()
{
    if(instance == 0l)
        instance = new ResourceGenerator();
    return instance;
}
//----------------------------------------------------------------------------------------/
void ResourceGenerator::RemoveInstance()
{
    delete instance;
    instance = 0l;
}
//----------------------------------------------------------------------------------------/
const QString ResourceGenerator::GetResourcePathDirectoryView(const QMimeType& type)
{
    auto it = pathToIconsDirectoryView.find(type.name());
    if( it != pathToIconsDirectoryView.end())
    {
        return it.value();
    }
    else
    {
        std::cout<<"КРИТИЧЕСКАЯ ОШИБКА!!! Нет ресурса с иконкой для отображения mimetype "
                 <<type.name().toStdString().c_str()<<". Это критическая ошибка."
                 "Программа будет закрыта."<<std::endl;
#ifndef DEBUG
        exit(1);
#endif
    }
}
//----------------------------------------------------------------------------------------/
const QString ResourceGenerator::GetResourcePathPropertyFile(const QMimeType& type)
{
    auto it = pathToIconsPropertyFile.find(type.name());
    if( it != pathToIconsPropertyFile.end())
    {
        return it.value();
    }
    else
    {
        std::cout<<"КРИТИЧЕСКАЯ ОШИБКА!!! Нет ресурса с иконкой для отображения mimetype "
                 <<type.name().toStdString().c_str()<<". Это критическая ошибка."
                 "Программа будет закрыта."<<std::endl;
#ifndef DEBUG
        exit(1);
#endif
    }
}
//----------------------------------------------------------------------------------------/
void ResourceGenerator::GenerateResource()
{
    pathToIconsDirectoryView.clear();
    pathToIconsPropertyFile.clear();

    // список директорий для просмотра
    QStringList possiblePathToSearch = QIcon::themeSearchPaths();

    // находим все файлы index.theme, и запоминаем директорию, в которой нашли
    std::vector<boost::filesystem::path> searchedDir;

    // путь, в котором содержатся иконки темы, которая сейчас выбрана в системе
    path themeDirIcons;
    bool findedThemeDirIcons = false;
    {
        const std::string fileName = "index.theme";
        // пробуем найти файл с текущим названием
        for(auto path = possiblePathToSearch.begin(); path != possiblePathToSearch.end(); ++path)
        {
            boost::filesystem::path rootSearchDir((*path).toStdString().c_str());
            FindFile(rootSearchDir, fileName, searchedDir);
        }

        dictionary* ini = 0l;
        // да, есть такие файлы, начинаем каждый просматривать, находя файл, который описывает текущую тему
        foreach (path dir, searchedDir)
        {
            ini = iniparser_load(dir.c_str());
            const char* curName = iniparser_getstring(ini, "Icon Theme:Name\0", "\0");
            const QString strCurName(curName);
            // если нашли текущую тему, то запоминаем путь с текущей темой
            if(strCurName.compare(currentThemeName, Qt::CaseInsensitive) == 0)
            {
                findedThemeDirIcons = true;
                themeDirIcons = dir;
                iniparser_freedict(ini);
                ini = 0l;
                break;
            }
            iniparser_freedict(ini);
            ini = 0l;
        }
    }
    if(!findedThemeDirIcons)
    {
        std::cout<<"Не смогли найти файл с описанием текущей темы. Это критическая ошибка. Программа будет закрыта"<<std::endl;
        exit(1);
    }
    // генерация иконок нужных размеров
    GenerateResourceIconsDirectoryView(themeDirIcons);
}
//----------------------------------------------------------------------------------------/
void ResourceGenerator::GenerateResourceIconsDirectoryView(const boost::filesystem::path& pathCurTheme)
{  
    // для проводника
    QVector<path> subPathSearchIcons;
    // генерируем пути, в которых буем искать иконки в зависимости от размера
    GenerateListPathInCurTheme(pathCurTheme, subPathSearchIcons, sizeIcons);
    GenerateResourceIconsForAllMimeTypes(subPathSearchIcons, pathToIconsDirectoryView);

    // для отображения свойств файла
    subPathSearchIcons.clear();
    // генерируем пути, в которых буем искать иконки в зависимости от размера
    GenerateListPathInCurTheme(pathCurTheme, subPathSearchIcons, sizeIconsPropertyFile);
    GenerateResourceIconsForAllMimeTypes(subPathSearchIcons, pathToIconsPropertyFile);
}
void ResourceGenerator::GenerateResourceIconsForAllMimeTypes(const QVector<boost::filesystem::path>& paths, QMap<QString, QString>& pathToIconsDirectoryView)
{
    boost::filesystem::path foundDir;
    //признак успешного нахождения файла
    bool successfulFind = false;
    for(auto type = listAllMimeType.begin(); type != listAllMimeType.end(); ++type)
    {
        successfulFind = false;
        for(auto path = paths.begin(); path != paths.end(); ++path)
        {
            try
            {
                if(QIcon::hasThemeIcon(type->iconName()))
                {
                    if(FindFile(*path, type->iconName().toStdString(), foundDir))
                    {
                        pathToIconsDirectoryView[type->name()] = QString(foundDir.c_str());
                        successfulFind = true;
                        break;
                    }

                }
                if(QIcon::hasThemeIcon(type->genericIconName()))
                {
                    // пробуем найти файл с текущим названием
                    if(FindFile(*path, type->genericIconName().toStdString(), foundDir))
                    {
                        pathToIconsDirectoryView[type->name()] = QString(foundDir.c_str());
                        successfulFind = true;
                        break;
                    }
                }

            }
            catch(filesystem_error)
            {
                std::cout<<"Произошло исключение библиотеки boost::filesystem, загружаем стандартную картинку для данного mimetype файла!!!"<<std::endl;
            }
        }
        if(!successfulFind)
        {
            // мы не нашли, соответственно загружаем какой-то ресурс по умолчанию
        }
    }
}
//----------------------------------------------------------------------------------------/
bool ResourceGenerator::FindFile(const boost::filesystem::path& dirPath, const std::string& fileName, boost::filesystem::path& pathFound)
{
    if(!exists(dirPath)) return false;
    directory_iterator endItr;

    static QRegExp regExp;
    const std::string strPattern = fileName + ".*";
    for (directory_iterator itr(dirPath ); itr != endItr; ++itr)
    {
        if(is_directory(*itr))
        {
            if(FindFile(*itr, fileName, pathFound)) { return true; };
        }
        else
        {
            boost::filesystem::path temp_path(*itr);
            const QString str(temp_path.c_str());
            regExp.setPattern(QString(strPattern.c_str()));
            if(regExp.indexIn(str) != -1)
            {
                pathFound = temp_path;
                return true;
            }
        }
    }
    return false;
}
//----------------------------------------------------------------------------------------/
bool ResourceGenerator::FindFile(const boost::filesystem::path& dirPath, const std::string &fileName, std::vector<boost::filesystem::path>& pathFound)
{
    if(!exists(dirPath)) return false;
    directory_iterator endItr;

    // path, указывающий на файл, который ищем
    boost::filesystem::path searchFile(fileName.c_str());

    for (directory_iterator itr(dirPath ); itr != endItr; ++itr)
    {
        if (is_directory( *itr ) )
        {
            FindFile(*itr, fileName, pathFound);
        }
        else
        {
            boost::filesystem::path temp_path(*itr);
            if(temp_path.filename() == searchFile)
            {
                pathFound.push_back(temp_path);
                return true;
            }
        }
    }
    if(pathFound.empty())
        return false;
    else
        return true;
}
//----------------------------------------------------------------------------------------/
void ResourceGenerator::GenerateListPathInCurTheme(const boost::filesystem::path& pathCurrentTheme, QVector<boost::filesystem::path>& pathSearch, const QSize& sizeIcons) const
{
    dictionary* ini = 0l;
    const QString fileName("index.theme");
    // вычеркиваем из полного пути имя файла, оно не нужно будет
    QString path = QString(pathCurrentTheme.c_str()).remove(fileName);

    ini = iniparser_load(pathCurrentTheme.c_str());
    const QString sizeString = QString::number(sizeIcons.width()) + "x" + QString::number(sizeIcons.height());
    for(auto it = subPathSearchIcons.begin(); it != subPathSearchIcons.end(); ++it)
    {
        const QString str = sizeString + "/"+ (*it);
        // ищем интересующие нас директории в ini файле для темы
        if(iniparser_find_entry(ini, str.toStdString().c_str()) )
        {
            const QString fullPath = path + str;
            boost::filesystem::path findedPath(fullPath.toStdString().c_str());
            assert(exists(findedPath));
            pathSearch.push_back(findedPath);
        }
        else
        {
            std::cout<<"WARNING!!! При поиске путей для генерации ресурсов в текущей теме нет иконко подходящего размера!!!"<<std::endl;
        }

    }
    iniparser_freedict(ini);
    ini = 0l;
}
//----------------------------------------------------------------------------------------/
