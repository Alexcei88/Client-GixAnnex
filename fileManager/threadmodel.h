#ifndef THREADMODEL_H
#define THREADMODEL_H

// Qt stuff
#include <QMutex>
#include <QMutexLocker>

// std stuff
#include <atomic>

struct ThreadModel
{
    // мьютекс для потока синхронизации иконок
    QMutex mutexSyncIcons;

    // атомарный флаг для потоков, выполняющий команды во threadPool
    std::atomic_flag atomicFlagExecuteCommand;
    class AtomicLock
    {
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


};




#endif // THREADMODEL_H
