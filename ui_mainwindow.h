/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created: Thu Nov 10 20:10:44 2011
**      by: Qt User Interface Compiler version 4.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
#include <QtGui/QStatusBar>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionReset;
    QAction *actionTop_Ten;
    QAction *actionExit;
    QAction *actionHelp;
    QAction *actionAbout;
    QAction *actionReset_Top_Ten;
    QWidget *centralWidget;
    QLabel *label_2;
    QLabel *mine_left_label;
    QLabel *mines_left_display;
    QLabel *timer_label;
    QPushButton *reset_button;
    QMenuBar *menuBar;
    QMenu *menuGame;
    QMenu *menuHelp;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(449, 488);
        actionReset = new QAction(MainWindow);
        actionReset->setObjectName(QString::fromUtf8("actionReset"));
        actionTop_Ten = new QAction(MainWindow);
        actionTop_Ten->setObjectName(QString::fromUtf8("actionTop_Ten"));
        actionExit = new QAction(MainWindow);
        actionExit->setObjectName(QString::fromUtf8("actionExit"));
        actionHelp = new QAction(MainWindow);
        actionHelp->setObjectName(QString::fromUtf8("actionHelp"));
        actionAbout = new QAction(MainWindow);
        actionAbout->setObjectName(QString::fromUtf8("actionAbout"));
        actionReset_Top_Ten = new QAction(MainWindow);
        actionReset_Top_Ten->setObjectName(QString::fromUtf8("actionReset_Top_Ten"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(280, 10, 31, 31));
        mine_left_label = new QLabel(centralWidget);
        mine_left_label->setObjectName(QString::fromUtf8("mine_left_label"));
        mine_left_label->setGeometry(QRect(80, 0, 61, 51));
        mine_left_label->setStyleSheet(QString::fromUtf8(""));
        mines_left_display = new QLabel(centralWidget);
        mines_left_display->setObjectName(QString::fromUtf8("mines_left_display"));
        mines_left_display->setGeometry(QRect(150, 10, 31, 31));
        mines_left_display->setStyleSheet(QString::fromUtf8(""));
        timer_label = new QLabel(centralWidget);
        timer_label->setObjectName(QString::fromUtf8("timer_label"));
        timer_label->setGeometry(QRect(320, 10, 46, 31));
        reset_button = new QPushButton(centralWidget);
        reset_button->setObjectName(QString::fromUtf8("reset_button"));
        reset_button->setGeometry(QRect(190, 10, 71, 31));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 449, 21));
        menuGame = new QMenu(menuBar);
        menuGame->setObjectName(QString::fromUtf8("menuGame"));
        menuHelp = new QMenu(menuBar);
        menuHelp->setObjectName(QString::fromUtf8("menuHelp"));
        MainWindow->setMenuBar(menuBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menuGame->menuAction());
        menuBar->addAction(menuHelp->menuAction());
        menuGame->addAction(actionReset);
        menuGame->addAction(actionTop_Ten);
        menuGame->addAction(actionReset_Top_Ten);
        menuGame->addAction(actionExit);
        menuHelp->addAction(actionHelp);
        menuHelp->addAction(actionAbout);

        retranslateUi(MainWindow);
        QObject::connect(reset_button, SIGNAL(clicked()), MainWindow, SLOT(reset()));

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Minesweeper", 0, QApplication::UnicodeUTF8));
        actionReset->setText(QApplication::translate("MainWindow", "Reset", 0, QApplication::UnicodeUTF8));
        actionReset->setShortcut(QApplication::translate("MainWindow", "R", 0, QApplication::UnicodeUTF8));
        actionTop_Ten->setText(QApplication::translate("MainWindow", "Top ten", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        actionTop_Ten->setToolTip(QApplication::translate("MainWindow", "Top Ten", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        actionTop_Ten->setShortcut(QApplication::translate("MainWindow", "T", 0, QApplication::UnicodeUTF8));
        actionExit->setText(QApplication::translate("MainWindow", "eXit", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        actionExit->setToolTip(QApplication::translate("MainWindow", "Exit", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        actionExit->setShortcut(QApplication::translate("MainWindow", "X", 0, QApplication::UnicodeUTF8));
        actionHelp->setText(QApplication::translate("MainWindow", "Help", 0, QApplication::UnicodeUTF8));
        actionHelp->setShortcut(QApplication::translate("MainWindow", "H", 0, QApplication::UnicodeUTF8));
        actionAbout->setText(QApplication::translate("MainWindow", "About", 0, QApplication::UnicodeUTF8));
        actionAbout->setShortcut(QApplication::translate("MainWindow", "A", 0, QApplication::UnicodeUTF8));
        actionReset_Top_Ten->setText(QApplication::translate("MainWindow", "reSet top ten", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        actionReset_Top_Ten->setToolTip(QApplication::translate("MainWindow", "Reset Top Ten", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        actionReset_Top_Ten->setShortcut(QApplication::translate("MainWindow", "S", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("MainWindow", "Time:", 0, QApplication::UnicodeUTF8));
        mine_left_label->setText(QApplication::translate("MainWindow", "Mines left: ", 0, QApplication::UnicodeUTF8));
        mines_left_display->setText(QApplication::translate("MainWindow", "10", 0, QApplication::UnicodeUTF8));
        timer_label->setText(QApplication::translate("MainWindow", "0", 0, QApplication::UnicodeUTF8));
        reset_button->setText(QApplication::translate("MainWindow", "Reset", 0, QApplication::UnicodeUTF8));
        menuGame->setTitle(QApplication::translate("MainWindow", "Game", 0, QApplication::UnicodeUTF8));
        menuHelp->setTitle(QApplication::translate("MainWindow", "Help", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
