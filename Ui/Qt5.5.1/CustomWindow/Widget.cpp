void drawShadow(QPainter &_painter, qint16 _margin, qreal _radius,
QColor _start, QColor _end, qreal _startPosition, qreal _endPosition0, qreal _endPosition1, qreal _width, qreal _height) {
	_painter.setPen(Qt::NoPen);

	QLinearGradient gradient;
	gradient.setColorAt(_startPosition, _start);
	gradient.setColorAt(_endPosition0, _end);
	// Right
	QPointF right0(_width - _margin, _height / 2);
	QPointF right1(_width, _height / 2);
	gradient.setStart(right0);
	gradient.setFinalStop(right1);
	_painter.setBrush(QBrush(gradient));
	_painter.drawRoundRect(QRectF(QPointF(_width - _margin*_radius, _margin), QPointF(_width, _height - _margin)), 0.0, 0.0);
	// Left
	QPointF left0(_margin, _height / 2);
	QPointF left1(0, _height / 2);
	gradient.setStart(left0);
	gradient.setFinalStop(left1);
	_painter.setBrush(QBrush(gradient));
	_painter.drawRoundRect(QRectF(QPointF(_margin *_radius, _margin), QPointF(0, _height - _margin)), 0.0, 0.0);
	// Top
	QPointF top0(_width / 2, _margin);
	QPointF top1(_width / 2, 0);
	gradient.setStart(top0);
	gradient.setFinalStop(top1);
	_painter.setBrush(QBrush(gradient));
	_painter.drawRoundRect(QRectF(QPointF(_width - _margin, 0), QPointF(_margin, _margin)), 0.0, 0.0);
	// Bottom
	QPointF bottom0(_width / 2, _height - _margin);
	QPointF bottom1(_width / 2, _height);
	gradient.setStart(bottom0);
	gradient.setFinalStop(bottom1);
	_painter.setBrush(QBrush(gradient));
	_painter.drawRoundRect(QRectF(QPointF(_margin, _height - _margin), QPointF(_width - _margin, _height)), 0.0, 0.0);
	// BottomRight
	QPointF bottomright0(_width - _margin, _height - _margin);
	QPointF bottomright1(_width, _height);
	gradient.setStart(bottomright0);
	gradient.setFinalStop(bottomright1);
	gradient.setColorAt(_endPosition1, _end);
	_painter.setBrush(QBrush(gradient));
	_painter.drawRoundRect(QRectF(bottomright0, bottomright1), 0.0, 0.0);
	// BottomLeft
	QPointF bottomleft0(_margin, _height - _margin);
	QPointF bottomleft1(0, _height);
	gradient.setStart(bottomleft0);
	gradient.setFinalStop(bottomleft1);
	gradient.setColorAt(_endPosition1, _end);
	_painter.setBrush(QBrush(gradient));
	_painter.drawRoundRect(QRectF(bottomleft0, bottomleft1), 0.0, 0.0);
	// TopLeft
	QPointF topleft0(_margin, _margin);
	QPointF topleft1(0, 0);
	gradient.setStart(topleft0);
	gradient.setFinalStop(topleft1);
	gradient.setColorAt(_endPosition1, _end);
	_painter.setBrush(QBrush(gradient));
	_painter.drawRoundRect(QRectF(topleft0, topleft1), 0.0, 0.0);
	// TopRight
	QPointF topright0(_width - _margin, _margin);
	QPointF topright1(_width, 0);
	gradient.setStart(topright0);
	gradient.setFinalStop(topright1);
	gradient.setColorAt(_endPosition1, _end);
	_painter.setBrush(QBrush(gradient));
	_painter.drawRoundRect(QRectF(topright0, topright1), 0.0, 0.0);
	// Widget
	_painter.setBrush(QBrush("#FFFFFF"));
	_painter.setRenderHint(QPainter::Antialiasing);
	_painter.drawRoundRect(QRectF(QPointF(_margin, _margin), QPointF(_width - _margin, _height - _margin)), _radius, _radius);
}


Widget::Widget() :
_cursorchanged(false),
_leftButtonPressed(false),
_radius(5.0),
_mousePress(None),
_mouseMove(None),
_borderWidth(10)
{
	setMouseTracking(true);
	setWindowFlags(Qt::FramelessWindowHint | Qt::CustomizeWindowHint | Qt::Window);
	setAttribute(Qt::WA_Hover);
	setAttribute(Qt::WA_TranslucentBackground);
	installEventFilter(this);
	_rubberband = new QRubberBand(QRubberBand::Rectangle);
}

Widget::~Widget() {}

void Widget::paintEvent(QPaintEvent *) {
	QPainter painter(this);
	drawShadow(painter, _borderWidth, _radius, QColor(120, 120, 120, 32), QColor(255, 255, 255, 0), 0.0, 1.0, 0.6, width(), height());
}

bool Widget::eventFilter(QObject *o, QEvent*e) {
	if (e->type() == QEvent::MouseMove ||
		e->type() == QEvent::HoverMove ||
		e->type() == QEvent::Leave ||
		e->type() == QEvent::MouseButtonPress ||
		e->type() == QEvent::MouseButtonRelease) {

		switch (e->type())
		{
		case QEvent::MouseMove:
			mouseMove(static_cast<QMouseEvent*>(e));
			return true;
			break;
		case QEvent::HoverMove:
			mouseHover(static_cast<QHoverEvent*>(e));
			return true;
			break;
		case QEvent::Leave:
			mouseLeave(e);
			return true;
			break;
		case QEvent::MouseButtonPress:
			mousePress(static_cast<QMouseEvent*>(e));
			return true;
			break;
		case QEvent::MouseButtonRelease:
			mouseRealese(static_cast<QMouseEvent*>(e));
			return true;
			break;
		}
	}
	else {
		return false;
	}
}

void Widget::mouseHover(QHoverEvent *e) {
	updateCursorShape(mapToGlobal(e->pos()));

}

void Widget::mouseLeave(QEvent *e) {
	Q_UNUSED(e);
	if (!_leftButtonPressed) {
		unsetCursor();
	}
}

void Widget::mousePress(QMouseEvent *e) {
	if (e->button() == Qt::LeftButton) {
		_leftButtonPressed = true;
		calculateCursorPosition(e->globalPos(), frameGeometry(), _mousePress);
		if (_mousePress != None) {
			_rubberband->setGeometry(frameGeometry());
		}
	}
}

void Widget::mouseRealese(QMouseEvent *e) {
	if (e->button() == Qt::LeftButton) {
		_leftButtonPressed = false;
	}
}

void Widget::mouseMove(QMouseEvent *e) {
	if (_leftButtonPressed)
	{
		if (_mousePress != None)
		{
			QRect origRect = _rubberband->frameGeometry();
			int left = origRect.left();
			int top = origRect.top();
			int right = origRect.right();
			int bottom = origRect.bottom();
			if (_mousePress == Top) {
				top = e->globalPos().y();
			}
			else if (_mousePress == Bottom) {
				bottom = e->globalPos().y();
			}
			else if (_mousePress == Left) {
				left = e->globalPos().x();
			}
			else if (_mousePress == Right) {
				right = e->globalPos().x();
			}
			else if (_mousePress == TopLeft) {
				top = e->globalPos().y();
				left = e->globalPos().x();
			}
			else if (_mousePress == TopRight) {
				right = e->globalPos().x();
				top = e->globalPos().y();
			}
			else if (_mousePress == BottomLeft) {
				bottom = e->globalPos().y();
				left = e->globalPos().x();
			}
			else if (_mousePress == BottomRight) {
				bottom = e->globalPos().y();
				right = e->globalPos().x();
			}
			QRect newRect(QPoint(left, top), QPoint(right, bottom));
			if (newRect.width() < minimumWidth() ) {
				left = frameGeometry().x();
			}
			else if (newRect.height() < minimumHeight()  )
			{
				top = frameGeometry().y();
			}
			setGeometry(QRect(QPoint(left, top), QPoint(right, bottom)));
			_rubberband->setGeometry(QRect(QPoint(left, top), QPoint(right, bottom)));
		}
	}
	else {
		updateCursorShape(e->globalPos());
	}
}

void Widget::updateCursorShape(const QPoint &pos) {
	if (isFullScreen() || isMaximized()) {
		if (_cursorchanged) {
			unsetCursor();
		}
		return;
	}
	if (!_leftButtonPressed)
	{
		calculateCursorPosition(pos, frameGeometry(), _mouseMove);
		if (_mouseMove == Top || _mouseMove == Bottom) {
			setCursor(Qt::SizeVerCursor);
			_cursorchanged = true;
		}
		else if (_mouseMove == Left || _mouseMove == Right) {
			setCursor(Qt::SizeHorCursor);
			_cursorchanged = true;
		}
		else if (_mouseMove == TopLeft || _mouseMove == BottomRight) {
			setCursor(Qt::SizeFDiagCursor);
			_cursorchanged = true;
		}
		else if (_mouseMove == TopRight || _mouseMove == BottomLeft) {
			setCursor(Qt::SizeBDiagCursor);
			_cursorchanged = true;
		}
		else if (_cursorchanged) {
			unsetCursor();
			_cursorchanged = false;
		}
	}
}

void Widget::calculateCursorPosition(const QPoint &pos, const QRect &framerect, Edge &_edge) {
	bool onLeft = pos.x() >= framerect.x() - _borderWidth && pos.x() <= framerect.x() + _borderWidth &&
		pos.y() <= framerect.y() + framerect.height() - _borderWidth && pos.y() >= framerect.y() + _borderWidth;

	bool onRight = pos.x() >= framerect.x() + framerect.width() - _borderWidth && pos.x() <= framerect.x() + framerect.width() &&
		pos.y() >= framerect.y() + _borderWidth && pos.y() <= framerect.y() + framerect.height() - _borderWidth;

	bool onBottom = pos.x() >= framerect.x() + _borderWidth && pos.x() <= framerect.x() + framerect.width() - _borderWidth  &&
		pos.y() >= framerect.y() + framerect.height() - _borderWidth && pos.y() <= framerect.y() + framerect.height();

	bool onTop = pos.x() >= framerect.x() + _borderWidth && pos.x() <= framerect.x() + framerect.width() - _borderWidth &&
		pos.y() >= framerect.y() && pos.y() <= framerect.y() + _borderWidth;

	bool  onBottomLeft = pos.x() <= framerect.x() + _borderWidth && pos.x() >= framerect.x() &&
		pos.y() <= framerect.y() + framerect.height() && pos.y() >= framerect.y() + framerect.height() - _borderWidth;

	bool onBottomRight = pos.x() >= framerect.x() + framerect.width() - _borderWidth && pos.x() <= framerect.x() + framerect.width() &&
		pos.y() >= framerect.y() + framerect.height() - _borderWidth && pos.y() <= framerect.y() + framerect.height();

	bool onTopRight = pos.x() >= framerect.x() + framerect.width() - _borderWidth && pos.x() <= framerect.x() + framerect.width() &&
		pos.y() >= framerect.y() && pos.y() <= framerect.y() + _borderWidth;

	bool onTopLeft = pos.x() >= framerect.x() && pos.x() <= framerect.x() + _borderWidth &&
		pos.y() >= framerect.y() && pos.y() <= framerect.y() + _borderWidth;

	if (onLeft) {
		_edge = Left;
	}
	else if (onRight) {
		_edge = Right;
	}
	else if (onBottom) {
		_edge = Bottom;
	}
	else if (onTop) {
		_edge = Top;
	}
	else if (onBottomLeft) {
		_edge = BottomLeft;
	}
	else if (onBottomRight) {
		_edge = BottomRight;
	}
	else if (onTopRight) {
		_edge = TopRight;
	}
	else if (onTopLeft) {
		_edge = TopLeft;
	}
	else {
		_edge = None;
	}
}

void Widget::setRadius(const qreal &radius) {
	_radius = radius;
}

qreal Widget::radius() const {
	return _radius;
}

void Widget::setBorderWidth(const qint16 &borderWidth) {
	_borderWidth = borderWidth;
}

qint16 Widget::borderWidth() const {
	return _borderWidth;
}
