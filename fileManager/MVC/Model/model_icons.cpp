#include "model_icons.h"
#include "facadeapplication.h"
#include "threadsyncicons.h"
#include "../Controller/controller_icons.h"

// Qt stuff
#include <QThread>

// boost stuff
#include <boost/make_shared.hpp>

using namespace GANN_MVC;

QThread* ModelQmlAndCIcons::thread = nullptr;
ThreadSyncIcons* ModelQmlAndCIcons::threadSyncIcons = nullptr;
//----------------------------------------------------------------------------------------/
ModelQmlAndCIcons::ModelQmlAndCIcons(ControllerIcons* contrIcons):
    contrIcons(contrIcons)
{}
//----------------------------------------------------------------------------------------/
ModelQmlAndCIcons::~ModelQmlAndCIcons()
{}
//----------------------------------------------------------------------------------------/
void ModelQmlAndCIcons::StartThreadIconsSync()
{
    if(thread && thread->isRunning())
        return;

//    // запускаем поток обновления иконок синхронизации
    thread = new QThread();
    threadSyncIcons = new ThreadSyncIcons(contrIcons);
    threadSyncIcons->moveToThread(thread);
    QObject::connect(thread, &QThread::started, [=] {threadSyncIcons->UpdateFileSyncIcons(); });
    thread->start();
}
//----------------------------------------------------------------------------------------/
void ModelQmlAndCIcons::StopThreadIconsSync()
{
    if(thread)
    {
        if(thread->isRunning())
        {
            delete threadSyncIcons;
            threadSyncIcons = nullptr;

            thread->quit();
            thread->wait();
        }
        delete thread;
        thread = nullptr;
    }
}
//----------------------------------------------------------------------------------------/

