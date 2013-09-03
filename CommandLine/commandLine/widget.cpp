#include "widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    m_process     = new QProcess(this);
    m_ptxtDisplay = new QTextEdit;

    QLabel* plbl = new QLabel("&Command:");

    m_ptxtCommand = new QLineEdit("dir");
    plbl->setBuddy(m_ptxtCommand);

    QPushButton* pcmd = new QPushButton("&Enter");

    connect(m_process,
            SIGNAL(readyReadStandardOutput()),
            SLOT(slotDataOnStdout())
            );
    connect(m_ptxtCommand,
            SIGNAL(returnPressed()),
            SLOT(slotReturnPressed())
            );
    connect(pcmd, SIGNAL(clicked()), SLOT(slotReturnPressed()));

    //Layout setup
    QHBoxLayout* phbxLayout = new QHBoxLayout;
    phbxLayout->addWidget(plbl);
    phbxLayout->addWidget(m_ptxtCommand);
    phbxLayout->addWidget(pcmd);

    QVBoxLayout* pvbxLayout = new QVBoxLayout;
    pvbxLayout->addWidget(m_ptxtDisplay);
    pvbxLayout->addLayout(phbxLayout);
    setLayout(pvbxLayout);
}

Widget::~Widget()
{

}
