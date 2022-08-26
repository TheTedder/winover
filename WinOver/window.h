#pragma once

#include "framework.h"

#define OVERLAY (TEXT("OVERLAY"))

namespace winover {
    extern HINSTANCE hinst;
    __declspec(dllexport) HWND CreateOverlay(HWND);
    LRESULT CALLBACK Wndproc(HWND, UINT, WPARAM, LPARAM);
}
