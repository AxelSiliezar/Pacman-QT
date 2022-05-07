/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.2.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QPushButton *twoPlayer;
    QLabel *label;
    QGraphicsView *graphicsView;
    QPushButton *onePlayer;
    QPushButton *levelOne;
    QPushButton *levelTwo;
    QPushButton *levelThree;
    QPushButton *levelFour;
    QPushButton *levelFive;
    QPushButton *boss;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1496, 963);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        twoPlayer = new QPushButton(centralwidget);
        twoPlayer->setObjectName(QString::fromUtf8("twoPlayer"));
        twoPlayer->setGeometry(QRect(680, 120, 100, 32));
        label = new QLabel(centralwidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(700, 30, 91, 51));
        graphicsView = new QGraphicsView(centralwidget);
        graphicsView->setObjectName(QString::fromUtf8("graphicsView"));
        graphicsView->setGeometry(QRect(-10, -20, 1501, 931));
        onePlayer = new QPushButton(centralwidget);
        onePlayer->setObjectName(QString::fromUtf8("onePlayer"));
        onePlayer->setGeometry(QRect(680, 80, 100, 32));
        levelOne = new QPushButton(centralwidget);
        levelOne->setObjectName(QString::fromUtf8("levelOne"));
        levelOne->setGeometry(QRect(400, 360, 100, 32));
        levelTwo = new QPushButton(centralwidget);
        levelTwo->setObjectName(QString::fromUtf8("levelTwo"));
        levelTwo->setGeometry(QRect(510, 360, 100, 32));
        levelThree = new QPushButton(centralwidget);
        levelThree->setObjectName(QString::fromUtf8("levelThree"));
        levelThree->setGeometry(QRect(620, 360, 100, 32));
        levelFour = new QPushButton(centralwidget);
        levelFour->setObjectName(QString::fromUtf8("levelFour"));
        levelFour->setGeometry(QRect(730, 360, 100, 32));
        levelFive = new QPushButton(centralwidget);
        levelFive->setObjectName(QString::fromUtf8("levelFive"));
        levelFive->setGeometry(QRect(840, 360, 100, 32));
        boss = new QPushButton(centralwidget);
        boss->setObjectName(QString::fromUtf8("boss"));
        boss->setGeometry(QRect(950, 360, 100, 32));
        MainWindow->setCentralWidget(centralwidget);
        graphicsView->raise();
        twoPlayer->raise();
        label->raise();
        onePlayer->raise();
        levelOne->raise();
        levelTwo->raise();
        levelThree->raise();
        levelFour->raise();
        levelFive->raise();
        boss->raise();
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 1496, 24));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        twoPlayer->setText(QCoreApplication::translate("MainWindow", "Versus", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "PACMAN", nullptr));
        onePlayer->setText(QCoreApplication::translate("MainWindow", "One Player", nullptr));
        levelOne->setText(QCoreApplication::translate("MainWindow", "Level 1", nullptr));
        levelTwo->setText(QCoreApplication::translate("MainWindow", "Level 2", nullptr));
        levelThree->setText(QCoreApplication::translate("MainWindow", "Level 3", nullptr));
        levelFour->setText(QCoreApplication::translate("MainWindow", "Level 4", nullptr));
        levelFive->setText(QCoreApplication::translate("MainWindow", "Level 5", nullptr));
        boss->setText(QCoreApplication::translate("MainWindow", "Boss", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
