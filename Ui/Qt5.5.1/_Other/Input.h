#ifndef INPUT_H
#define INPUT_H

#include <QtWidgets>
#include <QString>

QT_BEGIN_NAMESPACE

class  Q_WIDGETS_EXPORT Input : public QWidget
{
	Q_OBJECT

	Q_PROPERTY(QString text READ text WRITE setText RESET clearText NOTIFY textChanged);
	Q_PROPERTY(QString placeHolderText READ placeHolderText WRITE setPlaceHolderText RESET clearPlaceHolderText);
	Q_PROPERTY(EchoMode echoMode READ echoMode WRITE setEchoMode);
	Q_PROPERTY(Qt::Alignment alignment READ alignment WRITE setAlignment);
	Q_PROPERTY(State state READ state WRITE setState RESET clearState);

public:
	explicit Input(QWidget *parent = Q_NULLPTR);
	explicit Input(const QString &, QWidget *parent = Q_NULLPTR);
	~Input();
	
	QString text() const;
	void setText(const QString &);
	void clearText();

	QString placeHolderText() const;
	void setPlaceHolderText(const QString &);
	void clearPlaceHolderText();

	Qt::Alignment alignment() const;
	void setAlignment(Qt::Alignment flag);

	enum State {
		None = 0x00,
		Hover = 0x02,
		Over = 0x04,
		FocusIn = 0x08,
		FocusOut = 0x0B
	};
	Q_ENUM(State);

	State state() const;
	void setState(State &);

	enum EchoMode {
		Normal = 0x02,
		Password = 0x04
	};
	Q_ENUM(EchoMode);

	EchoMode echoMode() const;
	void setEchoMode(EchoMode);

#ifndef QT_NO_CLIPBOARD
	void copy() const;
	void cut();
	void paste();
#endif

private:
	QString _text;
	QString _placeHolderText;
	Qt::Alignment _alignment;

protected:
	void mousePressEvent(QMouseEvent *) Q_DECL_OVERRIDE;
	void mouseReleaseEvent(QMouseEvent *e) Q_DECL_OVERRIDE;
	void focusInEvent(QFocusEvent *e) Q_DECL_OVERRIDE;
	void focusOutEvent(QFocusEvent *e) Q_DECL_OVERRIDE;
	void keyPressEvent(QKeyEvent *e) Q_DECL_OVERRIDE;
	QSize minimumSizeHint() const Q_DECL_OVERRIDE;
	QSize sizeHint() const Q_DECL_OVERRIDE;

Q_SIGNALS:
	void textChanged(const QString &);
};

QT_END_NAMESPACE

#endif // !INPUT_H
