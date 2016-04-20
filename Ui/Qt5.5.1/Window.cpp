Window::Window() {
  setWindowFlags(Qt::FramelessWindowHint);
  setWindowFlags(Qt::FramelessWindowHint);
	_layout.setMargin(0);
	_layout.setSpacing(0);
	setLayout(&_layout);
}

Window::~Window() {}

void Window::paintEvent(QPaintEvent *) {
	QPainter painter(this);
	painter.setBrush(_background);
	painter.setPen(Qt::NoPen);
	painter.drawRect(0, 0, width(), height());
}
