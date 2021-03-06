/*
CustomWindow is a simple, native and easy to use custom top-level window created by Qt

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

#include "TitleWidget.h"

TitleWidget::TitleWidget(QWidget *parent) :QWidget(parent),
_state(None),
_opacity(0.650),
_step(0.004)
{
	setAttribute(Qt::WA_StaticContents);
	setMouseTracking(true);
	connect(&_timer, SIGNAL(timeout()), this, SLOT(timercall()));
}

TitleWidget::~TitleWidget() {}

void TitleWidget::mousePressEvent(QMouseEvent *e) {
	if (e->buttons() & Qt::LeftButton) {
		if (_state != Disable) {
			e->accept();
			emit clicked();
		} else {
			e->ignore();
		}
	}
}

void TitleWidget::enterEvent(QEvent *) {
	if (_state != Disable) {
		_state = Hover;
		_timer.start(1);
	}
}

void TitleWidget::leaveEvent(QEvent *) {
	if (_state != Disable) {
		_state = Over;
		_timer.start(1);
	}
}

QSize TitleWidget::minimumSizeHint() const {
	return sizeHint();
}

QSize TitleWidget::sizeHint() const {
	return QSize(_size, _size);
}

void TitleWidget::setDisable(bool disable) {
	if (disable) {
		_state = Disable;
		_opacity = 0.4;
	} else {
		_state = None;
	}
	repaint();
}

bool TitleWidget::isDisable() const {
	if (_state == Disable) {
		return true;
	} else {
		return false;
	}
}

void TitleWidget::setSize(const qint16 &size) {
	setFixedSize(size, size);
	_size = size;
	_rait = (sqrt((size*size) / 8) + 1) / 2;
	_weight = size / 24.0;
	_pen = QPen(QBrush("#FFFFFF", Qt::SolidPattern), _weight, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
}

void TitleWidget::timercall() {
	switch (_state)
	{
	case TitleWidget::None:
		break;
	case TitleWidget::Hover:
	{
		_opacity += _step;
		if (_opacity > 1.000) {
			_timer.stop();
			_state = None;
		}
		update();
	} break;
	case TitleWidget::Over:
	{
		_opacity -= _step;
		if (_opacity < 0.650) {
			_timer.stop();
			_state = None;
		}
		update();
	} break;
	}
}


CloseButton::CloseButton(const qint16 &size) {
	setSize(size);
	_line0 = QLine((size / 2) - _rait, (size / 2) - _rait, (size / 2), (size / 2));
	_line1 = QLine((size / 2), (size / 2), (size / 2) + _rait, (size / 2) + _rait);
	_line2 = QLine((size / 2) + _rait, (size / 2) - _rait, (size / 2) - _rait, (size / 2) + _rait);
	_cross << _line0 << _line1 << _line2;
}

CloseButton::~CloseButton() {}

void CloseButton::paintEvent(QPaintEvent *) {
	QPainter painter(this);
	painter.setRenderHint(QPainter::Antialiasing);
	painter.setPen(_pen);
	painter.setOpacity(_opacity);
	painter.drawLines(_cross);
}


MaximizeButton::MaximizeButton(const qint16 &size) : _maximized(false) {
	setSize(size);
	_line0 = QLine((size / 2) - _rait, (size / 2) - _rait + _weight, (size / 2) - _rait, (size / 2) + _rait);
	_line1 = QLine((size / 2) - _rait + _weight, (size / 2) + _rait, (size / 2) + _rait, (size / 2) + _rait);
	_line2 = QLine((size / 2) + _rait, (size / 2) + _rait - _weight + (_weight / 3), (size / 2) + _rait, (size / 2) - _rait);
	_line3 = QLine((size / 2) + _rait - _weight + (_weight / 3), (size / 2) - _rait, (size / 2) - _rait, (size / 2) - _rait);
	_maximize << _line0 << _line1 << _line2 << _line3;
	// inner
	_line0 = QLine((size / 2) - _rait, (size / 2) - _weight, (size / 2) - _rait, (size / 2) + _rait);
	_line1 = QLine((size / 2) - _rait + _weight, (size / 2) + _rait, (size / 2) + _weight + (_weight / 3), (size / 2) + _rait);
	_line2 = QLine((size / 2) + (_weight * 2), (size / 2) + _rait - (_weight / 2), (size / 2) + (_weight * 2), (size / 2) - _weight);
	_line3 = QLine((size / 2) + (_weight * 2), (size / 2) - (_weight * 2), (size / 2) - _rait, (size / 2) - (_weight * 2));
	// outer
	_line4 = QLine((size / 2) - (_weight * 2), (size / 2) - _weight - (_weight * 2), (size / 2) - (_weight * 2), (size / 2) - _rait);
	_line5 = QLine((size / 2) - _weight, (size / 2) - _rait, (size / 2) + _rait + (_weight / 2), (size / 2) - _rait);
	_line6 = QLine((size / 2) + _rait + (_weight / 2), (size / 2) - _rait + (_weight / 3) + (_weight / 2), (size / 2) + _rait + (_weight / 2), (size / 2) + _weight + (_weight / 3));
	_line7 = QLine((size / 2) + _rait + (_weight / 2), (size / 2) + (_weight * 2), (size / 2) + (_weight * 3) + (_weight / 2), (size / 2) + (_weight * 2));
	_restore << _line0 << _line1 << _line2 << _line3 << _line4 << _line5 << _line6 << _line7;
}

MaximizeButton::~MaximizeButton() {}

void MaximizeButton::paintEvent(QPaintEvent *) {
	QPainter painter(this);
	painter.setRenderHint(QPainter::Antialiasing);
	painter.setPen(_pen);
	painter.setOpacity(_opacity);
	if (_maximized) {
		painter.drawLines(_restore);
	} else {
		painter.drawLines(_maximize);
	}
}

void MaximizeButton::setMaximized(bool set) {
	_maximized = set;
	repaint();
}


MinimizeButton::MinimizeButton(const qint16 &size) {
	setSize(size);
	_line0 = QLine((size / 2) - _rait, (size / 2) + _rait, (size / 2) + _rait, (size / 2) + _rait);
}

MinimizeButton::~MinimizeButton() {}

void MinimizeButton::paintEvent(QPaintEvent *) {
	QPainter painter(this);
	painter.setRenderHint(QPainter::Antialiasing);
	painter.setPen(_pen);
	painter.setOpacity(_opacity);
	painter.drawLine(_line0);
}


Icon::Icon() {
	setAttribute(Qt::WA_StaticContents);
}

Icon::~Icon() {}

void Icon::paintEvent(QPaintEvent *e) {
	QPainter painter(this);
	painter.setPen(Qt::NoPen);
	painter.setRenderHint(QPainter::SmoothPixmapTransform);
	painter.drawPixmap(_rect, _pixelmap);
}

void Icon::setPixmap(const QPixmap &_pixmap, const qint16 &_width) {
	_size = _width;
	setFixedSize(_size, _size);
	_pixelmap = _pixmap.scaled(_size - ((_size / 6) * 2), _size - ((_size / 6) * 2), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
	_rect = QRect(_size / 6, _size / 6, _size - ((_size / 6) * 2), _size - ((_size / 6) * 2));
	update();
}

QPixmap Icon::pixelmap() const {
	return _pixelmap;
}
