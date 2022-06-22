#include "LocatarStoreGUI.h"

void LocatarStoreGUI::initializeGUIComponents()
{
	QHBoxLayout* lyMain = new QHBoxLayout;
	this->setLayout(lyMain);

	QWidget* right = new QWidget;
	QVBoxLayout* lyRight= new QVBoxLayout;
	right->setLayout(lyRight);

	QWidget* form = new QWidget;
	QFormLayout* lyForm = new QFormLayout;
	form->setLayout(lyForm);
	editApartment=new QLineEdit;
	editName=new QLineEdit;
	editSurface = new QLineEdit;
	editType = new QLineEdit;

	lyForm->addRow(lblApartment, editApartment);
	lyForm->addRow(lblName, editName);
	lyForm->addRow(lblSurface, editSurface);
	lyForm->addRow(lblType, editType);
	btnAddLocatar = new QPushButton("Adauga locatar");
	btnModifLocatar= new QPushButton("Modifica locatar");
	lyForm->addWidget(btnAddLocatar);
	lyForm->addWidget(btnModifLocatar);

	form->setLayout(lyForm);
	delApartment = new QLineEdit;
	lyForm->addRow(lblApartmentDelete, delApartment);
	btnDeleteLocatar = new QPushButton("Sterge locatar");
	lyForm->addWidget(btnDeleteLocatar);

	btnSearchLocatar = new QPushButton("Cauta locatar");
	lyForm->addWidget(btnSearchLocatar);

	lyRight->addWidget(form);


	QWidget* formFilterType = new QWidget;
	QFormLayout* lyFormFilterType = new QFormLayout;
	formFilterType->setLayout(lyFormFilterType);
	editFilterType = new QLineEdit();
	lyFormFilterType->addRow(lblFilterType, editFilterType);
	lyFormFilterType->addWidget(btnFilterLocatarType);
	lyRight->addWidget(formFilterType);

	QWidget* formFilterSurface = new QWidget;
	QFormLayout* lyFormFilterSurface = new QFormLayout;
	formFilterSurface->setLayout(lyFormFilterSurface);
	editFilterSurface = new QLineEdit();
	lyFormFilterSurface->addRow(lblFilterSurface, editFilterSurface);
	lyFormFilterSurface->addWidget(btnFilterLocatarSurface);
	lyRight->addWidget(formFilterSurface);

	QVBoxLayout* lyRadioBoxSort = new QVBoxLayout;
	this->groupBox->setLayout(lyRadioBoxSort);
	lyRadioBoxSort->addWidget(radioSortName);
	lyRadioBoxSort->addWidget(radioSortSurface);
	lyRadioBoxSort->addWidget(radioSortTypeSurface);
	lyRadioBoxSort->addWidget(btnSortLocatar);
	lyRight->addWidget(groupBox);

	lyRight->addWidget(btnReloadData);

	QWidget* left = new QWidget;
	QVBoxLayout* lyLeft = new QVBoxLayout;
	left->setLayout(lyLeft);
	QStringList headerTable;
	headerTable << "Apartament" << "Nume" << "Suprafata" << "Tip";
	this->tableLocatar->setHorizontalHeaderLabels(headerTable);
	this->tableLocatar->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);

	lyLeft->addWidget(tableLocatar);

	btnUndo = new QPushButton("Undo");
	btnListaNotificari = new QPushButton("Meniu lista notificari");

	btnDyn->setLayout(lyBtnDy);
	lyMain->addWidget(right);
	lyMain->addWidget(left);
	lyMain->addWidget(btnDyn);
	lyMain->addWidget(btnUndo);
	lyMain->addWidget(btnListaNotificari);
}

void LocatarStoreGUI::connectSignalsSlots()
{
	QObject::connect(btnAddLocatar, &QPushButton::clicked, this, &LocatarStoreGUI::guiAddLocatar);

	QObject::connect(btnDeleteLocatar, &QPushButton::clicked, this, &LocatarStoreGUI::guiDeleteLocatar);
	
	QObject::connect(btnModifLocatar, &QPushButton::clicked, this, &LocatarStoreGUI::guiModifLocatar);
	
	QObject::connect(btnSearchLocatar, &QPushButton::clicked, this, &LocatarStoreGUI::guiSearchLocatar);
	
	QObject::connect(btnUndo, &QPushButton::clicked, this, &LocatarStoreGUI::guiUndo);
	
	QObject::connect(btnListaNotificari, &QPushButton::clicked, [&]() {
		notificariWindow.show();
		});
	
	
	
	
	QObject::connect(btnFilterLocatarSurface, &QPushButton::clicked, [&]() {
		int filterSurf = this->editFilterSurface->text().toInt();
		this->reloadLocatarList(srv.filterSurface(filterSurf));
		editFilterSurface->clear();
		});

	QObject::connect(btnFilterLocatarType, &QPushButton::clicked, [&]() {
		string filterType = this->editFilterType->text().toStdString();
		this->reloadLocatarList(srv.filterType(filterType));
		editFilterType->clear();
		});
	
	QObject::connect(btnSortLocatar, &QPushButton::clicked, [&]() {
		if (this->radioSortName->isChecked())
			this->reloadLocatarList(srv.sortName());
		else if(this->radioSortSurface->isChecked())
			this->reloadLocatarList(srv.sortSurface());
		else if(this->radioSortTypeSurface->isChecked())
			this->reloadLocatarList(srv.sortTypeSurface());
		});

	QObject::connect(btnReloadData, &QPushButton::clicked, [&]() {
		this->reloadLocatarList(srv.getAll());
		});
}

void LocatarStoreGUI::reloadLocatarList(vector<Locatar> locatari)
{
	this->tableLocatar->clearContents();
	this->tableLocatar->setRowCount(int (locatari.size()));

	int noLines = 0;
	for (auto& l : locatari) {
		this->tableLocatar->setItem(noLines, 0, new QTableWidgetItem(QString::number(l.getApartment())));
		this->tableLocatar->setItem(noLines, 1, new QTableWidgetItem(QString::fromStdString(l.getName())));
		this->tableLocatar->setItem(noLines, 2, new QTableWidgetItem(QString::number(l.getSurface())));
		this->tableLocatar->setItem(noLines, 3, new QTableWidgetItem(QString::fromStdString(l.getType())));
		noLines++;
	}
}


void LocatarStoreGUI::addButtons(const std::vector<Locatar>& loc)
{
	for (const auto& l : loc) {
		bool ap = 0;
		for (const auto& t : types)
			if (l.getType()== t)
				ap=1;
		if (ap == 0) {
			auto btn = new QPushButton{ QString::fromStdString(l.getType()) };
			lyBtnDy->addWidget(btn);
			QObject::connect(btn, &QPushButton::clicked, [this, btn, l]() {
				QMessageBox::information(nullptr, "Info", QString::number(this->srv.typeNumber(l.getType())));
				});
			vecDynButtons.push_back(btn);
		}
		types.insert(types.end(), l.getType());
	}
}

//void LocatarStoreGUI::initializeGUIComponentsNotificari()
//{
//	form1 = new QWidget;
//	//QFormLayout* lyForm = new QFormLayout;
//	lyForm1 = new QFormLayout;
//	form1->setLayout(lyForm1);
//	addApartment = new QLineEdit;
//	lyForm1->addRow(lblApartment, addApartment);
//	btnAddNotificare = new QPushButton("Adauga notificare");
//	lyForm1->addWidget(btnAddNotificare);
//
//	btnListaNotifcariRevenire = new QPushButton("Meniu principal");
//	lyForm1->addWidget(btnListaNotifcariRevenire);
//
//	form1->setLayout(lyForm1);
//	form1->show();
//	hide();
//	listNotificari = new QListWidget{};
//	this->listNotificari->clear();
//
//
//	QLabel* randomNotif = new QLabel("Numar de notificari de adaugat");
//	addApartmentRandom = new QLineEdit;
//	lyForm1->addRow(randomNotif,addApartmentRandom);
//	btnAddNotificariRandom = new QPushButton("Adauga random notificari");
//	lyForm1->addWidget(btnAddNotificariRandom);
//	form1->setLayout(lyForm1);
//
//	btnDeleteNotificari = new QPushButton("Sterge toate notificarile");
//	lyForm1->addWidget(btnDeleteNotificari);
//
//
//	QLabel* exportFile = new QLabel("Numele fisierului pentru export");
//	exportFileName = new QLineEdit;
//	lyForm1->addRow(exportFile, exportFileName);
//	btnExportCVS = new QPushButton("Exporta fisier CVS");
//	btnExportHTML = new QPushButton("Exporta fisier HTML");
//	lyForm1->addWidget(btnExportCVS);
//	lyForm1->addWidget(btnExportHTML);
//	form1->setLayout(lyForm1);
//
//	//QStringList headerNotificari;
//	//headerNotificari << "Apartament" << "Nume" << "Suprafata" << "Tip";
//	//this->tableNotificari->setHorizontalHeaderLabels(headerNotificari);
//	//this->tableNotificari->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
//
//	//lyForm1->addWidget(tableNotificari);
//
//	lyForm1->addWidget(listNotificari);
//	form1->setLayout(lyForm1);
//
//	QObject::connect(btnListaNotifcariRevenire, &QPushButton::clicked, [&]() {
//		this->srv.emptyNotificari();
//		show();
//		form1->close();
//		});
//
//	QObject::connect(btnAddNotificare, &QPushButton::clicked, this, &LocatarStoreGUI::guiAddNotificare);
//
//	QObject::connect(btnAddNotificariRandom, &QPushButton::clicked, this, &LocatarStoreGUI::guiAddNotificareRandom);
//
//	QObject::connect(btnDeleteNotificari, &QPushButton::clicked, [&]() {
//		this->srv.emptyNotificari();
//		this->listNotificari->clear();
//		this->printNotificari();
//		});
//
//	QObject::connect(btnExportCVS, &QPushButton::clicked, this, &LocatarStoreGUI::exportaCVS);
//
//	QObject::connect(btnExportHTML, &QPushButton::clicked, this, &LocatarStoreGUI::exportaHTML);
//
//}

void LocatarStoreGUI::guiAddLocatar()
{
	try {
		int apartament = editApartment->text().toInt();
		string nume = editName->text().toStdString();
		int suprafata= editSurface->text().toInt();
		string tip = editType->text().toStdString();
		
		editApartment->clear();
		editName->clear();
		editSurface->clear();
		editType->clear();

		this->srv.addLocatar(apartament, nume, suprafata, tip);
		this->reloadLocatarList(this->srv.getAll());

		QMessageBox::information(this, "Info", QString::fromStdString("Locatar adaugat cu succes"));
	}
	catch (LocatarRepoException& re) {
		QMessageBox::warning(this, "Warning", QString::fromStdString(re.getMsg()));
	}
	catch (ValidateException& ve) {
		QMessageBox::warning(this, "Warning", QString::fromStdString(ve.getMsg()));
	}
}

void LocatarStoreGUI::guiDeleteLocatar()
{
	try {
		int apartament = delApartment->text().toInt();
		delApartment->clear();
		Locatar ap = srv.findLocatar(apartament);
		this->srv.delLocatar(apartament);
		this->reloadLocatarList(this->srv.getAll());

		QMessageBox::information(this, "Info", QString::fromStdString("Locatar sters cu succes"));
		
		deleteDynBut(ap.getType());
	}
	catch (LocatarRepoException& re) {
		QMessageBox::warning(this, "Warning", QString::fromStdString(re.getMsg()));
	}
}

void LocatarStoreGUI::guiModifLocatar()
{
	try {
		int apartament = editApartment->text().toInt();
		string nume = editName->text().toStdString();
		int suprafata = editSurface->text().toInt();
		string tip = editType->text().toStdString();

		editApartment->clear();
		editName->clear();
		editSurface->clear();
		editType->clear();

		this->srv.modifLocatar(apartament, nume, suprafata, tip);
		this->reloadLocatarList(this->srv.getAll());

		QMessageBox::information(this, "Info", QString::fromStdString("Locatar modificat cu succes"));
		addButtons(srv.getAll());
	}
	catch (LocatarRepoException& re) {
		QMessageBox::warning(this, "Warning", QString::fromStdString(re.getMsg()));
	}
	catch (ValidateException& ve) {
		QMessageBox::warning(this, "Warning", QString::fromStdString(ve.getMsg()));
	}
}

void LocatarStoreGUI::guiSearchLocatar()
{
		int apartament = delApartment->text().toInt();
		delApartment->clear();

		Locatar loc=this->srv.findLocatar(apartament);
		if(loc.getApartment()==-1)
			QMessageBox::warning(this, "Warning", QString::fromStdString("Apartament invalid"));
		else
			QMessageBox::information(this, "Info",QString::fromStdString(loc.getName()));
}

void LocatarStoreGUI::guiUndo()
{
	try {
		
		this->srv.undo();
		this->reloadLocatarList(this->srv.getAll());

		QMessageBox::information(this, "Info", QString::fromStdString("Locatar sters cu succes"));
		addButtons(srv.getAll());
	}
	catch (LocatarRepoException& re) {
		QMessageBox::warning(this, "Warning", QString::fromStdString(re.getMsg()));
	}
}

//void LocatarStoreGUI::guiAddNotificare()
//{
//	try {
//		int apartament = addApartment->text().toInt();
//		addApartment->clear();
//
//		this->srv.addToNotificari(apartament);
//
//		QMessageBox::information(this, "Info", QString::fromStdString("Notificare adaugata cu succes"));
//		this->listNotificari->clear();
//		this->printNotificari();
//	}
//	catch (LocatarRepoException& re) {
//		QMessageBox::warning(this, "Warning", QString::fromStdString(re.getMsg()));
//	}
//	catch (ValidateException& ve) {
//		QMessageBox::warning(this, "Warning", QString::fromStdString(ve.getMsg()));
//	}
//}

//void LocatarStoreGUI::guiAddNotificareRandom()
//{
//	int nr = addApartmentRandom->text().toInt();
//	this->srv.addRandomNotificari(nr);
//	this->listNotificari->clear();
//	this->printNotificari();
//	addApartmentRandom->clear();
//	QMessageBox::information(this, "Info", QString::fromStdString("Locatari adaugati cu succes"));
//}

void LocatarStoreGUI::deleteDynBut(string tip)
{
	int cont = 0;
	if (srv.filterType(tip).size() == 0)
	{
		for(auto& btn: vecDynButtons)
			if (btn->text().toStdString() == tip)
			{
				delete(btn);
				vecDynButtons.erase(vecDynButtons.begin() + cont);
				types.erase(types.begin() + cont);
				break;
			}
		cont++;
	}
}

//void LocatarStoreGUI::printNotificari()
//{
//	vector<Locatar> allNotif = this->srv.getAllNotificari();
//	for (const auto n : allNotif) {
//		QString mesaj= QString::number(n.getApartment())+' '+QString::fromStdString(n.getName()) + ' ' + QString::number(n.getSurface()) + ' ' + QString::fromStdString(n.getType());
//		const QString& label = (mesaj);
//		this->listNotificari->addItem(label);
//	}
//	lyForm1->addWidget(listNotificari);
//	form1->setLayout(lyForm1);
//}

//void LocatarStoreGUI::exportaCVS()
//{
//	try {
//		std::string fName = exportFileName->text().toStdString();
//		exportFileName->clear();
//
//		this->srv.exportListCVS(fName);
//
//		QMessageBox::information(this, "Info", QString::fromStdString("Lista exportata cu succes"));
//	}
//	catch (LocatarRepoException& re) {
//		QMessageBox::warning(this, "Warning", QString::fromStdString(re.getMsg()));
//	}
//}

//void LocatarStoreGUI::exportaHTML()
//{
//	try {
//		std::string fName = exportFileName->text().toStdString();
//		exportFileName->clear();
//
//		this->srv.exportListHTML(fName);
//
//		QMessageBox::information(this, "Info", QString::fromStdString("Lista exportata cu succes"));
//	}
//	catch (LocatarRepoException& re) {
//		QMessageBox::warning(this, "Warning", QString::fromStdString(re.getMsg()));
//	}
//}

