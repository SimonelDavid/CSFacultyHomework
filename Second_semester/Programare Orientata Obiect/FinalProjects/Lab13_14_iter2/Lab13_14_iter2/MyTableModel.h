#pragma once
#include <QAbstractTableModel>
#include <QBrush>
#include <Qt>
#include <qfont.h>
#include "Medicament.h"
#include <vector>
#include <qdebug.h>
using std::vector;


class MyTableModel :public QAbstractTableModel {
	std::vector<Medicament> meds;
public:
	MyTableModel(const std::vector<Medicament>& meds) :meds{ meds } {
	}

	int rowCount(const QModelIndex& parent = QModelIndex()) const override {
		return meds.size();
	}
	int columnCount(const QModelIndex& parent = QModelIndex()) const override {
		return 4;
	}
	//Returns the data stored under the given role for the item referred to by the index.
	QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override {
		qDebug() << "row:" << index.row() << " col:" << index.column() << " role" << role;
		//qDebug() << index.data(role);

		if (role == Qt::ForegroundRole) {
			auto song = this->meds[index.row()];
			if (song.getProducator() == "Bayer") {
				return QBrush(Qt::magenta);
			}
		}
		if (role == Qt::FontRole) {
			QFont f;
			f.setItalic(index.row() % 10 == 1);
			f.setBold(index.row() % 10 == 1);
			return f;
		}
		if (role == Qt::BackgroundRole) {

			int row = index.row();
			QModelIndex i = index.sibling(index.row(), 1);
			if (i.data().toString() == "Deep Purple") {
				QBrush bg(Qt::yellow);
				return bg;
			}
		}

		if (role == Qt::DisplayRole) {

			Medicament p = meds[index.row()];
			if (index.column() == 0) {
				return QString::fromStdString(p.getDenumire());
			}
			else if (index.column() == 1) {
				return QString::number(p.getPret());
			}
			else if (index.column() == 2) {
				return QString::fromStdString(p.getProducator());
			}
			else if (index.column() == 3) {
				return QString::number(p.getSubstantaActiva());
			}
		}

		return QVariant{};
	}

	void setSongs(const vector<Medicament> meds) {
		this->meds = meds;
		auto topLeft = createIndex(0, 0);
		auto bottomR = createIndex(rowCount(), columnCount());
		emit dataChanged(topLeft, bottomR);
	}

	Qt::ItemFlags flags(const QModelIndex& /*index*/) const {
		return Qt::ItemIsSelectable | Qt::ItemIsEditable | Qt::ItemIsEnabled;
	}

	QVariant headerData(int section, Qt::Orientation orientation, int role) const
	{
		if (role == Qt::DisplayRole)
		{
			if (orientation == Qt::Horizontal) {
				switch (section)
				{
				case 0:
					return tr("Denumire");
				case 1:
					return tr("Pret");
				case 2:
					return tr("Producator");
				case 3:
					return tr("Substanta Activa");
				default:
					return QString("");
				}
			}
		}
		return QVariant();
	}
};
