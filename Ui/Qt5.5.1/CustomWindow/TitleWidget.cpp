TitleWidget::TitleWidget(Type _tp, QWidget *parent)
	:QWidget(parent),
	_state(Normal),
	_color("#FFFFFF"),
	_weight(2),
	_size(38),
	_opacity(0.550),
	_step(0.003),
	_maxmized(false)
{
	setMouseTracking(true);
	setFixedSize(_size, _size);
	connect(_timer, SIGNAL(timeout()), this, SLOT(timercall()));
	switch (_tp)
	{
	case Close:
		_type = Close;
		break;
	case Minimize:
		_type = Minimize;
		break;
	case Maxmimize:
		_type = Maxmimize;
		break;
	case Icon:
		_type = Icon;
	}
}

TitleWidget::~TitleWidget() {}

void TitleWidget::setMaximized(const bool _control) {
	_maxmized = _control;
	update();
}

void TitleWidget::setPixmap(const QPixmap _pixmap) {
	_pixelmap = _pixmap;
	update();
}

void TitleWidget::paintEvent(QPaintEvent *) {
	QPainter painter(this);
	painter.setRenderHint(QPainter::HighQualityAntialiasing);
	painter.setPen(QPen(_color, _weight));
	painter.setOpacity(_opacity);
	switch (_type)
	{
	case Close:
	{
		painter.drawLine((_size / 2) - 6, (_size / 2) - 6, (_size / 2) - 1, (_size / 2) - 1);
		painter.drawLine((_size / 2) + 1, (_size / 2) + 1, (_size / 2) + 6, (_size / 2) + 6);
		painter.drawLine((_size / 2) + 6, (_size / 2) - 6, (_size / 2) - 6, (_size / 2) + 6);
	}
	break;
	case Minimize:
	{
		painter.drawLine((_size / 2) - 7, (_size / 2) + 7, (_size / 2) + 7, (_size / 2) + 7);
	}
	break;
	case Maxmimize:
	{
		if (_maxmized)
		{
			//inner
			painter.drawLine((_size / 2) - 7, (_size / 2) - 2, (_size / 2) - 7, (_size / 2) + 7);
			painter.drawLine((_size / 2) - 5, (_size / 2) + 7, (_size / 2) + 4, (_size / 2) + 7);
			painter.drawLine((_size / 2) + 4, (_size / 2) + 5, (_size / 2) + 4, (_size / 2) - 2);
			painter.drawLine((_size / 2) + 2, (_size / 2) - 2, (_size / 2) - 5, (_size / 2) - 2);
			//outer
			painter.drawLine((_size / 2) - 4, (_size / 2) - 4, (_size / 2) - 4, (_size / 2) - 6);
			painter.drawLine((_size / 2) - 2, (_size / 2) - 6, (_size / 2) + 8, (_size / 2) - 6);
			painter.drawLine((_size / 2) + 8, (_size / 2) - 4, (_size / 2) + 8, (_size / 2) + 4);
			painter.drawLine((_size / 2) + 6, (_size / 2) + 4, (_size / 2) + 6, (_size / 2) + 4);
		}
		else
		{
			painter.drawLine((_size / 2) - 7, (_size / 2) - 7, (_size / 2) - 7, (_size / 2) + 7);
			painter.drawLine((_size / 2) - 5, (_size / 2) + 7, (_size / 2) + 7, (_size / 2) + 7);
			painter.drawLine((_size / 2) + 7, (_size / 2) + 5, (_size / 2) + 7, (_size / 2) - 7);
			painter.drawLine((_size / 2) + 5, (_size / 2) - 7, (_size / 2) - 5, (_size / 2) - 7);

		}
	}
	case Icon:
	{
		painter.setPen(Qt::NoPen);
		painter.setOpacity(1.0);
		painter.setRenderHint(QPainter::SmoothPixmapTransform);
		if (_pixelmap.isNull()) IGNORE;
		else _pixelmap = _pixelmap.scaled((_size / 2) + 5, (_size / 2) + 5, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
		QRect _rect = QRect((_size / 2) - 12, (_size / 2) - 12, (_size / 2) + 3, (_size / 2) + 3);
		painter.drawPixmap(_rect, _pixelmap);
	}
	break;
	}
}

void TitleWidget::enterEvent(QEvent *) {
	_state = Hover;
	_timer->start(1);
}

void TitleWidget::leaveEvent(QEvent *) {
	_state = Over;
	_timer->start(1.5);
}

void TitleWidget::mousePressEvent(QMouseEvent *e) {
	if (e->type() == QMouseEvent::MouseButtonPress && e->button() == Qt::LeftButton)
	{
		e->accept();
		emit clicked();
	}
}

QSize TitleWidget::minimumSizeHint() const {
	return sizeHint();
}

QSize TitleWidget::sizeHint() const {
	return QSize(_size, _size);
}

void TitleWidget::timercall() {
	switch (_state)
	{
	case TitleWidget::Hover:
	{
		_opacity += _step;
		if (_opacity > 1.000)
		{
			_timer->stop();
		}
	}
	break;
	case TitleWidget::Over:
	{
		_opacity -= _step;
		if (_opacity < 0.550)
		{
			_timer->stop();
		}
	}
	break;
	default:
		break;
	}
	update();
}
