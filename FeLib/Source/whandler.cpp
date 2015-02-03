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
#include "whandler.h"
#include "graphics.h"
#include "error.h"
#include "bitmap.h"
#include "festring.h"



bool (*globalwindowhandler::ControlLoop[MAX_CONTROLS])();
int globalwindowhandler::Controls = 0;
ulong globalwindowhandler::Tick;
bool globalwindowhandler::ControlLoopsEnabled = true;

void globalwindowhandler::InstallControlLoop(bool (*What)())
{
  if(Controls == MAX_CONTROLS)
    ABORT("Animation control frenzy!");

  ControlLoop[Controls++] = What;
}

void globalwindowhandler::DeInstallControlLoop(bool (*What)())
{
  int c;

  for(c = 0; c < Controls; ++c)
    if(ControlLoop[c] == What)
      break;

  if(c != Controls)
  {
    --Controls;

    for(; c < Controls; ++c)
      ControlLoop[c] = ControlLoop[c + 1];
  }
}

#include <algorithm>

std::vector<int> globalwindowhandler::KeyBuffer;
bool (*globalwindowhandler::QuitMessageHandler)() = 0;

void globalwindowhandler::Init()
{
  //SDL_EnableUNICODE(1);
  //SDL_EnableKeyRepeat(500, 30);
}

int globalwindowhandler::GetKey(bool EmptyBuffer)
{
  SDL_Event Event;

  if (EmptyBuffer)
  {
    while (SDL_PollEvent(&Event))
    {
      ProcessEvent(Event);
    }

    KeyBuffer.clear();
  }

  while (1)
  {
    if (!KeyBuffer.empty())
    {
      int Key = KeyBuffer[0];
      KeyBuffer.erase(KeyBuffer.begin());

      if (Key > 0xE000)
        return Key - 0xE000;

      if (Key && Key < 0x81)
        return Key;
    }
    else
    {
      if (SDL_PollEvent(&Event))
      {
        ProcessEvent(Event);
      }
      else
      {
        if (graphics::IsActive() && Controls && ControlLoopsEnabled)
        // if (SDL_GetAppState() & SDL_APPACTIVE && Controls && ControlLoopsEnabled)
        {
          static ulong LastTick = 0;
          UpdateTick();

          if (LastTick != Tick)
          {
            LastTick = Tick;
            bool Draw = false;

            for (int c = 0; c < Controls; ++c)
              if (ControlLoop[c]())
                Draw = true;

            if (Draw)
              graphics::BlitDBToScreen();
          }

          SDL_Delay(10);
        }
        else
        {
          SDL_WaitEvent(&Event);
          ProcessEvent(Event);
        }
      }
    }
  }
}

int globalwindowhandler::ReadKey()
{
  SDL_Event Event;

  if (graphics::IsActive())
  {
    while (SDL_PollEvent(&Event))
      ProcessEvent(Event);
  }
  else
  {
    SDL_WaitEvent(&Event);
    ProcessEvent(Event);
  }

  return KeyBuffer.size() ? GetKey(false) : 0;
}

void globalwindowhandler::ProcessWindowEvent(const SDL_WindowEvent& event)
{
  switch (event.type)
  {
    case SDL_WINDOWEVENT_EXPOSED:
      graphics::BlitDBToScreen();
      break;
    default:
      break;
  }
}

void globalwindowhandler::ProcessQuitEvent(const SDL_QuitEvent& event)
{
  if (!QuitMessageHandler || QuitMessageHandler())
  {
    exit(0);
  }
}

void globalwindowhandler::ProcessKeyEvent(const SDL_KeyboardEvent& event)
{
  if (event.type == SDL_KEYDOWN)
  {
    int KeyPressed;

    switch (event.keysym.sym)
    {
      case SDLK_RETURN:
      case SDLK_KP_ENTER:
        if (event.keysym.mod & KMOD_ALT)
        {
          graphics::SwitchMode();
          return;
        }
        else
        {
          KeyPressed = KEY_ENTER; // Event->key.keysym.unicode;
        }

        break;
      case SDLK_DOWN:
      case SDLK_KP_2:
        KeyPressed = KEY_DOWN + 0xE000;
        break; 
      case SDLK_UP:
      case SDLK_KP_8:
        KeyPressed = KEY_UP + 0xE000;
        break;
      case SDLK_RIGHT:
      case SDLK_KP_6:
        KeyPressed = KEY_RIGHT + 0xE000;
        break;
      case SDLK_LEFT:
      case SDLK_KP_4:
        KeyPressed = KEY_LEFT + 0xE000;
        break;
      case SDLK_HOME:
      case SDLK_KP_7:
        KeyPressed = KEY_HOME + 0xE000;
        break;
      case SDLK_END:
      case SDLK_KP_1:
        KeyPressed = KEY_END + 0xE000;
        break;
      case SDLK_PAGEUP:
      case SDLK_KP_9:
        KeyPressed = KEY_PAGE_UP + 0xE000;
        break;
      case SDLK_KP_3:
      case SDLK_PAGEDOWN:
        KeyPressed = KEY_PAGE_DOWN + 0xE000;
        break;
      case SDLK_KP_5:
        KeyPressed = '.';
        break;
      case SDLK_SYSREQ:
      case SDLK_PRINTSCREEN:
#ifdef WIN32
        DOUBLE_BUFFER->Save("Scrshot.bmp");
#else
        DOUBLE_BUFFER->Save(festring(getenv("HOME")) + "/Scrshot.bmp");
#endif
        return;
      case SDLK_e:
        if (event.keysym.mod & KMOD_ALT &&
            (event.keysym.mod & KMOD_LCTRL || event.keysym.mod & KMOD_RCTRL))
        {
          KeyPressed = '\177';
        }
		else
		{
			KeyPressed = 'e';
		}
		break;
      default:
          return;
    }

    if (std::find(KeyBuffer.begin(), KeyBuffer.end(), KeyPressed) == KeyBuffer.end())
      KeyBuffer.push_back(KeyPressed);
  }
}

void globalwindowhandler::ProcessEvent(const SDL_Event& event)
{
  switch (event.type)
  {
    case SDL_WINDOWEVENT:
      ProcessWindowEvent(event.window);
      break;
    case SDL_QUIT:
      ProcessQuitEvent(event.quit);
      return;
    case SDL_KEYDOWN:
    case SDL_KEYUP:
      ProcessKeyEvent(event.key);
      break;
    default:
      break;
  }
}
