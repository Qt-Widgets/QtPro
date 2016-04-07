#pragma once
#ifndef SAMPLE_H
#define SAMPLE_H

#include <QtWidgets>
class QWidget;
class QPainter;
class QTimer;

class FlatButton : public QWidget
{
	Q_OBJECT
public:
	FlatButton(QWidget *parent = 0);
	~FlatButton();
private:
	QColor _back = "#1ABC9C", _color="#FFFFFF";
	qreal _opacity = 0.750;
	QString _fontfamily = "Open Sans", _text = "Submit";
	qint16 _pointsize = 12, _margin = 0;
	QTimer _timer;
	enum State { hover,over};
	State _state;
protected:
	virtual void paintEvent(QPaintEvent *);
	virtual void enterEvent(QEvent *);
	virtual void leaveEvent(QEvent *);
	virtual void mousePressEvent(QMouseEvent *);
	virtual void mouseReleaseEvent(QMouseEvent *);
	public slots:
	void tiemrcall();
};

#endif // SAMPLE_H
