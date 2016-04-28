#pragma once
#ifndef BUTTON_H
#define BUTTON_H

#include <QtWidgets>

class QWidget;
class QPainter;
class QTimer;

enum Type
{
	Close,
	Minimize,
	Maxmimize,
	Icon
};

class TitleWidget : public QWidget
{
	Q_OBJECT

private:
	enum State
	{
		Normal,
		Disable,
		Hover,
		Over
	};
	State _state;
	Type _type ;
	QColor _color = "#FFFFFF";
	qint16 _weight = 2;
	qint16 _size = 38;
	qreal _opacity = 0.550;
	qreal _step = 0.003;
	QTimer *_timer = new QTimer();
	bool _maxmized = 0;
	QPixmap _pixelmap;

public:
	explicit TitleWidget(Type _tp, QWidget *parent = 0);
	~TitleWidget();
	void setMaximized(const bool _control);
	void setPixmap(const QPixmap _pixmap);

protected:
	virtual void paintEvent(QPaintEvent *);
	virtual void enterEvent(QEvent *);
	virtual void leaveEvent(QEvent *);
	virtual void mousePressEvent(QMouseEvent *e);
	virtual QSize minimumSizeHint() const;
	virtual QSize sizeHint() const;

	signals:
	void clicked();

public slots:
	void timercall();

};

#endif // BUTTON_H
