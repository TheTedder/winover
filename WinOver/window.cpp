#include "window.h"

namespace winover {
    HINSTANCE hinst;
    /// <summary>
    /// Creates a new overlay. Do not forget to call DestroyWindow() when you are finished with it.
    /// </summary>
    /// <param name="hwnd"> A handle to the window you want the overlay to go on top of.</param>
    /// <returns></returns>
    HWND CreateOverlay(HWND hwnd) {
        return CreateWindowEx(
            WS_EX_LAYERED | WS_EX_TRANSPARENT,
            OVERLAY,
            NULL,
            WS_POPUP,
            0, 0, 200, 200,
            NULL,
            NULL,
            hinst,
            hwnd
        );
    }

    LRESULT CALLBACK Wndproc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
        switch (uMsg) {
        case WM_DESTROY:
            PostQuitMessage(0);
            break;
        default:
            return DefWindowProc(hWnd, uMsg, wParam, lParam);
        }

        return 0;
    }
}