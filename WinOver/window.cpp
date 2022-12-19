#include "window.h"

#pragma warning( disable : 4703)

namespace winover {
    extern ATOM overlay_class;

    HWND CreateOverlay(HWND hwnd) {
        if (0 == IsWindow(hwnd)) {
            return NULL;
        }

        HMODULE hmodule;
        if (0 == GetModuleHandleEx(GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT, TEXT("WinOver.dll"), &hmodule)) {
            return NULL;
        }

        const HWND result = CreateWindowEx(
            WS_EX_NOACTIVATE | WS_EX_LAYERED | WS_EX_TRANSPARENT,
            OVERLAY,
            NULL,
            WS_POPUP | WS_DISABLED,
            0, 0, 200, 200,
            NULL,
            NULL,
            hmodule,
            hwnd
        );

        if (result != NULL) {
            SetTimer(result, TIMER_IDEVENT, USER_TIMER_MINIMUM, TimerProc);
        }

        return result;
    }

    BOOL IsOverlay(HWND hwnd) {
        ULONG_PTR class_longptr = GetClassLongPtr(hwnd, GCW_ATOM);

        return class_longptr != 0 && class_longptr == overlay_class;

    }

    BOOL ChangeTarget(HWND overlay, HWND target) {
        if (overlay == target) {
            return FALSE;
        }

        if (!IsOverlay(overlay)) {
            return FALSE;
        }

        // 0 doesn't necessarily indicate an error for this function because it returns the previous value, which could be 0; however, the previous value should never be zero here.
        return SetWindowLongPtr(overlay, 0, (LONG_PTR)target) != 0;
    }

    LRESULT CALLBACK Wndproc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
        switch (uMsg) {
        case WM_CREATE:
            SetWindowLongPtr(hWnd, 0, (LONG_PTR)((LPCREATESTRUCT)lParam)->lpCreateParams);
            break;
        case WM_DESTROY:
            KillTimer(hWnd, TIMER_IDEVENT);
            PostQuitMessage(0);
            break;
        default:
            return DefWindowProc(hWnd, uMsg, wParam, lParam);
        }

        return 0;
    }

    VOID CALLBACK TimerProc(HWND hWnd, UINT uMsg, UINT_PTR id, DWORD time) {
        const HWND overlaid = (HWND)GetWindowLongPtr(hWnd, 0);

        WINDOWPLACEMENT placement = {
            sizeof(WINDOWPLACEMENT)
        };
        if (0 == GetWindowPlacement(overlaid, &placement)) {
            DestroyWindow(hWnd);
            return;
        }

        if (placement.showCmd == SW_SHOWMINIMIZED || !IsWindowVisible(overlaid)) {
            ShowWindow(hWnd, SW_HIDE);
            return;
        }

        WINDOWINFO info = {
            sizeof(WINDOWINFO)
        };
        if (0 == GetWindowInfo(overlaid, &info)) {
            DestroyWindow(hWnd);
            return;
        }

        UINT flags;

#ifdef _DEBUG
        HWND after = NULL;
#else
        HWND after;
#endif

        if (GetWindow(hWnd, GW_HWNDNEXT) == overlaid) {
            // If the overlay is already direct above the target window in the Z order then we don't need to change it.
            flags = SWP_SHOWWINDOW | SWP_NOACTIVATE | SWP_NOZORDER;
        } else {
            /*
                * Place our overlay directly below the window directly above the overlaid window.
                * This prevents the overlay from drawing over any windows it's not supposed to.
                * Conveniently, if there is no window of top of the one we want, GetWindow returns zero,
                * which corresponds to the value of HWND_TOP when passed into SetWindowPos,
                * producing the desired result of placing our overlay on top of every window.
                */
            after = GetWindow(overlaid, GW_HWNDPREV);
            flags = SWP_SHOWWINDOW | SWP_NOACTIVATE;
        }

        // Position the overlay.
        SetWindowPos(
            hWnd,
#pragma warning( suppress : 6001)
            after,
            info.rcClient.left,
            info.rcClient.top,
            info.rcClient.right - info.rcClient.left,
            info.rcClient.bottom - info.rcClient.top,
            flags
        );
    }
}