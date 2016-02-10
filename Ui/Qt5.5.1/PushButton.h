#ifndef PUSHBUTTON_H
#define PUSHBUTTON_H

#include <QtWidgets>
class QPainter;
class QPainterPath;


class PushButton : public QWidget
{
	Q_OBJECT
	
public:
	explicit PushButton(QWidget *parent = 0);
	~PushButton();
	void setText(QString Text);
	QString text();
protected:
	void paintEvent(QPaintEvent *);
	void enterEvent(QEvent *);
	void leaveEvent(QEvent *);
	void mousePressEvent(QMouseEvent *e);
	void mouseReleaseEvent(QMouseEvent *);
private:
	QString _text = "PushButton", _fontfamily = "Calibri";
	QColor border = "#ADADAD", back = "#E1E1E1", color = "#000000";
	int _pointsize = 12;
signals:
	void clicked();
	public slots:
};

#endif // PUSHBUTTON_H
