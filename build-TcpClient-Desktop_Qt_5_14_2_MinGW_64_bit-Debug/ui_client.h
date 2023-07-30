/********************************************************************************
** Form generated from reading UI file 'client.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CLIENT_H
#define UI_CLIENT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "qcustomplot.h"

QT_BEGIN_NAMESPACE

class Ui_client
{
public:
    QWidget *centralwidget;
    QPushButton *Connect;
    QLineEdit *IP;
    QLineEdit *Port;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *Status;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *Stable;
    QPushButton *CriStable;
    QPushButton *UnStable;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *Plot;
    QHBoxLayout *horizontalLayout;
    QCustomPlot *Voltage;
    QCustomPlot *Current;
    QHBoxLayout *horizontalLayout_2;
    QCustomPlot *Frequency;
    QCustomPlot *Power;
    QWidget *verticalLayoutWidget_2;
    QVBoxLayout *EngineState;
    QHBoxLayout *Engine_label;
    QLabel *Engine1_label;
    QLabel *Engine2_label;
    QHBoxLayout *EngineSet;
    QTextBrowser *Engine1;
    QTextBrowser *Engine2;
    QPushButton *Alarm;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *client)
    {
        if (client->objectName().isEmpty())
            client->setObjectName(QString::fromUtf8("client"));
        client->resize(1084, 895);
        centralwidget = new QWidget(client);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        Connect = new QPushButton(centralwidget);
        Connect->setObjectName(QString::fromUtf8("Connect"));
        Connect->setGeometry(QRect(460, 30, 251, 47));
        Connect->setStyleSheet(QString::fromUtf8("font: 75 20pt \"Consolas\";"));
        IP = new QLineEdit(centralwidget);
        IP->setObjectName(QString::fromUtf8("IP"));
        IP->setGeometry(QRect(20, 30, 301, 44));
        IP->setStyleSheet(QString::fromUtf8("font: 75 20pt \"Consolas\";"));
        IP->setAlignment(Qt::AlignCenter);
        Port = new QLineEdit(centralwidget);
        Port->setObjectName(QString::fromUtf8("Port"));
        Port->setGeometry(QRect(330, 30, 121, 44));
        Port->setStyleSheet(QString::fromUtf8("font: 75 20pt \"Consolas\";"));
        Port->setAlignment(Qt::AlignCenter);
        horizontalLayoutWidget = new QWidget(centralwidget);
        horizontalLayoutWidget->setObjectName(QString::fromUtf8("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(20, 270, 691, 81));
        Status = new QHBoxLayout(horizontalLayoutWidget);
        Status->setObjectName(QString::fromUtf8("Status"));
        Status->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        Stable = new QPushButton(horizontalLayoutWidget);
        Stable->setObjectName(QString::fromUtf8("Stable"));
        Stable->setStyleSheet(QString::fromUtf8("font: 75 20pt \\\"Consolas\\\"; color: #1d8aff;"));

        horizontalLayout_3->addWidget(Stable);

        CriStable = new QPushButton(horizontalLayoutWidget);
        CriStable->setObjectName(QString::fromUtf8("CriStable"));
        CriStable->setStyleSheet(QString::fromUtf8("font: 75 20pt \"Consolas\";"));

        horizontalLayout_3->addWidget(CriStable);

        UnStable = new QPushButton(horizontalLayoutWidget);
        UnStable->setObjectName(QString::fromUtf8("UnStable"));
        UnStable->setStyleSheet(QString::fromUtf8("font: 75 20pt \"Consolas\";"));

        horizontalLayout_3->addWidget(UnStable);


        Status->addLayout(horizontalLayout_3);

        verticalLayoutWidget = new QWidget(centralwidget);
        verticalLayoutWidget->setObjectName(QString::fromUtf8("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(20, 350, 1041, 471));
        Plot = new QVBoxLayout(verticalLayoutWidget);
        Plot->setObjectName(QString::fromUtf8("Plot"));
        Plot->setContentsMargins(0, 0, 0, 0);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        Voltage = new QCustomPlot(verticalLayoutWidget);
        Voltage->setObjectName(QString::fromUtf8("Voltage"));
        Voltage->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 85, 255);"));

        horizontalLayout->addWidget(Voltage);

        Current = new QCustomPlot(verticalLayoutWidget);
        Current->setObjectName(QString::fromUtf8("Current"));
        Current->setStyleSheet(QString::fromUtf8("background-color: rgb(85, 170, 255);"));

        horizontalLayout->addWidget(Current);


        Plot->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        Frequency = new QCustomPlot(verticalLayoutWidget);
        Frequency->setObjectName(QString::fromUtf8("Frequency"));
        Frequency->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 170, 255);"));

        horizontalLayout_2->addWidget(Frequency);

        Power = new QCustomPlot(verticalLayoutWidget);
        Power->setObjectName(QString::fromUtf8("Power"));
        Power->setStyleSheet(QString::fromUtf8("background-color: rgb(85, 255, 255);"));

        horizontalLayout_2->addWidget(Power);


        Plot->addLayout(horizontalLayout_2);

        verticalLayoutWidget_2 = new QWidget(centralwidget);
        verticalLayoutWidget_2->setObjectName(QString::fromUtf8("verticalLayoutWidget_2"));
        verticalLayoutWidget_2->setGeometry(QRect(20, 80, 691, 201));
        EngineState = new QVBoxLayout(verticalLayoutWidget_2);
        EngineState->setObjectName(QString::fromUtf8("EngineState"));
        EngineState->setContentsMargins(0, 0, 0, 0);
        Engine_label = new QHBoxLayout();
        Engine_label->setObjectName(QString::fromUtf8("Engine_label"));
        Engine1_label = new QLabel(verticalLayoutWidget_2);
        Engine1_label->setObjectName(QString::fromUtf8("Engine1_label"));
        Engine1_label->setStyleSheet(QString::fromUtf8("background-color: rgb(79, 170, 255);\n"
"color: rgb(237, 255, 255);\n"
"font: 75 16pt \"Candara\";"));
        Engine1_label->setAlignment(Qt::AlignCenter);

        Engine_label->addWidget(Engine1_label);

        Engine2_label = new QLabel(verticalLayoutWidget_2);
        Engine2_label->setObjectName(QString::fromUtf8("Engine2_label"));
        Engine2_label->setStyleSheet(QString::fromUtf8("background-color: rgb(79, 170, 255);\n"
"color: rgb(237, 255, 255);\n"
"font: 75 16pt \"Candara\";"));
        Engine2_label->setAlignment(Qt::AlignCenter);

        Engine_label->addWidget(Engine2_label);


        EngineState->addLayout(Engine_label);

        EngineSet = new QHBoxLayout();
        EngineSet->setObjectName(QString::fromUtf8("EngineSet"));
        Engine1 = new QTextBrowser(verticalLayoutWidget_2);
        Engine1->setObjectName(QString::fromUtf8("Engine1"));
        Engine1->setStyleSheet(QString::fromUtf8("font: 14pt \"Consolas\";\n"
"border-color: rgb(79, 170, 255);"));

        EngineSet->addWidget(Engine1);

        Engine2 = new QTextBrowser(verticalLayoutWidget_2);
        Engine2->setObjectName(QString::fromUtf8("Engine2"));
        Engine2->setStyleSheet(QString::fromUtf8("font: 14pt \"Consolas\";\n"
"border-color: rgb(79, 170, 255);"));

        EngineSet->addWidget(Engine2);


        EngineState->addLayout(EngineSet);

        Alarm = new QPushButton(centralwidget);
        Alarm->setObjectName(QString::fromUtf8("Alarm"));
        Alarm->setGeometry(QRect(820, 160, 101, 81));
        Alarm->setStyleSheet(QString::fromUtf8("background-color: rgb(170, 0, 0);\n"
"font: 20pt \"Candara\";"));
        client->setCentralWidget(centralwidget);
        menubar = new QMenuBar(client);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 1084, 26));
        client->setMenuBar(menubar);
        statusbar = new QStatusBar(client);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        client->setStatusBar(statusbar);

        retranslateUi(client);

        QMetaObject::connectSlotsByName(client);
    } // setupUi

    void retranslateUi(QMainWindow *client)
    {
        client->setWindowTitle(QCoreApplication::translate("client", "client", nullptr));
        Connect->setText(QCoreApplication::translate("client", "Connect", nullptr));
        IP->setText(QCoreApplication::translate("client", "127.0.0.1", nullptr));
        Port->setText(QCoreApplication::translate("client", "8080", nullptr));
        Stable->setText(QCoreApplication::translate("client", "Stable", nullptr));
        CriStable->setText(QCoreApplication::translate("client", "CriStable", nullptr));
        UnStable->setText(QCoreApplication::translate("client", "UnStable", nullptr));
        Engine1_label->setText(QCoreApplication::translate("client", "Engine1", nullptr));
        Engine2_label->setText(QCoreApplication::translate("client", "Engine2", nullptr));
        Alarm->setText(QCoreApplication::translate("client", "Alarm", nullptr));
    } // retranslateUi

};

namespace Ui {
    class client: public Ui_client {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CLIENT_H
