#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Melodii_rank.h"

class Melodii_rank : public QMainWindow
{
    Q_OBJECT

public:
    Melodii_rank(QWidget *parent = nullptr);
    ~Melodii_rank();

private:
    Ui::Melodii_rankClass ui;
};
