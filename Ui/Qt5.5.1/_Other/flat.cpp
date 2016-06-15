#include "flatbutton.h"
#include "shadow.h"

FlatButton::FlatButton(QWidget *parent) : QWidget(parent) {
	connect(&_timer, SIGNAL(timeout()), this, SLOT(timercall()));
	connect(this, SIGNAL(clicked()), this, SLOT(parent->close()));
	_font.setFamily(_fontfamily);
	_font.setPointSize(_pointsize);

	QFontMetrics fm(_font);
	qDebug() << fm.width(_text);
}

FlatButton::~FlatButton() {}

void FlatButton::paintEvent(QPaintEvent *) {
	QPainter p(this);
	p.setPen(Qt::NoPen);
	p.setRenderHint(QPainter::Antialiasing);

	QPainterPath path, path0;

	if (!_disabled) {
		p.setBrush(_back);
		p.setOpacity(1.0);

		path.addRoundedRect(QRect(0, 0, width(), height()), 2.0, 2.0);
		p.drawPath(path.simplified());

		p.setOpacity(_opacity2);
		p.setBrush(_back2);
		path0.addRoundedRect(0, 0, width(), height(), 2.0, 2.0);
		p.drawPath(path0.simplified());

		// text
		p.setOpacity(1.0);
		p.setFont(_font);
		p.setPen(_color);
		p.drawText(QRect(rect().x(), rect().y(), rect().width(), rect().height() - _margin), Qt::AlignCenter, _text);
	}
	else
	{
		p.setBrush(QColor("#000000"));
		p.setOpacity(0.120);
		path.addRoundedRect(QRect(0, 0, width(), height()), 2.0, 2.0);
		p.drawPath(path.simplified());

		p.setFont(_font);
		p.setPen(QColor("#000000"));
		p.setOpacity(0.260);
		p.drawText(QRect(rect().x(), rect().y(), rect().width(), rect().height() - _margin), Qt::AlignCenter, _text);
	}
}

void FlatButton::enterEvent(QEvent *) {
	_state = hover;
	_timer.start(2);
	setCursor(Qt::PointingHandCursor);
}

void FlatButton::leaveEvent(QEvent *) {
	_state = over;
	_timer.start(2);
}

void FlatButton::timercall() {
	switch (_state)
	{
	case FlatButton::hover:
	{
		_opacity2 += 0.001;
		if (_opacity2 > 0.120)
		{
			_timer.stop();
		}
		repaint();
	}
	break;
	case FlatButton::over:
	{
		_opacity2 -= 0.001;
		if (_opacity2 < 0.0)
		{
			_timer.stop();
		}
		repaint();
	} break;
	case FlatButton::pressed:
	{
		_opacity2 += 0.002;
		if (_opacity2 >= 0.320)
		{
			_timer.stop();
		}
		repaint();
	} break;
	case FlatButton::realese:
	{
		_opacity2 -= 0.002;
		if (_opacity2 <= 0.120)
		{
			_timer.stop();
		}
		repaint();
	} break;
	default: break;
	}
}

void FlatButton::mousePressEvent(QMouseEvent *e) {
	if (e->buttons() & Qt::LeftButton) {
		e->accept();
		_state = pressed;
		_timer.start(1);
		//_margin = -2;
		update();
	} else {
		e->ignore();
	}
}

void FlatButton::mouseReleaseEvent(QMouseEvent *e) {
	if (e->type() == QMouseEvent::MouseButtonRelease && e->button() == Qt::LeftButton) {
		e->accept();
		//emit clicked();
		_state = realese;
		_timer.start(1);
		//_margin = 0;
		update();
	} else {
		e->ignore();
	}
}

void FlatButton::setColor(const QColor &_brush) {
	_back = _brush;
}

void FlatButton::setText(const QString &text) {
	_text = text;
}

void FlatButton::setDisable(bool disabled) {
	_disabled = disabled;
}

QSize FlatButton::minimumSizeHint() const {
	QFontMetrics fm(_font);
	qDebug() << fm.width(_text);
	return QSize(fm.width(_text) + 16 + 16, 36); //padding = 16dp
}

QSize FlatButton::sizeHint() const {
	return minimumSizeHint();
}

Button::Button():
_state(None),
_disabled(false),
_text("")
{

}

Button::~Button() {};

void Button::mouseReleaseEvent(QMouseEvent *e) {
	if (e->type() == QMouseEvent::MouseButtonRelease && e->button() == Qt::LeftButton) {
		e->accept();
		emit clicked();
	} else {
		e->ignore();
	}
}

QSize Button::sizeHint() const {
	return sizeHint();
}

QSize Button::minimumSizeHint() const {
	return QSize(70, 36);
}

Shadow::Shadow() {
	//setAttribute(Qt::WA_TranslucentBackground);
}

void Shadow::paintEvent(QPaintEvent* ) {
	QPainter _painter(this);

	_painter.setPen(Qt::NoPen);

	int _width = width();
	int _height = height();

	QColor _start = QColor(218, 218, 218);
	QColor _end = QColor(255, 255, 255);

	QLinearGradient gradient;
	gradient.setColorAt(1.0, _start);
	gradient.setColorAt(0.0, _end);
	
	QPointF right0(_width / 2, _height / 2);
	QPointF right1(_width, _height / 2);
	gradient.setStart(right0);
	gradient.setFinalStop(right1);
	_painter.setBrush(QBrush(gradient));

	_painter.drawRoundRect(QRectF(QPointF(_width / 2, 0), QPointF(_width, _height)), 0.0, 0.0);

	_painter.setBrush(QBrush("#FFFFFF"));
	QPainterPath path;
	path.setFillRule(Qt::WindingFill);
	path.addRoundedRect(QRectF(QPointF(0, 0), QPointF(_width / 2, _height)), 0.0, 0.0);
	_painter.drawPath(path.simplified());
}
