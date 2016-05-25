#include "Window.h"
#include "shadow.h"



Window::Window(QWidget *parent) :_hasShadow(true), _radius(4.0), _borderWidth(10)
{
	_titlebar = new TitleBar(this);
	_framless = new FrameLess(this);
	_framless->setBorderWidth(_borderWidth);
	setAttribute(Qt::WA_TranslucentBackground);
	_layout.setMargin(_borderWidth);
	_layout.setRowStretch(1, 1);
	_layout.addWidget(_titlebar, 0, 0, 1, 1);
	setLayout(&_layout);
}

Window::Window(const QString &title, QWidget *parent) :_hasShadow(true), _radius(4.0), _borderWidth(10), _title(title)
{
	_titlebar = new TitleBar(this);
	_framless = new FrameLess(this);
	_framless->setBorderWidth(_borderWidth);
	setAttribute(Qt::WA_TranslucentBackground);
	_layout.setMargin(_borderWidth);
	_layout.setSpacing(0);
	_layout.setRowStretch(1, 1);
	_layout.addWidget(_titlebar, 0, 0, 1, 1);
	setLayout(&_layout);
	if (!_title.isEmpty()) {
		_titlebar->setText(_title);
	}
}

void Window::paintEvent(QPaintEvent *) {
	QPainter painter(this);
	if (_hasShadow) {
		drawShadow(painter, _borderWidth, _radius, QColor(120, 120, 120, 32), QColor(255, 255, 255, 0), 0.0, 1.0, 0.6, width(), height());
	} else {
		painter.setBrush(QColor("#FFFFFF"));
		painter.setPen(Qt::NoPen);
		painter.setRenderHint(QPainter::Antialiasing);

		QPainterPath path;
		path.setFillRule(Qt::WindingFill);
		path.addRoundedRect(QRect(0, 0, width(), height()), _radius, _radius);
		painter.drawPath(path.simplified());
	}
}

void Window::changeEvent(QEvent *e) {
	if (e->type() == QEvent::WindowStateChange) {
		if (windowState().testFlag(Qt::WindowMaximized)) {
			_hasShadow = false;
			_layout.setMargin(0);
			update();
		} else {
			_hasShadow = true;
			_layout.setMargin(_borderWidth);
			update();
		}
	}
}

Window::~Window() {}

void Window::setTitle(const QString &title) {
	_titlebar->setText(title);
}

void Window::setIcon(const QPixmap &icon) {
	_titlebar->setIcon(icon);
}

void Window::setColor(const QColor &titleColor) {
	_titlebar->setBackground(titleColor);
}

void Window::setRadius(const qreal &radius) {
	_radius = radius;
	_titlebar->setRadius(radius);
}

void Window::setBorderWidth(const qint16 &border) {
	_borderWidth = border;
	_layout.setMargin(border);
	_framless->setBorderWidth(border);
}

qint16 Window::borderWidth() const {
	return _borderWidth;
}

QString Window::title() const {
	return _title;
}

QPixmap Window::icon() const {
	return _titlebar->pixmap();
}

QColor Window::color() const {
	return _titlebar->background();
}

qreal Window::radius() const {
	return _radius;
}

void Window::setCloseDisable(bool disable) {
	if (disable) {
		_titlebar->closeDisable(disable);
	} else {
		_titlebar->closeDisable(disable);
	}
}

void Window::setMaximizeDisable(bool disable) {
	if (disable) {
		_titlebar->maximizeDisable(disable);
	} else {
		_titlebar->maximizeDisable(disable);
	}
}

void Window::setMinimizeDisable(bool disable) {
	if (disable) {
		_titlebar->minimizeDisable(disable);
	} else {
		_titlebar->minimizeDisable(disable);
	}
}
