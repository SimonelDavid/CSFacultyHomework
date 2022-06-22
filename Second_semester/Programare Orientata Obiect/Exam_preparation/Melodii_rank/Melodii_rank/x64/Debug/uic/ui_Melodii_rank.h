/********************************************************************************
** Form generated from reading UI file 'Melodii_rank.ui'
**
** Created by: Qt User Interface Compiler version 6.3.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MELODII_RANK_H
#define UI_MELODII_RANK_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Melodii_rankClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *Melodii_rankClass)
    {
        if (Melodii_rankClass->objectName().isEmpty())
            Melodii_rankClass->setObjectName(QString::fromUtf8("Melodii_rankClass"));
        Melodii_rankClass->resize(600, 400);
        menuBar = new QMenuBar(Melodii_rankClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        Melodii_rankClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(Melodii_rankClass);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        Melodii_rankClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(Melodii_rankClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        Melodii_rankClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(Melodii_rankClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        Melodii_rankClass->setStatusBar(statusBar);

        retranslateUi(Melodii_rankClass);

        QMetaObject::connectSlotsByName(Melodii_rankClass);
    } // setupUi

    void retranslateUi(QMainWindow *Melodii_rankClass)
    {
        Melodii_rankClass->setWindowTitle(QCoreApplication::translate("Melodii_rankClass", "Melodii_rank", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Melodii_rankClass: public Ui_Melodii_rankClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MELODII_RANK_H
