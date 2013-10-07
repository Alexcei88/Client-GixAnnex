#include "resourcegenerator.h"

boost::shared_ptr<ResourceGenerator> ResourceGenerator::instance = boost::shared_ptr<ResourceGenerator>();
//----------------------------------------------------------------------------------------/
ResourceGenerator::ResourceGenerator()
{
    resourceFileIcon = new QResource("icons.qrc");
    std::cout<<"AbsolutePath"<<resourceFileIcon->absoluteFilePath().toStdString().c_str()<<std::endl;
    GenerateResource();
}
//----------------------------------------------------------------------------------------/
ResourceGenerator::~ResourceGenerator()
{
    delete resourceFileIcon;
}
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
    if(QIcon::hasThemeIcon("application-msword"))
    {
        std::cout<<"Da, we finded"<<std::endl;
    }
    if(resourceFileIcon->registerResource("/home/alexcei/MyProject/Client-GixAnnex/fileManager/folder.png", "/folder"))
    {
        std::cout<<"Resource File Add"<<std::endl;
    }
}
//----------------------------------------------------------------------------------------/
