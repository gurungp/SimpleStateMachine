
#pragma once

#include "Spell.h"
#include "SSM.h"
#include <iostream>

Spell::Spell(std::initializer_list<float> times)
    : SSM(ST_MAXSTATES), m_cooldown(0), m_spellLevel(0), m_spellCDTimes(times),
      m_spellCDTimesDefault(times),
      m_lastCastTimePoint(std::chrono::system_clock::time_point{}),
      m_lastExpected_CD_FinishTime(std::chrono::system_clock::time_point{}),
      m_octarine(false) {
  // THE m_spellCDTimes should be set and should not be empty
}

void Spell::st_func_NotLearned(const EventData *data) {
  std::cout << std::endl;
  std::cout << "Not Learned" << std::endl;
}

void Spell::st_func_LearnAndReady(const EventData *data) {

  playSound("../Sounds/General/Learning.mp3");
  std::cout << "--------LEARN--------" << std::endl;

  std::cout << "Current Cooldown Time setting to "
            << m_spellCDTimes[m_spellLevel] << std::endl;
  m_lastCooldown = m_cooldown;
  m_cooldown = m_spellCDTimes[m_spellLevel];
  ++m_spellLevel;
}
void Spell::st_func_Casting(const EventData *data) {
  std::cout << "--------CASTING--------" << std::endl;

  std::cout << std::endl;
  std::cout << "Casting and Setting Cast time" << std::endl;
  m_lastCastTimePoint = std::chrono::system_clock::now();

  // Calculate the time at which the CD will end with the current CD Time
  auto durationToAdd =
      std::chrono::duration_cast<std::chrono::system_clock::duration>(
          std::chrono::duration<float>(m_cooldown));

  m_lastExpected_CD_FinishTime = m_lastCastTimePoint + durationToAdd;

  std::cout << "Moving to ON_COOLDOWN state" << std::endl;
  InternalAction(ST_ON_COOLDOWN,
                 nullptr); // After casting it immediately goes to Cooldown
}
void Spell::st_func_On_Cooldown(const EventData *data) {
  playSound("../Sounds/General/On Cooldown.mp3");
  std::cout << "On Cooldown" << std::endl;
}

// GUARD CONDITION FUCNTION

bool Spell::gd_func_checkIfLevelFull(const EventData *) {

  std::cout << "--------GUARD-IF-PROCEED-TO-LEVEL-UP--------" << std::endl;
  std::cout << "Current spell level is " << m_spellLevel << std::endl;
  std::cout << "Current Cooldown time is " << m_cooldown << std::endl;
  if (m_spellLevel >= m_spellCDTimes.size()) {
    std::cout << "Guard: Level Already Full" << std::endl;
    return false;
  } else {
    std::cout << "Guard: Proceed Leveling Up" << std::endl;
    return true;
  }
}

bool Spell::gd_func_checkOnCooldown(const EventData *data) {
  std::cout << "--------GUARD-CHECK-ON-COOLDOWN--------" << std::endl;

  auto currentTime = std::chrono::system_clock::now();
  std::cout << "Last expected CD time to finish: "
            << m_lastExpected_CD_FinishTime << std::endl;
  std::cout << "Current time: " << currentTime << std::endl;
  bool proceed = !onCoolDown(); // proceed = true if its not in cooldown. if its
                                // on cool down then proceeding for guard
                                // function is false otherwise guard function
                                // should proceed by equating to true
  if (proceed == false)
    std::cout << "Not on Cooldown " << std::endl;
  else
    std::cout << "Last expected CD Still not finished" << std::endl;

  return proceed;
  //
  // std::cout << "Checking On Cooldown" << std::endl;
  // if (m_spellLevel == 0) // first time learning/leveling up the spell
  // {
  //   return true;
  // }
  // auto timeElaspedinSeconds =
  // std::chrono::duration_cast<std::chrono::seconds>(
  //                                 currentTime - m_lastCastTimePoint)
  //                                 .count();
  // if (m_cooldown <= timeElaspedinSeconds) {
  //   std::cout << "Not in Cooldown. Proceed to Casting " << std::endl;

  //   // InternalAction(ST_LEARN_AND_READY, NULL);
  //   return true;
  // } else {
  //   return false;
  // }
}

void Spell::learnSpell(const EventData *data) {
  static const BYTE TRANSITIONS[] = {
      ST_LEARN_AND_READY, // NOT_LEARNED,
      ST_LEARN_AND_READY, // LEARN AND READY,
      ST_LEARN_AND_READY, // CASTING,
      ST_LEARN_AND_READY, // ON_COOLDOWN
  };

  ExternalEvent(TRANSITIONS[getCurrentState()], data);
}

void Spell::castSpell(const EventData *data) {

  static const BYTE TRANSITIONS[] = {
      EVENT_IGNORED, // NOT_LEARNED
      ST_CASTING,    // LEARN AND READY
      ST_CASTING,    // CASTING
      ST_CASTING,    // ON_COOLDOWN
  };
  ExternalEvent(TRANSITIONS[getCurrentState()], data);
}

bool Spell::onCoolDown() {
  auto currentTime = std::chrono::system_clock::now();
  if (m_lastExpected_CD_FinishTime < currentTime) {
    return false; // if the last expected CD finish time is already passed(less
                  // than current time) then onCooldown is false or it is not on
                  // cool down
  } else {

    playSound("../Sounds/General/On Cooldown.mp3");
    return true;
  }
}
void Spell::useRefresher() {
  m_lastCastTimePoint = std::chrono::system_clock::time_point{};
  m_lastExpected_CD_FinishTime = std::chrono::system_clock::time_point{};
}

void Spell::setOctarine(bool value) {
  m_octarine = value;
  if (m_octarine) {
    for (int i = 0; i < m_spellCDTimes.size(); i++) {
      float spell_time = m_spellCDTimes[i];
      m_spellCDTimes[i] = (spell_time) - (0.25 * spell_time);
    }
  } else {

    m_spellCDTimes = m_spellCDTimesDefault;
  }
}

void Spell::print_SpellTimes() {
  int i = 1;
  for (float time : m_spellCDTimes) {
    std::cout << i << ". Time: " << time << std::endl;
    i++;
  }
  std::cout << std::endl;
}
