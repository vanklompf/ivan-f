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

#ifndef __MISCITEM_H__
#define __MISCITEM_H__

#include <set>

#include "item.h"
#include "game.h" /// check
#include "trap.h"

ITEM(materialcontainer, item)
{
 public:
  materialcontainer() { }
  materialcontainer(const materialcontainer&);
  virtual ~materialcontainer();
  virtual material* GetSecondaryMaterial() const { return SecondaryMaterial; }
  virtual void SetSecondaryMaterial(material*, int = 0);
  virtual void ChangeSecondaryMaterial(material*, int = 0);
  void InitMaterials(material*, material*, bool = true);
  virtual void Save(outputfile&) const;
  virtual void Load(inputfile&);
  virtual int GetMaterials() const { return 2; }
  virtual void SignalSpoil(material*);
  virtual bool CanBePiledWith(const item*, const character*) const;
  virtual void Be();
  virtual int GetSpoilLevel() const;
  virtual material* GetMaterial(int) const;
  virtual int GetAttachedGod() const;
  virtual material* GetConsumeMaterial(const character*, materialpredicate = TrueMaterialPredicate) const;
  virtual material* RemoveMaterial(material*);
  material* RemoveMainMaterial();
  virtual material* RemoveSecondaryMaterial();
  virtual void CalculateEmitation();
  virtual void InitMaterials(const materialscript*, const materialscript*, bool);
  virtual int GetSparkleFlags() const;
 protected:
  virtual long GetMaterialPrice() const;
  virtual bool CalculateHasBe() const;
  virtual void GenerateMaterials();
  virtual col16 GetMaterialColorB(int) const;
  virtual alpha GetAlphaB(int) const;
  virtual int GetRustDataB() const;
  material* SecondaryMaterial;
};

ITEM(banana, materialcontainer)
{
 public:
  banana() : TimesUsed(0), Charges(6) { }
  virtual bool Zap(character*, v2, int);
  virtual void Save(outputfile&) const;
  virtual void Load(inputfile&);
  virtual void ChargeFully(character*) { TimesUsed = 0; }
  virtual bool IsZappable(const character*) const { return true; }
  virtual bool IsChargeable(const character*) const { return true; }
  virtual void SignalSpoil(material*);
  virtual bool IsBanana() const { return true; }
  virtual material* RemoveSecondaryMaterial();
 protected:
  int TimesUsed;
  int Charges;
};

ITEM(holybanana, banana)
{
 public:
  virtual bool HitEffect(character*, character*, v2, int, int, bool);
  virtual bool Zap(character*, v2, int);
  virtual void Be() { }
  virtual int GetSpecialFlags() const;
  virtual void AddInventoryEntry(const character*, festring&, int, bool) const;
  virtual bool ReceiveDamage(character*, int, int, int);
};

ITEM(lantern, item)
{
 public:
  virtual void SignalSquarePositionChange(int);
  virtual bool AllowAlphaEverywhere() const { return true; }
  virtual int GetSpecialFlags() const;
  virtual bool IsLanternOnWall() const { return GetSquarePosition() != CENTER; }
 protected:
  virtual int GetClassAnimationFrames() const { return !IsBroken() ? 32 : 1; }
  virtual col16 GetMaterialColorA(int) const;
  virtual col16 GetMaterialColorB(int) const;
  virtual col16 GetMaterialColorC(int) const;
  virtual col16 GetMaterialColorD(int) const;
  virtual alpha GetAlphaA(int) const { return 255; }
  virtual alpha GetAlphaB(int) const;
  virtual alpha GetAlphaC(int) const;
  virtual alpha GetAlphaD(int) const;
  virtual v2 GetBitmapPos(int) const;
};

ITEM(can, materialcontainer)
{
 public:
  virtual item* BetterVersion() const;
  virtual void DipInto(liquid*, character*);
  virtual bool IsDippable(const character*) const { return !SecondaryMaterial; }
  virtual bool IsDipDestination(const character*) const;
  virtual liquid* CreateDipLiquid();
  virtual bool AllowSpoil() const { return false; } // temporary
  virtual bool WillSpoil() const { return false; } // temporary
  virtual bool HasBetterVersion() const { return !SecondaryMaterial; }
 protected:
  virtual void AddPostFix(festring& String) const { AddContainerPostFix(String); }
  virtual bool AddAdjective(festring&, bool) const;
  virtual v2 GetBitmapPos(int) const;
};

ITEM(lump, item)
{
 protected:
  virtual void AddPostFix(festring& String) const { AddLumpyPostFix(String); }
  virtual bool ShowMaterial() const { return false; }
  virtual bool WeightIsIrrelevant() const { return true; }
};

ITEM(potion, materialcontainer)
{
 public:
  virtual item* BetterVersion() const;
  virtual void DipInto(liquid*, character*);
  virtual liquid* CreateDipLiquid();
  virtual bool IsDippable(const character*) const { return !SecondaryMaterial; }
  virtual void Break(character*, int);
  virtual bool IsDipDestination(const character*) const;
  virtual bool IsExplosive() const;
  virtual bool ReceiveDamage(character*, int, int, int);
  virtual bool HasBetterVersion() const { return !SecondaryMaterial; }
  virtual bool EffectIsGood() const;
  virtual bool IsKamikazeWeapon(const character*) const { return IsExplosive(); }
 protected:
  virtual void AddPostFix(festring& String) const { AddContainerPostFix(String); }
  virtual bool AddAdjective(festring&, bool) const;
};

ITEM(bananapeels, item)
{
 public:
  virtual item* BetterVersion() const;
  virtual bool HasBetterVersion() const { return true; }
  virtual void StepOnEffect(character*);
  virtual bool IsBananaPeel() const { return true; }
  virtual bool IsDangerous(const character*) const;
  virtual bool RaiseTheDead(character*);
};

ITEM(brokenbottle, item)
{
 public:
  virtual bool IsBroken() const { return true; }
  virtual item* BetterVersion() const;
  virtual bool HasBetterVersion() const { return true; }
  virtual void StepOnEffect(character*);
  virtual item* Fix();
  virtual bool IsDangerous(const character*) const;
};

ITEM(scroll, item)
{
 public:
  virtual bool CanBeRead(character*) const;
  virtual bool IsReadable(const character*) const { return true; }
  virtual bool ReceiveDamage(character*, int, int, int);
};

ITEM(scrollofteleportation, scroll)
{
 public:
  virtual void FinishReading(character*);
};

ITEM(scrollofcharging, scroll)
{
 public:
  virtual void FinishReading(character*);
};

ITEM(nut, item)
{
};

ITEM(leftnutofpetrus, nut)
{
 public:
  virtual void Be() { }
  virtual bool IsPetrussNut() const { return true; }
  virtual bool IsConsumable() const { return false; }
};

ITEM(bone, item)
{
 public:
  virtual bool DogWillCatchAndConsume(const character*) const;
};

ITEM(loaf, item)
{
 protected:
  virtual void AddPostFix(festring& String) const { AddLumpyPostFix(String); }
  virtual bool ShowMaterial() const { return false; }
};

ITEM(scrollofwishing, scroll)
{
 public:
  virtual void FinishReading(character*);
};

ITEM(copyofleftnutofpetrus, nut)
{
};

ITEM(wand, item)
{
 public:
  virtual bool Apply(character*);
  virtual void Save(outputfile&) const;
  virtual void Load(inputfile&);
  virtual void ChargeFully(character*) { TimesUsed = 0; }
  virtual bool IsAppliable(const character*) const { return true; }
  virtual bool IsZappable(const character*) const { return true; }
  virtual bool IsChargeable(const character*) const { return true; }
  virtual bool ReceiveDamage(character*, int, int, int);
  virtual bool Zap(character*, v2, int);
  virtual void AddInventoryEntry(const character*, festring&, int, bool) const;
  virtual long GetPrice() const;
  virtual bool IsExplosive() const { return true; }
 protected:
  virtual void PostConstruct();
  void BreakEffect(character*, const festring&);
  ulong GetSpecialParameters() const;
  int Charges;
  int TimesUsed;
};

ITEM(scrollofchangematerial, scroll)
{
 public:
  virtual void FinishReading(character*);
};

ITEM(avatarofvalpurus, item)
{
 public:
  virtual void Be() { }
  virtual bool IsTheAvatar() const { return true; }
  virtual bool IsConsumable() const { return false; }
};

ITEM(kiwi, item)
{
};

ITEM(pineapple, item)
{
};

ITEM(palmbranch, item)
{
 public:
  virtual bool IsShield(const character*) const { return true; }
};

ITEM(backpack, materialcontainer)
{
 public:
  virtual bool Apply(character*);
  virtual bool IsAppliable(const character*) const { return true; }
  virtual bool ReceiveDamage(character*, int, int, int);
  virtual bool IsExplosive() const;
  virtual long GetTotalExplosivePower() const;
  virtual void SpillFluid(character*, liquid*, int = 0);
 protected:
  virtual void AddPostFix(festring& String) const { AddContainerPostFix(String); }
};

ITEM(holybook, item)
{
 public:
  virtual bool CanBeRead(character*) const;
  virtual bool IsReadable(const character*) const { return true; }
  virtual bool ReceiveDamage(character*, int, int, int);
  virtual void FinishReading(character*);
 protected:
  virtual col16 GetMaterialColorA(int) const;
  virtual bool ShowMaterial() const { return false; }
};

ITEM(fiftymillionroubles, item)
{
};

ITEM(oillamp, item)
{
 public:
  oillamp();
  oillamp(const oillamp&);
  virtual void Save(outputfile&) const;
  virtual void Load(inputfile&);
  virtual bool GetInhabitedByGenie() const { return InhabitedByGenie; }
  virtual void SetInhabitedByGenie(bool What) { InhabitedByGenie = What; }
  virtual bool Apply(character*);
  virtual bool IsAppliable(const character*) const { return true; }
 protected:
  bool InhabitedByGenie;
};

ITEM(stone, item)
{
 public:
  virtual long GetTruePrice() const;
 protected:
  virtual bool WeightIsIrrelevant() const { return true; }
};

ITEM(scrolloftaming, scroll)
{
 public:
  virtual void FinishReading(character*);
};

ITEM(mine, materialcontainer)
{
 public:
  mine() : Active(false) { }
  virtual void Save(outputfile&) const;
  virtual void Load(inputfile&);
  virtual void StepOnEffect(character*);
  virtual bool ReceiveDamage(character*, int, int, int);
  virtual bool IsActive() const { return Active; }
  virtual void SetIsActive(bool);
  virtual bool CanBeSeenBy(const character*) const;
  virtual bool Apply(character* User);
  virtual bool IsAppliable(const character*) const { return true; }
  virtual bool IsDangerous(const character* Stepper) const { return WillExplode(Stepper); }
  virtual bool WillExplode(const character*) const;
  virtual int GetTeam() const { return Team; }
  virtual void SetTeam(int What) { Team = What; }
  virtual bool CheckPickUpEffect(character*);
  virtual void Search(const character*, int);
  virtual bool NeedDangerSymbol() const { return IsActive(); }
  virtual void FinalProcessForBone();
  virtual void TeleportRandomly();
 protected:
  virtual bool AddAdjective(festring&, bool) const;
  bool Active;
  int Team;
  std::set<int> DiscoveredByTeam;
};

ITEM(key, item)
{
 public:
  virtual bool Apply(character*);
  virtual bool IsAppliable(const character*) const { return true; }
  virtual bool CanOpenDoors() const { return true; }
  virtual bool CanOpenLockType(int AnotherLockType) const { return GetConfig() == AnotherLockType; }
};

ITEM(headofelpuri, item) // can't wear equipment, so not "head"
{
 public:
  virtual bool IsHeadOfElpuri() const { return true; }
  virtual bool IsConsumable() const { return false; }
  virtual void Be() { }
};

ITEM(whistle, item)
{
 public:
  virtual bool Apply(character*);
  virtual bool IsAppliable(const character*) const { return true; }
  virtual void BlowEffect(character*);
 protected:
  virtual col16 GetMaterialColorB(int) const;
};

ITEM(magicalwhistle, whistle)
{
 public:
  magicalwhistle() : LastUsed(0) { }
  virtual void BlowEffect(character*);
  virtual void Load(inputfile&);
  virtual void Save(outputfile&) const;
  virtual void FinalProcessForBone();
 protected:
  ulong LastUsed;
};

ITEM(itemcontainer, item)
{
 public:
  itemcontainer();
  itemcontainer(const itemcontainer&);
  virtual ~itemcontainer();
  virtual bool Open(character*);
  virtual bool IsOpenable(const character*) const { return true; }
  virtual bool TryKey(item*, character*);
  virtual bool HasLock(const character*) const { return true; }
  virtual void Lock() { Locked = true; }
  virtual bool IsLocked() const { return Locked; }
  virtual void SetIsLocked(bool What) { Locked = What; }
  virtual stack* GetContained() const { return Contained; }
  virtual void Load(inputfile&);
  virtual void Save(outputfile&) const;
  virtual bool Polymorph(character*, stack*);
  virtual void CalculateVolumeAndWeight();
  virtual bool ContentsCanBeSeenBy(const character*) const;
  virtual long GetTruePrice() const;
  virtual bool ReceiveDamage(character*, int, int, int);
  virtual void DrawContents(const character*);
  virtual bool Apply(character* Applier) { return Open(Applier); }
  virtual bool IsAppliable(const character*) const { return true; }
  virtual void SetItemsInside(const fearray<contentscript<item> >&, int);
  virtual bool AllowContentEmitation() const { return false; }
  virtual bool IsDestroyable(const character*) const;
  virtual int GetOfferValue(int) const;
  virtual void SortAllItems(const sortdata&) const;
  virtual void PreProcessForBone();
  virtual void PostProcessForBone();
  virtual void FinalProcessForBone();
  virtual material* RemoveMaterial(material*);
  virtual void SetLifeExpectancy(int, int);
  virtual void CalculateEnchantment();
  virtual int GetTeleportPriority() const;
  virtual void SetParameters(int);
  virtual void Disappear();
 protected:
  virtual col16 GetMaterialColorB(int) const;
  virtual void PostConstruct();
  stack* Contained;
  bool Locked;
};

ITEM(beartrap, item)
{
 public:
  beartrap();
  beartrap(const beartrap&);
  virtual ~beartrap();
  virtual void Load(inputfile&);
  virtual void Save(outputfile&) const;
  virtual void StepOnEffect(character*);
  virtual bool CheckPickUpEffect(character*);
  virtual bool IsPickable(character*) const;
  virtual bool IsActive() const { return Active; }
  virtual void SetIsActive(bool);
  virtual bool CanBeSeenBy(const character*) const;
  virtual bool Apply(character*);
  virtual v2 GetBitmapPos(int) const;
  virtual bool IsAppliable(const character*) const { return true; }
  virtual bool IsDangerous(const character*) const { return Active; }
  virtual int GetTeam() const { return Team; }
  virtual void SetTeam(int What) { Team = What; }
  virtual bool ReceiveDamage(character*, int, int, int);
  virtual void Search(const character*, int);
  virtual bool NeedDangerSymbol() const { return IsActive(); }
  virtual void Fly(character*, int, int);
  virtual void FinalProcessForBone();
  virtual void TeleportRandomly();
  virtual ulong GetTrapID() const { return TrapData.TrapID; }
  virtual ulong GetVictimID() const { return TrapData.VictimID; }
  virtual void UnStick() { TrapData.VictimID = 0; }
  virtual void UnStick(int I) { TrapData.BodyParts &= ~(1 << I); }
  virtual bool TryToUnStick(character*, v2);
  virtual void RemoveFromSlot();
  virtual int GetTrapType() const { return GetType() | ITEM_TRAP; }
  virtual void PreProcessForBone();
  virtual void PostProcessForBone();
  virtual void DonateSlotTo(item*);
 protected:
  virtual bool AddAdjective(festring&, bool) const;
  bool IsStuck() const { return TrapData.VictimID; }
  int GetBaseTrapDamage() const;
  int Team;
  std::set<int> DiscoveredByTeam;
  trapdata TrapData;
  bool Active;
};

ITEM(stethoscope, item)
{
 public:
  virtual bool Apply(character*);
  virtual bool IsAppliable(const character*) const { return true; };
};

ITEM(scrollofenchantweapon, scroll)
{
 public:
  virtual void FinishReading(character*);
};

ITEM(scrollofenchantarmor, scroll)
{
 public:
  virtual void FinishReading(character*);
};

ITEM(skull, item)
{
};

ITEM(scrollofrepair, scroll)
{
 public:
  virtual void FinishReading(character*);
};

ITEM(encryptedscroll, scroll)
{
 public:
  virtual void Be() { }
  virtual bool Read(character*);
  virtual bool ReceiveDamage(character*, int, int, int) { return false; }
  virtual bool IsEncryptedScroll() const { return true; }
};

ITEM(horn, item)
{
 public:
  horn() : LastUsed(0) { }
  virtual void Load(inputfile&);
  virtual void Save(outputfile&) const;
  virtual bool Apply(character*);
  virtual bool IsAppliable(const character*) const { return true; }
  virtual void FinalProcessForBone();
 protected:
  ulong LastUsed;
};

ITEM(carrot, item)
{
 public:
  virtual bool BunnyWillCatchAndConsume(const character*) const;
 protected:
  virtual col16 GetMaterialColorB(int) const;
};

ITEM(charmlyre, item)
{
 public:
  charmlyre();
  virtual bool Apply(character*);
  virtual bool IsAppliable(const character*) const { return true; }
  virtual void Load(inputfile&);
  virtual void Save(outputfile&) const;
  virtual void FinalProcessForBone();
 protected:
  virtual col16 GetMaterialColorB(int) const;
  ulong LastUsed;
};

ITEM(scrollofdetectmaterial, scroll)
{
 public:
  virtual void FinishReading(character*);
};

ITEM(stick, item)
{
 protected:
  virtual void AddPostFix(festring& String) const { AddLumpyPostFix(String); }
  virtual bool ShowMaterial() const { return false; }
  virtual bool WeightIsIrrelevant() const { return true; }
};

ITEM(scrollofhardenmaterial, scroll)
{
 public:
  virtual void FinishReading(character*);
};

ITEM(scrollofgolemcreation, scroll)
{
 public:
  virtual void FinishReading(character*);
};

#endif
