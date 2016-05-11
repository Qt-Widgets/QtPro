QPainter painter(this);
	painter.setRenderHint(QPainter::Antialiasing);
	painter.setPen(Qt::NoPen);


	QLinearGradient gradient;
	QPointF right0(width() - 7, height() / 2);
	QPointF right1(width(), height() / 2);

	gradient.setStart(right0);
	gradient.setFinalStop(right1);

	gradient.setSpread(QGradient::ReflectSpread);

	QColor grey1(151, 151, 151, 32);// #D8D8D8 
	QColor grey2(254, 254, 254, 0); // #FEFEFE

	gradient.setColorAt(0.000, grey1);
	gradient.setColorAt(0.999, grey2);

	painter.setBrush(QBrush(gradient));


	QPointF topLeft(0, 0);
	QPointF bottomRight(width(), height());
	QRectF rect(topLeft, bottomRight);
	painter.drawRoundRect(rect, 0.0, 0.0);

	QBrush brush2(QColor("#FFFFFF"), Qt::SolidPattern);
	painter.setBrush(brush2);

	QPointF topLeft2(0, 0);
	QPointF bottomRight2(width()-7, height() );
	QRectF rect2(topLeft2, bottomRight2);
	painter.drawRoundRect(rect2, 0.0, 0.0);
