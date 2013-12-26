#include "facadeanalyzecommand.h"
#include "../define.h"
#include "utils/utils.h"

// std stuff
#include <iostream>
#include <assert.h>

using namespace AnalyzeCommand;
using namespace Utils;

//----------------------------------------------------------------------------------------/
FacadeAnalyzeCommand::FacadeAnalyzeCommand()
{}
//----------------------------------------------------------------------------------------/
void FacadeAnalyzeCommand::SetCurrentPathRepository(const QString& currentPath)
{
    currentPathRepository.setPath(currentPath);
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
    for(auto iterator = gettingContentFile.constBegin(); iterator != gettingContentFile.constEnd(); ++iterator)
    {
        if(DirContainsFile(CatDirFile(currentPathRepository.path(), file), *iterator))
        {
            return true;
        }
    }
    return false;
}
//----------------------------------------------------------------------------------------/
bool FacadeAnalyzeCommand::IsErrorGettingContentFileDir(const QString& file) const
{
    for(auto iterator = errorGettingContentFile.constBegin(); iterator != errorGettingContentFile.constEnd(); ++iterator)
    {
        if(DirContainsFile(CatDirFile(currentPathRepository.path(), file), iterator.key()))
        {
            return true;
        }
    }
    return false;
}
//----------------------------------------------------------------------------------------/
void FacadeAnalyzeCommand::StartDropContentFile(const QString& file)
{
    if(std::find(droppingContentFile.begin(), droppingContentFile.end(), file) == droppingContentFile.end()){
        droppingContentFile.push_back(file);
    }
}
//----------------------------------------------------------------------------------------/
void FacadeAnalyzeCommand::EndDropContentFile(const QString& file)
{
    auto itErase = std::find(droppingContentFile.begin(), droppingContentFile.end(), file);
    if(itErase != droppingContentFile.end())
    {
        droppingContentFile.erase(itErase);
        // убираем файл из вектора ошибок
        if(errorDroppingContentFile.contains(file))
            errorDroppingContentFile.remove(file);
    }
    else
    {
        std::cout<<"WARNING!!!! В списке удаляемых в текущий момент файлов нет файла, удаление контента которого закончилось!!!"<<std::endl;
#ifdef DEBUG
        assert(0);
#endif
    }
}
//----------------------------------------------------------------------------------------/
void FacadeAnalyzeCommand::ErrorDropContentFile(const QString& file, const QString& error)
{
    auto itErase = std::find(droppingContentFile.begin(), droppingContentFile.end(), file);
    if(itErase != droppingContentFile.end()) {
        droppingContentFile.erase(itErase);
    }
    else
    {
        std::cout<<"WARNING!!!! В списке удаляемых в текущий момент файлов нет файла, удаление контента которого закончилось!!!"<<std::endl;
#ifdef DEBUG
        assert(0);
#endif
    }
    // помещаем файл в вектор ошибок
    if(errorDroppingContentFile.contains(file))
        errorDroppingContentFile.remove(file);

    errorDroppingContentFile[file] = error;
}
//----------------------------------------------------------------------------------------/
bool FacadeAnalyzeCommand::IsDroppingContentFileDir(const QString& file) const
{
    for(auto iterator = droppingContentFile.constBegin(); iterator != droppingContentFile.constEnd(); ++iterator)
    {
        if(DirContainsFile(CatDirFile(currentPathRepository.path(), file), *iterator))
        {
            return true;
        }
    }
    return false;
}
//----------------------------------------------------------------------------------------/
bool FacadeAnalyzeCommand::IsErrorDroppingContentFileDir(const QString& file) const
{
    for(auto iterator = errorDroppingContentFile.constBegin(); iterator != errorDroppingContentFile.constEnd(); ++iterator)
    {
        if(DirContainsFile(CatDirFile(currentPathRepository.path(), file), iterator.key()))
        {
            return true;
        }
    }
    return false;
}
//----------------------------------------------------------------------------------------/
bool FacadeAnalyzeCommand::DirContainsFile(const QString& dir, const QString& file) const
{
    return file.startsWith(dir);
}
//----------------------------------------------------------------------------------------/

