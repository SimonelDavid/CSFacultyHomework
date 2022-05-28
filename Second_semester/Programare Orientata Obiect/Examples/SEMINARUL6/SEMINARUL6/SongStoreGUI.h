#pragma once
#include <vector>
#include <string>
#include <QtWidgets/QApplication>
#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QLineEdit>
#include <QTableWidget>
#include <QMessageBox>
#include <QHeaderView>
#include <QGroupBox>
#include <QRadioButton>
#include "PlaylistGUI.h"

using std::vector;
using std::string;
class SongStoreGUI : public QWidget {
private:

	SongStore& srv;
	PlaylistGUI playlistWindow{ srv };
	QLabel* lblTitlu = new QLabel{ "Titlu melodie:" };
	QLabel* lblArtist = new QLabel{ "Artist melodie:" };
	QLabel* lblGen = new QLabel{ "Gen melodie:" };
	QLabel* lblDurata = new QLabel{ "Durata melodie:" };

	QLineEdit* editTitlu;
	QLineEdit* editArtist;
	QLineEdit* editGen;
	QLineEdit* editDurata;

	QPushButton* btnAddSong;

	QGroupBox* groupBox = new QGroupBox(tr("Tip sortare"));

	QRadioButton* radioSrtArtistTitlu = new QRadioButton(QString::fromStdString("Artist+Titlu"));
	QRadioButton* radioSrtDurata = new QRadioButton(QString::fromStdString("Durata"));
	QPushButton* btnSortSongs;

	QLabel* lblFilterCriteria = new QLabel{ "Gen dupa care se filtreaza:" };
	QLineEdit* editFilterGen;
	QPushButton* btnFilterSongs;

	QPushButton* btnReloadData;

	QTableWidget* tableSongs;

	QPushButton* btnPlaylist;

	
	void initializeGUIComponents();
	
	void connectSignalsSlots();
	void reloadSongList(vector<Song> songs);
public:
	SongStoreGUI(SongStore& songSrv) : srv{ songSrv } {
		initializeGUIComponents();
		connectSignalsSlots();
		reloadSongList(srv.getAllSongs());
	}
	void guiAddSong();

};
