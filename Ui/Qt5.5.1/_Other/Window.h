#pragma once
#include <Windows.h>
#include <QtWidgets/QApplication>


class Window
{
public:
	enum class Style : DWORD {
		BorderLess = (WS_CAPTION | WS_VISIBLE | WS_SYSMENU | WS_THICKFRAME | WS_MINIMIZEBOX | WS_MAXIMIZEBOX)
	};

	Window(QApplication *app, const int &x, const int &y, const int &width, const int &height);
	bool isClosed() const { return _closed; };
	void setMinimumSize(const int &width, const int &height);
	int minimumHeight() const{ return _height; }
	int minimumWidth() const{ return _width; }
	void setNcHeight(const int &non_client_height);
	int NcHeight() const{ return NC_HEIGHT; }

private:
	HWND _hWnd;
	QApplication *_app;
	bool _closed = false;
	int _width;
	int _height;
	int NC_HEIGHT;

	static const std::wstring& registerWindow();
	static LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);

	void show() const;
	void removeBorder() const;
};
