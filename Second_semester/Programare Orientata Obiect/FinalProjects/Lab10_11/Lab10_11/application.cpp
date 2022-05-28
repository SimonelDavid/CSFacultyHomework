#include "application.h"
#include "ui_Lab10_11.h"

application::application()
{

    initGUIcomponents();
    connectSignals();
    reloadMedList();
    ui_reteta.hide();
}

void application::initGUIcomponents(){
    QVBoxLayout* lyMain = new QVBoxLayout;
    this->setLayout(lyMain);

    //upper part of the application
    QWidget* top = new QWidget;
    QHBoxLayout* lyTop = new QHBoxLayout;
    top->setLayout(lyTop);

    //top-left: addition
    QWidget* topLeft = new QWidget;
    QVBoxLayout* lyTopLeft = new QVBoxLayout;
    topLeft->setLayout(lyTopLeft);

    QWidget* form = new QWidget;
    QFormLayout* lyForm = new QFormLayout;
    form->setLayout(lyForm);

    editNume = new QLineEdit;
    editPret = new QLineEdit;
    editProducator = new QLineEdit;
    editSubstanta = new QLineEdit;

    lyForm->addRow(lblNume, editNume);
    lyForm->addRow(lblPret, editPret);
    lyForm->addRow(lblProducator, editProducator);
    lyForm->addRow(lblSubstanta, editSubstanta);

    btnAddMed = new QPushButton("Adauga medicament");
    btnToggleReteta = new QPushButton("Reteta");
    lyForm->addWidget(btnAddMed);
    lyTopLeft->addWidget(form);
    lyTopLeft->addWidget(btnToggleReteta);
    lyTop->addWidget(topLeft);

    //top-right: table
    QWidget* topRight = new QWidget;
    QVBoxLayout* lyTopRight = new QVBoxLayout;
    topRight->setLayout(lyTopRight);


    int noColumns = 4;
    this->base_table = new QTableWidget{0, noColumns};
    QStringList tblHeaderList;
    tblHeaderList<<"Nume"<<"Pret"<<"Producator"<<"Substanta activa";

    this->base_table->setHorizontalHeaderLabels(tblHeaderList);
    this->base_table->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);

    lyTopRight->addWidget(base_table);
    QWidget *belowTable = new QWidget;
    QVBoxLayout* lyBelowTable = new QVBoxLayout;
    belowTable->setLayout(lyBelowTable);

    QWidget* options = new QWidget;
    QHBoxLayout* lyOptions = new QHBoxLayout;
    options->setLayout(lyOptions);

    btnDeleteMed = new QPushButton("Sterge medicament");
    btnDeleteMed->setDisabled(1);
    btnReloadData = new QPushButton("Reincarca lista");
    btnUndoOperation = new QPushButton("Undo");
    lyOptions->addWidget(btnDeleteMed);
    lyOptions->addWidget(btnReloadData);
    lyOptions->addWidget(btnUndoOperation);

    //sortere
    QWidget* sorters = new QWidget;
    QHBoxLayout* lySorters = new QHBoxLayout;
    sorters->setLayout(lySorters);

    btnSortByName = new QPushButton("Sorteaza lista dupa nume");
    btnSortByProducator = new QPushButton("Sorteaza lista dupa producator");
    btnSortBySubstanta = new QPushButton("Sorteaza lista dupa substanta");
    lySorters->addWidget(btnSortByName);
    lySorters->addWidget(btnSortByProducator);
    lySorters->addWidget(btnSortBySubstanta);

    lyBelowTable->addWidget(options);
    lyBelowTable->addWidget(sorters);

    lyTopRight->addWidget(belowTable);
    lyTop->addWidget(topRight);
    lyMain->addWidget(top);

    //bottom part
    QWidget* bottom = new QWidget;
    QHBoxLayout* lyBottom = new QHBoxLayout;
    bottom->setLayout(lyBottom);
    //filter form/s
    QWidget* filterForm = new QWidget;
    QFormLayout* lyFilterForm = new QFormLayout;
    filterForm->setLayout(lyFilterForm);

    editFilterNume = new QLineEdit;
    editFilterPret = new QLineEdit;
    editFilterSubstanta = new QLineEdit;
    lyFilterForm->addRow(lblFilterNume, editFilterNume);
    lyFilterForm->addRow(lblFilterPret, editFilterPret);
    lyFilterForm->addRow(lblFilterSubstanta, editFilterSubstanta);

    filter = new QPushButton("Filtreaza medicamentele");
    lyFilterForm->addWidget(filter);
    lyBottom->addWidget(filterForm);
    //filter table
    filterTable = new QTableWidget{0, noColumns};
    QStringList filterTableHeaderList;
    filterTableHeaderList<<"Nume"<<"Pret"<<"Producator"<<"Substanta activa";

    this->filterTable->setHorizontalHeaderLabels(filterTableHeaderList);
    this->filterTable->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);

    lyBottom->addWidget(filterTable);
    lyMain->addWidget(bottom);

    //reteta
//    QWidget* mainReteta = new QWidget;
    QVBoxLayout* lyMainReteta = new QVBoxLayout;
    ui_reteta.setLayout(lyMainReteta);

    //reteta_table = new QListWidget;
    reteta_table = new QTableWidget;
    QStringList retetaTableHeaderList;

    lyMainReteta->addWidget(reteta_table);

    QWidget* addRetetaForm = new QWidget;
    QFormLayout* lyAddRetetaForm = new QFormLayout;
    addRetetaForm->setLayout(lyAddRetetaForm );

    editComanda = new QLineEdit;
    lyAddRetetaForm->addRow(lblComanda, editComanda);

    lyMainReteta->addWidget(addRetetaForm);
    btnAdaugaMedicament = new QPushButton("Adauga medicament in reteta");
    lyMainReteta->addWidget(btnAdaugaMedicament);

    QWidget* nrMedicamenteForm = new QWidget;
    QFormLayout* lyNrMedicamenteForm = new QFormLayout;
    nrMedicamenteForm->setLayout(lyNrMedicamenteForm );

    nrMedicamente = new QLineEdit;
    lyNrMedicamenteForm->addRow(lblNrMedicamente, nrMedicamente);

    lyMainReteta->addWidget(nrMedicamenteForm);
    btnGenereazaReteta = new QPushButton("Genereaza reteta");
    lyMainReteta->addWidget(btnGenereazaReteta);

    QWidget* numeFisierForm = new QWidget;
    QFormLayout* lyNumeFisierForm = new QFormLayout;
    numeFisierForm->setLayout(lyNumeFisierForm );

    numeFisier = new QLineEdit;
    lyNumeFisierForm->addRow(lblFisier, numeFisier);

    lyMainReteta->addWidget(numeFisierForm);
    btnExportaReteta = new QPushButton("Exporta reteta in fisier");
    lyMainReteta->addWidget(btnExportaReteta);
    btnGolesteReteta = new QPushButton("Goleste reteta");

    lyMainReteta->addWidget(btnGolesteReteta);
}

void application::reloadMedList(){
    base_table->clearContents();
    base_table->setRowCount(serv->getNrElems());

    iter_pair aux = this->serv->getAll();
    int lineNumber = 0;
    id_connections.clear();
    for(;aux.first != aux.second;++aux.first){
        entity med = *(aux.first);
        this->base_table->setItem(lineNumber,0, new QTableWidgetItem(QString::fromStdString(med.getName())));
        this->base_table->setItem(lineNumber,1, new QTableWidgetItem(QString::fromStdString(to_string(med.getPrice()))));
        this->base_table->setItem(lineNumber,2, new QTableWidgetItem(QString::fromStdString(med.getManufacturer())));
        this->base_table->setItem(lineNumber,3, new QTableWidgetItem(QString::fromStdString(med.getSubstance())));
        id_connections.push_back(pair<int, int>(med.getCode(), lineNumber));

        ++lineNumber;
    }
}

void application::GUIAddMedicament(){
    try{
        string nume = editNume->text().toStdString();
        string pret = editPret->text().toStdString();
        string producator = editProducator->text().toStdString();
        string substanta = editSubstanta->text().toStdString();

        editNume->clear();
        editPret->clear();
        editProducator->clear();
        editSubstanta->clear();

        this->serv->addElem(nume, pret, producator, substanta);
        this->reloadMedList();

        QMessageBox::information(this, "Info", QString::fromStdString("Medicament adaugat cu succes"));
    }catch(ValidationError& e){
        QMessageBox::information(this, "Warning", QString::fromStdString(e.getMessage()));
    }

}

void application::reloadFilterList(iter_pair lst){
    filterTable->clearContents();
    filterTable->setRowCount(serv->getFilterNrElems());
    int lineNumber = 0;
    for(;lst.first != lst.second;++lst.first){
        entity med = *(lst.first);
        this->filterTable->setItem(lineNumber,0, new QTableWidgetItem(QString::fromStdString(med.getName())));
        this->filterTable->setItem(lineNumber,1, new QTableWidgetItem(QString::fromStdString(to_string(med.getPrice()))));
        this->filterTable->setItem(lineNumber,2, new QTableWidgetItem(QString::fromStdString(med.getManufacturer())));
        this->filterTable->setItem(lineNumber,3, new QTableWidgetItem(QString::fromStdString(med.getSubstance())));

        ++lineNumber;
    }
}

void application::reloadRetetaList(){
    reteta_table->clear();
    reteta_table->setRowCount(0);

    iter_pair aux = reteta->getAll();
    int lineNumber = 0;
    for(;aux.first!=aux.second;++aux.first){
        entity med = *(aux.first);
        string content = "Nume: " + med.getName();
        content += "; Pret: " + to_string(med.getPrice());
        content += "; Producator: " + med.getManufacturer();
        content += "; Substanta activa: " + med.getSubstance();

        //this->reteta_table->addItem(QString::fromStdString(content));
        this->reteta_table->insertRow(lineNumber);
        this->reteta_table->setItem(lineNumber, 0, new QTableWidgetItem(QString::fromStdString(content)));
        ++lineNumber;
    }
}

void application::connectSignals(){
    QObject::connect(btnAddMed, &QPushButton::clicked,this,&application::GUIAddMedicament);
    QObject::connect(btnUndoOperation, &QPushButton::clicked, this, [&](){
        try{
            serv->UNDO();
            this->reloadMedList();
            QMessageBox::information(this, "Info", QString::fromStdString("Undo realizat cu succes"));

        }catch(RangeError& e){
            QMessageBox::information(this, "Info", QString::fromStdString(e.getMessage()));
        }
    });

    QObject::connect(btnSortByName, &QPushButton::clicked, this, [&](){
        serv->sortElems(0);
        this->reloadMedList();
    });
    QObject::connect(btnSortByProducator, &QPushButton::clicked, this, [&](){
        serv->sortElems(1);
        this->reloadMedList();
    });
    QObject::connect(btnSortBySubstanta, &QPushButton::clicked, this, [&](){
        serv->sortElems(2);
        this->reloadMedList();
    });

    QObject::connect(base_table, &QTableWidget::cellChanged,this, [&](int row, int col){
        int id = -1;

        for(auto aux:id_connections){
            if(aux.second == row){
                id = aux.first;
                break;
            }
        }
        if(id != -1){

//            QMessageBox::information(this, "Info", QString::fromStdString("Bruh"));
            string nume = base_table->item(row, 0)->text().toStdString();
            string pret = base_table->item(row, 1)->text().toStdString();
            string producator = base_table->item(row, 2)->text().toStdString();
            string substanta = base_table->item(row, 3)->text().toStdString();

            try{
                serv->changeElem(id, nume, pret, producator, substanta);
                reloadMedList();
            }catch(POSError& e){
                QMessageBox::information(this, "Info", QString::fromStdString(e.getMessage()));
            }
        }
    });

    QObject::connect(base_table, &QTableWidget::cellClicked, this,  [&](int row, int col){
//        QMessageBox::information(this, "Info", QString::fromStdString("Bruh"));
        base_table->selectRow(row);
        btnDeleteMed->setDisabled(0);
    });
    QObject::connect(btnDeleteMed, &QPushButton::clicked, this,[&](){
        int pos = base_table->currentRow();
        int id = -1;

        for(auto aux:id_connections){
            if(aux.second == pos){
                id = aux.first;
                break;
            }
        }
        if(id != -1){
            try{
                serv->deleteElem(id);
                this->reloadMedList();
                btnDeleteMed->setDisabled(1);
            }catch(POSError& e){
                QMessageBox::information(this, "Info", QString::fromStdString(e.getMessage()));
            }
        }
    });

    QObject::connect(filter, &QPushButton::clicked,this, [&](){
        if(lblFilterNume->isChecked()){
//            QMessageBox::information(this, "Info", QString::fromStdString("Bruh"));
            string nume = editFilterNume->text().toStdString();
            editFilterNume->clear();
            try{
                iter_pair aux = serv->filterElems(nume, 1);
                reloadFilterList(aux);
            }catch(POSError& e){
                QMessageBox::information(this, "Info", QString::fromStdString(e.getMessage()));
            }
        }else if(lblFilterPret->isChecked()){
//            QMessageBox::information(this, "Info", QString::fromStdString("Bruh"));
            string pret = editFilterPret->text().toStdString();
            editFilterPret->clear();
            try{
                iter_pair aux = serv->filterElems(pret, 2);
                reloadFilterList(aux);
            }catch(POSError& e){
                QMessageBox::information(this, "Info", QString::fromStdString(e.getMessage()));
            }
        }else if(lblFilterSubstanta->isChecked()){
//            QMessageBox::information(this, "Info", QString::fromStdString("Bruh"));
            string substanta = editFilterSubstanta->text().toStdString();
            editFilterSubstanta->clear();
            try{
                iter_pair aux = serv->filterElems(substanta, 3);
                reloadFilterList(aux);
            }catch(POSError& e){
                QMessageBox::information(this, "Info", QString::fromStdString(e.getMessage()));
            }
        }
    });

    QObject::connect(btnToggleReteta, &QPushButton::clicked, this, [&](){
        ui_reteta.show();
    });

    QObject::connect(btnAdaugaMedicament, &QPushButton::clicked, this, [&](){
        string name = editComanda->text().toStdString();
        editComanda->clear();
        try{
            if(name.empty())
                throw ValidationError("Introdu un nume");
            reteta->adaugaPeReteta(name);
            reloadRetetaList();
        }catch(POSError& e){
            QMessageBox::information(this, "Info", QString::fromStdString(e.getMessage()));
        }
    });
    QObject::connect(btnGenereazaReteta, &QPushButton::clicked, this, [&](){
        string nr = nrMedicamente->text().toStdString();
        nrMedicamente->clear();
        try{
            if(nr.empty())
                throw ValidationError("Introdu un numar");
            reteta->golesteReteta();
            reteta->genereazaReteta(stoi(nr));
            reloadRetetaList();
        }catch(POSError& e){
            QMessageBox::information(this, "Info", QString::fromStdString(e.getMessage()));
        }
    });
    QObject::connect(btnExportaReteta, &QPushButton::clicked, this, [&](){
        string name = numeFisier->text().toStdString();
        numeFisier->clear();
        try{
            if(name.empty())
                throw ValidationError("Introdu un nume");
            reteta->exportReteta(name);
            QMessageBox::information(this, "Info", QString::fromStdString("Reteta exportata cu succes!"));
        }catch(POSError& e){
            QMessageBox::information(this, "Info", QString::fromStdString(e.getMessage()));
        }
    });
    QObject::connect(btnGolesteReteta, &QPushButton::clicked, this, [&](){

        try{
            reteta->golesteReteta();
            reloadRetetaList();
        }catch(POSError& e){
            QMessageBox::information(this, "Info", QString::fromStdString(e.getMessage()));
        }
    });
}


