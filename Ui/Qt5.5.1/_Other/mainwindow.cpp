#include <QApplication>
#include <QDesktopWidget>
#include <QTabWidget>
#include <QLineEdit>
#include <QStyle>
#include <QDebug>
#include "mainwindow.h"
#include "Windows.h"
#include "WinUser.h"
#include "windowsx.h"
#include "dwmapi.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setAttribute(Qt::WA_TranslucentBackground, true);

    tabWidget = new MyTabWidget(this);
    tabWidget->setTabsClosable(true);
    tabWidget->setMovable(true);
    tabWidget->setDocumentMode(true);
    tabWidget->addTab(new QLineEdit("1234"), "tab 1");
    tabWidget->addTab(new QLineEdit, "tab 2");
    tabWidget->addTab(new QLineEdit, "tab 3");

    this->setCentralWidget(tabWidget);
    resize(400,200);


    // Handle window creation.
    RECT rcClient;
    GetWindowRect((HWND)this->winId(), &rcClient);

    // Inform application of the frame change.
    SetWindowPos((HWND)this->winId(),
                 NULL,
                 rcClient.left, rcClient.top,
                 rcClient.right - rcClient.left,
                 rcClient.bottom - rcClient.top,
                 SWP_FRAMECHANGED);
}

bool MainWindow::winEvent(MSG *msg, long *result)
{
    bool fCallDWP = true;
    BOOL fDwmEnabled = FALSE;
    LRESULT lRet = 0;
    HRESULT hr = S_OK;
    HWND hWnd       = msg->hwnd;
    UINT message    = msg->message;
    WPARAM wParam   = msg->wParam;
    LPARAM lParam   = msg->lParam;

    // Winproc worker for custom frame issues.
    hr = DwmIsCompositionEnabled(&fDwmEnabled);
    if (!SUCCEEDED(hr) || !fDwmEnabled)
    {
        qDebug() << "DWM not enabled";
        return false;
    }

    if (message == WM_NCHITTEST)
    {
        return hitTestNCA(msg, result);
    }

    fCallDWP = !DwmDefWindowProc(hWnd, message, wParam, lParam, &lRet);

    // Handle window activation.
    if (message == WM_ACTIVATE)
    {
        // Extend the frame into the client area.
        MARGINS margins;

        margins.cxLeftWidth = -1;
        margins.cxRightWidth = -1;
        margins.cyBottomHeight = -1;
        margins.cyTopHeight = -1;//style()->pixelMetric(QStyle::PM_TitleBarHeight);

        hr = DwmExtendFrameIntoClientArea(hWnd, &margins);

        if (!SUCCEEDED(hr))
        {
            // Handle error.
        }

        fCallDWP = true;
        lRet = 0;
    }

    // Handle the non-client size message.
    if ((message == WM_NCCALCSIZE) && (wParam == TRUE))
    {
        // Calculate new NCCALCSIZE_PARAMS based on custom NCA inset.
        NCCALCSIZE_PARAMS *pncsp = reinterpret_cast<NCCALCSIZE_PARAMS*>(lParam);

        pncsp->rgrc[0].left   = pncsp->rgrc[0].left   + 0;
        pncsp->rgrc[0].top    = pncsp->rgrc[0].top    + 0;
        pncsp->rgrc[0].right  = pncsp->rgrc[0].right  - 0;
        pncsp->rgrc[0].bottom = pncsp->rgrc[0].bottom - 0;

        lRet = 0;

        // No need to pass the message on to the DefWindowProc.
        fCallDWP = false;
    }

    if (message == WM_GETMINMAXINFO) {
        MINMAXINFO *mmi = (MINMAXINFO*)lParam;
        QRect rect = QApplication::desktop()->availableGeometry();
        mmi->ptMaxSize.x = rect.width();
        mmi->ptMaxSize.y = rect.height()-1;
        mmi->ptMaxPosition.x = 0;
        mmi->ptMaxPosition.y = 0;
        lRet = 0;
        fCallDWP = false;
    }

    if (!fCallDWP)
        *result = lRet;

    return !fCallDWP;
}

bool MainWindow::nativeEvent(const QByteArray &eventType, void *message, long *result)
{
    return winEvent((MSG*)message, result);
}

bool MainWindow::hitTestNCA(MSG *msg, long *result)
{
    // Get the window rectangle.
    RECT rcWindow;
    GetWindowRect(msg->hwnd, &rcWindow);

    // Get the frame rectangle, adjusted for the style without a caption.
    RECT rcFrame = { 0 };
    AdjustWindowRectEx(&rcFrame, WS_OVERLAPPEDWINDOW & ~WS_CAPTION, FALSE, NULL);

    int x = GET_X_LPARAM(msg->lParam), y = GET_Y_LPARAM(msg->lParam);
    if (tabWidget->getTabAt(QPoint(x - rcWindow.left, y - rcWindow.top)) == -1) {
        LRESULT lRet = 0;
        if (DwmDefWindowProc(msg->hwnd, msg->message, msg->wParam, msg->lParam, &lRet)) {
            *result = lRet;
            return true;    // handled for Titlebar area
        }
    } else {
        *result = HTCLIENT;
        return true;
    }

    USHORT uRow = 1;
    USHORT uCol = 1;

    // Determine if the point is at the top or bottom of the window.
    if (y >= rcWindow.top && y < rcWindow.top + style()->pixelMetric(QStyle::PM_MDIFrameWidth))
        uRow = 0;
    else if (y < rcWindow.bottom && y >= rcWindow.bottom - style()->pixelMetric(QStyle::PM_MDIFrameWidth))
        uRow = 2;

    // Determine if the point is at the left or right of the window.
    if (x >= rcWindow.left && x < rcWindow.left + style()->pixelMetric(QStyle::PM_TitleBarHeight))
        uCol = 0;
    else if (x < rcWindow.right && x >= rcWindow.right - style()->pixelMetric(QStyle::PM_MDIFrameWidth))
        uCol = 2;

    LRESULT hitTests[3][3] =
    {
        { HTTOPLEFT,    y < (rcWindow.top - rcFrame.top) ? HTTOP : HTCAPTION,    HTTOPRIGHT },
        { HTLEFT,       HTNOWHERE,      HTRIGHT },
        { HTBOTTOMLEFT, HTBOTTOM,       HTBOTTOMRIGHT },
    };

    *result = hitTests[uRow][uCol];
    return *result != HTNOWHERE;
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
