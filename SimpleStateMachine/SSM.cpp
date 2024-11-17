//
//  SSM.cpp
//  Simple State Machine
//
//  Created by Prashant Gurung on 12/11/2024.
//
#include "SSM.h"

SSM::SSM(BYTE maxStates, BYTE initialState)
    : MAX_STATES(maxStates), m_currentState(initialState), m_newState(0) {}

BYTE SSM::getCurrentState() { return m_currentState; }

void SSM::setCurrentState(const BYTE newState) { m_currentState = newState; }

void SSM::ExternalEvent(const BYTE newEvent, const EventData *data) {
  if (newEvent == EVENT_IGNORED) {
    if (data)
      delete data;
    std::cout << "Event Ignored" << std::endl;
    return;
  }
  if (newEvent >= MAX_STATES) {
    std::cout << std::endl;
    std::cout << "Invalid State. New State value is not in the enum"
              << std::endl;
    return;
  }
  m_EventData = data;
  m_newState = newEvent;
  StateEngine();
}

void SSM::InternalAction(const BYTE newEvent, const EventData *data) {
  if (newEvent >= MAX_STATES) {
    std::cout << std::endl;
    std::cout << "Invalid State. New State value is not in the enum"
              << std::endl;
    return;
  }

  m_newState = newEvent;
}

void SSM::StateEngine() {
  const EventData *tempData = m_EventData;
  m_EventData = nullptr;

  const StateFunctionMap *stFuncMap = GetStateFunctionMap();
  const GuardBase *guard = stFuncMap[m_newState].guardCondtion;
  const StateBase *state = stFuncMap[m_newState].stateAction;

  std::cout << std::endl;
  bool guardResult = true;
  if (guard != nullptr) {
    guardResult = guard->InvokeGuardCondition(this, tempData);
  }
  if (guardResult) {

    setCurrentState(m_newState);
    state->InvokeStateAction(this, tempData);
    std::cout << std::endl;
    std::cout << "Changed to new state " << m_newState << " successfully"
              << std::endl;

  } else {
    std::cout << "Cannot set new state " << m_newState << std::endl;
  }
  if (tempData)
    delete tempData;
}
