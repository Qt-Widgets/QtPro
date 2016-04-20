#pragma once
#ifndef TITLEBAR_H
#define TITLEBAR_H

#include <QtWidgets>

class QWidget;
class QPainter;

class TitleBar : public QWidget {
	Q_OBJECT

private:
	QColor _background = "#00A0B4";
	QPixmap *_pixelmap;
public:
	explicit TitleBar(QWidget *parent = 0);
	~TitleBar();
protected:
	virtual void paintEvent(QPaintEvent *);
	virtual void resizeEvent(QResizeEvent *);
};

#endif // !TITLEBAR_H
