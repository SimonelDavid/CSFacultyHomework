#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_TaskManager.h"

class TaskManager : public QMainWindow
{
    Q_OBJECT

public:
    TaskManager(QWidget *parent = nullptr);
    ~TaskManager();

private:
    Ui::TaskManagerClass ui;
};
