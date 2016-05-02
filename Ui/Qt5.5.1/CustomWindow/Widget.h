class Widget : public QWidget {
	Q_OBJECT

public:
	explicit Widget();
	~Widget();
	void setBorderWidth(const qint16 borderWidth);

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
	qint16 _borderWidth;
	Edge _edge;

private:
	void hoverMoveEvent(QHoverEvent *e);
	void leaveMoveEvent(QEvent *e);
	void updateCursorShape(const QPoint &pos);
	void calculateCursorPosition(const QPoint &pos);

protected:
	void paintEvent(QPaintEvent *) Q_DECL_OVERRIDE;
	bool eventFilter(QObject *o, QEvent *e) Q_DECL_OVERRIDE;
};
