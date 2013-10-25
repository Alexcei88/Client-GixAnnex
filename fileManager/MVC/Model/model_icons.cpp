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
            std::cout<<"Обновляем представление с иконками"<<std::endl;
            FacadeApplication::getInstance()->systemTray->ReLoadDirectoryView();
            sleep(10);
        }
    }
}
//----------------------------------------------------------------------------------------/

