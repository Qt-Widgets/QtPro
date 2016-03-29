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
	qint16 _pointsize = 12, _margin = 45;
	QTimer _timer_in, _timer_out;
protected:
	virtual void paintEvent(QPaintEvent *);
};

#endif // SAMPLE_H
