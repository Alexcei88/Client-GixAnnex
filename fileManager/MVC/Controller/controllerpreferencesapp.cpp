#include "controllerpreferencesapp.h"

using namespace GANN_MVC;

//----------------------------------------------------------------------------------------/
ControllerPreferencesApp::ControllerPreferencesApp():
    model(QSharedPointer<ModelQmlAndCPreferencesApp>(new ModelQmlAndCPreferencesApp()))
{
}
//----------------------------------------------------------------------------------------/
void ControllerPreferencesApp::closePreferencesAppView() const
{
    model->ClosePreforencesAppView();
}
//----------------------------------------------------------------------------------------/
