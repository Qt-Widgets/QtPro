#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QGridLayout>
#include <QtGui/QMouseEvent>
#include <QtGui/QPainter>
#include <QtGui/QPixmap>
#include <QtGui/QImage>
#include <QtGui/QPen>
#include <QtGui/QFont>
#include <QtGui/QColor>
#include <QtGui/QShowEvent>
#include <QtGui/QCloseEvent>
#include <QtCore/QObject>
#include <QtCore/QEvent>
#include <QtCore/QRect>
#include <QtCore/QRectF>
#include <QtCore/Qt>
#include <QtCore/QSize>
#include <QtCore/QString>
#include <QtCore/QTimer>
#include <QtCore/QDebug>

class Dialog :public QWidget
{
	Q_OBJECT

public:
	enum Buttons {
		NoButton = 0x01,
		OK = 0x02,
		Cancel = 0x03,
		Yes = 0x04,
		No = 0x05,
		Delete = 0x06,
		Close = 0x07,
		Dicard = 0x08
	};

public:
	explicit Dialog(QWidget *parent = 0);
	explicit Dialog(const QString &title, const QString &text,
		const Buttons &buttons = Buttons::NoButton, QWidget *parent = 0);

private:
	qreal _opacity;
	QTimer _timer;
	bool _close;
	bool _show;

protected:
	QGridLayout _mainlayout;
	QGridLayout _actionlayout;
	QGridLayout _contentlayout;
	QGridLayout _titlelayout;

protected:
	void showEvent(QShowEvent *) Q_DECL_OVERRIDE;
	void closeEvent(QCloseEvent *e) Q_DECL_OVERRIDE;
	Dialog::Buttons clickedButton() {};

	public slots:
	void timercall();
};


class DialogMessage :public QDialog
{
	Q_OBJECT
public:
	explicit DialogMessage(QWidget *parent = 0);
	explicit DialogMessage(const QString &title, const QString &text,
		const Dialog::Buttons &buttons = Dialog::Buttons::NoButton, QWidget *parent = 0);
	void setTitle(const QString &title);
	void setContent(const QString &text);
};


class DialogForm :public Dialog
{
	Q_OBJECT

public:
	explicit DialogForm(QWidget *parent = 0);
};
