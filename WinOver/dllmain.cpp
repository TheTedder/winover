// dllmain.cpp : Defines the entry point for the DLL application.
#include "framework.h"
#include "window.h"

namespace winover {
    ATOM overlay_class;
}

BOOL APIENTRY DllMain(
    HMODULE hModule,
    DWORD  ul_reason_for_call,
    LPVOID lpReserved
) {
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
    {
        SetUserObjectInformation(GetCurrentProcess(), UOI_TIMERPROC_EXCEPTION_SUPPRESSION, FALSE, 0);
        
        const WNDCLASS wndclass = {
            CS_NOCLOSE,
            winover::Wndproc,
            0,
            sizeof(ULONG_PTR),
            hModule,
            NULL,
            NULL,
            NULL,
            NULL,
            winover::OVERLAY
        };

        ATOM registered_class = RegisterClass(&wndclass);

        if (registered_class != 0) {
            winover::overlay_class = registered_class;
        }
        break;
    }
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }

    UNREFERENCED_PARAMETER(lpReserved);
    return TRUE;
}