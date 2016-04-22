#pragma once
#ifndef WINDOW_H
#define WINDOW_H

#include <QtWidgets>
#include "TitleBar.h"

class QWidget;
class QPainter;
class QGridLayout;
class TitleBar;

class Window : public QWidget {
	Q_OBJECT

private:
	QGridLayout *_layout = new QGridLayout();
	QByteArray _state;
	TitleBar *_titlebar = new TitleBar();
public:
	explicit Window(QWidget *parent = 0);
	explicit Window(const QString &_title, QWidget *parent = 0);
	~Window();
	void setIcon(const QPixmap &_icon);
protected:
	virtual void paintEvent(QPaintEvent *);
	public slots:
	void change();
};

#endif // !WINDOW_H
