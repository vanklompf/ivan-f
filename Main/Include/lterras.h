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

#ifndef __LTERRAS_H__
#define __LTERRAS_H__

#include "lterra.h"

OLTERRAIN(wall, olterrain)
{
};

OLTERRAIN(decoration, olterrain)
{
};

GLTERRAIN(solidterrain, glterrain)
{
};

OLTERRAIN(door, olterrain)
{
 public:
  virtual bool Open(character*);
  virtual bool Close(character*);
  virtual bool CanBeOpened() const { return !Opened; }
  virtual void BeKicked(character*, int, int);
  virtual void SetIsOpened(bool What) { Opened = What; }
  virtual void Save(outputfile&) const;
  virtual void Load(inputfile&);
  virtual bool IsDoor() const { return true; }
  virtual void SetIsLocked(bool What) { Locked = What; }
  virtual bool IsLocked() const { return Locked; }
  virtual bool CanBeOpenedByAI();
  virtual void ReceiveDamage(character*, int, int);
  virtual void CreateBoobyTrap();
  virtual void ActivateBoobyTrap();
  virtual bool TryKey(item*, character*);
  virtual void SetParameters(int);
  virtual void Lock() { SetIsLocked(true); }
  virtual void HasBeenHitByItem(character*, item*, int);
  virtual bool IsTransparent() const;
  virtual int GetWalkability() const;
  virtual int GetTheoreticalWalkability() const;
  virtual void BeDestroyed();
 protected:
  virtual void PostConstruct();
  virtual bool AddAdjective(festring&, bool) const;
  virtual void Break();
  virtual v2 GetBitmapPos(int) const;
  virtual void MakeWalkable();
  virtual void MakeNotWalkable();
  virtual int GetBoobyTrap() { return BoobyTrap; }
  virtual void SetBoobyTrap(int What) { BoobyTrap = What; }
  bool Opened;
  bool Locked;
  int BoobyTrap;
};

OLTERRAIN(stairs, olterrain)
{
 public:
  virtual void Save(outputfile&) const;
  virtual void Load(inputfile&);
  virtual bool Enter(bool) const;
  virtual void StepOn(character*);
  virtual void SetAttachedArea(int What) { AttachedArea = What; }
  virtual void SetAttachedEntry(int What) { AttachedEntry = What; }
  int GetAttachedArea() const { return AttachedArea; }
  int GetAttachedEntry() const { return AttachedEntry; }
 protected:
  virtual void PostConstruct();
  int AttachedArea;
  int AttachedEntry;
};

OLTERRAIN(portal, stairs)
{
 protected:
  virtual int GetClassAnimationFrames() const { return 32; }
  virtual v2 GetBitmapPos(int) const;
};

OLTERRAIN(altar, olterrain)
{
 public:
  virtual bool AcceptsOffers() const { return true; }
  virtual void StepOn(character*);
  virtual void BeKicked(character*, int, int);
  virtual bool ReceiveVomit(character*, liquid*);
  virtual bool Polymorph(character*);
  virtual bool SitOn(character*);
  virtual void Draw(blitdata&) const;
  virtual bool VomitingIsDangerous(const character*) const;
};

OLTERRAIN(throne, decoration)
{
 public:
  virtual bool SitOn(character*);
};

OLTERRAIN(olterraincontainer, olterrain)
{
 public:
  olterraincontainer();
  virtual ~olterraincontainer();
  virtual bool Open(character*);
  virtual bool CanBeOpened() const { return true; }
  virtual stack* GetContained() const { return Contained; }
  virtual void Load(inputfile&);
  virtual void Save(outputfile&) const;
  virtual void SetItemsInside(const fearray<contentscript<item> >&, int);
  virtual void Break();
  virtual bool AllowContentEmitation() const { return false; }
  virtual void PreProcessForBone();
  virtual void PostProcessForBone();
  virtual void FinalProcessForBone();
 protected:
  stack* Contained;
};

OLTERRAIN(fountain, olterrain)
{
 public:
  virtual ~fountain();
  virtual bool SitOn(character*);
  virtual bool Drink(character*);
  virtual bool HasDrinkEffect() const { return true; }
  virtual void DryOut();
  virtual bool DipInto(item*, character*);
  virtual bool IsDipDestination() const;
  virtual material* GetSecondaryMaterial() const { return SecondaryMaterial; }
  virtual void SetSecondaryMaterial(material*, int = 0);
  virtual void ChangeSecondaryMaterial(material*, int = 0);
  void InitMaterials(material*, material*, bool = true);
  virtual void Save(outputfile&) const;
  virtual void Load(inputfile&);
  virtual int GetMaterials() const { return 2; }
  virtual material* GetMaterial(int) const;
  virtual void InitMaterials(const materialscript*, const materialscript*, bool);
  virtual bool IsFountainWithWater() const;
  virtual int GetSparkleFlags() const;
 protected:
  virtual void GenerateMaterials();
  virtual col16 GetMaterialColorB(int) const;
  virtual void AddPostFix(festring& String) const { AddContainerPostFix(String); }
  virtual bool AddAdjective(festring&, bool) const;
  virtual v2 GetBitmapPos(int) const;
  material* SecondaryMaterial;
};

OLTERRAIN(brokendoor, door)
{
 public:
  virtual void BeKicked(character*, int, int);
  virtual void ReceiveDamage(character*, int, int);
  virtual void HasBeenHitByItem(character*, item*, int);
  virtual void Break() { olterrain::Break(); }
};

GLTERRAIN(liquidterrain, glterrain)
{
 public:
  virtual const char* SurviveMessage() const;
  virtual const char* MonsterSurviveMessage() const;
  virtual const char* DeathMessage() const;
  virtual const char* MonsterDeathVerb() const;
  virtual const char* ScoreEntry() const;
  virtual bool IsFatalToStay() const { return true; }
  virtual bool DipInto(item*, character*);
  virtual bool IsDipDestination() const { return true; }
  virtual void SurviveEffect(character*);
  virtual void AddLocationDescription(festring&) const;
 protected:
  virtual void AddPostFix(festring& String) const { AddLumpyPostFix(String); }
  virtual int GetClassAnimationFrames() const { return 32; }
  virtual v2 GetBitmapPos(int) const;
};

OLTERRAIN(boulder, olterrain)
{
};

OLTERRAIN(sign, olterrain)
{
 public:
  virtual void Save(outputfile&) const;
  virtual void Load(inputfile&);
  virtual void SetText(const festring& What) { Text = What; }
  virtual festring GetText() const;
  virtual void AddPostFix(festring&) const;
  virtual void StepOn(character*);
 protected:
  festring Text;
};

OLTERRAIN(earth, olterrain)
{
 public:
  virtual void Save(outputfile&) const;
  virtual void Load(inputfile&);
 protected:
  virtual void PostConstruct();
  virtual v2 GetBitmapPos(int) const;
  int PictureIndex;
};

OLTERRAIN(monsterportal, olterrain)
{
 public:
  monsterportal();
 protected:
  virtual int GetClassAnimationFrames() const { return 32; }
  virtual v2 GetBitmapPos(int) const;
};

#endif
