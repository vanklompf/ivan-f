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

#ifndef __GRAPHICS_H__
#define __GRAPHICS_H__

#include "v2.h"

#define DOUBLE_BUFFER graphics::GetDoubleBuffer()
#define RES graphics::GetRes()
#define FONT graphics::GetDefaultFont()

class bitmap;
class rawbitmap;
class festring;

struct SDL_Window;
struct SDL_Renderer;
struct SDL_Texture;

class graphics
{
public:
  friend class bitmap;
  static void Init();
  static void DeInit();
  static void SwitchMode();
  static void SetMode(const char*, const char*, v2, bool);
  static void BlitDBToScreen();
  static v2 GetRes() { return Res; }
  static bitmap* GetDoubleBuffer() { return s_doubleBuffer; }
  static void LoadDefaultFont(const festring&);
  static rawbitmap* GetDefaultFont() { return DefaultFont; }
  static void SetSwitchModeHandler(void (*What)()) { SwitchModeHandler = What; }

private:
  static SDL_Window* Screen;
  static SDL_Renderer* Renderer;
  static SDL_Texture* Texture;

  static void (*SwitchModeHandler)();
  static bitmap* s_doubleBuffer;
  static v2 Res;
  static int ColorDepth;
  static rawbitmap* DefaultFont;

public:
  static bool IsActive();
};

#endif
