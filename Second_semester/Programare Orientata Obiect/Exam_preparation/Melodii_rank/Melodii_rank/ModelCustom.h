#pragma once
#include "Service.h"
//#include "qwidget.h"
//#include "qlabel.h"
//#include "qlayout.h"
//#include "qlineedit.h"
#include <QtCore>

using namespace std;

class List :public QAbstractTableModel {
private:
    vector<Melodie>melodii;
    Service& srv;
public:

    /*
    Constructorul implicit
    melodii->vector<Melodie>, vectorul cu melodii
    */
    List(vector<Melodie>melodii, Service& srv) :melodii{ melodii }, srv{ srv } {}

    /*
    Seteaza numarul de randuri din tabel
    */
    int rowCount(const QModelIndex& parent = QModelIndex()) const override {
        return melodii.size(); // Avem atatea randuri in tabel
    }

    /*
    Seteaza numarul de coloane din tabel
    */
    int columnCount(const QModelIndex& parent = QModelIndex()) const override {
        return 5; // Avem 5 coloane in tabel
    }

    /*
    Modifica data din tabel (se apeleaza de fiecare data cand o celula e modificata)
    */
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override {
        // Setam celula de pe pozitia [index.row(),index.column)
        if (role == Qt::DisplayRole) {

            auto c = melodii[index.row()]; // Melodia este cea de pe randul selectat
            if (index.column() == 0) {
                return to_string(c.getId()).c_str();
            }
            else if (index.column() == 1) {
                return to_string(c.getRank()).c_str();
            }
            else if (index.column() == 2) {
                return c.getTitlu().c_str();
            }
            else if (index.column() == 3) {
                return c.getArtist().c_str();
            }
            else if (index.column() == 4) {
                return to_string(srv.getFr(c.getRank())).c_str();
            }
        }

        return QVariant{};
    }
    /*
    Schimba melodiile din tabel
    melodi->vector<Melodie>, melodiile care vor fi puse in tabel
    */
    void schimba_melodii(vector<Melodie> melodi) {
        melodii = melodi;
        auto topLeft = createIndex(0, 0); // Indicele din stanga sus
        auto bottomR = createIndex(rowCount(), columnCount()); // Indicele din dreapta jos
        emit layoutChanged();
        emit dataChanged(topLeft, bottomR); // Umplem tot tabelul de stanga sus pana dreapta jos ( apeleaza functia "data" )
    }

    /*
    Seteaza headearele
    */
    QVariant headerData(int section, Qt::Orientation orientation, int role) const {
        if (role == Qt::DisplayRole) {
            if (orientation == Qt::Horizontal) // Headere Orizontale
            {
                if (section == 0) // Sectiunea practic e nr coloanei (in header)
                    return "ID";
                if (section == 1)
                    return "RANK";
                if (section == 2)
                    return "TITLU";
                if (section == 3)
                    return "ARTIST";
                if (section == 4)
                    return "FR";
                return "";
            }
        }
        return QVariant{};
    }
};