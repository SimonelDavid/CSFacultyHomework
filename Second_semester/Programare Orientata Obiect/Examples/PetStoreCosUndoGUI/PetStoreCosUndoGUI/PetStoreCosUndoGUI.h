#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_PetStoreCosUndoGUI.h"

class PetStoreCosUndoGUI : public QMainWindow
{
	Q_OBJECT

public:
	PetStoreCosUndoGUI(QWidget *parent = Q_NULLPTR);

private:
	Ui::PetStoreCosUndoGUIClass ui;
};
