#pragma once

#include <QVariantList>

#include <boost/shared_ptr.hpp>
#include <map>
//#include "../../facadeapplication.h"
#include "../define.h"
#include "../repository/irepository.h"

namespace GANN_MVC
{

class ModelQmlAndCRepository
{
public:
    ModelQmlAndCRepository();

    /** @brief Получить список репозиториев */
    QVariantList        GetListRepository();

    /** @brief Получить дефалтный репозиторий */
    const QString       GetDefaultRepository() const;

    /** @brief Клонировать репозиторий */
    GANN_DEFINE::RESULT_EXEC_PROCESS CloneRepository(const QString& localUlr, const QString& remoteURL, const QString& nameRepo);

    /** @brief Остановить клонирование */
    void                CancelCloneRepository(bool breakCommand = true) const;

    /** @brief взять контент у файла(директории)*/
    GANN_DEFINE::RESULT_EXEC_PROCESS GetContentDirectory(const QString& dir) const;

    /** @brief удалить контент у файла(директории)*/
    GANN_DEFINE::RESULT_EXEC_PROCESS DropContentDirectory(const QString& dir) const;

    /** @brief Сменить текущий репозиторий */
    void                ChangeCurrentRepository(const QString &dir) const;


};
}
