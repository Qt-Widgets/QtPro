#pragma once
#ifndef WIDGET_H
#define WIDGET_H
#include <QtWidgets>

class QWidget;
class QPainter;
class QpainterPath;
class QRubberBand;

class Widget : public QWidget {
	Q_OBJECT

public:
	explicit Widget();
	~Widget();
	void setBorderWidth(const qint16 &borderWidth);

private:
	enum Edge
	{
		None,
		Top,
		Bottom,
		Left,
		Right,
		TopLeft,
		TopRight,
		BottomLeft,
		BottomRight
	};
	QRubberBand *_rubberband;
	bool _cursorchanged;
	bool _leftButtonPressed;
	qint16 _borderWidth;
	Edge _edge;

private:
	void mouseHover(QHoverEvent *e);
	void mouseLeave(QEvent *e);
	void mousePress(QMouseEvent *e);
	void mouseRealese(QMouseEvent *e);
	void mouseMove(QMouseEvent *e);
	void updateCursorShape(const QPoint &pos);
	void calculateCursorPosition(const QPoint &pos);
	void updateRubberBand();

protected:
	void paintEvent(QPaintEvent *) Q_DECL_OVERRIDE;
	bool eventFilter(QObject *o, QEvent *e) Q_DECL_OVERRIDE;
};

#endif // !WIDGET_H
