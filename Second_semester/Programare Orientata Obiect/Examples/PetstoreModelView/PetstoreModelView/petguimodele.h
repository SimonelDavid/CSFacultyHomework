#pragma once
#include <qwidget.h>
#include <qlistwidget.h>
#include <qlistview.h>
#include <qpushbutton.h>
#include <qlabel.h>
#include <qlineedit.h>
#include <qtablewidget.h>
#include "petcontroller.h"
#include "pet.h"
#include <vector>
#include <MyTableModel.h>

class PetStoreGUIModele : public QWidget {
private:
	PetService& ctr;
	MyTableModel* model;
	QLabel* lblCate = new QLabel{ "Cate:" };
	QListView* lstV;

	QTableView* tblV = new QTableView;

	QPushButton* btnSortByPrice;
	QPushButton* btnSortByType;

	QLineEdit* txtSpecies;
	QLineEdit* txtType;
	QLineEdit* txtPrice;
	QPushButton* btnAdd;

	QPushButton* btnGenereaza10000;
	
	void initGUICmps();
	void connectSignalsSlots();
	void reloadList(std::vector<Pet> pets);
	void addNewPet();
public:
	PetStoreGUIModele(PetService& ctr) :ctr{ ctr } {
		initGUICmps();
		model = new MyTableModel{ ctr.getAllPets() };
		lstV->setModel(model);
		tblV->setModel(model);		
		connectSignalsSlots();		
	}

};