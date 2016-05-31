/*#include <stdexcept>
#include <typeinfo>
#include <string>

#include "gitbutton.h"

int main() {
	BorderlessWindow window;

	MSG msg{};
	while (!window.is_closed()) {
		while (PeekMessage(&msg, window.handle(), 0, 0, PM_REMOVE)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
}*/


#include <windows.h>
#include <Uxtheme.h>
#include <Dwmapi.h>

LPCWSTR Class_Name_Size = L"Win32APP";
static int LEFTEXTENDWIDTH = 8;
static int RIGHTEXTENDWIDTH = 8;
static int BOTTOMEXTENDWIDTH = 20;
static int TOPEXTENDWIDTH = 27;

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	switch (msg)
	{
	case WM_CLOSE:
		DestroyWindow(hwnd); break;
	case WM_DESTROY:
		PostQuitMessage(0); break;
	default:
		return DefWindowProc(hwnd, msg, wParam, lParam); break;
	}
	return 0;
}

int WINAPI WinMain(HINSTANCE hInsance, HINSTANCE hPrevInsance, LPSTR lpCmdLine, int nCmdShow) {
	WNDCLASSEX wcex;
	HWND hwnd;
	MSG msg;

	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = 0;
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

	hwnd = CreateWindowEx(
		WS_EX_CLIENTEDGE,
		Class_Name_Size,
		(LPCWSTR)L"Sample Win32 APP",
		(WS_POPUPWINDOW | WS_THICKFRAME),
		CW_USEDEFAULT, CW_USEDEFAULT, 240, 120,
		NULL, NULL, hInsance, NULL);

	if (hwnd == NULL) {
		MessageBox(NULL, (LPCWSTR)L"Window Registeration Faild !", (LPCWSTR)L"Error", MB_ICONEXCLAMATION | MB_OK);
		return 0;
	}

	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);

	while (GetMessage(&msg, NULL, NULL, 0) > 0) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return msg.wParam;
}


