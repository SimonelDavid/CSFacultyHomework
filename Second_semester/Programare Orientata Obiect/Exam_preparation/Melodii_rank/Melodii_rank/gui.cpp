#include "gui.h"
#include "ModelCustom.h"

void GUI::printLista(vector<Melodie> m)
{
	this->tabel1->setColumnCount(4);
	this->tabel1->setRowCount(m.size());
	this->tabel1->clearContents();
	tabel1->setFixedSize(200, 400);
	QStringList tr;
	tr << "ID" << "Rank" << "Titlu" << "Artist";
	this->tabel1->setHorizontalHeaderLabels(tr);
	int noLines = 0;
	for (auto& el : m) {
		this->tabel1->setItem(noLines, 0, new QTableWidgetItem(QString::number(el.getId())));
		this->tabel1->setItem(noLines, 1, new QTableWidgetItem(QString::number(el.getRank())));
		this->tabel1->setItem(noLines, 2, new QTableWidgetItem(QString::fromStdString(el.getTitlu())));
		this->tabel1->setItem(noLines, 3, new QTableWidgetItem(QString::fromStdString(el.getArtist())));
		noLines++;
	}
}

void GUI::connect()
{
	QObject::connect(tabel1, &QTableWidget::itemSelectionChanged, [&]() {
		auto selItms = tabel1->selectedItems();
		for (auto item : selItms) {
			qDebug() << item->text();
		}

		});

	QObject::connect(view->selectionModel(), &QItemSelectionModel::selectionChanged, [&]() {
		auto lst = view->selectionModel()->selectedIndexes();
		auto it = lst.begin();
		if (it) {
			int i = it->row();
			editTitlu->setText(srv.getAll()[i].getTitlu().c_str());
		}

		});

	QObject::connect(btnUpdate, &QPushButton::clicked, [&]() {
		int rank = sldRank->value();
		string titlu = editTitlu->text().toStdString();
		auto lst = view->selectionModel()->selectedIndexes();
		auto it = lst.begin();
		int id = 0;
		if (it) {
			int i = it->row();
			id = srv.getAll()[i].getId();
		}
		if (titlu != "")
			srv.updateRank(id, rank, titlu);
		tabel->schimba_melodii(srv.getAll());
		editTitlu->clear();
		update();
		});

	QObject::connect(btnDelete, &QPushButton::clicked, [&]() {
		string titlu = editTitlu->text().toStdString();
		auto lst = view->selectionModel()->selectedIndexes();
		auto it = lst.begin();
		int id = 0;
		if (it) {
			int i = it->row();
			id = srv.getAll()[i].getId();
		}
		try {
			srv.deletePos(id);
		}
		catch (std::exception& e) {
			string msg = e.what();
			QMessageBox* msgBox = new QMessageBox();
			msgBox->setText(QString::fromStdString(msg));
			msgBox->show();
		}
		tabel->schimba_melodii(srv.getAll());
		editTitlu->clear();
		update();

		});
}

void GUI::initialize()
{

	QHBoxLayout* lyMain = new QHBoxLayout;
	this->setLayout(lyMain);
	this->setFixedSize(1500, 800);
	tabel1 = new QTableWidget;
	lyMain->addWidget(tabel1);
	printLista(srv.getAll());

	QFormLayout* ly = new QFormLayout;
	view = new QTableView;
	tabel = new List{ srv.getAll(),srv };
	view->setModel(tabel);

	lyMain->addWidget(view);
	editTitlu = new QLineEdit;
	lyMain->addWidget(editTitlu);

	sldRank = new QSlider;
	sldRank->setMinimum(0);
	sldRank->setMaximum(10);
	lyMain->addWidget(sldRank);

	btnUpdate = new QPushButton("UPDATE");
	lyMain->addWidget(btnUpdate);

	btnDelete = new QPushButton("DELETE");
	lyMain->addWidget(btnDelete);
	view->setFixedSize(507, 400);
	

}


