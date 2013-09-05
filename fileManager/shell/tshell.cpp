#include "tshell.h"
#include <stdio.h>
     
TShell* TShell::instance = 0;

//----------------------------------------------------------------------------------------/
TShell::TShell(QObject* parent):
    QObject(parent)
{
    process = boost::make_shared<QProcess>(this);
}
//----------------------------------------------------------------------------------------/
TShell::~TShell(){}
//----------------------------------------------------------------------------------------/
TShell* TShell::GetInstance()
{
    if(!instance)
        instance = new TShell();
    return instance;
}
void TShell::RemoveInstance()
{
    delete instance;
    instance = 0l;
}
//----------------------------------------------------------------------------------------/
RESULT_EXEC_PROCESS TShell::ExecuteProcess(const QString &str, IParsingCommandOut *receiverParsing) const
{
    // соединяем сигнал получения данных со стандартного потока вывода с соот классом
    QMetaObject::Connection m_connection;
    m_connection = QObject::connect(process.get(), &QProcess::readyReadStandardError, [=](){receiverParsing->GetNewDataStdOut(); });
    QObject::disconnect(m_connection);

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
        printf("Process not started! \n");
        return ERROR_NO_STARTED;
    }

    // иначе ждем, пока он не завершиться
    // если процесс не завершился, то возвращаем -2
    if(!process->waitForFinished(-1))
    {
        printf("Process finished with error! \n");
        return ERROR_NO_FINISHED;
    }

    return NO_ERROR;
}
//----------------------------------------------------------------------------------------/
void TShell::SetWorkingDirectory(const QString& dir) const
{
    process->setWorkingDirectory(dir);
}
//----------------------------------------------------------------------------------------/
QByteArray TShell::readStandartOutput() const
{
    return process->readAllStandardOutput();
}
//----------------------------------------------------------------------------------------/

