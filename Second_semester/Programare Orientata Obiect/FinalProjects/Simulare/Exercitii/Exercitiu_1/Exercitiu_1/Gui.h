//
// Created by david on 17.05.2022.
//

#ifndef PARTIAL_RECAP_2_GUI_H
#define PARTIAL_RECAP_2_GUI_H
#include <QtWidgets>
#include "Service.h"


class Gui: public  QWidget{
private:
    Service& service;
    void init();
    void conec();
    void reloadProcesoareList(vector<Procesor> lst);
    void reloadPlaciList(vector<PlacaDeBaza> lst);
    QListWidget* procesoareList = new QListWidget;
    QListWidget* placiList = new QListWidget;
    QHBoxLayout* mainL = new QHBoxLayout;

    QWidget* formDreapta =  new QWidget;
    QVBoxLayout* formDreaptaL = new QVBoxLayout;

    QLineEdit* namePlaca = new QLineEdit;
    QLineEdit* socluPlaca = new QLineEdit;
    QLineEdit* pretPlaca = new QLineEdit;

    QPushButton* addBtn = new QPushButton("adaugă");

    QLabel* pret = new QLabel("");

public:
    Gui(Service& service):service{service}{
        init();
        conec();
        reloadProcesoareList(service.getProcesoare());
        reloadPlaciList(service.getPlaciDeBaza());
    };
};


#endif //PARTIAL_RECAP_2_GUI_H
