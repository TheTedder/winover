#pragma once

#include <sdkddkver.h>
#define NTDDI_VERSION NTDDI_WINXPSP3
#define _WIN32_WINNT _WIN32_WINNT_WS03
#define WINVER _WIN32_WINNT_WS03

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

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#include <tchar.h>