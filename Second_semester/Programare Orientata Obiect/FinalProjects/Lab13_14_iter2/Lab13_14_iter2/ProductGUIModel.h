#pragma once
#pragma once
#include <vector>
#include <string>
#include <QtWidgets/QApplication>
#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QLineEdit>
#include <QMessageBox>
#include <QHeaderView>
#include <QTableView>
#include <QGroupBox>
#include <QRadioButton>
#include "RetetaGUI.h"
#include "MyTableModel.h"

using std::vector;
using std::string;
class ProductGUIModel : public QWidget {
private:

	Service& srv;
	Reteta& ret;
	Repo& repo;
	RetetaGUI playlistWindow{ srv, ret, repo };
	QLabel* lblDenumire = new QLabel{ "Denumire:" };
	QLabel* lblPret = new QLabel{ "Pret:" };
	QLabel* lblProducator = new QLabel{ "Producator:" };
	QLabel* lblSubst = new QLabel{ "Sbstanta Activa:" };

	QLineEdit* editDenumire;
	QLineEdit* editPret;
	QLineEdit* editProducator;
	QLineEdit* editSubstanta;

	QPushButton* btnAddSong;

	QGroupBox* groupBox = new QGroupBox(tr("Tip sortare"));

	QRadioButton* radioSrtPretSubtanta = new QRadioButton(QString::fromStdString("Pret+Substanta"));
	QRadioButton* radioSrtDenumire = new QRadioButton(QString::fromStdString("Denumire"));
	QPushButton* btnSortMeds;

	QLabel* lblFilterCriteria = new QLabel{ "Producator dupa care se filtreaza:" };
	QLineEdit* editFilterGen;
	QPushButton* btnFilterMeds;

	QPushButton* btnReloadData;
	MyTableModel* model;

	QTableView* tableMeds = new QTableView;

	QPushButton* btnReteta;


	void initializeGUIComponents();

	void connectSignalsSlots();
	void reloadSongList(vector<Medicament> songs);
public:
	ProductGUIModel(Service& medSrv, Reteta& medsRet, Repo& medsRepo) : srv{ medSrv }, ret{ medsRet }, repo{ medsRepo } {
		initializeGUIComponents();
		this->model = new MyTableModel{ srv.getMeds() };
		this->tableMeds->setModel(model);
		connectSignalsSlots();
		reloadSongList(srv.getMeds());
	}
	void guiAddSong();

};
