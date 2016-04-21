#pragma once
#ifndef TITLEBUTTON_H
#define TITLEBUTTON_H

#include <QtWidgets>

class QPainter;
class QTimer;

enum Type
{
	Close,
	Minimize,
	Maxmimize
};

class TitleButton : public QWidget
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
	State _state = Normal;
	Type _type = Close;
	QColor _color = "#FFFFFF";
	qint16 _weight = 2, _size = 15;
	qreal _opacity = 0.650, _step = 0.002;
	QTimer _timer;

public:
	explicit TitleButton(Type _tp, QWidget *parent = 0);
	~TitleButton();

protected:
	virtual void paintEvent(QPaintEvent *);
	virtual void enterEvent(QEvent *);
	virtual void leaveEvent(QEvent *);
	virtual void mousePressEvent(QMouseEvent *e);
	virtual QSize minimumSizeHint() const;
	virtual QSize sizeHint() const;

	signals:
	void clicked(Qt::MouseButton _button);

public slots:
	void timercall();

};

#endif // !TITLEBUTTON_H
