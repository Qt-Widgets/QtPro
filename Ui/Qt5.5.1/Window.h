#pragma once
#ifndef WINDOW_H
#define WINDOW_H

#include <QtWidgets>
class QWidget;

class Window : public QWidget {
	Q_OBJECT

public:
	explicit Window();
	~Window();
};

#endif // !WINDOW_H
