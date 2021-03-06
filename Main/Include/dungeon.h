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

#ifndef __DUNGEON_H__
#define __DUNGEON_H__

#include "v2.h"

class level;
class outputfile;
class inputfile;
class dungeonscript;
class levelscript;
class festring;

class dungeon
{
 public:
  dungeon();
  dungeon(int);
  ~dungeon();
  bool PrepareLevel(int, bool = true);
  void SaveLevel(const festring&, int, bool = true);
  level* LoadLevel(const festring&, int);
  level* GetLevel(int I) const { return Level[I]; }
  int GetLevels() const;
  void Save(outputfile&) const;
  void Load(inputfile&);
  void SetIndex(int What) { Index = What; }
  int GetIndex() const { return Index; }
  const levelscript* GetLevelScript(int);
  v2 GetWorldMapPos() { return WorldMapPos; }
  void SetWorldMapPos(v2 What) { WorldMapPos = What; }
  festring GetLevelDescription(int);
  festring GetShortLevelDescription(int);
  level* LoadLevel(inputfile&, int);
  bool IsGenerated(int I) const { return Generated[I]; }
  void SetIsGenerated(int I, bool What) { Generated[I] = What; }
  int GetLevelTeleportDestination(int) const;
 private:
  void Initialize();
  const dungeonscript* DungeonScript;
  level** Level;
  int Index;
  bool* Generated;
  v2 WorldMapPos;
};

outputfile& operator<<(outputfile&, const dungeon*);
inputfile& operator>>(inputfile&, dungeon*&);

#endif
