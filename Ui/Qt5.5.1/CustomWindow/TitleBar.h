#pragma once
#ifndef TITLEBAR_H
#define TITLEBAR_H

#include <QtWidgets>
#include "TitleButton.h"

class QWidget;
class QPainter;

class TitleBar : public QWidget {
	Q_OBJECT

private:
	QColor _background = "#00A0B4";
	QHBoxLayout _l;
public:
	TitleButton *_close = new TitleButton(Close), *_minimize = new TitleButton(Minimize), 
	            *_maxmimize = new TitleButton(Maxmimize);
	explicit TitleBar(QWidget *parent = 0);
	~TitleBar();
protected:
	virtual void paintEvent(QPaintEvent *);
};

#endif // !TITLEBAR_H

