#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_SimulareFinal.h"

class SimulareFinal : public QMainWindow
{
    Q_OBJECT

public:
    SimulareFinal(QWidget *parent = Q_NULLPTR);

private:
    Ui::SimulareFinalClass ui;
};
