#include "resourcegenerator.h"

// Qt stuff
#include <QFile>
#include <QMimeDatabase>
#include <QIcon>

// iniparser stuff
#include "iniparser/iniparser.h"

using namespace boost::filesystem;

boost::shared_ptr<ResourceGenerator> ResourceGenerator::instance = boost::shared_ptr<ResourceGenerator>();
//----------------------------------------------------------------------------------------/
ResourceGenerator::ResourceGenerator() :
    listAllMimeType(QMimeDatabase().allMimeTypes())
{
    currentThemeName = QIcon::themeName();
    GenerateResource();
}
//----------------------------------------------------------------------------------------/
ResourceGenerator::~ResourceGenerator()
{}
//----------------------------------------------------------------------------------------/
ResourceGenerator* ResourceGenerator::getInstance()
{
    if(instance.get() == 0)
        instance = boost::shared_ptr<ResourceGenerator>(new ResourceGenerator());
    return instance.get();
}
//----------------------------------------------------------------------------------------/
const QString ResourceGenerator::GetResourcePath(const QMimeType& type)
{
    auto it = pathToIconsDirectoryView.find(type.name());
    if( it != pathToIconsDirectoryView.end())
    {
        return it.value();
    }
    else
    {
        std::cout<<"КРИТИЧЕСКАЯ ОШИБКА!!! Нет ресурса с иконкой для отображения данного mimetype. Это критическая ошибка."
                   "Программа будет закрыта."<<std::endl;
#ifndef DEBUG
        exit(1);
#endif
    }
}
//----------------------------------------------------------------------------------------/
void ResourceGenerator::GenerateResource()
{
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
            boost::filesystem::path rootSearchDir((*path).toStdString());
            FindFile(rootSearchDir, fileName, searchedDir);
        }

        dictionary* ini = 0l;
        // да, есть такие файлы, начинаем каждый просматривать, находя файл, который описывает текущую тему и общие
        foreach (path dir, searchedDir)
        {
            ini = iniparser_load(dir.c_str());
            const char* curName = iniparser_getstring(ini, "Icon Theme:Name", '\0');
            iniparser_freedict(ini);
            ini = 0l;
            // если нашли текущую тему, то запоминаем путь с текущей темой
            if(strcmp(curName, currentThemeName.toStdString().c_str()))
            {
                findedThemeDirIcons = true;
                themeDirIcons = dir;
                break;
            }
        }
    }
    assert(findedThemeDirIcons && "Не смогли найти файл с описанием текущей темы. Это критическая ошибка. Программа будет закрыта");
    if(!findedThemeDirIcons){
        std::cout<<"Не смогли найти файл с описанием текущей темы. Это критическая ошибка. Программа будет закрыта"<<std::endl;
        exit(1);
    }
    GenerateResourceIconsDirectoryView(themeDirIcons);
}
//----------------------------------------------------------------------------------------/
void ResourceGenerator::GenerateResourceIconsDirectoryView( const boost::filesystem::path& pathCurTheme
                                                           ,const QSize size
                                                            )
{
#if 1
    // список директорий для просмотра
    QStringList possiblePathToSearch = QIcon::themeSearchPaths();

    pathToIconsDirectoryView.clear();
    boost::filesystem::path foundDir;
    for(auto type = listAllMimeType.begin(); type != listAllMimeType.end(); ++type)
    {
        try
        {
            if(QIcon::hasThemeIcon(type->iconName()))
            {
                // пробуем найти файл с текущим названием
                for(auto path = possiblePathToSearch.begin(); path != possiblePathToSearch.end(); ++path)
                {
                    boost::filesystem::path rootSearchDir((*path).toStdString());
                    if(FindFile(rootSearchDir, (type->iconName() +".png").toStdString(), foundDir))
                    {
                        pathToIconsDirectoryView[type->name()] = QString(foundDir.c_str());
                    }
                }
            }
            else if(QIcon::hasThemeIcon(type->genericIconName()))
            {
                // пробуем найти файл с текущим названием
                for(auto path = possiblePathToSearch.begin(); path != possiblePathToSearch.end(); ++path)
                {
                    boost::filesystem::path rootSearchDir((*path).toStdString());
                    if(FindFile(rootSearchDir, (type->genericIconName() +".png").toStdString(), foundDir))
                    {
                        pathToIconsDirectoryView[type->name()] = QString(foundDir.c_str());
                    }
                }
            }
            else
            {
                // мы не нашли, соответственно загружаем какой-то ресурс по умолчанию
            }
        }
        catch(filesystem_error)
        {
            std::cout<<"Произошло исключение библиотеки boost::filesystem, загружаем стандартную картинку для данного mimetype файла!!!"<<std::endl;
        }
    }
#else
    pathToIconsDirectoryView.clear();
    boost::filesystem::path foundDir;
    for(auto type = listAllMimeType.begin(); type != listAllMimeType.end(); ++type)
    {
        try
        {
            if(QIcon::hasThemeIcon(type->iconName()))
            {
                if(FindFile(pathCurTheme, (type->iconName() +".png").toStdString(), foundDir))
                {
                    pathToIconsDirectoryView[type->name()] = QString(foundDir.c_str());
                }

            }
            else if(QIcon::hasThemeIcon(type->genericIconName()))
            {
                // пробуем найти файл с текущим названием
                if(FindFile(pathCurTheme, (type->genericIconName() +".png").toStdString(), foundDir))
                {
                    pathToIconsDirectoryView[type->name()] = QString(foundDir.c_str());
                }
            }
            else
            {
                // мы не нашли, соответственно загружаем какой-то ресурс по умолчанию
            }
        }
        catch(filesystem_error)
        {
            std::cout<<"Произошло исключение библиотеки boost::filesystem, загружаем стандартную картинку для данного mimetype файла!!!"<<std::endl;
        }
    }
#endif
}
//----------------------------------------------------------------------------------------/
bool ResourceGenerator::FindFile(const boost::filesystem::path& dirPath, const std::string& fileName, boost::filesystem::path& pathFound)
{
    if(!exists(dirPath)) return false;
    directory_iterator endItr;

    // path, указывающий на файл, который ищем
    boost::filesystem::path searchFile(fileName.c_str());

    for (directory_iterator itr(dirPath ); itr != endItr; ++itr)
    {
        if(is_directory(*itr))
        {
            if(FindFile(*itr, fileName, pathFound)) { return true; };
        }
        else
        {
            boost::filesystem::path temp_path(*itr);
            if(temp_path.filename() == searchFile)
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
