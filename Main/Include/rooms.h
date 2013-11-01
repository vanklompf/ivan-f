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

#ifndef __ROOMS_H__
#define __ROOMS_H__

#include "room.h"

ROOM(normalroom, room) { };

ROOM(shop, room)
{
 public:
  virtual void Enter(character*);
  virtual bool PickupItem(character*, item*, int);
  virtual bool DropItem(character*, item*, int);
  virtual void KickSquare(character*, lsquare*);
  virtual bool ConsumeItem(character*, item*, int);
  virtual bool AllowDropGifts() const { return false; }
  virtual void TeleportSquare(character*, lsquare*);
  virtual bool AllowSpoil(const item*) const;
  virtual bool AllowKick(const character*,const lsquare*) const;
  virtual void HostileAction(character*) const;
  virtual bool AllowFoodSearch() const { return false; }
  virtual void ReceiveVomit(character*);
};

ROOM(cathedral, room)
{
 public:
  cathedral();
  virtual void Enter(character*);
  virtual bool PickupItem(character*, item*, int);
  virtual bool DropItem(character*, item*, int);
  virtual void KickSquare(character*, lsquare*);
  virtual bool ConsumeItem(character*, item*, int);
  virtual void SetEntered(bool What) { Entered = What; }
  virtual void Save(outputfile&) const;
  virtual void Load(inputfile&);
  virtual bool AllowDropGifts() const { return false; }
  virtual bool Drink(character*) const;
  virtual bool HasDrinkHandler() const { return true; }
  virtual bool Dip(character*) const;
  virtual bool HasDipHandler() const { return true; }
  virtual void TeleportSquare(character*, lsquare*);
  virtual bool AllowSpoil(const item*) const { return false; }
  virtual int GetGodRelationAdjustment() const { return -150; }
  virtual bool AllowKick(const character*,const lsquare*) const;
  virtual void HostileAction(character*) const;
  virtual bool AllowAltarPolymorph() const { return false; }
  virtual bool AllowFoodSearch() const { return false; }
  virtual void AddItemEffect(item*);
  character* FindRandomExplosiveReceiver() const;
 protected:
  bool Entered;
};

ROOM(library, room)
{
 public:
  virtual void Enter(character*);
  virtual bool PickupItem(character*, item*, int);
  virtual bool DropItem(character*, item*, int);
  virtual void KickSquare(character*, lsquare*);
  virtual bool ConsumeItem(character*, item*, int);
  virtual bool AllowDropGifts() const { return false; }
  virtual void TeleportSquare(character*, lsquare*);
  virtual bool AllowKick(const character*, const lsquare*) const;
  virtual void HostileAction(character*) const;
};

ROOM(bananadroparea, room)
{
 public:
  virtual bool PickupItem(character*, item*, int);
  virtual bool DropItem(character*, item*, int);
  virtual void KickSquare(character*, lsquare*);
  virtual bool ConsumeItem(character*, item*, int);
  virtual bool AllowDropGifts() const { return false; }
  virtual void TeleportSquare(character*, lsquare*);
  virtual bool AllowKick(const character*, const lsquare*) const;
  virtual void HostileAction(character*) const;
};

ROOM(sumoarena, room)
{
 public:
  virtual void DestroyTerrain(character*);
  virtual void HostileAction(character*) const;
  virtual bool CheckDestroyTerrain(character*);
};

#endif
