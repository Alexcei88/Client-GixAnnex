#pragma once

#include "../define.h"
namespace Utils
{

// конкатенация строк директории и файла(между ними слеш нужно ставить)
template<class T>
T CatDirFile(const T& dir, const T& file)
{
    return dir + "/" + file;
}
// Заснуть потоку на time микросекунд времени
void LZDelay(const uint64t& time);
}

