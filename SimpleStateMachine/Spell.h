//
//  Spell.h
//  SimpleStateMachine
//
//  Created by Prashant Gurung on 13/11/2024.
//

#ifndef Spell_h
#define Spell_h

#include "PlaySound.h"
#include "SSM.h"
#include <chrono>
#include <initializer_list>
#include <string>
#include <vector>
class Spell : public SSM {

public:
  Spell(std::initializer_list<float> times);

public:
  enum StateBase {
    ST_NOTLEARNED,
    ST_LEARN_AND_READY,
    ST_CASTING,
    ST_ON_COOLDOWN,
    ST_MAXSTATES,
  };

  const std::string states[4] = {"ST_NOTLEARNED", "ST_LEARN", "ST_READY",
                                 "ST_ON_COOLDOWN"};

  float m_cooldown;
  float m_lastCooldown;
  int m_spellLevel;
  std::vector<float> m_spellCDTimes;
  std::vector<float> m_spellCDTimesDefault;
  std::chrono::system_clock::time_point m_lastCastTimePoint;
  std::chrono::system_clock::time_point m_lastExpected_CD_FinishTime;
  bool m_octarine;

  // State and Guard Functions
  void st_func_NotLearned(const EventData *); // variable name is not necessary
  void st_func_LearnAndReady(const EventData *);
  void st_func_Casting(const EventData *);
  void st_func_On_Cooldown(const EventData *);
  bool gd_func_checkOnCooldown(const EventData *);  // guard function
  bool gd_func_checkIfLevelFull(const EventData *); // guard function

  // General Functions
  bool onCoolDown();
  void useRefresher();
  void setOctarine(bool val);
  void print_SpellTimes();

  const StateAction<Spell, &Spell::st_func_NotLearned> func_NotLearned;
  const StateAction<Spell, &Spell::st_func_LearnAndReady> func_LearnAndReady;
  const StateAction<Spell, &Spell::st_func_Casting> func_Casting;
  const StateAction<Spell, &Spell::st_func_On_Cooldown> func_On_Cooldown;
  const GuardCondition<Spell, &Spell::gd_func_checkOnCooldown>
      func_checkOnCooldown;
  const GuardCondition<Spell, &Spell::gd_func_checkIfLevelFull>
      func_checkIfFullLevel;
  StateFunctionMap *GetStateFunctionMap() {
    static StateFunctionMap stFuncMap[] = {
        {&func_NotLearned, nullptr},
        {&func_LearnAndReady, &func_checkIfFullLevel},
        {&func_Casting, &func_checkOnCooldown},
        {&func_On_Cooldown, &func_checkOnCooldown},

    };
    return stFuncMap;
  };

  void learnSpell(const EventData *data);
  void castSpell(const EventData *data);
};

#endif /* Spell_h */
