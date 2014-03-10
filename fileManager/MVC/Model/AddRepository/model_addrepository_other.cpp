#include "model_addrepository_other.h"

using namespace GANN_MVC;

//----------------------------------------------------------------------------------------/
ModelAddOtherRepository::ModelAddOtherRepository():
    IModelQmlAndCAddRepository()
{
    listOptions << "Source URL" << "Destinition URL" << "Name";
}
//----------------------------------------------------------------------------------------/

