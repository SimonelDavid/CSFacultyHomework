/********************************************************************************
** Form generated from reading UI file 'PetstoreModelView.ui'
**
** Created by: Qt User Interface Compiler version 6.3.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PETSTOREMODELVIEW_H
#define UI_PETSTOREMODELVIEW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_PetstoreModelViewClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *PetstoreModelViewClass)
    {
        if (PetstoreModelViewClass->objectName().isEmpty())
            PetstoreModelViewClass->setObjectName(QString::fromUtf8("PetstoreModelViewClass"));
        PetstoreModelViewClass->resize(600, 400);
        menuBar = new QMenuBar(PetstoreModelViewClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        PetstoreModelViewClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(PetstoreModelViewClass);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        PetstoreModelViewClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(PetstoreModelViewClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        PetstoreModelViewClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(PetstoreModelViewClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        PetstoreModelViewClass->setStatusBar(statusBar);

        retranslateUi(PetstoreModelViewClass);

        QMetaObject::connectSlotsByName(PetstoreModelViewClass);
    } // setupUi

    void retranslateUi(QMainWindow *PetstoreModelViewClass)
    {
        PetstoreModelViewClass->setWindowTitle(QCoreApplication::translate("PetstoreModelViewClass", "PetstoreModelView", nullptr));
    } // retranslateUi

};

namespace Ui {
    class PetstoreModelViewClass: public Ui_PetstoreModelViewClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PETSTOREMODELVIEW_H
