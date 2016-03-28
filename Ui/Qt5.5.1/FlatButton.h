#ifndef SAMPLE_H
#define SAMPLE_H

#include <QtWidgets>
class QWidget;
class QPainter;
class QTimer;

class FlatButton : public QWidget
{
	Q_OBJECT
public:
	FlatButton(QWidget *parent = 0);
	~FlatButton();
private:
	QColor _back = "#2FA9E2", _color="#FFFFFF";
	qreal _opacity = 0.850;
	QString _fontfamily = "Open Sans", _text = "Submit";
	qint16 _pointsize = 12;
	QTimer _timer_in, _timer_out;
protected:
	virtual void paintEvent(QPaintEvent *);
	virtual void enterEvent(QEvent *);
	virtual void leaveEvent(QEvent *);
	public slots:
	void in_timer();
	void out_timer();
};

#endif // SAMPLE_H
