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

#ifndef __MATERIAS_H__
#define __MATERIAS_H__

#include "materia.h"

class lterrain;

MATERIAL(solid, material)
{
};

MATERIAL(organic, solid)
{
 public:
  virtual void Be();
  virtual bool HasBe() const { return true; }
  virtual void Save(outputfile&) const;
  virtual void Load(inputfile&);
  virtual bool IsVeryCloseToSpoiling() const { return SpoilLevel == 8; }
  virtual int GetSpoilLevel() const { return SpoilLevel; }
  virtual void ResetSpoiling();
  virtual material* EatEffect(character*, long);
  virtual void AddConsumeEndMessage(character*) const;
  virtual void SetSpoilCounter(int);
  virtual bool CanSpoil() const { return true; }
  virtual int GetSpoilPercentage() const;
  virtual bool Spoils() const { return true; }
 protected:
  virtual void PostConstruct();
  ushort SpoilCounter;
  uchar SpoilCheckCounter;
  uchar SpoilLevel;
};

MATERIAL(gas, material)
{
};

MATERIAL(liquid, material)
{
 public:
  virtual const char* GetConsumeVerb() const;
  virtual bool IsLiquid() const { return true; }
  void TouchEffect(item*, const festring&);
  void TouchEffect(character*, int);
  void TouchEffect(lterrain*);
  liquid* SpawnMoreLiquid(long Volume_) const { return static_cast<liquid*>(SpawnMore(Volume_)); }
};

MATERIAL(flesh, organic)
{
 public:
  virtual void Save(outputfile&) const;
  virtual void Load(inputfile&);
  virtual col16 GetSkinColor() const { return SkinColor; }
  virtual void SetSkinColor(int What) { SkinColor = What; }
  virtual bool SkinColorIsSparkling() const { return SkinColorSparkling; }
  virtual void SetSkinColorIsSparkling(bool What) { SkinColorSparkling = What; }
  virtual bool IsFlesh() const { return true; }
  virtual void SetIsInfectedByLeprosy(bool What) { InfectedByLeprosy = What; }
  virtual bool IsInfectedByLeprosy() const { return InfectedByLeprosy; }
 protected:
  virtual void PostConstruct();
  col16 SkinColor;
  bool SkinColorSparkling;
  bool InfectedByLeprosy;
};

MATERIAL(powder, liquid)
{
 public:
  powder() : Wetness(0) { }
  virtual bool IsPowder() const { return true; }
  virtual bool IsExplosive() const;
  virtual void AddWetness(long What) { Wetness += What; }
  virtual void Be();
  virtual bool HasBe() const { return true; }
  virtual void Save(outputfile&) const;
  virtual void Load(inputfile&);
 protected:
  long Wetness;
};

/* Materials that can rust */

MATERIAL(ironalloy, solid)
{
 public:
  ironalloy() : RustData(NOT_RUSTED) { }
  virtual void SetRustLevel(int);
  virtual int GetStrengthValue() const;
  virtual int GetRustLevel() const { return RustData & 3; }
  virtual bool IsSparkling() const;
  virtual void Save(outputfile&) const;
  virtual void Load(inputfile&);
  virtual int GetRustData() const { return RustData; }
  virtual bool TryToRust(long, long = 0);
  virtual bool AddRustLevelDescription(festring&, bool) const;
 protected:
  int RustData;
};

#endif
