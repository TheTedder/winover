#include <tchar.h>
#include <Windows.h>
#include "winover.h"

WNDPROC OldProc;

LRESULT __stdcall WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
void PrintError();

int WINAPI _tWinMain(HINSTANCE hInst, HINSTANCE hPrev, LPTSTR lpCmdLine, int nCmdShow) {
    // TODO: Get the window we want to overlay.

    HWND notepad;
    while ((notepad = FindWindowEx(NULL, NULL, NULL, TEXT("Untitled - Notepad"))) == NULL);

    HWND hwnd = winover::CreateOverlay(notepad);

    if (hwnd == NULL) {
        PrintError();
        return FALSE;
    }

    ShowWindow(hwnd, SW_SHOW);
    
    // Subclass.

    OldProc = (WNDPROC)SetWindowLongPtr(hwnd, GWLP_WNDPROC, (LONG_PTR)WndProc);

    // Set the transparency.

    if (0 == SetLayeredWindowAttributes(hwnd, RGB(0, 0, 0), 100, LWA_COLORKEY)) {
        PrintError();
    }
    
loop:
    MSG msg;
    BOOL received = GetMessage(&msg, NULL, 0, 0);
    
    if (received == 0 || received == -1) {
        return msg.wParam;
    }

    DispatchMessage(&msg);
    goto loop;
    
    UNREFERENCED_PARAMETER(lpCmdLine);
    UNREFERENCED_PARAMETER(nCmdShow);
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    if (uMsg == WM_PAINT) {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);
        SetTextColor(hdc, RGB(255, 31, 0));
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