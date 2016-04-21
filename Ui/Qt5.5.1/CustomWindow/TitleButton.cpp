#include "TitleButton.h"


TitleButton::TitleButton(Type _tp ,QWidget *parent)
	:QWidget(parent)
{
	setFixedSize(14, 14);
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
	switch (_type)
	{
	case Close:
	{
		painter.setPen(QPen(QColor("#00A0B4")));
		painter.drawRect(rect());
		painter.setPen(QPen(_color, _weight));
		painter.setOpacity(_opacity);
		painter.drawLine(0, 0, width(), height());
		painter.drawLine(0, height(), width(), 0);
	}
		break;
	case Minimize:
	{
		painter.setPen(QPen(QColor("#00A0B4")));
		painter.drawRect(rect());
		painter.setPen(QPen(_color, _weight));
		painter.setOpacity(_opacity);
		painter.drawLine(0, height()-2, width()-2, height()-2);
	}
		break;
	case Maxmimize:
	{
		painter.setPen(QPen(QColor("#00A0B4")));
		painter.drawRect(rect());
		painter.setPen(QPen(_color, _weight));
		painter.setOpacity(_opacity);
		painter.drawLine(1, 0, 1, height()-2);
		painter.drawLine(0, height() - 2, width() - 2, height() - 2);
		painter.drawLine(0, 1, width() , 1);
		painter.drawLine(width() - 1, 0, width() - 1, height() - 2);
	}
		break;
	default:
		break;
	}
}

QSize TitleButton::minimumSizeHint() const {
	return QSize(10, 10);
}

QSize TitleButton::sizeHint() const {
	return QSize(13, 13);
}

void TitleButton::enterEvent(QEvent *) {
	_state = Hover;
	_timer.start(1);
}

void TitleButton::leaveEvent(QEvent *) {
	_state = Over;
	_timer.start(1);
}

void TitleButton::timercall() {
	switch (_state)
	{
	case TitleButton::Hover:
	{
		_opacity -= 0.002;
		if (_opacity < 0.750)
		{
			_timer.stop();
		}
	}
		break;
	case TitleButton::Over:
	{
		_opacity += 0.002;
		if (_opacity > 0.999)
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
