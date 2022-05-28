/********************************************************************************
** Form generated from reading UI file 'Simulare_OOP.ui'
**
** Created by: Qt User Interface Compiler version 6.3.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SIMULARE_OOP_H
#define UI_SIMULARE_OOP_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Simulare_OOPClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *Simulare_OOPClass)
    {
        if (Simulare_OOPClass->objectName().isEmpty())
            Simulare_OOPClass->setObjectName(QString::fromUtf8("Simulare_OOPClass"));
        Simulare_OOPClass->resize(600, 400);
        menuBar = new QMenuBar(Simulare_OOPClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        Simulare_OOPClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(Simulare_OOPClass);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        Simulare_OOPClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(Simulare_OOPClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        Simulare_OOPClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(Simulare_OOPClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        Simulare_OOPClass->setStatusBar(statusBar);

        retranslateUi(Simulare_OOPClass);

        QMetaObject::connectSlotsByName(Simulare_OOPClass);
    } // setupUi

    void retranslateUi(QMainWindow *Simulare_OOPClass)
    {
        Simulare_OOPClass->setWindowTitle(QCoreApplication::translate("Simulare_OOPClass", "Simulare_OOP", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Simulare_OOPClass: public Ui_Simulare_OOPClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SIMULARE_OOP_H
