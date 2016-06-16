#include "dialog.h"

Dialog::Dialog(QWidget *parent) : QWidget(parent),
_opacity(0.000),
_close(false),
_show(true),
_margin(24)
{
	setStyleSheet("#FFFFFF");
	setAttribute(Qt::WA_StaticContents);
	setWindowFlags(Qt::FramelessWindowHint);
	connect(&_timer, SIGNAL(timeout()), this, SLOT(timercall()));
}

void Dialog::showEvent(QShowEvent*) {
	if (_show) {
		_timer.start(1);
	}
}

void Dialog::closeEvent(QCloseEvent *e) {
	if (_close) {
		e->accept();
	} else {
		_timer.start(1);
		_show = false;
		e->ignore();
	}
}

void Dialog::timercall() {
	if (_show) {
		_opacity += 0.006;
		setWindowOpacity(_opacity);
		if (_opacity >= 1.000) {
			_timer.stop();
		}
		repaint();
	} else {
		_opacity -= 0.006;
		setWindowOpacity(_opacity);
		if (_opacity < 0.000) {
			_timer.stop();
			_close = true;
			close();
		}
		repaint();
	}
}


DialogMessage::DialogMessage(QWidget *parent) :Dialog(parent) {
	_mainlayout.setContentsMargins(_margin, _margin, _margin, _margin); // 24dp padding from edges
	setLayout(&_mainlayout);
}
