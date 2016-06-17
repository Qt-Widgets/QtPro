#include "label.h"

TextLabel::TextLabel(QWidget *parent) :QWidget(parent),
_opacity(0.600),
_brush("#000000"),
_pointsize(16),
_fontfamily("Roboto medium"),
_text(""),
_offset(6)
{
	_font.setFamily(_fontfamily);
	_font.setPointSize(_pointsize);
}

void TextLabel::paintEvent(QPaintEvent*) {
	QPainter p(this);
	p.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);
	p.setPen(_brush);
	p.setOpacity(_opacity);

	QPainterPath textPath;
	textPath.addText(2, height() - _offset, _font, _text);
	p.drawPath(textPath);
}

QSize TextLabel::minimumSizeHint() const {
	QFontMetrics fm(_font);
	return QSize(fm.width(_text) + _offset, fm.height() + _offset);
}

QSize TextLabel::sizeHint() const {
	return minimumSizeHint();
}

void TextLabel::setText(const QString &text) {
	_text = text;
	repaint();
}
