TitleBar::TitleBar(QWidget *parent)
	:QWidget(parent)
{
	setFixedHeight(30);
	_pixelmap = NULL;
}


TitleBar::~TitleBar() {}

void TitleBar::paintEvent(QPaintEvent *) {
	QPainter painter(this);
	painter.setBrush(_background);
	painter.setPen(Qt::NoPen);
	painter.drawRect(0, 0, width(), height());
}
