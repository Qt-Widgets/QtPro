#include "TitleBar.h"

TitleBar::TitleBar(QWidget *parent) 
	:QWidget(parent), _parent(parent)
{
	setFixedHeight(_width);
	connect(_close, SIGNAL(clicked()), parent, SLOT(close()));
	connect(_maxmimize, SIGNAL(clicked()), this, SLOT(changeState()));
	connect(_minimize, SIGNAL(clicked()), parent, SLOT(showMinimized()));
	_l->addStretch();
	_l->addWidget(_minimize);
	_l->addWidget(_maxmimize);
	_l->addWidget(_close);
	_l->setMargin(0);
	_l->setSpacing(0);
	setLayout(_l);
}

TitleBar::~TitleBar() {}

void TitleBar::setText(const QString &_text) {
	delete _l;
	_hastext = 1;
	_textwidth += _text.size();

	_Title->setText("  " + _text);
	_Title->setMinimumHeight((_width / 2) + 3);
	_Title->setStyleSheet("color:white;");
	_Title->setFont(QFont("San Francisco Display Thin", 13));
	//_Title->setScaledContents(true);

	_primary->addWidget(_Title);
	_primary->addWidget(_minimize);
	_primary->addWidget(_maxmimize);
	_primary->addWidget(_close);
	_primary->setMargin(0);
	_primary->setSpacing(0);
	setLayout(_primary);
}

void TitleBar::setIcon(const QPixmap &_pixelmap) {
	if (_hastext)
	{
		delete _primary;
	}
	else
	{
		delete _l;
	}
	_hasicon = 1;
	_window_icon->setPixmap(_pixelmap);
	_secoundry->addWidget(_window_icon);
	_secoundry->addWidget(_Title);
	_secoundry->addWidget(_minimize);
	_secoundry->addWidget(_maxmimize);
	_secoundry->addWidget(_close);
	_secoundry->setMargin(0);
	_secoundry->setSpacing(0);
	setLayout(_secoundry);
}

qint16 TitleBar::minimumwidth() const {
	qint16 minimumwidth = (_close->width()) * 3 + (_maxmimize->width()) * 3 + (_minimize->width()) * 3;
	if (_hastext)
	{
		minimumwidth += _textwidth;
	}
	if (_hasicon)
	{
		minimumwidth += _window_icon->width();
	}
	return minimumwidth;
}

void TitleBar::paintEvent(QPaintEvent *) {
	QPainter painter(this);
	painter.setBrush(_background);
	painter.setPen(Qt::NoPen);
	painter.drawRect(0, 0, width(), height());
}

void TitleBar::mousePressEvent(QMouseEvent *e) {
	if (e->type() == QMouseEvent::MouseButtonPress && e->button() == Qt::LeftButton)
	{
	e->accept();
	_start = e->globalPos() - _parent->frameGeometry().topLeft();
	}
}

void TitleBar::mouseMoveEvent(QMouseEvent *e) {
	e->accept();
	_delta = e->globalPos() - _start;
	_parent->move(x() + _delta.x(), y() + _delta.y());
}

void TitleBar::mouseDoubleClickEvent(QMouseEvent *e) {
	Q_UNUSED(e);
	Qt::WindowStates s(_parent->windowState());
	if (s.testFlag(Qt::WindowMaximized))
	{
		_parent->setWindowState(s & ~Qt::WindowMaximized);
	} else {
		_parent->setWindowState(s | Qt::WindowMaximized);
	}
}

void TitleBar::changeState() {
	if (_maximized)
	{
		_maximized = 0;
		_maxmimize->setMaximized(0);
		_parent->restoreGeometry(_state);
	}
	else
	{
		_maximized = 1;
		_maxmimize->setMaximized(1);
		_state = _parent->saveGeometry();
		_parent->showMaximized();
	}
}


