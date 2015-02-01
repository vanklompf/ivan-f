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
#include "SDL.h"

#include "graphics.h"
#include "bitmap.h"
#include "whandler.h"
#include "error.h"
#include "rawbit.h"

void (*graphics::SwitchModeHandler)();

SDL_Window* graphics::Screen;
SDL_Renderer* graphics::Renderer;
SDL_Texture* graphics::Texture;

bitmap* graphics::s_doubleBuffer;
v2 graphics::Res;
int graphics::ColorDepth;
rawbitmap* graphics::DefaultFont = 0;

void graphics::Init()
{
  static bool AlreadyInstalled = false;

  if(!AlreadyInstalled)
  {
    AlreadyInstalled = true;

    if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_NOPARACHUTE))
      ABORT("Can't initialize SDL.");

    atexit(graphics::DeInit);
  }
}

void graphics::DeInit()
{
  delete DefaultFont;
  DefaultFont = 0;

  SDL_Quit();
}

#ifdef USE_SDL

void graphics::SetMode(const char* Title, const char* IconName,
		       v2 NewRes, bool FullScreen)
{
  if(IconName)
  {
    SDL_Surface* Icon = SDL_LoadBMP(IconName);
	if (Icon == NULL)
	{
		ABORT("Could not load Icon file");
	}
    SDL_SetColorKey(Icon, SDL_TRUE, SDL_MapRGB(Icon->format, 255, 255, 255));
	SDL_SetWindowIcon(Screen, Icon);
  }

  ulong Flags = SDL_SWSURFACE;

  if(FullScreen)
  {
    SDL_ShowCursor(SDL_DISABLE);
    Flags |= SDL_WINDOW_FULLSCREEN;
  }

  Screen = SDL_CreateWindow(Title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, NewRes.X, NewRes.Y, Flags);

  Renderer = SDL_CreateRenderer(Screen, -1, 0);
  SDL_SetRenderDrawColor(Renderer, 0, 0, 0, 255);
  SDL_RenderClear(Renderer);
  SDL_RenderPresent(Renderer);

  Texture =
      SDL_CreateTexture(Renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, NewRes.X, NewRes.Y);

  if(!Screen)
    ABORT("Couldn't set video mode.");

  globalwindowhandler::Init();
  s_doubleBuffer = new bitmap(NewRes);
  Res = NewRes;
  ColorDepth = 16;
}

void graphics::BlitDBToScreen()
{
  /*if(SDL_MUSTLOCK(Screen) && SDL_LockSurface(Screen) < 0)
    ABORT("Can't lock screen");*/
	/*
  packcol16* SrcPtr = s_doubleBuffer->GetImage()[0];
  packcol16* DestPtr = static_cast<packcol16*>(Screen->pixels);
  ulong ScreenYMove = (Screen->pitch >> 1);
  ulong LineSize = Res.X << 1;

  for (int y = 0; y < Res.Y; ++y, SrcPtr += Res.X, DestPtr += ScreenYMove)
    memcpy(DestPtr, SrcPtr, LineSize);
	*/
  /* if (SDL_MUSTLOCK(Screen)) SDL_UnlockSurface(Screen); */


  SDL_UpdateTexture(Texture, NULL, s_doubleBuffer, Res.Y);
  SDL_RenderClear(Renderer);
  SDL_RenderCopy(Renderer, Texture, NULL, NULL);
  SDL_RenderPresent(Renderer);
  //SDL_UpdateRect(Screen, 0, 0, Res.X, Res.Y);
}

void graphics::SwitchMode()
{
  ulong Flags;

  if(SDL_GetWindowFlags(Screen) & SDL_WINDOW_FULLSCREEN)
  {
    SDL_ShowCursor(SDL_ENABLE);
    Flags = SDL_SWSURFACE;
  }
  else
  {
    SDL_ShowCursor(SDL_DISABLE);
    Flags = SDL_SWSURFACE| SDL_WINDOW_FULLSCREEN;
  }

  if(SwitchModeHandler)
    SwitchModeHandler();

  SDL_SetWindowFullscreen(Screen, Flags);

  if(!Screen)
    ABORT("Couldn't toggle fullscreen mode.");

  BlitDBToScreen();
}

#endif

void graphics::LoadDefaultFont(const festring& FileName)
{
  DefaultFont = new rawbitmap(FileName);
}

bool graphics::IsActive()
{
	return !(SDL_GetWindowFlags(graphics::Screen) & SDL_WINDOW_MINIMIZED);
}
