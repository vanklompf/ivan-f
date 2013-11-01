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

#ifndef __NONHUMAN_H__
#define __NONHUMAN_H__

#include "char.h"

CHARACTER(nonhumanoid, character)
{
 public:
  virtual void Save(outputfile&) const;
  virtual void Load(inputfile&);
  void CalculateUnarmedDamage();
  void CalculateKickDamage();
  void CalculateBiteDamage();
  void CalculateUnarmedToHitValue();
  void CalculateKickToHitValue();
  void CalculateBiteToHitValue();
  void CalculateUnarmedAPCost();
  void CalculateKickAPCost();
  void CalculateBiteAPCost();
  double GetUnarmedDamage() const { return UnarmedDamage; }
  int GetUnarmedMinDamage() const;
  int GetUnarmedMaxDamage() const;
  double GetKickDamage() const { return KickDamage; }
  int GetKickMinDamage() const;
  int GetKickMaxDamage() const;
  double GetBiteDamage() const { return BiteDamage; }
  int GetBiteMinDamage() const;
  int GetBiteMaxDamage() const;
  double GetUnarmedToHitValue() const { return UnarmedToHitValue; }
  double GetKickToHitValue() const { return KickToHitValue; }
  double GetBiteToHitValue() const { return BiteToHitValue; }
  long GetUnarmedAPCost() const { return UnarmedAPCost; }
  long GetKickAPCost() const { return KickAPCost; }
  long GetBiteAPCost() const { return BiteAPCost; }
  virtual void Kick(lsquare*, int, bool = false);
  virtual bool Hit(character*, v2, int, bool = false);
  virtual void UnarmedHit(character*, v2, int, bool = false);
  virtual void InitSpecialAttributes();
  virtual double GetTimeToKill(const character*, bool) const;
  virtual int GetAttribute(int, bool = true) const;
  virtual bool EditAttribute(int, int);
  virtual void EditExperience(int, double, double);
  virtual int DrawStats(bool) const;
  virtual void Bite(character*, v2, int, bool = false);
  virtual int GetCarryingStrength() const;
  virtual void CalculateBattleInfo();
  void CalculateUnarmedAttackInfo();
  void CalculateKickAttackInfo();
  void CalculateBiteAttackInfo();
  virtual bool UseMaterialAttributes() const;
  virtual void AddSpecialStethoscopeInfo(felist&) const;
  virtual bool EditAllAttributes(int);
  virtual void AddAttributeInfo(festring&) const;
  virtual void AddAttackInfo(felist&) const;
 protected:
  double StrengthExperience;
  double AgilityExperience;
  double UnarmedDamage;
  double KickDamage;
  double BiteDamage;
  double UnarmedToHitValue;
  double KickToHitValue;
  double BiteToHitValue;
  long UnarmedAPCost;
  long KickAPCost;
  long BiteAPCost;
};

CHARACTER(frog, nonhumanoid)
{
 public:
  virtual bool MoveRandomly() { return MoveRandomlyInRoom(); }
};

CHARACTER(billswill, nonhumanoid)
{
 protected:
  virtual int GetBodyPartWobbleData(int) const;
  virtual const char* FirstPersonBiteVerb() const;
  virtual const char* FirstPersonCriticalBiteVerb() const;
  virtual const char* ThirdPersonBiteVerb() const;
  virtual const char* ThirdPersonCriticalBiteVerb() const;
  virtual bool AttackIsBlockable(int) const { return false; }
  virtual bool AttackMayDamageArmor() const { return false; }
};

CHARACTER(mommo, nonhumanoid)
{
 protected:
  virtual int GetBodyPartWobbleData(int) const;
  virtual bool CanVomit() const { return true; }
  virtual void CreateCorpse(lsquare*);
  virtual bool Hit(character*, v2, int, bool);
  virtual void GetAICommand();
};

CHARACTER(canine, nonhumanoid)
{
};

CHARACTER(wolf, canine)
{
 protected:
  virtual col16 GetSkinColor() const;
};

CHARACTER(dog, canine)
{
 public:
  virtual bool Catches(item*);
  virtual void BeTalkedTo();
 protected:
  virtual bodypart* MakeBodyPart(int) const;
  virtual void GetAICommand();
};

CHARACTER(spider, nonhumanoid)
{
 public:
  virtual bool SpecialBiteEffect(character*, v2, int, int, bool);
  virtual void GetAICommand();
};

CHARACTER(jackal, nonhumanoid)
{
};

CHARACTER(ass, nonhumanoid)
{
};

CHARACTER(bear, nonhumanoid)
{
};

CHARACTER(dolphin, nonhumanoid)
{
 protected:
  virtual int GetSpecialBodyPartFlags(int) const;
  virtual void SpecialTurnHandler() { UpdatePictures(); }
};

CHARACTER(bat, nonhumanoid)
{
};

CHARACTER(largecat, nonhumanoid)
{
 public:
  largecat() : Lives(7) { }
  virtual void Save(outputfile&) const;
  virtual void Load(inputfile&);
  virtual bool SpecialSaveLife();
 protected:
  int Lives;
};

CHARACTER(largerat, nonhumanoid)
{
};

CHARACTER(mammoth, nonhumanoid)
{
};

CHARACTER(unicorn, nonhumanoid)
{
 public:
  virtual int TakeHit(character*, item*, bodypart*, v2, double, double, int, int, int, bool, bool);
  virtual bool SpecialEnemySightedReaction(character*);
 protected:
  void MonsterTeleport(const char*);
};

CHARACTER(lion, nonhumanoid)
{
};

CHARACTER(carnivorousplant, nonhumanoid)
{
 protected:
  virtual col16 GetTorsoSpecialColor() const;
  virtual void GetAICommand();
  virtual void CreateCorpse(lsquare*);
};

CHARACTER(buffalo, nonhumanoid)
{
};

CHARACTER(snake, nonhumanoid)
{
 protected:
  virtual bool SpecialBiteEffect(character*, v2, int, int, bool);
};

CHARACTER(ostrich, nonhumanoid)
{
 public:
  ostrich() : HasDroppedBananas(false) { }
  virtual void Save(outputfile&) const;
  virtual void Load(inputfile&);
 protected:
  virtual bool HandleCharacterBlockingTheWay(character*, v2, int);
  virtual void GetAICommand();
  bool HasDroppedBananas;
};

CHARACTER(chameleon, nonhumanoid)
{
 public:
  virtual int TakeHit(character*, item*, bodypart*, v2, double, double, int, int, int, bool, bool);
  virtual bool SpecialEnemySightedReaction(character*);
 protected:
  virtual col16 GetSkinColor() const;
  virtual void SpecialTurnHandler() { UpdatePictures(); }
};

CHARACTER(floatingeye, nonhumanoid)
{
 public:
  floatingeye() : NextWayPoint(0) { }
  virtual bool Hit(character*, v2, int, bool);
  virtual int TakeHit(character*, item*, bodypart*, v2, double, double, int, int, int, bool, bool);
  virtual void SetWayPoints(const fearray<packv2>&);
  virtual void Save(outputfile&) const;
  virtual void Load(inputfile&);
  virtual bool IsSpy() const { return true; }
  virtual bool CanAttack() const { return false; }
 protected:
  virtual void GetAICommand();
  std::vector<v2> WayPoints;
  uint NextWayPoint;
};

CHARACTER(eddy, nonhumanoid)
{
 public:
  virtual bool Hit(character*, v2, int, bool = false);
 protected:
  virtual int GetBodyPartWobbleData(int) const;
  virtual bodypart* MakeBodyPart(int) const;
  virtual void GetAICommand();
};

CHARACTER(mushroom, nonhumanoid)
{
 public:
  virtual void Save(outputfile&) const;
  virtual void Load(inputfile&);
  void SetSpecies(int);
  int GetSpecies() const { return Species; }
  virtual bool IsMushroom() const { return true; }
 protected:
  virtual void PostConstruct();
  virtual void GetAICommand();
  virtual col16 GetTorsoMainColor() const { return Species; }
  int Species;
};

CHARACTER(magicmushroom, mushroom)
{
 protected:
  virtual bodypart* MakeBodyPart(int) const;
  virtual void GetAICommand();
};

CHARACTER(ghost, nonhumanoid)
{
 public:
  ghost() : Active(true) { }
  virtual void AddName(festring&, int) const;
  virtual void Save(outputfile&) const;
  virtual void Load(inputfile&);
  void SetOwnerSoul(const festring& What) { OwnerSoul = What; }
  virtual bool IsNameable() const { return OwnerSoul.IsEmpty(); }
  virtual bool RaiseTheDead(character*);
  virtual int ReceiveBodyPartDamage(character*, int, int, int, int = 8, bool = false, bool = false, bool = true, bool = false);
  virtual bool SpecialEnemySightedReaction(character*);
  void SetIsActive(bool What) { Active = What; }
  virtual bool IsPolymorphable() const { return MaxHP < 100; }
 protected:
  virtual int GetBodyPartWobbleData(int) const;
  virtual const char* FirstPersonBiteVerb() const;
  virtual const char* FirstPersonCriticalBiteVerb() const;
  virtual const char* ThirdPersonBiteVerb() const;
  virtual const char* ThirdPersonCriticalBiteVerb() const;
  virtual bool AttackIsBlockable(int) const { return false; }
  virtual bool AttackMayDamageArmor() const { return false; }
  virtual void GetAICommand();
  festring OwnerSoul;
  bool Active;
};

CHARACTER(twoheadedmoose, nonhumanoid)
{
 public:
  virtual bool Hit(character*, v2, int, bool = false);
};

CHARACTER(magpie, nonhumanoid)
{
 public:
  virtual void GetAICommand();
  virtual bool IsRetreating() const;
 protected:
  virtual const char* FirstPersonBiteVerb() const;
  virtual const char* FirstPersonCriticalBiteVerb() const;
  virtual const char* ThirdPersonBiteVerb() const;
  virtual const char* ThirdPersonCriticalBiteVerb() const;
};

CHARACTER(skunk, nonhumanoid)
{
 public:
  virtual void GetAICommand();
};

CHARACTER(invisiblestalker, nonhumanoid)
{
};

CHARACTER(largecreature, nonhumanoid)
{
 public:
  virtual void CalculateSquaresUnder() { SquaresUnder = 4; }
  virtual int GetSquareIndex(v2) const;
  virtual int GetNeighbourSquares() const { return 12; }
  virtual int GetExtendedNeighbourSquares() const { return 16; }
  virtual square* GetNeighbourSquare(int) const;
  virtual lsquare* GetNeighbourLSquare(int) const;
  virtual wsquare* GetNeighbourWSquare(int) const;
  virtual int CalculateNewSquaresUnder(lsquare**, v2) const;
  virtual bool IsFreeForMe(square*) const;
  virtual bool CanMoveOn(const lsquare*) const;
  virtual bool CanMoveOn(const square*) const;
  virtual void PutTo(v2);
  virtual void Remove();
  virtual bool CreateRoute();
  virtual bool CanTheoreticallyMoveOn(const lsquare*) const;
  virtual int GetFlySymbolSquareIndex() const { return 1; }
  virtual int GetSwimmingSymbolSquareIndex() const { return 3; }
  virtual int GetUnconsciousSymbolSquareIndex() const { return 2; }
  virtual bool PlaceIsIllegal(v2, v2) const;
  bool PartCanMoveOn(const lsquare*) const;
 protected:
  virtual bodypart* MakeBodyPart(int) const;
  virtual void CreateCorpse(lsquare*);
  virtual void LoadSquaresUnder();
};

CHARACTER(elpuri, largecreature)
{
 public:
  elpuri() : Active(false) { }
  virtual void Save(outputfile&) const;
  virtual void Load(inputfile&);
  virtual bool Hit(character*, v2, int, bool = false);
  virtual int ReceiveBodyPartDamage(character*, int, int, int, int = 8, bool = false, bool = false, bool = true, bool = false);
  virtual bool SpecialEnemySightedReaction(character*);
  virtual bool MustBeRemovedFromBone() const;
  virtual bool TryToRiseFromTheDead();
 protected:
  virtual void GetAICommand();
  virtual void CreateCorpse(lsquare*);
  bool Active;
};

CHARACTER(genetrixvesana, largecreature)
{
 public:
  genetrixvesana() : TurnsExisted(0) { }
  virtual void Save(outputfile&) const;
  virtual void Load(inputfile&);
  virtual void FinalProcessForBone();
 protected:
  virtual void GetAICommand();
  virtual void CreateCorpse(lsquare*);
  virtual bool MustBeRemovedFromBone() const;
  long TurnsExisted;
};

CHARACTER(hedgehog, nonhumanoid)
{
 public:
  virtual void SpecialBodyDefenceEffect(character*, bodypart*, int);
};

CHARACTER(bunny, nonhumanoid)
{
 public:
  virtual bool CheckIfSatiated() { return GetNP() > BLOATED_LEVEL; }
  virtual void SignalNaturalGeneration();
  virtual bool IsBunny() const { return true; }
  virtual bool Catches(item*);
 protected:
  bool CheckForMatePartner();
  virtual void GetAICommand();
};

CHARACTER(vladimir, largecreature)
{
 public:
  virtual bool MustBeRemovedFromBone() const;
  virtual col16 GetSkinColor() const;
  virtual void SpecialTurnHandler() { UpdatePictures(); }
};

CHARACTER(hattifattener, nonhumanoid)
{
 public:
  bool Hit(character*, v2, int, bool) { return false; }
 protected:
  virtual int GetBodyPartWobbleData(int) const;
  virtual int GetSpecialBodyPartFlags(int) const;
  virtual void GetAICommand();
  virtual void CreateCorpse(lsquare*);
};

CHARACTER(blinkdog, dog)
{
 public:
  blinkdog();
  virtual void Save(outputfile&) const;
  virtual void Load(inputfile&);
  virtual int TakeHit(character*, item*, bodypart*, v2, double, double, int, int, int, bool, bool);
  virtual bool SpecialEnemySightedReaction(character*);
 protected:
  virtual bodypart* MakeBodyPart(int) const;
  void MonsterTeleport(const char*);
  bool SummonFriend();
  int SummonModifier;
};

CHARACTER(mysticfrog, frog)
{
 public:
  virtual void GetAICommand();
 protected:
  virtual int GetBodyPartWobbleData(int) const;
  virtual bodypart* MakeBodyPart(int) const;
  int GetSpellAPCost() const { return 1500; }
};

CHARACTER(lobhse, largecreature)
{
 protected:
  virtual bool SpecialBiteEffect(character*, v2, int, int, bool);
  virtual void GetAICommand();
  virtual void CreateCorpse(lsquare*);
  virtual bool MustBeRemovedFromBone() const;
  virtual bodypart* MakeBodyPart(int) const;
};

#endif
