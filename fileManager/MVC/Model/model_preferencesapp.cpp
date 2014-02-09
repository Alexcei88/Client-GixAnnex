#include "model_preferencesapp.h"
#include "facadeapplication.h"

using namespace GANN_MVC;
//----------------------------------------------------------------------------------------/
ModelQmlAndCPreferencesApp::ModelQmlAndCPreferencesApp()
{}
//----------------------------------------------------------------------------------------/
void ModelQmlAndCPreferencesApp::ClosePreforencesAppView() const
{
    FacadeApplication::instance->systemTray->ClosePreferencesApplication();
}
//----------------------------------------------------------------------------------------/
