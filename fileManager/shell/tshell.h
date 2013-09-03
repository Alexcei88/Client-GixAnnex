#ifndef TMYSHELL_H
#define TMYSHELL_H

#include <stdio.h>

#include <QObject>
#include <QProcess>
#include <QStringList>
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

private:
    TShell(QObject* parent = 0);
    ~TShell();

public:
    static TShell*      GetInstance();
    static void         RemoveInstance();

    // выполнение команды без аргументов
    RESULT_EXEC_PROCESS ExecuteProcess(const QString& str) const;
    // выполнение команды с аргументами(пока не будет)
    // выполнение команды с возвращаемым cтроковым значением, содержащие какие то параметры(или просто например, стандартный поток вывода)
    RESULT_EXEC_PROCESS ExecuteProcess(const QString &str, QStringList& retString) const;

    // смена рабочего каталога
    void                SetWorkingDirectory(const QString& dir) const;
    
private:
    boost::shared_ptr<QProcess> process;
    static TShell*      instance;

    // информация из станд потока вывода
    QStringList         stdOut;
    // информация из стан потока ошибок
    QStringList         stdError;
};

#endif // TSHELL_H
