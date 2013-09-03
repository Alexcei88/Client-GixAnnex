#ifndef WIDGET_H
#define WIDGET_H

#include <iostream>

#include <QWidget>
#include <QApplication>
#include <QLineEdit>
#include <QTextEdit>
#include <QProcess>
#include <QLayout>
#include <QLabel>
#include <QPushButton>


class Widget : public QWidget
{
    Q_OBJECT

private:
    QProcess*  m_process;
    QLineEdit* m_ptxtCommand;
    QTextEdit* m_ptxtDisplay;
public:
    Widget(QWidget *parent = 0);
    ~Widget();

public slots:
    void slotDataOnStdout()
    {
        m_ptxtDisplay->append(m_process->readAllStandardOutput());
    }

    void slotReturnPressed()
    {
        QString strCommand = "";
#ifdef Q_WS_WIN
        strCommand = "cmd /C ";
#endif
        strCommand += m_ptxtCommand->text();

        static bool first = false;
        m_process->start(strCommand);
    }
};

#endif // WIDGET_H
