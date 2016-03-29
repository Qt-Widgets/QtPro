CircleButton::CircleButton(QWidget *parent)
	: QWidget(parent)
{}

CircleButton::~CircleButton() {}

void CircleButton::paintEvent(QPaintEvent *) {
	QPainter painter(this);
	painter.setRenderHint(QPainter::HighQualityAntialiasing);
	painter.setBrush(QBrush(_back));
	painter.setPen(Qt::NoPen);
	painter.drawEllipse(rect());
	painter.save();
	QPixmap img("QtPro/Resources/Icons/Arrow-1.png");
	QRect center(rect().x(), rect().y() + _margin, rect().width(), rect().height() - (2 * _margin));
	painter.drawPixmap(center , img);
}
