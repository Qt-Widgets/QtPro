#pragma once

#ifndef FLATBUTTON_H
#define FLATBUTTON_H

#include <QtWidgets>

class FlatButton : public QWidget
{
	Q_OBJECT

public:
	FlatButton(QWidget *parent = 0);
	~FlatButton();
	void setColor(const QColor &_brush);
	void setText(const QString &text);
	void setDisable(bool disable);


private:
	QWidget *_parent = new QWidget();
	QColor _back = "#2FA9E2", _color = "#FFFFFF", _back2 = "#000000";
	qreal _opacity = 0.999, _opacity2 = 0.000;
	qint16 _alpha = 0;
	QString _fontfamily = "Roboto Condensed", _text = "Log In";
	qint16 _pointsize = 14, _margin = 0, _margin0 = 0;
	QTimer _timer;
	enum State { hover, over, pressed, realese };
	State _state;
	bool _startup = true;
	bool _hastext = false;
	bool _effect = false;
	bool _disabled = false;
	QFont _font;

protected:
	virtual void paintEvent(QPaintEvent *);
	virtual void enterEvent(QEvent *);
	virtual void leaveEvent(QEvent *);
	virtual void mousePressEvent(QMouseEvent *e);
	virtual void mouseReleaseEvent(QMouseEvent *e);
	QSize minimumSizeHint() const Q_DECL_OVERRIDE;
	QSize sizeHint() const Q_DECL_OVERRIDE;

	public slots:
	void timercall();

signals:
	void clicked();
};


class Window : public QDialog 
{
	Q_OBJECT

public:
	Window() {
		_opacity = 0.000;
		_state = Show;
		connect(&_timer, SIGNAL(timeout()), this, SLOT(timercall()));
	}

private:
	qreal _opacity;
	QTimer _timer;
	enum State {
		Close,
		Show,
		None
	};
	State _state;
	bool _close = false;

protected:
	virtual void showEvent(QShowEvent *) {
		if (_state == Show) {
			_timer.start(1);
		}
		setStyleSheet("background:#FFFFFF;");
	}
	virtual void closeEvent(QCloseEvent *e) {
		_state = Close;
		if (_close) {
			e->accept();
		} else {
			e->ignore();
		}
		_timer.start(2);
	}

	public slots:
		void timercall() {
			switch (_state)
			{
			case Window::Close:
			{
				if (_opacity > 0.000) {
					setWindowOpacity(_opacity);
					_opacity -= 0.013;
				} else {
					_timer.stop();
					_state = None;
					_close = true;
					close();
				}
			} break;
			case Window::Show:
			{
				if (_opacity < 1.000) {
					_opacity += 0.009;
					setWindowOpacity(_opacity);
				} else {
					_timer.stop();
				}
			} break;
			case Window::None: break;
			}
	}
};

class Button :public QWidget
{
	Q_OBJECT

public:
	Button();
	~Button();
	void setText(const QString &text);
	void setDisable(bool _disable);
	bool isDisable() const;
	QString text() const;

private:
	enum State {
		None = 0x00,
		Hover = 0x02,
		Over = 0x04,
		Disabe = 0x08
	};

	bool _disabled;
	State _state;
	QString _text;

protected:
	QSize sizeHint() const Q_DECL_OVERRIDE;
	QSize minimumSizeHint() const Q_DECL_OVERRIDE;
	void mouseReleaseEvent(QMouseEvent *e) Q_DECL_OVERRIDE;

	signals:
	void clicked();
};

class Shadow :public QWidget
{
	Q_OBJECT

public:
	Shadow();

private:
	QColor _brush;

protected:
	void paintEvent(QPaintEvent *) Q_DECL_OVERRIDE;
};

#endif // FLATBUTTON_H
