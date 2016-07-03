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
}

void Input::focusInEvent(QFocusEvent *e) {
	_state = FocusIn;
	QWidget::focusInEvent(e);
}

void Input::focusOutEvent(QFocusEvent *e) {
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



LabelInput::LabelInput(QWidget *parent ) : Input(parent) {
	connect(&_timer, SIGNAL(timeout()), this, SLOT(timercall()));
}

LabelInput::LabelInput(const QString &placeholder, QWidget *parent) : Input(parent) {
	_label = placeholder;
	connect(&_timer, SIGNAL(timeout()), this, SLOT(timercall()));
}

void LabelInput::paintEvent(QPaintEvent *) {
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
	}
	else {
		p.setOpacity(0.25);
		p.setPen(QPen(QColor("#000000")));
	}
	p.drawText(QRectF(QPointF(0, height() - _textPadding - _textwidth - _labelMargin), QPointF(rect().width(), rect().height() - _textPadding)), Qt::AlignLeft, " " + _label);
}

void LabelInput::focusInEvent(QFocusEvent *e) {
	_timer.start(2);
	Input::focusInEvent(e);
}

void LabelInput::focusOutEvent(QFocusEvent *e) {
	_timer.start(2);
	Input::focusOutEvent(e);
}

void LabelInput::resizeEvent(QResizeEvent *e) {
	_dividerMargin = width() / 2;
	_labelPointSizeStep = 0.08;
	_dividerMarginStep = ((width() / 2) / 75.0);
	_labelMarginStep = 0.25;
	QWidget::resizeEvent(e);
}

void LabelInput::timercall() {
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
		_labelPointSize += _labelPointSizeStep;
		if (_dividerMargin >= width() / 2) {
			_timer.stop();
			_state = None;
		}
		repaint();
	} break;
	}
}



FlatInput::FlatInput(QWidget *parent) : Input(parent),
_opacity(0.250) {
	connect(&_timer, SIGNAL(timeout()), this, SLOT(timercall()));
}

FlatInput::FlatInput(const QString &placeholder, QWidget *parent) : Input(parent),
_opacity(0.250)
{
	_label = placeholder;
	connect(&_timer, SIGNAL(timeout()), this, SLOT(timercall()));
}

void FlatInput::paintEvent(QPaintEvent *) {
	QPainter p(this);

	p.setPen(QPen(QColor("#000000"), 1.0));
	p.setOpacity(0.2);
	p.drawLine(QPointF(0, height() - _dividerPadding), QPointF(width(), height() - _dividerPadding));

	if (_state == FocusIn || _state == FocusOut) {
		p.setOpacity(1.0);
		p.setPen(QPen(_brush, 2.0));
		p.drawLine(QPointF(_dividerMargin, height() - _dividerPadding), QPointF(width() - _dividerMargin, height() - _dividerPadding));
	}

	p.setOpacity(_opacity);
	p.setPen(QPen(QColor("#000000")));
	p.setFont(_font);
	p.drawText(rect(), Qt::AlignLeft, "" + _label);

	QStyleOptionFrameV2 option2;
	QLineEdit sample;
	option2.initFrom(&sample);
	option2.rect = QRect(0, _textPadding, width(), height() - _textPadding);
	option2.state |= QStyle::State_Sunken;
	option2.lineWidth = style()->pixelMetric(QStyle::PM_DefaultFrameWidth, &option2, &sample);
	style()->drawPrimitive(QStyle::PE_PanelLineEdit, &option2, &p, this);
}

void FlatInput::focusInEvent(QFocusEvent *e) {
	_timer.start(2);
	Input::focusInEvent(e);
}

void FlatInput::focusOutEvent(QFocusEvent *e) {
	_timer.start(2);
	Input::focusOutEvent(e);
}

void FlatInput::resizeEvent(QResizeEvent *e) {
	_dividerMargin = width() / 2;
	_dividerMarginStep = ((width() / 2) / 75.0);
	QWidget::resizeEvent(e);
}

QSize FlatInput::minimumSizeHint() const {
	QFontMetrics fm(_font);
	return QSize(fm.width(_label) + 20, fm.height() + _dividerPadding + _textPadding);
}

void FlatInput::timercall() {
	switch (_state)
	{
	case None: break;
	case Hover: break;
	case Over: break;
	case FocusIn:
	{
		_dividerMargin -= _dividerMarginStep;
		_opacity -= 0.001;
		if (_dividerMargin <= 0.0) {
			_timer.stop();
		}
		repaint();
	} break;
	case FocusOut:
	{
		_dividerMargin += _dividerMarginStep;
		_opacity += 0.001;
		if (_dividerMargin >= width() / 2) {
			_timer.stop();
			_state = None;
		}
		repaint();
	} break;
	}
}
