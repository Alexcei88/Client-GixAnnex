#include "facadeanalyzecommand.h"
#include "../define.h"
#include "utils/utils.h"

// std stuff
#include <iostream>
#include <assert.h>

using namespace AnalyzeCommand;
using namespace Utils;

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
        if(DirContainsFile(catDirFile(currentPathRepository.path(), file), *iterator))
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

