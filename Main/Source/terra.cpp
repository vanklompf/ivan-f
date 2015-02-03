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

/* TODO: too much includes? */
#include "allocate.h"
#include "char.h"
#include "game.h"
#include "graphics.h"
#include "bitmap.h"
#include "terra.h"
#include "proto.h"
#include "save.h"
#include "team.h"

const char* terrain::SurviveMessage() const
{
  return "somehow you survive";
}
const char* terrain::MonsterSurviveMessage() const
{
  return "somehow survives";
}
const char* terrain::DeathMessage() const
{
  return "strangely enough, you die";
}
const char* terrain::MonsterDeathVerb() const
{
  return "dies";
}
const char* terrain::ScoreEntry() const
{
  return "died on unfriendly terrain";
}
