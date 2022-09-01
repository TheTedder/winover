#include "window.h"

namespace winover {
    HWND CreateOverlay(HWND hwnd) {
        if (0 == IsWindow(hwnd)) {
            return NULL;
        }

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
            SetTimer(result, TIMER_IDEVENT, USER_TIMER_MINIMUM, TimerProc);
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

    VOID CALLBACK TimerProc(HWND hWnd, UINT uMsg, UINT_PTR id, DWORD time) {
        HWND overlaid = (HWND)GetWindowLongPtr(hWnd, 0);

        WINDOWPLACEMENT placement{
            sizeof(WINDOWPLACEMENT)
        };

        if (0 == GetWindowPlacement(overlaid, &placement)) {
            DestroyWindow(hWnd);
            return;
        }

        if (placement.showCmd == SW_SHOWMINIMIZED || !IsWindowVisible(overlaid)) {
            ShowWindow(hWnd, SW_HIDE);
        }
        else {
            WINDOWINFO info = {
                sizeof(WINDOWINFO)
            };
            if (0 == GetWindowInfo(overlaid, &info)) {
                DestroyWindow(hWnd);
                return;
            }

            /*POINT point = { 0L, 0L };
            if (0 == ClientToScreen(overlaid, &point)) {
                DestroyWindow(hWnd);
                return;
            }*/

            HWND after;
            if (WS_EX_TOPMOST & GetWindowLongPtr(overlaid, GWL_EXSTYLE) || info.dwWindowStatus == WS_ACTIVECAPTION) {
                after = HWND_TOPMOST;
            }
            else {
                /* 
                 * Place our overlay directly below the window directly above the overlaid window.
                 * This prevents the overlay from drawing over any windows it's not supposed to.
                 */
                after = GetWindow(overlaid, GW_HWNDPREV);
            }

            // Position the overlay.
            SetWindowPos(
                hWnd,
                after,
                info.rcClient.left,
                info.rcClient.top,
                info.rcClient.right - info.rcClient.left,
                info.rcClient.bottom - info.rcClient.top,
                SWP_SHOWWINDOW
            );
        }
    }
}