class Switcher : public QWidget
{
	Q_OBJECT

public:
	explicit Switcher(QWidget *parent = 0);
	explicit Switcher(const QColor &color, QWidget *parent = 0);
	void setColor(const QColor &color);
	QColor color() const;

private:
	bool _disabled;
	bool _switch;
	QColor _brush;
	qreal _opacity;
	qreal _radius;
	qint16 _x;
	qint16 _y;
	QTimer _timer;
	qint16 _height;

protected:
	void mousePressEvent(QMouseEvent *e) Q_DECL_OVERRIDE;
	void mouseReleaseEvent(QMouseEvent *e) Q_DECL_OVERRIDE;
	QSize sizeHint() const Q_DECL_OVERRIDE;
	QSize minimumSizeHint() const Q_DECL_OVERRIDE;
	void paintEvent(QPaintEvent*) Q_DECL_OVERRIDE;

	public slots:
	void timercall();

signals:
	void toggled();
};
