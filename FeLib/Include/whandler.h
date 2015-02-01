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

#ifndef __WHANDLER_H__
#define __WHANDLER_H__

#include <vector>
#include "SDL.h"

#include "felibdef.h"

#define GET_KEY globalwindowhandler::GetKey
#define READ_KEY globalwindowhandler::ReadKey
#define GET_TICK globalwindowhandler::GetTick

class globalwindowhandler
{
public:
  static int GetKey(bool = true);
  static int ReadKey();

  static void InstallControlLoop(bool (*)());
  static void DeInstallControlLoop(bool (*)());
  static ulong GetTick() { return Tick; }
  static bool ControlLoopsInstalled() { return Controls; }
  static void EnableControlLoops() { ControlLoopsEnabled = true; }
  static void DisableControlLoops() { ControlLoopsEnabled = false; }
  static void Init();
  static void SetQuitMessageHandler(bool (*What)()) { QuitMessageHandler = What; }
  static void UpdateTick() { Tick = SDL_GetTicks() / 40; }

private:
  static void ProcessEvent(const SDL_Event&);
  static void ProcessWindowEvent(const SDL_WindowEvent& );
  static void ProcessQuitEvent(const SDL_QuitEvent& );
  static void ProcessKeyEvent(const SDL_KeyboardEvent &);

  static std::vector<int> KeyBuffer;
  static bool (*QuitMessageHandler)();
  static bool (*ControlLoop[MAX_CONTROLS])();
  static int Controls;
  static ulong Tick;
  static bool ControlLoopsEnabled;
};

#endif
