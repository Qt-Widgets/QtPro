class Input : public QWidget
{
	Q_OBJECT

public:
	explicit Input(QWidget *parent = 0);
	explicit Input(const QString &placeholder, QWidget *parent = 0);
	QString text() const;
	void setText(const QString &text);
	void setPlaceHolderText(const QString &hinttext);
	QString placeHolderText() const;

private:
	enum State {
		None = 0x00,
		Hover = 0x02,
		Over = 0x04,
		FocusIn = 0x08,
		FocusOut = 0x0B
	};
	State _state;
	QString _label;
	QString _text;
	QString _fontFamily;
	QColor _brush;
	QTimer _timer;
	QFont _font;
	qreal _dividerMargin;
	qreal _dividerMarginStep;
	qreal _opacity;
	qreal _labelPointSize;
	qreal _labelPointSizeStep;
	qreal _labelMargin;
	qreal _labelMarginStep;
	qreal _pointSizeStep;
	qint16 _height;
	qint16 _dividerPadding;
	qint16 _textPadding;
	qint16 _textwidth;

protected:
	void paintEvent(QPaintEvent *e) Q_DECL_OVERRIDE;
	void enterEvent(QEvent *e) Q_DECL_OVERRIDE;
	void leaveEvent(QEvent *e) Q_DECL_OVERRIDE;
	void mousePressEvent(QMouseEvent *) Q_DECL_OVERRIDE;
	void mouseReleaseEvent(QMouseEvent *e) Q_DECL_OVERRIDE;
	void focusInEvent(QFocusEvent *e) Q_DECL_OVERRIDE;
	void focusOutEvent(QFocusEvent *e) Q_DECL_OVERRIDE;
	void resizeEvent(QResizeEvent *e) Q_DECL_OVERRIDE;
	void keyPressEvent(QKeyEvent *e) Q_DECL_OVERRIDE;
	QSize minimumSizeHint() const Q_DECL_OVERRIDE;
	QSize sizeHint() const Q_DECL_OVERRIDE;

	public slots:
	void timercall();

signals:
	void textChanged();
	void focused();
};
