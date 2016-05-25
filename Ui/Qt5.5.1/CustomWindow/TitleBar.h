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
#ifndef TITLEBAR_H
#define TITLEBAR_H

#include "TitleWidget.h"
#include "qt_windows.h"
#include <QWidget>
#include <QPainter>
#include <QHBoxLayout>
#include <QLabel>
#include <QColor>
#include <QPoint>
#include <QPixmap>
#include <QMouseEvent>
#include <QDebug>

class TitleBar : public QWidget {
	Q_OBJECT

public:
	explicit TitleBar(QWidget *parent = 0);
	~TitleBar();
	void setText(const QString &text);
	void setIcon(const QPixmap &pixelmap);
	void setRadius(const qreal &radius);
	void setBackground(const QColor &background);
	void closeDisable(bool disable);
	void maximizeDisable(bool disable);
	void minimizeDisable(bool disable);
	QPixmap pixmap() const;
	QColor background() const;

private:
	QWidget *_parent;
	bool _hastext;
	bool _hasicon;
	bool _draging;
	QPoint _start;
	QColor _background;
	qint16 _width;
	qreal _radius;
	QLabel _Title;
	CloseButton _close;
	MinimizeButton _minimize;
	MaximizeButton _maxmimize;
	QHBoxLayout _layout0;
	Icon _windowIcon;

protected:
	void paintEvent(QPaintEvent *) Q_DECL_OVERRIDE;
	void mousePressEvent(QMouseEvent *e) Q_DECL_OVERRIDE;
	void mouseReleaseEvent(QMouseEvent *e) Q_DECL_OVERRIDE;
	void mouseMoveEvent(QMouseEvent *e) Q_DECL_OVERRIDE;
	void mouseDoubleClickEvent(QMouseEvent *e) Q_DECL_OVERRIDE;
	void showEvent(QShowEvent *) Q_DECL_OVERRIDE;

	public slots:
	void changeState();
};

#endif // !TITLEBAR_H

