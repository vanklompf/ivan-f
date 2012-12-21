/*
 *
 *  Iter Vehemens ad Necem (IVAN)
 *  Copyright (C) Timo Kiviluoto
 *  Released under the GNU General
 *  Public License
 *
 *  See LICENSING which should be included
 *  along with this file for more details
 *
 */

#include <cstdarg>
#include <cstring>
#include <cstdlib>
#include <cstdio>

#ifdef _WIN32
#include "SDL.h"
#include <windows.h>
#else
#include <iostream>
#endif

#ifdef _MSC_VER
#include <new.h>
#define set_new_handler _set_new_handler
#else
#include <new>
#define set_new_handler std::set_new_handler
#endif

#include "error.h"

/* Shouldn't be initialized here! */

const char* globalerrorhandler::BugMsg
= "\n\nPlease send bug report to ivan-users@sourceforge.net\n"
"including a brief description of what you did, what version\n"
"you are running and which kind of system you are using.";

#ifdef _MSC_VER
int (*globalerrorhandler::OldNewHandler)(size_t) = 0;
#else
void (*globalerrorhandler::OldNewHandler)() = 0;
#endif

void globalerrorhandler::Install()
{
  static truth AlreadyInstalled = false;

  if(!AlreadyInstalled)
  {
    AlreadyInstalled = true;
    OldNewHandler = set_new_handler(NewHandler);

#ifdef __DJGPP__
    for(int c = 0; c < SIGNALS; ++c)
      OldSignal[c] = signal(Signal[c], SignalHandler);
#endif

    atexit(globalerrorhandler::DeInstall);
  }
}

void globalerrorhandler::DeInstall()
{
#ifdef __DJGPP__
  for(int c = 0; c < SIGNALS; ++c)
    signal(Signal[c], OldSignal[c]);
#endif

  set_new_handler(OldNewHandler);
}

void globalerrorhandler::Abort(const char* Format, ...)
{
  char Buffer[512];

  va_list AP;
  va_start(AP, Format);
  vsprintf(Buffer, Format, AP);
  va_end(AP);

  strcat(Buffer, BugMsg);

#ifdef _WIN32
  ShowWindow(GetActiveWindow(), SW_HIDE);
  MessageBox(NULL, Buffer, "Program aborted!",
	     MB_OK|MB_ICONEXCLAMATION|MB_TASKMODAL);
#endif
#ifdef __unix__
  std::cout << Buffer << std::endl;
#endif

  exit(4);
}

#ifdef _MSC_VER
int globalerrorhandler::NewHandler(size_t)
#else
  void globalerrorhandler::NewHandler()
#endif
{
  const char* Msg = "Fatal Error: Memory depleted.\n"
		    "Get more RAM and hard disk space.";
#ifdef _WIN32
  ShowWindow(GetActiveWindow(), SW_HIDE);
  MessageBox(NULL, Msg, "Program aborted!", MB_OK|MB_ICONEXCLAMATION);
#endif
#ifdef __unix__
  std::cout << Msg << std::endl;
#endif

  exit(1);

#ifdef _MSC_VER
  return 0;
#endif
}

#ifdef __DJGPP__

void globalerrorhandler::SignalHandler(int Signal)
{
  static truth AlreadySignalled = false;

  if(!AlreadySignalled)
  {
    AlreadySignalled = true;
    graphics::DeInit();
    std::cout << "Fatal Error: ";

    switch (Signal)
    {
     case SIGABRT:
      std::cout << "Abort";
      break;
     case SIGFPE:
      std::cout << "Divide by zero";
      break;
     case SIGILL:
      std::cout << "Invalid/unknown";
      break;
     case SIGSEGV:
      std::cout << "Segmentation violation";
      break;
     case SIGTERM:
      std::cout << "Termination request";
      break;
     case SIGINT:
      std::cout << "Break interrupt";
      break;
     case SIGKILL:
      std::cout << "Kill";
      break;
     case SIGQUIT:
      std::cout << "Quit";
      break;
     default:
      std::cout << "Unknown";
    }

    std::cout << " exception signalled.";

    if(Signal != SIGINT)
      std::cout << BugMsg;

    std::cout << std::endl;
  }

  exit(2);
}

#endif
