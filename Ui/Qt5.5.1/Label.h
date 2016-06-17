#pragma once 
#ifndef LABEL_H
#define LABEL_H

#include <QtWidgets>

class TextLabel :public QWidget
{
	Q_OBJECT

public:
	explicit TextLabel(QWidget *parent = 0);
	//explicit TextLabel(const QString &text, QWidget *parent);
	void setText(const QString &text);

private:
	QString _text;
	qreal _opacity;
	QColor _brush;
	QFont _font;
	QString _fontfamily;
	qint16 _pointsize;
	qint16 _offset;

protected:
	void paintEvent(QPaintEvent*) Q_DECL_OVERRIDE;
	QSize minimumSizeHint() const  Q_DECL_OVERRIDE;
	QSize sizeHint() const Q_DECL_OVERRIDE;
};

#endif // !LABEL_H
