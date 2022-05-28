/********************************************************************************
** Form generated from reading UI file 'Exercitiu_1.ui'
**
** Created by: Qt User Interface Compiler version 6.3.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EXERCITIU_1_H
#define UI_EXERCITIU_1_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Exercitiu_1Class
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *Exercitiu_1Class)
    {
        if (Exercitiu_1Class->objectName().isEmpty())
            Exercitiu_1Class->setObjectName(QString::fromUtf8("Exercitiu_1Class"));
        Exercitiu_1Class->resize(600, 400);
        menuBar = new QMenuBar(Exercitiu_1Class);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        Exercitiu_1Class->setMenuBar(menuBar);
        mainToolBar = new QToolBar(Exercitiu_1Class);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        Exercitiu_1Class->addToolBar(mainToolBar);
        centralWidget = new QWidget(Exercitiu_1Class);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        Exercitiu_1Class->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(Exercitiu_1Class);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        Exercitiu_1Class->setStatusBar(statusBar);

        retranslateUi(Exercitiu_1Class);

        QMetaObject::connectSlotsByName(Exercitiu_1Class);
    } // setupUi

    void retranslateUi(QMainWindow *Exercitiu_1Class)
    {
        Exercitiu_1Class->setWindowTitle(QCoreApplication::translate("Exercitiu_1Class", "Exercitiu_1", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Exercitiu_1Class: public Ui_Exercitiu_1Class {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EXERCITIU_1_H
