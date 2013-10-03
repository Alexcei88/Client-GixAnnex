#ifndef SHELLTASK_H
#define SHELLTASK_H

#include <QRunnable>
#include <QString>

class TShell;
class IParsingCommandOut;

class ShellTask: public QRunnable
{
public:
    ShellTask(const QString& strCommand, IParsingCommandOut* parsingCommand, const TShell* shell);
    // функция потока
    virtual void run();

protected:
    // команда
    const QString command;
    // класс парсинга
    IParsingCommandOut* parsingCommand;
    // класс выполнения команды
    const TShell* shell;
};

#endif // SHELLTASK_H
