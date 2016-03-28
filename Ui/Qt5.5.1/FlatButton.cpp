FlatButton::FlatButton(QWidget *parent)
	: QWidget(parent)
{
	connect(&_timer_in, SIGNAL(timeout()), this, SLOT(in_timer()));
	connect(&_timer_out, SIGNAL(timeout()), this, SLOT(out_timer()));
}

FlatButton::~FlatButton() {}

void FlatButton::paintEvent(QPaintEvent *) {
	QPainter painter(this);
	painter.setRenderHint(QPainter::Antialiasing);
	QRect Rectangle = QRect(100, 100, width() - 200, height() - 200);
	painter.setOpacity(_opacity);
	painter.fillRect(Rectangle, _back);
	painter.save();
	painter.setFont(QFont(_fontfamily, _pointsize));
	painter.setPen(QPen(_color));
	painter.drawText(QRect(rect().x(), rect().y(), rect().width(), rect().height() - _margin), Qt::AlignCenter, _text);
}

void FlatButton::enterEvent(QEvent *) {
	_timer_in.start(2);
	setCursor(Qt::PointingHandCursor);
}

void FlatButton::leaveEvent(QEvent *) {
	_timer_out.start(2);
}

void FlatButton::in_timer() {
	_opacity += 0.001;
	if (_opacity > 0.950)
	{
		_timer_in.stop();
	}
	update();
}

void FlatButton::out_timer() {
	_opacity -= 0.001;
	if (_opacity < 0.850)
	{
		_timer_out.stop();
	}
	update();
}

void FlatButton::mousePressEvent(QMouseEvent *) {
	_margin = -4;
	update();
}

void FlatButton::mouseReleaseEvent(QMouseEvent *) {
	_margin = 0;
	update();
}
