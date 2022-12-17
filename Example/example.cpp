#include <Windows.h>
#include <tchar.h>
#include "winover.h"

WNDPROC OldProc;

LRESULT __stdcall WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
void PrintError();

int APIENTRY _tWinMain(HINSTANCE hInst, HINSTANCE hPrev, LPTSTR lpCmdLine, int nCmdShow) {
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

    OldProc = (WNDPROC)SetWindowLongPtr(hwnd, GWLP_WNDPROC, (LONG_PTR)WndProc);
    
    // The message loop
loop:
    MSG msg;
    BOOL received = GetMessage(&msg, NULL, 0, 0);
    
    if (received == 0 || received == -1) {
        return msg.wParam;
    }

    DispatchMessage(&msg);
    goto loop;
    
    UNREFERENCED_PARAMETER(hInst);
    UNREFERENCED_PARAMETER(hPrev);
    UNREFERENCED_PARAMETER(lpCmdLine);
    UNREFERENCED_PARAMETER(nCmdShow);
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    if (uMsg == WM_PAINT) {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);
        SetTextColor(hdc, RGB(255, 31, 0));
        SetBkMode(hdc, TRANSPARENT);
        TCHAR text[] = TEXT("Check out this sick overlay.");
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