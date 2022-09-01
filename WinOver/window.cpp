#include "window.h"

namespace winover {
    HWND CreateOverlay(HWND hwnd) {
        HMODULE hmodule;
        if (0 == GetModuleHandleEx(GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT, TEXT("WinOver.dll"), &hmodule)) {
            return NULL;
        }

        const HWND result = CreateWindowEx(
            WS_EX_LAYERED | WS_EX_TRANSPARENT,
            OVERLAY,
            NULL,
            WS_POPUP,
            0, 0, 200, 200,
            NULL,
            NULL,
            hmodule,
            hwnd
        );

        if (result != NULL) {
            SetLayeredWindowAttributes(result, RGB(0, 0, 0), 100, LWA_COLORKEY);
        }

        return result;
    }

    LRESULT CALLBACK Wndproc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
        switch (uMsg) {
        case WM_CREATE:
            SetWindowLongPtr(hWnd, 0, (LONG_PTR)((LPCREATESTRUCT)lParam)->lpCreateParams);
            return 0;
        case WM_DESTROY:
            PostQuitMessage(0);
            break;
        default:
            return DefWindowProc(hWnd, uMsg, wParam, lParam);
        }

        return 0;
    }
}