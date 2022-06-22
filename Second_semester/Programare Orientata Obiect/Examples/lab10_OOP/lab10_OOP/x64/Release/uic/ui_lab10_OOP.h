/********************************************************************************
** Form generated from reading UI file 'lab10_OOP.ui'
**
** Created by: Qt User Interface Compiler version 6.3.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LAB10_OOP_H
#define UI_LAB10_OOP_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_lab10_OOPClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *lab10_OOPClass)
    {
        if (lab10_OOPClass->objectName().isEmpty())
            lab10_OOPClass->setObjectName(QString::fromUtf8("lab10_OOPClass"));
        lab10_OOPClass->resize(600, 400);
        menuBar = new QMenuBar(lab10_OOPClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        lab10_OOPClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(lab10_OOPClass);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        lab10_OOPClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(lab10_OOPClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        lab10_OOPClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(lab10_OOPClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        lab10_OOPClass->setStatusBar(statusBar);

        retranslateUi(lab10_OOPClass);

        QMetaObject::connectSlotsByName(lab10_OOPClass);
    } // setupUi

    void retranslateUi(QMainWindow *lab10_OOPClass)
    {
        lab10_OOPClass->setWindowTitle(QCoreApplication::translate("lab10_OOPClass", "lab10_OOP", nullptr));
    } // retranslateUi

};

namespace Ui {
    class lab10_OOPClass: public Ui_lab10_OOPClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LAB10_OOP_H
