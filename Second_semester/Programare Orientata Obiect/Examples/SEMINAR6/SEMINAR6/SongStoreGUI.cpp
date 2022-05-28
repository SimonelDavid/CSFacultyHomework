#include "SongStoreGUI.h"

void SongStoreGUI::initializeGUIComponents() {

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
	editTitlu = new QLineEdit;
	editArtist = new QLineEdit;
	editGen = new QLineEdit;
	editDurata = new QLineEdit;

	lyForm->addRow(lblTitlu, editTitlu);
	lyForm->addRow(lblArtist, editArtist);
	lyForm->addRow(lblGen, editGen);
	lyForm->addRow(lblDurata, editDurata);
	btnAddSong = new QPushButton("Adauga melodie");
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
	//criteriilor de sortare pe care le avem (dupa artist+titlu 
	//si durata) + butonul de sortare

	QVBoxLayout* lyRadioBox = new QVBoxLayout;
	this->groupBox->setLayout(lyRadioBox);
	lyRadioBox->addWidget(radioSrtArtistTitlu);
	lyRadioBox->addWidget(radioSrtDurata);

	btnSortSongs = new QPushButton("Sorteaza melodii");
	lyRadioBox->addWidget(btnSortSongs);

	//adaugam acest grup in partea stanga, 
	//dupa componentele pentru adaugare in layout-ul vertical
	lyLeft->addWidget(groupBox);

	//cream un form pentru filtrarea dupa gen 
	QWidget* formFilter = new QWidget;
	QFormLayout* lyFormFilter = new QFormLayout;
	formFilter->setLayout(lyFormFilter);
	editFilterGen = new QLineEdit();
	lyFormFilter->addRow(lblFilterCriteria, editFilterGen);
	btnFilterSongs = new QPushButton("Filtreaza melodii dupa gen");
	lyFormFilter->addWidget(btnFilterSongs);

	lyLeft->addWidget(formFilter);
	
	//Buton folosit pentru a reincarca datele
	//i.e. afisam toate melodiile in tabel, in ordinea initiala din fisier
	btnReloadData = new QPushButton("Reload data");
	lyLeft->addWidget(btnReloadData);
	
	
	//componenta right - contine doar tabelul cu melodii
	QWidget* right = new QWidget;
	QVBoxLayout* lyRight = new QVBoxLayout;
	right->setLayout(lyRight);

	int noLines = 10;
	int noColumns = 4;
	this->tableSongs = new QTableWidget{noLines, noColumns};
	
	//setam header-ul tabelului
	QStringList tblHeaderList;
	tblHeaderList << "Titlu" << "Artist" << "Gen" << "Durata";
	this->tableSongs->setHorizontalHeaderLabels(tblHeaderList);

	//optiune pentru a se redimensiona celulele din tabel in functie de continut
	this->tableSongs->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
	btnPlaylist = new QPushButton{ "Open playlist" };
	lyLeft->addWidget(btnPlaylist);
	lyRight->addWidget(tableSongs);

	lyMain->addWidget(left);
	lyMain->addWidget(right);

}
void SongStoreGUI::reloadSongList(vector<Song> songs) {
	this->tableSongs->clearContents();
	this->tableSongs->setRowCount(songs.size());
	
	int lineNumber = 0;
	for (auto& song : songs) {
		this->tableSongs->setItem(lineNumber, 0, new QTableWidgetItem(QString::fromStdString(song.getTitlu())));
		this->tableSongs->setItem(lineNumber, 1, new QTableWidgetItem(QString::fromStdString(song.getArtist())));
		this->tableSongs->setItem(lineNumber, 2, new QTableWidgetItem(QString::fromStdString(song.getGen())));
		this->tableSongs->setItem(lineNumber, 3, new QTableWidgetItem(QString::number(song.getDurata())));
		lineNumber++;
	}
}

void SongStoreGUI::connectSignalsSlots() {
	QObject::connect(btnAddSong, &QPushButton::clicked, this, &SongStoreGUI::guiAddSong);

	QObject::connect(btnSortSongs, &QPushButton::clicked, [&]() {
		if (this->radioSrtArtistTitlu->isChecked())
			this->reloadSongList(srv.sortByArtistSong());
		else if (this->radioSrtDurata->isChecked())
			this->reloadSongList(srv.sortByDurata());
		});

	QObject::connect(btnFilterSongs, &QPushButton::clicked, [&]() {
		string filterC = this->editFilterGen->text().toStdString();
		this->reloadSongList(srv.filtrareGen(filterC));
		});
	
	QObject::connect(btnReloadData, &QPushButton::clicked, [&]() {
		this->reloadSongList(srv.getAllSongs());
		});
	QObject::connect(btnPlaylist, &QPushButton::clicked, [&]() {
		
		playlistWindow.show();
		});
	
}


void SongStoreGUI::guiAddSong() {
	try {
		//preluare detalii din QLineEdit-uri
		string titlu = editTitlu->text().toStdString();
		string artist = editArtist->text().toStdString();
		string gen = editGen->text().toStdString();
		double durata = editDurata->text().toDouble();

		//optional - golim QLineEdit-urile dupa apasarea butonului
		editTitlu->clear();
		editArtist->clear();
		editGen->clear();
		editDurata->clear();

		this->srv.addSong(titlu, artist, gen, durata);
		this->reloadSongList(this->srv.getAllSongs());

		//afisam un mesaj pentru a anunta utilizatorul ca melodia s-a adaugat
		QMessageBox::information(this, "Info", QString::fromStdString("Melodie adaugata cu succes."));

	}
	catch (RepoException& re) {
		QMessageBox::warning(this, "Warning", QString::fromStdString(re.getErrorMessage()));
	}
	catch (ValidationException& ve) {
		QMessageBox::warning(this, "Warning", QString::fromStdString(ve.getErrorMessages()));
	}


}