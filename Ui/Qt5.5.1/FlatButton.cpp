FlatButton::FlatButton(QWidget *parent)
	: QWidget(parent)
{
	connect(&_timer, SIGNAL(timeout()), this, SLOT(timercall()));
}

FlatButton::~FlatButton() {}

void FlatButton::paintEvent(QPaintEvent *) {
	QPainter painter(this);
	painter.setRenderHint(QPainter::Antialiasing);
	QRect Rectangle = QRect(0, 0, width(), height());
	painter.setOpacity(_opacity);
	painter.fillRect(Rectangle, _back);
	painter.save();
	painter.setFont(QFont(_fontfamily, _pointsize));
	painter.setPen(QPen(_color));
	painter.drawText(QRect(rect().x(), rect().y(), rect().width(), rect().height() - _margin), Qt::AlignCenter, _text);
}

void FlatButton::enterEvent(QEvent *) {
	_state = hover;
	_timer_in.start(2);
	setCursor(Qt::PointingHandCursor);
}

void FlatButton::leaveEvent(QEvent *) {
	_state = over;
	_timer_out.start(2);
}

void FlatButton::timercall() {
	switch (_state)
	{
	case FlatButton::hover:
	{
		_opacity += 0.002;
		if (_opacity > 0.950)
		{
			_timer.stop();
		}
	}
		break;
	case FlatButton::over:
	{
		_opacity -= 0.002;
		if (_opacity < 0.750)
		{
			_timer.stop();
		}
	}
		break;
	default:
		break;
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
