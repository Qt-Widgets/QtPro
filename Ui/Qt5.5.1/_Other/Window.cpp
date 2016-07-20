#include "window.h"
#include <windowsx.h>
#include <dwmapi.h>
#pragma comment(lib, "dwmapi.lib")
#pragma comment(lib,"user32.lib")
#pragma warning(disable:4715)

LPCWSTR CLASS_NAME = L"Win32APP";
#define BORDER_WIDTH 8

Window::Window(QApplication *app, const int &x, const int &y, const int &width, const int &height) {
	_hwnd =
		CreateWindow(
		registerWindow().c_str(),
		NULL,
		static_cast<DWORD>(Style::BorderLess),
		x, y, width, height,
		0, 0,
		(HINSTANCE)GetModuleHandle(0),
		NULL);
	if (!_hwnd) throw std::runtime_error("Failed To Create Window");

	SetWindowLongPtr(_hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(this));

	SetWindowPos(_hwnd, NULL, 0, 0, 0, 0, SWP_FRAMECHANGED | SWP_NOMOVE | SWP_NOSIZE);

	_app = app;

	setNcHeight(36);
	removeBorder();
	show();
}

void Window::setMinimumSize(const int &mWidth, const int &mHeight) {
	_mWidth = mWidth;
	_mHeight = mHeight;
}

void Window::setNcHeight(const int &non_client_height) {
	NC_HEIGHT = non_client_height;
}

void Window::show() {
	ShowWindow(_hwnd, SW_SHOW);
}

void Window::removeBorder() {
	static const MARGINS frame = { -1, -1, -1, -1 };
	DwmExtendFrameIntoClientArea(_hwnd, &frame);
}

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

LRESULT CALLBACK Window::WndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam) {
	Window *window_ptr = reinterpret_cast<Window*>(GetWindowLongPtr(hwnd, GWLP_USERDATA));
	if (!window_ptr) return DefWindowProc(hwnd, msg, wparam, lparam);

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
			&& y >= winrect.top && y <= winrect.top + window.NC_HEIGHT) {
			return HTCAPTION;
		}
	} break;

	case WM_GETMINMAXINFO: {
		MINMAXINFO* minMaxInfo = (MINMAXINFO*)lparam;
		minMaxInfo->ptMinTrackSize.x = window.minimumWidth();
		minMaxInfo->ptMinTrackSize.y = window.minimumHeight();

		return 0;
	} break;

	case WM_DESTROY: {
		window._closed = true;
		PostQuitMessage(0);

		return 0;
	} break;

	default: return DefWindowProc(hwnd, msg, wparam, lparam); break;
	}
}
