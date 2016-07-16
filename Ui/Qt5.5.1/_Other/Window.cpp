#include "test.h"
#include <cassert>
#include <stdexcept>
#include <windowsx.h>
#include <dwmapi.h>
#pragma comment(lib, "dwmapi.lib")

LPCWSTR CLASS_NAME = L"Win32APP";
#define BORDER_WIDTH 8

enum class Style : DWORD {
	BorderLess = (WS_CAPTION | WS_VISIBLE | WS_SYSMENU | WS_THICKFRAME | WS_MINIMIZEBOX | WS_MAXIMIZEBOX)
};

const std::wstring& Window::registerWindow() {

	static const std::wstring WINDOW_CLASS = []{
		WNDCLASSEX wcex{};

		wcex.cbSize = sizeof(WNDCLASSEX);
		wcex.style = CS_HREDRAW | CS_VREDRAW;
		wcex.lpfnWndProc = WndProc;
		wcex.cbClsExtra = 0;
		wcex.cbWndExtra = 0;
		wcex.hInstance = (HINSTANCE)GetModuleHandle(nullptr);
		wcex.hIcon = LoadIcon(NULL, IDI_APPLICATION);
		wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
		wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
		wcex.lpszMenuName = NULL;
		wcex.lpszClassName = CLASS_NAME;
		wcex.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

		const HRESULT result = RegisterClassEx(&wcex);

		if (FAILED(result)) throw std::runtime_error("Faild To Register Window Class");

		return wcex.lpszClassName;
	}();
	return WINDOW_CLASS;
}

Window::Window()
	: hWnd(
	CreateWindow(
	registerWindow().c_str(),
	NULL,
	static_cast<DWORD>(Style::BorderLess),
	CW_USEDEFAULT, CW_USEDEFAULT, 480, 320,
	NULL, NULL,
	(HINSTANCE)GetModuleHandle(nullptr),
	NULL) ,&DestroyWindow)
{
	if (!hWnd) throw std::runtime_error("Failed To Create Window");

	SetWindowLongPtr(hWnd.get(), GWLP_USERDATA, reinterpret_cast<LONG_PTR>(this));

	SetWindowPos(hWnd.get(), nullptr, 0, 0, 0, 0, SWP_FRAMECHANGED | SWP_NOMOVE | SWP_NOSIZE);

	removeBorder();

	show();
}

LRESULT CALLBACK Window::WndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam) {
	if (Window* window_ptr = reinterpret_cast<Window*>(GetWindowLongPtr(hwnd, GWLP_USERDATA))) {
		auto & window = *window_ptr;

		switch (msg)
		{
		case WM_NCCALCSIZE: {
			NCCALCSIZE_PARAMS *pncsp = reinterpret_cast<NCCALCSIZE_PARAMS*>(lparam);

			pncsp->rgrc[0].left = pncsp->rgrc[0].left + BORDER_WIDTH;
			pncsp->rgrc[0].top = pncsp->rgrc[0].top + 0;
			pncsp->rgrc[0].right = pncsp->rgrc[0].right - BORDER_WIDTH;
			pncsp->rgrc[0].bottom = pncsp->rgrc[0].bottom - BORDER_WIDTH;

			return 0;
		} break;

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
			if (x >= winrect.left && x <= winrect.right 
				&& y >= winrect.top && y <= winrect.top + NC_HEIGHT) {
				return HTCAPTION;
			}
		} break;

		case WM_DESTROY:
			window._closed = true;
			PostQuitMessage(0);
			return 0;
		}
	}
	return DefWindowProc(hwnd, msg, wparam, lparam);
}

void Window::removeBorder() const {
	static const MARGINS frame = { -1, -1, -1, -1 };
	DwmExtendFrameIntoClientArea(hWnd.get(), &frame);
}

void Window::show() const {
	ShowWindow(hWnd.get(), SW_SHOW);
	MSG msg{};
	while (!isClosed()) {
		while (GetMessage(&msg, NULL, NULL, 0) > 0) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
}
