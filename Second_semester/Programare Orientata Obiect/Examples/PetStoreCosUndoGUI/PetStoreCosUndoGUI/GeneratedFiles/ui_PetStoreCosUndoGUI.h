/********************************************************************************
** Form generated from reading UI file 'PetStoreCosUndoGUI.ui'
**
** Created by: Qt User Interface Compiler version 6.3.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PETSTORECOSUNDOGUI_H
#define UI_PETSTORECOSUNDOGUI_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_PetStoreCosUndoGUIClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *PetStoreCosUndoGUIClass)
    {
        if (PetStoreCosUndoGUIClass->objectName().isEmpty())
            PetStoreCosUndoGUIClass->setObjectName(QString::fromUtf8("PetStoreCosUndoGUIClass"));
        PetStoreCosUndoGUIClass->resize(600, 400);
        menuBar = new QMenuBar(PetStoreCosUndoGUIClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        PetStoreCosUndoGUIClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(PetStoreCosUndoGUIClass);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        PetStoreCosUndoGUIClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(PetStoreCosUndoGUIClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        PetStoreCosUndoGUIClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(PetStoreCosUndoGUIClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        PetStoreCosUndoGUIClass->setStatusBar(statusBar);

        retranslateUi(PetStoreCosUndoGUIClass);

        QMetaObject::connectSlotsByName(PetStoreCosUndoGUIClass);
    } // setupUi

    void retranslateUi(QMainWindow *PetStoreCosUndoGUIClass)
    {
        PetStoreCosUndoGUIClass->setWindowTitle(QCoreApplication::translate("PetStoreCosUndoGUIClass", "PetStoreCosUndoGUI", nullptr));
    } // retranslateUi

};

namespace Ui {
    class PetStoreCosUndoGUIClass: public Ui_PetStoreCosUndoGUIClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PETSTORECOSUNDOGUI_H
