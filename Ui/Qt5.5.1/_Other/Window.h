#pragma once
#include "windows.h"
#include <QtWidgets/QApplication>

class Window
{
public:
	enum class Style : DWORD {
		BorderLess = (WS_CAPTION | WS_VISIBLE | WS_SYSMENU | WS_THICKFRAME | WS_MINIMIZEBOX | WS_MAXIMIZEBOX)
	};

	Window(QApplication *app, const int &x, const int &y, const int &width, const int &height);

	bool isClosed() const { return _closed; }
	int minimumWidth() const { return _mWidth; }
	int minimumHeight() const { return _mHeight; }
	int NcHeight() const { return NC_HEIGHT; }

	void setMinimumSize(const int &mWidth, const int &mHeight);
	void setNcHeight(const int &non_client_height);

	void show();
	void removeBorder();

private:
	HWND _hwnd;
	QApplication *_app = NULL;
	bool _closed = false;
	int _mWidth;
	int _mHeight;
	int NC_HEIGHT;

private:
	static const std::wstring& registerWindow();
	static LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);
};
