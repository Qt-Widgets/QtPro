#pragma once
#ifndef BUTTON_H
#define BUTTON_H

#include <QtWidgets>
class QPainter;
enum State
{
	Normal,
	Disable,
	Hover,
	Over
};

class Button : public QWidget
{
	Q_OBJECT
private:
	QString _text, _fontfamily = "Open Sans";
	int _pointsize = 12, _border_weight = 1;
public:
	explicit Button(const QString text = "", QWidget *parent = 0);
	~Button();
	void setText(const QString Text);
	void setDisable(bool);
	QString text() const;
	State _state = Normal;
protected:
	virtual void paintEvent(QPaintEvent *);
	virtual QSize minimumSizeHint() const;
	virtual QSize sizeHint() const;
signals:
	void clicked();
};

#endif // BUTTON_H
