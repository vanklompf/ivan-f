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

#ifndef __GEAR_H__
#define __GEAR_H__

#include "item.h"

ITEM(meleeweapon, item)
{
 public:
  meleeweapon() { }
  meleeweapon(const meleeweapon&);
  virtual ~meleeweapon();
  virtual bool HitEffect(character*, character*, v2, int, int, bool);
  virtual void DipInto(liquid*, character*);
  virtual long GetPrice() const;
  virtual bool IsDippable(const character*) const;
  virtual material* GetSecondaryMaterial() const { return SecondaryMaterial; }
  virtual void SetSecondaryMaterial(material*, int = 0);
  virtual void ChangeSecondaryMaterial(material*, int = 0);
  void InitMaterials(material*, material*, bool = true);
  virtual void Save(outputfile&) const;
  virtual void Load(inputfile&);
  virtual int GetMaterials() const { return 2; }
  virtual void AddInventoryEntry(const character*, festring&, int, bool) const;
  virtual void SignalSpoil(material*);
  virtual void Be();
  virtual bool IsWeapon(const character*) const { return true; }
  virtual int GetEnchantment() const { return Enchantment; }
  virtual void SetEnchantment(int);
  virtual void EditEnchantment(int);
  virtual int GetStrengthValue() const;
  virtual bool IsFixableBySmith(const character*) const { return IsBroken() || IsRusted(); }
  virtual bool IsFixableByTailor(const character*) const { return IsBroken(); }
  virtual double GetTHVBonus() const;
  virtual double GetDamageBonus() const;
  virtual int GetSpoilLevel() const;
  virtual material* GetMaterial(int) const;
  virtual void TryToRust(long);
  virtual material* GetConsumeMaterial(const character*, materialpredicate = TrueMaterialPredicate) const;
  virtual pixelpredicate GetFluidPixelAllowedPredicate() const;
  virtual material* RemoveMaterial(material*);
  material* RemoveMainMaterial();
  material* RemoveSecondaryMaterial();
  virtual v2 GetWieldedBitmapPos(int) const;
  virtual void CalculateEmitation();
  virtual void InitMaterials(const materialscript*, const materialscript*, bool);
  virtual item* Fix();
  virtual void CalculateEnchantment();
  virtual bool AllowFluids() const { return true; }
  virtual int GetSparkleFlags() const;
 protected:
  virtual long GetMaterialPrice() const;
  virtual bool CalculateHasBe() const;
  virtual void PostConstruct();
  virtual void AddPostFix(festring&) const;
  virtual void GenerateMaterials();
  virtual col16 GetMaterialColorB(int) const;
  virtual col16 GetMaterialColorC(int) const;
  virtual alpha GetAlphaB(int) const;
  virtual int GetRustDataB() const;
  virtual col16 GetDripColor() const;
  virtual bool AllowRegularColors() const;
  material* SecondaryMaterial;
  int Enchantment;
};

ITEM(justifier, meleeweapon)
{
 public:
  virtual bool AllowAlphaEverywhere() const { return true; }
 protected:
  virtual int GetClassAnimationFrames() const { return 32; }
  virtual col16 GetOutlineColor(int) const;
  virtual alpha GetOutlineAlpha(int) const;
};

ITEM(neercseulb, meleeweapon)
{
 public:
  virtual bool HitEffect(character*, character*, v2, int, int, bool);
  virtual bool AllowAlphaEverywhere() const { return true; }
 protected:
  virtual int GetClassAnimationFrames() const { return 32; }
  virtual col16 GetOutlineColor(int) const;
  virtual alpha GetOutlineAlpha(int) const;
};

ITEM(pickaxe, meleeweapon)
{
 public:
  virtual bool Apply(character*);
  virtual bool IsAppliable(const character*) const;
};

ITEM(whip, meleeweapon)
{
 public:
  virtual bool IsWhip() const { return true; }
 protected:
  virtual int GetFormModifier() const;
};

ITEM(flamingsword, meleeweapon)
{
 public:
  virtual bool HitEffect(character*, character*, v2, int, int, bool);
  virtual int GetSpecialFlags() const;
};

ITEM(mjolak, meleeweapon)
{
 public:
  virtual bool HitEffect(character*, character*, v2, int, int, bool);
};

ITEM(vermis, meleeweapon)
{
 public:
  virtual bool HitEffect(character*, character*, v2, int, int, bool);
};

ITEM(turox, meleeweapon)
{
 public:
  virtual bool HitEffect(character*, character*, v2, int, int, bool);
};

ITEM(whipofthievery, whip)
{
 public:
  virtual long GetPrice() const;
  virtual bool HitEffect(character*, character*, v2, int, int, bool);
 protected:
  virtual bool CleptiaHelps(const character*, const character*) const;
};

ITEM(gorovitshammer, meleeweapon)
{
 public:
  virtual bool IsGorovitsFamilyRelic() const { return true; }
  virtual bool AllowAlphaEverywhere() const { return true; }
 protected:
  virtual int GetClassAnimationFrames() const { return 32; }
  virtual col16 GetOutlineColor(int) const;
  virtual alpha GetOutlineAlpha(int) const;
};

ITEM(gorovitssickle, meleeweapon)
{
 public:
  virtual bool IsGorovitsFamilyRelic() const { return true; }
  virtual bool AllowAlphaEverywhere() const { return true; }
 protected:
  virtual int GetClassAnimationFrames() const { return 32; }
  virtual col16 GetOutlineColor(int) const;
  virtual alpha GetOutlineAlpha(int) const;
};

ITEM(thunderhammer, meleeweapon)
{
 public:
  virtual bool HitEffect(character*, character*, v2, int, int, bool);
  virtual int GetSpecialFlags() const;
  virtual bool ReceiveDamage(character*, int, int, int);
};

ITEM(saalthul, meleeweapon)
{
};

ITEM(armor, item)
{
 public:
  virtual long GetPrice() const;
  virtual void AddInventoryEntry(const character*, festring&, int, bool) const;
  virtual void Save(outputfile&) const;
  virtual void Load(inputfile&);
  virtual bool IsArmor(const character*) const { return true; }
  virtual int GetEnchantment() const { return Enchantment; }
  virtual void SetEnchantment(int);
  virtual void EditEnchantment(int);
  virtual int GetStrengthValue() const;
  virtual bool CanBePiledWith(const item*, const character*) const;
  virtual int GetInElasticityPenalty(int) const;
  virtual int GetCarryingBonus() const;
  virtual bool IsFixableBySmith(const character*) const { return IsBroken() || IsRusted(); }
  virtual bool IsFixableByTailor(const character*) const { return IsBroken(); }
  virtual bool AllowFluids() const { return true; }
  virtual void CalculateEnchantment();
  virtual double GetTHVBonus() const;
  virtual double GetDamageBonus() const;
 protected:
  virtual void AddPostFix(festring&) const;
  virtual void PostConstruct();
  int Enchantment;
};

ITEM(bodyarmor, armor)
{
 public:
  virtual long GetPrice() const;
  virtual bool IsBodyArmor(const character*) const { return true; }
  virtual bool IsInCorrectSlot(int) const;
 protected:
  virtual const char* GetBreakVerb() const;
  virtual bool AddAdjective(festring&, bool) const;
  virtual const festring& GetNameSingular() const;
};

ITEM(goldeneagleshirt, bodyarmor)
{
 public:
  virtual bool IsGoldenEagleShirt() const { return true; }
  virtual bool IsConsumable() const { return false; }
  virtual bool AllowAlphaEverywhere() const { return true; }
 protected:
  virtual int GetClassAnimationFrames() const { return 32; }
  virtual col16 GetOutlineColor(int) const;
  virtual alpha GetOutlineAlpha(int) const;
};

ITEM(shield, armor)
{
 public:
  virtual long GetPrice() const;
  virtual bool IsShield(const character*) const { return true; }
  virtual void AddInventoryEntry(const character*, festring&, int, bool) const;
};

ITEM(cloak, armor)
{
 public:
  virtual long GetPrice() const;
  virtual bool IsCloak(const character*) const { return true; }
  virtual bool IsInCorrectSlot(int) const;
  virtual bool ReceiveDamage(character*, int, int, int);
 protected:
  virtual int GetSpecialFlags() const;
  virtual const char* GetBreakVerb() const;
  virtual bool AddAdjective(festring&, bool) const;
  virtual col16 GetMaterialColorB(int) const;
};

ITEM(boot, armor)
{
 public:
  virtual long GetPrice() const;
  virtual bool IsBoot(const character*) const { return true; }
  virtual bool IsInCorrectSlot(int) const;
};

ITEM(gauntlet, armor)
{
 public:
  virtual long GetPrice() const;
  virtual bool IsGauntlet(const character*) const { return true; }
  virtual bool IsInCorrectSlot(int) const;
};

ITEM(belt, armor)
{
 public:
  virtual long GetPrice() const;
  virtual bool IsBelt(const character*) const { return true; }
  virtual int GetFormModifier() const;
  virtual bool IsInCorrectSlot(int) const;
  virtual col16 GetMaterialColorB(int Frame) const { return GetMaterialColorA(Frame); }
};

ITEM(ring, item)
{
 public:
  virtual bool IsRing(const character*) const { return true; }
  virtual bool IsInCorrectSlot(int) const;
 protected:
  virtual col16 GetMaterialColorB(int) const;
};

ITEM(amulet, item)
{
 public:
  virtual bool IsAmulet(const character*) const { return true; }
  virtual bool IsInCorrectSlot(int) const;
 protected:
  virtual col16 GetMaterialColorB(int) const;
};

ITEM(helmet, armor)
{
 public:
  virtual bool IsGorovitsFamilyRelic() const;
  virtual long GetPrice() const;
  virtual bool IsHelmet(const character*) const { return true; }
  virtual bool IsInCorrectSlot(int) const;
 protected:
  virtual col16 GetMaterialColorB(int) const;
  virtual col16 GetMaterialColorC(int) const;
};

ITEM(chameleonwhip, whip)
{
 public:
  virtual bool HitEffect(character*, character*, v2, int, int, bool);
 protected:
  virtual bool ScabiesHelps(const character*, const character*) const;
};

ITEM(wondersmellstaff, meleeweapon)
{
 public:
  virtual bool HitEffect(character*, character*, v2, int, int, bool);
  virtual bool AllowAlphaEverywhere() const { return true; }
 protected:
  virtual int GetClassAnimationFrames() const;
  virtual col16 GetOutlineColor(int) const;
  virtual alpha GetOutlineAlpha(int) const;
};

ITEM(decosadshirt, bodyarmor)
{
 public:
  decosadshirt();
  virtual void Be();
  virtual void Save(outputfile&) const;
  virtual void Load(inputfile&);
  ulong GetEquippedTicks() { return EquippedTicks; }
  void SetEquippedTicks(ulong What) { EquippedTicks = What; }
  virtual bool IsDecosAdShirt(const character*) const { return true; }
 protected:
  virtual bool CalculateHasBe() const { return true; }
  ulong EquippedTicks;
};

#endif
