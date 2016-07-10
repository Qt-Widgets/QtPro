#pragma once
#include <memory>
#include <string>
#include <Windows.h>

struct HWND_deleter {
	using pointer = HWND;
	void operator()(HWND handle) const;
};

using unique_hwnd = std::unique_ptr<HWND__, HWND_deleter>;

class Window
{
public:
	Window();
	HWND handle() const { return hWnd.get(); }
	bool isClosed() const { return _closed; };

private:
	unique_hwnd hWnd;
	bool _closed = false;

	static const std::wstring& registerWindow();
	static LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);

	void setBorderLess() const;
	void show() const;
	void setShadow() const;
};
