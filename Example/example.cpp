#include <Windows.h>
#include <Psapi.h>
#include <Shlwapi.h>
#include "winover.h"

typedef struct {
    LPCWSTR desired;
    HWND target;
} ENUMWNDPROCDATA;

LRESULT __stdcall WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
BOOL CALLBACK EnumWndProc(HWND hwnd, LPARAM lParam);
VOID PrintError();

WNDPROC OldProc;

int APIENTRY wWinMain(HINSTANCE hInst, HINSTANCE hPrev, LPWSTR lpCmdLine, int nCmdShow) {
    int argc;
    LPWSTR* const argv = CommandLineToArgvW(lpCmdLine, &argc);

    if (argc < 1) {
        LocalFree(argv);
        return 0;
    }

    ENUMWNDPROCDATA data {
        argv[0],
        NULL
    };

    // Find the top level window for the program specified on the command line.
    while (data.target == NULL) {
        EnumWindows(EnumWndProc, (LPARAM)&data);
    }

    LocalFree(argv);
    const HWND hwnd = winover::CreateOverlay(data.target);

    if (hwnd == NULL) {
        PrintError();
        return 0;
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

BOOL CALLBACK EnumWndProc(HWND hwnd, LPARAM lParam) {
    const LONG_PTR style = GetWindowLongPtrW(hwnd, GWL_STYLE);

    if (style == 0 || (style & WS_CHILD) != 0 || GetWindow(hwnd, GW_OWNER) != NULL || !IsWindowVisible(hwnd)) {
        return TRUE;
    }

    DWORD pid;
    GetWindowThreadProcessId(hwnd, &pid);
    const HANDLE hProc = OpenProcess(PROCESS_QUERY_LIMITED_INFORMATION, FALSE, pid);

    if (hProc == NULL) {
        return TRUE;
    }

    WCHAR procname[MAX_PATH];
    const DWORD result = GetModuleFileNameExW(hProc, NULL, procname, MAX_PATH);
    CloseHandle(hProc);

    if (result == 0) {
        return TRUE;
    }

    ENUMWNDPROCDATA* const data = (ENUMWNDPROCDATA*)lParam;
    LPCWSTR const file = PathFindFileNameW(procname);
    
    if (wcscmp(data->desired, file) != 0) {
        return TRUE;
    }

    data->target = hwnd;
    return FALSE;
}

VOID PrintError() {
    const DWORD error = GetLastError();
    WCHAR error_text[256];
    if (FormatMessageW(FORMAT_MESSAGE_FROM_SYSTEM, NULL, error, 0, error_text, sizeof(error_text) / sizeof(WCHAR), NULL) > 0) {
        OutputDebugStringW(error_text);
    }
}