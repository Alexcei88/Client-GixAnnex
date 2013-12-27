#pragma once

#include "../define.h"
#include <atomic>

namespace Utils
{
//----------------------------------------------------------------------------------------/
class AtomicLock
{
    public:
        AtomicLock(std::atomic_flag* lock): lock(lock)
        {
            while(this->lock->test_and_set(std::memory_order_acquire)) {}
        }

        ~AtomicLock()
        {
            this->lock->clear(std::memory_order_release);
        }
    private:
        std::atomic_flag* lock;
};
//----------------------------------------------------------------------------------------/
// конкатенация строк директории и файла(между ними слеш нужно ставить)
template<class T>
T CatDirFile(const T& dir, const T& file)
{
    return dir + "/" + file;
}
//----------------------------------------------------------------------------------------/
// Заснуть потоку на time микросекунд времени
void LZDelay(const uint64t& time);

}

