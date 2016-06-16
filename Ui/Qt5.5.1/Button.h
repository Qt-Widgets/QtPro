#include <QtWidgets>

class Button :public QWidget
{
	Q_OBJECT

public:
	explicit Button(QWidget *parent = 0);
	explicit Button(const QString &text, const QColor &color, QWidget *parent = 0);
	~Button();
	void setText(const QString &text);
	void setColor(const QColor &color);
	void setDisable(bool _disable);
	void setFont(const QString &family, const qint16 &pointsize);
	bool isDisable() const;
	QString text() const;
	QColor color() const;

protected:
	enum State {
		None = 0x00,
		Hover = 0x02,
		Over = 0x04,
		Pressed = 0x08,
		Released = 0x0B,
	};

	bool _disabled;

	State _state;

	QString _text;
	QString _fontfamily;

	QColor _color;
	QColor _brush;

	qreal _opacity;
	qreal _radius;

	qint16 _height;
	qint16 _padding;
	qint16 _pointsize;
	qint16 _x;
	qint16 _y;

	QFont _font;

	QTimer _timer;

protected:
	void mouseReleaseEvent(QMouseEvent *e) Q_DECL_OVERRIDE;
	void mousePressEvent(QMouseEvent *e) Q_DECL_OVERRIDE;
	void enterEvent(QEvent *) Q_DECL_OVERRIDE;
	void leaveEvent(QEvent *) Q_DECL_OVERRIDE;
	QSize sizeHint() const Q_DECL_OVERRIDE;
	QSize minimumSizeHint() const Q_DECL_OVERRIDE;

signals:
	void clicked();
};


class RaisedButton :public Button
{
	Q_OBJECT

public:
	explicit RaisedButton(QWidget *parent = 0);
	explicit RaisedButton(const QString &text, QWidget *parent = 0);
	explicit RaisedButton(const QString &text, const QColor &color, QWidget *parent = 0);
	~RaisedButton();

protected:
	void paintEvent(QPaintEvent*) Q_DECL_OVERRIDE;

	public slots:
	void timercall();
};


class FlatButton :public Button
{
	Q_OBJECT

public:
	explicit FlatButton(QWidget *parent = 0);
	explicit FlatButton(const QString &text, QWidget *parent = 0);
	explicit FlatButton(const QString &text, const QColor &color, QWidget *parent = 0);
	~FlatButton();

private:
	qint16 _rait;

protected:
	void paintEvent(QPaintEvent*) Q_DECL_OVERRIDE;
	void mousePressEvent(QMouseEvent *e) Q_DECL_OVERRIDE;
	void mouseReleaseEvent(QMouseEvent *e) Q_DECL_OVERRIDE;
	void enterEvent(QEvent *e) Q_DECL_OVERRIDE;
	void leaveEvent(QEvent *e) Q_DECL_OVERRIDE;

	public slots:
	void timercall();
};


class IconButton :public Button
{
	Q_OBJECT

public:
	explicit IconButton(const QPixmap &icon, QWidget *parent = 0);
	explicit IconButton(const QPixmap &icon, const QColor &brush, QWidget *parent = 0);

private:
	QPixmap _icon;
	QRect _rect;
	qint16 _rait;

protected:
	void paintEvent(QPaintEvent*) Q_DECL_OVERRIDE;
	QSize minimumSizeHint() const Q_DECL_OVERRIDE;
	void mousePressEvent(QMouseEvent *e) Q_DECL_OVERRIDE;
	void mouseReleaseEvent(QMouseEvent *e) Q_DECL_OVERRIDE;

	public slots:
	void timercall();
};


class LinkButton :public Button
{
	Q_OBJECT

public:
	explicit LinkButton(const QString &text, QWidget *parent = 0);
protected:
	void paintEvent(QPaintEvent*) Q_DECL_OVERRIDE;
	void enterEvent(QEvent *e) Q_DECL_OVERRIDE;
	void leaveEvent(QEvent *e) Q_DECL_OVERRIDE;
	QSize minimumSizeHint() const;
};
