#pragma once

#include "framework.h"
#include "messages.h"

namespace winover {
    // Constants 

    const TCHAR OVERLAY[] = TEXT("OVERLAY");
    const UINT_PTR TIMER_IDEVENT = 1;

    // Exported functions

    __declspec(dllexport) HWND CreateOverlay(HWND);
    __declspec(dllexport) BOOL SetBackgroundColor(HWND hWnd, COLORREF color);

    // Internal functions

    LRESULT CALLBACK Wndproc(HWND, UINT, WPARAM, LPARAM);
    VOID CALLBACK TimerProc(HWND, UINT, UINT_PTR, DWORD);
}