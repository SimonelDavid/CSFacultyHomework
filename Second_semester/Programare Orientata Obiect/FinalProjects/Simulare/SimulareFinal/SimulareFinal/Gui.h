//
// Created by david on 20.05.2022.
//

#ifndef SIMULARE_GUI_H
#define SIMULARE_GUI_H
#include <QWidget>
#include <QtWidgets>
#include "Service.h"

class Gui: public QWidget{
private:
    Service& srv;
    ///initializare elemente gui
    void init();
    ///conecate butoane si alte evenimente
    void conect();
    ///reface lista
    void reload(const vector<Candidat>& list);

    QHBoxLayout* mainL =new QHBoxLayout;
    ///lista de candidati
    QListWidget* lst = new QListWidget;

    ///partea din mijloc
    QVBoxLayout* mijlocL = new QVBoxLayout;
    QWidget* mijloc = new QWidget;
    QLineEdit* numeTxt = new QLineEdit;
    QLineEdit* jobTxt = new QLineEdit;
    ///combo de schimbare status
    QComboBox* candCombo = new QComboBox;
    QPushButton* modBtn = new QPushButton("modifica");
    ///partea din dreapta
    QVBoxLayout* dreaptaL = new QVBoxLayout;
    QWidget* dreapta = new QWidget;
    QLineEdit* filterTxt = new QLineEdit;
    QPushButton* filterBtn = new QPushButton("filtreaza");
    ///buton care reface lista
    QPushButton* reloadBtn = new QPushButton("reîmprospătare");

public:
    Gui(Service& srv):srv{srv}{
        init();
        conect();
        reload(srv.getAll());
    }
};


#endif //SIMULARE_GUI_H
