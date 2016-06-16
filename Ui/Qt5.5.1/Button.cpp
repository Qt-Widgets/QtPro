#include "button.h"

Button::Button(QWidget *parent) :
QWidget(parent),
_state(None),
_disabled(false),
_text("BUTTON"),
_radius(2.0),
_height(36),
_padding(16),
_opacity(0.000),
_color("#FFFFFF"),
_brush("#2FA9E2"),
_pointsize(14),
_fontfamily("Roboto medium")
{
	_font.setFamily(_fontfamily);
	_font.setPointSize(_pointsize);
}

Button::~Button() {}

void Button::mousePressEvent(QMouseEvent *e) {
	if (!_disabled) {
		if (e->buttons() & Qt::LeftButton) {
			e->accept();
			_state = Pressed;
		} else {
			e->ignore();
		}
	}
}

void Button::mouseReleaseEvent(QMouseEvent *e) {
	if (!_disabled) {
		if (e->type() == QMouseEvent::MouseButtonRelease && e->button() == Qt::LeftButton) {
			e->accept();
			emit clicked();
			_state = Released;
		} else {
			e->ignore();
		}
	}
}

void Button::enterEvent(QEvent*) {
	if (!_disabled) {
		_state = Hover;
		setCursor(Qt::PointingHandCursor);
	}
}

void Button::leaveEvent(QEvent*) {
	if (!_disabled) {
		_state = Over;
	}
}

QSize Button::sizeHint() const {
	return minimumSizeHint();
}

QSize Button::minimumSizeHint() const {
	QFontMetrics fm(_font);
	return QSize(_padding + fm.width(_text) + _padding, _height);
}

void Button::setText(const QString &text) {
	_text = text;
	update();
}

void Button::setColor(const QColor &color)  {
	_brush = color;
	update();
}

void Button::setDisable(bool disable) {
	_disabled = disable;
}

void Button::setFont(const QString &family, const qint16 &pointsize) {
	_font.setFamily(family);
	_font.setPointSize(pointsize);
	update();
}

bool Button::isDisable() const {
	return _disabled;
}

QString Button::text() const {
	return _text;
}

QColor Button::color() const {
	return _brush;
}



RaisedButton::RaisedButton(QWidget *parent) :Button(parent) {
	connect(&_timer, SIGNAL(timeout()), this, SLOT(timercall()));
}

RaisedButton::RaisedButton(const QString &text, QWidget *parent) : Button(parent) {
	_text = text;
	connect(&_timer, SIGNAL(timeout()), this, SLOT(timercall()));
}

RaisedButton::RaisedButton(const QString &text, const QColor &color, QWidget *parent) :Button(parent) {
	_text = text;
	_brush = color;
	connect(&_timer, SIGNAL(timeout()), this, SLOT(timercall()));
}

RaisedButton::~RaisedButton() {}

void RaisedButton::paintEvent(QPaintEvent*) {
	QPainter p(this);
	p.setPen(Qt::NoPen);
	p.setRenderHint(QPainter::Antialiasing);

	QPainterPath _primary, _secoundry;

	if (!_disabled) {
		p.setBrush(_brush);
		p.setOpacity(1.0);
		_primary.addRoundedRect(QRect(0, 0, width(), height()), _radius, _radius);
		p.drawPath(_primary.simplified());

		p.setBrush(QColor("#000000"));
		p.setOpacity(_opacity);
		_secoundry.addRoundedRect(QRect(0, 0, width(), height()), _radius, _radius);
		p.drawPath(_secoundry.simplified());
		// text
		p.setOpacity(1.0);
		p.setFont(_font);
		p.setPen(QColor("#FFFFFF"));
		p.drawText(rect(), Qt::AlignCenter, _text);
	} else {
		p.setBrush(QColor("#000000"));
		p.setOpacity(0.120); // 12% @ #000000
		_primary.addRoundedRect(QRect(0, 0, width(), height()), _radius, _radius);
		p.drawPath(_primary.simplified());

		p.setFont(_font);
		p.setPen(QColor("#000000"));
		p.setOpacity(0.260); // 26% @ #000000
		p.drawText(QRect(rect().x(), rect().y(), rect().width(), rect().height()), Qt::AlignCenter, _text);
	}
}

void RaisedButton::timercall() {
	switch (_state)
	{
	case Button::None: break;
	case Button::Hover:
	{
		_opacity += 0.001;
		if (_opacity > 0.120) { // 12% shade 
			_timer.stop();
		}
		repaint();
	} break;
	case Button::Over:
	{
		_opacity -= 0.001;
		if (_opacity < 0.000) {
			_timer.stop();
			_state = None;
		}
		repaint();
	} break;
	case Button::Pressed:
	{
		_opacity += 0.002;
		if (_opacity > 0.280) {
			_timer.stop();
		}
		repaint();
	} break;
	case Button::Released:
	{
		_opacity -= 0.001;
		if (_opacity < 0.120) {
			_timer.stop();
			_state = Hover;
		}
		repaint();
	} break;
	}
}



FlatButton::FlatButton(QWidget *parent):Button(parent) {
	_pointsize = 14;
	_blank = width();
	_opacity = 0.120;
	_brush = "#E91E63";
	connect(&_timer, SIGNAL(timeout()), this, SLOT(timercall()));
}

FlatButton::FlatButton(const QString &text, QWidget *parent) : Button(parent) {
	_text = text;
	connect(&_timer, SIGNAL(timeout()), this, SLOT(timercall()));
}

FlatButton::FlatButton(const QString &text, const QColor &color, QWidget *parent) :Button(parent) {
	_text = text;
	_brush = color;
	_pointsize = 14;
	_opacity = 0.120;
	connect(&_timer, SIGNAL(timeout()), this, SLOT(timercall()));
}

FlatButton::~FlatButton() {}

void FlatButton::paintEvent(QPaintEvent*) {
	QPainter p(this);
	p.setPen(Qt::NoPen);
	p.setRenderHint(QPainter::Antialiasing);


	p.setBrush(_brush);
	p.setOpacity(_opacity);

	p.drawEllipse(QRect(rect().x() + (_blank / 2), rect().y() + (_blank / 2), rect().width() - _blank, rect().height() - _blank));
}

void FlatButton::mousePressEvent(QMouseEvent *e) {
	_x = e->x();
	_y = e->y();
	Button::mousePressEvent(e);
}

void FlatButton::mouseReleaseEvent(QMouseEvent *e)  {
	Button::mouseReleaseEvent(e);
}

void FlatButton::timercall() {
	switch (_state)
	{
	case Button::None:
	case Button::Hover:
	case Button::Over:break;
	case Button::Pressed:
	{
		_blank -= 1;
		if (_blank < 0 ) {
			_timer.stop();
		}
		repaint();
	} break;
	case Button::Released:
	{
		_opacity -= 0.001;
		if (_opacity < 0.000) {
			_timer.stop();
			_opacity = 0.0120;
			_blank = width();
		}
		repaint();
	} break;
	}
}



IconButton::IconButton(const QPixmap &icon, QWidget *parent) :Button(parent) {
	_icon = icon.scaled(24, 24, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
	_rect = QRect(16, 16, 24, 24); // 16dp padding @ desktop
	_height = _rait = 56;
	_opacity = 0.120; // 12% shade on press

	// detect qpixmap color
	QImage img = icon.toImage();
	_brush = QColor(img.pixel((img.width() / 2) - (img.width() / 4), (img.height() / 2) - (img.height() / 4)));

	connect(&_timer, SIGNAL(timeout()), this, SLOT(timercall()));
}

IconButton::IconButton(const QPixmap &icon, const QColor &brush, QWidget *parent) :Button(parent) {
	_icon = icon.scaled(24, 24, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
	_rect = QRect(16, 16, 24, 24); // 16dp padding @ desktop
	_height = _rait = 56;
	_brush = brush;
	_opacity = 0.120; // 12% shade on press
	connect(&_timer, SIGNAL(timeout()), this, SLOT(timercall()));
}

void IconButton::paintEvent(QPaintEvent*) {
	QPainter p(this);
	p.setPen(Qt::NoPen);
	p.setBrush(_brush);
	p.setOpacity(1.0);

	QPainterPath path;
	path.addRoundedRect(rect(), 25.0, 25.0);
	//p.drawPath(path.simplified());

	p.setRenderHint(QPainter::SmoothPixmapTransform);
	p.drawPixmap(_rect, _icon);

	p.setBrush(_brush);
	p.setOpacity(_opacity);
	p.setRenderHint(QPainter::Antialiasing);
	p.drawEllipse(QRect(rect().x() + (_rait / 2), rect().y() + (_rait / 2), rect().width() - _rait, rect().height() - _rait));
}

void IconButton::mousePressEvent(QMouseEvent *e) {
	_timer.start(3);
	Button::mousePressEvent(e);
}

void IconButton::mouseReleaseEvent(QMouseEvent *e) {
	_timer.start(3);
	Button::mouseReleaseEvent(e);
}

QSize IconButton::minimumSizeHint() const {
	return QSize(_height, _height);
}

void IconButton::timercall() {
	switch (_state)
	{
	case Button::None:
	case Button::Hover:
	case Button::Over:break;
	case Button::Pressed:
	{
		_rait -= 2.0;
		if (_rait < 2) {
			_timer.stop();
		}
		repaint();
	} break;
	case Button::Released:
	{
		_opacity -= 0.001;
		if (_opacity < 0.000) {
			_timer.stop();
			_opacity = 0.120;
			_rait = _height;
		}
		repaint();
	} break;
	}
}




LinkButton::LinkButton(QWidget *parent) :Button(parent) {
	_pointsize = 12;
}

LinkButton::LinkButton(const QString &text, QWidget *parent) : Button(parent) {
	_text = text;
	_pointsize = 12;
}

void LinkButton::enterEvent(QEvent *) {
	setCursor(Qt::PointingHandCursor);
	_font.setUnderline(true);
	repaint();
}

void LinkButton::leaveEvent(QEvent *) {
	_font.setUnderline(false);
	repaint();
}

QSize LinkButton::minimumSizeHint() const {
	QFontMetrics _fm(_font);
	return QSize(_fm.width(_text), _fm.height());
}

void LinkButton::paintEvent(QPaintEvent*) {
	QPainter p(this);
	p.setRenderHint(QPainter::TextAntialiasing);
	p.setBrush(_brush);
	p.setFont(_font);
	p.setPen(_brush);
	p.drawText(rect(), Qt::AlignCenter, _text);
}
