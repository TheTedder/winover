#pragma once

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
//#include <sdkddkver.h>
//#define NTDDI_VERSION NTDDI_WINBLUE  
//#define _WIN32_WINNT _WIN32_WINNT_WINBLUE  
//#define WINVER _WIN32_WINNT_WINBLUE  
#define NOGDICAPMASKS
#define NOVIRTUALKEYCODES
#define NOSYSMETRICS
#define NOICONS
#define NOKEYSTATES
#define NOSYSCOMMANDS
#define OEMRESOURCE
#define NOATOM
#define NOCLIPBOARD
#define NOOPENFILE
#define NOSOUND
#define NOWH
#define NOKANJI
#define NOMCX
// Windows Header Files
#include <windows.h>
#include <tchar.h>