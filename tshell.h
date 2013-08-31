#ifndef TMYSHELL_H
#define TMYSHELL_H

#include <QObject>
#include <QProcess>
#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>

class TShell: public QObject
{
    Q_OBJECT

public:
    TShell(QObject* parent = 0);
    ~TShell();
    int         ExecuteProcess(const QString& str) const;
    
private:
    boost::shared_ptr<QProcess> process;

};

#endif // TSHELL_H
