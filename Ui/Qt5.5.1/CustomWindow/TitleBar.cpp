#include "TitleBar.h"


TitleBar::TitleBar(QWidget *parent)
	:QWidget(parent)
{
	setFixedHeight(35);
	_l.addStretch(10);
	_l.addWidget(_minimize);
	_l.addWidget(_maxmimize);
	_l.addWidget(_close);
	_l.setMargin(10);
	_l.setSpacing(15);
	_l.insertStretch(0);
	setLayout(&_l);
}


TitleBar::~TitleBar() {}

void TitleBar::paintEvent(QPaintEvent *) {
	QPainter painter(this);
	painter.setBrush(_background);
	painter.setPen(Qt::NoPen);
	painter.drawRect(0, 0, width(), height());
}
