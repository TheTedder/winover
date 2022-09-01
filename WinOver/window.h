#pragma once

#include "framework.h"

namespace winover {
    // The module handle. Its value is set when the library is loaded.
    extern HINSTANCE hinst;
    // Constants 

    const TCHAR OVERLAY[] = TEXT("OVERLAY");
    const UINT_PTR TIMER_IDEVENT = 1;

    // Exported functions:

    __declspec(dllexport) HWND CreateOverlay(HWND);
    
    // Internal functions:

    LRESULT CALLBACK Wndproc(HWND, UINT, WPARAM, LPARAM);
}