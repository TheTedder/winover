#include <tchar.h>
#include <Windows.h>
#include "winover.h"

WNDPROC OldProc;

LRESULT __stdcall WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
void PrintError();

int WINAPI _tWinMain(HINSTANCE hInst, HINSTANCE hPrev, LPTSTR lpCmdLine, int nCmdShow) {
    // TODO: Get the window we want to overlay.

    TCHAR* classname = winover::WindowClassName();
    _tprintf_s(TEXT("window class name: %s\n"), classname);

    HWND hwnd = CreateWindowEx(
        WS_EX_LAYERED | WS_EX_TRANSPARENT,
        classname,
        NULL,
        WS_POPUP | WS_VISIBLE,
        64,
        64,
        640,
        480,
        NULL,
        NULL,
        hInst,
        NULL
    );

    if (hwnd == NULL) {
        PrintError();
        return FALSE;
    }

    // Subclass.

    OldProc = (WNDPROC)SetWindowLongPtr(hwnd, GWLP_WNDPROC, (LONG_PTR)WndProc);

    if (0 == SetLayeredWindowAttributes(hwnd, RGB(0, 0, 0), 100, LWA_COLORKEY)) {
        PrintError();
    }

    ShowWindow(hwnd, SW_SHOW);
    
    MSG msg;
    for (BOOL received = GetMessage(&msg, hwnd, 0, 0); received != 0 && received != -1; received = GetMessage(&msg, hwnd, 0, 0)) {
        DispatchMessage(&msg);
    }

    return msg.wParam;

    UNREFERENCED_PARAMETER(lpCmdLine);
    UNREFERENCED_PARAMETER(nCmdShow);
}

LRESULT __stdcall WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    if (uMsg == WM_PAINT) {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);
        SetTextColor(hdc, RGB(255, 255, 255));
        SetBkMode(hdc, TRANSPARENT);
        TCHAR text[] = TEXT("Saveglitch is OOB.");
        TextOut(hdc, 0, 0, text, sizeof(text) / sizeof(TCHAR));
        EndPaint(hWnd, &ps);
    }

    return CallWindowProc(OldProc, hWnd, uMsg, wParam, lParam);
}

void PrintError() {
    DWORD error = GetLastError();
    TCHAR error_text[256];
    if (FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM, NULL, error, 0, error_text, sizeof(error_text) / sizeof(TCHAR), NULL) > 0) {
        OutputDebugString(error_text);
    }
}