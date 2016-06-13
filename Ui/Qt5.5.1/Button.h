#pragma once

#include <QtWidgets>

class Button :public QWidget
{
	Q_OBJECT

public:
	Button();
	~Button();
	void setText(const QString &text);
	void setDisable(bool _disable);
	bool isDisable() const;

private:
	enum State {
		None = 0x00,
		Hover = 0x02,
		Over = 0x04,
		Disabe = 0x08
	};

	bool _disable;
	State _state;

protected:
	QSize sizeHint() const Q_DECL_OVERRIDE;
	QSize minimumSizeHint() const Q_DECL_OVERRIDE;
	void mouseReleaseEvent(QMouseEvent *e) Q_DECL_OVERRIDE;
};

#endif // BUTTON_H
