#include "PushButton.h"

PushButton::PushButton(QString text)
	:QWidget() {
		setText(text);
	}

PushButton::~PushButton() {}

void PushButton::paintEvent(QPaintEvent *e) {
	QPainter painter(this);
	QPainterPath path;
	path.addRect(QRect(0, 0, rect().width(), rect().height()));
	painter.setPen(QPen(border,1));
	painter.fillPath(path, QBrush(back));
	painter.drawPath(path);

	painter.save();

	painter.setPen(QPen(color));
	painter.setFont(QFont(_fontfamily, _pointsize));
	painter.drawText(rect(), Qt::AlignCenter, _text);
	painter.setFont(_fontfamily);
}

void PushButton::setText(QString Text) {
	_text = Text;
}

void PushButton::enterEvent(QEvent *) {
	back = "#E5F1FB";
	border = "#0078D7";
	repaint();
}

void PushButton::leaveEvent(QEvent *) {
	back = "#E1E1E1";
	border = "#ADADAD";
	repaint();
}

void PushButton::mousePressEvent(QMouseEvent *) {
	back = "#CDE4F7";
	repaint();
	emit clicked();
}

void PushButton::mouseReleaseEvent(QMouseEvent *) {
	back = "#E5F1FB";
	repaint();
}
