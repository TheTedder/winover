#pragma once

#include "framework.h"

namespace winover {
    void RegisterWindowClass(HINSTANCE);
    void UnregisterWindowClass(HINSTANCE);
}

LRESULT __stdcall Wndproc(HWND, UINT, WPARAM, LPARAM);