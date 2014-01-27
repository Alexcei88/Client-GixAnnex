#include "model_icons.h"
#include "facadeapplication.h"
#include "threadsyncicons.h"
#include "../Controller/controller_icons.h"

// Qt stuff
#include <QThread>

// boost stuff
#include <boost/make_shared.hpp>

using namespace GANN_MVC;

QThread* ModelQmlAndCIcons::thread = 0l;
//----------------------------------------------------------------------------------------/
ModelQmlAndCIcons::ModelQmlAndCIcons(ControllerIcons* contrIcons):
    contrIcons(contrIcons)
{}
//----------------------------------------------------------------------------------------/
ModelQmlAndCIcons::~ModelQmlAndCIcons()
{
}
//----------------------------------------------------------------------------------------/
void ModelQmlAndCIcons::StartThreadIconsSync()
{
    if(thread != 0 && thread->isRunning())
        return;

//    // запускаем поток обновления иконок синхронизации
    thread = new QThread();
    threadSyncIcons = boost::make_shared<ThreadSyncIcons>(contrIcons);
    threadSyncIcons->moveToThread(thread);
    QObject::connect(thread, &QThread::started, [=] {threadSyncIcons->UpdateFileSyncIcons(); });

    FacadeApplication* facade = FacadeApplication::getInstance();
    QObject::connect(facade, &FacadeApplication::stopThreadIconsSync, [=] { ModelQmlAndCIcons::StopThreadIconsSync(); });
    thread->start();
}
//----------------------------------------------------------------------------------------/
void ModelQmlAndCIcons::StopThreadIconsSync()
{
    if(thread)
    {
        if(thread->isRunning())
        {
            thread->quit();
            thread->wait();
        }
        delete thread;
        thread = 0;
    }
}
//----------------------------------------------------------------------------------------/

