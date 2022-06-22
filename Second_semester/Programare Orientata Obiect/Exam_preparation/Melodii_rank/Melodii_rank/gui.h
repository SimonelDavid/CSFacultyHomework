#pragma once
#include <QtWidgets>
#include <QtCore>
#include <QTableView>
#include "Service.h"
#include "ModelCustom.h"

class GUI :public QWidget {
private:
	Service& srv;
	QTableWidget* tabel1;
	QTableView* view;
	QLineEdit* editTitlu;
	QSlider* sldRank;
	QPushButton* btnUpdate;
	QPushButton* btnDelete;
	List* tabel;

	void printLista(vector<Melodie> m);
public:

	void paintEvent(QPaintEvent*)override {
		QPainter p{ this };
		int x = 700;
		int y = 600;
		int frecv = 0;
		for (int a = 0; a <= 10; a++) {
			x += 50;
			frecv = srv.getFr(a);
			p.fillRect(x, y, 20, frecv * 5, Qt::GlobalColor::magenta);

		}
	}

	void connect();
	void initialize();
	GUI(Service& srv) :srv{ srv } {
		initialize();
		connect();
	};
};