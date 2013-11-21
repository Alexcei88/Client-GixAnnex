#include "model_icons.h"
#include "facadeapplication.h"
#include <iostream>
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
    while(!exitThread)
    {
        if(FacadeApplication::getInstance()->systemTray)
        {
            auto iterRepo = FacadeApplication::instance->currentRepository;
            if(iterRepo != FacadeApplication::instance->repository.end())
            {
                IRepository* curRepo = iterRepo->second.get();
                curRepo->UpdateParamSyncFileDir();
                contrIcons->UpdateStateIconsFileSync();
            }
            FacadeApplication::getInstance()->systemTray->ReLoadDirectoryView();
            sleep(2);
        }
    }
}
//----------------------------------------------------------------------------------------/

