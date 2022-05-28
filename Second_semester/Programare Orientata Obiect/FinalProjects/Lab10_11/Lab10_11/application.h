#ifndef APPLICATION_H
#define APPLICATION_H

#include <QWidget>
#include <QPushButton>
#include <QTableWidget>
#include <QLabel>
#include <QLineEdit>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QFormLayout>
#include <QHeaderView>
#include <QMessageBox>
#include <QRadioButton>
#include <QItemSelectionModel>
#include <QBrush>
#include <QColor>
#include <stdlib.h>
#include <QListWidget>
#include <QListWidgetItem>
#include "service.h"
QT_BEGIN_NAMESPACE
namespace Ui { class application; }
QT_END_NAMESPACE

class application : public QWidget
{
private:
    service* serv = new service();
    //Section for the layout of the reteta
    service_reteta* reteta = new service_reteta(*serv);
    QWidget ui_reteta;
    QPushButton* btnToggleReteta;

    //QListWidget* reteta_table;
    QTableWidget* reteta_table;
    QPushButton* btnAdaugaMedicament;
    QLabel* lblComanda = new QLabel{"Nume medicament"};
    QLineEdit* editComanda;
    
    QPushButton* btnGolesteReteta;

    QPushButton* btnExportaReteta;
    QLabel* lblFisier = new QLabel{"Nume fisier"};
    QLineEdit* numeFisier;

    QLabel* lblNrMedicamente = new QLabel{"Nr medicamente"};
    QLineEdit* nrMedicamente;
    QPushButton* btnGenereazaReteta;


    vector<pair<int,int>> id_connections;
    //Section for base table
    QTableWidget* base_table;
    QPushButton* btnUndoOperation;
    QPushButton* btnReloadData;
    QPushButton* btnDeleteMed;
        //Section for sorting the table
        QPushButton* btnSortByName;
        QPushButton* btnSortByProducator;
        QPushButton* btnSortBySubstanta;


    //Section for adding a med
    QLabel* lblNume = new QLabel{"Nume medicament"};
    QLabel* lblPret = new QLabel{"Pret medicament"};
    QLabel* lblProducator = new QLabel{"Nume producator"};
    QLabel* lblSubstanta = new QLabel{"Substanta activa"};

    QLineEdit* editNume;
    QLineEdit* editPret;
    QLineEdit* editProducator;
    QLineEdit* editSubstanta;

    QPushButton* btnAddMed;

    //Section for filtered elements;
    QRadioButton* lblFilterNume = new QRadioButton{"Nume dupa care se filtreaza"};
    QLineEdit* editFilterNume;

    QRadioButton* lblFilterPret = new QRadioButton{"Pret dupa care se filtreaza"};
    QLineEdit* editFilterPret;

    QRadioButton* lblFilterSubstanta = new QRadioButton{"Substanta dupa care se filtreaza"};
    QLineEdit* editFilterSubstanta;

    QPushButton* filter;
    QTableWidget* filterTable;

    void initGUIcomponents();
    void connectSignals();
    void reloadMedList();
    void reloadFilterList(iter_pair lst);
    void reloadRetetaList();
public:
    application();
    void GUIAddMedicament();


};
#endif // APPLICATION_H
