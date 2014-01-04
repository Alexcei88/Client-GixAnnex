#include "threadsyncicons.h"
#include "MVC/Model/model_icons.h"
#include "facadeapplication.h"

//----------------------------------------------------------------------------------------/
ThreadSyncIcons::ThreadSyncIcons(GANN_MVC::ModelQmlAndCIcons* modelIcons):
    modelIcons(modelIcons)
    , exitThread(false)
{}
//----------------------------------------------------------------------------------------/
ThreadSyncIcons::~ThreadSyncIcons()
{
    exitThread = true;
}
//----------------------------------------------------------------------------------------/
//----------------------------------------------------------------------------------------/
void ThreadSyncIcons::UpdateFileSyncIcons()
{
    FacadeApplication* facade = FacadeApplication::getInstance();
    QMutex& mutex = FacadeApplication::threadModel.mutexSyncIcons;

//    while(!exitThread)
//    {
//        if(facade->systemTray)
//        {
//            // здесь захватить мьютексом потока синхронизации иконок
//            mutex.lock();

//            auto iterRepo = facade->currentRepository;
//            if(iterRepo != facade->repository.end())
//            {
//                IRepository* curRepo = iterRepo->second.get();
//                curRepo->UpdateParamSyncFileDir();
////                contrIcons->UpdateStateIconsFileSync();
//            }
//            mutex.unlock();
////            sleep(1);
//        }
//    }
}
//----------------------------------------------------------------------------------------/


