#include "CosReadOnlyGUI.h"
#include <random>
#include <qcolor.h>
#include <qbrush.h>

void CosReadOnlyGUI::update()
{
	repaint();
}

void CosReadOnlyGUI::paintEvent(QPaintEvent* ev)
{
	int x = 10;
	int y = 10;
	int w = 10;
	QPainter p{ this };
	p.setPen(Qt::yellow);
	p.setBrush(Qt::BrushStyle());

	for (auto u : ret.getReteta())
	{
		QString text = QString::fromStdString(u.getDenumire());
		QPointF point(x, y);
		p.drawText(point, text);
		p.drawRect(x, y+5, w, u.getPret()*5);
		x += 50;
	}
}
