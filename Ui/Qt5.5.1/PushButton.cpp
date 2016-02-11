#include "PushButton.h"

PushButton::PushButton(QString text,QWidget *parent)
	:QWidget(parent) {
	setText(text);
}

PushButton::~PushButton() {}

void PushButton::paintEvent(QPaintEvent *e) {
	QPainter painter(this);
	QPainterPath path;
	path.addRect(QRect(0, 0, rect().width(), rect().height()));
	painter.setPen(QPen(_border,1));
	painter.fillPath(path, QBrush(_back));
	painter.drawPath(path);

	painter.save();

	painter.setPen(QPen(_color));
	painter.setFont(QFont(_fontfamily, _pointsize));
	painter.drawText(rect(), Qt::AlignCenter, _text);
	painter.setFont(_fontfamily);
}

void PushButton::setText(QString Text) {
	_text = Text;
}

void PushButton::enterEvent(QEvent *) {
	
	QParallelAnimationGroup *group_animation = new QParallelAnimationGroup;
	//border
	QPropertyAnimation *border_animation = new QPropertyAnimation(this,"border_color");
	border_animation->setDuration(200);
	border_animation->setStartValue(_border);
	_border = "#0078D7";
	border_animation->setEndValue(_border);
	//background
	QPropertyAnimation *back_animation = new QPropertyAnimation(this,"back_color");
	back_animation->setDuration(200);
	back_animation->setStartValue(_back);
	_back = "#E5F1FB";
	back_animation->setEndValue(_back);

	group_animation->addAnimation(back_animation);
	group_animation->addAnimation(border_animation);
	group_animation->start();
}

void PushButton::leaveEvent(QEvent *) {

	QParallelAnimationGroup *group_animation = new QParallelAnimationGroup;
	//border
	QPropertyAnimation *border_animation = new QPropertyAnimation(this, "border_color");
	border_animation->setDuration(200);
	border_animation->setStartValue(_border);
	_border = "#ADADAD";
	border_animation->setEndValue(_border);
	//background
	QPropertyAnimation *back_animation = new QPropertyAnimation(this, "back_color");
	back_animation->setDuration(200);
	back_animation->setStartValue(_back);
	_back = "#E1E1E1";
	back_animation->setEndValue(_back);

	group_animation->addAnimation(back_animation);
	group_animation->addAnimation(border_animation);
	group_animation->start();
	
}

void PushButton::mousePressEvent(QMouseEvent *) {

	QParallelAnimationGroup *group_animation = new QParallelAnimationGroup;
	//border
	QPropertyAnimation *border_animation = new QPropertyAnimation(this, "border_color");
	border_animation->setDuration(200);
	border_animation->setStartValue(_border);
	_border = "#00569D";
	border_animation->setEndValue(_border);
	//background
	QPropertyAnimation *back_animation = new QPropertyAnimation(this, "back_color");
	back_animation->setDuration(200);
	back_animation->setStartValue(_back);
	_back = "#CDE4F7";
	back_animation->setEndValue(_back);

	group_animation->addAnimation(back_animation);
	group_animation->addAnimation(border_animation);
	group_animation->start();

	emit clicked();
}

void PushButton::mouseReleaseEvent(QMouseEvent *) {

	QParallelAnimationGroup *group_animation = new QParallelAnimationGroup;
	//border
	QPropertyAnimation *border_animation = new QPropertyAnimation(this, "border_color");
	border_animation->setDuration(200);
	border_animation->setStartValue(_border);
	_border = "#0078D7";
	border_animation->setEndValue(_border);
	//background
	QPropertyAnimation *back_animation = new QPropertyAnimation(this, "back_color");
	back_animation->setDuration(200);
	back_animation->setStartValue(_back);
	_back = "#E5F1FB";
	back_animation->setEndValue(_back);

	group_animation->addAnimation(back_animation);
	group_animation->addAnimation(border_animation);
	group_animation->start();
}

void PushButton::set_back_Color(QColor color) {
	_back = color;
	repaint();
}

void PushButton::set_border_Color(QColor color) {
	_border = color;
	repaint();
}

QColor PushButton::back_color() {
	return _back;
}

QColor PushButton::border_color() {
	return _border;
}
