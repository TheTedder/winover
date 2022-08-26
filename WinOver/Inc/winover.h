#pragma once
#include <Windows.h>

namespace winover {
    __declspec(dllimport) HWND CreateOverlay(HWND hWnd);
}