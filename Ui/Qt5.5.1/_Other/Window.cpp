#include "test.h"
#include <cassert>
#include <stdexcept>
#include <windowsx.h>
#include <dwmapi.h>
#pragma comment(lib, "dwmapi.lib")

LPCWSTR CLASS_NAME = L"Win32APP";
#define  BORDER_WIDTH  5

enum Style : DWORD {
	BorderLess = (WS_POPUP | WS_THICKFRAME | WS_CAPTION | WS_SYSMENU | WS_MAXIMIZEBOX | WS_MINIMIZEBOX)
};

void HWND_deleter::operator()(HWND handle) const {
	assert(DestroyWindow(handle));
}



const std::wstring& Window::registerWindow() {

	static const std::wstring WINDOW_CLASS = []{
		WNDCLASSEX wcx{};
		wcx.cbSize = sizeof(wcx);
		wcx.style = CS_HREDRAW | CS_VREDRAW;
		wcx.hInstance = (HINSTANCE)GetModuleHandle(nullptr);
		wcx.lpfnWndProc = &Window::WndProc;
		wcx.lpszClassName = CLASS_NAME;
		wcx.hbrBackground = reinterpret_cast<HBRUSH>(COLOR_WINDOW + 1);
		wcx.hCursor = LoadCursor((HINSTANCE)GetModuleHandle(nullptr), IDC_ARROW);

		const HRESULT result = RegisterClassEx(&wcx);
		
		if (FAILED(result)) throw std::runtime_error("Faild To Register Window Class");

		return wcx.lpszClassName;
	}();
	return WINDOW_CLASS;
}

Window::Window()
	: hWnd(CreateWindow(registerWindow().c_str(),
	L"Borderless Window",
	static_cast<DWORD>(Style::BorderLess),
	0, 0, 480, 320,
	nullptr, nullptr,
	(HINSTANCE)GetModuleHandle(nullptr),
	nullptr)) 
{
	if (!hWnd) throw std::runtime_error("Failed To Create Window");

	SetWindowLongPtr(hWnd.get(), GWLP_USERDATA, reinterpret_cast<LONG_PTR>(this));

	setBorderLess();
	setShadow();
	show();
}

LRESULT CALLBACK Window::WndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam) {
	if (Window* window_ptr = reinterpret_cast<Window*>(GetWindowLongPtr(hwnd, GWLP_USERDATA))) {
		auto & window = *window_ptr;

		switch (msg) 
		{
		case WM_NCCALCSIZE: 
			return 0;
			break;

		case WM_NCACTIVATE:  
			return 1;
			break;

		case WM_NCHITTEST: {
			RECT winrect;
			GetWindowRect(hwnd, &winrect);
			long x = GET_X_LPARAM(lparam);
			long y = GET_Y_LPARAM(lparam);

			// BOTTOM LEFT
			if (x >= winrect.left && x < winrect.left + BORDER_WIDTH &&
				y < winrect.bottom && y >= winrect.bottom - BORDER_WIDTH) {
				return HTBOTTOMLEFT;
			}
			// BOTTOM RIGHT
			if (x < winrect.right && x >= winrect.right - BORDER_WIDTH &&
				y < winrect.bottom && y >= winrect.bottom - BORDER_WIDTH) {
				return HTBOTTOMRIGHT;
			}
			// TOP LEFT
			if (x >= winrect.left && x < winrect.left + BORDER_WIDTH &&
				y >= winrect.top && y < winrect.top + BORDER_WIDTH) {
				return HTTOPLEFT;
			}
			// TOP RIGHT
			if (x < winrect.right && x >= winrect.right - BORDER_WIDTH &&
				y >= winrect.top && y < winrect.top + BORDER_WIDTH) {
				return HTTOPRIGHT;
			}
			// LEFT
			if (x >= winrect.left && x < winrect.left + BORDER_WIDTH) {
				return HTLEFT;
			}
			// RIGHT
			if (x < winrect.right && x >= winrect.right - BORDER_WIDTH) {
				return HTRIGHT;
			}
			// BOTTOM
			if (y < winrect.bottom && y >= winrect.bottom - BORDER_WIDTH) {
				return HTBOTTOM;
			}
			// TOP
			if (y >= winrect.top && y < winrect.top + BORDER_WIDTH) {
				return HTTOP;
			}
			return HTCAPTION;
		} break;

		case WM_CLOSE: 
			DestroyWindow(hwnd);
			window._closed = true;
			return 0;
			break;

		case WM_DESTROY:
			PostQuitMessage(0);
			return 0;
		}
		}
	return DefWindowProc(hwnd, msg, wparam, lparam);
	}

void Window::setBorderLess() const {
	SetWindowLongPtr(hWnd.get(), GWL_STYLE, static_cast<LONG>(Style::BorderLess));
	SetWindowPos(hWnd.get(), nullptr, 0, 0, 0, 0, SWP_FRAMECHANGED | SWP_NOMOVE | SWP_NOSIZE);
	setShadow();
}

void Window::setShadow() const {
	static const MARGINS shadow_state = { 1, 1, 1, 1 };
	DwmExtendFrameIntoClientArea(hWnd.get(), &shadow_state);
}

void Window::show() const {
	ShowWindow(hWnd.get(), SW_SHOW);
}
