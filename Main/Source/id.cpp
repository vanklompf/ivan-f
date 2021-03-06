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

#include "id.h"
#include "game.h"
#include "god.h"
#include "festring.h"

void id::AddNameSingular(festring& String, bool Articled) const
{
  if(Articled)
    if(UsesLongArticle())
      String << "an ";
    else
      String << "a ";

  String << GetNameSingular();
}

void id::AddName(festring& Name, int Case) const
{
  bool Articled;

  if((Case & ARTICLE_BIT) && (GetArticleMode() == FORCE_THE || (!GetArticleMode() && !(Case & INDEFINE_BIT))))
  {
    Name << "the ";
    Articled = false;
  }
  else
    Articled = !(Case & PLURAL) && (Case & ARTICLE_BIT) && (Case & INDEFINE_BIT) && GetArticleMode() != NO_ARTICLE;

  if(AddRustLevelDescription(Name, Articled))
    Articled = false;

  if(AddAdjective(Name, Articled))
    Articled = false;

  if(ShowMaterial() && AddMaterialDescription(Name, Articled))
    Articled = false;

  if(Case & PLURAL)
    Name << GetNamePlural();
  else
    AddNameSingular(Name, Articled);

  AddPostFix(Name);
}

festring id::GetName(int Case) const
{
  static festring Name;
  Name.Empty();
  AddName(Name, Case);
  return Name;
}

void id::AddName(festring& Name, int Case, int Amount) const
{
  if(Amount == 1)
    AddName(Name, Case&~PLURAL);
  else
  {
    if((Case & ARTICLE_BIT) && (GetArticleMode() == FORCE_THE || (!GetArticleMode() && !(Case & INDEFINE_BIT))))
      Name << "the ";

    Name << Amount << ' ';
    AddName(Name, Case&~ARTICLE_BIT|PLURAL);
  }
}

festring id::GetName(int Case, int Amount) const
{
  static festring Name;
  Name.Empty();
  AddName(Name, Case, Amount);
  return Name;
}

bool id::AddAdjective(festring& String, bool Articled) const
{
  if(GetAdjective().GetSize())
  {
    if(Articled)
      if(UsesLongAdjectiveArticle())
	String << "an ";
      else
	String << "a ";

    String << GetAdjective() << ' ';
    return true;
  }
  else
    return false;
}

void id::AddPostFix(festring& String) const
{
  if(GetPostFix().GetSize())
    String << ' ' << GetPostFix();
}

bool id::AddActiveAdjective(festring& String, bool Articled) const
{
  String << (Articled ? "an active " : "active ");
  return true;
}
