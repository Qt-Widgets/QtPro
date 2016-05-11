	QPainter painter(this);
	painter.setPen(Qt::NoPen);

	int margin = 10;
	QColor start(151, 151, 151, 32);// start(151, 151, 151, 32)  #D8D8D8
	QColor end(255, 255, 255, 0);
	QPointF right0(width() - margin, height() / 2);
	QPointF right1(width(), height() / 2);
	QPointF left0(margin, height() / 2);
	QPointF left1(0, height() / 2);
	QPointF top0(width() / 2, margin);
	QPointF top1(width() / 2, 0);
	QPointF bottom0(width() / 2, height() - margin);
	QPointF bottom1(width() / 2, height());
	QPointF bottomright0(width() - margin, height() - margin);
	QPointF bottomright1(width(), height());
	QPointF bottomleft0(margin, height() - margin);
	QPointF bottomleft1(0, height());
	QPointF topLeft0(margin, margin);
	QPointF topleft1(0, 0);
	QPointF topright0(width() - margin, margin);
	QPointF topright1(width(), 0);

	QLinearGradient gradient;
	gradient.setColorAt(0.0, start);
	gradient.setColorAt(1.0, end);
	// right
	gradient.setStart(right0);
	gradient.setFinalStop(right1);
	painter.setBrush(QBrush(gradient));
	painter.drawRoundRect(QRectF(QPointF(margin, margin), QPointF(width(), height()-margin)), 0.0, 0.0);
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
	// bottom right
	gradient.setStart(bottomright0);
	gradient.setFinalStop(bottomright1);
	gradient.setColorAt(0.6, end);
	painter.setBrush(QBrush(gradient));
	painter.drawRoundRect(QRectF(bottomright0, bottomright1), 0.0, 0.0);
	// bottom left
	gradient.setStart(bottomleft0);
	gradient.setFinalStop(bottomleft1);
	gradient.setColorAt(0.6, end);
	painter.setBrush(QBrush(gradient));
	painter.drawRoundRect(QRectF(bottomleft0, bottomleft1), 0.0, 0.0);
	// top left
	gradient.setStart(topLeft0);
	gradient.setFinalStop(topleft1);
	painter.setBrush(QBrush(gradient));
	gradient.setColorAt(0.6, end);
	painter.drawRoundRect(QRectF(topLeft0, topleft1), 0.0, 0.0);
	// top right
	gradient.setStart(topright0);
	gradient.setFinalStop(topright1);
	painter.setBrush(QBrush(gradient));
	gradient.setColorAt(0.6, end);
	painter.drawRoundRect(QRectF(topright0, topright1), 0.0, 0.0);
	// actual widget
	painter.setBrush(QBrush("#FFFFFF"));
	painter.drawRoundRect(QRectF(QPointF(margin, margin), QPointF(width() - margin, height() - margin)), 0.0, 0.0);
