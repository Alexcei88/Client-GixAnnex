#pragma once


namespace Utils
{

// конкатенация строк директории и файла(между ними слеш нужно ставить)
template<class T>
T CatDirFile(const T& dir, const T& file)
{
    return dir + "/" + file;
}
}

