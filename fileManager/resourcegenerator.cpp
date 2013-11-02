#include "resourcegenerator.h"

// Qt stuff
#include <QFile>
#include <QMimeDatabase>
#include <QIcon>

using namespace boost::filesystem;

boost::shared_ptr<ResourceGenerator> ResourceGenerator::instance = boost::shared_ptr<ResourceGenerator>();
//----------------------------------------------------------------------------------------/
ResourceGenerator::ResourceGenerator() :
    listAllMimeType(QMimeDatabase().allMimeTypes())
{
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
            std::cout<<"Произошло исключение библиотеки boost::filesystem, загружаем стандартную картинку для данного mimetype"<<std::endl;
        }
    }


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
        if (is_directory( *itr ) )
        {
            if(FindFile(*itr, fileName, pathFound)) return true;
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
