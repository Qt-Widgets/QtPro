#include "switcher.h"

Switcher::Switcher(QWidget *parent) : QWidget(parent),
_opacity(0.000),
_x(0),
_disabled(false),
_switch(true),
_radius(10.0)
{

}

Switcher::Switcher(const QColor &color, QWidget *parent) : QWidget(parent),
_disabled(false),
_switch(true),
_x(0),
_opacity(0.000),
_radius(10.0)
{
	_brush = color;
}

void Switcher::mousePressEvent(QMouseEvent *e) {
	if (!_disabled) {
		if (e->buttons() & Qt::LeftButton) {
			e->accept();
		} else {
			e->ignore();
		}
	}
}

void Switcher::mouseReleaseEvent(QMouseEvent *e) {
	if (!_disabled) {
		if (e->type() == QMouseEvent::MouseButtonRelease && e->button() == Qt::LeftButton) {
			e->accept();
			emit toggled();
			_switch = _switch ? false : true;
		} else {
			e->ignore();
		}
	}
}

QSize Switcher::sizeHint() const {
	return minimumSizeHint();
}

QSize Switcher::minimumSizeHint() const {
	return QSize(_height * 2, _height);
}

void Switcher::timercall() {
	if (_switch)
	{

	}
	else
	{

	}
}
