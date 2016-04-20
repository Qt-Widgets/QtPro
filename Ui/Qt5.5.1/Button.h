#pragma once
#ifndef BUTTON_H
#define BUTTON_H

#include <QtWidgets>

class QPainter;

class Button : public QWidget
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
public:
	explicit Button(QWidget *parent = 0);
	~Button();
	State _state = Normal;
protected:
	virtual void paintEvent(QPaintEvent *);
	virtual QSize minimumSizeHint() const;
	virtual QSize sizeHint() const;
signals:
	void clicked();
};

#endif // BUTTON_H
