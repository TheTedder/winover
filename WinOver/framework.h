#pragma once
#pragma warning( disable: 4005 )

#include <sdkddkver.h>
#define NTDDI_VERSION NTDDI_VISTA
#define _WIN32_WINNT _WIN32_WINNT_VISTA
#define WINVER _WIN32_WINNT_VISTA

#define NOGDICAPMASKS
#define NOVIRTUALKEYCODES
#define NOSYSMETRICS
#define NOMENUS
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

#include <windows.h>