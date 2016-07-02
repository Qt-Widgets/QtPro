#include "Input.h"

Input::Input(QWidget *parent) : QWidget(parent),
_label("your name..."),
_brush("#62C0F7"),
_penWidth(4.0),
_margin(0.0),
_state(None),
_opacity(0.3),
_textPointSize(16.0),
_height(60),
_dividerPadding(4.0),
_textPadding(8.0),
_offset(0.0),
_fontFamily("Open Sans"),
_textwidth(30)
{
	connect(&_timer, SIGNAL(timeout()), this, SLOT(timercall()));
}

void Input::paintEvent(QPaintEvent *e) {
	QPainter p(this);

	p.setPen(QPen(QColor("#000000"), 1.0));
	p.setOpacity(0.3);
	p.drawLine(QPointF(0, height() - _dividerPadding), QPointF(width(), height() - _dividerPadding));

	if (_state == FocusIn || _state == FocusOut) {
		_pen.setWidth(2.0);
		_pen.setColor(_brush);

		p.setOpacity(1.0);
		p.setPen(_pen);
		p.drawLine(QPointF(_margin, height() - _dividerPadding), QPointF(width() - _margin, height() - _dividerPadding));
	}

	p.setOpacity(1.0);
	p.setFont(QFont(_fontFamily, _textPointSize));
	if (_state== FocusIn || _state == FocusOut) {
		p.setPen(QPen(_brush));
	}
	else
	{
		p.setOpacity(0.3);
		p.setPen(QPen(QColor("#000000")));
	}
	p.drawText(QRectF(QPointF(0, height() - _textPadding - _textwidth - _offset), QPointF(rect().width(), rect().height() - _textPadding)), Qt::AlignLeft, " " + _label);

	//p.setOpacity(0.120);
	//p.fillRect(rect(), QColor("#000000"));
}

void Input::focusInEvent(QFocusEvent *e) {
	_timer.start(2);
	_state = FocusIn;
}

void Input::focusOutEvent(QFocusEvent *e) {
	_timer.start(2);
	_state = FocusOut;
}

void Input::enterEvent(QEvent *e) {
	_state = Hover;
	setCursor(Qt::IBeamCursor);
	QWidget::enterEvent(e);
}

void Input::leaveEvent(QEvent *e) {
	_state = Over;
	unsetCursor();
	QWidget::leaveEvent(e);
}

void Input::mousePressEvent(QMouseEvent *e) {
	if (e->buttons() & Qt::LeftButton) {
		setFocus();
	}
}

void Input::mouseReleaseEvent(QMouseEvent *e) {

}

void Input::keyPressEvent(QKeyEvent *e) {
	if (e->type() == QEvent::KeyPress || e->key() == Qt::Key_Tab) {
		setFocus();
	}
}

QSize Input::minimumSizeHint() const {
	return QSize(120, 60);
}

QSize Input::sizeHint() const {
	return minimumSizeHint();
}

void Input::resizeEvent(QResizeEvent *e) {
	_margin = width() / 2;
	_step = 0.8;
}

void Input::setHintText(const QString &placeholder) {

}

void Input::setText(const QString &text) {

}

QString Input::text() const {
	return _text;
}

void Input::timercall() {
	switch (_state)
	{
	case None: break;
	case Hover: break;
	case Over: break;
	case FocusIn:
	{
		_margin -= _step;
		_offset += 0.25;
		_textPointSize -= 0.1;
		if (_margin <= 0.0) {
			_timer.stop();
		}
		repaint();
	} break;
	case FocusOut:
	{
		_margin += _step;
		_offset -= 0.25;
		_textPointSize += 0.1;
		if (_margin >= width() / 2) {
			_timer.stop();
			_state = None;
		}
		repaint();
	} break;
	}
}
