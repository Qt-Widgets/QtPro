#pragma once
#ifndef WIDGET_H

#include <QtWidgets>

class QWidget;
class QPainter;
class QpainterPath;
class QRubberBand;

class Widget : public QMainWindow {
	Q_OBJECT

public:
	explicit Widget();
	~Widget();
	void setRadius(const qreal &radius);
	qreal radius() const;
	void setBorderWidth(const qint16 &borderWidth);
	qint16 borderWidth() const;

private:
	enum Edge
	{
		None = 0x0,
		Left = 0x1,
		Top = 0x2,
		Right = 0x3,
		Bottom = 0x4,
		TopLeft = 0x5,
		TopRight = 0x6,
		BottomLeft = 0x7,
		BottomRight = 0x8
	};
	QRubberBand *_rubberband;
	bool _cursorchanged;
	bool _leftButtonPressed;
	qreal _radius;
	Edge _mousePress;
	Edge _mouseMove;
	qint16 _borderWidth;

private:
	void mouseHover(QHoverEvent *e);
	void mouseLeave(QEvent *e);
	void mousePress(QMouseEvent *e);
	void mouseRealese(QMouseEvent *e);
	void mouseMove(QMouseEvent *e);
	void updateCursorShape(const QPoint &pos);
	void updateRubberBand();
	void calculateCursorPosition(const QPoint &pos, const QRect &framerect, Edge &_edge);

protected:
	void paintEvent(QPaintEvent *) Q_DECL_OVERRIDE;
	bool eventFilter(QObject *o, QEvent *e) Q_DECL_OVERRIDE;
};

#endif // !WIDGET_H
