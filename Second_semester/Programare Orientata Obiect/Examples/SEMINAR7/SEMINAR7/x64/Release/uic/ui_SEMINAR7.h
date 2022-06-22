/********************************************************************************
** Form generated from reading UI file 'SEMINAR7.ui'
**
** Created by: Qt User Interface Compiler version 6.3.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SEMINAR7_H
#define UI_SEMINAR7_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SEMINAR7Class
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *SEMINAR7Class)
    {
        if (SEMINAR7Class->objectName().isEmpty())
            SEMINAR7Class->setObjectName(QString::fromUtf8("SEMINAR7Class"));
        SEMINAR7Class->resize(600, 400);
        menuBar = new QMenuBar(SEMINAR7Class);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        SEMINAR7Class->setMenuBar(menuBar);
        mainToolBar = new QToolBar(SEMINAR7Class);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        SEMINAR7Class->addToolBar(mainToolBar);
        centralWidget = new QWidget(SEMINAR7Class);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        SEMINAR7Class->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(SEMINAR7Class);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        SEMINAR7Class->setStatusBar(statusBar);

        retranslateUi(SEMINAR7Class);

        QMetaObject::connectSlotsByName(SEMINAR7Class);
    } // setupUi

    void retranslateUi(QMainWindow *SEMINAR7Class)
    {
        SEMINAR7Class->setWindowTitle(QCoreApplication::translate("SEMINAR7Class", "SEMINAR7", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SEMINAR7Class: public Ui_SEMINAR7Class {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SEMINAR7_H
