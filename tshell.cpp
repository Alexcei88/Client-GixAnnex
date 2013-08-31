#include "tshell.h"
#include <stdio.h>

//----------------------------------------------------------------------------------------/
TShell::TShell(QObject* parent):
    QObject(parent)
{
    process = boost::make_shared<QProcess>(this);
}
//----------------------------------------------------------------------------------------/
TShell::~TShell(){}
//----------------------------------------------------------------------------------------/
int TShell::ExecuteProcess(const QString &str) const
{
    QString strCommand = "";
    #ifdef Q_WS_WIN
            strCommand = "cmd /C ";
    #endif
    strCommand += str;

    process->start(strCommand);

    // ждем, пока процесс не запуститься
    // если процесс не запустился, возвращаем -1
    if(!process->waitForStarted(1000))
    {
        printf("Process not started!");
        return -1;
    }

    // иначе ждем, пока он не завершиться
    // если процесс не завершился, то возвращаем -2
    if(!process->waitForFinished(-1))
    {
        printf("Process finished with error");
        return -2;
    }

    return 0;
}
//----------------------------------------------------------------------------------------/

