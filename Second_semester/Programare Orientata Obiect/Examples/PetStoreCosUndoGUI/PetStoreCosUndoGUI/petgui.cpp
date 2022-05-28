#include "petgui.h"
#include "pet.h"
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMessageBox>
#include <qpalette.h>
#include <qbrush.h>
#include<qdebug.h>
#include <string>
#include <algorithm>

void PetStoreGUI::initGUICmps() {	
	setLayout(lyMain);

	//adaug lista si sub doua butoane de sort
	QWidget* widDreapta = new QWidget;
	QVBoxLayout* vl = new QVBoxLayout;
	widDreapta->setLayout(vl);
	lst = new QTableWidget;
	vl->addWidget(lst);
	
	QWidget* widBtnDreapta = new QWidget;
	QHBoxLayout* lyBtnsDr = new QHBoxLayout;
	widBtnDreapta->setLayout(lyBtnsDr);
	btnSortByPrice = new QPushButton("Sort by price");
	lyBtnsDr->addWidget(btnSortByPrice);
	
	btnSortByType = new QPushButton("Sort by type");
	lyBtnsDr->addWidget(btnSortByType);
	vl->addWidget(widBtnDreapta);
	lyMain->addWidget(widDreapta);

	//fac un form pentru detalii
	QWidget* widDetalii = new QWidget;
	QFormLayout* formLDetalii = new QFormLayout;
	widDetalii->setLayout(formLDetalii);
	txtSpecies = new QLineEdit;
	formLDetalii->addRow(new QLabel("Species:"),txtSpecies);
	txtType = new QLineEdit;
	formLDetalii->addRow(new QLabel("Type:"), txtType);
	txtPrice = new QLineEdit;
	formLDetalii->addRow(new QLabel("Price:"), txtPrice);

	btnAdd = new QPushButton("Add pet");
	
	formLDetalii->addWidget(btnAdd);

	lyMain->addWidget(widDetalii);
	
	btnDyn->setLayout(lyBtnDy);
	lyMain->addWidget(btnDyn);
	
}

void PetStoreGUI::connectSignalsSlots() {
	//cand se emite semnalul clicked de pe buton reincarc lista
	QObject::connect(btnSortByPrice, &QPushButton::clicked, [&]() {		
		qDebug() << "am ajuns aici!!!";
		reloadList(ctr.getSortByPrice());
	});
	//cand se emite semnalul clicked de pe buton reincarc lista
	QObject::connect(btnSortByType, &QPushButton::clicked, [&]() {
		reloadList(ctr.getSortByType());
	});
	QObject::connect(btnAdd, &QPushButton::clicked, this, &PetStoreGUI::addNewPet);

	QObject::connect(lst, &QTableWidget::itemSelectionChanged, [&]() {
		auto sel = lst->selectedItems();
		if (sel.isEmpty()) {
			txtSpecies->setText("");
			txtType->setText("");
			txtPrice->setText("");
		}
		else {
			auto selItem = sel.at(0);
			auto species = selItem->text();
			auto type = selItem->data(Qt::UserRole).toString();
			txtSpecies->setText(species);
			txtType->setText(type);
			auto p = ctr.find(type.toStdString(), species.toStdString());
			txtPrice->setText(QString::number(p.getPrice()));
		}
		});
}

void PetStoreGUI::addNewPet() {
	try {
		ctr.add(txtType->text().toStdString(), txtSpecies->text().toStdString(), txtPrice->text().toDouble());
		reloadList(ctr.getAllPets());	
	}
	catch (PetException& ex) {
		QMessageBox::warning(this, "Warning", QString::fromStdString(ex.getMsg()));
	}
}

void PetStoreGUI::adaugaButoane(const std::vector<Pet>& pets) {	
	for (const auto& p : pets) {
		if (p.getType() == "Pasare") {
			auto btn = new QPushButton{ QString::fromStdString(p.getSpecies()) };
			lyBtnDy->addWidget(btn);
			QObject::connect(btn, &QPushButton::clicked, [this,btn,p]() {
				QMessageBox::information(nullptr,"Info", QString::number(p.getPrice()));
				delete btn;
			});
		}
	}
	
}

void PetStoreGUI::reloadList(const std::vector<Pet>& pets) {	
	lst->clear();
	for (const auto& p : pets) {
		QListWidgetItem* item = new QListWidgetItem(QString::fromStdString(p.getSpecies()));		
		item->setData(Qt::UserRole, QString::fromStdString(p.getType()));
		if (p.getPrice() > 100) {
			item->setData(Qt::BackgroundRole, QBrush{ Qt::red, Qt::SolidPattern });
		}
		lst->addItem(item);

	}
}