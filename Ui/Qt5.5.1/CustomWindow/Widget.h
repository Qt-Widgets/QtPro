#pragma once
#ifdef Q_OS_WIN

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
	void setRadius(const qreal &radius);
	qreal radius() const;

private:
	enum Edge
	{
		None,
		Left,
		Top,
		Right,
		Bottom,
		TopLeft,
		TopRight,
		BottomLeft,
		BottomRight
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
	void calculateCursorPosition(const QPoint &pos, const QRect &framerect,Edge &_edge);

protected:
	void paintEvent(QPaintEvent *) Q_DECL_OVERRIDE;
	bool eventFilter(QObject *o, QEvent *e) Q_DECL_OVERRIDE;
};

#endif
