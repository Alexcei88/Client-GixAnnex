#include "facadeanalyzecommand.h"
#include "../define.h"

// std stuff
#include <iostream>
#include <assert.h>

using namespace AnalyzeCommand;

FacadeAnalyzeCommand::FacadeAnalyzeCommand()
{}
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
        //if(errorGettingContentFile.contains(file))
        //    errorGettingContentFile.remove(file);
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
void FacadeAnalyzeCommand::ErrorGetContentFile(const QString&, const QString&)
{

}
//----------------------------------------------------------------------------------------/

