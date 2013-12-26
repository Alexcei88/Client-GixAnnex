#include "facadeanalyzecommand.h"
#include "../define.h"

// std stuff
#include <iostream>
#include <assert.h>

using namespace AnalyzeCommand;

FacadeAnalyzeCommand::FacadeAnalyzeCommand()
{}
//----------------------------------------------------------------------------------------/
FacadeAnalyzeCommand::FacadeAnalyzeCommand(const QString &rootPathRepository):
    rootPathRepository(rootPathRepository)
{}
//----------------------------------------------------------------------------------------/
void FacadeAnalyzeCommand::SetRootPathRepository(const QString& rootPath)
{
    rootPathRepository = rootPath;
}
//----------------------------------------------------------------------------------------/
void FacadeAnalyzeCommand::SetCurrentPathRepository(const QString& currentPath)
{
    currentPathRepository = currentPath;
}
//----------------------------------------------------------------------------------------/
void FacadeAnalyzeCommand::StartGetContentFile(const QString& file)
{
    if(std::find(gettingContentFile.begin(), gettingContentFile.end(), file) == gettingContentFile.end()){
        gettingContentFile.push_back(file);
    }
}
//----------------------------------------------------------------------------------------/
void FacadeAnalyzeCommand::EndGetContentFile(const QString& file)
{
    auto itErase = std::find(gettingContentFile.begin(), gettingContentFile.end(), file);
    if(itErase != gettingContentFile.end())
    {
        gettingContentFile.erase(itErase);
        // убираем файл из вектора ошибок, если он там есть
        if(errorGettingContentFile.contains(file))
            errorGettingContentFile.remove(file);
    }
    else
    {
        std::cout<<"WARNING!!!! В списке получаемых в текущий момент файлов нет файла, получение контента которого закончилось!!!"<<std::endl;
        #ifdef DEBUG
                assert(0);
        #endif
    }
}
//----------------------------------------------------------------------------------------/
void FacadeAnalyzeCommand::ErrorGetContentFile(const QString& file, const QString& error)
{
    auto itErase = std::find(gettingContentFile.begin(), gettingContentFile.end(), file);
    if(itErase != gettingContentFile.end()) {
        gettingContentFile.erase(itErase);
    }
    else
    {
        std::cout<<"WARNING!!!! В списке получаемых в текущий момент файлов нет файла, получение контента которого закончилось!!!"<<std::endl;
#ifdef DEBUG
        assert(0);
#endif
    }
    // помещаем файл в вектор ошибок
    if(errorGettingContentFile.contains(file))
        errorGettingContentFile.remove(file);

    errorGettingContentFile[file] = error;
}
//----------------------------------------------------------------------------------------/
bool FacadeAnalyzeCommand::IsGettingContentFileDir(const QString& file) const
{
    const QString relativePath = QString(currentPathRepository + "/" + file).replace(rootPathRepository +"/", "");
    for(auto iterator = gettingContentFile.constBegin(); iterator != gettingContentFile.constEnd(); ++iterator)
    {
        std::cout<<"relativePath ="<<relativePath.toStdString()<<std::endl;
        std::cout<<"*iterator ="<<iterator->toStdString()<<std::endl;

        if(DirContainsFile(*iterator, relativePath))
        {
            std::cout<<"Getting file true"<<std::endl;
            return true;
        }
    }
    return false;
}
//----------------------------------------------------------------------------------------/
bool FacadeAnalyzeCommand::DirContainsFile(const QString& dir, const QString& file) const
{
    return dir.contains(file, Qt::CaseSensitive);
}
