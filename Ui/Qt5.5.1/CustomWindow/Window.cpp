Window::Window(QWidget *parent)
	:QWidget(parent) {
	setWindowFlags(Qt::FramelessWindowHint);
	setMinimumSize(640, 480);
	connect(_titlebar->_close, SIGNAL(clicked()), this, SLOT(close()));
	connect(_titlebar->_minimize, SIGNAL(clicked()), this, SLOT(showMinimized()));
	connect(_titlebar->_maxmimize, SIGNAL(clicked()), this, SLOT(change()));
	// _layout Settings
	_layout->setMargin(0);
	_layout->setSpacing(0);
	_layout->setRowStretch(1, 1);
	_layout->addWidget(_titlebar, 0, 0, 1, 1);
	setLayout(_layout);
}

Window::Window(const QString &_title, QWidget *parent)
:QWidget(parent) {
	setWindowFlags(Qt::FramelessWindowHint);
	setMinimumSize(640, 480);
	connect(_titlebar->_close, SIGNAL(clicked()), this, SLOT(close()));
	connect(_titlebar->_minimize, SIGNAL(clicked()), this, SLOT(showMinimized()));
	connect(_titlebar->_maxmimize, SIGNAL(clicked()), this, SLOT(change()));
	_titlebar->setText(_title);
	// _layout Settings
	_layout->setMargin(0);
	_layout->setSpacing(0);
	_layout->setRowStretch(1, 1);
	_layout->addWidget(_titlebar, 0, 0, 1, 1);
	setLayout(_layout);
}

Window::~Window() {}

void Window::paintEvent(QPaintEvent *) {
	QPainter painter(this);
	painter.setBrush(QColor("#FFFFFF"));
	painter.setPen(Qt::NoPen);
	painter.drawRect(0, 0, width(), height());
}

void Window::change() {
	if (windowState() == Qt::WindowMaximized)
	{
		_titlebar->_maxmimize->setMaximized(false);
		setToolTip("Restore Down");
		restoreGeometry(_state);
	}
	else
	{
		_state = saveGeometry();
		_titlebar->_maxmimize->setMaximized(true);
		setToolTip("Maximize");
		showMaximized();
	}
}

void Window::setIcon(const QPixmap &_icon) {
	_titlebar->setIcon(_icon);
}
