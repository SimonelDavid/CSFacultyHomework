#include "PlaylistGUI.h"



void PlaylistGUI::initGUI() {

	lyMain = new QHBoxLayout{};
	this->setLayout(lyMain);

	QWidget* leftSide = new QWidget{};
	QVBoxLayout* lyLeft = new QVBoxLayout{};
	leftSide->setLayout(lyLeft);

	QWidget* formW = new QWidget{};
	QFormLayout* lyEdits = new QFormLayout{};
	lblTitlu = new QLabel{ "Titlu" };
	lblArtist = new QLabel{ "Artist" };
	editTitlu = new QLineEdit{};
	editArtist = new QLineEdit{};

	lblSlider = new QLabel{ "Nr. melodii de generat" };
	editNoSlider = new QLineEdit{};
	lyEdits->addRow(lblTitlu, editTitlu);
	lyEdits->addRow(lblArtist,editArtist);
	lyEdits->addRow(lblSlider, editNoSlider);
	formW->setLayout(lyEdits);


	btnAdd = new QPushButton{ "Adauga in playlist" };
	btnGenerate = new QPushButton{ "Genereaza random" };
	btnEmpty = new QPushButton{ "Goleste playlist" };
	btnExport = new QPushButton{ "Export playlist" };
	btnClose = new QPushButton{ "Close" };

	btnLabelWindow = new QPushButton{ "Fereastra label" };
	btnLabelWindow->setStyleSheet("background-color: cyan");

	btnTableWindow = new QPushButton{ "Fereastra playlist tabel" };
	btnTableWindow->setStyleSheet("background-color: magenta");

	btnDrawWindow = new QPushButton{ "Fereastra desen" };
	btnDrawWindow->setStyleSheet("background-color: yellow");


	sliderGenerate = new QSlider{};
	sliderGenerate->setMinimum(1);
	sliderGenerate->setMaximum(srv.getAllSongs().size());

	lyLeft->addWidget(formW);
	lyLeft->addWidget(btnAdd);
	lyLeft->addWidget(btnGenerate);
	lyLeft->addWidget(btnEmpty);
	lyLeft->addWidget(btnExport);
	lyLeft->addWidget(btnClose);
	lyLeft->addWidget(btnLabelWindow);
	lyLeft->addWidget(btnTableWindow);
	lyLeft->addWidget(btnDrawWindow);

	QWidget* rightSide = new QWidget{};
	QVBoxLayout* lyRight = new QVBoxLayout{};
	rightSide->setLayout(lyRight);

	songList = new QListWidget{};
	songList->setFixedWidth(320);
	songList->setSelectionMode(QAbstractItemView::SingleSelection);

	lyRight->addWidget(songList);

	widgetDynamic = new QWidget{};
	lyBtnDynamic = new QVBoxLayout{};
	widgetDynamic->setLayout(lyBtnDynamic);
	reloadDynamicButtons();

	lyMain->addWidget(leftSide);
	lyMain->addWidget(sliderGenerate);
	lyMain->addWidget(rightSide);
	lyMain->addWidget(widgetDynamic);


}
set<string> PlaylistGUI::getGenres(const vector<Song>& playlistSongs) {
	set<string> genres;
	
	for (const auto& s : playlistSongs) {
		genres.insert(s.getGen());
	}
	return genres;
}
int howManyWithGenre(const vector<Song>& songs, string genre) {
	int noSongs = count_if(songs.begin(), songs.end(), [&](Song s) {
		return s.getGen() == genre; });
	return noSongs;
}
void clearLayout(QLayout* layout) {
	if (layout == NULL)
		return;
	QLayoutItem* item;
	while ((item = layout->takeAt(0))) {
		if (item->layout()) {
			clearLayout(item->layout());
			delete item->layout();
		}
		if (item->widget()) {
			delete item->widget();
		}
		delete item;
	}
}
void PlaylistGUI::reloadDynamicButtons() {
	clearLayout(this->lyBtnDynamic);
	const vector<Song>& playlistSongs = this->srv.getPlaylistSongs();
	set<string> genres = this->getGenres(playlistSongs);

	for (string genre : genres) {
		QPushButton* btn = new QPushButton{ QString::fromStdString(genre) };
		lyBtnDynamic->addWidget(btn);
		int howMany = howManyWithGenre(playlistSongs, genre);
		QObject::connect(btn, &QPushButton::clicked, [=]() {
			QMessageBox::information(this, "Info", QString::fromStdString("Melodii cu genul " + genre + " : " + to_string(howMany)));

			});
	}

}
void PlaylistGUI::connectSignalsSlots() {
	QObject::connect(btnAdd, &QPushButton::clicked, this, &PlaylistGUI::addToPlaylist);
	QObject::connect(sliderGenerate, &QSlider::sliderReleased, [&]() {
		qDebug() << sliderGenerate->value();
		});
	QObject::connect(btnGenerate, &QPushButton::clicked, [&]() {
		int noSongs = this->sliderGenerate->value();
		editNoSlider->setText(QString::number(noSongs));
		qDebug() << "This many songs to add:"<<noSongs;
		int howManyAdded = srv.addRandomToPlaylist(noSongs);
		this->reloadPlaylist();
		});
	QObject::connect(btnEmpty, &QPushButton::clicked, [&]() {
		srv.emptyPlayList();
		this->reloadPlaylist();
		});
	QObject::connect(btnExport, &QPushButton::clicked, [&]() {
		
		});
	QObject::connect(btnClose, &QPushButton::clicked, this, &PlaylistGUI::close);

	QObject::connect(btnLabelWindow, &QPushButton::clicked, [&]() {
		auto songcounter = new SongCounter(srv.getPlaylist());
		songcounter->show();
	});

	QObject::connect(btnDrawWindow, &QPushButton::clicked, [&]() {
		auto songdraw = new SongDraw(srv.getPlaylist());
		songdraw->show();
	});

	QObject::connect(songList, &QListWidget::itemSelectionChanged, [&]() {
		auto selItms = songList->selectedItems();
		for (auto item : selItms) {
			qDebug() << item->text();
			item->setBackground(Qt::green); // sets green background
		}

		});
		



}


void PlaylistGUI::reloadPlaylist() {
	
	this->songList->clear();
	
	const vector<Song>& songs = srv.getPlaylistSongs();
	for (auto& song : songs) {
		QString currentItem = QString::fromStdString(song.getTitlu() + "\t" + song.getArtist() + "\t" + song.getGen() + "\t" + to_string(song.getDurata()));
		this->songList->addItem(currentItem);
	}
	reloadDynamicButtons();
	
	}


void PlaylistGUI::addToPlaylist() {
	try {
		string titlu = editTitlu->text().toStdString();
		string artist = editArtist->text().toStdString();
	
		editTitlu->clear();
		editArtist->clear();
	

		this->srv.addToPlaylist(titlu, artist);
		this->reloadPlaylist();

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


