#ifndef QMLERRORMESSAGE_H
#define QMLERRORMESSAGE_H
#include <QObject>
#include <QMessageBox>
#include <QtWidgets>
class QMLMessage: public QObject
{
    Q_OBJECT
public:
    explicit QMLMessage(QWidget* parent = 0);
    ~QMLMessage();

    /** @brief Показ сообщения с ошибкой */
    Q_INVOKABLE void showErrorMessage(QVariant title, QVariant text) const;

    /** @brief Сообщения для подтверждения операции
        2 кнопки - Yes No
    */
    Q_INVOKABLE QVariant showConfirmMessage(QVariant title, QVariant text) const;
private:
    QMessageBox*    box;
};

#endif // QMLERRORMESSAGE_H
