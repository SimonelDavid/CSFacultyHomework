#include "petguimodele.h"
#include "pet.h"
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMessageBox>
#include <string>
#include "MyListModel.h"
#include "MyTableModel.h"
void PetStoreGUIModele::initGUICmps() {
	QHBoxLayout* ly = new QHBoxLayout;
	setLayout(ly);

	//adaug lista si sub doua butoane de sort
	QWidget* widDreapta = new QWidget;
	QVBoxLayout* vl = new QVBoxLayout;
	widDreapta->setLayout(vl);

	vl->addWidget(lblCate);

	lstV = new QListView;
	lstV->setUniformItemSizes(true);
	vl->addWidget(lstV);


	QWidget* widBtnDreapta = new QWidget;
	QHBoxLayout* lyBtnsDr = new QHBoxLayout;
	widBtnDreapta->setLayout(lyBtnsDr);
	btnSortByPrice = new QPushButton("Sort by price");
	lyBtnsDr->addWidget(btnSortByPrice);

	btnSortByType = new QPushButton("Sort by type");
	lyBtnsDr->addWidget(btnSortByType);
	vl->addWidget(widBtnDreapta);
	ly->addWidget(widDreapta);

	QWidget* widDreapta2 = new QWidget;
	QVBoxLayout *lyDreapta = new QVBoxLayout;
	widDreapta2->setLayout(lyDreapta);

	//fac un form pentru detalii
	QWidget* widDetalii = new QWidget;
	QFormLayout* formLDetalii = new QFormLayout;
	widDetalii->setLayout(formLDetalii);
	txtSpecies = new QLineEdit;
	formLDetalii->addRow(new QLabel("Species:"), txtSpecies);
	txtType = new QLineEdit;
	formLDetalii->addRow(new QLabel("Type:"), txtType);
	txtPrice = new QLineEdit;
	formLDetalii->addRow(new QLabel("Price:"), txtPrice);

	btnAdd = new QPushButton("Add pet");
	formLDetalii->addWidget(btnAdd);
	lyDreapta->addWidget(widDetalii);



	btnGenereaza10000 = new QPushButton("Genereaza 10000");
	lyDreapta->addWidget(btnGenereaza10000);

	ly->addWidget(widDreapta2);

	ly->addWidget(tblV);

}


void PetStoreGUIModele::connectSignalsSlots() {
	//cand se emite semnalul clicked de pe buton reincarc lista
	QObject::connect(btnSortByPrice, &QPushButton::clicked, [&]() {
		reloadList(ctr.getSortByPrice());
	});
	//cand se emite semnalul clicked de pe buton reincarc lista
	QObject::connect(btnSortByType, &QPushButton::clicked, [&]() {
		reloadList(ctr.getSortByType());
	});
	
	QObject::connect(btnAdd, &QPushButton::clicked, this, &PetStoreGUIModele::addNewPet);

	QObject::connect(btnGenereaza10000, &QPushButton::clicked, [&]() {
		ctr.genereazaAleatorAnimale(1000);
	});
	//selectia in tabel
	QObject::connect(tblV->selectionModel(), &QItemSelectionModel::selectionChanged, [this]() {
		if (tblV->selectionModel()->selectedIndexes().isEmpty()) {
			txtSpecies->setText("");
			txtType->setText("");
			txtPrice->setText("");
			return;
		}
		int selRow = tblV->selectionModel()->selectedIndexes().at(0).row();
		auto cel0Index = tblV->model()->index(selRow, 0);		
		auto cel0Value= tblV->model()->data(cel0Index, Qt::DisplayRole).toString();		
		txtSpecies->setText(cel0Value);
		auto cel1Index = tblV->model()->index(selRow, 1);
		auto cel1Value = tblV->model()->data(cel1Index, Qt::DisplayRole).toString();
		txtType->setText(cel1Value);
		auto cel2Index = tblV->model()->index(selRow, 2);
		auto cel2Value = tblV->model()->data(cel2Index, Qt::DisplayRole).toString();
		txtPrice->setText(cel2Value);
	});
}

void PetStoreGUIModele::addNewPet() {
	try {
		ctr.add(txtType->text().toStdString(), txtSpecies->text().toStdString(), txtPrice->text().toDouble());
		reloadList(ctr.getAllPets());
	}
	catch (PetException& ex) {
		QMessageBox::warning(this, "Warning", QString::fromStdString(ex.getMsg()));
	}
}
void PetStoreGUIModele::reloadList(std::vector<Pet> pets) {
	lblCate->setText(QString{ "Cate:" }+QString::number(pets.size()));
	model->setPets(pets);	
}