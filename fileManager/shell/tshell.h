#ifndef TMYSHELL_H
#define TMYSHELL_H

#include <stdio.h>
#include <vector>

#include <QObject>
#include <QProcess>
#include <QStringList>

#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>
#include <boost/foreach.hpp>
#include <boost/bind.hpp>

#undef foreach
#define foreach BOOST_FOREACH

#include "../parsing_command_out/iparsingcommandout.h"
#include "../define.h"


class TShell
{
public:
    TShell();
    ~TShell();

    // выполнение команды без аргументов
    GANN_DEFINE::RESULT_EXEC_PROCESS ExecuteProcess(const QString& str, IParsingCommandOut *receiverParsing) const;

    // смена рабочего каталога
    void                SetWorkingDirectory(const QString& dir) const;

    // чтение стандартного потока данных
    QByteArray          readStandartOutput() const;

//private:
    boost::shared_ptr<QProcess> process;
};

#endif // TSHELL_H
