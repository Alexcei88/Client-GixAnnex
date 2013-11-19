#ifndef QMLERRORMESSAGE_H
#define QMLERRORMESSAGE_H
#include <QObject>
#include <QMessageBox>
#include <QtWidgets>
class QMLErrorMessage: public QObject
{
    Q_OBJECT
public:
    explicit QMLErrorMessage(QWidget* parent = 0);
    ~QMLErrorMessage();

    Q_INVOKABLE void ShowErrorMessage(QVariant title, QVariant text) const;
private:
    QMessageBox*    box;
};

#endif // QMLERRORMESSAGE_H
