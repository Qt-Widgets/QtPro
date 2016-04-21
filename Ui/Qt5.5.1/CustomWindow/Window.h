#pragma once
#ifndef WINDOW_H
#define WINDOW_H

#include <QtWidgets>
#include "TitleBar.h"

class QWidget;
class QPainter;
class QGridLayout;

class Window : public QWidget {
	Q_OBJECT

private:
	QColor _background = "#FFFFFF";
	QGridLayout _layout;
	TitleBar _titlebar;
public:
	explicit Window();
	~Window();
protected:
	virtual void paintEvent(QPaintEvent *);
	public slots:
	void closeEvent();
};

#endif // !WINDOW_H
