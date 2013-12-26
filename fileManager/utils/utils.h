#pragma once


namespace Utils
{

// конкатенация строк директории и файла(между ними слеш нужно ставить)
template<class T>
T catDirFile(const T& dir, const T& file)
{
    return dir + "/" + file;
}
}

