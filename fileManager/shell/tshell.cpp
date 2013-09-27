#include "tshell.h"
#include <stdio.h>

using namespace GANN_DEFINE;

TShell* TShell::instance = 0;

//----------------------------------------------------------------------------------------/
TShell::TShell(QObject* parent):
    QObject(parent)
{
    process = boost::make_shared<QProcess>(this);
    process->setProcessChannelMode(QProcess::MergedChannels);
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
    QMetaObject::Connection m_connection_readOut;
//    QMetaObject::Connection m_connection_readOut1;
    QMetaObject::Connection m_connection_started;
    QMetaObject::Connection m_connection_finished;

    m_connection_readOut  = QObject::connect(process.get(), &QProcess::readyReadStandardOutput, [=](){receiverParsing->GetNewDataStdOut(); });
//    m_connection_readOut1  = QObject::connect(process.get(), &QProcess::readyRead, [=](){receiverParsing->GetNewDataStdOut(); });
    m_connection_started  = QObject::connect(process.get(), &QProcess::started, [=](){receiverParsing->SetParamBeforeStartCommand(); });
    m_connection_finished = QObject::connect(process.get(), &QProcess::finished, [=](int exitCode){ receiverParsing->SetParamAfterEndCommand(exitCode); });

    QString strCommand = "";
    #ifdef Q_WS_WIN
            strCommand = "cmd /C ";
    #endif
    strCommand += str;

    process->start(strCommand);

    // ждем, пока процесс не запуститься
    // если процесс не запустился, возвращаем -1
    if(!process->waitForStarted(5000))
    {
        printf("Process not started! \n");
        QObject::disconnect(m_connection_readOut);
        QObject::disconnect(m_connection_started);
        QObject::disconnect(m_connection_finished);
        return ERROR_NO_STARTED;
    }

    // иначе ждем, пока он не завершиться
    // если процесс не завершился, то возвращаем -2
    if(!process->waitForFinished(-1))
    {
        printf("Process finished with error! \n");
        QObject::disconnect(m_connection_readOut);
        QObject::disconnect(m_connection_started);
        QObject::disconnect(m_connection_finished);
        return ERROR_NO_FINISHED;
    }

    QObject::disconnect(m_connection_readOut);
    QObject::disconnect(m_connection_started);
    QObject::disconnect(m_connection_finished);
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

