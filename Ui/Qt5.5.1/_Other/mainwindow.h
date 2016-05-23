#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTabBar>
#include <QTabWidget>

class MyTabWidget : public QTabWidget
{
    Q_OBJECT
public:
    MyTabWidget(QWidget *p) : QTabWidget(p) { }
    int getTabAt(QPoint p) { return tabBar()->tabAt(p); }
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

    MyTabWidget *tabWidget;

    bool hitTestNCA(MSG *msg, long *result);

public:
    MainWindow(QWidget *parent = 0);

protected:
    bool winEvent(MSG *msg, long *result);
    bool nativeEvent(const QByteArray &eventType, void *message, long *result);
};

#endif // MAINWINDOW_H
