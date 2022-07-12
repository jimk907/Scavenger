#pragma once

#define WIN32_LEAN_AND_MEAN
// the following are taken from Windows.h remarks
// these defines prevent loading a lot of unneeded
// Windows definitions.

#define NOGDICAPMASKS
//#define NOVIRTUALKEYCODES
//#define NOWINMESSAGES
//#define NOWINSTYLES
//#define NOSYSMETRICS
//#define NOMENUS
//#define NOICONS
#define NOKEYSTATES
//#define NOSYSCOMMANDS
#define NORASTEROPS
//#define NOSHOWWINDOW
#define OEMRESOURCE
#define NOATOM
#define NOCLIPBOARD
//#define NOCOLOR    // std color definitions
//#define NOCTLMGR   // dialog and control styles
#define NODRAWTEXT
#define NOGDI
//#define NOKERNEL
//#define NOUSER     // needed for WNDPROC callback
//#define NONLS		 // needed for some string conversions (MultibyteToWideChar, etc)
//#define NOMB         // messagebox
#define NOMEMMGR
#define NOMETAFILE
#define NOMINMAX
//#define NOMSG
#define NOOPENFILE
#define NOSCROLL
#define NOSERVICE
//#define NOSOUND
#define NOTEXTMETRIC
#define NOWH         // Windows hook
//#define NOWINOFFSETS  // Get/Set Win32Window words
#define NOCOMM
#define NOKANJI
#define NOHELP
#define NOPROFILER
#define NODEFERWINDOWPOS
//#define NOMCX
#include <windows.h>
#include <windowsx.h>

