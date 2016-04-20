#pragma once
#ifndef WINDOW_H
#define WINDOW_H

#include <QtWidgets>
class QWidget;
class QPainter;
class QGridLayout;

class Window : public QWidget {
	Q_OBJECT

private:
	QColor _background = "#FFFFFF";
	QGridLayout _layout;
public:
	explicit Window();
	~Window();
protected:
	virtual void paintEvent(QPaintEvent *);
};

#endif // !WINDOW_H
