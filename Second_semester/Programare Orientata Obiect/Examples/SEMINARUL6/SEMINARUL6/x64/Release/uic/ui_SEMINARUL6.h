/********************************************************************************
** Form generated from reading UI file 'SEMINARUL6.ui'
**
** Created by: Qt User Interface Compiler version 6.3.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SEMINARUL6_H
#define UI_SEMINARUL6_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SEMINARUL6Class
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *SEMINARUL6Class)
    {
        if (SEMINARUL6Class->objectName().isEmpty())
            SEMINARUL6Class->setObjectName(QString::fromUtf8("SEMINARUL6Class"));
        SEMINARUL6Class->resize(600, 400);
        menuBar = new QMenuBar(SEMINARUL6Class);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        SEMINARUL6Class->setMenuBar(menuBar);
        mainToolBar = new QToolBar(SEMINARUL6Class);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        SEMINARUL6Class->addToolBar(mainToolBar);
        centralWidget = new QWidget(SEMINARUL6Class);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        SEMINARUL6Class->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(SEMINARUL6Class);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        SEMINARUL6Class->setStatusBar(statusBar);

        retranslateUi(SEMINARUL6Class);

        QMetaObject::connectSlotsByName(SEMINARUL6Class);
    } // setupUi

    void retranslateUi(QMainWindow *SEMINARUL6Class)
    {
        SEMINARUL6Class->setWindowTitle(QCoreApplication::translate("SEMINARUL6Class", "SEMINARUL6", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SEMINARUL6Class: public Ui_SEMINARUL6Class {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SEMINARUL6_H
