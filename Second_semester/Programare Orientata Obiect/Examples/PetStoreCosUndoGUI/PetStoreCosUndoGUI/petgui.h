#pragma once
#include <qwidget.h>
#include <qlistwidget.h>
#include <qpushbutton.h>
#include <qlineedit.h>
#include <qboxlayout.h>
#include <qdebug.h>
#include "petservice.h"
#include "pet.h"
#include <vector>
#include <qlabel.h>
#include <qtablewidget.h>
class SmallGUI : public QWidget {
private:
	QLabel* lbl = new QLabel("Nimic");
public:
	SmallGUI() {
		QHBoxLayout* ly = new QHBoxLayout;
		setLayout(ly);
		ly->addWidget(lbl);
	}

	void setPet(const Pet&p) {
		lbl->setText(QString::fromStdString( p.getSpecies()));
	}
};


class PetStoreGUI : public QWidget{
private:
	PetService& ctr;
	QHBoxLayout* lyMain = new QHBoxLayout;
	QTableWidget* lst;
	QPushButton* btnSortByPrice;
	QPushButton* btnSortByType;
	QLineEdit* txtSpecies;
	QLineEdit* txtType;
	QLineEdit* txtPrice;
	QPushButton* btnAdd;
	QVBoxLayout* lyBtnDy = new QVBoxLayout;
	QWidget* btnDyn = new QWidget;

	

	void initGUICmps();	
	void connectSignalsSlots();
	void reloadList(const std::vector<Pet>& pets);
	void addNewPet();
	void adaugaButoane(const std::vector<Pet>& pets);
public:
	PetStoreGUI(PetService& ctr) :ctr{ ctr } {
		initGUICmps();
		connectSignalsSlots();
		reloadList(ctr.getAllPets());
		adaugaButoane(ctr.getAllPets());
	}

};