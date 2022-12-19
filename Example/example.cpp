#include <Windows.h>
#include "winover.h"


LRESULT __stdcall WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
VOID PrintError();
WNDPROC OldProc;
int APIENTRY wWinMain(HINSTANCE hInst, HINSTANCE hPrev, LPWSTR lpCmdLine, int nCmdShow) {

    HWND notepad;
    while ((notepad = FindWindowEx(NULL, NULL, NULL, TEXT("Untitled - Notepad"))) == NULL);

    HWND hwnd = winover::CreateOverlay(notepad);

    if (hwnd == NULL) {
        PrintError();
        return FALSE;
    }

    // Set the background to solid black.
    SetClassLongPtrW(hwnd, GCLP_HBRBACKGROUND, (LONG_PTR)GetStockObject(BLACK_BRUSH));

    // Set the color key to black.
    if (0 == SetLayeredWindowAttributes(hwnd, RGB(0, 0, 0), 100, LWA_COLORKEY)) {
        PrintError();
        return FALSE;
    }

    // Subclass.

    OldProc = (WNDPROC)SetWindowLongPtrW(hwnd, GWLP_WNDPROC, (LONG_PTR)WndProc);
    
    // The message loop
loop:
    MSG msg;
    BOOL received = GetMessageW(&msg, NULL, 0, 0);
    
    if (received == 0 || received == -1) {
        return msg.wParam;
    }

    DispatchMessageW(&msg);
    goto loop;
    
    UNREFERENCED_PARAMETER(hInst);
    UNREFERENCED_PARAMETER(hPrev);
    UNREFERENCED_PARAMETER(lpCmdLine);
    UNREFERENCED_PARAMETER(nCmdShow);
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    if (uMsg == WM_PAINT) {
        PAINTSTRUCT ps;
        const HDC hdc = BeginPaint(hWnd, &ps);
        SetTextColor(hdc, RGB(255, 31, 0));
        SetBkMode(hdc, TRANSPARENT);
        const WCHAR text[] = TEXT("Check out this sick overlay.");
        TextOutW(hdc, 0, 0, text, sizeof(text) / sizeof(WCHAR));
        EndPaint(hWnd, &ps);
    }

    return CallWindowProcW(OldProc, hWnd, uMsg, wParam, lParam);
}

VOID PrintError() {
    const DWORD error = GetLastError();
    WCHAR error_text[256];
    if (FormatMessageW(FORMAT_MESSAGE_FROM_SYSTEM, NULL, error, 0, error_text, sizeof(error_text) / sizeof(WCHAR), NULL) > 0) {
        OutputDebugStringW(error_text);
    }
}