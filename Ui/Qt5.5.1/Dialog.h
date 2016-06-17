#pragma once 
#ifndef MESSAGEBOX_H
#define MESSAGEBOX_H

#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QGridLayout>
#include <QtGui/QMouseEvent>
#include <QtGui/QPainter>
#include <QtGui/QPixmap>
#include <QtGui/QImage>
#include <QtGui/QPen>
#include <QtGui/QFont>
#include <QtGui/QColor>
#include <QtGui/QShowEvent>
#include <QtGui/QCloseEvent>
#include <QtCore/QObject>
#include <QtCore/QEvent>
#include <QtCore/QRect>
#include <QtCore/QRectF>
#include <QtCore/Qt>
#include <QtCore/QSize>
#include <QtCore/QString>
#include <QtCore/QTimer>
#include <QtCore/QDebug>
#include "button.h"
#include "label.h"

class Dialog :public QWidget
{
	Q_OBJECT

public:
	enum Buttons {
		NoButton = 0x01,
		OK = 0x02,
		Cancel = 0x03,
		Yes = 0x04,
		No = 0x05,
		Delete = 0x06,
		Close = 0x07,
		Dicard = 0x08
	};

public:
	explicit Dialog(QWidget *parent = 0);

private:
	qreal _opacity;
	qreal _step;
	qreal _radius;
	QTimer _timer;
	bool _close;
	bool _show;

protected:
	QGridLayout _mainlayout;
	QHBoxLayout _actionlayout;
	QGridLayout _contentlayout;
	QGridLayout _titlelayout;
	qint16 _margin;

protected:
	void showEvent(QShowEvent *) Q_DECL_OVERRIDE;
	void closeEvent(QCloseEvent *e) Q_DECL_OVERRIDE;
	void paintEvent(QPaintEvent*) Q_DECL_OVERRIDE;

	public slots:
	void timercall();
};


class DialogMessage :public Dialog
{
	Q_OBJECT

public:
	explicit DialogMessage(QWidget *parent = 0);
	explicit DialogMessage(const QString &title, const QString &text, QWidget *parent = 0);
	void setTitle(const QString &title);
	void setContent(const QString &text);

private:
	TextLabel *_title;
	TextLabel *_content;
	FlatButton *_ok;
	FlatButton *_cancel;

protected:
	//void paintEvent(QPaintEvent*) Q_DECL_OVERRIDE;

	public slots:
	void onClose();
};


class DialogForm :public Dialog
{
	Q_OBJECT

public:
	explicit DialogForm(QWidget *parent = 0);
};

#endif // !MESSAGEBOX_H
