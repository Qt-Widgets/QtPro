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

#include "TitleBar.h"

TitleBar::TitleBar(QWidget *parent) :_parent(parent), _hastext(false), _hasicon(false), _draging(false), _start(0, 0),
_background("#00A0B4"), _width(36), _radius(4.0), _Title(""), _close(_width), _minimize(_width), _maxmimize(_width)
{
	setFixedHeight(_width);
	setAttribute(Qt::WA_StaticContents);
	connect(&_close, SIGNAL(clicked()), parent, SLOT(close()));
	connect(&_maxmimize, SIGNAL(clicked()), this, SLOT(changeState()));
	connect(&_minimize, SIGNAL(clicked()), parent, SLOT(showMinimized()));
}

TitleBar::~TitleBar() {}

void TitleBar::setText(const QString &text) {
	_Title.setMinimumHeight((_width / 2) + 3);
	_Title.setStyleSheet("color:#FFFFFF;");
	_Title.setFont(QFont("San Francisco Display Thin", 13));
	if (!text.isEmpty()) {
		_hastext = true;
		_Title.clear();
		_Title.setText(" " + text);
	} else {
		_hastext = false;
		_Title.clear();
		_Title.setText("");
	}
}

void TitleBar::setIcon(const QPixmap &pixelmap) {
	if (!_hasicon) {
		_hasicon = true;
	} 
	_windowIcon.setPixmap(pixelmap, _width);
}

void TitleBar::paintEvent(QPaintEvent *) {
	QPainter painter(this);
	painter.setBrush(_background);
	painter.setPen(Qt::NoPen);
	painter.setRenderHint(QPainter::Antialiasing);

	QPainterPath path;
	path.setFillRule(Qt::WindingFill);
	path.addRoundedRect(QRect(0, 0, width(), height()), _radius, _radius);
	//bottomRight
	path.addRect(QRect(width() - _radius, height() - _radius, _radius, _radius));
	//bottomLeft
	path.addRect(QRect(0, height() - _radius, _radius, _radius));
	painter.drawPath(path.simplified());
}

void TitleBar::mousePressEvent(QMouseEvent *e) {
	if (e->buttons() & Qt::LeftButton) {
		if ( _hasicon && _windowIcon.rect().contains(e->pos())) {
			e->ignore();
		} else {
			_start = e->globalPos() - _parent->frameGeometry().topLeft();
			_draging = true;
			e->accept();
		}
	}
}

void TitleBar::mouseReleaseEvent(QMouseEvent *e) {
	_draging = false;
	_start = QPoint(0, 0);
}

void TitleBar::mouseMoveEvent(QMouseEvent *e) {
	if (e->buttons() & Qt::LeftButton) {
		if (_draging) {
			if (_parent->windowState().testFlag(Qt::WindowMaximized)) {
				_parent->setWindowState(_parent->windowState() & ~Qt::WindowMaximized);
				_start = e->globalPos() - ((frameGeometry().topLeft()) + (frameGeometry().topRight())) / 2;
				e->accept();
			} else {
				_parent->move(e->globalPos() - _start);
				_maxmimize.setMaximized(false);
				e->accept();
			}
		}
	} else if (_draging) {
		_draging = false;
	}
}

void TitleBar::mouseDoubleClickEvent(QMouseEvent *e) {
	if (e->type() == QMouseEvent::MouseButtonDblClick & e->button() == Qt::LeftButton) {
		if (!_maxmimize.isDisable()) {
			Qt::WindowStates s(_parent->windowState());
			if (s.testFlag(Qt::WindowMaximized)) {
				_parent->setWindowState(s & ~Qt::WindowMaximized);
				_maxmimize.setMaximized(false);
				e->accept();
			} else {

				_maxmimize.setMaximized(true);
				_parent->setWindowState(s | Qt::WindowMaximized);
				e->accept();
			}
		}
	}
}

void TitleBar::showEvent(QShowEvent *) {
	_layout0.addWidget(&_windowIcon);
	_layout0.addWidget(&_Title);
	_layout0.addStretch();
	_layout0.addWidget(&_minimize);
	_layout0.addWidget(&_maxmimize);
	_layout0.addWidget(&_close);
	_layout0.setMargin(0);
	_layout0.setSpacing(0);
	setLayout(&_layout0);
}

void TitleBar::changeState() {
	if (_parent->windowState().testFlag(Qt::WindowMaximized)) {
		_maxmimize.setMaximized(false);
		_parent->setWindowState(_parent->windowState() & ~Qt::WindowMaximized);
	} else {
		_maxmimize.setMaximized(true);
		_parent->setWindowState(_parent->windowState() | Qt::WindowMaximized);
	}
}

void TitleBar::setRadius(const qreal &radius) {
	_radius = radius;
	update();
}

void TitleBar::setBackground(const QColor &background) {
	_background = background;
	update();
}

void TitleBar::closeDisable(bool disable) {
	if (disable) {
		_close.setDisable(disable);
	} else {
		_close.setDisable(disable);
	}
}

void TitleBar::maximizeDisable(bool disable) {
	if (disable) {
		_maxmimize.setDisable(disable);
	} else {
		_maxmimize.setDisable(disable);
	}
}

void TitleBar::minimizeDisable(bool disable) {
	if (disable) {
		_minimize.setDisable(disable);
	} else {
		_minimize.setDisable(disable);
	}
}

QPixmap TitleBar::pixmap() const {
	return _windowIcon.pixelmap();
}

QColor TitleBar::background() const {
	return _background;
}

