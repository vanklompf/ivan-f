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

#ifndef __ROOM_H__
#define __ROOM_H__

#include "v2.h"

class room;
class item;
class olterrain;
class lsquare;
class festring;
class outputfile;
class inputfile;
class character;

typedef room* (*roomspawner)();

class roomprototype
{
 public:
  roomprototype(roomspawner, const char*);
  room* Spawn() const { return Spawner(); }
  room* SpawnAndLoad(inputfile&) const;
  const char* GetClassID() const { return ClassID; }
  int GetIndex() const { return Index; }
 private:
  int Index;
  roomspawner Spawner;
  const char* ClassID;
};

class room
{
 public:
  typedef roomprototype prototype;
  room() : LastMasterSearchTick(0), MasterID(0) { }
  virtual ~room() { }
  virtual void Save(outputfile&) const;
  virtual void Load(inputfile&);
  virtual void Enter(character*) { }
  v2 GetPos() const { return Pos; }
  void SetPos(v2 What) { Pos = What; }
  v2 GetSize() const { return Size; }
  void SetSize(v2 What) { Size = What; }
  void SetIndex(int What) { Index = What; }
  int GetIndex() const { return Index; }
  character* GetMaster() const;
  void SetMasterID(ulong What) { MasterID = What; }
  virtual bool PickupItem(character*, item*, int) { return true; }
  virtual bool DropItem(character*, item*, int) { return true; }
  int GetDivineMaster() const { return DivineMaster; }
  void SetDivineMaster(int What) { DivineMaster = What; }
  virtual void KickSquare(character*, lsquare*) { }
  virtual bool ConsumeItem(character*, item*, int) { return true; }
  virtual bool AllowDropGifts() const { return true; }
  virtual bool Drink(character*) const { return true; }
  virtual bool HasDrinkHandler() const { return false; }
  virtual bool Dip(character*) const { return true; }
  virtual bool HasDipHandler() const { return false; }
  virtual void TeleportSquare(character*, lsquare*) { }
  virtual const prototype* GetProtoType() const = 0;
  int GetType() const { return GetProtoType()->GetIndex(); }
  virtual void DestroyTerrain(character*);
  virtual bool AllowSpoil(const item*) const { return true; }
  virtual bool CheckDestroyTerrain(character*);
  virtual int GetGodRelationAdjustment() const { return -50; }
  virtual bool AllowKick(const character*, const lsquare*) const { return true; }
  bool MasterIsActive() const;
  bool CheckKickSquare(const character*, const lsquare*) const;
  virtual void HostileAction(character*) const { }
  virtual bool AllowAltarPolymorph() const { return true; }
  virtual bool AllowFoodSearch() const { return true; }
  virtual void ReceiveVomit(character*) { }
  virtual bool IsOKToDestroyWalls(const character*) const;
  virtual void AddItemEffect(item*) { };
  void FinalProcessForBone();
  void SetFlags(ulong What) { Flags = What; }
  bool DontGenerateMonsters() const { return Flags & NO_MONSTER_GENERATION; }
 protected:
  mutable character* Master;
  mutable ulong LastMasterSearchTick;
  v2 Pos;
  v2 Size;
  ulong MasterID;
  int Index;
  int DivineMaster;
  ulong Flags;
};

#ifdef __FILE_OF_STATIC_ROOM_PROTOTYPE_DEFINITIONS__
#define ROOM_PROTO(name)\
template<> const roomprototype\
  name##sysbase::ProtoType((roomspawner)(&name##sysbase::Spawn), #name);
#else
#define ROOM_PROTO(name)
#endif

#define ROOM(name, base)\
class name;\
typedef simplesysbase<name, base, roomprototype> name##sysbase;\
ROOM_PROTO(name)\
class name : public name##sysbase

#endif
