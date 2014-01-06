#include "threadsyncicons.h"
#include "MVC/Controller/controller_icons.h"
#include "facadeapplication.h"

//----------------------------------------------------------------------------------------/
ThreadSyncIcons::ThreadSyncIcons(GANN_MVC::ControllerIcons* controllerIcons):
    controllerIcons(controllerIcons)
  , exitThread(false)
{}
//----------------------------------------------------------------------------------------/
ThreadSyncIcons::~ThreadSyncIcons()
{
    exitThread = true;
}
//----------------------------------------------------------------------------------------/
void ThreadSyncIcons::UpdateFileSyncIcons()
{
    FacadeApplication* facade = FacadeApplication::getInstance();
    QMutex& mutex = FacadeApplication::threadModel.mutexSyncIcons;

    while(!exitThread)
    {
        if(facade->GetSystemTray())
        {
            // здесь захватить мьютексом потока синхронизации иконок
            mutex.lock();
            IRepository* curRepo = facade->GetCurrentRepository();
            if(curRepo)
            {
                curRepo->UpdateParamSyncFileDir();
                if(controllerIcons)
                {
                    controllerIcons->UpdateStateIconsFileSync();
                }
            }
            mutex.unlock();
            // посылаем сигнал, что нужно обновить представление
//            emit facade->GetSystemTray()->updateIconsSyncronization();
//            sleep(1);
        }
    }
}
//----------------------------------------------------------------------------------------/


