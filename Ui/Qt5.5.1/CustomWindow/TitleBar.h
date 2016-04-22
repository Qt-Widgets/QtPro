#pragma once
#ifndef TITLEBAR_H
#define TITLEBAR_H

#include <QtWidgets>
#include "TitleButton.h"

class QWidget;
class QPainter;
class TitleButton;
class QHBoxLayout;

class TitleBar : public QWidget {
	Q_OBJECT

private:
	QColor _background = "#00A0B4";
	qint16 _width = 35;
	QHBoxLayout *_l = new QHBoxLayout(), *_primary = new QHBoxLayout(), *_secoundry = new QHBoxLayout();
	QLabel *_window_icon = new QLabel(), *_Title = new QLabel();
	bool _hastext = 0;
public:
	TitleButton *_close = new TitleButton(Close), *_minimize = new TitleButton(Minimize),
		        *_maxmimize = new TitleButton(Maxmimize);
	explicit TitleBar(QWidget *parent = 0);
	~TitleBar();
	void setText(const QString &_text);
	void setIcon(const QPixmap &_pixelmap);
protected:
	virtual void paintEvent(QPaintEvent *);
};

#endif // !TITLEBAR_H
