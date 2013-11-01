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

#ifndef __LTERRA_H__
#define __LTERRA_H__

#include "object.h"
#include "terra.h"
#include "script.h"

class glterrain;
class olterrain;
class item;
class level;
class lsquare;
class stack;
class room;
class liquid;
class materialscript;
class glterrainprototype;
class olterrainprototype;
template <class type> class databasecreator;
struct blitdata;

typedef glterrain* (*glterrainspawner)(int, int);
typedef olterrain* (*olterrainspawner)(int, int);

struct lterraindatabase : public databasebase
{
  void PostProcess() { }
  v2 BitmapPos;
  bool UsesLongArticle;
  festring Adjective;
  bool UsesLongAdjectiveArticle;
  festring NameSingular;
  festring NamePlural;
  festring PostFix;
  int ArticleMode;
  fearray<long> MainMaterialConfig;
  fearray<long> SecondaryMaterialConfig;
  fearray<long> MaterialConfigChances;
  long MaterialConfigChanceSum;
  int OKVisualEffects;
  col16 MaterialColorB;
  col16 MaterialColorC;
  col16 MaterialColorD;
  festring SitMessage;
  int AttachedGod;
  int Walkability;
  bool IsAbstract;
  bool ShowMaterial;
  bool HasSecondaryMaterial;
  bool UseBorderTiles;
  int BorderTilePriority;
};

class lterrain : public object
{
 public:
  lterrain() : LSquareUnder(0) { }
  virtual void Load(inputfile&);
  virtual bool Open(character*) { return false; }
  virtual bool Close(character*) { return false; }
  v2 GetPos() const;
  virtual bool CanBeOpened() const { return false; }
  virtual bool AcceptsOffers() const { return false; }
  virtual bool ReceiveVomit(character*, liquid*) { return false; }
  virtual bool CanBeOpenedByAI() { return false; }
  virtual bool Polymorph(character*) { return false; }
  virtual bool DipInto(item*, character*) { return false; }
  virtual bool IsDipDestination() const { return false; }
  virtual bool TryKey(item*, character*) { return false; }
  bool CanBeSeenByPlayer() const;
  bool CanBeSeenBy(character*) const;
  virtual const festring& GetSitMessage() const = 0;
  virtual bool SitOn(character*);
  virtual square* GetSquareUnderEntity(int = 0) const;
  void SetLSquareUnder(lsquare* What) { LSquareUnder = What; }
  lsquare* GetLSquareUnder() const { return LSquareUnder; }
  level* GetLevel() const;
  lsquare* GetNearLSquare(v2) const;
  lsquare* GetNearLSquare(int, int) const;
  virtual void CalculateAll() { CalculateEmitation(); }
  virtual void SignalEmitationIncrease(col24);
  virtual void SignalEmitationDecrease(col24);
  virtual bool HasKeyHole() const { return CanBeOpened(); }
  virtual bool IsOnGround() const { return true; }
  room* GetRoom() const;
  virtual void SignalRustLevelChange();
  virtual void TryToRust(long);
  virtual void ReceiveAcid(material*, long) { }
  void InitMaterials(material*, bool = true);
  void SetMainMaterial(material*, int = 0);
  void ChangeMainMaterial(material*, int = 0);
  virtual void GenerateMaterials();
  virtual void InitMaterials(const materialscript*, const materialscript*, bool);
  virtual const fearray<long>& GetMainMaterialConfig() const = 0;
  virtual void SurviveEffect(character*) { }
  virtual void RestoreHP() { }
  virtual void AddLocationDescription(festring&) const;
 protected:
  void Initialize(int, int);
  virtual void PostConstruct() { }
  virtual void InstallDataBase(int) = 0;
  lsquare* LSquareUnder;
};

struct glterraindatabase : public lterraindatabase
{
  typedef glterrainprototype prototype;
  void InitDefaults(const prototype*, int);
  bool AllowRandomInstantiation() const { return true; }
  const prototype* ProtoType;
};

class glterrainprototype
{
 public:
  friend class databasecreator<glterrain>;
  glterrainprototype(const glterrainprototype*, glterrainspawner, const char*);
  glterrain* Spawn(int Config = 0, int SpecialFlags = 0) const { return Spawner(Config, SpecialFlags); }
  glterrain* SpawnAndLoad(inputfile&) const;
  const char* GetClassID() const { return ClassID; }
  int GetIndex() const { return Index; }
  const glterrainprototype* GetBase() const { return Base; }
  int CreateSpecialConfigurations(glterraindatabase**, int Configs) { return Configs; }
  const glterraindatabase* ChooseBaseForConfig(glterraindatabase** TempConfig, int, int) { return *TempConfig; }
  const glterraindatabase*const* GetConfigData() const { return ConfigData; }
  int GetConfigSize() const { return ConfigSize; }
 private:
  int Index;
  const glterrainprototype* Base;
  glterraindatabase** ConfigData;
  glterraindatabase** ConfigTable[CONFIG_TABLE_SIZE];
  int ConfigSize;
  glterrainspawner Spawner;
  const char* ClassID;
};

class glterrain : public lterrain, public gterrain
{
 public:
  friend class databasecreator<glterrain>;
  typedef glterrainprototype prototype;
  typedef glterraindatabase database;
  virtual void Save(outputfile&) const;
  virtual void Load(inputfile&);
  virtual int GetEntryDifficulty() const { return 1; }
  int GetType() const { return GetProtoType()->GetIndex(); }
  const database* GetDataBase() const { return DataBase; }
  DATA_BASE_VALUE(const prototype*, ProtoType);
  DATA_BASE_VALUE(int, Config);
  DATA_BASE_TRUTH(UsesLongArticle);
  DATA_BASE_VALUE(const festring&, Adjective);
  DATA_BASE_TRUTH(UsesLongAdjectiveArticle);
  DATA_BASE_VALUE(const festring&, NameSingular);
  DATA_BASE_VALUE(const festring&, NamePlural);
  DATA_BASE_VALUE(const festring&, PostFix);
  DATA_BASE_VALUE(int, ArticleMode);
  virtual DATA_BASE_VALUE(const fearray<long>&, MainMaterialConfig);
  DATA_BASE_VALUE(const fearray<long>&, SecondaryMaterialConfig);
  virtual DATA_BASE_VALUE(const fearray<long>&, MaterialConfigChances);
  virtual DATA_BASE_VALUE(long, MaterialConfigChanceSum);
  DATA_BASE_VALUE(int, OKVisualEffects);
  virtual DATA_BASE_VALUE_WITH_PARAMETER(col16, MaterialColorB, int);
  virtual DATA_BASE_VALUE_WITH_PARAMETER(col16, MaterialColorC, int);
  virtual DATA_BASE_VALUE_WITH_PARAMETER(col16, MaterialColorD, int);
  virtual DATA_BASE_VALUE(const festring&, SitMessage);
  DATA_BASE_TRUTH(ShowMaterial);
  DATA_BASE_VALUE(int, Walkability);
  DATA_BASE_TRUTH(UseBorderTiles);
  DATA_BASE_VALUE(int, BorderTilePriority);
  virtual int GetAttachedGod() const;
  virtual int GetTheoreticalWalkability() const { return DataBase->Walkability; }
  void Draw(blitdata&) const;
  virtual bool IsAnimated() const;
 protected:
  virtual void InstallDataBase(int);
  virtual int GetGraphicsContainerIndex() const;
  virtual const prototype* FindProtoType() const { return &ProtoType; }
  virtual v2 GetBitmapPos(int) const;
  v2 GetBorderBitmapPos(v2, int) const;
  virtual void ModifyAnimationFrames(int&) const;
  static const prototype ProtoType;
  const database* DataBase;
};

struct olterraindatabase : public lterraindatabase
{
  typedef olterrainprototype prototype;
  void InitDefaults(const prototype*, int);
  bool AllowRandomInstantiation() const;
  const prototype* ProtoType;
  festring DigMessage;
  int RestModifier;
  festring RestMessage;
  long StorageVolume;
  int HPModifier;
  v2 OpenBitmapPos;
  v2 WindowBitmapPos;
  fearray<contentscript<item> > LeftOverItems;
  bool CreateDivineConfigurations;
  bool CanBeDestroyed;
  bool IsUpLink;
  bool CreateLockConfigurations;
  bool IsAlwaysTransparent;
  bool ShowThingsUnder;
  bool IsWall;
  bool CreateWindowConfigurations;
  bool IsSafeToCreateDoor;
};

class olterrainprototype
{
 public:
  friend class databasecreator<olterrain>;
  olterrainprototype(const olterrainprototype*, olterrainspawner, const char*);
  olterrain* Spawn(int Config = 0, int SpecialFlags = 0) const { return Spawner(Config, SpecialFlags); }
  olterrain* SpawnAndLoad(inputfile&) const;
  const char* GetClassID() const { return ClassID; }
  int GetIndex() const { return Index; }
  const olterrainprototype* GetBase() const { return Base; }
  int CreateSpecialConfigurations(olterraindatabase**, int);
  const olterraindatabase* ChooseBaseForConfig(olterraindatabase** TempConfig, int, int) { return *TempConfig; }
  const olterraindatabase*const* GetConfigData() const { return ConfigData; }
  int GetConfigSize() const { return ConfigSize; }
 private:
  int Index;
  const olterrainprototype* Base;
  olterraindatabase** ConfigData;
  olterraindatabase** ConfigTable[CONFIG_TABLE_SIZE];
  int ConfigSize;
  olterrainspawner Spawner;
  const char* ClassID;
};

class olterrain : public lterrain, public oterrain
{
 public:
  friend class databasecreator<olterrain>;
  typedef olterrainprototype prototype;
  typedef olterraindatabase database;
  virtual void Save(outputfile&) const;
  virtual void Load(inputfile&);
  virtual bool Enter(bool) const;
  virtual void BeKicked(character*, int, int);
  virtual bool IsDoor() const { return false; }
  virtual bool HasEatEffect() const { return false; }
  virtual bool HasDrinkEffect() const { return false; }
  virtual bool Eat(character*) { return false; }
  virtual bool Drink(character*) { return false; }
  virtual void Lock() { }
  virtual bool IsLocked() const { return false; }
  virtual void CreateBoobyTrap() { }
  virtual void HasBeenHitByItem(character*, item*, int) { }
  virtual void Break();
  int GetHP() const { return HP; }
  void EditHP(int What) { HP += What; }
  virtual void ReceiveDamage(character*, int, int);
  int GetType() const { return GetProtoType()->GetIndex(); }
  const database* GetDataBase() const { return DataBase; }
  void ShowRestMessage(character*) const;
  DATA_BASE_VALUE(const prototype*, ProtoType);
  DATA_BASE_VALUE(int, Config);
  DATA_BASE_TRUTH(UsesLongArticle);
  DATA_BASE_VALUE(const festring&, Adjective);
  DATA_BASE_TRUTH(UsesLongAdjectiveArticle);
  DATA_BASE_VALUE(const festring&, NameSingular);
  DATA_BASE_VALUE(const festring&, NamePlural);
  DATA_BASE_VALUE(const festring&, PostFix);
  DATA_BASE_VALUE(int, ArticleMode);
  virtual DATA_BASE_VALUE(const fearray<long>&, MainMaterialConfig);
  DATA_BASE_VALUE(const fearray<long>&, SecondaryMaterialConfig);
  virtual DATA_BASE_VALUE(const fearray<long>&, MaterialConfigChances);
  virtual DATA_BASE_VALUE(long, MaterialConfigChanceSum);
  DATA_BASE_VALUE(int, OKVisualEffects);
  virtual DATA_BASE_VALUE_WITH_PARAMETER(col16, MaterialColorB, int);
  virtual DATA_BASE_VALUE_WITH_PARAMETER(col16, MaterialColorC, int);
  virtual DATA_BASE_VALUE_WITH_PARAMETER(col16, MaterialColorD, int);
  virtual DATA_BASE_VALUE(const festring&, SitMessage);
  DATA_BASE_TRUTH(ShowMaterial);
  DATA_BASE_VALUE(const festring&, DigMessage);
  bool CanBeDestroyed() const;
  DATA_BASE_VALUE(int, RestModifier);
  DATA_BASE_VALUE(const festring&, RestMessage);
  DATA_BASE_TRUTH(IsUpLink);
  DATA_BASE_VALUE(long, StorageVolume);
  DATA_BASE_VALUE(int, HPModifier);
  DATA_BASE_TRUTH(IsSafeToCreateDoor);
  DATA_BASE_VALUE_WITH_PARAMETER(v2, OpenBitmapPos, int);
  DATA_BASE_TRUTH(UseBorderTiles);
  DATA_BASE_VALUE(int, BorderTilePriority);
  virtual DATA_BASE_VALUE(int, Walkability);
  DATA_BASE_TRUTH(IsAlwaysTransparent);
  DATA_BASE_TRUTH(CreateWindowConfigurations);
  DATA_BASE_VALUE(v2, WindowBitmapPos);
  DATA_BASE_VALUE(const fearray<contentscript<item> >&, LeftOverItems);
  DATA_BASE_TRUTH(IsWall);
  virtual void SetAttachedArea(int) { }
  virtual void SetAttachedEntry(int) { }
  virtual void SetText(const festring&) { }
  virtual festring GetText() const;
  virtual void SetItemsInside(const fearray<contentscript<item> >&, int) { }
  int GetStrengthValue() const;
  virtual void SignalVolumeAndWeightChange() { HP = CalculateMaxHP(); }
  int CalculateMaxHP();
  virtual int GetAttachedGod() const;
  void SetConfig(int, int = 0);
  god* GetMasterGod() const;
  virtual bool IsTransparent() const;
  virtual void Draw(blitdata&) const;
  virtual int GetTheoreticalWalkability() const { return DataBase->Walkability; }
  virtual void BeDestroyed() { Break(); }
  virtual void ReceiveAcid(material*, long);
  virtual void SignalRustLevelChange();
  virtual bool IsFountainWithWater() const { return false; }
  bool ShowThingsUnder() const;
  bool WillBeDestroyedBy(const character*) const;
  virtual void PreProcessForBone() { }
  virtual void PostProcessForBone() { }
  virtual void FinalProcessForBone() { }
  virtual void RestoreHP() { HP = CalculateMaxHP(); }
  virtual bool IsAnimated() const;
  virtual bool VomitingIsDangerous(const character*) const { return false; }
 protected:
  virtual v2 GetBitmapPos(int) const;
  v2 GetBorderBitmapPos(v2, int) const;
  virtual void ModifyAnimationFrames(int&) const;
  virtual void InstallDataBase(int);
  virtual int GetGraphicsContainerIndex() const;
  virtual const prototype* FindProtoType() const { return &ProtoType; }
  static const prototype ProtoType;
  const database* DataBase;
  int HP;
};

#ifdef __FILE_OF_STATIC_LTERRAIN_PROTOTYPE_DEFINITIONS__
#define LTERRAIN_PROTO(name, base, protobase)\
template<> const protobase##prototype\
  name##sysbase::ProtoType(&base::ProtoType,\
			   (protobase##spawner)(&name##sysbase::Spawn),\
			   #name);
#else
#define LTERRAIN_PROTO(name, base, protobase)
#endif

#define LTERRAIN(name, base, protobase)\
class name;\
typedef sysbase<name, base, protobase##prototype> name##sysbase;\
LTERRAIN_PROTO(name, base, protobase)\
class name : public name##sysbase

#define GLTERRAIN(name, base) LTERRAIN(name, base, glterrain)
#define OLTERRAIN(name, base) LTERRAIN(name, base, olterrain)

#endif
