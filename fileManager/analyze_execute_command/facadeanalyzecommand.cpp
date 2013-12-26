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
void FacadeAnalyzeCommand::AddGetContentFileQueue(const QString& file)
{
    gettingContentFilQueue.push_back(file);
}
//----------------------------------------------------------------------------------------/
void FacadeAnalyzeCommand::StartGetContentFile(const QString& file)
{
    gettingContentFile = file;
}
//----------------------------------------------------------------------------------------/
void FacadeAnalyzeCommand::EndGetContentFile(const QString& file)
{
    Q_UNUSED(file)
    assert(!gettingContentFile.isEmpty());
    gettingContentFile = "";
}
//----------------------------------------------------------------------------------------/
void FacadeAnalyzeCommand::ErrorGetContentFile(const QString& file, const QString& error)
{
    assert(!gettingContentFile.isEmpty());
    gettingContentFile = "";

    // помещаем файл в вектор ошибок
    if(errorGettingContentFile.contains(file))
        errorGettingContentFile.remove(file);

    errorGettingContentFile[file] = error;
}
//----------------------------------------------------------------------------------------/
bool FacadeAnalyzeCommand::IsGettingContentFileDir(const QString& file) const
{
    if(DirContainsFile(CatDirFile(currentPathRepository.path(), file), gettingContentFile))
    {
        return true;
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
    droppingContentFile = file;
}
//----------------------------------------------------------------------------------------/
void FacadeAnalyzeCommand::AddDropContentFileQueue(const QString& file)
{
    droppingContentFileQueue.push_back(file);
}
//----------------------------------------------------------------------------------------/
void FacadeAnalyzeCommand::EndDropContentFile(const QString& file)
{
    Q_UNUSED(file);
    assert(!droppingContentFile.isEmpty());
    droppingContentFile = "";
}
//----------------------------------------------------------------------------------------/
void FacadeAnalyzeCommand::ErrorDropContentFile(const QString& file, const QString& error)
{
    assert(!droppingContentFile.isEmpty());
    droppingContentFile = "";

    // помещаем файл в вектор ошибок
    if(errorDroppingContentFile.contains(file))
        errorDroppingContentFile.remove(file);

    errorDroppingContentFile[file] = error;
}
//----------------------------------------------------------------------------------------/
bool FacadeAnalyzeCommand::IsDroppingContentFileDir(const QString& file) const
{
    if(DirContainsFile(CatDirFile(currentPathRepository.path(), file), droppingContentFile))
    {
        return true;
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

