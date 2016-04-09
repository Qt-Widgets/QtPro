#pragma once
#ifndef BUTTON_H
#define BUTTON_H

#include <QtWidgets>
class QPainter;

class Button : public QWidget
{
	Q_OBJECT
private:
	enum State { Disable, Default, Normal };
	QString _text, _fontfamily = "Calibri";
	int _pointsize = 12, _border_weight = 1;
public:
	explicit Button(const QString text = "", QWidget *parent = 0);
	~Button();
	void setText(const QString Text);
	QString text() const ;
	void setDisable(bool);
protected:
	virtual void paintEvent(QPaintEvent *);
	virtual QSize minimumSizeHint() const;
	virtual QSize sizeHint() const;
signals:
	void clicked();
};

#endif // PUSHBUTTON_H
