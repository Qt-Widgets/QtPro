Widget::Widget() :
_cursorchanged(false),
_borderWidth(4),
_edge(None),
_leftButtonPressed(false),
_rubberband(0),
_radius(5.0) 
{
	setMouseTracking(true);
	setWindowFlags(Qt::CustomizeWindowHint | Qt::FramelessWindowHint);
	setAttribute(Qt::WA_Hover);
	setAttribute(Qt::WA_TranslucentBackground);
	installEventFilter(this);
}

Widget::~Widget() {}

void Widget::paintEvent(QPaintEvent *) {
	QPainter painter(this);
	painter.setBrush(QColor("#FFFFFF"));
	painter.setPen(Qt::NoPen);
	painter.setRenderHint(QPainter::Antialiasing);

	QPainterPath path;
	path.addRoundedRect(QRect(0, 0, width(), height()), _radius, _radius);
	painter.drawPath(path.simplified());
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
	} else {
		return false;
	}
}

void Widget::mouseHover(QHoverEvent *e) {
	updateCursorShape(mapToGlobal(e->pos()));

}

void Widget::mouseLeave(QEvent *e) {
	Q_UNUSED(e);
	unsetCursor();
	_leftButtonPressed = false;
	_edge = None;
}

void Widget::mousePress(QMouseEvent *e) {
	if (e->buttons() & Qt::LeftButton) {
		_leftButtonPressed = true;
		if (_edge != None) {
			updateRubberBand();
			_rubberband->setGeometry(frameGeometry());
		}
	}
}

void Widget::mouseRealese(QMouseEvent *e) {
	_leftButtonPressed = false;
	_edge = None;
	if (_rubberband) {
		updateRubberBand();
	}
}

void Widget::mouseMove(QMouseEvent *e) {
	if (_leftButtonPressed & _edge != None) {
		QRect originalRect = _rubberband->frameGeometry();
		int left = originalRect.left();
		int top = originalRect.top();
		int right = originalRect.right();
		int bottom = originalRect.bottom();
		if (_edge == Top) {
			top = e->globalPos().y();
		} else if (_edge == Bottom) {
			bottom = e->globalPos().y();
		} else if (_edge == Left) {
			left = e->globalPos().x();
		} else if (_edge == Right) {
			right = e->globalPos().x();
		} else if (_edge == TopLeft) {
			left = e->globalPos().x();
			top = e->globalPos().y();
		} else if (_edge == TopRight) {
			top = e->globalPos().y();
			right = e->globalPos().x();
		} else if (_edge == BottomLeft) {
			left = e->globalPos().x();
			bottom = e->globalPos().y();
		} else if (_edge == BottomRight) {
			bottom = e->globalPos().y();
			right = e->globalPos().x();
		}
		_rubberband->setGeometry(QRect(QPoint(left, top), QPoint(right, bottom)));
		setGeometry(_rubberband->geometry());
	}
}

void Widget::updateCursorShape(const QPoint &pos) {
	if (isFullScreen() || isMaximized()) {
		if (_cursorchanged) {
			unsetCursor();
			return;
		}
	}
	calculateCursorPosition(pos);
	if (_edge == TopLeft || _edge == BottomRight) {
		setCursor(Qt::SizeFDiagCursor);
		_cursorchanged = true;
	} else if (_edge == TopRight || _edge == BottomLeft) {
		setCursor(Qt::SizeBDiagCursor);
		_cursorchanged = true;
	} else if (_edge == Right || _edge == Left) {
		setCursor(Qt::SizeHorCursor);
		_cursorchanged = true;
	} else if (_edge == Top || _edge == Bottom) {
		setCursor(Qt::SizeVerCursor);
		_cursorchanged = true;
	} else if (_cursorchanged) {
		_cursorchanged = false;
		unsetCursor();
	}

}

void Widget::calculateCursorPosition(const QPoint &pos) {
	bool onLeft = pos.x() <= frameGeometry().x() + _borderWidth && pos.x() >= frameGeometry().x() - _borderWidth &&
		pos.y() <= frameGeometry().y() + frameGeometry().height() - _borderWidth && pos.y() >= frameGeometry().y() + _borderWidth;

	bool onRight = pos.x() >= frameGeometry().x() + frameGeometry().width() - _borderWidth && pos.x() <= frameGeometry().x() + frameGeometry().width() &&
		pos.y() >= frameGeometry().y() + _borderWidth && pos.y() <= frameGeometry().y() + frameGeometry().height() - _borderWidth ;

	bool onBottom = pos.x() >= frameGeometry().x() + _borderWidth && pos.x() <= frameGeometry().x() + frameGeometry().width() - _borderWidth  &&
		pos.y() >= frameGeometry().y() + frameGeometry().height() - _borderWidth && pos.y() <= frameGeometry().y() + frameGeometry().height();

	bool onTop = pos.x() >= frameGeometry().x() + _borderWidth && pos.x() <= frameGeometry().x() + frameGeometry().width() - _borderWidth &&
		pos.y() >= frameGeometry().y() - _borderWidth && pos.y() <= frameGeometry().y() + _borderWidth;

	bool  onBottomLeft = pos.x() <= frameGeometry().x() + _borderWidth && pos.x() >= frameGeometry().x() - _borderWidth &&
		pos.y() <= frameGeometry().y() + frameGeometry().height() + _borderWidth && pos.y() >= frameGeometry().y() + frameGeometry().height() - _borderWidth;

	bool onBottomRight = pos.x() >= frameGeometry().x() + frameGeometry().width() - _borderWidth && pos.x() <= frameGeometry().x() + frameGeometry().width() &&
		pos.y() >= frameGeometry().y() + frameGeometry().height() - _borderWidth && pos.y() <= frameGeometry().y() + frameGeometry().height();

	bool onTopRight = pos.x() >= frameGeometry().x() + frameGeometry().width() - _borderWidth && pos.x() <= frameGeometry().x() + frameGeometry().width() + _borderWidth &&
		pos.y() >= frameGeometry().y() - _borderWidth && pos.y() <= frameGeometry().y() + _borderWidth;

	bool onTopLeft = pos.x() >= frameGeometry().x() - _borderWidth && pos.x() <= frameGeometry().x() + _borderWidth &&
		pos.y() >= frameGeometry().y() - _borderWidth && pos.y() <= frameGeometry().y() + _borderWidth;

	if (onLeft) {
		_edge = Left;
	} else if (onRight) {
		_edge = Right;
	} else if (onBottom) {
		_edge = Bottom;
	} else if (onTop) {
		_edge = Top;
	} else if (onBottomLeft) {
		_edge = BottomLeft;
	} else if (onBottomRight) {
		_edge = BottomRight;
	} else if (onTopRight) {
		_edge = TopRight;
	} else if (onTopLeft) {
		_edge = TopLeft;
	} else {
		_edge = None;
	}
}

void Widget::updateRubberBand() {
	if (!_rubberband) {
		_rubberband = new QRubberBand(QRubberBand::Rectangle);
	} else {
		delete _rubberband;
		_rubberband = 0;
	}
}

void Widget::setBorderWidth(const qint16 &borderWidth) {
	_borderWidth = borderWidth;
}
