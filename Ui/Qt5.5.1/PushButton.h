#pragma once
#ifndef PUSHBUTTON_H
#define PUSHBUTTON_H

#include <QtWidgets>
class QPainter;
class QPainterPath;
class QPropertyAnimation;
class QParallelAnimationGroup;


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
	void set_back_Color(const QColor color);
	void set_border_Color(const QColor color);
	QColor back_color() const ;
	QColor border_color() const ;
	State _state = Normal;
public:
	explicit PushButton(const QString text = "", QWidget *parent = 0);
	~PushButton();
	void setText(const QString Text);
	QString text() const ;
	void setDefault(bool);
	void setDisable(bool);
protected:
	virtual void paintEvent(QPaintEvent *);
	virtual void enterEvent(QEvent *);
	virtual void leaveEvent(QEvent *);
	virtual void mousePressEvent(QMouseEvent *);
	virtual void mouseReleaseEvent(QMouseEvent *);
	virtual QSize minimumSizeHint() const;
	virtual QSize sizeHint() const;
signals:
	void clicked();
};

#endif // PUSHBUTTON_H
