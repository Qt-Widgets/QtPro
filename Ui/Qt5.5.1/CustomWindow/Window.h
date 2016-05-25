#pragma once
#ifndef WINDOW_H
#define WINDOW_H

#include <QtWidgets>
#include "TitleBar.h"
#include "FrameLess.h"

class QGridLayout;
class QPainter;
class QPainterPath;
class QTimer;
class QTime;


class Window : public QWidget {
	Q_OBJECT

public:
	explicit Window(QWidget *parent = 0);
	explicit Window(const QString &title, QWidget *parent = 0);
	~Window();
	void setTitle(const QString &title);
	void setIcon(const QPixmap &icon);
	void setColor(const QColor &titleColor);
	void setRadius(const qreal &radius);
	void setBorderWidth(const qint16 &border);
	void setCloseDisable(bool disable);
	void setMaximizeDisable(bool disable);
	void setMinimizeDisable(bool disable);
	qint16 borderWidth() const;
	QString title() const;
	QPixmap icon() const;
	QColor color() const;
	qreal radius() const;

private:
	TitleBar *_titlebar;
	FrameLess *_framless;
	QGridLayout _layout;
	QGridLayout _primary;
	QGridLayout _secoundry;
	qreal _radius;
	qint16 _borderWidth;
	QString _title;
	bool _hasShadow;

protected:
	void paintEvent(QPaintEvent *) Q_DECL_OVERRIDE;
	void changeEvent(QEvent *e) Q_DECL_OVERRIDE;
};

#endif // !WINDOW_H
