#include <QtWidgets>

class QPainter;
class QPointF;
class QRectF;
class QColor;
class QBrush;
class QLinerGradient;

void drawShadow(QPainter &_painter, const qint16 _margin, const qreal _radius, const QColor _start, const QColor _end,
	const qreal _startPosition, const qreal _endPosition0, const qreal _endPosition1, const qreal _width, const qreal _height) {

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
