#include <windows.h>
#include <cassert>
#include <stdexcept>
#include <windowsx.h>
#include <dwmapi.h>
#pragma comment(lib, "dwmapi.lib")

LPCWSTR Class_Name_Size = L"Win32APP";
#define BORDER_WIDTH 5

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	switch (msg)
	{
	case WM_CLOSE:
		DestroyWindow(hwnd); break;

	case WM_DESTROY:
		PostQuitMessage(0); break;

	case WM_NCHITTEST: {
		RECT winrect;
		GetWindowRect(hwnd, &winrect);
		long x = GET_X_LPARAM(lParam);
		long y = GET_Y_LPARAM(lParam);

		// TOP
		if (y >= winrect.top && y < winrect.top + BORDER_WIDTH - 3) {
			return HTTOP;
		}
		// BOTTOM
		if (y < winrect.bottom && y >= winrect.bottom - BORDER_WIDTH) {
			return HTBOTTOM;
		}
		// LEFT
		if (x >= winrect.left && x < winrect.left + BORDER_WIDTH) {
			return HTLEFT;
		}
		// RIGHT
		if (x < winrect.right && x >= winrect.right - BORDER_WIDTH) {
			return HTRIGHT;
		}
		// BOTTOM LEFT
		if (x >= winrect.left  && x < winrect.left + BORDER_WIDTH &&
			y < winrect.bottom && y >= winrect.bottom - BORDER_WIDTH) {
			return HTBOTTOMLEFT;
		}
		// BOTTOM RIGHT
		if (x < winrect.right  && x >= winrect.right - BORDER_WIDTH &&
			y < winrect.bottom && y >= winrect.bottom - BORDER_WIDTH) {
			return HTBOTTOMRIGHT;
		}
		// TOP LEFT
		if (x >= winrect.left && x < winrect.left + BORDER_WIDTH &&
			y >= winrect.top  && y < winrect.top + BORDER_WIDTH) {
			return HTTOPLEFT;
		}
		// TOP RIGHT
		if (x < winrect.right && x >= winrect.right - BORDER_WIDTH &&
			y >= winrect.top  && y < winrect.top + BORDER_WIDTH) {
			return HTTOPRIGHT;
		}
		return HTCAPTION;
	} break;
	}
	return DefWindowProc(hwnd, msg, wParam, lParam);
}

int WINAPI WinMain(HINSTANCE hInsance, HINSTANCE hPrevInsance, LPSTR lpCmdLine, int nCmdShow) {
	WNDCLASSEX wcex;
	HWND hwnd;
	MSG msg;

	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInsance;
	wcex.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = Class_Name_Size;
	wcex.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

	if (!RegisterClassEx(&wcex)) {
		MessageBox(NULL, (LPCWSTR)L"Window Registeration Faild !", (LPCWSTR)L"Error", MB_ICONEXCLAMATION | MB_OK);
		return 0;
	}

	hwnd = CreateWindow(
		Class_Name_Size,
		(LPCWSTR)L"Sample Win32 APP",
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, 240, 120,
		NULL, NULL, hInsance, NULL);

	if (hwnd == NULL) {
		MessageBox(NULL, (LPCWSTR)L"Window Registeration Faild !", (LPCWSTR)L"Error", MB_ICONEXCLAMATION | MB_OK);
		return 0;
	}

	ShowWindow(hwnd, nCmdShow);

	DWORD dwStyle = GetWindowLong(hwnd, GWL_STYLE);
	dwStyle &= ~WS_CAPTION;

	SetWindowLong(hwnd, GWL_STYLE, dwStyle);

	//SetWindowPos(hwnd, NULL, NULL, NULL, NULL, NULL, SWP_FRAMECHANGED | SWP_NOZORDER | SWP_NOMOVE | SWP_NOSIZE);

	int _m = -1;
	static const MARGINS shadow_state = { _m, _m, _m, _m };
	//DwmExtendFrameIntoClientArea(hwnd, &shadow_state);

	UpdateWindow(hwnd);

	while (GetMessage(&msg, NULL, NULL, 0) > 0) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return msg.wParam;
}
