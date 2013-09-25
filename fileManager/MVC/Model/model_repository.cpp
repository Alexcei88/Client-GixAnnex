#include "model_repository.h"

#include <QVariantList>

using namespace GANN_MVC;

//----------------------------------------------------------------------------------------/
ModelQmlAndCRepository::ModelQmlAndCRepository()
{
    GetListRepository();
}
//----------------------------------------------------------------------------------------/
QVariantList ModelQmlAndCRepository::GetListRepository()
{
    QVariantList repoRegistry;
    std::map<QString, boost::shared_ptr<IRepository>> repository = FacadeApplication::getInstance()->repository;
    // заполняем repoRegistry
    for(auto i = repository.begin(); i != repository.end(); ++i)
    {
        const QVariant pathRepo = i->first;
        repoRegistry.push_back(pathRepo);
    }
    return repoRegistry;
}

