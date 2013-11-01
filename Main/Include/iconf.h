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

#ifndef __ICONF_H__
#define __ICONF_H__

#include "config.h"
#include "v2.h"

class ivanconfig
{
 public:
  static const festring& GetDefaultName() { return DefaultName.Value; }
  static const festring& GetDefaultPetName() { return DefaultPetName.Value; }
  static long GetAutoSaveInterval() { return AutoSaveInterval.Value; }
  static long GetContrast() { return Contrast.Value; }
  static bool GetWarnAboutDanger() { return WarnAboutDanger.Value; }
  static bool GetAutoDropLeftOvers() { return AutoDropLeftOvers.Value; }
  static bool GetLookZoom() { return LookZoom.Value; }
  static bool GetUseAlternativeKeys() { return UseAlternativeKeys.Value; }
#ifndef __DJGPP__
  static bool GetFullScreenMode() { return FullScreenMode.Value; }
  static void SwitchModeHandler();
#else
  static bool GetFullScreenMode() { return true; }
#endif
  static long ApplyContrastTo(long);
  static void Save() { configsystem::Save(); }
  static void Load() { configsystem::Load(); }
  static void CalculateContrastLuminance();
  static col24 GetContrastLuminance() { return ContrastLuminance; }
  static void Initialize();
  static void Show();
 private:
  static v2 GetQuestionPos();
  static void AutoSaveIntervalDisplayer(const numberoption*, festring&);
  static void ContrastDisplayer(const numberoption*, festring&);
  static bool DefaultNameChangeInterface(stringoption*);
  static bool DefaultPetNameChangeInterface(stringoption*);
  static bool AutoSaveIntervalChangeInterface(numberoption*);
  static bool ContrastChangeInterface(numberoption*);
  static void AutoSaveIntervalChanger(numberoption*, long);
  static void ContrastChanger(numberoption*, long);
#ifndef __DJGPP__
  static void FullScreenModeChanger(truthoption*, bool);
#endif
  static void ContrastHandler(long);
  static void BackGroundDrawer();
  static stringoption DefaultName;
  static stringoption DefaultPetName;
  static numberoption AutoSaveInterval;
  static scrollbaroption Contrast;
  static truthoption WarnAboutDanger;
  static truthoption AutoDropLeftOvers;
  static truthoption LookZoom;
  static truthoption UseAlternativeKeys;
#ifndef __DJGPP__
  static truthoption FullScreenMode;
#endif
  static col24 ContrastLuminance;
};

inline long ivanconfig::ApplyContrastTo(long L)
{
  long C = Contrast.Value;

  if(C == 100)
    return L;
  else
    return MakeRGB24(41 * GetRed24(L) * C >> 12,
		     41 * GetGreen24(L) * C >> 12,
		     41 * GetBlue24(L) * C >> 12);
}

#endif
