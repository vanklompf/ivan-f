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

#ifndef __WSQUARE_H__
#define __WSQUARE_H__

#include "square.h"
#include "worldmap.h"

class gwterrain;
class owterrain;
struct blitdata;

class wsquare : public square
{
 public:
  friend class worldmap;
  wsquare(worldmap*, v2);
  virtual ~wsquare();
  virtual void Save(outputfile&) const;
  virtual void Load(inputfile&);
  void Draw(blitdata&);
  void SetGWTerrain(gwterrain*);
  void SetOWTerrain(owterrain*);
  gwterrain* GetGWTerrain() const { return GWTerrain; }
  owterrain* GetOWTerrain() const { return OWTerrain; }
  void ChangeWTerrain(gwterrain*, owterrain*);
  worldmap* GetWorldMap() const { return static_cast<worldmap*>(AreaUnder); }
  void SetWorldMapUnder(worldmap* What) { AreaUnder = What; }
  void UpdateMemorizedDescription(bool = false);
  virtual gterrain* GetGTerrain() const;
  virtual oterrain* GetOTerrain() const;
  void ChangeGWTerrain(gwterrain*);
  void ChangeOWTerrain(owterrain*);
  void SetWTerrain(gwterrain*, owterrain*);
  bool SignalSeen();
  void CalculateLuminance();
  wsquare* GetNeighbourWSquare(int I) const { return static_cast<worldmap*>(AreaUnder)->GetNeighbourWSquare(Pos, I); }
  int GetWalkability() const;
  virtual int GetSquareWalkability() const { return GetWalkability(); }
  virtual bool CanBeSeenByPlayer(bool = false) const;
  virtual bool CanBeSeenFrom(v2, long, bool = false) const;
 protected:
  gwterrain* GWTerrain;
  owterrain* OWTerrain;
};

#endif
