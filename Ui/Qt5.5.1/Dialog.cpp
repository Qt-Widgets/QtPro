#include "dialog.h"

Dialog::Dialog(QWidget *parent) : QWidget(parent),
_opacity(0.000),
_close(false),
_show(true),
_margin(24),
_radius(3.0),
_step(0.006)
{
	setAttribute(Qt::WA_StaticContents);
	setAttribute(Qt::WA_TranslucentBackground);
	setWindowFlags(Qt::FramelessWindowHint);
	connect(&_timer, SIGNAL(timeout()), this, SLOT(timercall()));
}

void Dialog::showEvent(QShowEvent*) {
	_timer.start(1);
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

void Dialog::paintEvent(QPaintEvent*) {
	QPainter p(this);
	p.setBrush(QColor("#FFFFFF"));
	p.setPen(Qt::NoPen);
	p.setRenderHint(QPainter::Antialiasing);

	QPainterPath path;
	path.addRoundedRect(QRect(0, 0, width(), height()), _radius, _radius);
	p.drawPath(path.simplified());
}

void Dialog::timercall() {
	if (_show) {
		_opacity += _step;
		setWindowOpacity(_opacity);
		if (_opacity >= 1.000) {
			_timer.stop();
		}
	} else {
		_opacity -= _step;
		setWindowOpacity(_opacity);
		if (_opacity < 0.000) {
			_timer.stop();
			_close = true;
			close();
		}
	}
}



DialogMessage::DialogMessage(QWidget *parent) :Dialog(parent) {
	_mainlayout.setContentsMargins(_margin, _margin, _margin, _margin - 16); // padding:24dp from top,left,right 8dp from bottom
	_mainlayout.setVerticalSpacing(24); // 24dp space between elements
	_mainlayout.addLayout(&_titlelayout, 0, 0, Qt::AlignLeft);
	_mainlayout.addLayout(&_contentlayout, 1, 0, Qt::AlignLeft);
	_mainlayout.addLayout(&_actionlayout, 2, 0, Qt::AlignRight);
	setLayout(&_mainlayout);

	_actionlayout.setContentsMargins(0, 8, 0, 8); // 8dp margin for action buttons
	_actionlayout.setSpacing(8);
	_actionlayout.addStretch();

	_ok = new FlatButton("DELETE",QColor("#4285F4"));
	_cancel = new FlatButton("CANCEL", QColor("#4285F4"));
	_actionlayout.addWidget(_cancel);
	_actionlayout.addWidget(_ok);

	_title = new TextLabel();
	_titlelayout.addWidget(_title);

	_content = new TextLabel();
	_contentlayout.addWidget(_content);

	//connect(_cancel, SIGNAL(clicked()), this, SLOT(onClose()));
	//connect(_ok, SIGNAL(clicked()), this, SLOT(close()));
}

void DialogMessage::setTitle(const QString &title) {
	_title->setText(title);
}

void DialogMessage::setContent(const QString &text) {
	_content->setText(text);
}

void DialogMessage::onClose() {
	DialogMessage *d = new DialogMessage();
	d->setTitle("Use Google's Location?");
	d->setContent("Let Google help apps determine location\n.this means sending anonymouslocation data to Google, even when no apps are running");
	d->setGeometry(width(), height(), width(), height());
	d->show();
}
