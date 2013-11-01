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

#ifndef __LEVEL_H__
#define __LEVEL_H__

#include <vector>
#include <queue>
#include <set>

#include "area.h"
#include "square.h"
#include "ivandef.h"

class levelscript;
class roomscript;
class squarescript;
class glterrain;
class olterrain;
class dungeon;
class lsquare;
class room;
class item;
class liquid;
class level;
class material;
class team;
struct node;
struct emitter;
template <class type> struct fearray;

struct nodepointerstorer
{
  nodepointerstorer(node* Node) : Node(Node) { }
  bool operator<(const nodepointerstorer&) const;
  node* Node;
};

struct spawnresult
{
  const character* Pioneer;
  int Seen;
};

typedef std::priority_queue<nodepointerstorer> nodequeue;
typedef std::vector<item*> itemvector;
typedef std::vector<character*> charactervector;
typedef std::vector<emitter> emittervector;
typedef std::vector<ulong> sunemittervector;
typedef character* (*characterspawner)(int, int);

struct node
{
  node(int x, int y, lsquare* Square) : Square(Square), Pos(x, y) { }
  void CalculateNextNodes();
  lsquare* Square;
  node* Last;
  v2 Pos;
  long Distance;
  long Remaining;
  long TotalDistanceEstimate;
  long Diagonals;
  bool InNodeQueue;
  bool Processed;
  static node*** NodeMap;
  static int RequiredWalkability;
  static const character* SpecialMover;
  static v2 To;
  static uchar** WalkabilityMap;
  static int XSize, YSize;
  static nodequeue* NodeQueue;
};

struct explosion
{
  character* Terrorist;
  festring DeathMsg;
  v2 Pos;
  ulong ID;
  int Strength;
  int RadiusSquare;
  int Size;
  bool HurtNeutrals;
};

struct beamdata
{
  beamdata(character*, const festring&, int, ulong);
  beamdata(character*, const festring&, v2, col16, int, int, int, ulong);
  character* Owner;
  festring DeathMsg;
  v2 StartPos;
  col16 BeamColor;
  int BeamEffect;
  int Direction;
  int Range;
  ulong SpecialParameters;
};

inline beamdata::beamdata
(
  character* Owner,
  const festring& DeathMsg,
  int Direction,
  ulong SpecialParameters
) :
Owner(Owner),
DeathMsg(DeathMsg),
Direction(Direction),
SpecialParameters(SpecialParameters)
{ }

inline beamdata::beamdata
(
  character* Owner,
  const festring& DeathMsg,
  v2 StartPos,
  col16 BeamColor,
  int BeamEffect,
  int Direction,
  int Range,
  ulong SpecialParameters
) :
Owner(Owner),
DeathMsg(DeathMsg),
StartPos(StartPos),
BeamColor(BeamColor),
BeamEffect(BeamEffect),
Direction(Direction),
Range(Range),
SpecialParameters(SpecialParameters)
{ }

class level : public area
{
 public:
  level();
  virtual ~level();
  void Generate(int);
  v2 GetRandomSquare(const character* = 0, int = 0, const rect* = 0) const;
  void GenerateMonsters();
  lsquare* GetLSquare(v2 Pos) const { return Map[Pos.X][Pos.Y]; }
  lsquare* GetLSquare(int x, int y) const { return Map[x][y]; }
  void GenerateTunnel(int, int, int, int, bool);
  void ExpandPossibleRoute(int, int, int, int, bool);
  void ExpandStillPossibleRoute(int, int, int, int, bool);
  void Save(outputfile&) const;
  void Load(inputfile&);
  void FiatLux();
  int GetIdealPopulation() const { return IdealPopulation; }
  double GetDifficulty() const { return Difficulty; }
  void GenerateNewMonsters(int, bool = true);
  void AttachPos(int, int);
  void AttachPos(v2 Pos) { AttachPos(Pos.X, Pos.Y); }
  void CreateItems(int);
  bool MakeRoom(const roomscript*);
  void ParticleTrail(v2, v2);
  festring GetLevelMessage() { return LevelMessage; }
  void SetLevelMessage(const festring& What) { LevelMessage = What; }
  void SetLevelScript(const levelscript* What) { LevelScript = What; }
  bool IsOnGround() const;
  const levelscript* GetLevelScript() const { return LevelScript; }
  int GetLOSModifier() const;
  room* GetRoom(int) const;
  void SetRoom(int, room*);
  void AddRoom(room*);
  void Explosion(character*, const festring&, v2, int, bool = true);
  bool CollectCreatures(charactervector&, character*, bool);
  void ApplyLSquareScript(const squarescript*);
  virtual void Draw(bool) const;
  v2 GetEntryPos(const character*, int) const;
  void GenerateRectangularRoom(std::vector<v2>&, std::vector<v2>&, std::vector<v2>&, const roomscript*, room*, v2, v2);
  void Reveal();
  static void (level::*GetBeam(int))(beamdata&);
  void ParticleBeam(beamdata&);
  void LightningBeam(beamdata&);
  void ShieldBeam(beamdata&);
  dungeon* GetDungeon() const { return Dungeon; }
  void SetDungeon(dungeon* What) { Dungeon = What; }
  int GetIndex() const { return Index; }
  void SetIndex(int What) { Index = What; }
  bool DrawExplosion(const explosion*) const;
  int TriggerExplosions(int);
  lsquare*** GetMap() const { return Map; }
  v2 GetNearestFreeSquare(const character*, v2, bool = true) const;
  v2 FreeSquareSeeker(const character*, v2, v2, int, bool) const;
  v2 GetFreeAdjacentSquare(const character*, v2, bool) const;
  static void (level::*GetBeamEffectVisualizer(int))(const fearray<lsquare*>&, col16) const;
  void ParticleVisualizer(const fearray<lsquare*>&, col16) const;
  void LightningVisualizer(const fearray<lsquare*>&, col16) const;
  bool PreProcessForBone();
  bool PostProcessForBone();
  void FinalProcessForBone();
  void GenerateDungeon(int);
  void GenerateDesert();
  void GenerateJungle();
  void GenerateSteppe();
  void GenerateLeafyForest();
  void GenerateEvergreenForest();
  void GenerateTundra();
  void GenerateGlacier();
  void CreateTunnelNetwork(int, int, int, int, v2);
  void SetWalkability(v2 Pos, int What) { WalkabilityMap[Pos.X][Pos.Y] = What; }
  node* FindRoute(v2, v2, const std::set<v2>&, int, const character* = 0);
  void AddToAttachQueue(v2);
  void CollectEverything(itemvector&, charactervector&);
  void CreateGlobalRain(liquid*, v2);
  void CheckSunLight();
  col24 GetSunLightEmitation() const { return SunLightEmitation; }
  void InitSquarePartEmitationTicks();
  col24 GetAmbientLuminance() const { return AmbientLuminance; }
  void ForceEmitterNoxify(const emittervector&) const;
  void ForceEmitterEmitation(const emittervector&, const sunemittervector&, ulong = 0) const;
  void UpdateLOS();
  void EnableGlobalRain();
  void DisableGlobalRain();
  void InitLastSeen();
  lsquare** GetSquareStack() const { return SquareStack; }
  col24 GetNightAmbientLuminance() const { return NightAmbientLuminance; }
  int DetectMaterial(const material*);
  void BlurMemory();
  void CalculateLuminances();
  int AddRadiusToSquareStack(v2, long) const;
  olterrain* GetRandomFountainWithWater(olterrain*) const;
  int GetEnchantmentMinusChance() { return EnchantmentMinusChance; }
  int GetEnchantmentPlusChance() { return EnchantmentPlusChance; }
  void Amnesia(int);
  spawnresult SpawnMonsters(characterspawner, team*, v2, int = 0, int = 1, bool = false);
 protected:
  bool GenerateLanterns(int, int, int) const;
  bool GenerateWindows(int, int) const;
  void CreateRoomSquare(glterrain*, olterrain*, int, int, int, int) const;
  void EmitSunBeams();
  void EmitSunBeam(v2, ulong, int) const;
  void ChangeSunLight();
  void EmitSunLight(v2);
  lsquare*** Map;
  const levelscript* LevelScript;
  festring LevelMessage;
  std::vector<v2> Door;
  std::vector<room*> Room;
  int IdealPopulation;
  int MonsterGenerationInterval;
  double Difficulty;
  dungeon* Dungeon;
  int Index;
  std::vector<explosion*> ExplosionQueue;
  std::vector<bool> PlayerHurt;
  node*** NodeMap;
  uchar** WalkabilityMap;
  std::vector<v2> AttachQueue;
  liquid* GlobalRainLiquid;
  v2 GlobalRainSpeed;
  col24 SunLightEmitation;
  v2 SunLightDirection;
  col24 AmbientLuminance;
  static ulong NextExplosionID;
  lsquare** SquareStack;
  col24 NightAmbientLuminance;
  int EnchantmentMinusChance;
  int EnchantmentPlusChance;
};

outputfile& operator<<(outputfile&, const level*);
inputfile& operator>>(inputfile&, level*&);

#endif
