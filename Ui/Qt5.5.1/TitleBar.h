#pragma once
#ifndef TITLEBAR_H
#define TITLEBAR_H

#include <QtWidgets>

class QWidget;

class TitleBar : public QWidget
{
	Q_OBJECT

public:
	TitleBar(QWidget *parent = 0);
	~TitleBar();
protected:
	virtual void mouseMoveEvent(QMouseEvent *e);
};

#endif // TITLEBAR_H
