//
//  SSM.h
//  Simple State Machine
//
//  Created by Prashant Gurung on 12/11/2024.
//
#pragma once
#include <iostream>

typedef unsigned int BYTE;

class SSM;

class EventData {
public:
  virtual ~EventData() {}
};

class StateBase {
public:
  virtual void InvokeStateAction(SSM *sm, const EventData *data) const = 0;
};

class GuardBase {
public:
  virtual bool InvokeGuardCondition(SSM *sm, const EventData *data) const = 0;
};

template <class ssm, void (ssm::*Func)(const EventData *)>
class StateAction : public StateBase {
public:
  void InvokeStateAction(SSM *sm, const EventData *data) const {
    ssm *derivedSSM = static_cast<ssm *>(sm);
    (derivedSSM->*Func)(data); // Call the function of the StateAction Object
  }
};

template <class ssm, bool (ssm::*Func)(const EventData *)>
class GuardCondition : public GuardBase {
public:
  bool InvokeGuardCondition(SSM *sm, const EventData *data) const {
    ssm *derivedSSM = static_cast<ssm *>(sm);
    return (derivedSSM->*Func)(data);
  }
};

struct StateFunctionMap {
  const StateBase *stateAction;
  const GuardBase *guardCondtion;
};

class SSM {
public:
  SSM(BYTE max_states, BYTE initialState = 0);
  enum { EVENT_IGNORED = 0XFE,
         CANNOT_HAPPEN };

  // Get the pointer to the StateFunctionMap array initialized in the inheriting
  // class, e.g. Spell, because GetStateFunctionMap() will be returning pointer
  // to that array
  virtual StateFunctionMap *GetStateFunctionMap() = 0;

  void ExternalEvent(const BYTE newEvent, const EventData *data = nullptr);
  void InternalAction(const BYTE newEvent, const EventData *data = nullptr);

  void StateEngine();
  // void StateEngine(const );
  BYTE getCurrentState();
  void setCurrentState(const BYTE newState);
  virtual ~SSM(){};

private:
  const BYTE MAX_STATES;
  BYTE m_currentState;
  BYTE m_newState;
  const EventData *m_EventData;
};
