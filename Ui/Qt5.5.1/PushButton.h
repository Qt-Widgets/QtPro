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
private:
	enum State { Disable, Default, Normal };
	QString _text, _fontfamily = "Calibri";
	QColor _border = "#ADADAD", _back = "#E1E1E1", _color = "#000000";
	int _pointsize = 12, _border_weight = 1;
	void set_back_Color(QColor color);
	void set_border_Color(QColor color);
	QColor back_color();
	QColor border_color();
	State _state;
public:
	explicit PushButton(QString text = "", QWidget *parent = 0);
	~PushButton();
	void setText(QString Text);
	QString text();
	void setDefault(bool Default);
	void setDisable(bool);
protected:
	void paintEvent(QPaintEvent *);
	void enterEvent(QEvent *);
	void leaveEvent(QEvent *);
	void mousePressEvent(QMouseEvent *);
	void mouseReleaseEvent(QMouseEvent *);
signals:
	void clicked();
};

#endif // PUSHBUTTON_H
