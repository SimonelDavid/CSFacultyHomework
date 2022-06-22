#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_lab10_OOP.h"

class lab10_OOP : public QMainWindow
{
    Q_OBJECT

public:
    lab10_OOP(QWidget *parent = Q_NULLPTR);

private:
    Ui::lab10_OOPClass ui;
};
