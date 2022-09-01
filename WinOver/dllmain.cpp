// dllmain.cpp : Defines the entry point for the DLL application.
#include "framework.h"
#include "window.h"

BOOL APIENTRY DllMain(
    HMODULE hModule,
    DWORD  ul_reason_for_call,
    LPVOID lpReserved
) {
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
    {
        winover::hinst = hModule;

        const WNDCLASS wndclass = {
            CS_NOCLOSE,
            winover::Wndproc,
            0,
            sizeof(ULONG_PTR),
            hModule,
            NULL,
            NULL,
            (HBRUSH)GetStockObject(BLACK_BRUSH),
            NULL,
            winover::OVERLAY
        };

        RegisterClass(&wndclass);
        break;
    }
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}