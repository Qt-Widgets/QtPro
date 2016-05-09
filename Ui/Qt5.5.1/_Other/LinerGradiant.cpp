void Widget::paintEvent(QPaintEvent *) {
	QPainter painter(this);
	painter.setRenderHint(QPainter::Antialiasing);
	painter.setPen(Qt::NoPen);


	QLinearGradient gradient;
	gradient.setStart(0, 0);
	gradient.setFinalStop(width(), 0);

	QColor grey1(150, 150, 150, 125);// starting color of the gradient - can play with the starting color and ,point since its not visible anyway

	// grey2 is ending color of the gradient - this is what will show up as the shadow. the last parameter is the alpha blend, its set
	// to 125 allowing a mix of th color and and the background, making more realistic shadow effect.
	QColor grey2(225, 225, 225, 125);

	gradient.setColorAt(0.0, grey1);
	gradient.setColorAt(0.1, grey2);

	QBrush brush(gradient);
	painter.setBrush(brush);

	// for the desired effect, no border will be drawn, and because a brush was set, the drawRoundRect will fill the box with the gradient brush.

	QPointF topLeft(10, 10);
	QPointF bottomRight(width(), height());
	QRectF rect(topLeft, bottomRight);
	painter.drawRoundRect(rect, 0.0, 0.0); // corner radius of 25 pixels

	// draw the top box, the visible one
	QBrush brush2(QColor(255, 250, 200, 255), Qt::SolidPattern);
	painter.setBrush(brush2);

	QPointF topLeft2(0, 0);
	QPointF bottomRight2(width() - 10, height() - 10);
	QRectF rect2(topLeft2, bottomRight2);
	painter.drawRoundRect(rect2, 0.0, 0.0);
}
