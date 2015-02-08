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

#ifndef __ACTION_H__
#define __ACTION_H__

#include "typedef.h"
#include "ivandef.h"

class character;
class action;
class outputfile;
class inputfile;

typedef action* (*actionspawner)(character*);

class actionprototype
{
 public:
  actionprototype(actionspawner, const char*);
  action* SpawnAndLoad(inputfile&) const;
  const char* GetClassID() const { return ClassID; }
  int GetIndex() const { return Index; }
 private:
  int Index;
  actionspawner Spawner;
  const char* ClassID;
};

class action
{
 public:
  typedef actionprototype prototype;
  action()  : m_actor(0), Flags(0) { }
  virtual ~action() { }
  virtual void Handle() = 0;
  virtual void Terminate(bool);
  character* GetActor() const { return m_actor; }
  void SetActor(character* What) { m_actor = What; }
  virtual bool IsVoluntary() const { return true; }
  virtual bool AllowUnconsciousness() const { return true; }
  virtual bool AllowFoodConsumption() const { return true; }
  virtual bool TryDisplace() const { return true; }
  virtual void Save(outputfile&) const;
  virtual void Load(inputfile&);
  virtual bool IsRest() const { return false; }
  virtual const prototype* GetProtoType() const = 0;
  int GetType() const { return GetProtoType()->GetIndex(); }
  virtual const char* GetDescription() const = 0;
  bool InDNDMode() const { return Flags & IN_DND_MODE; }
  void ActivateInDNDMode() { Flags |= IN_DND_MODE; }
  virtual bool ShowEnvironment() const { return true; }
  virtual const char* GetDeathExplanation() const { return ""; }
  virtual bool CanBeTalkedTo() const { return true; }
  virtual bool IsUnconsciousness() const { return false; }
 protected:
  ulong Flags;
private:
  character* m_actor;
};

template <class type, class base>
class actionsysbase : public base
{
 public:
  typedef actionsysbase mybase;
  static type* Spawn(character* Actor)
  {
    type* T = new type;
    T->SetActor(Actor);
    return T;
  }
  virtual const actionprototype* GetProtoType() const { return &ProtoType; }
  static const actionprototype ProtoType;
};

#ifdef __FILE_OF_STATIC_ACTION_PROTOTYPE_DEFINITIONS__
#define ACTION_PROTO(name)\
template<> const actionprototype\
  name##sysbase::ProtoType((actionspawner)(&name##sysbase::Spawn), #name);
#else
#define ACTION_PROTO(name)
#endif

#define ACTION(name, base)\
class name;\
typedef actionsysbase<name, base> name##sysbase;\
ACTION_PROTO(name)\
class name : public name##sysbase

#endif
