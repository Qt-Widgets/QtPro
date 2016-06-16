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
