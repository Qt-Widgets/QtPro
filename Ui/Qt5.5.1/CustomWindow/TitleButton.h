#pragma once
#ifndef BUTTON_H
#define BUTTON_H

#include <QtWidgets>

class QPainter;
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
	QColor _color = "#B2E2E8";
	qint16 _weight = 2;
	qreal _opacity = 0.999;
	QTimer _timer;
	QPixmap _image = "C:/Users/IMAN/Downloads/media.png";
public:
	explicit TitleButton(Type _tp, QWidget *parent = 0);
	~TitleButton();
protected:
	virtual void paintEvent(QPaintEvent *);
	virtual QSize minimumSizeHint() const;
	virtual QSize sizeHint() const;
	virtual void enterEvent(QEvent *);
	virtual void leaveEvent(QEvent *);
public slots:
	void timercall();

};

#endif // BUTTON_H
