#ifndef IMODELADDREPOSITORY_H
#define IMODELADDREPOSITORY_H

#include "define.h"


namespace GANN_MVC
{
class IModelQmlAndCAddRepository
{
public:
    IModelQmlAndCAddRepository();

    /** @brief Начать добавление репозитория */
    virtual GANN_DEFINE::RESULT_EXEC_PROCESS StartAddRepository() = 0;

    /** @brief Остановить добавление */
    void                CancelAddRepository() const;

    /** @brief Закрыть окно добавления репозитория */
    static void         CloseWindowAddRepository();


};

}
#endif // IMODELADDREPOSITORY_H
