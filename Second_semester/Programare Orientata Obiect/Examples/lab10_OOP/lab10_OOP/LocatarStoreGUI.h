#pragma once
#include "locatarStore.h"

#include <QtWidgets/QApplication>
#include <QLabel>
#include <QLineEdit>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QPushButton>
#include <QGroupBox>
#include <QRadioButton>
#include <QTableWidget>
#include <QHeaderView>
#include <QMessageBox>
#include <QListWidget>
#include "ListaNotificariGUI.h"

class LocatarStoreGUI :public QWidget {
private:
	LocatarStore& srv;

	NotificariGUI notificariWindow{ srv };
	//adaugare
	QLabel* lblApartment = new QLabel{ "Numar apartament: " };
	QLabel* lblName = new QLabel{ "Nume: " };
	QLabel* lblSurface = new QLabel{ "Suprafata apartament: " };
	QLabel* lblType = new QLabel{ "Tip apartament: " };

	QLineEdit* editApartment;
	QLineEdit* editName;
	QLineEdit* editSurface;
	QLineEdit* editType;

	QPushButton* btnAddLocatar;

	//modifica
	QPushButton* btnModifLocatar;
	
	//stergere
	QLabel* lblApartmentDelete = new QLabel{ "Numar apartament: " };
	QLineEdit* delApartment;
	QPushButton* btnDeleteLocatar;

	//cautare
	QPushButton* btnSearchLocatar;

	//undo
	QPushButton* btnUndo;
	
	//sortari
	QGroupBox* groupBox = new QGroupBox(tr("Tip sortare"));

	QRadioButton* radioSortName = new QRadioButton(QString::fromStdString("Nume"));
	QRadioButton* radioSortSurface = new QRadioButton(QString::fromStdString("Suprafata"));
	QRadioButton* radioSortTypeSurface = new QRadioButton(QString::fromStdString("Tip+Suprafata"));
	QPushButton* btnSortLocatar=new QPushButton(QString::fromStdString("Sorteaza"));

	//filtrari
	QLabel* lblFilterType= new QLabel{ "Tip dupa care se filtreaza:" };
	QLabel* lblFilterSurface= new QLabel{ "Suprafata dupa care se filtreaza:" };
	QLineEdit* editFilterType;
	QLineEdit* editFilterSurface;
	QPushButton* btnFilterLocatarType = new QPushButton(QString::fromStdString("Filtrare dupa tip"));
	QPushButton* btnFilterLocatarSurface = new QPushButton(QString::fromStdString("Filtrare dupa suprafata"));

	//reload
	QPushButton* btnReloadData=new QPushButton(QString::fromStdString("Reload"));

	//lista locatari
	QTableWidget* tableLocatar=new QTableWidget{10,4};

	QVBoxLayout* lyBtnDy = new QVBoxLayout;
	QWidget* btnDyn = new QWidget;
	vector<QPushButton*> vecDynButtons;
	
	void initializeGUIComponents();
	void connectSignalsSlots();
	void reloadLocatarList(vector<Locatar> locatari);
	void addButtons(const std::vector<Locatar>& loc);

	//void initializeGUIComponentsNotificari();

	vector<string> types;
	QPushButton* btnListaNotificari;
	////lista notificari
	//QWidget* form1;
	//QFormLayout* lyForm1;
	////QTableWidget* tableNotificari= new QTableWidget{ 10,4 };
	//QListWidget* listNotificari ;
	//QPushButton* btnListaNotificari;
	//QPushButton* btnListaNotifcariRevenire;

	//QLineEdit* addApartment;
	//
	//QLineEdit* addApartmentRandom;

	//QLineEdit* exportFileName;
	//
	//QPushButton* btnAddNotificare;
	//QPushButton* btnAddNotificariRandom;
	//QPushButton* btnDeleteNotificari;
	//QPushButton* btnExportCVS;
	//QPushButton* btnExportHTML;
public:
	LocatarStoreGUI(LocatarStore& locatarSrv) :srv{ locatarSrv }{
		initializeGUIComponents();
		connectSignalsSlots();
		reloadLocatarList(srv.getAll());
		addButtons(srv.getAll());
	}
	void guiAddLocatar();
	void guiDeleteLocatar();
	void guiModifLocatar();
	void guiSearchLocatar();
	void guiUndo();
	//void guiAddNotificare();
	//void guiAddNotificareRandom();
	void deleteDynBut(string tip);
	//void printNotificari();
	//void exportaCVS();
	//void exportaHTML();
};