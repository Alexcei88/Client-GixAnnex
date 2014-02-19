#include "threadsyncicons.h"
#include "MVC/Controller/controller_icons.h"
#include "facadeapplication.h"
#include "utils/utils.h"

using namespace Utils;
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
    QMutex& mutex = facade->threadModel.mutexSyncIcons;
    QSemaphore& sem = facade->threadModel.semSyncIcons;
    int& countCommand = facade->threadModel.countExecutingCommandWithSyncIcons;

    const uint64t timeDelay = 0.1E6;
    while(!exitThread)
    {
        if(countCommand == 0)
        {
            // если количество команд, для которых нужна синхронизация иконок равна 0,
            // то поток засыпает, пока его никто не пробудит
            sem.acquire();
        }
        if(facade->GetSystemTray())
        {
            // здесь захватить мьютексом потока синхронизации иконок
            mutex.lock();
#ifdef DEBUG
            std::cout<<"Thread sync icons working..."<<std::endl;
#endif
            IRepository* curRepo = facade->GetCurrentRepository();
            if(curRepo) {
                curRepo->UpdateParamSyncFileDir();
            }
            mutex.unlock();

            // обновляем представление в основном потоке
            facade->GetSystemTray()->OnUpdateIconsSyncronization();
            LZDelay(timeDelay);
        }
    }
}
//----------------------------------------------------------------------------------------/


