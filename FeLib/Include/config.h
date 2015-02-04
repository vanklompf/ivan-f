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

#ifndef __CONFIG_H__
#define __CONFIG_H__

#include <fstream>

#include "festring.h"
#include "felibdef.h"

class inputfile;
class felist;
struct configoption;
struct stringoption;
struct numberoption;
struct truthoption;

class configsystem
{
 public:
  static bool Save();
  static bool Load();
  static void Show(void (*)() = 0, void (*)(felist&) = 0, bool = false);
  static void AddOption(configoption*);
  static void NormalStringDisplayer(const stringoption*, festring&);
  static void NormalNumberDisplayer(const numberoption*, festring&);
  static void NormalTruthDisplayer(const truthoption*, festring&);
  static bool NormalStringChangeInterface(stringoption*);
  static bool NormalNumberChangeInterface(numberoption*);
  static bool NormalTruthChangeInterface(truthoption*);
  static void NormalStringChanger(stringoption*, const festring&);
  static void NormalNumberChanger(numberoption*, long);
  static void NormalTruthChanger(truthoption*, bool);
  static void SetConfigFileName(const festring& What)
  { ConfigFileName = What; }
 private:
  static configoption* Option[MAX_CONFIG_OPTIONS];
  static festring ConfigFileName;
  static int Options;
};

/* Currently there's no human-readable output option in outputfile,
   so we're forced to use std::ofstream */

struct configoption
{
  configoption(const char*, const char*);
  virtual ~configoption() { }
  virtual void SaveValue(std::ofstream&) const = 0;
  virtual void LoadValue(inputfile&) = 0;
  virtual bool ActivateChangeInterface() = 0;
  virtual void DisplayeValue(festring&) const = 0;
  const char* Name;
  const char* Description;
};

struct stringoption : public configoption
{
  stringoption(const char*, const char*, const festring&,
	       void (*)(const stringoption*, festring&)
	       = &configsystem::NormalStringDisplayer,
	       bool (*)(stringoption*)
	       = &configsystem::NormalStringChangeInterface,
	       void (*)(stringoption*, const festring&)
	       = &configsystem::NormalStringChanger);
  virtual void SaveValue(std::ofstream&) const;
  virtual void LoadValue(inputfile&);
  virtual void DisplayeValue(festring& Entry) const
  { ValueDisplayer(this, Entry); }
  virtual bool ActivateChangeInterface() { return ChangeInterface(this); }
  void ChangeValue(const festring& What) { ValueChanger(this, What); }
  festring Value;
  void (*ValueDisplayer)(const stringoption*, festring&);
  bool (*ChangeInterface)(stringoption*);
  void (*ValueChanger)(stringoption*, const festring&);
};

struct numberoption : public configoption
{
  numberoption(const char*, const char*, long,
	       void (*)(const numberoption*, festring&)
	       = &configsystem::NormalNumberDisplayer,
	       bool (*)(numberoption*)
	       = &configsystem::NormalNumberChangeInterface,
	       void (*)(numberoption*, long)
	       = &configsystem::NormalNumberChanger);
  virtual void SaveValue(std::ofstream&) const;
  virtual void LoadValue(inputfile&);
  virtual void DisplayeValue(festring& Entry) const
  { ValueDisplayer(this, Entry); }
  virtual bool ActivateChangeInterface() { return ChangeInterface(this); }
  void ChangeValue(long What) { ValueChanger(this, What); }
  long Value;
  void (*ValueDisplayer)(const numberoption*, festring&);
  bool (*ChangeInterface)(numberoption*);
  void (*ValueChanger)(numberoption*, long);
};

struct scrollbaroption : public numberoption
{
  scrollbaroption(const char*, const char*, long,
		  void (*)(const numberoption*, festring&),
		  bool (*)(numberoption*),
		  void (*)(numberoption*, long)
		  = &configsystem::NormalNumberChanger,
		  void (*)(long) = 0);
  void (*BarHandler)(long);
};

struct truthoption : public configoption
{
  truthoption(const char*, const char*, bool,
	      void (*)(const truthoption*, festring&)
	      = &configsystem::NormalTruthDisplayer,
	      bool (*)(truthoption*)
	      = &configsystem::NormalTruthChangeInterface,
	      void (*)(truthoption*, bool)
	      = &configsystem::NormalTruthChanger);
  virtual void SaveValue(std::ofstream&) const;
  virtual void LoadValue(inputfile&);
  virtual void DisplayeValue(festring& Entry) const
  { ValueDisplayer(this, Entry); }
  virtual bool ActivateChangeInterface() { return ChangeInterface(this); }
  void ChangeValue(bool What) { ValueChanger(this, What); }
  bool Value;
  void (*ValueDisplayer)(const truthoption*, festring&);
  bool (*ChangeInterface)(truthoption*);
  void (*ValueChanger)(truthoption*, bool);
};

#endif
