#include "customwindow.h"

Window::Window(QWidget *parent)
	:QWidget(parent) {
	setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
	setMinimumWidth(_titlebar->minimumwidth());
	// _layout Settings
	_layout->setMargin(0);
	_layout->setSpacing(0);
	_layout->setRowStretch(1, 1);
	_layout->addWidget(_titlebar, 0, 0, 1, 1);
	setLayout(_layout);
}

Window::Window(const QString &_title, QWidget *parent)
:QWidget(parent) {
	setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
	_titlebar->setText(_title);
	setMinimumWidth(_titlebar->minimumwidth());
	// _layout Settings
	_layout->setMargin(0);
	_layout->setSpacing(0);
	_layout->setRowStretch(1, 1);
	_layout->addWidget(_titlebar, 0, 0, 1, 1);
	setLayout(_layout);
}

Window::~Window() {}

void Window::setIcon(const QPixmap &_icon) {
	_titlebar->setIcon(_icon);
}

void Window::paintEvent(QPaintEvent *) {
	QPainter painter(this);
	painter.setBrush(QColor("#FFFFFF"));
	painter.setPen(Qt::NoPen);
	painter.drawRect(0, 0, width(), height());
}
