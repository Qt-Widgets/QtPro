#include "customwindow.h"

Window::Window() {
	setWindowFlags(Qt::FramelessWindowHint);
	setMinimumSize(640, 480);
	// _layout Settings
	_layout.setMargin(0);
	_layout.setSpacing(0);
	_layout.setRowStretch(1, 1);
	_layout.addWidget(&_titlebar, 0, 0, 1, 1);
	setLayout(&_layout);
}

Window::~Window() {}

void Window::paintEvent(QPaintEvent *) {
	QPainter painter(this);
	painter.setBrush(_background);
	painter.setPen(Qt::NoPen);
	painter.drawRect(0, 0, width(), height());
}

void Window::closeEvent() {
	close();
}
