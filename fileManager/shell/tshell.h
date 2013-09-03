#ifndef TMYSHELL_H
#define TMYSHELL_H

#include <stdio.h>

#include <QObject>
#include <QProcess>
#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>

enum RESULT_EXEC_PROCESS {
     NO_ERROR = 0
    ,ERROR_NO_STARTED = 1
    ,ERROR_NO_FINISHED = 1

};

class TShell: public QObject
{
    Q_OBJECT

public:
    TShell(QObject* parent = 0);
    ~TShell();
    RESULT_EXEC_PROCESS ExecuteProcess(const QString& str) const;
    
private:
    boost::shared_ptr<QProcess> process;

};

#endif // TSHELL_H
