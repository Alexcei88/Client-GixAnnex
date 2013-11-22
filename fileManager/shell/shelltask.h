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
    ShellTask(const QString strCommand, const QString localURL, boost::shared_ptr<IParsingCommandOut> parsingCommand);
    ~ShellTask();
    // функция потока
    virtual void run();

protected:
    // команда
    const QString command;
    // класс парсинга
    boost::shared_ptr<IParsingCommandOut> parsingCommand;
    // класс выполнения команды
    TShell* shell;
    // директория, откуда работаем с shell-ом
    const QString localURL;
};

#endif // SHELLTASK_H
