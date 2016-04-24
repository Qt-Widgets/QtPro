#include "TitleButton.h"


TitleButton::TitleButton(Type _tp ,QWidget *parent)
	:QWidget(parent)
{
	setMouseTracking(true);
	setFixedSize(_size, _size);
	_state = Normal;
	connect(&_timer, SIGNAL(timeout()), this, SLOT(timercall()));
	switch (_tp)
	{
	case Close:
		_type = Close;
		break;
	case Minimize:
		_type = Minimize;
		break;
	case Maxmimize:
		_type = Maxmimize;
		break;
	}
}

TitleButton::~TitleButton() {}

void TitleButton::paintEvent(QPaintEvent *) {
	QPainter painter(this);
	painter.setRenderHint(QPainter::Antialiasing);
	painter.setPen(QPen(_color, _weight));
	painter.setOpacity(_opacity);
	switch (_type)
	{
	case Close:
	{
		painter.drawLine(1, 1, _size - 2, _size - 2);
		painter.drawLine(1, _size - 2, _size - 2, 1);
	}
	break;
	case Minimize:
	{
		painter.drawLine(0, _size - 1, _size, _size - 1);
	}
	break;
	case Maxmimize:
	{
		if (_maxmized)
		{
			// inner
			painter.drawLine(1, 5, 1, 13);
			painter.drawLine(3, 13, 10, 13);
			painter.drawLine(10, 11, 10, 5);
			painter.drawLine(8, 5, 3, 5);
			// outer
			painter.drawLine(4, 3, 4, 1);
			painter.drawLine(6, 1, 14, 1);
			painter.drawLine(14, 3, 14, 11);
			painter.drawLine(12, 11, 12, 11);
		}
		else
		{
			painter.drawLine(1, 1, _size-1, 1);
			painter.drawLine(_size - 1, 3, _size - 1, _size - 1);
			painter.drawLine(_size - 3, _size - 1, 1, _size - 1);
			painter.drawLine(1, _size - 3, 1, 3);
		}
	}
	break;
	}
}

void TitleButton::enterEvent(QEvent *) {
	_state = Hover;
	_timer.start(1);
}

void TitleButton::leaveEvent(QEvent *) {
	_state = Over;
	_timer.start(1.5);
}

void TitleButton::mousePressEvent(QMouseEvent *e) {
	if (e->type() == QEvent::MouseButtonPress && e->button() == Qt::LeftButton)
	{
		e->accept();
		emit clicked();
	}
}

QSize TitleButton::sizeHint() const {
	return QSize(15, 15);
}

QSize TitleButton::minimumSizeHint() const {
	return QSize(10, 10);
}

void TitleButton::timercall() {
	switch (_state)
	{
	case TitleButton::Hover:
	{
		_opacity += _step;
		if (_opacity > 1.000)
		{
			_timer.stop();
		}
	}
		break;
	case TitleButton::Over:
	{
		_opacity -= _step;
		if (_opacity < 0.550)
		{
			_timer.stop();
		}
	}
		break;
	default:
		break;
	}
	update();
}

void TitleButton::setMaximized(bool _control) {
	_maxmized = _control;
	if (_control)
	{
		setFixedSize(15, 15);
	}
	else
	{
		setFixedSize(14, 14);
	}
	update();
}
