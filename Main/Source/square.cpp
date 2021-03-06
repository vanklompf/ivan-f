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

#include "allocate.h"
#include "char.h"
#include "game.h"
#include "graphics.h"
#include "bitmap.h"
#include "terra.h"
#include "proto.h"
#include "save.h"
#include "team.h"

square::square(area* AreaUnder, v2 Pos) : AreaUnder(AreaUnder), Character(0), Pos(Pos), Luminance(0), Flags(IS_TRANSPARENT|MEMORIZED_UPDATE_REQUEST|DESCRIPTION_CHANGE), StaticAnimatedEntities(0), AnimatedEntities(0), LastSeen(0) { }

square::~square()
{
  character* Char = GetCharacter();

  if(Char)
  {
    for(int c = 0; c < Char->GetSquaresUnder(); ++c)
      Char->GetSquareUnder(c)->Character = 0;

    delete Char;
  }
}

void square::Save(outputfile& SaveFile) const
{
  if(!Character || Character->IsMainPos(Pos))
    SaveFile << Character;

  SaveFile << StaticAnimatedEntities << AnimatedEntities << MemorizedDescription;
}

void square::Load(inputfile& SaveFile)
{
  if(!Character)
    SaveFile >> Character;

  SaveFile >> StaticAnimatedEntities >> AnimatedEntities >> MemorizedDescription;
}

void square::AddCharacter(character* Guy)
{
  Character = Guy;
  Flags |= STRONG_NEW_DRAW_REQUEST;

  if(Guy->IsAnimated())
    IncAnimatedEntities();

  Guy->CheckIfSeen();
}

void square::RemoveCharacter()
{
  if(Character && Character->IsAnimated())
    DecAnimatedEntities();

  Character = 0;
  Flags |= STRONG_NEW_DRAW_REQUEST;
}

const char* square::SurviveMessage(character* Char) const
{
  if(GetOTerrain() && !Char->CanMoveOn(GetOTerrain()))
    return GetOTerrain()->SurviveMessage();
  else
    return GetGTerrain()->SurviveMessage();
}

const char* square::MonsterSurviveMessage(character* Char) const
{
  if(GetOTerrain() && !Char->CanMoveOn(GetOTerrain()))
    return GetOTerrain()->MonsterSurviveMessage();
  else
    return GetGTerrain()->MonsterSurviveMessage();
}

const char* square::DeathMessage(character* Char) const
{
  if(GetOTerrain() && !Char->CanMoveOn(GetOTerrain()))
    return GetOTerrain()->DeathMessage();
  else
    return GetGTerrain()->DeathMessage();
}

const char* square::MonsterDeathVerb(character* Char) const
{
  if(GetOTerrain() && !Char->CanMoveOn(GetOTerrain()))
    return GetOTerrain()->MonsterDeathVerb();
  else
    return GetGTerrain()->MonsterDeathVerb();
}

const char* square::ScoreEntry(character* Char) const
{
  if(GetOTerrain() && !Char->CanMoveOn(GetOTerrain()))
    return GetOTerrain()->ScoreEntry();
  else
    return GetGTerrain()->ScoreEntry();
}

bool square::IsFatalToStay() const
{
  return GetGTerrain()->IsFatalToStay() || (GetOTerrain() && GetOTerrain()->IsFatalToStay());
}

int square::GetEntryDifficulty() const
{
  return GetGTerrain()->GetEntryDifficulty();
}

int square::GetRestModifier() const
{
  return GetOTerrain() ? GetOTerrain()->GetRestModifier() : 1;
}

bool square::CanBeSeenBy(const character* Who, bool IgnoreDarkness) const
{
  if(Who->IsPlayer())
    return CanBeSeenByPlayer(IgnoreDarkness);
  else
    return CanBeSeenFrom(Who->GetPos(), Who->GetLOSRangeSquare(), IgnoreDarkness);
}

void square::SurviveEffect(character* Who)
{
  if(GetOTerrain())
    GetOTerrain()->SurviveEffect(Who);

  GetGTerrain()->SurviveEffect(Who);
}

square* square::GetNeighbourSquare(int I) const
{
  return AreaUnder->GetNeighbourSquare(Pos, I);
}

square* square::GetNearSquare(v2 Pos) const
{
  return AreaUnder->GetSquare(Pos);
}
