#pragma once
#include "temp.h"
#include <QtWidgets/QApplication>

int  main(int __argc, char *argv[])
{
	QApplication a(__argc, __argv);
	Login w;
	w.show();
	return a.exec();
}
