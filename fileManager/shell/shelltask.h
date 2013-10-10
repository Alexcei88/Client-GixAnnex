#ifndef SHELLTASK_H
#define SHELLTASK_H

// Qt stuff
#include <QRunnable>
#include <QString>

// boost stuff
#include <boost/shared_ptr.hpp>
#include <boost/weak_ptr.hpp>

class TShell;
class IParsingCommandOut;

class ShellTask: public QRunnable
{
public:
    ShellTask(const QString strCommand, boost::shared_ptr<IParsingCommandOut> parsingCommand, const boost::shared_ptr<TShell> shell);
    // функция потока
    virtual void run();

protected:
    // команда
    const QString command;
    // класс парсинга
    boost::shared_ptr<IParsingCommandOut> parsingCommand;
    // класс выполнения команды
    const boost::shared_ptr<TShell> shell;
};

#endif // SHELLTASK_H
