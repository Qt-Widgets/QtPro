#pragma once

#include <QtWidgets/QWidget>
#include <QtGui/QMouseEvent>
#include <QtGui/QPainter>
#include <QtGui/QPixmap>
#include <QtGui/QImage>
#include <QtGui/QPen>
#include <QtGui/QFont>
#include <QtGui/QColor>
#include <QtCore/QObject>
#include <QtCore/QEvent>
#include <QtCore/QRect>
#include <QtCore/QRectF>
#include <QtCore/Qt>
#include <QtCore/QSize>
#include <QtCore/QString>
#include <QtCore/QTimer>
#include <QtCore/QDebug>

typedef enum ButtonState {
	None = 0x00,
	Hover = 0x02,
	Over = 0x04,
	Pressed = 0x08,
	Released = 0x0B,
};

class Button :public QWidget
{
	Q_OBJECT

public:
	explicit Button(QWidget *parent = 0);
	explicit Button(const QString &text, const QColor &color, QWidget *parent = 0);
	void setText(const QString &text);
	void setColor(const QColor &color);
	void setDisable(bool _disable);
	void setFont(const QString &family, const qint16 &pointsize);
	bool isDisable() const;
	QString text() const;
	QColor color() const;

protected:
	bool _disabled;
	ButtonState _state;
	QString _text;
	QString _fontfamily;
	QColor _brush;
	qreal _opacity;
	qreal _o;
	qreal _radius;
	qreal _rait;
	qreal _duration;
	qreal _r;
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
	void resizeEvent(QResizeEvent *e) Q_DECL_OVERRIDE;
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

protected:
	void paintEvent(QPaintEvent*) Q_DECL_OVERRIDE;
	void enterEvent(QEvent *e) Q_DECL_OVERRIDE;
	void leaveEvent(QEvent *e) Q_DECL_OVERRIDE;
	void mousePressEvent(QMouseEvent *e) Q_DECL_OVERRIDE;
	void mouseReleaseEvent(QMouseEvent *e) Q_DECL_OVERRIDE;

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
	explicit IconButton(QWidget *parent = 0);
	explicit IconButton(const QPixmap &icon, QWidget *parent = 0);
	explicit IconButton(const QPixmap &icon, const QColor &brush, QWidget *parent = 0);
	void setPixmap(const QPixmap &icon);

protected:
	QPixmap _icon;
	QRect _rect;

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
	explicit LinkButton(QWidget *parent = 0);
	explicit LinkButton(const QString &text, QWidget *parent = 0);

protected:
	void paintEvent(QPaintEvent*) Q_DECL_OVERRIDE;
	void enterEvent(QEvent *e) Q_DECL_OVERRIDE;
	void leaveEvent(QEvent *e) Q_DECL_OVERRIDE;
	QSize minimumSizeHint() const;
};


class FloatActionButton :public Button
{
	Q_OBJECT

public:
	explicit FloatActionButton(QWidget *parent = 0);
	explicit FloatActionButton(const QPixmap &icon, const QColor &brush, QWidget *parent = 0);
	void setPixmap(const QPixmap &icon);

protected:
	QPixmap _icon;
	QRect _rect;
	qint16 _margin;

protected:
	void paintEvent(QPaintEvent*) Q_DECL_OVERRIDE;
	QSize minimumSizeHint() const Q_DECL_OVERRIDE;
	void enterEvent(QEvent *e) Q_DECL_OVERRIDE;
	void leaveEvent(QEvent *e) Q_DECL_OVERRIDE;
	void mousePressEvent(QMouseEvent *e) Q_DECL_OVERRIDE;
	void mouseReleaseEvent(QMouseEvent *e) Q_DECL_OVERRIDE;

	public slots:
	void timercall();
};
