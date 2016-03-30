CircleButton::CircleButton(QWidget *parent)
	: QWidget(parent)
{
	setFixedHeight(150);
	setFixedWidth(150);
	_image = _image1;
	connect(&_timer_in, SIGNAL(timeout()), this, SLOT(in_timer()));
	connect(&_timer_out, SIGNAL(timeout()), this, SLOT(out_timer()));
}

CircleButton::~CircleButton() {}

void CircleButton::paintEvent(QPaintEvent *) {
	QPainter painter(this);
	painter.setRenderHint(QPainter::Antialiasing);
	painter.setPen(QPen(_back, 2));
	painter.drawEllipse(rect());
	painter.setBrush(QBrush(_back));
	painter.drawEllipse(QRect(rect().x() + (_blank / 2), rect().y() + (_blank / 2), rect().width() - _blank, rect().height() - _blank));
	QRect center(rect().x() - _margin / 2, rect().y() + _margin, rect().width(), rect().height() - (2 * _margin));
	painter.drawPixmap(center , _image);
}

void CircleButton::enterEvent(QEvent *) {
	_image = _image0;
	setCursor(Qt::PointingHandCursor);
	_timer_in.start(1.7);
}

void CircleButton::leaveEvent(QEvent *) {
	_image = _image1;
	_timer_out.start(1.7);
}

void CircleButton::in_timer() {
	_blank -= 1;
	if (_blank < 0)
	{
		_timer_in.stop();
	}
	update();
}

void CircleButton::out_timer() {
	_blank += 1;
	if (_blank >= 150)
	{
		_timer_out.stop();
	}
	update();
}
