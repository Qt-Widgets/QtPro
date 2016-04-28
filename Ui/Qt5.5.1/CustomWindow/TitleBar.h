#pragma once
#ifndef TITLEBAR_H
#define TITLEBAR_H

#include <QtWidgets>
#include "TitleButton.h"

class QWidget;
class QPainter;
class TitleButton;
class QHBoxLayout;
class QLabel;

class TitleBar : public QWidget {
	Q_OBJECT

private:
	QWidget *_parent;
	QColor _background;//#1976D2
	qint16 _width;
	qint16 _textwidth;
	QHBoxLayout *_l = new QHBoxLayout();
	QHBoxLayout *_primary = new QHBoxLayout();
	QHBoxLayout *_secoundry = new QHBoxLayout();
	QLabel *_Title = new QLabel();
	bool _hastext;
	bool _hasicon;
	bool _draging;
	QPoint _start;
	TitleWidget *_close = new TitleWidget(Close);
	TitleWidget *_minimize = new TitleWidget(Minimize);
	TitleWidget *_maxmimize = new TitleWidget(Maxmimize);
	TitleWidget *_window_icon = new TitleWidget(Icon);

public:
	explicit TitleBar(QWidget *parent = 0);
	~TitleBar();
	void setText(const QString &_text);
	void setIcon(const QPixmap &_pixelmap);
	qint16 minimumwidth() const;

protected:
	virtual void paintEvent(QPaintEvent *);
	virtual void mousePressEvent(QMouseEvent *e);
	virtual void mouseReleaseEvent(QMouseEvent *e);
	virtual void mouseMoveEvent(QMouseEvent *e);
	virtual void mouseDoubleClickEvent(QMouseEvent *e);

	public slots:
	void changeState();
};

#endif // !TITLEBAR_H

