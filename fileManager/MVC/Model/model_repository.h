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
    GANN_DEFINE::RESULT_EXEC_PROCESS CloneRepository(const QString& localUlr, const QString& remoteURL, const QString& nameRepo);

    /** @brief Остановить клонирование */
    void                CancelCloneRepository(bool breakCommand = true);

};
}
