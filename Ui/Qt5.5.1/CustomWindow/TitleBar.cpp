TitleBar::TitleBar(QWidget *parent)
	:QWidget(parent)
{
	_l->addStretch(10);
	_l->addWidget(_minimize);
	_l->addWidget(_maxmimize);
	_l->addWidget(_close);
	_l->setMargin(10);
	_l->setSpacing((_width / 2) - 2);
	setLayout(_l);
}

TitleBar::~TitleBar() {}

void TitleBar::paintEvent(QPaintEvent *) {
	QPainter painter(this);
	painter.setBrush(_background);
	painter.setPen(Qt::NoPen);
	painter.drawRect(0, 0, width(), height());
}

void TitleBar::setText(const QString &_text) {
	delete _l;
	_hastext = 1;
	_Title->setText(_text);
	_Title->setMinimumHeight((_width / 2) + 3);
	_Title->setStyleSheet("color:white;");
	_Title->setFont(QFont("San Francisco Display Thin", (_width / 2) - 3));

	_primary->addWidget(_Title);
	_primary->addStretch(10);
	_primary->addWidget(_minimize);
	_primary->addWidget(_maxmimize);
	_primary->addWidget(_close);
	_primary->setMargin(10);
	_primary->setSpacing((_width / 2) - 2);
	setLayout(_primary);
}

void TitleBar::setIcon(const QPixmap &_pixelmap) {
	if (!_hastext)
	{
		delete _l;
	}
	delete _primary;
	_window_icon->setPixmap(_pixelmap);
	_window_icon->setFixedSize((_width / 2) + 3, (_width / 2) + 3);
	_window_icon->setScaledContents(true);

	_secoundry->addWidget(_window_icon);
	_secoundry->addWidget(_Title);
	_secoundry->addStretch(10);
	_secoundry->addWidget(_minimize);
	_secoundry->addWidget(_maxmimize);
	_secoundry->addWidget(_close);
	_secoundry->setMargin(10);
	_secoundry->setSpacing((_width / 2) - 2);
	setLayout(_secoundry);
}

