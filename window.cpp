#include "window.h"

#define OVERLAY (TEXT("OVERLAY"))

namespace winover {
    void RegisterWindowClass(HINSTANCE hInst) {
        WNDCLASS existing;

        if (0 != GetClassInfo(hInst, OVERLAY, &existing)) {
            // The class has already been registered.

            HWND temp_window = CreateWindow(OVERLAY, NULL, NULL, 0, 0, 0, 0, HWND_MESSAGE, NULL, hInst, NULL);
            ULONG_PTR count = GetClassLongPtr(temp_window, 0);
            SetClassLongPtr(temp_window, 0, count + 1);
            DestroyWindow(temp_window);
            return;
        }

        // The class has not been registered.

        const WNDCLASS wndclass = {
            CS_GLOBALCLASS | CS_NOCLOSE,
            Wndproc,
            sizeof(ULONG_PTR),
            sizeof(ULONG_PTR),
            hInst,
            NULL,
            NULL,
            NULL,
            NULL,
            OVERLAY
        };

        RegisterClass(&wndclass);
    }

    void UnregisterWindowClass(HINSTANCE hInst) {
        HWND temp_window = CreateWindow(OVERLAY, NULL, NULL, 0, 0, 0, 0, HWND_MESSAGE, NULL, hInst, NULL);
        ULONG_PTR count = GetClassLongPtr(temp_window, 0);
        SetClassLongPtr(temp_window, 0, count - 1);
        DestroyWindow(temp_window);
        
        if (count == 1) {
            UnregisterClass(OVERLAY, hInst);
        }

        return;
    }
}

LRESULT __stdcall Wndproc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    return DefWindowProc(hWnd, uMsg, wParam, lParam);
}