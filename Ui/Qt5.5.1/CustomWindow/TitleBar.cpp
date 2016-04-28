TitleBar::TitleBar(QWidget *parent) 
	:QWidget(parent),
	_parent(parent),
	_hastext(false),
	_hasicon(false),
	_draging(false),
	_start(0,0),
	_background("#00A0B4"),
	_width(38),
	_textwidth(0)
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
	_hastext = true;
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
	_hasicon = true;
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
	qint16 minimumwidth = _close->width() + _maxmimize->width() + _minimize->width();
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
	painter.setRenderHint(QPainter::Antialiasing);

	QPainterPath path;
	path.setFillRule(Qt::WindingFill);
	path.addRoundedRect(QRect(0, 0, width(), height()), 5.0, 5.0);
	//bottomRight
	path.addRect(QRect(width() - 5, height() - 5, 5, 5)); 
	//bottomLeft
	path.addRect(QRect(0, height() - 5, 5, 5)); 
	painter.drawPath(path.simplified());
}

void TitleBar::mousePressEvent(QMouseEvent *e) {
	if (e->buttons() && Qt::LeftButton)
	{
		_start = e->globalPos() - _parent->frameGeometry().topLeft();
	_draging = true;
	e->accept();
	}
}

void TitleBar::mouseReleaseEvent(QMouseEvent *e) {
	_draging = false;
}

void TitleBar::mouseMoveEvent(QMouseEvent *e) {
	if (e->buttons() & Qt::LeftButton)
	{
		if (_draging)
		{
			if (_parent->windowState().testFlag(Qt::WindowMaximized))
			{
				_parent->setWindowState(_parent->windowState() & ~Qt::WindowMaximized);
				_start = e->globalPos() - ((frameGeometry().topLeft()) + (frameGeometry().topRight())) / 2;
				e->accept();
			} else {
				_parent->move(e->globalPos() - _start);
				_maxmimize->setMaximized(false);
				e->accept();
			}
		} 
	}
	else if (_draging)
	{
		_draging = false;
	}
}

void TitleBar::mouseDoubleClickEvent(QMouseEvent *e) {
	if (e->type() == QMouseEvent::MouseButtonDblClick & e->button() == Qt::LeftButton)
	{
		Qt::WindowStates s(_parent->windowState());
		if (s.testFlag(Qt::WindowMaximized))
		{
			_parent->setWindowState(s & ~Qt::WindowMaximized);
			_maxmimize->setMaximized(false);
			e->accept();
		} else {
			_maxmimize->setMaximized(true);
			_parent->setWindowState(s | Qt::WindowMaximized);
			e->accept();
		}
	}
}

void TitleBar::changeState() {
	if (_parent->windowState().testFlag(Qt::WindowMaximized))
	{
		_maxmimize->setMaximized(false);
		_parent->setWindowState(_parent->windowState() & ~Qt::WindowMaximized);
	} else {
		_maxmimize->setMaximized(true);
		_parent->setWindowState(_parent->windowState() | Qt::WindowMaximized);
	}
}
