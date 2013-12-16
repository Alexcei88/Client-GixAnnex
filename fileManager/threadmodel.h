#ifndef THREADMODEL_H
#define THREADMODEL_H

#include <QMutex>
#include <QMutexLocker>

struct ThreadModel
{
    // мьютекс для потока синхронизации иконок
    QMutex mutexSyncIcons;
};

#endif // THREADMODEL_H
