#pragma once
#include <Windows.h>

namespace winover {
    /// <summary>
    /// Creates a new overlay. The thread that calls this function must be responsible for handling window messages.
    /// The user can call DestroyWindow() to terminate the overlay manually, otherwise it will close itself when the overlaid window closes.
    /// </summary>
    /// <param name="hwnd">A handle to the window you want the overlay to go on top of.</param>
    /// <returns>A handle to the overlay or NULL if the overlay was not created successfully.</returns>
    __declspec(dllimport) HWND CreateOverlay(HWND hWnd);

    /// <summary>
    /// Switches the window that the overlay will draw over.
    /// It may take a moment for the change to take effect due to data caching performed by the operating system.
    /// </summary>
    /// <param name="overlay">
    /// A handle to the overlay whose target window you want to change.
    /// This must be a handle to a window that was created with the CreateOverlay function.
    /// </param>
    /// <param name="target">
    /// A handle to the window that is to become the overlay's new target.
    /// This cannot be the same window as the ovelay itself.
    /// Setting this paramater to an invalid or null handle will destroy the overlay.
    /// </param>
    /// <returns>TRUE for success and FALSE for failure. This function may or may not call SetLastError.</returns>
    __declspec(dllimport) BOOL ChangeTarget(HWND overlay, HWND target);

    /// <summary>
    /// Retrieves a handle to the target window that an overlay is drawing on top of.
    /// </summary>
    /// <param name="overlay">
    /// A handle to the overlay whose target you want to retrieve.
    /// This must be a handle to a window that was created with the CreateOverlay function.
    /// </param>
    /// <returns>
    /// A handle to the target window or NULL if it could not be retrieved.
    /// This function may or may not call SetLastError.
    /// </returns>
    __declspec(dllimport) HWND GetTarget(HWND overlay);
}