#ifndef IMODELADDREPOSITORY_H
#define IMODELADDREPOSITORY_H

#include "define.h"

// Qt stuff
#include <QString>
#include <QMap>
#include <QVariantList>

namespace GANN_MVC
{
class IModelQmlAndCAddRepository
{
public:

    IModelQmlAndCAddRepository();

    /** @brief Начать добавление репозитория */
    virtual GANN_DEFINE::RESULT_EXEC_PROCESS StartAddRepository(const QMap<QString, QString>& options);

    /** @brief Возвращает список параметров */
    virtual QVariantList GetListOptions() const;

    /** @brief Остановить добавление */
    virtual void        CancelAddRepository(const QMap<QString, QString> &options) const;

    /** @brief Закрыть окно добавления репозитория */
    static void         CloseWindowAddRepository();

protected:
    // список параметров
    QVariantList        listOptions;

private:
    // взять удаленный путь, откуда будет копироваться
    virtual QString     GetRemoteUrl(const QMap<QString, QString>& options) const;

    // взять локальный путь, куда будет копироваться
    virtual QString     GetLocalUrl(const QMap<QString, QString>& options) const;

    // взять имя репозитория
    virtual QString     GetNameRepository(const QMap<QString, QString>& options) const;
};

}
#endif // IMODELADDREPOSITORY_H
