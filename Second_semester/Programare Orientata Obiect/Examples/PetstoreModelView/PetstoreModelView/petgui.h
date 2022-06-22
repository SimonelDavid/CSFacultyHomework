#pragma once
#include <qwidget.h>
#include <qlistwidget.h>
#include <qpushbutton.h>
#include <qlabel.h>
#include <qlineedit.h>
#include <qtableview.h>
#include "petcontroller.h"
#include "pet.h"
#include <vector>
#include "MyListModel.h"

class PetStoreGUI : public QWidget{
private:	
	PetService& ctr;
	QLabel *lblCate = new QLabel("Cate:0");
	QListWidget* lst;

	QPushButton* btnSortByPrice;
	QPushButton* btnSortByType;

	QLineEdit* txtSpecies;
	QLineEdit* txtType;
	QLineEdit* txtPrice;
	QPushButton* btnAdd;

	QPushButton* btnAddToCos;
	QPushButton* btnPickRandom;
	QPushButton* btnClearCos;

	QPushButton* btnGenereaza10000;
	void initGUICmps();
	void connectSignalsSlots();
	void reloadList(std::vector<Pet> pets);
	void addNewPet();
public:
	PetStoreGUI(PetService& ctr) :ctr{ ctr } {
		initGUICmps();		
		lst->setUniformItemSizes(true);
		reloadList(ctr.getAllPets());
		connectSignalsSlots();		
	}

};