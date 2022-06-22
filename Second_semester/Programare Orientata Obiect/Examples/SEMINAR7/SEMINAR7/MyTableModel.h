#pragma once
#include <QAbstractTableModel>
#include <QBrush>
#include <Qt>
#include "Song.h"
#include <vector>
#include <qdebug.h>
using std::vector;


class MyTableModel :public QAbstractTableModel {
	std::vector<Song> songs;
public:
	MyTableModel(const std::vector<Song>& songs) :songs{ songs } {
	}

	int rowCount(const QModelIndex& parent = QModelIndex()) const override {
		return songs.size();
	}
	int columnCount(const QModelIndex& parent = QModelIndex()) const override {
		return 4;
	}
	//Returns the data stored under the given role for the item referred to by the index.
	QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override {
		qDebug() << "row:" << index.row() << " col:" << index.column() << " role" << role;
		//qDebug() << index.data(role);

		if (role == Qt::ForegroundRole) {
			auto song = this->songs[index.row()];
			if (song.getGen() == "indie rock") {
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

			Song p = songs[index.row()];
			if (index.column() == 0) {
				return QString::fromStdString(p.getTitlu());
			}
			else if (index.column() == 1) {
				return QString::fromStdString(p.getArtist());
			}
			else if (index.column() == 2) {
				return QString::fromStdString(p.getGen());
			}
			else if (index.column() == 3) {
				return QString::number(p.getDurata());
			}
		}

		return QVariant{};
	}

	void setSongs(const vector<Song> songs) {
		this->songs = songs;
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
					return tr("Titlu");
				case 1:
					return tr("Artist");
				case 2:
					return tr("Gen");
				case 3:
					return tr("Durata");
				default:
					return QString("");
				}
			}
		}
		return QVariant();
	}
};
