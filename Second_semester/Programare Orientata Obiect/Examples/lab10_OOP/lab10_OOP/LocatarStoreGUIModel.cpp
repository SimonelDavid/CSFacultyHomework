#include "LocatarStoreGUI.h"
#include "LocatarStoreGUIModel.h"

void LocatarStoreGUIModel::initializeGUIComponents()
{

	QHBoxLayout* lyMain = new QHBoxLayout;
	this->setLayout(lyMain);

	QWidget* right = new QWidget;
	QVBoxLayout* lyRight = new QVBoxLayout;
	right->setLayout(lyRight);

	QWidget* form = new QWidget;
	QFormLayout* lyForm = new QFormLayout;
	form->setLayout(lyForm);
	editApartment = new QLineEdit;
	editName = new QLineEdit;
	editSurface = new QLineEdit;
	editType = new QLineEdit;

	lyForm->addRow(lblApartment, editApartment);
	lyForm->addRow(lblName, editName);
	lyForm->addRow(lblSurface, editSurface);
	lyForm->addRow(lblType, editType);
	btnAddLocatar = new QPushButton("Adauga locatar");
	btnModifLocatar = new QPushButton("Modifica locatar");
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
	//QStringList headerTable;
	//headerTable << "Apartament" << "Nume" << "Suprafata" << "Tip";
	//this->tableLocatar->setHorizontalHeaderLabels(headerTable);
	//this->tableLocatar->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);

	this->model = new MyTableModel(srv.getAll());
	this->tableLocatar->setModel(model);
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

void LocatarStoreGUIModel::connectSignalsSlots()
{
	QObject::connect(btnAddLocatar, &QPushButton::clicked, this, &LocatarStoreGUIModel::guiAddLocatar);

	QObject::connect(btnDeleteLocatar, &QPushButton::clicked, this, &LocatarStoreGUIModel::guiDeleteLocatar);

	QObject::connect(btnModifLocatar, &QPushButton::clicked, this, &LocatarStoreGUIModel::guiModifLocatar);

	QObject::connect(btnSearchLocatar, &QPushButton::clicked, this, &LocatarStoreGUIModel::guiSearchLocatar);

	QObject::connect(btnUndo, &QPushButton::clicked, this, &LocatarStoreGUIModel::guiUndo);

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
		else if (this->radioSortSurface->isChecked())
			this->reloadLocatarList(srv.sortSurface());
		else if (this->radioSortTypeSurface->isChecked())
			this->reloadLocatarList(srv.sortTypeSurface());
		});

	QObject::connect(btnReloadData, &QPushButton::clicked, [&]() {
		this->reloadLocatarList(srv.getAll());
		});
	//selectia in tabel
	QObject::connect(tableLocatar->selectionModel(), &QItemSelectionModel::selectionChanged, [this]() {
		if (tableLocatar->selectionModel()->selectedIndexes().isEmpty()) {
			editApartment->setText("");
			editName->setText("");
			editSurface->setText("");
			editType->setText("");
			return;
		}
		int selRow = tableLocatar->selectionModel()->selectedIndexes().at(0).row();
		auto cel0Index = tableLocatar->model()->index(selRow, 0);
		auto cel1Index = tableLocatar->model()->index(selRow, 1);
		auto cel2Index = tableLocatar->model()->index(selRow, 2);
		auto cel3Index = tableLocatar->model()->index(selRow, 3);
		auto cellValue1 = tableLocatar->model()->data(cel0Index, Qt::DisplayRole).toString();
		auto cellValue2 = tableLocatar->model()->data(cel1Index, Qt::DisplayRole).toString();
		auto cellValue3 = tableLocatar->model()->data(cel2Index, Qt::DisplayRole).toString();
		auto cellValue4 = tableLocatar->model()->data(cel3Index, Qt::DisplayRole).toString();

		editApartment->setText(cellValue1);
		editName->setText(cellValue2);
		editSurface->setText(cellValue3);
		editType->setText(cellValue4);
		});
}

void LocatarStoreGUIModel ::reloadLocatarList(vector<Locatar> locatari)
{
	this->model->setLocatari(locatari);
}


void LocatarStoreGUIModel::addButtons(const std::vector<Locatar>& loc)
{
	for (const auto& l : loc) {
		bool ap = 0;
		for (const auto& t : types)
			if (l.getType() == t)
				ap = 1;
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


void LocatarStoreGUIModel ::guiAddLocatar()
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

void LocatarStoreGUIModel::guiDeleteLocatar()
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

void LocatarStoreGUIModel::guiModifLocatar()
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

void LocatarStoreGUIModel::guiSearchLocatar()
{
	int apartament = delApartment->text().toInt();
	delApartment->clear();

	Locatar loc = this->srv.findLocatar(apartament);
	if (loc.getApartment() == -1)
		QMessageBox::warning(this, "Warning", QString::fromStdString("Apartament invalid"));
	else
		QMessageBox::information(this, "Info", QString::fromStdString(loc.getName()));
}

void LocatarStoreGUIModel::guiUndo()
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



void LocatarStoreGUIModel::deleteDynBut(string tip)
{
	int cont = 0;
	if (srv.filterType(tip).size() == 0)
	{
		for (auto& btn : vecDynButtons)
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


