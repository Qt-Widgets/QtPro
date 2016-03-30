#pragma once
#ifndef SAMPLE_H
#define SAMPLE_H

#include <QtWidgets>
class QWidget;
class QPainter;
class QTimer;

class CircleButton : public QWidget
{
	Q_OBJECT
public:
	CircleButton(QWidget *parent = 0);
	~CircleButton();
private:
	QColor _back = "#1ABC9C", _color="#FFFFFF";
	qreal _opacity = 0.750;
	QString _fontfamily = "Open Sans", _text = "Submit";
	qint16 _pointsize = 12, _margin = 25, _blank = 150;
	QTimer _timer_in, _timer_out;
	QPixmap _image, _image1 = "C:/Users/Zahra/Desktop/Arrow-2.png", _image0 = "C:/Users/Zahra/Desktop/Arrow-1.png";
protected:
	virtual void paintEvent(QPaintEvent *);
	virtual void enterEvent(QEvent *);
	virtual void leaveEvent(QEvent *);
	public slots:
	void in_timer();
	void out_timer();
};

#endif // SAMPLE_H
