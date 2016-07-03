#include "Input.h"

Input::Input(QWidget *parent) : QWidget(parent),
_label("Input..."),
_brush("#62C0F7"),
_dividerMargin(0.0),
_state(None),
_labelPointSize(16.0),
_height(60),
_dividerPadding(4.0),
_textPadding(8.0),
_labelMargin(0.0),
_fontFamily("Open Sans Light"),
_textwidth(30)
{
	_font.setFamily(_fontFamily);
	_font.setPointSizeF(_labelPointSize);
	setFocusPolicy(Qt::TabFocus);
	connect(&_timer, SIGNAL(timeout()), this, SLOT(timercall()));
}

Input::Input(const QString &placeholder, QWidget *parent) : QWidget(parent),
_label(placeholder),
_brush("#62C0F7"),
_dividerMargin(0.0),
_state(None),
_labelPointSize(16.0),
_height(60),
_dividerPadding(4.0),
_textPadding(8.0),
_labelMargin(0.0),
_fontFamily("Open Sans"),
_textwidth(30)
{
	_font.setFamily(_fontFamily);
	_font.setPointSizeF(_labelPointSize);
	connect(&_timer, SIGNAL(timeout()), this, SLOT(timercall()));
}

void Input::paintEvent(QPaintEvent *e) {
	QPainter p(this);

	p.setPen(QPen(QColor("#000000"), 1.0));
	p.setOpacity(0.2);
	p.drawLine(QPointF(0, height() - _dividerPadding), QPointF(width(), height() - _dividerPadding));

	if (_state == FocusIn || _state == FocusOut) {
		p.setOpacity(1.0);
		p.setPen(QPen(_brush, 2.0));
		p.drawLine(QPointF(_dividerMargin, height() - _dividerPadding), QPointF(width() - _dividerMargin, height() - _dividerPadding));
	}

	_font.setPointSizeF(_labelPointSize);
	p.setFont(_font);
	if (_state == FocusIn || _state == FocusOut) {
		p.setPen(QPen(_brush));
	} else {
		p.setOpacity(0.2);
		p.setPen(QPen(QColor("#000000")));
	}
	p.drawText(QRectF(QPointF(0, height() - _textPadding - _textwidth - _labelMargin), QPointF(rect().width(), rect().height() - _textPadding)), Qt::AlignLeft, " " + _label);
}

void Input::focusInEvent(QFocusEvent *e) {
	_timer.start(2);
	_state = FocusIn;
	QWidget::focusInEvent(e);
}

void Input::focusOutEvent(QFocusEvent *e) {
	_timer.start(2);
	_state = FocusOut;
	QWidget::focusOutEvent(e);
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
		emit focused();
	}
	QWidget::mousePressEvent(e);
}

void Input::mouseReleaseEvent(QMouseEvent *e) {
	QWidget::mousePressEvent(e);
}

void Input::keyPressEvent(QKeyEvent *e) {
	if (e->type() == QEvent::KeyPress || e->key() == Qt::Key_Tab) {
		setFocus();
	}
	QWidget::keyPressEvent(e);
}

void Input::resizeEvent(QResizeEvent *e) {
	_dividerMargin = width() / 2;
	_labelPointSizeStep = 0.1;
	_dividerMarginStep = ((width() / 2) / 75.0);
	_labelMarginStep = 0.25;
	QWidget::resizeEvent(e);
}

QSize Input::minimumSizeHint() const {
	QFontMetrics fm(_font);
	return QSize(fm.width(_label) + 20, 60);
}

QSize Input::sizeHint() const {
	return minimumSizeHint();
}

void Input::setPlaceHolderText(const QString &placeholder) {
	_label = placeholder;
}

QString Input::placeHolderText() const {
	return _label;
}

void Input::setText(const QString &text) {
	_text = text;
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
		_dividerMargin -= _dividerMarginStep;
		_labelMargin += _labelMarginStep;
		_labelPointSize -= _labelPointSizeStep;
		if (_dividerMargin <= 0.0) {
			_timer.stop();
		}
		repaint();
	} break;
	case FocusOut:
	{
		_dividerMargin += _dividerMarginStep;
		_labelMargin -= _labelMarginStep;
		_labelPointSize +=_labelPointSizeStep;
		if (_dividerMargin >= width() / 2) {
			_timer.stop();
			_state = None;
		}
		repaint();
	} break;
	}
}
