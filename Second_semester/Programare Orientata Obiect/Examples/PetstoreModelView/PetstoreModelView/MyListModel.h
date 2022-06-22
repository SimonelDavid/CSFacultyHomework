#pragma once
#include<QAbstractListModel>
#include "pet.h"
#include <vector>
#include <qdebug.h>
class MyListModel :public QAbstractListModel {
	std::vector<Pet> pets;
public:
	MyListModel(const std::vector<Pet>& pets) :pets{ pets } {
	}

	int rowCount(const QModelIndex &parent = QModelIndex()) const override {
		return pets.size();
	}

	QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const override{
		if (role == Qt::DisplayRole) {
			qDebug() << "get row:" << index.row();
			auto sp = pets[index.row()].getSpecies();
			return QString::fromStdString(sp);
		}
		if (role == Qt::UserRole) {
			auto tp = pets[index.row()].getType();
			return QString::fromStdString(tp);
		}
		if (role == Qt::BackgroundRole) {
			if (pets[index.row()].getSpecies()[0] == 'R') {
				return QColor(Qt::red);
			}
		}
		return QVariant{};
	}
};