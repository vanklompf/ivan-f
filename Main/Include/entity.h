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

#ifndef __ENTITY_H__
#define __ENTITY_H__

#include <list>

#include "felibdef.h"

#define EXISTS 1
#define HAS_BE 2
#define ENTITY_FLAGS 3

class square;
class material;
class character;
class festring;
struct v2;

class entity
{
 public:
  friend class pool;
  entity(int);
  entity(const entity&);
  virtual ~entity();
  virtual void Be() { }
  bool Exists() const { return Flags & EXISTS; }
  void SendToHell();
  bool IsEnabled() const { return Flags & HAS_BE; }
  void Enable();
  void Disable();
  virtual square* GetSquareUnderEntity(int = 0) const = 0;
  virtual void SignalVolumeAndWeightChange() { }
  col24 GetEmitation() const { return Emitation; }
  virtual void SignalEmitationIncrease(col24) { }
  virtual void SignalEmitationDecrease(col24) { }
  virtual bool ContentsCanBeSeenBy(const character*) const { return false; }
  virtual bool AllowSpoil() const { return false; }
  virtual void SignalSpoil(material*) { }
  virtual void SignalSpoilLevelChange(material*) { }
  virtual bool IsOnGround() const = 0;
  virtual bool AllowContentEmitation() const { return true; }
  virtual void SignalRustLevelChange() { }
  virtual material* RemoveMaterial(material*) { return 0; }
  virtual character* TryNecromancy(character*) { return 0; }
  virtual void SignalDisappearance() { }
  virtual void SpecialEatEffect(character*, int) { }
  virtual ulong GetTrapID() const { return 0; }
  virtual ulong GetVictimID() const { return 0; }
  virtual void AddTrapName(festring&, int) const { }
  virtual void UnStick() { }
  virtual void UnStick(int) { }
  virtual bool TryToUnStick(character*, v2);
  virtual int GetTrapType() const { return 0; }
  void AddFlags(ulong What) { Flags |= What; }
  void RemoveFlags(ulong What) { Flags &= ~What; }
  virtual bool IsStuckTo(const character*) const { return false; }
  virtual const character* FindCarrier() const { return 0; }
 protected:
  col24 Emitation;
  ulong Flags;
 private:
  entity* Last;
  entity* Next;
};

#endif
