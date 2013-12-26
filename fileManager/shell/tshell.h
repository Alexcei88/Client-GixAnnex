#ifndef TMYSHELL_H
#define TMYSHELL_H

#include <QObject>
#include <QProcess>
#include <QStringList>

#include <boost/shared_ptr.hpp>

#include "../define.h"

class IParsingCommandOut;

class TShell
{
public:
    TShell();
    ~TShell();

    // выполнение команды без аргументов
    GANN_DEFINE::RESULT_EXEC_PROCESS ExecuteProcess(const QString& str, IParsingCommandOut *receiverParsing);

    // Прервать выполнение процесса
    void                TerminateProcess() const;
    // смена рабочего каталога
    void                SetWorkingDirectory(const QString& dir) const;
    // чтение стандартного потока данных
    QByteArray          readStandartOutput() const;
    // команда, которая выполняется
    inline const QString GetStrCommand() const { return strCommand; };

    boost::shared_ptr<QProcess> process;
private:
    QString             strCommand;
};

#endif // TSHELL_H
