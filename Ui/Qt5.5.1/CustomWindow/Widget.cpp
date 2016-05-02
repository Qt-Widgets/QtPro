#include "Widget.h"

Widget::Widget() :
_cursorchanged(false),
_borderWidth(3),
_edge(None),
_rubberband(0)
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
	path.setFillRule(Qt::WindingFill);
	path.addRoundedRect(QRect(0, 0, width(), height()), 5.0, 5.0);
	painter.drawPath(path.simplified());
}

bool Widget::eventFilter(QObject *o, QEvent*e) {
	if (e->type() == QEvent::MouseMove ||
		e->type() == QEvent::HoverMove ||
		e->type() == QEvent::Leave ||
		e->type() == QEvent::MouseButtonPress ||
		e->type() == QEvent::MouseButtonRelease)
	{
		switch (e->type())
		{
		default:
			break;
		case QEvent::MouseMove:
			//mouseMoveEvent(static_cast<QMouseEvent*>(e));
			break;
		case QEvent::HoverMove:
			hoverMoveEvent(static_cast<QHoverEvent*>(e));
			break;
		case QEvent::Leave:
			leaveMoveEvent(e);
			break;
		case QEvent::MouseButtonPress:
			//mouseButtonPress(static_cast<QMouseEvent*>(e));
			break;
		case QEvent::MouseButtonRelease:
			//mouseButtonRealese(static_cast<QMouseEvent*>(e));
			break;
		}
	}
	return false;
}

void Widget::hoverMoveEvent(QHoverEvent *e) {
	updateCursorShape(mapToGlobal(e->pos()));

}

void Widget::leaveMoveEvent(QEvent *e) {
	unsetCursor();
}

void Widget::updateCursorShape(const QPoint &pos) {
	if (isFullScreen() || isMaximized()) { 
		if (_cursorchanged)
		{
			unsetCursor();
			return;
		}
	}
	calculateCursorPosition((pos));
	if (_edge == TopLeft || _edge == BottomRight) {
		setCursor(Qt::SizeFDiagCursor);
		_cursorchanged = true;
	}
	else if (_edge == TopRight || _edge == BottomLeft) {
		setCursor(Qt::SizeBDiagCursor);
		_cursorchanged = true;
	}
	else if (_edge == Right || _edge == Left) {
		setCursor(Qt::SizeHorCursor);
		_cursorchanged = true;
	}
	else if (_edge == Top || _edge == Bottom) {
		setCursor(Qt::SizeVerCursor);
		_cursorchanged = true;
	}
	else {
		if (_cursorchanged)
		{
			_cursorchanged = false;
			unsetCursor();
		}
	}
}

void Widget::calculateCursorPosition(const QPoint &pos) {
	if (pos.x() >= frameGeometry().x() && pos.x() <= frameGeometry().x() + _borderWidth) {
		_edge = Left;
	} else if (pos.x() >= frameGeometry().x() + frameGeometry().width() - _borderWidth && pos.x() <= frameGeometry().x() + frameGeometry().width()) {
		_edge = Right;
	} else if (pos.y() >= frameGeometry().y() && pos.y() <= frameGeometry().y() + _borderWidth) {
		_edge = Top;
	} else if (pos.y() >= frameGeometry().y() + frameGeometry().height() - _borderWidth && pos.y() <= frameGeometry().y() + frameGeometry().height()) {
		_edge = Bottom;
	} else if (pos.y() >= frameGeometry().y() && pos.y() <= frameGeometry().y() + _borderWidth &&
		pos.x() >= frameGeometry().x() && pos.x() <= frameGeometry().x() + _borderWidth) {
		_edge = TopLeft;
	} else if (pos.y() >= frameGeometry().y() + frameGeometry().height() - _borderWidth && pos.y() <= frameGeometry().y() + frameGeometry().height() &&
		pos.x() >= frameGeometry().x() + frameGeometry().width() - _borderWidth && pos.x() <= frameGeometry().x() + frameGeometry().width()) {
		_edge = BottomRight;
	} else if (pos.y() >= frameGeometry().y() && pos.y() <= frameGeometry().y() + _borderWidth &&
		pos.x() >= frameGeometry().x() + frameGeometry().width() - _borderWidth && pos.x() <= frameGeometry().x() + frameGeometry().width()) {
		_edge = TopRight;
	} else if (pos.y() >= frameGeometry().y() + frameGeometry().height() - _borderWidth && pos.y() <= frameGeometry().y() + frameGeometry().height() &&
		pos.x() >= frameGeometry().x() && pos.x() <= frameGeometry().x() + _borderWidth) {
		_edge = BottomLeft;
	} else {
		_edge = None;
	}
}

void Widget::setBorderWidth(const qint16 borderWidth) {
	_borderWidth = borderWidth;
}
