#pragma once

#include "framework.h"

#define OVERLAY (TEXT("OVERLAY"))

namespace winover {
    // The module handle. Its value is set when the library is loaded.
    extern HINSTANCE hinst;

    // Exported functions:

    __declspec(dllexport) HWND CreateOverlay(HWND);
    
    // Internal functions:

    LRESULT CALLBACK Wndproc(HWND, UINT, WPARAM, LPARAM);
}