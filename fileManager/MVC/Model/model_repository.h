#pragma once

#include "../../facadeapplication.h"

namespace GANN_MVC
{

class ModelQmlAndCRepository
{
public:
    ModelQmlAndCRepository();

    /** @brief Получить список репозиториев */
    QVariantList        GetListRepository();

    /** @brief Клонировать репозиторий */
    int                 CloneRepository(const QString& localUlr, const QString& remoteURL, const QString& nameRepo);


};
}
