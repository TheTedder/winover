#pragma once

#include <windef.h>

namespace winover {
    /// <summary>
    /// Creates a new overlay. The thread that calls this function must be responsible for handling window messages.
    /// The user is encouraged to call SetLayeredWindowAttributes() immediately after calling this function.
    /// The window will have a completely black background by default.
    /// The user can call DestroyWindow() to terminate the overlay prematurely, otherwise it will close itself when the overlaid window closes.
    /// </summary>
    /// <param name="hwnd">A handle to the window you want the overlay to go on top of.</param>
    /// <returns>A handle to the overlay or NULL if the overlay was not created successfully.</returns>
    __declspec(dllimport) HWND CreateOverlay(HWND hWnd);
}