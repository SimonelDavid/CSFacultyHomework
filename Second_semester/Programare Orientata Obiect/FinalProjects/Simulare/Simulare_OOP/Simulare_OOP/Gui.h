#ifndef SIMULARE_GUI_H
#define SIMULARE_GUI_H
#include <QtWidgets>
#include "Service.h"


class Gui: public  QWidget{
private:
    Service& service;
    void init();
    void conec();
    void reloadListaCandidati(vector<Candidat> lst);
    QListWidget* listaCandidati = new QListWidget;
    QHBoxLayout* mainL = new QHBoxLayout;

    QWidget* formDreapta =  new QWidget;
    QVBoxLayout* formDreaptaL = new QVBoxLayout;

    QLineEdit* nameCandidat = new QLineEdit;
    QLineEdit* jobCandidat = new QLineEdit;
    QLineEdit* statusCandidat = new QLineEdit;

    QPushButton* addBtn = new QPushButton("adaugă");

    QLabel* status = new QLabel("");

public:
    Gui(Service& service):service{service}{
        init();
        conec();
        reloadListaCandidati(service.getCandidati());
    };
};


#endif //SIMULARE_GUI_H
