#include "tshell.h"
#include "../parsing_command_out/iparsingcommandout.h"

#include <stdio.h>

// boost stuff
#include <boost/make_shared.hpp>


using namespace GANN_DEFINE;

//----------------------------------------------------------------------------------------/
TShell::TShell()
{
    process = boost::make_shared<QProcess>();
    process->setProcessChannelMode(QProcess::MergedChannels);
}
//----------------------------------------------------------------------------------------/
TShell::~TShell(){}
//----------------------------------------------------------------------------------------/
RESULT_EXEC_PROCESS TShell::ExecuteProcess(const QString &str, IParsingCommandOut *receiverParsing)
{
    // сохраняем команду, которую будем выполнять
    this->strCommand = str;

    // соединяем сигнал получения данных со стандартного потока вывода с соот классом
    QMetaObject::Connection m_connection_readOut;
    QMetaObject::Connection m_connection_started;
    QMetaObject::Connection m_connection_finished;
    QMetaObject::Connection m_connection_error;

    m_connection_readOut  = QObject::connect(process.get(), &QProcess::readyReadStandardOutput, [=](){ receiverParsing->SetNewDataStdOut(); });
    m_connection_started  = QObject::connect(process.get(), &QProcess::started, [=](){receiverParsing->SetParamBeforeStartCommand(); });
    m_connection_finished = QObject::connect(process.get(), static_cast<void (QProcess::*)(int exitCode)>(&QProcess::finished),
                            [=](int exitCode){ receiverParsing->SetParamAfterEndCommand(exitCode); });
    m_connection_error    = QObject::connect(process.get(), static_cast<void (QProcess::*)(QProcess::ProcessError error)>(&QProcess::error),
                            [=](QProcess::ProcessError error){ receiverParsing->SetParamErrorExecuteCommand(error); });

    QString strCommand = "";
    #ifdef Q_WS_WIN
            strCommand = "cmd /C ";
    #endif
    strCommand += str;

    process->start(strCommand);

    // ждем, пока процесс не запуститься
    // если процесс не запустился, возвращаем -1
    if(!process->waitForStarted(600000))
    {
        printf("Process not started! \n");
        receiverParsing->SetParamErrorExecuteCommand(QProcess::FailedToStart);
        QObject::disconnect(m_connection_readOut);
        QObject::disconnect(m_connection_started);
        QObject::disconnect(m_connection_finished);
        QObject::disconnect(m_connection_error);
        return ERROR_NO_STARTED;
    }

    // иначе ждем, пока он не завершиться
    // если процесс не завершился, то возвращаем ошибку
    if(!process->waitForFinished(-1))
    {
        printf("Process finished with error! \n");
        QObject::disconnect(m_connection_readOut);
        QObject::disconnect(m_connection_started);
        QObject::disconnect(m_connection_finished);
        QObject::disconnect(m_connection_error);
        return ERROR_NO_FINISHED;
    }

    QObject::disconnect(m_connection_readOut);
    QObject::disconnect(m_connection_started);
    QObject::disconnect(m_connection_finished);
    QObject::disconnect(m_connection_error);
    return NO_ERROR;
}
//----------------------------------------------------------------------------------------/
void TShell::TerminateProcess() const
{
    process->terminate();
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

