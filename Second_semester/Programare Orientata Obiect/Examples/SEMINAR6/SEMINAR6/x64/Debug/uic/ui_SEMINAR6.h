/********************************************************************************
** Form generated from reading UI file 'SEMINAR6.ui'
**
** Created by: Qt User Interface Compiler version 6.3.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SEMINAR6_H
#define UI_SEMINAR6_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SEMINAR6Class
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *SEMINAR6Class)
    {
        if (SEMINAR6Class->objectName().isEmpty())
            SEMINAR6Class->setObjectName(QString::fromUtf8("SEMINAR6Class"));
        SEMINAR6Class->resize(600, 400);
        menuBar = new QMenuBar(SEMINAR6Class);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        SEMINAR6Class->setMenuBar(menuBar);
        mainToolBar = new QToolBar(SEMINAR6Class);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        SEMINAR6Class->addToolBar(mainToolBar);
        centralWidget = new QWidget(SEMINAR6Class);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        SEMINAR6Class->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(SEMINAR6Class);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        SEMINAR6Class->setStatusBar(statusBar);

        retranslateUi(SEMINAR6Class);

        QMetaObject::connectSlotsByName(SEMINAR6Class);
    } // setupUi

    void retranslateUi(QMainWindow *SEMINAR6Class)
    {
        SEMINAR6Class->setWindowTitle(QCoreApplication::translate("SEMINAR6Class", "SEMINAR6", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SEMINAR6Class: public Ui_SEMINAR6Class {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SEMINAR6_H
