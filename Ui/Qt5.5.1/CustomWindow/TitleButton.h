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
		painter.drawLine(0, 0, width(), height());
		painter.drawLine(0, height(), width(), 0);
	}
		break;
	case Minimize:
	{
		painter.drawLine(0, height()-2, width()-2, height()-2);
	}
		break;
	case Maxmimize:
	{
		painter.drawLine(1, 2, 1, height()-3);
		painter.drawLine(0, height() - 2, width() - 2, height() - 2);
		painter.drawLine(0, 1, width()-2 , 1);
		painter.drawLine(width() - 1, 0, width() - 1, height() - 2);
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
	_timer.start(3);
}

void TitleButton::mousePressEvent(QMouseEvent *e) {
	if (e->type() == QEvent::MouseButtonPress && e->button() == Qt::LeftButton)
	{
		Qt::MouseButton button = e->button();
		e->accept();
		emit clicked(button);
	}
}

QSize TitleButton::sizeHint() const {
	return QSize(13, 13);
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
		if (_opacity < 0.750)
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

void TitleButton::clicked(Qt::MouseButton _button) {
	Q_UNUSED(_button);
	qDebug("////////////////Clicked/////////////////");
}
