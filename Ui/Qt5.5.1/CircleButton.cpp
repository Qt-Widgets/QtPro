CircleButton::CircleButton(QWidget *parent)
	: QWidget(parent)
{}

CircleButton::~CircleButton() {}

void CircleButton::paintEvent(QPaintEvent *) {
	QPainter painter(this);
	painter.setRenderHint(QPainter::Antialiasing);
	painter.setBrush(QBrush(_back));
	painter.setPen(QPen(_back, 2));
	painter.drawEllipse(QRect(rect().x() + (_blank / 2), rect().y() + (_blank / 2), rect().width() - _blank, rect().height() - _blank));
	//QPixmap img(_image);
	//QRect center(rect().x() - _margin / 2, rect().y() + _margin, rect().width(), rect().height() - (2 * _margin));
	//painter.drawPixmap(center , img);
}

