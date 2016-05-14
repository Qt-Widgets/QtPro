#include <QtWidgets>

class QPainter;
class QPointF;
class QRectF;
class QColor;
class QBrush;
class QLinerGradient;

void drawShadow(QPainter &_painter, const qint16 _margin, const qreal _radius, const QColor _start, const QColor _end,
	const qreal _startPosition, const qreal _endPosition0, const qreal _endPosition1, const qreal _width, const qreal _height,
	bool _left = true, bool _right = true, bool _top = true, bool _bottom = true) {

	_painter.setPen(Qt::NoPen);

	QRectF widget(QPointF(_margin, _margin), QPointF(_width - _margin, _height - _margin));

	QLinearGradient gradient;
	gradient.setColorAt(_startPosition, _start);
	gradient.setColorAt(_endPosition0, _end);

	QPointF right0(_width - _margin, _height / 2);
	QPointF right1(_width, _height / 2);

	QPointF left0(_margin, _height / 2);
	QPointF left1(0, _height / 2);

	QPointF top0(_width / 2, _margin);
	QPointF top1(_width / 2, 0);

	QPointF bottom0(_width / 2, _height - _margin);
	QPointF bottom1(_width / 2, _height);

	QPointF bottomleft0(_margin, _height - _margin);
	QPointF bottomleft1(0, _height);

	QPointF bottomright0(_width - _margin, _height - _margin);
	QPointF bottomright1(_width, _height);

	QPointF topleft0(_margin, _margin);
	QPointF topleft1(0, 0);

	QPointF topright0(_width - _margin, _margin);
	QPointF topright1(_width, 0);
	if (_left && _right && _top && _bottom) {
		gradient.setStart(right0);
		gradient.setFinalStop(right1);
		_painter.setBrush(QBrush(gradient));
		_painter.drawRoundRect(QRectF(QPointF(_width - _margin, _margin), QPointF(_width, _height - _margin)), 0.0, 0.0);
		gradient.setStart(left0);
		gradient.setFinalStop(left1);
		_painter.setBrush(QBrush(gradient));
		_painter.drawRoundRect(QRectF(QPointF(0, _margin), QPointF(_margin, _height - _margin)), 0.0, 0.0);
		gradient.setStart(top0);
		gradient.setFinalStop(top1);
		_painter.setBrush(QBrush(gradient));
		_painter.drawRoundRect(QRectF(QPointF(_margin, 0), QPointF(_width - _margin, _margin)), 0.0, 0.0);
		gradient.setStart(bottom0);
		gradient.setFinalStop(bottom1);
		_painter.setBrush(QBrush(gradient));
		_painter.drawRoundRect(QRectF(QPointF(_margin, _height - _margin), QPointF(_width - _margin, _height)), 0.0, 0.0);
		gradient.setStart(bottomright0);
		gradient.setFinalStop(bottomright1);
		gradient.setColorAt(_endPosition1, _end);
		_painter.setBrush(QBrush(gradient));
		_painter.drawRoundRect(QRectF(bottomright0, bottomright1), 0.0, 0.0);
		gradient.setStart(bottomleft0);
		gradient.setFinalStop(bottomleft1);
		gradient.setColorAt(_endPosition1, _end);
		_painter.setBrush(QBrush(gradient));
		_painter.drawRoundRect(QRectF(bottomleft0, bottomleft1), 0.0, 0.0);
		gradient.setStart(topleft0);
		gradient.setFinalStop(topleft1);
		gradient.setColorAt(_endPosition1, _end);
		_painter.setBrush(QBrush(gradient));
		_painter.drawRoundRect(QRectF(topleft0, topleft1), 0.0, 0.0);
		gradient.setStart(topright0);
		gradient.setFinalStop(topright1);
		gradient.setColorAt(_endPosition1, _end);
		_painter.setBrush(QBrush(gradient));
		_painter.drawRoundRect(QRectF(topright0, topright1), 0.0, 0.0);
		widget = QRectF(QPointF(_margin, _margin), QPointF(_width - _margin, _height - _margin));
	} else if (!_left && !_right && !_top && !_bottom) {
		widget = QRectF(QPointF(0, 0), QPointF(_width, _height));
	} else if (!_left && _right && !_top && !_bottom) {
		gradient.setStart(right0);
		gradient.setFinalStop(right1);
		_painter.setBrush(QBrush(gradient));
		_painter.drawRoundRect(QRectF(QPointF(_width - _margin, 0), QPointF(_width, _height)), 0.0, 0.0);
		widget = QRectF(QPointF(0, 0), QPointF(_width, _height));
	} else if (_left && !_right && !_top && !_bottom) {
		gradient.setStart(left0);
		gradient.setFinalStop(left1);
		_painter.setBrush(QBrush(gradient));
		_painter.drawRoundRect(QRectF(QPointF(0, 0), QPointF(_margin, _height)), 0.0, 0.0);
		widget = QRectF(QPointF(_margin, 0), QPointF(_width, _height));
	} else if (!_left && !_right && _top && !_bottom) {
		gradient.setStart(top0);
		gradient.setFinalStop(top1);
		_painter.setBrush(QBrush(gradient));
		_painter.drawRoundRect(QRectF(QPointF(0, 0), QPointF(_width, _margin)), 0.0, 0.0);
		widget = QRectF(QPointF(0, _margin), QPointF(_width, _height));
	} else if (!_left && !_right && !_top && _bottom) {
		gradient.setStart(bottom0);
		gradient.setFinalStop(bottom1);
		_painter.setBrush(QBrush(gradient));
		_painter.drawRoundRect(QRectF(QPointF(0, _height - _margin), QPointF(_width, _height)), 0.0, 0.0);
		widget = QRectF(QPointF(0, 0), QPointF(_width, _height - _margin));
	} else if (!_left && !_right && _top && _bottom) {
		gradient.setStart(bottom0);
		gradient.setFinalStop(bottom1);
		_painter.setBrush(QBrush(gradient));
		_painter.drawRoundRect(QRectF(QPointF(0, _height - _margin), QPointF(_width, _height)), 0.0, 0.0);
		gradient.setStart(top0);
		gradient.setFinalStop(top1);
		_painter.setBrush(QBrush(gradient));
		_painter.drawRoundRect(QRectF(QPointF(0, 0), QPointF(_width, _margin)), 0.0, 0.0);
		widget = QRectF(QPointF(0, _margin), QPointF(_width, _height - _margin));
	} else if (_left && _right && !_top && !_bottom) {
		gradient.setStart(left0);
		gradient.setFinalStop(left1);
		_painter.setBrush(QBrush(gradient));
		_painter.drawRoundRect(QRectF(QPointF(0, 0), QPointF(_margin, _height)), 0.0, 0.0);
		gradient.setStart(right0);
		gradient.setFinalStop(right1);
		_painter.setBrush(QBrush(gradient));
		_painter.drawRoundRect(QRectF(QPointF(_width - _margin, 0), QPointF(_width, _height)), 0.0, 0.0);
		widget = QRectF(QPointF(_margin, 0), QPointF(_width - _margin, _height));
	} else if (_left && !_right && !_top && _bottom) {
		gradient.setStart(left0);
		gradient.setFinalStop(left1);
		_painter.setBrush(QBrush(gradient));
		_painter.drawRoundRect(QRectF(QPointF(0, 0), QPointF(_margin, _height-_margin)), 0.0, 0.0);
		gradient.setStart(bottom0);
		gradient.setFinalStop(bottom1);
		_painter.setBrush(QBrush(gradient));
		_painter.drawRoundRect(QRectF(QPointF(_margin, _height - _margin), QPointF(_width, _height)), 0.0, 0.0);
		gradient.setStart(bottomleft0);
		gradient.setFinalStop(bottomleft1);
		gradient.setColorAt(_endPosition1, _end);
		_painter.setBrush(QBrush(gradient));
		_painter.drawRoundRect(QRectF(bottomleft0, bottomleft1), 0.0, 0.0);
		widget = QRectF(QPointF(_margin, _height - _margin), QPointF(_width, 0));
	} else if (_left && !_right && _top && !_bottom) {
		gradient.setStart(left0);
		gradient.setFinalStop(left1);
		_painter.setBrush(QBrush(gradient));
		_painter.drawRoundRect(QRectF(QPointF(0, _margin), QPointF(_margin, _height)), 0.0, 0.0);
		gradient.setStart(top0);
		gradient.setFinalStop(top1);
		_painter.setBrush(QBrush(gradient));
		_painter.drawRoundRect(QRectF(QPointF(_margin, 0), QPointF(_width, _margin)), 0.0, 0.0);
		gradient.setStart(topleft0);
		gradient.setFinalStop(topleft1);
		gradient.setColorAt(_endPosition1, _end);
		_painter.setBrush(QBrush(gradient));
		_painter.drawRoundRect(QRectF(topleft0, topleft1), 0.0, 0.0);
		widget = QRectF(QPointF(_margin, _margin), QPointF(_width, _height));
	} else if (!_left && _right && !_top && _bottom) {
		gradient.setStart(right0);
		gradient.setFinalStop(right1);
		_painter.setBrush(QBrush(gradient));
		_painter.drawRoundRect(QRectF(QPointF(_width - _margin, 0), QPointF(_width, _height - _margin)), 0.0, 0.0);
		gradient.setStart(bottom0);
		gradient.setFinalStop(bottom1);
		_painter.setBrush(QBrush(gradient));
		_painter.drawRoundRect(QRectF(QPointF(0, _height - _margin), QPointF(_width - _margin, _height)), 0.0, 0.0);
		gradient.setStart(bottomright0);
		gradient.setFinalStop(bottomright1);
		gradient.setColorAt(_endPosition1, _end);
		_painter.setBrush(QBrush(gradient));
		_painter.drawRoundRect(QRectF(bottomright0, bottomright1), 0.0, 0.0);
		widget = QRectF(QPointF(0, 0), QPointF(_width - _margin, _height - _margin));
	} else if (!_left && _right && _top && !_bottom) {
		gradient.setStart(right0);
		gradient.setFinalStop(right1);
		_painter.setBrush(QBrush(gradient));
		_painter.drawRoundRect(QRectF(QPointF(_width - _margin, _margin), QPointF(_width, _height)), 0.0, 0.0);
		gradient.setStart(top0);
		gradient.setFinalStop(top1);
		_painter.setBrush(QBrush(gradient));
		_painter.drawRoundRect(QRectF(QPointF(0, 0), QPointF(_width-_margin, _margin)), 0.0, 0.0);
		gradient.setStart(topright0);
		gradient.setFinalStop(topright1);
		gradient.setColorAt(_endPosition1, _end);
		_painter.setBrush(QBrush(gradient));
		_painter.drawRoundRect(QRectF(topright0, topright1), 0.0, 0.0);
		widget = QRectF(QPointF(0, _height), QPointF(_width - _margin, _margin));
	}
	// Widget
	_painter.setBrush(QBrush("#FFFFFF"));
	_painter.setRenderHint(QPainter::HighQualityAntialiasing);
	QPainterPath path;
	path.addRoundedRect(widget, _radius, _radius);
	_painter.drawPath(path.simplified());
}
