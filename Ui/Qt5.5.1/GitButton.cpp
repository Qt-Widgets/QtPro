#ifndef GITBUTTON_H
#define GITBUTTON_H
#include <QWidget>
#include <QTimer>
#include <QPainter>

class GitButton : public QWidget {
  Q_OBJECT
 public:
  explicit GitButton(QWidget* parent = 0) : QWidget(parent) {
    setMouseTracking(true);
    // setup timer
    connect(&timer, SIGNAL(timeout()), this, SLOT(timercall()));
  }

 protected:
  virtual void enterEvent(QEvent*) {
    // start the timer
    Hover = QColor(0, 0, 255);
    Step = 0;
    timer.start(5);
  }
  virtual void leaveEvent(QEvent*) {
    // reset state
    ColorEffect = QRect(-1, -1, -1, -1);
    Step = 0;
    timer.stop();
    repaint();

  }
  virtual void paintEvent(QPaintEvent*) {

    QPainter p ( this );
    p.setRenderHint ( QPainter::Antialiasing );
    p.setBrush(QBrush(QColor(255, 255, 255)));
    p.drawEllipse(rect());
    // for the expanding
    p.setBrush(QBrush(Hover));
    p.drawEllipse(ColorEffect);


  }
 public slots:
// timer calls this function. each time we make circle bigger
  void timercall() {
    int w = rect().width() / 2;
    int h = rect().height() / 2;
    if (Step >= h - 5 ) {
      ColorEffect = QRect(-1, -1, -1, -1);
      timer.stop();
    }
    Step++;
    ColorEffect.setCoords(w - Step, h - Step, w + Step, h + Step);
    repaint();

  }
 private:
  QColor Hover;
  QRect ColorEffect;
  QTimer timer;
  int Step;
};

#endif // GITBUTTON_H
