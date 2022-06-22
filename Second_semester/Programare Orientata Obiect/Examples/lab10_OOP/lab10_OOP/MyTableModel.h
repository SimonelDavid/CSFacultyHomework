#pragma once
#include <QAbstractTableModel>
#include <QBrush>
#include <Qt>
#include "Locatar.h"
#include <vector>
#include <qdebug.h>
#include <qfont.h>
#include <qtableview.h>
#include <qwidget.h>
using std::vector;


class MyTableModel :public QAbstractTableModel {
	std::vector<Locatar> locatari;
public:
	MyTableModel(const std::vector<Locatar>& locatari) :locatari{ locatari } {
	}

	int rowCount(const QModelIndex& parent = QModelIndex()) const override {
		return locatari.size();
	}
	int columnCount(const QModelIndex& parent = QModelIndex()) const override {
		return 4;
	}
	//Returns the data stored under the given role for the item referred to by the index.
	QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override {
		qDebug() << "row:" << index.row() << " col:" << index.column() << " role" << role;
		

		if (role == Qt::ForegroundRole) {
			auto locatar = this->locatari[index.row()];
			if (locatar.getType() == "apartament") {
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
			if (i.data().toString() == "Ion") {
				QBrush bg(Qt::yellow);
				return bg;
			}
		}

		if (role == Qt::DisplayRole) {

			Locatar p = locatari[index.row()];
			if (index.column() == 0) {
				return QString::number(p.getApartment());
			}
			else if (index.column() == 1) {
				return QString::fromStdString(p.getName());
			}
			else if (index.column() == 2) {
				return QString::number(p.getSurface());
			}
			else if (index.column() == 3) {
				return QString::fromStdString(p.getType());
			}
		}

		return QVariant{};
	}

	void setLocatari(const vector<Locatar>& locatari) {
		this->locatari = locatari;
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
					return tr("Apartament");
				case 1:
					return tr("Nume");
				case 2:
					return tr("Suprafata");
				case 3:
					return tr("Tip");
				default:
					return QString("");
				}
			}
		}
		return QVariant();
	}
};


/*
#pragma once
#include <qwidget.h>
#include <qtableview.h>
#include "Locatar.h"
#include <vector>
#include <QAbstractTableModel>



using std::vector;




class MyTableModel : public QAbstractTableModel {
	vector<Locatar> locatari;
public:
	MyTableModel(const vector<Locatar>& _locatari) : locatari{ _locatari } {}

	int rowCount(const QModelIndex& parent = QModelIndex()) const override {
		return locatari.size();
	}



	int columnCount(const QModelIndex& parent = QModelIndex()) const override {
		return 4;
	}



	QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override {
		if (role == Qt::BackgroundRole) {
			switch (index.row() % 3) {
			case 0: return QBrush{ QColor{235,91,91} }; break;
			case 1: return QBrush{ QColor{250,253,162} }; break;
			case 2: return QBrush{ QColor{136,205,252} }; break;
			default: break;
			}
		}



		if (role == Qt::DisplayRole) {
			Locatar l = locatari[index.row()];
			switch (index.column()) {
			case 0: return QString::fromStdString(std::to_string(l.getApartment())); break;
			case 1: return QString::fromStdString(l.getName()); break;
			case 2: return QString::fromStdString(std::to_string(l.getSurface())); break;
			case 3: return QString::fromStdString(l.getType()); break;
			default: break;
			}
		}



		if (role == Qt::FontRole) {
			int rand = index.row();
			switch (rand % 3) {
			case 0: { QFont f("Arial", 10); f.setUnderline(true); return f; break; }
			case 1: { QFont f("Comic Sans MS", 10); f.setBold(true); return f; break; }
			case 2: { QFont f("Palatino Linotype", 10); f.setItalic(true); return f; break; }
			default: break;
			}
		}
		return QVariant{};
	}



	QVariant headerData(int section, Qt::Orientation orientation, int role) const override
	{
		if (orientation == Qt::Horizontal) {
			if (role == Qt::DisplayRole) {
				switch (section) {
				case 0: return "Apartament"; break;
				case 1: return "Nume locatar"; break;
				case 2: return "Suprafata"; break;
				case 3: return "Tipul de comfort"; break;
				default: break;
				}
			}
		}

		if (orientation == Qt::Vertical) {
			if (role == Qt::DisplayRole) {
				return section + 1;
			}
		}

		return QVariant();
	}



	void seteazaLocatari(vector<Locatar>& locatari) {
		this->locatari = locatari;
		QModelIndex topLeft = createIndex(0, 0);
		QModelIndex bottomRight = createIndex(rowCount(), columnCount());
		emit dataChanged(topLeft, bottomRight);
	}
};
*/
