#include "petgui.h"
#include "pet.h"
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMessageBox>
#include <string>
void PetStoreGUI::initGUICmps() {
	QHBoxLayout* ly = new QHBoxLayout;
	setLayout(ly);

	//adaug lista si sub doua butoane de sort
	QWidget* widDreapta = new QWidget;
	QVBoxLayout* vl = new QVBoxLayout;
	widDreapta->setLayout(vl);
	
	vl->addWidget(lblCate);
	lst = new QListWidget;
	vl->addWidget(lst);
	
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
	formLDetalii->addRow(new QLabel("Species:"),txtSpecies);
	txtType = new QLineEdit;
	formLDetalii->addRow(new QLabel("Type:"), txtType);
	txtPrice = new QLineEdit;
	formLDetalii->addRow(new QLabel("Price:"), txtPrice);

	btnAdd = new QPushButton("Add pet");
	formLDetalii->addWidget(btnAdd);
	lyDreapta->addWidget(widDetalii);

	

	btnAddToCos = new QPushButton("Add to cos");
	lyDreapta->addWidget(btnAddToCos);
	btnPickRandom = new QPushButton("Pick random");
	lyDreapta->addWidget(btnPickRandom);
	btnClearCos = new QPushButton("Clear cos");
	lyDreapta->addWidget(btnClearCos);


	btnGenereaza10000 = new QPushButton("Genereaza 1000");
	lyDreapta->addWidget(btnGenereaza10000);

	ly->addWidget(widDreapta2);
	
}


void PetStoreGUI::connectSignalsSlots() {
	//cand se emite semnalul clicked de pe buton reincarc lista
	QObject::connect(btnSortByPrice, &QPushButton::clicked, [&]() {
		reloadList(ctr.getSortByPrice());
	});
	//cand se emite semnalul clicked de pe buton reincarc lista
	QObject::connect(btnSortByType, &QPushButton::clicked, [&]() {
		reloadList(ctr.getSortByType());
	});
	//cand se selecteaza elementul din lista incarc detaliile	
	QObject::connect(lst->selectionModel(), &QItemSelectionModel::selectionChanged, [&]() {
		if (lst->selectionModel()->selectedIndexes().isEmpty()) {
			//nu este nimic selectat (golesc detaliile)
			txtSpecies->setText("");
			txtType->setText("");
			txtPrice->setText("");
			return;
		}
		auto selIndex = lst->selectionModel()->selectedIndexes().at(0);		
		QString species = selIndex.data(Qt::DisplayRole).toString();
		txtSpecies->setText(species);		
		QString type = selIndex.data(Qt::UserRole).toString();
		txtType->setText(type);
		try {
			//cautam Pet
			Pet p = ctr.find(species.toStdString(), type.toStdString());
			txtPrice->setText(QString::number(p.getPrice()));
		}
		catch (PetException& ex) {
			QMessageBox::warning(nullptr, "Warning", QString::fromStdString(ex.getMsg()));
		}
	});
	QObject::connect(btnAdd, &QPushButton::clicked, this, &PetStoreGUI::addNewPet);
	//butoane legate de cos
	QObject::connect(lst->selectionModel(), &QItemSelectionModel::selectionChanged, [&]() {
		btnAddToCos->setEnabled(!lst->selectionModel()->selectedIndexes().isEmpty());
	});

	QObject::connect(btnAddToCos, &QPushButton::clicked, [&]() {

	});
	
	QObject::connect(btnPickRandom, &QPushButton::clicked, [&]() {
		ctr.addRandom(5);
	});
	QObject::connect(btnClearCos, &QPushButton::clicked, [&]() {
		ctr.golesteCos();
	});

	QObject::connect(btnGenereaza10000, &QPushButton::clicked, [&]() {
		ctr.genereazaAleatorAnimale(100000);
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
void PetStoreGUI::reloadList(std::vector<Pet> pets) {
	lblCate->setText(QString{ "Cate:" }+QString::number(pets.size()));	
	lst->clear();
	for (const auto& p : pets) {
		auto item = new QListWidgetItem{ QString::fromStdString(p.getSpecies()) };
		item->setData(Qt::UserRole, QString::fromStdString(p.getType()));
		lst->addItem(item);
	}
}