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
#include "Observer.h"

using std::to_string;
using std::set;
using std::vector;

class SongCounter;

class PlaylistGUI : public QWidget {
private:
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
	
	set<string> getGenres(const vector<Song>& playlistSongs);
	void reloadDynamicButtons();
	
public:
	PlaylistGUI(SongStore& songStore) : srv{ songStore } {
		initGUI();
		connectSignalsSlots();
	}
	
};

class SongCounter : public QWidget, public Observer {
private:
	QLineEdit* textbox;
	Playlist& playlist;

public:
	SongCounter(Playlist& play_list) : playlist{ play_list } {
		textbox = new QLineEdit;
		QHBoxLayout* layout = new QHBoxLayout;
		setLayout(layout);
		layout->addWidget(textbox);
		playlist.addObserver(this);
		update();
	}
	void update() override {
		textbox->setText(std::to_string(playlist.getAllPlaylistSongs().size()).c_str());
	}
	~SongCounter() {
		playlist.removeObserver(this);
	}
};

class SongDraw : public QWidget, public Observer {
private:
	Playlist& playlist;
protected:
	void paintEvent(QPaintEvent* ev) override {
		int x=10, y=10, w=10;
		QPainter g{ this };
		g.setPen(Qt::blue);
		for (const auto& song : playlist.getAllPlaylistSongs())
		{
			g.drawRect(x, y, w, song.getDurata()*20);
			x += 40;
		}
		/*g.drawImage(x, 0, QImage("sky.jpg"));
		
		g.setFont(QFont("Arial", 30));
		g.drawText(rect(), Qt::AlignTop | Qt::AlignHCenter, "Qt QPainter");
		g.fillRect(0, 100, 100, 100, Qt::BrushStyle::Dense1Pattern);*/
	}
public:
	SongDraw(Playlist& play_list) : playlist{play_list} {
		update();
	}
	void update() override {
		this->repaint();
	}
};