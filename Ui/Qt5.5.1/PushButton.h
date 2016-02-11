#pragma once
#ifndef PUSHBUTTON_H
#define PUSHBUTTON_H

#include <QtWidgets>
class QPainter;
class QPainterPath;


class PushButton : public QWidget
{
	Q_OBJECT
	Q_PROPERTY(QColor back_color READ back_color WRITE set_back_Color)
	Q_PROPERTY(QColor border_color READ border_color WRITE set_border_Color)
public:
	explicit PushButton(QString text = "", QWidget *parent = 0);
	~PushButton();
	void setText(QString Text);
	QString text();
protected:
	void paintEvent(QPaintEvent *);
	void enterEvent(QEvent *);
	void leaveEvent(QEvent *);
	void mousePressEvent(QMouseEvent *);
	void mouseReleaseEvent(QMouseEvent *);
private:
	QString _text , _fontfamily = "Calibri";
	QColor _border = "#ADADAD", _back = "#E1E1E1", _color = "#000000";
	int _pointsize = 12;
	void set_back_Color(QColor color);
	void set_border_Color(QColor color);
	QColor back_color();
	QColor border_color();
signals:
	void clicked();
};

#endif // PUSHBUTTON_H
