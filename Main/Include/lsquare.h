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

#ifndef __LSQUARE_H__
#define __LSQUARE_H__

#include "level.h"
#include "dungeon.h"
#include "lterra.h"

#ifndef LIGHT_BORDER
#define LIGHT_BORDER 80
#endif

class stack;
class glterrain;
class olterrain;
class fluid;
class material;
class item;
class smoke;
class gas;
class bodypart;
class liquid;
class rain;
class trap;
struct sortdata;

typedef std::vector<item*> itemvector;
typedef bool (item::*sorter)(const character*) const;

struct emitter
{
  emitter(ulong ID, col24 Emitation) : ID(ID), Emitation(Emitation) { }
  explicit emitter() { }
  ulong ID;
  col24 Emitation;
};

inline ulong MakeEmitterID(v2 Pos)
{
  return Pos.X + (Pos.Y << 8);
}

inline v2 ExtractPosFromEmitterID(ulong ID)
{
  return v2(ID & 0xFF, (ID >> 8) & 0xFF);
}

typedef std::vector<emitter> emittervector;

outputfile& operator<<(outputfile&, const emitter&);
inputfile& operator>>(inputfile&, emitter&);

struct eyecontroller
{
  static bool Handler(int, int);
  static lsquare*** Map;
};

struct pathcontroller
{
  static bool Handler(int, int);
  static lsquare*** Map;
  static const character* Character;
};

struct stackcontroller
{
  static lsquare*** Map;
  static lsquare** Stack;
  static long StackIndex;
  static int LevelXSize, LevelYSize;
  static v2 Center;
};

struct tickcontroller
{
  static void PrepareShiftedTick();
  static ulong Tick;
  static ulong ShiftedTick[4];
  static ulong ShiftedQuadriTick[4];
};

class lsquare : public square
{
 public:
  friend class level;
  friend struct loscontroller;
  friend struct sunbeamcontroller;
  friend struct areacontroller;
  friend struct emitationcontroller;
  friend struct noxifycontroller;
  lsquare(level*, v2);
  virtual ~lsquare();
  virtual void AddCharacter(character*);
  virtual void RemoveCharacter();
  stack* GetStack() const { return Stack; }
  void AlterLuminance(ulong, col24);
  void Emitate() { Emitate(Emitation); }
  void Emitate(col24, ulong = 0);
  void Clean();
  bool Open(character*);
  bool Close(character*);
  virtual void Save(outputfile&) const;
  virtual void Load(inputfile&);
  void SignalEmitationIncrease(col24);
  void SignalEmitationDecrease(col24);
  col24 GetEmitation() const { return Emitation; }
  void Noxify() { Noxify(Emitation); }
  void Noxify(col24, ulong = 0);
  bool NoxifyEmitter(ulong);
  const char* GetEngraved() const { return Engraved; }
  bool Engrave(const festring&);
  void UpdateMemorizedDescription(bool = false);
  bool BeKicked(character*, item*, bodypart*, double, double, int, int, bool, bool);
  int GetDivineMaster() const;
  void Draw(blitdata&) const;
  void UpdateMemorized();
  bool CanBeDug() const;
  virtual gterrain* GetGTerrain() const { return GLTerrain; }
  virtual oterrain* GetOTerrain() const { return OLTerrain; }
  glterrain* GetGLTerrain() const { return GLTerrain; }
  olterrain* GetOLTerrain() const { return OLTerrain; }
  void ChangeLTerrain(glterrain*, olterrain*);
  level* GetLevel() const { return static_cast<level*>(AreaUnder); }
  void SetLevelUnder(level* What) { AreaUnder = What; }
  void ChangeGLTerrain(glterrain*);
  void ChangeOLTerrain(olterrain*);
  void SetLTerrain(glterrain*, olterrain*);
  void ApplyScript(const squarescript*, room*);
  virtual bool CanBeSeenByPlayer(bool = false) const;
  virtual bool CanBeSeenFrom(v2, long, bool = false) const ;
  void StepOn(character*, lsquare**);
  uint GetRoomIndex() const { return RoomIndex; }
  void SetRoomIndex(uint What) { RoomIndex = What; }
  void ReceiveVomit(character*, liquid*);
  room* GetRoom() const { return RoomIndex ? GetLevel()->GetRoom(RoomIndex) : 0; }
  void SetTemporaryEmitation(col24);
  col24 GetTemporaryEmitation() const { return TemporaryEmitation; }
  void ChangeOLTerrainAndUpdateLights(olterrain*);
  void DrawParticles(long, bool = true);
  v2 DrawLightning(v2, long, int, bool = true);
  bool DipInto(item*, character*);
  bool TryKey(item*, character*);
  void SignalSeen(ulong);
  void CalculateLuminance();
  void DrawStaticContents(blitdata&) const;
  void DrawMemorized(blitdata&) const;
  void DrawMemorizedCharacter(blitdata&) const;
  void SendMemorizedUpdateRequest();
  lsquare* GetNeighbourLSquare(int) const;
  lsquare* GetNearLSquare(v2 Pos_) const { return static_cast<lsquare*>(AreaUnder->GetSquare(Pos_)); }
  bool IsDangerous(const character*) const;
  bool IsScary(const character*) const;
  stack* GetStackOfAdjacentSquare(int) const;
  void KickAnyoneStandingHereAway();
  bool IsDark() const;
  void AddItem(item*);
  static bool (lsquare::*GetBeamEffect(int))(const beamdata&);
  bool Polymorph(const beamdata&);
  bool Strike(const beamdata&);
  bool FireBall(const beamdata&);
  bool Teleport(const beamdata&);
  bool Haste(const beamdata&);
  bool Slow(const beamdata&);
  bool Resurrect(const beamdata&);
  bool Invisibility(const beamdata&);
  bool Duplicate(const beamdata&);
  bool Lightning(const beamdata&);
  bool DoorCreation(const beamdata&);
  bool AcidRain(const beamdata&);
  bool Necromancy(const beamdata&);
  int GetLevelIndex() const { return static_cast<level*>(AreaUnder)->GetIndex(); }
  int GetDungeonIndex() const { return static_cast<level*>(AreaUnder)->GetDungeon()->GetIndex(); }
  dungeon* GetDungeon() const { return static_cast<level*>(AreaUnder)->GetDungeon(); }
  bool CheckKick(const character*) const;
  void GetHitByExplosion(const explosion*);
  int GetSpoiledItems() const;
  void SortAllItems(const sortdata&);
  bool LowerEnchantment(const beamdata&);
  void RemoveSmoke(smoke*);
  void AddSmoke(gas*);
  bool IsFlyable() const { return !OLTerrain || (OLTerrain->GetWalkability() & FLY); }
  bool IsTransparent() const { return Flags & IS_TRANSPARENT; }
  void SignalSmokeAlphaChange(int);
  void ShowSmokeMessage() const;
  void DisplaySmokeInfo(festring&) const;
  bool IsDipDestination() const;
  void ReceiveEarthQuakeDamage();
  bool CanBeFeltByPlayer() const;
  void PreProcessForBone();
  void PostProcessForBone(double&, int&);
  void DisplayEngravedInfo(festring&) const;
  bool EngravingsCanBeReadByPlayer();
  bool HasEngravings() const;
  void FinalProcessForBone();
  bool IsFreezed() const { return Flags & FREEZED; }
  bool IsDangerousToBreathe(const character*) const;
  bool IsScaryToBreathe(const character*) const;
  int GetWalkability() const;
  int GetTheoreticalWalkability() const { return OLTerrain ? OLTerrain->GetTheoreticalWalkability() & GLTerrain->GetTheoreticalWalkability() : GLTerrain->GetTheoreticalWalkability(); }
  virtual int GetSquareWalkability() const { return GetWalkability(); }
  void CalculateGroundBorderPartners();
  void RequestForGroundBorderPartnerUpdates();
  void CalculateOverBorderPartners();
  void RequestForOverBorderPartnerUpdates();
  void SpillFluid(character*, liquid*, bool = false, bool = true);
  void DisplayFluidInfo(festring&) const;
  void RemoveFluid(fluid*);
  fluid* AddFluid(liquid*);
  void DrawStacks(blitdata&) const;
  bool FluidIsVisible() const { return SmokeAlphaSum < 175; }
  void RemoveRain(rain*);
  void AddRain(liquid*, v2, int, bool);
  bool IsInside() const { return Flags & INSIDE; }
  void RemoveSunLight();
  void CheckIfIsSecondarySunLightEmitter();
  void CalculateNeighbourLSquares();
  const emittervector& GetEmitter() const { return Emitter; }
  void EnableGlobalRain();
  void DisableGlobalRain();
  void Freeze() { Flags |= FREEZED; }
  void UnFreeze() { Flags &= ~FREEZED; }
  void InitLastSeen();
  void GetSideItemDescription(festring&, bool = false) const;
  void AddSunLightEmitter(ulong);
  void SendSunLightSignals();
  const sunemittervector& GetSunEmitter() const { return SunEmitter; }
  void ZeroReSunEmitatedFlags();
  virtual bool HasBeenSeen() const;
  bool CalculateIsTransparent();
  void CalculateSunLightLuminance(ulong);
  void CreateMemorized();
  bool DetectMaterial(const material*) const;
  void Reveal(ulong, bool = false);
  void DestroyMemorized();
  void SwapMemorized(lsquare*);
  bool HasNoBorderPartners() const;
  lsquare* GetRandomAdjacentSquare() const;
  void SignalPossibleTransparencyChange();
  bool AddTrap(trap*);
  void RemoveTrap(trap*);
  void DisplayTrapInfo(festring&) const;
  void FillTrapVector(std::vector<trap*>&) const;
  void ReceiveTrapDamage(character*, int, int, int = YOURSELF);
  bool HasDangerousTraps(const character*) const;
  bool HasDangerousFluids(const character*) const;
  void AddLocationDescription(festring&) const;
  bool VomitingIsDangerous(const character*) const;
 protected:
  void ChangeLuminance(col24&, col24);
  void RemoveLuminance(col24&);
  void CalculateEmitation();
  void UpdateStaticContentCache(col24) const;
  mutable struct staticcontentcache
  {
    staticcontentcache() : Bitmap(0), Luminance(0) { }
    bitmap* Bitmap;
    col24 Luminance;
  } StaticContentCache;
  fluid* Fluid;
  smoke* Smoke;
  rain* Rain;
  trap* Trap;
  emittervector Emitter;
  sunemittervector SunEmitter;
  glterrain* GLTerrain;
  olterrain* OLTerrain;
  stack* Stack;
  bitmap* Memorized;
  bitmap* FowMemorized;
  char* Engraved;
  glterrain** GroundBorderPartnerTerrain;
  ulong GroundBorderPartnerInfo;
  olterrain** OverBorderPartnerTerrain;
  ulong OverBorderPartnerInfo;
  ulong SquarePartEmitationTick;
  ulong SquarePartLastSeen;
  col24 Emitation;
  int SmokeAlphaSum;
  lsquare* NeighbourLSquare[8];
  col24 AmbientLuminance;
  col24 SunLightLuminance;
  col24 TemporaryEmitation;
  col24 SecondarySunLightEmitation;
  ushort LastExplosionID;
  uchar RoomIndex;
};

inline bool lsquare::IsDark() const
{
  col24 Light = Luminance;

  return (!Light
	  || ((Light & 0xFF0000) < (LIGHT_BORDER << 16)
	      && (Light & 0x00FF00) < (LIGHT_BORDER << 8)
	      && (Light & 0x0000FF) < LIGHT_BORDER));
}

inline bool eyecontroller::Handler(int x, int y)
{
  return Map[x][y]->IsTransparent();
}

inline lsquare* lsquare::GetNeighbourLSquare(int I) const
{
  return I < 8 ? NeighbourLSquare[I] : const_cast<lsquare*>(this);
}

#endif
