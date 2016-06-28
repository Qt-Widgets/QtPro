#include "button.h"

Button::Button(QWidget *parent) :
QWidget(parent),
_disabled(false),
_text("BUTTON"),
_radius(2.0),
_height(36),
_padding(16),
_opacity(0.000),
_brush("#2FA9E2"),
_pointsize(14),
_fontfamily("Open Sans Semibold"),
_duration(0.0)
{
	_font.setFamily(_fontfamily);
	_font.setPointSize(_pointsize);
}

void Button::mousePressEvent(QMouseEvent *e) {
	if (!_disabled) {
		if (e->buttons() & Qt::LeftButton) {
			e->accept();
			_x = e->x();
			_y = e->y();
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

void Button::resizeEvent(QResizeEvent *e) {
	_duration = e->size().width() / 100.0; // 90 ms press motion duration
	QWidget::resizeEvent(e);
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



RaisedButton::RaisedButton(QWidget *parent ):Button(parent) {
	_rait = _height;
	connect(&_timer, SIGNAL(timeout()), this, SLOT(timercall()));
}

RaisedButton::RaisedButton(const QString &text, QWidget *parent) : Button(parent) {
	_rait = _height;
	_text = text;
	connect(&_timer, SIGNAL(timeout()), this, SLOT(timercall()));
}

RaisedButton::RaisedButton(const QString &text, const QColor &color, QWidget *parent) :Button(parent) {
	_rait = _height;
	_text = text;
	_brush = color;
	connect(&_timer, SIGNAL(timeout()), this, SLOT(timercall()));
}

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

		p.drawEllipse(QRectF(_x - (_height / 2) + (_rait / 2), _y - (_height / 2) + (_rait / 2), _height - _rait, _height - _rait));

		p.setOpacity(1.0);
		p.setFont(_font);
		p.setPen(QColor("#FFFFFF"));
		p.drawText(rect(), Qt::AlignCenter, _text);

	} else {
		p.setBrush(QColor("#000000"));
		p.setOpacity(0.120); 
		_primary.addRoundedRect(QRect(0, 0, width(), height()), _radius, _radius);
		p.drawPath(_primary.simplified());

		p.setFont(_font);
		p.setPen(QColor("#000000"));
		p.setOpacity(0.260); 
		p.drawText(QRect(rect().x(), rect().y(), rect().width(), rect().height()), Qt::AlignCenter, _text);
	}
}

void RaisedButton::enterEvent(QEvent *e) {
	_timer.start(1); // 120ms for hover
	Button::enterEvent(e);
}

void RaisedButton::leaveEvent(QEvent *e) {
	_timer.start(1); // 120 ms for leave
	Button::leaveEvent(e);
}

void RaisedButton::mousePressEvent(QMouseEvent *e) {
	_opacity = 0.260; // 26% shade on press
	_rait = _height;
	_timer.start(1); // 100ms for press
	Button::mousePressEvent(e);
}

void RaisedButton::mouseReleaseEvent(QMouseEvent *e)  {
	Q_UNUSED(e);
}

void RaisedButton::timercall() {
	switch (_state)
	{
	case ButtonState::Hover:
	{
		_opacity += 0.001;
		if (_opacity >= 0.120) { // 12% shade on hover
			_timer.stop();
		}
		repaint();
	} break;
	case ButtonState::Over:
	{
		_opacity -= 0.001;
		if (_opacity < 0.000) {
			_timer.stop();
			_rait = _height;
		}
		repaint();
	} break;
	case ButtonState::Pressed:
	{
		_rait -= _duration;
		if (_rait < -width()*2) {
			_timer.stop();
			_state = Released;
			_timer.start(2);
		}
		repaint();
	} break;
	case ButtonState::Released :
	{
		_opacity -= 0.001;
		if (_opacity < 0.120) {
			_timer.stop();
		}
		repaint();
	} break;
	}
}



FlatButton::FlatButton(QWidget *parent ):Button(parent) {
	_rait = _height;
	connect(&_timer, SIGNAL(timeout()), this, SLOT(timercall()));
}

FlatButton::FlatButton(const QString &text, QWidget *parent) : Button(parent) {
	_rait = _height;
	_text = text;
	_brush = "#FF5252";
	connect(&_timer, SIGNAL(timeout()), this, SLOT(timercall()));
}

FlatButton::FlatButton(const QString &text, const QColor &color, QWidget *parent) :Button(parent) {
	_rait = _height;
	_text = text;
	_brush = color;
	connect(&_timer, SIGNAL(timeout()), this, SLOT(timercall()));
}

void FlatButton::paintEvent(QPaintEvent*) {
	QPainter p(this);
	p.setPen(Qt::NoPen);
	p.setRenderHint(QPainter::Antialiasing);
	QPainterPath _primary;

	if (!_disabled) {
		p.setBrush(_brush);
		p.setOpacity(_opacity);
		_primary.addRoundedRect(QRect(0, 0, width(), height()), _radius, _radius);
		p.drawPath(_primary.simplified());

		p.drawEllipse(QRectF(_x - (_height / 2) + (_rait / 2), _y - (_height / 2) + (_rait / 2), _height - _rait, _height - _rait));

		p.setOpacity(1.0);
		p.setFont(_font);
		p.setPen(_brush);
		p.drawText(rect(), Qt::AlignCenter, _text);
	} else {
		p.setBrush(QColor("#000000"));
		p.setOpacity(0.120);
		_primary.addRoundedRect(QRect(0, 0, width(), height()), _radius, _radius);
		p.drawPath(_primary.simplified());

		p.setFont(_font);
		p.setPen(QColor("#000000"));
		p.setOpacity(0.260);
		p.drawText(QRect(rect().x(), rect().y(), rect().width(), rect().height()), Qt::AlignCenter, _text);
	}
}

void FlatButton::enterEvent(QEvent *e) {
	_timer.start(1); // 120ms for hover
	Button::enterEvent(e);
}

void FlatButton::leaveEvent(QEvent *e) {
	_timer.start(1); 
	Button::leaveEvent(e);
}

void FlatButton::mousePressEvent(QMouseEvent *e) {
	_x = e->x();
	_y = e->y();
	_opacity = 0.260; // 26% shade on press
	_rait = _height;
	_timer.start(1); // 100ms for press
	Button::mousePressEvent(e);
}

void FlatButton::mouseReleaseEvent(QMouseEvent *e)  {
	Button::mouseReleaseEvent(e);
	_state = Pressed;
}

void FlatButton::timercall() {
	switch (_state)
	{
	case ButtonState::Hover:
	{
		_opacity += 0.001;
		if (_opacity > 0.120) {
			_timer.stop();
		}
		repaint();
	} break;
	case ButtonState::Over:
	{
		_opacity -= 0.001;
		if (_opacity <  0.000) {
			_timer.stop();
			_rait = _height;
		}
		repaint();
	} break;
	case ButtonState::Pressed:
	{
		_rait -= _duration;
		if (_rait < -width() * 2) {
			_timer.stop();
			_state = Released;
			_timer.start(3);
		}
		repaint();
	} break;
	case ButtonState::Released:
	{
		_opacity -= 0.001;
		if (_opacity <= 0.120) {
			_timer.stop();
		}
		repaint();
	} break;
	}
}



IconButton::IconButton(QWidget *parent):Button(parent) {
	_height = _rait = 56;
	_rect = QRect(16, 16, 24, 24); // 16dp padding @ desktop
	_opacity = 0.120; // 12% shade on press
	connect(&_timer, SIGNAL(timeout()), this, SLOT(timercall()));
}

IconButton::IconButton(const QPixmap &icon, QWidget *parent) :Button(parent) {
	if (icon.isNull()) {
		qDebug() << icon;
	} else {
		_icon = icon.scaled(24, 24, Qt::IgnoreAspectRatio, Qt::SmoothTransformation); // scale for low resoloution
		_rect = QRect(16, 16, 24, 24); 
		_height = _rait = 56;
		_opacity = 0.120; 

		// detect qpixmap color
		QImage img = icon.toImage();
		_brush = QColor(img.pixel((img.width() / 2) - (img.width() / 4), (img.height() / 2) - (img.height() / 4)));

		connect(&_timer, SIGNAL(timeout()), this, SLOT(timercall()));
	}
}

IconButton::IconButton(const QPixmap &icon, const QColor &brush, QWidget *parent) :Button(parent) {
	if (icon.isNull()) {
		qDebug() << icon;
	} else {
		_icon = icon.scaled(24, 24, Qt::IgnoreAspectRatio, Qt::SmoothTransformation); 
		_rect = QRect(16, 16, 24, 24); 
		_height = _rait = 56;
		_brush = brush;
		_opacity = 0.120; 
		connect(&_timer, SIGNAL(timeout()), this, SLOT(timercall()));
	}
}

void IconButton::paintEvent(QPaintEvent*) {
	QPainter p(this);
	p.setPen(Qt::NoPen);

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
	case ButtonState::Hover: break;
	case ButtonState::Over:
	{
		_opacity -= 0.001;
		if (_opacity < 0.000) {
			_timer.stop();
			_opacity = 0.120;
			_rait = _height;
		}
		repaint();
	} break;
	case ButtonState::Pressed:
	{
		_rait -= 2;
		if (_rait < 2) {
			_timer.stop();
		}
		repaint();
	} break;
	case ButtonState::Released:
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

void IconButton::setPixmap(const QPixmap &icon) {
	if (icon.isNull()) {
		qDebug() << icon;
	} else {
		_icon = icon.scaled(24, 24, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);

		QImage img = icon.toImage();
		_brush = QColor(img.pixel((img.width() / 2) - (img.width() / 4), (img.height() / 2) - (img.height() / 4)));
	}
}



LinkButton::LinkButton(QWidget *parent ):Button(parent) {
	_pointsize = 10;
}

LinkButton::LinkButton(const QString &text, QWidget *parent) : Button(parent) {
	_text = text;
	_pointsize = 10;
}

void LinkButton::enterEvent(QEvent *e) {
	Button::enterEvent(e);
	_font.setUnderline(true);
	repaint();
}

void LinkButton::leaveEvent(QEvent *e) {
	Button::leaveEvent(e);
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



FloatActionButton::FloatActionButton(QWidget *parent ):Button(parent) {
	_height = _rait = 56;
	_opacity = 0.120; // 12% shade on press
	_margin = 3;
	_rect = QRect(16, 16, 24, 24); // 16dp padding @ desktop
	connect(&_timer, SIGNAL(timeout()), this, SLOT(timercall()));
}

FloatActionButton::FloatActionButton(const QPixmap &icon, const QColor &brush, QWidget *parent) :Button(parent) {
	if (icon.isNull()) {
		qDebug() << icon;
	}
	else {
		_icon = icon.scaled(24, 24, Qt::IgnoreAspectRatio, Qt::SmoothTransformation); // scale for low resoloution
		_rect = QRect(16, 16, 24, 24); 
		_height = _rait = 56;
		_opacity = 0.120;
		_margin = 3;
		_brush = brush;

		connect(&_timer, SIGNAL(timeout()), this, SLOT(timercall()));
	}
}

void FloatActionButton::paintEvent(QPaintEvent*) {
	QPainter p(this);
	p.setPen(Qt::NoPen);
	p.setRenderHint(QPainter::Antialiasing);

	QPainterPath _primary, _secoundry;
	if (!_disabled) {
		p.setBrush(_brush);
		p.setOpacity(1.0);
		_primary.addRoundedRect(QRect(_margin, _margin, width() - _margin * 2, height() - _margin * 2), 25.0, 25.0);
		p.drawPath(_primary.simplified());

		p.setBrush(QColor("#000000"));
		p.setOpacity(_opacity);
		_secoundry.addRoundedRect(QRect(_margin, _margin, width() - _margin * 2, height() - _margin * 2), 25.0, 25.0);
		p.drawPath(_secoundry.simplified());

		p.drawEllipse(QRect(rect().x() + (_rait / 2), rect().y() + (_rait / 2), rect().width() - _rait, rect().height() - _rait));

		p.setOpacity(1.0);
		p.drawPixmap(_rect, _icon);
	} else {

	}
}

QSize FloatActionButton::minimumSizeHint() const {
	return QSize(_height, _height);
}

void FloatActionButton::enterEvent(QEvent *e) {
	_timer.start(1);
	Button::enterEvent(e);
}

void FloatActionButton::leaveEvent(QEvent *e) {
	_timer.start(1);
	Button::leaveEvent(e);
}

void FloatActionButton::mousePressEvent(QMouseEvent *e) {
	_opacity = 0.260; // 26% shade on press
	_rait = _height;
	_timer.start(2); // 100ms for press
	Button::mousePressEvent(e);
}

void FloatActionButton::mouseReleaseEvent(QMouseEvent *e) {
	Q_UNUSED(e);
}

void FloatActionButton::timercall() {
	switch (_state)
	{
	case ButtonState::Hover:
	{
		_opacity += 0.001;
		if (_opacity > 0.120) { // 12% shade on hover
			_timer.stop();
		}
		repaint();
	} break;
	case ButtonState::Over:
	{
		_opacity -= 0.001;
		if (_opacity < 0.000) {
			_timer.stop();
			_rait = _height;
		}
		repaint();
	} break;
	case ButtonState::Pressed:
	{
		_rait -= _duration;
		if (_rait < _margin * 2) {
			_timer.stop();
			_state = Released;
			_timer.start(3);
		}
		repaint();
	} break;
	case ButtonState::Released:
	{
		_opacity -= 0.001;
		if (_opacity < 0.120) {
			_timer.stop();
		}
		repaint();
	} break;
	}
}

void FloatActionButton::setPixmap(const QPixmap &icon) {
	if (icon.isNull()) {
		qDebug() << icon;
	}
	else {
		_icon = icon.scaled(24, 24, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);

		QImage img = icon.toImage();
		_brush = QColor(img.pixel((img.width() / 2) - (img.width() / 4), (img.height() / 2) - (img.height() / 4)));
	}
}
