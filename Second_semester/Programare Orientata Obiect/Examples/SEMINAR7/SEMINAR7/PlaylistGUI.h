#pragma once
#include <QtWidgets/QApplication>
#include <QWindow>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QWidget>
#include <QListWidget>
#include <QTableWidget>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QGroupBox>
#include <QFormLayout>
#include "Service.h"
#include <QMessageBox>
#include <string>
#include <set>
#include <vector>
#include <QDebug>
#include <QPainter>
#include <cstdlib>
using std::to_string;
using std::set;
using std::vector;

class PlaylistGUI : public QWidget, public Observer {
private:
	QBrush bgBrush;
	SongStore& srv;
	QHBoxLayout* lyMain;
	QListWidget* songList;

	QLabel* lblTitlu;
	QLabel* lblArtist;
	QLineEdit* editTitlu;
	QLineEdit* editArtist;

	QPushButton* btnAdd;
	QPushButton* btnGenerate;
	QPushButton* btnEmpty;
	QPushButton* btnExport;
	QPushButton* btnClose;
	QPushButton* btnLabelWindow;
	QPushButton* btnTableWindow;
	QPushButton* btnDrawWindow;


	QLineEdit* editNoSlider;
	QLabel* lblSlider;
	QSlider* sliderGenerate;

	QWidget* widgetDynamic;
	QVBoxLayout* lyBtnDynamic;
	void initGUI();
	void connectSignalsSlots();
	
	void reloadPlaylist();
	void addToPlaylist();
	
	//ar trebui ca aceasta metoda sa fie aici sau in service?
	set<string> getGenres(const vector<Song>& playlistSongs);
	void reloadDynamicButtons();
	void update() override {
		reloadPlaylist();
	}
	
public:
	PlaylistGUI(SongStore& songStore) : srv{ songStore } {
		initGUI();
		connectSignalsSlots();
	}
	
};
class PlaylistGUILabel:public QWidget, public Observer{
private:
	Playlist& p;
	QLabel* lblNoSongs;
	QLineEdit* editNoSongs;
	void initGUI() {
		QHBoxLayout* ly = new QHBoxLayout{};
		this->setLayout(ly);
		lblNoSongs = new QLabel{ "Numar de melodii:" };
		editNoSongs = new QLineEdit{};
		ly->addWidget(lblNoSongs);
		ly->addWidget(editNoSongs);
		setAttribute(Qt::WA_DeleteOnClose);
		p.addObserver(this);
	};
	void update() override {
		this->editNoSongs->setText(QString::number(p.getAllPlaylistSongs().size()));
	};
	~PlaylistGUILabel() {
		p.removeObserver(this);
	}
	
public:
	PlaylistGUILabel(Playlist& playlist) :p{ playlist } {
		initGUI();
	};

};
class PlaylistGUITable :public QWidget, public Observer {
private:
	Playlist& p;
	QTableWidget* table;
	QPushButton* btnEmpty;
	void initGUI() {
		QHBoxLayout* ly = new QHBoxLayout{};
		this->setLayout(ly);
		table = new QTableWidget{};
		btnEmpty = new QPushButton{ "Goleste playlist" };
		ly->addWidget(table);
		ly->addWidget(btnEmpty);
		setAttribute(Qt::WA_DeleteOnClose);
		p.addObserver(this);
	};
	void reloadTableData(const vector<Song>& songs) {
		this->table->setColumnCount(4);
		this->table->setRowCount(songs.size());
		for (int i=0; i<songs.size();i++) {
			table->setItem(i, 0, new QTableWidgetItem(QString::fromStdString(songs[i].getTitlu())));
			table->setItem(i, 1, new QTableWidgetItem(QString::fromStdString(songs[i].getArtist())));
			table->setItem(i, 2, new QTableWidgetItem(QString::fromStdString(songs[i].getGen())));
			table->setItem(i, 3, new QTableWidgetItem(QString::number(songs[i].getDurata())));
		}

	};

	void connectSignalsSlots() {
		p.addObserver(this);

		QObject::connect(btnEmpty, &QPushButton::clicked, [&]() {
			p.emptyPlaylist();
			reloadTableData(p.getAllPlaylistSongs());
			});
	}
	

public:
	PlaylistGUITable(Playlist& playlist) :p{ playlist } {
		initGUI();
		connectSignalsSlots();
	};

	void update() override {
		this->reloadTableData(p.getAllPlaylistSongs());
	}
	~PlaylistGUITable() {
		p.removeObserver(this);
	}

};

class PlaylistGUIDraw :public QWidget, public Observer {
private:
	Playlist& playlist;
	void paintEvent(QPaintEvent* ev) override {
		QPainter p{ this };
		int x = 0;
		int y = 0;
		for (auto song : playlist.getAllPlaylistSongs()) {
			//p.drawRect(x, y, 10, song.getDurata() * 10);
			x= rand() % 400 + 1;
			y = rand() % 400 + 1;
			qDebug() << x << " " << y;
			QRectF target(x, y, 100, 94);
			QRectF source(0, 0, 732, 720);
			QImage image("sun.jpg");

			p.drawImage(target,image, source);
			
			x += 40;

		}
	}

	void update() override {
		repaint();
	};
	~PlaylistGUIDraw() {
		playlist.removeObserver(this);
	}

public:
	PlaylistGUIDraw(Playlist& playlist) :playlist{ playlist } {
		playlist.addObserver(this);
	};

};
