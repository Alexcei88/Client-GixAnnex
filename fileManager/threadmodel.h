#ifndef THREADMODEL_H
#define THREADMODEL_H

// Qt stuff
#include <QMutex>
#include <QMutexLocker>
#include <QSemaphore>

struct ThreadModel
{
    // ПОТОК СИНХРОНИЗАЦИИ ИКОНОК
    // мьютекс для потока синхронизации иконок
    QMutex mutexSyncIcons;
    // семафор для потока синхронизации иконок
    QSemaphore semSyncIcons;
    // количество выполняемых команд, которые требуют обновление синхронизации иконок
    int     countExecutingCommandWithSyncIcons;


};




#endif // THREADMODEL_H
