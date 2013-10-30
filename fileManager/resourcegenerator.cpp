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
void ResourceGenerator::GenerateResource()
{
    QStringList possiblePathToSearch = QIcon::themeSearchPaths();
    pathToIconsDirectoryView.clear();
    for(auto type = listAllMimeType.begin(); type != listAllMimeType.end(); ++type)
    {
        try
        {
            if(QIcon::hasThemeIcon(type->iconName()))
            {
                // пробуем найти файл с текущим названием
                for(auto path = possiblePathToSearch.begin(); path != possiblePathToSearch.end(); ++path)
                {
                    boost::filesystem::path rootSearchDir("path");
                    boost::filesystem::path foundDir;
                    if(FindFile(rootSearchDir, type->iconName().toStdString(), foundDir))
                    {
                        //мы нашли полный путь до иконки

                    }
                }
            }
        }
        catch(filesystem_error)
        {
            std::cout<<"Произошло исключение библиотеки boost::filesystem, загружаем стандартную картинку для данного mimetype"<<std::endl;
        }
    }
}
//----------------------------------------------------------------------------------------/
bool ResourceGenerator::FindFile(const boost::filesystem::path& dirPath,const std::string& fileName, boost::filesystem::path& pathFound)
{
    if(!exists(dirPath)) return false;
    directory_iterator endItr;

    for (directory_iterator itr(dirPath ); itr != endItr; ++itr)
    {
        if (is_directory( *itr ) )
        {
            if(FindFile(*itr, fileName, pathFound)) return true;
        }
//        else if(itr-> == fileName )
//        {
//            pathFound= *itr;
//            return true;
//        }
    }
    return false;
}

//----------------------------------------------------------------------------------------/
