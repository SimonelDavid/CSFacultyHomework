#pragma once
#include <QAbstractTableModel>
#include "pet.h"
#include <vector>
#include <qdebug.h>

class MyTableModel :public QAbstractTableModel {
	std::vector<Pet> pets;
public:
	MyTableModel(const std::vector<Pet>& pets) :pets{ pets } {
	}

	int rowCount(const QModelIndex & parent = QModelIndex()) const override{
		return pets.size();
	}
	int columnCount(const QModelIndex & parent = QModelIndex()) const override {
		return 3;
	}

	QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const override {
		qDebug() << "row:" << index.row() << " col:" << index.column()<<" role"<<role;
		if (role == Qt::ForegroundRole) {
			Pet p = pets[index.row()];
			if (p.getPrice() > 0) {
				return QBrush{ Qt::red };
			}
		}
		if (role == Qt::DisplayRole) {
		
			Pet p = pets[index.row()];
			if (index.column() == 0) {
				return QString::fromStdString(p.getSpecies());
			}else if (index.column() == 1) {
				return QString::fromStdString(p.getType());
			}
			else if (index.column() == 2) {
				return QString::number(p.getPrice());
			}
		}
		
		return QVariant{};
	}

	void setPets(const vector<Pet>& pets) {
		this->pets = pets;
		auto topLeft = createIndex(0,0);
		auto bottomR = createIndex(rowCount(), columnCount());
		emit dataChanged(topLeft, bottomR);
	}
};