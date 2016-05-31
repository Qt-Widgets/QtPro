#pragma comment(lib, "dwmapi.lib")
#pragma comment(lib, "UxTheme.lib")
#include <dwmapi.h>
#include <UxTheme.h>
#include <WindowsX.h>
#include "strsafe.h"
#include <afxres.h>
#include <Windows.h>

bool Window::nativeEvent(const QByteArray &eventType, void *message, long *result)
{
*result = 0;
MSG *msg = static_cast<MSG *>(message);

if(msg->message == WM_CREATE)
{
HWND hWnd = (HWND)this->winId();
qDebug() << "WM_ACTIVATE";

RECT rcClient;
GetWindowRect(hWnd, &rcClient);

SetWindowPos(hWnd,
NULL,
this->pos().x(), this->pos().y(),
this->size().width(), this->size().height(),
SWP_FRAMECHANGED);

*result = 0;
}

else if(msg->message == WM_ACTIVATE)
{
qDebug() << "WM_ACTIVATE";

HWND hWnd = (HWND)this->winId();
MARGINS margins;

margins.cxLeftWidth = 0;
margins.cxRightWidth = 0;
margins.cyBottomHeight = 0;
margins.cyTopHeight = 0;

DwmExtendFrameIntoClientArea(hWnd, &margins);

*result = 0;
}

else if(msg->message == WM_NCCALCSIZE)
{
qDebug() << "WM_NCCALCSIZE";

NCCALCSIZE_PARAMS pncsp = reinterpret_cast<NCCALCSIZE_PARAMS>(msg->lParam);

pncsp->rgrc[0].left = pncsp->rgrc[0].left + 0;
pncsp->rgrc[0].top = pncsp->rgrc[0].top + 0;
pncsp->rgrc[0].right = pncsp->rgrc[0].right - 0;
pncsp->rgrc[0].bottom = pncsp->rgrc[0].bottom - 0;
}

else
return QWidget::nativeEvent(eventType, message, result);
}
