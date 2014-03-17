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

    const uint64t timeDelay = 0.2E6;
    bool oneCall = false;

    while(!exitThread)
    {
        // условия на засыпание потока
        if(countCommand == 0)
        {
            // если количество команд, для которых нужна синхронизация иконок равна 0,
            // то поток засыпает, пока его никто внешне не пробудит
            if(oneCall) {
                oneCall = false;
            }
            else{
                // ждем пробуждения потока
                sem.acquire();
                // поток проснулся
                if(countCommand > 0)
                {
                    // выставляем флаг, что после окончания выполнения команды
                    // нужно еще один раз вызвать поток
                    oneCall = true;
                }
            }
        }
        // сама работа потока
        if(facade->GetSystemTray())
        {
            // здесь захватить мьютексом потока синхронизации иконок
            mutex.lock();
#ifdef DEBUG
//            std::cout<<"Thread sync icons working..."<<std::endl;
#endif
            IRepository* curRepo = facade->GetCurrentRepository();
            if(curRepo) {
                curRepo->UpdateParamSyncFileDir();
            }
            mutex.unlock();

            // обновляем представление в основном потоке
            facade->GetSystemTray()->OnUpdateIconsSyncronization();
        }
        LZDelay(timeDelay);
    }
}
//----------------------------------------------------------------------------------------/


