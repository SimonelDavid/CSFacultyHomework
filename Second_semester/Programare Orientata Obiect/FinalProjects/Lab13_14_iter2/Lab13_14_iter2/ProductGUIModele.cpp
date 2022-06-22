#pragma once
#include "ProductGUIModel.h"

#include "ProductGUI.h"

void ProductGUIModel::initializeGUIComponents() {

	//impartim fereastra in 2: in stanga, butoane+labels+qlineedits
	//iar in dreapta: tabelul cu melodii

	//"stanga" si "dreapta" pentru ca este QHBoxLayout
	//se adauga componente incepand din stanga, pe orizontala
	//aici: "left" component, then "right" component
	//care la randul lor contin alte componente

	//main layout
	QHBoxLayout* lyMain = new QHBoxLayout;
	this->setLayout(lyMain);


	//left part of the window
	//pentru aceasta parte setam layout vertical
	QWidget* left = new QWidget;
	QVBoxLayout* lyLeft = new QVBoxLayout;
	left->setLayout(lyLeft);

	//componente pentru functionalitatea de adaugare a unei melodii
	//folosim un QFormLayout pentru detaliile de adaugare a unei melodii
	QWidget* form = new QWidget;
	QFormLayout* lyForm = new QFormLayout;
	form->setLayout(lyForm);
	editDenumire = new QLineEdit;
	editPret = new QLineEdit;
	editProducator = new QLineEdit;
	editSubstanta = new QLineEdit;

	lyForm->addRow(lblDenumire, editDenumire);
	lyForm->addRow(lblPret, editPret);
	lyForm->addRow(lblProducator, editProducator);
	lyForm->addRow(lblSubst, editSubstanta);
	btnAddSong = new QPushButton("Adauga medicament");
	lyForm->addWidget(btnAddSong);

	//adaugam toate componentele legate de adaugare melodie
	//in layout-ul care corespunde partii din stanga a ferestrei
	lyLeft->addWidget(form);


	//Radio Buttons: ne ajuta cand trebuie sa selectam doar o 
	//optiune din mai multe (doar un RadioButton poate fi selectat
	//la un moment dat)


	//vs. CheckBox (see documentation)
	//also see documentation on QGroupBox, QRadioButton pentru detalii

	//cream un GroupBox pentru radiobuttons care corespund 
	//criteriilor de sortare pe care le avem (dupa pret+titlu 
	//si substanta) + butonul de sortare

	QVBoxLayout* lyRadioBox = new QVBoxLayout;
	this->groupBox->setLayout(lyRadioBox);
	lyRadioBox->addWidget(radioSrtPretSubtanta);
	lyRadioBox->addWidget(radioSrtDenumire);

	btnSortMeds = new QPushButton("Sorteaza medicamente");
	lyRadioBox->addWidget(btnSortMeds);

	//adaugam acest grup in partea stanga, 
	//dupa componentele pentru adaugare in layout-ul vertical
	lyLeft->addWidget(groupBox);

	//cream un form pentru filtrarea dupa producator 
	QWidget* formFilter = new QWidget;
	QFormLayout* lyFormFilter = new QFormLayout;
	formFilter->setLayout(lyFormFilter);
	editFilterGen = new QLineEdit();
	lyFormFilter->addRow(lblFilterCriteria, editFilterGen);
	btnFilterMeds = new QPushButton("Filtreaza melodii dupa producator");
	lyFormFilter->addWidget(btnFilterMeds);

	lyLeft->addWidget(formFilter);

	//Buton folosit pentru a reincarca datele
	//i.e. afisam toate melodiile in tabel, in ordinea initiala din fisier
	btnReloadData = new QPushButton("Reload data");
	lyLeft->addWidget(btnReloadData);


	//componenta right - contine doar tabelul cu melodii
	QWidget* right = new QWidget;
	QVBoxLayout* lyRight = new QVBoxLayout;
	right->setLayout(lyRight);

	/*int noLines = 10;
	int noColumns = 4;
	this->tableMeds = new QTableWidget{ noLines, noColumns };*/

	//setam header-ul tabelului
	/*QStringList tblHeaderList;
	tblHeaderList << "Titlu" << "Artist" << "Gen" << "Durata";
	this->tableMeds->setHorizontalHeader(tblHeaderList);*/

	//optiune pentru a se redimensiona celulele din tabel in functie de continut
	//this->tableMeds->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
	btnReteta = new QPushButton{ "Deschide reteta" };
	lyLeft->addWidget(btnReteta);
	lyRight->addWidget(tableMeds);

	lyMain->addWidget(left);
	lyMain->addWidget(right);



}
void ProductGUIModel::reloadSongList(vector<Medicament> songs) {
	this->model->setSongs(songs);
}

void ProductGUIModel::connectSignalsSlots() {
	QObject::connect(btnAddSong, &QPushButton::clicked, this, &ProductGUIModel::guiAddSong);

	QObject::connect(btnSortMeds, &QPushButton::clicked, [&]() {
		if (this->radioSrtPretSubtanta->isChecked())
			this->reloadSongList(srv.sortBySubstantaSiPret());
		else if (this->radioSrtDenumire->isChecked())
			this->reloadSongList(srv.sortByDenumire());
		});
	//selectia in tabel
	QObject::connect(tableMeds->selectionModel(), &QItemSelectionModel::selectionChanged, [this]() {
		if (tableMeds->selectionModel()->selectedIndexes().isEmpty()) {
			editDenumire->setText("");
			editPret->setText("");
			return;
		}
		int selRow = tableMeds->selectionModel()->selectedIndexes().at(0).row();
		auto cel0Index = tableMeds->model()->index(selRow, 0);
		auto cel1Index = tableMeds->model()->index(selRow, 1);
		auto cellValue1 = tableMeds->model()->data(cel0Index, Qt::DisplayRole).toString();
		auto cellValue2 = tableMeds->model()->data(cel1Index, Qt::DisplayRole).toString();

		editDenumire->setText(cellValue1);
		editPret->setText(cellValue2);
		});
	/*
	QObject::connect(btnFilterMeds, &QPushButton::clicked, [&]() {
		string pret = this->editFilterGen->text().toDouble();
		this->reloadSongList(srv.filterMeds(pret, subst, criteriu));
		});
	*/
	QObject::connect(btnReloadData, &QPushButton::clicked, [&]() {
		this->reloadSongList(srv.getMeds());
		});
	QObject::connect(btnReteta, &QPushButton::clicked, [&]() {

		playlistWindow.show();
		});


}


void ProductGUIModel::guiAddSong() {
	try {
		//preluare detalii din QLineEdit-uri
		string denumire = editDenumire->text().toStdString();
		double pret = editPret->text().toDouble();
		string producator = editProducator->text().toStdString();
		int substanta = editSubstanta->text().toInt();

		//optional - golim QLineEdit-urile dupa apasarea butonului
		editDenumire->clear();
		editPret->clear();
		editProducator->clear();
		editSubstanta->clear();

		this->srv.addMed(denumire, producator, pret, substanta);
		this->reloadSongList(this->srv.getMeds());

		//afisam un mesaj pentru a anunta utilizatorul ca melodia s-a adaugat
		QMessageBox::information(this, "Info", QString::fromStdString("Medicament adaugat cu succes."));

	}
	catch (ValidateException& ve) {
		QMessageBox::warning(this, "Warning", "Date invalide");
	}


}