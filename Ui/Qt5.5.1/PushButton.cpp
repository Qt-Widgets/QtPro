#include "PushButton.h"

PushButton::PushButton(const QString text, QWidget *parent)
	:QWidget(parent) {
	setText(text);
}

PushButton::~PushButton() {}

void PushButton::paintEvent(QPaintEvent *e) {
	QPainter painter(this);
	painter.setPen(QPen(_border, _border_weight));
	painter.setRenderHint(QPainter::Antialiasing);
	painter.drawRect(rect());
	QRect Rectangle = QRect(rect().x() + _border_weight/2, rect().y() + _border_weight/2,
		                    rect().width() - _border_weight, rect().height() - _border_weight);
	painter.fillRect(Rectangle, _back);
	painter.save();
	painter.setPen(QPen(_color));
	painter.setFont(QFont(_fontfamily, _pointsize));
	painter.drawText(rect(), Qt::AlignCenter, _text);
}

void PushButton::setText(const QString Text) {
	_text = Text;
}

void PushButton::enterEvent(QEvent * event) {
	switch (_state)
	{
	case PushButton::Disable:
		break;
	case PushButton::Default:
		break;
	case PushButton::Normal:
	{
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
	break;
	default:
		break;
	}
}

void PushButton::leaveEvent(QEvent *) {
	switch (_state)
	{
	case PushButton::Disable:
		break;
	case PushButton::Default:
		break;
	case PushButton::Normal:
	{
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
	break;
	default:
		break;
	}
}

void PushButton::mousePressEvent(QMouseEvent *) {
	switch (_state)
	{
	case PushButton::Disable:
		break;
	case PushButton::Default:
		break;
	case PushButton::Normal:
	{
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
	}
	break;
	default:
		break;
	}
	
	emit clicked();
}

void PushButton::mouseReleaseEvent(QMouseEvent *) {
	switch (_state)
	{
	case PushButton::Disable:
		break;
	case PushButton::Default:
		break;
	case PushButton::Normal:
	{
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
	break;
	default:
		break;
	}
}

void PushButton::set_back_Color(const QColor color) {
	_back = color;
	//repaint();
	update();
}

void PushButton::set_border_Color(const QColor color) {
	_border = color;
	//repaint();
	update();
}

QColor PushButton::back_color() const {
	return _back;
}

QColor PushButton::border_color() const {
	return _border;
}

void PushButton::setDisable(bool) {
	if (true)
	{
		_back = "#CCCCCC";
		_border = "#BFBFBF";
		_color = "#5f5f5f";
		_state = Disable;
		update();
	}
}

void PushButton::setDefault(bool) {
	if (true)
	{
		_border_weight = 2;
		_border = "#0078D7";
		_state = Default;
		update();
	}
}

QSize PushButton::minimumSizeHint() const {
	return QSize(75, 20);
}

QSize PushButton::sizeHint() const {
	return QSize(130, 40);
}
