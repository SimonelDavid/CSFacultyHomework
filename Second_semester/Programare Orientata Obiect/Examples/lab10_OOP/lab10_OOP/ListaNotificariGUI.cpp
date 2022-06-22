#include "ListaNotificariGUI.h"


void NotificariGUI::initializeGUIComponentsNotificari()
{
	srv.getListaNotificari().addObserver(this);
	lyMain = new QHBoxLayout{};
	this->setLayout(lyMain);
	form1 = new QWidget;
	//QFormLayout* lyForm = new QFormLayout;
	lyForm1 = new QFormLayout;
	form1->setLayout(lyForm1);
	addApartment = new QLineEdit;
	lyForm1->addRow(lblApartment, addApartment);
	btnAddNotificare = new QPushButton("Adauga notificare");
	lyForm1->addWidget(btnAddNotificare);

	btnListaNotifcariRevenire = new QPushButton("Meniu principal");
	lyForm1->addWidget(btnListaNotifcariRevenire);

	form1->setLayout(lyForm1);
	form1->show();
	hide();
	listNotificari = new QListWidget{};
	this->listNotificari->clear();


	QLabel* randomNotif = new QLabel("Numar de notificari de adaugat");
	addApartmentRandom = new QLineEdit;
	lyForm1->addRow(randomNotif, addApartmentRandom);
	btnAddNotificariRandom = new QPushButton("Adauga random notificari");
	lyForm1->addWidget(btnAddNotificariRandom);
	form1->setLayout(lyForm1);

	btnDeleteNotificari = new QPushButton("Sterge toate notificarile");
	lyForm1->addWidget(btnDeleteNotificari);


	QLabel* exportFile = new QLabel("Numele fisierului pentru export");
	exportFileName = new QLineEdit;
	lyForm1->addRow(exportFile, exportFileName);
	btnExportCVS = new QPushButton("Exporta fisier CVS");
	btnExportHTML = new QPushButton("Exporta fisier HTML");
	lyForm1->addWidget(btnExportCVS);
	lyForm1->addWidget(btnExportHTML);
	form1->setLayout(lyForm1);

	//QStringList headerNotificari;
	//headerNotificari << "Apartament" << "Nume" << "Suprafata" << "Tip";
	//this->tableNotificari->setHorizontalHeaderLabels(headerNotificari);
	//this->tableNotificari->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);

	//lyForm1->addWidget(tableNotificari);

	btnTableWindow = new QPushButton{ "cos CRUD gui" };
	lyForm1->addWidget(btnTableWindow);

	btnDrawWindow = new QPushButton{ "cos Read Only GUI" };
	lyForm1->addWidget(btnDrawWindow);

	lyForm1->addWidget(listNotificari);
	form1->setLayout(lyForm1);
	lyMain->addWidget(form1);
	this->setLayout(lyMain);
	srv.getListaNotificari().addObserver(this);
	QObject::connect(btnListaNotifcariRevenire, &QPushButton::clicked,this,&NotificariGUI::close);

	QObject::connect(btnAddNotificare, &QPushButton::clicked, this, &NotificariGUI::guiAddNotificare);

	QObject::connect(btnAddNotificariRandom, &QPushButton::clicked, this, &NotificariGUI::guiAddNotificareRandom);

	QObject::connect(btnDeleteNotificari, &QPushButton::clicked, [&]() {
		this->srv.emptyNotificari();
		this->listNotificari->clear();
		this->printNotificari();
		});

	QObject::connect(btnExportCVS, &QPushButton::clicked, this, &NotificariGUI::exportaCVS);

	QObject::connect(btnExportHTML, &QPushButton::clicked, this, &NotificariGUI::exportaHTML);

	QObject::connect(btnTableWindow, &QPushButton::clicked, this, [&]() {
		//LocatarRepoFile rep{ "locatari.txt" };
		//LocatarValidator val;
		//LocatarStore str{rep,val};
		const vector<Locatar>& allNotificari = srv.getAll();
		auto tableWindow = new NotificariGUITable{ srv.getListaNotificari() ,allNotificari };
		//auto tableWindow = new NotificariGUITable{ srv.getListaNotificari()};
		tableWindow->show();
		});

	QObject::connect(btnDrawWindow, &QPushButton::clicked, this, [&]() {
		auto drawWindow = new NotificariGUIDraw{ srv.getListaNotificari() };
		drawWindow->show();
		});

}

void NotificariGUI::guiAddNotificare()
{
	try {
		int apartament = addApartment->text().toInt();
		addApartment->clear();

		this->srv.addToNotificari(apartament);

		QMessageBox::information(this, "Info", QString::fromStdString("Notificare adaugata cu succes"));
		this->listNotificari->clear();
		this->printNotificari();
	}
	catch (LocatarRepoException& re) {
		QMessageBox::warning(this, "Warning", QString::fromStdString(re.getMsg()));
	}
	catch (ValidateException& ve) {
		QMessageBox::warning(this, "Warning", QString::fromStdString(ve.getMsg()));
	}
}

void NotificariGUI::guiAddNotificareRandom()
{
	int nr = addApartmentRandom->text().toInt();
	this->srv.addRandomNotificari(nr);
	this->listNotificari->clear();
	this->printNotificari();
	addApartmentRandom->clear();
	QMessageBox::information(this, "Info", QString::fromStdString("Locatari adaugati cu succes"));
}

void NotificariGUI::printNotificari()
{
	this->listNotificari->clear();
	vector<Locatar> allNotif = this->srv.getAllNotificari();
	for (const auto n : allNotif) {
		QString mesaj = QString::number(n.getApartment()) + ' ' + QString::fromStdString(n.getName()) + ' ' + QString::number(n.getSurface()) + ' ' + QString::fromStdString(n.getType());
		const QString& label = (mesaj);
		this->listNotificari->addItem(label);
	}
	lyForm1->addWidget(listNotificari);
	form1->setLayout(lyForm1);
}

void NotificariGUI::exportaCVS()
{
	try {
		std::string fName = exportFileName->text().toStdString();
		exportFileName->clear();

		this->srv.exportListCVS(fName);

		QMessageBox::information(this, "Info", QString::fromStdString("Lista exportata cu succes"));
	}
	catch (LocatarRepoException& re) {
		QMessageBox::warning(this, "Warning", QString::fromStdString(re.getMsg()));
	}
}

void NotificariGUI::exportaHTML()
{
	try {
		std::string fName = exportFileName->text().toStdString();
		exportFileName->clear();

		this->srv.exportListHTML(fName);

		QMessageBox::information(this, "Info", QString::fromStdString("Lista exportata cu succes"));
	}
	catch (LocatarRepoException& re) {
		QMessageBox::warning(this, "Warning", QString::fromStdString(re.getMsg()));
	}
}
