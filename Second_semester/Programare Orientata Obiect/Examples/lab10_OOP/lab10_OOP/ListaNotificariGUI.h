#pragma once
#include <QtWidgets/QApplication>
#include <QWidget>
#include "listaNotificare.h"
#include "locatarStore.h"
#include <QFormLayout>
#include <QListWidget>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QMessageBox>
#include <QTableWidget>
#include <QPainter>


class NotificariGUI :public QWidget, public Observer {
private:
	LocatarStore& srv;
	//lista notificari

	QHBoxLayout* lyMain;

	QWidget* form1;
	QFormLayout* lyForm1;
	//QTableWidget* tableNotificari= new QTableWidget{ 10,4 };
	QListWidget* listNotificari;
	//QPushButton* btnListaNotificari;
	QPushButton* btnListaNotifcariRevenire;

	QLineEdit* addApartment;

	QLineEdit* addApartmentRandom;

	QLineEdit* exportFileName;

	QPushButton* btnAddNotificare;
	QPushButton* btnAddNotificariRandom;
	QPushButton* btnDeleteNotificari;
	QPushButton* btnExportCVS;
	QPushButton* btnExportHTML;
	QLabel* lblApartment = new QLabel{ "Numar apartament: " };

	QPushButton* btnTableWindow;
	QPushButton* btnDrawWindow;


	void update()override {
		printNotificari();
	}

	void initializeGUIComponentsNotificari();

	void guiAddNotificare();
	void guiAddNotificareRandom();
	void printNotificari();
	void exportaCVS();
	void exportaHTML();
public:
	NotificariGUI(LocatarStore& locatarStore) :srv{ locatarStore } {
		initializeGUIComponentsNotificari();
	}
};

class NotificariGUITable :public QWidget, public Observer {
private:
	//LocatarStore& ctr;
	const vector<Locatar>& allFromSrv;
	ListaNotificare& n;
	QTableWidget* table;
	QPushButton* btnEmpty;
	QPushButton* btnAddRandom;
	QLineEdit* addRandom;
	void initGUI() {
		QHBoxLayout* ly = new QHBoxLayout{};
		this->setLayout(ly);
		table = new QTableWidget{};
		btnEmpty = new QPushButton{ "Goleste lista Notificari" };

		addRandom = new QLineEdit;
		btnAddRandom = new QPushButton{"Adauga random"};

		ly->addWidget(addRandom);
		ly->addWidget(btnAddRandom);
		ly->addWidget(table);
		ly->addWidget(btnEmpty);
		setAttribute(Qt::WA_DeleteOnClose);
		n.addObserver(this);
	};

	void reloadTableData(const vector<Locatar>& loc) {
		this->table->setColumnCount(4);
		this->table->setRowCount(static_cast<int>(loc.size()));
		for (int i = 0; i < loc.size(); i++) {
			table->setItem(i, 0, new QTableWidgetItem(QString::number(loc[i].getApartment())));
			table->setItem(i, 1, new QTableWidgetItem(QString::fromStdString(loc[i].getName())));
			table->setItem(i, 2, new QTableWidgetItem(QString::number(loc[i].getSurface())));
			table->setItem(i, 3, new QTableWidgetItem(QString::fromStdString(loc[i].getType())));
		}
	};

	void connectSignalsSlots() {
		n.addObserver(this);
		QObject::connect(btnAddRandom, &QPushButton::clicked, [&]() {
			int noLocatari = addRandom->text().toInt();
			n.addRandomLocatari(allFromSrv, noLocatari);
			reloadTableData(n.getAllListaNotificare());
			});
		QObject::connect(btnEmpty, &QPushButton::clicked, [&]() {
			n.emptyListaNotificare();
			reloadTableData(n.getAllListaNotificare());
			});
	}
public:
	NotificariGUITable(ListaNotificare& notificari, const vector<Locatar>& allFromSrv) :n{ notificari }, allFromSrv{ allFromSrv }{
	//NotificariGUITable(ListaNotificare& notificari) :n{ notificari }{
		initGUI(); connectSignalsSlots();
	};
	void update() override {
		this->reloadTableData(n.getAllListaNotificare());
	}
	~NotificariGUITable() {
		n.removeObserver(this);
	}
};

class NotificariGUIDraw :public QWidget, public Observer {
private:
	ListaNotificare& notificari;
	void paintEvent(QPaintEvent*) override {
		QPainter p{this};
		int x = 0;
		int y = 0;
		for (auto locatar : notificari.getAllListaNotificare()) {
			x = rand() % 400 + 1;
			y = rand() % 400 + 1;
			QRectF target(x, y, 60, 82);	
			QRectF source(0, 0, 602, 822);
			
			QImage image("building.jpg");
			
			//p.fillRect(x,y, 50, 50, Qt::GlobalColor::magenta);
			
			p.drawImage(target, image, source);
			x += 40;
		}
	}
	void update()override {
		repaint();
	};
	~NotificariGUIDraw() {
		notificari.removeObserver(this);
	}
public:
	NotificariGUIDraw(ListaNotificare& notificari) :notificari{ notificari } {
		notificari.addObserver(this);
	};
};