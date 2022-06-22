#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_PetstoreModelView.h"

class PetstoreModelView : public QMainWindow
{
	Q_OBJECT

public:
	PetstoreModelView(QWidget *parent = Q_NULLPTR);

private:
	Ui::PetstoreModelViewClass ui;
};
