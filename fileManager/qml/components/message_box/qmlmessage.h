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

    Q_INVOKABLE void showErrorMessage(QVariant title, QVariant text) const;
private:
    QMessageBox*    box;
};

#endif // QMLERRORMESSAGE_H
