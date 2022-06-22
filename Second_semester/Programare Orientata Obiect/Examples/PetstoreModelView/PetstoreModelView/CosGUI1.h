#pragma once
#include <qwidget.h>
#include <QtWidgets/QHBoxLayout>
#include <qlistwidget.h>
#include <qtablewidget.h>
#include <qstring.h>
#include <qlabel.h>
#include <vector>
#include "CosPet.h"
#include "observer.h"

class CosGUICuLista: public QWidget, public Observer {
private:
	CosPet& cos;
	QListWidget* lst;
	QPushButton* btn;
	QPushButton* btnRandom;
	void loadList(const std::vector<Pet>& pets) {
		lst->clear();
		for (auto& p : pets) {
			lst->addItem(QString::fromStdString(p.getSpecies()));
		}
	}
	void initGUI() {
		cos.addObserver(this);
		QHBoxLayout* ly = new QHBoxLayout;
		lst = new QListWidget;
		ly->addWidget(lst);
		btn = new QPushButton("Clear cos");
		ly->addWidget(btn);

		btnRandom = new QPushButton("Add random 3");
		ly->addWidget(btnRandom);
		setLayout(ly);
	}
	void connectSignals() {
		QObject::connect(btn, &QPushButton::clicked, [&]() {
			cos.goleste();
		});
		QObject::connect(btnRandom, &QPushButton::clicked, [&]() {
			cos.umple(3);
		});
	}
public:
	CosGUICuLista(CosPet& cos) :cos{cos} {
		initGUI();
		connectSignals();
		loadList(cos.lista());
	}

	void update() override {
		loadList(cos.lista());
	}
	~CosGUICuLista() {
		cos.removeObserver(this);
	}
};

class CosGUILabel :public QLabel,public Observer {	
	CosPet& cos;
public:
	CosGUILabel(CosPet& cos) :cos{ cos } {
		cos.addObserver(this);
		update();
	}

	void update() override {
		setText("Cosul contine:" + QString::number(cos.lista().size()));
	}
	~CosGUILabel() {
		cos.removeObserver(this);
	}
};

class CosGUICuTabel : public QWidget, public Observer {
private:
	CosPet& cos;
	QTableWidget* lst;
	QPushButton* btn;
	QPushButton* btnRandom;

	void loadTable(const std::vector<Pet>& pets) {
		lst->clear();
		lst->setRowCount(pets.size());
		lst->setColumnCount(3);
		for (int i = 0; i < pets.size(); i++) {
			lst->setItem(i, 0,new QTableWidgetItem(pets[i].getSpecies().c_str()));
			lst->setItem(i, 1, new QTableWidgetItem(pets[i].getType().c_str()));
			lst->setItem(i, 2, new QTableWidgetItem(QString::number(pets[i].getPrice())));
		}
	}

	void initGUI() {
		cos.addObserver(this);
		QHBoxLayout* ly = new QHBoxLayout;
		lst = new QTableWidget;
		ly->addWidget(lst);
		btn = new QPushButton("Clear cos");
		ly->addWidget(btn);

		btnRandom = new QPushButton("Add random 4");
		ly->addWidget(btnRandom);
		setLayout(ly);
	}
	void connectSignals() {
		QObject::connect(btn, &QPushButton::clicked, [&]() {
			cos.goleste();
		});
		QObject::connect(btnRandom, &QPushButton::clicked, [&]() {
			cos.umple(4);
		});
	}
public:
	CosGUICuTabel(CosPet& cos) :cos{ cos } {
		initGUI();
		connectSignals();
		loadTable(cos.lista());
	}

	void update() override {
		loadTable(cos.lista());
	}
	~CosGUICuTabel() {
		cos.removeObserver(this);
	}
};
