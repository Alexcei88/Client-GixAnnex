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

};
}
