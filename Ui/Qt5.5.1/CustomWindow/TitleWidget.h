/*
CustomWindow is a simple and easy to use custom top-level window (for Windows OS) created by Qt

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or 
(at your option) any later version.

This program is distributed in the hope that it will be useful, but
WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
See the GNU General Public License for more details
Full License:https://github.com/QtTools/CustomWindow/blob/master/LICENSE

Copyright (c) 2016 Iman Ahmadvand (IMAN4K), Contact:iman72411@yahoo.com
*/

#pragma once

#include <QWidget>
#include <QPainter>
#include <QTimer>
#include <QMouseEvent>
#include <QPixmap>
#include <QLine>
#include <QRect>
#include <QPen>


class TitleWidget : public QWidget
{
	Q_OBJECT

public:
	explicit TitleWidget(QWidget *parent = 0);
	~TitleWidget();
	void setDisable(bool disable);
	bool isDisable() const;
	void setSize(const qint16 &size);
	void setColor(const QColor &color);
	QColor color() const;

protected:
	enum State {
		None = 0x00,
		Disable = 0x01,
		Hover = 0x02,
		Over = 0x03
	};
	State _state;
	qint16 _size;
	qint16	_rait;
	QColor _color;
	qreal _weight;
	qreal _opacity;
	qreal _step;
	QTimer _timer;

protected:
	void mousePressEvent(QMouseEvent *e) Q_DECL_OVERRIDE;
	void enterEvent(QEvent *) Q_DECL_OVERRIDE;
	void leaveEvent(QEvent *) Q_DECL_OVERRIDE;
	QSize minimumSizeHint() const Q_DECL_OVERRIDE;
	QSize sizeHint() const Q_DECL_OVERRIDE;

	signals:
	void clicked();

public slots:
	void timercall();
};


class CloseButton : public TitleWidget {

public:
	explicit CloseButton(const qint16 &size);
	~CloseButton();

private:
	QLine _line0;
	QLine _line1;
	QLine _line2;
	QVector<QLine> _cross;

protected:
	void paintEvent(QPaintEvent *) Q_DECL_OVERRIDE;
};


class MaximizeButton : public TitleWidget {
public:
	explicit MaximizeButton(const qint16 &size);
	~MaximizeButton();
	void setMaximized(bool set);

private:
	bool _maximized;
	QLine _line0;
	QLine _line1;
	QLine _line2;
	QLine _line3;
	QLine _line4;
	QLine _line5;
	QLine _line6;
	QLine _line7;
	QVector<QLine> _maximize;
	QVector<QLine> _restore;

protected:
	void paintEvent(QPaintEvent *) Q_DECL_OVERRIDE;
};


class MinimizeButton : public TitleWidget {

public:
	explicit MinimizeButton(const qint16 &size);
	~MinimizeButton();

private:
	QLine _line0;
	
protected:
	void paintEvent(QPaintEvent *) Q_DECL_OVERRIDE;
};


class Icon : public QWidget {
	Q_OBJECT

public:
	explicit Icon();
	~Icon();
	void setPixmap(const QPixmap &_pixmap, const qint16 &_width);

private:
	QPixmap _pixelmap;
	QRect _rect;
	qint16 _size;

protected:
	void paintEvent(QPaintEvent *) Q_DECL_OVERRIDE;
};
