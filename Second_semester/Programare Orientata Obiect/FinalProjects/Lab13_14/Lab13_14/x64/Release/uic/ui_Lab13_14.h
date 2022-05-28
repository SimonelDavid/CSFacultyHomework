/********************************************************************************
** Form generated from reading UI file 'Lab13_14.ui'
**
** Created by: Qt User Interface Compiler version 6.3.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LAB13_14_H
#define UI_LAB13_14_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Lab13_14Class
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *Lab13_14Class)
    {
        if (Lab13_14Class->objectName().isEmpty())
            Lab13_14Class->setObjectName(QString::fromUtf8("Lab13_14Class"));
        Lab13_14Class->resize(600, 400);
        menuBar = new QMenuBar(Lab13_14Class);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        Lab13_14Class->setMenuBar(menuBar);
        mainToolBar = new QToolBar(Lab13_14Class);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        Lab13_14Class->addToolBar(mainToolBar);
        centralWidget = new QWidget(Lab13_14Class);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        Lab13_14Class->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(Lab13_14Class);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        Lab13_14Class->setStatusBar(statusBar);

        retranslateUi(Lab13_14Class);

        QMetaObject::connectSlotsByName(Lab13_14Class);
    } // setupUi

    void retranslateUi(QMainWindow *Lab13_14Class)
    {
        Lab13_14Class->setWindowTitle(QCoreApplication::translate("Lab13_14Class", "Lab13_14", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Lab13_14Class: public Ui_Lab13_14Class {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LAB13_14_H
