#include <QtWidgets>

class Switcher : public QWidget
{
	Q_OBJECT

public:
	explicit Switcher(QWidget *parent = 0);
	explicit Switcher(const QColor &color, QWidget *parent = 0);

private:
	QColor _brush;
	qreal _opacity;
	qint16 _x;
	qint16 _y;

protected:
	void paintEvent(QPaintEvent*) Q_DECL_OVERRIDE;
	void mousePressEvent(QMouseEvent *e) Q_DECL_OVERRIDE;
	void mouseReleaseEvent(QMouseEvent *e) Q_DECL_OVERRIDE;

signals:
	void switched();
};
