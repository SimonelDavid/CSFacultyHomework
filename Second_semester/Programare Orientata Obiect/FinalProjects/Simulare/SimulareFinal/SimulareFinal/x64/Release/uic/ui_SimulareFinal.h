/********************************************************************************
** Form generated from reading UI file 'SimulareFinal.ui'
**
** Created by: Qt User Interface Compiler version 6.3.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SIMULAREFINAL_H
#define UI_SIMULAREFINAL_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SimulareFinalClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *SimulareFinalClass)
    {
        if (SimulareFinalClass->objectName().isEmpty())
            SimulareFinalClass->setObjectName(QString::fromUtf8("SimulareFinalClass"));
        SimulareFinalClass->resize(600, 400);
        menuBar = new QMenuBar(SimulareFinalClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        SimulareFinalClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(SimulareFinalClass);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        SimulareFinalClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(SimulareFinalClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        SimulareFinalClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(SimulareFinalClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        SimulareFinalClass->setStatusBar(statusBar);

        retranslateUi(SimulareFinalClass);

        QMetaObject::connectSlotsByName(SimulareFinalClass);
    } // setupUi

    void retranslateUi(QMainWindow *SimulareFinalClass)
    {
        SimulareFinalClass->setWindowTitle(QCoreApplication::translate("SimulareFinalClass", "SimulareFinal", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SimulareFinalClass: public Ui_SimulareFinalClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SIMULAREFINAL_H
