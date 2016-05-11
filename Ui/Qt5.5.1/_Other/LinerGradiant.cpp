QPainter painter(this);
	painter.setRenderHint(QPainter::Antialiasing);
	painter.setPen(Qt::NoPen);
	int margin = 9;
	QColor start(151, 151, 151, 32);// #D8D8D8 
	QColor end(254, 254, 254, 0); // #FEFEFE
	QPointF right0(width() - margin, height() / 2);
	QPointF right1(width(), height() / 2);
	QPointF left0(margin, height() / 2);
	QPointF left1(0, height() / 2);
	QPointF top0(width() / 2, margin);
	QPointF top1(width() / 2, 0);
	QPointF bottom0(width() / 2, height() - margin);
	QPointF bottom1(width() / 2, height());

	QLinearGradient gradient;
	gradient.setColorAt(0.000, start);
	gradient.setColorAt(0.999, end);
	// right
	gradient.setStart(right0);
	gradient.setFinalStop(right1);
	painter.setBrush(QBrush(gradient));
	painter.drawRoundRect(QRectF(QPointF(margin, margin), QPointF(width(), height()-margin)), 0.0, 0.0);
	painter.save();
	// left
	gradient.setStart(left0);
	gradient.setFinalStop(left1);
	painter.setBrush(QBrush(gradient));
	painter.drawRoundRect(QRectF(QPointF(width() - margin, margin), QPointF(0, height()-margin)), 0.0, 0.0);
	// top
	gradient.setStart(top0);
	gradient.setFinalStop(top1);
	painter.setBrush(QBrush(gradient));
	painter.drawRoundRect(QRectF(QPointF(width() - margin, 0), QPointF(margin, height()-margin)), 0.0, 0.0);
	// bottom 
	gradient.setStart(bottom0);
	gradient.setFinalStop(bottom1);
	painter.setBrush(QBrush(gradient));
	painter.drawRoundRect(QRectF(QPointF(margin, margin), QPointF(width() - margin, height() )), 0.0, 0.0);
	// Draw actual widget
	painter.setBrush(QBrush("#FFFFFF", Qt::SolidPattern));
	painter.drawRoundRect(QRectF(QPointF(margin, margin), QPointF(width() - margin, height() - margin)), 0.0, 0.0);
