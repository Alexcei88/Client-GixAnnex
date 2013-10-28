#include "model_icons.h"
#include "facadeapplication.h"
#include <iostream>

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
    while(!exitThread)
    {
        if(FacadeApplication::getInstance()->systemTray)
        {
            auto iterRepo = FacadeApplication::instance->currentRepository;
            if(iterRepo != FacadeApplication::instance->repository.end())
            {
                IRepository* curRepo = iterRepo->second.get();
                curRepo->UpdateParamSyncFileDir();
            }

            std::cout<<"Обновляем представление с иконками"<<std::endl;
           // FacadeApplication::getInstance()->systemTray->ReLoadDirectoryView();
            sleep(2);
        }
    }
}
//----------------------------------------------------------------------------------------/

