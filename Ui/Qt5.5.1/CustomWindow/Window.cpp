Window::Window(QWidget *parent)
	:QWidget(parent) {
	setWindowFlags(Qt::CustomizeWindowHint | Qt::FramelessWindowHint);
	setAttribute(Qt::WA_TranslucentBackground);
	setMinimumSize(640, 480);
	setMouseTracking(true);
	// _layout Settings
	_layout->setMargin(0);
	_layout->setSpacing(0);
	_layout->setRowStretch(1, 1);
	_layout->addWidget(_titlebar, 0, 0, 1, 1);
	setLayout(_layout);
}

Window::Window(const QString &_title, QWidget *parent)
:QWidget(parent) {
	setWindowFlags(Qt::CustomizeWindowHint | Qt::FramelessWindowHint);
	setAttribute(Qt::WA_TranslucentBackground);
	setMinimumSize(640, 480);
	setMouseTracking(true);
	_titlebar->setText(_title);
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
	painter.setRenderHint(QPainter::Antialiasing);

	QPainterPath path;
	path.setFillRule(Qt::WindingFill);
	path.addRoundedRect(QRect(0, 0, width(), height()), 5.0, 5.0);
	painter.drawPath(path.simplified());
}
