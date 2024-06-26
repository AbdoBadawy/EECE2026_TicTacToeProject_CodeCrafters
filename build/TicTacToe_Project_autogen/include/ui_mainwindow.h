/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include <tictactoeboard.h>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionAbout_QT;
    QAction *actionQuit;
    QAction *actionSign_Out;
    QAction *actionAbout_us;
    QWidget *centralwidget;
    QHBoxLayout *horizontalLayout;
    QTabWidget *mainTabs;
    QWidget *profileTab;
    QWidget *gameTab;
    QHBoxLayout *horizontalLayout_2;
    TicTacToeBoard *XO_Board;
    QFrame *line;
    QVBoxLayout *verticalLayout;
    QGroupBox *groupBox_2;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label;
    QLabel *score1Label;
    QHBoxLayout *horizontalLayout_5;
    QLabel *player2Name;
    QLabel *score2Label;
    QHBoxLayout *horizontalLayout_7;
    QLabel *modLabel;
    QLabel *modText;
    QSpacerItem *verticalSpacer;
    QGroupBox *groupBox;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QWidget *tab;
    QMenuBar *menubar;
    QMenu *menuFIle;
    QMenu *menuAbout;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(800, 600);
        actionAbout_QT = new QAction(MainWindow);
        actionAbout_QT->setObjectName(QString::fromUtf8("actionAbout_QT"));
        actionQuit = new QAction(MainWindow);
        actionQuit->setObjectName(QString::fromUtf8("actionQuit"));
        actionSign_Out = new QAction(MainWindow);
        actionSign_Out->setObjectName(QString::fromUtf8("actionSign_Out"));
        actionAbout_us = new QAction(MainWindow);
        actionAbout_us->setObjectName(QString::fromUtf8("actionAbout_us"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        horizontalLayout = new QHBoxLayout(centralwidget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        mainTabs = new QTabWidget(centralwidget);
        mainTabs->setObjectName(QString::fromUtf8("mainTabs"));
        profileTab = new QWidget();
        profileTab->setObjectName(QString::fromUtf8("profileTab"));
        mainTabs->addTab(profileTab, QString());
        gameTab = new QWidget();
        gameTab->setObjectName(QString::fromUtf8("gameTab"));
        horizontalLayout_2 = new QHBoxLayout(gameTab);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        XO_Board = new TicTacToeBoard(gameTab);
        XO_Board->setObjectName(QString::fromUtf8("XO_Board"));

        horizontalLayout_2->addWidget(XO_Board);

        line = new QFrame(gameTab);
        line->setObjectName(QString::fromUtf8("line"));
        line->setFrameShape(QFrame::VLine);
        line->setFrameShadow(QFrame::Sunken);

        horizontalLayout_2->addWidget(line);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        groupBox_2 = new QGroupBox(gameTab);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        verticalLayout_2 = new QVBoxLayout(groupBox_2);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        label = new QLabel(groupBox_2);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout_4->addWidget(label);

        score1Label = new QLabel(groupBox_2);
        score1Label->setObjectName(QString::fromUtf8("score1Label"));

        horizontalLayout_4->addWidget(score1Label);


        verticalLayout_2->addLayout(horizontalLayout_4);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        player2Name = new QLabel(groupBox_2);
        player2Name->setObjectName(QString::fromUtf8("player2Name"));

        horizontalLayout_5->addWidget(player2Name);

        score2Label = new QLabel(groupBox_2);
        score2Label->setObjectName(QString::fromUtf8("score2Label"));

        horizontalLayout_5->addWidget(score2Label);


        verticalLayout_2->addLayout(horizontalLayout_5);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        modLabel = new QLabel(groupBox_2);
        modLabel->setObjectName(QString::fromUtf8("modLabel"));

        horizontalLayout_7->addWidget(modLabel);

        modText = new QLabel(groupBox_2);
        modText->setObjectName(QString::fromUtf8("modText"));

        horizontalLayout_7->addWidget(modText);


        verticalLayout_2->addLayout(horizontalLayout_7);


        verticalLayout->addWidget(groupBox_2);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        groupBox = new QGroupBox(gameTab);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        horizontalLayout_3 = new QHBoxLayout(groupBox);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        pushButton = new QPushButton(groupBox);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));

        horizontalLayout_3->addWidget(pushButton);

        pushButton_2 = new QPushButton(groupBox);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));

        horizontalLayout_3->addWidget(pushButton_2);


        verticalLayout->addWidget(groupBox);


        horizontalLayout_2->addLayout(verticalLayout);

        mainTabs->addTab(gameTab, QString());
        tab = new QWidget();
        tab->setObjectName(QString::fromUtf8("tab"));
        mainTabs->addTab(tab, QString());

        horizontalLayout->addWidget(mainTabs);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 22));
        menuFIle = new QMenu(menubar);
        menuFIle->setObjectName(QString::fromUtf8("menuFIle"));
        menuAbout = new QMenu(menubar);
        menuAbout->setObjectName(QString::fromUtf8("menuAbout"));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        menubar->addAction(menuFIle->menuAction());
        menubar->addAction(menuAbout->menuAction());
        menuFIle->addAction(actionSign_Out);
        menuFIle->addAction(actionQuit);
        menuAbout->addAction(actionAbout_us);
        menuAbout->addAction(actionAbout_QT);

        retranslateUi(MainWindow);
        QObject::connect(XO_Board, SIGNAL(scoreUpdate()), MainWindow, SLOT(scoreUpdateLabels()));
        QObject::connect(actionQuit, SIGNAL(triggered()), MainWindow, SLOT(close()));
        QObject::connect(actionSign_Out, SIGNAL(triggered()), MainWindow, SLOT(signOut()));

        mainTabs->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        actionAbout_QT->setText(QCoreApplication::translate("MainWindow", "About qt", nullptr));
        actionQuit->setText(QCoreApplication::translate("MainWindow", "Quit", nullptr));
        actionSign_Out->setText(QCoreApplication::translate("MainWindow", "Sign Out", nullptr));
        actionAbout_us->setText(QCoreApplication::translate("MainWindow", "About us", nullptr));
        mainTabs->setTabText(mainTabs->indexOf(profileTab), QCoreApplication::translate("MainWindow", "Profile", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("MainWindow", "Scores:", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "Player1:", nullptr));
        score1Label->setText(QCoreApplication::translate("MainWindow", "0", nullptr));
        player2Name->setText(QCoreApplication::translate("MainWindow", "Player2:", nullptr));
        score2Label->setText(QCoreApplication::translate("MainWindow", "0", nullptr));
        modLabel->setText(QCoreApplication::translate("MainWindow", "Mod:", nullptr));
        modText->setText(QString());
        groupBox->setTitle(QString());
        pushButton->setText(QCoreApplication::translate("MainWindow", "Reset Board", nullptr));
        pushButton_2->setText(QCoreApplication::translate("MainWindow", "New Game", nullptr));
        mainTabs->setTabText(mainTabs->indexOf(gameTab), QCoreApplication::translate("MainWindow", "Game Board", nullptr));
        mainTabs->setTabText(mainTabs->indexOf(tab), QCoreApplication::translate("MainWindow", "Histoy", nullptr));
        menuFIle->setTitle(QCoreApplication::translate("MainWindow", "FIle", nullptr));
        menuAbout->setTitle(QCoreApplication::translate("MainWindow", "About", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
