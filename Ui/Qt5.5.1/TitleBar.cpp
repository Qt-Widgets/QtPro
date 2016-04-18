TitleBar::TitleBar(QWidget *parent)
	: QWidget(parent)
{
	setWindowFlags(Qt::FramelessWindowHint);
}

TitleBar::~TitleBar() {}

void TitleBar::mouseMoveEvent(QMouseEvent *e) {
	if (e->buttons() && Qt::LeftButton)
	{
		move(e->globalPos() - e->pos());
		e->accept();
	}
}
