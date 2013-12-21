#include "model_icons.h"
#include "facadeapplication.h"
#include "../Controller/controller_icons.h"

using namespace GANN_MVC;

//----------------------------------------------------------------------------------------/
ModelQmlAndCIcons::ModelQmlAndCIcons(ControllerIcons* contrIcons):
    contrIcons(contrIcons)
  , exitThread(false)
{}
//----------------------------------------------------------------------------------------/
ModelQmlAndCIcons::~ModelQmlAndCIcons()
{
    exitThread = true;
}
//----------------------------------------------------------------------------------------/
void ModelQmlAndCIcons::UpdateFileSyncIcons()
{
    return;
    FacadeApplication* facade = FacadeApplication::getInstance();
    QMutex& mutex = FacadeApplication::threadModel.mutexSyncIcons;

    while(!exitThread)
    {
        if(facade->systemTray)
        {
            // здесь захватить мьютексом потока синхронизации иконок
            mutex.lock();

            auto iterRepo = facade->currentRepository;
            if(iterRepo != facade->repository.end())
            {
                IRepository* curRepo = iterRepo->second.get();
                curRepo->UpdateParamSyncFileDir();
                contrIcons->UpdateStateIconsFileSync();
            }
            mutex.unlock();
            sleep(1);
        }
    }
}
//----------------------------------------------------------------------------------------/

