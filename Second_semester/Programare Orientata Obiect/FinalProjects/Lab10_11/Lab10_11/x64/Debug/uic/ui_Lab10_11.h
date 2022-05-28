/********************************************************************************
** Form generated from reading UI file 'Lab10_11.ui'
**
** Created by: Qt User Interface Compiler version 6.3.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LAB10_11_H
#define UI_LAB10_11_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Lab10_11Class
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *Lab10_11Class)
    {
        if (Lab10_11Class->objectName().isEmpty())
            Lab10_11Class->setObjectName(QString::fromUtf8("Lab10_11Class"));
        Lab10_11Class->resize(600, 400);
        menuBar = new QMenuBar(Lab10_11Class);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        Lab10_11Class->setMenuBar(menuBar);
        mainToolBar = new QToolBar(Lab10_11Class);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        Lab10_11Class->addToolBar(mainToolBar);
        centralWidget = new QWidget(Lab10_11Class);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        Lab10_11Class->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(Lab10_11Class);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        Lab10_11Class->setStatusBar(statusBar);

        retranslateUi(Lab10_11Class);

        QMetaObject::connectSlotsByName(Lab10_11Class);
    } // setupUi

    void retranslateUi(QMainWindow *Lab10_11Class)
    {
        Lab10_11Class->setWindowTitle(QCoreApplication::translate("Lab10_11Class", "Lab10_11", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Lab10_11Class: public Ui_Lab10_11Class {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LAB10_11_H
