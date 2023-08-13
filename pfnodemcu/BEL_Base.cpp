#include "BEH_4_Base.hpp"
#include <Arduino.h>
#define BEAR_ESP8266
//#include <bearssl/bearssl.h>

namespace be {
/*
 * Copyright (c) 2015-2023, the Bennt Authors.
 *
 * SPDX-License-Identifier: BSD-2-Clause
 *
 * Licensed under the BSD 2-Clause License (the "License").
 * See the LICENSE file in the project root for more information.
 *
 */

std::unordered_map<std::string, int32_t> BECS_Ids::callIds;
std::unordered_map<int32_t, std::string> BECS_Ids::idCalls;

#ifdef BEDCC_PT
thread_local BECS_FrameStack BECS_Runtime::bevs_currentStack;
#endif

#ifndef BEDCC_PT
BECS_FrameStack BECS_Runtime::bevs_currentStack;
#endif

uint_fast16_t BECS_Runtime::bevg_currentGcMark = 1;

#ifdef BEDCC_PT
std::atomic<uint_fast16_t> BECS_Runtime::bevg_gcState{0};
std::atomic<uint_fast32_t> BECS_Runtime::bevg_sharedAllocsSinceGc{0};
#endif

#ifdef BEDCC_PT
std::map<std::thread::id, BECS_FrameStack*> BECS_Runtime::bevg_frameStacks;
#endif

BECS_FrameStack BECS_Runtime::bevg_oldInstsStack;

#ifdef BEDCC_PT
std::recursive_mutex BECS_Runtime::bevs_initLock;
std::mutex BECS_Runtime::bevg_gcLock;
std::condition_variable BECS_Runtime::bevg_gcWaiter;
#endif

uint_fast64_t BECS_Runtime::bevg_countGcs = 0;
uint_fast64_t BECS_Runtime::bevg_countSweeps = 0;
uint_fast64_t BECS_Runtime::bevg_countDeletes = 0;
uint_fast64_t BECS_Runtime::bevg_countRecycles = 0;
uint_fast64_t BECS_Runtime::bevg_countAllocs = 0;
uint_fast64_t BECS_Runtime::bevg_maxHs = 0;

void BECS_Lib::putCallId(std::string name, int32_t iid) {
    BECS_Ids::callIds[name] = iid;
    BECS_Ids::idCalls[iid] = name;
}
    
int32_t BECS_Lib::getCallId(std::string name) {
    return BECS_Ids::callIds[name];
}
    
void BECS_Lib::putNlcSourceMap(std::string clname, std::vector<int32_t>& vals) {
  BECS_Runtime::smnlcs[clname] = vals;
}
    
void BECS_Lib::putNlecSourceMap(std::string clname, std::vector<int32_t>& vals) {
  BECS_Runtime::smnlecs[clname] = vals;  
}

BEC_2_4_6_TextString* BECS_Object::bemc_clnames() {
  return nullptr;  
}

BEC_2_4_6_TextString* BECS_Object::bemc_clfiles() {
  return nullptr; 
}

BEC_2_6_6_SystemObject* BECS_Object::bemc_create() {
  return nullptr;
}

void BECS_Object::bemc_setInitial(BEC_2_6_6_SystemObject* becc_inst) { }

BEC_2_6_6_SystemObject* BECS_Object::bemc_getInitial() {
 return nullptr; 
}

void BECS_Object::bemg_doMark() {
 
}

size_t BECS_Object::bemg_getSize() {
   return sizeof(*this);
}

#ifdef BEDCC_SGC
    BEC_2_6_6_SystemObject* BECS_Object::bems_methodNotDefined(int32_t callId, std::vector<BEC_2_6_6_SystemObject*> args) {
#endif  

  BEC_2_6_6_SystemObject* soo = static_cast<BEC_2_6_6_SystemObject*>(this);

#ifdef BEDCC_SGC
  struct bes {  BEC_2_9_4_ContainerList* beArgs; BEC_2_4_6_TextString* beCallId; BEC_2_6_6_SystemObject* bevr_this;  };
  BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
  bes* beq = (bes*) bevs_myStack->bevs_hs;
  beq->beArgs = nullptr;
  beq->beCallId = nullptr;
  beq->bevr_this = soo;
  BECS_StackFrame bevs_stackFrame(3);

#endif

  beq->beArgs = new BEC_2_9_4_ContainerList(args);
  beq->beCallId = new BEC_2_4_6_TextString(BECS_Ids::idCalls[callId]);
  return beq->bevr_this->bem_methodNotDefined_2(beq->beCallId, beq->beArgs);
}

//bemds
BEC_2_6_6_SystemObject* BECS_Object::bemd_0(int32_t callId) {
#ifdef BEDCC_SGC
  std::vector<BEC_2_6_6_SystemObject*> args = { };
#endif 
  return bems_methodNotDefined(callId, args);
}

BEC_2_6_6_SystemObject* BECS_Object::bemd_1(int32_t callId, BEC_2_6_6_SystemObject* bevd_0) {
#ifdef BEDCC_SGC
  std::vector<BEC_2_6_6_SystemObject*> args = { bevd_0 };
#endif
  return bems_methodNotDefined(callId, args);
}

BEC_2_6_6_SystemObject* BECS_Object::bemd_2(int32_t callId, BEC_2_6_6_SystemObject* bevd_0, BEC_2_6_6_SystemObject* bevd_1) {
#ifdef BEDCC_SGC
  std::vector<BEC_2_6_6_SystemObject*> args = { bevd_0, bevd_1 };
#endif
  return bems_methodNotDefined(callId, args);
}

BEC_2_6_6_SystemObject* BECS_Object::bemd_3(int32_t callId, BEC_2_6_6_SystemObject* bevd_0, BEC_2_6_6_SystemObject* bevd_1, BEC_2_6_6_SystemObject* bevd_2) {
#ifdef BEDCC_SGC
  std::vector<BEC_2_6_6_SystemObject*> args = { bevd_0, bevd_1, bevd_2 };
#endif
  return bems_methodNotDefined(callId, args);
}

BEC_2_6_6_SystemObject* BECS_Object::bemd_4(int32_t callId, BEC_2_6_6_SystemObject* bevd_0, BEC_2_6_6_SystemObject* bevd_1, BEC_2_6_6_SystemObject* bevd_2, BEC_2_6_6_SystemObject* bevd_3) {
#ifdef BEDCC_SGC
  std::vector<BEC_2_6_6_SystemObject*> args = { bevd_0, bevd_1, bevd_2, bevd_3 };
#endif  
  return bems_methodNotDefined(callId, args);
}

BEC_2_6_6_SystemObject* BECS_Object::bemd_5(int32_t callId, BEC_2_6_6_SystemObject* bevd_0, BEC_2_6_6_SystemObject* bevd_1, BEC_2_6_6_SystemObject* bevd_2, BEC_2_6_6_SystemObject* bevd_3, BEC_2_6_6_SystemObject* bevd_4) {
#ifdef BEDCC_SGC
  std::vector<BEC_2_6_6_SystemObject*> args = { bevd_0, bevd_1, bevd_2, bevd_3, bevd_4 };
#endif  
  return bems_methodNotDefined(callId, args);
}

BEC_2_6_6_SystemObject* BECS_Object::bemd_6(int32_t callId, BEC_2_6_6_SystemObject* bevd_0, BEC_2_6_6_SystemObject* bevd_1, BEC_2_6_6_SystemObject* bevd_2, BEC_2_6_6_SystemObject* bevd_3, BEC_2_6_6_SystemObject* bevd_4, BEC_2_6_6_SystemObject* bevd_5) {

#ifdef BEDCC_SGC
  std::vector<BEC_2_6_6_SystemObject*> args = { bevd_0, bevd_1, bevd_2, bevd_3, bevd_4, bevd_5 };
#endif  
  return bems_methodNotDefined(callId, args);
}

BEC_2_6_6_SystemObject* BECS_Object::bemd_7(int32_t callId, BEC_2_6_6_SystemObject* bevd_0, BEC_2_6_6_SystemObject* bevd_1, BEC_2_6_6_SystemObject* bevd_2, BEC_2_6_6_SystemObject* bevd_3, BEC_2_6_6_SystemObject* bevd_4, BEC_2_6_6_SystemObject* bevd_5, BEC_2_6_6_SystemObject* bevd_6) {
#ifdef BEDCC_SGC
  std::vector<BEC_2_6_6_SystemObject*> args = { bevd_0, bevd_1, bevd_2, bevd_3, bevd_4, bevd_5, bevd_6 };
#endif 
  return bems_methodNotDefined(callId, args);
}

#ifdef BEDCC_SGC
    BEC_2_6_6_SystemObject* BECS_Object::bemd_x(int32_t callId, BEC_2_6_6_SystemObject* bevd_0, BEC_2_6_6_SystemObject* bevd_1, BEC_2_6_6_SystemObject* bevd_2, BEC_2_6_6_SystemObject* bevd_3, BEC_2_6_6_SystemObject* bevd_4, BEC_2_6_6_SystemObject* bevd_5, BEC_2_6_6_SystemObject* bevd_6, std::vector<BEC_2_6_6_SystemObject*> bevd_x) {
#endif 

#ifdef BEDCC_SGC
  std::vector<BEC_2_6_6_SystemObject*> args = { bevd_0, bevd_1, bevd_2, bevd_3, bevd_4, bevd_5, bevd_6 };
#endif
  args.insert(args.end(), bevd_x.begin(), bevd_x.end());
  return bems_methodNotDefined(callId, args);
}

#ifdef BEDCC_SGC
  BEC_2_6_6_SystemObject* BECS_Object::bems_forwardCall(std::string mname, std::vector<BEC_2_6_6_SystemObject*> bevd_x, int32_t numargs) {
#endif
  return nullptr;
}

bool BECS_Runtime::isInitted = false;

BEC_2_5_4_LogicBool* BECS_Runtime::boolTrue;
BEC_2_5_4_LogicBool* BECS_Runtime::boolFalse;

std::unordered_map<std::string, BETS_Object*> BECS_Runtime::typeRefs;

//for setting up initial instances
BEC_2_6_11_SystemInitializer* BECS_Runtime::initializer;

BEC_2_6_6_SystemObject * BECS_Runtime::maino;

std::string BECS_Runtime::platformName;

int BECS_Runtime::argc;
char** BECS_Runtime::argv;

std::unordered_map<std::string, std::vector<int32_t>> BECS_Runtime::smnlcs;
std::unordered_map<std::string, std::vector<int32_t>> BECS_Runtime::smnlecs;

void BECS_Runtime::init() { 
    if (isInitted) { return; }
    isInitted = true;
    BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
    bevs_myStack->bevs_ohs = (BECS_Object**) malloc(BEDCC_GCHSS * sizeof(BECS_Object*));
    bevs_myStack->bevs_hs = bevs_myStack->bevs_ohs;
    BECS_Runtime::boolTrue = new BEC_2_5_4_LogicBool(true);
    BECS_Runtime::boolFalse = new BEC_2_5_4_LogicBool(false);
    BECS_Runtime::initializer = new BEC_2_6_11_SystemInitializer();
}

void BECS_Runtime::doGc() {

#ifdef BEDCC_SGC
#ifdef BED_GCSTATS
std::cout << "GCDEBUG starting gc " << std::endl;
#endif

  ////cout << "GCDEBUG starting gc " << endl;
  ////cout << "GCDEBUG thread " << std::this_thread::get_id() << endl;

  BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
  
  bevs_myStack->bevs_allocsSinceGc = 0;
  
#ifdef BEDCC_PT
  BECS_Runtime::bevg_sharedAllocsSinceGc.store(0, std::memory_order_release);
#endif
  
  BECS_Runtime::bevg_countGcs++;
  //increment gcmark
  BECS_Runtime::bevg_currentGcMark++;
  if (BECS_Runtime::bevg_currentGcMark > BEDCC_GCRWM) {
    BECS_Runtime::bevg_currentGcMark = 1;
    BECS_Runtime::bemg_zero();
  }
  //do all marking
  BECS_Runtime::bemg_markAll();
  if (BECS_Runtime::bevg_currentGcMark % BEDCC_GCMPERS == 0) {
    //do all sweeping
    BECS_Runtime::bevg_countSweeps++;
    BECS_Runtime::bemg_sweep();
  }

#ifdef BEDCC_PT
  BECS_Runtime::bevg_gcState.store(0, std::memory_order_release);
#endif

#ifdef BED_GCSTATS
std::cout << "GCDEBUG ending gc " << std::endl;
std::cout << "GCDEBUG recycles " << BECS_Runtime::bevg_countRecycles  << std::endl;
std::cout << "GCDEBUG allocs " << BECS_Runtime::bevg_countAllocs  << std::endl;
std::cout << "GCDEBUG maxHs " << BECS_Runtime::bevg_maxHs  << std::endl;
#endif

#endif

}

int32_t BECS_Runtime::getNlcForNlec(std::string clname, int32_t val) {
  
  if (smnlcs.count(clname) > 0 && smnlecs.count(clname) > 0) {
    std::vector<int32_t> sls = smnlcs[clname];
    std::vector<int32_t> esls = smnlecs[clname];
    //Console.WriteLine("esls is not null " + clname + " val " + val);
    int eslslen = esls.size();
    for (int i = 0;i < eslslen;i++) {
      //Console.WriteLine("esls i " + esls[i]);
      if (esls[i] == val) {
        return sls[i];
      }
    }
  } else {
    //Console.WriteLine("esls is null " + clname);
  }
  return -1;
}

void BECS_Runtime::bemg_markAll() {
  
#ifdef BEDCC_SGC

  //static std::unordered_map<std::string, BETS_Object*> typeRefs;
  
  //cout << "starting markAll" << endl;
  
  //runtime true, false, initter
  //static BEC_2_5_4_LogicBool* boolTrue;
  //static BEC_2_5_4_LogicBool* boolFalse;
  //static BEC_2_6_11_SystemInitializer* initializer;
  if (boolTrue != nullptr && boolTrue->bevg_gcMark != bevg_currentGcMark) {
    boolTrue->bemg_doMark();
  }
  if (boolFalse != nullptr && boolFalse->bevg_gcMark != bevg_currentGcMark) {
    boolFalse->bemg_doMark();
  }
  if (initializer != nullptr && initializer->bevg_gcMark != bevg_currentGcMark) {
    initializer->bemg_doMark();
  }
  if (maino != nullptr && maino->bevg_gcMark != bevg_currentGcMark) {
    maino->bemg_doMark();
  }
  
  //cout << "starting markAll typerefs" << endl;
  
  for (auto nt : typeRefs) {
    nt.second->bemgt_doMark();
  }
  
  //cout << "starting markAll stack" << endl;
  
  //BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
  //BECS_Runtime::bemg_markStack(bevs_myStack);
#ifdef BEDCC_PT  
  for(auto const &idStack : bevg_frameStacks) {
    bemg_markStack(idStack.second);
  }
#endif
#ifndef BEDCC_PT 
  BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
  bemg_markStack(bevs_myStack);
#endif
  bemg_markStack(&bevg_oldInstsStack);
  //cout << "ending markAll" << endl;

#endif
  
}

void BECS_Runtime::bemg_markStack(BECS_FrameStack* bevs_myStack) {
  
#ifdef BEDCC_SGC

  //decls
  BECS_Object* bevg_leo;

  //new pass
  BECS_Object** bevs_ohs = bevs_myStack->bevs_ohs;
  BECS_Object** bevs_hs = bevs_myStack->bevs_hs;
  bevg_leo = nullptr;
  while (bevs_ohs < bevs_hs) {
    bevg_leo = *(bevs_ohs);
    if (bevg_leo != nullptr && bevg_leo->bevg_gcMark != bevg_currentGcMark) {
      bevg_leo->bemg_doMark();
    }
    bevs_ohs++;
  }
  bevs_myStack->bevs_nextReuse = bevs_myStack->bevs_lastInst;

#ifdef BED_GCSTATS
  uint_fast64_t chs = (bevs_myStack->bevs_hs - bevs_myStack->bevs_ohs) / sizeof(BECS_Object*);
  if (chs > bevg_maxHs) {
    bevg_maxHs = chs;
  }
#endif

  //old pass
  /*bevs_currFrame = bevs_myStack->bevs_lastFrame;
  bevg_le = nullptr;
  while (bevs_currFrame != nullptr) {
    for (size_t i = 0; i < bevs_currFrame->bevs_numVars; i++) {
      bevg_le = *(bevs_currFrame->bevs_localVars[i]);
      if (bevg_le != nullptr && bevg_le->bevg_gcMark != bevg_currentGcMark) {
        bevg_le->bemg_doMark();
      }
    }
    bevg_le = bevs_currFrame->bevs_thiso;
    if (bevg_le != nullptr && bevg_le->bevg_gcMark != bevg_currentGcMark) {
      bevg_le->bemg_doMark();
    }
    bevs_currFrame = bevs_currFrame->bevs_priorFrame;
  }
  bevs_myStack->bevs_nextReuse = bevs_myStack->bevs_lastInst;*/
  
#endif

}

void BECS_Runtime::bemg_sweep() {

#ifdef BEDCC_SGC

#ifdef BED_GCSTATS
std::cout << "GCDEBUG starting sweep " << std::endl;
#endif

  //BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
  //BECS_Runtime::bemg_sweepStack(bevs_myStack);
#ifdef BEDCC_PT  
  for(auto const &idStack : bevg_frameStacks) {
    bemg_sweepStack(idStack.second);
  }
#endif
#ifndef BEDCC_PT 
  BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
  bemg_sweepStack(bevs_myStack);
#endif
  bemg_sweepStack(&bevg_oldInstsStack);

#ifdef BED_GCSTATS
std::cout << "GCDEBUG ending sweep " << std::endl;
#endif
  
#endif

}

void BECS_Runtime::bemg_sweepStack(BECS_FrameStack* bevs_myStack) {

#ifdef BEDCC_SGC

  uint_fast16_t bevg_currentGcMark = BECS_Runtime::bevg_currentGcMark;
  
  BECS_Object* bevs_lastInst = bevs_myStack->bevs_lastInst;
  
  if (bevs_lastInst != nullptr) {
    BECS_Object* bevs_currInst = bevs_lastInst->bevg_priorInst;
    while (bevs_currInst != nullptr && bevs_currInst->bevg_priorInst != nullptr) {
      if (bevs_currInst->bevg_gcMark != bevg_currentGcMark) {
        bevs_lastInst->bevg_priorInst = bevs_currInst->bevg_priorInst;
        delete bevs_currInst;
        bevs_currInst = bevs_lastInst->bevg_priorInst;
      } else {
        bevs_lastInst = bevs_currInst;
        bevs_currInst = bevs_currInst->bevg_priorInst;
      }
    }
  }

#endif

}

void BECS_Runtime::bemg_zero() {

#ifdef BEDCC_SGC

#ifdef BED_GCSTATS
std::cout << "GCDEBUG starting zero " << std::endl;
#endif

#ifdef BEDCC_PT  
  for(auto const &idStack : bevg_frameStacks) {
    bemg_zeroStack(idStack.second);
  }
#endif
#ifndef BEDCC_PT 
  BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
  bemg_zeroStack(bevs_myStack);
#endif
  bemg_zeroStack(&bevg_oldInstsStack);

#ifdef BED_GCSTATS
std::cout << "GCDEBUG ending zero " << std::endl;
#endif
  
#endif

}

void BECS_Runtime::bemg_zeroStack(BECS_FrameStack* bevs_myStack) {

#ifdef BEDCC_SGC
  
  BECS_Object* bevs_currInst = bevs_myStack->bevs_lastInst;
  
  while (bevs_currInst != nullptr) {
    bevs_currInst->bevg_gcMark = 0;
    bevs_currInst = bevs_currInst->bevg_priorInst;
  }

#endif

}

void BECS_Runtime::bemg_addMyFrameStack() {

#ifdef BEDCC_SGC
#ifdef BEDCC_PT 
  std::thread::id tid = std::this_thread::get_id();
  BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
  bevg_frameStacks[tid] = bevs_myStack;
#endif
#endif

}

void BECS_Runtime::bemg_deleteMyFrameStack() {

#ifdef BEDCC_SGC
#ifdef BEDCC_PT  
  //cout << "GCDEBUG dmfs b " << bevg_frameStacks.size() << endl;
  std::thread::id tid = std::this_thread::get_id();
  auto it = bevg_frameStacks.find(tid);
  bevg_frameStacks.erase(it);
  //cout << "GCDEBUG dmfs e " << bevg_frameStacks.size() << endl;
#endif
#endif

}

void BECS_Runtime::bemg_beginThread() {

#ifdef BEDCC_SGC
#ifdef BEDCC_PT 
  //cout << "GCDEBUG start begin thread" << endl;
  bevg_gcLock.lock();
  bemg_addMyFrameStack();
  bevg_gcLock.unlock();
  //cout << "GCDEBUG st do gc" << endl;
  bemg_checkDoGc();
#endif
#endif

}

void BECS_Runtime::bemg_endThread() {

#ifdef BEDCC_SGC
#ifdef BEDCC_PT
  //cout << "GCDEBUG start end thread" << endl;
  bevg_gcLock.lock();
  BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
  BECS_Object* bevs_lastInst = bevs_myStack->bevs_lastInst;
  
  if (bevs_lastInst != nullptr) {
    BECS_Object* bevs_currInst = bevs_lastInst;
    while (bevs_currInst != nullptr) {
      bevs_lastInst = bevs_currInst;
      bevs_currInst = bevs_currInst->bevg_priorInst;
    }
  }
  bevs_lastInst->bevg_priorInst = BECS_Runtime::bevg_oldInstsStack.bevs_lastInst;
  BECS_Runtime::bevg_oldInstsStack.bevs_lastInst = bevs_myStack->bevs_lastInst;
  
  bemg_deleteMyFrameStack();
  bevg_gcLock.unlock();
  //cout << "GCDEBUG et do gc" << endl;
  bemg_checkDoGc();
#endif
#endif

}

void BECS_Runtime::bemg_enterBlocking() {

#ifdef BEDCC_SGC
#ifdef BEDCC_PT
  BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
  bevg_gcLock.lock();
  bevs_myStack->bevg_stackGcState = 1;
  bevg_gcLock.unlock();
  bemg_checkDoGc();
#endif
#endif

}

void BECS_Runtime::bemg_exitBlocking() {

#ifdef BEDCC_SGC
#ifdef BEDCC_PT
  BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
  bevg_gcLock.lock();
  bevs_myStack->bevg_stackGcState = 0;
  bevg_gcLock.unlock();
  bemg_checkDoGc();
#endif
#endif

}

//RT
//static std::mutex bevg_gcLock;
//static std::condition_variable bevg_gcWaiter;
//static std::atomic<uint_fast16_t> bevg_gcState;
//FS
//uint_fast16_t bevg_stackGcState = 0;

void BECS_Runtime::bemg_checkDoGc() {
  
#ifdef BEDCC_SGC
  BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
#ifndef BEDCC_PT
  doGc();
#endif 
#ifdef BEDCC_PT 
  //lock
  std::unique_lock<std::mutex> ulock(bevg_gcLock);

  //if time for gc
  if (bevg_gcState.load(std::memory_order_acquire) == 1) {
    uint_fast16_t bevg_stackGcState = bevs_myStack->bevg_stackGcState;
    if (bevg_stackGcState != 1) {
      bevs_myStack->bevg_stackGcState = 1;
    }
    bool readyForGc = bemg_readyForGc();
    if (readyForGc) {
      //do gc
      doGc();
      if (bevg_stackGcState != 1) {
        bevs_myStack->bevg_stackGcState = bevg_stackGcState;
      }
      //notify all
      //cout << "GCDEBUG gc na" << endl;
      bevg_gcWaiter.notify_all();
    } else {
      //wait until gc is done (condvar, recheck)
      while (bevg_gcState.load(std::memory_order_acquire) == 1) {
        bevg_gcWaiter.wait(ulock);//is going to unlock then relock
      }
      if (bevg_stackGcState != 1) {
        bevs_myStack->bevg_stackGcState = bevg_stackGcState;
      }
    }
  }
#endif
#endif

}

bool BECS_Runtime::bemg_readyForGc() {
  //cout << "GCDEBUG ready for gc " << endl;
  bool readyForGc = true;
#ifdef BEDCC_SGC
#ifdef BEDCC_PT
  for(auto const &idStack : bevg_frameStacks) {
    //cout << "GCDEBUG rgc sgc " << idStack.second->bevg_stackGcState << endl;
    if (idStack.second->bevg_stackGcState == 0) {
      readyForGc = false;
    }
  }
#endif
#endif
  return readyForGc;
}

void BETS_Object::bems_buildMethodNames(std::vector<std::string> names) {
  for (unsigned i=0; i < names.size(); i++) {
      bevs_methodNames[names[i]] = true;
  }
}

BEC_2_6_6_SystemObject* BETS_Object::bems_createInstance() {
  return nullptr;
}

void BETS_Object::bemgt_doMark() {
}

BECS_ThrowBack::BECS_ThrowBack() { }

BECS_ThrowBack::BECS_ThrowBack(BEC_2_6_6_SystemObject* thrown) {
  wasThrown = thrown;
}

BEC_2_6_6_SystemObject* BECS_ThrowBack::handleThrow(BECS_ThrowBack thrown) {
  return thrown.wasThrown;
}
BET_2_6_6_SystemObject::BET_2_6_6_SystemObject() {
std::vector<std::string> bevs_mtnames = {  };
bevs_fieldNames = {  };
}
BEC_2_6_6_SystemObject* BET_2_6_6_SystemObject::bems_createInstance() {
return new BEC_2_6_6_SystemObject();
}
void BET_2_6_6_SystemObject::bemgt_doMark() {
BEC_2_6_6_SystemObject* bevsl_inst_ref = *bevs_inst_ref;
if (bevsl_inst_ref != nullptr && bevsl_inst_ref->bevg_gcMark != BECS_Runtime::bevg_currentGcMark) {
bevsl_inst_ref->bemg_doMark();
}
}


#ifdef BEDCC_SGC
    BEC_2_6_6_SystemObject* BEC_2_6_6_SystemObject::bems_forwardCall(std::string mname, std::vector<BEC_2_6_6_SystemObject*> bevd_x, int32_t numargs) {
#endif  

#ifdef BEDCC_SGC

  struct bes {  BEC_2_4_6_TextString* name; BEC_2_9_4_ContainerList* args; BEC_2_6_6_SystemObject* bevr_this;  };
  BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
  bes* beq = (bes*) bevs_myStack->bevs_hs;
  beq->name = nullptr;
  beq->args = nullptr;
  beq->bevr_this = this;
  BECS_StackFrame bevs_stackFrame(3);

#endif

  //cout << "in sfwdcall " << endl;
  beq->name = new BEC_2_4_6_TextString(mname);
  beq->args = new BEC_2_9_4_ContainerList(bevd_x, numargs);
  //args = args->bem_copy_0();
  return bem_forwardCall_2(beq->name, beq->args);
  //return nullptr;
} //}

  BEC_2_6_6_SystemObject* BEC_2_6_6_SystemObject::bece_BEC_2_6_6_SystemObject_bevs_inst;

BET_2_6_6_SystemObject BEC_2_6_6_SystemObject::bece_BEC_2_6_6_SystemObject_bevs_type;
BEC_2_6_6_SystemObject** BET_2_6_6_SystemObject::bevs_inst_ref = (BEC_2_6_6_SystemObject**) &BEC_2_6_6_SystemObject::bece_BEC_2_6_6_SystemObject_bevs_inst;

BEC_2_6_6_SystemObject* BEC_2_6_6_SystemObject::bem_new_0() {
struct bes {  BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(1);
return this;
}
BEC_2_5_4_LogicBool* BEC_2_6_6_SystemObject::bem_undef_1(BEC_2_6_6_SystemObject* bevk_ref) {
struct bes { BEC_2_6_6_SystemObject* beva_ref; BEC_2_5_4_LogicBool* bevt_0_ta_ph; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->beva_ref = bevk_ref;
beq->bevt_0_ta_ph = nullptr;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(3);
beq->bevt_0_ta_ph = static_cast<BEC_2_5_4_LogicBool*>(BECS_Runtime::boolFalse);
return beq->bevt_0_ta_ph;
}
BEC_2_5_4_LogicBool* BEC_2_6_6_SystemObject::bem_def_1(BEC_2_6_6_SystemObject* bevk_ref) {
struct bes { BEC_2_6_6_SystemObject* beva_ref; BEC_2_5_4_LogicBool* bevt_0_ta_ph; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->beva_ref = bevk_ref;
beq->bevt_0_ta_ph = nullptr;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(3);
beq->bevt_0_ta_ph = static_cast<BEC_2_5_4_LogicBool*>(BECS_Runtime::boolTrue);
return beq->bevt_0_ta_ph;
}
BEC_2_6_6_SystemObject* BEC_2_6_6_SystemObject::bem_methodNotDefined_2(BEC_2_4_6_TextString* bevk_name, BEC_2_9_4_ContainerList* bevk_args) {
struct bes { BEC_2_4_6_TextString* beva_name; BEC_2_9_4_ContainerList* beva_args; BEC_2_5_4_LogicBool* bevt_0_ta_ph; BEC_2_6_16_SystemMethodNotDefined* bevt_1_ta_ph; BEC_2_4_6_TextString* bevt_2_ta_ph; BEC_2_4_6_TextString* bevt_3_ta_ph; BEC_2_4_6_TextString* bevt_4_ta_ph; BEC_2_4_6_TextString* bevt_5_ta_ph; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->beva_name = bevk_name;
beq->beva_args = bevk_args;
beq->bevt_0_ta_ph = nullptr;
beq->bevt_1_ta_ph = nullptr;
beq->bevt_2_ta_ph = nullptr;
beq->bevt_3_ta_ph = nullptr;
beq->bevt_4_ta_ph = nullptr;
beq->bevt_5_ta_ph = nullptr;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(9);
beq->bevt_0_ta_ph = static_cast<BEC_2_5_4_LogicBool*>(BECS_Runtime::boolTrue);
if (beq->bevt_0_ta_ph->bevi_bool) {
beq->bevt_4_ta_ph = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString(8, {0x4D,0x65,0x74,0x68,0x6F,0x64,0x3A,0x20}))));
beq->bevt_3_ta_ph = beq->bevt_4_ta_ph->bem_add_1(beq->beva_name);
beq->bevt_5_ta_ph = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString(12, {0x20,0x6E,0x6F,0x74,0x20,0x64,0x65,0x66,0x69,0x6E,0x65,0x64}))));
beq->bevt_2_ta_ph = beq->bevt_3_ta_ph->bem_add_1(beq->bevt_5_ta_ph);
beq->bevt_1_ta_ph = static_cast<BEC_2_6_16_SystemMethodNotDefined*>(((BEC_2_6_16_SystemMethodNotDefined*) (new BEC_2_6_16_SystemMethodNotDefined()))->bem_new_1(beq->bevt_2_ta_ph));
throw BECS_ThrowBack(beq->bevt_1_ta_ph);
} 
return this;
}
BEC_2_6_6_SystemObject* BEC_2_6_6_SystemObject::bem_forwardCall_2(BEC_2_4_6_TextString* bevk_name, BEC_2_9_4_ContainerList* bevk_args) {
struct bes { BEC_2_4_6_TextString* beva_name; BEC_2_9_4_ContainerList* beva_args; BEC_2_5_4_LogicBool* bevt_0_ta_ph; BEC_2_6_16_SystemMethodNotDefined* bevt_1_ta_ph; BEC_2_4_6_TextString* bevt_2_ta_ph; BEC_2_4_6_TextString* bevt_3_ta_ph; BEC_2_4_6_TextString* bevt_4_ta_ph; BEC_2_4_6_TextString* bevt_5_ta_ph; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->beva_name = bevk_name;
beq->beva_args = bevk_args;
beq->bevt_0_ta_ph = nullptr;
beq->bevt_1_ta_ph = nullptr;
beq->bevt_2_ta_ph = nullptr;
beq->bevt_3_ta_ph = nullptr;
beq->bevt_4_ta_ph = nullptr;
beq->bevt_5_ta_ph = nullptr;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(9);
beq->bevt_0_ta_ph = static_cast<BEC_2_5_4_LogicBool*>(BECS_Runtime::boolTrue);
if (beq->bevt_0_ta_ph->bevi_bool) {
beq->bevt_4_ta_ph = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString(8, {0x4D,0x65,0x74,0x68,0x6F,0x64,0x3A,0x20}))));
beq->bevt_3_ta_ph = beq->bevt_4_ta_ph->bem_add_1(beq->beva_name);
beq->bevt_5_ta_ph = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString(12, {0x20,0x6E,0x6F,0x74,0x20,0x64,0x65,0x66,0x69,0x6E,0x65,0x64}))));
beq->bevt_2_ta_ph = beq->bevt_3_ta_ph->bem_add_1(beq->bevt_5_ta_ph);
beq->bevt_1_ta_ph = static_cast<BEC_2_6_16_SystemMethodNotDefined*>(((BEC_2_6_16_SystemMethodNotDefined*) (new BEC_2_6_16_SystemMethodNotDefined()))->bem_new_1(beq->bevt_2_ta_ph));
throw BECS_ThrowBack(beq->bevt_1_ta_ph);
} 
return this;
}
BEC_2_6_6_SystemObject* BEC_2_6_6_SystemObject::bem_invoke_2(BEC_2_4_6_TextString* bevk_name, BEC_2_9_4_ContainerList* bevk_args) {
struct bes { BEC_2_4_6_TextString* beva_name; BEC_2_9_4_ContainerList* beva_args; BEC_2_4_6_TextString* bevl_cname; BEC_2_6_6_SystemObject* bevl_rval; BEC_2_4_3_MathInt* bevl_numargs; BEC_2_9_4_ContainerList* bevl_args2; BEC_2_4_3_MathInt* bevl_i; BEC_2_5_4_LogicBool* bevt_0_ta_ph; BEC_2_6_19_SystemInvocationException* bevt_1_ta_ph; BEC_2_4_6_TextString* bevt_2_ta_ph; BEC_2_5_4_LogicBool* bevt_3_ta_ph; BEC_2_6_19_SystemInvocationException* bevt_4_ta_ph; BEC_2_4_6_TextString* bevt_5_ta_ph; BEC_2_4_6_TextString* bevt_6_ta_ph; BEC_2_4_6_TextString* bevt_7_ta_ph; BEC_2_4_6_TextString* bevt_8_ta_ph; BEC_2_5_4_LogicBool* bevt_9_ta_ph; BEC_2_4_3_MathInt* bevt_10_ta_ph; BEC_2_4_3_MathInt* bevt_11_ta_ph; BEC_2_4_3_MathInt* bevt_12_ta_ph; BEC_2_5_4_LogicBool* bevt_13_ta_ph; BEC_2_4_3_MathInt* bevt_14_ta_ph; BEC_2_4_3_MathInt* bevt_15_ta_ph; BEC_2_6_6_SystemObject* bevt_16_ta_ph; BEC_2_5_4_LogicBool* bevt_17_ta_ph; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->beva_name = bevk_name;
beq->beva_args = bevk_args;
beq->bevl_cname = nullptr;
beq->bevl_rval = nullptr;
beq->bevl_numargs = nullptr;
beq->bevl_args2 = nullptr;
beq->bevl_i = nullptr;
beq->bevt_0_ta_ph = nullptr;
beq->bevt_1_ta_ph = nullptr;
beq->bevt_2_ta_ph = nullptr;
beq->bevt_3_ta_ph = nullptr;
beq->bevt_4_ta_ph = nullptr;
beq->bevt_5_ta_ph = nullptr;
beq->bevt_6_ta_ph = nullptr;
beq->bevt_7_ta_ph = nullptr;
beq->bevt_8_ta_ph = nullptr;
beq->bevt_9_ta_ph = nullptr;
beq->bevt_10_ta_ph = nullptr;
beq->bevt_11_ta_ph = nullptr;
beq->bevt_12_ta_ph = nullptr;
beq->bevt_13_ta_ph = nullptr;
beq->bevt_14_ta_ph = nullptr;
beq->bevt_15_ta_ph = nullptr;
beq->bevt_16_ta_ph = nullptr;
beq->bevt_17_ta_ph = nullptr;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(26);
if (beq->beva_name == nullptr) {
beq->bevt_0_ta_ph = BECS_Runtime::boolTrue;
 } else { 
beq->bevt_0_ta_ph = BECS_Runtime::boolFalse;
}
if (beq->bevt_0_ta_ph->bevi_bool) {
beq->bevt_2_ta_ph = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString(23, {0x69,0x6E,0x76,0x6F,0x63,0x61,0x74,0x69,0x6F,0x6E,0x20,0x6E,0x61,0x6D,0x65,0x20,0x69,0x73,0x20,0x6E,0x75,0x6C,0x6C}))));
beq->bevt_1_ta_ph = static_cast<BEC_2_6_19_SystemInvocationException*>(((BEC_2_6_19_SystemInvocationException*) (new BEC_2_6_19_SystemInvocationException()))->bem_new_1(beq->bevt_2_ta_ph));
throw BECS_ThrowBack(beq->bevt_1_ta_ph);
} 
if (beq->beva_args == nullptr) {
beq->bevt_3_ta_ph = BECS_Runtime::boolTrue;
 } else { 
beq->bevt_3_ta_ph = BECS_Runtime::boolFalse;
}
if (beq->bevt_3_ta_ph->bevi_bool) {
beq->bevt_5_ta_ph = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString(32, {0x69,0x6E,0x76,0x6F,0x63,0x61,0x74,0x69,0x6F,0x6E,0x20,0x61,0x72,0x67,0x75,0x6D,0x65,0x6E,0x74,0x20,0x4C,0x69,0x73,0x74,0x20,0x69,0x73,0x20,0x6E,0x75,0x6C,0x6C}))));
beq->bevt_4_ta_ph = static_cast<BEC_2_6_19_SystemInvocationException*>(((BEC_2_6_19_SystemInvocationException*) (new BEC_2_6_19_SystemInvocationException()))->bem_new_1(beq->bevt_5_ta_ph));
throw BECS_ThrowBack(beq->bevt_4_ta_ph);
} 
beq->bevl_numargs = beq->beva_args->bem_lengthGet_0();
beq->bevt_7_ta_ph = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString(1, {0x5F}))));
beq->bevt_6_ta_ph = beq->beva_name->bem_add_1(beq->bevt_7_ta_ph);
beq->bevt_8_ta_ph = beq->bevl_numargs->bem_toString_0();
beq->bevl_cname = beq->bevt_6_ta_ph->bem_add_1(beq->bevt_8_ta_ph);
beq->bevt_10_ta_ph = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(7))));
if (beq->bevl_numargs->bevi_int > beq->bevt_10_ta_ph->bevi_int) {
beq->bevt_9_ta_ph = BECS_Runtime::boolTrue;
 } else { 
beq->bevt_9_ta_ph = BECS_Runtime::boolFalse;
}
if (beq->bevt_9_ta_ph->bevi_bool) {
beq->bevt_12_ta_ph = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(7))));
beq->bevt_11_ta_ph = beq->bevl_numargs->bem_subtract_1(beq->bevt_12_ta_ph);
beq->bevl_args2 = static_cast<BEC_2_9_4_ContainerList*>(((BEC_2_9_4_ContainerList*) (new BEC_2_9_4_ContainerList()))->bem_new_1(beq->bevt_11_ta_ph));
beq->bevl_i = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(7))));
while (true)
 {
if (beq->bevl_i->bevi_int < beq->bevl_numargs->bevi_int) {
beq->bevt_13_ta_ph = BECS_Runtime::boolTrue;
 } else { 
beq->bevt_13_ta_ph = BECS_Runtime::boolFalse;
}
if (beq->bevt_13_ta_ph->bevi_bool) {
beq->bevt_15_ta_ph = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(7))));
beq->bevt_14_ta_ph = beq->bevl_i->bem_subtract_1(beq->bevt_15_ta_ph);
beq->bevt_16_ta_ph = beq->beva_args->bem_get_1(beq->bevl_i);
beq->bevl_args2->bem_put_2(beq->bevt_14_ta_ph, beq->bevt_16_ta_ph);
beq->bevl_i->bevi_int++;
} 
 else  {
break;
} 
} 
} 

        int32_t ci = BECS_Ids::callIds[beq->bevl_cname->bems_toCcString()];
        //check for count first?  this inserts the val
        
        int32_t swi = beq->bevl_numargs->bevi_int;
        if (swi == 0) {
            beq->bevl_rval = bemd_0(ci);
        } else if (swi == 1) {
            beq->bevl_rval = bemd_1(ci, beq->beva_args->bevi_list[0]);
        } else if (swi == 2) {
            beq->bevl_rval = bemd_2(ci, beq->beva_args->bevi_list[0], beq->beva_args->bevi_list[1]);
        } else if (swi == 3) {
            beq->bevl_rval = bemd_3(ci, beq->beva_args->bevi_list[0], beq->beva_args->bevi_list[1], beq->beva_args->bevi_list[2]);
        } else if (swi == 4) {
            beq->bevl_rval = bemd_4(ci, beq->beva_args->bevi_list[0], beq->beva_args->bevi_list[1], beq->beva_args->bevi_list[2], beq->beva_args->bevi_list[3]);
        } else if (swi == 5) {
            beq->bevl_rval = bemd_5(ci, beq->beva_args->bevi_list[0], beq->beva_args->bevi_list[1], beq->beva_args->bevi_list[2], beq->beva_args->bevi_list[3], beq->beva_args->bevi_list[4]);
        }  else if (swi == 6) {
            beq->bevl_rval = bemd_6(ci, beq->beva_args->bevi_list[0], beq->beva_args->bevi_list[1], beq->beva_args->bevi_list[2], beq->beva_args->bevi_list[3], beq->beva_args->bevi_list[4], beq->beva_args->bevi_list[5]);
        }  else if (swi == 7) {
            beq->bevl_rval = bemd_7(ci, beq->beva_args->bevi_list[0], beq->beva_args->bevi_list[1], beq->beva_args->bevi_list[2], beq->beva_args->bevi_list[3], beq->beva_args->bevi_list[4], beq->beva_args->bevi_list[5], beq->beva_args->bevi_list[6]);
        }  else {
            beq->bevl_rval = bemd_x(ci, beq->beva_args->bevi_list[0], beq->beva_args->bevi_list[1], beq->beva_args->bevi_list[2], beq->beva_args->bevi_list[3], beq->beva_args->bevi_list[4], beq->beva_args->bevi_list[5], beq->beva_args->bevi_list[6], beq->bevl_args2->bevi_list);
        }
        beq->bevt_17_ta_ph = static_cast<BEC_2_5_4_LogicBool*>(BECS_Runtime::boolFalse);
if (beq->bevt_17_ta_ph->bevi_bool) {
beq->bevl_rval->bemd_0(-1553512291);
} 
return beq->bevl_rval;
}
BEC_2_5_4_LogicBool* BEC_2_6_6_SystemObject::bem_can_2(BEC_2_4_6_TextString* bevk_name, BEC_2_4_3_MathInt* bevk_numargs) {
struct bes { BEC_2_4_6_TextString* beva_name; BEC_2_4_3_MathInt* beva_numargs; BEC_2_4_6_TextString* bevl_cname; BEC_2_4_3_MathInt* bevl_chash; BEC_2_6_6_SystemObject* bevl_rval; BEC_2_5_4_LogicBool* bevt_0_ta_ph; BEC_2_6_19_SystemInvocationException* bevt_1_ta_ph; BEC_2_4_6_TextString* bevt_2_ta_ph; BEC_2_5_4_LogicBool* bevt_3_ta_ph; BEC_2_6_19_SystemInvocationException* bevt_4_ta_ph; BEC_2_4_6_TextString* bevt_5_ta_ph; BEC_2_4_6_TextString* bevt_6_ta_ph; BEC_2_4_6_TextString* bevt_7_ta_ph; BEC_2_4_6_TextString* bevt_8_ta_ph; BEC_2_5_4_LogicBool* bevt_9_ta_ph; BEC_2_5_4_LogicBool* bevt_10_ta_ph; BEC_2_5_4_LogicBool* bevt_11_ta_ph; BEC_2_5_4_LogicBool* bevt_12_ta_ph; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->beva_name = bevk_name;
beq->beva_numargs = bevk_numargs;
beq->bevl_cname = nullptr;
beq->bevl_chash = nullptr;
beq->bevl_rval = nullptr;
beq->bevt_0_ta_ph = nullptr;
beq->bevt_1_ta_ph = nullptr;
beq->bevt_2_ta_ph = nullptr;
beq->bevt_3_ta_ph = nullptr;
beq->bevt_4_ta_ph = nullptr;
beq->bevt_5_ta_ph = nullptr;
beq->bevt_6_ta_ph = nullptr;
beq->bevt_7_ta_ph = nullptr;
beq->bevt_8_ta_ph = nullptr;
beq->bevt_9_ta_ph = nullptr;
beq->bevt_10_ta_ph = nullptr;
beq->bevt_11_ta_ph = nullptr;
beq->bevt_12_ta_ph = nullptr;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(19);
if (beq->beva_name == nullptr) {
beq->bevt_0_ta_ph = BECS_Runtime::boolTrue;
 } else { 
beq->bevt_0_ta_ph = BECS_Runtime::boolFalse;
}
if (beq->bevt_0_ta_ph->bevi_bool) {
beq->bevt_2_ta_ph = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString(18, {0x63,0x61,0x6E,0x28,0x29,0x20,0x6E,0x61,0x6D,0x65,0x20,0x69,0x73,0x20,0x6E,0x75,0x6C,0x6C}))));
beq->bevt_1_ta_ph = static_cast<BEC_2_6_19_SystemInvocationException*>(((BEC_2_6_19_SystemInvocationException*) (new BEC_2_6_19_SystemInvocationException()))->bem_new_1(beq->bevt_2_ta_ph));
throw BECS_ThrowBack(beq->bevt_1_ta_ph);
} 
if (beq->beva_numargs == nullptr) {
beq->bevt_3_ta_ph = BECS_Runtime::boolTrue;
 } else { 
beq->bevt_3_ta_ph = BECS_Runtime::boolFalse;
}
if (beq->bevt_3_ta_ph->bevi_bool) {
beq->bevt_5_ta_ph = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString(21, {0x63,0x61,0x6E,0x28,0x29,0x20,0x6E,0x75,0x6D,0x61,0x72,0x67,0x73,0x20,0x69,0x73,0x20,0x6E,0x75,0x6C,0x6C}))));
beq->bevt_4_ta_ph = static_cast<BEC_2_6_19_SystemInvocationException*>(((BEC_2_6_19_SystemInvocationException*) (new BEC_2_6_19_SystemInvocationException()))->bem_new_1(beq->bevt_5_ta_ph));
throw BECS_ThrowBack(beq->bevt_4_ta_ph);
} 
beq->bevt_7_ta_ph = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString(1, {0x5F}))));
beq->bevt_6_ta_ph = beq->beva_name->bem_add_1(beq->bevt_7_ta_ph);
beq->bevt_8_ta_ph = beq->beva_numargs->bem_toString_0();
beq->bevl_cname = beq->bevt_6_ta_ph->bem_add_1(beq->bevt_8_ta_ph);

      
      std::string name = beq->bevl_cname->bems_toCcString();
      
      BETS_Object* bevs_cano = bemc_getType();
      
      if (bevs_cano->bevs_methodNames.count(name) > 0) {
        return BECS_Runtime::boolTrue;
      }
      
      beq->bevt_9_ta_ph = static_cast<BEC_2_5_4_LogicBool*>(BECS_Runtime::boolFalse);
if (beq->bevt_9_ta_ph->bevi_bool) {
beq->bevl_rval->bemd_0(-1553512291);
} 
if (beq->bevl_rval == nullptr) {
beq->bevt_10_ta_ph = BECS_Runtime::boolFalse;
 } else { 
beq->bevt_10_ta_ph = BECS_Runtime::boolTrue;
}
if (beq->bevt_10_ta_ph->bevi_bool) {
beq->bevt_11_ta_ph = static_cast<BEC_2_5_4_LogicBool*>(BECS_Runtime::boolTrue);
return beq->bevt_11_ta_ph;
} 
beq->bevt_12_ta_ph = static_cast<BEC_2_5_4_LogicBool*>(BECS_Runtime::boolFalse);
return beq->bevt_12_ta_ph;
}
BEC_2_5_4_LogicBool* BEC_2_6_6_SystemObject::bem_equals_1(BEC_2_6_6_SystemObject* bevk_x) {
struct bes { BEC_2_6_6_SystemObject* beva_x; BEC_2_5_4_LogicBool* bevt_0_ta_ph; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->beva_x = bevk_x;
beq->bevt_0_ta_ph = nullptr;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(3);

      if (this != beq->beva_x) {
        return BECS_Runtime::boolFalse;
      }
      beq->bevt_0_ta_ph = static_cast<BEC_2_5_4_LogicBool*>(BECS_Runtime::boolTrue);
return beq->bevt_0_ta_ph;
}
BEC_2_4_3_MathInt* BEC_2_6_6_SystemObject::bem_hashGet_0() {
struct bes { BEC_2_4_3_MathInt* bevl_toRet; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->bevl_toRet = nullptr;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(2);
beq->bevl_toRet = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt())));

      BECS_Object* co = this;
      uintptr_t cou = (uintptr_t) co;
      int32_t co3 = (int32_t) cou;
      beq->bevl_toRet->bevi_int = co3;
      return beq->bevl_toRet;
}
BEC_2_5_4_LogicBool* BEC_2_6_6_SystemObject::bem_notEquals_1(BEC_2_6_6_SystemObject* bevk_x) {
struct bes { BEC_2_6_6_SystemObject* beva_x; BEC_2_5_4_LogicBool* bevt_0_ta_ph; BEC_2_5_4_LogicBool* bevt_1_ta_ph; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->beva_x = bevk_x;
beq->bevt_0_ta_ph = nullptr;
beq->bevt_1_ta_ph = nullptr;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(4);
beq->bevt_1_ta_ph = bem_equals_1(beq->beva_x);
if (beq->bevt_1_ta_ph->bevi_bool) {
beq->bevt_0_ta_ph = BECS_Runtime::boolFalse;
 } else { 
beq->bevt_0_ta_ph = BECS_Runtime::boolTrue;
}
return beq->bevt_0_ta_ph;
}
BEC_2_4_6_TextString* BEC_2_6_6_SystemObject::bem_toString_0() {
struct bes { BEC_2_4_6_TextString* bevt_0_ta_ph; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->bevt_0_ta_ph = nullptr;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(2);
beq->bevt_0_ta_ph = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString(15, {0x4F,0x62,0x6A,0x65,0x63,0x74,0x2E,0x74,0x6F,0x53,0x74,0x72,0x69,0x6E,0x67}))));
return beq->bevt_0_ta_ph;
}
BEC_2_6_6_SystemObject* BEC_2_6_6_SystemObject::bem_print_0() {
struct bes { BEC_2_4_6_TextString* bevt_0_ta_ph; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->bevt_0_ta_ph = nullptr;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(2);
beq->bevt_0_ta_ph = bem_toString_0();
beq->bevt_0_ta_ph->bem_print_0();
return this;
}
BEC_2_6_6_SystemObject* BEC_2_6_6_SystemObject::bem_copy_0() {
struct bes { BEC_2_6_6_SystemObject* bevt_0_ta_ph; BEC_2_6_6_SystemObject* bevt_1_ta_ph; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->bevt_0_ta_ph = nullptr;
beq->bevt_1_ta_ph = nullptr;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(3);
beq->bevt_1_ta_ph = static_cast<BEC_2_6_6_SystemObject*>(bem_create_0());
beq->bevt_0_ta_ph = static_cast<BEC_2_6_6_SystemObject*>(bem_copyTo_1(beq->bevt_1_ta_ph));
return static_cast<BEC_2_6_6_SystemObject*>(beq->bevt_0_ta_ph);
}
BEC_2_6_6_SystemObject* BEC_2_6_6_SystemObject::bem_copyTo_1(BEC_2_6_6_SystemObject* bevk_copy) {
struct bes { BEC_2_6_6_SystemObject* beva_copy; BEC_2_6_19_SystemObjectFieldIterator* bevl_siter; BEC_2_6_19_SystemObjectFieldIterator* bevl_citer; BEC_2_5_4_LogicBool* bevt_0_ta_ph; BEC_2_5_4_LogicBool* bevt_1_ta_ph; BEC_2_5_4_LogicBool* bevt_2_ta_ph; BEC_2_5_4_LogicBool* bevt_3_ta_ph; BEC_2_6_6_SystemObject* bevt_4_ta_ph; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->beva_copy = bevk_copy;
beq->bevl_siter = nullptr;
beq->bevl_citer = nullptr;
beq->bevt_0_ta_ph = nullptr;
beq->bevt_1_ta_ph = nullptr;
beq->bevt_2_ta_ph = nullptr;
beq->bevt_3_ta_ph = nullptr;
beq->bevt_4_ta_ph = nullptr;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(9);
if (beq->beva_copy == nullptr) {
beq->bevt_0_ta_ph = BECS_Runtime::boolTrue;
 } else { 
beq->bevt_0_ta_ph = BECS_Runtime::boolFalse;
}
if (beq->bevt_0_ta_ph->bevi_bool) {
return static_cast<BEC_2_6_6_SystemObject*>(beq->beva_copy);
} 
beq->bevt_1_ta_ph = static_cast<BEC_2_5_4_LogicBool*>(BECS_Runtime::boolTrue);
beq->bevl_siter = ((BEC_2_6_19_SystemObjectFieldIterator*) (new BEC_2_6_19_SystemObjectFieldIterator()))->bem_new_2(this, beq->bevt_1_ta_ph);
beq->bevt_2_ta_ph = static_cast<BEC_2_5_4_LogicBool*>(BECS_Runtime::boolTrue);
beq->bevl_citer = ((BEC_2_6_19_SystemObjectFieldIterator*) (new BEC_2_6_19_SystemObjectFieldIterator()))->bem_new_2(beq->beva_copy, beq->bevt_2_ta_ph);
while (true)
 {
beq->bevt_3_ta_ph = beq->bevl_siter->bem_hasNextGet_0();
if (beq->bevt_3_ta_ph->bevi_bool) {
beq->bevt_4_ta_ph = beq->bevl_siter->bem_nextGet_0();
beq->bevl_citer->bem_nextSet_1(beq->bevt_4_ta_ph);
} 
 else  {
break;
} 
} 
return this;
}
BEC_2_6_6_SystemObject* BEC_2_6_6_SystemObject::bem_iteratorGet_0() {
struct bes { BEC_2_6_19_SystemObjectFieldIterator* bevt_0_ta_ph; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->bevt_0_ta_ph = nullptr;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(2);
beq->bevt_0_ta_ph = ((BEC_2_6_19_SystemObjectFieldIterator*) (new BEC_2_6_19_SystemObjectFieldIterator()))->bem_new_1(this);
return beq->bevt_0_ta_ph;
}
BEC_2_6_6_SystemObject* BEC_2_6_6_SystemObject::bem_create_0() {
struct bes { BEC_2_6_6_SystemObject* bevl_copy; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->bevl_copy = nullptr;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(2);

      beq->bevl_copy = this->bemc_create();
      return static_cast<BEC_2_6_6_SystemObject*>(beq->bevl_copy);
}
BEC_2_6_6_SystemObject* BEC_2_6_6_SystemObject::bemd_0(int32_t callId) {
switch (callId) {
case -1677156504: return bem_hashGet_0();
case -1553512291: return bem_toString_0();
case 2142500088: return bem_copy_0();
case 1312387167: return bem_create_0();
case 1701756138: return bem_print_0();
case -1428269309: return bem_iteratorGet_0();
case -1785532669: return bem_new_0();
}
return bevs_super::bemd_0(callId);
}
BEC_2_6_6_SystemObject* BEC_2_6_6_SystemObject::bemd_1(int32_t callId, BEC_2_6_6_SystemObject* bevd_0) {
switch (callId) {
case 725716025: return bem_def_1(bevd_0);
case 1039122802: return bem_notEquals_1(bevd_0);
case 875773826: return bem_copyTo_1(bevd_0);
case 643138569: return bem_equals_1(bevd_0);
case 1974382165: return bem_undef_1(bevd_0);
}
return bevs_super::bemd_1(callId, bevd_0);
}
BEC_2_6_6_SystemObject* BEC_2_6_6_SystemObject::bemd_2(int32_t callId, BEC_2_6_6_SystemObject* bevd_0, BEC_2_6_6_SystemObject* bevd_1) {
switch (callId) {
case 1600280145: return bem_forwardCall_2(static_cast<BEC_2_4_6_TextString*>(bevd_0), static_cast<BEC_2_9_4_ContainerList*>(bevd_1));
case -1569524644: return bem_can_2(static_cast<BEC_2_4_6_TextString*>(bevd_0), static_cast<BEC_2_4_3_MathInt*>(bevd_1));
case 963430444: return bem_invoke_2(static_cast<BEC_2_4_6_TextString*>(bevd_0), static_cast<BEC_2_9_4_ContainerList*>(bevd_1));
case -1304156743: return bem_methodNotDefined_2(static_cast<BEC_2_4_6_TextString*>(bevd_0), static_cast<BEC_2_9_4_ContainerList*>(bevd_1));
}
return bevs_super::bemd_2(callId, bevd_0, bevd_1);
}
BEC_2_6_6_SystemObject* BEC_2_6_6_SystemObject::bemc_create() {
return new BEC_2_6_6_SystemObject();
}
void BEC_2_6_6_SystemObject::bemc_setInitial(BEC_2_6_6_SystemObject* becc_inst) {
BEC_2_6_6_SystemObject::bece_BEC_2_6_6_SystemObject_bevs_inst = becc_inst;
}
BEC_2_6_6_SystemObject* BEC_2_6_6_SystemObject::bemc_getInitial() {
return BEC_2_6_6_SystemObject::bece_BEC_2_6_6_SystemObject_bevs_inst;
}
void BEC_2_6_6_SystemObject::bemg_doMark() {
bevg_gcMark = BECS_Runtime::bevg_currentGcMark;
}
size_t BEC_2_6_6_SystemObject::bemg_getSize() {
return sizeof(*this);
}
BETS_Object* BEC_2_6_6_SystemObject::bemc_getType() {
return &BEC_2_6_6_SystemObject::bece_BEC_2_6_6_SystemObject_bevs_type;
}
BET_2_8_3_EmbeddedApp::BET_2_8_3_EmbeddedApp() {
std::vector<std::string> bevs_mtnames = {  };
bevs_fieldNames = {  };
}
BEC_2_6_6_SystemObject* BET_2_8_3_EmbeddedApp::bems_createInstance() {
return new BEC_2_8_3_EmbeddedApp();
}
void BET_2_8_3_EmbeddedApp::bemgt_doMark() {
BEC_2_6_6_SystemObject* bevsl_inst_ref = *bevs_inst_ref;
if (bevsl_inst_ref != nullptr && bevsl_inst_ref->bevg_gcMark != BECS_Runtime::bevg_currentGcMark) {
bevsl_inst_ref->bemg_doMark();
}
}
BEC_2_8_3_EmbeddedApp* BEC_2_8_3_EmbeddedApp::bece_BEC_2_8_3_EmbeddedApp_bevs_inst;

BET_2_8_3_EmbeddedApp BEC_2_8_3_EmbeddedApp::bece_BEC_2_8_3_EmbeddedApp_bevs_type;
BEC_2_6_6_SystemObject** BET_2_8_3_EmbeddedApp::bevs_inst_ref = (BEC_2_6_6_SystemObject**) &BEC_2_8_3_EmbeddedApp::bece_BEC_2_8_3_EmbeddedApp_bevs_inst;

BEC_2_8_3_EmbeddedApp* BEC_2_8_3_EmbeddedApp::bem_default_0() {
struct bes {  BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(1);
bevp_hlCount = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(0))));
bevp_zero = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(0))));
return this;
}
BEC_2_8_3_EmbeddedApp* BEC_2_8_3_EmbeddedApp::bem_handleWeb_1(BEC_2_6_6_SystemObject* bevk_request) {
struct bes { BEC_2_6_6_SystemObject* beva_request; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->beva_request = bevk_request;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(2);
bevp_plugin->bemd_1(-322423674, beq->beva_request);
return this;
}
BEC_2_8_3_EmbeddedApp* BEC_2_8_3_EmbeddedApp::bem_startLoop_0() {
struct bes { BEC_2_4_6_TextString* bevt_0_ta_ph; BEC_2_4_6_TextString* bevt_1_ta_ph; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->bevt_0_ta_ph = nullptr;
beq->bevt_1_ta_ph = nullptr;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(3);
beq->bevt_0_ta_ph = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString(12, {0x49,0x4E,0x20,0x53,0x54,0x41,0x52,0x54,0x4C,0x4F,0x4F,0x50}))));
beq->bevt_0_ta_ph->bem_print_0();
bevp_plugin->bemd_0(-1646341150);
beq->bevt_1_ta_ph = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString(19, {0x46,0x49,0x4E,0x49,0x53,0x48,0x49,0x4E,0x47,0x20,0x53,0x54,0x41,0x52,0x54,0x4C,0x4F,0x4F,0x50}))));
beq->bevt_1_ta_ph->bem_print_0();
return this;
}
BEC_2_8_3_EmbeddedApp* BEC_2_8_3_EmbeddedApp::bem_handleLoop_0() {
struct bes { BEC_2_5_4_LogicBool* bevt_0_ta_ph; BEC_2_4_6_TextString* bevt_1_ta_ph; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->bevt_0_ta_ph = nullptr;
beq->bevt_1_ta_ph = nullptr;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(3);
if (bevp_hlCount->bevi_int > bevp_zero->bevi_int) {
beq->bevt_0_ta_ph = BECS_Runtime::boolTrue;
 } else { 
beq->bevt_0_ta_ph = BECS_Runtime::boolFalse;
}
if (beq->bevt_0_ta_ph->bevi_bool) {
beq->bevt_1_ta_ph = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString(16, {0x48,0x4C,0x43,0x4F,0x55,0x4E,0x54,0x20,0x45,0x4C,0x45,0x56,0x41,0x54,0x45,0x44}))));
beq->bevt_1_ta_ph->bem_print_0();
} 
bevp_hlCount->bevi_int++;
bevp_plugin->bemd_0(-330685574);
bevp_hlCount->bem_decrementValue_0();
return this;
}
BEC_2_8_3_EmbeddedApp* BEC_2_8_3_EmbeddedApp::bem_delay_1(BEC_2_4_3_MathInt* bevk_millis) {
struct bes { BEC_2_4_3_MathInt* beva_millis; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->beva_millis = bevk_millis;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(2);

      delay(beq->beva_millis->bevi_int);
      return this;
}
BEC_2_8_3_EmbeddedApp* BEC_2_8_3_EmbeddedApp::bem_wdtFeed_0() {
struct bes {  BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(1);

#ifdef BEAR_ESP8266
      ESP.wdtFeed();
#endif
      return this;
}
BEC_2_8_3_EmbeddedApp* BEC_2_8_3_EmbeddedApp::bem_wdtDisable_0() {
struct bes {  BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(1);

#ifdef BEAR_ESP8266
      ESP.wdtDisable();
      //*((volatile uint32_t*) 0x60000900) &= ~(1); // Hardware WDT OFF
#endif
      return this;
}
BEC_2_8_3_EmbeddedApp* BEC_2_8_3_EmbeddedApp::bem_wdtEnable_1(BEC_2_4_3_MathInt* bevk_timeout) {
struct bes { BEC_2_4_3_MathInt* beva_timeout; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->beva_timeout = bevk_timeout;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(2);

      //*((volatile uint32_t*) 0x60000900) |= 1; // Hardware WDT ON
      ESP.wdtEnable(beq->beva_timeout->bevi_int);
      return this;
}
BEC_2_8_3_EmbeddedApp* BEC_2_8_3_EmbeddedApp::bem_yield_0() {
struct bes {  BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(1);

      yield();
      return this;
}
BEC_2_4_3_MathInt* BEC_2_8_3_EmbeddedApp::bem_uptime_0() {
struct bes { BEC_2_4_3_MathInt* bevl_millis; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->bevl_millis = nullptr;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(2);
beq->bevl_millis = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt())));

     beq->bevl_millis->bevi_int = millis();
     return beq->bevl_millis;
}
BEC_2_4_3_MathInt* BEC_2_8_3_EmbeddedApp::bem_uptime_1(BEC_2_4_3_MathInt* bevk_millis) {
struct bes { BEC_2_4_3_MathInt* beva_millis; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->beva_millis = bevk_millis;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(2);

     beq->beva_millis->bevi_int = millis();
     return beq->beva_millis;
}
BEC_2_8_3_EmbeddedApp* BEC_2_8_3_EmbeddedApp::bem_pinModeOutput_1(BEC_2_4_3_MathInt* bevk_pin) {
struct bes { BEC_2_4_3_MathInt* beva_pin; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->beva_pin = bevk_pin;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(2);

     //pinMode(255, OUTPUT);
     //analogWrite(255, 0);
     //analogWrite(255, 10);
     pinMode(beq->beva_pin->bevi_int,OUTPUT);
     return this;
}
BEC_2_8_3_EmbeddedApp* BEC_2_8_3_EmbeddedApp::bem_analogWrite_2(BEC_2_4_3_MathInt* bevk_pin, BEC_2_4_3_MathInt* bevk_value) {
struct bes { BEC_2_4_3_MathInt* beva_pin; BEC_2_4_3_MathInt* beva_value; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->beva_pin = bevk_pin;
beq->beva_value = bevk_value;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(3);

     uint8_t pin = (uint8_t) beq->beva_pin->bevi_int;
     uint8_t value = (uint8_t) beq->beva_value->bevi_int;
     analogWrite(pin,value);
     return this;
}
BEC_2_8_3_EmbeddedApp* BEC_2_8_3_EmbeddedApp::bem_pinModeInputPullup_1(BEC_2_4_3_MathInt* bevk_pin) {
struct bes { BEC_2_4_3_MathInt* beva_pin; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->beva_pin = bevk_pin;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(2);

     pinMode(beq->beva_pin->bevi_int,INPUT_PULLUP);
     return this;
}
BEC_2_4_3_MathInt* BEC_2_8_3_EmbeddedApp::bem_analogRead_2(BEC_2_4_3_MathInt* bevk_pin, BEC_2_4_3_MathInt* bevk_value) {
struct bes { BEC_2_4_3_MathInt* beva_pin; BEC_2_4_3_MathInt* beva_value; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->beva_pin = bevk_pin;
beq->beva_value = bevk_value;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(3);

     uint8_t pin = (uint8_t) beq->beva_pin->bevi_int;
     uint8_t value = analogRead(pin);
     beq->beva_value->bevi_int = (int32_t) value;
     return beq->beva_value;
}
BEC_2_8_3_EmbeddedApp* BEC_2_8_3_EmbeddedApp::bem_restart_0() {
struct bes {  BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(1);

     ESP.restart();
     return this;
}
BEC_2_4_3_MathInt* BEC_2_8_3_EmbeddedApp::bem_strToInt_1(BEC_2_4_6_TextString* bevk_str) {
struct bes { BEC_2_4_6_TextString* beva_str; BEC_2_4_3_MathInt* bevl_res; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->beva_str = bevk_str;
beq->bevl_res = nullptr;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(3);
beq->bevl_res = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt())));

       beq->bevl_res->bevi_int = atoi(beq->beva_str->bems_toCcString().c_str());
       return beq->bevl_res;
}
BEC_2_4_6_TextString* BEC_2_8_3_EmbeddedApp::bem_intToStr_1(BEC_2_4_3_MathInt* bevk_int) {
struct bes { BEC_2_4_3_MathInt* beva_int; BEC_2_4_6_TextString* bevl_res; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->beva_int = bevk_int;
beq->bevl_res = nullptr;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(3);

       char buffer[20];
       itoa(beq->beva_int->bevi_int,buffer,10);
       std::string ints = std::string(buffer);
       beq->bevl_res = new BEC_2_4_6_TextString(ints);
       return beq->bevl_res;
}
BEC_2_8_3_EmbeddedApp* BEC_2_8_3_EmbeddedApp::bem_maybeGc_0() {
struct bes {  BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(1);

   BECS_Runtime::doGc();
   return this;
}
BEC_2_6_6_SystemObject* BEC_2_8_3_EmbeddedApp::bem_pluginGet_0() {
struct bes {  BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(1);
return bevp_plugin;
}
BEC_2_8_3_EmbeddedApp* BEC_2_8_3_EmbeddedApp::bem_pluginSet_1(BEC_2_6_6_SystemObject* bevt_0_ta_SET) {
struct bes { BEC_2_6_6_SystemObject* bevt_0_ta_SET; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->bevt_0_ta_SET = bevt_0_ta_SET;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(2);
bevp_plugin = beq->bevt_0_ta_SET;
return this;
}
BEC_2_4_3_MathInt* BEC_2_8_3_EmbeddedApp::bem_hlCountGet_0() {
struct bes {  BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(1);
return bevp_hlCount;
}
BEC_2_8_3_EmbeddedApp* BEC_2_8_3_EmbeddedApp::bem_hlCountSet_1(BEC_2_6_6_SystemObject* bevt_0_ta_SET) {
struct bes { BEC_2_6_6_SystemObject* bevt_0_ta_SET; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->bevt_0_ta_SET = bevt_0_ta_SET;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(2);
bevp_hlCount = static_cast<BEC_2_4_3_MathInt*>(beq->bevt_0_ta_SET);
return this;
}
BEC_2_4_3_MathInt* BEC_2_8_3_EmbeddedApp::bem_zeroGet_0() {
struct bes {  BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(1);
return bevp_zero;
}
BEC_2_8_3_EmbeddedApp* BEC_2_8_3_EmbeddedApp::bem_zeroSet_1(BEC_2_6_6_SystemObject* bevt_0_ta_SET) {
struct bes { BEC_2_6_6_SystemObject* bevt_0_ta_SET; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->bevt_0_ta_SET = bevt_0_ta_SET;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(2);
bevp_zero = static_cast<BEC_2_4_3_MathInt*>(beq->bevt_0_ta_SET);
return this;
}
BEC_2_6_6_SystemObject* BEC_2_8_3_EmbeddedApp::bemd_0(int32_t callId) {
switch (callId) {
case -656204624: return bem_wdtFeed_0();
case -1305985439: return bem_restart_0();
case 1188815194: return bem_default_0();
case 763695625: return bem_pluginGet_0();
case 363757507: return bem_zeroGet_0();
case -700651862: return bem_hlCountGet_0();
case -330685574: return bem_handleLoop_0();
case -634183121: return bem_maybeGc_0();
case -875257880: return bem_uptime_0();
case -1646341150: return bem_startLoop_0();
case 932223214: return bem_wdtDisable_0();
case -510102876: return bem_yield_0();
}
return bevs_super::bemd_0(callId);
}
BEC_2_6_6_SystemObject* BEC_2_8_3_EmbeddedApp::bemd_1(int32_t callId, BEC_2_6_6_SystemObject* bevd_0) {
switch (callId) {
case 2066576199: return bem_pinModeInputPullup_1(static_cast<BEC_2_4_3_MathInt*>(bevd_0));
case -1788236849: return bem_intToStr_1(static_cast<BEC_2_4_3_MathInt*>(bevd_0));
case -386799862: return bem_uptime_1(static_cast<BEC_2_4_3_MathInt*>(bevd_0));
case 682962859: return bem_pluginSet_1(bevd_0);
case 1814078986: return bem_wdtEnable_1(static_cast<BEC_2_4_3_MathInt*>(bevd_0));
case -1607536321: return bem_pinModeOutput_1(static_cast<BEC_2_4_3_MathInt*>(bevd_0));
case 92163473: return bem_strToInt_1(static_cast<BEC_2_4_6_TextString*>(bevd_0));
case -322423674: return bem_handleWeb_1(bevd_0);
case 593309101: return bem_zeroSet_1(bevd_0);
case -1992605665: return bem_delay_1(static_cast<BEC_2_4_3_MathInt*>(bevd_0));
case -782968275: return bem_hlCountSet_1(bevd_0);
}
return bevs_super::bemd_1(callId, bevd_0);
}
BEC_2_6_6_SystemObject* BEC_2_8_3_EmbeddedApp::bemd_2(int32_t callId, BEC_2_6_6_SystemObject* bevd_0, BEC_2_6_6_SystemObject* bevd_1) {
switch (callId) {
case -2017369882: return bem_analogRead_2(static_cast<BEC_2_4_3_MathInt*>(bevd_0), static_cast<BEC_2_4_3_MathInt*>(bevd_1));
case 753978671: return bem_analogWrite_2(static_cast<BEC_2_4_3_MathInt*>(bevd_0), static_cast<BEC_2_4_3_MathInt*>(bevd_1));
}
return bevs_super::bemd_2(callId, bevd_0, bevd_1);
}
BEC_2_6_6_SystemObject* BEC_2_8_3_EmbeddedApp::bemc_create() {
return new BEC_2_8_3_EmbeddedApp();
}
void BEC_2_8_3_EmbeddedApp::bemc_setInitial(BEC_2_6_6_SystemObject* becc_inst) {
BEC_2_8_3_EmbeddedApp::bece_BEC_2_8_3_EmbeddedApp_bevs_inst = static_cast<BEC_2_8_3_EmbeddedApp*>(becc_inst);
}
BEC_2_6_6_SystemObject* BEC_2_8_3_EmbeddedApp::bemc_getInitial() {
return BEC_2_8_3_EmbeddedApp::bece_BEC_2_8_3_EmbeddedApp_bevs_inst;
}
void BEC_2_8_3_EmbeddedApp::bemg_doMark() {
bevg_gcMark = BECS_Runtime::bevg_currentGcMark;
if (bevp_plugin != nullptr && bevp_plugin->bevg_gcMark != BECS_Runtime::bevg_currentGcMark) {
bevp_plugin->bemg_doMark();
}
if (bevp_hlCount != nullptr && bevp_hlCount->bevg_gcMark != BECS_Runtime::bevg_currentGcMark) {
bevp_hlCount->bemg_doMark();
}
if (bevp_zero != nullptr && bevp_zero->bevg_gcMark != BECS_Runtime::bevg_currentGcMark) {
bevp_zero->bemg_doMark();
}
}
size_t BEC_2_8_3_EmbeddedApp::bemg_getSize() {
return sizeof(*this);
}
BETS_Object* BEC_2_8_3_EmbeddedApp::bemc_getType() {
return &BEC_2_8_3_EmbeddedApp::bece_BEC_2_8_3_EmbeddedApp_bevs_type;
}
BET_2_8_6_EmbeddedConfig::BET_2_8_6_EmbeddedConfig() {
std::vector<std::string> bevs_mtnames = {  };
bevs_fieldNames = {  };
}
BEC_2_6_6_SystemObject* BET_2_8_6_EmbeddedConfig::bems_createInstance() {
return new BEC_2_8_6_EmbeddedConfig();
}
void BET_2_8_6_EmbeddedConfig::bemgt_doMark() {
BEC_2_6_6_SystemObject* bevsl_inst_ref = *bevs_inst_ref;
if (bevsl_inst_ref != nullptr && bevsl_inst_ref->bevg_gcMark != BECS_Runtime::bevg_currentGcMark) {
bevsl_inst_ref->bemg_doMark();
}
}
BEC_2_8_6_EmbeddedConfig* BEC_2_8_6_EmbeddedConfig::bece_BEC_2_8_6_EmbeddedConfig_bevs_inst;

BET_2_8_6_EmbeddedConfig BEC_2_8_6_EmbeddedConfig::bece_BEC_2_8_6_EmbeddedConfig_bevs_type;
BEC_2_6_6_SystemObject** BET_2_8_6_EmbeddedConfig::bevs_inst_ref = (BEC_2_6_6_SystemObject**) &BEC_2_8_6_EmbeddedConfig::bece_BEC_2_8_6_EmbeddedConfig_bevs_inst;

BEC_2_6_6_SystemObject* BEC_2_8_6_EmbeddedConfig::bem_new_0() {
struct bes {  BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(1);
bevp_eesize = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(4096))));
bevp_maxsz = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(128))));
bevp_names = static_cast<BEC_2_9_4_ContainerList*>(((BEC_2_9_4_ContainerList*) (new BEC_2_9_4_ContainerList()))->bem_new_0());
bevp_values = static_cast<BEC_2_9_4_ContainerList*>(((BEC_2_9_4_ContainerList*) (new BEC_2_9_4_ContainerList()))->bem_new_0());
bevp_changed = static_cast<BEC_2_5_4_LogicBool*>(BECS_Runtime::boolFalse);
bevp_magic = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString(8, {0x62,0x72,0x61,0x63,0x65,0x45,0x6D,0x62}))));
bevp_zero = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(0))));
bevp_one = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(1))));
bevp_es = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(27))));
bevp_ess = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString()))->bem_codeNew_1(bevp_es));
bevp_gs = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(29))));
bevp_gss = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString()))->bem_codeNew_1(bevp_gs));
bevp_us = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(31))));
bevp_uss = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString()))->bem_codeNew_1(bevp_us));
bevp_rs = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(30))));
bevp_rss = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString()))->bem_codeNew_1(bevp_rs));
return this;
}
BEC_2_6_6_SystemObject* BEC_2_8_6_EmbeddedConfig::bem_getPos_1(BEC_2_4_6_TextString* bevk_name) {
struct bes { BEC_2_4_6_TextString* beva_name; BEC_2_4_3_MathInt* bevl_pos; BEC_2_5_4_LogicBool* bevt_0_ta_ph; BEC_2_4_3_MathInt* bevt_1_ta_ph; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->beva_name = bevk_name;
beq->bevl_pos = nullptr;
beq->bevt_0_ta_ph = nullptr;
beq->bevt_1_ta_ph = nullptr;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(5);
beq->bevl_pos = bevp_names->bem_find_1(beq->beva_name);
if (beq->bevl_pos == nullptr) {
beq->bevt_0_ta_ph = BECS_Runtime::boolTrue;
 } else { 
beq->bevt_0_ta_ph = BECS_Runtime::boolFalse;
}
if (beq->bevt_0_ta_ph->bevi_bool) {
beq->bevt_1_ta_ph = bevp_names->bem_sizeGet_0();
beq->bevl_pos = static_cast<BEC_2_4_3_MathInt*>(beq->bevt_1_ta_ph->bem_copy_0());
bevp_names->bem_addValue_1(beq->beva_name);
bevp_values->bem_addValue_1(nullptr);
} 
return beq->bevl_pos;
}
BEC_2_4_6_TextString* BEC_2_8_6_EmbeddedConfig::bem_get_1(BEC_2_4_3_MathInt* bevk_pos) {
struct bes { BEC_2_4_3_MathInt* beva_pos; BEC_2_6_6_SystemObject* bevt_0_ta_ph; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->beva_pos = bevk_pos;
beq->bevt_0_ta_ph = nullptr;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(3);
beq->bevt_0_ta_ph = bevp_values->bem_get_1(beq->beva_pos);
return static_cast<BEC_2_4_6_TextString*>(beq->bevt_0_ta_ph);
}
BEC_2_8_6_EmbeddedConfig* BEC_2_8_6_EmbeddedConfig::bem_put_2(BEC_2_4_3_MathInt* bevk_pos, BEC_2_4_6_TextString* bevk_value) {
struct bes { BEC_2_4_3_MathInt* beva_pos; BEC_2_4_6_TextString* beva_value; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->beva_pos = bevk_pos;
beq->beva_value = bevk_value;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(3);
bevp_values->bem_put_2(beq->beva_pos, beq->beva_value);
bevp_changed = static_cast<BEC_2_5_4_LogicBool*>(BECS_Runtime::boolTrue);
return this;
}
BEC_2_8_6_EmbeddedConfig* BEC_2_8_6_EmbeddedConfig::bem_maybeSave_0() {
struct bes {  BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(1);
if (bevp_changed->bevi_bool) {
bem_save_0();
bevp_changed = static_cast<BEC_2_5_4_LogicBool*>(BECS_Runtime::boolFalse);
} 
return this;
}
BEC_2_8_6_EmbeddedConfig* BEC_2_8_6_EmbeddedConfig::bem_load_0() {
struct bes { BEC_2_4_6_TextString* bevl_lbuf; BEC_2_4_3_MathInt* bevl_pe; BEC_2_4_3_MathInt* bevl_ps; BEC_2_4_3_MathInt* bevl_code; BEC_2_4_3_MathInt* bevl_lpos; BEC_2_4_3_MathInt* bevl_res; BEC_2_5_4_LogicBool* bevt_0_ta_anchor; BEC_2_4_3_MathInt* bevt_1_ta_ph; BEC_2_5_4_LogicBool* bevt_2_ta_ph; BEC_2_4_7_TextStrings* bevt_3_ta_ph; BEC_2_5_4_LogicBool* bevt_4_ta_ph; BEC_2_4_3_MathInt* bevt_5_ta_ph; BEC_2_5_4_LogicBool* bevt_6_ta_ph; BEC_2_4_6_TextString* bevt_7_ta_ph; BEC_2_5_4_LogicBool* bevt_8_ta_ph; BEC_2_4_6_TextString* bevt_9_ta_ph; BEC_2_5_4_LogicBool* bevt_10_ta_ph; BEC_2_4_6_TextString* bevt_11_ta_ph; BEC_2_4_6_TextString* bevt_12_ta_ph; BEC_2_4_6_TextString* bevt_13_ta_ph; BEC_2_4_6_TextString* bevt_14_ta_ph; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->bevl_lbuf = nullptr;
beq->bevl_pe = nullptr;
beq->bevl_ps = nullptr;
beq->bevl_code = nullptr;
beq->bevl_lpos = nullptr;
beq->bevl_res = nullptr;
beq->bevt_0_ta_anchor = nullptr;
beq->bevt_1_ta_ph = nullptr;
beq->bevt_2_ta_ph = nullptr;
beq->bevt_3_ta_ph = nullptr;
beq->bevt_4_ta_ph = nullptr;
beq->bevt_5_ta_ph = nullptr;
beq->bevt_6_ta_ph = nullptr;
beq->bevt_7_ta_ph = nullptr;
beq->bevt_8_ta_ph = nullptr;
beq->bevt_9_ta_ph = nullptr;
beq->bevt_10_ta_ph = nullptr;
beq->bevt_11_ta_ph = nullptr;
beq->bevt_12_ta_ph = nullptr;
beq->bevt_13_ta_ph = nullptr;
beq->bevt_14_ta_ph = nullptr;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(22);

    EEPROM.begin(bevp_eesize->bevi_int);
      beq->bevl_lbuf = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString()))->bem_new_0());
beq->bevl_pe = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(0))));
beq->bevl_ps = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(0))));
beq->bevl_code = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(0))));
beq->bevl_lpos = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(0))));
beq->bevt_1_ta_ph = bevp_magic->bem_sizeGet_0();
bem_epread_5(beq->bevl_lbuf, beq->bevl_ps, beq->bevl_pe, beq->bevl_code, beq->bevt_1_ta_ph);
beq->bevt_3_ta_ph = static_cast<BEC_2_4_7_TextStrings*>(BEC_2_4_7_TextStrings::bece_BEC_2_4_7_TextStrings_bevs_inst);
beq->bevt_2_ta_ph = beq->bevt_3_ta_ph->bem_notEmpty_1(beq->bevl_lbuf);
if (beq->bevt_2_ta_ph->bevi_bool) {
beq->bevt_4_ta_ph = beq->bevl_lbuf->bem_equals_1(bevp_magic);
if (beq->bevt_4_ta_ph->bevi_bool) {
beq->bevt_0_ta_anchor = BECS_Runtime::boolTrue;
} 
 else  {
beq->bevt_0_ta_anchor = BECS_Runtime::boolFalse;
} 
} 
 else  {
beq->bevt_0_ta_anchor = BECS_Runtime::boolFalse;
} 
if (beq->bevt_0_ta_anchor->bevi_bool) {
while (true)
 {
beq->bevl_ps->bevi_int = bevp_zero->bevi_int;
beq->bevt_5_ta_ph = beq->bevl_lbuf->bem_sizeGet_0();
beq->bevt_5_ta_ph->bevi_int = bevp_zero->bevi_int;
beq->bevl_res = bem_epread_5(beq->bevl_lbuf, beq->bevl_ps, beq->bevl_pe, beq->bevl_code, bevp_zero);
if (beq->bevl_res->bevi_int == bevp_us->bevi_int) {
beq->bevt_6_ta_ph = BECS_Runtime::boolTrue;
 } else { 
beq->bevt_6_ta_ph = BECS_Runtime::boolFalse;
}
if (beq->bevt_6_ta_ph->bevi_bool) {
beq->bevt_7_ta_ph = static_cast<BEC_2_4_6_TextString*>(beq->bevl_lbuf->bem_copy_0());
bevp_names->bem_put_2(beq->bevl_lpos, beq->bevt_7_ta_ph);
} 
 else  {
if (beq->bevl_res->bevi_int == bevp_rs->bevi_int) {
beq->bevt_8_ta_ph = BECS_Runtime::boolTrue;
 } else { 
beq->bevt_8_ta_ph = BECS_Runtime::boolFalse;
}
if (beq->bevt_8_ta_ph->bevi_bool) {
beq->bevt_9_ta_ph = static_cast<BEC_2_4_6_TextString*>(beq->bevl_lbuf->bem_copy_0());
bevp_values->bem_put_2(beq->bevl_lpos, beq->bevt_9_ta_ph);
beq->bevl_lpos->bevi_int++;
} 
 else  {
if (beq->bevl_res->bevi_int == bevp_gs->bevi_int) {
beq->bevt_10_ta_ph = BECS_Runtime::boolTrue;
 } else { 
beq->bevt_10_ta_ph = BECS_Runtime::boolFalse;
}
if (beq->bevt_10_ta_ph->bevi_bool) {
beq->bevt_11_ta_ph = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString(13, {0x72,0x65,0x61,0x64,0x20,0x61,0x6C,0x6C,0x20,0x64,0x6F,0x6E,0x65}))));
beq->bevt_11_ta_ph->bem_print_0();
break;
} 
 else  {
beq->bevt_13_ta_ph = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString(10, {0x72,0x65,0x61,0x64,0x20,0x66,0x61,0x69,0x6C,0x20}))));
beq->bevt_12_ta_ph = beq->bevt_13_ta_ph->bem_add_1(beq->bevl_res);
beq->bevt_12_ta_ph->bem_print_0();
break;
} 
} 
} 
} 
} 
 else  {
beq->bevt_14_ta_ph = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString(9, {0x62,0x61,0x64,0x20,0x6D,0x61,0x67,0x69,0x63}))));
beq->bevt_14_ta_ph->bem_print_0();
} 

    EEPROM.commit();
      return this;
}
BEC_2_4_3_MathInt* BEC_2_8_6_EmbeddedConfig::bem_epread_5(BEC_2_4_6_TextString* bevk_lbuf, BEC_2_4_3_MathInt* bevk_ps, BEC_2_4_3_MathInt* bevk_pe, BEC_2_4_3_MathInt* bevk_code, BEC_2_4_3_MathInt* bevk_rsize) {
struct bes { BEC_2_4_6_TextString* beva_lbuf; BEC_2_4_3_MathInt* beva_ps; BEC_2_4_3_MathInt* beva_pe; BEC_2_4_3_MathInt* beva_code; BEC_2_4_3_MathInt* beva_rsize; BEC_2_5_4_LogicBool* bevl_ines; BEC_2_4_3_MathInt* bevl_nsize; BEC_2_5_4_LogicBool* bevt_0_ta_anchor; BEC_2_5_4_LogicBool* bevt_1_ta_anchor; BEC_2_5_4_LogicBool* bevt_2_ta_anchor; BEC_2_5_4_LogicBool* bevt_3_ta_anchor; BEC_2_5_4_LogicBool* bevt_4_ta_ph; BEC_2_4_6_TextString* bevt_5_ta_ph; BEC_2_5_4_LogicBool* bevt_6_ta_ph; BEC_2_5_4_LogicBool* bevt_7_ta_ph; BEC_2_5_4_LogicBool* bevt_8_ta_ph; BEC_2_5_4_LogicBool* bevt_9_ta_ph; BEC_2_5_4_LogicBool* bevt_10_ta_ph; BEC_2_5_4_LogicBool* bevt_11_ta_ph; BEC_2_4_3_MathInt* bevt_12_ta_ph; BEC_2_4_3_MathInt* bevt_13_ta_ph; BEC_2_4_3_MathInt* bevt_14_ta_ph; BEC_2_4_3_MathInt* bevt_15_ta_ph; BEC_2_4_3_MathInt* bevt_16_ta_ph; BEC_2_4_3_MathInt* bevt_17_ta_ph; BEC_2_4_3_MathInt* bevt_18_ta_ph; BEC_2_5_4_LogicBool* bevt_19_ta_ph; BEC_2_5_4_LogicBool* bevt_20_ta_ph; BEC_2_4_3_MathInt* bevt_21_ta_ph; BEC_2_5_4_LogicBool* bevt_22_ta_ph; BEC_2_4_3_MathInt* bevt_23_ta_ph; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->beva_lbuf = bevk_lbuf;
beq->beva_ps = bevk_ps;
beq->beva_pe = bevk_pe;
beq->beva_code = bevk_code;
beq->beva_rsize = bevk_rsize;
beq->bevl_ines = nullptr;
beq->bevl_nsize = nullptr;
beq->bevt_0_ta_anchor = nullptr;
beq->bevt_1_ta_anchor = nullptr;
beq->bevt_2_ta_anchor = nullptr;
beq->bevt_3_ta_anchor = nullptr;
beq->bevt_4_ta_ph = nullptr;
beq->bevt_5_ta_ph = nullptr;
beq->bevt_6_ta_ph = nullptr;
beq->bevt_7_ta_ph = nullptr;
beq->bevt_8_ta_ph = nullptr;
beq->bevt_9_ta_ph = nullptr;
beq->bevt_10_ta_ph = nullptr;
beq->bevt_11_ta_ph = nullptr;
beq->bevt_12_ta_ph = nullptr;
beq->bevt_13_ta_ph = nullptr;
beq->bevt_14_ta_ph = nullptr;
beq->bevt_15_ta_ph = nullptr;
beq->bevt_16_ta_ph = nullptr;
beq->bevt_17_ta_ph = nullptr;
beq->bevt_18_ta_ph = nullptr;
beq->bevt_19_ta_ph = nullptr;
beq->bevt_20_ta_ph = nullptr;
beq->bevt_21_ta_ph = nullptr;
beq->bevt_22_ta_ph = nullptr;
beq->bevt_23_ta_ph = nullptr;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(32);
beq->bevl_ines = static_cast<BEC_2_5_4_LogicBool*>(BECS_Runtime::boolFalse);
while (true)
 {

      beq->beva_code->bevi_int = EEPROM.read(beq->beva_pe->bevi_int);
        if (beq->beva_pe->bevi_int < bevp_eesize->bevi_int) {
beq->bevt_4_ta_ph = BECS_Runtime::boolTrue;
 } else { 
beq->bevt_4_ta_ph = BECS_Runtime::boolFalse;
}
if (beq->bevt_4_ta_ph->bevi_bool) {
beq->beva_pe->bevi_int++;
} 
 else  {
beq->bevt_5_ta_ph = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString(19, {0x4F,0x75,0x74,0x20,0x6F,0x66,0x20,0x65,0x65,0x70,0x72,0x6F,0x6D,0x20,0x73,0x70,0x61,0x63,0x65}))));
beq->bevt_5_ta_ph->bem_print_0();
return bevp_gs;
} 
if (beq->beva_code->bevi_int == bevp_es->bevi_int) {
beq->bevt_6_ta_ph = BECS_Runtime::boolTrue;
 } else { 
beq->bevt_6_ta_ph = BECS_Runtime::boolFalse;
}
if (beq->bevt_6_ta_ph->bevi_bool) {
if (beq->bevl_ines->bevi_bool) {
beq->bevt_7_ta_ph = BECS_Runtime::boolFalse;
 } else { 
beq->bevt_7_ta_ph = BECS_Runtime::boolTrue;
}
if (beq->bevt_7_ta_ph->bevi_bool) {
beq->bevt_0_ta_anchor = BECS_Runtime::boolTrue;
} 
 else  {
beq->bevt_0_ta_anchor = BECS_Runtime::boolFalse;
} 
} 
 else  {
beq->bevt_0_ta_anchor = BECS_Runtime::boolFalse;
} 
if (beq->bevt_0_ta_anchor->bevi_bool) {
beq->bevl_ines = static_cast<BEC_2_5_4_LogicBool*>(BECS_Runtime::boolTrue);
} 
 else  {
if (beq->beva_code->bevi_int == bevp_rs->bevi_int) {
beq->bevt_8_ta_ph = BECS_Runtime::boolTrue;
 } else { 
beq->bevt_8_ta_ph = BECS_Runtime::boolFalse;
}
if (beq->bevt_8_ta_ph->bevi_bool) {
beq->bevt_2_ta_anchor = BECS_Runtime::boolTrue;
} 
 else  {
if (beq->beva_code->bevi_int == bevp_us->bevi_int) {
beq->bevt_9_ta_ph = BECS_Runtime::boolTrue;
 } else { 
beq->bevt_9_ta_ph = BECS_Runtime::boolFalse;
}
if (beq->bevt_9_ta_ph->bevi_bool) {
beq->bevt_2_ta_anchor = BECS_Runtime::boolTrue;
} 
 else  {
beq->bevt_2_ta_anchor = BECS_Runtime::boolFalse;
} 
} 
if (beq->bevt_2_ta_anchor->bevi_bool) {
beq->bevt_1_ta_anchor = BECS_Runtime::boolTrue;
} 
 else  {
if (beq->beva_code->bevi_int == bevp_gs->bevi_int) {
beq->bevt_10_ta_ph = BECS_Runtime::boolTrue;
 } else { 
beq->bevt_10_ta_ph = BECS_Runtime::boolFalse;
}
if (beq->bevt_10_ta_ph->bevi_bool) {
beq->bevt_1_ta_anchor = BECS_Runtime::boolTrue;
} 
 else  {
beq->bevt_1_ta_anchor = BECS_Runtime::boolFalse;
} 
} 
if (beq->bevt_1_ta_anchor->bevi_bool) {
if (!(beq->bevl_ines->bevi_bool)) {
return beq->beva_code;
} 
} 
beq->bevt_12_ta_ph = beq->beva_lbuf->bem_capacityGet_0();
if (beq->beva_ps->bevi_int >= beq->bevt_12_ta_ph->bevi_int) {
beq->bevt_11_ta_ph = BECS_Runtime::boolTrue;
 } else { 
beq->bevt_11_ta_ph = BECS_Runtime::boolFalse;
}
if (beq->bevt_11_ta_ph->bevi_bool) {
beq->bevt_15_ta_ph = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(16))));
beq->bevt_14_ta_ph = beq->beva_ps->bem_add_1(beq->bevt_15_ta_ph);
beq->bevt_16_ta_ph = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(3))));
beq->bevt_13_ta_ph = beq->bevt_14_ta_ph->bem_multiply_1(beq->bevt_16_ta_ph);
beq->bevt_17_ta_ph = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(2))));
beq->bevl_nsize = beq->bevt_13_ta_ph->bem_divide_1(beq->bevt_17_ta_ph);
beq->beva_lbuf->bem_capacitySet_1(beq->bevl_nsize);
} 
beq->beva_lbuf->bem_setCodeUnchecked_2(beq->beva_ps, beq->beva_code);
beq->beva_ps->bevi_int++;
beq->bevt_18_ta_ph = beq->beva_lbuf->bem_sizeGet_0();
beq->bevt_18_ta_ph->bevi_int = beq->beva_ps->bevi_int;
if (beq->bevl_ines->bevi_bool) {
beq->bevl_ines = static_cast<BEC_2_5_4_LogicBool*>(BECS_Runtime::boolFalse);
} 
if (beq->beva_rsize->bevi_int > bevp_zero->bevi_int) {
beq->bevt_19_ta_ph = BECS_Runtime::boolTrue;
 } else { 
beq->bevt_19_ta_ph = BECS_Runtime::boolFalse;
}
if (beq->bevt_19_ta_ph->bevi_bool) {
beq->bevt_21_ta_ph = beq->beva_lbuf->bem_sizeGet_0();
if (beq->bevt_21_ta_ph->bevi_int >= beq->beva_rsize->bevi_int) {
beq->bevt_20_ta_ph = BECS_Runtime::boolTrue;
 } else { 
beq->bevt_20_ta_ph = BECS_Runtime::boolFalse;
}
if (beq->bevt_20_ta_ph->bevi_bool) {
beq->bevt_3_ta_anchor = BECS_Runtime::boolTrue;
} 
 else  {
beq->bevt_3_ta_anchor = BECS_Runtime::boolFalse;
} 
} 
 else  {
beq->bevt_3_ta_anchor = BECS_Runtime::boolFalse;
} 
if (beq->bevt_3_ta_anchor->bevi_bool) {
return beq->beva_rsize;
} 
beq->bevt_23_ta_ph = beq->beva_lbuf->bem_sizeGet_0();
if (beq->bevt_23_ta_ph->bevi_int >= bevp_maxsz->bevi_int) {
beq->bevt_22_ta_ph = BECS_Runtime::boolTrue;
 } else { 
beq->bevt_22_ta_ph = BECS_Runtime::boolFalse;
}
if (beq->bevt_22_ta_ph->bevi_bool) {
return bevp_gs;
} 
} 
} 
}
BEC_2_8_6_EmbeddedConfig* BEC_2_8_6_EmbeddedConfig::bem_save_0() {
struct bes { BEC_2_4_3_MathInt* bevl_pe; BEC_2_4_3_MathInt* bevl_ps; BEC_2_4_3_MathInt* bevl_css; BEC_2_4_3_MathInt* bevl_code; BEC_2_4_3_MathInt* bevl_lpos; BEC_2_4_6_TextString* bevl_name; BEC_2_4_6_TextString* bevl_value; BEC_2_5_4_LogicBool* bevt_0_ta_anchor; BEC_2_5_4_LogicBool* bevt_1_ta_anchor; BEC_2_5_4_LogicBool* bevt_2_ta_ph; BEC_2_5_4_LogicBool* bevt_3_ta_ph; BEC_2_4_3_MathInt* bevt_4_ta_ph; BEC_2_5_4_LogicBool* bevt_5_ta_ph; BEC_2_4_7_TextStrings* bevt_6_ta_ph; BEC_2_5_4_LogicBool* bevt_7_ta_ph; BEC_2_4_7_TextStrings* bevt_8_ta_ph; BEC_2_5_4_LogicBool* bevt_9_ta_ph; BEC_2_4_3_MathInt* bevt_10_ta_ph; BEC_2_5_4_LogicBool* bevt_11_ta_ph; BEC_2_4_3_MathInt* bevt_12_ta_ph; BEC_2_5_4_LogicBool* bevt_13_ta_ph; BEC_2_5_4_LogicBool* bevt_14_ta_ph; BEC_2_5_4_LogicBool* bevt_15_ta_ph; BEC_2_5_4_LogicBool* bevt_16_ta_ph; BEC_2_4_6_TextString* bevt_17_ta_ph; BEC_2_5_4_LogicBool* bevt_18_ta_ph; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->bevl_pe = nullptr;
beq->bevl_ps = nullptr;
beq->bevl_css = nullptr;
beq->bevl_code = nullptr;
beq->bevl_lpos = nullptr;
beq->bevl_name = nullptr;
beq->bevl_value = nullptr;
beq->bevt_0_ta_anchor = nullptr;
beq->bevt_1_ta_anchor = nullptr;
beq->bevt_2_ta_ph = nullptr;
beq->bevt_3_ta_ph = nullptr;
beq->bevt_4_ta_ph = nullptr;
beq->bevt_5_ta_ph = nullptr;
beq->bevt_6_ta_ph = nullptr;
beq->bevt_7_ta_ph = nullptr;
beq->bevt_8_ta_ph = nullptr;
beq->bevt_9_ta_ph = nullptr;
beq->bevt_10_ta_ph = nullptr;
beq->bevt_11_ta_ph = nullptr;
beq->bevt_12_ta_ph = nullptr;
beq->bevt_13_ta_ph = nullptr;
beq->bevt_14_ta_ph = nullptr;
beq->bevt_15_ta_ph = nullptr;
beq->bevt_16_ta_ph = nullptr;
beq->bevt_17_ta_ph = nullptr;
beq->bevt_18_ta_ph = nullptr;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(27);

    EEPROM.begin(bevp_eesize->bevi_int);
      beq->bevl_pe = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(0))));
beq->bevl_ps = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(0))));
beq->bevl_css = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(0))));
beq->bevl_code = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(0))));
beq->bevt_2_ta_ph = static_cast<BEC_2_5_4_LogicBool*>(BECS_Runtime::boolFalse);
bem_epwrite_6(bevp_magic, beq->bevl_css, beq->bevl_ps, beq->bevl_pe, beq->bevl_code, beq->bevt_2_ta_ph);
beq->bevl_lpos = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(0))));
while (true)
 {
beq->bevt_4_ta_ph = bevp_names->bem_sizeGet_0();
if (beq->bevl_lpos->bevi_int < beq->bevt_4_ta_ph->bevi_int) {
beq->bevt_3_ta_ph = BECS_Runtime::boolTrue;
 } else { 
beq->bevt_3_ta_ph = BECS_Runtime::boolFalse;
}
if (beq->bevt_3_ta_ph->bevi_bool) {
beq->bevl_name = static_cast<BEC_2_4_6_TextString*>(bevp_names->bem_get_1(beq->bevl_lpos));
beq->bevl_value = static_cast<BEC_2_4_6_TextString*>(bevp_values->bem_get_1(beq->bevl_lpos));
beq->bevt_6_ta_ph = static_cast<BEC_2_4_7_TextStrings*>(BEC_2_4_7_TextStrings::bece_BEC_2_4_7_TextStrings_bevs_inst);
beq->bevt_5_ta_ph = beq->bevt_6_ta_ph->bem_notEmpty_1(beq->bevl_name);
if (beq->bevt_5_ta_ph->bevi_bool) {
beq->bevt_8_ta_ph = static_cast<BEC_2_4_7_TextStrings*>(BEC_2_4_7_TextStrings::bece_BEC_2_4_7_TextStrings_bevs_inst);
beq->bevt_7_ta_ph = beq->bevt_8_ta_ph->bem_notEmpty_1(beq->bevl_value);
if (beq->bevt_7_ta_ph->bevi_bool) {
beq->bevt_0_ta_anchor = BECS_Runtime::boolTrue;
} 
 else  {
beq->bevt_0_ta_anchor = BECS_Runtime::boolFalse;
} 
} 
 else  {
beq->bevt_0_ta_anchor = BECS_Runtime::boolFalse;
} 
if (beq->bevt_0_ta_anchor->bevi_bool) {
beq->bevt_10_ta_ph = beq->bevl_name->bem_sizeGet_0();
if (beq->bevt_10_ta_ph->bevi_int < bevp_maxsz->bevi_int) {
beq->bevt_9_ta_ph = BECS_Runtime::boolTrue;
 } else { 
beq->bevt_9_ta_ph = BECS_Runtime::boolFalse;
}
if (beq->bevt_9_ta_ph->bevi_bool) {
beq->bevt_12_ta_ph = beq->bevl_value->bem_sizeGet_0();
if (beq->bevt_12_ta_ph->bevi_int < bevp_maxsz->bevi_int) {
beq->bevt_11_ta_ph = BECS_Runtime::boolTrue;
 } else { 
beq->bevt_11_ta_ph = BECS_Runtime::boolFalse;
}
if (beq->bevt_11_ta_ph->bevi_bool) {
beq->bevt_1_ta_anchor = BECS_Runtime::boolTrue;
} 
 else  {
beq->bevt_1_ta_anchor = BECS_Runtime::boolFalse;
} 
} 
 else  {
beq->bevt_1_ta_anchor = BECS_Runtime::boolFalse;
} 
if (beq->bevt_1_ta_anchor->bevi_bool) {
beq->bevt_13_ta_ph = static_cast<BEC_2_5_4_LogicBool*>(BECS_Runtime::boolFalse);
bem_epwrite_6(beq->bevl_name, beq->bevl_css, beq->bevl_ps, beq->bevl_pe, beq->bevl_code, beq->bevt_13_ta_ph);
beq->bevt_14_ta_ph = static_cast<BEC_2_5_4_LogicBool*>(BECS_Runtime::boolTrue);
bem_epwrite_6(bevp_uss, beq->bevl_css, beq->bevl_ps, beq->bevl_pe, beq->bevl_code, beq->bevt_14_ta_ph);
beq->bevt_15_ta_ph = static_cast<BEC_2_5_4_LogicBool*>(BECS_Runtime::boolFalse);
bem_epwrite_6(beq->bevl_value, beq->bevl_css, beq->bevl_ps, beq->bevl_pe, beq->bevl_code, beq->bevt_15_ta_ph);
beq->bevt_16_ta_ph = static_cast<BEC_2_5_4_LogicBool*>(BECS_Runtime::boolTrue);
bem_epwrite_6(bevp_rss, beq->bevl_css, beq->bevl_ps, beq->bevl_pe, beq->bevl_code, beq->bevt_16_ta_ph);
} 
 else  {
beq->bevt_17_ta_ph = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString(30, {0x6E,0x61,0x6D,0x65,0x20,0x6F,0x72,0x20,0x76,0x61,0x6C,0x75,0x65,0x20,0x74,0x6F,0x6F,0x20,0x62,0x69,0x67,0x20,0x74,0x6F,0x20,0x77,0x72,0x69,0x74,0x65}))));
beq->bevt_17_ta_ph->bem_print_0();
} 
} 
 else  {
} 
beq->bevl_lpos->bevi_int++;
} 
 else  {
break;
} 
} 
beq->bevt_18_ta_ph = static_cast<BEC_2_5_4_LogicBool*>(BECS_Runtime::boolTrue);
bem_epwrite_6(bevp_gss, beq->bevl_css, beq->bevl_ps, beq->bevl_pe, beq->bevl_code, beq->bevt_18_ta_ph);

    EEPROM.commit();
      return this;
}
BEC_2_8_6_EmbeddedConfig* BEC_2_8_6_EmbeddedConfig::bem_epwrite_6(BEC_2_4_6_TextString* bevk_ws, BEC_2_4_3_MathInt* bevk_css, BEC_2_4_3_MathInt* bevk_ps, BEC_2_4_3_MathInt* bevk_pe, BEC_2_4_3_MathInt* bevk_code, BEC_2_5_4_LogicBool* bevk_noes) {
struct bes { BEC_2_4_6_TextString* beva_ws; BEC_2_4_3_MathInt* beva_css; BEC_2_4_3_MathInt* beva_ps; BEC_2_4_3_MathInt* beva_pe; BEC_2_4_3_MathInt* beva_code; BEC_2_5_4_LogicBool* beva_noes; BEC_2_5_4_LogicBool* bevt_0_ta_anchor; BEC_2_5_4_LogicBool* bevt_1_ta_anchor; BEC_2_5_4_LogicBool* bevt_2_ta_anchor; BEC_2_4_3_MathInt* bevt_3_ta_ph; BEC_2_5_4_LogicBool* bevt_4_ta_ph; BEC_2_5_4_LogicBool* bevt_5_ta_ph; BEC_2_5_4_LogicBool* bevt_6_ta_ph; BEC_2_5_4_LogicBool* bevt_7_ta_ph; BEC_2_5_4_LogicBool* bevt_8_ta_ph; BEC_2_5_4_LogicBool* bevt_9_ta_ph; BEC_2_5_4_LogicBool* bevt_10_ta_ph; BEC_2_4_6_TextString* bevt_11_ta_ph; BEC_2_4_6_TextString* bevt_12_ta_ph; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->beva_ws = bevk_ws;
beq->beva_css = bevk_css;
beq->beva_ps = bevk_ps;
beq->beva_pe = bevk_pe;
beq->beva_code = bevk_code;
beq->beva_noes = bevk_noes;
beq->bevt_0_ta_anchor = nullptr;
beq->bevt_1_ta_anchor = nullptr;
beq->bevt_2_ta_anchor = nullptr;
beq->bevt_3_ta_ph = nullptr;
beq->bevt_4_ta_ph = nullptr;
beq->bevt_5_ta_ph = nullptr;
beq->bevt_6_ta_ph = nullptr;
beq->bevt_7_ta_ph = nullptr;
beq->bevt_8_ta_ph = nullptr;
beq->bevt_9_ta_ph = nullptr;
beq->bevt_10_ta_ph = nullptr;
beq->bevt_11_ta_ph = nullptr;
beq->bevt_12_ta_ph = nullptr;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(20);
beq->bevt_3_ta_ph = beq->beva_ws->bem_sizeGet_0();
beq->beva_css->bevi_int = beq->bevt_3_ta_ph->bevi_int;
beq->beva_ps->bevi_int = bevp_zero->bevi_int;
while (true)
 {
if (beq->beva_ps->bevi_int < beq->beva_css->bevi_int) {
beq->bevt_4_ta_ph = BECS_Runtime::boolTrue;
 } else { 
beq->bevt_4_ta_ph = BECS_Runtime::boolFalse;
}
if (beq->bevt_4_ta_ph->bevi_bool) {
if (beq->beva_pe->bevi_int < bevp_eesize->bevi_int) {
beq->bevt_5_ta_ph = BECS_Runtime::boolTrue;
 } else { 
beq->bevt_5_ta_ph = BECS_Runtime::boolFalse;
}
if (beq->bevt_5_ta_ph->bevi_bool) {
beq->beva_ws->bem_getCode_2(beq->beva_ps, beq->beva_code);
if (beq->beva_code->bevi_int == bevp_es->bevi_int) {
beq->bevt_6_ta_ph = BECS_Runtime::boolTrue;
 } else { 
beq->bevt_6_ta_ph = BECS_Runtime::boolFalse;
}
if (beq->bevt_6_ta_ph->bevi_bool) {
beq->bevt_2_ta_anchor = BECS_Runtime::boolTrue;
} 
 else  {
if (beq->beva_code->bevi_int == bevp_gs->bevi_int) {
beq->bevt_7_ta_ph = BECS_Runtime::boolTrue;
 } else { 
beq->bevt_7_ta_ph = BECS_Runtime::boolFalse;
}
if (beq->bevt_7_ta_ph->bevi_bool) {
beq->bevt_2_ta_anchor = BECS_Runtime::boolTrue;
} 
 else  {
beq->bevt_2_ta_anchor = BECS_Runtime::boolFalse;
} 
} 
if (beq->bevt_2_ta_anchor->bevi_bool) {
beq->bevt_1_ta_anchor = BECS_Runtime::boolTrue;
} 
 else  {
if (beq->beva_code->bevi_int == bevp_us->bevi_int) {
beq->bevt_8_ta_ph = BECS_Runtime::boolTrue;
 } else { 
beq->bevt_8_ta_ph = BECS_Runtime::boolFalse;
}
if (beq->bevt_8_ta_ph->bevi_bool) {
beq->bevt_1_ta_anchor = BECS_Runtime::boolTrue;
} 
 else  {
beq->bevt_1_ta_anchor = BECS_Runtime::boolFalse;
} 
} 
if (beq->bevt_1_ta_anchor->bevi_bool) {
beq->bevt_0_ta_anchor = BECS_Runtime::boolTrue;
} 
 else  {
if (beq->beva_code->bevi_int == bevp_rs->bevi_int) {
beq->bevt_9_ta_ph = BECS_Runtime::boolTrue;
 } else { 
beq->bevt_9_ta_ph = BECS_Runtime::boolFalse;
}
if (beq->bevt_9_ta_ph->bevi_bool) {
beq->bevt_0_ta_anchor = BECS_Runtime::boolTrue;
} 
 else  {
beq->bevt_0_ta_anchor = BECS_Runtime::boolFalse;
} 
} 
if (beq->bevt_0_ta_anchor->bevi_bool) {
if (!(beq->beva_noes->bevi_bool)) {

                EEPROM.write(beq->beva_pe->bevi_int, bevp_es->bevi_int);
                  beq->beva_pe->bevi_int++;
if (beq->beva_pe->bevi_int >= bevp_eesize->bevi_int) {
beq->bevt_10_ta_ph = BECS_Runtime::boolTrue;
 } else { 
beq->bevt_10_ta_ph = BECS_Runtime::boolFalse;
}
if (beq->bevt_10_ta_ph->bevi_bool) {
beq->bevt_11_ta_ph = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString(19, {0x4F,0x75,0x74,0x20,0x6F,0x66,0x20,0x65,0x65,0x70,0x72,0x6F,0x6D,0x20,0x73,0x70,0x61,0x63,0x65}))));
beq->bevt_11_ta_ph->bem_print_0();
return this;
} 
} 
} 

            EEPROM.write(beq->beva_pe->bevi_int, beq->beva_code->bevi_int);
              beq->beva_pe->bevi_int++;
} 
 else  {
beq->bevt_12_ta_ph = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString(19, {0x4F,0x75,0x74,0x20,0x6F,0x66,0x20,0x65,0x65,0x70,0x72,0x6F,0x6D,0x20,0x73,0x70,0x61,0x63,0x65}))));
beq->bevt_12_ta_ph->bem_print_0();
return this;
} 
beq->beva_ps->bevi_int++;
} 
 else  {
break;
} 
} 
return this;
}
BEC_2_4_3_MathInt* BEC_2_8_6_EmbeddedConfig::bem_eesizeGet_0() {
struct bes {  BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(1);
return bevp_eesize;
}
BEC_2_8_6_EmbeddedConfig* BEC_2_8_6_EmbeddedConfig::bem_eesizeSet_1(BEC_2_6_6_SystemObject* bevt_0_ta_SET) {
struct bes { BEC_2_6_6_SystemObject* bevt_0_ta_SET; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->bevt_0_ta_SET = bevt_0_ta_SET;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(2);
bevp_eesize = static_cast<BEC_2_4_3_MathInt*>(beq->bevt_0_ta_SET);
return this;
}
BEC_2_4_3_MathInt* BEC_2_8_6_EmbeddedConfig::bem_maxszGet_0() {
struct bes {  BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(1);
return bevp_maxsz;
}
BEC_2_8_6_EmbeddedConfig* BEC_2_8_6_EmbeddedConfig::bem_maxszSet_1(BEC_2_6_6_SystemObject* bevt_0_ta_SET) {
struct bes { BEC_2_6_6_SystemObject* bevt_0_ta_SET; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->bevt_0_ta_SET = bevt_0_ta_SET;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(2);
bevp_maxsz = static_cast<BEC_2_4_3_MathInt*>(beq->bevt_0_ta_SET);
return this;
}
BEC_2_9_4_ContainerList* BEC_2_8_6_EmbeddedConfig::bem_namesGet_0() {
struct bes {  BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(1);
return bevp_names;
}
BEC_2_8_6_EmbeddedConfig* BEC_2_8_6_EmbeddedConfig::bem_namesSet_1(BEC_2_6_6_SystemObject* bevt_0_ta_SET) {
struct bes { BEC_2_6_6_SystemObject* bevt_0_ta_SET; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->bevt_0_ta_SET = bevt_0_ta_SET;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(2);
bevp_names = static_cast<BEC_2_9_4_ContainerList*>(beq->bevt_0_ta_SET);
return this;
}
BEC_2_9_4_ContainerList* BEC_2_8_6_EmbeddedConfig::bem_valuesGet_0() {
struct bes {  BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(1);
return bevp_values;
}
BEC_2_8_6_EmbeddedConfig* BEC_2_8_6_EmbeddedConfig::bem_valuesSet_1(BEC_2_6_6_SystemObject* bevt_0_ta_SET) {
struct bes { BEC_2_6_6_SystemObject* bevt_0_ta_SET; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->bevt_0_ta_SET = bevt_0_ta_SET;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(2);
bevp_values = static_cast<BEC_2_9_4_ContainerList*>(beq->bevt_0_ta_SET);
return this;
}
BEC_2_5_4_LogicBool* BEC_2_8_6_EmbeddedConfig::bem_changedGet_0() {
struct bes {  BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(1);
return bevp_changed;
}
BEC_2_8_6_EmbeddedConfig* BEC_2_8_6_EmbeddedConfig::bem_changedSet_1(BEC_2_6_6_SystemObject* bevt_0_ta_SET) {
struct bes { BEC_2_6_6_SystemObject* bevt_0_ta_SET; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->bevt_0_ta_SET = bevt_0_ta_SET;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(2);
bevp_changed = static_cast<BEC_2_5_4_LogicBool*>(beq->bevt_0_ta_SET);
return this;
}
BEC_2_4_6_TextString* BEC_2_8_6_EmbeddedConfig::bem_magicGet_0() {
struct bes {  BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(1);
return bevp_magic;
}
BEC_2_8_6_EmbeddedConfig* BEC_2_8_6_EmbeddedConfig::bem_magicSet_1(BEC_2_6_6_SystemObject* bevt_0_ta_SET) {
struct bes { BEC_2_6_6_SystemObject* bevt_0_ta_SET; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->bevt_0_ta_SET = bevt_0_ta_SET;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(2);
bevp_magic = static_cast<BEC_2_4_6_TextString*>(beq->bevt_0_ta_SET);
return this;
}
BEC_2_6_6_SystemObject* BEC_2_8_6_EmbeddedConfig::bemd_0(int32_t callId) {
switch (callId) {
case 457905500: return bem_namesGet_0();
case -2050131411: return bem_load_0();
case -1851102488: return bem_valuesGet_0();
case 729843097: return bem_eesizeGet_0();
case 42690229: return bem_maybeSave_0();
case -1785532669: return bem_new_0();
case 1085625590: return bem_save_0();
case 1561052494: return bem_magicGet_0();
case 117300340: return bem_changedGet_0();
case -1395793730: return bem_maxszGet_0();
}
return bevs_super::bemd_0(callId);
}
BEC_2_6_6_SystemObject* BEC_2_8_6_EmbeddedConfig::bemd_1(int32_t callId, BEC_2_6_6_SystemObject* bevd_0) {
switch (callId) {
case -641636713: return bem_getPos_1(static_cast<BEC_2_4_6_TextString*>(bevd_0));
case -2117772090: return bem_eesizeSet_1(bevd_0);
case -1109943370: return bem_namesSet_1(bevd_0);
case 1405447397: return bem_valuesSet_1(bevd_0);
case -1362425993: return bem_get_1(static_cast<BEC_2_4_3_MathInt*>(bevd_0));
case 1912665300: return bem_maxszSet_1(bevd_0);
case -2120193381: return bem_changedSet_1(bevd_0);
case 572089349: return bem_magicSet_1(bevd_0);
}
return bevs_super::bemd_1(callId, bevd_0);
}
BEC_2_6_6_SystemObject* BEC_2_8_6_EmbeddedConfig::bemd_2(int32_t callId, BEC_2_6_6_SystemObject* bevd_0, BEC_2_6_6_SystemObject* bevd_1) {
switch (callId) {
case -1764267367: return bem_put_2(static_cast<BEC_2_4_3_MathInt*>(bevd_0), static_cast<BEC_2_4_6_TextString*>(bevd_1));
}
return bevs_super::bemd_2(callId, bevd_0, bevd_1);
}
BEC_2_6_6_SystemObject* BEC_2_8_6_EmbeddedConfig::bemd_5(int32_t callId, BEC_2_6_6_SystemObject* bevd_0, BEC_2_6_6_SystemObject* bevd_1, BEC_2_6_6_SystemObject* bevd_2, BEC_2_6_6_SystemObject* bevd_3, BEC_2_6_6_SystemObject* bevd_4) {
switch (callId) {
case 489432662: return bem_epread_5(static_cast<BEC_2_4_6_TextString*>(bevd_0), static_cast<BEC_2_4_3_MathInt*>(bevd_1), static_cast<BEC_2_4_3_MathInt*>(bevd_2), static_cast<BEC_2_4_3_MathInt*>(bevd_3), static_cast<BEC_2_4_3_MathInt*>(bevd_4));
}
return bevs_super::bemd_5(callId, bevd_0, bevd_1, bevd_2, bevd_3, bevd_4);
}
BEC_2_6_6_SystemObject* BEC_2_8_6_EmbeddedConfig::bemd_6(int32_t callId, BEC_2_6_6_SystemObject* bevd_0, BEC_2_6_6_SystemObject* bevd_1, BEC_2_6_6_SystemObject* bevd_2, BEC_2_6_6_SystemObject* bevd_3, BEC_2_6_6_SystemObject* bevd_4, BEC_2_6_6_SystemObject* bevd_5) {
switch (callId) {
case -1997097663: return bem_epwrite_6(static_cast<BEC_2_4_6_TextString*>(bevd_0), static_cast<BEC_2_4_3_MathInt*>(bevd_1), static_cast<BEC_2_4_3_MathInt*>(bevd_2), static_cast<BEC_2_4_3_MathInt*>(bevd_3), static_cast<BEC_2_4_3_MathInt*>(bevd_4), static_cast<BEC_2_5_4_LogicBool*>(bevd_5));
}
return bevs_super::bemd_6(callId, bevd_0, bevd_1, bevd_2, bevd_3, bevd_4, bevd_5);
}
BEC_2_6_6_SystemObject* BEC_2_8_6_EmbeddedConfig::bemc_create() {
return new BEC_2_8_6_EmbeddedConfig();
}
void BEC_2_8_6_EmbeddedConfig::bemc_setInitial(BEC_2_6_6_SystemObject* becc_inst) {
BEC_2_8_6_EmbeddedConfig::bece_BEC_2_8_6_EmbeddedConfig_bevs_inst = static_cast<BEC_2_8_6_EmbeddedConfig*>(becc_inst);
}
BEC_2_6_6_SystemObject* BEC_2_8_6_EmbeddedConfig::bemc_getInitial() {
return BEC_2_8_6_EmbeddedConfig::bece_BEC_2_8_6_EmbeddedConfig_bevs_inst;
}
void BEC_2_8_6_EmbeddedConfig::bemg_doMark() {
bevg_gcMark = BECS_Runtime::bevg_currentGcMark;
if (bevp_eesize != nullptr && bevp_eesize->bevg_gcMark != BECS_Runtime::bevg_currentGcMark) {
bevp_eesize->bemg_doMark();
}
if (bevp_maxsz != nullptr && bevp_maxsz->bevg_gcMark != BECS_Runtime::bevg_currentGcMark) {
bevp_maxsz->bemg_doMark();
}
if (bevp_names != nullptr && bevp_names->bevg_gcMark != BECS_Runtime::bevg_currentGcMark) {
bevp_names->bemg_doMark();
}
if (bevp_values != nullptr && bevp_values->bevg_gcMark != BECS_Runtime::bevg_currentGcMark) {
bevp_values->bemg_doMark();
}
if (bevp_changed != nullptr && bevp_changed->bevg_gcMark != BECS_Runtime::bevg_currentGcMark) {
bevp_changed->bemg_doMark();
}
if (bevp_magic != nullptr && bevp_magic->bevg_gcMark != BECS_Runtime::bevg_currentGcMark) {
bevp_magic->bemg_doMark();
}
if (bevp_zero != nullptr && bevp_zero->bevg_gcMark != BECS_Runtime::bevg_currentGcMark) {
bevp_zero->bemg_doMark();
}
if (bevp_one != nullptr && bevp_one->bevg_gcMark != BECS_Runtime::bevg_currentGcMark) {
bevp_one->bemg_doMark();
}
if (bevp_es != nullptr && bevp_es->bevg_gcMark != BECS_Runtime::bevg_currentGcMark) {
bevp_es->bemg_doMark();
}
if (bevp_ess != nullptr && bevp_ess->bevg_gcMark != BECS_Runtime::bevg_currentGcMark) {
bevp_ess->bemg_doMark();
}
if (bevp_gs != nullptr && bevp_gs->bevg_gcMark != BECS_Runtime::bevg_currentGcMark) {
bevp_gs->bemg_doMark();
}
if (bevp_gss != nullptr && bevp_gss->bevg_gcMark != BECS_Runtime::bevg_currentGcMark) {
bevp_gss->bemg_doMark();
}
if (bevp_us != nullptr && bevp_us->bevg_gcMark != BECS_Runtime::bevg_currentGcMark) {
bevp_us->bemg_doMark();
}
if (bevp_uss != nullptr && bevp_uss->bevg_gcMark != BECS_Runtime::bevg_currentGcMark) {
bevp_uss->bemg_doMark();
}
if (bevp_rs != nullptr && bevp_rs->bevg_gcMark != BECS_Runtime::bevg_currentGcMark) {
bevp_rs->bemg_doMark();
}
if (bevp_rss != nullptr && bevp_rss->bevg_gcMark != BECS_Runtime::bevg_currentGcMark) {
bevp_rss->bemg_doMark();
}
}
size_t BEC_2_8_6_EmbeddedConfig::bemg_getSize() {
return sizeof(*this);
}
BETS_Object* BEC_2_8_6_EmbeddedConfig::bemc_getType() {
return &BEC_2_8_6_EmbeddedConfig::bece_BEC_2_8_6_EmbeddedConfig_bevs_type;
}
BET_2_8_4_EmbeddedWifi::BET_2_8_4_EmbeddedWifi() {
std::vector<std::string> bevs_mtnames = {  };
bevs_fieldNames = {  };
}
BEC_2_6_6_SystemObject* BET_2_8_4_EmbeddedWifi::bems_createInstance() {
return new BEC_2_8_4_EmbeddedWifi();
}
void BET_2_8_4_EmbeddedWifi::bemgt_doMark() {
BEC_2_6_6_SystemObject* bevsl_inst_ref = *bevs_inst_ref;
if (bevsl_inst_ref != nullptr && bevsl_inst_ref->bevg_gcMark != BECS_Runtime::bevg_currentGcMark) {
bevsl_inst_ref->bemg_doMark();
}
}
BEC_2_8_4_EmbeddedWifi* BEC_2_8_4_EmbeddedWifi::bece_BEC_2_8_4_EmbeddedWifi_bevs_inst;

BET_2_8_4_EmbeddedWifi BEC_2_8_4_EmbeddedWifi::bece_BEC_2_8_4_EmbeddedWifi_bevs_type;
BEC_2_6_6_SystemObject** BET_2_8_4_EmbeddedWifi::bevs_inst_ref = (BEC_2_6_6_SystemObject**) &BEC_2_8_4_EmbeddedWifi::bece_BEC_2_8_4_EmbeddedWifi_bevs_inst;

BEC_2_8_4_EmbeddedWifi* BEC_2_8_4_EmbeddedWifi::bem_default_0() {
struct bes {  BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(1);
bevp_up = static_cast<BEC_2_5_4_LogicBool*>(BECS_Runtime::boolFalse);
return this;
}
BEC_2_8_4_EmbeddedWifi* BEC_2_8_4_EmbeddedWifi::bem_clear_0() {
struct bes {  BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(1);
bevp_mode = nullptr;
bevp_up = static_cast<BEC_2_5_4_LogicBool*>(BECS_Runtime::boolFalse);
bevp_localIP = nullptr;
return this;
}
BEC_2_8_4_EmbeddedWifi* BEC_2_8_4_EmbeddedWifi::bem_clearAll_0() {
struct bes {  BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(1);
bem_clear_0();
bevp_ssid = nullptr;
bevp_password = nullptr;
return this;
}
BEC_2_8_4_EmbeddedWifi* BEC_2_8_4_EmbeddedWifi::bem_new_2(BEC_2_4_6_TextString* bevk__ssid, BEC_2_4_6_TextString* bevk__password) {
struct bes { BEC_2_4_6_TextString* beva__ssid; BEC_2_4_6_TextString* beva__password; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->beva__ssid = bevk__ssid;
beq->beva__password = bevk__password;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(3);
bevp_ssid = beq->beva__ssid;
bevp_password = beq->beva__password;
return this;
}
BEC_2_4_6_TextString* BEC_2_8_4_EmbeddedWifi::bem_macAddressGet_0() {
struct bes { BEC_2_4_6_TextString* bevl_macAddress; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->bevl_macAddress = nullptr;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(2);

      String mac = WiFi.macAddress();
      std::string macs = std::string(mac.c_str());
      beq->bevl_macAddress = new BEC_2_4_6_TextString(macs);
      return beq->bevl_macAddress;
}
BEC_2_9_4_ContainerList* BEC_2_8_4_EmbeddedWifi::bem_scanNetworks_0() {
struct bes { BEC_2_9_4_ContainerList* bevl_networks; BEC_2_4_6_TextString* bevl_network; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->bevl_networks = nullptr;
beq->bevl_network = nullptr;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(3);
beq->bevl_networks = static_cast<BEC_2_9_4_ContainerList*>(((BEC_2_9_4_ContainerList*) (new BEC_2_9_4_ContainerList()))->bem_new_0());

      int numberOfNetworks = WiFi.scanNetworks();

      for(int i =0; i<numberOfNetworks; i++){
        String ssid = WiFi.SSID(i);
        std::string ssids = std::string(ssid.c_str());
        beq->bevl_network = new BEC_2_4_6_TextString(ssids);
        beq->bevl_networks->bem_addValue_1(beq->bevl_network);
      }

      return beq->bevl_networks;
}
BEC_2_8_4_EmbeddedWifi* BEC_2_8_4_EmbeddedWifi::bem_startAp_0() {
struct bes { BEC_2_4_6_TextString* bevt_0_ta_ph; BEC_2_4_6_TextString* bevt_1_ta_ph; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->bevt_0_ta_ph = nullptr;
beq->bevt_1_ta_ph = nullptr;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(3);
bem_clear_0();
bevp_mode = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString(2, {0x61,0x70}))));
beq->bevt_1_ta_ph = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString(12, {0x53,0x74,0x61,0x72,0x74,0x69,0x6E,0x67,0x20,0x41,0x50,0x20}))));
beq->bevt_0_ta_ph = beq->bevt_1_ta_ph->bem_add_1(bevp_ssid);
beq->bevt_0_ta_ph->bem_print_0();

      boolean result = false;
      if (bevp_password == nullptr) {
        result = WiFi.softAP(bevp_ssid->bems_toCcString().c_str());
      } else {
        result = WiFi.softAP(bevp_ssid->bems_toCcString().c_str(), bevp_password->bems_toCcString().c_str());
      }
      if(result == true)
      {
        //Serial.println("AP Started");
        String lip = WiFi.softAPIP().toString();
        std::string lips = std::string(lip.c_str());
        bevp_localIP = new BEC_2_4_6_TextString(lips);
        bevp_up = BECS_Runtime::boolTrue;
      }
      else
      {
        //Serial.println("AP Start Failed!");
        bevp_up = BECS_Runtime::boolFalse;
      }
      return this;
}
BEC_2_8_4_EmbeddedWifi* BEC_2_8_4_EmbeddedWifi::bem_start_0() {
struct bes { BEC_2_4_6_TextString* bevt_0_ta_ph; BEC_2_4_6_TextString* bevt_1_ta_ph; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->bevt_0_ta_ph = nullptr;
beq->bevt_1_ta_ph = nullptr;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(3);
bem_clear_0();
bevp_mode = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString(7, {0x73,0x74,0x61,0x74,0x69,0x6F,0x6E}))));
beq->bevt_1_ta_ph = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString(14, {0x43,0x6F,0x6E,0x6E,0x65,0x63,0x74,0x69,0x6E,0x67,0x20,0x74,0x6F,0x20}))));
beq->bevt_0_ta_ph = beq->bevt_1_ta_ph->bem_add_1(bevp_ssid);
beq->bevt_0_ta_ph->bem_print_0();

    WiFi.setAutoReconnect(false);
    WiFi.persistent(false);
    WiFi.begin(bevp_ssid->bems_toCcString().c_str(), bevp_password->bems_toCcString().c_str());
    int count = 0;
    while (WiFi.status() != WL_CONNECTED && count < 40) {
      delay(500);
      Serial.print(".");
      count++;
    }
    if (WiFi.status() == WL_CONNECTED) {
      //Serial.print("Connected, IP address:\t");
      WiFi.setAutoReconnect(false);
      WiFi.persistent(false);
      Serial.println(WiFi.localIP());

      String lip = WiFi.localIP().toString();
      std::string lips = std::string(lip.c_str());
      bevp_localIP = new BEC_2_4_6_TextString(lips);

      bevp_up = BECS_Runtime::boolTrue;
    } else {
      //Serial.println("no luck connecting to wifi");
      bevp_up = BECS_Runtime::boolFalse;
    }
    return this;
}
BEC_2_5_4_LogicBool* BEC_2_8_4_EmbeddedWifi::bem_isConnectedGet_0() {
struct bes { BEC_2_5_4_LogicBool* bevl_connected; BEC_2_5_4_LogicBool* bevt_0_ta_anchor; BEC_2_5_4_LogicBool* bevt_1_ta_anchor; BEC_2_5_4_LogicBool* bevt_2_ta_ph; BEC_2_4_7_TextStrings* bevt_3_ta_ph; BEC_2_5_4_LogicBool* bevt_4_ta_ph; BEC_2_4_6_TextString* bevt_5_ta_ph; BEC_2_5_4_LogicBool* bevt_6_ta_ph; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->bevl_connected = nullptr;
beq->bevt_0_ta_anchor = nullptr;
beq->bevt_1_ta_anchor = nullptr;
beq->bevt_2_ta_ph = nullptr;
beq->bevt_3_ta_ph = nullptr;
beq->bevt_4_ta_ph = nullptr;
beq->bevt_5_ta_ph = nullptr;
beq->bevt_6_ta_ph = nullptr;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(9);
if (bevp_up->bevi_bool) {
beq->bevt_3_ta_ph = static_cast<BEC_2_4_7_TextStrings*>(BEC_2_4_7_TextStrings::bece_BEC_2_4_7_TextStrings_bevs_inst);
beq->bevt_2_ta_ph = beq->bevt_3_ta_ph->bem_notEmpty_1(bevp_mode);
if (beq->bevt_2_ta_ph->bevi_bool) {
beq->bevt_1_ta_anchor = BECS_Runtime::boolTrue;
} 
 else  {
beq->bevt_1_ta_anchor = BECS_Runtime::boolFalse;
} 
} 
 else  {
beq->bevt_1_ta_anchor = BECS_Runtime::boolFalse;
} 
if (beq->bevt_1_ta_anchor->bevi_bool) {
beq->bevt_5_ta_ph = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString(7, {0x73,0x74,0x61,0x74,0x69,0x6F,0x6E}))));
beq->bevt_4_ta_ph = bevp_mode->bem_equals_1(beq->bevt_5_ta_ph);
if (beq->bevt_4_ta_ph->bevi_bool) {
beq->bevt_0_ta_anchor = BECS_Runtime::boolTrue;
} 
 else  {
beq->bevt_0_ta_anchor = BECS_Runtime::boolFalse;
} 
} 
 else  {
beq->bevt_0_ta_anchor = BECS_Runtime::boolFalse;
} 
if (!(beq->bevt_0_ta_anchor->bevi_bool)) {
beq->bevt_6_ta_ph = static_cast<BEC_2_5_4_LogicBool*>(BECS_Runtime::boolFalse);
return beq->bevt_6_ta_ph;
} 

      if (WiFi.status() == WL_CONNECTED) {
        //Serial.println("wifi still connected");
        beq->bevl_connected = BECS_Runtime::boolTrue;
      } else {
        //Serial.println("wifi no more connected");
        beq->bevl_connected = BECS_Runtime::boolFalse;
      }
      return beq->bevl_connected;
}
BEC_2_8_4_EmbeddedWifi* BEC_2_8_4_EmbeddedWifi::bem_stop_0() {
struct bes {  BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(1);
bem_clear_0();

    WiFi.disconnect();
    return this;
}
BEC_2_4_6_TextString* BEC_2_8_4_EmbeddedWifi::bem_modeGet_0() {
struct bes {  BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(1);
return bevp_mode;
}
BEC_2_8_4_EmbeddedWifi* BEC_2_8_4_EmbeddedWifi::bem_modeSet_1(BEC_2_6_6_SystemObject* bevt_0_ta_SET) {
struct bes { BEC_2_6_6_SystemObject* bevt_0_ta_SET; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->bevt_0_ta_SET = bevt_0_ta_SET;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(2);
bevp_mode = static_cast<BEC_2_4_6_TextString*>(beq->bevt_0_ta_SET);
return this;
}
BEC_2_4_6_TextString* BEC_2_8_4_EmbeddedWifi::bem_ssidGet_0() {
struct bes {  BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(1);
return bevp_ssid;
}
BEC_2_8_4_EmbeddedWifi* BEC_2_8_4_EmbeddedWifi::bem_ssidSet_1(BEC_2_6_6_SystemObject* bevt_0_ta_SET) {
struct bes { BEC_2_6_6_SystemObject* bevt_0_ta_SET; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->bevt_0_ta_SET = bevt_0_ta_SET;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(2);
bevp_ssid = static_cast<BEC_2_4_6_TextString*>(beq->bevt_0_ta_SET);
return this;
}
BEC_2_4_6_TextString* BEC_2_8_4_EmbeddedWifi::bem_passwordGet_0() {
struct bes {  BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(1);
return bevp_password;
}
BEC_2_8_4_EmbeddedWifi* BEC_2_8_4_EmbeddedWifi::bem_passwordSet_1(BEC_2_6_6_SystemObject* bevt_0_ta_SET) {
struct bes { BEC_2_6_6_SystemObject* bevt_0_ta_SET; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->bevt_0_ta_SET = bevt_0_ta_SET;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(2);
bevp_password = static_cast<BEC_2_4_6_TextString*>(beq->bevt_0_ta_SET);
return this;
}
BEC_2_5_4_LogicBool* BEC_2_8_4_EmbeddedWifi::bem_upGet_0() {
struct bes {  BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(1);
return bevp_up;
}
BEC_2_8_4_EmbeddedWifi* BEC_2_8_4_EmbeddedWifi::bem_upSet_1(BEC_2_6_6_SystemObject* bevt_0_ta_SET) {
struct bes { BEC_2_6_6_SystemObject* bevt_0_ta_SET; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->bevt_0_ta_SET = bevt_0_ta_SET;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(2);
bevp_up = static_cast<BEC_2_5_4_LogicBool*>(beq->bevt_0_ta_SET);
return this;
}
BEC_2_4_6_TextString* BEC_2_8_4_EmbeddedWifi::bem_localIPGet_0() {
struct bes {  BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(1);
return bevp_localIP;
}
BEC_2_8_4_EmbeddedWifi* BEC_2_8_4_EmbeddedWifi::bem_localIPSet_1(BEC_2_6_6_SystemObject* bevt_0_ta_SET) {
struct bes { BEC_2_6_6_SystemObject* bevt_0_ta_SET; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->bevt_0_ta_SET = bevt_0_ta_SET;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(2);
bevp_localIP = static_cast<BEC_2_4_6_TextString*>(beq->bevt_0_ta_SET);
return this;
}
BEC_2_6_6_SystemObject* BEC_2_8_4_EmbeddedWifi::bemd_0(int32_t callId) {
switch (callId) {
case -416348137: return bem_ssidGet_0();
case -1354752537: return bem_isConnectedGet_0();
case 1844047077: return bem_passwordGet_0();
case 32406228: return bem_stop_0();
case 1803904661: return bem_modeGet_0();
case 1551129214: return bem_clear_0();
case 1188815194: return bem_default_0();
case 155495241: return bem_localIPGet_0();
case -1191767786: return bem_clearAll_0();
case 1075889334: return bem_upGet_0();
case 969648986: return bem_macAddressGet_0();
case 201078010: return bem_start_0();
case -236221381: return bem_startAp_0();
case 971828068: return bem_scanNetworks_0();
}
return bevs_super::bemd_0(callId);
}
BEC_2_6_6_SystemObject* BEC_2_8_4_EmbeddedWifi::bemd_1(int32_t callId, BEC_2_6_6_SystemObject* bevd_0) {
switch (callId) {
case 955155000: return bem_modeSet_1(bevd_0);
case -133432737: return bem_ssidSet_1(bevd_0);
case 2083404692: return bem_passwordSet_1(bevd_0);
case -1207948449: return bem_localIPSet_1(bevd_0);
case 1913261369: return bem_upSet_1(bevd_0);
}
return bevs_super::bemd_1(callId, bevd_0);
}
BEC_2_6_6_SystemObject* BEC_2_8_4_EmbeddedWifi::bemd_2(int32_t callId, BEC_2_6_6_SystemObject* bevd_0, BEC_2_6_6_SystemObject* bevd_1) {
switch (callId) {
case 878900077: return bem_new_2(static_cast<BEC_2_4_6_TextString*>(bevd_0), static_cast<BEC_2_4_6_TextString*>(bevd_1));
}
return bevs_super::bemd_2(callId, bevd_0, bevd_1);
}
BEC_2_6_6_SystemObject* BEC_2_8_4_EmbeddedWifi::bemc_create() {
return new BEC_2_8_4_EmbeddedWifi();
}
void BEC_2_8_4_EmbeddedWifi::bemc_setInitial(BEC_2_6_6_SystemObject* becc_inst) {
BEC_2_8_4_EmbeddedWifi::bece_BEC_2_8_4_EmbeddedWifi_bevs_inst = static_cast<BEC_2_8_4_EmbeddedWifi*>(becc_inst);
}
BEC_2_6_6_SystemObject* BEC_2_8_4_EmbeddedWifi::bemc_getInitial() {
return BEC_2_8_4_EmbeddedWifi::bece_BEC_2_8_4_EmbeddedWifi_bevs_inst;
}
void BEC_2_8_4_EmbeddedWifi::bemg_doMark() {
bevg_gcMark = BECS_Runtime::bevg_currentGcMark;
if (bevp_mode != nullptr && bevp_mode->bevg_gcMark != BECS_Runtime::bevg_currentGcMark) {
bevp_mode->bemg_doMark();
}
if (bevp_ssid != nullptr && bevp_ssid->bevg_gcMark != BECS_Runtime::bevg_currentGcMark) {
bevp_ssid->bemg_doMark();
}
if (bevp_password != nullptr && bevp_password->bevg_gcMark != BECS_Runtime::bevg_currentGcMark) {
bevp_password->bemg_doMark();
}
if (bevp_up != nullptr && bevp_up->bevg_gcMark != BECS_Runtime::bevg_currentGcMark) {
bevp_up->bemg_doMark();
}
if (bevp_localIP != nullptr && bevp_localIP->bevg_gcMark != BECS_Runtime::bevg_currentGcMark) {
bevp_localIP->bemg_doMark();
}
}
size_t BEC_2_8_4_EmbeddedWifi::bemg_getSize() {
return sizeof(*this);
}
BETS_Object* BEC_2_8_4_EmbeddedWifi::bemc_getType() {
return &BEC_2_8_4_EmbeddedWifi::bece_BEC_2_8_4_EmbeddedWifi_bevs_type;
}
BET_2_8_9_EmbeddedTCPServer::BET_2_8_9_EmbeddedTCPServer() {
std::vector<std::string> bevs_mtnames = {  };
bevs_fieldNames = {  };
}
BEC_2_6_6_SystemObject* BET_2_8_9_EmbeddedTCPServer::bems_createInstance() {
return new BEC_2_8_9_EmbeddedTCPServer();
}
void BET_2_8_9_EmbeddedTCPServer::bemgt_doMark() {
BEC_2_6_6_SystemObject* bevsl_inst_ref = *bevs_inst_ref;
if (bevsl_inst_ref != nullptr && bevsl_inst_ref->bevg_gcMark != BECS_Runtime::bevg_currentGcMark) {
bevsl_inst_ref->bemg_doMark();
}
}
BEC_2_8_9_EmbeddedTCPServer* BEC_2_8_9_EmbeddedTCPServer::bece_BEC_2_8_9_EmbeddedTCPServer_bevs_inst;

BET_2_8_9_EmbeddedTCPServer BEC_2_8_9_EmbeddedTCPServer::bece_BEC_2_8_9_EmbeddedTCPServer_bevs_type;
BEC_2_6_6_SystemObject** BET_2_8_9_EmbeddedTCPServer::bevs_inst_ref = (BEC_2_6_6_SystemObject**) &BEC_2_8_9_EmbeddedTCPServer::bece_BEC_2_8_9_EmbeddedTCPServer_bevs_inst;

BEC_2_8_9_EmbeddedTCPServer* BEC_2_8_9_EmbeddedTCPServer::bem_new_1(BEC_2_4_3_MathInt* bevk__port) {
struct bes { BEC_2_4_3_MathInt* beva__port; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->beva__port = bevk__port;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(2);
bevp_port = beq->beva__port;
return this;
}
BEC_2_8_9_EmbeddedTCPServer* BEC_2_8_9_EmbeddedTCPServer::bem_start_0() {
struct bes {  BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(1);

    server = std::make_unique<WiFiServer>(bevp_port->bevi_int);
    server->begin();
    return this;
}
BEC_2_8_9_EmbeddedTCPClient* BEC_2_8_9_EmbeddedTCPServer::bem_checkGetClient_0() {
struct bes { BEC_2_8_9_EmbeddedTCPClient* bevl_res; BEC_2_5_4_LogicBool* bevt_0_ta_ph; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->bevl_res = nullptr;
beq->bevt_0_ta_ph = nullptr;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(3);

    WiFiClient client = server->available();
    if (client) {
    beq->bevl_res = static_cast<BEC_2_8_9_EmbeddedTCPClient*>(((BEC_2_8_9_EmbeddedTCPClient*) (new BEC_2_8_9_EmbeddedTCPClient()))->bem_new_0());
beq->bevt_0_ta_ph = static_cast<BEC_2_5_4_LogicBool*>(BECS_Runtime::boolTrue);
beq->bevl_res->bem_openedSet_1(beq->bevt_0_ta_ph);

    beq->bevl_res->client = client;
    client.setTimeout(beq->bevl_res->bevp_streamTimeout->bevi_int);
    }
    return beq->bevl_res;
}
BEC_2_4_3_MathInt* BEC_2_8_9_EmbeddedTCPServer::bem_portGet_0() {
struct bes {  BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(1);
return bevp_port;
}
BEC_2_8_9_EmbeddedTCPServer* BEC_2_8_9_EmbeddedTCPServer::bem_portSet_1(BEC_2_6_6_SystemObject* bevt_0_ta_SET) {
struct bes { BEC_2_6_6_SystemObject* bevt_0_ta_SET; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->bevt_0_ta_SET = bevt_0_ta_SET;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(2);
bevp_port = static_cast<BEC_2_4_3_MathInt*>(beq->bevt_0_ta_SET);
return this;
}
BEC_2_6_6_SystemObject* BEC_2_8_9_EmbeddedTCPServer::bemd_0(int32_t callId) {
switch (callId) {
case 201078010: return bem_start_0();
case 1891751874: return bem_checkGetClient_0();
case -1205999815: return bem_portGet_0();
}
return bevs_super::bemd_0(callId);
}
BEC_2_6_6_SystemObject* BEC_2_8_9_EmbeddedTCPServer::bemd_1(int32_t callId, BEC_2_6_6_SystemObject* bevd_0) {
switch (callId) {
case -348641596: return bem_portSet_1(bevd_0);
case 1899676304: return bem_new_1(static_cast<BEC_2_4_3_MathInt*>(bevd_0));
}
return bevs_super::bemd_1(callId, bevd_0);
}
BEC_2_6_6_SystemObject* BEC_2_8_9_EmbeddedTCPServer::bemc_create() {
return new BEC_2_8_9_EmbeddedTCPServer();
}
void BEC_2_8_9_EmbeddedTCPServer::bemc_setInitial(BEC_2_6_6_SystemObject* becc_inst) {
BEC_2_8_9_EmbeddedTCPServer::bece_BEC_2_8_9_EmbeddedTCPServer_bevs_inst = static_cast<BEC_2_8_9_EmbeddedTCPServer*>(becc_inst);
}
BEC_2_6_6_SystemObject* BEC_2_8_9_EmbeddedTCPServer::bemc_getInitial() {
return BEC_2_8_9_EmbeddedTCPServer::bece_BEC_2_8_9_EmbeddedTCPServer_bevs_inst;
}
void BEC_2_8_9_EmbeddedTCPServer::bemg_doMark() {
bevg_gcMark = BECS_Runtime::bevg_currentGcMark;
if (bevp_port != nullptr && bevp_port->bevg_gcMark != BECS_Runtime::bevg_currentGcMark) {
bevp_port->bemg_doMark();
}
}
size_t BEC_2_8_9_EmbeddedTCPServer::bemg_getSize() {
return sizeof(*this);
}
BETS_Object* BEC_2_8_9_EmbeddedTCPServer::bemc_getType() {
return &BEC_2_8_9_EmbeddedTCPServer::bece_BEC_2_8_9_EmbeddedTCPServer_bevs_type;
}
BET_2_8_9_EmbeddedTCPClient::BET_2_8_9_EmbeddedTCPClient() {
std::vector<std::string> bevs_mtnames = {  };
bevs_fieldNames = {  };
}
BEC_2_6_6_SystemObject* BET_2_8_9_EmbeddedTCPClient::bems_createInstance() {
return new BEC_2_8_9_EmbeddedTCPClient();
}
void BET_2_8_9_EmbeddedTCPClient::bemgt_doMark() {
BEC_2_6_6_SystemObject* bevsl_inst_ref = *bevs_inst_ref;
if (bevsl_inst_ref != nullptr && bevsl_inst_ref->bevg_gcMark != BECS_Runtime::bevg_currentGcMark) {
bevsl_inst_ref->bemg_doMark();
}
}
BEC_2_8_9_EmbeddedTCPClient* BEC_2_8_9_EmbeddedTCPClient::bece_BEC_2_8_9_EmbeddedTCPClient_bevs_inst;

BET_2_8_9_EmbeddedTCPClient BEC_2_8_9_EmbeddedTCPClient::bece_BEC_2_8_9_EmbeddedTCPClient_bevs_type;
BEC_2_6_6_SystemObject** BET_2_8_9_EmbeddedTCPClient::bevs_inst_ref = (BEC_2_6_6_SystemObject**) &BEC_2_8_9_EmbeddedTCPClient::bece_BEC_2_8_9_EmbeddedTCPClient_bevs_inst;

BEC_2_6_6_SystemObject* BEC_2_8_9_EmbeddedTCPClient::bem_new_0() {
struct bes {  BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(1);
bevp_connectTimeout = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(200))));
bevp_streamTimeout = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(20))));
return this;
}
BEC_2_8_9_EmbeddedTCPClient* BEC_2_8_9_EmbeddedTCPClient::bem_new_2(BEC_2_4_6_TextString* bevk__host, BEC_2_4_3_MathInt* bevk__port) {
struct bes { BEC_2_4_6_TextString* beva__host; BEC_2_4_3_MathInt* beva__port; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->beva__host = bevk__host;
beq->beva__port = bevk__port;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(3);
bevp_host = beq->beva__host;
bevp_port = beq->beva__port;
bevp_opened = static_cast<BEC_2_5_4_LogicBool*>(BECS_Runtime::boolFalse);
bevp_connectTimeout = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(200))));
bevp_streamTimeout = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(20))));
return this;
}
BEC_2_8_9_EmbeddedTCPClient* BEC_2_8_9_EmbeddedTCPClient::bem_open_0() {
struct bes {  BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(1);

    //client.setTimeout, milliseconds, default 1000. works for con and stream
    client.setTimeout(bevp_connectTimeout->bevi_int);
    client.connect(bevp_host->bems_toCcString().c_str(), bevp_port->bevi_int);
    if (client.connected()) {
      client.setTimeout(bevp_streamTimeout->bevi_int);
    bevp_opened = static_cast<BEC_2_5_4_LogicBool*>(BECS_Runtime::boolTrue);

    } else {
      //Serial.println("connection failed");
    }
    return this;
}
BEC_2_8_9_EmbeddedTCPClient* BEC_2_8_9_EmbeddedTCPClient::bem_write_1(BEC_2_4_6_TextString* bevk_line) {
struct bes { BEC_2_4_6_TextString* beva_line; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->beva_line = bevk_line;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(2);

    client.write(beq->beva_line->bems_toCcString().c_str());
    return this;
}
BEC_2_4_6_TextString* BEC_2_8_9_EmbeddedTCPClient::bem_checkGetPayload_2(BEC_2_4_6_TextString* bevk_payload, BEC_2_4_6_TextString* bevk_endmark) {
struct bes { BEC_2_4_6_TextString* beva_payload; BEC_2_4_6_TextString* beva_endmark; BEC_2_4_3_MathInt* bevl_chari; BEC_2_4_6_TextString* bevl_chars; BEC_2_4_3_MathInt* bevl_zero; BEC_2_5_4_LogicBool* bevt_0_ta_anchor; BEC_2_5_4_LogicBool* bevt_1_ta_anchor; BEC_2_4_3_MathInt* bevt_2_ta_ph; BEC_2_4_3_MathInt* bevt_3_ta_ph; BEC_2_4_3_MathInt* bevt_4_ta_ph; BEC_2_4_3_MathInt* bevt_5_ta_ph; BEC_2_4_3_MathInt* bevt_6_ta_ph; BEC_2_5_4_LogicBool* bevt_7_ta_ph; BEC_2_5_4_LogicBool* bevt_8_ta_ph; BEC_2_4_3_MathInt* bevt_9_ta_ph; BEC_2_4_3_MathInt* bevt_10_ta_ph; BEC_2_4_6_TextString* bevt_11_ta_ph; BEC_2_5_4_LogicBool* bevt_12_ta_ph; BEC_2_5_4_LogicBool* bevt_13_ta_ph; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->beva_payload = bevk_payload;
beq->beva_endmark = bevk_endmark;
beq->bevl_chari = nullptr;
beq->bevl_chars = nullptr;
beq->bevl_zero = nullptr;
beq->bevt_0_ta_anchor = nullptr;
beq->bevt_1_ta_anchor = nullptr;
beq->bevt_2_ta_ph = nullptr;
beq->bevt_3_ta_ph = nullptr;
beq->bevt_4_ta_ph = nullptr;
beq->bevt_5_ta_ph = nullptr;
beq->bevt_6_ta_ph = nullptr;
beq->bevt_7_ta_ph = nullptr;
beq->bevt_8_ta_ph = nullptr;
beq->bevt_9_ta_ph = nullptr;
beq->bevt_10_ta_ph = nullptr;
beq->bevt_11_ta_ph = nullptr;
beq->bevt_12_ta_ph = nullptr;
beq->bevt_13_ta_ph = nullptr;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(20);

    unsigned long currentTime = millis();
    unsigned long previousTime = 0; 
    long timeoutTime = 2000;
    if (client) {
    beq->beva_payload->bem_clear_0();
beq->bevl_chari = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt())));
beq->bevt_2_ta_ph = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(1))));
beq->bevl_chars = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString()))->bem_new_1(beq->bevt_2_ta_ph));
beq->bevt_3_ta_ph = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(0))));
beq->bevt_4_ta_ph = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(32))));
beq->bevl_chars->bem_setCodeUnchecked_2(beq->bevt_3_ta_ph, beq->bevt_4_ta_ph);
beq->bevt_5_ta_ph = beq->bevl_chars->bem_sizeGet_0();
beq->bevt_6_ta_ph = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(1))));
beq->bevt_5_ta_ph->bevi_int = beq->bevt_6_ta_ph->bevi_int;
beq->bevl_zero = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(0))));
if (beq->beva_endmark == nullptr) {
beq->bevt_7_ta_ph = BECS_Runtime::boolFalse;
 } else { 
beq->bevt_7_ta_ph = BECS_Runtime::boolTrue;
}
if (beq->bevt_7_ta_ph->bevi_bool) {
beq->bevt_9_ta_ph = beq->beva_endmark->bem_sizeGet_0();
beq->bevt_10_ta_ph = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(1))));
if (beq->bevt_9_ta_ph->bevi_int > beq->bevt_10_ta_ph->bevi_int) {
beq->bevt_8_ta_ph = BECS_Runtime::boolTrue;
 } else { 
beq->bevt_8_ta_ph = BECS_Runtime::boolFalse;
}
if (beq->bevt_8_ta_ph->bevi_bool) {
beq->bevt_0_ta_anchor = BECS_Runtime::boolTrue;
} 
 else  {
beq->bevt_0_ta_anchor = BECS_Runtime::boolFalse;
} 
} 
 else  {
beq->bevt_0_ta_anchor = BECS_Runtime::boolFalse;
} 
if (beq->bevt_0_ta_anchor->bevi_bool) {
beq->bevt_11_ta_ph = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString(32, {0x6F,0x6E,0x6C,0x79,0x20,0x6F,0x6E,0x65,0x20,0x63,0x68,0x61,0x72,0x20,0x65,0x6E,0x64,0x6D,0x61,0x72,0x6B,0x73,0x20,0x73,0x75,0x70,0x70,0x6F,0x72,0x74,0x65,0x64}))));
beq->bevt_11_ta_ph->bem_print_0();
return beq->beva_payload;
} 
                          
      currentTime = millis();
      previousTime = currentTime;
      while (client.connected() && currentTime - previousTime <= timeoutTime) {
        previousTime = currentTime;
        currentTime = millis();
        if (client.available()) {
          char c = client.read(); 
          //Serial.write(c);
          beq->bevl_chari->bevi_int = c;
          beq->bevl_chars->bem_setCodeUnchecked_2(beq->bevl_zero, beq->bevl_chari);
beq->beva_payload->bem_addValue_1(beq->bevl_chars);
if (beq->beva_endmark == nullptr) {
beq->bevt_12_ta_ph = BECS_Runtime::boolFalse;
 } else { 
beq->bevt_12_ta_ph = BECS_Runtime::boolTrue;
}
if (beq->bevt_12_ta_ph->bevi_bool) {
beq->bevt_13_ta_ph = beq->bevl_chars->bem_equals_1(beq->beva_endmark);
if (beq->bevt_13_ta_ph->bevi_bool) {
beq->bevt_1_ta_anchor = BECS_Runtime::boolTrue;
} 
 else  {
beq->bevt_1_ta_anchor = BECS_Runtime::boolFalse;
} 
} 
 else  {
beq->bevt_1_ta_anchor = BECS_Runtime::boolFalse;
} 
if (beq->bevt_1_ta_anchor->bevi_bool) {
return beq->beva_payload;
} 
        
        } else {
          //Serial.println("not available");
        }
      }
    } else {
      //Serial.println("no client");
    }
    return beq->beva_payload;
}
BEC_2_5_4_LogicBool* BEC_2_8_9_EmbeddedTCPClient::bem_connectedGet_0() {
struct bes { BEC_2_5_4_LogicBool* bevt_0_ta_ph; BEC_2_5_4_LogicBool* bevt_1_ta_ph; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->bevt_0_ta_ph = nullptr;
beq->bevt_1_ta_ph = nullptr;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(3);

    if (client && client.connected()) {
     beq->bevt_0_ta_ph = static_cast<BEC_2_5_4_LogicBool*>(BECS_Runtime::boolTrue);
return beq->bevt_0_ta_ph;

     }
     beq->bevt_1_ta_ph = static_cast<BEC_2_5_4_LogicBool*>(BECS_Runtime::boolFalse);
return beq->bevt_1_ta_ph;
}
BEC_2_5_4_LogicBool* BEC_2_8_9_EmbeddedTCPClient::bem_availableGet_0() {
struct bes { BEC_2_5_4_LogicBool* bevt_0_ta_ph; BEC_2_5_4_LogicBool* bevt_1_ta_ph; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->bevt_0_ta_ph = nullptr;
beq->bevt_1_ta_ph = nullptr;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(3);

    if (client && client.connected() && client.available()) {
     beq->bevt_0_ta_ph = static_cast<BEC_2_5_4_LogicBool*>(BECS_Runtime::boolTrue);
return beq->bevt_0_ta_ph;

     }
     beq->bevt_1_ta_ph = static_cast<BEC_2_5_4_LogicBool*>(BECS_Runtime::boolFalse);
return beq->bevt_1_ta_ph;
}
BEC_2_4_6_TextString* BEC_2_8_9_EmbeddedTCPClient::bem_remoteIpGet_0() {
struct bes { BEC_2_4_6_TextString* bevl_ip; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->bevl_ip = nullptr;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(2);

      String lip = client.remoteIP().toString();
      std::string lips = std::string(lip.c_str());
      beq->bevl_ip = new BEC_2_4_6_TextString(lips);
      return beq->bevl_ip;
}
BEC_2_8_9_EmbeddedTCPClient* BEC_2_8_9_EmbeddedTCPClient::bem_close_0() {
struct bes {  BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(1);

    if (client) {  
      client.stop();
    }
    bevp_opened = static_cast<BEC_2_5_4_LogicBool*>(BECS_Runtime::boolFalse);
return this;
}
BEC_2_4_6_TextString* BEC_2_8_9_EmbeddedTCPClient::bem_hostGet_0() {
struct bes {  BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(1);
return bevp_host;
}
BEC_2_8_9_EmbeddedTCPClient* BEC_2_8_9_EmbeddedTCPClient::bem_hostSet_1(BEC_2_6_6_SystemObject* bevt_0_ta_SET) {
struct bes { BEC_2_6_6_SystemObject* bevt_0_ta_SET; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->bevt_0_ta_SET = bevt_0_ta_SET;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(2);
bevp_host = static_cast<BEC_2_4_6_TextString*>(beq->bevt_0_ta_SET);
return this;
}
BEC_2_4_3_MathInt* BEC_2_8_9_EmbeddedTCPClient::bem_portGet_0() {
struct bes {  BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(1);
return bevp_port;
}
BEC_2_8_9_EmbeddedTCPClient* BEC_2_8_9_EmbeddedTCPClient::bem_portSet_1(BEC_2_6_6_SystemObject* bevt_0_ta_SET) {
struct bes { BEC_2_6_6_SystemObject* bevt_0_ta_SET; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->bevt_0_ta_SET = bevt_0_ta_SET;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(2);
bevp_port = static_cast<BEC_2_4_3_MathInt*>(beq->bevt_0_ta_SET);
return this;
}
BEC_2_5_4_LogicBool* BEC_2_8_9_EmbeddedTCPClient::bem_openedGet_0() {
struct bes {  BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(1);
return bevp_opened;
}
BEC_2_8_9_EmbeddedTCPClient* BEC_2_8_9_EmbeddedTCPClient::bem_openedSet_1(BEC_2_6_6_SystemObject* bevt_0_ta_SET) {
struct bes { BEC_2_6_6_SystemObject* bevt_0_ta_SET; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->bevt_0_ta_SET = bevt_0_ta_SET;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(2);
bevp_opened = static_cast<BEC_2_5_4_LogicBool*>(beq->bevt_0_ta_SET);
return this;
}
BEC_2_4_3_MathInt* BEC_2_8_9_EmbeddedTCPClient::bem_connectTimeoutGet_0() {
struct bes {  BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(1);
return bevp_connectTimeout;
}
BEC_2_8_9_EmbeddedTCPClient* BEC_2_8_9_EmbeddedTCPClient::bem_connectTimeoutSet_1(BEC_2_6_6_SystemObject* bevt_0_ta_SET) {
struct bes { BEC_2_6_6_SystemObject* bevt_0_ta_SET; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->bevt_0_ta_SET = bevt_0_ta_SET;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(2);
bevp_connectTimeout = static_cast<BEC_2_4_3_MathInt*>(beq->bevt_0_ta_SET);
return this;
}
BEC_2_4_3_MathInt* BEC_2_8_9_EmbeddedTCPClient::bem_streamTimeoutGet_0() {
struct bes {  BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(1);
return bevp_streamTimeout;
}
BEC_2_8_9_EmbeddedTCPClient* BEC_2_8_9_EmbeddedTCPClient::bem_streamTimeoutSet_1(BEC_2_6_6_SystemObject* bevt_0_ta_SET) {
struct bes { BEC_2_6_6_SystemObject* bevt_0_ta_SET; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->bevt_0_ta_SET = bevt_0_ta_SET;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(2);
bevp_streamTimeout = static_cast<BEC_2_4_3_MathInt*>(beq->bevt_0_ta_SET);
return this;
}
BEC_2_6_6_SystemObject* BEC_2_8_9_EmbeddedTCPClient::bemd_0(int32_t callId) {
switch (callId) {
case -1933309898: return bem_hostGet_0();
case 1415525339: return bem_streamTimeoutGet_0();
case -1085545580: return bem_openedGet_0();
case -1205999815: return bem_portGet_0();
case 1030934124: return bem_open_0();
case -1546907271: return bem_close_0();
case -752421012: return bem_availableGet_0();
case -183529491: return bem_connectedGet_0();
case -1785532669: return bem_new_0();
case 625031139: return bem_remoteIpGet_0();
case 1961494473: return bem_connectTimeoutGet_0();
}
return bevs_super::bemd_0(callId);
}
BEC_2_6_6_SystemObject* BEC_2_8_9_EmbeddedTCPClient::bemd_1(int32_t callId, BEC_2_6_6_SystemObject* bevd_0) {
switch (callId) {
case -1303393487: return bem_connectTimeoutSet_1(bevd_0);
case 1129103463: return bem_write_1(static_cast<BEC_2_4_6_TextString*>(bevd_0));
case 2138985964: return bem_openedSet_1(bevd_0);
case -348641596: return bem_portSet_1(bevd_0);
case 189125515: return bem_hostSet_1(bevd_0);
case 261426681: return bem_streamTimeoutSet_1(bevd_0);
}
return bevs_super::bemd_1(callId, bevd_0);
}
BEC_2_6_6_SystemObject* BEC_2_8_9_EmbeddedTCPClient::bemd_2(int32_t callId, BEC_2_6_6_SystemObject* bevd_0, BEC_2_6_6_SystemObject* bevd_1) {
switch (callId) {
case 878900077: return bem_new_2(static_cast<BEC_2_4_6_TextString*>(bevd_0), static_cast<BEC_2_4_3_MathInt*>(bevd_1));
case 811447377: return bem_checkGetPayload_2(static_cast<BEC_2_4_6_TextString*>(bevd_0), static_cast<BEC_2_4_6_TextString*>(bevd_1));
}
return bevs_super::bemd_2(callId, bevd_0, bevd_1);
}
BEC_2_6_6_SystemObject* BEC_2_8_9_EmbeddedTCPClient::bemc_create() {
return new BEC_2_8_9_EmbeddedTCPClient();
}
void BEC_2_8_9_EmbeddedTCPClient::bemc_setInitial(BEC_2_6_6_SystemObject* becc_inst) {
BEC_2_8_9_EmbeddedTCPClient::bece_BEC_2_8_9_EmbeddedTCPClient_bevs_inst = static_cast<BEC_2_8_9_EmbeddedTCPClient*>(becc_inst);
}
BEC_2_6_6_SystemObject* BEC_2_8_9_EmbeddedTCPClient::bemc_getInitial() {
return BEC_2_8_9_EmbeddedTCPClient::bece_BEC_2_8_9_EmbeddedTCPClient_bevs_inst;
}
void BEC_2_8_9_EmbeddedTCPClient::bemg_doMark() {
bevg_gcMark = BECS_Runtime::bevg_currentGcMark;
if (bevp_host != nullptr && bevp_host->bevg_gcMark != BECS_Runtime::bevg_currentGcMark) {
bevp_host->bemg_doMark();
}
if (bevp_port != nullptr && bevp_port->bevg_gcMark != BECS_Runtime::bevg_currentGcMark) {
bevp_port->bemg_doMark();
}
if (bevp_opened != nullptr && bevp_opened->bevg_gcMark != BECS_Runtime::bevg_currentGcMark) {
bevp_opened->bemg_doMark();
}
if (bevp_connectTimeout != nullptr && bevp_connectTimeout->bevg_gcMark != BECS_Runtime::bevg_currentGcMark) {
bevp_connectTimeout->bemg_doMark();
}
if (bevp_streamTimeout != nullptr && bevp_streamTimeout->bevg_gcMark != BECS_Runtime::bevg_currentGcMark) {
bevp_streamTimeout->bemg_doMark();
}
}
size_t BEC_2_8_9_EmbeddedTCPClient::bemg_getSize() {
return sizeof(*this);
}
BETS_Object* BEC_2_8_9_EmbeddedTCPClient::bemc_getType() {
return &BEC_2_8_9_EmbeddedTCPClient::bece_BEC_2_8_9_EmbeddedTCPClient_bevs_type;
}
BET_2_8_4_EmbeddedMdns::BET_2_8_4_EmbeddedMdns() {
std::vector<std::string> bevs_mtnames = {  };
bevs_fieldNames = {  };
}
BEC_2_6_6_SystemObject* BET_2_8_4_EmbeddedMdns::bems_createInstance() {
return new BEC_2_8_4_EmbeddedMdns();
}
void BET_2_8_4_EmbeddedMdns::bemgt_doMark() {
BEC_2_6_6_SystemObject* bevsl_inst_ref = *bevs_inst_ref;
if (bevsl_inst_ref != nullptr && bevsl_inst_ref->bevg_gcMark != BECS_Runtime::bevg_currentGcMark) {
bevsl_inst_ref->bemg_doMark();
}
}
BEC_2_8_4_EmbeddedMdns* BEC_2_8_4_EmbeddedMdns::bece_BEC_2_8_4_EmbeddedMdns_bevs_inst;

BET_2_8_4_EmbeddedMdns BEC_2_8_4_EmbeddedMdns::bece_BEC_2_8_4_EmbeddedMdns_bevs_type;
BEC_2_6_6_SystemObject** BET_2_8_4_EmbeddedMdns::bevs_inst_ref = (BEC_2_6_6_SystemObject**) &BEC_2_8_4_EmbeddedMdns::bece_BEC_2_8_4_EmbeddedMdns_bevs_inst;

BEC_2_6_6_SystemObject* BEC_2_8_4_EmbeddedMdns::bem_new_0() {
struct bes {  BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(1);
return this;
}
BEC_2_8_4_EmbeddedMdns* BEC_2_8_4_EmbeddedMdns::bem_start_0() {
struct bes { BEC_2_5_4_LogicBool* bevt_0_ta_anchor; BEC_2_5_4_LogicBool* bevt_1_ta_anchor; BEC_2_5_4_LogicBool* bevt_2_ta_ph; BEC_2_4_7_TextStrings* bevt_3_ta_ph; BEC_2_4_6_TextString* bevt_4_ta_ph; BEC_2_5_4_LogicBool* bevt_5_ta_ph; BEC_2_5_4_LogicBool* bevt_6_ta_ph; BEC_2_4_7_TextStrings* bevt_7_ta_ph; BEC_2_5_4_LogicBool* bevt_8_ta_ph; BEC_2_4_7_TextStrings* bevt_9_ta_ph; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->bevt_0_ta_anchor = nullptr;
beq->bevt_1_ta_anchor = nullptr;
beq->bevt_2_ta_ph = nullptr;
beq->bevt_3_ta_ph = nullptr;
beq->bevt_4_ta_ph = nullptr;
beq->bevt_5_ta_ph = nullptr;
beq->bevt_6_ta_ph = nullptr;
beq->bevt_7_ta_ph = nullptr;
beq->bevt_8_ta_ph = nullptr;
beq->bevt_9_ta_ph = nullptr;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(11);
beq->bevt_3_ta_ph = static_cast<BEC_2_4_7_TextStrings*>(BEC_2_4_7_TextStrings::bece_BEC_2_4_7_TextStrings_bevs_inst);
beq->bevt_2_ta_ph = beq->bevt_3_ta_ph->bem_isEmpty_1(bevp_name);
if (beq->bevt_2_ta_ph->bevi_bool) {
beq->bevt_4_ta_ph = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString(17, {0x6D,0x64,0x6E,0x73,0x20,0x6E,0x65,0x65,0x64,0x73,0x20,0x61,0x20,0x6E,0x61,0x6D,0x65}))));
beq->bevt_4_ta_ph->bem_print_0();
return this;
} 

    int tries = 100;
    if (!MDNS.begin(bevp_name->bems_toCcString().c_str())) {
      Serial.println("Error setting up MDNS responder!");
      while (tries-- > 0) { delay(1000); }
    }
    Serial.println("mDNS responder started");
    if (bevp_port == nullptr) {
beq->bevt_5_ta_ph = BECS_Runtime::boolFalse;
 } else { 
beq->bevt_5_ta_ph = BECS_Runtime::boolTrue;
}
if (beq->bevt_5_ta_ph->bevi_bool) {
beq->bevt_7_ta_ph = static_cast<BEC_2_4_7_TextStrings*>(BEC_2_4_7_TextStrings::bece_BEC_2_4_7_TextStrings_bevs_inst);
beq->bevt_6_ta_ph = beq->bevt_7_ta_ph->bem_notEmpty_1(bevp_service);
if (beq->bevt_6_ta_ph->bevi_bool) {
beq->bevt_1_ta_anchor = BECS_Runtime::boolTrue;
} 
 else  {
beq->bevt_1_ta_anchor = BECS_Runtime::boolFalse;
} 
} 
 else  {
beq->bevt_1_ta_anchor = BECS_Runtime::boolFalse;
} 
if (beq->bevt_1_ta_anchor->bevi_bool) {
beq->bevt_9_ta_ph = static_cast<BEC_2_4_7_TextStrings*>(BEC_2_4_7_TextStrings::bece_BEC_2_4_7_TextStrings_bevs_inst);
beq->bevt_8_ta_ph = beq->bevt_9_ta_ph->bem_notEmpty_1(bevp_protocol);
if (beq->bevt_8_ta_ph->bevi_bool) {
beq->bevt_0_ta_anchor = BECS_Runtime::boolTrue;
} 
 else  {
beq->bevt_0_ta_anchor = BECS_Runtime::boolFalse;
} 
} 
 else  {
beq->bevt_0_ta_anchor = BECS_Runtime::boolFalse;
} 
if (beq->bevt_0_ta_anchor->bevi_bool) {

        MDNS.addService(bevp_service->bems_toCcString().c_str(), bevp_protocol->bems_toCcString().c_str(), bevp_port->bevi_int);
        Serial.println("mDNS service added");
        } 
return this;
}
BEC_2_8_4_EmbeddedMdns* BEC_2_8_4_EmbeddedMdns::bem_update_0() {
struct bes {  BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(1);

  MDNS.update();
  return this;
}
BEC_2_4_6_TextString* BEC_2_8_4_EmbeddedMdns::bem_nameGet_0() {
struct bes {  BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(1);
return bevp_name;
}
BEC_2_8_4_EmbeddedMdns* BEC_2_8_4_EmbeddedMdns::bem_nameSet_1(BEC_2_6_6_SystemObject* bevt_0_ta_SET) {
struct bes { BEC_2_6_6_SystemObject* bevt_0_ta_SET; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->bevt_0_ta_SET = bevt_0_ta_SET;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(2);
bevp_name = static_cast<BEC_2_4_6_TextString*>(beq->bevt_0_ta_SET);
return this;
}
BEC_2_4_6_TextString* BEC_2_8_4_EmbeddedMdns::bem_serviceGet_0() {
struct bes {  BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(1);
return bevp_service;
}
BEC_2_8_4_EmbeddedMdns* BEC_2_8_4_EmbeddedMdns::bem_serviceSet_1(BEC_2_6_6_SystemObject* bevt_0_ta_SET) {
struct bes { BEC_2_6_6_SystemObject* bevt_0_ta_SET; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->bevt_0_ta_SET = bevt_0_ta_SET;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(2);
bevp_service = static_cast<BEC_2_4_6_TextString*>(beq->bevt_0_ta_SET);
return this;
}
BEC_2_4_3_MathInt* BEC_2_8_4_EmbeddedMdns::bem_portGet_0() {
struct bes {  BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(1);
return bevp_port;
}
BEC_2_8_4_EmbeddedMdns* BEC_2_8_4_EmbeddedMdns::bem_portSet_1(BEC_2_6_6_SystemObject* bevt_0_ta_SET) {
struct bes { BEC_2_6_6_SystemObject* bevt_0_ta_SET; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->bevt_0_ta_SET = bevt_0_ta_SET;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(2);
bevp_port = static_cast<BEC_2_4_3_MathInt*>(beq->bevt_0_ta_SET);
return this;
}
BEC_2_4_6_TextString* BEC_2_8_4_EmbeddedMdns::bem_protocolGet_0() {
struct bes {  BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(1);
return bevp_protocol;
}
BEC_2_8_4_EmbeddedMdns* BEC_2_8_4_EmbeddedMdns::bem_protocolSet_1(BEC_2_6_6_SystemObject* bevt_0_ta_SET) {
struct bes { BEC_2_6_6_SystemObject* bevt_0_ta_SET; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->bevt_0_ta_SET = bevt_0_ta_SET;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(2);
bevp_protocol = static_cast<BEC_2_4_6_TextString*>(beq->bevt_0_ta_SET);
return this;
}
BEC_2_6_6_SystemObject* BEC_2_8_4_EmbeddedMdns::bemd_0(int32_t callId) {
switch (callId) {
case 201078010: return bem_start_0();
case -1486856859: return bem_update_0();
case 1359649681: return bem_nameGet_0();
case -1365977279: return bem_serviceGet_0();
case -1785532669: return bem_new_0();
case -1205999815: return bem_portGet_0();
case 1101001592: return bem_protocolGet_0();
}
return bevs_super::bemd_0(callId);
}
BEC_2_6_6_SystemObject* BEC_2_8_4_EmbeddedMdns::bemd_1(int32_t callId, BEC_2_6_6_SystemObject* bevd_0) {
switch (callId) {
case 761252723: return bem_serviceSet_1(bevd_0);
case -348641596: return bem_portSet_1(bevd_0);
case -1564323957: return bem_protocolSet_1(bevd_0);
case 787751337: return bem_nameSet_1(bevd_0);
}
return bevs_super::bemd_1(callId, bevd_0);
}
BEC_2_6_6_SystemObject* BEC_2_8_4_EmbeddedMdns::bemc_create() {
return new BEC_2_8_4_EmbeddedMdns();
}
void BEC_2_8_4_EmbeddedMdns::bemc_setInitial(BEC_2_6_6_SystemObject* becc_inst) {
BEC_2_8_4_EmbeddedMdns::bece_BEC_2_8_4_EmbeddedMdns_bevs_inst = static_cast<BEC_2_8_4_EmbeddedMdns*>(becc_inst);
}
BEC_2_6_6_SystemObject* BEC_2_8_4_EmbeddedMdns::bemc_getInitial() {
return BEC_2_8_4_EmbeddedMdns::bece_BEC_2_8_4_EmbeddedMdns_bevs_inst;
}
void BEC_2_8_4_EmbeddedMdns::bemg_doMark() {
bevg_gcMark = BECS_Runtime::bevg_currentGcMark;
if (bevp_name != nullptr && bevp_name->bevg_gcMark != BECS_Runtime::bevg_currentGcMark) {
bevp_name->bemg_doMark();
}
if (bevp_service != nullptr && bevp_service->bevg_gcMark != BECS_Runtime::bevg_currentGcMark) {
bevp_service->bemg_doMark();
}
if (bevp_port != nullptr && bevp_port->bevg_gcMark != BECS_Runtime::bevg_currentGcMark) {
bevp_port->bemg_doMark();
}
if (bevp_protocol != nullptr && bevp_protocol->bevg_gcMark != BECS_Runtime::bevg_currentGcMark) {
bevp_protocol->bemg_doMark();
}
}
size_t BEC_2_8_4_EmbeddedMdns::bemg_getSize() {
return sizeof(*this);
}
BETS_Object* BEC_2_8_4_EmbeddedMdns::bemc_getType() {
return &BEC_2_8_4_EmbeddedMdns::bece_BEC_2_8_4_EmbeddedMdns_bevs_type;
}
BET_2_8_4_EmbeddedMqtt::BET_2_8_4_EmbeddedMqtt() {
std::vector<std::string> bevs_mtnames = {  };
bevs_fieldNames = {  };
}
BEC_2_6_6_SystemObject* BET_2_8_4_EmbeddedMqtt::bems_createInstance() {
return new BEC_2_8_4_EmbeddedMqtt();
}
void BET_2_8_4_EmbeddedMqtt::bemgt_doMark() {
BEC_2_6_6_SystemObject* bevsl_inst_ref = *bevs_inst_ref;
if (bevsl_inst_ref != nullptr && bevsl_inst_ref->bevg_gcMark != BECS_Runtime::bevg_currentGcMark) {
bevsl_inst_ref->bemg_doMark();
}
}

std::string BEC_2_8_4_EmbeddedMqtt::gotTopic;
std::string BEC_2_8_4_EmbeddedMqtt::gotPayload;

void messageReceived(String &topic, String &payload) {
  //Serial.println("incoming: " + topic + " - " + payload);

  // Note: Do not use the client in the callback to publish, subscribe or
  // unsubscribe as it may cause deadlocks when other things arrive while
  // sending and receiving acknowledgments. Instead, change a global variable,
  // or push to a queue and handle it in the loop after calling `client.loop()`.

  //std::string lips = std::string(lip.c_str());
  BEC_2_8_4_EmbeddedMqtt::gotTopic = std::string(topic.c_str());
  BEC_2_8_4_EmbeddedMqtt::gotPayload = std::string(payload.c_str());
}
 BEC_2_8_4_EmbeddedMqtt* BEC_2_8_4_EmbeddedMqtt::bece_BEC_2_8_4_EmbeddedMqtt_bevs_inst;

BET_2_8_4_EmbeddedMqtt BEC_2_8_4_EmbeddedMqtt::bece_BEC_2_8_4_EmbeddedMqtt_bevs_type;
BEC_2_6_6_SystemObject** BET_2_8_4_EmbeddedMqtt::bevs_inst_ref = (BEC_2_6_6_SystemObject**) &BEC_2_8_4_EmbeddedMqtt::bece_BEC_2_8_4_EmbeddedMqtt_bevs_inst;

BEC_2_6_6_SystemObject* BEC_2_8_4_EmbeddedMqtt::bem_new_0() {
struct bes { BEC_2_6_6_SystemRandom* bevt_0_ta_ph; BEC_2_4_3_MathInt* bevt_1_ta_ph; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->bevt_0_ta_ph = nullptr;
beq->bevt_1_ta_ph = nullptr;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(3);
bevp_mqttPort = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(1883))));
beq->bevt_0_ta_ph = static_cast<BEC_2_6_6_SystemRandom*>(BEC_2_6_6_SystemRandom::bece_BEC_2_6_6_SystemRandom_bevs_inst);
beq->bevt_1_ta_ph = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(16))));
bevp_id = beq->bevt_0_ta_ph->bem_getString_1(beq->bevt_1_ta_ph);
bevp_mqsubl = static_cast<BEC_2_9_4_ContainerList*>(((BEC_2_9_4_ContainerList*) (new BEC_2_9_4_ContainerList()))->bem_new_0());
bevp_mqpubl = static_cast<BEC_2_9_4_ContainerList*>(((BEC_2_9_4_ContainerList*) (new BEC_2_9_4_ContainerList()))->bem_new_0());
bevp_mqpublmax = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(8))));
bevp_mqrcl = static_cast<BEC_2_9_4_ContainerList*>(((BEC_2_9_4_ContainerList*) (new BEC_2_9_4_ContainerList()))->bem_new_0());
bevp_mqrcmax = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(8))));
bevp_zero = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(0))));

      client = std::make_unique<MQTTClient>(384);
      return this;
}
BEC_2_8_4_EmbeddedMqtt* BEC_2_8_4_EmbeddedMqtt::bem_new_3(BEC_2_4_6_TextString* bevk__mqttServer, BEC_2_4_6_TextString* bevk__user, BEC_2_4_6_TextString* bevk__pass) {
struct bes { BEC_2_4_6_TextString* beva__mqttServer; BEC_2_4_6_TextString* beva__user; BEC_2_4_6_TextString* beva__pass; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->beva__mqttServer = bevk__mqttServer;
beq->beva__user = bevk__user;
beq->beva__pass = bevk__pass;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(4);
bevp_mqttServer = beq->beva__mqttServer;
bevp_user = beq->beva__user;
bevp_pass = beq->beva__pass;
bem_new_0();
return this;
}
BEC_2_8_4_EmbeddedMqtt* BEC_2_8_4_EmbeddedMqtt::bem_minAsyncCapacitySet_1(BEC_2_4_3_MathInt* bevk_size) {
struct bes { BEC_2_4_3_MathInt* beva_size; BEC_2_5_4_LogicBool* bevt_0_ta_ph; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->beva_size = bevk_size;
beq->bevt_0_ta_ph = nullptr;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(3);
if (bevp_mqpublmax->bevi_int < beq->beva_size->bevi_int) {
beq->bevt_0_ta_ph = BECS_Runtime::boolTrue;
 } else { 
beq->bevt_0_ta_ph = BECS_Runtime::boolFalse;
}
if (beq->bevt_0_ta_ph->bevi_bool) {
bevp_mqpublmax->bevi_int = beq->beva_size->bevi_int;
} 
return this;
}
BEC_2_5_4_LogicBool* BEC_2_8_4_EmbeddedMqtt::bem_hasAsyncCapacity_1(BEC_2_4_3_MathInt* bevk_amount) {
struct bes { BEC_2_4_3_MathInt* beva_amount; BEC_2_5_4_LogicBool* bevt_0_ta_anchor; BEC_2_5_4_LogicBool* bevt_1_ta_ph; BEC_2_4_3_MathInt* bevt_2_ta_ph; BEC_2_5_4_LogicBool* bevt_3_ta_ph; BEC_2_4_3_MathInt* bevt_4_ta_ph; BEC_2_4_3_MathInt* bevt_5_ta_ph; BEC_2_5_4_LogicBool* bevt_6_ta_ph; BEC_2_5_4_LogicBool* bevt_7_ta_ph; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->beva_amount = bevk_amount;
beq->bevt_0_ta_anchor = nullptr;
beq->bevt_1_ta_ph = nullptr;
beq->bevt_2_ta_ph = nullptr;
beq->bevt_3_ta_ph = nullptr;
beq->bevt_4_ta_ph = nullptr;
beq->bevt_5_ta_ph = nullptr;
beq->bevt_6_ta_ph = nullptr;
beq->bevt_7_ta_ph = nullptr;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(10);
beq->bevt_2_ta_ph = bevp_mqpubl->bem_sizeGet_0();
if (bevp_mqpublmax->bevi_int >= beq->bevt_2_ta_ph->bevi_int) {
beq->bevt_1_ta_ph = BECS_Runtime::boolTrue;
 } else { 
beq->bevt_1_ta_ph = BECS_Runtime::boolFalse;
}
if (beq->bevt_1_ta_ph->bevi_bool) {
beq->bevt_5_ta_ph = bevp_mqpubl->bem_sizeGet_0();
beq->bevt_4_ta_ph = bevp_mqpublmax->bem_subtract_1(beq->bevt_5_ta_ph);
if (beq->bevt_4_ta_ph->bevi_int >= beq->beva_amount->bevi_int) {
beq->bevt_3_ta_ph = BECS_Runtime::boolTrue;
 } else { 
beq->bevt_3_ta_ph = BECS_Runtime::boolFalse;
}
if (beq->bevt_3_ta_ph->bevi_bool) {
beq->bevt_0_ta_anchor = BECS_Runtime::boolTrue;
} 
 else  {
beq->bevt_0_ta_anchor = BECS_Runtime::boolFalse;
} 
} 
 else  {
beq->bevt_0_ta_anchor = BECS_Runtime::boolFalse;
} 
if (beq->bevt_0_ta_anchor->bevi_bool) {
beq->bevt_6_ta_ph = static_cast<BEC_2_5_4_LogicBool*>(BECS_Runtime::boolTrue);
return beq->bevt_6_ta_ph;
} 
beq->bevt_7_ta_ph = static_cast<BEC_2_5_4_LogicBool*>(BECS_Runtime::boolFalse);
return beq->bevt_7_ta_ph;
}
BEC_2_5_4_LogicBool* BEC_2_8_4_EmbeddedMqtt::bem_publishAsync_2(BEC_2_4_6_TextString* bevk_pt, BEC_2_4_6_TextString* bevk_cf) {
struct bes { BEC_2_4_6_TextString* beva_pt; BEC_2_4_6_TextString* beva_cf; BEC_2_5_4_LogicBool* bevt_0_ta_ph; BEC_2_8_11_EmbeddedMqttMessage* bevt_1_ta_ph; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->beva_pt = bevk_pt;
beq->beva_cf = bevk_cf;
beq->bevt_0_ta_ph = nullptr;
beq->bevt_1_ta_ph = nullptr;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(5);
beq->bevt_1_ta_ph = static_cast<BEC_2_8_11_EmbeddedMqttMessage*>(((BEC_2_8_11_EmbeddedMqttMessage*) (new BEC_2_8_11_EmbeddedMqttMessage()))->bem_new_2(beq->beva_pt, beq->beva_cf));
beq->bevt_0_ta_ph = bem_publishAsync_1(beq->bevt_1_ta_ph);
return beq->bevt_0_ta_ph;
}
BEC_2_5_4_LogicBool* BEC_2_8_4_EmbeddedMqtt::bem_publishAsync_1(BEC_2_8_11_EmbeddedMqttMessage* bevk_msg) {
struct bes { BEC_2_8_11_EmbeddedMqttMessage* beva_msg; BEC_2_5_4_LogicBool* bevt_0_ta_ph; BEC_2_4_3_MathInt* bevt_1_ta_ph; BEC_2_5_4_LogicBool* bevt_2_ta_ph; BEC_2_5_4_LogicBool* bevt_3_ta_ph; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->beva_msg = bevk_msg;
beq->bevt_0_ta_ph = nullptr;
beq->bevt_1_ta_ph = nullptr;
beq->bevt_2_ta_ph = nullptr;
beq->bevt_3_ta_ph = nullptr;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(6);
beq->bevt_1_ta_ph = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(1))));
beq->bevt_0_ta_ph = bem_hasAsyncCapacity_1(beq->bevt_1_ta_ph);
if (beq->bevt_0_ta_ph->bevi_bool) {
bevp_mqpubl->bem_addValue_1(beq->beva_msg);
beq->bevt_2_ta_ph = static_cast<BEC_2_5_4_LogicBool*>(BECS_Runtime::boolTrue);
return beq->bevt_2_ta_ph;
} 
beq->bevt_3_ta_ph = static_cast<BEC_2_5_4_LogicBool*>(BECS_Runtime::boolFalse);
return beq->bevt_3_ta_ph;
}
BEC_2_5_4_LogicBool* BEC_2_8_4_EmbeddedMqtt::bem_subscribeAsync_1(BEC_2_4_6_TextString* bevk_topic) {
struct bes { BEC_2_4_6_TextString* beva_topic; BEC_2_5_4_LogicBool* bevt_0_ta_ph; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->beva_topic = bevk_topic;
beq->bevt_0_ta_ph = nullptr;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(3);
bevp_mqsubl->bem_addValue_1(beq->beva_topic);
beq->bevt_0_ta_ph = static_cast<BEC_2_5_4_LogicBool*>(BECS_Runtime::boolTrue);
return beq->bevt_0_ta_ph;
}
BEC_2_5_4_LogicBool* BEC_2_8_4_EmbeddedMqtt::bem_isOpenGet_0() {
struct bes { BEC_2_5_4_LogicBool* bevl_ret; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->bevl_ret = nullptr;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(2);

      if (client->connected()) {
        beq->bevl_ret = BECS_Runtime::boolTrue;
      } else {
        beq->bevl_ret = BECS_Runtime::boolFalse;
      }
        return beq->bevl_ret;
}
BEC_2_5_4_LogicBool* BEC_2_8_4_EmbeddedMqtt::bem_close_0() {
struct bes { BEC_2_5_4_LogicBool* bevl_ret; BEC_2_4_6_TextString* bevt_0_ta_ph; BEC_2_4_6_TextString* bevt_1_ta_ph; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->bevl_ret = nullptr;
beq->bevt_0_ta_ph = nullptr;
beq->bevt_1_ta_ph = nullptr;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(4);

      if (client->connected()) {
        if (client->disconnect()) {
          beq->bevl_ret = BECS_Runtime::boolTrue;
        } else {
          beq->bevl_ret = BECS_Runtime::boolFalse;
        }
      } else {
        beq->bevl_ret = BECS_Runtime::boolFalse;
      }
      if (beq->bevl_ret->bevi_bool) {
beq->bevt_0_ta_ph = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString(20, {0x6D,0x71,0x74,0x74,0x20,0x63,0x6C,0x6F,0x73,0x65,0x20,0x73,0x75,0x63,0x63,0x65,0x65,0x64,0x65,0x64}))));
beq->bevt_0_ta_ph->bem_print_0();
} 
 else  {
beq->bevt_1_ta_ph = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString(17, {0x6D,0x71,0x74,0x74,0x20,0x63,0x6C,0x6F,0x73,0x65,0x20,0x66,0x61,0x69,0x6C,0x65,0x64}))));
beq->bevt_1_ta_ph->bem_print_0();
} 
return beq->bevl_ret;
}
BEC_2_5_4_LogicBool* BEC_2_8_4_EmbeddedMqtt::bem_open_0() {
struct bes { BEC_2_5_4_LogicBool* bevl_ret; BEC_2_4_6_TextString* bevt_0_ta_ph; BEC_2_4_6_TextString* bevt_1_ta_ph; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->bevl_ret = nullptr;
beq->bevt_0_ta_ph = nullptr;
beq->bevt_1_ta_ph = nullptr;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(4);

      client->begin(bevp_mqttServer->bems_toCcString().c_str(), bevp_mqttPort->bevi_int, net);
      client->onMessage(messageReceived);
      if (client->connect(bevp_id->bems_toCcString().c_str(), bevp_user->bems_toCcString().c_str(), bevp_pass->bems_toCcString().c_str())) {
          beq->bevl_ret = BECS_Runtime::boolTrue;
        } else {
          beq->bevl_ret = BECS_Runtime::boolFalse;
        }
      if (beq->bevl_ret->bevi_bool) {
beq->bevt_0_ta_ph = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString(11, {0x6D,0x71,0x74,0x74,0x20,0x6F,0x70,0x65,0x6E,0x65,0x64}))));
beq->bevt_0_ta_ph->bem_print_0();
} 
 else  {
beq->bevt_1_ta_ph = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString(16, {0x6D,0x71,0x74,0x74,0x20,0x6F,0x70,0x65,0x6E,0x20,0x66,0x61,0x69,0x6C,0x65,0x64}))));
beq->bevt_1_ta_ph->bem_print_0();
} 
return beq->bevl_ret;
}
BEC_2_5_4_LogicBool* BEC_2_8_4_EmbeddedMqtt::bem_publish_2(BEC_2_4_6_TextString* bevk_topic, BEC_2_4_6_TextString* bevk_payload) {
struct bes { BEC_2_4_6_TextString* beva_topic; BEC_2_4_6_TextString* beva_payload; BEC_2_5_4_LogicBool* bevl_ret; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->beva_topic = bevk_topic;
beq->beva_payload = bevk_payload;
beq->bevl_ret = nullptr;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(4);

      if (client->publish(beq->beva_topic->bems_toCcString().c_str(), beq->beva_payload->bems_toCcString().c_str())) {
          beq->bevl_ret = BECS_Runtime::boolTrue;
        } else {
          beq->bevl_ret = BECS_Runtime::boolFalse;
        }
      return beq->bevl_ret;
}
BEC_2_5_4_LogicBool* BEC_2_8_4_EmbeddedMqtt::bem_publish_1(BEC_2_8_11_EmbeddedMqttMessage* bevk_msg) {
struct bes { BEC_2_8_11_EmbeddedMqttMessage* beva_msg; BEC_2_5_4_LogicBool* bevt_0_ta_ph; BEC_2_4_6_TextString* bevt_1_ta_ph; BEC_2_4_6_TextString* bevt_2_ta_ph; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->beva_msg = bevk_msg;
beq->bevt_0_ta_ph = nullptr;
beq->bevt_1_ta_ph = nullptr;
beq->bevt_2_ta_ph = nullptr;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(5);
beq->bevt_1_ta_ph = beq->beva_msg->bem_topicGet_0();
beq->bevt_2_ta_ph = beq->beva_msg->bem_payloadGet_0();
beq->bevt_0_ta_ph = bem_publish_2(beq->bevt_1_ta_ph, beq->bevt_2_ta_ph);
return beq->bevt_0_ta_ph;
}
BEC_2_5_4_LogicBool* BEC_2_8_4_EmbeddedMqtt::bem_handleAsync_1(BEC_2_6_6_SystemObject* bevk_mqttHandler) {
struct bes { BEC_2_6_6_SystemObject* beva_mqttHandler; BEC_2_4_6_TextString* bevl_gott; BEC_2_4_6_TextString* bevl_gotp; BEC_2_4_6_TextString* bevl_tosub; BEC_2_8_11_EmbeddedMqttMessage* bevl_m; BEC_2_5_4_LogicBool* bevt_0_ta_anchor; BEC_2_5_4_LogicBool* bevt_1_ta_ph; BEC_2_5_4_LogicBool* bevt_2_ta_ph; BEC_2_4_7_TextStrings* bevt_3_ta_ph; BEC_2_5_4_LogicBool* bevt_4_ta_ph; BEC_2_4_7_TextStrings* bevt_5_ta_ph; BEC_2_5_4_LogicBool* bevt_6_ta_ph; BEC_2_4_3_MathInt* bevt_7_ta_ph; BEC_2_8_11_EmbeddedMqttMessage* bevt_8_ta_ph; BEC_2_4_6_TextString* bevt_9_ta_ph; BEC_2_5_4_LogicBool* bevt_10_ta_ph; BEC_2_5_4_LogicBool* bevt_11_ta_ph; BEC_2_5_4_LogicBool* bevt_12_ta_ph; BEC_2_5_4_LogicBool* bevt_13_ta_ph; BEC_2_5_4_LogicBool* bevt_14_ta_ph; BEC_2_5_4_LogicBool* bevt_15_ta_ph; BEC_2_4_3_MathInt* bevt_16_ta_ph; BEC_2_5_4_LogicBool* bevt_17_ta_ph; BEC_2_5_4_LogicBool* bevt_18_ta_ph; BEC_2_4_6_TextString* bevt_19_ta_ph; BEC_2_4_6_TextString* bevt_20_ta_ph; BEC_2_5_4_LogicBool* bevt_21_ta_ph; BEC_2_5_4_LogicBool* bevt_22_ta_ph; BEC_2_5_4_LogicBool* bevt_23_ta_ph; BEC_2_5_4_LogicBool* bevt_24_ta_ph; BEC_2_5_4_LogicBool* bevt_25_ta_ph; BEC_2_5_4_LogicBool* bevt_26_ta_ph; BEC_2_4_3_MathInt* bevt_27_ta_ph; BEC_2_5_4_LogicBool* bevt_28_ta_ph; BEC_2_5_4_LogicBool* bevt_29_ta_ph; BEC_2_5_4_LogicBool* bevt_30_ta_ph; BEC_2_5_4_LogicBool* bevt_31_ta_ph; BEC_2_5_4_LogicBool* bevt_32_ta_ph; BEC_2_5_4_LogicBool* bevt_33_ta_ph; BEC_2_5_4_LogicBool* bevt_34_ta_ph; BEC_2_5_4_LogicBool* bevt_35_ta_ph; BEC_2_4_3_MathInt* bevt_36_ta_ph; BEC_2_5_4_LogicBool* bevt_37_ta_ph; BEC_2_5_4_LogicBool* bevt_38_ta_ph; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->beva_mqttHandler = bevk_mqttHandler;
beq->bevl_gott = nullptr;
beq->bevl_gotp = nullptr;
beq->bevl_tosub = nullptr;
beq->bevl_m = nullptr;
beq->bevt_0_ta_anchor = nullptr;
beq->bevt_1_ta_ph = nullptr;
beq->bevt_2_ta_ph = nullptr;
beq->bevt_3_ta_ph = nullptr;
beq->bevt_4_ta_ph = nullptr;
beq->bevt_5_ta_ph = nullptr;
beq->bevt_6_ta_ph = nullptr;
beq->bevt_7_ta_ph = nullptr;
beq->bevt_8_ta_ph = nullptr;
beq->bevt_9_ta_ph = nullptr;
beq->bevt_10_ta_ph = nullptr;
beq->bevt_11_ta_ph = nullptr;
beq->bevt_12_ta_ph = nullptr;
beq->bevt_13_ta_ph = nullptr;
beq->bevt_14_ta_ph = nullptr;
beq->bevt_15_ta_ph = nullptr;
beq->bevt_16_ta_ph = nullptr;
beq->bevt_17_ta_ph = nullptr;
beq->bevt_18_ta_ph = nullptr;
beq->bevt_19_ta_ph = nullptr;
beq->bevt_20_ta_ph = nullptr;
beq->bevt_21_ta_ph = nullptr;
beq->bevt_22_ta_ph = nullptr;
beq->bevt_23_ta_ph = nullptr;
beq->bevt_24_ta_ph = nullptr;
beq->bevt_25_ta_ph = nullptr;
beq->bevt_26_ta_ph = nullptr;
beq->bevt_27_ta_ph = nullptr;
beq->bevt_28_ta_ph = nullptr;
beq->bevt_29_ta_ph = nullptr;
beq->bevt_30_ta_ph = nullptr;
beq->bevt_31_ta_ph = nullptr;
beq->bevt_32_ta_ph = nullptr;
beq->bevt_33_ta_ph = nullptr;
beq->bevt_34_ta_ph = nullptr;
beq->bevt_35_ta_ph = nullptr;
beq->bevt_36_ta_ph = nullptr;
beq->bevt_37_ta_ph = nullptr;
beq->bevt_38_ta_ph = nullptr;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(45);

      if (!client->loop()) {
        //Serial.println(client->lastError());
        //if got something during recieve, return
      beq->bevt_1_ta_ph = static_cast<BEC_2_5_4_LogicBool*>(BECS_Runtime::boolFalse);
return beq->bevt_1_ta_ph;

    } else {
      if (BEC_2_8_4_EmbeddedMqtt::gotTopic.size() > 0 &&  BEC_2_8_4_EmbeddedMqtt::gotPayload.size() > 0) {
        beq->bevl_gott = new BEC_2_4_6_TextString(BEC_2_8_4_EmbeddedMqtt::gotTopic);
        beq->bevl_gotp = new BEC_2_4_6_TextString(BEC_2_8_4_EmbeddedMqtt::gotPayload);
        BEC_2_8_4_EmbeddedMqtt::gotTopic.clear();
        BEC_2_8_4_EmbeddedMqtt::gotPayload.clear();
      }
    }
      beq->bevt_3_ta_ph = static_cast<BEC_2_4_7_TextStrings*>(BEC_2_4_7_TextStrings::bece_BEC_2_4_7_TextStrings_bevs_inst);
beq->bevt_2_ta_ph = beq->bevt_3_ta_ph->bem_notEmpty_1(beq->bevl_gott);
if (beq->bevt_2_ta_ph->bevi_bool) {
beq->bevt_5_ta_ph = static_cast<BEC_2_4_7_TextStrings*>(BEC_2_4_7_TextStrings::bece_BEC_2_4_7_TextStrings_bevs_inst);
beq->bevt_4_ta_ph = beq->bevt_5_ta_ph->bem_notEmpty_1(beq->bevl_gotp);
if (beq->bevt_4_ta_ph->bevi_bool) {
beq->bevt_0_ta_anchor = BECS_Runtime::boolTrue;
} 
 else  {
beq->bevt_0_ta_anchor = BECS_Runtime::boolFalse;
} 
} 
 else  {
beq->bevt_0_ta_anchor = BECS_Runtime::boolFalse;
} 
if (beq->bevt_0_ta_anchor->bevi_bool) {
beq->bevt_7_ta_ph = bevp_mqrcl->bem_sizeGet_0();
if (bevp_mqrcmax->bevi_int > beq->bevt_7_ta_ph->bevi_int) {
beq->bevt_6_ta_ph = BECS_Runtime::boolTrue;
 } else { 
beq->bevt_6_ta_ph = BECS_Runtime::boolFalse;
}
if (beq->bevt_6_ta_ph->bevi_bool) {
beq->bevt_8_ta_ph = static_cast<BEC_2_8_11_EmbeddedMqttMessage*>(((BEC_2_8_11_EmbeddedMqttMessage*) (new BEC_2_8_11_EmbeddedMqttMessage()))->bem_new_2(beq->bevl_gott, beq->bevl_gotp));
bevp_mqrcl->bem_addValue_1(beq->bevt_8_ta_ph);
} 
 else  {
beq->bevt_9_ta_ph = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString(10, {0x6D,0x71,0x72,0x63,0x6C,0x20,0x66,0x75,0x6C,0x6C}))));
beq->bevt_9_ta_ph->bem_print_0();
} 
beq->bevt_10_ta_ph = static_cast<BEC_2_5_4_LogicBool*>(BECS_Runtime::boolFalse);
return beq->bevt_10_ta_ph;
} 
if (bevp_mqsubi == nullptr) {
beq->bevt_11_ta_ph = BECS_Runtime::boolFalse;
 } else { 
beq->bevt_11_ta_ph = BECS_Runtime::boolTrue;
}
if (beq->bevt_11_ta_ph->bevi_bool) {
beq->bevt_12_ta_ph = bevp_mqsubi->bem_hasNextGet_0();
if (beq->bevt_12_ta_ph->bevi_bool) {
beq->bevl_tosub = static_cast<BEC_2_4_6_TextString*>(bevp_mqsubi->bem_nextGet_0());
bem_subscribe_1(beq->bevl_tosub);
beq->bevt_13_ta_ph = static_cast<BEC_2_5_4_LogicBool*>(BECS_Runtime::boolTrue);
return beq->bevt_13_ta_ph;
} 
 else  {
bevp_mqsubi = nullptr;
bevp_mqsubl->bem_clear_0();
beq->bevt_14_ta_ph = static_cast<BEC_2_5_4_LogicBool*>(BECS_Runtime::boolFalse);
return beq->bevt_14_ta_ph;
} 
} 
 else  {
beq->bevt_16_ta_ph = bevp_mqsubl->bem_sizeGet_0();
if (beq->bevt_16_ta_ph->bevi_int > bevp_zero->bevi_int) {
beq->bevt_15_ta_ph = BECS_Runtime::boolTrue;
 } else { 
beq->bevt_15_ta_ph = BECS_Runtime::boolFalse;
}
if (beq->bevt_15_ta_ph->bevi_bool) {
bevp_mqsubi = static_cast<BEC_3_9_4_8_ContainerListIterator*>(bevp_mqsubl->bem_iteratorGet_0());
beq->bevt_17_ta_ph = static_cast<BEC_2_5_4_LogicBool*>(BECS_Runtime::boolFalse);
return beq->bevt_17_ta_ph;
} 
} 
if (bevp_mqrcm == nullptr) {
beq->bevt_18_ta_ph = BECS_Runtime::boolFalse;
 } else { 
beq->bevt_18_ta_ph = BECS_Runtime::boolTrue;
}
if (beq->bevt_18_ta_ph->bevi_bool) {
beq->bevl_m = bevp_mqrcm;
bevp_mqrcm = nullptr;
beq->bevt_19_ta_ph = beq->bevl_m->bem_topicGet_0();
beq->bevt_20_ta_ph = beq->bevl_m->bem_payloadGet_0();
beq->beva_mqttHandler->bemd_2(-290210157, beq->bevt_19_ta_ph, beq->bevt_20_ta_ph);
beq->bevt_21_ta_ph = static_cast<BEC_2_5_4_LogicBool*>(BECS_Runtime::boolTrue);
return beq->bevt_21_ta_ph;
} 
 else  {
if (bevp_mqrci == nullptr) {
beq->bevt_22_ta_ph = BECS_Runtime::boolFalse;
 } else { 
beq->bevt_22_ta_ph = BECS_Runtime::boolTrue;
}
if (beq->bevt_22_ta_ph->bevi_bool) {
beq->bevt_23_ta_ph = bevp_mqrci->bem_hasNextGet_0();
if (beq->bevt_23_ta_ph->bevi_bool) {
bevp_mqrcm = static_cast<BEC_2_8_11_EmbeddedMqttMessage*>(bevp_mqrci->bem_nextGet_0());
beq->bevt_24_ta_ph = static_cast<BEC_2_5_4_LogicBool*>(BECS_Runtime::boolFalse);
return beq->bevt_24_ta_ph;
} 
 else  {
bevp_mqrci = nullptr;
beq->bevt_25_ta_ph = static_cast<BEC_2_5_4_LogicBool*>(BECS_Runtime::boolFalse);
return beq->bevt_25_ta_ph;
} 
} 
 else  {
beq->bevt_27_ta_ph = bevp_mqrcl->bem_sizeGet_0();
if (beq->bevt_27_ta_ph->bevi_int > bevp_zero->bevi_int) {
beq->bevt_26_ta_ph = BECS_Runtime::boolTrue;
 } else { 
beq->bevt_26_ta_ph = BECS_Runtime::boolFalse;
}
if (beq->bevt_26_ta_ph->bevi_bool) {
bevp_mqrci = static_cast<BEC_3_9_4_8_ContainerListIterator*>(bevp_mqrcl->bem_iteratorGet_0());
bevp_mqrcl = static_cast<BEC_2_9_4_ContainerList*>(((BEC_2_9_4_ContainerList*) (new BEC_2_9_4_ContainerList()))->bem_new_0());
beq->bevt_28_ta_ph = static_cast<BEC_2_5_4_LogicBool*>(BECS_Runtime::boolFalse);
return beq->bevt_28_ta_ph;
} 
} 
} 
if (bevp_mqpubm == nullptr) {
beq->bevt_29_ta_ph = BECS_Runtime::boolFalse;
 } else { 
beq->bevt_29_ta_ph = BECS_Runtime::boolTrue;
}
if (beq->bevt_29_ta_ph->bevi_bool) {
bem_publish_1(bevp_mqpubm);
bevp_mqpubm = nullptr;
beq->bevt_30_ta_ph = static_cast<BEC_2_5_4_LogicBool*>(BECS_Runtime::boolTrue);
return beq->bevt_30_ta_ph;
} 
 else  {
if (bevp_mqpubi == nullptr) {
beq->bevt_31_ta_ph = BECS_Runtime::boolFalse;
 } else { 
beq->bevt_31_ta_ph = BECS_Runtime::boolTrue;
}
if (beq->bevt_31_ta_ph->bevi_bool) {
beq->bevt_32_ta_ph = bevp_mqpubi->bem_hasNextGet_0();
if (beq->bevt_32_ta_ph->bevi_bool) {
bevp_mqpubm = static_cast<BEC_2_8_11_EmbeddedMqttMessage*>(bevp_mqpubi->bem_nextGet_0());
beq->bevt_33_ta_ph = static_cast<BEC_2_5_4_LogicBool*>(BECS_Runtime::boolFalse);
return beq->bevt_33_ta_ph;
} 
 else  {
bevp_mqpubi = nullptr;
bevp_mqpubl->bem_clear_0();
beq->bevt_34_ta_ph = static_cast<BEC_2_5_4_LogicBool*>(BECS_Runtime::boolFalse);
return beq->bevt_34_ta_ph;
} 
} 
 else  {
beq->bevt_36_ta_ph = bevp_mqpubl->bem_sizeGet_0();
if (beq->bevt_36_ta_ph->bevi_int > bevp_zero->bevi_int) {
beq->bevt_35_ta_ph = BECS_Runtime::boolTrue;
 } else { 
beq->bevt_35_ta_ph = BECS_Runtime::boolFalse;
}
if (beq->bevt_35_ta_ph->bevi_bool) {
bevp_mqpubi = static_cast<BEC_3_9_4_8_ContainerListIterator*>(bevp_mqpubl->bem_iteratorGet_0());
beq->bevt_37_ta_ph = static_cast<BEC_2_5_4_LogicBool*>(BECS_Runtime::boolFalse);
return beq->bevt_37_ta_ph;
} 
} 
} 
beq->bevt_38_ta_ph = static_cast<BEC_2_5_4_LogicBool*>(BECS_Runtime::boolFalse);
return beq->bevt_38_ta_ph;
}
BEC_2_8_4_EmbeddedMqtt* BEC_2_8_4_EmbeddedMqtt::bem_subscribe_1(BEC_2_4_6_TextString* bevk_topic) {
struct bes { BEC_2_4_6_TextString* beva_topic; BEC_2_5_4_LogicBool* bevt_0_ta_ph; BEC_2_4_7_TextStrings* bevt_1_ta_ph; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->beva_topic = bevk_topic;
beq->bevt_0_ta_ph = nullptr;
beq->bevt_1_ta_ph = nullptr;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(4);
beq->bevt_1_ta_ph = static_cast<BEC_2_4_7_TextStrings*>(BEC_2_4_7_TextStrings::bece_BEC_2_4_7_TextStrings_bevs_inst);
beq->bevt_0_ta_ph = beq->bevt_1_ta_ph->bem_notEmpty_1(beq->beva_topic);
if (beq->bevt_0_ta_ph->bevi_bool) {

        client->subscribe(beq->beva_topic->bems_toCcString().c_str());
        } 
return this;
}
BEC_2_4_6_TextString* BEC_2_8_4_EmbeddedMqtt::bem_mqttServerGet_0() {
struct bes {  BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(1);
return bevp_mqttServer;
}
BEC_2_8_4_EmbeddedMqtt* BEC_2_8_4_EmbeddedMqtt::bem_mqttServerSet_1(BEC_2_6_6_SystemObject* bevt_0_ta_SET) {
struct bes { BEC_2_6_6_SystemObject* bevt_0_ta_SET; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->bevt_0_ta_SET = bevt_0_ta_SET;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(2);
bevp_mqttServer = static_cast<BEC_2_4_6_TextString*>(beq->bevt_0_ta_SET);
return this;
}
BEC_2_4_6_TextString* BEC_2_8_4_EmbeddedMqtt::bem_userGet_0() {
struct bes {  BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(1);
return bevp_user;
}
BEC_2_8_4_EmbeddedMqtt* BEC_2_8_4_EmbeddedMqtt::bem_userSet_1(BEC_2_6_6_SystemObject* bevt_0_ta_SET) {
struct bes { BEC_2_6_6_SystemObject* bevt_0_ta_SET; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->bevt_0_ta_SET = bevt_0_ta_SET;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(2);
bevp_user = static_cast<BEC_2_4_6_TextString*>(beq->bevt_0_ta_SET);
return this;
}
BEC_2_4_6_TextString* BEC_2_8_4_EmbeddedMqtt::bem_passGet_0() {
struct bes {  BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(1);
return bevp_pass;
}
BEC_2_8_4_EmbeddedMqtt* BEC_2_8_4_EmbeddedMqtt::bem_passSet_1(BEC_2_6_6_SystemObject* bevt_0_ta_SET) {
struct bes { BEC_2_6_6_SystemObject* bevt_0_ta_SET; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->bevt_0_ta_SET = bevt_0_ta_SET;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(2);
bevp_pass = static_cast<BEC_2_4_6_TextString*>(beq->bevt_0_ta_SET);
return this;
}
BEC_2_4_3_MathInt* BEC_2_8_4_EmbeddedMqtt::bem_mqttPortGet_0() {
struct bes {  BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(1);
return bevp_mqttPort;
}
BEC_2_8_4_EmbeddedMqtt* BEC_2_8_4_EmbeddedMqtt::bem_mqttPortSet_1(BEC_2_6_6_SystemObject* bevt_0_ta_SET) {
struct bes { BEC_2_6_6_SystemObject* bevt_0_ta_SET; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->bevt_0_ta_SET = bevt_0_ta_SET;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(2);
bevp_mqttPort = static_cast<BEC_2_4_3_MathInt*>(beq->bevt_0_ta_SET);
return this;
}
BEC_2_4_6_TextString* BEC_2_8_4_EmbeddedMqtt::bem_idGet_0() {
struct bes {  BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(1);
return bevp_id;
}
BEC_2_8_4_EmbeddedMqtt* BEC_2_8_4_EmbeddedMqtt::bem_idSet_1(BEC_2_6_6_SystemObject* bevt_0_ta_SET) {
struct bes { BEC_2_6_6_SystemObject* bevt_0_ta_SET; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->bevt_0_ta_SET = bevt_0_ta_SET;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(2);
bevp_id = static_cast<BEC_2_4_6_TextString*>(beq->bevt_0_ta_SET);
return this;
}
BEC_2_9_4_ContainerList* BEC_2_8_4_EmbeddedMqtt::bem_mqsublGet_0() {
struct bes {  BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(1);
return bevp_mqsubl;
}
BEC_2_8_4_EmbeddedMqtt* BEC_2_8_4_EmbeddedMqtt::bem_mqsublSet_1(BEC_2_6_6_SystemObject* bevt_0_ta_SET) {
struct bes { BEC_2_6_6_SystemObject* bevt_0_ta_SET; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->bevt_0_ta_SET = bevt_0_ta_SET;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(2);
bevp_mqsubl = static_cast<BEC_2_9_4_ContainerList*>(beq->bevt_0_ta_SET);
return this;
}
BEC_3_9_4_8_ContainerListIterator* BEC_2_8_4_EmbeddedMqtt::bem_mqsubiGet_0() {
struct bes {  BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(1);
return bevp_mqsubi;
}
BEC_2_8_4_EmbeddedMqtt* BEC_2_8_4_EmbeddedMqtt::bem_mqsubiSet_1(BEC_2_6_6_SystemObject* bevt_0_ta_SET) {
struct bes { BEC_2_6_6_SystemObject* bevt_0_ta_SET; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->bevt_0_ta_SET = bevt_0_ta_SET;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(2);
bevp_mqsubi = static_cast<BEC_3_9_4_8_ContainerListIterator*>(beq->bevt_0_ta_SET);
return this;
}
BEC_2_8_11_EmbeddedMqttMessage* BEC_2_8_4_EmbeddedMqtt::bem_mqpubmGet_0() {
struct bes {  BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(1);
return bevp_mqpubm;
}
BEC_2_8_4_EmbeddedMqtt* BEC_2_8_4_EmbeddedMqtt::bem_mqpubmSet_1(BEC_2_6_6_SystemObject* bevt_0_ta_SET) {
struct bes { BEC_2_6_6_SystemObject* bevt_0_ta_SET; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->bevt_0_ta_SET = bevt_0_ta_SET;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(2);
bevp_mqpubm = static_cast<BEC_2_8_11_EmbeddedMqttMessage*>(beq->bevt_0_ta_SET);
return this;
}
BEC_2_9_4_ContainerList* BEC_2_8_4_EmbeddedMqtt::bem_mqpublGet_0() {
struct bes {  BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(1);
return bevp_mqpubl;
}
BEC_2_8_4_EmbeddedMqtt* BEC_2_8_4_EmbeddedMqtt::bem_mqpublSet_1(BEC_2_6_6_SystemObject* bevt_0_ta_SET) {
struct bes { BEC_2_6_6_SystemObject* bevt_0_ta_SET; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->bevt_0_ta_SET = bevt_0_ta_SET;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(2);
bevp_mqpubl = static_cast<BEC_2_9_4_ContainerList*>(beq->bevt_0_ta_SET);
return this;
}
BEC_3_9_4_8_ContainerListIterator* BEC_2_8_4_EmbeddedMqtt::bem_mqpubiGet_0() {
struct bes {  BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(1);
return bevp_mqpubi;
}
BEC_2_8_4_EmbeddedMqtt* BEC_2_8_4_EmbeddedMqtt::bem_mqpubiSet_1(BEC_2_6_6_SystemObject* bevt_0_ta_SET) {
struct bes { BEC_2_6_6_SystemObject* bevt_0_ta_SET; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->bevt_0_ta_SET = bevt_0_ta_SET;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(2);
bevp_mqpubi = static_cast<BEC_3_9_4_8_ContainerListIterator*>(beq->bevt_0_ta_SET);
return this;
}
BEC_2_4_3_MathInt* BEC_2_8_4_EmbeddedMqtt::bem_mqpublmaxGet_0() {
struct bes {  BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(1);
return bevp_mqpublmax;
}
BEC_2_8_4_EmbeddedMqtt* BEC_2_8_4_EmbeddedMqtt::bem_mqpublmaxSet_1(BEC_2_6_6_SystemObject* bevt_0_ta_SET) {
struct bes { BEC_2_6_6_SystemObject* bevt_0_ta_SET; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->bevt_0_ta_SET = bevt_0_ta_SET;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(2);
bevp_mqpublmax = static_cast<BEC_2_4_3_MathInt*>(beq->bevt_0_ta_SET);
return this;
}
BEC_2_8_11_EmbeddedMqttMessage* BEC_2_8_4_EmbeddedMqtt::bem_mqrcmGet_0() {
struct bes {  BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(1);
return bevp_mqrcm;
}
BEC_2_8_4_EmbeddedMqtt* BEC_2_8_4_EmbeddedMqtt::bem_mqrcmSet_1(BEC_2_6_6_SystemObject* bevt_0_ta_SET) {
struct bes { BEC_2_6_6_SystemObject* bevt_0_ta_SET; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->bevt_0_ta_SET = bevt_0_ta_SET;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(2);
bevp_mqrcm = static_cast<BEC_2_8_11_EmbeddedMqttMessage*>(beq->bevt_0_ta_SET);
return this;
}
BEC_2_9_4_ContainerList* BEC_2_8_4_EmbeddedMqtt::bem_mqrclGet_0() {
struct bes {  BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(1);
return bevp_mqrcl;
}
BEC_2_8_4_EmbeddedMqtt* BEC_2_8_4_EmbeddedMqtt::bem_mqrclSet_1(BEC_2_6_6_SystemObject* bevt_0_ta_SET) {
struct bes { BEC_2_6_6_SystemObject* bevt_0_ta_SET; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->bevt_0_ta_SET = bevt_0_ta_SET;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(2);
bevp_mqrcl = static_cast<BEC_2_9_4_ContainerList*>(beq->bevt_0_ta_SET);
return this;
}
BEC_3_9_4_8_ContainerListIterator* BEC_2_8_4_EmbeddedMqtt::bem_mqrciGet_0() {
struct bes {  BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(1);
return bevp_mqrci;
}
BEC_2_8_4_EmbeddedMqtt* BEC_2_8_4_EmbeddedMqtt::bem_mqrciSet_1(BEC_2_6_6_SystemObject* bevt_0_ta_SET) {
struct bes { BEC_2_6_6_SystemObject* bevt_0_ta_SET; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->bevt_0_ta_SET = bevt_0_ta_SET;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(2);
bevp_mqrci = static_cast<BEC_3_9_4_8_ContainerListIterator*>(beq->bevt_0_ta_SET);
return this;
}
BEC_2_4_3_MathInt* BEC_2_8_4_EmbeddedMqtt::bem_mqrcmaxGet_0() {
struct bes {  BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(1);
return bevp_mqrcmax;
}
BEC_2_8_4_EmbeddedMqtt* BEC_2_8_4_EmbeddedMqtt::bem_mqrcmaxSet_1(BEC_2_6_6_SystemObject* bevt_0_ta_SET) {
struct bes { BEC_2_6_6_SystemObject* bevt_0_ta_SET; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->bevt_0_ta_SET = bevt_0_ta_SET;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(2);
bevp_mqrcmax = static_cast<BEC_2_4_3_MathInt*>(beq->bevt_0_ta_SET);
return this;
}
BEC_2_4_3_MathInt* BEC_2_8_4_EmbeddedMqtt::bem_zeroGet_0() {
struct bes {  BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(1);
return bevp_zero;
}
BEC_2_8_4_EmbeddedMqtt* BEC_2_8_4_EmbeddedMqtt::bem_zeroSet_1(BEC_2_6_6_SystemObject* bevt_0_ta_SET) {
struct bes { BEC_2_6_6_SystemObject* bevt_0_ta_SET; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->bevt_0_ta_SET = bevt_0_ta_SET;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(2);
bevp_zero = static_cast<BEC_2_4_3_MathInt*>(beq->bevt_0_ta_SET);
return this;
}
BEC_2_6_6_SystemObject* BEC_2_8_4_EmbeddedMqtt::bemd_0(int32_t callId) {
switch (callId) {
case 2076043936: return bem_mqpubiGet_0();
case 1030934124: return bem_open_0();
case 378355279: return bem_mqrclGet_0();
case 864457272: return bem_mqrciGet_0();
case -1419867654: return bem_passGet_0();
case -1398839411: return bem_mqsubiGet_0();
case 363757507: return bem_zeroGet_0();
case -1546907271: return bem_close_0();
case -2020464889: return bem_mqsublGet_0();
case 412187378: return bem_mqttPortGet_0();
case -1708851498: return bem_idGet_0();
case -656365695: return bem_mqpublmaxGet_0();
case -858738685: return bem_mqrcmaxGet_0();
case -981934879: return bem_userGet_0();
case -906392495: return bem_mqttServerGet_0();
case -1785532669: return bem_new_0();
case -1028410983: return bem_mqpublGet_0();
case -1325181676: return bem_mqpubmGet_0();
case -1043915750: return bem_isOpenGet_0();
case -253705086: return bem_mqrcmGet_0();
}
return bevs_super::bemd_0(callId);
}
BEC_2_6_6_SystemObject* BEC_2_8_4_EmbeddedMqtt::bemd_1(int32_t callId, BEC_2_6_6_SystemObject* bevd_0) {
switch (callId) {
case 593309101: return bem_zeroSet_1(bevd_0);
case 340167002: return bem_handleAsync_1(bevd_0);
case -14277259: return bem_mqttPortSet_1(bevd_0);
case 730829460: return bem_mqsubiSet_1(bevd_0);
case 690037214: return bem_publish_1(static_cast<BEC_2_8_11_EmbeddedMqttMessage*>(bevd_0));
case -670112816: return bem_subscribe_1(static_cast<BEC_2_4_6_TextString*>(bevd_0));
case 845955769: return bem_mqrcmSet_1(bevd_0);
case 612267570: return bem_mqpubiSet_1(bevd_0);
case -1685322371: return bem_minAsyncCapacitySet_1(static_cast<BEC_2_4_3_MathInt*>(bevd_0));
case -1998292872: return bem_mqpublmaxSet_1(bevd_0);
case -202227122: return bem_mqrcmaxSet_1(bevd_0);
case -894014927: return bem_publishAsync_1(static_cast<BEC_2_8_11_EmbeddedMqttMessage*>(bevd_0));
case -988558829: return bem_mqrciSet_1(bevd_0);
case -945954232: return bem_mqpublSet_1(bevd_0);
case -710990134: return bem_passSet_1(bevd_0);
case 554973435: return bem_subscribeAsync_1(static_cast<BEC_2_4_6_TextString*>(bevd_0));
case 422713187: return bem_userSet_1(bevd_0);
case -1138404590: return bem_hasAsyncCapacity_1(static_cast<BEC_2_4_3_MathInt*>(bevd_0));
case 2058516640: return bem_mqrclSet_1(bevd_0);
case -490009595: return bem_mqttServerSet_1(bevd_0);
case 674953895: return bem_mqpubmSet_1(bevd_0);
case -1257752447: return bem_idSet_1(bevd_0);
case -904703648: return bem_mqsublSet_1(bevd_0);
}
return bevs_super::bemd_1(callId, bevd_0);
}
BEC_2_6_6_SystemObject* BEC_2_8_4_EmbeddedMqtt::bemd_2(int32_t callId, BEC_2_6_6_SystemObject* bevd_0, BEC_2_6_6_SystemObject* bevd_1) {
switch (callId) {
case 941784113: return bem_publishAsync_2(static_cast<BEC_2_4_6_TextString*>(bevd_0), static_cast<BEC_2_4_6_TextString*>(bevd_1));
case -1399237067: return bem_publish_2(static_cast<BEC_2_4_6_TextString*>(bevd_0), static_cast<BEC_2_4_6_TextString*>(bevd_1));
}
return bevs_super::bemd_2(callId, bevd_0, bevd_1);
}
BEC_2_6_6_SystemObject* BEC_2_8_4_EmbeddedMqtt::bemd_3(int32_t callId, BEC_2_6_6_SystemObject* bevd_0, BEC_2_6_6_SystemObject* bevd_1, BEC_2_6_6_SystemObject* bevd_2) {
switch (callId) {
case 1621481437: return bem_new_3(static_cast<BEC_2_4_6_TextString*>(bevd_0), static_cast<BEC_2_4_6_TextString*>(bevd_1), static_cast<BEC_2_4_6_TextString*>(bevd_2));
}
return bevs_super::bemd_3(callId, bevd_0, bevd_1, bevd_2);
}
BEC_2_6_6_SystemObject* BEC_2_8_4_EmbeddedMqtt::bemc_create() {
return new BEC_2_8_4_EmbeddedMqtt();
}
void BEC_2_8_4_EmbeddedMqtt::bemc_setInitial(BEC_2_6_6_SystemObject* becc_inst) {
BEC_2_8_4_EmbeddedMqtt::bece_BEC_2_8_4_EmbeddedMqtt_bevs_inst = static_cast<BEC_2_8_4_EmbeddedMqtt*>(becc_inst);
}
BEC_2_6_6_SystemObject* BEC_2_8_4_EmbeddedMqtt::bemc_getInitial() {
return BEC_2_8_4_EmbeddedMqtt::bece_BEC_2_8_4_EmbeddedMqtt_bevs_inst;
}
void BEC_2_8_4_EmbeddedMqtt::bemg_doMark() {
bevg_gcMark = BECS_Runtime::bevg_currentGcMark;
if (bevp_mqttServer != nullptr && bevp_mqttServer->bevg_gcMark != BECS_Runtime::bevg_currentGcMark) {
bevp_mqttServer->bemg_doMark();
}
if (bevp_user != nullptr && bevp_user->bevg_gcMark != BECS_Runtime::bevg_currentGcMark) {
bevp_user->bemg_doMark();
}
if (bevp_pass != nullptr && bevp_pass->bevg_gcMark != BECS_Runtime::bevg_currentGcMark) {
bevp_pass->bemg_doMark();
}
if (bevp_mqttPort != nullptr && bevp_mqttPort->bevg_gcMark != BECS_Runtime::bevg_currentGcMark) {
bevp_mqttPort->bemg_doMark();
}
if (bevp_id != nullptr && bevp_id->bevg_gcMark != BECS_Runtime::bevg_currentGcMark) {
bevp_id->bemg_doMark();
}
if (bevp_mqsubl != nullptr && bevp_mqsubl->bevg_gcMark != BECS_Runtime::bevg_currentGcMark) {
bevp_mqsubl->bemg_doMark();
}
if (bevp_mqsubi != nullptr && bevp_mqsubi->bevg_gcMark != BECS_Runtime::bevg_currentGcMark) {
bevp_mqsubi->bemg_doMark();
}
if (bevp_mqpubm != nullptr && bevp_mqpubm->bevg_gcMark != BECS_Runtime::bevg_currentGcMark) {
bevp_mqpubm->bemg_doMark();
}
if (bevp_mqpubl != nullptr && bevp_mqpubl->bevg_gcMark != BECS_Runtime::bevg_currentGcMark) {
bevp_mqpubl->bemg_doMark();
}
if (bevp_mqpubi != nullptr && bevp_mqpubi->bevg_gcMark != BECS_Runtime::bevg_currentGcMark) {
bevp_mqpubi->bemg_doMark();
}
if (bevp_mqpublmax != nullptr && bevp_mqpublmax->bevg_gcMark != BECS_Runtime::bevg_currentGcMark) {
bevp_mqpublmax->bemg_doMark();
}
if (bevp_mqrcm != nullptr && bevp_mqrcm->bevg_gcMark != BECS_Runtime::bevg_currentGcMark) {
bevp_mqrcm->bemg_doMark();
}
if (bevp_mqrcl != nullptr && bevp_mqrcl->bevg_gcMark != BECS_Runtime::bevg_currentGcMark) {
bevp_mqrcl->bemg_doMark();
}
if (bevp_mqrci != nullptr && bevp_mqrci->bevg_gcMark != BECS_Runtime::bevg_currentGcMark) {
bevp_mqrci->bemg_doMark();
}
if (bevp_mqrcmax != nullptr && bevp_mqrcmax->bevg_gcMark != BECS_Runtime::bevg_currentGcMark) {
bevp_mqrcmax->bemg_doMark();
}
if (bevp_zero != nullptr && bevp_zero->bevg_gcMark != BECS_Runtime::bevg_currentGcMark) {
bevp_zero->bemg_doMark();
}
}
size_t BEC_2_8_4_EmbeddedMqtt::bemg_getSize() {
return sizeof(*this);
}
BETS_Object* BEC_2_8_4_EmbeddedMqtt::bemc_getType() {
return &BEC_2_8_4_EmbeddedMqtt::bece_BEC_2_8_4_EmbeddedMqtt_bevs_type;
}
BET_2_8_11_EmbeddedMqttMessage::BET_2_8_11_EmbeddedMqttMessage() {
std::vector<std::string> bevs_mtnames = {  };
bevs_fieldNames = {  };
}
BEC_2_6_6_SystemObject* BET_2_8_11_EmbeddedMqttMessage::bems_createInstance() {
return new BEC_2_8_11_EmbeddedMqttMessage();
}
void BET_2_8_11_EmbeddedMqttMessage::bemgt_doMark() {
BEC_2_6_6_SystemObject* bevsl_inst_ref = *bevs_inst_ref;
if (bevsl_inst_ref != nullptr && bevsl_inst_ref->bevg_gcMark != BECS_Runtime::bevg_currentGcMark) {
bevsl_inst_ref->bemg_doMark();
}
}
BEC_2_8_11_EmbeddedMqttMessage* BEC_2_8_11_EmbeddedMqttMessage::bece_BEC_2_8_11_EmbeddedMqttMessage_bevs_inst;

BET_2_8_11_EmbeddedMqttMessage BEC_2_8_11_EmbeddedMqttMessage::bece_BEC_2_8_11_EmbeddedMqttMessage_bevs_type;
BEC_2_6_6_SystemObject** BET_2_8_11_EmbeddedMqttMessage::bevs_inst_ref = (BEC_2_6_6_SystemObject**) &BEC_2_8_11_EmbeddedMqttMessage::bece_BEC_2_8_11_EmbeddedMqttMessage_bevs_inst;

BEC_2_8_11_EmbeddedMqttMessage* BEC_2_8_11_EmbeddedMqttMessage::bem_new_2(BEC_2_4_6_TextString* bevk__topic, BEC_2_4_6_TextString* bevk__payload) {
struct bes { BEC_2_4_6_TextString* beva__topic; BEC_2_4_6_TextString* beva__payload; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->beva__topic = bevk__topic;
beq->beva__payload = bevk__payload;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(3);
bevp_topic = beq->beva__topic;
bevp_payload = beq->beva__payload;
return this;
}
BEC_2_4_6_TextString* BEC_2_8_11_EmbeddedMqttMessage::bem_toString_0() {
struct bes { BEC_2_4_6_TextString* bevl_ret; BEC_2_5_4_LogicBool* bevt_0_ta_ph; BEC_2_4_7_TextStrings* bevt_1_ta_ph; BEC_2_4_6_TextString* bevt_2_ta_ph; BEC_2_4_6_TextString* bevt_3_ta_ph; BEC_2_4_6_TextString* bevt_4_ta_ph; BEC_2_4_6_TextString* bevt_5_ta_ph; BEC_2_4_6_TextString* bevt_6_ta_ph; BEC_2_5_4_LogicBool* bevt_7_ta_ph; BEC_2_4_7_TextStrings* bevt_8_ta_ph; BEC_2_4_6_TextString* bevt_9_ta_ph; BEC_2_4_6_TextString* bevt_10_ta_ph; BEC_2_4_6_TextString* bevt_11_ta_ph; BEC_2_4_6_TextString* bevt_12_ta_ph; BEC_2_4_6_TextString* bevt_13_ta_ph; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->bevl_ret = nullptr;
beq->bevt_0_ta_ph = nullptr;
beq->bevt_1_ta_ph = nullptr;
beq->bevt_2_ta_ph = nullptr;
beq->bevt_3_ta_ph = nullptr;
beq->bevt_4_ta_ph = nullptr;
beq->bevt_5_ta_ph = nullptr;
beq->bevt_6_ta_ph = nullptr;
beq->bevt_7_ta_ph = nullptr;
beq->bevt_8_ta_ph = nullptr;
beq->bevt_9_ta_ph = nullptr;
beq->bevt_10_ta_ph = nullptr;
beq->bevt_11_ta_ph = nullptr;
beq->bevt_12_ta_ph = nullptr;
beq->bevt_13_ta_ph = nullptr;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(16);
beq->bevl_ret = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString()))->bem_new_0());
beq->bevt_1_ta_ph = static_cast<BEC_2_4_7_TextStrings*>(BEC_2_4_7_TextStrings::bece_BEC_2_4_7_TextStrings_bevs_inst);
beq->bevt_0_ta_ph = beq->bevt_1_ta_ph->bem_notEmpty_1(bevp_topic);
if (beq->bevt_0_ta_ph->bevi_bool) {
beq->bevt_4_ta_ph = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString(6, {0x54,0x6F,0x70,0x69,0x63,0x3A}))));
beq->bevt_3_ta_ph = static_cast<BEC_2_4_6_TextString*>(beq->bevl_ret->bem_addValue_1(beq->bevt_4_ta_ph));
beq->bevt_2_ta_ph = static_cast<BEC_2_4_6_TextString*>(beq->bevt_3_ta_ph->bem_addValue_1(bevp_topic));
beq->bevt_5_ta_ph = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString(1, {0x3B}))));
beq->bevt_2_ta_ph->bem_addValue_1(beq->bevt_5_ta_ph);
} 
 else  {
beq->bevt_6_ta_ph = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString(12, {0x54,0x6F,0x70,0x69,0x63,0x45,0x6D,0x70,0x74,0x79,0x3A,0x3B}))));
beq->bevl_ret->bem_addValue_1(beq->bevt_6_ta_ph);
} 
beq->bevt_8_ta_ph = static_cast<BEC_2_4_7_TextStrings*>(BEC_2_4_7_TextStrings::bece_BEC_2_4_7_TextStrings_bevs_inst);
beq->bevt_7_ta_ph = beq->bevt_8_ta_ph->bem_notEmpty_1(bevp_payload);
if (beq->bevt_7_ta_ph->bevi_bool) {
beq->bevt_11_ta_ph = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString(8, {0x50,0x61,0x79,0x6C,0x6F,0x61,0x64,0x3A}))));
beq->bevt_10_ta_ph = static_cast<BEC_2_4_6_TextString*>(beq->bevl_ret->bem_addValue_1(beq->bevt_11_ta_ph));
beq->bevt_9_ta_ph = static_cast<BEC_2_4_6_TextString*>(beq->bevt_10_ta_ph->bem_addValue_1(bevp_payload));
beq->bevt_12_ta_ph = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString(1, {0x3B}))));
beq->bevt_9_ta_ph->bem_addValue_1(beq->bevt_12_ta_ph);
} 
 else  {
beq->bevt_13_ta_ph = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString(14, {0x50,0x61,0x79,0x6C,0x6F,0x61,0x64,0x45,0x6D,0x70,0x74,0x79,0x3A,0x3B}))));
beq->bevl_ret->bem_addValue_1(beq->bevt_13_ta_ph);
} 
return beq->bevl_ret;
}
BEC_2_4_6_TextString* BEC_2_8_11_EmbeddedMqttMessage::bem_topicGet_0() {
struct bes {  BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(1);
return bevp_topic;
}
BEC_2_8_11_EmbeddedMqttMessage* BEC_2_8_11_EmbeddedMqttMessage::bem_topicSet_1(BEC_2_6_6_SystemObject* bevt_0_ta_SET) {
struct bes { BEC_2_6_6_SystemObject* bevt_0_ta_SET; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->bevt_0_ta_SET = bevt_0_ta_SET;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(2);
bevp_topic = static_cast<BEC_2_4_6_TextString*>(beq->bevt_0_ta_SET);
return this;
}
BEC_2_4_6_TextString* BEC_2_8_11_EmbeddedMqttMessage::bem_payloadGet_0() {
struct bes {  BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(1);
return bevp_payload;
}
BEC_2_8_11_EmbeddedMqttMessage* BEC_2_8_11_EmbeddedMqttMessage::bem_payloadSet_1(BEC_2_6_6_SystemObject* bevt_0_ta_SET) {
struct bes { BEC_2_6_6_SystemObject* bevt_0_ta_SET; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->bevt_0_ta_SET = bevt_0_ta_SET;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(2);
bevp_payload = static_cast<BEC_2_4_6_TextString*>(beq->bevt_0_ta_SET);
return this;
}
BEC_2_6_6_SystemObject* BEC_2_8_11_EmbeddedMqttMessage::bemd_0(int32_t callId) {
switch (callId) {
case 1080042700: return bem_payloadGet_0();
case -1553512291: return bem_toString_0();
case 1565117901: return bem_topicGet_0();
}
return bevs_super::bemd_0(callId);
}
BEC_2_6_6_SystemObject* BEC_2_8_11_EmbeddedMqttMessage::bemd_1(int32_t callId, BEC_2_6_6_SystemObject* bevd_0) {
switch (callId) {
case 1954628973: return bem_topicSet_1(bevd_0);
case 484691404: return bem_payloadSet_1(bevd_0);
}
return bevs_super::bemd_1(callId, bevd_0);
}
BEC_2_6_6_SystemObject* BEC_2_8_11_EmbeddedMqttMessage::bemd_2(int32_t callId, BEC_2_6_6_SystemObject* bevd_0, BEC_2_6_6_SystemObject* bevd_1) {
switch (callId) {
case 878900077: return bem_new_2(static_cast<BEC_2_4_6_TextString*>(bevd_0), static_cast<BEC_2_4_6_TextString*>(bevd_1));
}
return bevs_super::bemd_2(callId, bevd_0, bevd_1);
}
BEC_2_6_6_SystemObject* BEC_2_8_11_EmbeddedMqttMessage::bemc_create() {
return new BEC_2_8_11_EmbeddedMqttMessage();
}
void BEC_2_8_11_EmbeddedMqttMessage::bemc_setInitial(BEC_2_6_6_SystemObject* becc_inst) {
BEC_2_8_11_EmbeddedMqttMessage::bece_BEC_2_8_11_EmbeddedMqttMessage_bevs_inst = static_cast<BEC_2_8_11_EmbeddedMqttMessage*>(becc_inst);
}
BEC_2_6_6_SystemObject* BEC_2_8_11_EmbeddedMqttMessage::bemc_getInitial() {
return BEC_2_8_11_EmbeddedMqttMessage::bece_BEC_2_8_11_EmbeddedMqttMessage_bevs_inst;
}
void BEC_2_8_11_EmbeddedMqttMessage::bemg_doMark() {
bevg_gcMark = BECS_Runtime::bevg_currentGcMark;
if (bevp_topic != nullptr && bevp_topic->bevg_gcMark != BECS_Runtime::bevg_currentGcMark) {
bevp_topic->bemg_doMark();
}
if (bevp_payload != nullptr && bevp_payload->bevg_gcMark != BECS_Runtime::bevg_currentGcMark) {
bevp_payload->bemg_doMark();
}
}
size_t BEC_2_8_11_EmbeddedMqttMessage::bemg_getSize() {
return sizeof(*this);
}
BETS_Object* BEC_2_8_11_EmbeddedMqttMessage::bemc_getType() {
return &BEC_2_8_11_EmbeddedMqttMessage::bece_BEC_2_8_11_EmbeddedMqttMessage_bevs_type;
}
BET_2_8_6_EmbeddedUpdate::BET_2_8_6_EmbeddedUpdate() {
std::vector<std::string> bevs_mtnames = {  };
bevs_fieldNames = {  };
}
BEC_2_6_6_SystemObject* BET_2_8_6_EmbeddedUpdate::bems_createInstance() {
return new BEC_2_8_6_EmbeddedUpdate();
}
void BET_2_8_6_EmbeddedUpdate::bemgt_doMark() {
BEC_2_6_6_SystemObject* bevsl_inst_ref = *bevs_inst_ref;
if (bevsl_inst_ref != nullptr && bevsl_inst_ref->bevg_gcMark != BECS_Runtime::bevg_currentGcMark) {
bevsl_inst_ref->bemg_doMark();
}
}
BEC_2_8_6_EmbeddedUpdate* BEC_2_8_6_EmbeddedUpdate::bece_BEC_2_8_6_EmbeddedUpdate_bevs_inst;

BET_2_8_6_EmbeddedUpdate BEC_2_8_6_EmbeddedUpdate::bece_BEC_2_8_6_EmbeddedUpdate_bevs_type;
BEC_2_6_6_SystemObject** BET_2_8_6_EmbeddedUpdate::bevs_inst_ref = (BEC_2_6_6_SystemObject**) &BEC_2_8_6_EmbeddedUpdate::bece_BEC_2_8_6_EmbeddedUpdate_bevs_inst;

BEC_2_8_6_EmbeddedUpdate* BEC_2_8_6_EmbeddedUpdate::bem_updateFromUrl_1(BEC_2_4_6_TextString* bevk_url) {
struct bes { BEC_2_4_6_TextString* beva_url; BEC_2_4_3_MathInt* bevl_res; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->beva_url = bevk_url;
beq->bevl_res = nullptr;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(3);
beq->bevl_res = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt())));

     Serial.println("gonna update");
     WiFiClient client;
     t_httpUpdate_return ret = ESPhttpUpdate.update(client, beq->beva_url->bems_toCcString().c_str());
     Serial.println("return ret");
     Serial.println(ESPhttpUpdate.getLastError());
     Serial.println(ESPhttpUpdate.getLastErrorString());
     return this;
}
BEC_2_6_6_SystemObject* BEC_2_8_6_EmbeddedUpdate::bemd_1(int32_t callId, BEC_2_6_6_SystemObject* bevd_0) {
switch (callId) {
case -696671066: return bem_updateFromUrl_1(static_cast<BEC_2_4_6_TextString*>(bevd_0));
}
return bevs_super::bemd_1(callId, bevd_0);
}
BEC_2_6_6_SystemObject* BEC_2_8_6_EmbeddedUpdate::bemc_create() {
return new BEC_2_8_6_EmbeddedUpdate();
}
void BEC_2_8_6_EmbeddedUpdate::bemc_setInitial(BEC_2_6_6_SystemObject* becc_inst) {
BEC_2_8_6_EmbeddedUpdate::bece_BEC_2_8_6_EmbeddedUpdate_bevs_inst = static_cast<BEC_2_8_6_EmbeddedUpdate*>(becc_inst);
}
BEC_2_6_6_SystemObject* BEC_2_8_6_EmbeddedUpdate::bemc_getInitial() {
return BEC_2_8_6_EmbeddedUpdate::bece_BEC_2_8_6_EmbeddedUpdate_bevs_inst;
}
void BEC_2_8_6_EmbeddedUpdate::bemg_doMark() {
bevg_gcMark = BECS_Runtime::bevg_currentGcMark;
}
size_t BEC_2_8_6_EmbeddedUpdate::bemg_getSize() {
return sizeof(*this);
}
BETS_Object* BEC_2_8_6_EmbeddedUpdate::bemc_getType() {
return &BEC_2_8_6_EmbeddedUpdate::bece_BEC_2_8_6_EmbeddedUpdate_bevs_type;
}
BET_2_8_8_EmbeddedAppShell::BET_2_8_8_EmbeddedAppShell() {
std::vector<std::string> bevs_mtnames = {  };
bevs_fieldNames = {  };
}
BEC_2_6_6_SystemObject* BET_2_8_8_EmbeddedAppShell::bems_createInstance() {
return new BEC_2_8_8_EmbeddedAppShell();
}
void BET_2_8_8_EmbeddedAppShell::bemgt_doMark() {
BEC_2_6_6_SystemObject* bevsl_inst_ref = *bevs_inst_ref;
if (bevsl_inst_ref != nullptr && bevsl_inst_ref->bevg_gcMark != BECS_Runtime::bevg_currentGcMark) {
bevsl_inst_ref->bemg_doMark();
}
}
BEC_2_8_8_EmbeddedAppShell* BEC_2_8_8_EmbeddedAppShell::bece_BEC_2_8_8_EmbeddedAppShell_bevs_inst;

BET_2_8_8_EmbeddedAppShell BEC_2_8_8_EmbeddedAppShell::bece_BEC_2_8_8_EmbeddedAppShell_bevs_type;
BEC_2_6_6_SystemObject** BET_2_8_8_EmbeddedAppShell::bevs_inst_ref = (BEC_2_6_6_SystemObject**) &BEC_2_8_8_EmbeddedAppShell::bece_BEC_2_8_8_EmbeddedAppShell_bevs_inst;

BEC_2_8_8_EmbeddedAppShell* BEC_2_8_8_EmbeddedAppShell::bem_main_0() {
struct bes { BEC_2_4_6_TextString* bevt_0_ta_ph; BEC_2_4_6_TextString* bevt_1_ta_ph; BEC_2_4_6_TextString* bevt_2_ta_ph; BEC_2_4_6_TextString* bevt_3_ta_ph; BEC_2_4_6_TextString* bevt_4_ta_ph; BEC_2_4_6_TextString* bevt_5_ta_ph; BEC_2_4_6_TextString* bevt_6_ta_ph; BEC_2_4_3_MathInt* bevt_7_ta_ph; BEC_2_4_3_MathInt* bevt_8_ta_ph; BEC_2_4_3_MathInt* bevt_9_ta_ph; BEC_2_4_3_MathInt* bevt_10_ta_ph; BEC_2_4_3_MathInt* bevt_11_ta_ph; BEC_2_4_3_MathInt* bevt_12_ta_ph; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->bevt_0_ta_ph = nullptr;
beq->bevt_1_ta_ph = nullptr;
beq->bevt_2_ta_ph = nullptr;
beq->bevt_3_ta_ph = nullptr;
beq->bevt_4_ta_ph = nullptr;
beq->bevt_5_ta_ph = nullptr;
beq->bevt_6_ta_ph = nullptr;
beq->bevt_7_ta_ph = nullptr;
beq->bevt_8_ta_ph = nullptr;
beq->bevt_9_ta_ph = nullptr;
beq->bevt_10_ta_ph = nullptr;
beq->bevt_11_ta_ph = nullptr;
beq->bevt_12_ta_ph = nullptr;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(14);
bevp_app = static_cast<BEC_2_8_3_EmbeddedApp*>(BEC_2_8_3_EmbeddedApp::bece_BEC_2_8_3_EmbeddedApp_bevs_inst);
bevp_config = static_cast<BEC_2_8_6_EmbeddedConfig*>(((BEC_2_8_6_EmbeddedConfig*) (new BEC_2_8_6_EmbeddedConfig()))->bem_new_0());
bevp_nowup = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt())));
bevp_needsStateUp = static_cast<BEC_2_5_4_LogicBool*>(BECS_Runtime::boolFalse);
bevp_needsStateUpSoon = static_cast<BEC_2_5_4_LogicBool*>(BECS_Runtime::boolFalse);
bevp_controls = static_cast<BEC_2_9_4_ContainerList*>(((BEC_2_9_4_ContainerList*) (new BEC_2_9_4_ContainerList()))->bem_new_0());
bevp_loopers = static_cast<BEC_2_9_4_ContainerList*>(((BEC_2_9_4_ContainerList*) (new BEC_2_9_4_ContainerList()))->bem_new_0());
bevp_zero = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(0))));
bevp_nextUpdateCheck = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(0))));
bevp_nextMq = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(0))));
bevp_nextSwInfo = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(0))));
bevp_nextRestart = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(0))));
bevp_nextMaybeSave = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(0))));
bevp_nextApCheck = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(0))));
bevp_nextWifiCheck = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(0))));
bevp_slashn = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString(1, {0x0A}))));
bevp_slashr = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString(1, {0x0D}))));
bevp_fcdot = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString(3, {0x66,0x63,0x2E}))));
bevp_needsFsRestart = static_cast<BEC_2_5_4_LogicBool*>(BECS_Runtime::boolFalse);
bevp_needsRestart = static_cast<BEC_2_5_4_LogicBool*>(BECS_Runtime::boolFalse);
bevp_readBuf = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString()))->bem_new_0());
bevp_needsNetworkInit = static_cast<BEC_2_5_4_LogicBool*>(BECS_Runtime::boolTrue);
bevp_readyForAp = static_cast<BEC_2_5_4_LogicBool*>(BECS_Runtime::boolFalse);
bevp_needsBuildControls = static_cast<BEC_2_5_4_LogicBool*>(BECS_Runtime::boolTrue);
bevp_needsInitControls = static_cast<BEC_2_5_4_LogicBool*>(BECS_Runtime::boolTrue);
bevp_needsGc = static_cast<BEC_2_5_4_LogicBool*>(BECS_Runtime::boolFalse);
bevp_needsMqConfUp = static_cast<BEC_2_5_4_LogicBool*>(BECS_Runtime::boolFalse);
bevp_looperI = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt())));
bevp_app->bem_pluginSet_1(this);
beq->bevt_0_ta_ph = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString(14, {0x6C,0x6F,0x61,0x64,0x69,0x6E,0x67,0x20,0x63,0x6F,0x6E,0x66,0x69,0x67}))));
beq->bevt_0_ta_ph->bem_print_0();
bevp_config->bem_load_0();
beq->bevt_1_ta_ph = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString(6, {0x73,0x68,0x2E,0x70,0x69,0x6E}))));
bevp_shpini = static_cast<BEC_2_4_3_MathInt*>(bevp_config->bem_getPos_1(beq->bevt_1_ta_ph));
beq->bevt_2_ta_ph = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString(7, {0x73,0x68,0x2E,0x70,0x61,0x73,0x73}))));
bevp_shpassi = static_cast<BEC_2_4_3_MathInt*>(bevp_config->bem_getPos_1(beq->bevt_2_ta_ph));
beq->bevt_3_ta_ph = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString(8, {0x73,0x68,0x2E,0x73,0x70,0x61,0x73,0x73}))));
bevp_shspassi = static_cast<BEC_2_4_3_MathInt*>(bevp_config->bem_getPos_1(beq->bevt_3_ta_ph));
beq->bevt_4_ta_ph = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString(7, {0x73,0x68,0x2E,0x73,0x73,0x69,0x64}))));
bevp_shssidi = static_cast<BEC_2_4_3_MathInt*>(bevp_config->bem_getPos_1(beq->bevt_4_ta_ph));
beq->bevt_5_ta_ph = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString(6, {0x73,0x68,0x2E,0x73,0x65,0x63}))));
bevp_shseci = static_cast<BEC_2_4_3_MathInt*>(bevp_config->bem_getPos_1(beq->bevt_5_ta_ph));
beq->bevt_6_ta_ph = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString(6, {0x73,0x68,0x2E,0x64,0x69,0x64}))));
bevp_shdidi = static_cast<BEC_2_4_3_MathInt*>(bevp_config->bem_getPos_1(beq->bevt_6_ta_ph));
bevp_app->bem_uptime_1(bevp_nowup);
beq->bevt_7_ta_ph = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(60000))));
bevp_nextUpdateCheck = bevp_nowup->bem_add_1(beq->bevt_7_ta_ph);
beq->bevt_8_ta_ph = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(11000))));
bevp_nextMq = bevp_nowup->bem_add_1(beq->bevt_8_ta_ph);
beq->bevt_9_ta_ph = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(540000))));
bevp_nextSwInfo = bevp_nowup->bem_add_1(beq->bevt_9_ta_ph);
beq->bevt_10_ta_ph = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(45000))));
bevp_nextMaybeSave = bevp_nowup->bem_add_1(beq->bevt_10_ta_ph);
beq->bevt_11_ta_ph = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(240000))));
bevp_nextApCheck = bevp_nowup->bem_add_1(beq->bevt_11_ta_ph);
beq->bevt_12_ta_ph = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(300000))));
bevp_nextWifiCheck = bevp_nowup->bem_add_1(beq->bevt_12_ta_ph);
return this;
}
BEC_2_8_8_EmbeddedAppShell* BEC_2_8_8_EmbeddedAppShell::bem_sendWebPage_1(BEC_2_6_6_SystemObject* bevk_treq) {
struct bes { BEC_2_6_6_SystemObject* beva_treq; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->beva_treq = bevk_treq;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(2);
return this;
}
BEC_2_8_8_EmbeddedAppShell* BEC_2_8_8_EmbeddedAppShell::bem_initControls_0() {
struct bes { BEC_2_6_6_SystemObject* bevl_control; BEC_2_6_6_SystemObject* bevt_0_ta_loop; BEC_2_6_6_SystemObject* bevt_1_ta_ph; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->bevl_control = nullptr;
beq->bevt_0_ta_loop = nullptr;
beq->bevt_1_ta_ph = nullptr;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(4);
beq->bevt_0_ta_loop = bevp_controls->bem_iteratorGet_0();
while (true)
 {
beq->bevt_1_ta_ph = beq->bevt_0_ta_loop->bemd_0(448214784);
if ((static_cast<BEC_2_5_4_LogicBool*>(beq->bevt_1_ta_ph))->bevi_bool) {
beq->bevl_control = beq->bevt_0_ta_loop->bemd_0(-119099042);
beq->bevl_control->bemd_0(-1469083060);
} 
 else  {
break;
} 
} 
return this;
}
BEC_2_4_6_TextString* BEC_2_8_8_EmbeddedAppShell::bem_doState_1(BEC_2_9_4_ContainerList* bevk_cmdl) {
struct bes { BEC_2_9_4_ContainerList* beva_cmdl; BEC_2_4_3_MathInt* bevl_ctlPos; BEC_2_6_6_SystemObject* bevt_0_ta_ph; BEC_2_4_3_MathInt* bevt_1_ta_ph; BEC_2_6_6_SystemObject* bevt_2_ta_ph; BEC_2_6_6_SystemObject* bevt_3_ta_ph; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->beva_cmdl = bevk_cmdl;
beq->bevl_ctlPos = nullptr;
beq->bevt_0_ta_ph = nullptr;
beq->bevt_1_ta_ph = nullptr;
beq->bevt_2_ta_ph = nullptr;
beq->bevt_3_ta_ph = nullptr;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(7);
beq->bevt_1_ta_ph = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(2))));
beq->bevt_0_ta_ph = beq->beva_cmdl->bem_get_1(beq->bevt_1_ta_ph);
beq->bevl_ctlPos = bevp_app->bem_strToInt_1(static_cast<BEC_2_4_6_TextString*>(beq->bevt_0_ta_ph) );
beq->bevt_3_ta_ph = bevp_controls->bem_get_1(beq->bevl_ctlPos);
beq->bevt_2_ta_ph = beq->bevt_3_ta_ph->bemd_1(472494009, beq->beva_cmdl);
return static_cast<BEC_2_4_6_TextString*>(beq->bevt_2_ta_ph);
}
BEC_2_4_6_TextString* BEC_2_8_8_EmbeddedAppShell::bem_getLastEvents_1(BEC_2_9_4_ContainerList* bevk_cmdl) {
struct bes { BEC_2_9_4_ContainerList* beva_cmdl; BEC_2_4_6_TextString* bevl_les; BEC_2_4_6_TextString* bevl_d; BEC_2_4_6_TextString* bevl_cd; BEC_2_6_6_SystemObject* bevl_control; BEC_2_4_6_TextString* bevl_conName; BEC_2_4_3_MathInt* bevl_le; BEC_2_4_3_MathInt* bevl_conPos; BEC_2_6_6_SystemObject* bevt_0_ta_loop; BEC_2_5_4_LogicBool* bevt_1_ta_anchor; BEC_2_5_4_LogicBool* bevt_2_ta_ph; BEC_2_5_4_LogicBool* bevt_3_ta_ph; BEC_2_4_7_TextStrings* bevt_4_ta_ph; BEC_2_6_6_SystemObject* bevt_5_ta_ph; BEC_2_5_4_LogicBool* bevt_6_ta_ph; BEC_2_5_4_LogicBool* bevt_7_ta_ph; BEC_2_4_6_TextString* bevt_8_ta_ph; BEC_2_4_6_TextString* bevt_9_ta_ph; BEC_2_4_6_TextString* bevt_10_ta_ph; BEC_2_4_6_TextString* bevt_11_ta_ph; BEC_2_4_6_TextString* bevt_12_ta_ph; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->beva_cmdl = bevk_cmdl;
beq->bevl_les = nullptr;
beq->bevl_d = nullptr;
beq->bevl_cd = nullptr;
beq->bevl_control = nullptr;
beq->bevl_conName = nullptr;
beq->bevl_le = nullptr;
beq->bevl_conPos = nullptr;
beq->bevt_0_ta_loop = nullptr;
beq->bevt_1_ta_anchor = nullptr;
beq->bevt_2_ta_ph = nullptr;
beq->bevt_3_ta_ph = nullptr;
beq->bevt_4_ta_ph = nullptr;
beq->bevt_5_ta_ph = nullptr;
beq->bevt_6_ta_ph = nullptr;
beq->bevt_7_ta_ph = nullptr;
beq->bevt_8_ta_ph = nullptr;
beq->bevt_9_ta_ph = nullptr;
beq->bevt_10_ta_ph = nullptr;
beq->bevt_11_ta_ph = nullptr;
beq->bevt_12_ta_ph = nullptr;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(22);
if (bevp_lastEventsRes == nullptr) {
beq->bevt_2_ta_ph = BECS_Runtime::boolFalse;
 } else { 
beq->bevt_2_ta_ph = BECS_Runtime::boolTrue;
}
if (beq->bevt_2_ta_ph->bevi_bool) {
return bevp_lastEventsRes;
} 
beq->bevl_les = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString()))->bem_new_0());
beq->bevt_4_ta_ph = static_cast<BEC_2_4_7_TextStrings*>(BEC_2_4_7_TextStrings::bece_BEC_2_4_7_TextStrings_bevs_inst);
beq->bevt_3_ta_ph = beq->bevt_4_ta_ph->bem_notEmpty_1(bevp_did);
if (beq->bevt_3_ta_ph->bevi_bool) {
beq->bevl_d = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString(1, {0x2C}))));
beq->bevl_cd = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString(1, {0x3B}))));
beq->bevt_0_ta_loop = bevp_controls->bem_iteratorGet_0();
while (true)
 {
beq->bevt_5_ta_ph = beq->bevt_0_ta_loop->bemd_0(448214784);
if ((static_cast<BEC_2_5_4_LogicBool*>(beq->bevt_5_ta_ph))->bevi_bool) {
beq->bevl_control = beq->bevt_0_ta_loop->bemd_0(-119099042);
beq->bevl_conName = static_cast<BEC_2_4_6_TextString*>(beq->bevl_control->bemd_0(1530937685));
beq->bevl_le = static_cast<BEC_2_4_3_MathInt*>(beq->bevl_control->bemd_0(315366234));
beq->bevl_conPos = static_cast<BEC_2_4_3_MathInt*>(beq->bevl_control->bemd_0(355723905));
if (beq->bevl_le == nullptr) {
beq->bevt_6_ta_ph = BECS_Runtime::boolFalse;
 } else { 
beq->bevt_6_ta_ph = BECS_Runtime::boolTrue;
}
if (beq->bevt_6_ta_ph->bevi_bool) {
if (beq->bevl_conPos == nullptr) {
beq->bevt_7_ta_ph = BECS_Runtime::boolFalse;
 } else { 
beq->bevt_7_ta_ph = BECS_Runtime::boolTrue;
}
if (beq->bevt_7_ta_ph->bevi_bool) {
beq->bevt_1_ta_anchor = BECS_Runtime::boolTrue;
} 
 else  {
beq->bevt_1_ta_anchor = BECS_Runtime::boolFalse;
} 
} 
 else  {
beq->bevt_1_ta_anchor = BECS_Runtime::boolFalse;
} 
if (beq->bevt_1_ta_anchor->bevi_bool) {
beq->bevt_12_ta_ph = static_cast<BEC_2_4_6_TextString*>(beq->bevl_les->bem_addValue_1(beq->bevl_conName));
beq->bevt_11_ta_ph = static_cast<BEC_2_4_6_TextString*>(beq->bevt_12_ta_ph->bem_addValue_1(beq->bevl_d));
beq->bevt_10_ta_ph = static_cast<BEC_2_4_6_TextString*>(beq->bevt_11_ta_ph->bem_addValue_1(beq->bevl_conPos));
beq->bevt_9_ta_ph = static_cast<BEC_2_4_6_TextString*>(beq->bevt_10_ta_ph->bem_addValue_1(beq->bevl_d));
beq->bevt_8_ta_ph = static_cast<BEC_2_4_6_TextString*>(beq->bevt_9_ta_ph->bem_addValue_1(beq->bevl_le));
beq->bevt_8_ta_ph->bem_addValue_1(beq->bevl_cd);
} 
} 
 else  {
break;
} 
} 
} 
bevp_lastEventsRes = beq->bevl_les;
return beq->bevl_les;
}
BEC_2_8_8_EmbeddedAppShell* BEC_2_8_8_EmbeddedAppShell::bem_clearStates_0() {
struct bes { BEC_2_6_6_SystemObject* bevl_control; BEC_2_6_6_SystemObject* bevt_0_ta_loop; BEC_2_6_6_SystemObject* bevt_1_ta_ph; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->bevl_control = nullptr;
beq->bevt_0_ta_loop = nullptr;
beq->bevt_1_ta_ph = nullptr;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(4);
beq->bevt_0_ta_loop = bevp_controls->bem_iteratorGet_0();
while (true)
 {
beq->bevt_1_ta_ph = beq->bevt_0_ta_loop->bemd_0(448214784);
if ((static_cast<BEC_2_5_4_LogicBool*>(beq->bevt_1_ta_ph))->bevi_bool) {
beq->bevl_control = beq->bevt_0_ta_loop->bemd_0(-119099042);
beq->bevl_control->bemd_0(-1592447609);
} 
 else  {
break;
} 
} 
return this;
}
BEC_2_8_8_EmbeddedAppShell* BEC_2_8_8_EmbeddedAppShell::bem_checkMakeIds_0() {
struct bes { BEC_2_4_6_TextString* bevl_pinpart; BEC_2_5_4_LogicBool* bevt_0_ta_anchor; BEC_2_5_4_LogicBool* bevt_1_ta_ph; BEC_2_4_7_TextStrings* bevt_2_ta_ph; BEC_2_5_4_LogicBool* bevt_3_ta_ph; BEC_2_4_3_MathInt* bevt_4_ta_ph; BEC_2_4_3_MathInt* bevt_5_ta_ph; BEC_2_4_6_TextString* bevt_6_ta_ph; BEC_2_6_6_SystemRandom* bevt_7_ta_ph; BEC_2_4_3_MathInt* bevt_8_ta_ph; BEC_2_5_4_LogicBool* bevt_9_ta_ph; BEC_2_4_7_TextStrings* bevt_10_ta_ph; BEC_2_4_6_TextString* bevt_11_ta_ph; BEC_2_6_6_SystemRandom* bevt_12_ta_ph; BEC_2_4_3_MathInt* bevt_13_ta_ph; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->bevl_pinpart = nullptr;
beq->bevt_0_ta_anchor = nullptr;
beq->bevt_1_ta_ph = nullptr;
beq->bevt_2_ta_ph = nullptr;
beq->bevt_3_ta_ph = nullptr;
beq->bevt_4_ta_ph = nullptr;
beq->bevt_5_ta_ph = nullptr;
beq->bevt_6_ta_ph = nullptr;
beq->bevt_7_ta_ph = nullptr;
beq->bevt_8_ta_ph = nullptr;
beq->bevt_9_ta_ph = nullptr;
beq->bevt_10_ta_ph = nullptr;
beq->bevt_11_ta_ph = nullptr;
beq->bevt_12_ta_ph = nullptr;
beq->bevt_13_ta_ph = nullptr;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(16);
bevp_pin = bevp_config->bem_get_1(bevp_shpini);
beq->bevt_2_ta_ph = static_cast<BEC_2_4_7_TextStrings*>(BEC_2_4_7_TextStrings::bece_BEC_2_4_7_TextStrings_bevs_inst);
beq->bevt_1_ta_ph = beq->bevt_2_ta_ph->bem_isEmpty_1(bevp_pin);
if (beq->bevt_1_ta_ph->bevi_bool) {
beq->bevt_0_ta_anchor = BECS_Runtime::boolTrue;
} 
 else  {
beq->bevt_4_ta_ph = bevp_pin->bem_sizeGet_0();
beq->bevt_5_ta_ph = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(16))));
if (beq->bevt_4_ta_ph->bevi_int != beq->bevt_5_ta_ph->bevi_int) {
beq->bevt_3_ta_ph = BECS_Runtime::boolTrue;
 } else { 
beq->bevt_3_ta_ph = BECS_Runtime::boolFalse;
}
if (beq->bevt_3_ta_ph->bevi_bool) {
beq->bevt_0_ta_anchor = BECS_Runtime::boolTrue;
} 
 else  {
beq->bevt_0_ta_anchor = BECS_Runtime::boolFalse;
} 
} 
if (beq->bevt_0_ta_anchor->bevi_bool) {
beq->bevt_7_ta_ph = static_cast<BEC_2_6_6_SystemRandom*>(BEC_2_6_6_SystemRandom::bece_BEC_2_6_6_SystemRandom_bevs_inst);
beq->bevt_8_ta_ph = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(8))));
beq->bevt_6_ta_ph = beq->bevt_7_ta_ph->bem_getString_1(beq->bevt_8_ta_ph);
beq->bevl_pinpart = static_cast<BEC_2_4_6_TextString*>(beq->bevt_6_ta_ph->bem_lowerValue_0());
bevp_pin = beq->bevl_pinpart->bem_add_1(beq->bevl_pinpart);
bevp_config->bem_put_2(bevp_shpini, bevp_pin);
} 
bevp_did = bevp_config->bem_get_1(bevp_shdidi);
beq->bevt_10_ta_ph = static_cast<BEC_2_4_7_TextStrings*>(BEC_2_4_7_TextStrings::bece_BEC_2_4_7_TextStrings_bevs_inst);
beq->bevt_9_ta_ph = beq->bevt_10_ta_ph->bem_isEmpty_1(bevp_did);
if (beq->bevt_9_ta_ph->bevi_bool) {
beq->bevt_12_ta_ph = static_cast<BEC_2_6_6_SystemRandom*>(BEC_2_6_6_SystemRandom::bece_BEC_2_6_6_SystemRandom_bevs_inst);
beq->bevt_13_ta_ph = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(16))));
beq->bevt_11_ta_ph = beq->bevt_12_ta_ph->bem_getString_1(beq->bevt_13_ta_ph);
bevp_did = static_cast<BEC_2_4_6_TextString*>(beq->bevt_11_ta_ph->bem_lowerValue_0());
bevp_config->bem_put_2(bevp_shdidi, bevp_did);
} 
return this;
}
BEC_2_8_8_EmbeddedAppShell* BEC_2_8_8_EmbeddedAppShell::bem_loadPasses_0() {
struct bes {  BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(1);
bevp_pass = bevp_config->bem_get_1(bevp_shpassi);
bevp_spass = bevp_config->bem_get_1(bevp_shspassi);
return this;
}
BEC_2_8_8_EmbeddedAppShell* BEC_2_8_8_EmbeddedAppShell::bem_buildSwInfoIn_0() {
struct bes { BEC_2_9_4_ContainerList* bevl_swl; BEC_2_5_4_LogicBool* bevt_0_ta_ph; BEC_2_4_7_TextStrings* bevt_1_ta_ph; BEC_2_4_6_TextString* bevt_2_ta_ph; BEC_2_4_3_MathInt* bevt_3_ta_ph; BEC_2_6_6_SystemObject* bevt_4_ta_ph; BEC_2_4_3_MathInt* bevt_5_ta_ph; BEC_2_4_6_TextString* bevt_6_ta_ph; BEC_2_4_6_TextString* bevt_7_ta_ph; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->bevl_swl = nullptr;
beq->bevt_0_ta_ph = nullptr;
beq->bevt_1_ta_ph = nullptr;
beq->bevt_2_ta_ph = nullptr;
beq->bevt_3_ta_ph = nullptr;
beq->bevt_4_ta_ph = nullptr;
beq->bevt_5_ta_ph = nullptr;
beq->bevt_6_ta_ph = nullptr;
beq->bevt_7_ta_ph = nullptr;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(10);
beq->bevt_1_ta_ph = static_cast<BEC_2_4_7_TextStrings*>(BEC_2_4_7_TextStrings::bece_BEC_2_4_7_TextStrings_bevs_inst);
beq->bevt_0_ta_ph = beq->bevt_1_ta_ph->bem_isEmpty_1(bevp_swSpec);
if (beq->bevt_0_ta_ph->bevi_bool) {
bevp_swSpec = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString(7, {0x30,0x2E,0x67,0x73,0x68,0x2E,0x34}))));
} 
beq->bevt_2_ta_ph = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString(1, {0x2E}))));
beq->bevl_swl = bevp_swSpec->bem_split_1(beq->bevt_2_ta_ph);
beq->bevt_3_ta_ph = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(1))));
bevp_devCode = static_cast<BEC_2_4_6_TextString*>(beq->bevl_swl->bem_get_1(beq->bevt_3_ta_ph));
beq->bevt_5_ta_ph = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(2))));
beq->bevt_4_ta_ph = beq->bevl_swl->bem_get_1(beq->bevt_5_ta_ph);
bevp_version = bevp_app->bem_strToInt_1(static_cast<BEC_2_4_6_TextString*>(beq->bevt_4_ta_ph) );
beq->bevt_7_ta_ph = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString(1, {0x20}))));
beq->bevt_6_ta_ph = bevp_devCode->bem_add_1(beq->bevt_7_ta_ph);
bevp_swInfo = beq->bevt_6_ta_ph->bem_add_1(bevp_version);
return this;
}
BEC_2_8_8_EmbeddedAppShell* BEC_2_8_8_EmbeddedAppShell::bem_buildSwInfo_0() {
struct bes { BEC_2_5_4_LogicBool* bevt_0_ta_ph; BEC_2_4_7_TextStrings* bevt_1_ta_ph; BEC_2_6_6_SystemObject* bevt_2_ta_ph; BEC_2_4_6_TextString* bevt_3_ta_ph; BEC_2_5_4_LogicBool* bevt_4_ta_ph; BEC_2_4_7_TextStrings* bevt_5_ta_ph; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->bevt_0_ta_ph = nullptr;
beq->bevt_1_ta_ph = nullptr;
beq->bevt_2_ta_ph = nullptr;
beq->bevt_3_ta_ph = nullptr;
beq->bevt_4_ta_ph = nullptr;
beq->bevt_5_ta_ph = nullptr;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(7);
beq->bevt_1_ta_ph = static_cast<BEC_2_4_7_TextStrings*>(BEC_2_4_7_TextStrings::bece_BEC_2_4_7_TextStrings_bevs_inst);
beq->bevt_0_ta_ph = beq->bevt_1_ta_ph->bem_isEmpty_1(bevp_swSpec);
if (beq->bevt_0_ta_ph->bevi_bool) {
beq->bevt_3_ta_ph = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString(6, {0x73,0x77,0x73,0x70,0x65,0x63}))));
beq->bevt_2_ta_ph = bevp_config->bem_getPos_1(beq->bevt_3_ta_ph);
bevp_swSpec = bevp_config->bem_get_1(static_cast<BEC_2_4_3_MathInt*>(beq->bevt_2_ta_ph) );
beq->bevt_5_ta_ph = static_cast<BEC_2_4_7_TextStrings*>(BEC_2_4_7_TextStrings::bece_BEC_2_4_7_TextStrings_bevs_inst);
beq->bevt_4_ta_ph = beq->bevt_5_ta_ph->bem_isEmpty_1(bevp_swSpec);
if (beq->bevt_4_ta_ph->bevi_bool) {

          std::string swspec = BESPEC_SW;
          bevp_swSpec = new BEC_2_4_6_TextString(swspec);
          } 
} 
bem_buildSwInfoIn_0();
return this;
}
BEC_2_6_6_SystemObject* BEC_2_8_8_EmbeddedAppShell::bem_buildControl_3(BEC_2_4_3_MathInt* bevk_conPos, BEC_2_4_6_TextString* bevk_conName, BEC_2_4_6_TextString* bevk_conArgs) {
struct bes { BEC_2_4_3_MathInt* beva_conPos; BEC_2_4_6_TextString* beva_conName; BEC_2_4_6_TextString* beva_conArgs; BEC_2_4_6_TextString* bevt_0_ta_ph; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->beva_conPos = bevk_conPos;
beq->beva_conName = bevk_conName;
beq->beva_conArgs = bevk_conArgs;
beq->bevt_0_ta_ph = nullptr;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(5);
beq->bevt_0_ta_ph = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString(25, {0x62,0x75,0x69,0x6C,0x64,0x43,0x6F,0x6E,0x74,0x72,0x6F,0x6C,0x20,0x63,0x61,0x6C,0x6C,0x65,0x64,0x20,0x69,0x6E,0x20,0x53,0x48}))));
beq->bevt_0_ta_ph->bem_print_0();
return nullptr;
}
BEC_2_8_8_EmbeddedAppShell* BEC_2_8_8_EmbeddedAppShell::bem_buildControlsIn_0() {
struct bes { BEC_2_9_4_ContainerList* bevl_conl; BEC_2_4_3_MathInt* bevl_i; BEC_2_4_3_MathInt* bevl_conPos; BEC_2_4_6_TextString* bevl_conName; BEC_2_4_6_TextString* bevl_conArgs; BEC_2_5_4_LogicBool* bevt_0_ta_ph; BEC_2_4_7_TextStrings* bevt_1_ta_ph; BEC_2_4_6_TextString* bevt_2_ta_ph; BEC_2_5_4_LogicBool* bevt_3_ta_ph; BEC_2_4_3_MathInt* bevt_4_ta_ph; BEC_2_5_4_LogicBool* bevt_5_ta_ph; BEC_2_4_3_MathInt* bevt_6_ta_ph; BEC_2_4_6_TextString* bevt_7_ta_ph; BEC_2_6_6_SystemObject* bevt_8_ta_ph; BEC_2_4_6_TextString* bevt_9_ta_ph; BEC_2_4_6_TextString* bevt_10_ta_ph; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->bevl_conl = nullptr;
beq->bevl_i = nullptr;
beq->bevl_conPos = nullptr;
beq->bevl_conName = nullptr;
beq->bevl_conArgs = nullptr;
beq->bevt_0_ta_ph = nullptr;
beq->bevt_1_ta_ph = nullptr;
beq->bevt_2_ta_ph = nullptr;
beq->bevt_3_ta_ph = nullptr;
beq->bevt_4_ta_ph = nullptr;
beq->bevt_5_ta_ph = nullptr;
beq->bevt_6_ta_ph = nullptr;
beq->bevt_7_ta_ph = nullptr;
beq->bevt_8_ta_ph = nullptr;
beq->bevt_9_ta_ph = nullptr;
beq->bevt_10_ta_ph = nullptr;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(17);
beq->bevt_1_ta_ph = static_cast<BEC_2_4_7_TextStrings*>(BEC_2_4_7_TextStrings::bece_BEC_2_4_7_TextStrings_bevs_inst);
beq->bevt_0_ta_ph = beq->bevt_1_ta_ph->bem_isEmpty_1(bevp_controlSpec);
if (beq->bevt_0_ta_ph->bevi_bool) {
bevp_controlSpec = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString(0, {}))));
} 
bevp_controlDef = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString(11, {0x63,0x6F,0x6E,0x74,0x72,0x6F,0x6C,0x64,0x65,0x66,0x2C}))));
beq->bevt_2_ta_ph = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString(1, {0x2E}))));
beq->bevl_conl = bevp_controlSpec->bem_split_1(beq->bevt_2_ta_ph);
beq->bevl_i = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(1))));
beq->bevl_conPos = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(0))));
while (true)
 {
beq->bevt_4_ta_ph = beq->bevl_conl->bem_sizeGet_0();
if (beq->bevl_i->bevi_int < beq->bevt_4_ta_ph->bevi_int) {
beq->bevt_3_ta_ph = BECS_Runtime::boolTrue;
 } else { 
beq->bevt_3_ta_ph = BECS_Runtime::boolFalse;
}
if (beq->bevt_3_ta_ph->bevi_bool) {
beq->bevt_6_ta_ph = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(0))));
if (beq->bevl_conPos->bevi_int > beq->bevt_6_ta_ph->bevi_int) {
beq->bevt_5_ta_ph = BECS_Runtime::boolTrue;
 } else { 
beq->bevt_5_ta_ph = BECS_Runtime::boolFalse;
}
if (beq->bevt_5_ta_ph->bevi_bool) {
beq->bevt_7_ta_ph = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString(1, {0x2C}))));
bevp_controlDef->bem_addValue_1(beq->bevt_7_ta_ph);
} 
beq->bevl_conName = static_cast<BEC_2_4_6_TextString*>(beq->bevl_conl->bem_get_1(beq->bevl_i));
bevp_controlDef->bem_addValue_1(beq->bevl_conName);
beq->bevl_i->bevi_int++;
beq->bevl_conArgs = static_cast<BEC_2_4_6_TextString*>(beq->bevl_conl->bem_get_1(beq->bevl_i));
beq->bevt_8_ta_ph = bem_buildControl_3(beq->bevl_conPos, beq->bevl_conName, beq->bevl_conArgs);
bevp_controls->bem_put_2(beq->bevl_conPos, beq->bevt_8_ta_ph);
beq->bevl_conPos = beq->bevl_conPos->bem_increment_0();
beq->bevl_i->bevi_int++;
} 
 else  {
break;
} 
} 
beq->bevt_10_ta_ph = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString(11, {0x63,0x6F,0x6E,0x74,0x72,0x6F,0x6C,0x44,0x65,0x66,0x20}))));
beq->bevt_9_ta_ph = beq->bevt_10_ta_ph->bem_add_1(bevp_controlDef);
beq->bevt_9_ta_ph->bem_print_0();
return this;
}
BEC_2_8_8_EmbeddedAppShell* BEC_2_8_8_EmbeddedAppShell::bem_buildControls_0() {
struct bes { BEC_2_5_4_LogicBool* bevt_0_ta_ph; BEC_2_4_7_TextStrings* bevt_1_ta_ph; BEC_2_6_6_SystemObject* bevt_2_ta_ph; BEC_2_4_6_TextString* bevt_3_ta_ph; BEC_2_5_4_LogicBool* bevt_4_ta_ph; BEC_2_4_7_TextStrings* bevt_5_ta_ph; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->bevt_0_ta_ph = nullptr;
beq->bevt_1_ta_ph = nullptr;
beq->bevt_2_ta_ph = nullptr;
beq->bevt_3_ta_ph = nullptr;
beq->bevt_4_ta_ph = nullptr;
beq->bevt_5_ta_ph = nullptr;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(7);
beq->bevt_1_ta_ph = static_cast<BEC_2_4_7_TextStrings*>(BEC_2_4_7_TextStrings::bece_BEC_2_4_7_TextStrings_bevs_inst);
beq->bevt_0_ta_ph = beq->bevt_1_ta_ph->bem_isEmpty_1(bevp_controlSpec);
if (beq->bevt_0_ta_ph->bevi_bool) {
beq->bevt_3_ta_ph = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString(7, {0x63,0x6F,0x6E,0x73,0x70,0x65,0x63}))));
beq->bevt_2_ta_ph = bevp_config->bem_getPos_1(beq->bevt_3_ta_ph);
bevp_controlSpec = bevp_config->bem_get_1(static_cast<BEC_2_4_3_MathInt*>(beq->bevt_2_ta_ph) );
beq->bevt_5_ta_ph = static_cast<BEC_2_4_7_TextStrings*>(BEC_2_4_7_TextStrings::bece_BEC_2_4_7_TextStrings_bevs_inst);
beq->bevt_4_ta_ph = beq->bevt_5_ta_ph->bem_isEmpty_1(bevp_controlSpec);
if (beq->bevt_4_ta_ph->bevi_bool) {

          std::string conspec = BESPEC_CON;
          bevp_controlSpec = new BEC_2_4_6_TextString(conspec);
          } 
} 
bem_buildControlsIn_0();
return this;
}
BEC_2_8_8_EmbeddedAppShell* BEC_2_8_8_EmbeddedAppShell::bem_initRandom_0() {
struct bes { BEC_2_8_4_EmbeddedWifi* bevl_wifi; BEC_2_4_6_TextString* bevl_rhash; BEC_2_4_3_MathInt* bevl_i; BEC_2_4_6_TextString* bevl_net; BEC_2_6_6_SystemObject* bevt_0_ta_loop; BEC_2_9_4_ContainerList* bevt_1_ta_ph; BEC_2_6_6_SystemObject* bevt_2_ta_ph; BEC_2_5_4_LogicBool* bevt_3_ta_ph; BEC_2_4_3_MathInt* bevt_4_ta_ph; BEC_2_6_6_SystemRandom* bevt_5_ta_ph; BEC_2_4_3_MathInt* bevt_6_ta_ph; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->bevl_wifi = nullptr;
beq->bevl_rhash = nullptr;
beq->bevl_i = nullptr;
beq->bevl_net = nullptr;
beq->bevt_0_ta_loop = nullptr;
beq->bevt_1_ta_ph = nullptr;
beq->bevt_2_ta_ph = nullptr;
beq->bevt_3_ta_ph = nullptr;
beq->bevt_4_ta_ph = nullptr;
beq->bevt_5_ta_ph = nullptr;
beq->bevt_6_ta_ph = nullptr;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(12);
beq->bevl_wifi = static_cast<BEC_2_8_4_EmbeddedWifi*>(BEC_2_8_4_EmbeddedWifi::bece_BEC_2_8_4_EmbeddedWifi_bevs_inst);
beq->bevl_rhash = beq->bevl_wifi->bem_macAddressGet_0();
beq->bevl_i = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(0))));
beq->bevt_1_ta_ph = beq->bevl_wifi->bem_scanNetworks_0();
beq->bevt_0_ta_loop = beq->bevt_1_ta_ph->bem_iteratorGet_0();
while (true)
 {
beq->bevt_2_ta_ph = beq->bevt_0_ta_loop->bemd_0(448214784);
if ((static_cast<BEC_2_5_4_LogicBool*>(beq->bevt_2_ta_ph))->bevi_bool) {
beq->bevl_net = static_cast<BEC_2_4_6_TextString*>(beq->bevt_0_ta_loop->bemd_0(-119099042));
beq->bevl_rhash->bem_addValue_1(beq->bevl_net);
beq->bevl_i->bevi_int++;
beq->bevt_4_ta_ph = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(7))));
if (beq->bevl_i->bevi_int > beq->bevt_4_ta_ph->bevi_int) {
beq->bevt_3_ta_ph = BECS_Runtime::boolTrue;
 } else { 
beq->bevt_3_ta_ph = BECS_Runtime::boolFalse;
}
if (beq->bevt_3_ta_ph->bevi_bool) {
break;
} 
} 
 else  {
break;
} 
} 
beq->bevt_5_ta_ph = static_cast<BEC_2_6_6_SystemRandom*>(BEC_2_6_6_SystemRandom::bece_BEC_2_6_6_SystemRandom_bevs_inst);
beq->bevt_6_ta_ph = beq->bevl_rhash->bem_hashGet_0();
beq->bevt_5_ta_ph->bem_seed_1(beq->bevt_6_ta_ph);
return this;
}
BEC_2_8_8_EmbeddedAppShell* BEC_2_8_8_EmbeddedAppShell::bem_startLoop_0() {
struct bes { BEC_2_4_3_MathInt* bevt_0_ta_ph; BEC_2_4_6_TextString* bevt_1_ta_ph; BEC_2_4_6_TextString* bevt_2_ta_ph; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->bevt_0_ta_ph = nullptr;
beq->bevt_1_ta_ph = nullptr;
beq->bevt_2_ta_ph = nullptr;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(4);
bevp_app->bem_wdtFeed_0();
bevp_app->bem_yield_0();
beq->bevt_0_ta_ph = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(0))));
bevp_app->bem_wdtEnable_1(beq->bevt_0_ta_ph);
bem_buildSwInfo_0();
bem_initRandom_0();
bem_checkMakeIds_0();
bem_loadPasses_0();
bevp_swInfo->bem_print_0();
beq->bevt_1_ta_ph = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString(9, {0x44,0x65,0x76,0x69,0x63,0x65,0x20,0x49,0x64}))));
beq->bevt_1_ta_ph->bem_print_0();
bevp_did->bem_print_0();
beq->bevt_2_ta_ph = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString(3, {0x50,0x69,0x6E}))));
beq->bevt_2_ta_ph->bem_print_0();
bevp_pin->bem_print_0();
bevp_swInfo->bem_print_0();
return this;
}
BEC_2_8_8_EmbeddedAppShell* BEC_2_8_8_EmbeddedAppShell::bem_networkInit_0() {
struct bes { BEC_2_4_6_TextString* bevl_tccon; BEC_2_5_4_LogicBool* bevt_0_ta_ph; BEC_2_4_6_TextString* bevt_1_ta_ph; BEC_2_8_4_EmbeddedWifi* bevt_2_ta_ph; BEC_2_4_6_TextString* bevt_3_ta_ph; BEC_2_4_6_TextString* bevt_4_ta_ph; BEC_2_4_6_TextString* bevt_5_ta_ph; BEC_2_8_4_EmbeddedWifi* bevt_6_ta_ph; BEC_2_5_4_LogicBool* bevt_7_ta_ph; BEC_2_8_4_EmbeddedWifi* bevt_8_ta_ph; BEC_2_4_3_MathInt* bevt_9_ta_ph; BEC_2_5_4_LogicBool* bevt_10_ta_ph; BEC_2_4_6_TextString* bevt_11_ta_ph; BEC_2_4_3_MathInt* bevt_12_ta_ph; BEC_2_4_6_TextString* bevt_13_ta_ph; BEC_2_4_6_TextString* bevt_14_ta_ph; BEC_2_5_4_LogicBool* bevt_15_ta_ph; BEC_2_8_4_EmbeddedWifi* bevt_16_ta_ph; BEC_2_4_6_TextString* bevt_17_ta_ph; BEC_2_4_6_TextString* bevt_18_ta_ph; BEC_2_4_6_TextString* bevt_19_ta_ph; BEC_2_4_3_MathInt* bevt_20_ta_ph; BEC_2_4_6_TextString* bevt_21_ta_ph; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->bevl_tccon = nullptr;
beq->bevt_0_ta_ph = nullptr;
beq->bevt_1_ta_ph = nullptr;
beq->bevt_2_ta_ph = nullptr;
beq->bevt_3_ta_ph = nullptr;
beq->bevt_4_ta_ph = nullptr;
beq->bevt_5_ta_ph = nullptr;
beq->bevt_6_ta_ph = nullptr;
beq->bevt_7_ta_ph = nullptr;
beq->bevt_8_ta_ph = nullptr;
beq->bevt_9_ta_ph = nullptr;
beq->bevt_10_ta_ph = nullptr;
beq->bevt_11_ta_ph = nullptr;
beq->bevt_12_ta_ph = nullptr;
beq->bevt_13_ta_ph = nullptr;
beq->bevt_14_ta_ph = nullptr;
beq->bevt_15_ta_ph = nullptr;
beq->bevt_16_ta_ph = nullptr;
beq->bevt_17_ta_ph = nullptr;
beq->bevt_18_ta_ph = nullptr;
beq->bevt_19_ta_ph = nullptr;
beq->bevt_20_ta_ph = nullptr;
beq->bevt_21_ta_ph = nullptr;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(24);
bem_checkWifiAp_0();
beq->bevt_2_ta_ph = static_cast<BEC_2_8_4_EmbeddedWifi*>(BEC_2_8_4_EmbeddedWifi::bece_BEC_2_8_4_EmbeddedWifi_bevs_inst);
beq->bevt_1_ta_ph = beq->bevt_2_ta_ph->bem_localIPGet_0();
if (beq->bevt_1_ta_ph == nullptr) {
beq->bevt_0_ta_ph = BECS_Runtime::boolFalse;
 } else { 
beq->bevt_0_ta_ph = BECS_Runtime::boolTrue;
}
if (beq->bevt_0_ta_ph->bevi_bool) {
beq->bevt_4_ta_ph = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString(9, {0x4C,0x6F,0x63,0x61,0x6C,0x20,0x69,0x70,0x20}))));
beq->bevt_6_ta_ph = static_cast<BEC_2_8_4_EmbeddedWifi*>(BEC_2_8_4_EmbeddedWifi::bece_BEC_2_8_4_EmbeddedWifi_bevs_inst);
beq->bevt_5_ta_ph = beq->bevt_6_ta_ph->bem_localIPGet_0();
beq->bevt_3_ta_ph = beq->bevt_4_ta_ph->bem_add_1(beq->bevt_5_ta_ph);
beq->bevt_3_ta_ph->bem_print_0();
beq->bevt_8_ta_ph = static_cast<BEC_2_8_4_EmbeddedWifi*>(BEC_2_8_4_EmbeddedWifi::bece_BEC_2_8_4_EmbeddedWifi_bevs_inst);
beq->bevt_7_ta_ph = beq->bevt_8_ta_ph->bem_upGet_0();
if (beq->bevt_7_ta_ph->bevi_bool) {
beq->bevt_9_ta_ph = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(6420))));
bevp_tcpserver = static_cast<BEC_2_8_9_EmbeddedTCPServer*>(((BEC_2_8_9_EmbeddedTCPServer*) (new BEC_2_8_9_EmbeddedTCPServer()))->bem_new_1(beq->bevt_9_ta_ph));
bevp_tcpserver->bem_start_0();

          std::string tccon = BE_TCPCONSOLE;
          beq->bevl_tccon = new BEC_2_4_6_TextString(tccon);
          beq->bevt_11_ta_ph = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString(2, {0x6F,0x6E}))));
beq->bevt_10_ta_ph = beq->bevl_tccon->bem_equals_1(beq->bevt_11_ta_ph);
if (beq->bevt_10_ta_ph->bevi_bool) {
beq->bevt_12_ta_ph = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(32259))));
bevp_conserver = static_cast<BEC_2_8_9_EmbeddedTCPServer*>(((BEC_2_8_9_EmbeddedTCPServer*) (new BEC_2_8_9_EmbeddedTCPServer()))->bem_new_1(beq->bevt_12_ta_ph));
bevp_conserver->bem_start_0();
} 
beq->bevt_14_ta_ph = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString(11, {0x74,0x63,0x70,0x63,0x6F,0x6E,0x73,0x6F,0x6C,0x65,0x20}))));
beq->bevt_13_ta_ph = beq->bevt_14_ta_ph->bem_add_1(beq->bevl_tccon);
beq->bevt_13_ta_ph->bem_print_0();
beq->bevt_16_ta_ph = static_cast<BEC_2_8_4_EmbeddedWifi*>(BEC_2_8_4_EmbeddedWifi::bece_BEC_2_8_4_EmbeddedWifi_bevs_inst);
beq->bevt_15_ta_ph = beq->bevt_16_ta_ph->bem_isConnectedGet_0();
if (beq->bevt_15_ta_ph->bevi_bool) {
bevp_mdserver = static_cast<BEC_2_8_4_EmbeddedMdns*>(((BEC_2_8_4_EmbeddedMdns*) (new BEC_2_8_4_EmbeddedMdns()))->bem_new_0());
beq->bevt_18_ta_ph = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString(6, {0x43,0x61,0x73,0x4E,0x69,0x63}))));
beq->bevt_17_ta_ph = beq->bevt_18_ta_ph->bem_add_1(bevp_did);
bevp_mdserver->bem_nameSet_1(beq->bevt_17_ta_ph);
beq->bevt_19_ta_ph = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString(4, {0x68,0x74,0x74,0x70}))));
bevp_mdserver->bem_serviceSet_1(beq->bevt_19_ta_ph);
beq->bevt_20_ta_ph = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(80))));
bevp_mdserver->bem_portSet_1(beq->bevt_20_ta_ph);
beq->bevt_21_ta_ph = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString(3, {0x74,0x63,0x70}))));
bevp_mdserver->bem_protocolSet_1(beq->bevt_21_ta_ph);
bevp_mdserver->bem_start_0();
} 
} 
} 
return this;
}
BEC_2_8_8_EmbeddedAppShell* BEC_2_8_8_EmbeddedAppShell::bem_initMq_0() {
struct bes { BEC_2_8_4_EmbeddedMqtt* bevl_oldmqtt; BEC_2_4_6_TextString* bevl_mqhost; BEC_2_4_6_TextString* bevl_mquser; BEC_2_4_6_TextString* bevl_mqpass; BEC_2_5_4_LogicBool* bevt_0_ta_anchor; BEC_2_5_4_LogicBool* bevt_1_ta_anchor; BEC_2_5_4_LogicBool* bevt_2_ta_ph; BEC_2_5_4_LogicBool* bevt_3_ta_ph; BEC_2_8_4_EmbeddedWifi* bevt_4_ta_ph; BEC_2_6_6_SystemObject* bevt_5_ta_ph; BEC_2_4_6_TextString* bevt_6_ta_ph; BEC_2_6_6_SystemObject* bevt_7_ta_ph; BEC_2_4_6_TextString* bevt_8_ta_ph; BEC_2_6_6_SystemObject* bevt_9_ta_ph; BEC_2_4_6_TextString* bevt_10_ta_ph; BEC_2_5_4_LogicBool* bevt_11_ta_ph; BEC_2_4_7_TextStrings* bevt_12_ta_ph; BEC_2_5_4_LogicBool* bevt_13_ta_ph; BEC_2_4_7_TextStrings* bevt_14_ta_ph; BEC_2_5_4_LogicBool* bevt_15_ta_ph; BEC_2_4_7_TextStrings* bevt_16_ta_ph; BEC_2_5_4_LogicBool* bevt_17_ta_ph; BEC_2_4_6_TextString* bevt_18_ta_ph; BEC_2_5_4_LogicBool* bevt_19_ta_ph; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->bevl_oldmqtt = nullptr;
beq->bevl_mqhost = nullptr;
beq->bevl_mquser = nullptr;
beq->bevl_mqpass = nullptr;
beq->bevt_0_ta_anchor = nullptr;
beq->bevt_1_ta_anchor = nullptr;
beq->bevt_2_ta_ph = nullptr;
beq->bevt_3_ta_ph = nullptr;
beq->bevt_4_ta_ph = nullptr;
beq->bevt_5_ta_ph = nullptr;
beq->bevt_6_ta_ph = nullptr;
beq->bevt_7_ta_ph = nullptr;
beq->bevt_8_ta_ph = nullptr;
beq->bevt_9_ta_ph = nullptr;
beq->bevt_10_ta_ph = nullptr;
beq->bevt_11_ta_ph = nullptr;
beq->bevt_12_ta_ph = nullptr;
beq->bevt_13_ta_ph = nullptr;
beq->bevt_14_ta_ph = nullptr;
beq->bevt_15_ta_ph = nullptr;
beq->bevt_16_ta_ph = nullptr;
beq->bevt_17_ta_ph = nullptr;
beq->bevt_18_ta_ph = nullptr;
beq->bevt_19_ta_ph = nullptr;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(25);
if (bevp_mqtt == nullptr) {
beq->bevt_2_ta_ph = BECS_Runtime::boolFalse;
 } else { 
beq->bevt_2_ta_ph = BECS_Runtime::boolTrue;
}
if (beq->bevt_2_ta_ph->bevi_bool) {
beq->bevl_oldmqtt = bevp_mqtt;
bevp_mqtt = nullptr;
beq->bevl_oldmqtt->bem_close_0();
} 
beq->bevt_4_ta_ph = static_cast<BEC_2_8_4_EmbeddedWifi*>(BEC_2_8_4_EmbeddedWifi::bece_BEC_2_8_4_EmbeddedWifi_bevs_inst);
beq->bevt_3_ta_ph = beq->bevt_4_ta_ph->bem_isConnectedGet_0();
if (beq->bevt_3_ta_ph->bevi_bool) {
beq->bevt_6_ta_ph = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString(9, {0x66,0x63,0x2E,0x6D,0x71,0x68,0x6F,0x73,0x74}))));
beq->bevt_5_ta_ph = bevp_config->bem_getPos_1(beq->bevt_6_ta_ph);
beq->bevl_mqhost = bevp_config->bem_get_1(static_cast<BEC_2_4_3_MathInt*>(beq->bevt_5_ta_ph) );
beq->bevt_8_ta_ph = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString(9, {0x66,0x63,0x2E,0x6D,0x71,0x75,0x73,0x65,0x72}))));
beq->bevt_7_ta_ph = bevp_config->bem_getPos_1(beq->bevt_8_ta_ph);
beq->bevl_mquser = bevp_config->bem_get_1(static_cast<BEC_2_4_3_MathInt*>(beq->bevt_7_ta_ph) );
beq->bevt_10_ta_ph = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString(9, {0x66,0x63,0x2E,0x6D,0x71,0x70,0x61,0x73,0x73}))));
beq->bevt_9_ta_ph = bevp_config->bem_getPos_1(beq->bevt_10_ta_ph);
beq->bevl_mqpass = bevp_config->bem_get_1(static_cast<BEC_2_4_3_MathInt*>(beq->bevt_9_ta_ph) );
beq->bevt_12_ta_ph = static_cast<BEC_2_4_7_TextStrings*>(BEC_2_4_7_TextStrings::bece_BEC_2_4_7_TextStrings_bevs_inst);
beq->bevt_11_ta_ph = beq->bevt_12_ta_ph->bem_notEmpty_1(beq->bevl_mqhost);
if (beq->bevt_11_ta_ph->bevi_bool) {
beq->bevt_14_ta_ph = static_cast<BEC_2_4_7_TextStrings*>(BEC_2_4_7_TextStrings::bece_BEC_2_4_7_TextStrings_bevs_inst);
beq->bevt_13_ta_ph = beq->bevt_14_ta_ph->bem_notEmpty_1(beq->bevl_mquser);
if (beq->bevt_13_ta_ph->bevi_bool) {
beq->bevt_1_ta_anchor = BECS_Runtime::boolTrue;
} 
 else  {
beq->bevt_1_ta_anchor = BECS_Runtime::boolFalse;
} 
} 
 else  {
beq->bevt_1_ta_anchor = BECS_Runtime::boolFalse;
} 
if (beq->bevt_1_ta_anchor->bevi_bool) {
beq->bevt_16_ta_ph = static_cast<BEC_2_4_7_TextStrings*>(BEC_2_4_7_TextStrings::bece_BEC_2_4_7_TextStrings_bevs_inst);
beq->bevt_15_ta_ph = beq->bevt_16_ta_ph->bem_notEmpty_1(beq->bevl_mqpass);
if (beq->bevt_15_ta_ph->bevi_bool) {
beq->bevt_0_ta_anchor = BECS_Runtime::boolTrue;
} 
 else  {
beq->bevt_0_ta_anchor = BECS_Runtime::boolFalse;
} 
} 
 else  {
beq->bevt_0_ta_anchor = BECS_Runtime::boolFalse;
} 
if (beq->bevt_0_ta_anchor->bevi_bool) {
bevp_mqtt = static_cast<BEC_2_8_4_EmbeddedMqtt*>(((BEC_2_8_4_EmbeddedMqtt*) (new BEC_2_8_4_EmbeddedMqtt()))->bem_new_3(beq->bevl_mqhost, beq->bevl_mquser, beq->bevl_mqpass));
beq->bevt_17_ta_ph = bevp_mqtt->bem_open_0();
if (beq->bevt_17_ta_ph->bevi_bool) {
beq->bevt_18_ta_ph = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString(20, {0x68,0x6F,0x6D,0x65,0x61,0x73,0x73,0x69,0x73,0x74,0x61,0x6E,0x74,0x2F,0x73,0x74,0x61,0x74,0x75,0x73}))));
bevp_mqtt->bem_subscribeAsync_1(beq->bevt_18_ta_ph);
beq->bevt_19_ta_ph = static_cast<BEC_2_5_4_LogicBool*>(BECS_Runtime::boolTrue);
bem_mqConfUp_1(beq->bevt_19_ta_ph);
bevp_needsGc = static_cast<BEC_2_5_4_LogicBool*>(BECS_Runtime::boolTrue);
} 
 else  {
beq->bevl_oldmqtt = bevp_mqtt;
bevp_mqtt = nullptr;
beq->bevl_oldmqtt->bem_close_0();
} 
} 
} 
return this;
}
BEC_2_8_8_EmbeddedAppShell* BEC_2_8_8_EmbeddedAppShell::bem_mqConfUp_1(BEC_2_5_4_LogicBool* bevk_doSubs) {
struct bes { BEC_2_5_4_LogicBool* beva_doSubs; BEC_2_4_3_MathInt* bevl_cap; BEC_2_4_3_MathInt* bevl_keyi; BEC_2_4_6_TextString* bevl_dname; BEC_2_4_6_TextString* bevl_csnc; BEC_2_6_6_SystemObject* bevl_ctl; BEC_2_4_6_TextString* bevl_conName; BEC_2_4_3_MathInt* bevl_conPoss; BEC_2_4_6_TextString* bevl_tpp; BEC_2_4_6_TextString* bevl_cf; BEC_2_4_6_TextString* bevl_pt; BEC_2_6_6_SystemObject* bevt_0_ta_loop; BEC_2_5_4_LogicBool* bevt_1_ta_anchor; BEC_2_4_6_TextString* bevt_2_ta_ph; BEC_2_5_4_LogicBool* bevt_3_ta_ph; BEC_2_4_6_TextString* bevt_4_ta_ph; BEC_2_4_3_MathInt* bevt_5_ta_ph; BEC_2_4_3_MathInt* bevt_6_ta_ph; BEC_2_5_4_LogicBool* bevt_7_ta_ph; BEC_2_4_6_TextString* bevt_8_ta_ph; BEC_2_4_6_TextString* bevt_9_ta_ph; BEC_2_5_4_LogicBool* bevt_10_ta_ph; BEC_2_4_7_TextStrings* bevt_11_ta_ph; BEC_2_4_6_TextString* bevt_12_ta_ph; BEC_2_4_6_TextString* bevt_13_ta_ph; BEC_2_4_6_TextString* bevt_14_ta_ph; BEC_2_4_6_TextString* bevt_15_ta_ph; BEC_2_6_6_SystemObject* bevt_16_ta_ph; BEC_2_6_6_SystemObject* bevt_17_ta_ph; BEC_2_5_4_LogicBool* bevt_18_ta_ph; BEC_2_4_6_TextString* bevt_19_ta_ph; BEC_2_4_6_TextString* bevt_20_ta_ph; BEC_2_4_6_TextString* bevt_21_ta_ph; BEC_2_4_6_TextString* bevt_22_ta_ph; BEC_2_4_6_TextString* bevt_23_ta_ph; BEC_2_4_6_TextString* bevt_24_ta_ph; BEC_2_4_6_TextString* bevt_25_ta_ph; BEC_2_4_6_TextString* bevt_26_ta_ph; BEC_2_4_6_TextString* bevt_27_ta_ph; BEC_2_4_6_TextString* bevt_28_ta_ph; BEC_2_4_6_TextString* bevt_29_ta_ph; BEC_2_4_6_TextString* bevt_30_ta_ph; BEC_2_4_6_TextString* bevt_31_ta_ph; BEC_2_4_6_TextString* bevt_32_ta_ph; BEC_2_4_6_TextString* bevt_33_ta_ph; BEC_2_4_6_TextString* bevt_34_ta_ph; BEC_2_4_6_TextString* bevt_35_ta_ph; BEC_2_4_6_TextString* bevt_36_ta_ph; BEC_2_4_6_TextString* bevt_37_ta_ph; BEC_2_4_6_TextString* bevt_38_ta_ph; BEC_2_4_6_TextString* bevt_39_ta_ph; BEC_2_4_6_TextString* bevt_40_ta_ph; BEC_2_4_6_TextString* bevt_41_ta_ph; BEC_2_4_6_TextString* bevt_42_ta_ph; BEC_2_4_6_TextString* bevt_43_ta_ph; BEC_2_4_6_TextString* bevt_44_ta_ph; BEC_2_5_4_LogicBool* bevt_45_ta_ph; BEC_2_4_6_TextString* bevt_46_ta_ph; BEC_2_4_6_TextString* bevt_47_ta_ph; BEC_2_4_6_TextString* bevt_48_ta_ph; BEC_2_4_6_TextString* bevt_49_ta_ph; BEC_2_4_6_TextString* bevt_50_ta_ph; BEC_2_4_6_TextString* bevt_51_ta_ph; BEC_2_4_6_TextString* bevt_52_ta_ph; BEC_2_4_6_TextString* bevt_53_ta_ph; BEC_2_4_6_TextString* bevt_54_ta_ph; BEC_2_4_6_TextString* bevt_55_ta_ph; BEC_2_4_6_TextString* bevt_56_ta_ph; BEC_2_4_6_TextString* bevt_57_ta_ph; BEC_2_4_6_TextString* bevt_58_ta_ph; BEC_2_4_6_TextString* bevt_59_ta_ph; BEC_2_4_6_TextString* bevt_60_ta_ph; BEC_2_4_6_TextString* bevt_61_ta_ph; BEC_2_4_6_TextString* bevt_62_ta_ph; BEC_2_4_6_TextString* bevt_63_ta_ph; BEC_2_4_6_TextString* bevt_64_ta_ph; BEC_2_4_6_TextString* bevt_65_ta_ph; BEC_2_4_6_TextString* bevt_66_ta_ph; BEC_2_4_6_TextString* bevt_67_ta_ph; BEC_2_4_6_TextString* bevt_68_ta_ph; BEC_2_4_6_TextString* bevt_69_ta_ph; BEC_2_4_6_TextString* bevt_70_ta_ph; BEC_2_4_6_TextString* bevt_71_ta_ph; BEC_2_5_4_LogicBool* bevt_72_ta_ph; BEC_2_4_7_TextStrings* bevt_73_ta_ph; BEC_2_5_4_LogicBool* bevt_74_ta_ph; BEC_2_4_7_TextStrings* bevt_75_ta_ph; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->beva_doSubs = bevk_doSubs;
beq->bevl_cap = nullptr;
beq->bevl_keyi = nullptr;
beq->bevl_dname = nullptr;
beq->bevl_csnc = nullptr;
beq->bevl_ctl = nullptr;
beq->bevl_conName = nullptr;
beq->bevl_conPoss = nullptr;
beq->bevl_tpp = nullptr;
beq->bevl_cf = nullptr;
beq->bevl_pt = nullptr;
beq->bevt_0_ta_loop = nullptr;
beq->bevt_1_ta_anchor = nullptr;
beq->bevt_2_ta_ph = nullptr;
beq->bevt_3_ta_ph = nullptr;
beq->bevt_4_ta_ph = nullptr;
beq->bevt_5_ta_ph = nullptr;
beq->bevt_6_ta_ph = nullptr;
beq->bevt_7_ta_ph = nullptr;
beq->bevt_8_ta_ph = nullptr;
beq->bevt_9_ta_ph = nullptr;
beq->bevt_10_ta_ph = nullptr;
beq->bevt_11_ta_ph = nullptr;
beq->bevt_12_ta_ph = nullptr;
beq->bevt_13_ta_ph = nullptr;
beq->bevt_14_ta_ph = nullptr;
beq->bevt_15_ta_ph = nullptr;
beq->bevt_16_ta_ph = nullptr;
beq->bevt_17_ta_ph = nullptr;
beq->bevt_18_ta_ph = nullptr;
beq->bevt_19_ta_ph = nullptr;
beq->bevt_20_ta_ph = nullptr;
beq->bevt_21_ta_ph = nullptr;
beq->bevt_22_ta_ph = nullptr;
beq->bevt_23_ta_ph = nullptr;
beq->bevt_24_ta_ph = nullptr;
beq->bevt_25_ta_ph = nullptr;
beq->bevt_26_ta_ph = nullptr;
beq->bevt_27_ta_ph = nullptr;
beq->bevt_28_ta_ph = nullptr;
beq->bevt_29_ta_ph = nullptr;
beq->bevt_30_ta_ph = nullptr;
beq->bevt_31_ta_ph = nullptr;
beq->bevt_32_ta_ph = nullptr;
beq->bevt_33_ta_ph = nullptr;
beq->bevt_34_ta_ph = nullptr;
beq->bevt_35_ta_ph = nullptr;
beq->bevt_36_ta_ph = nullptr;
beq->bevt_37_ta_ph = nullptr;
beq->bevt_38_ta_ph = nullptr;
beq->bevt_39_ta_ph = nullptr;
beq->bevt_40_ta_ph = nullptr;
beq->bevt_41_ta_ph = nullptr;
beq->bevt_42_ta_ph = nullptr;
beq->bevt_43_ta_ph = nullptr;
beq->bevt_44_ta_ph = nullptr;
beq->bevt_45_ta_ph = nullptr;
beq->bevt_46_ta_ph = nullptr;
beq->bevt_47_ta_ph = nullptr;
beq->bevt_48_ta_ph = nullptr;
beq->bevt_49_ta_ph = nullptr;
beq->bevt_50_ta_ph = nullptr;
beq->bevt_51_ta_ph = nullptr;
beq->bevt_52_ta_ph = nullptr;
beq->bevt_53_ta_ph = nullptr;
beq->bevt_54_ta_ph = nullptr;
beq->bevt_55_ta_ph = nullptr;
beq->bevt_56_ta_ph = nullptr;
beq->bevt_57_ta_ph = nullptr;
beq->bevt_58_ta_ph = nullptr;
beq->bevt_59_ta_ph = nullptr;
beq->bevt_60_ta_ph = nullptr;
beq->bevt_61_ta_ph = nullptr;
beq->bevt_62_ta_ph = nullptr;
beq->bevt_63_ta_ph = nullptr;
beq->bevt_64_ta_ph = nullptr;
beq->bevt_65_ta_ph = nullptr;
beq->bevt_66_ta_ph = nullptr;
beq->bevt_67_ta_ph = nullptr;
beq->bevt_68_ta_ph = nullptr;
beq->bevt_69_ta_ph = nullptr;
beq->bevt_70_ta_ph = nullptr;
beq->bevt_71_ta_ph = nullptr;
beq->bevt_72_ta_ph = nullptr;
beq->bevt_73_ta_ph = nullptr;
beq->bevt_74_ta_ph = nullptr;
beq->bevt_75_ta_ph = nullptr;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(88);
beq->bevt_2_ta_ph = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString(8, {0x6D,0x71,0x43,0x6F,0x6E,0x66,0x55,0x70}))));
beq->bevt_2_ta_ph->bem_print_0();
if (bevp_mqtt == nullptr) {
beq->bevt_3_ta_ph = BECS_Runtime::boolTrue;
 } else { 
beq->bevt_3_ta_ph = BECS_Runtime::boolFalse;
}
if (beq->bevt_3_ta_ph->bevi_bool) {
beq->bevt_4_ta_ph = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString(10, {0x6D,0x71,0x74,0x74,0x20,0x75,0x6E,0x64,0x65,0x66}))));
beq->bevt_4_ta_ph->bem_print_0();
return this;
} 
beq->bevt_5_ta_ph = bevp_controls->bem_sizeGet_0();
beq->bevt_6_ta_ph = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(1))));
beq->bevl_cap = beq->bevt_5_ta_ph->bem_add_1(beq->bevt_6_ta_ph);
bevp_mqtt->bem_minAsyncCapacitySet_1(beq->bevl_cap);
beq->bevt_7_ta_ph = bevp_mqtt->bem_hasAsyncCapacity_1(beq->bevl_cap);
if (!(beq->bevt_7_ta_ph->bevi_bool)) {
beq->bevt_8_ta_ph = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString(26, {0x6D,0x71,0x74,0x74,0x20,0x63,0x6F,0x6E,0x66,0x20,0x6E,0x6F,0x74,0x20,0x65,0x6E,0x6F,0x75,0x67,0x68,0x20,0x73,0x70,0x61,0x63,0x65}))));
beq->bevt_8_ta_ph->bem_print_0();
return this;
} 
beq->bevt_9_ta_ph = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString(8, {0x66,0x63,0x2E,0x64,0x6E,0x61,0x6D,0x65}))));
beq->bevl_keyi = static_cast<BEC_2_4_3_MathInt*>(bevp_config->bem_getPos_1(beq->bevt_9_ta_ph));
beq->bevl_dname = bevp_config->bem_get_1(beq->bevl_keyi);
beq->bevt_11_ta_ph = static_cast<BEC_2_4_7_TextStrings*>(BEC_2_4_7_TextStrings::bece_BEC_2_4_7_TextStrings_bevs_inst);
beq->bevt_10_ta_ph = beq->bevt_11_ta_ph->bem_isEmpty_1(beq->bevl_dname);
if (beq->bevt_10_ta_ph->bevi_bool) {
beq->bevl_dname = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString(13, {0x43,0x61,0x73,0x4E,0x69,0x63,0x20,0x44,0x65,0x76,0x69,0x63,0x65}))));
} 
beq->bevt_13_ta_ph = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString(5, {0x63,0x6E,0x63,0x6D,0x2F}))));
beq->bevt_12_ta_ph = beq->bevt_13_ta_ph->bem_add_1(bevp_did);
beq->bevt_14_ta_ph = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString(4, {0x2F,0x63,0x6D,0x64}))));
beq->bevl_csnc = beq->bevt_12_ta_ph->bem_add_1(beq->bevt_14_ta_ph);
if (beq->beva_doSubs->bevi_bool) {
bevp_mqtt->bem_subscribeAsync_1(beq->bevl_csnc);
} 
beq->bevt_15_ta_ph = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString(4, {0x63,0x6E,0x64,0x73}))));
bevp_mqtt->bem_publishAsync_2(beq->bevt_15_ta_ph, bevp_did);
beq->bevt_0_ta_loop = bevp_controls->bem_iteratorGet_0();
while (true)
 {
beq->bevt_16_ta_ph = beq->bevt_0_ta_loop->bemd_0(448214784);
if ((static_cast<BEC_2_5_4_LogicBool*>(beq->bevt_16_ta_ph))->bevi_bool) {
beq->bevl_ctl = beq->bevt_0_ta_loop->bemd_0(-119099042);
beq->bevl_conName = static_cast<BEC_2_4_6_TextString*>(beq->bevl_ctl->bemd_0(1530937685));
beq->bevt_17_ta_ph = beq->bevl_ctl->bemd_0(355723905);
beq->bevl_conPoss = static_cast<BEC_2_4_3_MathInt*>(beq->bevt_17_ta_ph->bemd_0(-1553512291));
beq->bevl_cf = nullptr;
beq->bevl_pt = nullptr;
beq->bevt_19_ta_ph = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString(2, {0x73,0x77}))));
beq->bevt_18_ta_ph = beq->bevl_conName->bem_equals_1(beq->bevt_19_ta_ph);
if (beq->bevt_18_ta_ph->bevi_bool) {
beq->bevt_22_ta_ph = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString(21, {0x68,0x6F,0x6D,0x65,0x61,0x73,0x73,0x69,0x73,0x74,0x61,0x6E,0x74,0x2F,0x73,0x77,0x69,0x74,0x63,0x68,0x2F}))));
beq->bevt_21_ta_ph = beq->bevt_22_ta_ph->bem_add_1(bevp_did);
beq->bevt_23_ta_ph = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString(1, {0x2D}))));
beq->bevt_20_ta_ph = beq->bevt_21_ta_ph->bem_add_1(beq->bevt_23_ta_ph);
beq->bevl_tpp = beq->bevt_20_ta_ph->bem_add_1(beq->bevl_conPoss);
beq->bevt_24_ta_ph = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString(7, {0x2F,0x63,0x6F,0x6E,0x66,0x69,0x67}))));
beq->bevl_pt = beq->bevl_tpp->bem_add_1(beq->bevt_24_ta_ph);
beq->bevt_36_ta_ph = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString(11, {0x7B,0x20,0x22,0x6E,0x61,0x6D,0x65,0x22,0x3A,0x20,0x22}))));
beq->bevt_35_ta_ph = static_cast<BEC_2_4_6_TextString*>(beq->bevt_36_ta_ph->bem_addValue_1(beq->bevl_dname));
beq->bevt_37_ta_ph = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString(1, {0x20}))));
beq->bevt_34_ta_ph = static_cast<BEC_2_4_6_TextString*>(beq->bevt_35_ta_ph->bem_addValue_1(beq->bevt_37_ta_ph));
beq->bevt_33_ta_ph = static_cast<BEC_2_4_6_TextString*>(beq->bevt_34_ta_ph->bem_addValue_1(beq->bevl_conPoss));
beq->bevt_38_ta_ph = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString(21, {0x22,0x2C,0x20,0x22,0x63,0x6F,0x6D,0x6D,0x61,0x6E,0x64,0x5F,0x74,0x6F,0x70,0x69,0x63,0x22,0x3A,0x20,0x22}))));
beq->bevt_32_ta_ph = static_cast<BEC_2_4_6_TextString*>(beq->bevt_33_ta_ph->bem_addValue_1(beq->bevt_38_ta_ph));
beq->bevt_31_ta_ph = static_cast<BEC_2_4_6_TextString*>(beq->bevt_32_ta_ph->bem_addValue_1(beq->bevl_tpp));
beq->bevt_39_ta_ph = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString(23, {0x2F,0x73,0x65,0x74,0x22,0x2C,0x20,0x22,0x73,0x74,0x61,0x74,0x65,0x5F,0x74,0x6F,0x70,0x69,0x63,0x22,0x3A,0x20,0x22}))));
beq->bevt_30_ta_ph = static_cast<BEC_2_4_6_TextString*>(beq->bevt_31_ta_ph->bem_addValue_1(beq->bevt_39_ta_ph));
beq->bevt_29_ta_ph = static_cast<BEC_2_4_6_TextString*>(beq->bevt_30_ta_ph->bem_addValue_1(beq->bevl_tpp));
beq->bevt_40_ta_ph = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString(23, {0x2F,0x73,0x74,0x61,0x74,0x65,0x22,0x2C,0x20,0x22,0x75,0x6E,0x69,0x71,0x75,0x65,0x5F,0x69,0x64,0x22,0x3A,0x20,0x22}))));
beq->bevt_28_ta_ph = static_cast<BEC_2_4_6_TextString*>(beq->bevt_29_ta_ph->bem_addValue_1(beq->bevt_40_ta_ph));
beq->bevt_27_ta_ph = static_cast<BEC_2_4_6_TextString*>(beq->bevt_28_ta_ph->bem_addValue_1(bevp_did));
beq->bevt_41_ta_ph = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString(1, {0x2D}))));
beq->bevt_26_ta_ph = static_cast<BEC_2_4_6_TextString*>(beq->bevt_27_ta_ph->bem_addValue_1(beq->bevt_41_ta_ph));
beq->bevt_25_ta_ph = static_cast<BEC_2_4_6_TextString*>(beq->bevt_26_ta_ph->bem_addValue_1(beq->bevl_conPoss));
beq->bevt_42_ta_ph = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString(3, {0x22,0x20,0x7D}))));
beq->bevl_cf = static_cast<BEC_2_4_6_TextString*>(beq->bevt_25_ta_ph->bem_addValue_1(beq->bevt_42_ta_ph));
if (beq->beva_doSubs->bevi_bool) {
beq->bevt_44_ta_ph = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString(4, {0x2F,0x73,0x65,0x74}))));
beq->bevt_43_ta_ph = static_cast<BEC_2_4_6_TextString*>(beq->bevl_tpp->bem_addValue_1(beq->bevt_44_ta_ph));
bevp_mqtt->bem_subscribeAsync_1(beq->bevt_43_ta_ph);
} 
} 
 else  {
beq->bevt_46_ta_ph = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString(3, {0x64,0x69,0x6D}))));
beq->bevt_45_ta_ph = beq->bevl_conName->bem_equals_1(beq->bevt_46_ta_ph);
if (beq->bevt_45_ta_ph->bevi_bool) {
beq->bevt_49_ta_ph = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString(20, {0x68,0x6F,0x6D,0x65,0x61,0x73,0x73,0x69,0x73,0x74,0x61,0x6E,0x74,0x2F,0x6C,0x69,0x67,0x68,0x74,0x2F}))));
beq->bevt_48_ta_ph = beq->bevt_49_ta_ph->bem_add_1(bevp_did);
beq->bevt_50_ta_ph = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString(1, {0x2D}))));
beq->bevt_47_ta_ph = beq->bevt_48_ta_ph->bem_add_1(beq->bevt_50_ta_ph);
beq->bevl_tpp = beq->bevt_47_ta_ph->bem_add_1(beq->bevl_conPoss);
beq->bevt_51_ta_ph = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString(7, {0x2F,0x63,0x6F,0x6E,0x66,0x69,0x67}))));
beq->bevl_pt = beq->bevl_tpp->bem_add_1(beq->bevt_51_ta_ph);
beq->bevt_63_ta_ph = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString(11, {0x7B,0x20,0x22,0x6E,0x61,0x6D,0x65,0x22,0x3A,0x20,0x22}))));
beq->bevt_62_ta_ph = static_cast<BEC_2_4_6_TextString*>(beq->bevt_63_ta_ph->bem_addValue_1(beq->bevl_dname));
beq->bevt_64_ta_ph = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString(1, {0x20}))));
beq->bevt_61_ta_ph = static_cast<BEC_2_4_6_TextString*>(beq->bevt_62_ta_ph->bem_addValue_1(beq->bevt_64_ta_ph));
beq->bevt_60_ta_ph = static_cast<BEC_2_4_6_TextString*>(beq->bevt_61_ta_ph->bem_addValue_1(beq->bevl_conPoss));
beq->bevt_65_ta_ph = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString(21, {0x22,0x2C,0x20,0x22,0x63,0x6F,0x6D,0x6D,0x61,0x6E,0x64,0x5F,0x74,0x6F,0x70,0x69,0x63,0x22,0x3A,0x20,0x22}))));
beq->bevt_59_ta_ph = static_cast<BEC_2_4_6_TextString*>(beq->bevt_60_ta_ph->bem_addValue_1(beq->bevt_65_ta_ph));
beq->bevt_58_ta_ph = static_cast<BEC_2_4_6_TextString*>(beq->bevt_59_ta_ph->bem_addValue_1(beq->bevl_tpp));
beq->bevt_66_ta_ph = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString(23, {0x2F,0x73,0x65,0x74,0x22,0x2C,0x20,0x22,0x73,0x74,0x61,0x74,0x65,0x5F,0x74,0x6F,0x70,0x69,0x63,0x22,0x3A,0x20,0x22}))));
beq->bevt_57_ta_ph = static_cast<BEC_2_4_6_TextString*>(beq->bevt_58_ta_ph->bem_addValue_1(beq->bevt_66_ta_ph));
beq->bevt_56_ta_ph = static_cast<BEC_2_4_6_TextString*>(beq->bevt_57_ta_ph->bem_addValue_1(beq->bevl_tpp));
beq->bevt_67_ta_ph = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString(23, {0x2F,0x73,0x74,0x61,0x74,0x65,0x22,0x2C,0x20,0x22,0x75,0x6E,0x69,0x71,0x75,0x65,0x5F,0x69,0x64,0x22,0x3A,0x20,0x22}))));
beq->bevt_55_ta_ph = static_cast<BEC_2_4_6_TextString*>(beq->bevt_56_ta_ph->bem_addValue_1(beq->bevt_67_ta_ph));
beq->bevt_54_ta_ph = static_cast<BEC_2_4_6_TextString*>(beq->bevt_55_ta_ph->bem_addValue_1(bevp_did));
beq->bevt_68_ta_ph = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString(1, {0x2D}))));
beq->bevt_53_ta_ph = static_cast<BEC_2_4_6_TextString*>(beq->bevt_54_ta_ph->bem_addValue_1(beq->bevt_68_ta_ph));
beq->bevt_52_ta_ph = static_cast<BEC_2_4_6_TextString*>(beq->bevt_53_ta_ph->bem_addValue_1(beq->bevl_conPoss));
beq->bevt_69_ta_ph = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString(66, {0x22,0x2C,0x20,0x22,0x73,0x63,0x68,0x65,0x6D,0x61,0x22,0x3A,0x20,0x22,0x6A,0x73,0x6F,0x6E,0x22,0x2C,0x20,0x22,0x62,0x72,0x69,0x67,0x68,0x74,0x6E,0x65,0x73,0x73,0x22,0x3A,0x20,0x74,0x72,0x75,0x65,0x2C,0x20,0x22,0x62,0x72,0x69,0x67,0x68,0x74,0x6E,0x65,0x73,0x73,0x5F,0x73,0x63,0x61,0x6C,0x65,0x22,0x3A,0x20,0x32,0x35,0x35,0x20,0x7D}))));
beq->bevl_cf = static_cast<BEC_2_4_6_TextString*>(beq->bevt_52_ta_ph->bem_addValue_1(beq->bevt_69_ta_ph));
if (beq->beva_doSubs->bevi_bool) {
beq->bevt_71_ta_ph = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString(4, {0x2F,0x73,0x65,0x74}))));
beq->bevt_70_ta_ph = static_cast<BEC_2_4_6_TextString*>(beq->bevl_tpp->bem_addValue_1(beq->bevt_71_ta_ph));
bevp_mqtt->bem_subscribeAsync_1(beq->bevt_70_ta_ph);
} 
} 
} 
beq->bevt_73_ta_ph = static_cast<BEC_2_4_7_TextStrings*>(BEC_2_4_7_TextStrings::bece_BEC_2_4_7_TextStrings_bevs_inst);
beq->bevt_72_ta_ph = beq->bevt_73_ta_ph->bem_notEmpty_1(beq->bevl_pt);
if (beq->bevt_72_ta_ph->bevi_bool) {
beq->bevt_75_ta_ph = static_cast<BEC_2_4_7_TextStrings*>(BEC_2_4_7_TextStrings::bece_BEC_2_4_7_TextStrings_bevs_inst);
beq->bevt_74_ta_ph = beq->bevt_75_ta_ph->bem_notEmpty_1(beq->bevl_cf);
if (beq->bevt_74_ta_ph->bevi_bool) {
beq->bevt_1_ta_anchor = BECS_Runtime::boolTrue;
} 
 else  {
beq->bevt_1_ta_anchor = BECS_Runtime::boolFalse;
} 
} 
 else  {
beq->bevt_1_ta_anchor = BECS_Runtime::boolFalse;
} 
if (beq->bevt_1_ta_anchor->bevi_bool) {
beq->bevl_cf->bem_print_0();
bevp_mqtt->bem_publishAsync_2(beq->bevl_pt, beq->bevl_cf);
} 
} 
 else  {
break;
} 
} 
bevp_needsStateUpSoon = static_cast<BEC_2_5_4_LogicBool*>(BECS_Runtime::boolTrue);
return this;
}
BEC_2_8_8_EmbeddedAppShell* BEC_2_8_8_EmbeddedAppShell::bem_mqStateUp_0() {
struct bes { BEC_2_6_6_SystemObject* bevl_ctl; BEC_2_4_6_TextString* bevl_conName; BEC_2_4_3_MathInt* bevl_conPoss; BEC_2_4_6_TextString* bevl_tpp; BEC_2_4_6_TextString* bevl_cf; BEC_2_4_6_TextString* bevl_pt; BEC_2_4_3_MathInt* bevl_inlvli; BEC_2_6_6_SystemObject* bevt_0_ta_loop; BEC_2_5_4_LogicBool* bevt_1_ta_anchor; BEC_2_4_6_TextString* bevt_2_ta_ph; BEC_2_5_4_LogicBool* bevt_3_ta_ph; BEC_2_4_6_TextString* bevt_4_ta_ph; BEC_2_5_4_LogicBool* bevt_5_ta_ph; BEC_2_4_3_MathInt* bevt_6_ta_ph; BEC_2_4_6_TextString* bevt_7_ta_ph; BEC_2_6_6_SystemObject* bevt_8_ta_ph; BEC_2_6_6_SystemObject* bevt_9_ta_ph; BEC_2_5_4_LogicBool* bevt_10_ta_ph; BEC_2_4_6_TextString* bevt_11_ta_ph; BEC_2_4_6_TextString* bevt_12_ta_ph; BEC_2_4_6_TextString* bevt_13_ta_ph; BEC_2_4_6_TextString* bevt_14_ta_ph; BEC_2_4_6_TextString* bevt_15_ta_ph; BEC_2_4_6_TextString* bevt_16_ta_ph; BEC_2_5_4_LogicBool* bevt_17_ta_ph; BEC_2_4_7_TextStrings* bevt_18_ta_ph; BEC_2_6_6_SystemObject* bevt_19_ta_ph; BEC_2_6_6_SystemObject* bevt_20_ta_ph; BEC_2_5_4_LogicBool* bevt_21_ta_ph; BEC_2_4_6_TextString* bevt_22_ta_ph; BEC_2_4_6_TextString* bevt_23_ta_ph; BEC_2_4_6_TextString* bevt_24_ta_ph; BEC_2_4_6_TextString* bevt_25_ta_ph; BEC_2_4_6_TextString* bevt_26_ta_ph; BEC_2_4_6_TextString* bevt_27_ta_ph; BEC_2_5_4_LogicBool* bevt_28_ta_ph; BEC_2_4_7_TextStrings* bevt_29_ta_ph; BEC_2_6_6_SystemObject* bevt_30_ta_ph; BEC_2_6_6_SystemObject* bevt_31_ta_ph; BEC_2_6_6_SystemObject* bevt_32_ta_ph; BEC_2_4_6_TextString* bevt_33_ta_ph; BEC_2_4_6_TextString* bevt_34_ta_ph; BEC_2_5_4_LogicBool* bevt_35_ta_ph; BEC_2_4_7_TextStrings* bevt_36_ta_ph; BEC_2_6_6_SystemObject* bevt_37_ta_ph; BEC_2_6_6_SystemObject* bevt_38_ta_ph; BEC_2_4_3_MathInt* bevt_39_ta_ph; BEC_2_4_6_TextString* bevt_40_ta_ph; BEC_2_4_6_TextString* bevt_41_ta_ph; BEC_2_4_6_TextString* bevt_42_ta_ph; BEC_2_4_6_TextString* bevt_43_ta_ph; BEC_2_5_4_LogicBool* bevt_44_ta_ph; BEC_2_4_7_TextStrings* bevt_45_ta_ph; BEC_2_5_4_LogicBool* bevt_46_ta_ph; BEC_2_4_7_TextStrings* bevt_47_ta_ph; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->bevl_ctl = nullptr;
beq->bevl_conName = nullptr;
beq->bevl_conPoss = nullptr;
beq->bevl_tpp = nullptr;
beq->bevl_cf = nullptr;
beq->bevl_pt = nullptr;
beq->bevl_inlvli = nullptr;
beq->bevt_0_ta_loop = nullptr;
beq->bevt_1_ta_anchor = nullptr;
beq->bevt_2_ta_ph = nullptr;
beq->bevt_3_ta_ph = nullptr;
beq->bevt_4_ta_ph = nullptr;
beq->bevt_5_ta_ph = nullptr;
beq->bevt_6_ta_ph = nullptr;
beq->bevt_7_ta_ph = nullptr;
beq->bevt_8_ta_ph = nullptr;
beq->bevt_9_ta_ph = nullptr;
beq->bevt_10_ta_ph = nullptr;
beq->bevt_11_ta_ph = nullptr;
beq->bevt_12_ta_ph = nullptr;
beq->bevt_13_ta_ph = nullptr;
beq->bevt_14_ta_ph = nullptr;
beq->bevt_15_ta_ph = nullptr;
beq->bevt_16_ta_ph = nullptr;
beq->bevt_17_ta_ph = nullptr;
beq->bevt_18_ta_ph = nullptr;
beq->bevt_19_ta_ph = nullptr;
beq->bevt_20_ta_ph = nullptr;
beq->bevt_21_ta_ph = nullptr;
beq->bevt_22_ta_ph = nullptr;
beq->bevt_23_ta_ph = nullptr;
beq->bevt_24_ta_ph = nullptr;
beq->bevt_25_ta_ph = nullptr;
beq->bevt_26_ta_ph = nullptr;
beq->bevt_27_ta_ph = nullptr;
beq->bevt_28_ta_ph = nullptr;
beq->bevt_29_ta_ph = nullptr;
beq->bevt_30_ta_ph = nullptr;
beq->bevt_31_ta_ph = nullptr;
beq->bevt_32_ta_ph = nullptr;
beq->bevt_33_ta_ph = nullptr;
beq->bevt_34_ta_ph = nullptr;
beq->bevt_35_ta_ph = nullptr;
beq->bevt_36_ta_ph = nullptr;
beq->bevt_37_ta_ph = nullptr;
beq->bevt_38_ta_ph = nullptr;
beq->bevt_39_ta_ph = nullptr;
beq->bevt_40_ta_ph = nullptr;
beq->bevt_41_ta_ph = nullptr;
beq->bevt_42_ta_ph = nullptr;
beq->bevt_43_ta_ph = nullptr;
beq->bevt_44_ta_ph = nullptr;
beq->bevt_45_ta_ph = nullptr;
beq->bevt_46_ta_ph = nullptr;
beq->bevt_47_ta_ph = nullptr;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(56);
beq->bevt_2_ta_ph = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString(9, {0x6D,0x71,0x53,0x74,0x61,0x74,0x65,0x55,0x70}))));
beq->bevt_2_ta_ph->bem_print_0();
if (bevp_mqtt == nullptr) {
beq->bevt_3_ta_ph = BECS_Runtime::boolTrue;
 } else { 
beq->bevt_3_ta_ph = BECS_Runtime::boolFalse;
}
if (beq->bevt_3_ta_ph->bevi_bool) {
beq->bevt_4_ta_ph = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString(10, {0x6D,0x71,0x74,0x74,0x20,0x75,0x6E,0x64,0x65,0x66}))));
beq->bevt_4_ta_ph->bem_print_0();
return this;
} 
beq->bevt_6_ta_ph = bevp_controls->bem_sizeGet_0();
beq->bevt_5_ta_ph = bevp_mqtt->bem_hasAsyncCapacity_1(beq->bevt_6_ta_ph);
if (!(beq->bevt_5_ta_ph->bevi_bool)) {
beq->bevt_7_ta_ph = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString(27, {0x6D,0x71,0x74,0x74,0x20,0x73,0x74,0x61,0x74,0x65,0x20,0x6E,0x6F,0x74,0x20,0x65,0x6E,0x6F,0x75,0x67,0x68,0x20,0x73,0x70,0x61,0x63,0x65}))));
beq->bevt_7_ta_ph->bem_print_0();
return this;
} 
beq->bevt_0_ta_loop = bevp_controls->bem_iteratorGet_0();
while (true)
 {
beq->bevt_8_ta_ph = beq->bevt_0_ta_loop->bemd_0(448214784);
if ((static_cast<BEC_2_5_4_LogicBool*>(beq->bevt_8_ta_ph))->bevi_bool) {
beq->bevl_ctl = beq->bevt_0_ta_loop->bemd_0(-119099042);
beq->bevl_conName = static_cast<BEC_2_4_6_TextString*>(beq->bevl_ctl->bemd_0(1530937685));
beq->bevt_9_ta_ph = beq->bevl_ctl->bemd_0(355723905);
beq->bevl_conPoss = static_cast<BEC_2_4_3_MathInt*>(beq->bevt_9_ta_ph->bemd_0(-1553512291));
beq->bevl_cf = nullptr;
beq->bevl_pt = nullptr;
beq->bevt_11_ta_ph = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString(2, {0x73,0x77}))));
beq->bevt_10_ta_ph = beq->bevl_conName->bem_equals_1(beq->bevt_11_ta_ph);
if (beq->bevt_10_ta_ph->bevi_bool) {
beq->bevt_14_ta_ph = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString(21, {0x68,0x6F,0x6D,0x65,0x61,0x73,0x73,0x69,0x73,0x74,0x61,0x6E,0x74,0x2F,0x73,0x77,0x69,0x74,0x63,0x68,0x2F}))));
beq->bevt_13_ta_ph = beq->bevt_14_ta_ph->bem_add_1(bevp_did);
beq->bevt_15_ta_ph = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString(1, {0x2D}))));
beq->bevt_12_ta_ph = beq->bevt_13_ta_ph->bem_add_1(beq->bevt_15_ta_ph);
beq->bevl_tpp = beq->bevt_12_ta_ph->bem_add_1(beq->bevl_conPoss);
beq->bevt_16_ta_ph = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString(6, {0x2F,0x73,0x74,0x61,0x74,0x65}))));
beq->bevl_pt = beq->bevl_tpp->bem_add_1(beq->bevt_16_ta_ph);
beq->bevt_18_ta_ph = static_cast<BEC_2_4_7_TextStrings*>(BEC_2_4_7_TextStrings::bece_BEC_2_4_7_TextStrings_bevs_inst);
beq->bevt_19_ta_ph = beq->bevl_ctl->bemd_0(-691724196);
beq->bevt_17_ta_ph = beq->bevt_18_ta_ph->bem_notEmpty_1(static_cast<BEC_2_4_6_TextString*>(beq->bevt_19_ta_ph) );
if (beq->bevt_17_ta_ph->bevi_bool) {
beq->bevt_20_ta_ph = beq->bevl_ctl->bemd_0(-691724196);
beq->bevl_cf = static_cast<BEC_2_4_6_TextString*>(beq->bevt_20_ta_ph->bemd_0(-459248972));
} 
 else  {
beq->bevl_cf = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString(3, {0x4F,0x46,0x46}))));
} 
} 
 else  {
beq->bevt_22_ta_ph = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString(3, {0x64,0x69,0x6D}))));
beq->bevt_21_ta_ph = beq->bevl_conName->bem_equals_1(beq->bevt_22_ta_ph);
if (beq->bevt_21_ta_ph->bevi_bool) {
beq->bevt_25_ta_ph = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString(20, {0x68,0x6F,0x6D,0x65,0x61,0x73,0x73,0x69,0x73,0x74,0x61,0x6E,0x74,0x2F,0x6C,0x69,0x67,0x68,0x74,0x2F}))));
beq->bevt_24_ta_ph = beq->bevt_25_ta_ph->bem_add_1(bevp_did);
beq->bevt_26_ta_ph = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString(1, {0x2D}))));
beq->bevt_23_ta_ph = beq->bevt_24_ta_ph->bem_add_1(beq->bevt_26_ta_ph);
beq->bevl_tpp = beq->bevt_23_ta_ph->bem_add_1(beq->bevl_conPoss);
beq->bevt_27_ta_ph = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString(6, {0x2F,0x73,0x74,0x61,0x74,0x65}))));
beq->bevl_pt = beq->bevl_tpp->bem_add_1(beq->bevt_27_ta_ph);
beq->bevl_cf = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString(12, {0x7B,0x20,0x22,0x73,0x74,0x61,0x74,0x65,0x22,0x3A,0x20,0x22}))));
beq->bevt_29_ta_ph = static_cast<BEC_2_4_7_TextStrings*>(BEC_2_4_7_TextStrings::bece_BEC_2_4_7_TextStrings_bevs_inst);
beq->bevt_30_ta_ph = beq->bevl_ctl->bemd_0(-691724196);
beq->bevt_28_ta_ph = beq->bevt_29_ta_ph->bem_notEmpty_1(static_cast<BEC_2_4_6_TextString*>(beq->bevt_30_ta_ph) );
if (beq->bevt_28_ta_ph->bevi_bool) {
beq->bevt_32_ta_ph = beq->bevl_ctl->bemd_0(-691724196);
beq->bevt_31_ta_ph = beq->bevt_32_ta_ph->bemd_0(-459248972);
beq->bevl_cf->bem_addValue_1(beq->bevt_31_ta_ph);
} 
 else  {
beq->bevt_33_ta_ph = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString(3, {0x4F,0x46,0x46}))));
beq->bevl_cf->bem_addValue_1(beq->bevt_33_ta_ph);
} 
beq->bevt_34_ta_ph = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString(1, {0x22}))));
beq->bevl_cf->bem_addValue_1(beq->bevt_34_ta_ph);
beq->bevt_36_ta_ph = static_cast<BEC_2_4_7_TextStrings*>(BEC_2_4_7_TextStrings::bece_BEC_2_4_7_TextStrings_bevs_inst);
beq->bevt_37_ta_ph = beq->bevl_ctl->bemd_0(-271568658);
beq->bevt_35_ta_ph = beq->bevt_36_ta_ph->bem_notEmpty_1(static_cast<BEC_2_4_6_TextString*>(beq->bevt_37_ta_ph) );
if (beq->bevt_35_ta_ph->bevi_bool) {
beq->bevt_38_ta_ph = beq->bevl_ctl->bemd_0(-271568658);
beq->bevl_inlvli = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt()))->bem_new_1(beq->bevt_38_ta_ph));
beq->bevt_39_ta_ph = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(255))));
beq->bevl_inlvli = beq->bevt_39_ta_ph->bem_subtract_1(beq->bevl_inlvli);
beq->bevt_41_ta_ph = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString(16, {0x2C,0x20,0x22,0x62,0x72,0x69,0x67,0x68,0x74,0x6E,0x65,0x73,0x73,0x22,0x3A,0x20}))));
beq->bevt_40_ta_ph = static_cast<BEC_2_4_6_TextString*>(beq->bevl_cf->bem_addValue_1(beq->bevt_41_ta_ph));
beq->bevt_42_ta_ph = beq->bevl_inlvli->bem_toString_0();
beq->bevt_40_ta_ph->bem_addValue_1(beq->bevt_42_ta_ph);
} 
beq->bevt_43_ta_ph = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString(2, {0x20,0x7D}))));
beq->bevl_cf->bem_addValue_1(beq->bevt_43_ta_ph);
} 
} 
beq->bevt_45_ta_ph = static_cast<BEC_2_4_7_TextStrings*>(BEC_2_4_7_TextStrings::bece_BEC_2_4_7_TextStrings_bevs_inst);
beq->bevt_44_ta_ph = beq->bevt_45_ta_ph->bem_notEmpty_1(beq->bevl_pt);
if (beq->bevt_44_ta_ph->bevi_bool) {
beq->bevt_47_ta_ph = static_cast<BEC_2_4_7_TextStrings*>(BEC_2_4_7_TextStrings::bece_BEC_2_4_7_TextStrings_bevs_inst);
beq->bevt_46_ta_ph = beq->bevt_47_ta_ph->bem_notEmpty_1(beq->bevl_cf);
if (beq->bevt_46_ta_ph->bevi_bool) {
beq->bevt_1_ta_anchor = BECS_Runtime::boolTrue;
} 
 else  {
beq->bevt_1_ta_anchor = BECS_Runtime::boolFalse;
} 
} 
 else  {
beq->bevt_1_ta_anchor = BECS_Runtime::boolFalse;
} 
if (beq->bevt_1_ta_anchor->bevi_bool) {
beq->bevl_cf->bem_print_0();
bevp_mqtt->bem_publishAsync_2(beq->bevl_pt, beq->bevl_cf);
} 
} 
 else  {
break;
} 
} 
return this;
}
BEC_2_8_8_EmbeddedAppShell* BEC_2_8_8_EmbeddedAppShell::bem_checkWifiAp_0() {
struct bes { BEC_2_5_4_LogicBool* bevt_0_ta_anchor; BEC_2_5_4_LogicBool* bevt_1_ta_anchor; BEC_2_5_4_LogicBool* bevt_2_ta_ph; BEC_2_8_4_EmbeddedWifi* bevt_3_ta_ph; BEC_2_5_4_LogicBool* bevt_4_ta_ph; BEC_2_4_6_TextString* bevt_5_ta_ph; BEC_2_8_4_EmbeddedWifi* bevt_6_ta_ph; BEC_2_4_6_TextString* bevt_7_ta_ph; BEC_2_5_4_LogicBool* bevt_8_ta_ph; BEC_2_8_4_EmbeddedWifi* bevt_9_ta_ph; BEC_2_5_4_LogicBool* bevt_10_ta_ph; BEC_2_4_7_TextStrings* bevt_11_ta_ph; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->bevt_0_ta_anchor = nullptr;
beq->bevt_1_ta_anchor = nullptr;
beq->bevt_2_ta_ph = nullptr;
beq->bevt_3_ta_ph = nullptr;
beq->bevt_4_ta_ph = nullptr;
beq->bevt_5_ta_ph = nullptr;
beq->bevt_6_ta_ph = nullptr;
beq->bevt_7_ta_ph = nullptr;
beq->bevt_8_ta_ph = nullptr;
beq->bevt_9_ta_ph = nullptr;
beq->bevt_10_ta_ph = nullptr;
beq->bevt_11_ta_ph = nullptr;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(13);
beq->bevt_3_ta_ph = static_cast<BEC_2_8_4_EmbeddedWifi*>(BEC_2_8_4_EmbeddedWifi::bece_BEC_2_8_4_EmbeddedWifi_bevs_inst);
beq->bevt_2_ta_ph = beq->bevt_3_ta_ph->bem_upGet_0();
if (beq->bevt_2_ta_ph->bevi_bool) {
beq->bevt_6_ta_ph = static_cast<BEC_2_8_4_EmbeddedWifi*>(BEC_2_8_4_EmbeddedWifi::bece_BEC_2_8_4_EmbeddedWifi_bevs_inst);
beq->bevt_5_ta_ph = beq->bevt_6_ta_ph->bem_modeGet_0();
beq->bevt_7_ta_ph = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString(7, {0x73,0x74,0x61,0x74,0x69,0x6F,0x6E}))));
beq->bevt_4_ta_ph = beq->bevt_5_ta_ph->bem_equals_1(beq->bevt_7_ta_ph);
if (beq->bevt_4_ta_ph->bevi_bool) {
beq->bevt_0_ta_anchor = BECS_Runtime::boolTrue;
} 
 else  {
beq->bevt_0_ta_anchor = BECS_Runtime::boolFalse;
} 
} 
 else  {
beq->bevt_0_ta_anchor = BECS_Runtime::boolFalse;
} 
if (!(beq->bevt_0_ta_anchor->bevi_bool)) {
bem_startWifi_0();
beq->bevt_9_ta_ph = static_cast<BEC_2_8_4_EmbeddedWifi*>(BEC_2_8_4_EmbeddedWifi::bece_BEC_2_8_4_EmbeddedWifi_bevs_inst);
beq->bevt_8_ta_ph = beq->bevt_9_ta_ph->bem_upGet_0();
if (!(beq->bevt_8_ta_ph->bevi_bool)) {
beq->bevt_11_ta_ph = static_cast<BEC_2_4_7_TextStrings*>(BEC_2_4_7_TextStrings::bece_BEC_2_4_7_TextStrings_bevs_inst);
beq->bevt_10_ta_ph = beq->bevt_11_ta_ph->bem_isEmpty_1(bevp_ssid);
if (beq->bevt_10_ta_ph->bevi_bool) {
beq->bevt_1_ta_anchor = BECS_Runtime::boolTrue;
} 
 else  {
if (bevp_readyForAp->bevi_bool) {
beq->bevt_1_ta_anchor = BECS_Runtime::boolTrue;
} 
 else  {
beq->bevt_1_ta_anchor = BECS_Runtime::boolFalse;
} 
} 
if (beq->bevt_1_ta_anchor->bevi_bool) {
bem_initAp_0();
} 
} 
} 
return this;
}
BEC_2_8_8_EmbeddedAppShell* BEC_2_8_8_EmbeddedAppShell::bem_initAp_0() {
struct bes { BEC_2_4_6_TextString* bevl_pinpt; BEC_2_4_6_TextString* bevl_sec; BEC_2_4_6_TextString* bevl_ssid; BEC_2_8_4_EmbeddedWifi* bevl_wifi; BEC_2_9_4_ContainerList* bevl_nets; BEC_2_6_6_SystemRandom* bevl_rand; BEC_2_4_6_TextString* bevl_finssid; BEC_2_5_4_LogicBool* bevt_0_ta_anchor; BEC_2_5_4_LogicBool* bevt_1_ta_ph; BEC_2_4_7_TextStrings* bevt_2_ta_ph; BEC_2_5_4_LogicBool* bevt_3_ta_ph; BEC_2_4_3_MathInt* bevt_4_ta_ph; BEC_2_4_3_MathInt* bevt_5_ta_ph; BEC_2_4_3_MathInt* bevt_6_ta_ph; BEC_2_4_3_MathInt* bevt_7_ta_ph; BEC_2_4_3_MathInt* bevt_8_ta_ph; BEC_2_4_3_MathInt* bevt_9_ta_ph; BEC_2_4_6_TextString* bevt_10_ta_ph; BEC_2_4_6_TextString* bevt_11_ta_ph; BEC_2_4_6_TextString* bevt_12_ta_ph; BEC_2_4_6_TextString* bevt_13_ta_ph; BEC_2_4_6_TextString* bevt_14_ta_ph; BEC_2_4_6_TextString* bevt_15_ta_ph; BEC_2_4_6_TextString* bevt_16_ta_ph; BEC_2_4_3_MathInt* bevt_17_ta_ph; BEC_2_4_3_MathInt* bevt_18_ta_ph; BEC_2_5_4_LogicBool* bevt_19_ta_ph; BEC_2_4_6_TextString* bevt_20_ta_ph; BEC_2_4_6_TextString* bevt_21_ta_ph; BEC_2_4_6_TextString* bevt_22_ta_ph; BEC_2_4_6_TextString* bevt_23_ta_ph; BEC_2_4_6_TextString* bevt_24_ta_ph; BEC_2_4_6_TextString* bevt_25_ta_ph; BEC_2_4_3_MathInt* bevt_26_ta_ph; BEC_2_4_3_MathInt* bevt_27_ta_ph; BEC_2_5_4_LogicBool* bevt_28_ta_ph; BEC_2_4_6_TextString* bevt_29_ta_ph; BEC_2_8_4_EmbeddedWifi* bevt_30_ta_ph; BEC_2_8_4_EmbeddedWifi* bevt_31_ta_ph; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->bevl_pinpt = nullptr;
beq->bevl_sec = nullptr;
beq->bevl_ssid = nullptr;
beq->bevl_wifi = nullptr;
beq->bevl_nets = nullptr;
beq->bevl_rand = nullptr;
beq->bevl_finssid = nullptr;
beq->bevt_0_ta_anchor = nullptr;
beq->bevt_1_ta_ph = nullptr;
beq->bevt_2_ta_ph = nullptr;
beq->bevt_3_ta_ph = nullptr;
beq->bevt_4_ta_ph = nullptr;
beq->bevt_5_ta_ph = nullptr;
beq->bevt_6_ta_ph = nullptr;
beq->bevt_7_ta_ph = nullptr;
beq->bevt_8_ta_ph = nullptr;
beq->bevt_9_ta_ph = nullptr;
beq->bevt_10_ta_ph = nullptr;
beq->bevt_11_ta_ph = nullptr;
beq->bevt_12_ta_ph = nullptr;
beq->bevt_13_ta_ph = nullptr;
beq->bevt_14_ta_ph = nullptr;
beq->bevt_15_ta_ph = nullptr;
beq->bevt_16_ta_ph = nullptr;
beq->bevt_17_ta_ph = nullptr;
beq->bevt_18_ta_ph = nullptr;
beq->bevt_19_ta_ph = nullptr;
beq->bevt_20_ta_ph = nullptr;
beq->bevt_21_ta_ph = nullptr;
beq->bevt_22_ta_ph = nullptr;
beq->bevt_23_ta_ph = nullptr;
beq->bevt_24_ta_ph = nullptr;
beq->bevt_25_ta_ph = nullptr;
beq->bevt_26_ta_ph = nullptr;
beq->bevt_27_ta_ph = nullptr;
beq->bevt_28_ta_ph = nullptr;
beq->bevt_29_ta_ph = nullptr;
beq->bevt_30_ta_ph = nullptr;
beq->bevt_31_ta_ph = nullptr;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(40);
bevp_apType = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString(1, {0x4F}))));
beq->bevt_2_ta_ph = static_cast<BEC_2_4_7_TextStrings*>(BEC_2_4_7_TextStrings::bece_BEC_2_4_7_TextStrings_bevs_inst);
beq->bevt_1_ta_ph = beq->bevt_2_ta_ph->bem_notEmpty_1(bevp_pin);
if (beq->bevt_1_ta_ph->bevi_bool) {
beq->bevt_4_ta_ph = bevp_pin->bem_sizeGet_0();
beq->bevt_5_ta_ph = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(16))));
if (beq->bevt_4_ta_ph->bevi_int == beq->bevt_5_ta_ph->bevi_int) {
beq->bevt_3_ta_ph = BECS_Runtime::boolTrue;
 } else { 
beq->bevt_3_ta_ph = BECS_Runtime::boolFalse;
}
if (beq->bevt_3_ta_ph->bevi_bool) {
beq->bevt_0_ta_anchor = BECS_Runtime::boolTrue;
} 
 else  {
beq->bevt_0_ta_anchor = BECS_Runtime::boolFalse;
} 
} 
 else  {
beq->bevt_0_ta_anchor = BECS_Runtime::boolFalse;
} 
if (beq->bevt_0_ta_anchor->bevi_bool) {
beq->bevt_6_ta_ph = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(0))));
beq->bevt_7_ta_ph = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(8))));
beq->bevl_pinpt = bevp_pin->bem_substring_2(beq->bevt_6_ta_ph, beq->bevt_7_ta_ph);
beq->bevt_8_ta_ph = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(8))));
beq->bevt_9_ta_ph = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(16))));
beq->bevl_sec = bevp_pin->bem_substring_2(beq->bevt_8_ta_ph, beq->bevt_9_ta_ph);
beq->bevt_10_ta_ph = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString(7, {0x43,0x61,0x73,0x6E,0x69,0x63,0x2D}))));
beq->bevl_ssid = bevp_apType->bem_add_1(beq->bevt_10_ta_ph);
beq->bevl_wifi = static_cast<BEC_2_8_4_EmbeddedWifi*>(BEC_2_8_4_EmbeddedWifi::bece_BEC_2_8_4_EmbeddedWifi_bevs_inst);
beq->bevl_nets = beq->bevl_wifi->bem_scanNetworks_0();
beq->bevl_rand = static_cast<BEC_2_6_6_SystemRandom*>(BEC_2_6_6_SystemRandom::bece_BEC_2_6_6_SystemRandom_bevs_inst);
beq->bevt_14_ta_ph = beq->bevl_ssid->bem_add_1(beq->bevl_pinpt);
beq->bevt_15_ta_ph = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString(1, {0x2D}))));
beq->bevt_13_ta_ph = beq->bevt_14_ta_ph->bem_add_1(beq->bevt_15_ta_ph);
beq->bevt_12_ta_ph = beq->bevt_13_ta_ph->bem_add_1(bevp_devCode);
beq->bevt_16_ta_ph = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString(1, {0x2D}))));
beq->bevt_11_ta_ph = beq->bevt_12_ta_ph->bem_add_1(beq->bevt_16_ta_ph);
beq->bevt_18_ta_ph = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(999))));
beq->bevt_17_ta_ph = beq->bevl_rand->bem_getIntMax_1(beq->bevt_18_ta_ph);
beq->bevl_finssid = beq->bevt_11_ta_ph->bem_add_1(beq->bevt_17_ta_ph);
while (true)
 {
beq->bevt_19_ta_ph = beq->bevl_nets->bem_has_1(beq->bevl_finssid);
if (beq->bevt_19_ta_ph->bevi_bool) {
beq->bevt_23_ta_ph = beq->bevl_ssid->bem_add_1(beq->bevl_pinpt);
beq->bevt_24_ta_ph = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString(1, {0x2D}))));
beq->bevt_22_ta_ph = beq->bevt_23_ta_ph->bem_add_1(beq->bevt_24_ta_ph);
beq->bevt_21_ta_ph = beq->bevt_22_ta_ph->bem_add_1(bevp_devCode);
beq->bevt_25_ta_ph = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString(1, {0x2D}))));
beq->bevt_20_ta_ph = beq->bevt_21_ta_ph->bem_add_1(beq->bevt_25_ta_ph);
beq->bevt_27_ta_ph = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(999))));
beq->bevt_26_ta_ph = beq->bevl_rand->bem_getIntMax_1(beq->bevt_27_ta_ph);
beq->bevl_finssid = beq->bevt_20_ta_ph->bem_add_1(beq->bevt_26_ta_ph);
} 
 else  {
break;
} 
} 
bevp_apSsid = beq->bevl_finssid;
beq->bevt_29_ta_ph = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString(1, {0x4F}))));
beq->bevt_28_ta_ph = bevp_apType->bem_equals_1(beq->bevt_29_ta_ph);
if (beq->bevt_28_ta_ph->bevi_bool) {
beq->bevt_30_ta_ph = static_cast<BEC_2_8_4_EmbeddedWifi*>(BEC_2_8_4_EmbeddedWifi::bece_BEC_2_8_4_EmbeddedWifi_bevs_inst->bem_new_2(beq->bevl_finssid, nullptr));
beq->bevt_30_ta_ph->bem_startAp_0();
} 
 else  {
beq->bevt_31_ta_ph = static_cast<BEC_2_8_4_EmbeddedWifi*>(BEC_2_8_4_EmbeddedWifi::bece_BEC_2_8_4_EmbeddedWifi_bevs_inst->bem_new_2(beq->bevl_finssid, beq->bevl_sec));
beq->bevt_31_ta_ph->bem_startAp_0();
} 
} 
return this;
}
BEC_2_8_8_EmbeddedAppShell* BEC_2_8_8_EmbeddedAppShell::bem_startWifi_0() {
struct bes { BEC_2_5_4_LogicBool* bevt_0_ta_anchor; BEC_2_5_4_LogicBool* bevt_1_ta_ph; BEC_2_4_7_TextStrings* bevt_2_ta_ph; BEC_2_5_4_LogicBool* bevt_3_ta_ph; BEC_2_4_7_TextStrings* bevt_4_ta_ph; BEC_2_4_6_TextString* bevt_5_ta_ph; BEC_2_4_6_TextString* bevt_6_ta_ph; BEC_2_4_6_TextString* bevt_7_ta_ph; BEC_2_4_6_TextString* bevt_8_ta_ph; BEC_2_4_6_TextString* bevt_9_ta_ph; BEC_2_8_4_EmbeddedWifi* bevt_10_ta_ph; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->bevt_0_ta_anchor = nullptr;
beq->bevt_1_ta_ph = nullptr;
beq->bevt_2_ta_ph = nullptr;
beq->bevt_3_ta_ph = nullptr;
beq->bevt_4_ta_ph = nullptr;
beq->bevt_5_ta_ph = nullptr;
beq->bevt_6_ta_ph = nullptr;
beq->bevt_7_ta_ph = nullptr;
beq->bevt_8_ta_ph = nullptr;
beq->bevt_9_ta_ph = nullptr;
beq->bevt_10_ta_ph = nullptr;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(12);
bevp_ssid = bevp_config->bem_get_1(bevp_shssidi);
bevp_sec = bevp_config->bem_get_1(bevp_shseci);
beq->bevt_2_ta_ph = static_cast<BEC_2_4_7_TextStrings*>(BEC_2_4_7_TextStrings::bece_BEC_2_4_7_TextStrings_bevs_inst);
beq->bevt_1_ta_ph = beq->bevt_2_ta_ph->bem_notEmpty_1(bevp_ssid);
if (beq->bevt_1_ta_ph->bevi_bool) {
beq->bevt_4_ta_ph = static_cast<BEC_2_4_7_TextStrings*>(BEC_2_4_7_TextStrings::bece_BEC_2_4_7_TextStrings_bevs_inst);
beq->bevt_3_ta_ph = beq->bevt_4_ta_ph->bem_notEmpty_1(bevp_sec);
if (beq->bevt_3_ta_ph->bevi_bool) {
beq->bevt_0_ta_anchor = BECS_Runtime::boolTrue;
} 
 else  {
beq->bevt_0_ta_anchor = BECS_Runtime::boolFalse;
} 
} 
 else  {
beq->bevt_0_ta_anchor = BECS_Runtime::boolFalse;
} 
if (beq->bevt_0_ta_anchor->bevi_bool) {
beq->bevt_8_ta_ph = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString(5, {0x73,0x73,0x69,0x64,0x20}))));
beq->bevt_7_ta_ph = beq->bevt_8_ta_ph->bem_add_1(bevp_ssid);
beq->bevt_9_ta_ph = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString(5, {0x20,0x73,0x65,0x63,0x20}))));
beq->bevt_6_ta_ph = beq->bevt_7_ta_ph->bem_add_1(beq->bevt_9_ta_ph);
beq->bevt_5_ta_ph = beq->bevt_6_ta_ph->bem_add_1(bevp_sec);
beq->bevt_5_ta_ph->bem_print_0();
bevp_app->bem_wdtFeed_0();
bevp_app->bem_yield_0();
beq->bevt_10_ta_ph = static_cast<BEC_2_8_4_EmbeddedWifi*>(BEC_2_8_4_EmbeddedWifi::bece_BEC_2_8_4_EmbeddedWifi_bevs_inst->bem_new_2(bevp_ssid, bevp_sec));
beq->bevt_10_ta_ph->bem_start_0();
} 
return this;
}
BEC_2_8_8_EmbeddedAppShell* BEC_2_8_8_EmbeddedAppShell::bem_checkWifiUp_0() {
struct bes { BEC_2_8_4_EmbeddedWifi* bevl_wifi; BEC_2_9_4_ContainerList* bevl_nets; BEC_2_5_4_LogicBool* bevt_0_ta_anchor; BEC_2_5_4_LogicBool* bevt_1_ta_anchor; BEC_2_5_4_LogicBool* bevt_2_ta_ph; BEC_2_8_4_EmbeddedWifi* bevt_3_ta_ph; BEC_2_5_4_LogicBool* bevt_4_ta_ph; BEC_2_4_7_TextStrings* bevt_5_ta_ph; BEC_2_4_6_TextString* bevt_6_ta_ph; BEC_2_5_4_LogicBool* bevt_7_ta_ph; BEC_2_4_6_TextString* bevt_8_ta_ph; BEC_2_5_4_LogicBool* bevt_9_ta_ph; BEC_2_8_4_EmbeddedWifi* bevt_10_ta_ph; BEC_2_5_4_LogicBool* bevt_11_ta_ph; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->bevl_wifi = nullptr;
beq->bevl_nets = nullptr;
beq->bevt_0_ta_anchor = nullptr;
beq->bevt_1_ta_anchor = nullptr;
beq->bevt_2_ta_ph = nullptr;
beq->bevt_3_ta_ph = nullptr;
beq->bevt_4_ta_ph = nullptr;
beq->bevt_5_ta_ph = nullptr;
beq->bevt_6_ta_ph = nullptr;
beq->bevt_7_ta_ph = nullptr;
beq->bevt_8_ta_ph = nullptr;
beq->bevt_9_ta_ph = nullptr;
beq->bevt_10_ta_ph = nullptr;
beq->bevt_11_ta_ph = nullptr;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(15);
beq->bevt_3_ta_ph = static_cast<BEC_2_8_4_EmbeddedWifi*>(BEC_2_8_4_EmbeddedWifi::bece_BEC_2_8_4_EmbeddedWifi_bevs_inst);
beq->bevt_2_ta_ph = beq->bevt_3_ta_ph->bem_isConnectedGet_0();
if (beq->bevt_2_ta_ph->bevi_bool) {
beq->bevt_0_ta_anchor = BECS_Runtime::boolTrue;
} 
 else  {
beq->bevt_5_ta_ph = static_cast<BEC_2_4_7_TextStrings*>(BEC_2_4_7_TextStrings::bece_BEC_2_4_7_TextStrings_bevs_inst);
beq->bevt_4_ta_ph = beq->bevt_5_ta_ph->bem_isEmpty_1(bevp_ssid);
if (beq->bevt_4_ta_ph->bevi_bool) {
beq->bevt_0_ta_anchor = BECS_Runtime::boolTrue;
} 
 else  {
beq->bevt_0_ta_anchor = BECS_Runtime::boolFalse;
} 
} 
if (!(beq->bevt_0_ta_anchor->bevi_bool)) {
beq->bevt_6_ta_ph = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString(26, {0x77,0x69,0x66,0x69,0x20,0x63,0x6F,0x6E,0x66,0x69,0x67,0x75,0x72,0x65,0x64,0x20,0x62,0x75,0x74,0x20,0x6E,0x6F,0x74,0x20,0x75,0x70}))));
beq->bevt_6_ta_ph->bem_print_0();
beq->bevl_wifi = static_cast<BEC_2_8_4_EmbeddedWifi*>(BEC_2_8_4_EmbeddedWifi::bece_BEC_2_8_4_EmbeddedWifi_bevs_inst);
beq->bevl_nets = beq->bevl_wifi->bem_scanNetworks_0();
beq->bevt_7_ta_ph = beq->bevl_nets->bem_has_1(bevp_ssid);
if (beq->bevt_7_ta_ph->bevi_bool) {
beq->bevt_8_ta_ph = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString(27, {0x6D,0x79,0x20,0x73,0x73,0x69,0x64,0x20,0x70,0x72,0x65,0x73,0x65,0x6E,0x74,0x2C,0x20,0x72,0x65,0x73,0x74,0x61,0x72,0x74,0x69,0x6E,0x67}))));
beq->bevt_8_ta_ph->bem_print_0();
bevp_needsFsRestart = static_cast<BEC_2_5_4_LogicBool*>(BECS_Runtime::boolTrue);
} 
} 
if (!(bevp_needsFsRestart->bevi_bool)) {
beq->bevt_10_ta_ph = static_cast<BEC_2_8_4_EmbeddedWifi*>(BEC_2_8_4_EmbeddedWifi::bece_BEC_2_8_4_EmbeddedWifi_bevs_inst);
beq->bevt_9_ta_ph = beq->bevt_10_ta_ph->bem_upGet_0();
if (beq->bevt_9_ta_ph->bevi_bool) {
if (bevp_tcpserver == nullptr) {
beq->bevt_11_ta_ph = BECS_Runtime::boolTrue;
 } else { 
beq->bevt_11_ta_ph = BECS_Runtime::boolFalse;
}
if (beq->bevt_11_ta_ph->bevi_bool) {
beq->bevt_1_ta_anchor = BECS_Runtime::boolTrue;
} 
 else  {
beq->bevt_1_ta_anchor = BECS_Runtime::boolFalse;
} 
} 
 else  {
beq->bevt_1_ta_anchor = BECS_Runtime::boolFalse;
} 
if (beq->bevt_1_ta_anchor->bevi_bool) {
bevp_needsNetworkInit = static_cast<BEC_2_5_4_LogicBool*>(BECS_Runtime::boolTrue);
} 
} 
return this;
}
BEC_2_8_8_EmbeddedAppShell* BEC_2_8_8_EmbeddedAppShell::bem_sysupdate_1(BEC_2_4_6_TextString* bevk_upurl) {
struct bes { BEC_2_4_6_TextString* beva_upurl; BEC_2_8_6_EmbeddedUpdate* bevl_eupd; BEC_2_4_6_TextString* bevt_0_ta_ph; BEC_2_4_6_TextString* bevt_1_ta_ph; BEC_2_4_6_TextString* bevt_2_ta_ph; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->beva_upurl = bevk_upurl;
beq->bevl_eupd = nullptr;
beq->bevt_0_ta_ph = nullptr;
beq->bevt_1_ta_ph = nullptr;
beq->bevt_2_ta_ph = nullptr;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(6);
beq->bevt_0_ta_ph = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString(9, {0x69,0x6E,0x20,0x75,0x70,0x64,0x61,0x74,0x65}))));
beq->bevt_0_ta_ph->bem_print_0();
beq->bevt_1_ta_ph = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString(5, {0x75,0x70,0x75,0x72,0x6C}))));
beq->bevt_1_ta_ph->bem_print_0();
beq->beva_upurl->bem_print_0();
beq->bevl_eupd = static_cast<BEC_2_8_6_EmbeddedUpdate*>(((BEC_2_8_6_EmbeddedUpdate*) (new BEC_2_8_6_EmbeddedUpdate())));
beq->bevl_eupd->bem_updateFromUrl_1(beq->beva_upurl);
beq->bevt_2_ta_ph = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString(11, {0x75,0x70,0x64,0x61,0x74,0x65,0x20,0x64,0x6F,0x6E,0x65}))));
beq->bevt_2_ta_ph->bem_print_0();
return this;
}
BEC_2_8_8_EmbeddedAppShell* BEC_2_8_8_EmbeddedAppShell::bem_handleLoop_0() {
struct bes { BEC_2_4_6_TextString* bevl_rbps; BEC_2_4_6_TextString* bevl_upurl; BEC_2_8_9_EmbeddedTCPClient* bevl_preq; BEC_2_4_6_TextString* bevl_ppay; BEC_2_4_6_TextString* bevl_pcmdres; BEC_2_6_6_SystemObject* bevl_pdce; BEC_2_5_4_LogicBool* bevt_0_ta_anchor; BEC_2_5_4_LogicBool* bevt_1_ta_anchor; BEC_2_5_4_LogicBool* bevt_2_ta_anchor; BEC_2_5_4_LogicBool* bevt_3_ta_anchor; BEC_2_5_4_LogicBool* bevt_4_ta_ph; BEC_2_5_4_LogicBool* bevt_5_ta_ph; BEC_2_4_7_TextStrings* bevt_6_ta_ph; BEC_2_5_4_LogicBool* bevt_7_ta_ph; BEC_2_4_6_TextString* bevt_8_ta_ph; BEC_2_4_6_TextString* bevt_9_ta_ph; BEC_2_4_6_TextString* bevt_10_ta_ph; BEC_2_5_4_LogicBool* bevt_11_ta_ph; BEC_2_4_3_MathInt* bevt_12_ta_ph; BEC_2_5_4_LogicBool* bevt_13_ta_ph; BEC_2_4_6_TextString* bevt_14_ta_ph; BEC_2_5_4_LogicBool* bevt_15_ta_ph; BEC_2_4_3_MathInt* bevt_16_ta_ph; BEC_2_5_4_LogicBool* bevt_17_ta_ph; BEC_2_8_4_EmbeddedWifi* bevt_18_ta_ph; BEC_2_5_4_LogicBool* bevt_19_ta_ph; BEC_2_4_3_MathInt* bevt_20_ta_ph; BEC_2_5_4_LogicBool* bevt_21_ta_ph; BEC_2_4_3_MathInt* bevt_22_ta_ph; BEC_2_5_4_LogicBool* bevt_23_ta_ph; BEC_2_5_4_LogicBool* bevt_24_ta_ph; BEC_2_4_6_TextString* bevt_25_ta_ph; BEC_2_8_4_EmbeddedWifi* bevt_26_ta_ph; BEC_2_8_4_EmbeddedWifi* bevt_27_ta_ph; BEC_2_5_4_LogicBool* bevt_28_ta_ph; BEC_2_4_3_MathInt* bevt_29_ta_ph; BEC_2_5_4_LogicBool* bevt_30_ta_ph; BEC_2_5_4_LogicBool* bevt_31_ta_ph; BEC_2_4_7_TextStrings* bevt_32_ta_ph; BEC_2_5_4_LogicBool* bevt_33_ta_ph; BEC_2_5_4_LogicBool* bevt_34_ta_ph; BEC_2_4_3_MathInt* bevt_35_ta_ph; BEC_2_5_4_LogicBool* bevt_36_ta_ph; BEC_2_5_4_LogicBool* bevt_37_ta_ph; BEC_2_5_4_LogicBool* bevt_38_ta_ph; BEC_2_5_4_LogicBool* bevt_39_ta_ph; BEC_2_5_4_LogicBool* bevt_40_ta_ph; BEC_2_4_7_TextStrings* bevt_41_ta_ph; BEC_2_4_6_TextString* bevt_42_ta_ph; BEC_2_4_6_TextString* bevt_43_ta_ph; BEC_2_5_4_LogicBool* bevt_44_ta_ph; BEC_2_4_7_TextStrings* bevt_45_ta_ph; BEC_2_4_6_TextString* bevt_46_ta_ph; BEC_2_4_6_TextString* bevt_47_ta_ph; BEC_2_4_6_TextString* bevt_48_ta_ph; BEC_2_4_6_TextString* bevt_49_ta_ph; BEC_2_4_6_TextString* bevt_50_ta_ph; BEC_2_5_4_LogicBool* bevt_51_ta_ph; BEC_2_5_4_LogicBool* bevt_52_ta_ph; BEC_2_5_4_LogicBool* bevt_53_ta_ph; BEC_2_5_4_LogicBool* bevt_54_ta_ph; BEC_2_5_4_LogicBool* bevt_55_ta_ph; BEC_2_5_4_LogicBool* bevt_56_ta_ph; BEC_2_4_3_MathInt* bevt_57_ta_ph; BEC_2_6_6_SystemObject* bevt_58_ta_ph; BEC_2_5_4_LogicBool* bevt_59_ta_ph; BEC_2_5_4_LogicBool* bevt_60_ta_ph; BEC_2_4_6_TextString* bevt_61_ta_ph; BEC_2_4_3_MathInt* bevt_62_ta_ph; BEC_2_4_6_TextString* bevt_63_ta_ph; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->bevl_rbps = nullptr;
beq->bevl_upurl = nullptr;
beq->bevl_preq = nullptr;
beq->bevl_ppay = nullptr;
beq->bevl_pcmdres = nullptr;
beq->bevl_pdce = nullptr;
beq->bevt_0_ta_anchor = nullptr;
beq->bevt_1_ta_anchor = nullptr;
beq->bevt_2_ta_anchor = nullptr;
beq->bevt_3_ta_anchor = nullptr;
beq->bevt_4_ta_ph = nullptr;
beq->bevt_5_ta_ph = nullptr;
beq->bevt_6_ta_ph = nullptr;
beq->bevt_7_ta_ph = nullptr;
beq->bevt_8_ta_ph = nullptr;
beq->bevt_9_ta_ph = nullptr;
beq->bevt_10_ta_ph = nullptr;
beq->bevt_11_ta_ph = nullptr;
beq->bevt_12_ta_ph = nullptr;
beq->bevt_13_ta_ph = nullptr;
beq->bevt_14_ta_ph = nullptr;
beq->bevt_15_ta_ph = nullptr;
beq->bevt_16_ta_ph = nullptr;
beq->bevt_17_ta_ph = nullptr;
beq->bevt_18_ta_ph = nullptr;
beq->bevt_19_ta_ph = nullptr;
beq->bevt_20_ta_ph = nullptr;
beq->bevt_21_ta_ph = nullptr;
beq->bevt_22_ta_ph = nullptr;
beq->bevt_23_ta_ph = nullptr;
beq->bevt_24_ta_ph = nullptr;
beq->bevt_25_ta_ph = nullptr;
beq->bevt_26_ta_ph = nullptr;
beq->bevt_27_ta_ph = nullptr;
beq->bevt_28_ta_ph = nullptr;
beq->bevt_29_ta_ph = nullptr;
beq->bevt_30_ta_ph = nullptr;
beq->bevt_31_ta_ph = nullptr;
beq->bevt_32_ta_ph = nullptr;
beq->bevt_33_ta_ph = nullptr;
beq->bevt_34_ta_ph = nullptr;
beq->bevt_35_ta_ph = nullptr;
beq->bevt_36_ta_ph = nullptr;
beq->bevt_37_ta_ph = nullptr;
beq->bevt_38_ta_ph = nullptr;
beq->bevt_39_ta_ph = nullptr;
beq->bevt_40_ta_ph = nullptr;
beq->bevt_41_ta_ph = nullptr;
beq->bevt_42_ta_ph = nullptr;
beq->bevt_43_ta_ph = nullptr;
beq->bevt_44_ta_ph = nullptr;
beq->bevt_45_ta_ph = nullptr;
beq->bevt_46_ta_ph = nullptr;
beq->bevt_47_ta_ph = nullptr;
beq->bevt_48_ta_ph = nullptr;
beq->bevt_49_ta_ph = nullptr;
beq->bevt_50_ta_ph = nullptr;
beq->bevt_51_ta_ph = nullptr;
beq->bevt_52_ta_ph = nullptr;
beq->bevt_53_ta_ph = nullptr;
beq->bevt_54_ta_ph = nullptr;
beq->bevt_55_ta_ph = nullptr;
beq->bevt_56_ta_ph = nullptr;
beq->bevt_57_ta_ph = nullptr;
beq->bevt_58_ta_ph = nullptr;
beq->bevt_59_ta_ph = nullptr;
beq->bevt_60_ta_ph = nullptr;
beq->bevt_61_ta_ph = nullptr;
beq->bevt_62_ta_ph = nullptr;
beq->bevt_63_ta_ph = nullptr;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(71);
bevp_app->bem_wdtFeed_0();
bevp_app->bem_yield_0();
bevp_app->bem_uptime_1(bevp_nowup);
if (bevp_resetByPin == nullptr) {
beq->bevt_4_ta_ph = BECS_Runtime::boolTrue;
 } else { 
beq->bevt_4_ta_ph = BECS_Runtime::boolFalse;
}
if (beq->bevt_4_ta_ph->bevi_bool) {

          std::string rbps = BE_RESETBYPIN;
          beq->bevl_rbps = new BEC_2_4_6_TextString(rbps);
          beq->bevt_6_ta_ph = static_cast<BEC_2_4_7_TextStrings*>(BEC_2_4_7_TextStrings::bece_BEC_2_4_7_TextStrings_bevs_inst);
beq->bevt_5_ta_ph = beq->bevt_6_ta_ph->bem_notEmpty_1(beq->bevl_rbps);
if (beq->bevt_5_ta_ph->bevi_bool) {
beq->bevt_8_ta_ph = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString(2, {0x6F,0x6E}))));
beq->bevt_7_ta_ph = beq->bevl_rbps->bem_equals_1(beq->bevt_8_ta_ph);
if (beq->bevt_7_ta_ph->bevi_bool) {
beq->bevt_0_ta_anchor = BECS_Runtime::boolTrue;
} 
 else  {
beq->bevt_0_ta_anchor = BECS_Runtime::boolFalse;
} 
} 
 else  {
beq->bevt_0_ta_anchor = BECS_Runtime::boolFalse;
} 
if (beq->bevt_0_ta_anchor->bevi_bool) {
bevp_resetByPin = static_cast<BEC_2_5_4_LogicBool*>(BECS_Runtime::boolTrue);
} 
 else  {
bevp_resetByPin = static_cast<BEC_2_5_4_LogicBool*>(BECS_Runtime::boolFalse);
} 
beq->bevt_10_ta_ph = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString(15, {0x72,0x65,0x73,0x65,0x74,0x42,0x79,0x50,0x69,0x6E,0x20,0x73,0x65,0x74,0x20}))));
beq->bevt_9_ta_ph = beq->bevt_10_ta_ph->bem_add_1(bevp_resetByPin);
beq->bevt_9_ta_ph->bem_print_0();
return this;
} 
if (bevp_needsNetworkInit->bevi_bool) {
bevp_needsNetworkInit = static_cast<BEC_2_5_4_LogicBool*>(BECS_Runtime::boolFalse);
bem_networkInit_0();
return this;
} 
if (bevp_needsBuildControls->bevi_bool) {
bevp_needsBuildControls = static_cast<BEC_2_5_4_LogicBool*>(BECS_Runtime::boolFalse);
bem_buildControls_0();
return this;
} 
if (bevp_needsInitControls->bevi_bool) {
bevp_needsInitControls = static_cast<BEC_2_5_4_LogicBool*>(BECS_Runtime::boolFalse);
bem_initControls_0();
bevp_needsStateUp = static_cast<BEC_2_5_4_LogicBool*>(BECS_Runtime::boolFalse);
return this;
} 
if (bevp_needsGc->bevi_bool) {
bevp_needsGc = static_cast<BEC_2_5_4_LogicBool*>(BECS_Runtime::boolFalse);
bevp_app->bem_maybeGc_0();
return this;
} 
if (bevp_nowup->bevi_int > bevp_nextMaybeSave->bevi_int) {
beq->bevt_11_ta_ph = BECS_Runtime::boolTrue;
 } else { 
beq->bevt_11_ta_ph = BECS_Runtime::boolFalse;
}
if (beq->bevt_11_ta_ph->bevi_bool) {
beq->bevt_12_ta_ph = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(45000))));
bevp_nextMaybeSave = bevp_nowup->bem_add_1(beq->bevt_12_ta_ph);
beq->bevt_13_ta_ph = bevp_config->bem_changedGet_0();
if (beq->bevt_13_ta_ph->bevi_bool) {
beq->bevt_14_ta_ph = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString(16, {0x6D,0x61,0x79,0x62,0x65,0x53,0x61,0x76,0x65,0x20,0x63,0x6F,0x6E,0x66,0x69,0x67}))));
beq->bevt_14_ta_ph->bem_print_0();
bevp_config->bem_maybeSave_0();
} 
bevp_needsGc = static_cast<BEC_2_5_4_LogicBool*>(BECS_Runtime::boolTrue);
return this;
} 
if (bevp_nowup->bevi_int > bevp_nextApCheck->bevi_int) {
beq->bevt_15_ta_ph = BECS_Runtime::boolTrue;
 } else { 
beq->bevt_15_ta_ph = BECS_Runtime::boolFalse;
}
if (beq->bevt_15_ta_ph->bevi_bool) {
beq->bevt_16_ta_ph = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(240000))));
bevp_nextApCheck = bevp_nowup->bem_add_1(beq->bevt_16_ta_ph);
if (!(bevp_readyForAp->bevi_bool)) {
bevp_readyForAp = static_cast<BEC_2_5_4_LogicBool*>(BECS_Runtime::boolTrue);
beq->bevt_18_ta_ph = static_cast<BEC_2_8_4_EmbeddedWifi*>(BEC_2_8_4_EmbeddedWifi::bece_BEC_2_8_4_EmbeddedWifi_bevs_inst);
beq->bevt_17_ta_ph = beq->bevt_18_ta_ph->bem_upGet_0();
if (!(beq->bevt_17_ta_ph->bevi_bool)) {
bevp_needsNetworkInit = static_cast<BEC_2_5_4_LogicBool*>(BECS_Runtime::boolTrue);
} 
} 
return this;
} 
if (bevp_nowup->bevi_int > bevp_nextWifiCheck->bevi_int) {
beq->bevt_19_ta_ph = BECS_Runtime::boolTrue;
 } else { 
beq->bevt_19_ta_ph = BECS_Runtime::boolFalse;
}
if (beq->bevt_19_ta_ph->bevi_bool) {
beq->bevt_20_ta_ph = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(300000))));
bevp_nextWifiCheck = bevp_nowup->bem_add_1(beq->bevt_20_ta_ph);
bem_checkWifiUp_0();
return this;
} 
if (bevp_nowup->bevi_int > bevp_nextSwInfo->bevi_int) {
beq->bevt_21_ta_ph = BECS_Runtime::boolTrue;
 } else { 
beq->bevt_21_ta_ph = BECS_Runtime::boolFalse;
}
if (beq->bevt_21_ta_ph->bevi_bool) {
beq->bevt_22_ta_ph = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(540000))));
bevp_nextSwInfo = bevp_nowup->bem_add_1(beq->bevt_22_ta_ph);
bevp_swInfo->bem_print_0();
return this;
} 
if (bevp_nextRestart->bevi_int > bevp_zero->bevi_int) {
beq->bevt_23_ta_ph = BECS_Runtime::boolTrue;
 } else { 
beq->bevt_23_ta_ph = BECS_Runtime::boolFalse;
}
if (beq->bevt_23_ta_ph->bevi_bool) {
if (bevp_nowup->bevi_int > bevp_nextRestart->bevi_int) {
beq->bevt_24_ta_ph = BECS_Runtime::boolTrue;
 } else { 
beq->bevt_24_ta_ph = BECS_Runtime::boolFalse;
}
if (beq->bevt_24_ta_ph->bevi_bool) {
beq->bevt_1_ta_anchor = BECS_Runtime::boolTrue;
} 
 else  {
beq->bevt_1_ta_anchor = BECS_Runtime::boolFalse;
} 
} 
 else  {
beq->bevt_1_ta_anchor = BECS_Runtime::boolFalse;
} 
if (beq->bevt_1_ta_anchor->bevi_bool) {
beq->bevt_25_ta_ph = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString(27, {0x72,0x65,0x73,0x74,0x61,0x72,0x74,0x69,0x6E,0x67,0x20,0x66,0x72,0x6F,0x6D,0x20,0x6E,0x65,0x78,0x74,0x52,0x65,0x73,0x74,0x61,0x72,0x74}))));
beq->bevt_25_ta_ph->bem_print_0();
beq->bevt_26_ta_ph = static_cast<BEC_2_8_4_EmbeddedWifi*>(BEC_2_8_4_EmbeddedWifi::bece_BEC_2_8_4_EmbeddedWifi_bevs_inst);
beq->bevt_26_ta_ph->bem_stop_0();
beq->bevt_27_ta_ph = static_cast<BEC_2_8_4_EmbeddedWifi*>(BEC_2_8_4_EmbeddedWifi::bece_BEC_2_8_4_EmbeddedWifi_bevs_inst);
beq->bevt_27_ta_ph->bem_clearAll_0();
bevp_app->bem_restart_0();
return this;
} 
if (bevp_nowup->bevi_int > bevp_nextUpdateCheck->bevi_int) {
beq->bevt_28_ta_ph = BECS_Runtime::boolTrue;
 } else { 
beq->bevt_28_ta_ph = BECS_Runtime::boolFalse;
}
if (beq->bevt_28_ta_ph->bevi_bool) {
beq->bevt_29_ta_ph = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(60000))));
bevp_nextUpdateCheck = bevp_nowup->bem_add_1(beq->bevt_29_ta_ph);
if (bevp_supurl == nullptr) {
beq->bevt_30_ta_ph = BECS_Runtime::boolFalse;
 } else { 
beq->bevt_30_ta_ph = BECS_Runtime::boolTrue;
}
if (beq->bevt_30_ta_ph->bevi_bool) {
beq->bevt_32_ta_ph = static_cast<BEC_2_4_7_TextStrings*>(BEC_2_4_7_TextStrings::bece_BEC_2_4_7_TextStrings_bevs_inst);
beq->bevt_31_ta_ph = beq->bevt_32_ta_ph->bem_notEmpty_1(bevp_supurl);
if (beq->bevt_31_ta_ph->bevi_bool) {
beq->bevt_2_ta_anchor = BECS_Runtime::boolTrue;
} 
 else  {
beq->bevt_2_ta_anchor = BECS_Runtime::boolFalse;
} 
} 
 else  {
beq->bevt_2_ta_anchor = BECS_Runtime::boolFalse;
} 
if (beq->bevt_2_ta_anchor->bevi_bool) {
beq->bevl_upurl = bevp_supurl;
bevp_supurl = nullptr;
bem_sysupdate_1(beq->bevl_upurl);
} 
return this;
} 
if (bevp_needsMqConfUp->bevi_bool) {
bevp_needsMqConfUp = static_cast<BEC_2_5_4_LogicBool*>(BECS_Runtime::boolFalse);
beq->bevt_33_ta_ph = static_cast<BEC_2_5_4_LogicBool*>(BECS_Runtime::boolFalse);
bem_mqConfUp_1(beq->bevt_33_ta_ph);
bevp_needsGc = static_cast<BEC_2_5_4_LogicBool*>(BECS_Runtime::boolTrue);
return this;
} 
if (bevp_nowup->bevi_int > bevp_nextMq->bevi_int) {
beq->bevt_34_ta_ph = BECS_Runtime::boolTrue;
 } else { 
beq->bevt_34_ta_ph = BECS_Runtime::boolFalse;
}
if (beq->bevt_34_ta_ph->bevi_bool) {
beq->bevt_35_ta_ph = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(11000))));
bevp_nextMq = bevp_nowup->bem_add_1(beq->bevt_35_ta_ph);
if (bevp_mqtt == nullptr) {
beq->bevt_36_ta_ph = BECS_Runtime::boolFalse;
 } else { 
beq->bevt_36_ta_ph = BECS_Runtime::boolTrue;
}
if (beq->bevt_36_ta_ph->bevi_bool) {
beq->bevt_37_ta_ph = bevp_mqtt->bem_isOpenGet_0();
if (beq->bevt_37_ta_ph->bevi_bool) {
beq->bevt_3_ta_anchor = BECS_Runtime::boolTrue;
} 
 else  {
beq->bevt_3_ta_anchor = BECS_Runtime::boolFalse;
} 
} 
 else  {
beq->bevt_3_ta_anchor = BECS_Runtime::boolFalse;
} 
if (!(beq->bevt_3_ta_anchor->bevi_bool)) {
bem_initMq_0();
} 
 else  {
if (bevp_needsStateUpSoon->bevi_bool) {
bevp_needsStateUpSoon = static_cast<BEC_2_5_4_LogicBool*>(BECS_Runtime::boolFalse);
bevp_needsStateUp = static_cast<BEC_2_5_4_LogicBool*>(BECS_Runtime::boolTrue);
} 
} 
return this;
} 
if (bevp_tcpserver == nullptr) {
beq->bevt_38_ta_ph = BECS_Runtime::boolFalse;
 } else { 
beq->bevt_38_ta_ph = BECS_Runtime::boolTrue;
}
if (beq->bevt_38_ta_ph->bevi_bool) {
beq->bevl_preq = bevp_tcpserver->bem_checkGetClient_0();
if (beq->bevl_preq == nullptr) {
beq->bevt_39_ta_ph = BECS_Runtime::boolFalse;
 } else { 
beq->bevt_39_ta_ph = BECS_Runtime::boolTrue;
}
if (beq->bevt_39_ta_ph->bevi_bool) {
beq->bevl_ppay = beq->bevl_preq->bem_checkGetPayload_2(bevp_readBuf, bevp_slashn);
beq->bevt_41_ta_ph = static_cast<BEC_2_4_7_TextStrings*>(BEC_2_4_7_TextStrings::bece_BEC_2_4_7_TextStrings_bevs_inst);
beq->bevt_40_ta_ph = beq->bevt_41_ta_ph->bem_notEmpty_1(beq->bevl_ppay);
if (beq->bevt_40_ta_ph->bevi_bool) {
try  {
beq->bevt_42_ta_ph = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString(3, {0x74,0x63,0x70}))));
beq->bevt_43_ta_ph = beq->bevl_preq->bem_remoteIpGet_0();
beq->bevl_pcmdres = bem_doCmd_3(beq->bevt_42_ta_ph, beq->bevt_43_ta_ph, beq->bevl_ppay);
beq->bevt_45_ta_ph = static_cast<BEC_2_4_7_TextStrings*>(BEC_2_4_7_TextStrings::bece_BEC_2_4_7_TextStrings_bevs_inst);
beq->bevt_44_ta_ph = beq->bevt_45_ta_ph->bem_isEmpty_1(beq->bevl_pcmdres);
if (beq->bevt_44_ta_ph->bevi_bool) {
beq->bevt_46_ta_ph = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString(13, {0x70,0x63,0x6D,0x64,0x72,0x65,0x73,0x20,0x65,0x6D,0x70,0x74,0x79}))));
beq->bevt_46_ta_ph->bem_print_0();
} 
 else  {
beq->bevt_48_ta_ph = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString(8, {0x70,0x63,0x6D,0x64,0x72,0x65,0x73,0x20}))));
beq->bevt_47_ta_ph = beq->bevt_48_ta_ph->bem_add_1(beq->bevl_pcmdres);
beq->bevt_47_ta_ph->bem_print_0();
beq->bevl_preq->bem_write_1(beq->bevl_pcmdres);
beq->bevl_preq->bem_write_1(bevp_slashr);
beq->bevl_preq->bem_write_1(bevp_slashn);
beq->bevt_49_ta_ph = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString(17, {0x70,0x63,0x6D,0x64,0x72,0x65,0x73,0x20,0x73,0x65,0x6E,0x64,0x20,0x64,0x6F,0x6E,0x65}))));
beq->bevt_49_ta_ph->bem_print_0();
} 
} 
 catch (BECS_ThrowBack beve_0) {
beq->bevl_pdce = BECS_ThrowBack::handleThrow(beve_0);
beq->bevt_50_ta_ph = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString(22, {0x65,0x72,0x72,0x6F,0x72,0x20,0x68,0x61,0x6E,0x64,0x6C,0x69,0x6E,0x67,0x20,0x63,0x6F,0x6D,0x6D,0x61,0x6E,0x64}))));
beq->bevt_50_ta_ph->bem_print_0();
beq->bevl_pdce->bemd_0(1701756138);
} 
} 
beq->bevl_preq->bem_close_0();
return this;
} 
} 
if (bevp_conserver == nullptr) {
beq->bevt_51_ta_ph = BECS_Runtime::boolFalse;
 } else { 
beq->bevt_51_ta_ph = BECS_Runtime::boolTrue;
}
if (beq->bevt_51_ta_ph->bevi_bool) {
if (bevp_concon == nullptr) {
beq->bevt_52_ta_ph = BECS_Runtime::boolTrue;
 } else { 
beq->bevt_52_ta_ph = BECS_Runtime::boolFalse;
}
if (beq->bevt_52_ta_ph->bevi_bool) {
bevp_concon = bevp_conserver->bem_checkGetClient_0();
} 
 else  {
beq->bevt_53_ta_ph = bevp_concon->bem_connectedGet_0();
if (!(beq->bevt_53_ta_ph->bevi_bool)) {
bevp_concon = nullptr;
} 
} 
} 
if (bevp_mqtt == nullptr) {
beq->bevt_54_ta_ph = BECS_Runtime::boolFalse;
 } else { 
beq->bevt_54_ta_ph = BECS_Runtime::boolTrue;
}
if (beq->bevt_54_ta_ph->bevi_bool) {
beq->bevt_55_ta_ph = bevp_mqtt->bem_handleAsync_1(this);
if (beq->bevt_55_ta_ph->bevi_bool) {
bevp_needsGc = static_cast<BEC_2_5_4_LogicBool*>(BECS_Runtime::boolTrue);
return this;
} 
} 
bevp_looperI->bevi_int = bevp_zero->bevi_int;
while (true)
 {
beq->bevt_57_ta_ph = bevp_loopers->bem_sizeGet_0();
if (bevp_looperI->bevi_int < beq->bevt_57_ta_ph->bevi_int) {
beq->bevt_56_ta_ph = BECS_Runtime::boolTrue;
 } else { 
beq->bevt_56_ta_ph = BECS_Runtime::boolFalse;
}
if (beq->bevt_56_ta_ph->bevi_bool) {
beq->bevt_58_ta_ph = bevp_loopers->bem_get_1(bevp_looperI);
beq->bevt_58_ta_ph->bemd_0(-330685574);
bevp_looperI->bevi_int++;
} 
 else  {
break;
} 
} 
if (bevp_needsStateUp->bevi_bool) {
bevp_needsStateUp = static_cast<BEC_2_5_4_LogicBool*>(BECS_Runtime::boolFalse);
if (bevp_mqtt == nullptr) {
beq->bevt_59_ta_ph = BECS_Runtime::boolFalse;
 } else { 
beq->bevt_59_ta_ph = BECS_Runtime::boolTrue;
}
if (beq->bevt_59_ta_ph->bevi_bool) {
bem_mqStateUp_0();
} 
bevp_needsGc = static_cast<BEC_2_5_4_LogicBool*>(BECS_Runtime::boolTrue);
return this;
} 
if (bevp_mdserver == nullptr) {
beq->bevt_60_ta_ph = BECS_Runtime::boolFalse;
 } else { 
beq->bevt_60_ta_ph = BECS_Runtime::boolTrue;
}
if (beq->bevt_60_ta_ph->bevi_bool) {
bevp_mdserver->bem_update_0();
} 
if (bevp_needsRestart->bevi_bool) {
bevp_needsRestart = static_cast<BEC_2_5_4_LogicBool*>(BECS_Runtime::boolFalse);
beq->bevt_61_ta_ph = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString(25, {0x70,0x72,0x65,0x70,0x20,0x72,0x65,0x73,0x74,0x61,0x72,0x74,0x20,0x6E,0x65,0x65,0x64,0x73,0x52,0x65,0x73,0x74,0x61,0x72,0x74}))));
beq->bevt_61_ta_ph->bem_print_0();
beq->bevt_62_ta_ph = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(2000))));
bevp_nextRestart = bevp_nowup->bem_add_1(beq->bevt_62_ta_ph);
} 
if (bevp_needsFsRestart->bevi_bool) {
bevp_needsFsRestart = static_cast<BEC_2_5_4_LogicBool*>(BECS_Runtime::boolFalse);
beq->bevt_63_ta_ph = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString(16, {0x6D,0x61,0x79,0x62,0x65,0x53,0x61,0x76,0x65,0x20,0x63,0x6F,0x6E,0x66,0x69,0x67}))));
beq->bevt_63_ta_ph->bem_print_0();
bevp_config->bem_maybeSave_0();
bevp_needsRestart = static_cast<BEC_2_5_4_LogicBool*>(BECS_Runtime::boolTrue);
} 
return this;
}
BEC_2_8_8_EmbeddedAppShell* BEC_2_8_8_EmbeddedAppShell::bem_handleMqtt_2(BEC_2_4_6_TextString* bevk_topic, BEC_2_4_6_TextString* bevk_payload) {
struct bes { BEC_2_4_6_TextString* beva_topic; BEC_2_4_6_TextString* beva_payload; BEC_2_9_4_ContainerList* bevl_twl; BEC_2_4_6_TextString* bevl_cid; BEC_2_9_4_ContainerList* bevl_cl; BEC_2_4_6_TextString* bevl_cps; BEC_2_4_3_MathInt* bevl_cp; BEC_2_9_4_ContainerList* bevl_cmdl; BEC_2_4_6_TextString* bevl_res; BEC_2_5_4_LogicBool* bevt_0_ta_anchor; BEC_2_5_4_LogicBool* bevt_1_ta_anchor; BEC_2_5_4_LogicBool* bevt_2_ta_anchor; BEC_2_5_4_LogicBool* bevt_3_ta_anchor; BEC_2_4_6_TextString* bevt_4_ta_ph; BEC_2_5_4_LogicBool* bevt_5_ta_ph; BEC_2_4_7_TextStrings* bevt_6_ta_ph; BEC_2_5_4_LogicBool* bevt_7_ta_ph; BEC_2_4_7_TextStrings* bevt_8_ta_ph; BEC_2_4_6_TextString* bevt_9_ta_ph; BEC_2_4_6_TextString* bevt_10_ta_ph; BEC_2_4_6_TextString* bevt_11_ta_ph; BEC_2_4_6_TextString* bevt_12_ta_ph; BEC_2_4_6_TextString* bevt_13_ta_ph; BEC_2_5_4_LogicBool* bevt_14_ta_ph; BEC_2_4_6_TextString* bevt_15_ta_ph; BEC_2_5_4_LogicBool* bevt_16_ta_ph; BEC_2_4_6_TextString* bevt_17_ta_ph; BEC_2_5_4_LogicBool* bevt_18_ta_ph; BEC_2_4_6_TextString* bevt_19_ta_ph; BEC_2_4_6_TextString* bevt_20_ta_ph; BEC_2_5_4_LogicBool* bevt_21_ta_ph; BEC_2_4_3_MathInt* bevt_22_ta_ph; BEC_2_4_3_MathInt* bevt_23_ta_ph; BEC_2_4_3_MathInt* bevt_24_ta_ph; BEC_2_4_6_TextString* bevt_25_ta_ph; BEC_2_5_4_LogicBool* bevt_26_ta_ph; BEC_2_4_3_MathInt* bevt_27_ta_ph; BEC_2_4_3_MathInt* bevt_28_ta_ph; BEC_2_4_3_MathInt* bevt_29_ta_ph; BEC_2_5_4_LogicBool* bevt_30_ta_ph; BEC_2_4_7_TextStrings* bevt_31_ta_ph; BEC_2_5_4_LogicBool* bevt_32_ta_ph; BEC_2_4_6_TextString* bevt_33_ta_ph; BEC_2_4_6_TextString* bevt_34_ta_ph; BEC_2_5_4_LogicBool* bevt_35_ta_ph; BEC_2_5_4_LogicBool* bevt_36_ta_ph; BEC_2_4_3_MathInt* bevt_37_ta_ph; BEC_2_6_6_SystemObject* bevt_38_ta_ph; BEC_2_5_4_LogicBool* bevt_39_ta_ph; BEC_2_4_6_TextString* bevt_40_ta_ph; BEC_2_4_6_TextString* bevt_41_ta_ph; BEC_2_5_4_LogicBool* bevt_42_ta_ph; BEC_2_4_3_MathInt* bevt_43_ta_ph; BEC_2_4_3_MathInt* bevt_44_ta_ph; BEC_2_6_6_SystemObject* bevt_45_ta_ph; BEC_2_6_6_SystemObject* bevt_46_ta_ph; BEC_2_4_3_MathInt* bevt_47_ta_ph; BEC_2_4_6_TextString* bevt_48_ta_ph; BEC_2_4_3_MathInt* bevt_49_ta_ph; BEC_2_6_6_SystemObject* bevt_50_ta_ph; BEC_2_6_6_SystemObject* bevt_51_ta_ph; BEC_2_4_3_MathInt* bevt_52_ta_ph; BEC_2_4_6_TextString* bevt_53_ta_ph; BEC_2_4_3_MathInt* bevt_54_ta_ph; BEC_2_4_6_TextString* bevt_55_ta_ph; BEC_2_4_6_TextString* bevt_56_ta_ph; BEC_2_5_4_LogicBool* bevt_57_ta_ph; BEC_2_4_6_TextString* bevt_58_ta_ph; BEC_2_4_6_TextString* bevt_59_ta_ph; BEC_2_4_6_TextString* bevt_60_ta_ph; BEC_2_4_6_TextString* bevt_61_ta_ph; BEC_2_4_6_TextString* bevt_62_ta_ph; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->beva_topic = bevk_topic;
beq->beva_payload = bevk_payload;
beq->bevl_twl = nullptr;
beq->bevl_cid = nullptr;
beq->bevl_cl = nullptr;
beq->bevl_cps = nullptr;
beq->bevl_cp = nullptr;
beq->bevl_cmdl = nullptr;
beq->bevl_res = nullptr;
beq->bevt_0_ta_anchor = nullptr;
beq->bevt_1_ta_anchor = nullptr;
beq->bevt_2_ta_anchor = nullptr;
beq->bevt_3_ta_anchor = nullptr;
beq->bevt_4_ta_ph = nullptr;
beq->bevt_5_ta_ph = nullptr;
beq->bevt_6_ta_ph = nullptr;
beq->bevt_7_ta_ph = nullptr;
beq->bevt_8_ta_ph = nullptr;
beq->bevt_9_ta_ph = nullptr;
beq->bevt_10_ta_ph = nullptr;
beq->bevt_11_ta_ph = nullptr;
beq->bevt_12_ta_ph = nullptr;
beq->bevt_13_ta_ph = nullptr;
beq->bevt_14_ta_ph = nullptr;
beq->bevt_15_ta_ph = nullptr;
beq->bevt_16_ta_ph = nullptr;
beq->bevt_17_ta_ph = nullptr;
beq->bevt_18_ta_ph = nullptr;
beq->bevt_19_ta_ph = nullptr;
beq->bevt_20_ta_ph = nullptr;
beq->bevt_21_ta_ph = nullptr;
beq->bevt_22_ta_ph = nullptr;
beq->bevt_23_ta_ph = nullptr;
beq->bevt_24_ta_ph = nullptr;
beq->bevt_25_ta_ph = nullptr;
beq->bevt_26_ta_ph = nullptr;
beq->bevt_27_ta_ph = nullptr;
beq->bevt_28_ta_ph = nullptr;
beq->bevt_29_ta_ph = nullptr;
beq->bevt_30_ta_ph = nullptr;
beq->bevt_31_ta_ph = nullptr;
beq->bevt_32_ta_ph = nullptr;
beq->bevt_33_ta_ph = nullptr;
beq->bevt_34_ta_ph = nullptr;
beq->bevt_35_ta_ph = nullptr;
beq->bevt_36_ta_ph = nullptr;
beq->bevt_37_ta_ph = nullptr;
beq->bevt_38_ta_ph = nullptr;
beq->bevt_39_ta_ph = nullptr;
beq->bevt_40_ta_ph = nullptr;
beq->bevt_41_ta_ph = nullptr;
beq->bevt_42_ta_ph = nullptr;
beq->bevt_43_ta_ph = nullptr;
beq->bevt_44_ta_ph = nullptr;
beq->bevt_45_ta_ph = nullptr;
beq->bevt_46_ta_ph = nullptr;
beq->bevt_47_ta_ph = nullptr;
beq->bevt_48_ta_ph = nullptr;
beq->bevt_49_ta_ph = nullptr;
beq->bevt_50_ta_ph = nullptr;
beq->bevt_51_ta_ph = nullptr;
beq->bevt_52_ta_ph = nullptr;
beq->bevt_53_ta_ph = nullptr;
beq->bevt_54_ta_ph = nullptr;
beq->bevt_55_ta_ph = nullptr;
beq->bevt_56_ta_ph = nullptr;
beq->bevt_57_ta_ph = nullptr;
beq->bevt_58_ta_ph = nullptr;
beq->bevt_59_ta_ph = nullptr;
beq->bevt_60_ta_ph = nullptr;
beq->bevt_61_ta_ph = nullptr;
beq->bevt_62_ta_ph = nullptr;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(73);
beq->bevt_4_ta_ph = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString(8, {0x67,0x6F,0x74,0x20,0x6D,0x71,0x74,0x74}))));
beq->bevt_4_ta_ph->bem_print_0();
beq->bevt_6_ta_ph = static_cast<BEC_2_4_7_TextStrings*>(BEC_2_4_7_TextStrings::bece_BEC_2_4_7_TextStrings_bevs_inst);
beq->bevt_5_ta_ph = beq->bevt_6_ta_ph->bem_notEmpty_1(beq->beva_topic);
if (beq->bevt_5_ta_ph->bevi_bool) {
beq->bevt_8_ta_ph = static_cast<BEC_2_4_7_TextStrings*>(BEC_2_4_7_TextStrings::bece_BEC_2_4_7_TextStrings_bevs_inst);
beq->bevt_7_ta_ph = beq->bevt_8_ta_ph->bem_notEmpty_1(beq->beva_payload);
if (beq->bevt_7_ta_ph->bevi_bool) {
beq->bevt_0_ta_anchor = BECS_Runtime::boolTrue;
} 
 else  {
beq->bevt_0_ta_anchor = BECS_Runtime::boolFalse;
} 
} 
 else  {
beq->bevt_0_ta_anchor = BECS_Runtime::boolFalse;
} 
if (beq->bevt_0_ta_anchor->bevi_bool) {
beq->bevt_12_ta_ph = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString(7, {0x54,0x6F,0x70,0x69,0x63,0x3A,0x20}))));
beq->bevt_11_ta_ph = beq->bevt_12_ta_ph->bem_add_1(beq->beva_topic);
beq->bevt_13_ta_ph = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString(10, {0x20,0x50,0x61,0x79,0x6C,0x6F,0x61,0x64,0x3A,0x20}))));
beq->bevt_10_ta_ph = beq->bevt_11_ta_ph->bem_add_1(beq->bevt_13_ta_ph);
beq->bevt_9_ta_ph = beq->bevt_10_ta_ph->bem_add_1(beq->beva_payload);
beq->bevt_9_ta_ph->bem_print_0();
beq->bevt_15_ta_ph = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString(20, {0x68,0x6F,0x6D,0x65,0x61,0x73,0x73,0x69,0x73,0x74,0x61,0x6E,0x74,0x2F,0x73,0x74,0x61,0x74,0x75,0x73}))));
beq->bevt_14_ta_ph = beq->beva_topic->bem_equals_1(beq->bevt_15_ta_ph);
if (beq->bevt_14_ta_ph->bevi_bool) {
beq->bevt_17_ta_ph = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString(6, {0x6F,0x6E,0x6C,0x69,0x6E,0x65}))));
beq->bevt_16_ta_ph = beq->beva_payload->bem_equals_1(beq->bevt_17_ta_ph);
if (beq->bevt_16_ta_ph->bevi_bool) {
beq->bevt_1_ta_anchor = BECS_Runtime::boolTrue;
} 
 else  {
beq->bevt_1_ta_anchor = BECS_Runtime::boolFalse;
} 
} 
 else  {
beq->bevt_1_ta_anchor = BECS_Runtime::boolFalse;
} 
if (beq->bevt_1_ta_anchor->bevi_bool) {
bevp_needsGc = static_cast<BEC_2_5_4_LogicBool*>(BECS_Runtime::boolTrue);
bevp_needsMqConfUp = static_cast<BEC_2_5_4_LogicBool*>(BECS_Runtime::boolTrue);
} 
 else  {
beq->bevt_19_ta_ph = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString(4, {0x2F,0x73,0x65,0x74}))));
beq->bevt_18_ta_ph = beq->beva_topic->bem_ends_1(beq->bevt_19_ta_ph);
if (beq->bevt_18_ta_ph->bevi_bool) {
beq->bevt_20_ta_ph = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString(1, {0x2F}))));
beq->bevl_twl = beq->beva_topic->bem_split_1(beq->bevt_20_ta_ph);
beq->bevt_22_ta_ph = beq->bevl_twl->bem_sizeGet_0();
beq->bevt_23_ta_ph = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(4))));
if (beq->bevt_22_ta_ph->bevi_int == beq->bevt_23_ta_ph->bevi_int) {
beq->bevt_21_ta_ph = BECS_Runtime::boolTrue;
 } else { 
beq->bevt_21_ta_ph = BECS_Runtime::boolFalse;
}
if (beq->bevt_21_ta_ph->bevi_bool) {
beq->bevt_24_ta_ph = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(2))));
beq->bevl_cid = static_cast<BEC_2_4_6_TextString*>(beq->bevl_twl->bem_get_1(beq->bevt_24_ta_ph));
beq->bevt_25_ta_ph = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString(1, {0x2D}))));
beq->bevl_cl = beq->bevl_cid->bem_split_1(beq->bevt_25_ta_ph);
beq->bevt_27_ta_ph = beq->bevl_cl->bem_sizeGet_0();
beq->bevt_28_ta_ph = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(2))));
if (beq->bevt_27_ta_ph->bevi_int == beq->bevt_28_ta_ph->bevi_int) {
beq->bevt_26_ta_ph = BECS_Runtime::boolTrue;
 } else { 
beq->bevt_26_ta_ph = BECS_Runtime::boolFalse;
}
if (beq->bevt_26_ta_ph->bevi_bool) {
beq->bevt_29_ta_ph = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(1))));
beq->bevl_cps = static_cast<BEC_2_4_6_TextString*>(beq->bevl_cl->bem_get_1(beq->bevt_29_ta_ph));
beq->bevt_31_ta_ph = static_cast<BEC_2_4_7_TextStrings*>(BEC_2_4_7_TextStrings::bece_BEC_2_4_7_TextStrings_bevs_inst);
beq->bevt_30_ta_ph = beq->bevt_31_ta_ph->bem_notEmpty_1(beq->bevl_cps);
if (beq->bevt_30_ta_ph->bevi_bool) {
beq->bevt_32_ta_ph = beq->bevl_cps->bem_isIntegerGet_0();
if (beq->bevt_32_ta_ph->bevi_bool) {
beq->bevt_2_ta_anchor = BECS_Runtime::boolTrue;
} 
 else  {
beq->bevt_2_ta_anchor = BECS_Runtime::boolFalse;
} 
} 
 else  {
beq->bevt_2_ta_anchor = BECS_Runtime::boolFalse;
} 
if (beq->bevt_2_ta_anchor->bevi_bool) {
beq->bevl_cp = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt()))->bem_new_1(beq->bevl_cps));
beq->bevt_34_ta_ph = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString(7, {0x67,0x6F,0x74,0x20,0x63,0x70,0x20}))));
beq->bevt_33_ta_ph = beq->bevt_34_ta_ph->bem_add_1(beq->bevl_cps);
beq->bevt_33_ta_ph->bem_print_0();
if (bevp_controls == nullptr) {
beq->bevt_35_ta_ph = BECS_Runtime::boolFalse;
 } else { 
beq->bevt_35_ta_ph = BECS_Runtime::boolTrue;
}
if (beq->bevt_35_ta_ph->bevi_bool) {
beq->bevt_37_ta_ph = bevp_controls->bem_sizeGet_0();
if (beq->bevl_cp->bevi_int < beq->bevt_37_ta_ph->bevi_int) {
beq->bevt_36_ta_ph = BECS_Runtime::boolTrue;
 } else { 
beq->bevt_36_ta_ph = BECS_Runtime::boolFalse;
}
if (beq->bevt_36_ta_ph->bevi_bool) {
beq->bevt_3_ta_anchor = BECS_Runtime::boolTrue;
} 
 else  {
beq->bevt_3_ta_anchor = BECS_Runtime::boolFalse;
} 
} 
 else  {
beq->bevt_3_ta_anchor = BECS_Runtime::boolFalse;
} 
if (beq->bevt_3_ta_anchor->bevi_bool) {
beq->bevt_38_ta_ph = bevp_controls->bem_get_1(beq->bevl_cp);
beq->bevt_38_ta_ph->bemd_2(785325488, beq->beva_topic, beq->beva_payload);
} 
} 
} 
} 
} 
 else  {
beq->bevt_40_ta_ph = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString(3, {0x63,0x6D,0x64}))));
beq->bevt_39_ta_ph = beq->beva_topic->bem_ends_1(beq->bevt_40_ta_ph);
if (beq->bevt_39_ta_ph->bevi_bool) {
beq->bevt_41_ta_ph = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString(1, {0x20}))));
beq->bevl_cmdl = beq->beva_payload->bem_split_1(beq->bevt_41_ta_ph);
beq->bevt_43_ta_ph = beq->bevl_cmdl->bem_sizeGet_0();
beq->bevt_44_ta_ph = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(1))));
if (beq->bevt_43_ta_ph->bevi_int > beq->bevt_44_ta_ph->bevi_int) {
beq->bevt_42_ta_ph = BECS_Runtime::boolTrue;
 } else { 
beq->bevt_42_ta_ph = BECS_Runtime::boolFalse;
}
if (beq->bevt_42_ta_ph->bevi_bool) {
beq->bevt_47_ta_ph = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(1))));
beq->bevt_46_ta_ph = beq->bevl_cmdl->bem_get_1(beq->bevt_47_ta_ph);
beq->bevt_48_ta_ph = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString(4, {0x70,0x61,0x73,0x73}))));
beq->bevt_45_ta_ph = beq->bevt_46_ta_ph->bemd_1(643138569, beq->bevt_48_ta_ph);
if ((static_cast<BEC_2_5_4_LogicBool*>(beq->bevt_45_ta_ph))->bevi_bool) {
beq->bevt_49_ta_ph = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(1))));
beq->bevl_cmdl->bem_put_2(beq->bevt_49_ta_ph, bevp_pass);
} 
 else  {
beq->bevt_52_ta_ph = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(1))));
beq->bevt_51_ta_ph = beq->bevl_cmdl->bem_get_1(beq->bevt_52_ta_ph);
beq->bevt_53_ta_ph = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString(5, {0x73,0x70,0x61,0x73,0x73}))));
beq->bevt_50_ta_ph = beq->bevt_51_ta_ph->bemd_1(643138569, beq->bevt_53_ta_ph);
if ((static_cast<BEC_2_5_4_LogicBool*>(beq->bevt_50_ta_ph))->bevi_bool) {
beq->bevt_54_ta_ph = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(1))));
beq->bevl_cmdl->bem_put_2(beq->bevt_54_ta_ph, bevp_spass);
} 
} 
beq->bevt_55_ta_ph = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString(4, {0x6D,0x71,0x74,0x74}))));
beq->bevt_56_ta_ph = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString(0, {}))));
beq->bevl_res = bem_doCmdl_3(beq->bevt_55_ta_ph, beq->bevt_56_ta_ph, beq->bevl_cmdl);
if (beq->bevl_res == nullptr) {
beq->bevt_57_ta_ph = BECS_Runtime::boolFalse;
 } else { 
beq->bevt_57_ta_ph = BECS_Runtime::boolTrue;
}
if (beq->bevt_57_ta_ph->bevi_bool) {
beq->bevt_60_ta_ph = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString(5, {0x63,0x6E,0x63,0x6D,0x2F}))));
beq->bevt_59_ta_ph = beq->bevt_60_ta_ph->bem_add_1(bevp_did);
beq->bevt_61_ta_ph = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString(4, {0x2F,0x72,0x65,0x73}))));
beq->bevt_58_ta_ph = beq->bevt_59_ta_ph->bem_add_1(beq->bevt_61_ta_ph);
bevp_mqtt->bem_publishAsync_2(beq->bevt_58_ta_ph, beq->bevl_res);
} 
} 
} 
} 
} 
bevp_needsGc = static_cast<BEC_2_5_4_LogicBool*>(BECS_Runtime::boolTrue);
} 
 else  {
beq->bevt_62_ta_ph = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString(22, {0x54,0x6F,0x70,0x69,0x63,0x20,0x6F,0x72,0x20,0x50,0x61,0x79,0x6C,0x6F,0x61,0x64,0x20,0x45,0x6D,0x70,0x74,0x79}))));
beq->bevt_62_ta_ph->bem_print_0();
} 
return this;
}
BEC_2_4_6_TextString* BEC_2_8_8_EmbeddedAppShell::bem_doCmd_3(BEC_2_4_6_TextString* bevk_channel, BEC_2_4_6_TextString* bevk_origin, BEC_2_4_6_TextString* bevk_cmdline) {
struct bes { BEC_2_4_6_TextString* beva_channel; BEC_2_4_6_TextString* beva_origin; BEC_2_4_6_TextString* beva_cmdline; BEC_2_9_4_ContainerList* bevl_cmdl; BEC_2_5_4_LogicBool* bevt_0_ta_anchor; BEC_2_5_4_LogicBool* bevt_1_ta_anchor; BEC_2_5_4_LogicBool* bevt_2_ta_ph; BEC_2_4_7_TextStrings* bevt_3_ta_ph; BEC_2_4_6_TextString* bevt_4_ta_ph; BEC_2_5_4_LogicBool* bevt_5_ta_ph; BEC_2_4_7_TextStrings* bevt_6_ta_ph; BEC_2_4_6_TextString* bevt_7_ta_ph; BEC_2_4_6_TextString* bevt_8_ta_ph; BEC_2_4_6_TextString* bevt_9_ta_ph; BEC_2_4_6_TextString* bevt_10_ta_ph; BEC_2_5_4_LogicBool* bevt_11_ta_ph; BEC_2_4_3_MathInt* bevt_12_ta_ph; BEC_2_4_3_MathInt* bevt_13_ta_ph; BEC_2_6_6_SystemObject* bevt_14_ta_ph; BEC_2_6_6_SystemObject* bevt_15_ta_ph; BEC_2_4_3_MathInt* bevt_16_ta_ph; BEC_2_4_6_TextString* bevt_17_ta_ph; BEC_2_6_6_SystemObject* bevt_18_ta_ph; BEC_2_6_6_SystemObject* bevt_19_ta_ph; BEC_2_4_3_MathInt* bevt_20_ta_ph; BEC_2_4_6_TextString* bevt_21_ta_ph; BEC_2_4_6_TextString* bevt_22_ta_ph; BEC_2_4_6_TextString* bevt_23_ta_ph; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->beva_channel = bevk_channel;
beq->beva_origin = bevk_origin;
beq->beva_cmdline = bevk_cmdline;
beq->bevl_cmdl = nullptr;
beq->bevt_0_ta_anchor = nullptr;
beq->bevt_1_ta_anchor = nullptr;
beq->bevt_2_ta_ph = nullptr;
beq->bevt_3_ta_ph = nullptr;
beq->bevt_4_ta_ph = nullptr;
beq->bevt_5_ta_ph = nullptr;
beq->bevt_6_ta_ph = nullptr;
beq->bevt_7_ta_ph = nullptr;
beq->bevt_8_ta_ph = nullptr;
beq->bevt_9_ta_ph = nullptr;
beq->bevt_10_ta_ph = nullptr;
beq->bevt_11_ta_ph = nullptr;
beq->bevt_12_ta_ph = nullptr;
beq->bevt_13_ta_ph = nullptr;
beq->bevt_14_ta_ph = nullptr;
beq->bevt_15_ta_ph = nullptr;
beq->bevt_16_ta_ph = nullptr;
beq->bevt_17_ta_ph = nullptr;
beq->bevt_18_ta_ph = nullptr;
beq->bevt_19_ta_ph = nullptr;
beq->bevt_20_ta_ph = nullptr;
beq->bevt_21_ta_ph = nullptr;
beq->bevt_22_ta_ph = nullptr;
beq->bevt_23_ta_ph = nullptr;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(29);
bevp_app->bem_wdtFeed_0();
bevp_app->bem_yield_0();
beq->bevt_3_ta_ph = static_cast<BEC_2_4_7_TextStrings*>(BEC_2_4_7_TextStrings::bece_BEC_2_4_7_TextStrings_bevs_inst);
beq->bevt_2_ta_ph = beq->bevt_3_ta_ph->bem_isEmpty_1(beq->beva_cmdline);
if (beq->bevt_2_ta_ph->bevi_bool) {
beq->bevt_4_ta_ph = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString(13, {0x63,0x6D,0x64,0x6C,0x69,0x6E,0x65,0x20,0x65,0x6D,0x70,0x74,0x79}))));
return beq->bevt_4_ta_ph;
} 
beq->bevt_6_ta_ph = static_cast<BEC_2_4_7_TextStrings*>(BEC_2_4_7_TextStrings::bece_BEC_2_4_7_TextStrings_bevs_inst);
beq->bevt_5_ta_ph = beq->bevt_6_ta_ph->bem_isEmpty_1(beq->beva_channel);
if (beq->bevt_5_ta_ph->bevi_bool) {
beq->bevt_7_ta_ph = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString(13, {0x63,0x68,0x61,0x6E,0x6E,0x65,0x6C,0x20,0x65,0x6D,0x70,0x74,0x79}))));
return beq->bevt_7_ta_ph;
} 
beq->bevt_8_ta_ph = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString(11, {0x63,0x6D,0x64,0x20,0x63,0x68,0x61,0x6E,0x6E,0x65,0x6C}))));
beq->bevt_8_ta_ph->bem_print_0();
beq->beva_channel->bem_print_0();
beq->bevt_9_ta_ph = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString(7, {0x63,0x6D,0x64,0x6C,0x69,0x6E,0x65}))));
beq->bevt_9_ta_ph->bem_print_0();
beq->beva_cmdline->bem_print_0();
beq->bevt_10_ta_ph = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString(1, {0x20}))));
beq->bevl_cmdl = beq->beva_cmdline->bem_split_1(beq->bevt_10_ta_ph);
beq->bevt_12_ta_ph = beq->bevl_cmdl->bem_sizeGet_0();
beq->bevt_13_ta_ph = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(0))));
if (beq->bevt_12_ta_ph->bevi_int > beq->bevt_13_ta_ph->bevi_int) {
beq->bevt_11_ta_ph = BECS_Runtime::boolTrue;
 } else { 
beq->bevt_11_ta_ph = BECS_Runtime::boolFalse;
}
if (beq->bevt_11_ta_ph->bevi_bool) {
beq->bevt_16_ta_ph = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(0))));
beq->bevt_15_ta_ph = beq->bevl_cmdl->bem_get_1(beq->bevt_16_ta_ph);
beq->bevt_17_ta_ph = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString(3, {0x73,0x70,0x32}))));
beq->bevt_14_ta_ph = beq->bevt_15_ta_ph->bemd_1(643138569, beq->bevt_17_ta_ph);
if ((static_cast<BEC_2_5_4_LogicBool*>(beq->bevt_14_ta_ph))->bevi_bool) {
beq->bevt_1_ta_anchor = BECS_Runtime::boolTrue;
} 
 else  {
beq->bevt_1_ta_anchor = BECS_Runtime::boolFalse;
} 
} 
 else  {
beq->bevt_1_ta_anchor = BECS_Runtime::boolFalse;
} 
if (beq->bevt_1_ta_anchor->bevi_bool) {
beq->bevt_0_ta_anchor = BECS_Runtime::boolTrue;
} 
 else  {
beq->bevt_20_ta_ph = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(0))));
beq->bevt_19_ta_ph = beq->bevl_cmdl->bem_get_1(beq->bevt_20_ta_ph);
beq->bevt_21_ta_ph = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString(3, {0x61,0x70,0x32}))));
beq->bevt_18_ta_ph = beq->bevt_19_ta_ph->bemd_1(643138569, beq->bevt_21_ta_ph);
if ((static_cast<BEC_2_5_4_LogicBool*>(beq->bevt_18_ta_ph))->bevi_bool) {
beq->bevt_0_ta_anchor = BECS_Runtime::boolTrue;
} 
 else  {
beq->bevt_0_ta_anchor = BECS_Runtime::boolFalse;
} 
} 
if (beq->bevt_0_ta_anchor->bevi_bool) {
beq->bevt_22_ta_ph = bem_doCmdlSec_3(beq->beva_channel, beq->beva_origin, beq->bevl_cmdl);
return beq->bevt_22_ta_ph;
} 
beq->bevt_23_ta_ph = bem_doCmdl_3(beq->beva_channel, beq->beva_origin, beq->bevl_cmdl);
return beq->bevt_23_ta_ph;
}
BEC_2_4_6_TextString* BEC_2_8_8_EmbeddedAppShell::bem_doCmdlSec_3(BEC_2_4_6_TextString* bevk_channel, BEC_2_4_6_TextString* bevk_origin, BEC_2_9_4_ContainerList* bevk_cmdl) {
struct bes { BEC_2_4_6_TextString* beva_channel; BEC_2_4_6_TextString* beva_origin; BEC_2_9_4_ContainerList* beva_cmdl; BEC_2_9_4_ContainerList* bevl_cmdn; BEC_2_4_6_TextString* bevl_hdone; BEC_2_4_6_TextString* bevl_spw; BEC_2_4_6_TextString* bevl_tohash; BEC_2_4_3_MathInt* bevl_toc; BEC_2_4_6_TextString* bevl_sp; BEC_2_4_3_MathInt* bevl_j; BEC_2_4_3_MathInt* bevl_i; BEC_2_5_4_LogicBool* bevt_0_ta_anchor; BEC_2_5_4_LogicBool* bevt_1_ta_ph; BEC_2_4_3_MathInt* bevt_2_ta_ph; BEC_2_4_3_MathInt* bevt_3_ta_ph; BEC_2_4_6_TextString* bevt_4_ta_ph; BEC_2_6_6_SystemObject* bevt_5_ta_ph; BEC_2_6_6_SystemObject* bevt_6_ta_ph; BEC_2_4_3_MathInt* bevt_7_ta_ph; BEC_2_4_6_TextString* bevt_8_ta_ph; BEC_2_6_6_SystemObject* bevt_9_ta_ph; BEC_2_6_6_SystemObject* bevt_10_ta_ph; BEC_2_4_3_MathInt* bevt_11_ta_ph; BEC_2_4_6_TextString* bevt_12_ta_ph; BEC_2_4_6_TextString* bevt_13_ta_ph; BEC_2_4_6_TextString* bevt_14_ta_ph; BEC_2_6_6_SystemObject* bevt_15_ta_ph; BEC_2_4_3_MathInt* bevt_16_ta_ph; BEC_2_5_4_LogicBool* bevt_17_ta_ph; BEC_2_4_7_TextStrings* bevt_18_ta_ph; BEC_2_6_6_SystemObject* bevt_19_ta_ph; BEC_2_6_6_SystemObject* bevt_20_ta_ph; BEC_2_6_6_SystemObject* bevt_21_ta_ph; BEC_2_6_6_SystemObject* bevt_22_ta_ph; BEC_2_6_6_SystemObject* bevt_23_ta_ph; BEC_2_4_3_MathInt* bevt_24_ta_ph; BEC_2_4_6_TextString* bevt_25_ta_ph; BEC_2_4_6_TextString* bevt_26_ta_ph; BEC_2_4_6_TextString* bevt_27_ta_ph; BEC_2_4_3_MathInt* bevt_28_ta_ph; BEC_2_4_3_MathInt* bevt_29_ta_ph; BEC_2_5_4_LogicBool* bevt_30_ta_ph; BEC_2_4_6_TextString* bevt_31_ta_ph; BEC_2_6_6_SystemObject* bevt_32_ta_ph; BEC_2_5_4_LogicBool* bevt_33_ta_ph; BEC_2_4_7_TextStrings* bevt_34_ta_ph; BEC_2_5_4_LogicBool* bevt_35_ta_ph; BEC_2_4_7_TextStrings* bevt_36_ta_ph; BEC_2_6_6_SystemObject* bevt_37_ta_ph; BEC_2_4_3_MathInt* bevt_38_ta_ph; BEC_2_5_4_LogicBool* bevt_39_ta_ph; BEC_2_6_6_SystemObject* bevt_40_ta_ph; BEC_2_4_3_MathInt* bevt_41_ta_ph; BEC_2_4_6_TextString* bevt_42_ta_ph; BEC_2_4_3_MathInt* bevt_43_ta_ph; BEC_2_5_4_LogicBool* bevt_44_ta_ph; BEC_2_4_3_MathInt* bevt_45_ta_ph; BEC_2_6_6_SystemObject* bevt_46_ta_ph; BEC_2_4_6_TextString* bevt_47_ta_ph; BEC_2_4_6_TextString* bevt_48_ta_ph; BEC_2_4_6_TextString* bevt_49_ta_ph; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->beva_channel = bevk_channel;
beq->beva_origin = bevk_origin;
beq->beva_cmdl = bevk_cmdl;
beq->bevl_cmdn = nullptr;
beq->bevl_hdone = nullptr;
beq->bevl_spw = nullptr;
beq->bevl_tohash = nullptr;
beq->bevl_toc = nullptr;
beq->bevl_sp = nullptr;
beq->bevl_j = nullptr;
beq->bevl_i = nullptr;
beq->bevt_0_ta_anchor = nullptr;
beq->bevt_1_ta_ph = nullptr;
beq->bevt_2_ta_ph = nullptr;
beq->bevt_3_ta_ph = nullptr;
beq->bevt_4_ta_ph = nullptr;
beq->bevt_5_ta_ph = nullptr;
beq->bevt_6_ta_ph = nullptr;
beq->bevt_7_ta_ph = nullptr;
beq->bevt_8_ta_ph = nullptr;
beq->bevt_9_ta_ph = nullptr;
beq->bevt_10_ta_ph = nullptr;
beq->bevt_11_ta_ph = nullptr;
beq->bevt_12_ta_ph = nullptr;
beq->bevt_13_ta_ph = nullptr;
beq->bevt_14_ta_ph = nullptr;
beq->bevt_15_ta_ph = nullptr;
beq->bevt_16_ta_ph = nullptr;
beq->bevt_17_ta_ph = nullptr;
beq->bevt_18_ta_ph = nullptr;
beq->bevt_19_ta_ph = nullptr;
beq->bevt_20_ta_ph = nullptr;
beq->bevt_21_ta_ph = nullptr;
beq->bevt_22_ta_ph = nullptr;
beq->bevt_23_ta_ph = nullptr;
beq->bevt_24_ta_ph = nullptr;
beq->bevt_25_ta_ph = nullptr;
beq->bevt_26_ta_ph = nullptr;
beq->bevt_27_ta_ph = nullptr;
beq->bevt_28_ta_ph = nullptr;
beq->bevt_29_ta_ph = nullptr;
beq->bevt_30_ta_ph = nullptr;
beq->bevt_31_ta_ph = nullptr;
beq->bevt_32_ta_ph = nullptr;
beq->bevt_33_ta_ph = nullptr;
beq->bevt_34_ta_ph = nullptr;
beq->bevt_35_ta_ph = nullptr;
beq->bevt_36_ta_ph = nullptr;
beq->bevt_37_ta_ph = nullptr;
beq->bevt_38_ta_ph = nullptr;
beq->bevt_39_ta_ph = nullptr;
beq->bevt_40_ta_ph = nullptr;
beq->bevt_41_ta_ph = nullptr;
beq->bevt_42_ta_ph = nullptr;
beq->bevt_43_ta_ph = nullptr;
beq->bevt_44_ta_ph = nullptr;
beq->bevt_45_ta_ph = nullptr;
beq->bevt_46_ta_ph = nullptr;
beq->bevt_47_ta_ph = nullptr;
beq->bevt_48_ta_ph = nullptr;
beq->bevt_49_ta_ph = nullptr;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(62);
beq->bevt_2_ta_ph = beq->beva_cmdl->bem_sizeGet_0();
beq->bevt_3_ta_ph = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(4))));
if (beq->bevt_2_ta_ph->bevi_int > beq->bevt_3_ta_ph->bevi_int) {
beq->bevt_1_ta_ph = BECS_Runtime::boolTrue;
 } else { 
beq->bevt_1_ta_ph = BECS_Runtime::boolFalse;
}
if (beq->bevt_1_ta_ph->bevi_bool) {
beq->bevl_cmdn = static_cast<BEC_2_9_4_ContainerList*>(((BEC_2_9_4_ContainerList*) (new BEC_2_9_4_ContainerList()))->bem_new_0());
beq->bevt_4_ta_ph = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString(13, {0x64,0x6F,0x69,0x6E,0x67,0x20,0x63,0x6D,0x64,0x6C,0x73,0x65,0x63}))));
beq->bevt_4_ta_ph->bem_print_0();
beq->bevl_spw = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString(0, {}))));
beq->bevt_7_ta_ph = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(0))));
beq->bevt_6_ta_ph = beq->beva_cmdl->bem_get_1(beq->bevt_7_ta_ph);
beq->bevt_8_ta_ph = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString(3, {0x73,0x70,0x32}))));
beq->bevt_5_ta_ph = beq->bevt_6_ta_ph->bemd_1(643138569, beq->bevt_8_ta_ph);
if ((static_cast<BEC_2_5_4_LogicBool*>(beq->bevt_5_ta_ph))->bevi_bool) {
beq->bevl_spw = bevp_spass;
} 
 else  {
beq->bevt_11_ta_ph = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(0))));
beq->bevt_10_ta_ph = beq->beva_cmdl->bem_get_1(beq->bevt_11_ta_ph);
beq->bevt_12_ta_ph = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString(3, {0x61,0x70,0x32}))));
beq->bevt_9_ta_ph = beq->bevt_10_ta_ph->bemd_1(643138569, beq->bevt_12_ta_ph);
if ((static_cast<BEC_2_5_4_LogicBool*>(beq->bevt_9_ta_ph))->bevi_bool) {
beq->bevl_spw = bevp_pass;
} 
 else  {
beq->bevt_14_ta_ph = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString(17, {0x75,0x6E,0x6B,0x6E,0x6F,0x77,0x6E,0x20,0x73,0x65,0x63,0x73,0x63,0x65,0x6D,0x65,0x20}))));
beq->bevt_16_ta_ph = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(0))));
beq->bevt_15_ta_ph = beq->beva_cmdl->bem_get_1(beq->bevt_16_ta_ph);
beq->bevt_13_ta_ph = beq->bevt_14_ta_ph->bem_add_1(beq->bevt_15_ta_ph);
beq->bevt_13_ta_ph->bem_print_0();
} 
} 
beq->bevt_18_ta_ph = static_cast<BEC_2_4_7_TextStrings*>(BEC_2_4_7_TextStrings::bece_BEC_2_4_7_TextStrings_bevs_inst);
beq->bevt_17_ta_ph = beq->bevt_18_ta_ph->bem_notEmpty_1(beq->beva_origin);
if (beq->bevt_17_ta_ph->bevi_bool) {
} 
 else  {
beq->beva_origin = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString(0, {}))));
} 
beq->bevt_24_ta_ph = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(1))));
beq->bevt_23_ta_ph = beq->beva_cmdl->bem_get_1(beq->bevt_24_ta_ph);
beq->bevt_25_ta_ph = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString(1, {0x2C}))));
beq->bevt_22_ta_ph = beq->bevt_23_ta_ph->bemd_1(202420412, beq->bevt_25_ta_ph);
beq->bevt_21_ta_ph = beq->bevt_22_ta_ph->bemd_1(202420412, beq->beva_origin);
beq->bevt_26_ta_ph = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString(1, {0x2C}))));
beq->bevt_20_ta_ph = beq->bevt_21_ta_ph->bemd_1(202420412, beq->bevt_26_ta_ph);
beq->bevt_19_ta_ph = beq->bevt_20_ta_ph->bemd_1(202420412, beq->bevl_spw);
beq->bevt_27_ta_ph = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString(1, {0x2C}))));
beq->bevl_tohash = static_cast<BEC_2_4_6_TextString*>(beq->bevt_19_ta_ph->bemd_1(202420412, beq->bevt_27_ta_ph));
beq->bevt_28_ta_ph = beq->beva_cmdl->bem_sizeGet_0();
beq->bevt_29_ta_ph = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(1))));
beq->bevl_toc = beq->bevt_28_ta_ph->bem_subtract_1(beq->bevt_29_ta_ph);
beq->bevl_sp = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString(1, {0x20}))));
beq->bevl_j = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(3))));
while (true)
 {
if (beq->bevl_j->bevi_int < beq->bevl_toc->bevi_int) {
beq->bevt_30_ta_ph = BECS_Runtime::boolTrue;
 } else { 
beq->bevt_30_ta_ph = BECS_Runtime::boolFalse;
}
if (beq->bevt_30_ta_ph->bevi_bool) {
beq->bevt_32_ta_ph = beq->beva_cmdl->bem_get_1(beq->bevl_j);
beq->bevt_31_ta_ph = static_cast<BEC_2_4_6_TextString*>(beq->bevl_tohash->bem_addValue_1(beq->bevt_32_ta_ph));
beq->bevt_31_ta_ph->bem_addValue_1(beq->bevl_sp);
beq->bevl_j->bevi_int++;
} 
 else  {
break;
} 
} 

      String lip = sha1(beq->bevl_tohash->bems_toCcString().c_str());
      std::string lips = std::string(lip.c_str());
      beq->bevl_hdone = new BEC_2_4_6_TextString(lips);
         beq->bevt_34_ta_ph = static_cast<BEC_2_4_7_TextStrings*>(BEC_2_4_7_TextStrings::bece_BEC_2_4_7_TextStrings_bevs_inst);
beq->bevt_33_ta_ph = beq->bevt_34_ta_ph->bem_notEmpty_1(beq->bevl_hdone);
if (beq->bevt_33_ta_ph->bevi_bool) {
beq->bevt_36_ta_ph = static_cast<BEC_2_4_7_TextStrings*>(BEC_2_4_7_TextStrings::bece_BEC_2_4_7_TextStrings_bevs_inst);
beq->bevt_38_ta_ph = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(2))));
beq->bevt_37_ta_ph = beq->beva_cmdl->bem_get_1(beq->bevt_38_ta_ph);
beq->bevt_35_ta_ph = beq->bevt_36_ta_ph->bem_notEmpty_1(static_cast<BEC_2_4_6_TextString*>(beq->bevt_37_ta_ph) );
if (beq->bevt_35_ta_ph->bevi_bool) {
beq->bevt_41_ta_ph = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(2))));
beq->bevt_40_ta_ph = beq->beva_cmdl->bem_get_1(beq->bevt_41_ta_ph);
beq->bevt_39_ta_ph = beq->bevl_hdone->bem_equals_1(beq->bevt_40_ta_ph);
if (beq->bevt_39_ta_ph->bevi_bool) {
beq->bevt_0_ta_anchor = BECS_Runtime::boolTrue;
} 
 else  {
beq->bevt_0_ta_anchor = BECS_Runtime::boolFalse;
} 
} 
 else  {
beq->bevt_0_ta_anchor = BECS_Runtime::boolFalse;
} 
if (beq->bevt_0_ta_anchor->bevi_bool) {
beq->bevt_42_ta_ph = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString(11, {0x68,0x73,0x65,0x63,0x20,0x70,0x61,0x73,0x73,0x65,0x64}))));
beq->bevt_42_ta_ph->bem_print_0();
beq->bevt_43_ta_ph = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(4))));
beq->beva_cmdl->bem_put_2(beq->bevt_43_ta_ph, beq->bevl_spw);
beq->bevl_i = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(3))));
while (true)
 {
beq->bevt_45_ta_ph = beq->beva_cmdl->bem_sizeGet_0();
if (beq->bevl_i->bevi_int < beq->bevt_45_ta_ph->bevi_int) {
beq->bevt_44_ta_ph = BECS_Runtime::boolTrue;
 } else { 
beq->bevt_44_ta_ph = BECS_Runtime::boolFalse;
}
if (beq->bevt_44_ta_ph->bevi_bool) {
beq->bevt_46_ta_ph = beq->beva_cmdl->bem_get_1(beq->bevl_i);
beq->bevl_cmdn->bem_addValue_1(beq->bevt_46_ta_ph);
beq->bevl_i->bevi_int++;
} 
 else  {
break;
} 
} 
} 
 else  {
beq->bevt_47_ta_ph = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString(11, {0x68,0x73,0x65,0x63,0x20,0x66,0x61,0x69,0x6C,0x65,0x64}))));
beq->bevt_47_ta_ph->bem_print_0();
} 
} 
beq->bevt_48_ta_ph = bem_doCmdl_3(beq->beva_channel, beq->beva_origin, beq->bevl_cmdn);
return beq->bevt_48_ta_ph;
} 
beq->bevt_49_ta_ph = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString(6, {0x6E,0x6F,0x64,0x69,0x63,0x65}))));
return beq->bevt_49_ta_ph;
}
BEC_2_4_6_TextString* BEC_2_8_8_EmbeddedAppShell::bem_doCmdl_3(BEC_2_4_6_TextString* bevk_channel, BEC_2_4_6_TextString* bevk_origin, BEC_2_9_4_ContainerList* bevk_cmdl) {
struct bes { BEC_2_4_6_TextString* beva_channel; BEC_2_4_6_TextString* beva_origin; BEC_2_9_4_ContainerList* beva_cmdl; BEC_2_4_6_TextString* bevl_cmd; BEC_2_4_6_TextString* bevl_inpass; BEC_2_4_6_TextString* bevl_stateres; BEC_2_4_6_TextString* bevl_newpin; BEC_2_4_6_TextString* bevl_inpin; BEC_2_4_6_TextString* bevl_newpass; BEC_2_4_6_TextString* bevl_newspass; BEC_2_4_6_TextString* bevl_newdid; BEC_2_5_4_LogicBool* bevl_deHex; BEC_2_4_3_MathInt* bevl_cmdle; BEC_2_4_3_MathInt* bevl_k; BEC_2_4_6_TextString* bevl_key; BEC_2_4_6_TextString* bevl_value; BEC_2_4_3_MathInt* bevl_keyi; BEC_2_5_4_LogicBool* bevt_0_ta_anchor; BEC_2_5_4_LogicBool* bevt_1_ta_anchor; BEC_2_5_4_LogicBool* bevt_2_ta_anchor; BEC_2_5_4_LogicBool* bevt_3_ta_ph; BEC_2_4_3_MathInt* bevt_4_ta_ph; BEC_2_4_3_MathInt* bevt_5_ta_ph; BEC_2_4_6_TextString* bevt_6_ta_ph; BEC_2_4_3_MathInt* bevt_7_ta_ph; BEC_2_5_4_LogicBool* bevt_8_ta_ph; BEC_2_4_6_TextString* bevt_9_ta_ph; BEC_2_5_4_LogicBool* bevt_10_ta_ph; BEC_2_4_6_TextString* bevt_11_ta_ph; BEC_2_5_4_LogicBool* bevt_12_ta_ph; BEC_2_4_6_TextString* bevt_13_ta_ph; BEC_2_5_4_LogicBool* bevt_14_ta_ph; BEC_2_4_6_TextString* bevt_15_ta_ph; BEC_2_5_4_LogicBool* bevt_16_ta_ph; BEC_2_4_6_TextString* bevt_17_ta_ph; BEC_2_5_4_LogicBool* bevt_18_ta_ph; BEC_2_4_7_TextStrings* bevt_19_ta_ph; BEC_2_4_6_TextString* bevt_20_ta_ph; BEC_2_4_3_MathInt* bevt_21_ta_ph; BEC_2_5_4_LogicBool* bevt_22_ta_ph; BEC_2_4_7_TextStrings* bevt_23_ta_ph; BEC_2_4_6_TextString* bevt_24_ta_ph; BEC_2_5_4_LogicBool* bevt_25_ta_ph; BEC_2_4_6_TextString* bevt_26_ta_ph; BEC_2_5_4_LogicBool* bevt_27_ta_ph; BEC_2_4_6_TextString* bevt_28_ta_ph; BEC_2_5_4_LogicBool* bevt_29_ta_ph; BEC_2_4_6_TextString* bevt_30_ta_ph; BEC_2_5_4_LogicBool* bevt_31_ta_ph; BEC_2_4_6_TextString* bevt_32_ta_ph; BEC_2_4_3_MathInt* bevt_33_ta_ph; BEC_2_5_4_LogicBool* bevt_34_ta_ph; BEC_2_4_6_TextString* bevt_35_ta_ph; BEC_2_4_6_TextString* bevt_36_ta_ph; BEC_2_5_4_LogicBool* bevt_37_ta_ph; BEC_2_4_7_TextStrings* bevt_38_ta_ph; BEC_2_4_6_TextString* bevt_39_ta_ph; BEC_2_5_4_LogicBool* bevt_40_ta_ph; BEC_2_5_4_LogicBool* bevt_41_ta_ph; BEC_2_4_6_TextString* bevt_42_ta_ph; BEC_2_5_4_LogicBool* bevt_43_ta_ph; BEC_2_4_3_MathInt* bevt_44_ta_ph; BEC_2_4_3_MathInt* bevt_45_ta_ph; BEC_2_4_6_TextString* bevt_46_ta_ph; BEC_2_4_6_TextString* bevt_47_ta_ph; BEC_2_5_4_LogicBool* bevt_48_ta_ph; BEC_2_4_6_TextString* bevt_49_ta_ph; BEC_2_4_3_MathInt* bevt_50_ta_ph; BEC_2_5_4_LogicBool* bevt_51_ta_ph; BEC_2_4_7_TextStrings* bevt_52_ta_ph; BEC_2_5_4_LogicBool* bevt_53_ta_ph; BEC_2_4_7_TextStrings* bevt_54_ta_ph; BEC_2_4_6_TextString* bevt_55_ta_ph; BEC_2_5_4_LogicBool* bevt_56_ta_ph; BEC_2_4_6_TextString* bevt_57_ta_ph; BEC_2_4_6_TextString* bevt_58_ta_ph; BEC_2_4_3_MathInt* bevt_59_ta_ph; BEC_2_5_4_LogicBool* bevt_60_ta_ph; BEC_2_4_7_TextStrings* bevt_61_ta_ph; BEC_2_5_4_LogicBool* bevt_62_ta_ph; BEC_2_4_7_TextStrings* bevt_63_ta_ph; BEC_2_4_6_TextString* bevt_64_ta_ph; BEC_2_5_4_LogicBool* bevt_65_ta_ph; BEC_2_4_6_TextString* bevt_66_ta_ph; BEC_2_5_4_LogicBool* bevt_67_ta_ph; BEC_2_4_7_TextStrings* bevt_68_ta_ph; BEC_2_4_6_TextString* bevt_69_ta_ph; BEC_2_4_3_MathInt* bevt_70_ta_ph; BEC_2_5_4_LogicBool* bevt_71_ta_ph; BEC_2_4_7_TextStrings* bevt_72_ta_ph; BEC_2_4_6_TextString* bevt_73_ta_ph; BEC_2_4_3_MathInt* bevt_74_ta_ph; BEC_2_5_4_LogicBool* bevt_75_ta_ph; BEC_2_4_7_TextStrings* bevt_76_ta_ph; BEC_2_5_4_LogicBool* bevt_77_ta_ph; BEC_2_4_3_MathInt* bevt_78_ta_ph; BEC_2_4_3_MathInt* bevt_79_ta_ph; BEC_2_4_6_TextString* bevt_80_ta_ph; BEC_2_4_6_TextString* bevt_81_ta_ph; BEC_2_5_4_LogicBool* bevt_82_ta_ph; BEC_2_4_6_TextString* bevt_83_ta_ph; BEC_2_5_4_LogicBool* bevt_84_ta_ph; BEC_2_4_6_TextString* bevt_85_ta_ph; BEC_2_4_3_MathInt* bevt_86_ta_ph; BEC_2_5_4_LogicBool* bevt_87_ta_ph; BEC_2_4_7_TextStrings* bevt_88_ta_ph; BEC_2_5_4_LogicBool* bevt_89_ta_ph; BEC_2_4_7_TextStrings* bevt_90_ta_ph; BEC_2_4_6_TextString* bevt_91_ta_ph; BEC_2_5_4_LogicBool* bevt_92_ta_ph; BEC_2_4_6_TextString* bevt_93_ta_ph; BEC_2_4_6_TextString* bevt_94_ta_ph; BEC_2_5_4_LogicBool* bevt_95_ta_ph; BEC_2_8_4_EmbeddedWifi* bevt_96_ta_ph; BEC_2_4_6_TextString* bevt_97_ta_ph; BEC_2_4_6_TextString* bevt_98_ta_ph; BEC_2_5_4_LogicBool* bevt_99_ta_ph; BEC_2_4_7_TextStrings* bevt_100_ta_ph; BEC_2_4_6_TextString* bevt_101_ta_ph; BEC_2_4_3_MathInt* bevt_102_ta_ph; BEC_2_5_4_LogicBool* bevt_103_ta_ph; BEC_2_4_7_TextStrings* bevt_104_ta_ph; BEC_2_4_6_TextString* bevt_105_ta_ph; BEC_2_5_4_LogicBool* bevt_106_ta_ph; BEC_2_4_6_TextString* bevt_107_ta_ph; BEC_2_5_4_LogicBool* bevt_108_ta_ph; BEC_2_4_6_TextString* bevt_109_ta_ph; BEC_2_4_3_MathInt* bevt_110_ta_ph; BEC_2_4_3_MathInt* bevt_111_ta_ph; BEC_2_6_6_SystemObject* bevt_112_ta_ph; BEC_2_6_6_SystemObject* bevt_113_ta_ph; BEC_2_4_3_MathInt* bevt_114_ta_ph; BEC_2_4_6_TextString* bevt_115_ta_ph; BEC_2_5_4_LogicBool* bevt_116_ta_ph; BEC_2_4_7_TextStrings* bevt_117_ta_ph; BEC_2_6_3_EncodeHex* bevt_118_ta_ph; BEC_2_5_4_LogicBool* bevt_119_ta_ph; BEC_2_4_7_TextStrings* bevt_120_ta_ph; BEC_2_6_3_EncodeHex* bevt_121_ta_ph; BEC_2_5_4_LogicBool* bevt_122_ta_ph; BEC_2_4_7_TextStrings* bevt_123_ta_ph; BEC_2_5_4_LogicBool* bevt_124_ta_ph; BEC_2_4_7_TextStrings* bevt_125_ta_ph; BEC_2_4_6_TextString* bevt_126_ta_ph; BEC_2_4_6_TextString* bevt_127_ta_ph; BEC_2_4_6_TextString* bevt_128_ta_ph; BEC_2_4_6_TextString* bevt_129_ta_ph; BEC_2_4_6_TextString* bevt_130_ta_ph; BEC_2_4_6_TextString* bevt_131_ta_ph; BEC_2_4_6_TextString* bevt_132_ta_ph; BEC_2_5_4_LogicBool* bevt_133_ta_ph; BEC_2_4_6_TextString* bevt_134_ta_ph; BEC_2_4_6_TextString* bevt_135_ta_ph; BEC_2_5_4_LogicBool* bevt_136_ta_ph; BEC_2_4_6_TextString* bevt_137_ta_ph; BEC_2_6_6_SystemObject* bevt_138_ta_ph; BEC_2_6_6_SystemObject* bevt_139_ta_ph; BEC_2_4_3_MathInt* bevt_140_ta_ph; BEC_2_4_6_TextString* bevt_141_ta_ph; BEC_2_4_3_MathInt* bevt_142_ta_ph; BEC_2_4_3_MathInt* bevt_143_ta_ph; BEC_2_5_4_LogicBool* bevt_144_ta_ph; BEC_2_5_4_LogicBool* bevt_145_ta_ph; BEC_2_5_4_LogicBool* bevt_146_ta_ph; BEC_2_4_7_TextStrings* bevt_147_ta_ph; BEC_2_5_4_LogicBool* bevt_148_ta_ph; BEC_2_5_4_LogicBool* bevt_149_ta_ph; BEC_2_4_7_TextStrings* bevt_150_ta_ph; BEC_2_4_6_TextString* bevt_151_ta_ph; BEC_2_6_3_EncodeHex* bevt_152_ta_ph; BEC_2_4_6_TextString* bevt_153_ta_ph; BEC_2_4_6_TextString* bevt_154_ta_ph; BEC_2_5_4_LogicBool* bevt_155_ta_ph; BEC_2_4_6_TextString* bevt_156_ta_ph; BEC_2_4_6_TextString* bevt_157_ta_ph; BEC_2_5_4_LogicBool* bevt_158_ta_ph; BEC_2_4_6_TextString* bevt_159_ta_ph; BEC_2_4_3_MathInt* bevt_160_ta_ph; BEC_2_4_6_TextString* bevt_161_ta_ph; BEC_2_5_4_LogicBool* bevt_162_ta_ph; BEC_2_4_6_TextString* bevt_163_ta_ph; BEC_2_4_6_TextString* bevt_164_ta_ph; BEC_2_5_4_LogicBool* bevt_165_ta_ph; BEC_2_4_6_TextString* bevt_166_ta_ph; BEC_2_4_6_TextString* bevt_167_ta_ph; BEC_2_4_6_TextString* bevt_168_ta_ph; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->beva_channel = bevk_channel;
beq->beva_origin = bevk_origin;
beq->beva_cmdl = bevk_cmdl;
beq->bevl_cmd = nullptr;
beq->bevl_inpass = nullptr;
beq->bevl_stateres = nullptr;
beq->bevl_newpin = nullptr;
beq->bevl_inpin = nullptr;
beq->bevl_newpass = nullptr;
beq->bevl_newspass = nullptr;
beq->bevl_newdid = nullptr;
beq->bevl_deHex = nullptr;
beq->bevl_cmdle = nullptr;
beq->bevl_k = nullptr;
beq->bevl_key = nullptr;
beq->bevl_value = nullptr;
beq->bevl_keyi = nullptr;
beq->bevt_0_ta_anchor = nullptr;
beq->bevt_1_ta_anchor = nullptr;
beq->bevt_2_ta_anchor = nullptr;
beq->bevt_3_ta_ph = nullptr;
beq->bevt_4_ta_ph = nullptr;
beq->bevt_5_ta_ph = nullptr;
beq->bevt_6_ta_ph = nullptr;
beq->bevt_7_ta_ph = nullptr;
beq->bevt_8_ta_ph = nullptr;
beq->bevt_9_ta_ph = nullptr;
beq->bevt_10_ta_ph = nullptr;
beq->bevt_11_ta_ph = nullptr;
beq->bevt_12_ta_ph = nullptr;
beq->bevt_13_ta_ph = nullptr;
beq->bevt_14_ta_ph = nullptr;
beq->bevt_15_ta_ph = nullptr;
beq->bevt_16_ta_ph = nullptr;
beq->bevt_17_ta_ph = nullptr;
beq->bevt_18_ta_ph = nullptr;
beq->bevt_19_ta_ph = nullptr;
beq->bevt_20_ta_ph = nullptr;
beq->bevt_21_ta_ph = nullptr;
beq->bevt_22_ta_ph = nullptr;
beq->bevt_23_ta_ph = nullptr;
beq->bevt_24_ta_ph = nullptr;
beq->bevt_25_ta_ph = nullptr;
beq->bevt_26_ta_ph = nullptr;
beq->bevt_27_ta_ph = nullptr;
beq->bevt_28_ta_ph = nullptr;
beq->bevt_29_ta_ph = nullptr;
beq->bevt_30_ta_ph = nullptr;
beq->bevt_31_ta_ph = nullptr;
beq->bevt_32_ta_ph = nullptr;
beq->bevt_33_ta_ph = nullptr;
beq->bevt_34_ta_ph = nullptr;
beq->bevt_35_ta_ph = nullptr;
beq->bevt_36_ta_ph = nullptr;
beq->bevt_37_ta_ph = nullptr;
beq->bevt_38_ta_ph = nullptr;
beq->bevt_39_ta_ph = nullptr;
beq->bevt_40_ta_ph = nullptr;
beq->bevt_41_ta_ph = nullptr;
beq->bevt_42_ta_ph = nullptr;
beq->bevt_43_ta_ph = nullptr;
beq->bevt_44_ta_ph = nullptr;
beq->bevt_45_ta_ph = nullptr;
beq->bevt_46_ta_ph = nullptr;
beq->bevt_47_ta_ph = nullptr;
beq->bevt_48_ta_ph = nullptr;
beq->bevt_49_ta_ph = nullptr;
beq->bevt_50_ta_ph = nullptr;
beq->bevt_51_ta_ph = nullptr;
beq->bevt_52_ta_ph = nullptr;
beq->bevt_53_ta_ph = nullptr;
beq->bevt_54_ta_ph = nullptr;
beq->bevt_55_ta_ph = nullptr;
beq->bevt_56_ta_ph = nullptr;
beq->bevt_57_ta_ph = nullptr;
beq->bevt_58_ta_ph = nullptr;
beq->bevt_59_ta_ph = nullptr;
beq->bevt_60_ta_ph = nullptr;
beq->bevt_61_ta_ph = nullptr;
beq->bevt_62_ta_ph = nullptr;
beq->bevt_63_ta_ph = nullptr;
beq->bevt_64_ta_ph = nullptr;
beq->bevt_65_ta_ph = nullptr;
beq->bevt_66_ta_ph = nullptr;
beq->bevt_67_ta_ph = nullptr;
beq->bevt_68_ta_ph = nullptr;
beq->bevt_69_ta_ph = nullptr;
beq->bevt_70_ta_ph = nullptr;
beq->bevt_71_ta_ph = nullptr;
beq->bevt_72_ta_ph = nullptr;
beq->bevt_73_ta_ph = nullptr;
beq->bevt_74_ta_ph = nullptr;
beq->bevt_75_ta_ph = nullptr;
beq->bevt_76_ta_ph = nullptr;
beq->bevt_77_ta_ph = nullptr;
beq->bevt_78_ta_ph = nullptr;
beq->bevt_79_ta_ph = nullptr;
beq->bevt_80_ta_ph = nullptr;
beq->bevt_81_ta_ph = nullptr;
beq->bevt_82_ta_ph = nullptr;
beq->bevt_83_ta_ph = nullptr;
beq->bevt_84_ta_ph = nullptr;
beq->bevt_85_ta_ph = nullptr;
beq->bevt_86_ta_ph = nullptr;
beq->bevt_87_ta_ph = nullptr;
beq->bevt_88_ta_ph = nullptr;
beq->bevt_89_ta_ph = nullptr;
beq->bevt_90_ta_ph = nullptr;
beq->bevt_91_ta_ph = nullptr;
beq->bevt_92_ta_ph = nullptr;
beq->bevt_93_ta_ph = nullptr;
beq->bevt_94_ta_ph = nullptr;
beq->bevt_95_ta_ph = nullptr;
beq->bevt_96_ta_ph = nullptr;
beq->bevt_97_ta_ph = nullptr;
beq->bevt_98_ta_ph = nullptr;
beq->bevt_99_ta_ph = nullptr;
beq->bevt_100_ta_ph = nullptr;
beq->bevt_101_ta_ph = nullptr;
beq->bevt_102_ta_ph = nullptr;
beq->bevt_103_ta_ph = nullptr;
beq->bevt_104_ta_ph = nullptr;
beq->bevt_105_ta_ph = nullptr;
beq->bevt_106_ta_ph = nullptr;
beq->bevt_107_ta_ph = nullptr;
beq->bevt_108_ta_ph = nullptr;
beq->bevt_109_ta_ph = nullptr;
beq->bevt_110_ta_ph = nullptr;
beq->bevt_111_ta_ph = nullptr;
beq->bevt_112_ta_ph = nullptr;
beq->bevt_113_ta_ph = nullptr;
beq->bevt_114_ta_ph = nullptr;
beq->bevt_115_ta_ph = nullptr;
beq->bevt_116_ta_ph = nullptr;
beq->bevt_117_ta_ph = nullptr;
beq->bevt_118_ta_ph = nullptr;
beq->bevt_119_ta_ph = nullptr;
beq->bevt_120_ta_ph = nullptr;
beq->bevt_121_ta_ph = nullptr;
beq->bevt_122_ta_ph = nullptr;
beq->bevt_123_ta_ph = nullptr;
beq->bevt_124_ta_ph = nullptr;
beq->bevt_125_ta_ph = nullptr;
beq->bevt_126_ta_ph = nullptr;
beq->bevt_127_ta_ph = nullptr;
beq->bevt_128_ta_ph = nullptr;
beq->bevt_129_ta_ph = nullptr;
beq->bevt_130_ta_ph = nullptr;
beq->bevt_131_ta_ph = nullptr;
beq->bevt_132_ta_ph = nullptr;
beq->bevt_133_ta_ph = nullptr;
beq->bevt_134_ta_ph = nullptr;
beq->bevt_135_ta_ph = nullptr;
beq->bevt_136_ta_ph = nullptr;
beq->bevt_137_ta_ph = nullptr;
beq->bevt_138_ta_ph = nullptr;
beq->bevt_139_ta_ph = nullptr;
beq->bevt_140_ta_ph = nullptr;
beq->bevt_141_ta_ph = nullptr;
beq->bevt_142_ta_ph = nullptr;
beq->bevt_143_ta_ph = nullptr;
beq->bevt_144_ta_ph = nullptr;
beq->bevt_145_ta_ph = nullptr;
beq->bevt_146_ta_ph = nullptr;
beq->bevt_147_ta_ph = nullptr;
beq->bevt_148_ta_ph = nullptr;
beq->bevt_149_ta_ph = nullptr;
beq->bevt_150_ta_ph = nullptr;
beq->bevt_151_ta_ph = nullptr;
beq->bevt_152_ta_ph = nullptr;
beq->bevt_153_ta_ph = nullptr;
beq->bevt_154_ta_ph = nullptr;
beq->bevt_155_ta_ph = nullptr;
beq->bevt_156_ta_ph = nullptr;
beq->bevt_157_ta_ph = nullptr;
beq->bevt_158_ta_ph = nullptr;
beq->bevt_159_ta_ph = nullptr;
beq->bevt_160_ta_ph = nullptr;
beq->bevt_161_ta_ph = nullptr;
beq->bevt_162_ta_ph = nullptr;
beq->bevt_163_ta_ph = nullptr;
beq->bevt_164_ta_ph = nullptr;
beq->bevt_165_ta_ph = nullptr;
beq->bevt_166_ta_ph = nullptr;
beq->bevt_167_ta_ph = nullptr;
beq->bevt_168_ta_ph = nullptr;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(187);
bevp_app->bem_maybeGc_0();
bevp_app->bem_wdtFeed_0();
bevp_app->bem_yield_0();
bevp_needsGc = static_cast<BEC_2_5_4_LogicBool*>(BECS_Runtime::boolTrue);
beq->bevt_4_ta_ph = beq->beva_cmdl->bem_sizeGet_0();
beq->bevt_5_ta_ph = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(1))));
if (beq->bevt_4_ta_ph->bevi_int < beq->bevt_5_ta_ph->bevi_int) {
beq->bevt_3_ta_ph = BECS_Runtime::boolTrue;
 } else { 
beq->bevt_3_ta_ph = BECS_Runtime::boolFalse;
}
if (beq->bevt_3_ta_ph->bevi_bool) {
beq->bevt_6_ta_ph = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString(16, {0x6E,0x6F,0x20,0x63,0x6D,0x64,0x20,0x73,0x70,0x65,0x63,0x69,0x66,0x69,0x65,0x64}))));
return beq->bevt_6_ta_ph;
} 
beq->bevt_7_ta_ph = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(0))));
beq->bevl_cmd = static_cast<BEC_2_4_6_TextString*>(beq->beva_cmdl->bem_get_1(beq->bevt_7_ta_ph));
beq->bevt_9_ta_ph = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString(9, {0x67,0x65,0x74,0x61,0x70,0x73,0x73,0x69,0x64}))));
beq->bevt_8_ta_ph = beq->bevl_cmd->bem_equals_1(beq->bevt_9_ta_ph);
if (beq->bevt_8_ta_ph->bevi_bool) {
if (bevp_apSsid == nullptr) {
beq->bevt_10_ta_ph = BECS_Runtime::boolFalse;
 } else { 
beq->bevt_10_ta_ph = BECS_Runtime::boolTrue;
}
if (beq->bevt_10_ta_ph->bevi_bool) {
return bevp_apSsid;
} 
 else  {
beq->bevt_11_ta_ph = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString(0, {}))));
return beq->bevt_11_ta_ph;
} 
} 
 else  {
beq->bevt_13_ta_ph = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString(13, {0x67,0x65,0x74,0x6C,0x61,0x73,0x74,0x65,0x76,0x65,0x6E,0x74,0x73}))));
beq->bevt_12_ta_ph = beq->bevl_cmd->bem_equals_1(beq->bevt_13_ta_ph);
if (beq->bevt_12_ta_ph->bevi_bool) {
beq->bevl_stateres = bem_getLastEvents_1(beq->beva_cmdl);
return beq->bevl_stateres;
} 
} 
beq->bevt_15_ta_ph = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString(7, {0x64,0x6F,0x73,0x74,0x61,0x74,0x65}))));
beq->bevt_14_ta_ph = beq->bevl_cmd->bem_equals_1(beq->bevt_15_ta_ph);
if (beq->bevt_14_ta_ph->bevi_bool) {
beq->bevt_0_ta_anchor = BECS_Runtime::boolTrue;
} 
 else  {
beq->bevt_17_ta_ph = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString(13, {0x67,0x65,0x74,0x63,0x6F,0x6E,0x74,0x72,0x6F,0x6C,0x64,0x65,0x66}))));
beq->bevt_16_ta_ph = beq->bevl_cmd->bem_equals_1(beq->bevt_17_ta_ph);
if (beq->bevt_16_ta_ph->bevi_bool) {
beq->bevt_0_ta_anchor = BECS_Runtime::boolTrue;
} 
 else  {
beq->bevt_0_ta_anchor = BECS_Runtime::boolFalse;
} 
} 
if (beq->bevt_0_ta_anchor->bevi_bool) {
beq->bevt_19_ta_ph = static_cast<BEC_2_4_7_TextStrings*>(BEC_2_4_7_TextStrings::bece_BEC_2_4_7_TextStrings_bevs_inst);
beq->bevt_18_ta_ph = beq->bevt_19_ta_ph->bem_isEmpty_1(bevp_spass);
if (beq->bevt_18_ta_ph->bevi_bool) {
beq->bevt_20_ta_ph = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString(26, {0x53,0x74,0x61,0x74,0x65,0x20,0x50,0x61,0x73,0x73,0x77,0x6F,0x72,0x64,0x20,0x4D,0x75,0x73,0x74,0x20,0x42,0x65,0x20,0x53,0x65,0x74}))));
return beq->bevt_20_ta_ph;
} 
beq->bevt_21_ta_ph = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(1))));
beq->bevl_inpass = static_cast<BEC_2_4_6_TextString*>(beq->beva_cmdl->bem_get_1(beq->bevt_21_ta_ph));
beq->bevt_23_ta_ph = static_cast<BEC_2_4_7_TextStrings*>(BEC_2_4_7_TextStrings::bece_BEC_2_4_7_TextStrings_bevs_inst);
beq->bevt_22_ta_ph = beq->bevt_23_ta_ph->bem_isEmpty_1(beq->bevl_inpass);
if (beq->bevt_22_ta_ph->bevi_bool) {
beq->bevt_24_ta_ph = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString(31, {0x53,0x74,0x61,0x74,0x65,0x20,0x70,0x61,0x73,0x73,0x77,0x6F,0x72,0x64,0x20,0x6D,0x75,0x73,0x74,0x20,0x62,0x65,0x20,0x70,0x72,0x6F,0x76,0x69,0x64,0x65,0x64}))));
return beq->bevt_24_ta_ph;
} 
beq->bevt_25_ta_ph = beq->bevl_inpass->bem_notEquals_1(bevp_spass);
if (beq->bevt_25_ta_ph->bevi_bool) {
beq->bevt_26_ta_ph = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString(24, {0x53,0x74,0x61,0x74,0x65,0x20,0x50,0x61,0x73,0x73,0x77,0x6F,0x72,0x64,0x20,0x49,0x6E,0x63,0x6F,0x72,0x72,0x65,0x63,0x74}))));
return beq->bevt_26_ta_ph;
} 
beq->bevt_28_ta_ph = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString(7, {0x64,0x6F,0x73,0x74,0x61,0x74,0x65}))));
beq->bevt_27_ta_ph = beq->bevl_cmd->bem_equals_1(beq->bevt_28_ta_ph);
if (beq->bevt_27_ta_ph->bevi_bool) {
beq->bevl_stateres = bem_doState_1(beq->beva_cmdl);
return beq->bevl_stateres;
} 
 else  {
if (bevp_controlDef == nullptr) {
beq->bevt_29_ta_ph = BECS_Runtime::boolFalse;
 } else { 
beq->bevt_29_ta_ph = BECS_Runtime::boolTrue;
}
if (beq->bevt_29_ta_ph->bevi_bool) {
return bevp_controlDef;
} 
 else  {
beq->bevt_30_ta_ph = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString(11, {0x63,0x6F,0x6E,0x74,0x72,0x6F,0x6C,0x64,0x65,0x66,0x2C}))));
return beq->bevt_30_ta_ph;
} 
} 
} 
beq->bevt_32_ta_ph = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString(6, {0x73,0x65,0x74,0x70,0x69,0x6E}))));
beq->bevt_31_ta_ph = beq->bevl_cmd->bem_equals_1(beq->bevt_32_ta_ph);
if (beq->bevt_31_ta_ph->bevi_bool) {
beq->bevt_33_ta_ph = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(1))));
beq->bevl_newpin = static_cast<BEC_2_4_6_TextString*>(beq->beva_cmdl->bem_get_1(beq->bevt_33_ta_ph));
beq->bevt_35_ta_ph = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString(6, {0x73,0x65,0x72,0x69,0x61,0x6C}))));
beq->bevt_34_ta_ph = beq->beva_channel->bem_equals_1(beq->bevt_35_ta_ph);
if (!(beq->bevt_34_ta_ph->bevi_bool)) {
beq->bevt_36_ta_ph = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString(33, {0x45,0x72,0x72,0x6F,0x72,0x2C,0x20,0x6F,0x6E,0x6C,0x79,0x20,0x73,0x75,0x70,0x70,0x6F,0x72,0x74,0x65,0x64,0x20,0x6F,0x76,0x65,0x72,0x20,0x53,0x65,0x72,0x69,0x61,0x6C}))));
return beq->bevt_36_ta_ph;
} 
beq->bevt_38_ta_ph = static_cast<BEC_2_4_7_TextStrings*>(BEC_2_4_7_TextStrings::bece_BEC_2_4_7_TextStrings_bevs_inst);
beq->bevt_37_ta_ph = beq->bevt_38_ta_ph->bem_isEmpty_1(beq->bevl_newpin);
if (beq->bevt_37_ta_ph->bevi_bool) {
beq->bevt_39_ta_ph = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString(22, {0x45,0x72,0x72,0x6F,0x72,0x2C,0x20,0x70,0x69,0x6E,0x20,0x69,0x73,0x20,0x72,0x65,0x71,0x75,0x69,0x72,0x65,0x64}))));
return beq->bevt_39_ta_ph;
} 
 else  {
beq->bevt_41_ta_ph = beq->bevl_newpin->bem_isAlphaNumGet_0();
if (beq->bevt_41_ta_ph->bevi_bool) {
beq->bevt_40_ta_ph = BECS_Runtime::boolFalse;
 } else { 
beq->bevt_40_ta_ph = BECS_Runtime::boolTrue;
}
if (beq->bevt_40_ta_ph->bevi_bool) {
beq->bevt_42_ta_ph = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString(51, {0x45,0x72,0x72,0x6F,0x72,0x2C,0x20,0x70,0x69,0x6E,0x20,0x6D,0x61,0x6E,0x79,0x20,0x6F,0x6E,0x6C,0x79,0x20,0x63,0x6F,0x6E,0x73,0x69,0x73,0x74,0x20,0x6F,0x66,0x20,0x6C,0x65,0x74,0x74,0x65,0x72,0x73,0x20,0x61,0x6E,0x64,0x20,0x6E,0x75,0x6D,0x62,0x65,0x72,0x73}))));
return beq->bevt_42_ta_ph;
} 
 else  {
beq->bevt_44_ta_ph = beq->bevl_newpin->bem_sizeGet_0();
beq->bevt_45_ta_ph = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(16))));
if (beq->bevt_44_ta_ph->bevi_int != beq->bevt_45_ta_ph->bevi_int) {
beq->bevt_43_ta_ph = BECS_Runtime::boolTrue;
 } else { 
beq->bevt_43_ta_ph = BECS_Runtime::boolFalse;
}
if (beq->bevt_43_ta_ph->bevi_bool) {
beq->bevt_46_ta_ph = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString(37, {0x45,0x72,0x72,0x6F,0x72,0x2C,0x20,0x70,0x69,0x6E,0x20,0x6D,0x75,0x73,0x74,0x20,0x62,0x65,0x20,0x31,0x36,0x20,0x63,0x68,0x61,0x72,0x73,0x20,0x69,0x6E,0x20,0x6C,0x65,0x6E,0x67,0x74,0x68}))));
return beq->bevt_46_ta_ph;
} 
 else  {
bevp_pin = beq->bevl_newpin;
bevp_pin->bem_print_0();
bevp_config->bem_put_2(bevp_shpini, bevp_pin);
beq->bevt_47_ta_ph = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString(7, {0x50,0x69,0x6E,0x20,0x73,0x65,0x74}))));
return beq->bevt_47_ta_ph;
} 
} 
} 
} 
 else  {
beq->bevt_49_ta_ph = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString(6, {0x61,0x6C,0x6C,0x73,0x65,0x74}))));
beq->bevt_48_ta_ph = beq->bevl_cmd->bem_equals_1(beq->bevt_49_ta_ph);
if (beq->bevt_48_ta_ph->bevi_bool) {
beq->bevt_50_ta_ph = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(1))));
beq->bevl_inpin = static_cast<BEC_2_4_6_TextString*>(beq->beva_cmdl->bem_get_1(beq->bevt_50_ta_ph));
beq->bevt_52_ta_ph = static_cast<BEC_2_4_7_TextStrings*>(BEC_2_4_7_TextStrings::bece_BEC_2_4_7_TextStrings_bevs_inst);
beq->bevt_51_ta_ph = beq->bevt_52_ta_ph->bem_notEmpty_1(bevp_pin);
if (beq->bevt_51_ta_ph->bevi_bool) {
beq->bevt_54_ta_ph = static_cast<BEC_2_4_7_TextStrings*>(BEC_2_4_7_TextStrings::bece_BEC_2_4_7_TextStrings_bevs_inst);
beq->bevt_53_ta_ph = beq->bevt_54_ta_ph->bem_isEmpty_1(beq->bevl_inpin);
if (beq->bevt_53_ta_ph->bevi_bool) {
beq->bevt_55_ta_ph = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString(23, {0x45,0x72,0x72,0x6F,0x72,0x2C,0x20,0x70,0x69,0x6E,0x20,0x77,0x61,0x73,0x20,0x6E,0x6F,0x74,0x20,0x73,0x65,0x6E,0x74}))));
return beq->bevt_55_ta_ph;
} 
 else  {
beq->bevt_56_ta_ph = bevp_pin->bem_notEquals_1(beq->bevl_inpin);
if (beq->bevt_56_ta_ph->bevi_bool) {
beq->bevt_57_ta_ph = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString(23, {0x45,0x72,0x72,0x6F,0x72,0x2C,0x20,0x70,0x69,0x6E,0x20,0x69,0x73,0x20,0x69,0x6E,0x63,0x6F,0x72,0x72,0x65,0x63,0x74}))));
return beq->bevt_57_ta_ph;
} 
} 
} 
 else  {
beq->bevt_58_ta_ph = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString(22, {0x45,0x72,0x72,0x6F,0x72,0x2C,0x20,0x70,0x69,0x6E,0x20,0x6D,0x75,0x73,0x74,0x20,0x62,0x65,0x20,0x73,0x65,0x74}))));
return beq->bevt_58_ta_ph;
} 
beq->bevt_59_ta_ph = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(2))));
beq->bevl_newpass = static_cast<BEC_2_4_6_TextString*>(beq->beva_cmdl->bem_get_1(beq->bevt_59_ta_ph));
beq->bevt_61_ta_ph = static_cast<BEC_2_4_7_TextStrings*>(BEC_2_4_7_TextStrings::bece_BEC_2_4_7_TextStrings_bevs_inst);
beq->bevt_60_ta_ph = beq->bevt_61_ta_ph->bem_notEmpty_1(bevp_pass);
if (beq->bevt_60_ta_ph->bevi_bool) {
beq->bevt_63_ta_ph = static_cast<BEC_2_4_7_TextStrings*>(BEC_2_4_7_TextStrings::bece_BEC_2_4_7_TextStrings_bevs_inst);
beq->bevt_62_ta_ph = beq->bevt_63_ta_ph->bem_isEmpty_1(beq->bevl_newpass);
if (beq->bevt_62_ta_ph->bevi_bool) {
beq->bevt_64_ta_ph = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString(24, {0x45,0x72,0x72,0x6F,0x72,0x2C,0x20,0x70,0x61,0x73,0x73,0x20,0x77,0x61,0x73,0x20,0x6E,0x6F,0x74,0x20,0x73,0x65,0x6E,0x74}))));
return beq->bevt_64_ta_ph;
} 
 else  {
beq->bevt_65_ta_ph = bevp_pass->bem_notEquals_1(beq->bevl_newpass);
if (beq->bevt_65_ta_ph->bevi_bool) {
beq->bevt_66_ta_ph = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString(24, {0x45,0x72,0x72,0x6F,0x72,0x2C,0x20,0x70,0x61,0x73,0x73,0x20,0x69,0x73,0x20,0x69,0x6E,0x63,0x6F,0x72,0x72,0x65,0x63,0x74}))));
return beq->bevt_66_ta_ph;
} 
} 
} 
beq->bevt_68_ta_ph = static_cast<BEC_2_4_7_TextStrings*>(BEC_2_4_7_TextStrings::bece_BEC_2_4_7_TextStrings_bevs_inst);
beq->bevt_67_ta_ph = beq->bevt_68_ta_ph->bem_isEmpty_1(beq->bevl_newpass);
if (beq->bevt_67_ta_ph->bevi_bool) {
beq->bevt_69_ta_ph = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString(31, {0x45,0x72,0x72,0x6F,0x72,0x2C,0x20,0x6E,0x65,0x77,0x20,0x70,0x61,0x73,0x73,0x77,0x6F,0x72,0x64,0x20,0x69,0x73,0x20,0x72,0x65,0x71,0x75,0x69,0x72,0x65,0x64}))));
return beq->bevt_69_ta_ph;
} 
 else  {
bevp_config->bem_put_2(bevp_shpassi, beq->bevl_newpass);
bevp_pass = beq->bevl_newpass;
} 
beq->bevt_70_ta_ph = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(3))));
beq->bevl_newspass = static_cast<BEC_2_4_6_TextString*>(beq->beva_cmdl->bem_get_1(beq->bevt_70_ta_ph));
beq->bevt_72_ta_ph = static_cast<BEC_2_4_7_TextStrings*>(BEC_2_4_7_TextStrings::bece_BEC_2_4_7_TextStrings_bevs_inst);
beq->bevt_71_ta_ph = beq->bevt_72_ta_ph->bem_isEmpty_1(beq->bevl_newspass);
if (beq->bevt_71_ta_ph->bevi_bool) {
beq->bevt_73_ta_ph = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString(28, {0x45,0x72,0x72,0x6F,0x72,0x2C,0x20,0x6E,0x65,0x77,0x20,0x73,0x70,0x61,0x73,0x73,0x20,0x69,0x73,0x20,0x72,0x65,0x71,0x75,0x69,0x72,0x65,0x64}))));
return beq->bevt_73_ta_ph;
} 
bevp_spass = beq->bevl_newspass;
bevp_config->bem_put_2(bevp_shspassi, bevp_spass);
beq->bevt_74_ta_ph = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(4))));
beq->bevl_newdid = static_cast<BEC_2_4_6_TextString*>(beq->beva_cmdl->bem_get_1(beq->bevt_74_ta_ph));
beq->bevt_76_ta_ph = static_cast<BEC_2_4_7_TextStrings*>(BEC_2_4_7_TextStrings::bece_BEC_2_4_7_TextStrings_bevs_inst);
beq->bevt_75_ta_ph = beq->bevt_76_ta_ph->bem_notEmpty_1(bevp_did);
if (beq->bevt_75_ta_ph->bevi_bool) {
beq->bevt_78_ta_ph = bevp_did->bem_sizeGet_0();
beq->bevt_79_ta_ph = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(16))));
if (beq->bevt_78_ta_ph->bevi_int == beq->bevt_79_ta_ph->bevi_int) {
beq->bevt_77_ta_ph = BECS_Runtime::boolTrue;
 } else { 
beq->bevt_77_ta_ph = BECS_Runtime::boolFalse;
}
if (beq->bevt_77_ta_ph->bevi_bool) {
beq->bevt_1_ta_anchor = BECS_Runtime::boolTrue;
} 
 else  {
beq->bevt_1_ta_anchor = BECS_Runtime::boolFalse;
} 
} 
 else  {
beq->bevt_1_ta_anchor = BECS_Runtime::boolFalse;
} 
if (beq->bevt_1_ta_anchor->bevi_bool) {
bevp_did = beq->bevl_newdid;
bevp_config->bem_put_2(bevp_shdidi, bevp_did);
} 
 else  {
beq->bevt_80_ta_ph = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString(31, {0x45,0x72,0x72,0x6F,0x72,0x2C,0x20,0x6E,0x65,0x77,0x64,0x69,0x64,0x20,0x73,0x69,0x7A,0x65,0x64,0x20,0x31,0x36,0x20,0x72,0x65,0x71,0x75,0x69,0x72,0x65,0x64}))));
return beq->bevt_80_ta_ph;
} 
beq->bevt_81_ta_ph = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString(11, {0x61,0x6C,0x6C,0x73,0x65,0x74,0x20,0x64,0x6F,0x6E,0x65}))));
return beq->bevt_81_ta_ph;
} 
 else  {
beq->bevt_83_ta_ph = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString(10, {0x72,0x65,0x73,0x65,0x74,0x62,0x79,0x70,0x69,0x6E}))));
beq->bevt_82_ta_ph = beq->bevl_cmd->bem_equals_1(beq->bevt_83_ta_ph);
if (beq->bevt_82_ta_ph->bevi_bool) {
if (bevp_resetByPin == nullptr) {
beq->bevt_84_ta_ph = BECS_Runtime::boolFalse;
 } else { 
beq->bevt_84_ta_ph = BECS_Runtime::boolTrue;
}
if (beq->bevt_84_ta_ph->bevi_bool) {
if (bevp_resetByPin->bevi_bool) {
beq->bevt_2_ta_anchor = BECS_Runtime::boolTrue;
} 
 else  {
beq->bevt_2_ta_anchor = BECS_Runtime::boolFalse;
} 
} 
 else  {
beq->bevt_2_ta_anchor = BECS_Runtime::boolFalse;
} 
if (!(beq->bevt_2_ta_anchor->bevi_bool)) {
beq->bevt_85_ta_ph = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString(49, {0x45,0x72,0x72,0x6F,0x72,0x2C,0x20,0x72,0x65,0x73,0x65,0x74,0x62,0x79,0x70,0x69,0x6E,0x20,0x6E,0x6F,0x74,0x20,0x65,0x6E,0x61,0x62,0x6C,0x65,0x64,0x2C,0x20,0x74,0x72,0x79,0x20,0x70,0x68,0x79,0x73,0x69,0x63,0x61,0x6C,0x20,0x72,0x65,0x73,0x65,0x74}))));
return beq->bevt_85_ta_ph;
} 
beq->bevt_86_ta_ph = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(1))));
beq->bevl_inpin = static_cast<BEC_2_4_6_TextString*>(beq->beva_cmdl->bem_get_1(beq->bevt_86_ta_ph));
beq->bevt_88_ta_ph = static_cast<BEC_2_4_7_TextStrings*>(BEC_2_4_7_TextStrings::bece_BEC_2_4_7_TextStrings_bevs_inst);
beq->bevt_87_ta_ph = beq->bevt_88_ta_ph->bem_notEmpty_1(bevp_pin);
if (beq->bevt_87_ta_ph->bevi_bool) {
beq->bevt_90_ta_ph = static_cast<BEC_2_4_7_TextStrings*>(BEC_2_4_7_TextStrings::bece_BEC_2_4_7_TextStrings_bevs_inst);
beq->bevt_89_ta_ph = beq->bevt_90_ta_ph->bem_isEmpty_1(beq->bevl_inpin);
if (beq->bevt_89_ta_ph->bevi_bool) {
beq->bevt_91_ta_ph = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString(23, {0x45,0x72,0x72,0x6F,0x72,0x2C,0x20,0x70,0x69,0x6E,0x20,0x77,0x61,0x73,0x20,0x6E,0x6F,0x74,0x20,0x73,0x65,0x6E,0x74}))));
return beq->bevt_91_ta_ph;
} 
 else  {
beq->bevt_92_ta_ph = bevp_pin->bem_notEquals_1(beq->bevl_inpin);
if (beq->bevt_92_ta_ph->bevi_bool) {
beq->bevt_93_ta_ph = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString(23, {0x45,0x72,0x72,0x6F,0x72,0x2C,0x20,0x70,0x69,0x6E,0x20,0x69,0x73,0x20,0x69,0x6E,0x63,0x6F,0x72,0x72,0x65,0x63,0x74}))));
return beq->bevt_93_ta_ph;
} 
} 
} 
 else  {
beq->bevt_94_ta_ph = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString(22, {0x45,0x72,0x72,0x6F,0x72,0x2C,0x20,0x70,0x69,0x6E,0x20,0x6D,0x75,0x73,0x74,0x20,0x62,0x65,0x20,0x73,0x65,0x74}))));
return beq->bevt_94_ta_ph;
} 
beq->bevt_96_ta_ph = static_cast<BEC_2_8_4_EmbeddedWifi*>(BEC_2_8_4_EmbeddedWifi::bece_BEC_2_8_4_EmbeddedWifi_bevs_inst);
beq->bevt_95_ta_ph = beq->bevt_96_ta_ph->bem_isConnectedGet_0();
if (beq->bevt_95_ta_ph->bevi_bool) {
beq->bevt_97_ta_ph = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString(62, {0x45,0x72,0x72,0x6F,0x72,0x2C,0x20,0x72,0x65,0x73,0x65,0x74,0x62,0x79,0x70,0x69,0x6E,0x20,0x6F,0x6E,0x6C,0x79,0x20,0x61,0x76,0x61,0x69,0x6C,0x61,0x62,0x6C,0x65,0x20,0x77,0x68,0x65,0x6E,0x20,0x6E,0x6F,0x74,0x20,0x6F,0x6E,0x20,0x77,0x69,0x66,0x69,0x20,0x61,0x63,0x63,0x65,0x73,0x73,0x20,0x70,0x6F,0x69,0x6E,0x74}))));
return beq->bevt_97_ta_ph;
} 
bem_reset_0();
beq->bevt_98_ta_ph = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString(12, {0x44,0x65,0x76,0x69,0x63,0x65,0x20,0x72,0x65,0x73,0x65,0x74}))));
return beq->bevt_98_ta_ph;
} 
} 
} 
beq->bevt_100_ta_ph = static_cast<BEC_2_4_7_TextStrings*>(BEC_2_4_7_TextStrings::bece_BEC_2_4_7_TextStrings_bevs_inst);
beq->bevt_99_ta_ph = beq->bevt_100_ta_ph->bem_isEmpty_1(bevp_pass);
if (beq->bevt_99_ta_ph->bevi_bool) {
beq->bevt_101_ta_ph = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString(27, {0x44,0x65,0x76,0x69,0x63,0x65,0x20,0x50,0x61,0x73,0x73,0x77,0x6F,0x72,0x64,0x20,0x4D,0x75,0x73,0x74,0x20,0x42,0x65,0x20,0x53,0x65,0x74}))));
return beq->bevt_101_ta_ph;
} 
beq->bevt_102_ta_ph = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(1))));
beq->bevl_inpass = static_cast<BEC_2_4_6_TextString*>(beq->beva_cmdl->bem_get_1(beq->bevt_102_ta_ph));
beq->bevt_104_ta_ph = static_cast<BEC_2_4_7_TextStrings*>(BEC_2_4_7_TextStrings::bece_BEC_2_4_7_TextStrings_bevs_inst);
beq->bevt_103_ta_ph = beq->bevt_104_ta_ph->bem_isEmpty_1(beq->bevl_inpass);
if (beq->bevt_103_ta_ph->bevi_bool) {
beq->bevt_105_ta_ph = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString(32, {0x44,0x65,0x76,0x69,0x63,0x65,0x20,0x70,0x61,0x73,0x73,0x77,0x6F,0x72,0x64,0x20,0x6D,0x75,0x73,0x74,0x20,0x62,0x65,0x20,0x70,0x72,0x6F,0x76,0x69,0x64,0x65,0x64}))));
return beq->bevt_105_ta_ph;
} 
beq->bevt_106_ta_ph = beq->bevl_inpass->bem_notEquals_1(bevp_pass);
if (beq->bevt_106_ta_ph->bevi_bool) {
beq->bevt_107_ta_ph = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString(25, {0x44,0x65,0x76,0x69,0x63,0x65,0x20,0x50,0x61,0x73,0x73,0x77,0x6F,0x72,0x64,0x20,0x49,0x6E,0x63,0x6F,0x72,0x72,0x65,0x63,0x74}))));
return beq->bevt_107_ta_ph;
} 
beq->bevt_109_ta_ph = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString(7, {0x73,0x65,0x74,0x77,0x69,0x66,0x69}))));
beq->bevt_108_ta_ph = beq->bevl_cmd->bem_equals_1(beq->bevt_109_ta_ph);
if (beq->bevt_108_ta_ph->bevi_bool) {
beq->bevt_110_ta_ph = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(3))));
bevp_ssid = static_cast<BEC_2_4_6_TextString*>(beq->beva_cmdl->bem_get_1(beq->bevt_110_ta_ph));
beq->bevt_111_ta_ph = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(4))));
bevp_sec = static_cast<BEC_2_4_6_TextString*>(beq->beva_cmdl->bem_get_1(beq->bevt_111_ta_ph));
beq->bevt_114_ta_ph = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(2))));
beq->bevt_113_ta_ph = beq->beva_cmdl->bem_get_1(beq->bevt_114_ta_ph);
beq->bevt_115_ta_ph = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString(3, {0x68,0x65,0x78}))));
beq->bevt_112_ta_ph = beq->bevt_113_ta_ph->bemd_1(643138569, beq->bevt_115_ta_ph);
if ((static_cast<BEC_2_5_4_LogicBool*>(beq->bevt_112_ta_ph))->bevi_bool) {
beq->bevt_117_ta_ph = static_cast<BEC_2_4_7_TextStrings*>(BEC_2_4_7_TextStrings::bece_BEC_2_4_7_TextStrings_bevs_inst);
beq->bevt_116_ta_ph = beq->bevt_117_ta_ph->bem_notEmpty_1(bevp_ssid);
if (beq->bevt_116_ta_ph->bevi_bool) {
beq->bevt_118_ta_ph = static_cast<BEC_2_6_3_EncodeHex*>(BEC_2_6_3_EncodeHex::bece_BEC_2_6_3_EncodeHex_bevs_inst);
bevp_ssid = beq->bevt_118_ta_ph->bem_decode_1(bevp_ssid);
} 
beq->bevt_120_ta_ph = static_cast<BEC_2_4_7_TextStrings*>(BEC_2_4_7_TextStrings::bece_BEC_2_4_7_TextStrings_bevs_inst);
beq->bevt_119_ta_ph = beq->bevt_120_ta_ph->bem_notEmpty_1(bevp_sec);
if (beq->bevt_119_ta_ph->bevi_bool) {
beq->bevt_121_ta_ph = static_cast<BEC_2_6_3_EncodeHex*>(BEC_2_6_3_EncodeHex::bece_BEC_2_6_3_EncodeHex_bevs_inst);
bevp_sec = beq->bevt_121_ta_ph->bem_decode_1(bevp_sec);
} 
} 
beq->bevt_123_ta_ph = static_cast<BEC_2_4_7_TextStrings*>(BEC_2_4_7_TextStrings::bece_BEC_2_4_7_TextStrings_bevs_inst);
beq->bevt_122_ta_ph = beq->bevt_123_ta_ph->bem_notEmpty_1(bevp_ssid);
if (beq->bevt_122_ta_ph->bevi_bool) {
bevp_config->bem_put_2(bevp_shssidi, bevp_ssid);
beq->bevt_125_ta_ph = static_cast<BEC_2_4_7_TextStrings*>(BEC_2_4_7_TextStrings::bece_BEC_2_4_7_TextStrings_bevs_inst);
beq->bevt_124_ta_ph = beq->bevt_125_ta_ph->bem_notEmpty_1(bevp_sec);
if (beq->bevt_124_ta_ph->bevi_bool) {
bevp_config->bem_put_2(bevp_shseci, bevp_sec);
} 
 else  {
beq->bevt_126_ta_ph = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString(11, {0x73,0x65,0x63,0x20,0x6D,0x69,0x73,0x73,0x69,0x6E,0x67}))));
beq->bevt_126_ta_ph->bem_print_0();
beq->bevt_127_ta_ph = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString(0, {}))));
bevp_config->bem_put_2(bevp_shseci, beq->bevt_127_ta_ph);
} 
beq->bevt_128_ta_ph = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString(39, {0x57,0x69,0x66,0x69,0x20,0x53,0x65,0x74,0x75,0x70,0x20,0x57,0x72,0x69,0x74,0x74,0x65,0x6E,0x2C,0x20,0x72,0x65,0x73,0x74,0x61,0x72,0x74,0x20,0x74,0x6F,0x20,0x61,0x63,0x74,0x69,0x76,0x61,0x74,0x65}))));
return beq->bevt_128_ta_ph;
} 
 else  {
beq->bevt_129_ta_ph = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString(12, {0x73,0x73,0x69,0x64,0x20,0x6D,0x69,0x73,0x73,0x69,0x6E,0x67}))));
beq->bevt_129_ta_ph->bem_print_0();
beq->bevt_130_ta_ph = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString(0, {}))));
bevp_config->bem_put_2(bevp_shssidi, beq->bevt_130_ta_ph);
beq->bevt_131_ta_ph = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString(0, {}))));
bevp_config->bem_put_2(bevp_shseci, beq->bevt_131_ta_ph);
beq->bevt_132_ta_ph = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString(39, {0x57,0x69,0x66,0x69,0x20,0x53,0x65,0x74,0x75,0x70,0x20,0x63,0x6C,0x65,0x61,0x72,0x65,0x64,0x2C,0x20,0x72,0x65,0x73,0x74,0x61,0x72,0x74,0x20,0x74,0x6F,0x20,0x61,0x63,0x74,0x69,0x76,0x61,0x74,0x65}))));
return beq->bevt_132_ta_ph;
} 
} 
 else  {
beq->bevt_134_ta_ph = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString(5, {0x72,0x65,0x73,0x65,0x74}))));
beq->bevt_133_ta_ph = beq->bevl_cmd->bem_equals_1(beq->bevt_134_ta_ph);
if (beq->bevt_133_ta_ph->bevi_bool) {
bem_reset_0();
beq->bevt_135_ta_ph = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString(12, {0x44,0x65,0x76,0x69,0x63,0x65,0x20,0x72,0x65,0x73,0x65,0x74}))));
return beq->bevt_135_ta_ph;
} 
 else  {
beq->bevt_137_ta_ph = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString(10, {0x70,0x75,0x74,0x63,0x6F,0x6E,0x66,0x69,0x67,0x73}))));
beq->bevt_136_ta_ph = beq->bevl_cmd->bem_equals_1(beq->bevt_137_ta_ph);
if (beq->bevt_136_ta_ph->bevi_bool) {
beq->bevt_140_ta_ph = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(2))));
beq->bevt_139_ta_ph = beq->beva_cmdl->bem_get_1(beq->bevt_140_ta_ph);
beq->bevt_141_ta_ph = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString(4, {0x76,0x68,0x65,0x78}))));
beq->bevt_138_ta_ph = beq->bevt_139_ta_ph->bemd_1(643138569, beq->bevt_141_ta_ph);
if ((static_cast<BEC_2_5_4_LogicBool*>(beq->bevt_138_ta_ph))->bevi_bool) {
beq->bevl_deHex = static_cast<BEC_2_5_4_LogicBool*>(BECS_Runtime::boolTrue);
} 
 else  {
beq->bevl_deHex = static_cast<BEC_2_5_4_LogicBool*>(BECS_Runtime::boolFalse);
} 
beq->bevt_142_ta_ph = beq->beva_cmdl->bem_sizeGet_0();
beq->bevt_143_ta_ph = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(1))));
beq->bevl_cmdle = beq->bevt_142_ta_ph->bem_subtract_1(beq->bevt_143_ta_ph);
beq->bevl_k = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(3))));
while (true)
 {
if (beq->bevl_k->bevi_int < beq->bevl_cmdle->bevi_int) {
beq->bevt_144_ta_ph = BECS_Runtime::boolTrue;
 } else { 
beq->bevt_144_ta_ph = BECS_Runtime::boolFalse;
}
if (beq->bevt_144_ta_ph->bevi_bool) {
beq->bevl_key = static_cast<BEC_2_4_6_TextString*>(beq->beva_cmdl->bem_get_1(beq->bevl_k));
beq->bevl_k->bevi_int++;
if (beq->bevl_k->bevi_int < beq->bevl_cmdle->bevi_int) {
beq->bevt_145_ta_ph = BECS_Runtime::boolTrue;
 } else { 
beq->bevt_145_ta_ph = BECS_Runtime::boolFalse;
}
if (beq->bevt_145_ta_ph->bevi_bool) {
beq->bevl_value = static_cast<BEC_2_4_6_TextString*>(beq->beva_cmdl->bem_get_1(beq->bevl_k));
} 
 else  {
beq->bevl_value = nullptr;
} 
beq->bevt_147_ta_ph = static_cast<BEC_2_4_7_TextStrings*>(BEC_2_4_7_TextStrings::bece_BEC_2_4_7_TextStrings_bevs_inst);
beq->bevt_146_ta_ph = beq->bevt_147_ta_ph->bem_notEmpty_1(beq->bevl_key);
if (beq->bevt_146_ta_ph->bevi_bool) {
beq->bevt_148_ta_ph = beq->bevl_key->bem_begins_1(bevp_fcdot);
if (beq->bevt_148_ta_ph->bevi_bool) {
beq->bevl_keyi = static_cast<BEC_2_4_3_MathInt*>(bevp_config->bem_getPos_1(beq->bevl_key));
beq->bevt_150_ta_ph = static_cast<BEC_2_4_7_TextStrings*>(BEC_2_4_7_TextStrings::bece_BEC_2_4_7_TextStrings_bevs_inst);
beq->bevt_149_ta_ph = beq->bevt_150_ta_ph->bem_isEmpty_1(beq->bevl_value);
if (beq->bevt_149_ta_ph->bevi_bool) {
beq->bevt_151_ta_ph = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString(0, {}))));
bevp_config->bem_put_2(beq->bevl_keyi, beq->bevt_151_ta_ph);
} 
 else  {
if (beq->bevl_deHex->bevi_bool) {
beq->bevt_152_ta_ph = static_cast<BEC_2_6_3_EncodeHex*>(BEC_2_6_3_EncodeHex::bece_BEC_2_6_3_EncodeHex_bevs_inst);
beq->bevl_value = beq->bevt_152_ta_ph->bem_decode_1(beq->bevl_value);
} 
bevp_config->bem_put_2(beq->bevl_keyi, beq->bevl_value);
} 
} 
 else  {
beq->bevt_153_ta_ph = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString(22, {0x63,0x6F,0x6E,0x66,0x69,0x67,0x73,0x20,0x66,0x61,0x69,0x6C,0x65,0x64,0x20,0x62,0x61,0x64,0x20,0x6B,0x65,0x79}))));
return beq->bevt_153_ta_ph;
} 
} 
beq->bevl_k->bevi_int++;
} 
 else  {
break;
} 
} 
beq->bevt_154_ta_ph = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString(11, {0x63,0x6F,0x6E,0x66,0x69,0x67,0x73,0x20,0x73,0x65,0x74}))));
return beq->bevt_154_ta_ph;
} 
 else  {
beq->bevt_156_ta_ph = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString(9, {0x6D,0x61,0x79,0x62,0x65,0x73,0x61,0x76,0x65}))));
beq->bevt_155_ta_ph = beq->bevl_cmd->bem_equals_1(beq->bevt_156_ta_ph);
if (beq->bevt_155_ta_ph->bevi_bool) {
bevp_config->bem_maybeSave_0();
bevp_needsGc = static_cast<BEC_2_5_4_LogicBool*>(BECS_Runtime::boolTrue);
beq->bevt_157_ta_ph = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString(11, {0x6D,0x61,0x79,0x62,0x65,0x20,0x73,0x61,0x76,0x65,0x64}))));
return beq->bevt_157_ta_ph;
} 
 else  {
beq->bevt_159_ta_ph = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString(9, {0x73,0x79,0x73,0x75,0x70,0x64,0x61,0x74,0x65}))));
beq->bevt_158_ta_ph = beq->bevl_cmd->bem_equals_1(beq->bevt_159_ta_ph);
if (beq->bevt_158_ta_ph->bevi_bool) {
beq->bevt_160_ta_ph = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(2))));
bevp_supurl = static_cast<BEC_2_4_6_TextString*>(beq->beva_cmdl->bem_get_1(beq->bevt_160_ta_ph));
beq->bevt_161_ta_ph = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString(10, {0x73,0x65,0x74,0x20,0x73,0x75,0x70,0x75,0x72,0x6C}))));
return beq->bevt_161_ta_ph;
} 
 else  {
beq->bevt_163_ta_ph = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString(7, {0x72,0x65,0x73,0x74,0x61,0x72,0x74}))));
beq->bevt_162_ta_ph = beq->bevl_cmd->bem_equals_1(beq->bevt_163_ta_ph);
if (beq->bevt_162_ta_ph->bevi_bool) {
bevp_needsFsRestart = static_cast<BEC_2_5_4_LogicBool*>(BECS_Runtime::boolTrue);
beq->bevt_164_ta_ph = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString(20, {0x57,0x69,0x6C,0x6C,0x20,0x72,0x65,0x73,0x74,0x61,0x72,0x74,0x20,0x73,0x6F,0x6F,0x6E,0x69,0x73,0x68}))));
return beq->bevt_164_ta_ph;
} 
 else  {
beq->bevt_166_ta_ph = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString(9, {0x67,0x65,0x74,0x73,0x77,0x69,0x6E,0x66,0x6F}))));
beq->bevt_165_ta_ph = beq->bevl_cmd->bem_equals_1(beq->bevt_166_ta_ph);
if (beq->bevt_165_ta_ph->bevi_bool) {
return bevp_swInfo;
} 
 else  {
beq->bevt_167_ta_ph = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString(20, {0x75,0x6E,0x72,0x65,0x63,0x6F,0x67,0x6E,0x69,0x7A,0x65,0x64,0x20,0x63,0x6F,0x6D,0x6D,0x61,0x6E,0x64}))));
return beq->bevt_167_ta_ph;
} 
} 
} 
} 
} 
} 
} 
beq->bevt_168_ta_ph = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString(17, {0x53,0x6F,0x6D,0x65,0x74,0x68,0x69,0x6E,0x67,0x27,0x73,0x20,0x66,0x69,0x73,0x68,0x79}))));
return beq->bevt_168_ta_ph;
}
BEC_2_8_8_EmbeddedAppShell* BEC_2_8_8_EmbeddedAppShell::bem_reset_0() {
struct bes { BEC_2_4_6_TextString* bevt_0_ta_ph; BEC_2_4_6_TextString* bevt_1_ta_ph; BEC_2_4_6_TextString* bevt_2_ta_ph; BEC_2_4_6_TextString* bevt_3_ta_ph; BEC_2_4_6_TextString* bevt_4_ta_ph; BEC_2_6_6_SystemObject* bevt_5_ta_ph; BEC_2_4_6_TextString* bevt_6_ta_ph; BEC_2_4_6_TextString* bevt_7_ta_ph; BEC_2_6_6_SystemObject* bevt_8_ta_ph; BEC_2_4_6_TextString* bevt_9_ta_ph; BEC_2_4_6_TextString* bevt_10_ta_ph; BEC_2_6_6_SystemObject* bevt_11_ta_ph; BEC_2_4_6_TextString* bevt_12_ta_ph; BEC_2_4_6_TextString* bevt_13_ta_ph; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->bevt_0_ta_ph = nullptr;
beq->bevt_1_ta_ph = nullptr;
beq->bevt_2_ta_ph = nullptr;
beq->bevt_3_ta_ph = nullptr;
beq->bevt_4_ta_ph = nullptr;
beq->bevt_5_ta_ph = nullptr;
beq->bevt_6_ta_ph = nullptr;
beq->bevt_7_ta_ph = nullptr;
beq->bevt_8_ta_ph = nullptr;
beq->bevt_9_ta_ph = nullptr;
beq->bevt_10_ta_ph = nullptr;
beq->bevt_11_ta_ph = nullptr;
beq->bevt_12_ta_ph = nullptr;
beq->bevt_13_ta_ph = nullptr;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(15);
beq->bevt_0_ta_ph = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString(0, {}))));
bevp_config->bem_put_2(bevp_shpassi, beq->bevt_0_ta_ph);
beq->bevt_1_ta_ph = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString(0, {}))));
bevp_config->bem_put_2(bevp_shssidi, beq->bevt_1_ta_ph);
beq->bevt_2_ta_ph = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString(0, {}))));
bevp_config->bem_put_2(bevp_shseci, beq->bevt_2_ta_ph);
beq->bevt_3_ta_ph = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString(0, {}))));
bevp_config->bem_put_2(bevp_shspassi, beq->bevt_3_ta_ph);
beq->bevt_4_ta_ph = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString(0, {}))));
bevp_config->bem_put_2(bevp_shdidi, beq->bevt_4_ta_ph);
beq->bevt_6_ta_ph = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString(9, {0x66,0x63,0x2E,0x6D,0x71,0x68,0x6F,0x73,0x74}))));
beq->bevt_5_ta_ph = bevp_config->bem_getPos_1(beq->bevt_6_ta_ph);
beq->bevt_7_ta_ph = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString(0, {}))));
bevp_config->bem_put_2(static_cast<BEC_2_4_3_MathInt*>(beq->bevt_5_ta_ph) , beq->bevt_7_ta_ph);
beq->bevt_9_ta_ph = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString(9, {0x66,0x63,0x2E,0x6D,0x71,0x75,0x73,0x65,0x72}))));
beq->bevt_8_ta_ph = bevp_config->bem_getPos_1(beq->bevt_9_ta_ph);
beq->bevt_10_ta_ph = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString(0, {}))));
bevp_config->bem_put_2(static_cast<BEC_2_4_3_MathInt*>(beq->bevt_8_ta_ph) , beq->bevt_10_ta_ph);
beq->bevt_12_ta_ph = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString(9, {0x66,0x63,0x2E,0x6D,0x71,0x70,0x61,0x73,0x73}))));
beq->bevt_11_ta_ph = bevp_config->bem_getPos_1(beq->bevt_12_ta_ph);
beq->bevt_13_ta_ph = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString(0, {}))));
bevp_config->bem_put_2(static_cast<BEC_2_4_3_MathInt*>(beq->bevt_11_ta_ph) , beq->bevt_13_ta_ph);
bem_clearStates_0();
bevp_needsFsRestart = static_cast<BEC_2_5_4_LogicBool*>(BECS_Runtime::boolTrue);
return this;
}
BEC_2_6_6_SystemObject* BEC_2_8_8_EmbeddedAppShell::bem_appGet_0() {
struct bes {  BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(1);
return bevp_app;
}
BEC_2_8_8_EmbeddedAppShell* BEC_2_8_8_EmbeddedAppShell::bem_appSet_1(BEC_2_6_6_SystemObject* bevt_0_ta_SET) {
struct bes { BEC_2_6_6_SystemObject* bevt_0_ta_SET; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->bevt_0_ta_SET = bevt_0_ta_SET;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(2);
bevp_app = static_cast<BEC_2_8_3_EmbeddedApp*>(beq->bevt_0_ta_SET);
return this;
}
BEC_2_8_6_EmbeddedConfig* BEC_2_8_8_EmbeddedAppShell::bem_configGet_0() {
struct bes {  BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(1);
return bevp_config;
}
BEC_2_8_8_EmbeddedAppShell* BEC_2_8_8_EmbeddedAppShell::bem_configSet_1(BEC_2_6_6_SystemObject* bevt_0_ta_SET) {
struct bes { BEC_2_6_6_SystemObject* bevt_0_ta_SET; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->bevt_0_ta_SET = bevt_0_ta_SET;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(2);
bevp_config = static_cast<BEC_2_8_6_EmbeddedConfig*>(beq->bevt_0_ta_SET);
return this;
}
BEC_2_4_3_MathInt* BEC_2_8_8_EmbeddedAppShell::bem_nowupGet_0() {
struct bes {  BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(1);
return bevp_nowup;
}
BEC_2_8_8_EmbeddedAppShell* BEC_2_8_8_EmbeddedAppShell::bem_nowupSet_1(BEC_2_6_6_SystemObject* bevt_0_ta_SET) {
struct bes { BEC_2_6_6_SystemObject* bevt_0_ta_SET; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->bevt_0_ta_SET = bevt_0_ta_SET;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(2);
bevp_nowup = static_cast<BEC_2_4_3_MathInt*>(beq->bevt_0_ta_SET);
return this;
}
BEC_2_4_6_TextString* BEC_2_8_8_EmbeddedAppShell::bem_lastEventsResGet_0() {
struct bes {  BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(1);
return bevp_lastEventsRes;
}
BEC_2_8_8_EmbeddedAppShell* BEC_2_8_8_EmbeddedAppShell::bem_lastEventsResSet_1(BEC_2_6_6_SystemObject* bevt_0_ta_SET) {
struct bes { BEC_2_6_6_SystemObject* bevt_0_ta_SET; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->bevt_0_ta_SET = bevt_0_ta_SET;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(2);
bevp_lastEventsRes = static_cast<BEC_2_4_6_TextString*>(beq->bevt_0_ta_SET);
return this;
}
BEC_2_5_4_LogicBool* BEC_2_8_8_EmbeddedAppShell::bem_needsStateUpGet_0() {
struct bes {  BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(1);
return bevp_needsStateUp;
}
BEC_2_8_8_EmbeddedAppShell* BEC_2_8_8_EmbeddedAppShell::bem_needsStateUpSet_1(BEC_2_6_6_SystemObject* bevt_0_ta_SET) {
struct bes { BEC_2_6_6_SystemObject* bevt_0_ta_SET; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->bevt_0_ta_SET = bevt_0_ta_SET;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(2);
bevp_needsStateUp = static_cast<BEC_2_5_4_LogicBool*>(beq->bevt_0_ta_SET);
return this;
}
BEC_2_5_4_LogicBool* BEC_2_8_8_EmbeddedAppShell::bem_needsStateUpSoonGet_0() {
struct bes {  BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(1);
return bevp_needsStateUpSoon;
}
BEC_2_8_8_EmbeddedAppShell* BEC_2_8_8_EmbeddedAppShell::bem_needsStateUpSoonSet_1(BEC_2_6_6_SystemObject* bevt_0_ta_SET) {
struct bes { BEC_2_6_6_SystemObject* bevt_0_ta_SET; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->bevt_0_ta_SET = bevt_0_ta_SET;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(2);
bevp_needsStateUpSoon = static_cast<BEC_2_5_4_LogicBool*>(beq->bevt_0_ta_SET);
return this;
}
BEC_2_9_4_ContainerList* BEC_2_8_8_EmbeddedAppShell::bem_controlsGet_0() {
struct bes {  BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(1);
return bevp_controls;
}
BEC_2_8_8_EmbeddedAppShell* BEC_2_8_8_EmbeddedAppShell::bem_controlsSet_1(BEC_2_6_6_SystemObject* bevt_0_ta_SET) {
struct bes { BEC_2_6_6_SystemObject* bevt_0_ta_SET; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->bevt_0_ta_SET = bevt_0_ta_SET;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(2);
bevp_controls = static_cast<BEC_2_9_4_ContainerList*>(beq->bevt_0_ta_SET);
return this;
}
BEC_2_9_4_ContainerList* BEC_2_8_8_EmbeddedAppShell::bem_loopersGet_0() {
struct bes {  BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(1);
return bevp_loopers;
}
BEC_2_8_8_EmbeddedAppShell* BEC_2_8_8_EmbeddedAppShell::bem_loopersSet_1(BEC_2_6_6_SystemObject* bevt_0_ta_SET) {
struct bes { BEC_2_6_6_SystemObject* bevt_0_ta_SET; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->bevt_0_ta_SET = bevt_0_ta_SET;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(2);
bevp_loopers = static_cast<BEC_2_9_4_ContainerList*>(beq->bevt_0_ta_SET);
return this;
}
BEC_2_8_9_EmbeddedTCPClient* BEC_2_8_8_EmbeddedAppShell::bem_conconGet_0() {
struct bes {  BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(1);
return bevp_concon;
}
BEC_2_8_8_EmbeddedAppShell* BEC_2_8_8_EmbeddedAppShell::bem_conconSet_1(BEC_2_6_6_SystemObject* bevt_0_ta_SET) {
struct bes { BEC_2_6_6_SystemObject* bevt_0_ta_SET; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->bevt_0_ta_SET = bevt_0_ta_SET;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(2);
bevp_concon = static_cast<BEC_2_8_9_EmbeddedTCPClient*>(beq->bevt_0_ta_SET);
return this;
}
BEC_2_4_6_TextString* BEC_2_8_8_EmbeddedAppShell::bem_pinGet_0() {
struct bes {  BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(1);
return bevp_pin;
}
BEC_2_8_8_EmbeddedAppShell* BEC_2_8_8_EmbeddedAppShell::bem_pinSet_1(BEC_2_6_6_SystemObject* bevt_0_ta_SET) {
struct bes { BEC_2_6_6_SystemObject* bevt_0_ta_SET; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->bevt_0_ta_SET = bevt_0_ta_SET;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(2);
bevp_pin = static_cast<BEC_2_4_6_TextString*>(beq->bevt_0_ta_SET);
return this;
}
BEC_2_8_4_EmbeddedMdns* BEC_2_8_8_EmbeddedAppShell::bem_mdserverGet_0() {
struct bes {  BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(1);
return bevp_mdserver;
}
BEC_2_8_8_EmbeddedAppShell* BEC_2_8_8_EmbeddedAppShell::bem_mdserverSet_1(BEC_2_6_6_SystemObject* bevt_0_ta_SET) {
struct bes { BEC_2_6_6_SystemObject* bevt_0_ta_SET; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->bevt_0_ta_SET = bevt_0_ta_SET;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(2);
bevp_mdserver = static_cast<BEC_2_8_4_EmbeddedMdns*>(beq->bevt_0_ta_SET);
return this;
}
BEC_2_8_4_EmbeddedMqtt* BEC_2_8_8_EmbeddedAppShell::bem_mqttGet_0() {
struct bes {  BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(1);
return bevp_mqtt;
}
BEC_2_8_8_EmbeddedAppShell* BEC_2_8_8_EmbeddedAppShell::bem_mqttSet_1(BEC_2_6_6_SystemObject* bevt_0_ta_SET) {
struct bes { BEC_2_6_6_SystemObject* bevt_0_ta_SET; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->bevt_0_ta_SET = bevt_0_ta_SET;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(2);
bevp_mqtt = static_cast<BEC_2_8_4_EmbeddedMqtt*>(beq->bevt_0_ta_SET);
return this;
}
BEC_2_8_9_EmbeddedTCPServer* BEC_2_8_8_EmbeddedAppShell::bem_tcpserverGet_0() {
struct bes {  BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(1);
return bevp_tcpserver;
}
BEC_2_8_8_EmbeddedAppShell* BEC_2_8_8_EmbeddedAppShell::bem_tcpserverSet_1(BEC_2_6_6_SystemObject* bevt_0_ta_SET) {
struct bes { BEC_2_6_6_SystemObject* bevt_0_ta_SET; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->bevt_0_ta_SET = bevt_0_ta_SET;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(2);
bevp_tcpserver = static_cast<BEC_2_8_9_EmbeddedTCPServer*>(beq->bevt_0_ta_SET);
return this;
}
BEC_2_8_9_EmbeddedTCPServer* BEC_2_8_8_EmbeddedAppShell::bem_conserverGet_0() {
struct bes {  BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(1);
return bevp_conserver;
}
BEC_2_8_8_EmbeddedAppShell* BEC_2_8_8_EmbeddedAppShell::bem_conserverSet_1(BEC_2_6_6_SystemObject* bevt_0_ta_SET) {
struct bes { BEC_2_6_6_SystemObject* bevt_0_ta_SET; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->bevt_0_ta_SET = bevt_0_ta_SET;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(2);
bevp_conserver = static_cast<BEC_2_8_9_EmbeddedTCPServer*>(beq->bevt_0_ta_SET);
return this;
}
BEC_2_6_6_SystemObject* BEC_2_8_8_EmbeddedAppShell::bemd_0(int32_t callId) {
switch (callId) {
case 1638522954: return bem_initControls_0();
case -1397590890: return bem_initRandom_0();
case 1733902865: return bem_lastEventsResGet_0();
case 1816776120: return bem_initMq_0();
case 1854188166: return bem_reset_0();
case 875606373: return bem_appGet_0();
case 1169081041: return bem_nowupGet_0();
case 659365477: return bem_buildSwInfo_0();
case 2080347263: return bem_buildSwInfoIn_0();
case 303267955: return bem_mqStateUp_0();
case -81368761: return bem_loadPasses_0();
case -709425261: return bem_mdserverGet_0();
case 675826141: return bem_startWifi_0();
case 196153092: return bem_needsStateUpGet_0();
case -1592447609: return bem_clearStates_0();
case 766095905: return bem_tcpserverGet_0();
case -138813948: return bem_mqttGet_0();
case -892153784: return bem_checkWifiUp_0();
case 1210683371: return bem_configGet_0();
case -1219107877: return bem_main_0();
case 2029400688: return bem_networkInit_0();
case -1975826961: return bem_loopersGet_0();
case -1460993466: return bem_controlsGet_0();
case -671092123: return bem_checkMakeIds_0();
case -1512853507: return bem_conconGet_0();
case -330685574: return bem_handleLoop_0();
case 860365963: return bem_needsStateUpSoonGet_0();
case -1646341150: return bem_startLoop_0();
case -1924192972: return bem_buildControlsIn_0();
case 731034202: return bem_pinGet_0();
case -1469369457: return bem_buildControls_0();
case 622114428: return bem_conserverGet_0();
case 1271285058: return bem_checkWifiAp_0();
case -467870059: return bem_initAp_0();
}
return bevs_super::bemd_0(callId);
}
BEC_2_6_6_SystemObject* BEC_2_8_8_EmbeddedAppShell::bemd_1(int32_t callId, BEC_2_6_6_SystemObject* bevd_0) {
switch (callId) {
case 472494009: return bem_doState_1(static_cast<BEC_2_9_4_ContainerList*>(bevd_0));
case 826290599: return bem_getLastEvents_1(static_cast<BEC_2_9_4_ContainerList*>(bevd_0));
case 1438708777: return bem_nowupSet_1(bevd_0);
case 2005940174: return bem_configSet_1(bevd_0);
case -1719080846: return bem_conconSet_1(bevd_0);
case -648782044: return bem_controlsSet_1(bevd_0);
case -255341944: return bem_sendWebPage_1(bevd_0);
case 1707478197: return bem_needsStateUpSoonSet_1(bevd_0);
case -1618720108: return bem_mqttSet_1(bevd_0);
case -785541804: return bem_loopersSet_1(bevd_0);
case -996672766: return bem_mdserverSet_1(bevd_0);
case -1186176816: return bem_appSet_1(bevd_0);
case -1017687456: return bem_pinSet_1(bevd_0);
case 882165402: return bem_sysupdate_1(static_cast<BEC_2_4_6_TextString*>(bevd_0));
case -1115403092: return bem_conserverSet_1(bevd_0);
case 1480641973: return bem_tcpserverSet_1(bevd_0);
case -95615898: return bem_mqConfUp_1(static_cast<BEC_2_5_4_LogicBool*>(bevd_0));
case 1198618340: return bem_needsStateUpSet_1(bevd_0);
case -446025531: return bem_lastEventsResSet_1(bevd_0);
}
return bevs_super::bemd_1(callId, bevd_0);
}
BEC_2_6_6_SystemObject* BEC_2_8_8_EmbeddedAppShell::bemd_2(int32_t callId, BEC_2_6_6_SystemObject* bevd_0, BEC_2_6_6_SystemObject* bevd_1) {
switch (callId) {
case -290210157: return bem_handleMqtt_2(static_cast<BEC_2_4_6_TextString*>(bevd_0), static_cast<BEC_2_4_6_TextString*>(bevd_1));
}
return bevs_super::bemd_2(callId, bevd_0, bevd_1);
}
BEC_2_6_6_SystemObject* BEC_2_8_8_EmbeddedAppShell::bemd_3(int32_t callId, BEC_2_6_6_SystemObject* bevd_0, BEC_2_6_6_SystemObject* bevd_1, BEC_2_6_6_SystemObject* bevd_2) {
switch (callId) {
case 2046895056: return bem_doCmd_3(static_cast<BEC_2_4_6_TextString*>(bevd_0), static_cast<BEC_2_4_6_TextString*>(bevd_1), static_cast<BEC_2_4_6_TextString*>(bevd_2));
case 2077815246: return bem_doCmdl_3(static_cast<BEC_2_4_6_TextString*>(bevd_0), static_cast<BEC_2_4_6_TextString*>(bevd_1), static_cast<BEC_2_9_4_ContainerList*>(bevd_2));
case -638531368: return bem_buildControl_3(static_cast<BEC_2_4_3_MathInt*>(bevd_0), static_cast<BEC_2_4_6_TextString*>(bevd_1), static_cast<BEC_2_4_6_TextString*>(bevd_2));
case -2120421678: return bem_doCmdlSec_3(static_cast<BEC_2_4_6_TextString*>(bevd_0), static_cast<BEC_2_4_6_TextString*>(bevd_1), static_cast<BEC_2_9_4_ContainerList*>(bevd_2));
}
return bevs_super::bemd_3(callId, bevd_0, bevd_1, bevd_2);
}
BEC_2_6_6_SystemObject* BEC_2_8_8_EmbeddedAppShell::bemc_create() {
return new BEC_2_8_8_EmbeddedAppShell();
}
void BEC_2_8_8_EmbeddedAppShell::bemc_setInitial(BEC_2_6_6_SystemObject* becc_inst) {
BEC_2_8_8_EmbeddedAppShell::bece_BEC_2_8_8_EmbeddedAppShell_bevs_inst = static_cast<BEC_2_8_8_EmbeddedAppShell*>(becc_inst);
}
BEC_2_6_6_SystemObject* BEC_2_8_8_EmbeddedAppShell::bemc_getInitial() {
return BEC_2_8_8_EmbeddedAppShell::bece_BEC_2_8_8_EmbeddedAppShell_bevs_inst;
}
void BEC_2_8_8_EmbeddedAppShell::bemg_doMark() {
bevg_gcMark = BECS_Runtime::bevg_currentGcMark;
if (bevp_app != nullptr && bevp_app->bevg_gcMark != BECS_Runtime::bevg_currentGcMark) {
bevp_app->bemg_doMark();
}
if (bevp_config != nullptr && bevp_config->bevg_gcMark != BECS_Runtime::bevg_currentGcMark) {
bevp_config->bemg_doMark();
}
if (bevp_nowup != nullptr && bevp_nowup->bevg_gcMark != BECS_Runtime::bevg_currentGcMark) {
bevp_nowup->bemg_doMark();
}
if (bevp_lastEventsRes != nullptr && bevp_lastEventsRes->bevg_gcMark != BECS_Runtime::bevg_currentGcMark) {
bevp_lastEventsRes->bemg_doMark();
}
if (bevp_needsStateUp != nullptr && bevp_needsStateUp->bevg_gcMark != BECS_Runtime::bevg_currentGcMark) {
bevp_needsStateUp->bemg_doMark();
}
if (bevp_needsStateUpSoon != nullptr && bevp_needsStateUpSoon->bevg_gcMark != BECS_Runtime::bevg_currentGcMark) {
bevp_needsStateUpSoon->bemg_doMark();
}
if (bevp_controls != nullptr && bevp_controls->bevg_gcMark != BECS_Runtime::bevg_currentGcMark) {
bevp_controls->bemg_doMark();
}
if (bevp_loopers != nullptr && bevp_loopers->bevg_gcMark != BECS_Runtime::bevg_currentGcMark) {
bevp_loopers->bemg_doMark();
}
if (bevp_concon != nullptr && bevp_concon->bevg_gcMark != BECS_Runtime::bevg_currentGcMark) {
bevp_concon->bemg_doMark();
}
if (bevp_shpini != nullptr && bevp_shpini->bevg_gcMark != BECS_Runtime::bevg_currentGcMark) {
bevp_shpini->bemg_doMark();
}
if (bevp_shpassi != nullptr && bevp_shpassi->bevg_gcMark != BECS_Runtime::bevg_currentGcMark) {
bevp_shpassi->bemg_doMark();
}
if (bevp_shspassi != nullptr && bevp_shspassi->bevg_gcMark != BECS_Runtime::bevg_currentGcMark) {
bevp_shspassi->bemg_doMark();
}
if (bevp_shssidi != nullptr && bevp_shssidi->bevg_gcMark != BECS_Runtime::bevg_currentGcMark) {
bevp_shssidi->bemg_doMark();
}
if (bevp_shseci != nullptr && bevp_shseci->bevg_gcMark != BECS_Runtime::bevg_currentGcMark) {
bevp_shseci->bemg_doMark();
}
if (bevp_shdidi != nullptr && bevp_shdidi->bevg_gcMark != BECS_Runtime::bevg_currentGcMark) {
bevp_shdidi->bemg_doMark();
}
if (bevp_zero != nullptr && bevp_zero->bevg_gcMark != BECS_Runtime::bevg_currentGcMark) {
bevp_zero->bemg_doMark();
}
if (bevp_nextUpdateCheck != nullptr && bevp_nextUpdateCheck->bevg_gcMark != BECS_Runtime::bevg_currentGcMark) {
bevp_nextUpdateCheck->bemg_doMark();
}
if (bevp_nextMq != nullptr && bevp_nextMq->bevg_gcMark != BECS_Runtime::bevg_currentGcMark) {
bevp_nextMq->bemg_doMark();
}
if (bevp_nextSwInfo != nullptr && bevp_nextSwInfo->bevg_gcMark != BECS_Runtime::bevg_currentGcMark) {
bevp_nextSwInfo->bemg_doMark();
}
if (bevp_nextRestart != nullptr && bevp_nextRestart->bevg_gcMark != BECS_Runtime::bevg_currentGcMark) {
bevp_nextRestart->bemg_doMark();
}
if (bevp_nextMaybeSave != nullptr && bevp_nextMaybeSave->bevg_gcMark != BECS_Runtime::bevg_currentGcMark) {
bevp_nextMaybeSave->bemg_doMark();
}
if (bevp_nextApCheck != nullptr && bevp_nextApCheck->bevg_gcMark != BECS_Runtime::bevg_currentGcMark) {
bevp_nextApCheck->bemg_doMark();
}
if (bevp_nextWifiCheck != nullptr && bevp_nextWifiCheck->bevg_gcMark != BECS_Runtime::bevg_currentGcMark) {
bevp_nextWifiCheck->bemg_doMark();
}
if (bevp_slashn != nullptr && bevp_slashn->bevg_gcMark != BECS_Runtime::bevg_currentGcMark) {
bevp_slashn->bemg_doMark();
}
if (bevp_slashr != nullptr && bevp_slashr->bevg_gcMark != BECS_Runtime::bevg_currentGcMark) {
bevp_slashr->bemg_doMark();
}
if (bevp_fcdot != nullptr && bevp_fcdot->bevg_gcMark != BECS_Runtime::bevg_currentGcMark) {
bevp_fcdot->bemg_doMark();
}
if (bevp_htmlHead != nullptr && bevp_htmlHead->bevg_gcMark != BECS_Runtime::bevg_currentGcMark) {
bevp_htmlHead->bemg_doMark();
}
if (bevp_needsFsRestart != nullptr && bevp_needsFsRestart->bevg_gcMark != BECS_Runtime::bevg_currentGcMark) {
bevp_needsFsRestart->bemg_doMark();
}
if (bevp_needsRestart != nullptr && bevp_needsRestart->bevg_gcMark != BECS_Runtime::bevg_currentGcMark) {
bevp_needsRestart->bemg_doMark();
}
if (bevp_did != nullptr && bevp_did->bevg_gcMark != BECS_Runtime::bevg_currentGcMark) {
bevp_did->bemg_doMark();
}
if (bevp_swSpec != nullptr && bevp_swSpec->bevg_gcMark != BECS_Runtime::bevg_currentGcMark) {
bevp_swSpec->bemg_doMark();
}
if (bevp_devCode != nullptr && bevp_devCode->bevg_gcMark != BECS_Runtime::bevg_currentGcMark) {
bevp_devCode->bemg_doMark();
}
if (bevp_version != nullptr && bevp_version->bevg_gcMark != BECS_Runtime::bevg_currentGcMark) {
bevp_version->bemg_doMark();
}
if (bevp_swInfo != nullptr && bevp_swInfo->bevg_gcMark != BECS_Runtime::bevg_currentGcMark) {
bevp_swInfo->bemg_doMark();
}
if (bevp_resetByPin != nullptr && bevp_resetByPin->bevg_gcMark != BECS_Runtime::bevg_currentGcMark) {
bevp_resetByPin->bemg_doMark();
}
if (bevp_readBuf != nullptr && bevp_readBuf->bevg_gcMark != BECS_Runtime::bevg_currentGcMark) {
bevp_readBuf->bemg_doMark();
}
if (bevp_supurl != nullptr && bevp_supurl->bevg_gcMark != BECS_Runtime::bevg_currentGcMark) {
bevp_supurl->bemg_doMark();
}
if (bevp_controlSpec != nullptr && bevp_controlSpec->bevg_gcMark != BECS_Runtime::bevg_currentGcMark) {
bevp_controlSpec->bemg_doMark();
}
if (bevp_controlDef != nullptr && bevp_controlDef->bevg_gcMark != BECS_Runtime::bevg_currentGcMark) {
bevp_controlDef->bemg_doMark();
}
if (bevp_needsNetworkInit != nullptr && bevp_needsNetworkInit->bevg_gcMark != BECS_Runtime::bevg_currentGcMark) {
bevp_needsNetworkInit->bemg_doMark();
}
if (bevp_readyForAp != nullptr && bevp_readyForAp->bevg_gcMark != BECS_Runtime::bevg_currentGcMark) {
bevp_readyForAp->bemg_doMark();
}
if (bevp_needsBuildControls != nullptr && bevp_needsBuildControls->bevg_gcMark != BECS_Runtime::bevg_currentGcMark) {
bevp_needsBuildControls->bemg_doMark();
}
if (bevp_needsInitControls != nullptr && bevp_needsInitControls->bevg_gcMark != BECS_Runtime::bevg_currentGcMark) {
bevp_needsInitControls->bemg_doMark();
}
if (bevp_needsGc != nullptr && bevp_needsGc->bevg_gcMark != BECS_Runtime::bevg_currentGcMark) {
bevp_needsGc->bemg_doMark();
}
if (bevp_needsMqConfUp != nullptr && bevp_needsMqConfUp->bevg_gcMark != BECS_Runtime::bevg_currentGcMark) {
bevp_needsMqConfUp->bemg_doMark();
}
if (bevp_looperI != nullptr && bevp_looperI->bevg_gcMark != BECS_Runtime::bevg_currentGcMark) {
bevp_looperI->bemg_doMark();
}
if (bevp_pin != nullptr && bevp_pin->bevg_gcMark != BECS_Runtime::bevg_currentGcMark) {
bevp_pin->bemg_doMark();
}
if (bevp_pass != nullptr && bevp_pass->bevg_gcMark != BECS_Runtime::bevg_currentGcMark) {
bevp_pass->bemg_doMark();
}
if (bevp_spass != nullptr && bevp_spass->bevg_gcMark != BECS_Runtime::bevg_currentGcMark) {
bevp_spass->bemg_doMark();
}
if (bevp_mdserver != nullptr && bevp_mdserver->bevg_gcMark != BECS_Runtime::bevg_currentGcMark) {
bevp_mdserver->bemg_doMark();
}
if (bevp_mqtt != nullptr && bevp_mqtt->bevg_gcMark != BECS_Runtime::bevg_currentGcMark) {
bevp_mqtt->bemg_doMark();
}
if (bevp_tcpserver != nullptr && bevp_tcpserver->bevg_gcMark != BECS_Runtime::bevg_currentGcMark) {
bevp_tcpserver->bemg_doMark();
}
if (bevp_conserver != nullptr && bevp_conserver->bevg_gcMark != BECS_Runtime::bevg_currentGcMark) {
bevp_conserver->bemg_doMark();
}
if (bevp_apSsid != nullptr && bevp_apSsid->bevg_gcMark != BECS_Runtime::bevg_currentGcMark) {
bevp_apSsid->bemg_doMark();
}
if (bevp_apType != nullptr && bevp_apType->bevg_gcMark != BECS_Runtime::bevg_currentGcMark) {
bevp_apType->bemg_doMark();
}
if (bevp_ssid != nullptr && bevp_ssid->bevg_gcMark != BECS_Runtime::bevg_currentGcMark) {
bevp_ssid->bemg_doMark();
}
if (bevp_sec != nullptr && bevp_sec->bevg_gcMark != BECS_Runtime::bevg_currentGcMark) {
bevp_sec->bemg_doMark();
}
}
size_t BEC_2_8_8_EmbeddedAppShell::bemg_getSize() {
return sizeof(*this);
}
BETS_Object* BEC_2_8_8_EmbeddedAppShell::bemc_getType() {
return &BEC_2_8_8_EmbeddedAppShell::bece_BEC_2_8_8_EmbeddedAppShell_bevs_type;
}
BET_2_8_13_EmbeddedSwitchControl::BET_2_8_13_EmbeddedSwitchControl() {
std::vector<std::string> bevs_mtnames = {  };
bevs_fieldNames = {  };
}
BEC_2_6_6_SystemObject* BET_2_8_13_EmbeddedSwitchControl::bems_createInstance() {
return new BEC_2_8_13_EmbeddedSwitchControl();
}
void BET_2_8_13_EmbeddedSwitchControl::bemgt_doMark() {
BEC_2_6_6_SystemObject* bevsl_inst_ref = *bevs_inst_ref;
if (bevsl_inst_ref != nullptr && bevsl_inst_ref->bevg_gcMark != BECS_Runtime::bevg_currentGcMark) {
bevsl_inst_ref->bemg_doMark();
}
}
BEC_2_8_13_EmbeddedSwitchControl* BEC_2_8_13_EmbeddedSwitchControl::bece_BEC_2_8_13_EmbeddedSwitchControl_bevs_inst;

BET_2_8_13_EmbeddedSwitchControl BEC_2_8_13_EmbeddedSwitchControl::bece_BEC_2_8_13_EmbeddedSwitchControl_bevs_type;
BEC_2_6_6_SystemObject** BET_2_8_13_EmbeddedSwitchControl::bevs_inst_ref = (BEC_2_6_6_SystemObject**) &BEC_2_8_13_EmbeddedSwitchControl::bece_BEC_2_8_13_EmbeddedSwitchControl_bevs_inst;

BEC_2_8_13_EmbeddedSwitchControl* BEC_2_8_13_EmbeddedSwitchControl::bem_new_4(BEC_2_6_6_SystemObject* bevk__ash, BEC_2_4_3_MathInt* bevk__conPos, BEC_2_4_6_TextString* bevk__conName, BEC_2_4_6_TextString* bevk__conArgs) {
struct bes { BEC_2_6_6_SystemObject* beva__ash; BEC_2_4_3_MathInt* beva__conPos; BEC_2_4_6_TextString* beva__conName; BEC_2_4_6_TextString* beva__conArgs; BEC_2_9_4_ContainerList* bevl_cal; BEC_2_4_6_TextString* bevl_sdir; BEC_2_4_6_TextString* bevl_spin; BEC_2_5_4_LogicBool* bevt_0_ta_ph; BEC_2_4_6_TextString* bevt_1_ta_ph; BEC_2_4_6_TextString* bevt_2_ta_ph; BEC_2_4_3_MathInt* bevt_3_ta_ph; BEC_2_4_3_MathInt* bevt_4_ta_ph; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->beva__ash = bevk__ash;
beq->beva__conPos = bevk__conPos;
beq->beva__conName = bevk__conName;
beq->beva__conArgs = bevk__conArgs;
beq->bevl_cal = nullptr;
beq->bevl_sdir = nullptr;
beq->bevl_spin = nullptr;
beq->bevt_0_ta_ph = nullptr;
beq->bevt_1_ta_ph = nullptr;
beq->bevt_2_ta_ph = nullptr;
beq->bevt_3_ta_ph = nullptr;
beq->bevt_4_ta_ph = nullptr;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(13);
bevp_ash = static_cast<BEC_2_8_8_EmbeddedAppShell*>(beq->beva__ash);
bevp_diri = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(0))));
bevp_config = bevp_ash->bem_configGet_0();
bevp_app = static_cast<BEC_2_8_3_EmbeddedApp*>(bevp_ash->bem_appGet_0());
bevp_conPos = beq->beva__conPos;
bevp_lastEvent = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt())));
bevp_conName = beq->beva__conName;
beq->bevt_1_ta_ph = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString(1, {0x2C}))));
beq->bevt_0_ta_ph = beq->beva__conArgs->bem_has_1(beq->bevt_1_ta_ph);
if (beq->bevt_0_ta_ph->bevi_bool) {
beq->bevt_2_ta_ph = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString(1, {0x2C}))));
beq->bevl_cal = beq->beva__conArgs->bem_split_1(beq->bevt_2_ta_ph);
beq->bevt_3_ta_ph = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(0))));
beq->bevl_spin = static_cast<BEC_2_4_6_TextString*>(beq->bevl_cal->bem_get_1(beq->bevt_3_ta_ph));
beq->bevt_4_ta_ph = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(1))));
beq->bevl_sdir = static_cast<BEC_2_4_6_TextString*>(beq->bevl_cal->bem_get_1(beq->bevt_4_ta_ph));
bevp_diri = bevp_app->bem_strToInt_1(beq->bevl_sdir);
} 
 else  {
beq->bevl_spin = beq->beva__conArgs;
} 
bevp_pini = bevp_app->bem_strToInt_1(beq->bevl_spin);
return this;
}
BEC_2_8_13_EmbeddedSwitchControl* BEC_2_8_13_EmbeddedSwitchControl::bem_initControl_0() {
struct bes { BEC_2_4_6_TextString* bevl_insw; BEC_2_4_6_TextString* bevt_0_ta_ph; BEC_2_4_6_TextString* bevt_1_ta_ph; BEC_2_5_4_LogicBool* bevt_2_ta_ph; BEC_2_4_7_TextStrings* bevt_3_ta_ph; BEC_2_9_4_ContainerList* bevt_4_ta_ph; BEC_2_9_4_ContainerList* bevt_5_ta_ph; BEC_2_9_4_ContainerList* bevt_6_ta_ph; BEC_2_9_4_ContainerList* bevt_7_ta_ph; BEC_2_9_4_ContainerList* bevt_8_ta_ph; BEC_2_9_4_ContainerList* bevt_9_ta_ph; BEC_2_4_6_TextString* bevt_10_ta_ph; BEC_2_4_6_TextString* bevt_11_ta_ph; BEC_2_4_6_TextString* bevt_12_ta_ph; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->bevl_insw = nullptr;
beq->bevt_0_ta_ph = nullptr;
beq->bevt_1_ta_ph = nullptr;
beq->bevt_2_ta_ph = nullptr;
beq->bevt_3_ta_ph = nullptr;
beq->bevt_4_ta_ph = nullptr;
beq->bevt_5_ta_ph = nullptr;
beq->bevt_6_ta_ph = nullptr;
beq->bevt_7_ta_ph = nullptr;
beq->bevt_8_ta_ph = nullptr;
beq->bevt_9_ta_ph = nullptr;
beq->bevt_10_ta_ph = nullptr;
beq->bevt_11_ta_ph = nullptr;
beq->bevt_12_ta_ph = nullptr;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(15);
bevp_getsw = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString(5, {0x67,0x65,0x74,0x73,0x77}))));
bevp_on = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString(2, {0x6F,0x6E}))));
bevp_off = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString(3, {0x6F,0x66,0x66}))));
bevp_setsw = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString(5, {0x73,0x65,0x74,0x73,0x77}))));
beq->bevt_1_ta_ph = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString(6, {0x73,0x63,0x2E,0x73,0x77,0x2E}))));
beq->bevt_0_ta_ph = beq->bevt_1_ta_ph->bem_add_1(bevp_conPos);
bevp_scswi = static_cast<BEC_2_4_3_MathInt*>(bevp_config->bem_getPos_1(beq->bevt_0_ta_ph));
beq->bevl_insw = bevp_config->bem_get_1(bevp_scswi);
beq->bevt_3_ta_ph = static_cast<BEC_2_4_7_TextStrings*>(BEC_2_4_7_TextStrings::bece_BEC_2_4_7_TextStrings_bevs_inst);
beq->bevt_2_ta_ph = beq->bevt_3_ta_ph->bem_notEmpty_1(beq->bevl_insw);
if (beq->bevt_2_ta_ph->bevi_bool) {
bevp_sw = beq->bevl_insw;
beq->bevt_9_ta_ph = static_cast<BEC_2_9_4_ContainerList*>(((BEC_2_9_4_ContainerList*) (new BEC_2_9_4_ContainerList()))->bem_new_0());
beq->bevt_10_ta_ph = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString(7, {0x64,0x6F,0x73,0x74,0x61,0x74,0x65}))));
beq->bevt_8_ta_ph = static_cast<BEC_2_9_4_ContainerList*>(beq->bevt_9_ta_ph->bem_addValue_1(beq->bevt_10_ta_ph));
beq->bevt_11_ta_ph = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString(5, {0x6E,0x6F,0x74,0x70,0x77}))));
beq->bevt_7_ta_ph = static_cast<BEC_2_9_4_ContainerList*>(beq->bevt_8_ta_ph->bem_addValue_1(beq->bevt_11_ta_ph));
beq->bevt_12_ta_ph = bevp_conPos->bem_toString_0();
beq->bevt_6_ta_ph = static_cast<BEC_2_9_4_ContainerList*>(beq->bevt_7_ta_ph->bem_addValue_1(beq->bevt_12_ta_ph));
beq->bevt_5_ta_ph = static_cast<BEC_2_9_4_ContainerList*>(beq->bevt_6_ta_ph->bem_addValue_1(bevp_setsw));
beq->bevt_4_ta_ph = static_cast<BEC_2_9_4_ContainerList*>(beq->bevt_5_ta_ph->bem_addValue_1(bevp_sw));
bem_doState_1(beq->bevt_4_ta_ph);
} 
return this;
}
BEC_2_4_6_TextString* BEC_2_8_13_EmbeddedSwitchControl::bem_doStateMq_2(BEC_2_4_6_TextString* bevk_topic, BEC_2_4_6_TextString* bevk_payload) {
struct bes { BEC_2_4_6_TextString* beva_topic; BEC_2_4_6_TextString* beva_payload; BEC_2_9_4_ContainerList* bevl_ds; BEC_2_4_6_TextString* bevt_0_ta_ph; BEC_2_4_6_TextString* bevt_1_ta_ph; BEC_2_4_6_TextString* bevt_2_ta_ph; BEC_2_4_6_TextString* bevt_3_ta_ph; BEC_2_4_6_TextString* bevt_4_ta_ph; BEC_2_9_4_ContainerList* bevt_5_ta_ph; BEC_2_9_4_ContainerList* bevt_6_ta_ph; BEC_2_9_4_ContainerList* bevt_7_ta_ph; BEC_2_9_4_ContainerList* bevt_8_ta_ph; BEC_2_9_4_ContainerList* bevt_9_ta_ph; BEC_2_4_6_TextString* bevt_10_ta_ph; BEC_2_4_6_TextString* bevt_11_ta_ph; BEC_2_4_6_TextString* bevt_12_ta_ph; BEC_2_4_6_TextString* bevt_13_ta_ph; BEC_2_4_6_TextString* bevt_14_ta_ph; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->beva_topic = bevk_topic;
beq->beva_payload = bevk_payload;
beq->bevl_ds = nullptr;
beq->bevt_0_ta_ph = nullptr;
beq->bevt_1_ta_ph = nullptr;
beq->bevt_2_ta_ph = nullptr;
beq->bevt_3_ta_ph = nullptr;
beq->bevt_4_ta_ph = nullptr;
beq->bevt_5_ta_ph = nullptr;
beq->bevt_6_ta_ph = nullptr;
beq->bevt_7_ta_ph = nullptr;
beq->bevt_8_ta_ph = nullptr;
beq->bevt_9_ta_ph = nullptr;
beq->bevt_10_ta_ph = nullptr;
beq->bevt_11_ta_ph = nullptr;
beq->bevt_12_ta_ph = nullptr;
beq->bevt_13_ta_ph = nullptr;
beq->bevt_14_ta_ph = nullptr;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(19);
beq->bevt_3_ta_ph = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString(16, {0x69,0x6E,0x20,0x64,0x6F,0x53,0x74,0x61,0x74,0x65,0x4D,0x71,0x20,0x73,0x63,0x20}))));
beq->bevt_2_ta_ph = beq->bevt_3_ta_ph->bem_add_1(beq->beva_topic);
beq->bevt_4_ta_ph = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString(1, {0x20}))));
beq->bevt_1_ta_ph = beq->bevt_2_ta_ph->bem_add_1(beq->bevt_4_ta_ph);
beq->bevt_0_ta_ph = beq->bevt_1_ta_ph->bem_add_1(beq->beva_payload);
beq->bevt_0_ta_ph->bem_print_0();
beq->bevt_9_ta_ph = static_cast<BEC_2_9_4_ContainerList*>(((BEC_2_9_4_ContainerList*) (new BEC_2_9_4_ContainerList()))->bem_new_0());
beq->bevt_10_ta_ph = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString(2, {0x6E,0x61}))));
beq->bevt_8_ta_ph = static_cast<BEC_2_9_4_ContainerList*>(beq->bevt_9_ta_ph->bem_addValue_1(beq->bevt_10_ta_ph));
beq->bevt_11_ta_ph = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString(2, {0x6E,0x61}))));
beq->bevt_7_ta_ph = static_cast<BEC_2_9_4_ContainerList*>(beq->bevt_8_ta_ph->bem_addValue_1(beq->bevt_11_ta_ph));
beq->bevt_12_ta_ph = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString(2, {0x6E,0x61}))));
beq->bevt_6_ta_ph = static_cast<BEC_2_9_4_ContainerList*>(beq->bevt_7_ta_ph->bem_addValue_1(beq->bevt_12_ta_ph));
beq->bevt_5_ta_ph = static_cast<BEC_2_9_4_ContainerList*>(beq->bevt_6_ta_ph->bem_addValue_1(bevp_setsw));
beq->bevt_13_ta_ph = beq->beva_payload->bem_lower_0();
beq->bevl_ds = static_cast<BEC_2_9_4_ContainerList*>(beq->bevt_5_ta_ph->bem_addValue_1(beq->bevt_13_ta_ph));
beq->bevt_14_ta_ph = bem_doState_1(beq->bevl_ds);
return beq->bevt_14_ta_ph;
}
BEC_2_4_6_TextString* BEC_2_8_13_EmbeddedSwitchControl::bem_doState_1(BEC_2_9_4_ContainerList* bevk_cmdl) {
struct bes { BEC_2_9_4_ContainerList* beva_cmdl; BEC_2_4_6_TextString* bevl_scm; BEC_2_4_6_TextString* bevl_insw; BEC_2_4_6_TextString* bevt_0_ta_ph; BEC_2_4_3_MathInt* bevt_1_ta_ph; BEC_2_5_4_LogicBool* bevt_2_ta_ph; BEC_2_5_4_LogicBool* bevt_3_ta_ph; BEC_2_4_7_TextStrings* bevt_4_ta_ph; BEC_2_4_6_TextString* bevt_5_ta_ph; BEC_2_5_4_LogicBool* bevt_6_ta_ph; BEC_2_4_3_MathInt* bevt_7_ta_ph; BEC_2_5_4_LogicBool* bevt_8_ta_ph; BEC_2_5_4_LogicBool* bevt_9_ta_ph; BEC_2_4_3_MathInt* bevt_10_ta_ph; BEC_2_4_3_MathInt* bevt_11_ta_ph; BEC_2_4_3_MathInt* bevt_12_ta_ph; BEC_2_5_4_LogicBool* bevt_13_ta_ph; BEC_2_5_4_LogicBool* bevt_14_ta_ph; BEC_2_4_3_MathInt* bevt_15_ta_ph; BEC_2_4_3_MathInt* bevt_16_ta_ph; BEC_2_4_3_MathInt* bevt_17_ta_ph; BEC_2_4_3_MathInt* bevt_18_ta_ph; BEC_2_5_4_LogicBool* bevt_19_ta_ph; BEC_2_4_6_TextString* bevt_20_ta_ph; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->beva_cmdl = bevk_cmdl;
beq->bevl_scm = nullptr;
beq->bevl_insw = nullptr;
beq->bevt_0_ta_ph = nullptr;
beq->bevt_1_ta_ph = nullptr;
beq->bevt_2_ta_ph = nullptr;
beq->bevt_3_ta_ph = nullptr;
beq->bevt_4_ta_ph = nullptr;
beq->bevt_5_ta_ph = nullptr;
beq->bevt_6_ta_ph = nullptr;
beq->bevt_7_ta_ph = nullptr;
beq->bevt_8_ta_ph = nullptr;
beq->bevt_9_ta_ph = nullptr;
beq->bevt_10_ta_ph = nullptr;
beq->bevt_11_ta_ph = nullptr;
beq->bevt_12_ta_ph = nullptr;
beq->bevt_13_ta_ph = nullptr;
beq->bevt_14_ta_ph = nullptr;
beq->bevt_15_ta_ph = nullptr;
beq->bevt_16_ta_ph = nullptr;
beq->bevt_17_ta_ph = nullptr;
beq->bevt_18_ta_ph = nullptr;
beq->bevt_19_ta_ph = nullptr;
beq->bevt_20_ta_ph = nullptr;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(25);
beq->bevt_0_ta_ph = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString(10, {0x69,0x6E,0x20,0x64,0x6F,0x73,0x74,0x61,0x74,0x65}))));
beq->bevt_0_ta_ph->bem_print_0();
beq->bevt_1_ta_ph = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(3))));
beq->bevl_scm = static_cast<BEC_2_4_6_TextString*>(beq->beva_cmdl->bem_get_1(beq->bevt_1_ta_ph));
beq->bevt_2_ta_ph = beq->bevl_scm->bem_equals_1(bevp_getsw);
if (beq->bevt_2_ta_ph->bevi_bool) {
beq->bevt_4_ta_ph = static_cast<BEC_2_4_7_TextStrings*>(BEC_2_4_7_TextStrings::bece_BEC_2_4_7_TextStrings_bevs_inst);
beq->bevt_3_ta_ph = beq->bevt_4_ta_ph->bem_notEmpty_1(bevp_sw);
if (beq->bevt_3_ta_ph->bevi_bool) {
return bevp_sw;
} 
 else  {
beq->bevt_5_ta_ph = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString(9, {0x75,0x6E,0x64,0x65,0x66,0x69,0x6E,0x65,0x64}))));
return beq->bevt_5_ta_ph;
} 
} 
 else  {
beq->bevt_6_ta_ph = beq->bevl_scm->bem_equals_1(bevp_setsw);
if (beq->bevt_6_ta_ph->bevi_bool) {
beq->bevt_7_ta_ph = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(4))));
beq->bevl_insw = static_cast<BEC_2_4_6_TextString*>(beq->beva_cmdl->bem_get_1(beq->bevt_7_ta_ph));
beq->bevt_8_ta_ph = beq->bevl_insw->bem_equals_1(bevp_on);
if (beq->bevt_8_ta_ph->bevi_bool) {
bevp_on->bem_print_0();
bevp_app->bem_pinModeOutput_1(bevp_pini);
beq->bevt_10_ta_ph = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(0))));
if (bevp_diri->bevi_int == beq->bevt_10_ta_ph->bevi_int) {
beq->bevt_9_ta_ph = BECS_Runtime::boolTrue;
 } else { 
beq->bevt_9_ta_ph = BECS_Runtime::boolFalse;
}
if (beq->bevt_9_ta_ph->bevi_bool) {
beq->bevt_11_ta_ph = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(0))));
bevp_app->bem_analogWrite_2(bevp_pini, beq->bevt_11_ta_ph);
} 
 else  {
beq->bevt_12_ta_ph = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(255))));
bevp_app->bem_analogWrite_2(bevp_pini, beq->bevt_12_ta_ph);
} 
bevp_sw = beq->bevl_insw;
bevp_config->bem_put_2(bevp_scswi, bevp_on);
} 
 else  {
beq->bevt_13_ta_ph = beq->bevl_insw->bem_equals_1(bevp_off);
if (beq->bevt_13_ta_ph->bevi_bool) {
bevp_off->bem_print_0();
bevp_app->bem_pinModeOutput_1(bevp_pini);
beq->bevt_15_ta_ph = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(0))));
if (bevp_diri->bevi_int == beq->bevt_15_ta_ph->bevi_int) {
beq->bevt_14_ta_ph = BECS_Runtime::boolTrue;
 } else { 
beq->bevt_14_ta_ph = BECS_Runtime::boolFalse;
}
if (beq->bevt_14_ta_ph->bevi_bool) {
beq->bevt_16_ta_ph = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(255))));
bevp_app->bem_analogWrite_2(bevp_pini, beq->bevt_16_ta_ph);
} 
 else  {
beq->bevt_17_ta_ph = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(0))));
bevp_app->bem_analogWrite_2(bevp_pini, beq->bevt_17_ta_ph);
} 
bevp_sw = beq->bevl_insw;
bevp_config->bem_put_2(bevp_scswi, bevp_off);
} 
} 
beq->bevt_18_ta_ph = bevp_ash->bem_nowupGet_0();
bevp_lastEvent->bevi_int = beq->bevt_18_ta_ph->bevi_int;
bevp_ash->bem_lastEventsResSet_1(nullptr);
beq->bevt_19_ta_ph = static_cast<BEC_2_5_4_LogicBool*>(BECS_Runtime::boolTrue);
bevp_ash->bem_needsStateUpSet_1(beq->bevt_19_ta_ph);
} 
} 
beq->bevt_20_ta_ph = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString(2, {0x6F,0x6B}))));
return beq->bevt_20_ta_ph;
}
BEC_2_8_13_EmbeddedSwitchControl* BEC_2_8_13_EmbeddedSwitchControl::bem_clearStates_0() {
struct bes {  BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(1);
bevp_config->bem_put_2(bevp_scswi, bevp_off);
return this;
}
BEC_2_4_3_MathInt* BEC_2_8_13_EmbeddedSwitchControl::bem_conPosGet_0() {
struct bes {  BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(1);
return bevp_conPos;
}
BEC_2_8_13_EmbeddedSwitchControl* BEC_2_8_13_EmbeddedSwitchControl::bem_conPosSet_1(BEC_2_6_6_SystemObject* bevt_0_ta_SET) {
struct bes { BEC_2_6_6_SystemObject* bevt_0_ta_SET; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->bevt_0_ta_SET = bevt_0_ta_SET;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(2);
bevp_conPos = static_cast<BEC_2_4_3_MathInt*>(beq->bevt_0_ta_SET);
return this;
}
BEC_2_4_3_MathInt* BEC_2_8_13_EmbeddedSwitchControl::bem_lastEventGet_0() {
struct bes {  BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(1);
return bevp_lastEvent;
}
BEC_2_8_13_EmbeddedSwitchControl* BEC_2_8_13_EmbeddedSwitchControl::bem_lastEventSet_1(BEC_2_6_6_SystemObject* bevt_0_ta_SET) {
struct bes { BEC_2_6_6_SystemObject* bevt_0_ta_SET; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->bevt_0_ta_SET = bevt_0_ta_SET;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(2);
bevp_lastEvent = static_cast<BEC_2_4_3_MathInt*>(beq->bevt_0_ta_SET);
return this;
}
BEC_2_4_6_TextString* BEC_2_8_13_EmbeddedSwitchControl::bem_conNameGet_0() {
struct bes {  BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(1);
return bevp_conName;
}
BEC_2_8_13_EmbeddedSwitchControl* BEC_2_8_13_EmbeddedSwitchControl::bem_conNameSet_1(BEC_2_6_6_SystemObject* bevt_0_ta_SET) {
struct bes { BEC_2_6_6_SystemObject* bevt_0_ta_SET; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->bevt_0_ta_SET = bevt_0_ta_SET;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(2);
bevp_conName = static_cast<BEC_2_4_6_TextString*>(beq->bevt_0_ta_SET);
return this;
}
BEC_2_4_6_TextString* BEC_2_8_13_EmbeddedSwitchControl::bem_onGet_0() {
struct bes {  BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(1);
return bevp_on;
}
BEC_2_8_13_EmbeddedSwitchControl* BEC_2_8_13_EmbeddedSwitchControl::bem_onSet_1(BEC_2_6_6_SystemObject* bevt_0_ta_SET) {
struct bes { BEC_2_6_6_SystemObject* bevt_0_ta_SET; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->bevt_0_ta_SET = bevt_0_ta_SET;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(2);
bevp_on = static_cast<BEC_2_4_6_TextString*>(beq->bevt_0_ta_SET);
return this;
}
BEC_2_4_6_TextString* BEC_2_8_13_EmbeddedSwitchControl::bem_offGet_0() {
struct bes {  BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(1);
return bevp_off;
}
BEC_2_8_13_EmbeddedSwitchControl* BEC_2_8_13_EmbeddedSwitchControl::bem_offSet_1(BEC_2_6_6_SystemObject* bevt_0_ta_SET) {
struct bes { BEC_2_6_6_SystemObject* bevt_0_ta_SET; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->bevt_0_ta_SET = bevt_0_ta_SET;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(2);
bevp_off = static_cast<BEC_2_4_6_TextString*>(beq->bevt_0_ta_SET);
return this;
}
BEC_2_4_6_TextString* BEC_2_8_13_EmbeddedSwitchControl::bem_setswGet_0() {
struct bes {  BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(1);
return bevp_setsw;
}
BEC_2_8_13_EmbeddedSwitchControl* BEC_2_8_13_EmbeddedSwitchControl::bem_setswSet_1(BEC_2_6_6_SystemObject* bevt_0_ta_SET) {
struct bes { BEC_2_6_6_SystemObject* bevt_0_ta_SET; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->bevt_0_ta_SET = bevt_0_ta_SET;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(2);
bevp_setsw = static_cast<BEC_2_4_6_TextString*>(beq->bevt_0_ta_SET);
return this;
}
BEC_2_4_6_TextString* BEC_2_8_13_EmbeddedSwitchControl::bem_swGet_0() {
struct bes {  BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(1);
return bevp_sw;
}
BEC_2_8_13_EmbeddedSwitchControl* BEC_2_8_13_EmbeddedSwitchControl::bem_swSet_1(BEC_2_6_6_SystemObject* bevt_0_ta_SET) {
struct bes { BEC_2_6_6_SystemObject* bevt_0_ta_SET; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->bevt_0_ta_SET = bevt_0_ta_SET;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(2);
bevp_sw = static_cast<BEC_2_4_6_TextString*>(beq->bevt_0_ta_SET);
return this;
}
BEC_2_6_6_SystemObject* BEC_2_8_13_EmbeddedSwitchControl::bemd_0(int32_t callId) {
switch (callId) {
case -506180731: return bem_setswGet_0();
case 1530937685: return bem_conNameGet_0();
case 642415534: return bem_onGet_0();
case -1469083060: return bem_initControl_0();
case -1592447609: return bem_clearStates_0();
case 315366234: return bem_lastEventGet_0();
case -110385943: return bem_offGet_0();
case 355723905: return bem_conPosGet_0();
case -691724196: return bem_swGet_0();
}
return bevs_super::bemd_0(callId);
}
BEC_2_6_6_SystemObject* BEC_2_8_13_EmbeddedSwitchControl::bemd_1(int32_t callId, BEC_2_6_6_SystemObject* bevd_0) {
switch (callId) {
case 255961020: return bem_setswSet_1(bevd_0);
case -180844426: return bem_conNameSet_1(bevd_0);
case 991266055: return bem_lastEventSet_1(bevd_0);
case -1719026797: return bem_onSet_1(bevd_0);
case 807981456: return bem_swSet_1(bevd_0);
case 613339521: return bem_conPosSet_1(bevd_0);
case 472494009: return bem_doState_1(static_cast<BEC_2_9_4_ContainerList*>(bevd_0));
case 270911292: return bem_offSet_1(bevd_0);
}
return bevs_super::bemd_1(callId, bevd_0);
}
BEC_2_6_6_SystemObject* BEC_2_8_13_EmbeddedSwitchControl::bemd_2(int32_t callId, BEC_2_6_6_SystemObject* bevd_0, BEC_2_6_6_SystemObject* bevd_1) {
switch (callId) {
case 785325488: return bem_doStateMq_2(static_cast<BEC_2_4_6_TextString*>(bevd_0), static_cast<BEC_2_4_6_TextString*>(bevd_1));
}
return bevs_super::bemd_2(callId, bevd_0, bevd_1);
}
BEC_2_6_6_SystemObject* BEC_2_8_13_EmbeddedSwitchControl::bemd_4(int32_t callId, BEC_2_6_6_SystemObject* bevd_0, BEC_2_6_6_SystemObject* bevd_1, BEC_2_6_6_SystemObject* bevd_2, BEC_2_6_6_SystemObject* bevd_3) {
switch (callId) {
case -936892514: return bem_new_4(bevd_0, static_cast<BEC_2_4_3_MathInt*>(bevd_1), static_cast<BEC_2_4_6_TextString*>(bevd_2), static_cast<BEC_2_4_6_TextString*>(bevd_3));
}
return bevs_super::bemd_4(callId, bevd_0, bevd_1, bevd_2, bevd_3);
}
BEC_2_6_6_SystemObject* BEC_2_8_13_EmbeddedSwitchControl::bemc_create() {
return new BEC_2_8_13_EmbeddedSwitchControl();
}
void BEC_2_8_13_EmbeddedSwitchControl::bemc_setInitial(BEC_2_6_6_SystemObject* becc_inst) {
BEC_2_8_13_EmbeddedSwitchControl::bece_BEC_2_8_13_EmbeddedSwitchControl_bevs_inst = static_cast<BEC_2_8_13_EmbeddedSwitchControl*>(becc_inst);
}
BEC_2_6_6_SystemObject* BEC_2_8_13_EmbeddedSwitchControl::bemc_getInitial() {
return BEC_2_8_13_EmbeddedSwitchControl::bece_BEC_2_8_13_EmbeddedSwitchControl_bevs_inst;
}
void BEC_2_8_13_EmbeddedSwitchControl::bemg_doMark() {
bevg_gcMark = BECS_Runtime::bevg_currentGcMark;
if (bevp_ash != nullptr && bevp_ash->bevg_gcMark != BECS_Runtime::bevg_currentGcMark) {
bevp_ash->bemg_doMark();
}
if (bevp_pini != nullptr && bevp_pini->bevg_gcMark != BECS_Runtime::bevg_currentGcMark) {
bevp_pini->bemg_doMark();
}
if (bevp_diri != nullptr && bevp_diri->bevg_gcMark != BECS_Runtime::bevg_currentGcMark) {
bevp_diri->bemg_doMark();
}
if (bevp_config != nullptr && bevp_config->bevg_gcMark != BECS_Runtime::bevg_currentGcMark) {
bevp_config->bemg_doMark();
}
if (bevp_app != nullptr && bevp_app->bevg_gcMark != BECS_Runtime::bevg_currentGcMark) {
bevp_app->bemg_doMark();
}
if (bevp_conPos != nullptr && bevp_conPos->bevg_gcMark != BECS_Runtime::bevg_currentGcMark) {
bevp_conPos->bemg_doMark();
}
if (bevp_lastEvent != nullptr && bevp_lastEvent->bevg_gcMark != BECS_Runtime::bevg_currentGcMark) {
bevp_lastEvent->bemg_doMark();
}
if (bevp_conName != nullptr && bevp_conName->bevg_gcMark != BECS_Runtime::bevg_currentGcMark) {
bevp_conName->bemg_doMark();
}
if (bevp_scswi != nullptr && bevp_scswi->bevg_gcMark != BECS_Runtime::bevg_currentGcMark) {
bevp_scswi->bemg_doMark();
}
if (bevp_getsw != nullptr && bevp_getsw->bevg_gcMark != BECS_Runtime::bevg_currentGcMark) {
bevp_getsw->bemg_doMark();
}
if (bevp_on != nullptr && bevp_on->bevg_gcMark != BECS_Runtime::bevg_currentGcMark) {
bevp_on->bemg_doMark();
}
if (bevp_off != nullptr && bevp_off->bevg_gcMark != BECS_Runtime::bevg_currentGcMark) {
bevp_off->bemg_doMark();
}
if (bevp_setsw != nullptr && bevp_setsw->bevg_gcMark != BECS_Runtime::bevg_currentGcMark) {
bevp_setsw->bemg_doMark();
}
if (bevp_sw != nullptr && bevp_sw->bevg_gcMark != BECS_Runtime::bevg_currentGcMark) {
bevp_sw->bemg_doMark();
}
}
size_t BEC_2_8_13_EmbeddedSwitchControl::bemg_getSize() {
return sizeof(*this);
}
BETS_Object* BEC_2_8_13_EmbeddedSwitchControl::bemc_getType() {
return &BEC_2_8_13_EmbeddedSwitchControl::bece_BEC_2_8_13_EmbeddedSwitchControl_bevs_type;
}
BET_2_8_13_EmbeddedDimmerControl::BET_2_8_13_EmbeddedDimmerControl() {
std::vector<std::string> bevs_mtnames = {  };
bevs_fieldNames = {  };
}
BEC_2_6_6_SystemObject* BET_2_8_13_EmbeddedDimmerControl::bems_createInstance() {
return new BEC_2_8_13_EmbeddedDimmerControl();
}
void BET_2_8_13_EmbeddedDimmerControl::bemgt_doMark() {
BEC_2_6_6_SystemObject* bevsl_inst_ref = *bevs_inst_ref;
if (bevsl_inst_ref != nullptr && bevsl_inst_ref->bevg_gcMark != BECS_Runtime::bevg_currentGcMark) {
bevsl_inst_ref->bemg_doMark();
}
}
BEC_2_8_13_EmbeddedDimmerControl* BEC_2_8_13_EmbeddedDimmerControl::bece_BEC_2_8_13_EmbeddedDimmerControl_bevs_inst;

BET_2_8_13_EmbeddedDimmerControl BEC_2_8_13_EmbeddedDimmerControl::bece_BEC_2_8_13_EmbeddedDimmerControl_bevs_type;
BEC_2_6_6_SystemObject** BET_2_8_13_EmbeddedDimmerControl::bevs_inst_ref = (BEC_2_6_6_SystemObject**) &BEC_2_8_13_EmbeddedDimmerControl::bece_BEC_2_8_13_EmbeddedDimmerControl_bevs_inst;

BEC_2_8_13_EmbeddedDimmerControl* BEC_2_8_13_EmbeddedDimmerControl::bem_new_4(BEC_2_6_6_SystemObject* bevk__ash, BEC_2_4_3_MathInt* bevk__conPos, BEC_2_4_6_TextString* bevk__conName, BEC_2_4_6_TextString* bevk__conArgs) {
struct bes { BEC_2_6_6_SystemObject* beva__ash; BEC_2_4_3_MathInt* beva__conPos; BEC_2_4_6_TextString* beva__conName; BEC_2_4_6_TextString* beva__conArgs; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->beva__ash = bevk__ash;
beq->beva__conPos = bevk__conPos;
beq->beva__conName = bevk__conName;
beq->beva__conArgs = bevk__conArgs;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(5);
bevp_ash = static_cast<BEC_2_8_8_EmbeddedAppShell*>(beq->beva__ash);
bevp_config = bevp_ash->bem_configGet_0();
bevp_app = static_cast<BEC_2_8_3_EmbeddedApp*>(bevp_ash->bem_appGet_0());
bevp_conPos = beq->beva__conPos;
bevp_lastEvent = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt())));
bevp_conName = beq->beva__conName;
bevp_pini = bevp_app->bem_strToInt_1(beq->beva__conArgs);
return this;
}
BEC_2_8_13_EmbeddedDimmerControl* BEC_2_8_13_EmbeddedDimmerControl::bem_initControl_0() {
struct bes { BEC_2_4_6_TextString* bevl_inlvl; BEC_2_4_6_TextString* bevl_insw; BEC_2_4_6_TextString* bevt_0_ta_ph; BEC_2_4_6_TextString* bevt_1_ta_ph; BEC_2_4_6_TextString* bevt_2_ta_ph; BEC_2_4_6_TextString* bevt_3_ta_ph; BEC_2_5_4_LogicBool* bevt_4_ta_ph; BEC_2_4_7_TextStrings* bevt_5_ta_ph; BEC_2_5_4_LogicBool* bevt_6_ta_ph; BEC_2_4_7_TextStrings* bevt_7_ta_ph; BEC_2_9_4_ContainerList* bevt_8_ta_ph; BEC_2_9_4_ContainerList* bevt_9_ta_ph; BEC_2_9_4_ContainerList* bevt_10_ta_ph; BEC_2_9_4_ContainerList* bevt_11_ta_ph; BEC_2_9_4_ContainerList* bevt_12_ta_ph; BEC_2_9_4_ContainerList* bevt_13_ta_ph; BEC_2_4_6_TextString* bevt_14_ta_ph; BEC_2_4_6_TextString* bevt_15_ta_ph; BEC_2_4_6_TextString* bevt_16_ta_ph; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->bevl_inlvl = nullptr;
beq->bevl_insw = nullptr;
beq->bevt_0_ta_ph = nullptr;
beq->bevt_1_ta_ph = nullptr;
beq->bevt_2_ta_ph = nullptr;
beq->bevt_3_ta_ph = nullptr;
beq->bevt_4_ta_ph = nullptr;
beq->bevt_5_ta_ph = nullptr;
beq->bevt_6_ta_ph = nullptr;
beq->bevt_7_ta_ph = nullptr;
beq->bevt_8_ta_ph = nullptr;
beq->bevt_9_ta_ph = nullptr;
beq->bevt_10_ta_ph = nullptr;
beq->bevt_11_ta_ph = nullptr;
beq->bevt_12_ta_ph = nullptr;
beq->bevt_13_ta_ph = nullptr;
beq->bevt_14_ta_ph = nullptr;
beq->bevt_15_ta_ph = nullptr;
beq->bevt_16_ta_ph = nullptr;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(20);
bevp_setlvll = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString(6, {0x73,0x65,0x74,0x6C,0x76,0x6C}))));
bevp_setrlvll = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString(7, {0x73,0x65,0x74,0x72,0x6C,0x76,0x6C}))));
bevp_getlvl = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString(6, {0x67,0x65,0x74,0x6C,0x76,0x6C}))));
bevp_on = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString(2, {0x6F,0x6E}))));
bevp_off = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString(3, {0x6F,0x66,0x66}))));
bevp_setsw = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString(5, {0x73,0x65,0x74,0x73,0x77}))));
bevp_getsw = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString(5, {0x67,0x65,0x74,0x73,0x77}))));
beq->bevt_1_ta_ph = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString(7, {0x64,0x63,0x2E,0x6C,0x76,0x6C,0x2E}))));
beq->bevt_0_ta_ph = beq->bevt_1_ta_ph->bem_add_1(bevp_conPos);
bevp_dclvli = static_cast<BEC_2_4_3_MathInt*>(bevp_config->bem_getPos_1(beq->bevt_0_ta_ph));
beq->bevt_3_ta_ph = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString(6, {0x64,0x63,0x2E,0x73,0x77,0x2E}))));
beq->bevt_2_ta_ph = beq->bevt_3_ta_ph->bem_add_1(bevp_conPos);
bevp_dcswi = static_cast<BEC_2_4_3_MathInt*>(bevp_config->bem_getPos_1(beq->bevt_2_ta_ph));
beq->bevl_inlvl = bevp_config->bem_get_1(bevp_dclvli);
beq->bevt_5_ta_ph = static_cast<BEC_2_4_7_TextStrings*>(BEC_2_4_7_TextStrings::bece_BEC_2_4_7_TextStrings_bevs_inst);
beq->bevt_4_ta_ph = beq->bevt_5_ta_ph->bem_notEmpty_1(beq->bevl_inlvl);
if (beq->bevt_4_ta_ph->bevi_bool) {
bevp_lvl = beq->bevl_inlvl;
} 
beq->bevl_insw = bevp_config->bem_get_1(bevp_dcswi);
beq->bevt_7_ta_ph = static_cast<BEC_2_4_7_TextStrings*>(BEC_2_4_7_TextStrings::bece_BEC_2_4_7_TextStrings_bevs_inst);
beq->bevt_6_ta_ph = beq->bevt_7_ta_ph->bem_notEmpty_1(beq->bevl_insw);
if (beq->bevt_6_ta_ph->bevi_bool) {
bevp_sw = beq->bevl_insw;
beq->bevt_13_ta_ph = static_cast<BEC_2_9_4_ContainerList*>(((BEC_2_9_4_ContainerList*) (new BEC_2_9_4_ContainerList()))->bem_new_0());
beq->bevt_14_ta_ph = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString(7, {0x64,0x6F,0x73,0x74,0x61,0x74,0x65}))));
beq->bevt_12_ta_ph = static_cast<BEC_2_9_4_ContainerList*>(beq->bevt_13_ta_ph->bem_addValue_1(beq->bevt_14_ta_ph));
beq->bevt_15_ta_ph = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString(5, {0x6E,0x6F,0x74,0x70,0x77}))));
beq->bevt_11_ta_ph = static_cast<BEC_2_9_4_ContainerList*>(beq->bevt_12_ta_ph->bem_addValue_1(beq->bevt_15_ta_ph));
beq->bevt_16_ta_ph = bevp_conPos->bem_toString_0();
beq->bevt_10_ta_ph = static_cast<BEC_2_9_4_ContainerList*>(beq->bevt_11_ta_ph->bem_addValue_1(beq->bevt_16_ta_ph));
beq->bevt_9_ta_ph = static_cast<BEC_2_9_4_ContainerList*>(beq->bevt_10_ta_ph->bem_addValue_1(bevp_setsw));
beq->bevt_8_ta_ph = static_cast<BEC_2_9_4_ContainerList*>(beq->bevt_9_ta_ph->bem_addValue_1(bevp_sw));
bem_doState_1(beq->bevt_8_ta_ph);
} 
return this;
}
BEC_2_4_6_TextString* BEC_2_8_13_EmbeddedDimmerControl::bem_doStateMq_2(BEC_2_4_6_TextString* bevk_topic, BEC_2_4_6_TextString* bevk_payload) {
struct bes { BEC_2_4_6_TextString* beva_topic; BEC_2_4_6_TextString* beva_payload; BEC_2_4_3_MathInt* bevl_stok; BEC_2_9_4_ContainerList* bevl_ds; BEC_2_4_6_TextString* bevt_0_ta_ph; BEC_2_4_6_TextString* bevt_1_ta_ph; BEC_2_4_6_TextString* bevt_2_ta_ph; BEC_2_4_6_TextString* bevt_3_ta_ph; BEC_2_4_6_TextString* bevt_4_ta_ph; BEC_2_4_6_TextString* bevt_5_ta_ph; BEC_2_5_4_LogicBool* bevt_6_ta_ph; BEC_2_4_3_MathInt* bevt_7_ta_ph; BEC_2_4_6_TextString* bevt_8_ta_ph; BEC_2_5_4_LogicBool* bevt_9_ta_ph; BEC_2_4_3_MathInt* bevt_10_ta_ph; BEC_2_4_3_MathInt* bevt_11_ta_ph; BEC_2_4_3_MathInt* bevt_12_ta_ph; BEC_2_4_6_TextString* bevt_13_ta_ph; BEC_2_5_4_LogicBool* bevt_14_ta_ph; BEC_2_4_3_MathInt* bevt_15_ta_ph; BEC_2_4_6_TextString* bevt_16_ta_ph; BEC_2_5_4_LogicBool* bevt_17_ta_ph; BEC_2_4_3_MathInt* bevt_18_ta_ph; BEC_2_9_4_ContainerList* bevt_19_ta_ph; BEC_2_9_4_ContainerList* bevt_20_ta_ph; BEC_2_9_4_ContainerList* bevt_21_ta_ph; BEC_2_9_4_ContainerList* bevt_22_ta_ph; BEC_2_9_4_ContainerList* bevt_23_ta_ph; BEC_2_4_6_TextString* bevt_24_ta_ph; BEC_2_4_6_TextString* bevt_25_ta_ph; BEC_2_4_6_TextString* bevt_26_ta_ph; BEC_2_4_6_TextString* bevt_27_ta_ph; BEC_2_5_4_LogicBool* bevt_28_ta_ph; BEC_2_4_6_TextString* bevt_29_ta_ph; BEC_2_9_4_ContainerList* bevt_30_ta_ph; BEC_2_9_4_ContainerList* bevt_31_ta_ph; BEC_2_9_4_ContainerList* bevt_32_ta_ph; BEC_2_9_4_ContainerList* bevt_33_ta_ph; BEC_2_9_4_ContainerList* bevt_34_ta_ph; BEC_2_4_6_TextString* bevt_35_ta_ph; BEC_2_4_6_TextString* bevt_36_ta_ph; BEC_2_4_6_TextString* bevt_37_ta_ph; BEC_2_4_6_TextString* bevt_38_ta_ph; BEC_2_5_4_LogicBool* bevt_39_ta_ph; BEC_2_4_6_TextString* bevt_40_ta_ph; BEC_2_9_4_ContainerList* bevt_41_ta_ph; BEC_2_9_4_ContainerList* bevt_42_ta_ph; BEC_2_9_4_ContainerList* bevt_43_ta_ph; BEC_2_9_4_ContainerList* bevt_44_ta_ph; BEC_2_9_4_ContainerList* bevt_45_ta_ph; BEC_2_4_6_TextString* bevt_46_ta_ph; BEC_2_4_6_TextString* bevt_47_ta_ph; BEC_2_4_6_TextString* bevt_48_ta_ph; BEC_2_4_6_TextString* bevt_49_ta_ph; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->beva_topic = bevk_topic;
beq->beva_payload = bevk_payload;
beq->bevl_stok = nullptr;
beq->bevl_ds = nullptr;
beq->bevt_0_ta_ph = nullptr;
beq->bevt_1_ta_ph = nullptr;
beq->bevt_2_ta_ph = nullptr;
beq->bevt_3_ta_ph = nullptr;
beq->bevt_4_ta_ph = nullptr;
beq->bevt_5_ta_ph = nullptr;
beq->bevt_6_ta_ph = nullptr;
beq->bevt_7_ta_ph = nullptr;
beq->bevt_8_ta_ph = nullptr;
beq->bevt_9_ta_ph = nullptr;
beq->bevt_10_ta_ph = nullptr;
beq->bevt_11_ta_ph = nullptr;
beq->bevt_12_ta_ph = nullptr;
beq->bevt_13_ta_ph = nullptr;
beq->bevt_14_ta_ph = nullptr;
beq->bevt_15_ta_ph = nullptr;
beq->bevt_16_ta_ph = nullptr;
beq->bevt_17_ta_ph = nullptr;
beq->bevt_18_ta_ph = nullptr;
beq->bevt_19_ta_ph = nullptr;
beq->bevt_20_ta_ph = nullptr;
beq->bevt_21_ta_ph = nullptr;
beq->bevt_22_ta_ph = nullptr;
beq->bevt_23_ta_ph = nullptr;
beq->bevt_24_ta_ph = nullptr;
beq->bevt_25_ta_ph = nullptr;
beq->bevt_26_ta_ph = nullptr;
beq->bevt_27_ta_ph = nullptr;
beq->bevt_28_ta_ph = nullptr;
beq->bevt_29_ta_ph = nullptr;
beq->bevt_30_ta_ph = nullptr;
beq->bevt_31_ta_ph = nullptr;
beq->bevt_32_ta_ph = nullptr;
beq->bevt_33_ta_ph = nullptr;
beq->bevt_34_ta_ph = nullptr;
beq->bevt_35_ta_ph = nullptr;
beq->bevt_36_ta_ph = nullptr;
beq->bevt_37_ta_ph = nullptr;
beq->bevt_38_ta_ph = nullptr;
beq->bevt_39_ta_ph = nullptr;
beq->bevt_40_ta_ph = nullptr;
beq->bevt_41_ta_ph = nullptr;
beq->bevt_42_ta_ph = nullptr;
beq->bevt_43_ta_ph = nullptr;
beq->bevt_44_ta_ph = nullptr;
beq->bevt_45_ta_ph = nullptr;
beq->bevt_46_ta_ph = nullptr;
beq->bevt_47_ta_ph = nullptr;
beq->bevt_48_ta_ph = nullptr;
beq->bevt_49_ta_ph = nullptr;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(55);
beq->bevt_3_ta_ph = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString(16, {0x69,0x6E,0x20,0x64,0x6F,0x53,0x74,0x61,0x74,0x65,0x4D,0x71,0x20,0x64,0x63,0x20}))));
beq->bevt_2_ta_ph = beq->bevt_3_ta_ph->bem_add_1(beq->beva_topic);
beq->bevt_4_ta_ph = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString(1, {0x20}))));
beq->bevt_1_ta_ph = beq->bevt_2_ta_ph->bem_add_1(beq->bevt_4_ta_ph);
beq->bevt_0_ta_ph = beq->bevt_1_ta_ph->bem_add_1(beq->beva_payload);
beq->bevt_0_ta_ph->bem_print_0();
beq->bevt_5_ta_ph = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString(10, {0x62,0x72,0x69,0x67,0x68,0x74,0x6E,0x65,0x73,0x73}))));
beq->bevl_stok = beq->beva_payload->bem_find_1(beq->bevt_5_ta_ph);
if (beq->bevl_stok == nullptr) {
beq->bevt_6_ta_ph = BECS_Runtime::boolFalse;
 } else { 
beq->bevt_6_ta_ph = BECS_Runtime::boolTrue;
}
if (beq->bevt_6_ta_ph->bevi_bool) {
beq->bevt_7_ta_ph = beq->beva_payload->bem_sizeGet_0();
beq->beva_payload = beq->beva_payload->bem_substring_2(beq->bevl_stok, beq->bevt_7_ta_ph);
beq->bevt_8_ta_ph = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString(1, {0x3A}))));
beq->bevl_stok = beq->beva_payload->bem_find_1(beq->bevt_8_ta_ph);
if (beq->bevl_stok == nullptr) {
beq->bevt_9_ta_ph = BECS_Runtime::boolFalse;
 } else { 
beq->bevt_9_ta_ph = BECS_Runtime::boolTrue;
}
if (beq->bevt_9_ta_ph->bevi_bool) {
beq->bevt_11_ta_ph = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(1))));
beq->bevt_10_ta_ph = beq->bevl_stok->bem_add_1(beq->bevt_11_ta_ph);
beq->bevt_12_ta_ph = beq->beva_payload->bem_sizeGet_0();
beq->beva_payload = beq->beva_payload->bem_substring_2(beq->bevt_10_ta_ph, beq->bevt_12_ta_ph);
beq->bevt_13_ta_ph = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString(1, {0x7D}))));
beq->bevl_stok = beq->beva_payload->bem_find_1(beq->bevt_13_ta_ph);
if (beq->bevl_stok == nullptr) {
beq->bevt_14_ta_ph = BECS_Runtime::boolFalse;
 } else { 
beq->bevt_14_ta_ph = BECS_Runtime::boolTrue;
}
if (beq->bevt_14_ta_ph->bevi_bool) {
beq->bevt_15_ta_ph = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(0))));
beq->beva_payload = beq->beva_payload->bem_substring_2(beq->bevt_15_ta_ph, beq->bevl_stok);
} 
beq->bevt_16_ta_ph = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString(1, {0x2C}))));
beq->bevl_stok = beq->beva_payload->bem_find_1(beq->bevt_16_ta_ph);
if (beq->bevl_stok == nullptr) {
beq->bevt_17_ta_ph = BECS_Runtime::boolFalse;
 } else { 
beq->bevt_17_ta_ph = BECS_Runtime::boolTrue;
}
if (beq->bevt_17_ta_ph->bevi_bool) {
beq->bevt_18_ta_ph = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(0))));
beq->beva_payload = beq->beva_payload->bem_substring_2(beq->bevt_18_ta_ph, beq->bevl_stok);
} 
beq->bevt_23_ta_ph = static_cast<BEC_2_9_4_ContainerList*>(((BEC_2_9_4_ContainerList*) (new BEC_2_9_4_ContainerList()))->bem_new_0());
beq->bevt_24_ta_ph = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString(2, {0x6E,0x61}))));
beq->bevt_22_ta_ph = static_cast<BEC_2_9_4_ContainerList*>(beq->bevt_23_ta_ph->bem_addValue_1(beq->bevt_24_ta_ph));
beq->bevt_25_ta_ph = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString(2, {0x6E,0x61}))));
beq->bevt_21_ta_ph = static_cast<BEC_2_9_4_ContainerList*>(beq->bevt_22_ta_ph->bem_addValue_1(beq->bevt_25_ta_ph));
beq->bevt_26_ta_ph = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString(2, {0x6E,0x61}))));
beq->bevt_20_ta_ph = static_cast<BEC_2_9_4_ContainerList*>(beq->bevt_21_ta_ph->bem_addValue_1(beq->bevt_26_ta_ph));
beq->bevt_19_ta_ph = static_cast<BEC_2_9_4_ContainerList*>(beq->bevt_20_ta_ph->bem_addValue_1(bevp_setrlvll));
beq->bevl_ds = static_cast<BEC_2_9_4_ContainerList*>(beq->bevt_19_ta_ph->bem_addValue_1(beq->beva_payload));
beq->bevt_27_ta_ph = bem_doState_1(beq->bevl_ds);
return beq->bevt_27_ta_ph;
} 
} 
 else  {
beq->bevt_29_ta_ph = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString(2, {0x4F,0x4E}))));
beq->bevt_28_ta_ph = beq->beva_payload->bem_has_1(beq->bevt_29_ta_ph);
if (beq->bevt_28_ta_ph->bevi_bool) {
beq->bevt_34_ta_ph = static_cast<BEC_2_9_4_ContainerList*>(((BEC_2_9_4_ContainerList*) (new BEC_2_9_4_ContainerList()))->bem_new_0());
beq->bevt_35_ta_ph = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString(2, {0x6E,0x61}))));
beq->bevt_33_ta_ph = static_cast<BEC_2_9_4_ContainerList*>(beq->bevt_34_ta_ph->bem_addValue_1(beq->bevt_35_ta_ph));
beq->bevt_36_ta_ph = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString(2, {0x6E,0x61}))));
beq->bevt_32_ta_ph = static_cast<BEC_2_9_4_ContainerList*>(beq->bevt_33_ta_ph->bem_addValue_1(beq->bevt_36_ta_ph));
beq->bevt_37_ta_ph = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString(2, {0x6E,0x61}))));
beq->bevt_31_ta_ph = static_cast<BEC_2_9_4_ContainerList*>(beq->bevt_32_ta_ph->bem_addValue_1(beq->bevt_37_ta_ph));
beq->bevt_30_ta_ph = static_cast<BEC_2_9_4_ContainerList*>(beq->bevt_31_ta_ph->bem_addValue_1(bevp_setsw));
beq->bevl_ds = static_cast<BEC_2_9_4_ContainerList*>(beq->bevt_30_ta_ph->bem_addValue_1(bevp_on));
beq->bevt_38_ta_ph = bem_doState_1(beq->bevl_ds);
return beq->bevt_38_ta_ph;
} 
 else  {
beq->bevt_40_ta_ph = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString(3, {0x4F,0x46,0x46}))));
beq->bevt_39_ta_ph = beq->beva_payload->bem_has_1(beq->bevt_40_ta_ph);
if (beq->bevt_39_ta_ph->bevi_bool) {
beq->bevt_45_ta_ph = static_cast<BEC_2_9_4_ContainerList*>(((BEC_2_9_4_ContainerList*) (new BEC_2_9_4_ContainerList()))->bem_new_0());
beq->bevt_46_ta_ph = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString(2, {0x6E,0x61}))));
beq->bevt_44_ta_ph = static_cast<BEC_2_9_4_ContainerList*>(beq->bevt_45_ta_ph->bem_addValue_1(beq->bevt_46_ta_ph));
beq->bevt_47_ta_ph = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString(2, {0x6E,0x61}))));
beq->bevt_43_ta_ph = static_cast<BEC_2_9_4_ContainerList*>(beq->bevt_44_ta_ph->bem_addValue_1(beq->bevt_47_ta_ph));
beq->bevt_48_ta_ph = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString(2, {0x6E,0x61}))));
beq->bevt_42_ta_ph = static_cast<BEC_2_9_4_ContainerList*>(beq->bevt_43_ta_ph->bem_addValue_1(beq->bevt_48_ta_ph));
beq->bevt_41_ta_ph = static_cast<BEC_2_9_4_ContainerList*>(beq->bevt_42_ta_ph->bem_addValue_1(bevp_setsw));
beq->bevl_ds = static_cast<BEC_2_9_4_ContainerList*>(beq->bevt_41_ta_ph->bem_addValue_1(bevp_off));
beq->bevt_49_ta_ph = bem_doState_1(beq->bevl_ds);
return beq->bevt_49_ta_ph;
} 
} 
} 
return nullptr;
}
BEC_2_4_6_TextString* BEC_2_8_13_EmbeddedDimmerControl::bem_doState_1(BEC_2_9_4_ContainerList* bevk_cmdl) {
struct bes { BEC_2_9_4_ContainerList* beva_cmdl; BEC_2_4_6_TextString* bevl_scm; BEC_2_4_6_TextString* bevl_inlvl; BEC_2_4_3_MathInt* bevl_inlvli; BEC_2_4_6_TextString* bevl_insw; BEC_2_5_4_LogicBool* bevt_0_ta_anchor; BEC_2_5_4_LogicBool* bevt_1_ta_anchor; BEC_2_5_4_LogicBool* bevt_2_ta_anchor; BEC_2_4_6_TextString* bevt_3_ta_ph; BEC_2_4_3_MathInt* bevt_4_ta_ph; BEC_2_5_4_LogicBool* bevt_5_ta_ph; BEC_2_5_4_LogicBool* bevt_6_ta_ph; BEC_2_4_7_TextStrings* bevt_7_ta_ph; BEC_2_4_6_TextString* bevt_8_ta_ph; BEC_2_5_4_LogicBool* bevt_9_ta_ph; BEC_2_5_4_LogicBool* bevt_10_ta_ph; BEC_2_4_7_TextStrings* bevt_11_ta_ph; BEC_2_4_6_TextString* bevt_12_ta_ph; BEC_2_5_4_LogicBool* bevt_13_ta_ph; BEC_2_5_4_LogicBool* bevt_14_ta_ph; BEC_2_4_3_MathInt* bevt_15_ta_ph; BEC_2_5_4_LogicBool* bevt_16_ta_ph; BEC_2_5_4_LogicBool* bevt_17_ta_ph; BEC_2_4_3_MathInt* bevt_18_ta_ph; BEC_2_5_4_LogicBool* bevt_19_ta_ph; BEC_2_4_3_MathInt* bevt_20_ta_ph; BEC_2_5_4_LogicBool* bevt_21_ta_ph; BEC_2_4_3_MathInt* bevt_22_ta_ph; BEC_2_5_4_LogicBool* bevt_23_ta_ph; BEC_2_4_3_MathInt* bevt_24_ta_ph; BEC_2_4_3_MathInt* bevt_25_ta_ph; BEC_2_5_4_LogicBool* bevt_26_ta_ph; BEC_2_4_3_MathInt* bevt_27_ta_ph; BEC_2_4_3_MathInt* bevt_28_ta_ph; BEC_2_5_4_LogicBool* bevt_29_ta_ph; BEC_2_5_4_LogicBool* bevt_30_ta_ph; BEC_2_4_3_MathInt* bevt_31_ta_ph; BEC_2_5_4_LogicBool* bevt_32_ta_ph; BEC_2_5_4_LogicBool* bevt_33_ta_ph; BEC_2_4_7_TextStrings* bevt_34_ta_ph; BEC_2_5_4_LogicBool* bevt_35_ta_ph; BEC_2_4_3_MathInt* bevt_36_ta_ph; BEC_2_4_3_MathInt* bevt_37_ta_ph; BEC_2_5_4_LogicBool* bevt_38_ta_ph; BEC_2_4_6_TextString* bevt_39_ta_ph; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->beva_cmdl = bevk_cmdl;
beq->bevl_scm = nullptr;
beq->bevl_inlvl = nullptr;
beq->bevl_inlvli = nullptr;
beq->bevl_insw = nullptr;
beq->bevt_0_ta_anchor = nullptr;
beq->bevt_1_ta_anchor = nullptr;
beq->bevt_2_ta_anchor = nullptr;
beq->bevt_3_ta_ph = nullptr;
beq->bevt_4_ta_ph = nullptr;
beq->bevt_5_ta_ph = nullptr;
beq->bevt_6_ta_ph = nullptr;
beq->bevt_7_ta_ph = nullptr;
beq->bevt_8_ta_ph = nullptr;
beq->bevt_9_ta_ph = nullptr;
beq->bevt_10_ta_ph = nullptr;
beq->bevt_11_ta_ph = nullptr;
beq->bevt_12_ta_ph = nullptr;
beq->bevt_13_ta_ph = nullptr;
beq->bevt_14_ta_ph = nullptr;
beq->bevt_15_ta_ph = nullptr;
beq->bevt_16_ta_ph = nullptr;
beq->bevt_17_ta_ph = nullptr;
beq->bevt_18_ta_ph = nullptr;
beq->bevt_19_ta_ph = nullptr;
beq->bevt_20_ta_ph = nullptr;
beq->bevt_21_ta_ph = nullptr;
beq->bevt_22_ta_ph = nullptr;
beq->bevt_23_ta_ph = nullptr;
beq->bevt_24_ta_ph = nullptr;
beq->bevt_25_ta_ph = nullptr;
beq->bevt_26_ta_ph = nullptr;
beq->bevt_27_ta_ph = nullptr;
beq->bevt_28_ta_ph = nullptr;
beq->bevt_29_ta_ph = nullptr;
beq->bevt_30_ta_ph = nullptr;
beq->bevt_31_ta_ph = nullptr;
beq->bevt_32_ta_ph = nullptr;
beq->bevt_33_ta_ph = nullptr;
beq->bevt_34_ta_ph = nullptr;
beq->bevt_35_ta_ph = nullptr;
beq->bevt_36_ta_ph = nullptr;
beq->bevt_37_ta_ph = nullptr;
beq->bevt_38_ta_ph = nullptr;
beq->bevt_39_ta_ph = nullptr;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(46);
beq->bevt_3_ta_ph = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString(10, {0x69,0x6E,0x20,0x64,0x6F,0x73,0x74,0x61,0x74,0x65}))));
beq->bevt_3_ta_ph->bem_print_0();
beq->bevt_4_ta_ph = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(3))));
beq->bevl_scm = static_cast<BEC_2_4_6_TextString*>(beq->beva_cmdl->bem_get_1(beq->bevt_4_ta_ph));
beq->bevt_5_ta_ph = beq->bevl_scm->bem_equals_1(bevp_getsw);
if (beq->bevt_5_ta_ph->bevi_bool) {
beq->bevt_7_ta_ph = static_cast<BEC_2_4_7_TextStrings*>(BEC_2_4_7_TextStrings::bece_BEC_2_4_7_TextStrings_bevs_inst);
beq->bevt_6_ta_ph = beq->bevt_7_ta_ph->bem_notEmpty_1(bevp_sw);
if (beq->bevt_6_ta_ph->bevi_bool) {
return bevp_sw;
} 
 else  {
beq->bevt_8_ta_ph = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString(9, {0x75,0x6E,0x64,0x65,0x66,0x69,0x6E,0x65,0x64}))));
return beq->bevt_8_ta_ph;
} 
} 
 else  {
beq->bevt_9_ta_ph = beq->bevl_scm->bem_equals_1(bevp_getlvl);
if (beq->bevt_9_ta_ph->bevi_bool) {
beq->bevt_11_ta_ph = static_cast<BEC_2_4_7_TextStrings*>(BEC_2_4_7_TextStrings::bece_BEC_2_4_7_TextStrings_bevs_inst);
beq->bevt_10_ta_ph = beq->bevt_11_ta_ph->bem_notEmpty_1(bevp_lvl);
if (beq->bevt_10_ta_ph->bevi_bool) {
return bevp_lvl;
} 
 else  {
beq->bevt_12_ta_ph = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString(9, {0x75,0x6E,0x64,0x65,0x66,0x69,0x6E,0x65,0x64}))));
return beq->bevt_12_ta_ph;
} 
} 
 else  {
beq->bevt_13_ta_ph = beq->bevl_scm->bem_equals_1(bevp_setlvll);
if (beq->bevt_13_ta_ph->bevi_bool) {
beq->bevt_0_ta_anchor = BECS_Runtime::boolTrue;
} 
 else  {
beq->bevt_14_ta_ph = beq->bevl_scm->bem_equals_1(bevp_setrlvll);
if (beq->bevt_14_ta_ph->bevi_bool) {
beq->bevt_0_ta_anchor = BECS_Runtime::boolTrue;
} 
 else  {
beq->bevt_0_ta_anchor = BECS_Runtime::boolFalse;
} 
} 
if (beq->bevt_0_ta_anchor->bevi_bool) {
beq->bevt_15_ta_ph = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(4))));
beq->bevl_inlvl = static_cast<BEC_2_4_6_TextString*>(beq->beva_cmdl->bem_get_1(beq->bevt_15_ta_ph));
beq->bevl_inlvli = bevp_app->bem_strToInt_1(beq->bevl_inlvl);
beq->bevt_16_ta_ph = beq->bevl_scm->bem_equals_1(bevp_setlvll);
if (beq->bevt_16_ta_ph->bevi_bool) {
beq->bevt_18_ta_ph = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(0))));
if (beq->bevl_inlvli->bevi_int < beq->bevt_18_ta_ph->bevi_int) {
beq->bevt_17_ta_ph = BECS_Runtime::boolTrue;
 } else { 
beq->bevt_17_ta_ph = BECS_Runtime::boolFalse;
}
if (beq->bevt_17_ta_ph->bevi_bool) {
beq->bevt_1_ta_anchor = BECS_Runtime::boolTrue;
} 
 else  {
beq->bevt_20_ta_ph = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(255))));
if (beq->bevl_inlvli->bevi_int > beq->bevt_20_ta_ph->bevi_int) {
beq->bevt_19_ta_ph = BECS_Runtime::boolTrue;
 } else { 
beq->bevt_19_ta_ph = BECS_Runtime::boolFalse;
}
if (beq->bevt_19_ta_ph->bevi_bool) {
beq->bevt_1_ta_anchor = BECS_Runtime::boolTrue;
} 
 else  {
beq->bevt_1_ta_anchor = BECS_Runtime::boolFalse;
} 
} 
if (beq->bevt_1_ta_anchor->bevi_bool) {
beq->bevl_inlvli = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(255))));
} 
} 
 else  {
beq->bevt_22_ta_ph = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(0))));
if (beq->bevl_inlvli->bevi_int < beq->bevt_22_ta_ph->bevi_int) {
beq->bevt_21_ta_ph = BECS_Runtime::boolTrue;
 } else { 
beq->bevt_21_ta_ph = BECS_Runtime::boolFalse;
}
if (beq->bevt_21_ta_ph->bevi_bool) {
beq->bevt_2_ta_anchor = BECS_Runtime::boolTrue;
} 
 else  {
beq->bevt_24_ta_ph = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(255))));
if (beq->bevl_inlvli->bevi_int > beq->bevt_24_ta_ph->bevi_int) {
beq->bevt_23_ta_ph = BECS_Runtime::boolTrue;
 } else { 
beq->bevt_23_ta_ph = BECS_Runtime::boolFalse;
}
if (beq->bevt_23_ta_ph->bevi_bool) {
beq->bevt_2_ta_anchor = BECS_Runtime::boolTrue;
} 
 else  {
beq->bevt_2_ta_anchor = BECS_Runtime::boolFalse;
} 
} 
if (beq->bevt_2_ta_anchor->bevi_bool) {
beq->bevl_inlvli = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(255))));
} 
 else  {
beq->bevt_25_ta_ph = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(255))));
beq->bevl_inlvli = beq->bevt_25_ta_ph->bem_subtract_1(beq->bevl_inlvli);
} 
} 
beq->bevt_27_ta_ph = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(255))));
if (beq->bevl_inlvli->bevi_int == beq->bevt_27_ta_ph->bevi_int) {
beq->bevt_26_ta_ph = BECS_Runtime::boolTrue;
 } else { 
beq->bevt_26_ta_ph = BECS_Runtime::boolFalse;
}
if (beq->bevt_26_ta_ph->bevi_bool) {
beq->bevl_inlvli = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(254))));
} 
beq->bevl_inlvl = bevp_app->bem_intToStr_1(beq->bevl_inlvli);
bevp_lvl = beq->bevl_inlvl;
beq->bevl_inlvl->bem_print_0();
bevp_sw = bevp_on;
bevp_config->bem_put_2(bevp_dcswi, bevp_on);
bevp_config->bem_put_2(bevp_dclvli, beq->bevl_inlvl);
bevp_app->bem_pinModeOutput_1(bevp_pini);
bevp_app->bem_analogWrite_2(bevp_pini, beq->bevl_inlvli);
beq->bevt_28_ta_ph = bevp_ash->bem_nowupGet_0();
bevp_lastEvent->bevi_int = beq->bevt_28_ta_ph->bevi_int;
bevp_ash->bem_lastEventsResSet_1(nullptr);
beq->bevt_29_ta_ph = static_cast<BEC_2_5_4_LogicBool*>(BECS_Runtime::boolTrue);
bevp_ash->bem_needsStateUpSet_1(beq->bevt_29_ta_ph);
} 
 else  {
beq->bevt_30_ta_ph = beq->bevl_scm->bem_equals_1(bevp_setsw);
if (beq->bevt_30_ta_ph->bevi_bool) {
beq->bevt_31_ta_ph = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(4))));
beq->bevl_insw = static_cast<BEC_2_4_6_TextString*>(beq->beva_cmdl->bem_get_1(beq->bevt_31_ta_ph));
beq->bevt_32_ta_ph = beq->bevl_insw->bem_equals_1(bevp_on);
if (beq->bevt_32_ta_ph->bevi_bool) {
beq->bevt_34_ta_ph = static_cast<BEC_2_4_7_TextStrings*>(BEC_2_4_7_TextStrings::bece_BEC_2_4_7_TextStrings_bevs_inst);
beq->bevt_33_ta_ph = beq->bevt_34_ta_ph->bem_notEmpty_1(bevp_lvl);
if (beq->bevt_33_ta_ph->bevi_bool) {
beq->bevl_inlvli = bevp_app->bem_strToInt_1(bevp_lvl);
} 
 else  {
beq->bevl_inlvli = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(0))));
} 
bevp_on->bem_print_0();
bevp_app->bem_pinModeOutput_1(bevp_pini);
bevp_app->bem_analogWrite_2(bevp_pini, beq->bevl_inlvli);
bevp_sw = beq->bevl_insw;
bevp_config->bem_put_2(bevp_dcswi, bevp_on);
} 
 else  {
beq->bevt_35_ta_ph = beq->bevl_insw->bem_equals_1(bevp_off);
if (beq->bevt_35_ta_ph->bevi_bool) {
bevp_off->bem_print_0();
bevp_app->bem_pinModeOutput_1(bevp_pini);
beq->bevt_36_ta_ph = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(255))));
bevp_app->bem_analogWrite_2(bevp_pini, beq->bevt_36_ta_ph);
bevp_sw = beq->bevl_insw;
bevp_config->bem_put_2(bevp_dcswi, bevp_off);
} 
} 
beq->bevt_37_ta_ph = bevp_ash->bem_nowupGet_0();
bevp_lastEvent->bevi_int = beq->bevt_37_ta_ph->bevi_int;
bevp_ash->bem_lastEventsResSet_1(nullptr);
beq->bevt_38_ta_ph = static_cast<BEC_2_5_4_LogicBool*>(BECS_Runtime::boolTrue);
bevp_ash->bem_needsStateUpSet_1(beq->bevt_38_ta_ph);
} 
} 
} 
} 
beq->bevt_39_ta_ph = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString(2, {0x6F,0x6B}))));
return beq->bevt_39_ta_ph;
}
BEC_2_8_13_EmbeddedDimmerControl* BEC_2_8_13_EmbeddedDimmerControl::bem_clearStates_0() {
struct bes { BEC_2_4_6_TextString* bevt_0_ta_ph; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->bevt_0_ta_ph = nullptr;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(2);
bevp_config->bem_put_2(bevp_dcswi, bevp_off);
beq->bevt_0_ta_ph = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString(1, {0x30}))));
bevp_config->bem_put_2(bevp_dclvli, beq->bevt_0_ta_ph);
return this;
}
BEC_2_4_3_MathInt* BEC_2_8_13_EmbeddedDimmerControl::bem_conPosGet_0() {
struct bes {  BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(1);
return bevp_conPos;
}
BEC_2_8_13_EmbeddedDimmerControl* BEC_2_8_13_EmbeddedDimmerControl::bem_conPosSet_1(BEC_2_6_6_SystemObject* bevt_0_ta_SET) {
struct bes { BEC_2_6_6_SystemObject* bevt_0_ta_SET; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->bevt_0_ta_SET = bevt_0_ta_SET;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(2);
bevp_conPos = static_cast<BEC_2_4_3_MathInt*>(beq->bevt_0_ta_SET);
return this;
}
BEC_2_4_3_MathInt* BEC_2_8_13_EmbeddedDimmerControl::bem_lastEventGet_0() {
struct bes {  BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(1);
return bevp_lastEvent;
}
BEC_2_8_13_EmbeddedDimmerControl* BEC_2_8_13_EmbeddedDimmerControl::bem_lastEventSet_1(BEC_2_6_6_SystemObject* bevt_0_ta_SET) {
struct bes { BEC_2_6_6_SystemObject* bevt_0_ta_SET; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->bevt_0_ta_SET = bevt_0_ta_SET;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(2);
bevp_lastEvent = static_cast<BEC_2_4_3_MathInt*>(beq->bevt_0_ta_SET);
return this;
}
BEC_2_4_6_TextString* BEC_2_8_13_EmbeddedDimmerControl::bem_conNameGet_0() {
struct bes {  BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(1);
return bevp_conName;
}
BEC_2_8_13_EmbeddedDimmerControl* BEC_2_8_13_EmbeddedDimmerControl::bem_conNameSet_1(BEC_2_6_6_SystemObject* bevt_0_ta_SET) {
struct bes { BEC_2_6_6_SystemObject* bevt_0_ta_SET; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->bevt_0_ta_SET = bevt_0_ta_SET;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(2);
bevp_conName = static_cast<BEC_2_4_6_TextString*>(beq->bevt_0_ta_SET);
return this;
}
BEC_2_4_6_TextString* BEC_2_8_13_EmbeddedDimmerControl::bem_lvlGet_0() {
struct bes {  BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(1);
return bevp_lvl;
}
BEC_2_8_13_EmbeddedDimmerControl* BEC_2_8_13_EmbeddedDimmerControl::bem_lvlSet_1(BEC_2_6_6_SystemObject* bevt_0_ta_SET) {
struct bes { BEC_2_6_6_SystemObject* bevt_0_ta_SET; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->bevt_0_ta_SET = bevt_0_ta_SET;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(2);
bevp_lvl = static_cast<BEC_2_4_6_TextString*>(beq->bevt_0_ta_SET);
return this;
}
BEC_2_4_6_TextString* BEC_2_8_13_EmbeddedDimmerControl::bem_swGet_0() {
struct bes {  BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(1);
return bevp_sw;
}
BEC_2_8_13_EmbeddedDimmerControl* BEC_2_8_13_EmbeddedDimmerControl::bem_swSet_1(BEC_2_6_6_SystemObject* bevt_0_ta_SET) {
struct bes { BEC_2_6_6_SystemObject* bevt_0_ta_SET; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->bevt_0_ta_SET = bevt_0_ta_SET;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(2);
bevp_sw = static_cast<BEC_2_4_6_TextString*>(beq->bevt_0_ta_SET);
return this;
}
BEC_2_6_6_SystemObject* BEC_2_8_13_EmbeddedDimmerControl::bemd_0(int32_t callId) {
switch (callId) {
case 1530937685: return bem_conNameGet_0();
case -691724196: return bem_swGet_0();
case 315366234: return bem_lastEventGet_0();
case -1469083060: return bem_initControl_0();
case -1592447609: return bem_clearStates_0();
case 355723905: return bem_conPosGet_0();
case -271568658: return bem_lvlGet_0();
}
return bevs_super::bemd_0(callId);
}
BEC_2_6_6_SystemObject* BEC_2_8_13_EmbeddedDimmerControl::bemd_1(int32_t callId, BEC_2_6_6_SystemObject* bevd_0) {
switch (callId) {
case 613339521: return bem_conPosSet_1(bevd_0);
case -180844426: return bem_conNameSet_1(bevd_0);
case 807981456: return bem_swSet_1(bevd_0);
case 1634954340: return bem_lvlSet_1(bevd_0);
case 472494009: return bem_doState_1(static_cast<BEC_2_9_4_ContainerList*>(bevd_0));
case 991266055: return bem_lastEventSet_1(bevd_0);
}
return bevs_super::bemd_1(callId, bevd_0);
}
BEC_2_6_6_SystemObject* BEC_2_8_13_EmbeddedDimmerControl::bemd_2(int32_t callId, BEC_2_6_6_SystemObject* bevd_0, BEC_2_6_6_SystemObject* bevd_1) {
switch (callId) {
case 785325488: return bem_doStateMq_2(static_cast<BEC_2_4_6_TextString*>(bevd_0), static_cast<BEC_2_4_6_TextString*>(bevd_1));
}
return bevs_super::bemd_2(callId, bevd_0, bevd_1);
}
BEC_2_6_6_SystemObject* BEC_2_8_13_EmbeddedDimmerControl::bemd_4(int32_t callId, BEC_2_6_6_SystemObject* bevd_0, BEC_2_6_6_SystemObject* bevd_1, BEC_2_6_6_SystemObject* bevd_2, BEC_2_6_6_SystemObject* bevd_3) {
switch (callId) {
case -936892514: return bem_new_4(bevd_0, static_cast<BEC_2_4_3_MathInt*>(bevd_1), static_cast<BEC_2_4_6_TextString*>(bevd_2), static_cast<BEC_2_4_6_TextString*>(bevd_3));
}
return bevs_super::bemd_4(callId, bevd_0, bevd_1, bevd_2, bevd_3);
}
BEC_2_6_6_SystemObject* BEC_2_8_13_EmbeddedDimmerControl::bemc_create() {
return new BEC_2_8_13_EmbeddedDimmerControl();
}
void BEC_2_8_13_EmbeddedDimmerControl::bemc_setInitial(BEC_2_6_6_SystemObject* becc_inst) {
BEC_2_8_13_EmbeddedDimmerControl::bece_BEC_2_8_13_EmbeddedDimmerControl_bevs_inst = static_cast<BEC_2_8_13_EmbeddedDimmerControl*>(becc_inst);
}
BEC_2_6_6_SystemObject* BEC_2_8_13_EmbeddedDimmerControl::bemc_getInitial() {
return BEC_2_8_13_EmbeddedDimmerControl::bece_BEC_2_8_13_EmbeddedDimmerControl_bevs_inst;
}
void BEC_2_8_13_EmbeddedDimmerControl::bemg_doMark() {
bevg_gcMark = BECS_Runtime::bevg_currentGcMark;
if (bevp_ash != nullptr && bevp_ash->bevg_gcMark != BECS_Runtime::bevg_currentGcMark) {
bevp_ash->bemg_doMark();
}
if (bevp_pini != nullptr && bevp_pini->bevg_gcMark != BECS_Runtime::bevg_currentGcMark) {
bevp_pini->bemg_doMark();
}
if (bevp_config != nullptr && bevp_config->bevg_gcMark != BECS_Runtime::bevg_currentGcMark) {
bevp_config->bemg_doMark();
}
if (bevp_app != nullptr && bevp_app->bevg_gcMark != BECS_Runtime::bevg_currentGcMark) {
bevp_app->bemg_doMark();
}
if (bevp_conPos != nullptr && bevp_conPos->bevg_gcMark != BECS_Runtime::bevg_currentGcMark) {
bevp_conPos->bemg_doMark();
}
if (bevp_lastEvent != nullptr && bevp_lastEvent->bevg_gcMark != BECS_Runtime::bevg_currentGcMark) {
bevp_lastEvent->bemg_doMark();
}
if (bevp_conName != nullptr && bevp_conName->bevg_gcMark != BECS_Runtime::bevg_currentGcMark) {
bevp_conName->bemg_doMark();
}
if (bevp_setlvll != nullptr && bevp_setlvll->bevg_gcMark != BECS_Runtime::bevg_currentGcMark) {
bevp_setlvll->bemg_doMark();
}
if (bevp_setrlvll != nullptr && bevp_setrlvll->bevg_gcMark != BECS_Runtime::bevg_currentGcMark) {
bevp_setrlvll->bemg_doMark();
}
if (bevp_getlvl != nullptr && bevp_getlvl->bevg_gcMark != BECS_Runtime::bevg_currentGcMark) {
bevp_getlvl->bemg_doMark();
}
if (bevp_on != nullptr && bevp_on->bevg_gcMark != BECS_Runtime::bevg_currentGcMark) {
bevp_on->bemg_doMark();
}
if (bevp_off != nullptr && bevp_off->bevg_gcMark != BECS_Runtime::bevg_currentGcMark) {
bevp_off->bemg_doMark();
}
if (bevp_setsw != nullptr && bevp_setsw->bevg_gcMark != BECS_Runtime::bevg_currentGcMark) {
bevp_setsw->bemg_doMark();
}
if (bevp_getsw != nullptr && bevp_getsw->bevg_gcMark != BECS_Runtime::bevg_currentGcMark) {
bevp_getsw->bemg_doMark();
}
if (bevp_dclvli != nullptr && bevp_dclvli->bevg_gcMark != BECS_Runtime::bevg_currentGcMark) {
bevp_dclvli->bemg_doMark();
}
if (bevp_dcswi != nullptr && bevp_dcswi->bevg_gcMark != BECS_Runtime::bevg_currentGcMark) {
bevp_dcswi->bemg_doMark();
}
if (bevp_lvl != nullptr && bevp_lvl->bevg_gcMark != BECS_Runtime::bevg_currentGcMark) {
bevp_lvl->bemg_doMark();
}
if (bevp_sw != nullptr && bevp_sw->bevg_gcMark != BECS_Runtime::bevg_currentGcMark) {
bevp_sw->bemg_doMark();
}
}
size_t BEC_2_8_13_EmbeddedDimmerControl::bemg_getSize() {
return sizeof(*this);
}
BETS_Object* BEC_2_8_13_EmbeddedDimmerControl::bemc_getType() {
return &BEC_2_8_13_EmbeddedDimmerControl::bece_BEC_2_8_13_EmbeddedDimmerControl_bevs_type;
}
BET_2_4_3_MathInt::BET_2_4_3_MathInt() {
std::vector<std::string> bevs_mtnames = {  };
bevs_fieldNames = {  };
}
BEC_2_6_6_SystemObject* BET_2_4_3_MathInt::bems_createInstance() {
return new BEC_2_4_3_MathInt();
}
void BET_2_4_3_MathInt::bemgt_doMark() {
BEC_2_6_6_SystemObject* bevsl_inst_ref = *bevs_inst_ref;
if (bevsl_inst_ref != nullptr && bevsl_inst_ref->bevg_gcMark != BECS_Runtime::bevg_currentGcMark) {
bevsl_inst_ref->bemg_doMark();
}
}
BEC_2_4_3_MathInt* BEC_2_4_3_MathInt::bece_BEC_2_4_3_MathInt_bevs_inst;

BET_2_4_3_MathInt BEC_2_4_3_MathInt::bece_BEC_2_4_3_MathInt_bevs_type;
BEC_2_6_6_SystemObject** BET_2_4_3_MathInt::bevs_inst_ref = (BEC_2_6_6_SystemObject**) &BEC_2_4_3_MathInt::bece_BEC_2_4_3_MathInt_bevs_inst;

BEC_2_4_3_MathInt* BEC_2_4_3_MathInt::bem_vintGet_0() {
struct bes {  BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(1);
return this;
}
BEC_2_4_3_MathInt* BEC_2_4_3_MathInt::bem_vintSet_0() {
struct bes {  BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(1);
return this;
}
BEC_2_6_6_SystemObject* BEC_2_4_3_MathInt::bem_new_0() {
struct bes {  BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(1);

      bevi_int = 0;
      return this;
}
BEC_2_6_6_SystemObject* BEC_2_4_3_MathInt::bem_create_0() {
struct bes { BEC_2_4_3_MathInt* bevt_0_ta_ph; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->bevt_0_ta_ph = nullptr;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(2);
beq->bevt_0_ta_ph = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt())));
return static_cast<BEC_2_6_6_SystemObject*>(beq->bevt_0_ta_ph);
}
BEC_2_4_3_MathInt* BEC_2_4_3_MathInt::bem_new_1(BEC_2_6_6_SystemObject* bevk_str) {
struct bes { BEC_2_6_6_SystemObject* beva_str; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->beva_str = bevk_str;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(2);
bem_setStringValueDec_1(static_cast<BEC_2_4_6_TextString*>(beq->beva_str) );
return this;
}
BEC_2_4_3_MathInt* BEC_2_4_3_MathInt::bem_hexNew_1(BEC_2_4_6_TextString* bevk_str) {
struct bes { BEC_2_4_6_TextString* beva_str; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->beva_str = bevk_str;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(2);
bem_setStringValueHex_1(beq->beva_str);
return this;
}
BEC_2_4_3_MathInt* BEC_2_4_3_MathInt::bem_setStringValueDec_1(BEC_2_4_6_TextString* bevk_str) {
struct bes { BEC_2_4_6_TextString* beva_str; BEC_2_4_3_MathInt* bevt_0_ta_ph; BEC_2_4_3_MathInt* bevt_1_ta_ph; BEC_2_4_3_MathInt* bevt_2_ta_ph; BEC_2_4_3_MathInt* bevt_3_ta_ph; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->beva_str = bevk_str;
beq->bevt_0_ta_ph = nullptr;
beq->bevt_1_ta_ph = nullptr;
beq->bevt_2_ta_ph = nullptr;
beq->bevt_3_ta_ph = nullptr;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(6);
beq->bevt_0_ta_ph = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(10))));
beq->bevt_1_ta_ph = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(58))));
beq->bevt_2_ta_ph = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(65))));
beq->bevt_3_ta_ph = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(97))));
bem_setStringValue_5(beq->beva_str, beq->bevt_0_ta_ph, beq->bevt_1_ta_ph, beq->bevt_2_ta_ph, beq->bevt_3_ta_ph);
return this;
}
BEC_2_4_3_MathInt* BEC_2_4_3_MathInt::bem_setStringValueHex_1(BEC_2_4_6_TextString* bevk_str) {
struct bes { BEC_2_4_6_TextString* beva_str; BEC_2_4_3_MathInt* bevt_0_ta_ph; BEC_2_4_3_MathInt* bevt_1_ta_ph; BEC_2_4_3_MathInt* bevt_2_ta_ph; BEC_2_4_3_MathInt* bevt_3_ta_ph; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->beva_str = bevk_str;
beq->bevt_0_ta_ph = nullptr;
beq->bevt_1_ta_ph = nullptr;
beq->bevt_2_ta_ph = nullptr;
beq->bevt_3_ta_ph = nullptr;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(6);
beq->bevt_0_ta_ph = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(16))));
beq->bevt_1_ta_ph = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(58))));
beq->bevt_2_ta_ph = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(71))));
beq->bevt_3_ta_ph = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(103))));
bem_setStringValue_5(beq->beva_str, beq->bevt_0_ta_ph, beq->bevt_1_ta_ph, beq->bevt_2_ta_ph, beq->bevt_3_ta_ph);
return this;
}
BEC_2_4_3_MathInt* BEC_2_4_3_MathInt::bem_setStringValue_2(BEC_2_4_6_TextString* bevk_str, BEC_2_4_3_MathInt* bevk_radix) {
struct bes { BEC_2_4_6_TextString* beva_str; BEC_2_4_3_MathInt* beva_radix; BEC_2_4_3_MathInt* bevl_max0; BEC_2_4_3_MathInt* bevl_maxA; BEC_2_4_3_MathInt* bevl_maxa; BEC_2_5_4_LogicBool* bevt_0_ta_anchor; BEC_2_5_4_LogicBool* bevt_1_ta_ph; BEC_2_4_3_MathInt* bevt_2_ta_ph; BEC_2_5_4_LogicBool* bevt_3_ta_ph; BEC_2_4_3_MathInt* bevt_4_ta_ph; BEC_2_6_9_SystemException* bevt_5_ta_ph; BEC_2_4_6_TextString* bevt_6_ta_ph; BEC_2_4_6_TextString* bevt_7_ta_ph; BEC_2_5_4_LogicBool* bevt_8_ta_ph; BEC_2_4_3_MathInt* bevt_9_ta_ph; BEC_2_4_3_MathInt* bevt_10_ta_ph; BEC_2_4_3_MathInt* bevt_11_ta_ph; BEC_2_4_3_MathInt* bevt_12_ta_ph; BEC_2_4_3_MathInt* bevt_13_ta_ph; BEC_2_4_3_MathInt* bevt_14_ta_ph; BEC_2_4_3_MathInt* bevt_15_ta_ph; BEC_2_4_3_MathInt* bevt_16_ta_ph; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->beva_str = bevk_str;
beq->beva_radix = bevk_radix;
beq->bevl_max0 = nullptr;
beq->bevl_maxA = nullptr;
beq->bevl_maxa = nullptr;
beq->bevt_0_ta_anchor = nullptr;
beq->bevt_1_ta_ph = nullptr;
beq->bevt_2_ta_ph = nullptr;
beq->bevt_3_ta_ph = nullptr;
beq->bevt_4_ta_ph = nullptr;
beq->bevt_5_ta_ph = nullptr;
beq->bevt_6_ta_ph = nullptr;
beq->bevt_7_ta_ph = nullptr;
beq->bevt_8_ta_ph = nullptr;
beq->bevt_9_ta_ph = nullptr;
beq->bevt_10_ta_ph = nullptr;
beq->bevt_11_ta_ph = nullptr;
beq->bevt_12_ta_ph = nullptr;
beq->bevt_13_ta_ph = nullptr;
beq->bevt_14_ta_ph = nullptr;
beq->bevt_15_ta_ph = nullptr;
beq->bevt_16_ta_ph = nullptr;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(23);
beq->bevt_2_ta_ph = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(2))));
if (beq->beva_radix->bevi_int < beq->bevt_2_ta_ph->bevi_int) {
beq->bevt_1_ta_ph = BECS_Runtime::boolTrue;
 } else { 
beq->bevt_1_ta_ph = BECS_Runtime::boolFalse;
}
if (beq->bevt_1_ta_ph->bevi_bool) {
beq->bevt_0_ta_anchor = BECS_Runtime::boolTrue;
} 
 else  {
beq->bevt_4_ta_ph = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(24))));
if (beq->beva_radix->bevi_int > beq->bevt_4_ta_ph->bevi_int) {
beq->bevt_3_ta_ph = BECS_Runtime::boolTrue;
 } else { 
beq->bevt_3_ta_ph = BECS_Runtime::boolFalse;
}
if (beq->bevt_3_ta_ph->bevi_bool) {
beq->bevt_0_ta_anchor = BECS_Runtime::boolTrue;
} 
 else  {
beq->bevt_0_ta_anchor = BECS_Runtime::boolFalse;
} 
} 
if (beq->bevt_0_ta_anchor->bevi_bool) {
beq->bevt_7_ta_ph = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString(39, {0x44,0x6F,0x6E,0x27,0x74,0x20,0x6B,0x6E,0x6F,0x77,0x20,0x68,0x6F,0x77,0x20,0x74,0x6F,0x20,0x68,0x61,0x6E,0x64,0x6C,0x65,0x20,0x72,0x61,0x64,0x69,0x78,0x20,0x6F,0x66,0x20,0x73,0x69,0x7A,0x65,0x20}))));
beq->bevt_6_ta_ph = beq->bevt_7_ta_ph->bem_add_1(beq->beva_radix);
beq->bevt_5_ta_ph = static_cast<BEC_2_6_9_SystemException*>(((BEC_2_6_9_SystemException*) (new BEC_2_6_9_SystemException()))->bem_new_1(beq->bevt_6_ta_ph));
throw BECS_ThrowBack(beq->bevt_5_ta_ph);
} 
beq->bevt_9_ta_ph = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(10))));
if (beq->beva_radix->bevi_int < beq->bevt_9_ta_ph->bevi_int) {
beq->bevt_8_ta_ph = BECS_Runtime::boolTrue;
 } else { 
beq->bevt_8_ta_ph = BECS_Runtime::boolFalse;
}
if (beq->bevt_8_ta_ph->bevi_bool) {
beq->bevl_max0 = static_cast<BEC_2_4_3_MathInt*>(beq->beva_radix->bem_copy_0());
} 
 else  {
beq->bevl_max0 = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(10))));
} 
beq->bevt_10_ta_ph = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(48))));
beq->bevl_max0->bevi_int += beq->bevt_10_ta_ph->bevi_int;
beq->bevt_11_ta_ph = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(65))));
beq->bevt_13_ta_ph = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(10))));
beq->bevt_12_ta_ph = beq->beva_radix->bem_subtract_1(beq->bevt_13_ta_ph);
beq->bevl_maxA = beq->bevt_11_ta_ph->bem_add_1(beq->bevt_12_ta_ph);
beq->bevt_14_ta_ph = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(97))));
beq->bevt_16_ta_ph = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(10))));
beq->bevt_15_ta_ph = beq->beva_radix->bem_subtract_1(beq->bevt_16_ta_ph);
beq->bevl_maxa = beq->bevt_14_ta_ph->bem_add_1(beq->bevt_15_ta_ph);
bem_setStringValue_5(beq->beva_str, beq->beva_radix, beq->bevl_max0, beq->bevl_maxA, beq->bevl_maxa);
return this;
}
BEC_2_4_3_MathInt* BEC_2_4_3_MathInt::bem_setStringValue_5(BEC_2_4_6_TextString* bevk_str, BEC_2_4_3_MathInt* bevk_radix, BEC_2_4_3_MathInt* bevk_max0, BEC_2_4_3_MathInt* bevk_maxA, BEC_2_4_3_MathInt* bevk_maxa) {
struct bes { BEC_2_4_6_TextString* beva_str; BEC_2_4_3_MathInt* beva_radix; BEC_2_4_3_MathInt* beva_max0; BEC_2_4_3_MathInt* beva_maxA; BEC_2_4_3_MathInt* beva_maxa; BEC_2_4_3_MathInt* bevl_j; BEC_2_4_3_MathInt* bevl_pow; BEC_2_4_3_MathInt* bevl_ic; BEC_2_5_4_LogicBool* bevt_0_ta_anchor; BEC_2_5_4_LogicBool* bevt_1_ta_anchor; BEC_2_5_4_LogicBool* bevt_2_ta_anchor; BEC_2_4_3_MathInt* bevt_3_ta_ph; BEC_2_4_3_MathInt* bevt_4_ta_ph; BEC_2_5_4_LogicBool* bevt_5_ta_ph; BEC_2_4_3_MathInt* bevt_6_ta_ph; BEC_2_5_4_LogicBool* bevt_7_ta_ph; BEC_2_4_3_MathInt* bevt_8_ta_ph; BEC_2_5_4_LogicBool* bevt_9_ta_ph; BEC_2_4_3_MathInt* bevt_10_ta_ph; BEC_2_5_4_LogicBool* bevt_11_ta_ph; BEC_2_4_3_MathInt* bevt_12_ta_ph; BEC_2_5_4_LogicBool* bevt_13_ta_ph; BEC_2_4_3_MathInt* bevt_14_ta_ph; BEC_2_5_4_LogicBool* bevt_15_ta_ph; BEC_2_4_3_MathInt* bevt_16_ta_ph; BEC_2_5_4_LogicBool* bevt_17_ta_ph; BEC_2_4_3_MathInt* bevt_18_ta_ph; BEC_2_5_4_LogicBool* bevt_19_ta_ph; BEC_2_4_3_MathInt* bevt_20_ta_ph; BEC_2_4_3_MathInt* bevt_21_ta_ph; BEC_2_5_4_LogicBool* bevt_22_ta_ph; BEC_2_4_3_MathInt* bevt_23_ta_ph; BEC_2_6_9_SystemException* bevt_24_ta_ph; BEC_2_4_6_TextString* bevt_25_ta_ph; BEC_2_4_6_TextString* bevt_26_ta_ph; BEC_2_4_6_TextString* bevt_27_ta_ph; BEC_2_4_6_TextString* bevt_28_ta_ph; BEC_2_4_6_TextString* bevt_29_ta_ph; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->beva_str = bevk_str;
beq->beva_radix = bevk_radix;
beq->beva_max0 = bevk_max0;
beq->beva_maxA = bevk_maxA;
beq->beva_maxa = bevk_maxa;
beq->bevl_j = nullptr;
beq->bevl_pow = nullptr;
beq->bevl_ic = nullptr;
beq->bevt_0_ta_anchor = nullptr;
beq->bevt_1_ta_anchor = nullptr;
beq->bevt_2_ta_anchor = nullptr;
beq->bevt_3_ta_ph = nullptr;
beq->bevt_4_ta_ph = nullptr;
beq->bevt_5_ta_ph = nullptr;
beq->bevt_6_ta_ph = nullptr;
beq->bevt_7_ta_ph = nullptr;
beq->bevt_8_ta_ph = nullptr;
beq->bevt_9_ta_ph = nullptr;
beq->bevt_10_ta_ph = nullptr;
beq->bevt_11_ta_ph = nullptr;
beq->bevt_12_ta_ph = nullptr;
beq->bevt_13_ta_ph = nullptr;
beq->bevt_14_ta_ph = nullptr;
beq->bevt_15_ta_ph = nullptr;
beq->bevt_16_ta_ph = nullptr;
beq->bevt_17_ta_ph = nullptr;
beq->bevt_18_ta_ph = nullptr;
beq->bevt_19_ta_ph = nullptr;
beq->bevt_20_ta_ph = nullptr;
beq->bevt_21_ta_ph = nullptr;
beq->bevt_22_ta_ph = nullptr;
beq->bevt_23_ta_ph = nullptr;
beq->bevt_24_ta_ph = nullptr;
beq->bevt_25_ta_ph = nullptr;
beq->bevt_26_ta_ph = nullptr;
beq->bevt_27_ta_ph = nullptr;
beq->bevt_28_ta_ph = nullptr;
beq->bevt_29_ta_ph = nullptr;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(39);
beq->bevt_3_ta_ph = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(0))));
bevi_int = beq->bevt_3_ta_ph->bevi_int;
beq->bevt_4_ta_ph = beq->beva_str->bem_sizeGet_0();
beq->bevl_j = static_cast<BEC_2_4_3_MathInt*>(beq->bevt_4_ta_ph->bem_copy_0());
beq->bevl_j->bem_decrementValue_0();
beq->bevl_pow = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(1))));
beq->bevl_ic = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt())));
while (true)
 {
beq->bevt_6_ta_ph = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(0))));
if (beq->bevl_j->bevi_int >= beq->bevt_6_ta_ph->bevi_int) {
beq->bevt_5_ta_ph = BECS_Runtime::boolTrue;
 } else { 
beq->bevt_5_ta_ph = BECS_Runtime::boolFalse;
}
if (beq->bevt_5_ta_ph->bevi_bool) {
beq->beva_str->bem_getInt_2(beq->bevl_j, beq->bevl_ic);
beq->bevt_8_ta_ph = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(47))));
if (beq->bevl_ic->bevi_int > beq->bevt_8_ta_ph->bevi_int) {
beq->bevt_7_ta_ph = BECS_Runtime::boolTrue;
 } else { 
beq->bevt_7_ta_ph = BECS_Runtime::boolFalse;
}
if (beq->bevt_7_ta_ph->bevi_bool) {
if (beq->bevl_ic->bevi_int < beq->beva_max0->bevi_int) {
beq->bevt_9_ta_ph = BECS_Runtime::boolTrue;
 } else { 
beq->bevt_9_ta_ph = BECS_Runtime::boolFalse;
}
if (beq->bevt_9_ta_ph->bevi_bool) {
beq->bevt_0_ta_anchor = BECS_Runtime::boolTrue;
} 
 else  {
beq->bevt_0_ta_anchor = BECS_Runtime::boolFalse;
} 
} 
 else  {
beq->bevt_0_ta_anchor = BECS_Runtime::boolFalse;
} 
if (beq->bevt_0_ta_anchor->bevi_bool) {
beq->bevt_10_ta_ph = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(48))));
beq->bevl_ic->bem_subtractValue_1(beq->bevt_10_ta_ph);
beq->bevl_ic->bem_multiplyValue_1(beq->bevl_pow);
bevi_int += beq->bevl_ic->bevi_int;
} 
 else  {
beq->bevt_12_ta_ph = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(64))));
if (beq->bevl_ic->bevi_int > beq->bevt_12_ta_ph->bevi_int) {
beq->bevt_11_ta_ph = BECS_Runtime::boolTrue;
 } else { 
beq->bevt_11_ta_ph = BECS_Runtime::boolFalse;
}
if (beq->bevt_11_ta_ph->bevi_bool) {
if (beq->bevl_ic->bevi_int < beq->beva_maxA->bevi_int) {
beq->bevt_13_ta_ph = BECS_Runtime::boolTrue;
 } else { 
beq->bevt_13_ta_ph = BECS_Runtime::boolFalse;
}
if (beq->bevt_13_ta_ph->bevi_bool) {
beq->bevt_1_ta_anchor = BECS_Runtime::boolTrue;
} 
 else  {
beq->bevt_1_ta_anchor = BECS_Runtime::boolFalse;
} 
} 
 else  {
beq->bevt_1_ta_anchor = BECS_Runtime::boolFalse;
} 
if (beq->bevt_1_ta_anchor->bevi_bool) {
beq->bevt_14_ta_ph = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(55))));
beq->bevl_ic->bem_subtractValue_1(beq->bevt_14_ta_ph);
beq->bevl_ic->bem_multiplyValue_1(beq->bevl_pow);
bevi_int += beq->bevl_ic->bevi_int;
} 
 else  {
beq->bevt_16_ta_ph = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(96))));
if (beq->bevl_ic->bevi_int > beq->bevt_16_ta_ph->bevi_int) {
beq->bevt_15_ta_ph = BECS_Runtime::boolTrue;
 } else { 
beq->bevt_15_ta_ph = BECS_Runtime::boolFalse;
}
if (beq->bevt_15_ta_ph->bevi_bool) {
if (beq->bevl_ic->bevi_int < beq->beva_maxa->bevi_int) {
beq->bevt_17_ta_ph = BECS_Runtime::boolTrue;
 } else { 
beq->bevt_17_ta_ph = BECS_Runtime::boolFalse;
}
if (beq->bevt_17_ta_ph->bevi_bool) {
beq->bevt_2_ta_anchor = BECS_Runtime::boolTrue;
} 
 else  {
beq->bevt_2_ta_anchor = BECS_Runtime::boolFalse;
} 
} 
 else  {
beq->bevt_2_ta_anchor = BECS_Runtime::boolFalse;
} 
if (beq->bevt_2_ta_anchor->bevi_bool) {
beq->bevt_18_ta_ph = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(87))));
beq->bevl_ic->bem_subtractValue_1(beq->bevt_18_ta_ph);
beq->bevl_ic->bem_multiplyValue_1(beq->bevl_pow);
bevi_int += beq->bevl_ic->bevi_int;
} 
 else  {
beq->bevt_20_ta_ph = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(45))));
if (beq->bevl_ic->bevi_int == beq->bevt_20_ta_ph->bevi_int) {
beq->bevt_19_ta_ph = BECS_Runtime::boolTrue;
 } else { 
beq->bevt_19_ta_ph = BECS_Runtime::boolFalse;
}
if (beq->bevt_19_ta_ph->bevi_bool) {
beq->bevt_21_ta_ph = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(-1))));
bem_multiplyValue_1(beq->bevt_21_ta_ph);
} 
 else  {
beq->bevt_23_ta_ph = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(43))));
if (beq->bevl_ic->bevi_int == beq->bevt_23_ta_ph->bevi_int) {
beq->bevt_22_ta_ph = BECS_Runtime::boolTrue;
 } else { 
beq->bevt_22_ta_ph = BECS_Runtime::boolFalse;
}
if (beq->bevt_22_ta_ph->bevi_bool) {
} 
 else  {
beq->bevt_28_ta_ph = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString(21, {0x53,0x74,0x72,0x69,0x6E,0x67,0x20,0x69,0x73,0x20,0x6E,0x6F,0x74,0x20,0x61,0x6E,0x20,0x69,0x6E,0x74,0x20}))));
beq->bevt_27_ta_ph = beq->bevt_28_ta_ph->bem_add_1(beq->beva_str);
beq->bevt_29_ta_ph = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString(1, {0x20}))));
beq->bevt_26_ta_ph = beq->bevt_27_ta_ph->bem_add_1(beq->bevt_29_ta_ph);
beq->bevt_25_ta_ph = beq->bevt_26_ta_ph->bem_add_1(beq->bevl_ic);
beq->bevt_24_ta_ph = static_cast<BEC_2_6_9_SystemException*>(((BEC_2_6_9_SystemException*) (new BEC_2_6_9_SystemException()))->bem_new_1(beq->bevt_25_ta_ph));
throw BECS_ThrowBack(beq->bevt_24_ta_ph);
} 
} 
} 
} 
} 
beq->bevl_j->bem_decrementValue_0();
beq->bevl_pow->bem_multiplyValue_1(beq->beva_radix);
} 
 else  {
break;
} 
} 
return this;
}
BEC_2_4_6_TextString* BEC_2_4_3_MathInt::bem_serializeToString_0() {
struct bes { BEC_2_4_6_TextString* bevt_0_ta_ph; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->bevt_0_ta_ph = nullptr;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(2);
beq->bevt_0_ta_ph = bem_toString_0();
return beq->bevt_0_ta_ph;
}
BEC_2_4_3_MathInt* BEC_2_4_3_MathInt::bem_deserializeFromStringNew_1(BEC_2_4_6_TextString* bevk_snw) {
struct bes { BEC_2_4_6_TextString* beva_snw; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->beva_snw = bevk_snw;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(2);
bem_new_1(beq->beva_snw);
return this;
}
BEC_2_5_4_LogicBool* BEC_2_4_3_MathInt::bem_serializeContentsGet_0() {
struct bes { BEC_2_5_4_LogicBool* bevt_0_ta_ph; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->bevt_0_ta_ph = nullptr;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(2);
beq->bevt_0_ta_ph = static_cast<BEC_2_5_4_LogicBool*>(BECS_Runtime::boolFalse);
return beq->bevt_0_ta_ph;
}
BEC_2_4_3_MathInt* BEC_2_4_3_MathInt::bem_hashGet_0() {
struct bes {  BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(1);
return this;
}
BEC_2_4_6_TextString* BEC_2_4_3_MathInt::bem_toString_0() {
struct bes { BEC_2_4_6_TextString* bevt_0_ta_ph; BEC_2_4_6_TextString* bevt_1_ta_ph; BEC_2_4_3_MathInt* bevt_2_ta_ph; BEC_2_4_3_MathInt* bevt_3_ta_ph; BEC_2_4_3_MathInt* bevt_4_ta_ph; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->bevt_0_ta_ph = nullptr;
beq->bevt_1_ta_ph = nullptr;
beq->bevt_2_ta_ph = nullptr;
beq->bevt_3_ta_ph = nullptr;
beq->bevt_4_ta_ph = nullptr;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(6);
beq->bevt_2_ta_ph = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(1))));
beq->bevt_1_ta_ph = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString()))->bem_new_1(beq->bevt_2_ta_ph));
beq->bevt_3_ta_ph = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(1))));
beq->bevt_4_ta_ph = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(10))));
beq->bevt_0_ta_ph = bem_toString_4(beq->bevt_1_ta_ph, beq->bevt_3_ta_ph, beq->bevt_4_ta_ph, nullptr);
return beq->bevt_0_ta_ph;
}
BEC_2_4_6_TextString* BEC_2_4_3_MathInt::bem_toHexString_0() {
struct bes { BEC_2_4_6_TextString* bevt_0_ta_ph; BEC_2_4_6_TextString* bevt_1_ta_ph; BEC_2_4_3_MathInt* bevt_2_ta_ph; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->bevt_0_ta_ph = nullptr;
beq->bevt_1_ta_ph = nullptr;
beq->bevt_2_ta_ph = nullptr;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(4);
beq->bevt_2_ta_ph = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(2))));
beq->bevt_1_ta_ph = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString()))->bem_new_1(beq->bevt_2_ta_ph));
beq->bevt_0_ta_ph = bem_toHexString_1(beq->bevt_1_ta_ph);
return beq->bevt_0_ta_ph;
}
BEC_2_4_6_TextString* BEC_2_4_3_MathInt::bem_toHexString_1(BEC_2_4_6_TextString* bevk_res) {
struct bes { BEC_2_4_6_TextString* beva_res; BEC_2_4_6_TextString* bevt_0_ta_ph; BEC_2_4_3_MathInt* bevt_1_ta_ph; BEC_2_4_3_MathInt* bevt_2_ta_ph; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->beva_res = bevk_res;
beq->bevt_0_ta_ph = nullptr;
beq->bevt_1_ta_ph = nullptr;
beq->bevt_2_ta_ph = nullptr;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(5);
beq->bevt_1_ta_ph = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(2))));
beq->bevt_2_ta_ph = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(16))));
beq->bevt_0_ta_ph = bem_toString_3(beq->beva_res, beq->bevt_1_ta_ph, beq->bevt_2_ta_ph);
return beq->bevt_0_ta_ph;
}
BEC_2_4_6_TextString* BEC_2_4_3_MathInt::bem_toString_2(BEC_2_4_3_MathInt* bevk_zeroPad, BEC_2_4_3_MathInt* bevk_radix) {
struct bes { BEC_2_4_3_MathInt* beva_zeroPad; BEC_2_4_3_MathInt* beva_radix; BEC_2_4_6_TextString* bevt_0_ta_ph; BEC_2_4_6_TextString* bevt_1_ta_ph; BEC_2_4_3_MathInt* bevt_2_ta_ph; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->beva_zeroPad = bevk_zeroPad;
beq->beva_radix = bevk_radix;
beq->bevt_0_ta_ph = nullptr;
beq->bevt_1_ta_ph = nullptr;
beq->bevt_2_ta_ph = nullptr;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(6);
beq->bevt_1_ta_ph = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString()))->bem_new_1(beq->beva_zeroPad));
beq->bevt_2_ta_ph = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(55))));
beq->bevt_0_ta_ph = bem_toString_4(beq->bevt_1_ta_ph, beq->beva_zeroPad, beq->beva_radix, beq->bevt_2_ta_ph);
return beq->bevt_0_ta_ph;
}
BEC_2_4_6_TextString* BEC_2_4_3_MathInt::bem_toString_3(BEC_2_4_6_TextString* bevk_res, BEC_2_4_3_MathInt* bevk_zeroPad, BEC_2_4_3_MathInt* bevk_radix) {
struct bes { BEC_2_4_6_TextString* beva_res; BEC_2_4_3_MathInt* beva_zeroPad; BEC_2_4_3_MathInt* beva_radix; BEC_2_4_6_TextString* bevt_0_ta_ph; BEC_2_4_3_MathInt* bevt_1_ta_ph; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->beva_res = bevk_res;
beq->beva_zeroPad = bevk_zeroPad;
beq->beva_radix = bevk_radix;
beq->bevt_0_ta_ph = nullptr;
beq->bevt_1_ta_ph = nullptr;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(6);
beq->bevt_1_ta_ph = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(55))));
beq->bevt_0_ta_ph = bem_toString_4(beq->beva_res, beq->beva_zeroPad, beq->beva_radix, beq->bevt_1_ta_ph);
return beq->bevt_0_ta_ph;
}
BEC_2_4_6_TextString* BEC_2_4_3_MathInt::bem_toString_4(BEC_2_4_6_TextString* bevk_res, BEC_2_4_3_MathInt* bevk_zeroPad, BEC_2_4_3_MathInt* bevk_radix, BEC_2_4_3_MathInt* bevk_alphaStart) {
struct bes { BEC_2_4_6_TextString* beva_res; BEC_2_4_3_MathInt* beva_zeroPad; BEC_2_4_3_MathInt* beva_radix; BEC_2_4_3_MathInt* beva_alphaStart; BEC_2_4_3_MathInt* bevl_ts; BEC_2_4_3_MathInt* bevl_val; BEC_2_5_4_LogicBool* bevt_0_ta_ph; BEC_2_4_3_MathInt* bevt_1_ta_ph; BEC_2_5_4_LogicBool* bevt_2_ta_ph; BEC_2_4_3_MathInt* bevt_3_ta_ph; BEC_2_4_3_MathInt* bevt_4_ta_ph; BEC_2_5_4_LogicBool* bevt_5_ta_ph; BEC_2_4_3_MathInt* bevt_6_ta_ph; BEC_2_4_3_MathInt* bevt_7_ta_ph; BEC_2_4_3_MathInt* bevt_8_ta_ph; BEC_2_4_3_MathInt* bevt_9_ta_ph; BEC_2_4_3_MathInt* bevt_10_ta_ph; BEC_2_4_3_MathInt* bevt_11_ta_ph; BEC_2_4_3_MathInt* bevt_12_ta_ph; BEC_2_4_3_MathInt* bevt_13_ta_ph; BEC_2_4_3_MathInt* bevt_14_ta_ph; BEC_2_5_4_LogicBool* bevt_15_ta_ph; BEC_2_4_3_MathInt* bevt_16_ta_ph; BEC_2_5_4_LogicBool* bevt_17_ta_ph; BEC_2_4_3_MathInt* bevt_18_ta_ph; BEC_2_4_3_MathInt* bevt_19_ta_ph; BEC_2_4_3_MathInt* bevt_20_ta_ph; BEC_2_4_3_MathInt* bevt_21_ta_ph; BEC_2_4_3_MathInt* bevt_22_ta_ph; BEC_2_4_3_MathInt* bevt_23_ta_ph; BEC_2_4_3_MathInt* bevt_24_ta_ph; BEC_2_4_3_MathInt* bevt_25_ta_ph; BEC_2_4_3_MathInt* bevt_26_ta_ph; BEC_2_4_3_MathInt* bevt_27_ta_ph; BEC_2_5_4_LogicBool* bevt_28_ta_ph; BEC_2_4_3_MathInt* bevt_29_ta_ph; BEC_2_4_6_TextString* bevt_30_ta_ph; BEC_2_4_6_TextString* bevt_31_ta_ph; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->beva_res = bevk_res;
beq->beva_zeroPad = bevk_zeroPad;
beq->beva_radix = bevk_radix;
beq->beva_alphaStart = bevk_alphaStart;
beq->bevl_ts = nullptr;
beq->bevl_val = nullptr;
beq->bevt_0_ta_ph = nullptr;
beq->bevt_1_ta_ph = nullptr;
beq->bevt_2_ta_ph = nullptr;
beq->bevt_3_ta_ph = nullptr;
beq->bevt_4_ta_ph = nullptr;
beq->bevt_5_ta_ph = nullptr;
beq->bevt_6_ta_ph = nullptr;
beq->bevt_7_ta_ph = nullptr;
beq->bevt_8_ta_ph = nullptr;
beq->bevt_9_ta_ph = nullptr;
beq->bevt_10_ta_ph = nullptr;
beq->bevt_11_ta_ph = nullptr;
beq->bevt_12_ta_ph = nullptr;
beq->bevt_13_ta_ph = nullptr;
beq->bevt_14_ta_ph = nullptr;
beq->bevt_15_ta_ph = nullptr;
beq->bevt_16_ta_ph = nullptr;
beq->bevt_17_ta_ph = nullptr;
beq->bevt_18_ta_ph = nullptr;
beq->bevt_19_ta_ph = nullptr;
beq->bevt_20_ta_ph = nullptr;
beq->bevt_21_ta_ph = nullptr;
beq->bevt_22_ta_ph = nullptr;
beq->bevt_23_ta_ph = nullptr;
beq->bevt_24_ta_ph = nullptr;
beq->bevt_25_ta_ph = nullptr;
beq->bevt_26_ta_ph = nullptr;
beq->bevt_27_ta_ph = nullptr;
beq->bevt_28_ta_ph = nullptr;
beq->bevt_29_ta_ph = nullptr;
beq->bevt_30_ta_ph = nullptr;
beq->bevt_31_ta_ph = nullptr;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(39);
beq->beva_res->bem_clear_0();
beq->bevl_ts = bem_abs_0();
beq->bevl_val = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt())));
while (true)
 {
beq->bevt_1_ta_ph = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(0))));
if (beq->bevl_ts->bevi_int > beq->bevt_1_ta_ph->bevi_int) {
beq->bevt_0_ta_ph = BECS_Runtime::boolTrue;
 } else { 
beq->bevt_0_ta_ph = BECS_Runtime::boolFalse;
}
if (beq->bevt_0_ta_ph->bevi_bool) {
beq->bevl_val->bevi_int = beq->bevl_ts->bevi_int;
beq->bevl_val->bem_modulusValue_1(beq->beva_radix);
beq->bevt_3_ta_ph = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(10))));
if (beq->bevl_val->bevi_int < beq->bevt_3_ta_ph->bevi_int) {
beq->bevt_2_ta_ph = BECS_Runtime::boolTrue;
 } else { 
beq->bevt_2_ta_ph = BECS_Runtime::boolFalse;
}
if (beq->bevt_2_ta_ph->bevi_bool) {
beq->bevt_4_ta_ph = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(48))));
beq->bevl_val->bevi_int += beq->bevt_4_ta_ph->bevi_int;
} 
 else  {
beq->bevl_val->bevi_int += beq->beva_alphaStart->bevi_int;
} 
beq->bevt_6_ta_ph = beq->beva_res->bem_capacityGet_0();
beq->bevt_7_ta_ph = beq->beva_res->bem_sizeGet_0();
if (beq->bevt_6_ta_ph->bevi_int <= beq->bevt_7_ta_ph->bevi_int) {
beq->bevt_5_ta_ph = BECS_Runtime::boolTrue;
 } else { 
beq->bevt_5_ta_ph = BECS_Runtime::boolFalse;
}
if (beq->bevt_5_ta_ph->bevi_bool) {
beq->bevt_9_ta_ph = beq->beva_res->bem_capacityGet_0();
beq->bevt_10_ta_ph = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(4))));
beq->bevt_8_ta_ph = beq->bevt_9_ta_ph->bem_add_1(beq->bevt_10_ta_ph);
beq->beva_res->bem_capacitySet_1(beq->bevt_8_ta_ph);
} 
beq->bevt_11_ta_ph = beq->beva_res->bem_sizeGet_0();
beq->beva_res->bem_setIntUnchecked_2(beq->bevt_11_ta_ph, beq->bevl_val);
beq->bevt_13_ta_ph = beq->beva_res->bem_sizeGet_0();
beq->bevt_14_ta_ph = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(1))));
beq->bevt_12_ta_ph = beq->bevt_13_ta_ph->bem_add_1(beq->bevt_14_ta_ph);
beq->beva_res->bem_sizeSet_1(beq->bevt_12_ta_ph);
beq->bevl_ts->bem_divideValue_1(beq->beva_radix);
} 
 else  {
break;
} 
} 
while (true)
 {
beq->bevt_16_ta_ph = beq->beva_res->bem_sizeGet_0();
if (beq->bevt_16_ta_ph->bevi_int < beq->beva_zeroPad->bevi_int) {
beq->bevt_15_ta_ph = BECS_Runtime::boolTrue;
 } else { 
beq->bevt_15_ta_ph = BECS_Runtime::boolFalse;
}
if (beq->bevt_15_ta_ph->bevi_bool) {
beq->bevt_18_ta_ph = beq->beva_res->bem_capacityGet_0();
beq->bevt_19_ta_ph = beq->beva_res->bem_sizeGet_0();
if (beq->bevt_18_ta_ph->bevi_int <= beq->bevt_19_ta_ph->bevi_int) {
beq->bevt_17_ta_ph = BECS_Runtime::boolTrue;
 } else { 
beq->bevt_17_ta_ph = BECS_Runtime::boolFalse;
}
if (beq->bevt_17_ta_ph->bevi_bool) {
beq->bevt_21_ta_ph = beq->beva_res->bem_capacityGet_0();
beq->bevt_22_ta_ph = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(4))));
beq->bevt_20_ta_ph = beq->bevt_21_ta_ph->bem_add_1(beq->bevt_22_ta_ph);
beq->beva_res->bem_capacitySet_1(beq->bevt_20_ta_ph);
} 
beq->bevt_23_ta_ph = beq->beva_res->bem_sizeGet_0();
beq->bevt_24_ta_ph = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(48))));
beq->beva_res->bem_setIntUnchecked_2(beq->bevt_23_ta_ph, beq->bevt_24_ta_ph);
beq->bevt_26_ta_ph = beq->beva_res->bem_sizeGet_0();
beq->bevt_27_ta_ph = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(1))));
beq->bevt_25_ta_ph = beq->bevt_26_ta_ph->bem_add_1(beq->bevt_27_ta_ph);
beq->beva_res->bem_sizeSet_1(beq->bevt_25_ta_ph);
} 
 else  {
break;
} 
} 
beq->bevt_29_ta_ph = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(0))));
if (bevi_int < beq->bevt_29_ta_ph->bevi_int) {
beq->bevt_28_ta_ph = BECS_Runtime::boolTrue;
 } else { 
beq->bevt_28_ta_ph = BECS_Runtime::boolFalse;
}
if (beq->bevt_28_ta_ph->bevi_bool) {
beq->bevt_30_ta_ph = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString(1, {0x2D}))));
beq->beva_res->bem_addValue_1(beq->bevt_30_ta_ph);
} 
beq->bevt_31_ta_ph = static_cast<BEC_2_4_6_TextString*>(beq->beva_res->bem_reverseBytes_0());
return beq->bevt_31_ta_ph;
}
BEC_2_6_6_SystemObject* BEC_2_4_3_MathInt::bem_copy_0() {
struct bes { BEC_2_4_3_MathInt* bevl_c; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->bevl_c = nullptr;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(2);
beq->bevl_c = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt())));
beq->bevl_c->bevi_int = bevi_int;
return static_cast<BEC_2_6_6_SystemObject*>(beq->bevl_c);
}
BEC_2_4_3_MathInt* BEC_2_4_3_MathInt::bem_abs_0() {
struct bes { BEC_2_4_3_MathInt* bevt_0_ta_ph; BEC_2_4_3_MathInt* bevt_1_ta_ph; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->bevt_0_ta_ph = nullptr;
beq->bevt_1_ta_ph = nullptr;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(3);
beq->bevt_1_ta_ph = static_cast<BEC_2_4_3_MathInt*>(bem_copy_0());
beq->bevt_0_ta_ph = beq->bevt_1_ta_ph->bem_absValue_0();
return beq->bevt_0_ta_ph;
}
BEC_2_4_3_MathInt* BEC_2_4_3_MathInt::bem_absValue_0() {
struct bes { BEC_2_5_4_LogicBool* bevt_0_ta_ph; BEC_2_4_3_MathInt* bevt_1_ta_ph; BEC_2_4_3_MathInt* bevt_2_ta_ph; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->bevt_0_ta_ph = nullptr;
beq->bevt_1_ta_ph = nullptr;
beq->bevt_2_ta_ph = nullptr;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(4);
beq->bevt_1_ta_ph = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(0))));
if (bevi_int < beq->bevt_1_ta_ph->bevi_int) {
beq->bevt_0_ta_ph = BECS_Runtime::boolTrue;
 } else { 
beq->bevt_0_ta_ph = BECS_Runtime::boolFalse;
}
if (beq->bevt_0_ta_ph->bevi_bool) {
beq->bevt_2_ta_ph = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(-1))));
bem_multiplyValue_1(beq->bevt_2_ta_ph);
} 
return this;
}
BEC_2_4_3_MathInt* BEC_2_4_3_MathInt::bem_setValue_1(BEC_2_4_3_MathInt* bevk_xi) {
struct bes { BEC_2_4_3_MathInt* beva_xi; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->beva_xi = bevk_xi;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(2);

bevi_int = beq->beva_xi->bevi_int;
return this;
}
BEC_2_4_3_MathInt* BEC_2_4_3_MathInt::bem_increment_0() {
struct bes { BEC_2_4_3_MathInt* bevl_res; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->bevl_res = nullptr;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(2);
beq->bevl_res = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt())));

                beq->bevl_res->bevi_int = bevi_int + 1;
            return beq->bevl_res;
}
BEC_2_4_3_MathInt* BEC_2_4_3_MathInt::bem_decrement_0() {
struct bes { BEC_2_4_3_MathInt* bevl_res; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->bevl_res = nullptr;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(2);
beq->bevl_res = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt())));

                beq->bevl_res->bevi_int = bevi_int - 1;
            return beq->bevl_res;
}
BEC_2_4_3_MathInt* BEC_2_4_3_MathInt::bem_incrementValue_0() {
struct bes {  BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(1);

      bevi_int++;
      return this;
}
BEC_2_4_3_MathInt* BEC_2_4_3_MathInt::bem_decrementValue_0() {
struct bes {  BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(1);

      bevi_int--;
      return this;
}
BEC_2_4_3_MathInt* BEC_2_4_3_MathInt::bem_add_1(BEC_2_4_3_MathInt* bevk_xi) {
struct bes { BEC_2_4_3_MathInt* beva_xi; BEC_2_4_3_MathInt* bevl_res; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->beva_xi = bevk_xi;
beq->bevl_res = nullptr;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(3);
beq->bevl_res = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt())));

                beq->bevl_res->bevi_int = bevi_int + beq->beva_xi->bevi_int;
            return beq->bevl_res;
}
BEC_2_4_3_MathInt* BEC_2_4_3_MathInt::bem_addValue_1(BEC_2_4_3_MathInt* bevk_xi) {
struct bes { BEC_2_4_3_MathInt* beva_xi; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->beva_xi = bevk_xi;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(2);

      this->bevi_int += beq->beva_xi->bevi_int;
      return this;
}
BEC_2_4_3_MathInt* BEC_2_4_3_MathInt::bem_subtract_1(BEC_2_4_3_MathInt* bevk_xi) {
struct bes { BEC_2_4_3_MathInt* beva_xi; BEC_2_4_3_MathInt* bevl_res; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->beva_xi = bevk_xi;
beq->bevl_res = nullptr;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(3);
beq->bevl_res = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt())));

                beq->bevl_res->bevi_int = bevi_int - beq->beva_xi->bevi_int;
            return beq->bevl_res;
}
BEC_2_4_3_MathInt* BEC_2_4_3_MathInt::bem_subtractValue_1(BEC_2_4_3_MathInt* bevk_xi) {
struct bes { BEC_2_4_3_MathInt* beva_xi; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->beva_xi = bevk_xi;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(2);

      bevi_int -= beq->beva_xi->bevi_int;
      return this;
}
BEC_2_4_3_MathInt* BEC_2_4_3_MathInt::bem_multiply_1(BEC_2_4_3_MathInt* bevk_xi) {
struct bes { BEC_2_4_3_MathInt* beva_xi; BEC_2_4_3_MathInt* bevl_res; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->beva_xi = bevk_xi;
beq->bevl_res = nullptr;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(3);
beq->bevl_res = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt())));

            beq->bevl_res->bevi_int = bevi_int * beq->beva_xi->bevi_int;
        return beq->bevl_res;
}
BEC_2_4_3_MathInt* BEC_2_4_3_MathInt::bem_multiplyValue_1(BEC_2_4_3_MathInt* bevk_xi) {
struct bes { BEC_2_4_3_MathInt* beva_xi; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->beva_xi = bevk_xi;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(2);

      bevi_int *= beq->beva_xi->bevi_int;
      return this;
}
BEC_2_4_3_MathInt* BEC_2_4_3_MathInt::bem_divide_1(BEC_2_4_3_MathInt* bevk_xi) {
struct bes { BEC_2_4_3_MathInt* beva_xi; BEC_2_4_3_MathInt* bevl_res; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->beva_xi = bevk_xi;
beq->bevl_res = nullptr;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(3);
beq->bevl_res = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt())));

                beq->bevl_res->bevi_int = bevi_int / beq->beva_xi->bevi_int;
            return beq->bevl_res;
}
BEC_2_4_3_MathInt* BEC_2_4_3_MathInt::bem_divideValue_1(BEC_2_4_3_MathInt* bevk_xi) {
struct bes { BEC_2_4_3_MathInt* beva_xi; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->beva_xi = bevk_xi;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(2);

      bevi_int /= beq->beva_xi->bevi_int;
      return this;
}
BEC_2_4_3_MathInt* BEC_2_4_3_MathInt::bem_modulus_1(BEC_2_4_3_MathInt* bevk_xi) {
struct bes { BEC_2_4_3_MathInt* beva_xi; BEC_2_4_3_MathInt* bevl_res; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->beva_xi = bevk_xi;
beq->bevl_res = nullptr;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(3);
beq->bevl_res = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt())));

                beq->bevl_res->bevi_int = bevi_int % beq->beva_xi->bevi_int;
            return beq->bevl_res;
}
BEC_2_4_3_MathInt* BEC_2_4_3_MathInt::bem_modulusValue_1(BEC_2_4_3_MathInt* bevk_xi) {
struct bes { BEC_2_4_3_MathInt* beva_xi; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->beva_xi = bevk_xi;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(2);

      bevi_int %= beq->beva_xi->bevi_int;
      return this;
}
BEC_2_4_3_MathInt* BEC_2_4_3_MathInt::bem_and_1(BEC_2_4_3_MathInt* bevk_xi) {
struct bes { BEC_2_4_3_MathInt* beva_xi; BEC_2_4_3_MathInt* bevl_toReti; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->beva_xi = bevk_xi;
beq->bevl_toReti = nullptr;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(3);
beq->bevl_toReti = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt())));

        beq->bevl_toReti->bevi_int = bevi_int & beq->beva_xi->bevi_int;
    return beq->bevl_toReti;
}
BEC_2_4_3_MathInt* BEC_2_4_3_MathInt::bem_andValue_1(BEC_2_4_3_MathInt* bevk_xi) {
struct bes { BEC_2_4_3_MathInt* beva_xi; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->beva_xi = bevk_xi;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(2);

        bevi_int &= beq->beva_xi->bevi_int;
    return this;
}
BEC_2_4_3_MathInt* BEC_2_4_3_MathInt::bem_or_1(BEC_2_4_3_MathInt* bevk_xi) {
struct bes { BEC_2_4_3_MathInt* beva_xi; BEC_2_4_3_MathInt* bevl_toReti; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->beva_xi = bevk_xi;
beq->bevl_toReti = nullptr;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(3);
beq->bevl_toReti = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt())));

        beq->bevl_toReti->bevi_int = bevi_int | beq->beva_xi->bevi_int;
    return beq->bevl_toReti;
}
BEC_2_4_3_MathInt* BEC_2_4_3_MathInt::bem_orValue_1(BEC_2_4_3_MathInt* bevk_xi) {
struct bes { BEC_2_4_3_MathInt* beva_xi; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->beva_xi = bevk_xi;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(2);

        bevi_int |= beq->beva_xi->bevi_int;
    return this;
}
BEC_2_4_3_MathInt* BEC_2_4_3_MathInt::bem_shiftLeft_1(BEC_2_4_3_MathInt* bevk_xi) {
struct bes { BEC_2_4_3_MathInt* beva_xi; BEC_2_4_3_MathInt* bevl_toReti; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->beva_xi = bevk_xi;
beq->bevl_toReti = nullptr;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(3);
beq->bevl_toReti = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt())));

        beq->bevl_toReti->bevi_int = bevi_int << beq->beva_xi->bevi_int;
    return beq->bevl_toReti;
}
BEC_2_4_3_MathInt* BEC_2_4_3_MathInt::bem_shiftLeftValue_1(BEC_2_4_3_MathInt* bevk_xi) {
struct bes { BEC_2_4_3_MathInt* beva_xi; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->beva_xi = bevk_xi;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(2);

        bevi_int <<= beq->beva_xi->bevi_int;
    return this;
}
BEC_2_4_3_MathInt* BEC_2_4_3_MathInt::bem_shiftRight_1(BEC_2_4_3_MathInt* bevk_xi) {
struct bes { BEC_2_4_3_MathInt* beva_xi; BEC_2_4_3_MathInt* bevl_toReti; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->beva_xi = bevk_xi;
beq->bevl_toReti = nullptr;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(3);
beq->bevl_toReti = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt())));

        beq->bevl_toReti->bevi_int = bevi_int >> beq->beva_xi->bevi_int;
    return beq->bevl_toReti;
}
BEC_2_4_3_MathInt* BEC_2_4_3_MathInt::bem_shiftRightValue_1(BEC_2_4_3_MathInt* bevk_xi) {
struct bes { BEC_2_4_3_MathInt* beva_xi; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->beva_xi = bevk_xi;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(2);

        bevi_int >>= beq->beva_xi->bevi_int;
    return this;
}
BEC_2_4_3_MathInt* BEC_2_4_3_MathInt::bem_power_1(BEC_2_4_3_MathInt* bevk_other) {
struct bes { BEC_2_4_3_MathInt* beva_other; BEC_2_4_3_MathInt* bevl_result; BEC_2_4_3_MathInt* bevl_i; BEC_2_5_4_LogicBool* bevt_0_ta_ph; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->beva_other = bevk_other;
beq->bevl_result = nullptr;
beq->bevl_i = nullptr;
beq->bevt_0_ta_ph = nullptr;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(5);
beq->bevl_result = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(1))));
beq->bevl_i = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(0))));
while (true)
 {
if (beq->bevl_i->bevi_int < beq->beva_other->bevi_int) {
beq->bevt_0_ta_ph = BECS_Runtime::boolTrue;
 } else { 
beq->bevt_0_ta_ph = BECS_Runtime::boolFalse;
}
if (beq->bevt_0_ta_ph->bevi_bool) {
beq->bevl_result->bem_multiplyValue_1(this);
beq->bevl_i->bevi_int++;
} 
 else  {
break;
} 
} 
return beq->bevl_result;
}
BEC_2_5_4_LogicBool* BEC_2_4_3_MathInt::bem_equals_1(BEC_2_6_6_SystemObject* bevk_xi) {
struct bes { BEC_2_6_6_SystemObject* beva_xi; BEC_2_5_4_LogicBool* bevt_0_ta_ph; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->beva_xi = bevk_xi;
beq->bevt_0_ta_ph = nullptr;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(3);

#ifndef BEDCC_NORTTI
      BEC_2_4_3_MathInt* bevls_xi = dynamic_cast<BEC_2_4_3_MathInt*>(beq->beva_xi);
#endif
#ifdef BEDCC_NORTTI
      BEC_2_4_3_MathInt* bevls_xi = static_cast<BEC_2_4_3_MathInt*>(beq->beva_xi);
#endif
      if (bevi_int == bevls_xi->bevi_int) {
        return BECS_Runtime::boolTrue;
      }
      beq->bevt_0_ta_ph = static_cast<BEC_2_5_4_LogicBool*>(BECS_Runtime::boolFalse);
return beq->bevt_0_ta_ph;
}
BEC_2_5_4_LogicBool* BEC_2_4_3_MathInt::bem_notEquals_1(BEC_2_6_6_SystemObject* bevk_xi) {
struct bes { BEC_2_6_6_SystemObject* beva_xi; BEC_2_5_4_LogicBool* bevt_0_ta_ph; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->beva_xi = bevk_xi;
beq->bevt_0_ta_ph = nullptr;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(3);

#ifndef BEDCC_NORTTI
      BEC_2_4_3_MathInt* bevls_xi = dynamic_cast<BEC_2_4_3_MathInt*>(beq->beva_xi);
#endif
#ifdef BEDCC_NORTTI
      BEC_2_4_3_MathInt* bevls_xi = static_cast<BEC_2_4_3_MathInt*>(beq->beva_xi);
#endif
      if (bevi_int != bevls_xi ->bevi_int) {
        return BECS_Runtime::boolTrue;
      }
      beq->bevt_0_ta_ph = static_cast<BEC_2_5_4_LogicBool*>(BECS_Runtime::boolFalse);
return beq->bevt_0_ta_ph;
}
BEC_2_5_4_LogicBool* BEC_2_4_3_MathInt::bem_greater_1(BEC_2_4_3_MathInt* bevk_xi) {
struct bes { BEC_2_4_3_MathInt* beva_xi; BEC_2_5_4_LogicBool* bevt_0_ta_ph; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->beva_xi = bevk_xi;
beq->bevt_0_ta_ph = nullptr;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(3);

      if (bevi_int > beq->beva_xi->bevi_int) {
        return BECS_Runtime::boolTrue;
      }
      beq->bevt_0_ta_ph = static_cast<BEC_2_5_4_LogicBool*>(BECS_Runtime::boolFalse);
return beq->bevt_0_ta_ph;
}
BEC_2_5_4_LogicBool* BEC_2_4_3_MathInt::bem_lesser_1(BEC_2_4_3_MathInt* bevk_xi) {
struct bes { BEC_2_4_3_MathInt* beva_xi; BEC_2_5_4_LogicBool* bevt_0_ta_ph; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->beva_xi = bevk_xi;
beq->bevt_0_ta_ph = nullptr;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(3);

      if (bevi_int < beq->beva_xi->bevi_int) {
        return BECS_Runtime::boolTrue;
      }
      beq->bevt_0_ta_ph = static_cast<BEC_2_5_4_LogicBool*>(BECS_Runtime::boolFalse);
return beq->bevt_0_ta_ph;
}
BEC_2_5_4_LogicBool* BEC_2_4_3_MathInt::bem_greaterEquals_1(BEC_2_4_3_MathInt* bevk_xi) {
struct bes { BEC_2_4_3_MathInt* beva_xi; BEC_2_5_4_LogicBool* bevt_0_ta_ph; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->beva_xi = bevk_xi;
beq->bevt_0_ta_ph = nullptr;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(3);

      if (bevi_int >= beq->beva_xi->bevi_int) {
        return BECS_Runtime::boolTrue;
      }
      beq->bevt_0_ta_ph = static_cast<BEC_2_5_4_LogicBool*>(BECS_Runtime::boolFalse);
return beq->bevt_0_ta_ph;
}
BEC_2_5_4_LogicBool* BEC_2_4_3_MathInt::bem_lesserEquals_1(BEC_2_4_3_MathInt* bevk_xi) {
struct bes { BEC_2_4_3_MathInt* beva_xi; BEC_2_5_4_LogicBool* bevt_0_ta_ph; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->beva_xi = bevk_xi;
beq->bevt_0_ta_ph = nullptr;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(3);

      if (bevi_int <= beq->beva_xi->bevi_int) {
        return BECS_Runtime::boolTrue;
      }
      beq->bevt_0_ta_ph = static_cast<BEC_2_5_4_LogicBool*>(BECS_Runtime::boolFalse);
return beq->bevt_0_ta_ph;
}
BEC_2_6_6_SystemObject* BEC_2_4_3_MathInt::bemd_0(int32_t callId) {
switch (callId) {
case -1553512291: return bem_toString_0();
case 1312387167: return bem_create_0();
case 1564564681: return bem_vintSet_0();
case 2142500088: return bem_copy_0();
case 1003273574: return bem_decrement_0();
case 1889303852: return bem_vintGet_0();
case 995602520: return bem_abs_0();
case 2127377985: return bem_decrementValue_0();
case -534328503: return bem_serializeContentsGet_0();
case 950712084: return bem_serializeToString_0();
case 465886877: return bem_incrementValue_0();
case -1785532669: return bem_new_0();
case 1712544865: return bem_toHexString_0();
case 25638260: return bem_increment_0();
case -1677156504: return bem_hashGet_0();
case 818264171: return bem_absValue_0();
}
return bevs_super::bemd_0(callId);
}
BEC_2_6_6_SystemObject* BEC_2_4_3_MathInt::bemd_1(int32_t callId, BEC_2_6_6_SystemObject* bevd_0) {
switch (callId) {
case -188417492: return bem_shiftRight_1(static_cast<BEC_2_4_3_MathInt*>(bevd_0));
case 1325848887: return bem_addValue_1(static_cast<BEC_2_4_3_MathInt*>(bevd_0));
case -1156975652: return bem_subtract_1(static_cast<BEC_2_4_3_MathInt*>(bevd_0));
case 834681409: return bem_greaterEquals_1(static_cast<BEC_2_4_3_MathInt*>(bevd_0));
case -1772423088: return bem_shiftLeftValue_1(static_cast<BEC_2_4_3_MathInt*>(bevd_0));
case 368955507: return bem_toHexString_1(static_cast<BEC_2_4_6_TextString*>(bevd_0));
case 202420412: return bem_add_1(static_cast<BEC_2_4_3_MathInt*>(bevd_0));
case 1911891644: return bem_lesser_1(static_cast<BEC_2_4_3_MathInt*>(bevd_0));
case 482404416: return bem_divide_1(static_cast<BEC_2_4_3_MathInt*>(bevd_0));
case 845322277: return bem_modulus_1(static_cast<BEC_2_4_3_MathInt*>(bevd_0));
case -901039784: return bem_setStringValueDec_1(static_cast<BEC_2_4_6_TextString*>(bevd_0));
case 43079495: return bem_power_1(static_cast<BEC_2_4_3_MathInt*>(bevd_0));
case 850171568: return bem_modulusValue_1(static_cast<BEC_2_4_3_MathInt*>(bevd_0));
case -1290749461: return bem_setValue_1(static_cast<BEC_2_4_3_MathInt*>(bevd_0));
case -1198675849: return bem_shiftLeft_1(static_cast<BEC_2_4_3_MathInt*>(bevd_0));
case -81346366: return bem_or_1(static_cast<BEC_2_4_3_MathInt*>(bevd_0));
case -1473213502: return bem_multiply_1(static_cast<BEC_2_4_3_MathInt*>(bevd_0));
case 964997039: return bem_lesserEquals_1(static_cast<BEC_2_4_3_MathInt*>(bevd_0));
case 1854297838: return bem_divideValue_1(static_cast<BEC_2_4_3_MathInt*>(bevd_0));
case 1055530813: return bem_andValue_1(static_cast<BEC_2_4_3_MathInt*>(bevd_0));
case 643138569: return bem_equals_1(bevd_0);
case 1899676304: return bem_new_1(bevd_0);
case 1358779174: return bem_and_1(static_cast<BEC_2_4_3_MathInt*>(bevd_0));
case 1039122802: return bem_notEquals_1(bevd_0);
case 1479971157: return bem_shiftRightValue_1(static_cast<BEC_2_4_3_MathInt*>(bevd_0));
case -393938669: return bem_setStringValueHex_1(static_cast<BEC_2_4_6_TextString*>(bevd_0));
case -206108566: return bem_greater_1(static_cast<BEC_2_4_3_MathInt*>(bevd_0));
case 244719229: return bem_multiplyValue_1(static_cast<BEC_2_4_3_MathInt*>(bevd_0));
case -1387495415: return bem_orValue_1(static_cast<BEC_2_4_3_MathInt*>(bevd_0));
case 1174166648: return bem_subtractValue_1(static_cast<BEC_2_4_3_MathInt*>(bevd_0));
case -1618488206: return bem_deserializeFromStringNew_1(static_cast<BEC_2_4_6_TextString*>(bevd_0));
case 639868603: return bem_hexNew_1(static_cast<BEC_2_4_6_TextString*>(bevd_0));
}
return bevs_super::bemd_1(callId, bevd_0);
}
BEC_2_6_6_SystemObject* BEC_2_4_3_MathInt::bemd_2(int32_t callId, BEC_2_6_6_SystemObject* bevd_0, BEC_2_6_6_SystemObject* bevd_1) {
switch (callId) {
case 1212035225: return bem_toString_2(static_cast<BEC_2_4_3_MathInt*>(bevd_0), static_cast<BEC_2_4_3_MathInt*>(bevd_1));
case -1713935397: return bem_setStringValue_2(static_cast<BEC_2_4_6_TextString*>(bevd_0), static_cast<BEC_2_4_3_MathInt*>(bevd_1));
}
return bevs_super::bemd_2(callId, bevd_0, bevd_1);
}
BEC_2_6_6_SystemObject* BEC_2_4_3_MathInt::bemd_3(int32_t callId, BEC_2_6_6_SystemObject* bevd_0, BEC_2_6_6_SystemObject* bevd_1, BEC_2_6_6_SystemObject* bevd_2) {
switch (callId) {
case 1724749452: return bem_toString_3(static_cast<BEC_2_4_6_TextString*>(bevd_0), static_cast<BEC_2_4_3_MathInt*>(bevd_1), static_cast<BEC_2_4_3_MathInt*>(bevd_2));
}
return bevs_super::bemd_3(callId, bevd_0, bevd_1, bevd_2);
}
BEC_2_6_6_SystemObject* BEC_2_4_3_MathInt::bemd_4(int32_t callId, BEC_2_6_6_SystemObject* bevd_0, BEC_2_6_6_SystemObject* bevd_1, BEC_2_6_6_SystemObject* bevd_2, BEC_2_6_6_SystemObject* bevd_3) {
switch (callId) {
case -1943262120: return bem_toString_4(static_cast<BEC_2_4_6_TextString*>(bevd_0), static_cast<BEC_2_4_3_MathInt*>(bevd_1), static_cast<BEC_2_4_3_MathInt*>(bevd_2), static_cast<BEC_2_4_3_MathInt*>(bevd_3));
}
return bevs_super::bemd_4(callId, bevd_0, bevd_1, bevd_2, bevd_3);
}
BEC_2_6_6_SystemObject* BEC_2_4_3_MathInt::bemd_5(int32_t callId, BEC_2_6_6_SystemObject* bevd_0, BEC_2_6_6_SystemObject* bevd_1, BEC_2_6_6_SystemObject* bevd_2, BEC_2_6_6_SystemObject* bevd_3, BEC_2_6_6_SystemObject* bevd_4) {
switch (callId) {
case 2030762520: return bem_setStringValue_5(static_cast<BEC_2_4_6_TextString*>(bevd_0), static_cast<BEC_2_4_3_MathInt*>(bevd_1), static_cast<BEC_2_4_3_MathInt*>(bevd_2), static_cast<BEC_2_4_3_MathInt*>(bevd_3), static_cast<BEC_2_4_3_MathInt*>(bevd_4));
}
return bevs_super::bemd_5(callId, bevd_0, bevd_1, bevd_2, bevd_3, bevd_4);
}
BEC_2_6_6_SystemObject* BEC_2_4_3_MathInt::bemc_create() {
return new BEC_2_4_3_MathInt();
}
void BEC_2_4_3_MathInt::bemc_setInitial(BEC_2_6_6_SystemObject* becc_inst) {
BEC_2_4_3_MathInt::bece_BEC_2_4_3_MathInt_bevs_inst = static_cast<BEC_2_4_3_MathInt*>(becc_inst);
}
BEC_2_6_6_SystemObject* BEC_2_4_3_MathInt::bemc_getInitial() {
return BEC_2_4_3_MathInt::bece_BEC_2_4_3_MathInt_bevs_inst;
}
void BEC_2_4_3_MathInt::bemg_doMark() {
bevg_gcMark = BECS_Runtime::bevg_currentGcMark;
}
size_t BEC_2_4_3_MathInt::bemg_getSize() {
return sizeof(*this);
}
BETS_Object* BEC_2_4_3_MathInt::bemc_getType() {
return &BEC_2_4_3_MathInt::bece_BEC_2_4_3_MathInt_bevs_type;
}
BET_2_4_4_MathInts::BET_2_4_4_MathInts() {
std::vector<std::string> bevs_mtnames = {  };
bevs_fieldNames = {  };
}
BEC_2_6_6_SystemObject* BET_2_4_4_MathInts::bems_createInstance() {
return new BEC_2_4_4_MathInts();
}
void BET_2_4_4_MathInts::bemgt_doMark() {
BEC_2_6_6_SystemObject* bevsl_inst_ref = *bevs_inst_ref;
if (bevsl_inst_ref != nullptr && bevsl_inst_ref->bevg_gcMark != BECS_Runtime::bevg_currentGcMark) {
bevsl_inst_ref->bemg_doMark();
}
}
BEC_2_4_4_MathInts* BEC_2_4_4_MathInts::bece_BEC_2_4_4_MathInts_bevs_inst;

BET_2_4_4_MathInts BEC_2_4_4_MathInts::bece_BEC_2_4_4_MathInts_bevs_type;
BEC_2_6_6_SystemObject** BET_2_4_4_MathInts::bevs_inst_ref = (BEC_2_6_6_SystemObject**) &BEC_2_4_4_MathInts::bece_BEC_2_4_4_MathInts_bevs_inst;

BEC_2_6_6_SystemObject* BEC_2_4_4_MathInts::bem_create_0() {
struct bes {  BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(1);
return this;
}
BEC_2_4_4_MathInts* BEC_2_4_4_MathInts::bem_default_0() {
struct bes { BEC_2_4_3_MathInt* bevl__max; BEC_2_4_3_MathInt* bevl__min; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->bevl__max = nullptr;
beq->bevl__min = nullptr;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(3);
beq->bevl__max = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt())));
beq->bevl__min = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt())));

      beq->bevl__max->bevi_int = std::numeric_limits<int32_t>::max();
      beq->bevl__min->bevi_int = std::numeric_limits<int32_t>::min();
      bevp_max = beq->bevl__max;
bevp_min = beq->bevl__min;
bevp_zero = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(0))));
bevp_one = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(1))));
return this;
}
BEC_2_6_6_SystemObject* BEC_2_4_4_MathInts::bem_min_2(BEC_2_4_3_MathInt* bevk_a, BEC_2_4_3_MathInt* bevk_b) {
struct bes { BEC_2_4_3_MathInt* beva_a; BEC_2_4_3_MathInt* beva_b; BEC_2_5_4_LogicBool* bevt_0_ta_anchor; BEC_2_5_4_LogicBool* bevt_1_ta_ph; BEC_2_5_4_LogicBool* bevt_2_ta_ph; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->beva_a = bevk_a;
beq->beva_b = bevk_b;
beq->bevt_0_ta_anchor = nullptr;
beq->bevt_1_ta_ph = nullptr;
beq->bevt_2_ta_ph = nullptr;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(6);
if (beq->beva_a == nullptr) {
beq->bevt_1_ta_ph = BECS_Runtime::boolTrue;
 } else { 
beq->bevt_1_ta_ph = BECS_Runtime::boolFalse;
}
if (beq->bevt_1_ta_ph->bevi_bool) {
beq->bevt_0_ta_anchor = BECS_Runtime::boolTrue;
} 
 else  {
if (beq->beva_a->bevi_int < beq->beva_b->bevi_int) {
beq->bevt_2_ta_ph = BECS_Runtime::boolTrue;
 } else { 
beq->bevt_2_ta_ph = BECS_Runtime::boolFalse;
}
if (beq->bevt_2_ta_ph->bevi_bool) {
beq->bevt_0_ta_anchor = BECS_Runtime::boolTrue;
} 
 else  {
beq->bevt_0_ta_anchor = BECS_Runtime::boolFalse;
} 
} 
if (beq->bevt_0_ta_anchor->bevi_bool) {
return beq->beva_a;
} 
return beq->beva_b;
}
BEC_2_6_6_SystemObject* BEC_2_4_4_MathInts::bem_max_2(BEC_2_4_3_MathInt* bevk_a, BEC_2_4_3_MathInt* bevk_b) {
struct bes { BEC_2_4_3_MathInt* beva_a; BEC_2_4_3_MathInt* beva_b; BEC_2_5_4_LogicBool* bevt_0_ta_anchor; BEC_2_5_4_LogicBool* bevt_1_ta_ph; BEC_2_5_4_LogicBool* bevt_2_ta_ph; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->beva_a = bevk_a;
beq->beva_b = bevk_b;
beq->bevt_0_ta_anchor = nullptr;
beq->bevt_1_ta_ph = nullptr;
beq->bevt_2_ta_ph = nullptr;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(6);
if (beq->beva_a == nullptr) {
beq->bevt_1_ta_ph = BECS_Runtime::boolTrue;
 } else { 
beq->bevt_1_ta_ph = BECS_Runtime::boolFalse;
}
if (beq->bevt_1_ta_ph->bevi_bool) {
beq->bevt_0_ta_anchor = BECS_Runtime::boolTrue;
} 
 else  {
if (beq->beva_a->bevi_int > beq->beva_b->bevi_int) {
beq->bevt_2_ta_ph = BECS_Runtime::boolTrue;
 } else { 
beq->bevt_2_ta_ph = BECS_Runtime::boolFalse;
}
if (beq->bevt_2_ta_ph->bevi_bool) {
beq->bevt_0_ta_anchor = BECS_Runtime::boolTrue;
} 
 else  {
beq->bevt_0_ta_anchor = BECS_Runtime::boolFalse;
} 
} 
if (beq->bevt_0_ta_anchor->bevi_bool) {
return beq->beva_a;
} 
return beq->beva_b;
}
BEC_2_4_3_MathInt* BEC_2_4_4_MathInts::bem_maxGet_0() {
struct bes {  BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(1);
return bevp_max;
}
BEC_2_4_4_MathInts* BEC_2_4_4_MathInts::bem_maxSet_1(BEC_2_6_6_SystemObject* bevt_0_ta_SET) {
struct bes { BEC_2_6_6_SystemObject* bevt_0_ta_SET; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->bevt_0_ta_SET = bevt_0_ta_SET;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(2);
bevp_max = static_cast<BEC_2_4_3_MathInt*>(beq->bevt_0_ta_SET);
return this;
}
BEC_2_4_3_MathInt* BEC_2_4_4_MathInts::bem_minGet_0() {
struct bes {  BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(1);
return bevp_min;
}
BEC_2_4_4_MathInts* BEC_2_4_4_MathInts::bem_minSet_1(BEC_2_6_6_SystemObject* bevt_0_ta_SET) {
struct bes { BEC_2_6_6_SystemObject* bevt_0_ta_SET; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->bevt_0_ta_SET = bevt_0_ta_SET;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(2);
bevp_min = static_cast<BEC_2_4_3_MathInt*>(beq->bevt_0_ta_SET);
return this;
}
BEC_2_4_3_MathInt* BEC_2_4_4_MathInts::bem_zeroGet_0() {
struct bes {  BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(1);
return bevp_zero;
}
BEC_2_4_4_MathInts* BEC_2_4_4_MathInts::bem_zeroSet_1(BEC_2_6_6_SystemObject* bevt_0_ta_SET) {
struct bes { BEC_2_6_6_SystemObject* bevt_0_ta_SET; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->bevt_0_ta_SET = bevt_0_ta_SET;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(2);
bevp_zero = static_cast<BEC_2_4_3_MathInt*>(beq->bevt_0_ta_SET);
return this;
}
BEC_2_4_3_MathInt* BEC_2_4_4_MathInts::bem_oneGet_0() {
struct bes {  BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(1);
return bevp_one;
}
BEC_2_4_4_MathInts* BEC_2_4_4_MathInts::bem_oneSet_1(BEC_2_6_6_SystemObject* bevt_0_ta_SET) {
struct bes { BEC_2_6_6_SystemObject* bevt_0_ta_SET; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->bevt_0_ta_SET = bevt_0_ta_SET;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(2);
bevp_one = static_cast<BEC_2_4_3_MathInt*>(beq->bevt_0_ta_SET);
return this;
}
BEC_2_6_6_SystemObject* BEC_2_4_4_MathInts::bemd_0(int32_t callId) {
switch (callId) {
case 1558451664: return bem_oneGet_0();
case 1312387167: return bem_create_0();
case 363757507: return bem_zeroGet_0();
case 1188815194: return bem_default_0();
case -221922676: return bem_maxGet_0();
case -1580235215: return bem_minGet_0();
}
return bevs_super::bemd_0(callId);
}
BEC_2_6_6_SystemObject* BEC_2_4_4_MathInts::bemd_1(int32_t callId, BEC_2_6_6_SystemObject* bevd_0) {
switch (callId) {
case 1264572243: return bem_minSet_1(bevd_0);
case 593309101: return bem_zeroSet_1(bevd_0);
case -1238641604: return bem_maxSet_1(bevd_0);
case 1576645321: return bem_oneSet_1(bevd_0);
}
return bevs_super::bemd_1(callId, bevd_0);
}
BEC_2_6_6_SystemObject* BEC_2_4_4_MathInts::bemd_2(int32_t callId, BEC_2_6_6_SystemObject* bevd_0, BEC_2_6_6_SystemObject* bevd_1) {
switch (callId) {
case 1456597236: return bem_min_2(static_cast<BEC_2_4_3_MathInt*>(bevd_0), static_cast<BEC_2_4_3_MathInt*>(bevd_1));
case 1532460192: return bem_max_2(static_cast<BEC_2_4_3_MathInt*>(bevd_0), static_cast<BEC_2_4_3_MathInt*>(bevd_1));
}
return bevs_super::bemd_2(callId, bevd_0, bevd_1);
}
BEC_2_6_6_SystemObject* BEC_2_4_4_MathInts::bemc_create() {
return new BEC_2_4_4_MathInts();
}
void BEC_2_4_4_MathInts::bemc_setInitial(BEC_2_6_6_SystemObject* becc_inst) {
BEC_2_4_4_MathInts::bece_BEC_2_4_4_MathInts_bevs_inst = static_cast<BEC_2_4_4_MathInts*>(becc_inst);
}
BEC_2_6_6_SystemObject* BEC_2_4_4_MathInts::bemc_getInitial() {
return BEC_2_4_4_MathInts::bece_BEC_2_4_4_MathInts_bevs_inst;
}
void BEC_2_4_4_MathInts::bemg_doMark() {
bevg_gcMark = BECS_Runtime::bevg_currentGcMark;
if (bevp_max != nullptr && bevp_max->bevg_gcMark != BECS_Runtime::bevg_currentGcMark) {
bevp_max->bemg_doMark();
}
if (bevp_min != nullptr && bevp_min->bevg_gcMark != BECS_Runtime::bevg_currentGcMark) {
bevp_min->bemg_doMark();
}
if (bevp_zero != nullptr && bevp_zero->bevg_gcMark != BECS_Runtime::bevg_currentGcMark) {
bevp_zero->bemg_doMark();
}
if (bevp_one != nullptr && bevp_one->bevg_gcMark != BECS_Runtime::bevg_currentGcMark) {
bevp_one->bemg_doMark();
}
}
size_t BEC_2_4_4_MathInts::bemg_getSize() {
return sizeof(*this);
}
BETS_Object* BEC_2_4_4_MathInts::bemc_getType() {
return &BEC_2_4_4_MathInts::bece_BEC_2_4_4_MathInts_bevs_type;
}
BET_2_4_6_TextString::BET_2_4_6_TextString() {
std::vector<std::string> bevs_mtnames = {  };
bevs_fieldNames = {  };
}
BEC_2_6_6_SystemObject* BET_2_4_6_TextString::bems_createInstance() {
return new BEC_2_4_6_TextString();
}
void BET_2_4_6_TextString::bemgt_doMark() {
BEC_2_6_6_SystemObject* bevsl_inst_ref = *bevs_inst_ref;
if (bevsl_inst_ref != nullptr && bevsl_inst_ref->bevg_gcMark != BECS_Runtime::bevg_currentGcMark) {
bevsl_inst_ref->bemg_doMark();
}
}

   std::string BEC_2_4_6_TextString::bems_toCcString() {
      std::string ccString(bevi_bytes.begin(), bevi_bytes.end());
      ccString.resize(bevp_size->bevi_int);
      return ccString;
    }

   char* BEC_2_4_6_TextString::bems_c_str(char* buf, int mxlen) {
      int i = 0;

      for (i = 0;i < bevp_size->bevi_int && i < mxlen;i++) {
         buf[i] = (char) bevi_bytes[i];
      }
      buf[i] = '\0';

      return(buf);
   }

   BEC_2_4_6_TextString* BEC_2_4_6_TextString::bece_BEC_2_4_6_TextString_bevs_inst;

BET_2_4_6_TextString BEC_2_4_6_TextString::bece_BEC_2_4_6_TextString_bevs_type;
BEC_2_6_6_SystemObject** BET_2_4_6_TextString::bevs_inst_ref = (BEC_2_6_6_SystemObject**) &BEC_2_4_6_TextString::bece_BEC_2_4_6_TextString_bevs_inst;

BEC_2_4_6_TextString* BEC_2_4_6_TextString::bem_vstringGet_0() {
struct bes {  BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(1);
return this;
}
BEC_2_4_6_TextString* BEC_2_4_6_TextString::bem_vstringSet_0() {
struct bes {  BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(1);
return this;
}
BEC_2_4_6_TextString* BEC_2_4_6_TextString::bem_new_1(BEC_2_4_3_MathInt* bevk__capacity) {
struct bes { BEC_2_4_3_MathInt* beva__capacity; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->beva__capacity = bevk__capacity;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(2);
bevp_size = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(0))));
bem_capacitySet_1(beq->beva__capacity);
return this;
}
BEC_2_6_6_SystemObject* BEC_2_4_6_TextString::bem_new_0() {
struct bes { BEC_2_4_3_MathInt* bevt_0_ta_ph; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->bevt_0_ta_ph = nullptr;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(2);
beq->bevt_0_ta_ph = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(0))));
bem_new_1(beq->bevt_0_ta_ph);
return this;
}
BEC_2_4_6_TextString* BEC_2_4_6_TextString::bem_capacitySet_1(BEC_2_4_3_MathInt* bevk_ncap) {
struct bes { BEC_2_4_3_MathInt* beva_ncap; BEC_2_5_4_LogicBool* bevt_0_ta_ph; BEC_2_5_4_LogicBool* bevt_1_ta_ph; BEC_2_5_4_LogicBool* bevt_2_ta_ph; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->beva_ncap = bevk_ncap;
beq->bevt_0_ta_ph = nullptr;
beq->bevt_1_ta_ph = nullptr;
beq->bevt_2_ta_ph = nullptr;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(5);
if (bevp_capacity == nullptr) {
beq->bevt_0_ta_ph = BECS_Runtime::boolTrue;
 } else { 
beq->bevt_0_ta_ph = BECS_Runtime::boolFalse;
}
if (beq->bevt_0_ta_ph->bevi_bool) {
bevp_capacity = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(0))));
} 
 else  {
if (bevp_capacity->bevi_int == beq->beva_ncap->bevi_int) {
beq->bevt_1_ta_ph = BECS_Runtime::boolTrue;
 } else { 
beq->bevt_1_ta_ph = BECS_Runtime::boolFalse;
}
if (beq->bevt_1_ta_ph->bevi_bool) {
return this;
} 
} 

        bevi_bytes.resize(beq->beva_ncap->bevi_int, 0);
      if (bevp_size->bevi_int > beq->beva_ncap->bevi_int) {
beq->bevt_2_ta_ph = BECS_Runtime::boolTrue;
 } else { 
beq->bevt_2_ta_ph = BECS_Runtime::boolFalse;
}
if (beq->bevt_2_ta_ph->bevi_bool) {
bevp_size->bevi_int = beq->beva_ncap->bevi_int;
} 
bevp_capacity->bevi_int = beq->beva_ncap->bevi_int;
return this;
}
BEC_2_4_6_TextString* BEC_2_4_6_TextString::bem_hexNew_1(BEC_2_4_6_TextString* bevk_val) {
struct bes { BEC_2_4_6_TextString* beva_val; BEC_2_4_3_MathInt* bevt_0_ta_ph; BEC_2_4_3_MathInt* bevt_1_ta_ph; BEC_2_4_3_MathInt* bevt_2_ta_ph; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->beva_val = bevk_val;
beq->bevt_0_ta_ph = nullptr;
beq->bevt_1_ta_ph = nullptr;
beq->bevt_2_ta_ph = nullptr;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(5);
beq->bevt_0_ta_ph = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(1))));
bem_new_1(beq->bevt_0_ta_ph);
beq->bevt_1_ta_ph = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(1))));
bevp_size->bevi_int = beq->bevt_1_ta_ph->bevi_int;
beq->bevt_2_ta_ph = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(0))));
bem_setHex_2(beq->bevt_2_ta_ph, beq->beva_val);
return this;
}
BEC_2_4_6_TextString* BEC_2_4_6_TextString::bem_getHex_1(BEC_2_4_3_MathInt* bevk_pos) {
struct bes { BEC_2_4_3_MathInt* beva_pos; BEC_2_4_6_TextString* bevt_0_ta_ph; BEC_2_4_3_MathInt* bevt_1_ta_ph; BEC_2_4_3_MathInt* bevt_2_ta_ph; BEC_2_4_6_TextString* bevt_3_ta_ph; BEC_2_4_3_MathInt* bevt_4_ta_ph; BEC_2_4_3_MathInt* bevt_5_ta_ph; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->beva_pos = bevk_pos;
beq->bevt_0_ta_ph = nullptr;
beq->bevt_1_ta_ph = nullptr;
beq->bevt_2_ta_ph = nullptr;
beq->bevt_3_ta_ph = nullptr;
beq->bevt_4_ta_ph = nullptr;
beq->bevt_5_ta_ph = nullptr;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(8);
beq->bevt_2_ta_ph = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt())));
beq->bevt_1_ta_ph = bem_getCode_2(beq->beva_pos, beq->bevt_2_ta_ph);
beq->bevt_3_ta_ph = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString()))->bem_new_0());
beq->bevt_4_ta_ph = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(2))));
beq->bevt_5_ta_ph = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(16))));
beq->bevt_0_ta_ph = beq->bevt_1_ta_ph->bem_toString_3(beq->bevt_3_ta_ph, beq->bevt_4_ta_ph, beq->bevt_5_ta_ph);
return beq->bevt_0_ta_ph;
}
BEC_2_4_6_TextString* BEC_2_4_6_TextString::bem_setHex_2(BEC_2_4_3_MathInt* bevk_pos, BEC_2_4_6_TextString* bevk_hval) {
struct bes { BEC_2_4_3_MathInt* beva_pos; BEC_2_4_6_TextString* beva_hval; BEC_2_4_3_MathInt* bevl_val; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->beva_pos = bevk_pos;
beq->beva_hval = bevk_hval;
beq->bevl_val = nullptr;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(4);
beq->bevl_val = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt()))->bem_hexNew_1(beq->beva_hval));
bem_setCode_2(beq->beva_pos, beq->bevl_val);
return this;
}
BEC_2_4_6_TextString* BEC_2_4_6_TextString::bem_addValue_1(BEC_2_6_6_SystemObject* bevk_astr) {
struct bes { BEC_2_6_6_SystemObject* beva_astr; BEC_2_4_6_TextString* bevl_str; BEC_2_4_3_MathInt* bevl_sizi; BEC_2_4_3_MathInt* bevl_nsize; BEC_2_4_3_MathInt* bevt_0_ta_ph; BEC_2_5_4_LogicBool* bevt_1_ta_ph; BEC_2_4_3_MathInt* bevt_2_ta_ph; BEC_2_4_3_MathInt* bevt_3_ta_ph; BEC_2_4_3_MathInt* bevt_4_ta_ph; BEC_2_4_3_MathInt* bevt_5_ta_ph; BEC_2_4_3_MathInt* bevt_6_ta_ph; BEC_2_4_3_MathInt* bevt_7_ta_ph; BEC_2_4_7_TextStrings* bevt_8_ta_ph; BEC_2_4_3_MathInt* bevt_9_ta_ph; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->beva_astr = bevk_astr;
beq->bevl_str = nullptr;
beq->bevl_sizi = nullptr;
beq->bevl_nsize = nullptr;
beq->bevt_0_ta_ph = nullptr;
beq->bevt_1_ta_ph = nullptr;
beq->bevt_2_ta_ph = nullptr;
beq->bevt_3_ta_ph = nullptr;
beq->bevt_4_ta_ph = nullptr;
beq->bevt_5_ta_ph = nullptr;
beq->bevt_6_ta_ph = nullptr;
beq->bevt_7_ta_ph = nullptr;
beq->bevt_8_ta_ph = nullptr;
beq->bevt_9_ta_ph = nullptr;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(15);
beq->bevl_str = static_cast<BEC_2_4_6_TextString*>(beq->beva_astr->bemd_0(-1553512291));
beq->bevl_sizi = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt())));
beq->bevt_0_ta_ph = beq->bevl_str->bem_sizeGet_0();
beq->bevl_sizi->bevi_int = beq->bevt_0_ta_ph->bevi_int;
beq->bevl_sizi->bevi_int += bevp_size->bevi_int;
if (bevp_capacity->bevi_int < beq->bevl_sizi->bevi_int) {
beq->bevt_1_ta_ph = BECS_Runtime::boolTrue;
 } else { 
beq->bevt_1_ta_ph = BECS_Runtime::boolFalse;
}
if (beq->bevt_1_ta_ph->bevi_bool) {
beq->bevt_4_ta_ph = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(16))));
beq->bevt_3_ta_ph = beq->bevl_sizi->bem_add_1(beq->bevt_4_ta_ph);
beq->bevt_5_ta_ph = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(3))));
beq->bevt_2_ta_ph = beq->bevt_3_ta_ph->bem_multiply_1(beq->bevt_5_ta_ph);
beq->bevt_6_ta_ph = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(2))));
beq->bevl_nsize = beq->bevt_2_ta_ph->bem_divide_1(beq->bevt_6_ta_ph);
bem_capacitySet_1(beq->bevl_nsize);
} 
beq->bevt_8_ta_ph = static_cast<BEC_2_4_7_TextStrings*>(BEC_2_4_7_TextStrings::bece_BEC_2_4_7_TextStrings_bevs_inst);
beq->bevt_7_ta_ph = beq->bevt_8_ta_ph->bem_zeroGet_0();
beq->bevt_9_ta_ph = beq->bevl_str->bem_sizeGet_0();
bem_copyValue_4(beq->bevl_str, beq->bevt_7_ta_ph, beq->bevt_9_ta_ph, bevp_size);
return this;
}
BEC_2_4_6_TextString* BEC_2_4_6_TextString::bem_readBuffer_0() {
struct bes {  BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(1);
return this;
}
BEC_2_4_6_TextString* BEC_2_4_6_TextString::bem_readString_0() {
struct bes {  BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(1);
return this;
}
BEC_2_4_6_TextString* BEC_2_4_6_TextString::bem_write_1(BEC_2_6_6_SystemObject* bevk_stri) {
struct bes { BEC_2_6_6_SystemObject* beva_stri; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->beva_stri = bevk_stri;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(2);
bem_addValue_1(beq->beva_stri);
return this;
}
BEC_2_4_6_TextString* BEC_2_4_6_TextString::bem_writeTo_1(BEC_2_6_6_SystemObject* bevk_w) {
struct bes { BEC_2_6_6_SystemObject* beva_w; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->beva_w = bevk_w;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(2);
beq->beva_w->bemd_1(1129103463, this);
return this;
}
BEC_2_4_6_TextString* BEC_2_4_6_TextString::bem_open_0() {
struct bes {  BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(1);
return this;
}
BEC_2_4_6_TextString* BEC_2_4_6_TextString::bem_close_0() {
struct bes {  BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(1);
return this;
}
BEC_2_4_6_TextString* BEC_2_4_6_TextString::bem_extractString_0() {
struct bes { BEC_2_4_6_TextString* bevl_str; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->bevl_str = nullptr;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(2);
beq->bevl_str = static_cast<BEC_2_4_6_TextString*>(bem_copy_0());
bem_clear_0();
return beq->bevl_str;
}
BEC_2_4_6_TextString* BEC_2_4_6_TextString::bem_clear_0() {
struct bes { BEC_2_5_4_LogicBool* bevt_0_ta_ph; BEC_2_4_3_MathInt* bevt_1_ta_ph; BEC_2_4_3_MathInt* bevt_2_ta_ph; BEC_2_4_3_MathInt* bevt_3_ta_ph; BEC_2_4_3_MathInt* bevt_4_ta_ph; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->bevt_0_ta_ph = nullptr;
beq->bevt_1_ta_ph = nullptr;
beq->bevt_2_ta_ph = nullptr;
beq->bevt_3_ta_ph = nullptr;
beq->bevt_4_ta_ph = nullptr;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(6);
beq->bevt_1_ta_ph = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(0))));
if (bevp_size->bevi_int > beq->bevt_1_ta_ph->bevi_int) {
beq->bevt_0_ta_ph = BECS_Runtime::boolTrue;
 } else { 
beq->bevt_0_ta_ph = BECS_Runtime::boolFalse;
}
if (beq->bevt_0_ta_ph->bevi_bool) {
beq->bevt_2_ta_ph = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(0))));
beq->bevt_3_ta_ph = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(0))));
bem_setIntUnchecked_2(beq->bevt_2_ta_ph, beq->bevt_3_ta_ph);
beq->bevt_4_ta_ph = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(0))));
bevp_size->bevi_int = beq->bevt_4_ta_ph->bevi_int;
} 
return this;
}
BEC_2_4_6_TextString* BEC_2_4_6_TextString::bem_codeNew_1(BEC_2_6_6_SystemObject* bevk_codei) {
struct bes { BEC_2_6_6_SystemObject* beva_codei; BEC_2_4_3_MathInt* bevt_0_ta_ph; BEC_2_4_3_MathInt* bevt_1_ta_ph; BEC_2_4_3_MathInt* bevt_2_ta_ph; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->beva_codei = bevk_codei;
beq->bevt_0_ta_ph = nullptr;
beq->bevt_1_ta_ph = nullptr;
beq->bevt_2_ta_ph = nullptr;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(5);
beq->bevt_0_ta_ph = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(1))));
bem_new_1(beq->bevt_0_ta_ph);
beq->bevt_1_ta_ph = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(1))));
bevp_size->bevi_int = beq->bevt_1_ta_ph->bevi_int;
beq->bevt_2_ta_ph = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(0))));
bem_setCodeUnchecked_2(beq->bevt_2_ta_ph, static_cast<BEC_2_4_3_MathInt*>(beq->beva_codei) );
return this;
}
BEC_2_4_6_TextString* BEC_2_4_6_TextString::bem_chomp_0() {
struct bes { BEC_2_4_6_TextString* bevl_nl; BEC_2_5_4_LogicBool* bevt_0_ta_ph; BEC_2_4_6_TextString* bevt_1_ta_ph; BEC_2_4_3_MathInt* bevt_2_ta_ph; BEC_2_4_3_MathInt* bevt_3_ta_ph; BEC_2_4_3_MathInt* bevt_4_ta_ph; BEC_2_5_4_LogicBool* bevt_5_ta_ph; BEC_2_4_6_TextString* bevt_6_ta_ph; BEC_2_4_3_MathInt* bevt_7_ta_ph; BEC_2_4_3_MathInt* bevt_8_ta_ph; BEC_2_4_3_MathInt* bevt_9_ta_ph; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->bevl_nl = nullptr;
beq->bevt_0_ta_ph = nullptr;
beq->bevt_1_ta_ph = nullptr;
beq->bevt_2_ta_ph = nullptr;
beq->bevt_3_ta_ph = nullptr;
beq->bevt_4_ta_ph = nullptr;
beq->bevt_5_ta_ph = nullptr;
beq->bevt_6_ta_ph = nullptr;
beq->bevt_7_ta_ph = nullptr;
beq->bevt_8_ta_ph = nullptr;
beq->bevt_9_ta_ph = nullptr;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(12);
beq->bevl_nl = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString(1, {0x0A}))));
beq->bevt_0_ta_ph = bem_ends_1(beq->bevl_nl);
if (beq->bevt_0_ta_ph->bevi_bool) {
beq->bevt_2_ta_ph = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(0))));
beq->bevt_4_ta_ph = beq->bevl_nl->bem_sizeGet_0();
beq->bevt_3_ta_ph = bevp_size->bem_subtract_1(beq->bevt_4_ta_ph);
beq->bevt_1_ta_ph = bem_substring_2(beq->bevt_2_ta_ph, beq->bevt_3_ta_ph);
return beq->bevt_1_ta_ph;
} 
beq->bevl_nl = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString(1, {0x0A}))));
beq->bevt_5_ta_ph = bem_ends_1(beq->bevl_nl);
if (beq->bevt_5_ta_ph->bevi_bool) {
beq->bevt_7_ta_ph = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(0))));
beq->bevt_9_ta_ph = beq->bevl_nl->bem_sizeGet_0();
beq->bevt_8_ta_ph = bevp_size->bem_subtract_1(beq->bevt_9_ta_ph);
beq->bevt_6_ta_ph = bem_substring_2(beq->bevt_7_ta_ph, beq->bevt_8_ta_ph);
return beq->bevt_6_ta_ph;
} 
return this;
}
BEC_2_6_6_SystemObject* BEC_2_4_6_TextString::bem_copy_0() {
struct bes { BEC_2_4_6_TextString* bevl_c; BEC_2_4_3_MathInt* bevt_0_ta_ph; BEC_2_4_3_MathInt* bevt_1_ta_ph; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->bevl_c = nullptr;
beq->bevt_0_ta_ph = nullptr;
beq->bevt_1_ta_ph = nullptr;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(4);
beq->bevt_1_ta_ph = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(1))));
beq->bevt_0_ta_ph = bevp_size->bem_add_1(beq->bevt_1_ta_ph);
beq->bevl_c = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString()))->bem_new_1(beq->bevt_0_ta_ph));
beq->bevl_c->bem_addValue_1(this);
return static_cast<BEC_2_6_6_SystemObject*>(beq->bevl_c);
}
BEC_2_5_4_LogicBool* BEC_2_4_6_TextString::bem_begins_1(BEC_2_4_6_TextString* bevk_str) {
struct bes { BEC_2_4_6_TextString* beva_str; BEC_2_4_3_MathInt* bevl_found; BEC_2_5_4_LogicBool* bevt_0_ta_anchor; BEC_2_5_4_LogicBool* bevt_1_ta_ph; BEC_2_5_4_LogicBool* bevt_2_ta_ph; BEC_2_4_3_MathInt* bevt_3_ta_ph; BEC_2_5_4_LogicBool* bevt_4_ta_ph; BEC_2_5_4_LogicBool* bevt_5_ta_ph; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->beva_str = bevk_str;
beq->bevl_found = nullptr;
beq->bevt_0_ta_anchor = nullptr;
beq->bevt_1_ta_ph = nullptr;
beq->bevt_2_ta_ph = nullptr;
beq->bevt_3_ta_ph = nullptr;
beq->bevt_4_ta_ph = nullptr;
beq->bevt_5_ta_ph = nullptr;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(9);
beq->bevl_found = bem_find_1(beq->beva_str);
if (beq->bevl_found == nullptr) {
beq->bevt_1_ta_ph = BECS_Runtime::boolTrue;
 } else { 
beq->bevt_1_ta_ph = BECS_Runtime::boolFalse;
}
if (beq->bevt_1_ta_ph->bevi_bool) {
beq->bevt_0_ta_anchor = BECS_Runtime::boolTrue;
} 
 else  {
beq->bevt_3_ta_ph = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(0))));
if (beq->bevl_found->bevi_int != beq->bevt_3_ta_ph->bevi_int) {
beq->bevt_2_ta_ph = BECS_Runtime::boolTrue;
 } else { 
beq->bevt_2_ta_ph = BECS_Runtime::boolFalse;
}
if (beq->bevt_2_ta_ph->bevi_bool) {
beq->bevt_0_ta_anchor = BECS_Runtime::boolTrue;
} 
 else  {
beq->bevt_0_ta_anchor = BECS_Runtime::boolFalse;
} 
} 
if (beq->bevt_0_ta_anchor->bevi_bool) {
beq->bevt_4_ta_ph = static_cast<BEC_2_5_4_LogicBool*>(BECS_Runtime::boolFalse);
return beq->bevt_4_ta_ph;
} 
beq->bevt_5_ta_ph = static_cast<BEC_2_5_4_LogicBool*>(BECS_Runtime::boolTrue);
return beq->bevt_5_ta_ph;
}
BEC_2_5_4_LogicBool* BEC_2_4_6_TextString::bem_ends_1(BEC_2_4_6_TextString* bevk_str) {
struct bes { BEC_2_4_6_TextString* beva_str; BEC_2_4_3_MathInt* bevl_found; BEC_2_5_4_LogicBool* bevt_0_ta_ph; BEC_2_5_4_LogicBool* bevt_1_ta_ph; BEC_2_4_3_MathInt* bevt_2_ta_ph; BEC_2_4_3_MathInt* bevt_3_ta_ph; BEC_2_5_4_LogicBool* bevt_4_ta_ph; BEC_2_5_4_LogicBool* bevt_5_ta_ph; BEC_2_5_4_LogicBool* bevt_6_ta_ph; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->beva_str = bevk_str;
beq->bevl_found = nullptr;
beq->bevt_0_ta_ph = nullptr;
beq->bevt_1_ta_ph = nullptr;
beq->bevt_2_ta_ph = nullptr;
beq->bevt_3_ta_ph = nullptr;
beq->bevt_4_ta_ph = nullptr;
beq->bevt_5_ta_ph = nullptr;
beq->bevt_6_ta_ph = nullptr;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(10);
if (beq->beva_str == nullptr) {
beq->bevt_0_ta_ph = BECS_Runtime::boolTrue;
 } else { 
beq->bevt_0_ta_ph = BECS_Runtime::boolFalse;
}
if (beq->bevt_0_ta_ph->bevi_bool) {
beq->bevt_1_ta_ph = static_cast<BEC_2_5_4_LogicBool*>(BECS_Runtime::boolFalse);
return beq->bevt_1_ta_ph;
} 
beq->bevt_3_ta_ph = beq->beva_str->bem_sizeGet_0();
beq->bevt_2_ta_ph = bevp_size->bem_subtract_1(beq->bevt_3_ta_ph);
beq->bevl_found = bem_find_2(beq->beva_str, beq->bevt_2_ta_ph);
if (beq->bevl_found == nullptr) {
beq->bevt_4_ta_ph = BECS_Runtime::boolTrue;
 } else { 
beq->bevt_4_ta_ph = BECS_Runtime::boolFalse;
}
if (beq->bevt_4_ta_ph->bevi_bool) {
beq->bevt_5_ta_ph = static_cast<BEC_2_5_4_LogicBool*>(BECS_Runtime::boolFalse);
return beq->bevt_5_ta_ph;
} 
beq->bevt_6_ta_ph = static_cast<BEC_2_5_4_LogicBool*>(BECS_Runtime::boolTrue);
return beq->bevt_6_ta_ph;
}
BEC_2_5_4_LogicBool* BEC_2_4_6_TextString::bem_has_1(BEC_2_4_6_TextString* bevk_str) {
struct bes { BEC_2_4_6_TextString* beva_str; BEC_2_5_4_LogicBool* bevt_0_ta_anchor; BEC_2_5_4_LogicBool* bevt_1_ta_ph; BEC_2_5_4_LogicBool* bevt_2_ta_ph; BEC_2_4_3_MathInt* bevt_3_ta_ph; BEC_2_5_4_LogicBool* bevt_4_ta_ph; BEC_2_5_4_LogicBool* bevt_5_ta_ph; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->beva_str = bevk_str;
beq->bevt_0_ta_anchor = nullptr;
beq->bevt_1_ta_ph = nullptr;
beq->bevt_2_ta_ph = nullptr;
beq->bevt_3_ta_ph = nullptr;
beq->bevt_4_ta_ph = nullptr;
beq->bevt_5_ta_ph = nullptr;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(8);
if (beq->beva_str == nullptr) {
beq->bevt_1_ta_ph = BECS_Runtime::boolTrue;
 } else { 
beq->bevt_1_ta_ph = BECS_Runtime::boolFalse;
}
if (beq->bevt_1_ta_ph->bevi_bool) {
beq->bevt_0_ta_anchor = BECS_Runtime::boolTrue;
} 
 else  {
beq->bevt_3_ta_ph = bem_find_1(beq->beva_str);
if (beq->bevt_3_ta_ph == nullptr) {
beq->bevt_2_ta_ph = BECS_Runtime::boolTrue;
 } else { 
beq->bevt_2_ta_ph = BECS_Runtime::boolFalse;
}
if (beq->bevt_2_ta_ph->bevi_bool) {
beq->bevt_0_ta_anchor = BECS_Runtime::boolTrue;
} 
 else  {
beq->bevt_0_ta_anchor = BECS_Runtime::boolFalse;
} 
} 
if (beq->bevt_0_ta_anchor->bevi_bool) {
beq->bevt_4_ta_ph = static_cast<BEC_2_5_4_LogicBool*>(BECS_Runtime::boolFalse);
return beq->bevt_4_ta_ph;
} 
beq->bevt_5_ta_ph = static_cast<BEC_2_5_4_LogicBool*>(BECS_Runtime::boolTrue);
return beq->bevt_5_ta_ph;
}
BEC_2_5_4_LogicBool* BEC_2_4_6_TextString::bem_isIntegerGet_0() {
struct bes { BEC_2_5_4_LogicBool* bevt_0_ta_ph; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->bevt_0_ta_ph = nullptr;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(2);
beq->bevt_0_ta_ph = bem_isInteger_0();
return beq->bevt_0_ta_ph;
}
BEC_2_5_4_LogicBool* BEC_2_4_6_TextString::bem_isInteger_0() {
struct bes { BEC_2_4_3_MathInt* bevl_ic; BEC_2_4_3_MathInt* bevl_j; BEC_2_5_4_LogicBool* bevt_0_ta_anchor; BEC_2_5_4_LogicBool* bevt_1_ta_anchor; BEC_2_5_4_LogicBool* bevt_2_ta_ph; BEC_2_5_4_LogicBool* bevt_3_ta_ph; BEC_2_4_3_MathInt* bevt_4_ta_ph; BEC_2_5_4_LogicBool* bevt_5_ta_ph; BEC_2_4_3_MathInt* bevt_6_ta_ph; BEC_2_5_4_LogicBool* bevt_7_ta_ph; BEC_2_4_3_MathInt* bevt_8_ta_ph; BEC_2_5_4_LogicBool* bevt_9_ta_ph; BEC_2_4_3_MathInt* bevt_10_ta_ph; BEC_2_5_4_LogicBool* bevt_11_ta_ph; BEC_2_4_3_MathInt* bevt_12_ta_ph; BEC_2_5_4_LogicBool* bevt_13_ta_ph; BEC_2_5_4_LogicBool* bevt_14_ta_ph; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->bevl_ic = nullptr;
beq->bevl_j = nullptr;
beq->bevt_0_ta_anchor = nullptr;
beq->bevt_1_ta_anchor = nullptr;
beq->bevt_2_ta_ph = nullptr;
beq->bevt_3_ta_ph = nullptr;
beq->bevt_4_ta_ph = nullptr;
beq->bevt_5_ta_ph = nullptr;
beq->bevt_6_ta_ph = nullptr;
beq->bevt_7_ta_ph = nullptr;
beq->bevt_8_ta_ph = nullptr;
beq->bevt_9_ta_ph = nullptr;
beq->bevt_10_ta_ph = nullptr;
beq->bevt_11_ta_ph = nullptr;
beq->bevt_12_ta_ph = nullptr;
beq->bevt_13_ta_ph = nullptr;
beq->bevt_14_ta_ph = nullptr;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(18);
beq->bevl_ic = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt())));
beq->bevl_j = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(0))));
while (true)
 {
if (beq->bevl_j->bevi_int < bevp_size->bevi_int) {
beq->bevt_2_ta_ph = BECS_Runtime::boolTrue;
 } else { 
beq->bevt_2_ta_ph = BECS_Runtime::boolFalse;
}
if (beq->bevt_2_ta_ph->bevi_bool) {
bem_getInt_2(beq->bevl_j, beq->bevl_ic);
beq->bevt_4_ta_ph = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(0))));
if (beq->bevl_j->bevi_int == beq->bevt_4_ta_ph->bevi_int) {
beq->bevt_3_ta_ph = BECS_Runtime::boolTrue;
 } else { 
beq->bevt_3_ta_ph = BECS_Runtime::boolFalse;
}
if (beq->bevt_3_ta_ph->bevi_bool) {
beq->bevt_6_ta_ph = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(43))));
if (beq->bevl_ic->bevi_int == beq->bevt_6_ta_ph->bevi_int) {
beq->bevt_5_ta_ph = BECS_Runtime::boolTrue;
 } else { 
beq->bevt_5_ta_ph = BECS_Runtime::boolFalse;
}
if (beq->bevt_5_ta_ph->bevi_bool) {
beq->bevt_0_ta_anchor = BECS_Runtime::boolTrue;
} 
 else  {
beq->bevt_8_ta_ph = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(45))));
if (beq->bevl_ic->bevi_int == beq->bevt_8_ta_ph->bevi_int) {
beq->bevt_7_ta_ph = BECS_Runtime::boolTrue;
 } else { 
beq->bevt_7_ta_ph = BECS_Runtime::boolFalse;
}
if (beq->bevt_7_ta_ph->bevi_bool) {
beq->bevt_0_ta_anchor = BECS_Runtime::boolTrue;
} 
 else  {
beq->bevt_0_ta_anchor = BECS_Runtime::boolFalse;
} 
} 
if (beq->bevt_0_ta_anchor->bevi_bool) {
beq->bevt_0_ta_anchor = BECS_Runtime::boolTrue;
} 
 else  {
beq->bevt_0_ta_anchor = BECS_Runtime::boolFalse;
} 
} 
 else  {
beq->bevt_0_ta_anchor = BECS_Runtime::boolFalse;
} 
if (beq->bevt_0_ta_anchor->bevi_bool) {
} 
 else  {
beq->bevt_10_ta_ph = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(57))));
if (beq->bevl_ic->bevi_int > beq->bevt_10_ta_ph->bevi_int) {
beq->bevt_9_ta_ph = BECS_Runtime::boolTrue;
 } else { 
beq->bevt_9_ta_ph = BECS_Runtime::boolFalse;
}
if (beq->bevt_9_ta_ph->bevi_bool) {
beq->bevt_1_ta_anchor = BECS_Runtime::boolTrue;
} 
 else  {
beq->bevt_12_ta_ph = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(48))));
if (beq->bevl_ic->bevi_int < beq->bevt_12_ta_ph->bevi_int) {
beq->bevt_11_ta_ph = BECS_Runtime::boolTrue;
 } else { 
beq->bevt_11_ta_ph = BECS_Runtime::boolFalse;
}
if (beq->bevt_11_ta_ph->bevi_bool) {
beq->bevt_1_ta_anchor = BECS_Runtime::boolTrue;
} 
 else  {
beq->bevt_1_ta_anchor = BECS_Runtime::boolFalse;
} 
} 
if (beq->bevt_1_ta_anchor->bevi_bool) {
beq->bevt_13_ta_ph = static_cast<BEC_2_5_4_LogicBool*>(BECS_Runtime::boolFalse);
return beq->bevt_13_ta_ph;
} 
} 
beq->bevl_j->bevi_int++;
} 
 else  {
break;
} 
} 
beq->bevt_14_ta_ph = static_cast<BEC_2_5_4_LogicBool*>(BECS_Runtime::boolTrue);
return beq->bevt_14_ta_ph;
}
BEC_2_5_4_LogicBool* BEC_2_4_6_TextString::bem_isAlphaNumGet_0() {
struct bes { BEC_2_4_3_MathInt* bevl_ic; BEC_2_4_3_MathInt* bevl_j; BEC_2_5_4_LogicBool* bevt_0_ta_anchor; BEC_2_5_4_LogicBool* bevt_1_ta_anchor; BEC_2_5_4_LogicBool* bevt_2_ta_anchor; BEC_2_5_4_LogicBool* bevt_3_ta_ph; BEC_2_5_4_LogicBool* bevt_4_ta_ph; BEC_2_4_3_MathInt* bevt_5_ta_ph; BEC_2_5_4_LogicBool* bevt_6_ta_ph; BEC_2_4_3_MathInt* bevt_7_ta_ph; BEC_2_5_4_LogicBool* bevt_8_ta_ph; BEC_2_4_3_MathInt* bevt_9_ta_ph; BEC_2_5_4_LogicBool* bevt_10_ta_ph; BEC_2_4_3_MathInt* bevt_11_ta_ph; BEC_2_5_4_LogicBool* bevt_12_ta_ph; BEC_2_4_3_MathInt* bevt_13_ta_ph; BEC_2_5_4_LogicBool* bevt_14_ta_ph; BEC_2_4_3_MathInt* bevt_15_ta_ph; BEC_2_5_4_LogicBool* bevt_16_ta_ph; BEC_2_5_4_LogicBool* bevt_17_ta_ph; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->bevl_ic = nullptr;
beq->bevl_j = nullptr;
beq->bevt_0_ta_anchor = nullptr;
beq->bevt_1_ta_anchor = nullptr;
beq->bevt_2_ta_anchor = nullptr;
beq->bevt_3_ta_ph = nullptr;
beq->bevt_4_ta_ph = nullptr;
beq->bevt_5_ta_ph = nullptr;
beq->bevt_6_ta_ph = nullptr;
beq->bevt_7_ta_ph = nullptr;
beq->bevt_8_ta_ph = nullptr;
beq->bevt_9_ta_ph = nullptr;
beq->bevt_10_ta_ph = nullptr;
beq->bevt_11_ta_ph = nullptr;
beq->bevt_12_ta_ph = nullptr;
beq->bevt_13_ta_ph = nullptr;
beq->bevt_14_ta_ph = nullptr;
beq->bevt_15_ta_ph = nullptr;
beq->bevt_16_ta_ph = nullptr;
beq->bevt_17_ta_ph = nullptr;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(21);
beq->bevl_ic = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt())));
beq->bevl_j = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(0))));
while (true)
 {
if (beq->bevl_j->bevi_int < bevp_size->bevi_int) {
beq->bevt_3_ta_ph = BECS_Runtime::boolTrue;
 } else { 
beq->bevt_3_ta_ph = BECS_Runtime::boolFalse;
}
if (beq->bevt_3_ta_ph->bevi_bool) {
bem_getInt_2(beq->bevl_j, beq->bevl_ic);
beq->bevt_5_ta_ph = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(47))));
if (beq->bevl_ic->bevi_int > beq->bevt_5_ta_ph->bevi_int) {
beq->bevt_4_ta_ph = BECS_Runtime::boolTrue;
 } else { 
beq->bevt_4_ta_ph = BECS_Runtime::boolFalse;
}
if (beq->bevt_4_ta_ph->bevi_bool) {
beq->bevt_7_ta_ph = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(58))));
if (beq->bevl_ic->bevi_int < beq->bevt_7_ta_ph->bevi_int) {
beq->bevt_6_ta_ph = BECS_Runtime::boolTrue;
 } else { 
beq->bevt_6_ta_ph = BECS_Runtime::boolFalse;
}
if (beq->bevt_6_ta_ph->bevi_bool) {
beq->bevt_2_ta_anchor = BECS_Runtime::boolTrue;
} 
 else  {
beq->bevt_2_ta_anchor = BECS_Runtime::boolFalse;
} 
} 
 else  {
beq->bevt_2_ta_anchor = BECS_Runtime::boolFalse;
} 
if (beq->bevt_2_ta_anchor->bevi_bool) {
beq->bevt_1_ta_anchor = BECS_Runtime::boolTrue;
} 
 else  {
beq->bevt_9_ta_ph = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(64))));
if (beq->bevl_ic->bevi_int > beq->bevt_9_ta_ph->bevi_int) {
beq->bevt_8_ta_ph = BECS_Runtime::boolTrue;
 } else { 
beq->bevt_8_ta_ph = BECS_Runtime::boolFalse;
}
if (beq->bevt_8_ta_ph->bevi_bool) {
beq->bevt_11_ta_ph = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(91))));
if (beq->bevl_ic->bevi_int < beq->bevt_11_ta_ph->bevi_int) {
beq->bevt_10_ta_ph = BECS_Runtime::boolTrue;
 } else { 
beq->bevt_10_ta_ph = BECS_Runtime::boolFalse;
}
if (beq->bevt_10_ta_ph->bevi_bool) {
beq->bevt_1_ta_anchor = BECS_Runtime::boolTrue;
} 
 else  {
beq->bevt_1_ta_anchor = BECS_Runtime::boolFalse;
} 
} 
 else  {
beq->bevt_1_ta_anchor = BECS_Runtime::boolFalse;
} 
if (beq->bevt_1_ta_anchor->bevi_bool) {
beq->bevt_1_ta_anchor = BECS_Runtime::boolTrue;
} 
 else  {
beq->bevt_1_ta_anchor = BECS_Runtime::boolFalse;
} 
} 
if (beq->bevt_1_ta_anchor->bevi_bool) {
beq->bevt_0_ta_anchor = BECS_Runtime::boolTrue;
} 
 else  {
beq->bevt_13_ta_ph = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(96))));
if (beq->bevl_ic->bevi_int > beq->bevt_13_ta_ph->bevi_int) {
beq->bevt_12_ta_ph = BECS_Runtime::boolTrue;
 } else { 
beq->bevt_12_ta_ph = BECS_Runtime::boolFalse;
}
if (beq->bevt_12_ta_ph->bevi_bool) {
beq->bevt_15_ta_ph = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(123))));
if (beq->bevl_ic->bevi_int < beq->bevt_15_ta_ph->bevi_int) {
beq->bevt_14_ta_ph = BECS_Runtime::boolTrue;
 } else { 
beq->bevt_14_ta_ph = BECS_Runtime::boolFalse;
}
if (beq->bevt_14_ta_ph->bevi_bool) {
beq->bevt_0_ta_anchor = BECS_Runtime::boolTrue;
} 
 else  {
beq->bevt_0_ta_anchor = BECS_Runtime::boolFalse;
} 
} 
 else  {
beq->bevt_0_ta_anchor = BECS_Runtime::boolFalse;
} 
if (beq->bevt_0_ta_anchor->bevi_bool) {
beq->bevt_0_ta_anchor = BECS_Runtime::boolTrue;
} 
 else  {
beq->bevt_0_ta_anchor = BECS_Runtime::boolFalse;
} 
} 
if (!(beq->bevt_0_ta_anchor->bevi_bool)) {
beq->bevt_16_ta_ph = static_cast<BEC_2_5_4_LogicBool*>(BECS_Runtime::boolFalse);
return beq->bevt_16_ta_ph;
} 
beq->bevl_j->bevi_int++;
} 
 else  {
break;
} 
} 
beq->bevt_17_ta_ph = static_cast<BEC_2_5_4_LogicBool*>(BECS_Runtime::boolTrue);
return beq->bevt_17_ta_ph;
}
BEC_2_5_4_LogicBool* BEC_2_4_6_TextString::bem_isAlphaNumericGet_0() {
struct bes { BEC_2_5_4_LogicBool* bevt_0_ta_ph; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->bevt_0_ta_ph = nullptr;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(2);
beq->bevt_0_ta_ph = bem_isAlphaNumGet_0();
return beq->bevt_0_ta_ph;
}
BEC_2_4_6_TextString* BEC_2_4_6_TextString::bem_lowerValue_0() {
struct bes { BEC_2_4_3_MathInt* bevl_vc; BEC_2_4_3_MathInt* bevl_j; BEC_2_5_4_LogicBool* bevt_0_ta_anchor; BEC_2_5_4_LogicBool* bevt_1_ta_ph; BEC_2_5_4_LogicBool* bevt_2_ta_ph; BEC_2_4_3_MathInt* bevt_3_ta_ph; BEC_2_5_4_LogicBool* bevt_4_ta_ph; BEC_2_4_3_MathInt* bevt_5_ta_ph; BEC_2_4_3_MathInt* bevt_6_ta_ph; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->bevl_vc = nullptr;
beq->bevl_j = nullptr;
beq->bevt_0_ta_anchor = nullptr;
beq->bevt_1_ta_ph = nullptr;
beq->bevt_2_ta_ph = nullptr;
beq->bevt_3_ta_ph = nullptr;
beq->bevt_4_ta_ph = nullptr;
beq->bevt_5_ta_ph = nullptr;
beq->bevt_6_ta_ph = nullptr;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(10);
beq->bevl_vc = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt())));
beq->bevl_j = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(0))));
while (true)
 {
if (beq->bevl_j->bevi_int < bevp_size->bevi_int) {
beq->bevt_1_ta_ph = BECS_Runtime::boolTrue;
 } else { 
beq->bevt_1_ta_ph = BECS_Runtime::boolFalse;
}
if (beq->bevt_1_ta_ph->bevi_bool) {
bem_getInt_2(beq->bevl_j, beq->bevl_vc);
beq->bevt_3_ta_ph = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(64))));
if (beq->bevl_vc->bevi_int > beq->bevt_3_ta_ph->bevi_int) {
beq->bevt_2_ta_ph = BECS_Runtime::boolTrue;
 } else { 
beq->bevt_2_ta_ph = BECS_Runtime::boolFalse;
}
if (beq->bevt_2_ta_ph->bevi_bool) {
beq->bevt_5_ta_ph = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(91))));
if (beq->bevl_vc->bevi_int < beq->bevt_5_ta_ph->bevi_int) {
beq->bevt_4_ta_ph = BECS_Runtime::boolTrue;
 } else { 
beq->bevt_4_ta_ph = BECS_Runtime::boolFalse;
}
if (beq->bevt_4_ta_ph->bevi_bool) {
beq->bevt_0_ta_anchor = BECS_Runtime::boolTrue;
} 
 else  {
beq->bevt_0_ta_anchor = BECS_Runtime::boolFalse;
} 
} 
 else  {
beq->bevt_0_ta_anchor = BECS_Runtime::boolFalse;
} 
if (beq->bevt_0_ta_anchor->bevi_bool) {
beq->bevt_6_ta_ph = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(32))));
beq->bevl_vc->bevi_int += beq->bevt_6_ta_ph->bevi_int;
bem_setIntUnchecked_2(beq->bevl_j, beq->bevl_vc);
} 
beq->bevl_j->bevi_int++;
} 
 else  {
break;
} 
} 
return this;
}
BEC_2_4_6_TextString* BEC_2_4_6_TextString::bem_lower_0() {
struct bes { BEC_2_4_6_TextString* bevt_0_ta_ph; BEC_2_4_6_TextString* bevt_1_ta_ph; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->bevt_0_ta_ph = nullptr;
beq->bevt_1_ta_ph = nullptr;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(3);
beq->bevt_1_ta_ph = static_cast<BEC_2_4_6_TextString*>(bem_copy_0());
beq->bevt_0_ta_ph = static_cast<BEC_2_4_6_TextString*>(beq->bevt_1_ta_ph->bem_lowerValue_0());
return beq->bevt_0_ta_ph;
}
BEC_2_4_6_TextString* BEC_2_4_6_TextString::bem_upperValue_0() {
struct bes { BEC_2_4_3_MathInt* bevl_vc; BEC_2_4_3_MathInt* bevl_j; BEC_2_5_4_LogicBool* bevt_0_ta_anchor; BEC_2_5_4_LogicBool* bevt_1_ta_ph; BEC_2_5_4_LogicBool* bevt_2_ta_ph; BEC_2_4_3_MathInt* bevt_3_ta_ph; BEC_2_5_4_LogicBool* bevt_4_ta_ph; BEC_2_4_3_MathInt* bevt_5_ta_ph; BEC_2_4_3_MathInt* bevt_6_ta_ph; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->bevl_vc = nullptr;
beq->bevl_j = nullptr;
beq->bevt_0_ta_anchor = nullptr;
beq->bevt_1_ta_ph = nullptr;
beq->bevt_2_ta_ph = nullptr;
beq->bevt_3_ta_ph = nullptr;
beq->bevt_4_ta_ph = nullptr;
beq->bevt_5_ta_ph = nullptr;
beq->bevt_6_ta_ph = nullptr;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(10);
beq->bevl_vc = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt())));
beq->bevl_j = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(0))));
while (true)
 {
if (beq->bevl_j->bevi_int < bevp_size->bevi_int) {
beq->bevt_1_ta_ph = BECS_Runtime::boolTrue;
 } else { 
beq->bevt_1_ta_ph = BECS_Runtime::boolFalse;
}
if (beq->bevt_1_ta_ph->bevi_bool) {
bem_getInt_2(beq->bevl_j, beq->bevl_vc);
beq->bevt_3_ta_ph = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(96))));
if (beq->bevl_vc->bevi_int > beq->bevt_3_ta_ph->bevi_int) {
beq->bevt_2_ta_ph = BECS_Runtime::boolTrue;
 } else { 
beq->bevt_2_ta_ph = BECS_Runtime::boolFalse;
}
if (beq->bevt_2_ta_ph->bevi_bool) {
beq->bevt_5_ta_ph = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(123))));
if (beq->bevl_vc->bevi_int < beq->bevt_5_ta_ph->bevi_int) {
beq->bevt_4_ta_ph = BECS_Runtime::boolTrue;
 } else { 
beq->bevt_4_ta_ph = BECS_Runtime::boolFalse;
}
if (beq->bevt_4_ta_ph->bevi_bool) {
beq->bevt_0_ta_anchor = BECS_Runtime::boolTrue;
} 
 else  {
beq->bevt_0_ta_anchor = BECS_Runtime::boolFalse;
} 
} 
 else  {
beq->bevt_0_ta_anchor = BECS_Runtime::boolFalse;
} 
if (beq->bevt_0_ta_anchor->bevi_bool) {
beq->bevt_6_ta_ph = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(32))));
beq->bevl_vc->bem_subtractValue_1(beq->bevt_6_ta_ph);
bem_setIntUnchecked_2(beq->bevl_j, beq->bevl_vc);
} 
beq->bevl_j->bevi_int++;
} 
 else  {
break;
} 
} 
return this;
}
BEC_2_4_6_TextString* BEC_2_4_6_TextString::bem_upper_0() {
struct bes { BEC_2_4_6_TextString* bevt_0_ta_ph; BEC_2_4_6_TextString* bevt_1_ta_ph; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->bevt_0_ta_ph = nullptr;
beq->bevt_1_ta_ph = nullptr;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(3);
beq->bevt_1_ta_ph = static_cast<BEC_2_4_6_TextString*>(bem_copy_0());
beq->bevt_0_ta_ph = static_cast<BEC_2_4_6_TextString*>(beq->bevt_1_ta_ph->bem_upperValue_0());
return beq->bevt_0_ta_ph;
}
BEC_2_6_6_SystemObject* BEC_2_4_6_TextString::bem_swapFirst_2(BEC_2_4_6_TextString* bevk_from, BEC_2_4_6_TextString* bevk_to) {
struct bes { BEC_2_4_6_TextString* beva_from; BEC_2_4_6_TextString* beva_to; BEC_2_4_6_TextString* bevl_res; BEC_2_4_3_MathInt* bevl_last; BEC_2_4_3_MathInt* bevl_nxt; BEC_2_5_4_LogicBool* bevt_0_ta_ph; BEC_2_4_6_TextString* bevt_1_ta_ph; BEC_2_4_3_MathInt* bevt_2_ta_ph; BEC_2_4_6_TextString* bevt_3_ta_ph; BEC_2_4_3_MathInt* bevt_4_ta_ph; BEC_2_4_6_TextString* bevt_5_ta_ph; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->beva_from = bevk_from;
beq->beva_to = bevk_to;
beq->bevl_res = nullptr;
beq->bevl_last = nullptr;
beq->bevl_nxt = nullptr;
beq->bevt_0_ta_ph = nullptr;
beq->bevt_1_ta_ph = nullptr;
beq->bevt_2_ta_ph = nullptr;
beq->bevt_3_ta_ph = nullptr;
beq->bevt_4_ta_ph = nullptr;
beq->bevt_5_ta_ph = nullptr;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(12);
beq->bevl_res = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString()))->bem_new_0());
beq->bevl_last = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(0))));
beq->bevl_nxt = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(0))));
beq->bevl_nxt = bem_find_2(beq->beva_from, beq->bevl_last);
if (beq->bevl_nxt == nullptr) {
beq->bevt_0_ta_ph = BECS_Runtime::boolFalse;
 } else { 
beq->bevt_0_ta_ph = BECS_Runtime::boolTrue;
}
if (beq->bevt_0_ta_ph->bevi_bool) {
beq->bevt_1_ta_ph = bem_substring_2(beq->bevl_last, beq->bevl_nxt);
beq->bevl_res->bem_addValue_1(beq->bevt_1_ta_ph);
beq->bevl_res->bem_addValue_1(beq->beva_to);
beq->bevt_2_ta_ph = beq->beva_from->bem_sizeGet_0();
beq->bevl_last = beq->bevl_nxt->bem_add_1(beq->bevt_2_ta_ph);
beq->bevt_4_ta_ph = bem_sizeGet_0();
beq->bevt_3_ta_ph = bem_substring_2(beq->bevl_last, beq->bevt_4_ta_ph);
beq->bevl_res->bem_addValue_1(beq->bevt_3_ta_ph);
} 
 else  {
beq->bevt_5_ta_ph = static_cast<BEC_2_4_6_TextString*>(beq->beva_from->bem_copy_0());
return beq->bevt_5_ta_ph;
} 
return beq->bevl_res;
}
BEC_2_6_6_SystemObject* BEC_2_4_6_TextString::bem_swap_2(BEC_2_4_6_TextString* bevk_from, BEC_2_4_6_TextString* bevk_to) {
struct bes { BEC_2_4_6_TextString* beva_from; BEC_2_4_6_TextString* beva_to; BEC_2_4_6_TextString* bevl_res; BEC_2_4_3_MathInt* bevl_last; BEC_2_4_3_MathInt* bevl_nxt; BEC_2_5_4_LogicBool* bevt_0_ta_ph; BEC_2_5_4_LogicBool* bevt_1_ta_ph; BEC_2_4_6_TextString* bevt_2_ta_ph; BEC_2_4_3_MathInt* bevt_3_ta_ph; BEC_2_4_6_TextString* bevt_4_ta_ph; BEC_2_4_3_MathInt* bevt_5_ta_ph; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->beva_from = bevk_from;
beq->beva_to = bevk_to;
beq->bevl_res = nullptr;
beq->bevl_last = nullptr;
beq->bevl_nxt = nullptr;
beq->bevt_0_ta_ph = nullptr;
beq->bevt_1_ta_ph = nullptr;
beq->bevt_2_ta_ph = nullptr;
beq->bevt_3_ta_ph = nullptr;
beq->bevt_4_ta_ph = nullptr;
beq->bevt_5_ta_ph = nullptr;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(12);
beq->bevl_res = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString()))->bem_new_0());
beq->bevl_last = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(0))));
beq->bevl_nxt = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(0))));
while (true)
 {
if (beq->bevl_nxt == nullptr) {
beq->bevt_0_ta_ph = BECS_Runtime::boolFalse;
 } else { 
beq->bevt_0_ta_ph = BECS_Runtime::boolTrue;
}
if (beq->bevt_0_ta_ph->bevi_bool) {
beq->bevl_nxt = bem_find_2(beq->beva_from, beq->bevl_last);
if (beq->bevl_nxt == nullptr) {
beq->bevt_1_ta_ph = BECS_Runtime::boolFalse;
 } else { 
beq->bevt_1_ta_ph = BECS_Runtime::boolTrue;
}
if (beq->bevt_1_ta_ph->bevi_bool) {
beq->bevt_2_ta_ph = bem_substring_2(beq->bevl_last, beq->bevl_nxt);
beq->bevl_res->bem_addValue_1(beq->bevt_2_ta_ph);
beq->bevl_res->bem_addValue_1(beq->beva_to);
beq->bevt_3_ta_ph = beq->beva_from->bem_sizeGet_0();
beq->bevl_last = beq->bevl_nxt->bem_add_1(beq->bevt_3_ta_ph);
} 
 else  {
beq->bevt_5_ta_ph = bem_sizeGet_0();
beq->bevt_4_ta_ph = bem_substring_2(beq->bevl_last, beq->bevt_5_ta_ph);
beq->bevl_res->bem_addValue_1(beq->bevt_4_ta_ph);
} 
} 
 else  {
break;
} 
} 
return beq->bevl_res;
}
BEC_2_4_6_TextString* BEC_2_4_6_TextString::bem_getPoint_1(BEC_2_4_3_MathInt* bevk_posi) {
struct bes { BEC_2_4_3_MathInt* beva_posi; BEC_2_4_6_TextString* bevl_buf; BEC_2_4_17_TextMultiByteIterator* bevl_j; BEC_2_4_3_MathInt* bevl_i; BEC_2_4_6_TextString* bevl_y; BEC_2_4_3_MathInt* bevt_0_ta_ph; BEC_2_5_4_LogicBool* bevt_1_ta_ph; BEC_2_4_6_TextString* bevt_2_ta_ph; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->beva_posi = bevk_posi;
beq->bevl_buf = nullptr;
beq->bevl_j = nullptr;
beq->bevl_i = nullptr;
beq->bevl_y = nullptr;
beq->bevt_0_ta_ph = nullptr;
beq->bevt_1_ta_ph = nullptr;
beq->bevt_2_ta_ph = nullptr;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(9);
beq->bevt_0_ta_ph = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(2))));
beq->bevl_buf = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString()))->bem_new_1(beq->bevt_0_ta_ph));
beq->bevl_j = bem_mbiterGet_0();
beq->bevl_i = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(0))));
while (true)
 {
if (beq->bevl_i->bevi_int < beq->beva_posi->bevi_int) {
beq->bevt_1_ta_ph = BECS_Runtime::boolTrue;
 } else { 
beq->bevt_1_ta_ph = BECS_Runtime::boolFalse;
}
if (beq->bevt_1_ta_ph->bevi_bool) {
beq->bevl_j->bem_next_1(beq->bevl_buf);
beq->bevl_i->bevi_int++;
} 
 else  {
break;
} 
} 
beq->bevt_2_ta_ph = beq->bevl_j->bem_next_1(beq->bevl_buf);
beq->bevl_y = beq->bevt_2_ta_ph->bem_toString_0();
return beq->bevl_y;
}
BEC_2_4_3_MathInt* BEC_2_4_6_TextString::bem_hashValue_1(BEC_2_4_3_MathInt* bevk_into) {
struct bes { BEC_2_4_3_MathInt* beva_into; BEC_2_4_3_MathInt* bevl_c; BEC_2_4_3_MathInt* bevl_j; BEC_2_4_3_MathInt* bevt_0_ta_ph; BEC_2_5_4_LogicBool* bevt_1_ta_ph; BEC_2_4_3_MathInt* bevt_2_ta_ph; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->beva_into = bevk_into;
beq->bevl_c = nullptr;
beq->bevl_j = nullptr;
beq->bevt_0_ta_ph = nullptr;
beq->bevt_1_ta_ph = nullptr;
beq->bevt_2_ta_ph = nullptr;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(7);
beq->bevl_c = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt())));
beq->bevt_0_ta_ph = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(0))));
beq->beva_into->bevi_int = beq->bevt_0_ta_ph->bevi_int;
beq->bevl_j = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(0))));
while (true)
 {
if (beq->bevl_j->bevi_int < bevp_size->bevi_int) {
beq->bevt_1_ta_ph = BECS_Runtime::boolTrue;
 } else { 
beq->bevt_1_ta_ph = BECS_Runtime::boolFalse;
}
if (beq->bevt_1_ta_ph->bevi_bool) {
bem_getInt_2(beq->bevl_j, beq->bevl_c);
beq->bevt_2_ta_ph = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(31))));
beq->beva_into->bem_multiplyValue_1(beq->bevt_2_ta_ph);
beq->beva_into->bevi_int += beq->bevl_c->bevi_int;
beq->bevl_j->bevi_int++;
} 
 else  {
break;
} 
} 
return beq->beva_into;
}
BEC_2_4_3_MathInt* BEC_2_4_6_TextString::bem_hashGet_0() {
struct bes { BEC_2_4_3_MathInt* bevt_0_ta_ph; BEC_2_4_3_MathInt* bevt_1_ta_ph; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->bevt_0_ta_ph = nullptr;
beq->bevt_1_ta_ph = nullptr;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(3);
beq->bevt_1_ta_ph = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt())));
beq->bevt_0_ta_ph = bem_hashValue_1(beq->bevt_1_ta_ph);
return beq->bevt_0_ta_ph;
}
BEC_2_4_3_MathInt* BEC_2_4_6_TextString::bem_getCode_1(BEC_2_4_3_MathInt* bevk_pos) {
struct bes { BEC_2_4_3_MathInt* beva_pos; BEC_2_4_3_MathInt* bevt_0_ta_ph; BEC_2_4_3_MathInt* bevt_1_ta_ph; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->beva_pos = bevk_pos;
beq->bevt_0_ta_ph = nullptr;
beq->bevt_1_ta_ph = nullptr;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(4);
beq->bevt_1_ta_ph = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt())));
beq->bevt_0_ta_ph = bem_getCode_2(beq->beva_pos, beq->bevt_1_ta_ph);
return beq->bevt_0_ta_ph;
}
BEC_2_4_3_MathInt* BEC_2_4_6_TextString::bem_getInt_2(BEC_2_4_3_MathInt* bevk_pos, BEC_2_4_3_MathInt* bevk_into) {
struct bes { BEC_2_4_3_MathInt* beva_pos; BEC_2_4_3_MathInt* beva_into; BEC_2_5_4_LogicBool* bevt_0_ta_anchor; BEC_2_5_4_LogicBool* bevt_1_ta_ph; BEC_2_4_3_MathInt* bevt_2_ta_ph; BEC_2_5_4_LogicBool* bevt_3_ta_ph; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->beva_pos = bevk_pos;
beq->beva_into = bevk_into;
beq->bevt_0_ta_anchor = nullptr;
beq->bevt_1_ta_ph = nullptr;
beq->bevt_2_ta_ph = nullptr;
beq->bevt_3_ta_ph = nullptr;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(7);
beq->bevt_2_ta_ph = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(0))));
if (beq->beva_pos->bevi_int >= beq->bevt_2_ta_ph->bevi_int) {
beq->bevt_1_ta_ph = BECS_Runtime::boolTrue;
 } else { 
beq->bevt_1_ta_ph = BECS_Runtime::boolFalse;
}
if (beq->bevt_1_ta_ph->bevi_bool) {
if (bevp_size->bevi_int > beq->beva_pos->bevi_int) {
beq->bevt_3_ta_ph = BECS_Runtime::boolTrue;
 } else { 
beq->bevt_3_ta_ph = BECS_Runtime::boolFalse;
}
if (beq->bevt_3_ta_ph->bevi_bool) {
beq->bevt_0_ta_anchor = BECS_Runtime::boolTrue;
} 
 else  {
beq->bevt_0_ta_anchor = BECS_Runtime::boolFalse;
} 
} 
 else  {
beq->bevt_0_ta_anchor = BECS_Runtime::boolFalse;
} 
if (beq->bevt_0_ta_anchor->bevi_bool) {

         beq->beva_into->bevi_int = (int32_t) bevi_bytes[beq->beva_pos->bevi_int];
         if (beq->beva_into->bevi_int > 127) {
            beq->beva_into->bevi_int -= 256;
         }
         } 
 else  {
return nullptr;
} 
return beq->beva_into;
}
BEC_2_4_3_MathInt* BEC_2_4_6_TextString::bem_getCode_2(BEC_2_4_3_MathInt* bevk_pos, BEC_2_4_3_MathInt* bevk_into) {
struct bes { BEC_2_4_3_MathInt* beva_pos; BEC_2_4_3_MathInt* beva_into; BEC_2_5_4_LogicBool* bevt_0_ta_anchor; BEC_2_5_4_LogicBool* bevt_1_ta_ph; BEC_2_4_3_MathInt* bevt_2_ta_ph; BEC_2_5_4_LogicBool* bevt_3_ta_ph; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->beva_pos = bevk_pos;
beq->beva_into = bevk_into;
beq->bevt_0_ta_anchor = nullptr;
beq->bevt_1_ta_ph = nullptr;
beq->bevt_2_ta_ph = nullptr;
beq->bevt_3_ta_ph = nullptr;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(7);
beq->bevt_2_ta_ph = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(0))));
if (beq->beva_pos->bevi_int >= beq->bevt_2_ta_ph->bevi_int) {
beq->bevt_1_ta_ph = BECS_Runtime::boolTrue;
 } else { 
beq->bevt_1_ta_ph = BECS_Runtime::boolFalse;
}
if (beq->bevt_1_ta_ph->bevi_bool) {
if (bevp_size->bevi_int > beq->beva_pos->bevi_int) {
beq->bevt_3_ta_ph = BECS_Runtime::boolTrue;
 } else { 
beq->bevt_3_ta_ph = BECS_Runtime::boolFalse;
}
if (beq->bevt_3_ta_ph->bevi_bool) {
beq->bevt_0_ta_anchor = BECS_Runtime::boolTrue;
} 
 else  {
beq->bevt_0_ta_anchor = BECS_Runtime::boolFalse;
} 
} 
 else  {
beq->bevt_0_ta_anchor = BECS_Runtime::boolFalse;
} 
if (beq->bevt_0_ta_anchor->bevi_bool) {

         beq->beva_into->bevi_int = bevi_bytes[beq->beva_pos->bevi_int];
         } 
 else  {
return nullptr;
} 
return beq->beva_into;
}
BEC_2_4_6_TextString* BEC_2_4_6_TextString::bem_setInt_2(BEC_2_4_3_MathInt* bevk_pos, BEC_2_4_3_MathInt* bevk_into) {
struct bes { BEC_2_4_3_MathInt* beva_pos; BEC_2_4_3_MathInt* beva_into; BEC_2_5_4_LogicBool* bevt_0_ta_anchor; BEC_2_5_4_LogicBool* bevt_1_ta_ph; BEC_2_4_3_MathInt* bevt_2_ta_ph; BEC_2_5_4_LogicBool* bevt_3_ta_ph; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->beva_pos = bevk_pos;
beq->beva_into = bevk_into;
beq->bevt_0_ta_anchor = nullptr;
beq->bevt_1_ta_ph = nullptr;
beq->bevt_2_ta_ph = nullptr;
beq->bevt_3_ta_ph = nullptr;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(7);
beq->bevt_2_ta_ph = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(0))));
if (beq->beva_pos->bevi_int >= beq->bevt_2_ta_ph->bevi_int) {
beq->bevt_1_ta_ph = BECS_Runtime::boolTrue;
 } else { 
beq->bevt_1_ta_ph = BECS_Runtime::boolFalse;
}
if (beq->bevt_1_ta_ph->bevi_bool) {
if (bevp_size->bevi_int > beq->beva_pos->bevi_int) {
beq->bevt_3_ta_ph = BECS_Runtime::boolTrue;
 } else { 
beq->bevt_3_ta_ph = BECS_Runtime::boolFalse;
}
if (beq->bevt_3_ta_ph->bevi_bool) {
beq->bevt_0_ta_anchor = BECS_Runtime::boolTrue;
} 
 else  {
beq->bevt_0_ta_anchor = BECS_Runtime::boolFalse;
} 
} 
 else  {
beq->bevt_0_ta_anchor = BECS_Runtime::boolFalse;
} 
if (beq->bevt_0_ta_anchor->bevi_bool) {
bem_setIntUnchecked_2(beq->beva_pos, beq->beva_into);
} 
return this;
}
BEC_2_4_6_TextString* BEC_2_4_6_TextString::bem_setCode_2(BEC_2_4_3_MathInt* bevk_pos, BEC_2_4_3_MathInt* bevk_into) {
struct bes { BEC_2_4_3_MathInt* beva_pos; BEC_2_4_3_MathInt* beva_into; BEC_2_5_4_LogicBool* bevt_0_ta_anchor; BEC_2_5_4_LogicBool* bevt_1_ta_ph; BEC_2_4_3_MathInt* bevt_2_ta_ph; BEC_2_5_4_LogicBool* bevt_3_ta_ph; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->beva_pos = bevk_pos;
beq->beva_into = bevk_into;
beq->bevt_0_ta_anchor = nullptr;
beq->bevt_1_ta_ph = nullptr;
beq->bevt_2_ta_ph = nullptr;
beq->bevt_3_ta_ph = nullptr;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(7);
beq->bevt_2_ta_ph = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(0))));
if (beq->beva_pos->bevi_int >= beq->bevt_2_ta_ph->bevi_int) {
beq->bevt_1_ta_ph = BECS_Runtime::boolTrue;
 } else { 
beq->bevt_1_ta_ph = BECS_Runtime::boolFalse;
}
if (beq->bevt_1_ta_ph->bevi_bool) {
if (bevp_size->bevi_int > beq->beva_pos->bevi_int) {
beq->bevt_3_ta_ph = BECS_Runtime::boolTrue;
 } else { 
beq->bevt_3_ta_ph = BECS_Runtime::boolFalse;
}
if (beq->bevt_3_ta_ph->bevi_bool) {
beq->bevt_0_ta_anchor = BECS_Runtime::boolTrue;
} 
 else  {
beq->bevt_0_ta_anchor = BECS_Runtime::boolFalse;
} 
} 
 else  {
beq->bevt_0_ta_anchor = BECS_Runtime::boolFalse;
} 
if (beq->bevt_0_ta_anchor->bevi_bool) {
bem_setCodeUnchecked_2(beq->beva_pos, beq->beva_into);
} 
return this;
}
BEC_2_4_6_TextString* BEC_2_4_6_TextString::bem_toAlphaNum_0() {
struct bes { BEC_2_4_6_TextString* bevl_input; BEC_2_4_3_MathInt* bevl_insz; BEC_2_4_6_TextString* bevl_output; BEC_2_4_3_MathInt* bevl_c; BEC_2_4_3_MathInt* bevl_p; BEC_2_4_3_MathInt* bevl_i; BEC_2_5_4_LogicBool* bevt_0_ta_anchor; BEC_2_5_4_LogicBool* bevt_1_ta_anchor; BEC_2_5_4_LogicBool* bevt_2_ta_anchor; BEC_2_4_3_MathInt* bevt_3_ta_ph; BEC_2_5_4_LogicBool* bevt_4_ta_ph; BEC_2_5_4_LogicBool* bevt_5_ta_ph; BEC_2_4_3_MathInt* bevt_6_ta_ph; BEC_2_5_4_LogicBool* bevt_7_ta_ph; BEC_2_4_3_MathInt* bevt_8_ta_ph; BEC_2_5_4_LogicBool* bevt_9_ta_ph; BEC_2_4_3_MathInt* bevt_10_ta_ph; BEC_2_5_4_LogicBool* bevt_11_ta_ph; BEC_2_4_3_MathInt* bevt_12_ta_ph; BEC_2_5_4_LogicBool* bevt_13_ta_ph; BEC_2_4_3_MathInt* bevt_14_ta_ph; BEC_2_5_4_LogicBool* bevt_15_ta_ph; BEC_2_4_3_MathInt* bevt_16_ta_ph; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->bevl_input = nullptr;
beq->bevl_insz = nullptr;
beq->bevl_output = nullptr;
beq->bevl_c = nullptr;
beq->bevl_p = nullptr;
beq->bevl_i = nullptr;
beq->bevt_0_ta_anchor = nullptr;
beq->bevt_1_ta_anchor = nullptr;
beq->bevt_2_ta_anchor = nullptr;
beq->bevt_3_ta_ph = nullptr;
beq->bevt_4_ta_ph = nullptr;
beq->bevt_5_ta_ph = nullptr;
beq->bevt_6_ta_ph = nullptr;
beq->bevt_7_ta_ph = nullptr;
beq->bevt_8_ta_ph = nullptr;
beq->bevt_9_ta_ph = nullptr;
beq->bevt_10_ta_ph = nullptr;
beq->bevt_11_ta_ph = nullptr;
beq->bevt_12_ta_ph = nullptr;
beq->bevt_13_ta_ph = nullptr;
beq->bevt_14_ta_ph = nullptr;
beq->bevt_15_ta_ph = nullptr;
beq->bevt_16_ta_ph = nullptr;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(24);
beq->bevl_input = this;
beq->bevt_3_ta_ph = beq->bevl_input->bem_sizeGet_0();
beq->bevl_insz = static_cast<BEC_2_4_3_MathInt*>(beq->bevt_3_ta_ph->bem_copy_0());
beq->bevl_output = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString()))->bem_new_1(beq->bevl_insz));
beq->bevl_c = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt())));
beq->bevl_p = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(0))));
beq->bevl_i = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(0))));
while (true)
 {
if (beq->bevl_i->bevi_int < beq->bevl_insz->bevi_int) {
beq->bevt_4_ta_ph = BECS_Runtime::boolTrue;
 } else { 
beq->bevt_4_ta_ph = BECS_Runtime::boolFalse;
}
if (beq->bevt_4_ta_ph->bevi_bool) {
beq->bevl_input->bem_getInt_2(beq->bevl_i, beq->bevl_c);
beq->bevt_6_ta_ph = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(64))));
if (beq->bevl_c->bevi_int > beq->bevt_6_ta_ph->bevi_int) {
beq->bevt_5_ta_ph = BECS_Runtime::boolTrue;
 } else { 
beq->bevt_5_ta_ph = BECS_Runtime::boolFalse;
}
if (beq->bevt_5_ta_ph->bevi_bool) {
beq->bevt_8_ta_ph = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(91))));
if (beq->bevl_c->bevi_int < beq->bevt_8_ta_ph->bevi_int) {
beq->bevt_7_ta_ph = BECS_Runtime::boolTrue;
 } else { 
beq->bevt_7_ta_ph = BECS_Runtime::boolFalse;
}
if (beq->bevt_7_ta_ph->bevi_bool) {
beq->bevt_2_ta_anchor = BECS_Runtime::boolTrue;
} 
 else  {
beq->bevt_2_ta_anchor = BECS_Runtime::boolFalse;
} 
} 
 else  {
beq->bevt_2_ta_anchor = BECS_Runtime::boolFalse;
} 
if (beq->bevt_2_ta_anchor->bevi_bool) {
beq->bevt_1_ta_anchor = BECS_Runtime::boolTrue;
} 
 else  {
beq->bevt_10_ta_ph = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(96))));
if (beq->bevl_c->bevi_int > beq->bevt_10_ta_ph->bevi_int) {
beq->bevt_9_ta_ph = BECS_Runtime::boolTrue;
 } else { 
beq->bevt_9_ta_ph = BECS_Runtime::boolFalse;
}
if (beq->bevt_9_ta_ph->bevi_bool) {
beq->bevt_12_ta_ph = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(123))));
if (beq->bevl_c->bevi_int < beq->bevt_12_ta_ph->bevi_int) {
beq->bevt_11_ta_ph = BECS_Runtime::boolTrue;
 } else { 
beq->bevt_11_ta_ph = BECS_Runtime::boolFalse;
}
if (beq->bevt_11_ta_ph->bevi_bool) {
beq->bevt_1_ta_anchor = BECS_Runtime::boolTrue;
} 
 else  {
beq->bevt_1_ta_anchor = BECS_Runtime::boolFalse;
} 
} 
 else  {
beq->bevt_1_ta_anchor = BECS_Runtime::boolFalse;
} 
if (beq->bevt_1_ta_anchor->bevi_bool) {
beq->bevt_1_ta_anchor = BECS_Runtime::boolTrue;
} 
 else  {
beq->bevt_1_ta_anchor = BECS_Runtime::boolFalse;
} 
} 
if (beq->bevt_1_ta_anchor->bevi_bool) {
beq->bevt_0_ta_anchor = BECS_Runtime::boolTrue;
} 
 else  {
beq->bevt_14_ta_ph = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(47))));
if (beq->bevl_c->bevi_int > beq->bevt_14_ta_ph->bevi_int) {
beq->bevt_13_ta_ph = BECS_Runtime::boolTrue;
 } else { 
beq->bevt_13_ta_ph = BECS_Runtime::boolFalse;
}
if (beq->bevt_13_ta_ph->bevi_bool) {
beq->bevt_16_ta_ph = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(58))));
if (beq->bevl_c->bevi_int < beq->bevt_16_ta_ph->bevi_int) {
beq->bevt_15_ta_ph = BECS_Runtime::boolTrue;
 } else { 
beq->bevt_15_ta_ph = BECS_Runtime::boolFalse;
}
if (beq->bevt_15_ta_ph->bevi_bool) {
beq->bevt_0_ta_anchor = BECS_Runtime::boolTrue;
} 
 else  {
beq->bevt_0_ta_anchor = BECS_Runtime::boolFalse;
} 
} 
 else  {
beq->bevt_0_ta_anchor = BECS_Runtime::boolFalse;
} 
if (beq->bevt_0_ta_anchor->bevi_bool) {
beq->bevt_0_ta_anchor = BECS_Runtime::boolTrue;
} 
 else  {
beq->bevt_0_ta_anchor = BECS_Runtime::boolFalse;
} 
} 
if (beq->bevt_0_ta_anchor->bevi_bool) {
beq->bevl_output->bem_setIntUnchecked_2(beq->bevl_p, beq->bevl_c);
beq->bevl_p->bevi_int++;
} 
beq->bevl_i->bevi_int++;
} 
 else  {
break;
} 
} 
beq->bevl_output->bem_sizeSet_1(beq->bevl_p);
return beq->bevl_output;
}
BEC_2_5_4_LogicBool* BEC_2_4_6_TextString::bem_isEmptyGet_0() {
struct bes { BEC_2_5_4_LogicBool* bevt_0_ta_ph; BEC_2_4_3_MathInt* bevt_1_ta_ph; BEC_2_5_4_LogicBool* bevt_2_ta_ph; BEC_2_5_4_LogicBool* bevt_3_ta_ph; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->bevt_0_ta_ph = nullptr;
beq->bevt_1_ta_ph = nullptr;
beq->bevt_2_ta_ph = nullptr;
beq->bevt_3_ta_ph = nullptr;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(5);
beq->bevt_1_ta_ph = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(0))));
if (bevp_size->bevi_int <= beq->bevt_1_ta_ph->bevi_int) {
beq->bevt_0_ta_ph = BECS_Runtime::boolTrue;
 } else { 
beq->bevt_0_ta_ph = BECS_Runtime::boolFalse;
}
if (beq->bevt_0_ta_ph->bevi_bool) {
beq->bevt_2_ta_ph = static_cast<BEC_2_5_4_LogicBool*>(BECS_Runtime::boolTrue);
return beq->bevt_2_ta_ph;
} 
beq->bevt_3_ta_ph = static_cast<BEC_2_5_4_LogicBool*>(BECS_Runtime::boolFalse);
return beq->bevt_3_ta_ph;
}
BEC_2_4_6_TextString* BEC_2_4_6_TextString::bem_setIntUnchecked_2(BEC_2_4_3_MathInt* bevk_pos, BEC_2_4_3_MathInt* bevk_into) {
struct bes { BEC_2_4_3_MathInt* beva_pos; BEC_2_4_3_MathInt* beva_into; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->beva_pos = bevk_pos;
beq->beva_into = bevk_into;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(3);

     int32_t twvls_b = beq->beva_into->bevi_int;
     if (twvls_b < 0) {
        twvls_b += 256;
     }
     bevi_bytes[beq->beva_pos->bevi_int] = (unsigned char) twvls_b;
     return this;
}
BEC_2_4_6_TextString* BEC_2_4_6_TextString::bem_setCodeUnchecked_2(BEC_2_4_3_MathInt* bevk_pos, BEC_2_4_3_MathInt* bevk_into) {
struct bes { BEC_2_4_3_MathInt* beva_pos; BEC_2_4_3_MathInt* beva_into; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->beva_pos = bevk_pos;
beq->beva_into = bevk_into;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(3);

     bevi_bytes[beq->beva_pos->bevi_int] = (unsigned char) beq->beva_into->bevi_int;
     return this;
}
BEC_2_4_3_MathInt* BEC_2_4_6_TextString::bem_reverseFind_1(BEC_2_4_6_TextString* bevk_str) {
struct bes { BEC_2_4_6_TextString* beva_str; BEC_2_4_3_MathInt* bevt_0_ta_ph; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->beva_str = bevk_str;
beq->bevt_0_ta_ph = nullptr;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(3);
beq->bevt_0_ta_ph = bem_rfind_1(beq->beva_str);
return beq->bevt_0_ta_ph;
}
BEC_2_4_3_MathInt* BEC_2_4_6_TextString::bem_rfind_1(BEC_2_4_6_TextString* bevk_str) {
struct bes { BEC_2_4_6_TextString* beva_str; BEC_2_4_3_MathInt* bevl_rpos; BEC_2_4_6_TextString* bevt_0_ta_ph; BEC_2_4_6_TextString* bevt_1_ta_ph; BEC_2_4_6_TextString* bevt_2_ta_ph; BEC_2_4_6_TextString* bevt_3_ta_ph; BEC_2_5_4_LogicBool* bevt_4_ta_ph; BEC_2_4_3_MathInt* bevt_5_ta_ph; BEC_2_4_3_MathInt* bevt_6_ta_ph; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->beva_str = bevk_str;
beq->bevl_rpos = nullptr;
beq->bevt_0_ta_ph = nullptr;
beq->bevt_1_ta_ph = nullptr;
beq->bevt_2_ta_ph = nullptr;
beq->bevt_3_ta_ph = nullptr;
beq->bevt_4_ta_ph = nullptr;
beq->bevt_5_ta_ph = nullptr;
beq->bevt_6_ta_ph = nullptr;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(10);
beq->bevt_1_ta_ph = static_cast<BEC_2_4_6_TextString*>(bem_copy_0());
beq->bevt_0_ta_ph = static_cast<BEC_2_4_6_TextString*>(beq->bevt_1_ta_ph->bem_reverseBytes_0());
beq->bevt_3_ta_ph = static_cast<BEC_2_4_6_TextString*>(beq->beva_str->bem_copy_0());
beq->bevt_2_ta_ph = static_cast<BEC_2_4_6_TextString*>(beq->bevt_3_ta_ph->bem_reverseBytes_0());
beq->bevl_rpos = beq->bevt_0_ta_ph->bem_find_1(beq->bevt_2_ta_ph);
if (beq->bevl_rpos == nullptr) {
beq->bevt_4_ta_ph = BECS_Runtime::boolFalse;
 } else { 
beq->bevt_4_ta_ph = BECS_Runtime::boolTrue;
}
if (beq->bevt_4_ta_ph->bevi_bool) {
beq->bevt_5_ta_ph = beq->beva_str->bem_sizeGet_0();
beq->bevl_rpos->bevi_int += beq->bevt_5_ta_ph->bevi_int;
beq->bevt_6_ta_ph = bevp_size->bem_subtract_1(beq->bevl_rpos);
return beq->bevt_6_ta_ph;
} 
return nullptr;
}
BEC_2_4_3_MathInt* BEC_2_4_6_TextString::bem_find_1(BEC_2_4_6_TextString* bevk_str) {
struct bes { BEC_2_4_6_TextString* beva_str; BEC_2_4_3_MathInt* bevt_0_ta_ph; BEC_2_4_3_MathInt* bevt_1_ta_ph; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->beva_str = bevk_str;
beq->bevt_0_ta_ph = nullptr;
beq->bevt_1_ta_ph = nullptr;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(4);
beq->bevt_1_ta_ph = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(0))));
beq->bevt_0_ta_ph = bem_find_2(beq->beva_str, beq->bevt_1_ta_ph);
return beq->bevt_0_ta_ph;
}
BEC_2_4_3_MathInt* BEC_2_4_6_TextString::bem_find_2(BEC_2_4_6_TextString* bevk_str, BEC_2_4_3_MathInt* bevk_start) {
struct bes { BEC_2_4_6_TextString* beva_str; BEC_2_4_3_MathInt* beva_start; BEC_2_4_3_MathInt* bevl_end; BEC_2_4_3_MathInt* bevl_current; BEC_2_4_3_MathInt* bevl_myval; BEC_2_4_3_MathInt* bevl_strfirst; BEC_2_4_3_MathInt* bevl_strsize; BEC_2_4_3_MathInt* bevl_strval; BEC_2_4_3_MathInt* bevl_current2; BEC_2_4_3_MathInt* bevl_end2; BEC_2_4_3_MathInt* bevl_currentstr2; BEC_2_5_4_LogicBool* bevt_0_ta_anchor; BEC_2_5_4_LogicBool* bevt_1_ta_anchor; BEC_2_5_4_LogicBool* bevt_2_ta_anchor; BEC_2_5_4_LogicBool* bevt_3_ta_anchor; BEC_2_5_4_LogicBool* bevt_4_ta_anchor; BEC_2_5_4_LogicBool* bevt_5_ta_anchor; BEC_2_5_4_LogicBool* bevt_6_ta_ph; BEC_2_5_4_LogicBool* bevt_7_ta_ph; BEC_2_5_4_LogicBool* bevt_8_ta_ph; BEC_2_4_3_MathInt* bevt_9_ta_ph; BEC_2_5_4_LogicBool* bevt_10_ta_ph; BEC_2_5_4_LogicBool* bevt_11_ta_ph; BEC_2_4_3_MathInt* bevt_12_ta_ph; BEC_2_5_4_LogicBool* bevt_13_ta_ph; BEC_2_4_3_MathInt* bevt_14_ta_ph; BEC_2_5_4_LogicBool* bevt_15_ta_ph; BEC_2_4_3_MathInt* bevt_16_ta_ph; BEC_2_4_3_MathInt* bevt_17_ta_ph; BEC_2_4_3_MathInt* bevt_18_ta_ph; BEC_2_5_4_LogicBool* bevt_19_ta_ph; BEC_2_4_3_MathInt* bevt_20_ta_ph; BEC_2_5_4_LogicBool* bevt_21_ta_ph; BEC_2_5_4_LogicBool* bevt_22_ta_ph; BEC_2_5_4_LogicBool* bevt_23_ta_ph; BEC_2_4_3_MathInt* bevt_24_ta_ph; BEC_2_4_3_MathInt* bevt_25_ta_ph; BEC_2_5_4_LogicBool* bevt_26_ta_ph; BEC_2_4_3_MathInt* bevt_27_ta_ph; BEC_2_5_4_LogicBool* bevt_28_ta_ph; BEC_2_5_4_LogicBool* bevt_29_ta_ph; BEC_2_5_4_LogicBool* bevt_30_ta_ph; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->beva_str = bevk_str;
beq->beva_start = bevk_start;
beq->bevl_end = nullptr;
beq->bevl_current = nullptr;
beq->bevl_myval = nullptr;
beq->bevl_strfirst = nullptr;
beq->bevl_strsize = nullptr;
beq->bevl_strval = nullptr;
beq->bevl_current2 = nullptr;
beq->bevl_end2 = nullptr;
beq->bevl_currentstr2 = nullptr;
beq->bevt_0_ta_anchor = nullptr;
beq->bevt_1_ta_anchor = nullptr;
beq->bevt_2_ta_anchor = nullptr;
beq->bevt_3_ta_anchor = nullptr;
beq->bevt_4_ta_anchor = nullptr;
beq->bevt_5_ta_anchor = nullptr;
beq->bevt_6_ta_ph = nullptr;
beq->bevt_7_ta_ph = nullptr;
beq->bevt_8_ta_ph = nullptr;
beq->bevt_9_ta_ph = nullptr;
beq->bevt_10_ta_ph = nullptr;
beq->bevt_11_ta_ph = nullptr;
beq->bevt_12_ta_ph = nullptr;
beq->bevt_13_ta_ph = nullptr;
beq->bevt_14_ta_ph = nullptr;
beq->bevt_15_ta_ph = nullptr;
beq->bevt_16_ta_ph = nullptr;
beq->bevt_17_ta_ph = nullptr;
beq->bevt_18_ta_ph = nullptr;
beq->bevt_19_ta_ph = nullptr;
beq->bevt_20_ta_ph = nullptr;
beq->bevt_21_ta_ph = nullptr;
beq->bevt_22_ta_ph = nullptr;
beq->bevt_23_ta_ph = nullptr;
beq->bevt_24_ta_ph = nullptr;
beq->bevt_25_ta_ph = nullptr;
beq->bevt_26_ta_ph = nullptr;
beq->bevt_27_ta_ph = nullptr;
beq->bevt_28_ta_ph = nullptr;
beq->bevt_29_ta_ph = nullptr;
beq->bevt_30_ta_ph = nullptr;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(43);
if (beq->beva_str == nullptr) {
beq->bevt_6_ta_ph = BECS_Runtime::boolTrue;
 } else { 
beq->bevt_6_ta_ph = BECS_Runtime::boolFalse;
}
if (beq->bevt_6_ta_ph->bevi_bool) {
beq->bevt_5_ta_anchor = BECS_Runtime::boolTrue;
} 
 else  {
if (beq->beva_start == nullptr) {
beq->bevt_7_ta_ph = BECS_Runtime::boolTrue;
 } else { 
beq->bevt_7_ta_ph = BECS_Runtime::boolFalse;
}
if (beq->bevt_7_ta_ph->bevi_bool) {
beq->bevt_5_ta_anchor = BECS_Runtime::boolTrue;
} 
 else  {
beq->bevt_5_ta_anchor = BECS_Runtime::boolFalse;
} 
} 
if (beq->bevt_5_ta_anchor->bevi_bool) {
beq->bevt_4_ta_anchor = BECS_Runtime::boolTrue;
} 
 else  {
beq->bevt_9_ta_ph = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(0))));
if (beq->beva_start->bevi_int < beq->bevt_9_ta_ph->bevi_int) {
beq->bevt_8_ta_ph = BECS_Runtime::boolTrue;
 } else { 
beq->bevt_8_ta_ph = BECS_Runtime::boolFalse;
}
if (beq->bevt_8_ta_ph->bevi_bool) {
beq->bevt_4_ta_anchor = BECS_Runtime::boolTrue;
} 
 else  {
beq->bevt_4_ta_anchor = BECS_Runtime::boolFalse;
} 
} 
if (beq->bevt_4_ta_anchor->bevi_bool) {
beq->bevt_3_ta_anchor = BECS_Runtime::boolTrue;
} 
 else  {
if (beq->beva_start->bevi_int >= bevp_size->bevi_int) {
beq->bevt_10_ta_ph = BECS_Runtime::boolTrue;
 } else { 
beq->bevt_10_ta_ph = BECS_Runtime::boolFalse;
}
if (beq->bevt_10_ta_ph->bevi_bool) {
beq->bevt_3_ta_anchor = BECS_Runtime::boolTrue;
} 
 else  {
beq->bevt_3_ta_anchor = BECS_Runtime::boolFalse;
} 
} 
if (beq->bevt_3_ta_anchor->bevi_bool) {
beq->bevt_2_ta_anchor = BECS_Runtime::boolTrue;
} 
 else  {
beq->bevt_12_ta_ph = beq->beva_str->bem_sizeGet_0();
if (beq->bevt_12_ta_ph->bevi_int > bevp_size->bevi_int) {
beq->bevt_11_ta_ph = BECS_Runtime::boolTrue;
 } else { 
beq->bevt_11_ta_ph = BECS_Runtime::boolFalse;
}
if (beq->bevt_11_ta_ph->bevi_bool) {
beq->bevt_2_ta_anchor = BECS_Runtime::boolTrue;
} 
 else  {
beq->bevt_2_ta_anchor = BECS_Runtime::boolFalse;
} 
} 
if (beq->bevt_2_ta_anchor->bevi_bool) {
beq->bevt_1_ta_anchor = BECS_Runtime::boolTrue;
} 
 else  {
beq->bevt_14_ta_ph = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(0))));
if (bevp_size->bevi_int == beq->bevt_14_ta_ph->bevi_int) {
beq->bevt_13_ta_ph = BECS_Runtime::boolTrue;
 } else { 
beq->bevt_13_ta_ph = BECS_Runtime::boolFalse;
}
if (beq->bevt_13_ta_ph->bevi_bool) {
beq->bevt_1_ta_anchor = BECS_Runtime::boolTrue;
} 
 else  {
beq->bevt_1_ta_anchor = BECS_Runtime::boolFalse;
} 
} 
if (beq->bevt_1_ta_anchor->bevi_bool) {
beq->bevt_0_ta_anchor = BECS_Runtime::boolTrue;
} 
 else  {
beq->bevt_16_ta_ph = beq->beva_str->bem_sizeGet_0();
beq->bevt_17_ta_ph = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(0))));
if (beq->bevt_16_ta_ph->bevi_int == beq->bevt_17_ta_ph->bevi_int) {
beq->bevt_15_ta_ph = BECS_Runtime::boolTrue;
 } else { 
beq->bevt_15_ta_ph = BECS_Runtime::boolFalse;
}
if (beq->bevt_15_ta_ph->bevi_bool) {
beq->bevt_0_ta_anchor = BECS_Runtime::boolTrue;
} 
 else  {
beq->bevt_0_ta_anchor = BECS_Runtime::boolFalse;
} 
} 
if (beq->bevt_0_ta_anchor->bevi_bool) {
return nullptr;
} 
beq->bevl_end = bevp_size;
beq->bevl_current = static_cast<BEC_2_4_3_MathInt*>(beq->beva_start->bem_copy_0());
beq->bevl_myval = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt())));
beq->bevl_strfirst = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt())));
beq->bevt_18_ta_ph = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(0))));
beq->beva_str->bem_getInt_2(beq->bevt_18_ta_ph, beq->bevl_strfirst);
beq->bevl_strsize = beq->beva_str->bem_sizeGet_0();
beq->bevt_20_ta_ph = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(1))));
if (beq->bevl_strsize->bevi_int > beq->bevt_20_ta_ph->bevi_int) {
beq->bevt_19_ta_ph = BECS_Runtime::boolTrue;
 } else { 
beq->bevt_19_ta_ph = BECS_Runtime::boolFalse;
}
if (beq->bevt_19_ta_ph->bevi_bool) {
beq->bevl_strval = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt())));
beq->bevl_current2 = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt())));
beq->bevl_end2 = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt())));
} 
beq->bevl_currentstr2 = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt())));
while (true)
 {
if (beq->bevl_current->bevi_int < beq->bevl_end->bevi_int) {
beq->bevt_21_ta_ph = BECS_Runtime::boolTrue;
 } else { 
beq->bevt_21_ta_ph = BECS_Runtime::boolFalse;
}
if (beq->bevt_21_ta_ph->bevi_bool) {
bem_getInt_2(beq->bevl_current, beq->bevl_myval);
if (beq->bevl_myval->bevi_int == beq->bevl_strfirst->bevi_int) {
beq->bevt_22_ta_ph = BECS_Runtime::boolTrue;
 } else { 
beq->bevt_22_ta_ph = BECS_Runtime::boolFalse;
}
if (beq->bevt_22_ta_ph->bevi_bool) {
beq->bevt_24_ta_ph = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(1))));
if (beq->bevl_strsize->bevi_int == beq->bevt_24_ta_ph->bevi_int) {
beq->bevt_23_ta_ph = BECS_Runtime::boolTrue;
 } else { 
beq->bevt_23_ta_ph = BECS_Runtime::boolFalse;
}
if (beq->bevt_23_ta_ph->bevi_bool) {
return beq->bevl_current;
} 
beq->bevl_current2->bevi_int = beq->bevl_current->bevi_int;
beq->bevl_current2->bevi_int++;
beq->bevl_end2->bevi_int = beq->bevl_current->bevi_int;
beq->bevt_25_ta_ph = beq->beva_str->bem_sizeGet_0();
beq->bevl_end2->bevi_int += beq->bevt_25_ta_ph->bevi_int;
if (beq->bevl_end2->bevi_int > bevp_size->bevi_int) {
beq->bevt_26_ta_ph = BECS_Runtime::boolTrue;
 } else { 
beq->bevt_26_ta_ph = BECS_Runtime::boolFalse;
}
if (beq->bevt_26_ta_ph->bevi_bool) {
return nullptr;
} 
beq->bevt_27_ta_ph = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(1))));
beq->bevl_currentstr2->bevi_int = beq->bevt_27_ta_ph->bevi_int;
while (true)
 {
if (beq->bevl_current2->bevi_int < beq->bevl_end2->bevi_int) {
beq->bevt_28_ta_ph = BECS_Runtime::boolTrue;
 } else { 
beq->bevt_28_ta_ph = BECS_Runtime::boolFalse;
}
if (beq->bevt_28_ta_ph->bevi_bool) {
bem_getInt_2(beq->bevl_current2, beq->bevl_myval);
beq->beva_str->bem_getInt_2(beq->bevl_currentstr2, beq->bevl_strval);
if (beq->bevl_myval->bevi_int != beq->bevl_strval->bevi_int) {
beq->bevt_29_ta_ph = BECS_Runtime::boolTrue;
 } else { 
beq->bevt_29_ta_ph = BECS_Runtime::boolFalse;
}
if (beq->bevt_29_ta_ph->bevi_bool) {
break;
} 
beq->bevl_current2->bevi_int++;
beq->bevl_currentstr2->bevi_int++;
} 
 else  {
break;
} 
} 
if (beq->bevl_current2->bevi_int == beq->bevl_end2->bevi_int) {
beq->bevt_30_ta_ph = BECS_Runtime::boolTrue;
 } else { 
beq->bevt_30_ta_ph = BECS_Runtime::boolFalse;
}
if (beq->bevt_30_ta_ph->bevi_bool) {
return beq->bevl_current;
} 
} 
beq->bevl_current->bevi_int++;
} 
 else  {
break;
} 
} 
return nullptr;
}
BEC_2_9_4_ContainerList* BEC_2_4_6_TextString::bem_split_1(BEC_2_4_6_TextString* bevk_delim) {
struct bes { BEC_2_4_6_TextString* beva_delim; BEC_2_9_4_ContainerList* bevl_splits; BEC_2_4_3_MathInt* bevl_last; BEC_2_4_3_MathInt* bevl_i; BEC_2_4_3_MathInt* bevl_ds; BEC_2_5_4_LogicBool* bevt_0_ta_ph; BEC_2_4_6_TextString* bevt_1_ta_ph; BEC_2_5_4_LogicBool* bevt_2_ta_ph; BEC_2_4_6_TextString* bevt_3_ta_ph; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->beva_delim = bevk_delim;
beq->bevl_splits = nullptr;
beq->bevl_last = nullptr;
beq->bevl_i = nullptr;
beq->bevl_ds = nullptr;
beq->bevt_0_ta_ph = nullptr;
beq->bevt_1_ta_ph = nullptr;
beq->bevt_2_ta_ph = nullptr;
beq->bevt_3_ta_ph = nullptr;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(10);
beq->bevl_splits = static_cast<BEC_2_9_4_ContainerList*>(((BEC_2_9_4_ContainerList*) (new BEC_2_9_4_ContainerList()))->bem_new_0());
beq->bevl_last = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(0))));
beq->bevl_i = bem_find_2(beq->beva_delim, beq->bevl_last);
beq->bevl_ds = beq->beva_delim->bem_sizeGet_0();
while (true)
 {
if (beq->bevl_i == nullptr) {
beq->bevt_0_ta_ph = BECS_Runtime::boolFalse;
 } else { 
beq->bevt_0_ta_ph = BECS_Runtime::boolTrue;
}
if (beq->bevt_0_ta_ph->bevi_bool) {
beq->bevt_1_ta_ph = bem_substring_2(beq->bevl_last, beq->bevl_i);
beq->bevl_splits->bem_addValue_1(beq->bevt_1_ta_ph);
beq->bevl_last = beq->bevl_i->bem_add_1(beq->bevl_ds);
beq->bevl_i = bem_find_2(beq->beva_delim, beq->bevl_last);
} 
 else  {
break;
} 
} 
if (beq->bevl_last->bevi_int < bevp_size->bevi_int) {
beq->bevt_2_ta_ph = BECS_Runtime::boolTrue;
 } else { 
beq->bevt_2_ta_ph = BECS_Runtime::boolFalse;
}
if (beq->bevt_2_ta_ph->bevi_bool) {
beq->bevt_3_ta_ph = bem_substring_2(beq->bevl_last, bevp_size);
beq->bevl_splits->bem_addValue_1(beq->bevt_3_ta_ph);
} 
return beq->bevl_splits;
}
BEC_2_4_6_TextString* BEC_2_4_6_TextString::bem_join_2(BEC_2_4_6_TextString* bevk_delim, BEC_2_6_6_SystemObject* bevk_splits) {
struct bes { BEC_2_4_6_TextString* beva_delim; BEC_2_6_6_SystemObject* beva_splits; BEC_2_4_6_TextString* bevt_0_ta_ph; BEC_2_4_7_TextStrings* bevt_1_ta_ph; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->beva_delim = bevk_delim;
beq->beva_splits = bevk_splits;
beq->bevt_0_ta_ph = nullptr;
beq->bevt_1_ta_ph = nullptr;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(5);
beq->bevt_1_ta_ph = static_cast<BEC_2_4_7_TextStrings*>(BEC_2_4_7_TextStrings::bece_BEC_2_4_7_TextStrings_bevs_inst);
beq->bevt_0_ta_ph = beq->bevt_1_ta_ph->bem_join_2(beq->beva_delim, beq->beva_splits);
return beq->bevt_0_ta_ph;
}
BEC_2_4_6_TextString* BEC_2_4_6_TextString::bem_toString_0() {
struct bes {  BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(1);
return this;
}
BEC_2_4_3_MathInt* BEC_2_4_6_TextString::bem_compare_1(BEC_2_6_6_SystemObject* bevk_stri) {
struct bes { BEC_2_6_6_SystemObject* beva_stri; BEC_2_4_3_MathInt* bevl_mysize; BEC_2_4_3_MathInt* bevl_osize; BEC_2_4_3_MathInt* bevl_maxsize; BEC_2_4_3_MathInt* bevl_myret; BEC_2_4_3_MathInt* bevl_mv; BEC_2_4_3_MathInt* bevl_ov; BEC_2_4_3_MathInt* bevl_i; BEC_2_5_4_LogicBool* bevt_0_ta_anchor; BEC_2_5_4_LogicBool* bevt_1_ta_ph; BEC_2_5_4_LogicBool* bevt_2_ta_ph; BEC_2_6_5_SystemTypes* bevt_3_ta_ph; BEC_2_5_4_LogicBool* bevt_4_ta_ph; BEC_2_5_4_LogicBool* bevt_5_ta_ph; BEC_2_5_4_LogicBool* bevt_6_ta_ph; BEC_2_5_4_LogicBool* bevt_7_ta_ph; BEC_2_4_3_MathInt* bevt_8_ta_ph; BEC_2_4_3_MathInt* bevt_9_ta_ph; BEC_2_5_4_LogicBool* bevt_10_ta_ph; BEC_2_4_3_MathInt* bevt_11_ta_ph; BEC_2_5_4_LogicBool* bevt_12_ta_ph; BEC_2_5_4_LogicBool* bevt_13_ta_ph; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->beva_stri = bevk_stri;
beq->bevl_mysize = nullptr;
beq->bevl_osize = nullptr;
beq->bevl_maxsize = nullptr;
beq->bevl_myret = nullptr;
beq->bevl_mv = nullptr;
beq->bevl_ov = nullptr;
beq->bevl_i = nullptr;
beq->bevt_0_ta_anchor = nullptr;
beq->bevt_1_ta_ph = nullptr;
beq->bevt_2_ta_ph = nullptr;
beq->bevt_3_ta_ph = nullptr;
beq->bevt_4_ta_ph = nullptr;
beq->bevt_5_ta_ph = nullptr;
beq->bevt_6_ta_ph = nullptr;
beq->bevt_7_ta_ph = nullptr;
beq->bevt_8_ta_ph = nullptr;
beq->bevt_9_ta_ph = nullptr;
beq->bevt_10_ta_ph = nullptr;
beq->bevt_11_ta_ph = nullptr;
beq->bevt_12_ta_ph = nullptr;
beq->bevt_13_ta_ph = nullptr;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(23);
if (beq->beva_stri == nullptr) {
beq->bevt_1_ta_ph = BECS_Runtime::boolTrue;
 } else { 
beq->bevt_1_ta_ph = BECS_Runtime::boolFalse;
}
if (beq->bevt_1_ta_ph->bevi_bool) {
beq->bevt_0_ta_anchor = BECS_Runtime::boolTrue;
} 
 else  {
beq->bevt_3_ta_ph = static_cast<BEC_2_6_5_SystemTypes*>(BEC_2_6_5_SystemTypes::bece_BEC_2_6_5_SystemTypes_bevs_inst);
beq->bevt_2_ta_ph = beq->bevt_3_ta_ph->bem_otherType_2(beq->beva_stri, this);
if (beq->bevt_2_ta_ph->bevi_bool) {
beq->bevt_0_ta_anchor = BECS_Runtime::boolTrue;
} 
 else  {
beq->bevt_0_ta_anchor = BECS_Runtime::boolFalse;
} 
} 
if (beq->bevt_0_ta_anchor->bevi_bool) {
return nullptr;
} 
beq->bevl_mysize = bevp_size;
beq->bevl_osize = static_cast<BEC_2_4_3_MathInt*>(beq->beva_stri->bemd_0(-443788785));
if (beq->bevl_mysize->bevi_int > beq->bevl_osize->bevi_int) {
beq->bevt_4_ta_ph = BECS_Runtime::boolTrue;
 } else { 
beq->bevt_4_ta_ph = BECS_Runtime::boolFalse;
}
if (beq->bevt_4_ta_ph->bevi_bool) {
beq->bevl_maxsize = beq->bevl_osize;
} 
 else  {
beq->bevl_maxsize = beq->bevl_mysize;
} 
beq->bevl_myret = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt())));
beq->bevl_mv = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt())));
beq->bevl_ov = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt())));
beq->bevl_i = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(0))));
while (true)
 {
if (beq->bevl_i->bevi_int < beq->bevl_maxsize->bevi_int) {
beq->bevt_5_ta_ph = BECS_Runtime::boolTrue;
 } else { 
beq->bevt_5_ta_ph = BECS_Runtime::boolFalse;
}
if (beq->bevt_5_ta_ph->bevi_bool) {
bem_getCode_2(beq->bevl_i, beq->bevl_mv);
beq->beva_stri->bemd_2(131208798, beq->bevl_i, beq->bevl_ov);
if (beq->bevl_mv->bevi_int != beq->bevl_ov->bevi_int) {
beq->bevt_6_ta_ph = BECS_Runtime::boolTrue;
 } else { 
beq->bevt_6_ta_ph = BECS_Runtime::boolFalse;
}
if (beq->bevt_6_ta_ph->bevi_bool) {
if (beq->bevl_mv->bevi_int > beq->bevl_ov->bevi_int) {
beq->bevt_7_ta_ph = BECS_Runtime::boolTrue;
 } else { 
beq->bevt_7_ta_ph = BECS_Runtime::boolFalse;
}
if (beq->bevt_7_ta_ph->bevi_bool) {
beq->bevt_8_ta_ph = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(1))));
return beq->bevt_8_ta_ph;
} 
 else  {
beq->bevt_9_ta_ph = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(-1))));
return beq->bevt_9_ta_ph;
} 
} 
beq->bevl_i->bevi_int++;
} 
 else  {
break;
} 
} 
beq->bevt_11_ta_ph = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(0))));
if (beq->bevl_myret->bevi_int == beq->bevt_11_ta_ph->bevi_int) {
beq->bevt_10_ta_ph = BECS_Runtime::boolTrue;
 } else { 
beq->bevt_10_ta_ph = BECS_Runtime::boolFalse;
}
if (beq->bevt_10_ta_ph->bevi_bool) {
if (beq->bevl_mysize->bevi_int > beq->bevl_osize->bevi_int) {
beq->bevt_12_ta_ph = BECS_Runtime::boolTrue;
 } else { 
beq->bevt_12_ta_ph = BECS_Runtime::boolFalse;
}
if (beq->bevt_12_ta_ph->bevi_bool) {
beq->bevl_myret = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(1))));
} 
 else  {
if (beq->bevl_osize->bevi_int > beq->bevl_mysize->bevi_int) {
beq->bevt_13_ta_ph = BECS_Runtime::boolTrue;
 } else { 
beq->bevt_13_ta_ph = BECS_Runtime::boolFalse;
}
if (beq->bevt_13_ta_ph->bevi_bool) {
beq->bevl_myret = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(-1))));
} 
} 
} 
return beq->bevl_myret;
}
BEC_2_5_4_LogicBool* BEC_2_4_6_TextString::bem_lesser_1(BEC_2_4_6_TextString* bevk_stri) {
struct bes { BEC_2_4_6_TextString* beva_stri; BEC_2_5_4_LogicBool* bevt_0_ta_ph; BEC_2_5_4_LogicBool* bevt_1_ta_ph; BEC_2_4_3_MathInt* bevt_2_ta_ph; BEC_2_4_3_MathInt* bevt_3_ta_ph; BEC_2_5_4_LogicBool* bevt_4_ta_ph; BEC_2_5_4_LogicBool* bevt_5_ta_ph; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->beva_stri = bevk_stri;
beq->bevt_0_ta_ph = nullptr;
beq->bevt_1_ta_ph = nullptr;
beq->bevt_2_ta_ph = nullptr;
beq->bevt_3_ta_ph = nullptr;
beq->bevt_4_ta_ph = nullptr;
beq->bevt_5_ta_ph = nullptr;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(8);
if (beq->beva_stri == nullptr) {
beq->bevt_0_ta_ph = BECS_Runtime::boolTrue;
 } else { 
beq->bevt_0_ta_ph = BECS_Runtime::boolFalse;
}
if (beq->bevt_0_ta_ph->bevi_bool) {
return nullptr;
} 
beq->bevt_2_ta_ph = bem_compare_1(beq->beva_stri);
beq->bevt_3_ta_ph = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(-1))));
if (beq->bevt_2_ta_ph->bevi_int == beq->bevt_3_ta_ph->bevi_int) {
beq->bevt_1_ta_ph = BECS_Runtime::boolTrue;
 } else { 
beq->bevt_1_ta_ph = BECS_Runtime::boolFalse;
}
if (beq->bevt_1_ta_ph->bevi_bool) {
beq->bevt_4_ta_ph = static_cast<BEC_2_5_4_LogicBool*>(BECS_Runtime::boolTrue);
return beq->bevt_4_ta_ph;
} 
beq->bevt_5_ta_ph = static_cast<BEC_2_5_4_LogicBool*>(BECS_Runtime::boolFalse);
return beq->bevt_5_ta_ph;
}
BEC_2_5_4_LogicBool* BEC_2_4_6_TextString::bem_greater_1(BEC_2_4_6_TextString* bevk_stri) {
struct bes { BEC_2_4_6_TextString* beva_stri; BEC_2_5_4_LogicBool* bevt_0_ta_ph; BEC_2_5_4_LogicBool* bevt_1_ta_ph; BEC_2_4_3_MathInt* bevt_2_ta_ph; BEC_2_4_3_MathInt* bevt_3_ta_ph; BEC_2_5_4_LogicBool* bevt_4_ta_ph; BEC_2_5_4_LogicBool* bevt_5_ta_ph; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->beva_stri = bevk_stri;
beq->bevt_0_ta_ph = nullptr;
beq->bevt_1_ta_ph = nullptr;
beq->bevt_2_ta_ph = nullptr;
beq->bevt_3_ta_ph = nullptr;
beq->bevt_4_ta_ph = nullptr;
beq->bevt_5_ta_ph = nullptr;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(8);
if (beq->beva_stri == nullptr) {
beq->bevt_0_ta_ph = BECS_Runtime::boolTrue;
 } else { 
beq->bevt_0_ta_ph = BECS_Runtime::boolFalse;
}
if (beq->bevt_0_ta_ph->bevi_bool) {
return nullptr;
} 
beq->bevt_2_ta_ph = bem_compare_1(beq->beva_stri);
beq->bevt_3_ta_ph = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(1))));
if (beq->bevt_2_ta_ph->bevi_int == beq->bevt_3_ta_ph->bevi_int) {
beq->bevt_1_ta_ph = BECS_Runtime::boolTrue;
 } else { 
beq->bevt_1_ta_ph = BECS_Runtime::boolFalse;
}
if (beq->bevt_1_ta_ph->bevi_bool) {
beq->bevt_4_ta_ph = static_cast<BEC_2_5_4_LogicBool*>(BECS_Runtime::boolTrue);
return beq->bevt_4_ta_ph;
} 
beq->bevt_5_ta_ph = static_cast<BEC_2_5_4_LogicBool*>(BECS_Runtime::boolFalse);
return beq->bevt_5_ta_ph;
}
BEC_2_5_4_LogicBool* BEC_2_4_6_TextString::bem_equals_1(BEC_2_6_6_SystemObject* bevk_stri) {
struct bes { BEC_2_6_6_SystemObject* beva_stri; BEC_2_5_4_LogicBool* bevt_0_ta_ph; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->beva_stri = bevk_stri;
beq->bevt_0_ta_ph = nullptr;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(3);

#ifndef BEDCC_NORTTI
      BEC_2_4_6_TextString* bevls_stri = dynamic_cast<BEC_2_4_6_TextString*>(beq->beva_stri);
#endif
#ifdef BEDCC_NORTTI
      BEC_2_4_6_TextString* bevls_stri = static_cast<BEC_2_4_6_TextString*>(beq->beva_stri);
#endif
    if (bevp_size->bevi_int == bevls_stri->bevp_size->bevi_int) {
       for (int32_t i = 0;i < bevp_size->bevi_int;i++) {
          if (bevi_bytes[i] != bevls_stri->bevi_bytes[i]) {
            return BECS_Runtime::boolFalse;
          }
       }
       return BECS_Runtime::boolTrue;
   }
  beq->bevt_0_ta_ph = static_cast<BEC_2_5_4_LogicBool*>(BECS_Runtime::boolFalse);
return beq->bevt_0_ta_ph;
}
BEC_2_5_4_LogicBool* BEC_2_4_6_TextString::bem_notEquals_1(BEC_2_6_6_SystemObject* bevk_str) {
struct bes { BEC_2_6_6_SystemObject* beva_str; BEC_2_5_4_LogicBool* bevt_0_ta_ph; BEC_2_5_4_LogicBool* bevt_1_ta_ph; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->beva_str = bevk_str;
beq->bevt_0_ta_ph = nullptr;
beq->bevt_1_ta_ph = nullptr;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(4);
beq->bevt_1_ta_ph = bem_equals_1(beq->beva_str);
if (beq->bevt_1_ta_ph->bevi_bool) {
beq->bevt_0_ta_ph = BECS_Runtime::boolFalse;
 } else { 
beq->bevt_0_ta_ph = BECS_Runtime::boolTrue;
}
return beq->bevt_0_ta_ph;
}
BEC_2_4_6_TextString* BEC_2_4_6_TextString::bem_add_1(BEC_2_6_6_SystemObject* bevk_astr) {
struct bes { BEC_2_6_6_SystemObject* beva_astr; BEC_2_4_6_TextString* bevl_str; BEC_2_4_6_TextString* bevl_res; BEC_2_4_3_MathInt* bevt_0_ta_ph; BEC_2_4_3_MathInt* bevt_1_ta_ph; BEC_2_4_3_MathInt* bevt_2_ta_ph; BEC_2_4_3_MathInt* bevt_3_ta_ph; BEC_2_4_3_MathInt* bevt_4_ta_ph; BEC_2_4_3_MathInt* bevt_5_ta_ph; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->beva_astr = bevk_astr;
beq->bevl_str = nullptr;
beq->bevl_res = nullptr;
beq->bevt_0_ta_ph = nullptr;
beq->bevt_1_ta_ph = nullptr;
beq->bevt_2_ta_ph = nullptr;
beq->bevt_3_ta_ph = nullptr;
beq->bevt_4_ta_ph = nullptr;
beq->bevt_5_ta_ph = nullptr;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(10);
beq->bevl_str = static_cast<BEC_2_4_6_TextString*>(beq->beva_astr->bemd_0(-1553512291));
beq->bevt_1_ta_ph = beq->bevl_str->bem_sizeGet_0();
beq->bevt_0_ta_ph = bevp_size->bem_add_1(beq->bevt_1_ta_ph);
beq->bevl_res = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString()))->bem_new_1(beq->bevt_0_ta_ph));
beq->bevt_2_ta_ph = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(0))));
beq->bevt_3_ta_ph = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(0))));
beq->bevl_res->bem_copyValue_4(this, beq->bevt_2_ta_ph, bevp_size, beq->bevt_3_ta_ph);
beq->bevt_4_ta_ph = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(0))));
beq->bevt_5_ta_ph = beq->bevl_str->bem_sizeGet_0();
beq->bevl_res->bem_copyValue_4(beq->bevl_str, beq->bevt_4_ta_ph, beq->bevt_5_ta_ph, bevp_size);
return beq->bevl_res;
}
BEC_2_6_6_SystemObject* BEC_2_4_6_TextString::bem_create_0() {
struct bes { BEC_2_4_6_TextString* bevt_0_ta_ph; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->bevt_0_ta_ph = nullptr;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(2);
beq->bevt_0_ta_ph = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString()))->bem_new_0());
return static_cast<BEC_2_6_6_SystemObject*>(beq->bevt_0_ta_ph);
}
BEC_2_4_6_TextString* BEC_2_4_6_TextString::bem_copyValue_4(BEC_2_4_6_TextString* bevk_org, BEC_2_4_3_MathInt* bevk_starti, BEC_2_4_3_MathInt* bevk_endi, BEC_2_4_3_MathInt* bevk_dstarti) {
struct bes { BEC_2_4_6_TextString* beva_org; BEC_2_4_3_MathInt* beva_starti; BEC_2_4_3_MathInt* beva_endi; BEC_2_4_3_MathInt* beva_dstarti; BEC_2_4_3_MathInt* bevl_leni; BEC_2_4_3_MathInt* bevl_mleni; BEC_2_4_3_MathInt* bevl_sizi; BEC_2_5_4_LogicBool* bevt_0_ta_anchor; BEC_2_5_4_LogicBool* bevt_1_ta_ph; BEC_2_4_3_MathInt* bevt_2_ta_ph; BEC_2_4_7_TextStrings* bevt_3_ta_ph; BEC_2_5_4_LogicBool* bevt_4_ta_ph; BEC_2_4_3_MathInt* bevt_5_ta_ph; BEC_2_5_4_LogicBool* bevt_6_ta_ph; BEC_2_4_3_MathInt* bevt_7_ta_ph; BEC_2_6_9_SystemException* bevt_8_ta_ph; BEC_2_4_6_TextString* bevt_9_ta_ph; BEC_2_5_4_LogicBool* bevt_10_ta_ph; BEC_2_5_4_LogicBool* bevt_11_ta_ph; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->beva_org = bevk_org;
beq->beva_starti = bevk_starti;
beq->beva_endi = bevk_endi;
beq->beva_dstarti = bevk_dstarti;
beq->bevl_leni = nullptr;
beq->bevl_mleni = nullptr;
beq->bevl_sizi = nullptr;
beq->bevt_0_ta_anchor = nullptr;
beq->bevt_1_ta_ph = nullptr;
beq->bevt_2_ta_ph = nullptr;
beq->bevt_3_ta_ph = nullptr;
beq->bevt_4_ta_ph = nullptr;
beq->bevt_5_ta_ph = nullptr;
beq->bevt_6_ta_ph = nullptr;
beq->bevt_7_ta_ph = nullptr;
beq->bevt_8_ta_ph = nullptr;
beq->bevt_9_ta_ph = nullptr;
beq->bevt_10_ta_ph = nullptr;
beq->bevt_11_ta_ph = nullptr;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(20);
beq->bevt_3_ta_ph = static_cast<BEC_2_4_7_TextStrings*>(BEC_2_4_7_TextStrings::bece_BEC_2_4_7_TextStrings_bevs_inst);
beq->bevt_2_ta_ph = beq->bevt_3_ta_ph->bem_zeroGet_0();
if (beq->beva_starti->bevi_int < beq->bevt_2_ta_ph->bevi_int) {
beq->bevt_1_ta_ph = BECS_Runtime::boolTrue;
 } else { 
beq->bevt_1_ta_ph = BECS_Runtime::boolFalse;
}
if (beq->bevt_1_ta_ph->bevi_bool) {
beq->bevt_0_ta_anchor = BECS_Runtime::boolTrue;
} 
 else  {
beq->bevt_5_ta_ph = beq->beva_org->bem_sizeGet_0();
if (beq->beva_starti->bevi_int > beq->bevt_5_ta_ph->bevi_int) {
beq->bevt_4_ta_ph = BECS_Runtime::boolTrue;
 } else { 
beq->bevt_4_ta_ph = BECS_Runtime::boolFalse;
}
if (beq->bevt_4_ta_ph->bevi_bool) {
beq->bevt_0_ta_anchor = BECS_Runtime::boolTrue;
} 
 else  {
beq->bevt_7_ta_ph = beq->beva_org->bem_sizeGet_0();
if (beq->beva_endi->bevi_int > beq->bevt_7_ta_ph->bevi_int) {
beq->bevt_6_ta_ph = BECS_Runtime::boolTrue;
 } else { 
beq->bevt_6_ta_ph = BECS_Runtime::boolFalse;
}
if (beq->bevt_6_ta_ph->bevi_bool) {
beq->bevt_0_ta_anchor = BECS_Runtime::boolTrue;
} 
 else  {
beq->bevt_0_ta_anchor = BECS_Runtime::boolFalse;
} 
} 
if (beq->bevt_0_ta_anchor->bevi_bool) {
beq->bevt_0_ta_anchor = BECS_Runtime::boolTrue;
} 
 else  {
beq->bevt_0_ta_anchor = BECS_Runtime::boolFalse;
} 
} 
if (beq->bevt_0_ta_anchor->bevi_bool) {
beq->bevt_9_ta_ph = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString(31, {0x63,0x6F,0x70,0x79,0x56,0x61,0x6C,0x75,0x65,0x20,0x72,0x65,0x71,0x75,0x65,0x73,0x74,0x20,0x6F,0x75,0x74,0x20,0x6F,0x66,0x20,0x62,0x6F,0x75,0x6E,0x64,0x73}))));
beq->bevt_8_ta_ph = static_cast<BEC_2_6_9_SystemException*>(((BEC_2_6_9_SystemException*) (new BEC_2_6_9_SystemException()))->bem_new_1(beq->bevt_9_ta_ph));
throw BECS_ThrowBack(beq->bevt_8_ta_ph);
} 
 else  {
beq->bevl_leni = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt())));
beq->bevl_leni->bevi_int = beq->beva_endi->bevi_int;
beq->bevl_leni->bem_subtractValue_1(beq->beva_starti);
beq->bevl_mleni = beq->bevl_leni;
beq->bevl_sizi = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt())));
beq->bevl_sizi->bevi_int = beq->beva_dstarti->bevi_int;
beq->bevl_sizi->bevi_int += beq->bevl_leni->bevi_int;
if (beq->bevl_sizi->bevi_int > bevp_capacity->bevi_int) {
beq->bevt_10_ta_ph = BECS_Runtime::boolTrue;
 } else { 
beq->bevt_10_ta_ph = BECS_Runtime::boolFalse;
}
if (beq->bevt_10_ta_ph->bevi_bool) {
bem_capacitySet_1(beq->bevl_sizi);
} 

         for (int32_t i = 0; i < beq->bevl_mleni->bevi_int;i++) {
            bevi_bytes[i + beq->beva_dstarti->bevi_int] = beq->beva_org->bevi_bytes[i + beq->beva_starti->bevi_int];
         }
         if (beq->bevl_sizi->bevi_int > bevp_size->bevi_int) {
beq->bevt_11_ta_ph = BECS_Runtime::boolTrue;
 } else { 
beq->bevt_11_ta_ph = BECS_Runtime::boolFalse;
}
if (beq->bevt_11_ta_ph->bevi_bool) {
bevp_size->bevi_int = beq->bevl_sizi->bevi_int;
} 
return this;
} 
}
BEC_2_4_6_TextString* BEC_2_4_6_TextString::bem_substring_1(BEC_2_4_3_MathInt* bevk_starti) {
struct bes { BEC_2_4_3_MathInt* beva_starti; BEC_2_4_6_TextString* bevt_0_ta_ph; BEC_2_4_3_MathInt* bevt_1_ta_ph; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->beva_starti = bevk_starti;
beq->bevt_0_ta_ph = nullptr;
beq->bevt_1_ta_ph = nullptr;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(4);
beq->bevt_1_ta_ph = bem_sizeGet_0();
beq->bevt_0_ta_ph = bem_substring_2(beq->beva_starti, beq->bevt_1_ta_ph);
return beq->bevt_0_ta_ph;
}
BEC_2_4_6_TextString* BEC_2_4_6_TextString::bem_substring_2(BEC_2_4_3_MathInt* bevk_starti, BEC_2_4_3_MathInt* bevk_endi) {
struct bes { BEC_2_4_3_MathInt* beva_starti; BEC_2_4_3_MathInt* beva_endi; BEC_2_4_6_TextString* bevt_0_ta_ph; BEC_2_4_6_TextString* bevt_1_ta_ph; BEC_2_4_3_MathInt* bevt_2_ta_ph; BEC_2_4_3_MathInt* bevt_3_ta_ph; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->beva_starti = bevk_starti;
beq->beva_endi = bevk_endi;
beq->bevt_0_ta_ph = nullptr;
beq->bevt_1_ta_ph = nullptr;
beq->bevt_2_ta_ph = nullptr;
beq->bevt_3_ta_ph = nullptr;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(7);
beq->bevt_2_ta_ph = beq->beva_endi->bem_subtract_1(beq->beva_starti);
beq->bevt_1_ta_ph = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString()))->bem_new_1(beq->bevt_2_ta_ph));
beq->bevt_3_ta_ph = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(0))));
beq->bevt_0_ta_ph = static_cast<BEC_2_4_6_TextString*>(beq->bevt_1_ta_ph->bem_copyValue_4(this, beq->beva_starti, beq->beva_endi, beq->bevt_3_ta_ph));
return beq->bevt_0_ta_ph;
}
BEC_2_4_6_TextString* BEC_2_4_6_TextString::bem_output_0() {
struct bes {  BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(1);
return this;
}
BEC_2_6_6_SystemObject* BEC_2_4_6_TextString::bem_print_0() {
struct bes { BEC_2_6_6_SystemObject* bevl_pl; BEC_2_6_6_SystemObject* bevl_concon; BEC_2_5_4_LogicBool* bevt_0_ta_anchor; BEC_2_8_3_EmbeddedApp* bevt_1_ta_ph; BEC_2_5_4_LogicBool* bevt_2_ta_ph; BEC_2_5_4_LogicBool* bevt_3_ta_ph; BEC_2_6_6_SystemObject* bevt_4_ta_ph; BEC_2_4_6_TextString* bevt_5_ta_ph; BEC_2_4_7_TextStrings* bevt_6_ta_ph; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->bevl_pl = nullptr;
beq->bevl_concon = nullptr;
beq->bevt_0_ta_anchor = nullptr;
beq->bevt_1_ta_ph = nullptr;
beq->bevt_2_ta_ph = nullptr;
beq->bevt_3_ta_ph = nullptr;
beq->bevt_4_ta_ph = nullptr;
beq->bevt_5_ta_ph = nullptr;
beq->bevt_6_ta_ph = nullptr;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(10);

#ifdef BEDCC_ISIOS
    NSLog(@"%@", @(this->bems_toCcString().c_str()));
#endif

#ifndef BEDCC_ISIOS
     std::cout.write(reinterpret_cast<const char*>(&bevi_bytes[0]), bevp_size->bevi_int);
     std::cout << std::endl;
#endif
     beq->bevt_1_ta_ph = static_cast<BEC_2_8_3_EmbeddedApp*>(BEC_2_8_3_EmbeddedApp::bece_BEC_2_8_3_EmbeddedApp_bevs_inst);
beq->bevl_pl = beq->bevt_1_ta_ph->bem_pluginGet_0();
if (beq->bevl_pl == nullptr) {
beq->bevt_2_ta_ph = BECS_Runtime::boolFalse;
 } else { 
beq->bevt_2_ta_ph = BECS_Runtime::boolTrue;
}
if (beq->bevt_2_ta_ph->bevi_bool) {
beq->bevl_concon = beq->bevl_pl->bemd_0(-1512853507);
if (beq->bevl_concon == nullptr) {
beq->bevt_3_ta_ph = BECS_Runtime::boolFalse;
 } else { 
beq->bevt_3_ta_ph = BECS_Runtime::boolTrue;
}
if (beq->bevt_3_ta_ph->bevi_bool) {
beq->bevt_4_ta_ph = beq->bevl_concon->bemd_0(-183529491);
if ((static_cast<BEC_2_5_4_LogicBool*>(beq->bevt_4_ta_ph))->bevi_bool) {
beq->bevt_0_ta_anchor = BECS_Runtime::boolTrue;
} 
 else  {
beq->bevt_0_ta_anchor = BECS_Runtime::boolFalse;
} 
} 
 else  {
beq->bevt_0_ta_anchor = BECS_Runtime::boolFalse;
} 
if (beq->bevt_0_ta_anchor->bevi_bool) {
beq->bevl_concon->bemd_1(1129103463, this);
beq->bevt_6_ta_ph = static_cast<BEC_2_4_7_TextStrings*>(BEC_2_4_7_TextStrings::bece_BEC_2_4_7_TextStrings_bevs_inst);
beq->bevt_5_ta_ph = beq->bevt_6_ta_ph->bem_unixNewlineGet_0();
beq->bevl_concon->bemd_1(1129103463, beq->bevt_5_ta_ph);
} 
} 
return this;
}
BEC_2_4_6_TextString* BEC_2_4_6_TextString::bem_echo_0() {
struct bes {  BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(1);
bem_output_0();
return this;
}
BEC_2_6_6_SystemObject* BEC_2_4_6_TextString::bem_iteratorGet_0() {
struct bes { BEC_2_4_17_TextMultiByteIterator* bevt_0_ta_ph; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->bevt_0_ta_ph = nullptr;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(2);
beq->bevt_0_ta_ph = static_cast<BEC_2_4_17_TextMultiByteIterator*>(((BEC_2_4_17_TextMultiByteIterator*) (new BEC_2_4_17_TextMultiByteIterator()))->bem_new_1(this));
return beq->bevt_0_ta_ph;
}
BEC_2_4_12_TextByteIterator* BEC_2_4_6_TextString::bem_byteIteratorGet_0() {
struct bes { BEC_2_4_12_TextByteIterator* bevt_0_ta_ph; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->bevt_0_ta_ph = nullptr;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(2);
beq->bevt_0_ta_ph = static_cast<BEC_2_4_12_TextByteIterator*>(((BEC_2_4_12_TextByteIterator*) (new BEC_2_4_12_TextByteIterator()))->bem_new_1(this));
return beq->bevt_0_ta_ph;
}
BEC_2_4_17_TextMultiByteIterator* BEC_2_4_6_TextString::bem_multiByteIteratorGet_0() {
struct bes { BEC_2_4_17_TextMultiByteIterator* bevt_0_ta_ph; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->bevt_0_ta_ph = nullptr;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(2);
beq->bevt_0_ta_ph = static_cast<BEC_2_4_17_TextMultiByteIterator*>(((BEC_2_4_17_TextMultiByteIterator*) (new BEC_2_4_17_TextMultiByteIterator()))->bem_new_1(this));
return beq->bevt_0_ta_ph;
}
BEC_2_4_12_TextByteIterator* BEC_2_4_6_TextString::bem_biterGet_0() {
struct bes { BEC_2_4_12_TextByteIterator* bevt_0_ta_ph; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->bevt_0_ta_ph = nullptr;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(2);
beq->bevt_0_ta_ph = static_cast<BEC_2_4_12_TextByteIterator*>(((BEC_2_4_12_TextByteIterator*) (new BEC_2_4_12_TextByteIterator()))->bem_new_1(this));
return beq->bevt_0_ta_ph;
}
BEC_2_4_17_TextMultiByteIterator* BEC_2_4_6_TextString::bem_mbiterGet_0() {
struct bes { BEC_2_4_17_TextMultiByteIterator* bevt_0_ta_ph; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->bevt_0_ta_ph = nullptr;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(2);
beq->bevt_0_ta_ph = static_cast<BEC_2_4_17_TextMultiByteIterator*>(((BEC_2_4_17_TextMultiByteIterator*) (new BEC_2_4_17_TextMultiByteIterator()))->bem_new_1(this));
return beq->bevt_0_ta_ph;
}
BEC_2_4_17_TextMultiByteIterator* BEC_2_4_6_TextString::bem_stringIteratorGet_0() {
struct bes { BEC_2_4_17_TextMultiByteIterator* bevt_0_ta_ph; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->bevt_0_ta_ph = nullptr;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(2);
beq->bevt_0_ta_ph = static_cast<BEC_2_4_17_TextMultiByteIterator*>(((BEC_2_4_17_TextMultiByteIterator*) (new BEC_2_4_17_TextMultiByteIterator()))->bem_new_1(this));
return beq->bevt_0_ta_ph;
}
BEC_2_4_6_TextString* BEC_2_4_6_TextString::bem_serializeToString_0() {
struct bes {  BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(1);
return this;
}
BEC_2_4_6_TextString* BEC_2_4_6_TextString::bem_deserializeFromStringNew_1(BEC_2_4_6_TextString* bevk_snw) {
struct bes { BEC_2_4_6_TextString* beva_snw; BEC_2_5_4_LogicBool* bevt_0_ta_ph; BEC_2_4_3_MathInt* bevt_1_ta_ph; BEC_2_4_3_MathInt* bevt_2_ta_ph; BEC_2_4_3_MathInt* bevt_3_ta_ph; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->beva_snw = bevk_snw;
beq->bevt_0_ta_ph = nullptr;
beq->bevt_1_ta_ph = nullptr;
beq->bevt_2_ta_ph = nullptr;
beq->bevt_3_ta_ph = nullptr;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(6);
if (beq->beva_snw == nullptr) {
beq->bevt_0_ta_ph = BECS_Runtime::boolTrue;
 } else { 
beq->bevt_0_ta_ph = BECS_Runtime::boolFalse;
}
if (beq->bevt_0_ta_ph->bevi_bool) {
bem_new_0();
} 
 else  {
beq->bevt_2_ta_ph = beq->beva_snw->bem_sizeGet_0();
beq->bevt_3_ta_ph = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(1))));
beq->bevt_1_ta_ph = beq->bevt_2_ta_ph->bem_add_1(beq->bevt_3_ta_ph);
bem_new_1(beq->bevt_1_ta_ph);
bem_addValue_1(beq->beva_snw);
} 
return this;
}
BEC_2_5_4_LogicBool* BEC_2_4_6_TextString::bem_serializeContentsGet_0() {
struct bes { BEC_2_5_4_LogicBool* bevt_0_ta_ph; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->bevt_0_ta_ph = nullptr;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(2);
beq->bevt_0_ta_ph = static_cast<BEC_2_5_4_LogicBool*>(BECS_Runtime::boolFalse);
return beq->bevt_0_ta_ph;
}
BEC_2_6_6_SystemObject* BEC_2_4_6_TextString::bem_strip_0() {
struct bes { BEC_2_6_6_SystemObject* bevt_0_ta_ph; BEC_2_4_7_TextStrings* bevt_1_ta_ph; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->bevt_0_ta_ph = nullptr;
beq->bevt_1_ta_ph = nullptr;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(3);
beq->bevt_1_ta_ph = static_cast<BEC_2_4_7_TextStrings*>(BEC_2_4_7_TextStrings::bece_BEC_2_4_7_TextStrings_bevs_inst);
beq->bevt_0_ta_ph = beq->bevt_1_ta_ph->bem_strip_1(this);
return beq->bevt_0_ta_ph;
}
BEC_2_4_6_TextString* BEC_2_4_6_TextString::bem_reverseBytes_0() {
struct bes { BEC_2_4_3_MathInt* bevl_vb; BEC_2_4_3_MathInt* bevl_ve; BEC_2_4_3_MathInt* bevl_b; BEC_2_4_3_MathInt* bevl_e; BEC_2_4_3_MathInt* bevt_0_ta_ph; BEC_2_5_4_LogicBool* bevt_1_ta_ph; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->bevl_vb = nullptr;
beq->bevl_ve = nullptr;
beq->bevl_b = nullptr;
beq->bevl_e = nullptr;
beq->bevt_0_ta_ph = nullptr;
beq->bevt_1_ta_ph = nullptr;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(7);
beq->bevl_vb = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt())));
beq->bevl_ve = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt())));
beq->bevl_b = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(0))));
beq->bevt_0_ta_ph = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(1))));
beq->bevl_e = bevp_size->bem_subtract_1(beq->bevt_0_ta_ph);
while (true)
 {
if (beq->bevl_e->bevi_int > beq->bevl_b->bevi_int) {
beq->bevt_1_ta_ph = BECS_Runtime::boolTrue;
 } else { 
beq->bevt_1_ta_ph = BECS_Runtime::boolFalse;
}
if (beq->bevt_1_ta_ph->bevi_bool) {
bem_getInt_2(beq->bevl_b, beq->bevl_vb);
bem_getInt_2(beq->bevl_e, beq->bevl_ve);
bem_setInt_2(beq->bevl_b, beq->bevl_ve);
bem_setInt_2(beq->bevl_e, beq->bevl_vb);
beq->bevl_b->bevi_int++;
beq->bevl_e->bem_decrementValue_0();
} 
 else  {
break;
} 
} 
return this;
}
BEC_2_4_3_MathInt* BEC_2_4_6_TextString::bem_sizeGet_0() {
struct bes {  BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(1);
return bevp_size;
}
BEC_2_4_6_TextString* BEC_2_4_6_TextString::bem_sizeSet_1(BEC_2_6_6_SystemObject* bevt_0_ta_SET) {
struct bes { BEC_2_6_6_SystemObject* bevt_0_ta_SET; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->bevt_0_ta_SET = bevt_0_ta_SET;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(2);
bevp_size = static_cast<BEC_2_4_3_MathInt*>(beq->bevt_0_ta_SET);
return this;
}
BEC_2_4_3_MathInt* BEC_2_4_6_TextString::bem_capacityGet_0() {
struct bes {  BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(1);
return bevp_capacity;
}
BEC_2_6_6_SystemObject* BEC_2_4_6_TextString::bemd_0(int32_t callId) {
switch (callId) {
case -534328503: return bem_serializeContentsGet_0();
case 1030934124: return bem_open_0();
case 237293377: return bem_lowerValue_0();
case -49715204: return bem_readBuffer_0();
case 950712084: return bem_serializeToString_0();
case 517283222: return bem_mbiterGet_0();
case -1915711376: return bem_isAlphaNumGet_0();
case -1546907271: return bem_close_0();
case -1677156504: return bem_hashGet_0();
case -443788785: return bem_sizeGet_0();
case 227052708: return bem_isInteger_0();
case -459248972: return bem_upper_0();
case -1155747893: return bem_lower_0();
case 1802312682: return bem_strip_0();
case -2007913808: return bem_toAlphaNum_0();
case 904075520: return bem_upperValue_0();
case -1553512291: return bem_toString_0();
case -1475798894: return bem_multiByteIteratorGet_0();
case -1296317310: return bem_isAlphaNumericGet_0();
case -1605438187: return bem_vstringGet_0();
case -1445610842: return bem_capacityGet_0();
case -1566936209: return bem_chomp_0();
case 1234063303: return bem_echo_0();
case -1343052705: return bem_stringIteratorGet_0();
case 1551129214: return bem_clear_0();
case 1223754425: return bem_output_0();
case 590752678: return bem_vstringSet_0();
case 285667512: return bem_isIntegerGet_0();
case 131990292: return bem_readString_0();
case -1428269309: return bem_iteratorGet_0();
case 1231811798: return bem_extractString_0();
case -830083990: return bem_reverseBytes_0();
case 1701756138: return bem_print_0();
case -1970706839: return bem_biterGet_0();
case -1785532669: return bem_new_0();
case 2053303229: return bem_isEmptyGet_0();
case 1312387167: return bem_create_0();
case 2142500088: return bem_copy_0();
case -457332879: return bem_byteIteratorGet_0();
}
return bevs_super::bemd_0(callId);
}
BEC_2_6_6_SystemObject* BEC_2_4_6_TextString::bemd_1(int32_t callId, BEC_2_6_6_SystemObject* bevd_0) {
switch (callId) {
case 1294772652: return bem_writeTo_1(bevd_0);
case 1039122802: return bem_notEquals_1(bevd_0);
case -509225527: return bem_begins_1(static_cast<BEC_2_4_6_TextString*>(bevd_0));
case -1618488206: return bem_deserializeFromStringNew_1(static_cast<BEC_2_4_6_TextString*>(bevd_0));
case -504553897: return bem_sizeSet_1(bevd_0);
case -206108566: return bem_greater_1(static_cast<BEC_2_4_6_TextString*>(bevd_0));
case 1325848887: return bem_addValue_1(bevd_0);
case -842994802: return bem_capacitySet_1(static_cast<BEC_2_4_3_MathInt*>(bevd_0));
case -1215580115: return bem_getPoint_1(static_cast<BEC_2_4_3_MathInt*>(bevd_0));
case 1547801726: return bem_getCode_1(static_cast<BEC_2_4_3_MathInt*>(bevd_0));
case 1110980433: return bem_reverseFind_1(static_cast<BEC_2_4_6_TextString*>(bevd_0));
case -676350368: return bem_ends_1(static_cast<BEC_2_4_6_TextString*>(bevd_0));
case 1386790685: return bem_getHex_1(static_cast<BEC_2_4_3_MathInt*>(bevd_0));
case 1129103463: return bem_write_1(bevd_0);
case 2003075056: return bem_rfind_1(static_cast<BEC_2_4_6_TextString*>(bevd_0));
case 40746631: return bem_compare_1(bevd_0);
case 1911891644: return bem_lesser_1(static_cast<BEC_2_4_6_TextString*>(bevd_0));
case 202420412: return bem_add_1(bevd_0);
case 643138569: return bem_equals_1(bevd_0);
case -1572266813: return bem_codeNew_1(bevd_0);
case 415584667: return bem_find_1(static_cast<BEC_2_4_6_TextString*>(bevd_0));
case -1432506154: return bem_hashValue_1(static_cast<BEC_2_4_3_MathInt*>(bevd_0));
case -1666740144: return bem_split_1(static_cast<BEC_2_4_6_TextString*>(bevd_0));
case 262380141: return bem_has_1(static_cast<BEC_2_4_6_TextString*>(bevd_0));
case 1899676304: return bem_new_1(static_cast<BEC_2_4_3_MathInt*>(bevd_0));
case 639868603: return bem_hexNew_1(static_cast<BEC_2_4_6_TextString*>(bevd_0));
case 154620176: return bem_substring_1(static_cast<BEC_2_4_3_MathInt*>(bevd_0));
}
return bevs_super::bemd_1(callId, bevd_0);
}
BEC_2_6_6_SystemObject* BEC_2_4_6_TextString::bemd_2(int32_t callId, BEC_2_6_6_SystemObject* bevd_0, BEC_2_6_6_SystemObject* bevd_1) {
switch (callId) {
case -803790145: return bem_find_2(static_cast<BEC_2_4_6_TextString*>(bevd_0), static_cast<BEC_2_4_3_MathInt*>(bevd_1));
case 1087357298: return bem_setHex_2(static_cast<BEC_2_4_3_MathInt*>(bevd_0), static_cast<BEC_2_4_6_TextString*>(bevd_1));
case -1369633204: return bem_substring_2(static_cast<BEC_2_4_3_MathInt*>(bevd_0), static_cast<BEC_2_4_3_MathInt*>(bevd_1));
case 1378364608: return bem_swap_2(static_cast<BEC_2_4_6_TextString*>(bevd_0), static_cast<BEC_2_4_6_TextString*>(bevd_1));
case -838416593: return bem_setIntUnchecked_2(static_cast<BEC_2_4_3_MathInt*>(bevd_0), static_cast<BEC_2_4_3_MathInt*>(bevd_1));
case -519618212: return bem_swapFirst_2(static_cast<BEC_2_4_6_TextString*>(bevd_0), static_cast<BEC_2_4_6_TextString*>(bevd_1));
case -905387253: return bem_setInt_2(static_cast<BEC_2_4_3_MathInt*>(bevd_0), static_cast<BEC_2_4_3_MathInt*>(bevd_1));
case 23693735: return bem_getInt_2(static_cast<BEC_2_4_3_MathInt*>(bevd_0), static_cast<BEC_2_4_3_MathInt*>(bevd_1));
case 657044472: return bem_setCode_2(static_cast<BEC_2_4_3_MathInt*>(bevd_0), static_cast<BEC_2_4_3_MathInt*>(bevd_1));
case -1920728717: return bem_setCodeUnchecked_2(static_cast<BEC_2_4_3_MathInt*>(bevd_0), static_cast<BEC_2_4_3_MathInt*>(bevd_1));
case 131208798: return bem_getCode_2(static_cast<BEC_2_4_3_MathInt*>(bevd_0), static_cast<BEC_2_4_3_MathInt*>(bevd_1));
case -1737207353: return bem_join_2(static_cast<BEC_2_4_6_TextString*>(bevd_0), bevd_1);
}
return bevs_super::bemd_2(callId, bevd_0, bevd_1);
}
BEC_2_6_6_SystemObject* BEC_2_4_6_TextString::bemd_4(int32_t callId, BEC_2_6_6_SystemObject* bevd_0, BEC_2_6_6_SystemObject* bevd_1, BEC_2_6_6_SystemObject* bevd_2, BEC_2_6_6_SystemObject* bevd_3) {
switch (callId) {
case -760314510: return bem_copyValue_4(static_cast<BEC_2_4_6_TextString*>(bevd_0), static_cast<BEC_2_4_3_MathInt*>(bevd_1), static_cast<BEC_2_4_3_MathInt*>(bevd_2), static_cast<BEC_2_4_3_MathInt*>(bevd_3));
}
return bevs_super::bemd_4(callId, bevd_0, bevd_1, bevd_2, bevd_3);
}
BEC_2_6_6_SystemObject* BEC_2_4_6_TextString::bemc_create() {
return new BEC_2_4_6_TextString();
}
void BEC_2_4_6_TextString::bemc_setInitial(BEC_2_6_6_SystemObject* becc_inst) {
BEC_2_4_6_TextString::bece_BEC_2_4_6_TextString_bevs_inst = static_cast<BEC_2_4_6_TextString*>(becc_inst);
}
BEC_2_6_6_SystemObject* BEC_2_4_6_TextString::bemc_getInitial() {
return BEC_2_4_6_TextString::bece_BEC_2_4_6_TextString_bevs_inst;
}
void BEC_2_4_6_TextString::bemg_doMark() {
bevg_gcMark = BECS_Runtime::bevg_currentGcMark;
if (bevp_size != nullptr && bevp_size->bevg_gcMark != BECS_Runtime::bevg_currentGcMark) {
bevp_size->bemg_doMark();
}
if (bevp_capacity != nullptr && bevp_capacity->bevg_gcMark != BECS_Runtime::bevg_currentGcMark) {
bevp_capacity->bemg_doMark();
}
}
size_t BEC_2_4_6_TextString::bemg_getSize() {
return sizeof(*this);
}
BETS_Object* BEC_2_4_6_TextString::bemc_getType() {
return &BEC_2_4_6_TextString::bece_BEC_2_4_6_TextString_bevs_type;
}
BET_2_4_7_TextStrings::BET_2_4_7_TextStrings() {
std::vector<std::string> bevs_mtnames = {  };
bevs_fieldNames = {  };
}
BEC_2_6_6_SystemObject* BET_2_4_7_TextStrings::bems_createInstance() {
return new BEC_2_4_7_TextStrings();
}
void BET_2_4_7_TextStrings::bemgt_doMark() {
BEC_2_6_6_SystemObject* bevsl_inst_ref = *bevs_inst_ref;
if (bevsl_inst_ref != nullptr && bevsl_inst_ref->bevg_gcMark != BECS_Runtime::bevg_currentGcMark) {
bevsl_inst_ref->bemg_doMark();
}
}
BEC_2_4_7_TextStrings* BEC_2_4_7_TextStrings::bece_BEC_2_4_7_TextStrings_bevs_inst;

BET_2_4_7_TextStrings BEC_2_4_7_TextStrings::bece_BEC_2_4_7_TextStrings_bevs_type;
BEC_2_6_6_SystemObject** BET_2_4_7_TextStrings::bevs_inst_ref = (BEC_2_6_6_SystemObject**) &BEC_2_4_7_TextStrings::bece_BEC_2_4_7_TextStrings_bevs_inst;

BEC_2_6_6_SystemObject* BEC_2_4_7_TextStrings::bem_create_0() {
struct bes {  BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(1);
return this;
}
BEC_2_4_7_TextStrings* BEC_2_4_7_TextStrings::bem_default_0() {
struct bes { BEC_2_4_3_MathInt* bevt_0_ta_ph; BEC_2_4_3_MathInt* bevt_1_ta_ph; BEC_2_4_3_MathInt* bevt_2_ta_ph; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->bevt_0_ta_ph = nullptr;
beq->bevt_1_ta_ph = nullptr;
beq->bevt_2_ta_ph = nullptr;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(4);
bevp_zero = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(0))));
bevp_one = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(1))));
bevp_space = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString(1, {0x20}))));
bevp_empty = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString()))->bem_new_0());
beq->bevt_0_ta_ph = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(34))));
bevp_quote = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString()))->bem_codeNew_1(beq->bevt_0_ta_ph));
beq->bevt_1_ta_ph = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(9))));
bevp_tab = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString()))->bem_codeNew_1(beq->bevt_1_ta_ph));
bevp_dosNewline = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString(2, {0x0D,0x0A}))));
bevp_unixNewline = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString(1, {0x0A}))));
beq->bevt_2_ta_ph = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(13))));
bevp_cr = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString()))->bem_codeNew_1(beq->bevt_2_ta_ph));
bevp_lf = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString(1, {0x0A}))));
bevp_colon = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString(1, {0x3A}))));
return this;
}
BEC_2_4_6_TextString* BEC_2_4_7_TextStrings::bem_join_2(BEC_2_4_6_TextString* bevk_delim, BEC_2_6_6_SystemObject* bevk_splits) {
struct bes { BEC_2_4_6_TextString* beva_delim; BEC_2_6_6_SystemObject* beva_splits; BEC_2_4_6_TextString* bevt_0_ta_ph; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->beva_delim = bevk_delim;
beq->beva_splits = bevk_splits;
beq->bevt_0_ta_ph = nullptr;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(4);
beq->bevt_0_ta_ph = bem_joinBuffer_2(beq->beva_delim, beq->beva_splits);
return beq->bevt_0_ta_ph;
}
BEC_2_4_6_TextString* BEC_2_4_7_TextStrings::bem_joinBuffer_2(BEC_2_4_6_TextString* bevk_delim, BEC_2_6_6_SystemObject* bevk_splits) {
struct bes { BEC_2_4_6_TextString* beva_delim; BEC_2_6_6_SystemObject* beva_splits; BEC_2_6_6_SystemObject* bevl_i; BEC_2_4_6_TextString* bevl_buf; BEC_2_6_6_SystemObject* bevt_0_ta_ph; BEC_2_6_6_SystemObject* bevt_1_ta_ph; BEC_2_4_6_TextString* bevt_2_ta_ph; BEC_2_6_6_SystemObject* bevt_3_ta_ph; BEC_2_6_6_SystemObject* bevt_4_ta_ph; BEC_2_6_6_SystemObject* bevt_5_ta_ph; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->beva_delim = bevk_delim;
beq->beva_splits = bevk_splits;
beq->bevl_i = nullptr;
beq->bevl_buf = nullptr;
beq->bevt_0_ta_ph = nullptr;
beq->bevt_1_ta_ph = nullptr;
beq->bevt_2_ta_ph = nullptr;
beq->bevt_3_ta_ph = nullptr;
beq->bevt_4_ta_ph = nullptr;
beq->bevt_5_ta_ph = nullptr;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(11);
beq->bevl_i = beq->beva_splits->bemd_0(-1428269309);
beq->bevt_1_ta_ph = beq->bevl_i->bemd_0(448214784);
beq->bevt_0_ta_ph = beq->bevt_1_ta_ph->bemd_0(354802963);
if ((static_cast<BEC_2_5_4_LogicBool*>(beq->bevt_0_ta_ph))->bevi_bool) {
beq->bevt_2_ta_ph = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString()))->bem_new_0());
return beq->bevt_2_ta_ph;
} 
beq->bevl_buf = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString()))->bem_new_0());
beq->bevt_3_ta_ph = beq->bevl_i->bemd_0(-119099042);
beq->bevl_buf->bem_addValue_1(beq->bevt_3_ta_ph);
while (true)
 {
beq->bevt_4_ta_ph = beq->bevl_i->bemd_0(448214784);
if ((static_cast<BEC_2_5_4_LogicBool*>(beq->bevt_4_ta_ph))->bevi_bool) {
beq->bevl_buf->bem_addValue_1(beq->beva_delim);
beq->bevt_5_ta_ph = beq->bevl_i->bemd_0(-119099042);
beq->bevl_buf->bem_addValue_1(beq->bevt_5_ta_ph);
} 
 else  {
break;
} 
} 
return beq->bevl_buf;
}
BEC_2_6_6_SystemObject* BEC_2_4_7_TextStrings::bem_strip_1(BEC_2_4_6_TextString* bevk_str) {
struct bes { BEC_2_4_6_TextString* beva_str; BEC_2_4_3_MathInt* bevl_beg; BEC_2_4_3_MathInt* bevl_end; BEC_2_5_4_LogicBool* bevl_foundChar; BEC_2_4_17_TextMultiByteIterator* bevl_mb; BEC_2_4_6_TextString* bevl_step; BEC_2_4_6_TextString* bevl_toRet; BEC_2_5_4_LogicBool* bevt_0_ta_anchor; BEC_2_5_4_LogicBool* bevt_1_ta_anchor; BEC_2_5_4_LogicBool* bevt_2_ta_anchor; BEC_2_5_4_LogicBool* bevt_3_ta_ph; BEC_2_5_4_LogicBool* bevt_4_ta_ph; BEC_2_5_4_LogicBool* bevt_5_ta_ph; BEC_2_5_4_LogicBool* bevt_6_ta_ph; BEC_2_5_4_LogicBool* bevt_7_ta_ph; BEC_2_4_3_MathInt* bevt_8_ta_ph; BEC_2_4_3_MathInt* bevt_9_ta_ph; BEC_2_4_3_MathInt* bevt_10_ta_ph; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->beva_str = bevk_str;
beq->bevl_beg = nullptr;
beq->bevl_end = nullptr;
beq->bevl_foundChar = nullptr;
beq->bevl_mb = nullptr;
beq->bevl_step = nullptr;
beq->bevl_toRet = nullptr;
beq->bevt_0_ta_anchor = nullptr;
beq->bevt_1_ta_anchor = nullptr;
beq->bevt_2_ta_anchor = nullptr;
beq->bevt_3_ta_ph = nullptr;
beq->bevt_4_ta_ph = nullptr;
beq->bevt_5_ta_ph = nullptr;
beq->bevt_6_ta_ph = nullptr;
beq->bevt_7_ta_ph = nullptr;
beq->bevt_8_ta_ph = nullptr;
beq->bevt_9_ta_ph = nullptr;
beq->bevt_10_ta_ph = nullptr;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(19);
beq->bevl_beg = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(0))));
beq->bevl_end = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(0))));
beq->bevl_foundChar = static_cast<BEC_2_5_4_LogicBool*>(BECS_Runtime::boolFalse);
beq->bevl_mb = beq->beva_str->bem_mbiterGet_0();
while (true)
 {
beq->bevt_3_ta_ph = beq->bevl_mb->bem_hasNextGet_0();
if (beq->bevt_3_ta_ph->bevi_bool) {
beq->bevl_step = beq->bevl_mb->bem_nextGet_0();
beq->bevt_4_ta_ph = beq->bevl_step->bem_equals_1(bevp_space);
if (beq->bevt_4_ta_ph->bevi_bool) {
beq->bevt_2_ta_anchor = BECS_Runtime::boolTrue;
} 
 else  {
beq->bevt_5_ta_ph = beq->bevl_step->bem_equals_1(bevp_tab);
if (beq->bevt_5_ta_ph->bevi_bool) {
beq->bevt_2_ta_anchor = BECS_Runtime::boolTrue;
} 
 else  {
beq->bevt_2_ta_anchor = BECS_Runtime::boolFalse;
} 
} 
if (beq->bevt_2_ta_anchor->bevi_bool) {
beq->bevt_1_ta_anchor = BECS_Runtime::boolTrue;
} 
 else  {
beq->bevt_6_ta_ph = beq->bevl_step->bem_equals_1(bevp_cr);
if (beq->bevt_6_ta_ph->bevi_bool) {
beq->bevt_1_ta_anchor = BECS_Runtime::boolTrue;
} 
 else  {
beq->bevt_1_ta_anchor = BECS_Runtime::boolFalse;
} 
} 
if (beq->bevt_1_ta_anchor->bevi_bool) {
beq->bevt_0_ta_anchor = BECS_Runtime::boolTrue;
} 
 else  {
beq->bevt_7_ta_ph = beq->bevl_step->bem_equals_1(bevp_unixNewline);
if (beq->bevt_7_ta_ph->bevi_bool) {
beq->bevt_0_ta_anchor = BECS_Runtime::boolTrue;
} 
 else  {
beq->bevt_0_ta_anchor = BECS_Runtime::boolFalse;
} 
} 
if (beq->bevt_0_ta_anchor->bevi_bool) {
if (beq->bevl_foundChar->bevi_bool) {
beq->bevl_end->bevi_int++;
} 
 else  {
beq->bevl_beg->bevi_int++;
} 
} 
 else  {
beq->bevt_8_ta_ph = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(0))));
beq->bevl_end->bevi_int = beq->bevt_8_ta_ph->bevi_int;
beq->bevl_foundChar = static_cast<BEC_2_5_4_LogicBool*>(BECS_Runtime::boolTrue);
} 
} 
 else  {
break;
} 
} 
if (beq->bevl_foundChar->bevi_bool) {
beq->bevt_10_ta_ph = beq->beva_str->bem_sizeGet_0();
beq->bevt_9_ta_ph = beq->bevt_10_ta_ph->bem_subtract_1(beq->bevl_end);
beq->bevl_toRet = beq->beva_str->bem_substring_2(beq->bevl_beg, beq->bevt_9_ta_ph);
} 
 else  {
beq->bevl_toRet = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString(0, {}))));
} 
return beq->bevl_toRet;
}
BEC_2_4_6_TextString* BEC_2_4_7_TextStrings::bem_commonPrefix_2(BEC_2_4_6_TextString* bevk_a, BEC_2_4_6_TextString* bevk_b) {
struct bes { BEC_2_4_6_TextString* beva_a; BEC_2_4_6_TextString* beva_b; BEC_2_4_3_MathInt* bevl_sz; BEC_2_6_6_SystemObject* bevl_ai; BEC_2_6_6_SystemObject* bevl_bi; BEC_2_4_6_TextString* bevl_av; BEC_2_4_6_TextString* bevl_bv; BEC_2_4_3_MathInt* bevl_i; BEC_2_5_4_LogicBool* bevt_0_ta_anchor; BEC_2_5_4_LogicBool* bevt_1_ta_ph; BEC_2_5_4_LogicBool* bevt_2_ta_ph; BEC_2_4_4_MathInts* bevt_3_ta_ph; BEC_2_4_3_MathInt* bevt_4_ta_ph; BEC_2_4_3_MathInt* bevt_5_ta_ph; BEC_2_5_4_LogicBool* bevt_6_ta_ph; BEC_2_5_4_LogicBool* bevt_7_ta_ph; BEC_2_4_6_TextString* bevt_8_ta_ph; BEC_2_4_3_MathInt* bevt_9_ta_ph; BEC_2_4_6_TextString* bevt_10_ta_ph; BEC_2_4_3_MathInt* bevt_11_ta_ph; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->beva_a = bevk_a;
beq->beva_b = bevk_b;
beq->bevl_sz = nullptr;
beq->bevl_ai = nullptr;
beq->bevl_bi = nullptr;
beq->bevl_av = nullptr;
beq->bevl_bv = nullptr;
beq->bevl_i = nullptr;
beq->bevt_0_ta_anchor = nullptr;
beq->bevt_1_ta_ph = nullptr;
beq->bevt_2_ta_ph = nullptr;
beq->bevt_3_ta_ph = nullptr;
beq->bevt_4_ta_ph = nullptr;
beq->bevt_5_ta_ph = nullptr;
beq->bevt_6_ta_ph = nullptr;
beq->bevt_7_ta_ph = nullptr;
beq->bevt_8_ta_ph = nullptr;
beq->bevt_9_ta_ph = nullptr;
beq->bevt_10_ta_ph = nullptr;
beq->bevt_11_ta_ph = nullptr;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(21);
if (beq->beva_a == nullptr) {
beq->bevt_1_ta_ph = BECS_Runtime::boolTrue;
 } else { 
beq->bevt_1_ta_ph = BECS_Runtime::boolFalse;
}
if (beq->bevt_1_ta_ph->bevi_bool) {
beq->bevt_0_ta_anchor = BECS_Runtime::boolTrue;
} 
 else  {
if (beq->beva_b == nullptr) {
beq->bevt_2_ta_ph = BECS_Runtime::boolTrue;
 } else { 
beq->bevt_2_ta_ph = BECS_Runtime::boolFalse;
}
if (beq->bevt_2_ta_ph->bevi_bool) {
beq->bevt_0_ta_anchor = BECS_Runtime::boolTrue;
} 
 else  {
beq->bevt_0_ta_anchor = BECS_Runtime::boolFalse;
} 
} 
if (beq->bevt_0_ta_anchor->bevi_bool) {
return nullptr;
} 
beq->bevt_3_ta_ph = static_cast<BEC_2_4_4_MathInts*>(BEC_2_4_4_MathInts::bece_BEC_2_4_4_MathInts_bevs_inst);
beq->bevt_4_ta_ph = beq->beva_a->bem_sizeGet_0();
beq->bevt_5_ta_ph = beq->beva_b->bem_sizeGet_0();
beq->bevl_sz = static_cast<BEC_2_4_3_MathInt*>(beq->bevt_3_ta_ph->bem_min_2(beq->bevt_4_ta_ph, beq->bevt_5_ta_ph));
beq->bevl_ai = beq->beva_a->bem_biterGet_0();
beq->bevl_bi = beq->beva_b->bem_biterGet_0();
beq->bevl_av = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString()))->bem_new_0());
beq->bevl_bv = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString()))->bem_new_0());
beq->bevl_i = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(0))));
while (true)
 {
if (beq->bevl_i->bevi_int < beq->bevl_sz->bevi_int) {
beq->bevt_6_ta_ph = BECS_Runtime::boolTrue;
 } else { 
beq->bevt_6_ta_ph = BECS_Runtime::boolFalse;
}
if (beq->bevt_6_ta_ph->bevi_bool) {
beq->bevl_ai->bemd_1(-1793507420, beq->bevl_av);
beq->bevl_bi->bemd_1(-1793507420, beq->bevl_bv);
beq->bevt_7_ta_ph = beq->bevl_av->bem_notEquals_1(beq->bevl_bv);
if (beq->bevt_7_ta_ph->bevi_bool) {
beq->bevt_9_ta_ph = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(0))));
beq->bevt_8_ta_ph = beq->beva_a->bem_substring_2(beq->bevt_9_ta_ph, beq->bevl_i);
return beq->bevt_8_ta_ph;
} 
beq->bevl_i->bevi_int++;
} 
 else  {
break;
} 
} 
beq->bevt_11_ta_ph = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(0))));
beq->bevt_10_ta_ph = beq->beva_a->bem_substring_2(beq->bevt_11_ta_ph, beq->bevl_i);
return beq->bevt_10_ta_ph;
}
BEC_2_5_4_LogicBool* BEC_2_4_7_TextStrings::bem_anyEmpty_1(BEC_2_6_6_SystemObject* bevk_strs) {
struct bes { BEC_2_6_6_SystemObject* beva_strs; BEC_2_4_6_TextString* bevl_i; BEC_2_6_6_SystemObject* bevt_0_ta_loop; BEC_2_6_6_SystemObject* bevt_1_ta_ph; BEC_2_5_4_LogicBool* bevt_2_ta_ph; BEC_2_5_4_LogicBool* bevt_3_ta_ph; BEC_2_5_4_LogicBool* bevt_4_ta_ph; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->beva_strs = bevk_strs;
beq->bevl_i = nullptr;
beq->bevt_0_ta_loop = nullptr;
beq->bevt_1_ta_ph = nullptr;
beq->bevt_2_ta_ph = nullptr;
beq->bevt_3_ta_ph = nullptr;
beq->bevt_4_ta_ph = nullptr;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(8);
beq->bevt_0_ta_loop = beq->beva_strs->bemd_0(-1428269309);
while (true)
 {
beq->bevt_1_ta_ph = beq->bevt_0_ta_loop->bemd_0(448214784);
if ((static_cast<BEC_2_5_4_LogicBool*>(beq->bevt_1_ta_ph))->bevi_bool) {
beq->bevl_i = static_cast<BEC_2_4_6_TextString*>(beq->bevt_0_ta_loop->bemd_0(-119099042));
beq->bevt_2_ta_ph = bem_isEmpty_1(beq->bevl_i);
if (beq->bevt_2_ta_ph->bevi_bool) {
beq->bevt_3_ta_ph = static_cast<BEC_2_5_4_LogicBool*>(BECS_Runtime::boolTrue);
return beq->bevt_3_ta_ph;
} 
} 
 else  {
break;
} 
} 
beq->bevt_4_ta_ph = static_cast<BEC_2_5_4_LogicBool*>(BECS_Runtime::boolFalse);
return beq->bevt_4_ta_ph;
}
BEC_2_5_4_LogicBool* BEC_2_4_7_TextStrings::bem_isEmpty_1(BEC_2_4_6_TextString* bevk_value) {
struct bes { BEC_2_4_6_TextString* beva_value; BEC_2_5_4_LogicBool* bevt_0_ta_anchor; BEC_2_5_4_LogicBool* bevt_1_ta_ph; BEC_2_5_4_LogicBool* bevt_2_ta_ph; BEC_2_4_3_MathInt* bevt_3_ta_ph; BEC_2_5_4_LogicBool* bevt_4_ta_ph; BEC_2_5_4_LogicBool* bevt_5_ta_ph; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->beva_value = bevk_value;
beq->bevt_0_ta_anchor = nullptr;
beq->bevt_1_ta_ph = nullptr;
beq->bevt_2_ta_ph = nullptr;
beq->bevt_3_ta_ph = nullptr;
beq->bevt_4_ta_ph = nullptr;
beq->bevt_5_ta_ph = nullptr;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(8);
if (beq->beva_value == nullptr) {
beq->bevt_1_ta_ph = BECS_Runtime::boolTrue;
 } else { 
beq->bevt_1_ta_ph = BECS_Runtime::boolFalse;
}
if (beq->bevt_1_ta_ph->bevi_bool) {
beq->bevt_0_ta_anchor = BECS_Runtime::boolTrue;
} 
 else  {
beq->bevt_3_ta_ph = beq->beva_value->bem_sizeGet_0();
if (beq->bevt_3_ta_ph->bevi_int < bevp_one->bevi_int) {
beq->bevt_2_ta_ph = BECS_Runtime::boolTrue;
 } else { 
beq->bevt_2_ta_ph = BECS_Runtime::boolFalse;
}
if (beq->bevt_2_ta_ph->bevi_bool) {
beq->bevt_0_ta_anchor = BECS_Runtime::boolTrue;
} 
 else  {
beq->bevt_0_ta_anchor = BECS_Runtime::boolFalse;
} 
} 
if (beq->bevt_0_ta_anchor->bevi_bool) {
beq->bevt_4_ta_ph = static_cast<BEC_2_5_4_LogicBool*>(BECS_Runtime::boolTrue);
return beq->bevt_4_ta_ph;
} 
beq->bevt_5_ta_ph = static_cast<BEC_2_5_4_LogicBool*>(BECS_Runtime::boolFalse);
return beq->bevt_5_ta_ph;
}
BEC_2_5_4_LogicBool* BEC_2_4_7_TextStrings::bem_notEmpty_1(BEC_2_4_6_TextString* bevk_value) {
struct bes { BEC_2_4_6_TextString* beva_value; BEC_2_5_4_LogicBool* bevt_0_ta_anchor; BEC_2_5_4_LogicBool* bevt_1_ta_ph; BEC_2_5_4_LogicBool* bevt_2_ta_ph; BEC_2_4_3_MathInt* bevt_3_ta_ph; BEC_2_5_4_LogicBool* bevt_4_ta_ph; BEC_2_5_4_LogicBool* bevt_5_ta_ph; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->beva_value = bevk_value;
beq->bevt_0_ta_anchor = nullptr;
beq->bevt_1_ta_ph = nullptr;
beq->bevt_2_ta_ph = nullptr;
beq->bevt_3_ta_ph = nullptr;
beq->bevt_4_ta_ph = nullptr;
beq->bevt_5_ta_ph = nullptr;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(8);
if (beq->beva_value == nullptr) {
beq->bevt_1_ta_ph = BECS_Runtime::boolFalse;
 } else { 
beq->bevt_1_ta_ph = BECS_Runtime::boolTrue;
}
if (beq->bevt_1_ta_ph->bevi_bool) {
beq->bevt_3_ta_ph = beq->beva_value->bem_sizeGet_0();
if (beq->bevt_3_ta_ph->bevi_int > bevp_zero->bevi_int) {
beq->bevt_2_ta_ph = BECS_Runtime::boolTrue;
 } else { 
beq->bevt_2_ta_ph = BECS_Runtime::boolFalse;
}
if (beq->bevt_2_ta_ph->bevi_bool) {
beq->bevt_0_ta_anchor = BECS_Runtime::boolTrue;
} 
 else  {
beq->bevt_0_ta_anchor = BECS_Runtime::boolFalse;
} 
} 
 else  {
beq->bevt_0_ta_anchor = BECS_Runtime::boolFalse;
} 
if (beq->bevt_0_ta_anchor->bevi_bool) {
beq->bevt_4_ta_ph = static_cast<BEC_2_5_4_LogicBool*>(BECS_Runtime::boolTrue);
return beq->bevt_4_ta_ph;
} 
beq->bevt_5_ta_ph = static_cast<BEC_2_5_4_LogicBool*>(BECS_Runtime::boolFalse);
return beq->bevt_5_ta_ph;
}
BEC_2_4_3_MathInt* BEC_2_4_7_TextStrings::bem_zeroGet_0() {
struct bes {  BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(1);
return bevp_zero;
}
BEC_2_4_7_TextStrings* BEC_2_4_7_TextStrings::bem_zeroSet_1(BEC_2_6_6_SystemObject* bevt_0_ta_SET) {
struct bes { BEC_2_6_6_SystemObject* bevt_0_ta_SET; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->bevt_0_ta_SET = bevt_0_ta_SET;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(2);
bevp_zero = static_cast<BEC_2_4_3_MathInt*>(beq->bevt_0_ta_SET);
return this;
}
BEC_2_4_3_MathInt* BEC_2_4_7_TextStrings::bem_oneGet_0() {
struct bes {  BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(1);
return bevp_one;
}
BEC_2_4_7_TextStrings* BEC_2_4_7_TextStrings::bem_oneSet_1(BEC_2_6_6_SystemObject* bevt_0_ta_SET) {
struct bes { BEC_2_6_6_SystemObject* bevt_0_ta_SET; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->bevt_0_ta_SET = bevt_0_ta_SET;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(2);
bevp_one = static_cast<BEC_2_4_3_MathInt*>(beq->bevt_0_ta_SET);
return this;
}
BEC_2_4_6_TextString* BEC_2_4_7_TextStrings::bem_spaceGet_0() {
struct bes {  BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(1);
return bevp_space;
}
BEC_2_4_7_TextStrings* BEC_2_4_7_TextStrings::bem_spaceSet_1(BEC_2_6_6_SystemObject* bevt_0_ta_SET) {
struct bes { BEC_2_6_6_SystemObject* bevt_0_ta_SET; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->bevt_0_ta_SET = bevt_0_ta_SET;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(2);
bevp_space = static_cast<BEC_2_4_6_TextString*>(beq->bevt_0_ta_SET);
return this;
}
BEC_2_4_6_TextString* BEC_2_4_7_TextStrings::bem_emptyGet_0() {
struct bes {  BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(1);
return bevp_empty;
}
BEC_2_4_7_TextStrings* BEC_2_4_7_TextStrings::bem_emptySet_1(BEC_2_6_6_SystemObject* bevt_0_ta_SET) {
struct bes { BEC_2_6_6_SystemObject* bevt_0_ta_SET; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->bevt_0_ta_SET = bevt_0_ta_SET;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(2);
bevp_empty = static_cast<BEC_2_4_6_TextString*>(beq->bevt_0_ta_SET);
return this;
}
BEC_2_4_6_TextString* BEC_2_4_7_TextStrings::bem_quoteGet_0() {
struct bes {  BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(1);
return bevp_quote;
}
BEC_2_4_7_TextStrings* BEC_2_4_7_TextStrings::bem_quoteSet_1(BEC_2_6_6_SystemObject* bevt_0_ta_SET) {
struct bes { BEC_2_6_6_SystemObject* bevt_0_ta_SET; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->bevt_0_ta_SET = bevt_0_ta_SET;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(2);
bevp_quote = static_cast<BEC_2_4_6_TextString*>(beq->bevt_0_ta_SET);
return this;
}
BEC_2_4_6_TextString* BEC_2_4_7_TextStrings::bem_tabGet_0() {
struct bes {  BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(1);
return bevp_tab;
}
BEC_2_4_7_TextStrings* BEC_2_4_7_TextStrings::bem_tabSet_1(BEC_2_6_6_SystemObject* bevt_0_ta_SET) {
struct bes { BEC_2_6_6_SystemObject* bevt_0_ta_SET; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->bevt_0_ta_SET = bevt_0_ta_SET;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(2);
bevp_tab = static_cast<BEC_2_4_6_TextString*>(beq->bevt_0_ta_SET);
return this;
}
BEC_2_4_6_TextString* BEC_2_4_7_TextStrings::bem_dosNewlineGet_0() {
struct bes {  BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(1);
return bevp_dosNewline;
}
BEC_2_4_7_TextStrings* BEC_2_4_7_TextStrings::bem_dosNewlineSet_1(BEC_2_6_6_SystemObject* bevt_0_ta_SET) {
struct bes { BEC_2_6_6_SystemObject* bevt_0_ta_SET; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->bevt_0_ta_SET = bevt_0_ta_SET;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(2);
bevp_dosNewline = static_cast<BEC_2_4_6_TextString*>(beq->bevt_0_ta_SET);
return this;
}
BEC_2_4_6_TextString* BEC_2_4_7_TextStrings::bem_unixNewlineGet_0() {
struct bes {  BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(1);
return bevp_unixNewline;
}
BEC_2_4_7_TextStrings* BEC_2_4_7_TextStrings::bem_unixNewlineSet_1(BEC_2_6_6_SystemObject* bevt_0_ta_SET) {
struct bes { BEC_2_6_6_SystemObject* bevt_0_ta_SET; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->bevt_0_ta_SET = bevt_0_ta_SET;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(2);
bevp_unixNewline = static_cast<BEC_2_4_6_TextString*>(beq->bevt_0_ta_SET);
return this;
}
BEC_2_4_6_TextString* BEC_2_4_7_TextStrings::bem_newlineGet_0() {
struct bes {  BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(1);
return bevp_newline;
}
BEC_2_4_7_TextStrings* BEC_2_4_7_TextStrings::bem_newlineSet_1(BEC_2_6_6_SystemObject* bevt_0_ta_SET) {
struct bes { BEC_2_6_6_SystemObject* bevt_0_ta_SET; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->bevt_0_ta_SET = bevt_0_ta_SET;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(2);
bevp_newline = static_cast<BEC_2_4_6_TextString*>(beq->bevt_0_ta_SET);
return this;
}
BEC_2_4_6_TextString* BEC_2_4_7_TextStrings::bem_crGet_0() {
struct bes {  BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(1);
return bevp_cr;
}
BEC_2_4_7_TextStrings* BEC_2_4_7_TextStrings::bem_crSet_1(BEC_2_6_6_SystemObject* bevt_0_ta_SET) {
struct bes { BEC_2_6_6_SystemObject* bevt_0_ta_SET; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->bevt_0_ta_SET = bevt_0_ta_SET;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(2);
bevp_cr = static_cast<BEC_2_4_6_TextString*>(beq->bevt_0_ta_SET);
return this;
}
BEC_2_4_6_TextString* BEC_2_4_7_TextStrings::bem_lfGet_0() {
struct bes {  BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(1);
return bevp_lf;
}
BEC_2_4_7_TextStrings* BEC_2_4_7_TextStrings::bem_lfSet_1(BEC_2_6_6_SystemObject* bevt_0_ta_SET) {
struct bes { BEC_2_6_6_SystemObject* bevt_0_ta_SET; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->bevt_0_ta_SET = bevt_0_ta_SET;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(2);
bevp_lf = static_cast<BEC_2_4_6_TextString*>(beq->bevt_0_ta_SET);
return this;
}
BEC_2_4_6_TextString* BEC_2_4_7_TextStrings::bem_colonGet_0() {
struct bes {  BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(1);
return bevp_colon;
}
BEC_2_4_7_TextStrings* BEC_2_4_7_TextStrings::bem_colonSet_1(BEC_2_6_6_SystemObject* bevt_0_ta_SET) {
struct bes { BEC_2_6_6_SystemObject* bevt_0_ta_SET; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->bevt_0_ta_SET = bevt_0_ta_SET;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(2);
bevp_colon = static_cast<BEC_2_4_6_TextString*>(beq->bevt_0_ta_SET);
return this;
}
BEC_2_6_6_SystemObject* BEC_2_4_7_TextStrings::bemd_0(int32_t callId) {
switch (callId) {
case 2105030690: return bem_crGet_0();
case 1558451664: return bem_oneGet_0();
case 140740517: return bem_lfGet_0();
case 1980106247: return bem_unixNewlineGet_0();
case 1312387167: return bem_create_0();
case 2009331464: return bem_newlineGet_0();
case 1188815194: return bem_default_0();
case 363757507: return bem_zeroGet_0();
case 1410565248: return bem_quoteGet_0();
case 765815352: return bem_colonGet_0();
case -808694583: return bem_dosNewlineGet_0();
case 771265898: return bem_tabGet_0();
case 780455061: return bem_emptyGet_0();
case -336976510: return bem_spaceGet_0();
}
return bevs_super::bemd_0(callId);
}
BEC_2_6_6_SystemObject* BEC_2_4_7_TextStrings::bemd_1(int32_t callId, BEC_2_6_6_SystemObject* bevd_0) {
switch (callId) {
case 1960421600: return bem_spaceSet_1(bevd_0);
case 593309101: return bem_zeroSet_1(bevd_0);
case -375635801: return bem_strip_1(static_cast<BEC_2_4_6_TextString*>(bevd_0));
case -2096396301: return bem_emptySet_1(bevd_0);
case -664937506: return bem_quoteSet_1(bevd_0);
case -1504048614: return bem_unixNewlineSet_1(bevd_0);
case -1958052018: return bem_newlineSet_1(bevd_0);
case 447202520: return bem_crSet_1(bevd_0);
case 1576645321: return bem_oneSet_1(bevd_0);
case -582613831: return bem_notEmpty_1(static_cast<BEC_2_4_6_TextString*>(bevd_0));
case -1163199546: return bem_tabSet_1(bevd_0);
case -196267156: return bem_lfSet_1(bevd_0);
case -857631970: return bem_dosNewlineSet_1(bevd_0);
case -1565286878: return bem_isEmpty_1(static_cast<BEC_2_4_6_TextString*>(bevd_0));
case -869717083: return bem_anyEmpty_1(bevd_0);
case -1202696895: return bem_colonSet_1(bevd_0);
}
return bevs_super::bemd_1(callId, bevd_0);
}
BEC_2_6_6_SystemObject* BEC_2_4_7_TextStrings::bemd_2(int32_t callId, BEC_2_6_6_SystemObject* bevd_0, BEC_2_6_6_SystemObject* bevd_1) {
switch (callId) {
case 1680902333: return bem_commonPrefix_2(static_cast<BEC_2_4_6_TextString*>(bevd_0), static_cast<BEC_2_4_6_TextString*>(bevd_1));
case -1737207353: return bem_join_2(static_cast<BEC_2_4_6_TextString*>(bevd_0), bevd_1);
case -1501613426: return bem_joinBuffer_2(static_cast<BEC_2_4_6_TextString*>(bevd_0), bevd_1);
}
return bevs_super::bemd_2(callId, bevd_0, bevd_1);
}
BEC_2_6_6_SystemObject* BEC_2_4_7_TextStrings::bemc_create() {
return new BEC_2_4_7_TextStrings();
}
void BEC_2_4_7_TextStrings::bemc_setInitial(BEC_2_6_6_SystemObject* becc_inst) {
BEC_2_4_7_TextStrings::bece_BEC_2_4_7_TextStrings_bevs_inst = static_cast<BEC_2_4_7_TextStrings*>(becc_inst);
}
BEC_2_6_6_SystemObject* BEC_2_4_7_TextStrings::bemc_getInitial() {
return BEC_2_4_7_TextStrings::bece_BEC_2_4_7_TextStrings_bevs_inst;
}
void BEC_2_4_7_TextStrings::bemg_doMark() {
bevg_gcMark = BECS_Runtime::bevg_currentGcMark;
if (bevp_zero != nullptr && bevp_zero->bevg_gcMark != BECS_Runtime::bevg_currentGcMark) {
bevp_zero->bemg_doMark();
}
if (bevp_one != nullptr && bevp_one->bevg_gcMark != BECS_Runtime::bevg_currentGcMark) {
bevp_one->bemg_doMark();
}
if (bevp_space != nullptr && bevp_space->bevg_gcMark != BECS_Runtime::bevg_currentGcMark) {
bevp_space->bemg_doMark();
}
if (bevp_empty != nullptr && bevp_empty->bevg_gcMark != BECS_Runtime::bevg_currentGcMark) {
bevp_empty->bemg_doMark();
}
if (bevp_quote != nullptr && bevp_quote->bevg_gcMark != BECS_Runtime::bevg_currentGcMark) {
bevp_quote->bemg_doMark();
}
if (bevp_tab != nullptr && bevp_tab->bevg_gcMark != BECS_Runtime::bevg_currentGcMark) {
bevp_tab->bemg_doMark();
}
if (bevp_dosNewline != nullptr && bevp_dosNewline->bevg_gcMark != BECS_Runtime::bevg_currentGcMark) {
bevp_dosNewline->bemg_doMark();
}
if (bevp_unixNewline != nullptr && bevp_unixNewline->bevg_gcMark != BECS_Runtime::bevg_currentGcMark) {
bevp_unixNewline->bemg_doMark();
}
if (bevp_newline != nullptr && bevp_newline->bevg_gcMark != BECS_Runtime::bevg_currentGcMark) {
bevp_newline->bemg_doMark();
}
if (bevp_cr != nullptr && bevp_cr->bevg_gcMark != BECS_Runtime::bevg_currentGcMark) {
bevp_cr->bemg_doMark();
}
if (bevp_lf != nullptr && bevp_lf->bevg_gcMark != BECS_Runtime::bevg_currentGcMark) {
bevp_lf->bemg_doMark();
}
if (bevp_colon != nullptr && bevp_colon->bevg_gcMark != BECS_Runtime::bevg_currentGcMark) {
bevp_colon->bemg_doMark();
}
}
size_t BEC_2_4_7_TextStrings::bemg_getSize() {
return sizeof(*this);
}
BETS_Object* BEC_2_4_7_TextStrings::bemc_getType() {
return &BEC_2_4_7_TextStrings::bece_BEC_2_4_7_TextStrings_bevs_type;
}
BET_2_4_12_TextByteIterator::BET_2_4_12_TextByteIterator() {
std::vector<std::string> bevs_mtnames = {  };
bevs_fieldNames = {  };
}
BEC_2_6_6_SystemObject* BET_2_4_12_TextByteIterator::bems_createInstance() {
return new BEC_2_4_12_TextByteIterator();
}
void BET_2_4_12_TextByteIterator::bemgt_doMark() {
BEC_2_6_6_SystemObject* bevsl_inst_ref = *bevs_inst_ref;
if (bevsl_inst_ref != nullptr && bevsl_inst_ref->bevg_gcMark != BECS_Runtime::bevg_currentGcMark) {
bevsl_inst_ref->bemg_doMark();
}
}
BEC_2_4_12_TextByteIterator* BEC_2_4_12_TextByteIterator::bece_BEC_2_4_12_TextByteIterator_bevs_inst;

BET_2_4_12_TextByteIterator BEC_2_4_12_TextByteIterator::bece_BEC_2_4_12_TextByteIterator_bevs_type;
BEC_2_6_6_SystemObject** BET_2_4_12_TextByteIterator::bevs_inst_ref = (BEC_2_6_6_SystemObject**) &BEC_2_4_12_TextByteIterator::bece_BEC_2_4_12_TextByteIterator_bevs_inst;

BEC_2_6_6_SystemObject* BEC_2_4_12_TextByteIterator::bem_new_0() {
struct bes { BEC_2_4_6_TextString* bevt_0_ta_ph; BEC_2_4_7_TextStrings* bevt_1_ta_ph; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->bevt_0_ta_ph = nullptr;
beq->bevt_1_ta_ph = nullptr;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(3);
beq->bevt_1_ta_ph = static_cast<BEC_2_4_7_TextStrings*>(BEC_2_4_7_TextStrings::bece_BEC_2_4_7_TextStrings_bevs_inst);
beq->bevt_0_ta_ph = beq->bevt_1_ta_ph->bem_emptyGet_0();
bem_new_1(beq->bevt_0_ta_ph);
return this;
}
BEC_2_4_6_TextString* BEC_2_4_12_TextByteIterator::bem_containerGet_0() {
struct bes {  BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(1);
return bevp_str;
}
BEC_2_4_6_TextString* BEC_2_4_12_TextByteIterator::bem_serializeToString_0() {
struct bes {  BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(1);
return bevp_str;
}
BEC_2_4_12_TextByteIterator* BEC_2_4_12_TextByteIterator::bem_deserializeFromStringNew_1(BEC_2_4_6_TextString* bevk_str) {
struct bes { BEC_2_4_6_TextString* beva_str; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->beva_str = bevk_str;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(2);
bem_new_1(beq->beva_str);
return this;
}
BEC_2_4_12_TextByteIterator* BEC_2_4_12_TextByteIterator::bem_new_1(BEC_2_4_6_TextString* bevk__str) {
struct bes { BEC_2_4_6_TextString* beva__str; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->beva__str = bevk__str;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(2);
bevp_pos = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(0))));
bevp_str = beq->beva__str;
bevp_vcopy = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt())));
return this;
}
BEC_2_5_4_LogicBool* BEC_2_4_12_TextByteIterator::bem_hasNextGet_0() {
struct bes { BEC_2_5_4_LogicBool* bevt_0_ta_ph; BEC_2_4_3_MathInt* bevt_1_ta_ph; BEC_2_5_4_LogicBool* bevt_2_ta_ph; BEC_2_5_4_LogicBool* bevt_3_ta_ph; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->bevt_0_ta_ph = nullptr;
beq->bevt_1_ta_ph = nullptr;
beq->bevt_2_ta_ph = nullptr;
beq->bevt_3_ta_ph = nullptr;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(5);
beq->bevt_1_ta_ph = bevp_str->bem_sizeGet_0();
if (beq->bevt_1_ta_ph->bevi_int > bevp_pos->bevi_int) {
beq->bevt_0_ta_ph = BECS_Runtime::boolTrue;
 } else { 
beq->bevt_0_ta_ph = BECS_Runtime::boolFalse;
}
if (beq->bevt_0_ta_ph->bevi_bool) {
beq->bevt_2_ta_ph = static_cast<BEC_2_5_4_LogicBool*>(BECS_Runtime::boolTrue);
return beq->bevt_2_ta_ph;
} 
beq->bevt_3_ta_ph = static_cast<BEC_2_5_4_LogicBool*>(BECS_Runtime::boolFalse);
return beq->bevt_3_ta_ph;
}
BEC_2_4_6_TextString* BEC_2_4_12_TextByteIterator::bem_nextGet_0() {
struct bes { BEC_2_4_6_TextString* bevt_0_ta_ph; BEC_2_4_6_TextString* bevt_1_ta_ph; BEC_2_4_3_MathInt* bevt_2_ta_ph; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->bevt_0_ta_ph = nullptr;
beq->bevt_1_ta_ph = nullptr;
beq->bevt_2_ta_ph = nullptr;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(4);
beq->bevt_2_ta_ph = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(1))));
beq->bevt_1_ta_ph = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString()))->bem_new_1(beq->bevt_2_ta_ph));
beq->bevt_0_ta_ph = bem_next_1(beq->bevt_1_ta_ph);
return beq->bevt_0_ta_ph;
}
BEC_2_4_6_TextString* BEC_2_4_12_TextByteIterator::bem_next_1(BEC_2_4_6_TextString* bevk_buf) {
struct bes { BEC_2_4_6_TextString* beva_buf; BEC_2_5_4_LogicBool* bevt_0_ta_ph; BEC_2_4_3_MathInt* bevt_1_ta_ph; BEC_2_5_4_LogicBool* bevt_2_ta_ph; BEC_2_4_3_MathInt* bevt_3_ta_ph; BEC_2_4_3_MathInt* bevt_4_ta_ph; BEC_2_4_3_MathInt* bevt_5_ta_ph; BEC_2_5_4_LogicBool* bevt_6_ta_ph; BEC_2_4_3_MathInt* bevt_7_ta_ph; BEC_2_4_3_MathInt* bevt_8_ta_ph; BEC_2_4_3_MathInt* bevt_9_ta_ph; BEC_2_4_3_MathInt* bevt_10_ta_ph; BEC_2_4_3_MathInt* bevt_11_ta_ph; BEC_2_4_3_MathInt* bevt_12_ta_ph; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->beva_buf = bevk_buf;
beq->bevt_0_ta_ph = nullptr;
beq->bevt_1_ta_ph = nullptr;
beq->bevt_2_ta_ph = nullptr;
beq->bevt_3_ta_ph = nullptr;
beq->bevt_4_ta_ph = nullptr;
beq->bevt_5_ta_ph = nullptr;
beq->bevt_6_ta_ph = nullptr;
beq->bevt_7_ta_ph = nullptr;
beq->bevt_8_ta_ph = nullptr;
beq->bevt_9_ta_ph = nullptr;
beq->bevt_10_ta_ph = nullptr;
beq->bevt_11_ta_ph = nullptr;
beq->bevt_12_ta_ph = nullptr;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(15);
beq->bevt_1_ta_ph = bevp_str->bem_sizeGet_0();
if (beq->bevt_1_ta_ph->bevi_int > bevp_pos->bevi_int) {
beq->bevt_0_ta_ph = BECS_Runtime::boolTrue;
 } else { 
beq->bevt_0_ta_ph = BECS_Runtime::boolFalse;
}
if (beq->bevt_0_ta_ph->bevi_bool) {
beq->bevt_3_ta_ph = beq->beva_buf->bem_capacityGet_0();
beq->bevt_4_ta_ph = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(1))));
if (beq->bevt_3_ta_ph->bevi_int < beq->bevt_4_ta_ph->bevi_int) {
beq->bevt_2_ta_ph = BECS_Runtime::boolTrue;
 } else { 
beq->bevt_2_ta_ph = BECS_Runtime::boolFalse;
}
if (beq->bevt_2_ta_ph->bevi_bool) {
beq->bevt_5_ta_ph = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(1))));
beq->beva_buf->bem_capacitySet_1(beq->bevt_5_ta_ph);
} 
beq->bevt_7_ta_ph = beq->beva_buf->bem_sizeGet_0();
beq->bevt_8_ta_ph = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(1))));
if (beq->bevt_7_ta_ph->bevi_int != beq->bevt_8_ta_ph->bevi_int) {
beq->bevt_6_ta_ph = BECS_Runtime::boolTrue;
 } else { 
beq->bevt_6_ta_ph = BECS_Runtime::boolFalse;
}
if (beq->bevt_6_ta_ph->bevi_bool) {
beq->bevt_9_ta_ph = beq->beva_buf->bem_sizeGet_0();
beq->bevt_10_ta_ph = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(1))));
beq->bevt_9_ta_ph->bevi_int = beq->bevt_10_ta_ph->bevi_int;
} 
beq->bevt_11_ta_ph = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(0))));
beq->bevt_12_ta_ph = bevp_str->bem_getInt_2(bevp_pos, bevp_vcopy);
beq->beva_buf->bem_setIntUnchecked_2(beq->bevt_11_ta_ph, beq->bevt_12_ta_ph);
bevp_pos->bevi_int++;
} 
return beq->beva_buf;
}
BEC_2_4_3_MathInt* BEC_2_4_12_TextByteIterator::bem_nextInt_1(BEC_2_4_3_MathInt* bevk_into) {
struct bes { BEC_2_4_3_MathInt* beva_into; BEC_2_5_4_LogicBool* bevt_0_ta_ph; BEC_2_4_3_MathInt* bevt_1_ta_ph; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->beva_into = bevk_into;
beq->bevt_0_ta_ph = nullptr;
beq->bevt_1_ta_ph = nullptr;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(4);
beq->bevt_1_ta_ph = bevp_str->bem_sizeGet_0();
if (beq->bevt_1_ta_ph->bevi_int > bevp_pos->bevi_int) {
beq->bevt_0_ta_ph = BECS_Runtime::boolTrue;
 } else { 
beq->bevt_0_ta_ph = BECS_Runtime::boolFalse;
}
if (beq->bevt_0_ta_ph->bevi_bool) {
bevp_str->bem_getInt_2(bevp_pos, beq->beva_into);
bevp_pos->bevi_int++;
} 
return beq->beva_into;
}
BEC_2_4_3_MathInt* BEC_2_4_12_TextByteIterator::bem_currentInt_1(BEC_2_4_3_MathInt* bevk_into) {
struct bes { BEC_2_4_3_MathInt* beva_into; BEC_2_5_4_LogicBool* bevt_0_ta_anchor; BEC_2_5_4_LogicBool* bevt_1_ta_ph; BEC_2_4_3_MathInt* bevt_2_ta_ph; BEC_2_5_4_LogicBool* bevt_3_ta_ph; BEC_2_4_3_MathInt* bevt_4_ta_ph; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->beva_into = bevk_into;
beq->bevt_0_ta_anchor = nullptr;
beq->bevt_1_ta_ph = nullptr;
beq->bevt_2_ta_ph = nullptr;
beq->bevt_3_ta_ph = nullptr;
beq->bevt_4_ta_ph = nullptr;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(7);
beq->bevt_2_ta_ph = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(0))));
if (bevp_pos->bevi_int > beq->bevt_2_ta_ph->bevi_int) {
beq->bevt_1_ta_ph = BECS_Runtime::boolTrue;
 } else { 
beq->bevt_1_ta_ph = BECS_Runtime::boolFalse;
}
if (beq->bevt_1_ta_ph->bevi_bool) {
beq->bevt_4_ta_ph = bevp_str->bem_sizeGet_0();
if (beq->bevt_4_ta_ph->bevi_int >= bevp_pos->bevi_int) {
beq->bevt_3_ta_ph = BECS_Runtime::boolTrue;
 } else { 
beq->bevt_3_ta_ph = BECS_Runtime::boolFalse;
}
if (beq->bevt_3_ta_ph->bevi_bool) {
beq->bevt_0_ta_anchor = BECS_Runtime::boolTrue;
} 
 else  {
beq->bevt_0_ta_anchor = BECS_Runtime::boolFalse;
} 
} 
 else  {
beq->bevt_0_ta_anchor = BECS_Runtime::boolFalse;
} 
if (beq->bevt_0_ta_anchor->bevi_bool) {
bevp_pos->bem_decrementValue_0();
bevp_str->bem_getInt_2(bevp_pos, beq->beva_into);
bevp_pos->bevi_int++;
} 
return beq->beva_into;
}
BEC_2_4_12_TextByteIterator* BEC_2_4_12_TextByteIterator::bem_currentIntSet_1(BEC_2_4_3_MathInt* bevk_into) {
struct bes { BEC_2_4_3_MathInt* beva_into; BEC_2_5_4_LogicBool* bevt_0_ta_anchor; BEC_2_5_4_LogicBool* bevt_1_ta_ph; BEC_2_4_3_MathInt* bevt_2_ta_ph; BEC_2_5_4_LogicBool* bevt_3_ta_ph; BEC_2_4_3_MathInt* bevt_4_ta_ph; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->beva_into = bevk_into;
beq->bevt_0_ta_anchor = nullptr;
beq->bevt_1_ta_ph = nullptr;
beq->bevt_2_ta_ph = nullptr;
beq->bevt_3_ta_ph = nullptr;
beq->bevt_4_ta_ph = nullptr;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(7);
beq->bevt_2_ta_ph = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(0))));
if (bevp_pos->bevi_int > beq->bevt_2_ta_ph->bevi_int) {
beq->bevt_1_ta_ph = BECS_Runtime::boolTrue;
 } else { 
beq->bevt_1_ta_ph = BECS_Runtime::boolFalse;
}
if (beq->bevt_1_ta_ph->bevi_bool) {
beq->bevt_4_ta_ph = bevp_str->bem_sizeGet_0();
if (beq->bevt_4_ta_ph->bevi_int >= bevp_pos->bevi_int) {
beq->bevt_3_ta_ph = BECS_Runtime::boolTrue;
 } else { 
beq->bevt_3_ta_ph = BECS_Runtime::boolFalse;
}
if (beq->bevt_3_ta_ph->bevi_bool) {
beq->bevt_0_ta_anchor = BECS_Runtime::boolTrue;
} 
 else  {
beq->bevt_0_ta_anchor = BECS_Runtime::boolFalse;
} 
} 
 else  {
beq->bevt_0_ta_anchor = BECS_Runtime::boolFalse;
} 
if (beq->bevt_0_ta_anchor->bevi_bool) {
bevp_pos->bem_decrementValue_0();
bevp_str->bem_setIntUnchecked_2(bevp_pos, beq->beva_into);
bevp_pos->bevi_int++;
} 
return this;
}
BEC_2_6_6_SystemObject* BEC_2_4_12_TextByteIterator::bem_iteratorGet_0() {
struct bes {  BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(1);
return this;
}
BEC_2_4_12_TextByteIterator* BEC_2_4_12_TextByteIterator::bem_byteIteratorIteratorGet_0() {
struct bes {  BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(1);
return this;
}
BEC_2_4_3_MathInt* BEC_2_4_12_TextByteIterator::bem_posGet_0() {
struct bes {  BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(1);
return bevp_pos;
}
BEC_2_4_12_TextByteIterator* BEC_2_4_12_TextByteIterator::bem_posSet_1(BEC_2_6_6_SystemObject* bevt_0_ta_SET) {
struct bes { BEC_2_6_6_SystemObject* bevt_0_ta_SET; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->bevt_0_ta_SET = bevt_0_ta_SET;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(2);
bevp_pos = static_cast<BEC_2_4_3_MathInt*>(beq->bevt_0_ta_SET);
return this;
}
BEC_2_6_6_SystemObject* BEC_2_4_12_TextByteIterator::bemd_0(int32_t callId) {
switch (callId) {
case 950712084: return bem_serializeToString_0();
case 814057402: return bem_containerGet_0();
case -1785532669: return bem_new_0();
case -119099042: return bem_nextGet_0();
case 448214784: return bem_hasNextGet_0();
case 526909609: return bem_posGet_0();
case -997655856: return bem_byteIteratorIteratorGet_0();
case -1428269309: return bem_iteratorGet_0();
}
return bevs_super::bemd_0(callId);
}
BEC_2_6_6_SystemObject* BEC_2_4_12_TextByteIterator::bemd_1(int32_t callId, BEC_2_6_6_SystemObject* bevd_0) {
switch (callId) {
case -1793507420: return bem_next_1(static_cast<BEC_2_4_6_TextString*>(bevd_0));
case 189929456: return bem_posSet_1(bevd_0);
case 71436049: return bem_nextInt_1(static_cast<BEC_2_4_3_MathInt*>(bevd_0));
case -1618488206: return bem_deserializeFromStringNew_1(static_cast<BEC_2_4_6_TextString*>(bevd_0));
case 321660806: return bem_currentIntSet_1(static_cast<BEC_2_4_3_MathInt*>(bevd_0));
case 877763487: return bem_currentInt_1(static_cast<BEC_2_4_3_MathInt*>(bevd_0));
case 1899676304: return bem_new_1(static_cast<BEC_2_4_6_TextString*>(bevd_0));
}
return bevs_super::bemd_1(callId, bevd_0);
}
BEC_2_6_6_SystemObject* BEC_2_4_12_TextByteIterator::bemc_create() {
return new BEC_2_4_12_TextByteIterator();
}
void BEC_2_4_12_TextByteIterator::bemc_setInitial(BEC_2_6_6_SystemObject* becc_inst) {
BEC_2_4_12_TextByteIterator::bece_BEC_2_4_12_TextByteIterator_bevs_inst = static_cast<BEC_2_4_12_TextByteIterator*>(becc_inst);
}
BEC_2_6_6_SystemObject* BEC_2_4_12_TextByteIterator::bemc_getInitial() {
return BEC_2_4_12_TextByteIterator::bece_BEC_2_4_12_TextByteIterator_bevs_inst;
}
void BEC_2_4_12_TextByteIterator::bemg_doMark() {
bevg_gcMark = BECS_Runtime::bevg_currentGcMark;
if (bevp_pos != nullptr && bevp_pos->bevg_gcMark != BECS_Runtime::bevg_currentGcMark) {
bevp_pos->bemg_doMark();
}
if (bevp_str != nullptr && bevp_str->bevg_gcMark != BECS_Runtime::bevg_currentGcMark) {
bevp_str->bemg_doMark();
}
if (bevp_vcopy != nullptr && bevp_vcopy->bevg_gcMark != BECS_Runtime::bevg_currentGcMark) {
bevp_vcopy->bemg_doMark();
}
}
size_t BEC_2_4_12_TextByteIterator::bemg_getSize() {
return sizeof(*this);
}
BETS_Object* BEC_2_4_12_TextByteIterator::bemc_getType() {
return &BEC_2_4_12_TextByteIterator::bece_BEC_2_4_12_TextByteIterator_bevs_type;
}
BET_2_5_4_LogicBool::BET_2_5_4_LogicBool() {
std::vector<std::string> bevs_mtnames = {  };
bevs_fieldNames = {  };
}
BEC_2_6_6_SystemObject* BET_2_5_4_LogicBool::bems_createInstance() {
return new BEC_2_5_4_LogicBool();
}
void BET_2_5_4_LogicBool::bemgt_doMark() {
BEC_2_6_6_SystemObject* bevsl_inst_ref = *bevs_inst_ref;
if (bevsl_inst_ref != nullptr && bevsl_inst_ref->bevg_gcMark != BECS_Runtime::bevg_currentGcMark) {
bevsl_inst_ref->bemg_doMark();
}
}
BEC_2_5_4_LogicBool* BEC_2_5_4_LogicBool::bece_BEC_2_5_4_LogicBool_bevs_inst;

BET_2_5_4_LogicBool BEC_2_5_4_LogicBool::bece_BEC_2_5_4_LogicBool_bevs_type;
BEC_2_6_6_SystemObject** BET_2_5_4_LogicBool::bevs_inst_ref = (BEC_2_6_6_SystemObject**) &BEC_2_5_4_LogicBool::bece_BEC_2_5_4_LogicBool_bevs_inst;

BEC_2_6_6_SystemObject* BEC_2_5_4_LogicBool::bem_new_0() {
struct bes {  BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(1);
return this;
}
BEC_2_5_4_LogicBool* BEC_2_5_4_LogicBool::bem_new_1(BEC_2_6_6_SystemObject* bevk_str) {
struct bes { BEC_2_6_6_SystemObject* beva_str; BEC_2_6_6_SystemObject* bevt_0_ta_ph; BEC_2_4_6_TextString* bevt_1_ta_ph; BEC_2_5_4_LogicBool* bevt_2_ta_ph; BEC_2_5_4_LogicBool* bevt_3_ta_ph; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->beva_str = bevk_str;
beq->bevt_0_ta_ph = nullptr;
beq->bevt_1_ta_ph = nullptr;
beq->bevt_2_ta_ph = nullptr;
beq->bevt_3_ta_ph = nullptr;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(6);
beq->bevt_1_ta_ph = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString(4, {0x74,0x72,0x75,0x65}))));
beq->bevt_0_ta_ph = beq->beva_str->bemd_1(643138569, beq->bevt_1_ta_ph);
if ((static_cast<BEC_2_5_4_LogicBool*>(beq->bevt_0_ta_ph))->bevi_bool) {
beq->bevt_2_ta_ph = static_cast<BEC_2_5_4_LogicBool*>(BECS_Runtime::boolTrue);
return beq->bevt_2_ta_ph;
} 
beq->bevt_3_ta_ph = static_cast<BEC_2_5_4_LogicBool*>(BECS_Runtime::boolFalse);
return beq->bevt_3_ta_ph;
}
BEC_2_5_4_LogicBool* BEC_2_5_4_LogicBool::bem_checkDefNew_1(BEC_2_6_6_SystemObject* bevk_str) {
struct bes { BEC_2_6_6_SystemObject* beva_str; BEC_2_5_4_LogicBool* bevt_0_ta_anchor; BEC_2_5_4_LogicBool* bevt_1_ta_ph; BEC_2_6_6_SystemObject* bevt_2_ta_ph; BEC_2_4_6_TextString* bevt_3_ta_ph; BEC_2_5_4_LogicBool* bevt_4_ta_ph; BEC_2_5_4_LogicBool* bevt_5_ta_ph; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->beva_str = bevk_str;
beq->bevt_0_ta_anchor = nullptr;
beq->bevt_1_ta_ph = nullptr;
beq->bevt_2_ta_ph = nullptr;
beq->bevt_3_ta_ph = nullptr;
beq->bevt_4_ta_ph = nullptr;
beq->bevt_5_ta_ph = nullptr;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(8);
if (beq->beva_str == nullptr) {
beq->bevt_1_ta_ph = BECS_Runtime::boolFalse;
 } else { 
beq->bevt_1_ta_ph = BECS_Runtime::boolTrue;
}
if (beq->bevt_1_ta_ph->bevi_bool) {
beq->bevt_3_ta_ph = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString(4, {0x74,0x72,0x75,0x65}))));
beq->bevt_2_ta_ph = beq->beva_str->bemd_1(643138569, beq->bevt_3_ta_ph);
if ((static_cast<BEC_2_5_4_LogicBool*>(beq->bevt_2_ta_ph))->bevi_bool) {
beq->bevt_0_ta_anchor = BECS_Runtime::boolTrue;
} 
 else  {
beq->bevt_0_ta_anchor = BECS_Runtime::boolFalse;
} 
} 
 else  {
beq->bevt_0_ta_anchor = BECS_Runtime::boolFalse;
} 
if (beq->bevt_0_ta_anchor->bevi_bool) {
beq->bevt_4_ta_ph = static_cast<BEC_2_5_4_LogicBool*>(BECS_Runtime::boolTrue);
return beq->bevt_4_ta_ph;
} 
beq->bevt_5_ta_ph = static_cast<BEC_2_5_4_LogicBool*>(BECS_Runtime::boolFalse);
return beq->bevt_5_ta_ph;
}
BEC_2_5_4_LogicBool* BEC_2_5_4_LogicBool::bem_serializeContentsGet_0() {
struct bes { BEC_2_5_4_LogicBool* bevt_0_ta_ph; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->bevt_0_ta_ph = nullptr;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(2);
beq->bevt_0_ta_ph = static_cast<BEC_2_5_4_LogicBool*>(BECS_Runtime::boolFalse);
return beq->bevt_0_ta_ph;
}
BEC_2_4_6_TextString* BEC_2_5_4_LogicBool::bem_serializeToString_0() {
struct bes { BEC_2_4_6_TextString* bevt_0_ta_ph; BEC_2_4_6_TextString* bevt_1_ta_ph; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->bevt_0_ta_ph = nullptr;
beq->bevt_1_ta_ph = nullptr;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(3);
if (bevi_bool) {
beq->bevt_0_ta_ph = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString(1, {0x31}))));
return beq->bevt_0_ta_ph;
} 
beq->bevt_1_ta_ph = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString(1, {0x30}))));
return beq->bevt_1_ta_ph;
}
BEC_2_4_6_TextString* BEC_2_5_4_LogicBool::bem_deserializeClassNameGet_0() {
struct bes { BEC_2_4_6_TextString* bevt_0_ta_ph; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->bevt_0_ta_ph = nullptr;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(2);
beq->bevt_0_ta_ph = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString(11, {0x4C,0x6F,0x67,0x69,0x63,0x3A,0x42,0x6F,0x6F,0x6C,0x73}))));
return beq->bevt_0_ta_ph;
}
BEC_2_4_3_MathInt* BEC_2_5_4_LogicBool::bem_hashGet_0() {
struct bes { BEC_2_4_3_MathInt* bevt_0_ta_ph; BEC_2_4_3_MathInt* bevt_1_ta_ph; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->bevt_0_ta_ph = nullptr;
beq->bevt_1_ta_ph = nullptr;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(3);
if (bevi_bool) {
beq->bevt_0_ta_ph = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(1))));
return beq->bevt_0_ta_ph;
} 
beq->bevt_1_ta_ph = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(0))));
return beq->bevt_1_ta_ph;
}
BEC_2_5_4_LogicBool* BEC_2_5_4_LogicBool::bem_increment_0() {
struct bes { BEC_2_5_4_LogicBool* bevt_0_ta_ph; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->bevt_0_ta_ph = nullptr;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(2);
beq->bevt_0_ta_ph = static_cast<BEC_2_5_4_LogicBool*>(BECS_Runtime::boolTrue);
return beq->bevt_0_ta_ph;
}
BEC_2_5_4_LogicBool* BEC_2_5_4_LogicBool::bem_decrement_0() {
struct bes { BEC_2_5_4_LogicBool* bevt_0_ta_ph; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->bevt_0_ta_ph = nullptr;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(2);
beq->bevt_0_ta_ph = static_cast<BEC_2_5_4_LogicBool*>(BECS_Runtime::boolFalse);
return beq->bevt_0_ta_ph;
}
BEC_2_5_4_LogicBool* BEC_2_5_4_LogicBool::bem_not_0() {
struct bes { BEC_2_5_4_LogicBool* bevt_0_ta_ph; BEC_2_5_4_LogicBool* bevt_1_ta_ph; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->bevt_0_ta_ph = nullptr;
beq->bevt_1_ta_ph = nullptr;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(3);
if (bevi_bool) {
beq->bevt_0_ta_ph = static_cast<BEC_2_5_4_LogicBool*>(BECS_Runtime::boolFalse);
return beq->bevt_0_ta_ph;
} 
beq->bevt_1_ta_ph = static_cast<BEC_2_5_4_LogicBool*>(BECS_Runtime::boolTrue);
return beq->bevt_1_ta_ph;
}
BEC_2_4_6_TextString* BEC_2_5_4_LogicBool::bem_toString_0() {
struct bes { BEC_2_4_6_TextString* bevt_0_ta_ph; BEC_2_4_6_TextString* bevt_1_ta_ph; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->bevt_0_ta_ph = nullptr;
beq->bevt_1_ta_ph = nullptr;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(3);
if (bevi_bool) {
beq->bevt_0_ta_ph = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString(4, {0x74,0x72,0x75,0x65}))));
return beq->bevt_0_ta_ph;
} 
beq->bevt_1_ta_ph = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString(5, {0x66,0x61,0x6C,0x73,0x65}))));
return beq->bevt_1_ta_ph;
}
BEC_2_6_6_SystemObject* BEC_2_5_4_LogicBool::bem_copy_0() {
struct bes {  BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(1);
return this;
}
BEC_2_6_6_SystemObject* BEC_2_5_4_LogicBool::bemd_0(int32_t callId) {
switch (callId) {
case 2142500088: return bem_copy_0();
case 354802963: return bem_not_0();
case 25638260: return bem_increment_0();
case -1553512291: return bem_toString_0();
case 950712084: return bem_serializeToString_0();
case 1003273574: return bem_decrement_0();
case -1785532669: return bem_new_0();
case -656721707: return bem_deserializeClassNameGet_0();
case -534328503: return bem_serializeContentsGet_0();
case -1677156504: return bem_hashGet_0();
}
return bevs_super::bemd_0(callId);
}
BEC_2_6_6_SystemObject* BEC_2_5_4_LogicBool::bemd_1(int32_t callId, BEC_2_6_6_SystemObject* bevd_0) {
switch (callId) {
case -297720259: return bem_checkDefNew_1(bevd_0);
case 1899676304: return bem_new_1(bevd_0);
}
return bevs_super::bemd_1(callId, bevd_0);
}
BEC_2_6_6_SystemObject* BEC_2_5_4_LogicBool::bemc_create() {
return new BEC_2_5_4_LogicBool();
}
void BEC_2_5_4_LogicBool::bemc_setInitial(BEC_2_6_6_SystemObject* becc_inst) {
BEC_2_5_4_LogicBool::bece_BEC_2_5_4_LogicBool_bevs_inst = static_cast<BEC_2_5_4_LogicBool*>(becc_inst);
}
BEC_2_6_6_SystemObject* BEC_2_5_4_LogicBool::bemc_getInitial() {
return BEC_2_5_4_LogicBool::bece_BEC_2_5_4_LogicBool_bevs_inst;
}
void BEC_2_5_4_LogicBool::bemg_doMark() {
bevg_gcMark = BECS_Runtime::bevg_currentGcMark;
}
size_t BEC_2_5_4_LogicBool::bemg_getSize() {
return sizeof(*this);
}
BETS_Object* BEC_2_5_4_LogicBool::bemc_getType() {
return &BEC_2_5_4_LogicBool::bece_BEC_2_5_4_LogicBool_bevs_type;
}
BET_2_5_5_LogicBools::BET_2_5_5_LogicBools() {
std::vector<std::string> bevs_mtnames = {  };
bevs_fieldNames = {  };
}
BEC_2_6_6_SystemObject* BET_2_5_5_LogicBools::bems_createInstance() {
return new BEC_2_5_5_LogicBools();
}
void BET_2_5_5_LogicBools::bemgt_doMark() {
BEC_2_6_6_SystemObject* bevsl_inst_ref = *bevs_inst_ref;
if (bevsl_inst_ref != nullptr && bevsl_inst_ref->bevg_gcMark != BECS_Runtime::bevg_currentGcMark) {
bevsl_inst_ref->bemg_doMark();
}
}
BEC_2_5_5_LogicBools* BEC_2_5_5_LogicBools::bece_BEC_2_5_5_LogicBools_bevs_inst;

BET_2_5_5_LogicBools BEC_2_5_5_LogicBools::bece_BEC_2_5_5_LogicBools_bevs_type;
BEC_2_6_6_SystemObject** BET_2_5_5_LogicBools::bevs_inst_ref = (BEC_2_6_6_SystemObject**) &BEC_2_5_5_LogicBools::bece_BEC_2_5_5_LogicBools_bevs_inst;

BEC_2_6_6_SystemObject* BEC_2_5_5_LogicBools::bem_create_0() {
struct bes {  BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(1);
return this;
}
BEC_2_5_5_LogicBools* BEC_2_5_5_LogicBools::bem_default_0() {
struct bes {  BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(1);
return this;
}
BEC_2_5_4_LogicBool* BEC_2_5_5_LogicBools::bem_forString_1(BEC_2_6_6_SystemObject* bevk_str) {
struct bes { BEC_2_6_6_SystemObject* beva_str; BEC_2_6_6_SystemObject* bevt_0_ta_ph; BEC_2_4_6_TextString* bevt_1_ta_ph; BEC_2_5_4_LogicBool* bevt_2_ta_ph; BEC_2_5_4_LogicBool* bevt_3_ta_ph; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->beva_str = bevk_str;
beq->bevt_0_ta_ph = nullptr;
beq->bevt_1_ta_ph = nullptr;
beq->bevt_2_ta_ph = nullptr;
beq->bevt_3_ta_ph = nullptr;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(6);
beq->bevt_1_ta_ph = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString(4, {0x74,0x72,0x75,0x65}))));
beq->bevt_0_ta_ph = beq->beva_str->bemd_1(643138569, beq->bevt_1_ta_ph);
if ((static_cast<BEC_2_5_4_LogicBool*>(beq->bevt_0_ta_ph))->bevi_bool) {
beq->bevt_2_ta_ph = static_cast<BEC_2_5_4_LogicBool*>(BECS_Runtime::boolTrue);
return beq->bevt_2_ta_ph;
} 
beq->bevt_3_ta_ph = static_cast<BEC_2_5_4_LogicBool*>(BECS_Runtime::boolFalse);
return beq->bevt_3_ta_ph;
}
BEC_2_5_4_LogicBool* BEC_2_5_5_LogicBools::bem_fromString_1(BEC_2_6_6_SystemObject* bevk_str) {
struct bes { BEC_2_6_6_SystemObject* beva_str; BEC_2_5_4_LogicBool* bevt_0_ta_anchor; BEC_2_5_4_LogicBool* bevt_1_ta_ph; BEC_2_6_6_SystemObject* bevt_2_ta_ph; BEC_2_4_6_TextString* bevt_3_ta_ph; BEC_2_5_4_LogicBool* bevt_4_ta_ph; BEC_2_5_4_LogicBool* bevt_5_ta_ph; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->beva_str = bevk_str;
beq->bevt_0_ta_anchor = nullptr;
beq->bevt_1_ta_ph = nullptr;
beq->bevt_2_ta_ph = nullptr;
beq->bevt_3_ta_ph = nullptr;
beq->bevt_4_ta_ph = nullptr;
beq->bevt_5_ta_ph = nullptr;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(8);
if (beq->beva_str == nullptr) {
beq->bevt_1_ta_ph = BECS_Runtime::boolFalse;
 } else { 
beq->bevt_1_ta_ph = BECS_Runtime::boolTrue;
}
if (beq->bevt_1_ta_ph->bevi_bool) {
beq->bevt_3_ta_ph = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString(4, {0x74,0x72,0x75,0x65}))));
beq->bevt_2_ta_ph = beq->beva_str->bemd_1(643138569, beq->bevt_3_ta_ph);
if ((static_cast<BEC_2_5_4_LogicBool*>(beq->bevt_2_ta_ph))->bevi_bool) {
beq->bevt_0_ta_anchor = BECS_Runtime::boolTrue;
} 
 else  {
beq->bevt_0_ta_anchor = BECS_Runtime::boolFalse;
} 
} 
 else  {
beq->bevt_0_ta_anchor = BECS_Runtime::boolFalse;
} 
if (beq->bevt_0_ta_anchor->bevi_bool) {
beq->bevt_4_ta_ph = static_cast<BEC_2_5_4_LogicBool*>(BECS_Runtime::boolTrue);
return beq->bevt_4_ta_ph;
} 
beq->bevt_5_ta_ph = static_cast<BEC_2_5_4_LogicBool*>(BECS_Runtime::boolFalse);
return beq->bevt_5_ta_ph;
}
BEC_2_6_6_SystemObject* BEC_2_5_5_LogicBools::bem_deserializeFromString_1(BEC_2_4_6_TextString* bevk_str) {
struct bes { BEC_2_4_6_TextString* beva_str; BEC_2_5_4_LogicBool* bevt_0_ta_ph; BEC_2_4_6_TextString* bevt_1_ta_ph; BEC_2_5_4_LogicBool* bevt_2_ta_ph; BEC_2_5_4_LogicBool* bevt_3_ta_ph; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->beva_str = bevk_str;
beq->bevt_0_ta_ph = nullptr;
beq->bevt_1_ta_ph = nullptr;
beq->bevt_2_ta_ph = nullptr;
beq->bevt_3_ta_ph = nullptr;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(6);
beq->bevt_1_ta_ph = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString(1, {0x31}))));
beq->bevt_0_ta_ph = beq->beva_str->bem_equals_1(beq->bevt_1_ta_ph);
if (beq->bevt_0_ta_ph->bevi_bool) {
beq->bevt_2_ta_ph = static_cast<BEC_2_5_4_LogicBool*>(BECS_Runtime::boolTrue);
return beq->bevt_2_ta_ph;
} 
beq->bevt_3_ta_ph = static_cast<BEC_2_5_4_LogicBool*>(BECS_Runtime::boolFalse);
return beq->bevt_3_ta_ph;
}
BEC_2_6_6_SystemObject* BEC_2_5_5_LogicBools::bem_isTrue_1(BEC_2_5_4_LogicBool* bevk_val) {
struct bes { BEC_2_5_4_LogicBool* beva_val; BEC_2_5_4_LogicBool* bevt_0_ta_anchor; BEC_2_5_4_LogicBool* bevt_1_ta_ph; BEC_2_5_4_LogicBool* bevt_2_ta_ph; BEC_2_5_4_LogicBool* bevt_3_ta_ph; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->beva_val = bevk_val;
beq->bevt_0_ta_anchor = nullptr;
beq->bevt_1_ta_ph = nullptr;
beq->bevt_2_ta_ph = nullptr;
beq->bevt_3_ta_ph = nullptr;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(6);
if (beq->beva_val == nullptr) {
beq->bevt_1_ta_ph = BECS_Runtime::boolFalse;
 } else { 
beq->bevt_1_ta_ph = BECS_Runtime::boolTrue;
}
if (beq->bevt_1_ta_ph->bevi_bool) {
if (beq->beva_val->bevi_bool) {
beq->bevt_0_ta_anchor = BECS_Runtime::boolTrue;
} 
 else  {
beq->bevt_0_ta_anchor = BECS_Runtime::boolFalse;
} 
} 
 else  {
beq->bevt_0_ta_anchor = BECS_Runtime::boolFalse;
} 
if (beq->bevt_0_ta_anchor->bevi_bool) {
beq->bevt_2_ta_ph = static_cast<BEC_2_5_4_LogicBool*>(BECS_Runtime::boolTrue);
return beq->bevt_2_ta_ph;
} 
beq->bevt_3_ta_ph = static_cast<BEC_2_5_4_LogicBool*>(BECS_Runtime::boolFalse);
return beq->bevt_3_ta_ph;
}
BEC_2_6_6_SystemObject* BEC_2_5_5_LogicBools::bemd_0(int32_t callId) {
switch (callId) {
case 1312387167: return bem_create_0();
case 1188815194: return bem_default_0();
}
return bevs_super::bemd_0(callId);
}
BEC_2_6_6_SystemObject* BEC_2_5_5_LogicBools::bemd_1(int32_t callId, BEC_2_6_6_SystemObject* bevd_0) {
switch (callId) {
case -1998922832: return bem_deserializeFromString_1(static_cast<BEC_2_4_6_TextString*>(bevd_0));
case -2057579256: return bem_forString_1(bevd_0);
case 654314251: return bem_fromString_1(bevd_0);
case 612143167: return bem_isTrue_1(static_cast<BEC_2_5_4_LogicBool*>(bevd_0));
}
return bevs_super::bemd_1(callId, bevd_0);
}
BEC_2_6_6_SystemObject* BEC_2_5_5_LogicBools::bemc_create() {
return new BEC_2_5_5_LogicBools();
}
void BEC_2_5_5_LogicBools::bemc_setInitial(BEC_2_6_6_SystemObject* becc_inst) {
BEC_2_5_5_LogicBools::bece_BEC_2_5_5_LogicBools_bevs_inst = static_cast<BEC_2_5_5_LogicBools*>(becc_inst);
}
BEC_2_6_6_SystemObject* BEC_2_5_5_LogicBools::bemc_getInitial() {
return BEC_2_5_5_LogicBools::bece_BEC_2_5_5_LogicBools_bevs_inst;
}
void BEC_2_5_5_LogicBools::bemg_doMark() {
bevg_gcMark = BECS_Runtime::bevg_currentGcMark;
}
size_t BEC_2_5_5_LogicBools::bemg_getSize() {
return sizeof(*this);
}
BETS_Object* BEC_2_5_5_LogicBools::bemc_getType() {
return &BEC_2_5_5_LogicBools::bece_BEC_2_5_5_LogicBools_bevs_type;
}
BET_2_6_3_EncodeHex::BET_2_6_3_EncodeHex() {
std::vector<std::string> bevs_mtnames = {  };
bevs_fieldNames = {  };
}
BEC_2_6_6_SystemObject* BET_2_6_3_EncodeHex::bems_createInstance() {
return new BEC_2_6_3_EncodeHex();
}
void BET_2_6_3_EncodeHex::bemgt_doMark() {
BEC_2_6_6_SystemObject* bevsl_inst_ref = *bevs_inst_ref;
if (bevsl_inst_ref != nullptr && bevsl_inst_ref->bevg_gcMark != BECS_Runtime::bevg_currentGcMark) {
bevsl_inst_ref->bemg_doMark();
}
}
BEC_2_6_3_EncodeHex* BEC_2_6_3_EncodeHex::bece_BEC_2_6_3_EncodeHex_bevs_inst;

BET_2_6_3_EncodeHex BEC_2_6_3_EncodeHex::bece_BEC_2_6_3_EncodeHex_bevs_type;
BEC_2_6_6_SystemObject** BET_2_6_3_EncodeHex::bevs_inst_ref = (BEC_2_6_6_SystemObject**) &BEC_2_6_3_EncodeHex::bece_BEC_2_6_3_EncodeHex_bevs_inst;

BEC_2_6_6_SystemObject* BEC_2_6_3_EncodeHex::bem_create_0() {
struct bes {  BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(1);
return this;
}
BEC_2_6_3_EncodeHex* BEC_2_6_3_EncodeHex::bem_default_0() {
struct bes {  BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(1);
return this;
}
BEC_2_4_6_TextString* BEC_2_6_3_EncodeHex::bem_encode_1(BEC_2_4_6_TextString* bevk_str) {
struct bes { BEC_2_4_6_TextString* beva_str; BEC_2_4_3_MathInt* bevl_ac; BEC_2_4_6_TextString* bevl_cur; BEC_2_4_3_MathInt* bevl_ssz; BEC_2_4_6_TextString* bevl_r; BEC_2_4_3_MathInt* bevl_pos; BEC_2_4_3_MathInt* bevt_0_ta_ph; BEC_2_4_3_MathInt* bevt_1_ta_ph; BEC_2_4_3_MathInt* bevt_2_ta_ph; BEC_2_5_4_LogicBool* bevt_3_ta_ph; BEC_2_4_6_TextString* bevt_4_ta_ph; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->beva_str = bevk_str;
beq->bevl_ac = nullptr;
beq->bevl_cur = nullptr;
beq->bevl_ssz = nullptr;
beq->bevl_r = nullptr;
beq->bevl_pos = nullptr;
beq->bevt_0_ta_ph = nullptr;
beq->bevt_1_ta_ph = nullptr;
beq->bevt_2_ta_ph = nullptr;
beq->bevt_3_ta_ph = nullptr;
beq->bevt_4_ta_ph = nullptr;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(12);
beq->bevl_ac = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt())));
beq->bevt_0_ta_ph = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(2))));
beq->bevl_cur = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString()))->bem_new_1(beq->bevt_0_ta_ph));
beq->bevl_ssz = beq->beva_str->bem_sizeGet_0();
beq->bevt_2_ta_ph = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(2))));
beq->bevt_1_ta_ph = beq->bevl_ssz->bem_multiply_1(beq->bevt_2_ta_ph);
beq->bevl_r = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString()))->bem_new_1(beq->bevt_1_ta_ph));
beq->bevl_pos = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(0))));
while (true)
 {
if (beq->bevl_pos->bevi_int < beq->bevl_ssz->bevi_int) {
beq->bevt_3_ta_ph = BECS_Runtime::boolTrue;
 } else { 
beq->bevt_3_ta_ph = BECS_Runtime::boolFalse;
}
if (beq->bevt_3_ta_ph->bevi_bool) {
beq->beva_str->bem_getCode_2(beq->bevl_pos, beq->bevl_ac);
beq->bevt_4_ta_ph = beq->bevl_ac->bem_toHexString_1(beq->bevl_cur);
beq->bevl_r->bem_addValue_1(beq->bevt_4_ta_ph);
beq->bevl_pos->bevi_int++;
} 
 else  {
break;
} 
} 
return beq->bevl_r;
}
BEC_2_4_6_TextString* BEC_2_6_3_EncodeHex::bem_decode_1(BEC_2_4_6_TextString* bevk_str) {
struct bes { BEC_2_4_6_TextString* beva_str; BEC_2_4_3_MathInt* bevl_ssz; BEC_2_4_6_TextString* bevl_cur; BEC_2_4_6_TextString* bevl_r; BEC_2_4_12_TextByteIterator* bevl_tb; BEC_2_4_6_TextString* bevl_pta; BEC_2_4_6_TextString* bevl_ptb; BEC_2_4_3_MathInt* bevl_pos; BEC_2_5_4_LogicBool* bevt_0_ta_ph; BEC_2_4_3_MathInt* bevt_1_ta_ph; BEC_2_5_4_LogicBool* bevt_2_ta_ph; BEC_2_4_3_MathInt* bevt_3_ta_ph; BEC_2_4_3_MathInt* bevt_4_ta_ph; BEC_2_4_3_MathInt* bevt_5_ta_ph; BEC_2_6_9_SystemException* bevt_6_ta_ph; BEC_2_4_6_TextString* bevt_7_ta_ph; BEC_2_4_6_TextString* bevt_8_ta_ph; BEC_2_4_3_MathInt* bevt_9_ta_ph; BEC_2_4_3_MathInt* bevt_10_ta_ph; BEC_2_4_3_MathInt* bevt_11_ta_ph; BEC_2_4_3_MathInt* bevt_12_ta_ph; BEC_2_4_3_MathInt* bevt_13_ta_ph; BEC_2_4_3_MathInt* bevt_14_ta_ph; BEC_2_4_3_MathInt* bevt_15_ta_ph; BEC_2_5_4_LogicBool* bevt_16_ta_ph; BEC_2_4_3_MathInt* bevt_17_ta_ph; BEC_2_4_6_TextString* bevt_18_ta_ph; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->beva_str = bevk_str;
beq->bevl_ssz = nullptr;
beq->bevl_cur = nullptr;
beq->bevl_r = nullptr;
beq->bevl_tb = nullptr;
beq->bevl_pta = nullptr;
beq->bevl_ptb = nullptr;
beq->bevl_pos = nullptr;
beq->bevt_0_ta_ph = nullptr;
beq->bevt_1_ta_ph = nullptr;
beq->bevt_2_ta_ph = nullptr;
beq->bevt_3_ta_ph = nullptr;
beq->bevt_4_ta_ph = nullptr;
beq->bevt_5_ta_ph = nullptr;
beq->bevt_6_ta_ph = nullptr;
beq->bevt_7_ta_ph = nullptr;
beq->bevt_8_ta_ph = nullptr;
beq->bevt_9_ta_ph = nullptr;
beq->bevt_10_ta_ph = nullptr;
beq->bevt_11_ta_ph = nullptr;
beq->bevt_12_ta_ph = nullptr;
beq->bevt_13_ta_ph = nullptr;
beq->bevt_14_ta_ph = nullptr;
beq->bevt_15_ta_ph = nullptr;
beq->bevt_16_ta_ph = nullptr;
beq->bevt_17_ta_ph = nullptr;
beq->bevt_18_ta_ph = nullptr;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(28);
beq->bevl_ssz = beq->beva_str->bem_sizeGet_0();
beq->bevt_1_ta_ph = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(1))));
if (beq->bevl_ssz->bevi_int < beq->bevt_1_ta_ph->bevi_int) {
beq->bevt_0_ta_ph = BECS_Runtime::boolTrue;
 } else { 
beq->bevt_0_ta_ph = BECS_Runtime::boolFalse;
}
if (beq->bevt_0_ta_ph->bevi_bool) {
return beq->beva_str;
} 
beq->bevt_4_ta_ph = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(2))));
beq->bevt_3_ta_ph = beq->bevl_ssz->bem_modulus_1(beq->bevt_4_ta_ph);
beq->bevt_5_ta_ph = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(0))));
if (beq->bevt_3_ta_ph->bevi_int != beq->bevt_5_ta_ph->bevi_int) {
beq->bevt_2_ta_ph = BECS_Runtime::boolTrue;
 } else { 
beq->bevt_2_ta_ph = BECS_Runtime::boolFalse;
}
if (beq->bevt_2_ta_ph->bevi_bool) {
beq->bevt_8_ta_ph = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString(26, {0x49,0x6E,0x76,0x61,0x6C,0x69,0x64,0x20,0x68,0x65,0x78,0x20,0x73,0x74,0x72,0x69,0x6E,0x67,0x20,0x6C,0x65,0x6E,0x67,0x74,0x68,0x20}))));
beq->bevt_7_ta_ph = beq->bevt_8_ta_ph->bem_add_1(beq->bevl_ssz);
beq->bevt_6_ta_ph = static_cast<BEC_2_6_9_SystemException*>(((BEC_2_6_9_SystemException*) (new BEC_2_6_9_SystemException()))->bem_new_1(beq->bevt_7_ta_ph));
throw BECS_ThrowBack(beq->bevt_6_ta_ph);
} 
beq->bevt_9_ta_ph = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(2))));
beq->bevl_cur = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString()))->bem_new_1(beq->bevt_9_ta_ph));
beq->bevt_11_ta_ph = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(2))));
beq->bevt_10_ta_ph = beq->bevl_ssz->bem_divide_1(beq->bevt_11_ta_ph);
beq->bevl_r = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString()))->bem_new_1(beq->bevt_10_ta_ph));
beq->bevt_13_ta_ph = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(2))));
beq->bevt_12_ta_ph = beq->bevl_ssz->bem_divide_1(beq->bevt_13_ta_ph);
beq->bevl_r->bem_sizeSet_1(beq->bevt_12_ta_ph);
beq->bevl_tb = static_cast<BEC_2_4_12_TextByteIterator*>(((BEC_2_4_12_TextByteIterator*) (new BEC_2_4_12_TextByteIterator()))->bem_new_1(beq->beva_str));
beq->bevt_14_ta_ph = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(1))));
beq->bevl_pta = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString()))->bem_new_1(beq->bevt_14_ta_ph));
beq->bevt_15_ta_ph = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(1))));
beq->bevl_ptb = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString()))->bem_new_1(beq->bevt_15_ta_ph));
beq->bevl_pos = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(0))));
while (true)
 {
beq->bevt_16_ta_ph = beq->bevl_tb->bem_hasNextGet_0();
if (beq->bevt_16_ta_ph->bevi_bool) {
beq->bevl_tb->bem_next_1(beq->bevl_pta);
beq->bevl_tb->bem_next_1(beq->bevl_ptb);
beq->bevt_18_ta_ph = beq->bevl_pta->bem_add_1(beq->bevl_ptb);
beq->bevt_17_ta_ph = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt()))->bem_hexNew_1(beq->bevt_18_ta_ph));
beq->bevl_r->bem_setCodeUnchecked_2(beq->bevl_pos, beq->bevt_17_ta_ph);
beq->bevl_pos->bevi_int++;
} 
 else  {
break;
} 
} 
return beq->bevl_r;
}
BEC_2_6_6_SystemObject* BEC_2_6_3_EncodeHex::bemd_0(int32_t callId) {
switch (callId) {
case 1312387167: return bem_create_0();
case 1188815194: return bem_default_0();
}
return bevs_super::bemd_0(callId);
}
BEC_2_6_6_SystemObject* BEC_2_6_3_EncodeHex::bemd_1(int32_t callId, BEC_2_6_6_SystemObject* bevd_0) {
switch (callId) {
case -1557312399: return bem_encode_1(static_cast<BEC_2_4_6_TextString*>(bevd_0));
case 1305979012: return bem_decode_1(static_cast<BEC_2_4_6_TextString*>(bevd_0));
}
return bevs_super::bemd_1(callId, bevd_0);
}
BEC_2_6_6_SystemObject* BEC_2_6_3_EncodeHex::bemc_create() {
return new BEC_2_6_3_EncodeHex();
}
void BEC_2_6_3_EncodeHex::bemc_setInitial(BEC_2_6_6_SystemObject* becc_inst) {
BEC_2_6_3_EncodeHex::bece_BEC_2_6_3_EncodeHex_bevs_inst = static_cast<BEC_2_6_3_EncodeHex*>(becc_inst);
}
BEC_2_6_6_SystemObject* BEC_2_6_3_EncodeHex::bemc_getInitial() {
return BEC_2_6_3_EncodeHex::bece_BEC_2_6_3_EncodeHex_bevs_inst;
}
void BEC_2_6_3_EncodeHex::bemg_doMark() {
bevg_gcMark = BECS_Runtime::bevg_currentGcMark;
}
size_t BEC_2_6_3_EncodeHex::bemg_getSize() {
return sizeof(*this);
}
BETS_Object* BEC_2_6_3_EncodeHex::bemc_getType() {
return &BEC_2_6_3_EncodeHex::bece_BEC_2_6_3_EncodeHex_bevs_type;
}
BET_2_6_3_EncodeUrl::BET_2_6_3_EncodeUrl() {
std::vector<std::string> bevs_mtnames = {  };
bevs_fieldNames = {  };
}
BEC_2_6_6_SystemObject* BET_2_6_3_EncodeUrl::bems_createInstance() {
return new BEC_2_6_3_EncodeUrl();
}
void BET_2_6_3_EncodeUrl::bemgt_doMark() {
BEC_2_6_6_SystemObject* bevsl_inst_ref = *bevs_inst_ref;
if (bevsl_inst_ref != nullptr && bevsl_inst_ref->bevg_gcMark != BECS_Runtime::bevg_currentGcMark) {
bevsl_inst_ref->bemg_doMark();
}
}
BEC_2_6_3_EncodeUrl* BEC_2_6_3_EncodeUrl::bece_BEC_2_6_3_EncodeUrl_bevs_inst;

BET_2_6_3_EncodeUrl BEC_2_6_3_EncodeUrl::bece_BEC_2_6_3_EncodeUrl_bevs_type;
BEC_2_6_6_SystemObject** BET_2_6_3_EncodeUrl::bevs_inst_ref = (BEC_2_6_6_SystemObject**) &BEC_2_6_3_EncodeUrl::bece_BEC_2_6_3_EncodeUrl_bevs_inst;

BEC_2_6_6_SystemObject* BEC_2_6_3_EncodeUrl::bem_create_0() {
struct bes {  BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(1);
return this;
}
BEC_2_6_3_EncodeUrl* BEC_2_6_3_EncodeUrl::bem_default_0() {
struct bes {  BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(1);
return this;
}
BEC_2_4_6_TextString* BEC_2_6_3_EncodeUrl::bem_encode_1(BEC_2_4_6_TextString* bevk_str) {
struct bes { BEC_2_4_6_TextString* beva_str; BEC_2_4_6_TextString* bevl_r; BEC_2_4_12_TextByteIterator* bevl_tb; BEC_2_4_6_TextString* bevl_pt; BEC_2_4_3_MathInt* bevl_ac; BEC_2_4_6_TextString* bevl_hcs; BEC_2_5_4_LogicBool* bevt_0_ta_anchor; BEC_2_5_4_LogicBool* bevt_1_ta_anchor; BEC_2_5_4_LogicBool* bevt_2_ta_anchor; BEC_2_5_4_LogicBool* bevt_3_ta_anchor; BEC_2_5_4_LogicBool* bevt_4_ta_anchor; BEC_2_4_3_MathInt* bevt_5_ta_ph; BEC_2_4_3_MathInt* bevt_6_ta_ph; BEC_2_4_3_MathInt* bevt_7_ta_ph; BEC_2_4_3_MathInt* bevt_8_ta_ph; BEC_2_5_4_LogicBool* bevt_9_ta_ph; BEC_2_4_3_MathInt* bevt_10_ta_ph; BEC_2_5_4_LogicBool* bevt_11_ta_ph; BEC_2_4_3_MathInt* bevt_12_ta_ph; BEC_2_5_4_LogicBool* bevt_13_ta_ph; BEC_2_4_3_MathInt* bevt_14_ta_ph; BEC_2_5_4_LogicBool* bevt_15_ta_ph; BEC_2_4_3_MathInt* bevt_16_ta_ph; BEC_2_5_4_LogicBool* bevt_17_ta_ph; BEC_2_4_3_MathInt* bevt_18_ta_ph; BEC_2_5_4_LogicBool* bevt_19_ta_ph; BEC_2_4_3_MathInt* bevt_20_ta_ph; BEC_2_5_4_LogicBool* bevt_21_ta_ph; BEC_2_4_3_MathInt* bevt_22_ta_ph; BEC_2_5_4_LogicBool* bevt_23_ta_ph; BEC_2_4_3_MathInt* bevt_24_ta_ph; BEC_2_5_4_LogicBool* bevt_25_ta_ph; BEC_2_4_3_MathInt* bevt_26_ta_ph; BEC_2_5_4_LogicBool* bevt_27_ta_ph; BEC_2_4_3_MathInt* bevt_28_ta_ph; BEC_2_5_4_LogicBool* bevt_29_ta_ph; BEC_2_4_3_MathInt* bevt_30_ta_ph; BEC_2_4_6_TextString* bevt_31_ta_ph; BEC_2_4_6_TextString* bevt_32_ta_ph; BEC_2_4_3_MathInt* bevt_33_ta_ph; BEC_2_4_6_TextString* bevt_34_ta_ph; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->beva_str = bevk_str;
beq->bevl_r = nullptr;
beq->bevl_tb = nullptr;
beq->bevl_pt = nullptr;
beq->bevl_ac = nullptr;
beq->bevl_hcs = nullptr;
beq->bevt_0_ta_anchor = nullptr;
beq->bevt_1_ta_anchor = nullptr;
beq->bevt_2_ta_anchor = nullptr;
beq->bevt_3_ta_anchor = nullptr;
beq->bevt_4_ta_anchor = nullptr;
beq->bevt_5_ta_ph = nullptr;
beq->bevt_6_ta_ph = nullptr;
beq->bevt_7_ta_ph = nullptr;
beq->bevt_8_ta_ph = nullptr;
beq->bevt_9_ta_ph = nullptr;
beq->bevt_10_ta_ph = nullptr;
beq->bevt_11_ta_ph = nullptr;
beq->bevt_12_ta_ph = nullptr;
beq->bevt_13_ta_ph = nullptr;
beq->bevt_14_ta_ph = nullptr;
beq->bevt_15_ta_ph = nullptr;
beq->bevt_16_ta_ph = nullptr;
beq->bevt_17_ta_ph = nullptr;
beq->bevt_18_ta_ph = nullptr;
beq->bevt_19_ta_ph = nullptr;
beq->bevt_20_ta_ph = nullptr;
beq->bevt_21_ta_ph = nullptr;
beq->bevt_22_ta_ph = nullptr;
beq->bevt_23_ta_ph = nullptr;
beq->bevt_24_ta_ph = nullptr;
beq->bevt_25_ta_ph = nullptr;
beq->bevt_26_ta_ph = nullptr;
beq->bevt_27_ta_ph = nullptr;
beq->bevt_28_ta_ph = nullptr;
beq->bevt_29_ta_ph = nullptr;
beq->bevt_30_ta_ph = nullptr;
beq->bevt_31_ta_ph = nullptr;
beq->bevt_32_ta_ph = nullptr;
beq->bevt_33_ta_ph = nullptr;
beq->bevt_34_ta_ph = nullptr;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(42);
beq->bevt_6_ta_ph = beq->beva_str->bem_sizeGet_0();
beq->bevt_7_ta_ph = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(2))));
beq->bevt_5_ta_ph = beq->bevt_6_ta_ph->bem_multiply_1(beq->bevt_7_ta_ph);
beq->bevl_r = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString()))->bem_new_1(beq->bevt_5_ta_ph));
beq->bevl_tb = static_cast<BEC_2_4_12_TextByteIterator*>(((BEC_2_4_12_TextByteIterator*) (new BEC_2_4_12_TextByteIterator()))->bem_new_1(beq->beva_str));
beq->bevt_8_ta_ph = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(2))));
beq->bevl_pt = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString()))->bem_new_1(beq->bevt_8_ta_ph));
while (true)
 {
beq->bevt_9_ta_ph = beq->bevl_tb->bem_hasNextGet_0();
if (beq->bevt_9_ta_ph->bevi_bool) {
beq->bevl_tb->bem_next_1(beq->bevl_pt);
beq->bevt_10_ta_ph = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(0))));
beq->bevl_ac = beq->bevl_pt->bem_getCode_1(beq->bevt_10_ta_ph);
beq->bevt_12_ta_ph = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(47))));
if (beq->bevl_ac->bevi_int > beq->bevt_12_ta_ph->bevi_int) {
beq->bevt_11_ta_ph = BECS_Runtime::boolTrue;
 } else { 
beq->bevt_11_ta_ph = BECS_Runtime::boolFalse;
}
if (beq->bevt_11_ta_ph->bevi_bool) {
beq->bevt_14_ta_ph = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(58))));
if (beq->bevl_ac->bevi_int < beq->bevt_14_ta_ph->bevi_int) {
beq->bevt_13_ta_ph = BECS_Runtime::boolTrue;
 } else { 
beq->bevt_13_ta_ph = BECS_Runtime::boolFalse;
}
if (beq->bevt_13_ta_ph->bevi_bool) {
beq->bevt_4_ta_anchor = BECS_Runtime::boolTrue;
} 
 else  {
beq->bevt_4_ta_anchor = BECS_Runtime::boolFalse;
} 
} 
 else  {
beq->bevt_4_ta_anchor = BECS_Runtime::boolFalse;
} 
if (beq->bevt_4_ta_anchor->bevi_bool) {
beq->bevt_3_ta_anchor = BECS_Runtime::boolTrue;
} 
 else  {
beq->bevt_16_ta_ph = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(64))));
if (beq->bevl_ac->bevi_int > beq->bevt_16_ta_ph->bevi_int) {
beq->bevt_15_ta_ph = BECS_Runtime::boolTrue;
 } else { 
beq->bevt_15_ta_ph = BECS_Runtime::boolFalse;
}
if (beq->bevt_15_ta_ph->bevi_bool) {
beq->bevt_18_ta_ph = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(94))));
if (beq->bevl_ac->bevi_int < beq->bevt_18_ta_ph->bevi_int) {
beq->bevt_17_ta_ph = BECS_Runtime::boolTrue;
 } else { 
beq->bevt_17_ta_ph = BECS_Runtime::boolFalse;
}
if (beq->bevt_17_ta_ph->bevi_bool) {
beq->bevt_3_ta_anchor = BECS_Runtime::boolTrue;
} 
 else  {
beq->bevt_3_ta_anchor = BECS_Runtime::boolFalse;
} 
} 
 else  {
beq->bevt_3_ta_anchor = BECS_Runtime::boolFalse;
} 
if (beq->bevt_3_ta_anchor->bevi_bool) {
beq->bevt_3_ta_anchor = BECS_Runtime::boolTrue;
} 
 else  {
beq->bevt_3_ta_anchor = BECS_Runtime::boolFalse;
} 
} 
if (beq->bevt_3_ta_anchor->bevi_bool) {
beq->bevt_2_ta_anchor = BECS_Runtime::boolTrue;
} 
 else  {
beq->bevt_20_ta_ph = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(94))));
if (beq->bevl_ac->bevi_int > beq->bevt_20_ta_ph->bevi_int) {
beq->bevt_19_ta_ph = BECS_Runtime::boolTrue;
 } else { 
beq->bevt_19_ta_ph = BECS_Runtime::boolFalse;
}
if (beq->bevt_19_ta_ph->bevi_bool) {
beq->bevt_22_ta_ph = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(123))));
if (beq->bevl_ac->bevi_int < beq->bevt_22_ta_ph->bevi_int) {
beq->bevt_21_ta_ph = BECS_Runtime::boolTrue;
 } else { 
beq->bevt_21_ta_ph = BECS_Runtime::boolFalse;
}
if (beq->bevt_21_ta_ph->bevi_bool) {
beq->bevt_2_ta_anchor = BECS_Runtime::boolTrue;
} 
 else  {
beq->bevt_2_ta_anchor = BECS_Runtime::boolFalse;
} 
} 
 else  {
beq->bevt_2_ta_anchor = BECS_Runtime::boolFalse;
} 
if (beq->bevt_2_ta_anchor->bevi_bool) {
beq->bevt_2_ta_anchor = BECS_Runtime::boolTrue;
} 
 else  {
beq->bevt_2_ta_anchor = BECS_Runtime::boolFalse;
} 
} 
if (beq->bevt_2_ta_anchor->bevi_bool) {
beq->bevt_1_ta_anchor = BECS_Runtime::boolTrue;
} 
 else  {
beq->bevt_24_ta_ph = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(44))));
if (beq->bevl_ac->bevi_int > beq->bevt_24_ta_ph->bevi_int) {
beq->bevt_23_ta_ph = BECS_Runtime::boolTrue;
 } else { 
beq->bevt_23_ta_ph = BECS_Runtime::boolFalse;
}
if (beq->bevt_23_ta_ph->bevi_bool) {
beq->bevt_26_ta_ph = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(47))));
if (beq->bevl_ac->bevi_int < beq->bevt_26_ta_ph->bevi_int) {
beq->bevt_25_ta_ph = BECS_Runtime::boolTrue;
 } else { 
beq->bevt_25_ta_ph = BECS_Runtime::boolFalse;
}
if (beq->bevt_25_ta_ph->bevi_bool) {
beq->bevt_1_ta_anchor = BECS_Runtime::boolTrue;
} 
 else  {
beq->bevt_1_ta_anchor = BECS_Runtime::boolFalse;
} 
} 
 else  {
beq->bevt_1_ta_anchor = BECS_Runtime::boolFalse;
} 
if (beq->bevt_1_ta_anchor->bevi_bool) {
beq->bevt_1_ta_anchor = BECS_Runtime::boolTrue;
} 
 else  {
beq->bevt_1_ta_anchor = BECS_Runtime::boolFalse;
} 
} 
if (beq->bevt_1_ta_anchor->bevi_bool) {
beq->bevt_0_ta_anchor = BECS_Runtime::boolTrue;
} 
 else  {
beq->bevt_28_ta_ph = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(42))));
if (beq->bevl_ac->bevi_int == beq->bevt_28_ta_ph->bevi_int) {
beq->bevt_27_ta_ph = BECS_Runtime::boolTrue;
 } else { 
beq->bevt_27_ta_ph = BECS_Runtime::boolFalse;
}
if (beq->bevt_27_ta_ph->bevi_bool) {
beq->bevt_0_ta_anchor = BECS_Runtime::boolTrue;
} 
 else  {
beq->bevt_0_ta_anchor = BECS_Runtime::boolFalse;
} 
} 
if (beq->bevt_0_ta_anchor->bevi_bool) {
beq->bevl_r->bem_addValue_1(beq->bevl_pt);
} 
 else  {
beq->bevt_30_ta_ph = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(32))));
if (beq->bevl_ac->bevi_int == beq->bevt_30_ta_ph->bevi_int) {
beq->bevt_29_ta_ph = BECS_Runtime::boolTrue;
 } else { 
beq->bevt_29_ta_ph = BECS_Runtime::boolFalse;
}
if (beq->bevt_29_ta_ph->bevi_bool) {
beq->bevt_31_ta_ph = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString(1, {0x2B}))));
beq->bevl_r->bem_addValue_1(beq->bevt_31_ta_ph);
} 
 else  {
beq->bevt_32_ta_ph = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString(1, {0x25}))));
beq->bevl_r->bem_addValue_1(beq->bevt_32_ta_ph);
beq->bevt_33_ta_ph = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(0))));
beq->bevl_hcs = beq->bevl_pt->bem_getHex_1(beq->bevt_33_ta_ph);
beq->bevl_r->bem_addValue_1(beq->bevl_hcs);
} 
} 
} 
 else  {
break;
} 
} 
beq->bevt_34_ta_ph = beq->bevl_r->bem_toString_0();
return beq->bevt_34_ta_ph;
}
BEC_2_4_6_TextString* BEC_2_6_3_EncodeUrl::bem_decode_1(BEC_2_4_6_TextString* bevk_str) {
struct bes { BEC_2_4_6_TextString* beva_str; BEC_2_4_6_TextString* bevl_r; BEC_2_4_3_MathInt* bevl_last; BEC_2_4_3_MathInt* bevl_npl; BEC_2_4_3_MathInt* bevl_npe; BEC_2_4_3_MathInt* bevl_i; BEC_2_5_4_LogicBool* bevl_ispl; BEC_2_4_3_MathInt* bevl_len; BEC_2_5_4_LogicBool* bevt_0_ta_anchor; BEC_2_5_4_LogicBool* bevt_1_ta_anchor; BEC_2_4_3_MathInt* bevt_2_ta_ph; BEC_2_4_6_TextString* bevt_3_ta_ph; BEC_2_4_6_TextString* bevt_4_ta_ph; BEC_2_5_4_LogicBool* bevt_5_ta_ph; BEC_2_5_4_LogicBool* bevt_6_ta_ph; BEC_2_5_4_LogicBool* bevt_7_ta_ph; BEC_2_5_4_LogicBool* bevt_8_ta_ph; BEC_2_5_4_LogicBool* bevt_9_ta_ph; BEC_2_4_6_TextString* bevt_10_ta_ph; BEC_2_4_6_TextString* bevt_11_ta_ph; BEC_2_4_3_MathInt* bevt_12_ta_ph; BEC_2_5_4_LogicBool* bevt_13_ta_ph; BEC_2_4_3_MathInt* bevt_14_ta_ph; BEC_2_4_3_MathInt* bevt_15_ta_ph; BEC_2_4_6_TextString* bevt_16_ta_ph; BEC_2_4_6_TextString* bevt_17_ta_ph; BEC_2_4_3_MathInt* bevt_18_ta_ph; BEC_2_4_3_MathInt* bevt_19_ta_ph; BEC_2_4_3_MathInt* bevt_20_ta_ph; BEC_2_4_3_MathInt* bevt_21_ta_ph; BEC_2_4_3_MathInt* bevt_22_ta_ph; BEC_2_4_6_TextString* bevt_23_ta_ph; BEC_2_4_6_TextString* bevt_24_ta_ph; BEC_2_5_4_LogicBool* bevt_25_ta_ph; BEC_2_5_4_LogicBool* bevt_26_ta_ph; BEC_2_5_4_LogicBool* bevt_27_ta_ph; BEC_2_5_4_LogicBool* bevt_28_ta_ph; BEC_2_4_6_TextString* bevt_29_ta_ph; BEC_2_4_6_TextString* bevt_30_ta_ph; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->beva_str = bevk_str;
beq->bevl_r = nullptr;
beq->bevl_last = nullptr;
beq->bevl_npl = nullptr;
beq->bevl_npe = nullptr;
beq->bevl_i = nullptr;
beq->bevl_ispl = nullptr;
beq->bevl_len = nullptr;
beq->bevt_0_ta_anchor = nullptr;
beq->bevt_1_ta_anchor = nullptr;
beq->bevt_2_ta_ph = nullptr;
beq->bevt_3_ta_ph = nullptr;
beq->bevt_4_ta_ph = nullptr;
beq->bevt_5_ta_ph = nullptr;
beq->bevt_6_ta_ph = nullptr;
beq->bevt_7_ta_ph = nullptr;
beq->bevt_8_ta_ph = nullptr;
beq->bevt_9_ta_ph = nullptr;
beq->bevt_10_ta_ph = nullptr;
beq->bevt_11_ta_ph = nullptr;
beq->bevt_12_ta_ph = nullptr;
beq->bevt_13_ta_ph = nullptr;
beq->bevt_14_ta_ph = nullptr;
beq->bevt_15_ta_ph = nullptr;
beq->bevt_16_ta_ph = nullptr;
beq->bevt_17_ta_ph = nullptr;
beq->bevt_18_ta_ph = nullptr;
beq->bevt_19_ta_ph = nullptr;
beq->bevt_20_ta_ph = nullptr;
beq->bevt_21_ta_ph = nullptr;
beq->bevt_22_ta_ph = nullptr;
beq->bevt_23_ta_ph = nullptr;
beq->bevt_24_ta_ph = nullptr;
beq->bevt_25_ta_ph = nullptr;
beq->bevt_26_ta_ph = nullptr;
beq->bevt_27_ta_ph = nullptr;
beq->bevt_28_ta_ph = nullptr;
beq->bevt_29_ta_ph = nullptr;
beq->bevt_30_ta_ph = nullptr;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(40);
beq->bevt_2_ta_ph = beq->beva_str->bem_sizeGet_0();
beq->bevl_r = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString()))->bem_new_1(beq->bevt_2_ta_ph));
beq->bevl_last = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(0))));
beq->bevt_3_ta_ph = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString(1, {0x2B}))));
beq->bevl_npl = beq->beva_str->bem_find_2(beq->bevt_3_ta_ph, beq->bevl_last);
beq->bevt_4_ta_ph = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString(1, {0x25}))));
beq->bevl_npe = beq->beva_str->bem_find_2(beq->bevt_4_ta_ph, beq->bevl_last);
if (beq->bevl_npe == nullptr) {
beq->bevt_5_ta_ph = BECS_Runtime::boolTrue;
 } else { 
beq->bevt_5_ta_ph = BECS_Runtime::boolFalse;
}
if (beq->bevt_5_ta_ph->bevi_bool) {
beq->bevt_0_ta_anchor = BECS_Runtime::boolTrue;
} 
 else  {
if (beq->bevl_npl == nullptr) {
beq->bevt_6_ta_ph = BECS_Runtime::boolFalse;
 } else { 
beq->bevt_6_ta_ph = BECS_Runtime::boolTrue;
}
if (beq->bevt_6_ta_ph->bevi_bool) {
if (beq->bevl_npl->bevi_int < beq->bevl_npe->bevi_int) {
beq->bevt_7_ta_ph = BECS_Runtime::boolTrue;
 } else { 
beq->bevt_7_ta_ph = BECS_Runtime::boolFalse;
}
if (beq->bevt_7_ta_ph->bevi_bool) {
beq->bevt_0_ta_anchor = BECS_Runtime::boolTrue;
} 
 else  {
beq->bevt_0_ta_anchor = BECS_Runtime::boolFalse;
} 
} 
 else  {
beq->bevt_0_ta_anchor = BECS_Runtime::boolFalse;
} 
if (beq->bevt_0_ta_anchor->bevi_bool) {
beq->bevt_0_ta_anchor = BECS_Runtime::boolTrue;
} 
 else  {
beq->bevt_0_ta_anchor = BECS_Runtime::boolFalse;
} 
} 
if (beq->bevt_0_ta_anchor->bevi_bool) {
beq->bevl_ispl = static_cast<BEC_2_5_4_LogicBool*>(BECS_Runtime::boolTrue);
beq->bevl_i = beq->bevl_npl;
} 
 else  {
beq->bevl_ispl = static_cast<BEC_2_5_4_LogicBool*>(BECS_Runtime::boolFalse);
beq->bevl_i = beq->bevl_npe;
} 
beq->bevl_len = beq->beva_str->bem_sizeGet_0();
while (true)
 {
if (beq->bevl_i == nullptr) {
beq->bevt_8_ta_ph = BECS_Runtime::boolFalse;
 } else { 
beq->bevt_8_ta_ph = BECS_Runtime::boolTrue;
}
if (beq->bevt_8_ta_ph->bevi_bool) {
if (beq->bevl_i->bevi_int > beq->bevl_last->bevi_int) {
beq->bevt_9_ta_ph = BECS_Runtime::boolTrue;
 } else { 
beq->bevt_9_ta_ph = BECS_Runtime::boolFalse;
}
if (beq->bevt_9_ta_ph->bevi_bool) {
beq->bevt_10_ta_ph = beq->beva_str->bem_substring_2(beq->bevl_last, beq->bevl_i);
beq->bevl_r->bem_addValue_1(beq->bevt_10_ta_ph);
beq->bevl_last = beq->bevl_i;
} 
if (beq->bevl_ispl->bevi_bool) {
beq->bevt_11_ta_ph = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString(1, {0x20}))));
beq->bevl_r->bem_addValue_1(beq->bevt_11_ta_ph);
beq->bevt_12_ta_ph = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(1))));
beq->bevl_last = beq->bevl_i->bem_add_1(beq->bevt_12_ta_ph);
} 
 else  {
beq->bevt_15_ta_ph = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(2))));
beq->bevt_14_ta_ph = beq->bevl_i->bem_add_1(beq->bevt_15_ta_ph);
if (beq->bevt_14_ta_ph->bevi_int < beq->bevl_len->bevi_int) {
beq->bevt_13_ta_ph = BECS_Runtime::boolTrue;
 } else { 
beq->bevt_13_ta_ph = BECS_Runtime::boolFalse;
}
if (beq->bevt_13_ta_ph->bevi_bool) {
beq->bevt_19_ta_ph = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(1))));
beq->bevt_18_ta_ph = beq->bevl_i->bem_add_1(beq->bevt_19_ta_ph);
beq->bevt_21_ta_ph = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(3))));
beq->bevt_20_ta_ph = beq->bevl_i->bem_add_1(beq->bevt_21_ta_ph);
beq->bevt_17_ta_ph = beq->beva_str->bem_substring_2(beq->bevt_18_ta_ph, beq->bevt_20_ta_ph);
beq->bevt_16_ta_ph = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString()))->bem_hexNew_1(beq->bevt_17_ta_ph));
beq->bevl_r->bem_addValue_1(beq->bevt_16_ta_ph);
beq->bevt_22_ta_ph = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(3))));
beq->bevl_last = beq->bevl_i->bem_add_1(beq->bevt_22_ta_ph);
} 
} 
beq->bevt_23_ta_ph = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString(1, {0x2B}))));
beq->bevl_npl = beq->beva_str->bem_find_2(beq->bevt_23_ta_ph, beq->bevl_last);
beq->bevt_24_ta_ph = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString(1, {0x25}))));
beq->bevl_npe = beq->beva_str->bem_find_2(beq->bevt_24_ta_ph, beq->bevl_last);
if (beq->bevl_npe == nullptr) {
beq->bevt_25_ta_ph = BECS_Runtime::boolTrue;
 } else { 
beq->bevt_25_ta_ph = BECS_Runtime::boolFalse;
}
if (beq->bevt_25_ta_ph->bevi_bool) {
beq->bevt_1_ta_anchor = BECS_Runtime::boolTrue;
} 
 else  {
if (beq->bevl_npl == nullptr) {
beq->bevt_26_ta_ph = BECS_Runtime::boolFalse;
 } else { 
beq->bevt_26_ta_ph = BECS_Runtime::boolTrue;
}
if (beq->bevt_26_ta_ph->bevi_bool) {
if (beq->bevl_npl->bevi_int < beq->bevl_npe->bevi_int) {
beq->bevt_27_ta_ph = BECS_Runtime::boolTrue;
 } else { 
beq->bevt_27_ta_ph = BECS_Runtime::boolFalse;
}
if (beq->bevt_27_ta_ph->bevi_bool) {
beq->bevt_1_ta_anchor = BECS_Runtime::boolTrue;
} 
 else  {
beq->bevt_1_ta_anchor = BECS_Runtime::boolFalse;
} 
} 
 else  {
beq->bevt_1_ta_anchor = BECS_Runtime::boolFalse;
} 
if (beq->bevt_1_ta_anchor->bevi_bool) {
beq->bevt_1_ta_anchor = BECS_Runtime::boolTrue;
} 
 else  {
beq->bevt_1_ta_anchor = BECS_Runtime::boolFalse;
} 
} 
if (beq->bevt_1_ta_anchor->bevi_bool) {
beq->bevl_ispl = static_cast<BEC_2_5_4_LogicBool*>(BECS_Runtime::boolTrue);
beq->bevl_i = beq->bevl_npl;
} 
 else  {
beq->bevl_ispl = static_cast<BEC_2_5_4_LogicBool*>(BECS_Runtime::boolFalse);
beq->bevl_i = beq->bevl_npe;
} 
} 
 else  {
break;
} 
} 
if (beq->bevl_last->bevi_int < beq->bevl_len->bevi_int) {
beq->bevt_28_ta_ph = BECS_Runtime::boolTrue;
 } else { 
beq->bevt_28_ta_ph = BECS_Runtime::boolFalse;
}
if (beq->bevt_28_ta_ph->bevi_bool) {
beq->bevt_29_ta_ph = beq->beva_str->bem_substring_2(beq->bevl_last, beq->bevl_len);
beq->bevl_r->bem_addValue_1(beq->bevt_29_ta_ph);
} 
beq->bevt_30_ta_ph = beq->bevl_r->bem_toString_0();
return beq->bevt_30_ta_ph;
}
BEC_2_6_6_SystemObject* BEC_2_6_3_EncodeUrl::bemd_0(int32_t callId) {
switch (callId) {
case 1312387167: return bem_create_0();
case 1188815194: return bem_default_0();
}
return bevs_super::bemd_0(callId);
}
BEC_2_6_6_SystemObject* BEC_2_6_3_EncodeUrl::bemd_1(int32_t callId, BEC_2_6_6_SystemObject* bevd_0) {
switch (callId) {
case -1557312399: return bem_encode_1(static_cast<BEC_2_4_6_TextString*>(bevd_0));
case 1305979012: return bem_decode_1(static_cast<BEC_2_4_6_TextString*>(bevd_0));
}
return bevs_super::bemd_1(callId, bevd_0);
}
BEC_2_6_6_SystemObject* BEC_2_6_3_EncodeUrl::bemc_create() {
return new BEC_2_6_3_EncodeUrl();
}
void BEC_2_6_3_EncodeUrl::bemc_setInitial(BEC_2_6_6_SystemObject* becc_inst) {
BEC_2_6_3_EncodeUrl::bece_BEC_2_6_3_EncodeUrl_bevs_inst = static_cast<BEC_2_6_3_EncodeUrl*>(becc_inst);
}
BEC_2_6_6_SystemObject* BEC_2_6_3_EncodeUrl::bemc_getInitial() {
return BEC_2_6_3_EncodeUrl::bece_BEC_2_6_3_EncodeUrl_bevs_inst;
}
void BEC_2_6_3_EncodeUrl::bemg_doMark() {
bevg_gcMark = BECS_Runtime::bevg_currentGcMark;
}
size_t BEC_2_6_3_EncodeUrl::bemg_getSize() {
return sizeof(*this);
}
BETS_Object* BEC_2_6_3_EncodeUrl::bemc_getType() {
return &BEC_2_6_3_EncodeUrl::bece_BEC_2_6_3_EncodeUrl_bevs_type;
}
BET_3_9_4_8_ContainerListIterator::BET_3_9_4_8_ContainerListIterator() {
std::vector<std::string> bevs_mtnames = {  };
bevs_fieldNames = {  };
}
BEC_2_6_6_SystemObject* BET_3_9_4_8_ContainerListIterator::bems_createInstance() {
return new BEC_3_9_4_8_ContainerListIterator();
}
void BET_3_9_4_8_ContainerListIterator::bemgt_doMark() {
BEC_2_6_6_SystemObject* bevsl_inst_ref = *bevs_inst_ref;
if (bevsl_inst_ref != nullptr && bevsl_inst_ref->bevg_gcMark != BECS_Runtime::bevg_currentGcMark) {
bevsl_inst_ref->bemg_doMark();
}
}
BEC_3_9_4_8_ContainerListIterator* BEC_3_9_4_8_ContainerListIterator::bece_BEC_3_9_4_8_ContainerListIterator_bevs_inst;

BET_3_9_4_8_ContainerListIterator BEC_3_9_4_8_ContainerListIterator::bece_BEC_3_9_4_8_ContainerListIterator_bevs_type;
BEC_2_6_6_SystemObject** BET_3_9_4_8_ContainerListIterator::bevs_inst_ref = (BEC_2_6_6_SystemObject**) &BEC_3_9_4_8_ContainerListIterator::bece_BEC_3_9_4_8_ContainerListIterator_bevs_inst;

BEC_2_6_6_SystemObject* BEC_3_9_4_8_ContainerListIterator::bem_new_0() {
struct bes { BEC_2_4_3_MathInt* bevt_0_ta_ph; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->bevt_0_ta_ph = nullptr;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(2);
bevp_pos = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(-1))));
beq->bevt_0_ta_ph = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(1))));
bevp_list = static_cast<BEC_2_9_4_ContainerList*>(((BEC_2_9_4_ContainerList*) (new BEC_2_9_4_ContainerList()))->bem_new_1(beq->bevt_0_ta_ph));
bevp_npos = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt())));
bevp_none = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(-1))));
bevp_zero = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(0))));
return this;
}
BEC_3_9_4_8_ContainerListIterator* BEC_3_9_4_8_ContainerListIterator::bem_new_1(BEC_2_6_6_SystemObject* bevk_a) {
struct bes { BEC_2_6_6_SystemObject* beva_a; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->beva_a = bevk_a;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(2);
bevp_pos = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(-1))));
bevp_list = static_cast<BEC_2_9_4_ContainerList*>(beq->beva_a);
bevp_npos = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt())));
bevp_none = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(-1))));
bevp_zero = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(0))));
return this;
}
BEC_2_9_4_ContainerList* BEC_3_9_4_8_ContainerListIterator::bem_containerGet_0() {
struct bes {  BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(1);
return bevp_list;
}
BEC_2_5_4_LogicBool* BEC_3_9_4_8_ContainerListIterator::bem_hasCurrentGet_0() {
struct bes { BEC_2_5_4_LogicBool* bevt_0_ta_anchor; BEC_2_5_4_LogicBool* bevt_1_ta_ph; BEC_2_5_4_LogicBool* bevt_2_ta_ph; BEC_2_4_3_MathInt* bevt_3_ta_ph; BEC_2_5_4_LogicBool* bevt_4_ta_ph; BEC_2_5_4_LogicBool* bevt_5_ta_ph; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->bevt_0_ta_anchor = nullptr;
beq->bevt_1_ta_ph = nullptr;
beq->bevt_2_ta_ph = nullptr;
beq->bevt_3_ta_ph = nullptr;
beq->bevt_4_ta_ph = nullptr;
beq->bevt_5_ta_ph = nullptr;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(7);
if (bevp_pos->bevi_int > bevp_zero->bevi_int) {
beq->bevt_1_ta_ph = BECS_Runtime::boolTrue;
 } else { 
beq->bevt_1_ta_ph = BECS_Runtime::boolFalse;
}
if (beq->bevt_1_ta_ph->bevi_bool) {
beq->bevt_3_ta_ph = bevp_list->bem_lengthGet_0();
if (bevp_pos->bevi_int < beq->bevt_3_ta_ph->bevi_int) {
beq->bevt_2_ta_ph = BECS_Runtime::boolTrue;
 } else { 
beq->bevt_2_ta_ph = BECS_Runtime::boolFalse;
}
if (beq->bevt_2_ta_ph->bevi_bool) {
beq->bevt_0_ta_anchor = BECS_Runtime::boolTrue;
} 
 else  {
beq->bevt_0_ta_anchor = BECS_Runtime::boolFalse;
} 
} 
 else  {
beq->bevt_0_ta_anchor = BECS_Runtime::boolFalse;
} 
if (beq->bevt_0_ta_anchor->bevi_bool) {
beq->bevt_4_ta_ph = static_cast<BEC_2_5_4_LogicBool*>(BECS_Runtime::boolTrue);
return beq->bevt_4_ta_ph;
} 
beq->bevt_5_ta_ph = static_cast<BEC_2_5_4_LogicBool*>(BECS_Runtime::boolFalse);
return beq->bevt_5_ta_ph;
}
BEC_2_5_4_LogicBool* BEC_3_9_4_8_ContainerListIterator::bem_currentGet_0() {
struct bes { BEC_2_6_6_SystemObject* bevt_0_ta_ph; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->bevt_0_ta_ph = nullptr;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(2);
beq->bevt_0_ta_ph = bevp_list->bem_get_1(bevp_pos);
return static_cast<BEC_2_5_4_LogicBool*>(beq->bevt_0_ta_ph);
}
BEC_2_6_6_SystemObject* BEC_3_9_4_8_ContainerListIterator::bem_currentSet_1(BEC_2_6_6_SystemObject* bevk_toSet) {
struct bes { BEC_2_6_6_SystemObject* beva_toSet; BEC_2_9_4_ContainerList* bevt_0_ta_ph; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->beva_toSet = bevk_toSet;
beq->bevt_0_ta_ph = nullptr;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(3);
beq->bevt_0_ta_ph = static_cast<BEC_2_9_4_ContainerList*>(bevp_list->bem_put_2(bevp_pos, beq->beva_toSet));
return beq->bevt_0_ta_ph;
}
BEC_2_5_4_LogicBool* BEC_3_9_4_8_ContainerListIterator::bem_hasNextGet_0() {
struct bes { BEC_2_5_4_LogicBool* bevt_0_ta_anchor; BEC_2_5_4_LogicBool* bevt_1_ta_ph; BEC_2_5_4_LogicBool* bevt_2_ta_ph; BEC_2_4_3_MathInt* bevt_3_ta_ph; BEC_2_5_4_LogicBool* bevt_4_ta_ph; BEC_2_5_4_LogicBool* bevt_5_ta_ph; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->bevt_0_ta_anchor = nullptr;
beq->bevt_1_ta_ph = nullptr;
beq->bevt_2_ta_ph = nullptr;
beq->bevt_3_ta_ph = nullptr;
beq->bevt_4_ta_ph = nullptr;
beq->bevt_5_ta_ph = nullptr;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(7);
bevp_npos->bevi_int = bevp_pos->bevi_int;
bevp_npos->bevi_int++;
if (bevp_pos->bevi_int >= bevp_none->bevi_int) {
beq->bevt_1_ta_ph = BECS_Runtime::boolTrue;
 } else { 
beq->bevt_1_ta_ph = BECS_Runtime::boolFalse;
}
if (beq->bevt_1_ta_ph->bevi_bool) {
beq->bevt_3_ta_ph = bevp_list->bem_lengthGet_0();
if (bevp_npos->bevi_int < beq->bevt_3_ta_ph->bevi_int) {
beq->bevt_2_ta_ph = BECS_Runtime::boolTrue;
 } else { 
beq->bevt_2_ta_ph = BECS_Runtime::boolFalse;
}
if (beq->bevt_2_ta_ph->bevi_bool) {
beq->bevt_0_ta_anchor = BECS_Runtime::boolTrue;
} 
 else  {
beq->bevt_0_ta_anchor = BECS_Runtime::boolFalse;
} 
} 
 else  {
beq->bevt_0_ta_anchor = BECS_Runtime::boolFalse;
} 
if (beq->bevt_0_ta_anchor->bevi_bool) {
beq->bevt_4_ta_ph = static_cast<BEC_2_5_4_LogicBool*>(BECS_Runtime::boolTrue);
return beq->bevt_4_ta_ph;
} 
beq->bevt_5_ta_ph = static_cast<BEC_2_5_4_LogicBool*>(BECS_Runtime::boolFalse);
return beq->bevt_5_ta_ph;
}
BEC_2_6_6_SystemObject* BEC_3_9_4_8_ContainerListIterator::bem_nextGet_0() {
struct bes { BEC_2_6_6_SystemObject* bevt_0_ta_ph; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->bevt_0_ta_ph = nullptr;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(2);
bevp_pos->bevi_int++;
beq->bevt_0_ta_ph = bevp_list->bem_get_1(bevp_pos);
return beq->bevt_0_ta_ph;
}
BEC_2_6_6_SystemObject* BEC_3_9_4_8_ContainerListIterator::bem_nextSet_1(BEC_2_6_6_SystemObject* bevk_toSet) {
struct bes { BEC_2_6_6_SystemObject* beva_toSet; BEC_2_9_4_ContainerList* bevt_0_ta_ph; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->beva_toSet = bevk_toSet;
beq->bevt_0_ta_ph = nullptr;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(3);
bevp_pos->bevi_int++;
beq->bevt_0_ta_ph = static_cast<BEC_2_9_4_ContainerList*>(bevp_list->bem_put_2(bevp_pos, beq->beva_toSet));
return beq->bevt_0_ta_ph;
}
BEC_3_9_4_8_ContainerListIterator* BEC_3_9_4_8_ContainerListIterator::bem_skip_1(BEC_2_4_3_MathInt* bevk_multiNullCount) {
struct bes { BEC_2_4_3_MathInt* beva_multiNullCount; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->beva_multiNullCount = bevk_multiNullCount;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(2);
bevp_pos->bevi_int += beq->beva_multiNullCount->bevi_int;
return this;
}
BEC_2_6_6_SystemObject* BEC_3_9_4_8_ContainerListIterator::bemd_0(int32_t callId) {
switch (callId) {
case 814057402: return bem_containerGet_0();
case -1785532669: return bem_new_0();
case -119099042: return bem_nextGet_0();
case 448214784: return bem_hasNextGet_0();
case -1881779334: return bem_hasCurrentGet_0();
case 1242825350: return bem_currentGet_0();
}
return bevs_super::bemd_0(callId);
}
BEC_2_6_6_SystemObject* BEC_3_9_4_8_ContainerListIterator::bemd_1(int32_t callId, BEC_2_6_6_SystemObject* bevd_0) {
switch (callId) {
case 1626002742: return bem_skip_1(static_cast<BEC_2_4_3_MathInt*>(bevd_0));
case -1206415723: return bem_nextSet_1(bevd_0);
case -191629072: return bem_currentSet_1(bevd_0);
case 1899676304: return bem_new_1(bevd_0);
}
return bevs_super::bemd_1(callId, bevd_0);
}
BEC_2_6_6_SystemObject* BEC_3_9_4_8_ContainerListIterator::bemc_create() {
return new BEC_3_9_4_8_ContainerListIterator();
}
void BEC_3_9_4_8_ContainerListIterator::bemc_setInitial(BEC_2_6_6_SystemObject* becc_inst) {
BEC_3_9_4_8_ContainerListIterator::bece_BEC_3_9_4_8_ContainerListIterator_bevs_inst = static_cast<BEC_3_9_4_8_ContainerListIterator*>(becc_inst);
}
BEC_2_6_6_SystemObject* BEC_3_9_4_8_ContainerListIterator::bemc_getInitial() {
return BEC_3_9_4_8_ContainerListIterator::bece_BEC_3_9_4_8_ContainerListIterator_bevs_inst;
}
void BEC_3_9_4_8_ContainerListIterator::bemg_doMark() {
bevg_gcMark = BECS_Runtime::bevg_currentGcMark;
if (bevp_pos != nullptr && bevp_pos->bevg_gcMark != BECS_Runtime::bevg_currentGcMark) {
bevp_pos->bemg_doMark();
}
if (bevp_list != nullptr && bevp_list->bevg_gcMark != BECS_Runtime::bevg_currentGcMark) {
bevp_list->bemg_doMark();
}
if (bevp_npos != nullptr && bevp_npos->bevg_gcMark != BECS_Runtime::bevg_currentGcMark) {
bevp_npos->bemg_doMark();
}
if (bevp_none != nullptr && bevp_none->bevg_gcMark != BECS_Runtime::bevg_currentGcMark) {
bevp_none->bemg_doMark();
}
if (bevp_zero != nullptr && bevp_zero->bevg_gcMark != BECS_Runtime::bevg_currentGcMark) {
bevp_zero->bemg_doMark();
}
}
size_t BEC_3_9_4_8_ContainerListIterator::bemg_getSize() {
return sizeof(*this);
}
BETS_Object* BEC_3_9_4_8_ContainerListIterator::bemc_getType() {
return &BEC_3_9_4_8_ContainerListIterator::bece_BEC_3_9_4_8_ContainerListIterator_bevs_type;
}
BET_2_9_4_ContainerList::BET_2_9_4_ContainerList() {
std::vector<std::string> bevs_mtnames = {  };
bevs_fieldNames = {  };
}
BEC_2_6_6_SystemObject* BET_2_9_4_ContainerList::bems_createInstance() {
return new BEC_2_9_4_ContainerList();
}
void BET_2_9_4_ContainerList::bemgt_doMark() {
BEC_2_6_6_SystemObject* bevsl_inst_ref = *bevs_inst_ref;
if (bevsl_inst_ref != nullptr && bevsl_inst_ref->bevg_gcMark != BECS_Runtime::bevg_currentGcMark) {
bevsl_inst_ref->bemg_doMark();
}
}
BEC_2_9_4_ContainerList* BEC_2_9_4_ContainerList::bece_BEC_2_9_4_ContainerList_bevs_inst;

BET_2_9_4_ContainerList BEC_2_9_4_ContainerList::bece_BEC_2_9_4_ContainerList_bevs_type;
BEC_2_6_6_SystemObject** BET_2_9_4_ContainerList::bevs_inst_ref = (BEC_2_6_6_SystemObject**) &BEC_2_9_4_ContainerList::bece_BEC_2_9_4_ContainerList_bevs_inst;

BEC_2_6_6_SystemObject* BEC_2_9_4_ContainerList::bem_new_0() {
struct bes { BEC_2_4_3_MathInt* bevt_0_ta_ph; BEC_2_4_3_MathInt* bevt_1_ta_ph; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->bevt_0_ta_ph = nullptr;
beq->bevt_1_ta_ph = nullptr;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(3);
beq->bevt_0_ta_ph = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(0))));
beq->bevt_1_ta_ph = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(16))));
bem_new_2(beq->bevt_0_ta_ph, beq->bevt_1_ta_ph);
return this;
}
BEC_2_9_4_ContainerList* BEC_2_9_4_ContainerList::bem_new_1(BEC_2_4_3_MathInt* bevk_leni) {
struct bes { BEC_2_4_3_MathInt* beva_leni; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->beva_leni = bevk_leni;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(2);
bem_new_2(beq->beva_leni, beq->beva_leni);
return this;
}
BEC_2_9_4_ContainerList* BEC_2_9_4_ContainerList::bem_new_2(BEC_2_4_3_MathInt* bevk_leni, BEC_2_4_3_MathInt* bevk_capi) {
struct bes { BEC_2_4_3_MathInt* beva_leni; BEC_2_4_3_MathInt* beva_capi; BEC_2_5_4_LogicBool* bevt_0_ta_anchor; BEC_2_5_4_LogicBool* bevt_1_ta_ph; BEC_2_5_4_LogicBool* bevt_2_ta_ph; BEC_2_6_9_SystemException* bevt_3_ta_ph; BEC_2_4_6_TextString* bevt_4_ta_ph; BEC_2_5_4_LogicBool* bevt_5_ta_ph; BEC_2_5_4_LogicBool* bevt_6_ta_ph; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->beva_leni = bevk_leni;
beq->beva_capi = bevk_capi;
beq->bevt_0_ta_anchor = nullptr;
beq->bevt_1_ta_ph = nullptr;
beq->bevt_2_ta_ph = nullptr;
beq->bevt_3_ta_ph = nullptr;
beq->bevt_4_ta_ph = nullptr;
beq->bevt_5_ta_ph = nullptr;
beq->bevt_6_ta_ph = nullptr;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(10);
if (beq->beva_leni == nullptr) {
beq->bevt_1_ta_ph = BECS_Runtime::boolTrue;
 } else { 
beq->bevt_1_ta_ph = BECS_Runtime::boolFalse;
}
if (beq->bevt_1_ta_ph->bevi_bool) {
beq->bevt_0_ta_anchor = BECS_Runtime::boolTrue;
} 
 else  {
if (beq->beva_capi == nullptr) {
beq->bevt_2_ta_ph = BECS_Runtime::boolTrue;
 } else { 
beq->bevt_2_ta_ph = BECS_Runtime::boolFalse;
}
if (beq->bevt_2_ta_ph->bevi_bool) {
beq->bevt_0_ta_anchor = BECS_Runtime::boolTrue;
} 
 else  {
beq->bevt_0_ta_anchor = BECS_Runtime::boolFalse;
} 
} 
if (beq->bevt_0_ta_anchor->bevi_bool) {
beq->bevt_4_ta_ph = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString(61, {0x41,0x74,0x74,0x65,0x6D,0x70,0x74,0x20,0x74,0x6F,0x20,0x69,0x6E,0x69,0x74,0x69,0x61,0x6C,0x69,0x7A,0x65,0x20,0x61,0x6E,0x20,0x61,0x72,0x72,0x61,0x79,0x20,0x77,0x69,0x74,0x68,0x20,0x61,0x20,0x6E,0x75,0x6C,0x6C,0x20,0x6C,0x65,0x6E,0x67,0x74,0x68,0x20,0x6F,0x72,0x20,0x63,0x61,0x70,0x61,0x63,0x69,0x74,0x79}))));
beq->bevt_3_ta_ph = static_cast<BEC_2_6_9_SystemException*>(((BEC_2_6_9_SystemException*) (new BEC_2_6_9_SystemException()))->bem_new_1(beq->bevt_4_ta_ph));
throw BECS_ThrowBack(beq->bevt_3_ta_ph);
} 
if (bevp_length == nullptr) {
beq->bevt_5_ta_ph = BECS_Runtime::boolFalse;
 } else { 
beq->bevt_5_ta_ph = BECS_Runtime::boolTrue;
}
if (beq->bevt_5_ta_ph->bevi_bool) {
if (bevp_length->bevi_int == beq->beva_leni->bevi_int) {
beq->bevt_6_ta_ph = BECS_Runtime::boolTrue;
 } else { 
beq->bevt_6_ta_ph = BECS_Runtime::boolFalse;
}
if (beq->bevt_6_ta_ph->bevi_bool) {
return this;
} 
} 

      if (bevi_list.size() > 0) {
        bevi_list.resize(0); //the others clear in this case, this preps for that
      }
      bevi_list.resize(beq->beva_capi->bevi_int);
      bevp_length = static_cast<BEC_2_4_3_MathInt*>(beq->beva_leni->bem_copy_0());
bevp_capacity = static_cast<BEC_2_4_3_MathInt*>(beq->beva_capi->bem_copy_0());
bevp_multiplier = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(2))));
return this;
}
BEC_2_4_3_MathInt* BEC_2_9_4_ContainerList::bem_sizeGet_0() {
struct bes {  BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(1);
return bevp_length;
}
BEC_2_9_4_ContainerList* BEC_2_9_4_ContainerList::bem_sizeSet_1(BEC_2_4_3_MathInt* bevk_val) {
struct bes { BEC_2_4_3_MathInt* beva_val; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->beva_val = bevk_val;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(2);
bem_lengthSet_1(beq->beva_val);
return this;
}
BEC_2_5_4_LogicBool* BEC_2_9_4_ContainerList::bem_isEmptyGet_0() {
struct bes { BEC_2_5_4_LogicBool* bevt_0_ta_ph; BEC_2_4_3_MathInt* bevt_1_ta_ph; BEC_2_5_4_LogicBool* bevt_2_ta_ph; BEC_2_5_4_LogicBool* bevt_3_ta_ph; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->bevt_0_ta_ph = nullptr;
beq->bevt_1_ta_ph = nullptr;
beq->bevt_2_ta_ph = nullptr;
beq->bevt_3_ta_ph = nullptr;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(5);
beq->bevt_1_ta_ph = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(0))));
if (bevp_length->bevi_int == beq->bevt_1_ta_ph->bevi_int) {
beq->bevt_0_ta_ph = BECS_Runtime::boolTrue;
 } else { 
beq->bevt_0_ta_ph = BECS_Runtime::boolFalse;
}
if (beq->bevt_0_ta_ph->bevi_bool) {
beq->bevt_2_ta_ph = static_cast<BEC_2_5_4_LogicBool*>(BECS_Runtime::boolTrue);
return beq->bevt_2_ta_ph;
} 
beq->bevt_3_ta_ph = static_cast<BEC_2_5_4_LogicBool*>(BECS_Runtime::boolFalse);
return beq->bevt_3_ta_ph;
}
BEC_2_9_4_ContainerList* BEC_2_9_4_ContainerList::bem_anyrayGet_0() {
struct bes {  BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(1);
return this;
}
BEC_2_9_4_ContainerList* BEC_2_9_4_ContainerList::bem_anyraySet_0() {
struct bes {  BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(1);
return this;
}
BEC_2_4_6_TextString* BEC_2_9_4_ContainerList::bem_serializeToString_0() {
struct bes { BEC_2_4_6_TextString* bevt_0_ta_ph; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->bevt_0_ta_ph = nullptr;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(2);
beq->bevt_0_ta_ph = bevp_length->bem_toString_0();
return beq->bevt_0_ta_ph;
}
BEC_2_9_4_ContainerList* BEC_2_9_4_ContainerList::bem_deserializeFromStringNew_1(BEC_2_4_6_TextString* bevk_snw) {
struct bes { BEC_2_4_6_TextString* beva_snw; BEC_2_4_3_MathInt* bevt_0_ta_ph; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->beva_snw = bevk_snw;
beq->bevt_0_ta_ph = nullptr;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(3);
beq->bevt_0_ta_ph = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt()))->bem_new_1(beq->beva_snw));
bem_new_1(beq->bevt_0_ta_ph);
return this;
}
BEC_2_6_6_SystemObject* BEC_2_9_4_ContainerList::bem_firstGet_0() {
struct bes { BEC_2_6_6_SystemObject* bevt_0_ta_ph; BEC_2_4_3_MathInt* bevt_1_ta_ph; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->bevt_0_ta_ph = nullptr;
beq->bevt_1_ta_ph = nullptr;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(3);
beq->bevt_1_ta_ph = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(0))));
beq->bevt_0_ta_ph = bem_get_1(beq->bevt_1_ta_ph);
return beq->bevt_0_ta_ph;
}
BEC_2_6_6_SystemObject* BEC_2_9_4_ContainerList::bem_lastGet_0() {
struct bes { BEC_2_6_6_SystemObject* bevt_0_ta_ph; BEC_2_4_3_MathInt* bevt_1_ta_ph; BEC_2_4_3_MathInt* bevt_2_ta_ph; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->bevt_0_ta_ph = nullptr;
beq->bevt_1_ta_ph = nullptr;
beq->bevt_2_ta_ph = nullptr;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(4);
beq->bevt_2_ta_ph = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(1))));
beq->bevt_1_ta_ph = bevp_length->bem_subtract_1(beq->bevt_2_ta_ph);
beq->bevt_0_ta_ph = bem_get_1(beq->bevt_1_ta_ph);
return beq->bevt_0_ta_ph;
}
BEC_2_9_4_ContainerList* BEC_2_9_4_ContainerList::bem_put_2(BEC_2_4_3_MathInt* bevk_posi, BEC_2_6_6_SystemObject* bevk_val) {
struct bes { BEC_2_4_3_MathInt* beva_posi; BEC_2_6_6_SystemObject* beva_val; BEC_2_5_4_LogicBool* bevt_0_ta_ph; BEC_2_4_3_MathInt* bevt_1_ta_ph; BEC_2_6_9_SystemException* bevt_2_ta_ph; BEC_2_4_6_TextString* bevt_3_ta_ph; BEC_2_5_4_LogicBool* bevt_4_ta_ph; BEC_2_4_3_MathInt* bevt_5_ta_ph; BEC_2_4_3_MathInt* bevt_6_ta_ph; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->beva_posi = bevk_posi;
beq->beva_val = bevk_val;
beq->bevt_0_ta_ph = nullptr;
beq->bevt_1_ta_ph = nullptr;
beq->bevt_2_ta_ph = nullptr;
beq->bevt_3_ta_ph = nullptr;
beq->bevt_4_ta_ph = nullptr;
beq->bevt_5_ta_ph = nullptr;
beq->bevt_6_ta_ph = nullptr;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(10);
beq->bevt_1_ta_ph = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(0))));
if (beq->beva_posi->bevi_int < beq->bevt_1_ta_ph->bevi_int) {
beq->bevt_0_ta_ph = BECS_Runtime::boolTrue;
 } else { 
beq->bevt_0_ta_ph = BECS_Runtime::boolFalse;
}
if (beq->bevt_0_ta_ph->bevi_bool) {
beq->bevt_3_ta_ph = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString(36, {0x41,0x74,0x74,0x65,0x6D,0x70,0x74,0x65,0x64,0x20,0x70,0x75,0x74,0x20,0x77,0x69,0x74,0x68,0x20,0x69,0x6E,0x64,0x65,0x78,0x20,0x6C,0x65,0x73,0x73,0x20,0x74,0x68,0x61,0x6E,0x20,0x30}))));
beq->bevt_2_ta_ph = static_cast<BEC_2_6_9_SystemException*>(((BEC_2_6_9_SystemException*) (new BEC_2_6_9_SystemException()))->bem_new_1(beq->bevt_3_ta_ph));
throw BECS_ThrowBack(beq->bevt_2_ta_ph);
} 
if (beq->beva_posi->bevi_int >= bevp_length->bevi_int) {
beq->bevt_4_ta_ph = BECS_Runtime::boolTrue;
 } else { 
beq->bevt_4_ta_ph = BECS_Runtime::boolFalse;
}
if (beq->bevt_4_ta_ph->bevi_bool) {
beq->bevt_6_ta_ph = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(1))));
beq->bevt_5_ta_ph = beq->beva_posi->bem_add_1(beq->bevt_6_ta_ph);
bem_lengthSet_1(beq->bevt_5_ta_ph);
} 

      bevi_list[beq->beva_posi->bevi_int] = beq->beva_val;
      return this;
}
BEC_2_6_6_SystemObject* BEC_2_9_4_ContainerList::bem_get_1(BEC_2_4_3_MathInt* bevk_posi) {
struct bes { BEC_2_4_3_MathInt* beva_posi; BEC_2_6_6_SystemObject* bevl_val; BEC_2_5_4_LogicBool* bevt_0_ta_anchor; BEC_2_5_4_LogicBool* bevt_1_ta_ph; BEC_2_4_3_MathInt* bevt_2_ta_ph; BEC_2_5_4_LogicBool* bevt_3_ta_ph; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->beva_posi = bevk_posi;
beq->bevl_val = nullptr;
beq->bevt_0_ta_anchor = nullptr;
beq->bevt_1_ta_ph = nullptr;
beq->bevt_2_ta_ph = nullptr;
beq->bevt_3_ta_ph = nullptr;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(7);
beq->bevt_2_ta_ph = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(0))));
if (beq->beva_posi->bevi_int >= beq->bevt_2_ta_ph->bevi_int) {
beq->bevt_1_ta_ph = BECS_Runtime::boolTrue;
 } else { 
beq->bevt_1_ta_ph = BECS_Runtime::boolFalse;
}
if (beq->bevt_1_ta_ph->bevi_bool) {
if (beq->beva_posi->bevi_int < bevp_length->bevi_int) {
beq->bevt_3_ta_ph = BECS_Runtime::boolTrue;
 } else { 
beq->bevt_3_ta_ph = BECS_Runtime::boolFalse;
}
if (beq->bevt_3_ta_ph->bevi_bool) {
beq->bevt_0_ta_anchor = BECS_Runtime::boolTrue;
} 
 else  {
beq->bevt_0_ta_anchor = BECS_Runtime::boolFalse;
} 
} 
 else  {
beq->bevt_0_ta_anchor = BECS_Runtime::boolFalse;
} 
if (beq->bevt_0_ta_anchor->bevi_bool) {

      beq->bevl_val = bevi_list[beq->beva_posi->bevi_int];
      } 
return beq->bevl_val;
}
BEC_2_6_6_SystemObject* BEC_2_9_4_ContainerList::bem_delete_1(BEC_2_4_3_MathInt* bevk_pos) {
struct bes { BEC_2_4_3_MathInt* beva_pos; BEC_2_4_3_MathInt* bevl_fl; BEC_2_4_3_MathInt* bevl_j; BEC_2_4_3_MathInt* bevl_i; BEC_2_5_4_LogicBool* bevt_0_ta_ph; BEC_2_4_3_MathInt* bevt_1_ta_ph; BEC_2_4_3_MathInt* bevt_2_ta_ph; BEC_2_5_4_LogicBool* bevt_3_ta_ph; BEC_2_6_6_SystemObject* bevt_4_ta_ph; BEC_2_4_3_MathInt* bevt_5_ta_ph; BEC_2_4_3_MathInt* bevt_6_ta_ph; BEC_2_5_4_LogicBool* bevt_7_ta_ph; BEC_2_5_4_LogicBool* bevt_8_ta_ph; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->beva_pos = bevk_pos;
beq->bevl_fl = nullptr;
beq->bevl_j = nullptr;
beq->bevl_i = nullptr;
beq->bevt_0_ta_ph = nullptr;
beq->bevt_1_ta_ph = nullptr;
beq->bevt_2_ta_ph = nullptr;
beq->bevt_3_ta_ph = nullptr;
beq->bevt_4_ta_ph = nullptr;
beq->bevt_5_ta_ph = nullptr;
beq->bevt_6_ta_ph = nullptr;
beq->bevt_7_ta_ph = nullptr;
beq->bevt_8_ta_ph = nullptr;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(14);
if (beq->beva_pos->bevi_int < bevp_length->bevi_int) {
beq->bevt_0_ta_ph = BECS_Runtime::boolTrue;
 } else { 
beq->bevt_0_ta_ph = BECS_Runtime::boolFalse;
}
if (beq->bevt_0_ta_ph->bevi_bool) {
beq->bevt_1_ta_ph = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(1))));
beq->bevl_fl = bevp_length->bem_subtract_1(beq->bevt_1_ta_ph);
beq->bevt_2_ta_ph = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(1))));
beq->bevl_j = beq->beva_pos->bem_add_1(beq->bevt_2_ta_ph);
beq->bevl_i = static_cast<BEC_2_4_3_MathInt*>(beq->beva_pos->bem_copy_0());
while (true)
 {
if (beq->bevl_i->bevi_int < beq->bevl_fl->bevi_int) {
beq->bevt_3_ta_ph = BECS_Runtime::boolTrue;
 } else { 
beq->bevt_3_ta_ph = BECS_Runtime::boolFalse;
}
if (beq->bevt_3_ta_ph->bevi_bool) {
beq->bevt_4_ta_ph = bem_get_1(beq->bevl_j);
bem_put_2(beq->bevl_i, beq->bevt_4_ta_ph);
beq->bevl_j->bevi_int++;
beq->bevl_i->bevi_int++;
} 
 else  {
break;
} 
} 
bem_put_2(beq->bevl_fl, nullptr);
beq->bevt_6_ta_ph = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(1))));
beq->bevt_5_ta_ph = bevp_length->bem_subtract_1(beq->bevt_6_ta_ph);
bem_lengthSet_1(beq->bevt_5_ta_ph);
beq->bevt_7_ta_ph = static_cast<BEC_2_5_4_LogicBool*>(BECS_Runtime::boolTrue);
return beq->bevt_7_ta_ph;
} 
beq->bevt_8_ta_ph = static_cast<BEC_2_5_4_LogicBool*>(BECS_Runtime::boolFalse);
return beq->bevt_8_ta_ph;
}
BEC_2_6_6_SystemObject* BEC_2_9_4_ContainerList::bem_iteratorGet_0() {
struct bes { BEC_3_9_4_8_ContainerListIterator* bevt_0_ta_ph; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->bevt_0_ta_ph = nullptr;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(2);
beq->bevt_0_ta_ph = static_cast<BEC_3_9_4_8_ContainerListIterator*>(((BEC_3_9_4_8_ContainerListIterator*) (new BEC_3_9_4_8_ContainerListIterator()))->bem_new_1(this));
return beq->bevt_0_ta_ph;
}
BEC_3_9_4_8_ContainerListIterator* BEC_2_9_4_ContainerList::bem_arrayIteratorGet_0() {
struct bes { BEC_3_9_4_8_ContainerListIterator* bevt_0_ta_ph; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->bevt_0_ta_ph = nullptr;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(2);
beq->bevt_0_ta_ph = static_cast<BEC_3_9_4_8_ContainerListIterator*>(((BEC_3_9_4_8_ContainerListIterator*) (new BEC_3_9_4_8_ContainerListIterator()))->bem_new_1(this));
return beq->bevt_0_ta_ph;
}
BEC_2_9_4_ContainerList* BEC_2_9_4_ContainerList::bem_clear_0() {
struct bes { BEC_2_4_3_MathInt* bevl_i; BEC_2_5_4_LogicBool* bevt_0_ta_ph; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->bevl_i = nullptr;
beq->bevt_0_ta_ph = nullptr;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(3);
beq->bevl_i = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(0))));
while (true)
 {
if (beq->bevl_i->bevi_int < bevp_length->bevi_int) {
beq->bevt_0_ta_ph = BECS_Runtime::boolTrue;
 } else { 
beq->bevt_0_ta_ph = BECS_Runtime::boolFalse;
}
if (beq->bevt_0_ta_ph->bevi_bool) {
bem_put_2(beq->bevl_i, nullptr);
beq->bevl_i->bevi_int++;
} 
 else  {
break;
} 
} 
bevp_length = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(0))));
return this;
}
BEC_2_6_6_SystemObject* BEC_2_9_4_ContainerList::bem_copy_0() {
struct bes { BEC_2_9_4_ContainerList* bevl_n; BEC_2_4_3_MathInt* bevl_i; BEC_2_5_4_LogicBool* bevt_0_ta_ph; BEC_2_6_6_SystemObject* bevt_1_ta_ph; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->bevl_n = nullptr;
beq->bevl_i = nullptr;
beq->bevt_0_ta_ph = nullptr;
beq->bevt_1_ta_ph = nullptr;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(5);
beq->bevl_n = static_cast<BEC_2_9_4_ContainerList*>(bem_create_0());
beq->bevl_i = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(0))));
while (true)
 {
if (beq->bevl_i->bevi_int < bevp_length->bevi_int) {
beq->bevt_0_ta_ph = BECS_Runtime::boolTrue;
 } else { 
beq->bevt_0_ta_ph = BECS_Runtime::boolFalse;
}
if (beq->bevt_0_ta_ph->bevi_bool) {
beq->bevt_1_ta_ph = bem_get_1(beq->bevl_i);
beq->bevl_n->bem_put_2(beq->bevl_i, beq->bevt_1_ta_ph);
beq->bevl_i->bevi_int++;
} 
 else  {
break;
} 
} 
return static_cast<BEC_2_6_6_SystemObject*>(beq->bevl_n);
}
BEC_2_6_6_SystemObject* BEC_2_9_4_ContainerList::bem_create_1(BEC_2_4_3_MathInt* bevk_len) {
struct bes { BEC_2_4_3_MathInt* beva_len; BEC_2_9_4_ContainerList* bevt_0_ta_ph; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->beva_len = bevk_len;
beq->bevt_0_ta_ph = nullptr;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(3);
beq->bevt_0_ta_ph = static_cast<BEC_2_9_4_ContainerList*>(((BEC_2_9_4_ContainerList*) (new BEC_2_9_4_ContainerList()))->bem_new_1(beq->beva_len));
return beq->bevt_0_ta_ph;
}
BEC_2_6_6_SystemObject* BEC_2_9_4_ContainerList::bem_create_0() {
struct bes { BEC_2_9_4_ContainerList* bevt_0_ta_ph; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->bevt_0_ta_ph = nullptr;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(2);
beq->bevt_0_ta_ph = static_cast<BEC_2_9_4_ContainerList*>(((BEC_2_9_4_ContainerList*) (new BEC_2_9_4_ContainerList()))->bem_new_1(bevp_length));
return static_cast<BEC_2_6_6_SystemObject*>(beq->bevt_0_ta_ph);
}
BEC_2_9_4_ContainerList* BEC_2_9_4_ContainerList::bem_add_1(BEC_2_9_4_ContainerList* bevk_xi) {
struct bes { BEC_2_9_4_ContainerList* beva_xi; BEC_2_9_4_ContainerList* bevl_yi; BEC_2_6_6_SystemObject* bevl_c; BEC_2_6_6_SystemObject* bevt_0_ta_loop; BEC_2_6_6_SystemObject* bevt_1_ta_loop; BEC_2_4_3_MathInt* bevt_2_ta_ph; BEC_2_4_3_MathInt* bevt_3_ta_ph; BEC_2_4_3_MathInt* bevt_4_ta_ph; BEC_2_6_6_SystemObject* bevt_5_ta_ph; BEC_2_6_6_SystemObject* bevt_6_ta_ph; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->beva_xi = bevk_xi;
beq->bevl_yi = nullptr;
beq->bevl_c = nullptr;
beq->bevt_0_ta_loop = nullptr;
beq->bevt_1_ta_loop = nullptr;
beq->bevt_2_ta_ph = nullptr;
beq->bevt_3_ta_ph = nullptr;
beq->bevt_4_ta_ph = nullptr;
beq->bevt_5_ta_ph = nullptr;
beq->bevt_6_ta_ph = nullptr;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(11);
beq->bevt_2_ta_ph = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(0))));
beq->bevt_4_ta_ph = beq->beva_xi->bem_lengthGet_0();
beq->bevt_3_ta_ph = bevp_length->bem_add_1(beq->bevt_4_ta_ph);
beq->bevl_yi = static_cast<BEC_2_9_4_ContainerList*>(((BEC_2_9_4_ContainerList*) (new BEC_2_9_4_ContainerList()))->bem_new_2(beq->bevt_2_ta_ph, beq->bevt_3_ta_ph));
beq->bevt_0_ta_loop = bem_iteratorGet_0();
while (true)
 {
beq->bevt_5_ta_ph = beq->bevt_0_ta_loop->bemd_0(448214784);
if ((static_cast<BEC_2_5_4_LogicBool*>(beq->bevt_5_ta_ph))->bevi_bool) {
beq->bevl_c = beq->bevt_0_ta_loop->bemd_0(-119099042);
beq->bevl_yi->bem_addValueWhole_1(beq->bevl_c);
} 
 else  {
break;
} 
} 
beq->bevt_1_ta_loop = beq->beva_xi->bem_iteratorGet_0();
while (true)
 {
beq->bevt_6_ta_ph = beq->bevt_1_ta_loop->bemd_0(448214784);
if ((static_cast<BEC_2_5_4_LogicBool*>(beq->bevt_6_ta_ph))->bevi_bool) {
beq->bevl_c = beq->bevt_1_ta_loop->bemd_0(-119099042);
beq->bevl_yi->bem_addValueWhole_1(beq->bevl_c);
} 
 else  {
break;
} 
} 
return static_cast<BEC_2_9_4_ContainerList*>(beq->bevl_yi);
}
BEC_2_9_4_ContainerList* BEC_2_9_4_ContainerList::bem_sort_0() {
struct bes { BEC_2_9_4_ContainerList* bevt_0_ta_ph; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->bevt_0_ta_ph = nullptr;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(2);
beq->bevt_0_ta_ph = static_cast<BEC_2_9_4_ContainerList*>(bem_mergeSort_0());
return static_cast<BEC_2_9_4_ContainerList*>(beq->bevt_0_ta_ph);
}
BEC_2_9_4_ContainerList* BEC_2_9_4_ContainerList::bem_sortValue_0() {
struct bes { BEC_2_4_3_MathInt* bevt_0_ta_ph; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->bevt_0_ta_ph = nullptr;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(2);
beq->bevt_0_ta_ph = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(0))));
bem_sortValue_2(beq->bevt_0_ta_ph, bevp_length);
return this;
}
BEC_2_9_4_ContainerList* BEC_2_9_4_ContainerList::bem_sortValue_2(BEC_2_4_3_MathInt* bevk_start, BEC_2_4_3_MathInt* bevk_end) {
struct bes { BEC_2_4_3_MathInt* beva_start; BEC_2_4_3_MathInt* beva_end; BEC_2_4_3_MathInt* bevl_i; BEC_2_4_3_MathInt* bevl_c; BEC_2_4_3_MathInt* bevl_j; BEC_2_6_6_SystemObject* bevl_hold; BEC_2_5_4_LogicBool* bevt_0_ta_ph; BEC_2_5_4_LogicBool* bevt_1_ta_ph; BEC_2_6_6_SystemObject* bevt_2_ta_ph; BEC_2_6_6_SystemObject* bevt_3_ta_ph; BEC_2_6_6_SystemObject* bevt_4_ta_ph; BEC_2_6_6_SystemObject* bevt_5_ta_ph; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->beva_start = bevk_start;
beq->beva_end = bevk_end;
beq->bevl_i = nullptr;
beq->bevl_c = nullptr;
beq->bevl_j = nullptr;
beq->bevl_hold = nullptr;
beq->bevt_0_ta_ph = nullptr;
beq->bevt_1_ta_ph = nullptr;
beq->bevt_2_ta_ph = nullptr;
beq->bevt_3_ta_ph = nullptr;
beq->bevt_4_ta_ph = nullptr;
beq->bevt_5_ta_ph = nullptr;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(13);
beq->bevl_i = static_cast<BEC_2_4_3_MathInt*>(beq->beva_start->bem_copy_0());
while (true)
 {
if (beq->bevl_i->bevi_int < beq->beva_end->bevi_int) {
beq->bevt_0_ta_ph = BECS_Runtime::boolTrue;
 } else { 
beq->bevt_0_ta_ph = BECS_Runtime::boolFalse;
}
if (beq->bevt_0_ta_ph->bevi_bool) {
beq->bevl_c = static_cast<BEC_2_4_3_MathInt*>(beq->bevl_i->bem_copy_0());
beq->bevl_j = static_cast<BEC_2_4_3_MathInt*>(beq->bevl_i->bem_copy_0());
while (true)
 {
if (beq->bevl_j->bevi_int < beq->beva_end->bevi_int) {
beq->bevt_1_ta_ph = BECS_Runtime::boolTrue;
 } else { 
beq->bevt_1_ta_ph = BECS_Runtime::boolFalse;
}
if (beq->bevt_1_ta_ph->bevi_bool) {
beq->bevt_3_ta_ph = bem_get_1(beq->bevl_j);
beq->bevt_4_ta_ph = bem_get_1(beq->bevl_c);
beq->bevt_2_ta_ph = beq->bevt_3_ta_ph->bemd_1(1911891644, beq->bevt_4_ta_ph);
if ((static_cast<BEC_2_5_4_LogicBool*>(beq->bevt_2_ta_ph))->bevi_bool) {
beq->bevl_c = static_cast<BEC_2_4_3_MathInt*>(beq->bevl_j->bem_copy_0());
} 
beq->bevl_j->bevi_int++;
} 
 else  {
break;
} 
} 
beq->bevl_hold = bem_get_1(beq->bevl_i);
beq->bevt_5_ta_ph = bem_get_1(beq->bevl_c);
bem_put_2(beq->bevl_i, beq->bevt_5_ta_ph);
bem_put_2(beq->bevl_c, beq->bevl_hold);
beq->bevl_i->bevi_int++;
} 
 else  {
break;
} 
} 
return this;
}
BEC_2_9_4_ContainerList* BEC_2_9_4_ContainerList::bem_mergeIn_2(BEC_2_9_4_ContainerList* bevk_first, BEC_2_9_4_ContainerList* bevk_second) {
struct bes { BEC_2_9_4_ContainerList* beva_first; BEC_2_9_4_ContainerList* beva_second; BEC_2_4_3_MathInt* bevl_i; BEC_2_4_3_MathInt* bevl_fi; BEC_2_4_3_MathInt* bevl_si; BEC_2_4_3_MathInt* bevl_fl; BEC_2_4_3_MathInt* bevl_sl; BEC_2_6_6_SystemObject* bevl_fo; BEC_2_6_6_SystemObject* bevl_so; BEC_2_5_4_LogicBool* bevt_0_ta_anchor; BEC_2_5_4_LogicBool* bevt_1_ta_ph; BEC_2_5_4_LogicBool* bevt_2_ta_ph; BEC_2_5_4_LogicBool* bevt_3_ta_ph; BEC_2_6_6_SystemObject* bevt_4_ta_ph; BEC_2_5_4_LogicBool* bevt_5_ta_ph; BEC_2_5_4_LogicBool* bevt_6_ta_ph; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->beva_first = bevk_first;
beq->beva_second = bevk_second;
beq->bevl_i = nullptr;
beq->bevl_fi = nullptr;
beq->bevl_si = nullptr;
beq->bevl_fl = nullptr;
beq->bevl_sl = nullptr;
beq->bevl_fo = nullptr;
beq->bevl_so = nullptr;
beq->bevt_0_ta_anchor = nullptr;
beq->bevt_1_ta_ph = nullptr;
beq->bevt_2_ta_ph = nullptr;
beq->bevt_3_ta_ph = nullptr;
beq->bevt_4_ta_ph = nullptr;
beq->bevt_5_ta_ph = nullptr;
beq->bevt_6_ta_ph = nullptr;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(17);
beq->bevl_i = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(0))));
beq->bevl_fi = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(0))));
beq->bevl_si = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(0))));
beq->bevl_fl = beq->beva_first->bem_lengthGet_0();
beq->bevl_sl = beq->beva_second->bem_lengthGet_0();
while (true)
 {
if (beq->bevl_i->bevi_int < bevp_length->bevi_int) {
beq->bevt_1_ta_ph = BECS_Runtime::boolTrue;
 } else { 
beq->bevt_1_ta_ph = BECS_Runtime::boolFalse;
}
if (beq->bevt_1_ta_ph->bevi_bool) {
if (beq->bevl_fi->bevi_int < beq->bevl_fl->bevi_int) {
beq->bevt_2_ta_ph = BECS_Runtime::boolTrue;
 } else { 
beq->bevt_2_ta_ph = BECS_Runtime::boolFalse;
}
if (beq->bevt_2_ta_ph->bevi_bool) {
if (beq->bevl_si->bevi_int < beq->bevl_sl->bevi_int) {
beq->bevt_3_ta_ph = BECS_Runtime::boolTrue;
 } else { 
beq->bevt_3_ta_ph = BECS_Runtime::boolFalse;
}
if (beq->bevt_3_ta_ph->bevi_bool) {
beq->bevt_0_ta_anchor = BECS_Runtime::boolTrue;
} 
 else  {
beq->bevt_0_ta_anchor = BECS_Runtime::boolFalse;
} 
} 
 else  {
beq->bevt_0_ta_anchor = BECS_Runtime::boolFalse;
} 
if (beq->bevt_0_ta_anchor->bevi_bool) {
beq->bevl_fo = beq->beva_first->bem_get_1(beq->bevl_fi);
beq->bevl_so = beq->beva_second->bem_get_1(beq->bevl_si);
beq->bevt_4_ta_ph = beq->bevl_so->bemd_1(1911891644, beq->bevl_fo);
if ((static_cast<BEC_2_5_4_LogicBool*>(beq->bevt_4_ta_ph))->bevi_bool) {
beq->bevl_si->bevi_int++;
bem_put_2(beq->bevl_i, beq->bevl_so);
} 
 else  {
beq->bevl_fi->bevi_int++;
bem_put_2(beq->bevl_i, beq->bevl_fo);
} 
} 
 else  {
if (beq->bevl_si->bevi_int < beq->bevl_sl->bevi_int) {
beq->bevt_5_ta_ph = BECS_Runtime::boolTrue;
 } else { 
beq->bevt_5_ta_ph = BECS_Runtime::boolFalse;
}
if (beq->bevt_5_ta_ph->bevi_bool) {
beq->bevl_so = beq->beva_second->bem_get_1(beq->bevl_si);
beq->bevl_si->bevi_int++;
bem_put_2(beq->bevl_i, beq->bevl_so);
} 
 else  {
if (beq->bevl_fi->bevi_int < beq->bevl_fl->bevi_int) {
beq->bevt_6_ta_ph = BECS_Runtime::boolTrue;
 } else { 
beq->bevt_6_ta_ph = BECS_Runtime::boolFalse;
}
if (beq->bevt_6_ta_ph->bevi_bool) {
beq->bevl_fo = beq->beva_first->bem_get_1(beq->bevl_fi);
beq->bevl_fi->bevi_int++;
bem_put_2(beq->bevl_i, beq->bevl_fo);
} 
} 
} 
beq->bevl_i->bevi_int++;
} 
 else  {
break;
} 
} 
return this;
}
BEC_2_9_4_ContainerList* BEC_2_9_4_ContainerList::bem_mergeSort_0() {
struct bes { BEC_2_9_4_ContainerList* bevt_0_ta_ph; BEC_2_4_3_MathInt* bevt_1_ta_ph; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->bevt_0_ta_ph = nullptr;
beq->bevt_1_ta_ph = nullptr;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(3);
beq->bevt_1_ta_ph = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(0))));
beq->bevt_0_ta_ph = static_cast<BEC_2_9_4_ContainerList*>(bem_mergeSort_2(beq->bevt_1_ta_ph, bevp_length));
return static_cast<BEC_2_9_4_ContainerList*>(beq->bevt_0_ta_ph);
}
BEC_2_9_4_ContainerList* BEC_2_9_4_ContainerList::bem_mergeSort_2(BEC_2_4_3_MathInt* bevk_start, BEC_2_4_3_MathInt* bevk_end) {
struct bes { BEC_2_4_3_MathInt* beva_start; BEC_2_4_3_MathInt* beva_end; BEC_2_4_3_MathInt* bevl_mlen; BEC_2_9_4_ContainerList* bevl_ra; BEC_2_4_3_MathInt* bevl_shalf; BEC_2_4_3_MathInt* bevl_fhalf; BEC_2_4_3_MathInt* bevl_fend; BEC_2_9_4_ContainerList* bevl_fa; BEC_2_9_4_ContainerList* bevl_sa; BEC_2_5_4_LogicBool* bevt_0_ta_ph; BEC_2_4_3_MathInt* bevt_1_ta_ph; BEC_2_6_6_SystemObject* bevt_2_ta_ph; BEC_2_4_3_MathInt* bevt_3_ta_ph; BEC_2_5_4_LogicBool* bevt_4_ta_ph; BEC_2_4_3_MathInt* bevt_5_ta_ph; BEC_2_4_3_MathInt* bevt_6_ta_ph; BEC_2_4_3_MathInt* bevt_7_ta_ph; BEC_2_6_6_SystemObject* bevt_8_ta_ph; BEC_2_4_3_MathInt* bevt_9_ta_ph; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->beva_start = bevk_start;
beq->beva_end = bevk_end;
beq->bevl_mlen = nullptr;
beq->bevl_ra = nullptr;
beq->bevl_shalf = nullptr;
beq->bevl_fhalf = nullptr;
beq->bevl_fend = nullptr;
beq->bevl_fa = nullptr;
beq->bevl_sa = nullptr;
beq->bevt_0_ta_ph = nullptr;
beq->bevt_1_ta_ph = nullptr;
beq->bevt_2_ta_ph = nullptr;
beq->bevt_3_ta_ph = nullptr;
beq->bevt_4_ta_ph = nullptr;
beq->bevt_5_ta_ph = nullptr;
beq->bevt_6_ta_ph = nullptr;
beq->bevt_7_ta_ph = nullptr;
beq->bevt_8_ta_ph = nullptr;
beq->bevt_9_ta_ph = nullptr;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(20);
beq->bevl_mlen = beq->beva_end->bem_subtract_1(beq->beva_start);
beq->bevt_1_ta_ph = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(0))));
if (beq->bevl_mlen->bevi_int == beq->bevt_1_ta_ph->bevi_int) {
beq->bevt_0_ta_ph = BECS_Runtime::boolTrue;
 } else { 
beq->bevt_0_ta_ph = BECS_Runtime::boolFalse;
}
if (beq->bevt_0_ta_ph->bevi_bool) {
beq->bevt_3_ta_ph = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(0))));
beq->bevt_2_ta_ph = bem_create_1(beq->bevt_3_ta_ph);
return static_cast<BEC_2_9_4_ContainerList*>(beq->bevt_2_ta_ph);
} 
 else  {
beq->bevt_5_ta_ph = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(1))));
if (beq->bevl_mlen->bevi_int == beq->bevt_5_ta_ph->bevi_int) {
beq->bevt_4_ta_ph = BECS_Runtime::boolTrue;
 } else { 
beq->bevt_4_ta_ph = BECS_Runtime::boolFalse;
}
if (beq->bevt_4_ta_ph->bevi_bool) {
beq->bevt_6_ta_ph = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(1))));
beq->bevl_ra = static_cast<BEC_2_9_4_ContainerList*>(bem_create_1(beq->bevt_6_ta_ph));
beq->bevt_7_ta_ph = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(0))));
beq->bevt_8_ta_ph = bem_get_1(beq->beva_start);
beq->bevl_ra->bem_put_2(beq->bevt_7_ta_ph, beq->bevt_8_ta_ph);
return static_cast<BEC_2_9_4_ContainerList*>(beq->bevl_ra);
} 
 else  {
beq->bevt_9_ta_ph = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(2))));
beq->bevl_shalf = beq->bevl_mlen->bem_divide_1(beq->bevt_9_ta_ph);
beq->bevl_fhalf = beq->bevl_mlen->bem_subtract_1(beq->bevl_shalf);
beq->bevl_fend = beq->beva_start->bem_add_1(beq->bevl_fhalf);
beq->bevl_fa = static_cast<BEC_2_9_4_ContainerList*>(bem_mergeSort_2(beq->beva_start, beq->bevl_fend));
beq->bevl_sa = static_cast<BEC_2_9_4_ContainerList*>(bem_mergeSort_2(beq->bevl_fend, beq->beva_end));
beq->bevl_ra = static_cast<BEC_2_9_4_ContainerList*>(bem_create_1(beq->bevl_mlen));
beq->bevl_ra->bem_mergeIn_2(beq->bevl_fa, beq->bevl_sa);
return static_cast<BEC_2_9_4_ContainerList*>(beq->bevl_ra);
} 
} 
}
BEC_2_9_4_ContainerList* BEC_2_9_4_ContainerList::bem_capacitySet_1(BEC_2_4_3_MathInt* bevk_newcap) {
struct bes { BEC_2_4_3_MathInt* beva_newcap; BEC_2_5_4_LogicBool* bevt_0_ta_ph; BEC_2_6_9_SystemException* bevt_1_ta_ph; BEC_2_4_6_TextString* bevt_2_ta_ph; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->beva_newcap = bevk_newcap;
beq->bevt_0_ta_ph = nullptr;
beq->bevt_1_ta_ph = nullptr;
beq->bevt_2_ta_ph = nullptr;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(5);
beq->bevt_0_ta_ph = static_cast<BEC_2_5_4_LogicBool*>(BECS_Runtime::boolTrue);
if (beq->bevt_0_ta_ph->bevi_bool) {
beq->bevt_2_ta_ph = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString(13, {0x4E,0x6F,0x74,0x20,0x53,0x75,0x70,0x70,0x6F,0x72,0x74,0x65,0x64}))));
beq->bevt_1_ta_ph = static_cast<BEC_2_6_9_SystemException*>(((BEC_2_6_9_SystemException*) (new BEC_2_6_9_SystemException()))->bem_new_1(beq->bevt_2_ta_ph));
throw BECS_ThrowBack(beq->bevt_1_ta_ph);
} 
return this;
}
BEC_2_9_4_ContainerList* BEC_2_9_4_ContainerList::bem_lengthSet_1(BEC_2_4_3_MathInt* bevk_newlen) {
struct bes { BEC_2_4_3_MathInt* beva_newlen; BEC_2_4_3_MathInt* bevl_newcap; BEC_2_5_4_LogicBool* bevt_0_ta_ph; BEC_2_5_4_LogicBool* bevt_1_ta_ph; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->beva_newlen = bevk_newlen;
beq->bevl_newcap = nullptr;
beq->bevt_0_ta_ph = nullptr;
beq->bevt_1_ta_ph = nullptr;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(5);
if (beq->beva_newlen->bevi_int > bevp_capacity->bevi_int) {
beq->bevt_0_ta_ph = BECS_Runtime::boolTrue;
 } else { 
beq->bevt_0_ta_ph = BECS_Runtime::boolFalse;
}
if (beq->bevt_0_ta_ph->bevi_bool) {
beq->bevl_newcap = beq->beva_newlen->bem_multiply_1(bevp_multiplier);

         bevi_list.resize(beq->bevl_newcap->bevi_int);
         bevp_capacity = beq->bevl_newcap;
} 
while (true)
 {
if (bevp_length->bevi_int < beq->beva_newlen->bevi_int) {
beq->bevt_1_ta_ph = BECS_Runtime::boolTrue;
 } else { 
beq->bevt_1_ta_ph = BECS_Runtime::boolFalse;
}
if (beq->bevt_1_ta_ph->bevi_bool) {

         bevi_list[bevp_length->bevi_int] = nullptr;
         bevp_length->bevi_int++;
} 
 else  {
break;
} 
} 
bevp_length->bevi_int = beq->beva_newlen->bevi_int;
return this;
}
BEC_2_9_4_ContainerList* BEC_2_9_4_ContainerList::bem_iterateAdd_1(BEC_2_6_6_SystemObject* bevk_val) {
struct bes { BEC_2_6_6_SystemObject* beva_val; BEC_2_5_4_LogicBool* bevt_0_ta_ph; BEC_2_6_6_SystemObject* bevt_1_ta_ph; BEC_2_6_6_SystemObject* bevt_2_ta_ph; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->beva_val = bevk_val;
beq->bevt_0_ta_ph = nullptr;
beq->bevt_1_ta_ph = nullptr;
beq->bevt_2_ta_ph = nullptr;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(5);
if (beq->beva_val == nullptr) {
beq->bevt_0_ta_ph = BECS_Runtime::boolFalse;
 } else { 
beq->bevt_0_ta_ph = BECS_Runtime::boolTrue;
}
if (beq->bevt_0_ta_ph->bevi_bool) {
while (true)
 {
beq->bevt_1_ta_ph = beq->beva_val->bemd_0(448214784);
if ((static_cast<BEC_2_5_4_LogicBool*>(beq->bevt_1_ta_ph))->bevi_bool) {
beq->bevt_2_ta_ph = beq->beva_val->bemd_0(-119099042);
bem_addValueWhole_1(beq->bevt_2_ta_ph);
} 
 else  {
break;
} 
} 
} 
return this;
}
BEC_2_9_4_ContainerList* BEC_2_9_4_ContainerList::bem_addAll_1(BEC_2_6_6_SystemObject* bevk_val) {
struct bes { BEC_2_6_6_SystemObject* beva_val; BEC_2_5_4_LogicBool* bevt_0_ta_ph; BEC_2_6_6_SystemObject* bevt_1_ta_ph; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->beva_val = bevk_val;
beq->bevt_0_ta_ph = nullptr;
beq->bevt_1_ta_ph = nullptr;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(4);
if (beq->beva_val == nullptr) {
beq->bevt_0_ta_ph = BECS_Runtime::boolFalse;
 } else { 
beq->bevt_0_ta_ph = BECS_Runtime::boolTrue;
}
if (beq->bevt_0_ta_ph->bevi_bool) {
beq->bevt_1_ta_ph = beq->beva_val->bemd_0(-1428269309);
bem_iterateAdd_1(beq->bevt_1_ta_ph);
} 
return this;
}
BEC_2_9_4_ContainerList* BEC_2_9_4_ContainerList::bem_addValueWhole_1(BEC_2_6_6_SystemObject* bevk_val) {
struct bes { BEC_2_6_6_SystemObject* beva_val; BEC_2_5_4_LogicBool* bevt_0_ta_ph; BEC_2_4_3_MathInt* bevt_1_ta_ph; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->beva_val = bevk_val;
beq->bevt_0_ta_ph = nullptr;
beq->bevt_1_ta_ph = nullptr;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(4);
if (bevp_length->bevi_int < bevp_capacity->bevi_int) {
beq->bevt_0_ta_ph = BECS_Runtime::boolTrue;
 } else { 
beq->bevt_0_ta_ph = BECS_Runtime::boolFalse;
}
if (beq->bevt_0_ta_ph->bevi_bool) {

       bevi_list[bevp_length->bevi_int] = beq->beva_val;
       bevp_length->bevi_int++;
} 
 else  {
beq->bevt_1_ta_ph = static_cast<BEC_2_4_3_MathInt*>(bevp_length->bem_copy_0());
bem_put_2(beq->bevt_1_ta_ph, beq->beva_val);
} 
return this;
}
BEC_2_9_4_ContainerList* BEC_2_9_4_ContainerList::bem_addValue_1(BEC_2_6_6_SystemObject* bevk_val) {
struct bes { BEC_2_6_6_SystemObject* beva_val; BEC_2_5_4_LogicBool* bevt_0_ta_anchor; BEC_2_5_4_LogicBool* bevt_1_ta_ph; BEC_2_5_4_LogicBool* bevt_2_ta_ph; BEC_2_6_5_SystemTypes* bevt_3_ta_ph; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->beva_val = bevk_val;
beq->bevt_0_ta_anchor = nullptr;
beq->bevt_1_ta_ph = nullptr;
beq->bevt_2_ta_ph = nullptr;
beq->bevt_3_ta_ph = nullptr;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(6);
if (beq->beva_val == nullptr) {
beq->bevt_1_ta_ph = BECS_Runtime::boolFalse;
 } else { 
beq->bevt_1_ta_ph = BECS_Runtime::boolTrue;
}
if (beq->bevt_1_ta_ph->bevi_bool) {
beq->bevt_3_ta_ph = static_cast<BEC_2_6_5_SystemTypes*>(BEC_2_6_5_SystemTypes::bece_BEC_2_6_5_SystemTypes_bevs_inst);
beq->bevt_2_ta_ph = beq->bevt_3_ta_ph->bem_sameType_2(beq->beva_val, this);
if (beq->bevt_2_ta_ph->bevi_bool) {
beq->bevt_0_ta_anchor = BECS_Runtime::boolTrue;
} 
 else  {
beq->bevt_0_ta_anchor = BECS_Runtime::boolFalse;
} 
} 
 else  {
beq->bevt_0_ta_anchor = BECS_Runtime::boolFalse;
} 
if (beq->bevt_0_ta_anchor->bevi_bool) {
bem_addAll_1(beq->beva_val);
} 
 else  {
bem_addValueWhole_1(beq->beva_val);
} 
return this;
}
BEC_2_4_3_MathInt* BEC_2_9_4_ContainerList::bem_find_1(BEC_2_6_6_SystemObject* bevk_value) {
struct bes { BEC_2_6_6_SystemObject* beva_value; BEC_2_4_3_MathInt* bevl_i; BEC_2_6_6_SystemObject* bevl_aval; BEC_2_5_4_LogicBool* bevt_0_ta_anchor; BEC_2_5_4_LogicBool* bevt_1_ta_ph; BEC_2_5_4_LogicBool* bevt_2_ta_ph; BEC_2_6_6_SystemObject* bevt_3_ta_ph; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->beva_value = bevk_value;
beq->bevl_i = nullptr;
beq->bevl_aval = nullptr;
beq->bevt_0_ta_anchor = nullptr;
beq->bevt_1_ta_ph = nullptr;
beq->bevt_2_ta_ph = nullptr;
beq->bevt_3_ta_ph = nullptr;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(8);
beq->bevl_i = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(0))));
while (true)
 {
if (beq->bevl_i->bevi_int < bevp_length->bevi_int) {
beq->bevt_1_ta_ph = BECS_Runtime::boolTrue;
 } else { 
beq->bevt_1_ta_ph = BECS_Runtime::boolFalse;
}
if (beq->bevt_1_ta_ph->bevi_bool) {
beq->bevl_aval = bem_get_1(beq->bevl_i);
if (beq->bevl_aval == nullptr) {
beq->bevt_2_ta_ph = BECS_Runtime::boolFalse;
 } else { 
beq->bevt_2_ta_ph = BECS_Runtime::boolTrue;
}
if (beq->bevt_2_ta_ph->bevi_bool) {
beq->bevt_3_ta_ph = beq->beva_value->bemd_1(643138569, beq->bevl_aval);
if ((static_cast<BEC_2_5_4_LogicBool*>(beq->bevt_3_ta_ph))->bevi_bool) {
beq->bevt_0_ta_anchor = BECS_Runtime::boolTrue;
} 
 else  {
beq->bevt_0_ta_anchor = BECS_Runtime::boolFalse;
} 
} 
 else  {
beq->bevt_0_ta_anchor = BECS_Runtime::boolFalse;
} 
if (beq->bevt_0_ta_anchor->bevi_bool) {
return beq->bevl_i;
} 
beq->bevl_i->bevi_int++;
} 
 else  {
break;
} 
} 
return nullptr;
}
BEC_2_5_4_LogicBool* BEC_2_9_4_ContainerList::bem_has_1(BEC_2_6_6_SystemObject* bevk_value) {
struct bes { BEC_2_6_6_SystemObject* beva_value; BEC_2_5_4_LogicBool* bevt_0_ta_ph; BEC_2_4_3_MathInt* bevt_1_ta_ph; BEC_2_5_4_LogicBool* bevt_2_ta_ph; BEC_2_5_4_LogicBool* bevt_3_ta_ph; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->beva_value = bevk_value;
beq->bevt_0_ta_ph = nullptr;
beq->bevt_1_ta_ph = nullptr;
beq->bevt_2_ta_ph = nullptr;
beq->bevt_3_ta_ph = nullptr;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(6);
beq->bevt_1_ta_ph = bem_find_1(beq->beva_value);
if (beq->bevt_1_ta_ph == nullptr) {
beq->bevt_0_ta_ph = BECS_Runtime::boolFalse;
 } else { 
beq->bevt_0_ta_ph = BECS_Runtime::boolTrue;
}
if (beq->bevt_0_ta_ph->bevi_bool) {
beq->bevt_2_ta_ph = static_cast<BEC_2_5_4_LogicBool*>(BECS_Runtime::boolTrue);
return beq->bevt_2_ta_ph;
} 
beq->bevt_3_ta_ph = static_cast<BEC_2_5_4_LogicBool*>(BECS_Runtime::boolFalse);
return beq->bevt_3_ta_ph;
}
BEC_2_4_3_MathInt* BEC_2_9_4_ContainerList::bem_sortedFind_1(BEC_2_6_6_SystemObject* bevk_value) {
struct bes { BEC_2_6_6_SystemObject* beva_value; BEC_2_4_3_MathInt* bevt_0_ta_ph; BEC_2_5_4_LogicBool* bevt_1_ta_ph; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->beva_value = bevk_value;
beq->bevt_0_ta_ph = nullptr;
beq->bevt_1_ta_ph = nullptr;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(4);
beq->bevt_1_ta_ph = static_cast<BEC_2_5_4_LogicBool*>(BECS_Runtime::boolFalse);
beq->bevt_0_ta_ph = bem_sortedFind_2(beq->beva_value, beq->bevt_1_ta_ph);
return beq->bevt_0_ta_ph;
}
BEC_2_4_3_MathInt* BEC_2_9_4_ContainerList::bem_sortedFind_2(BEC_2_6_6_SystemObject* bevk_value, BEC_2_5_4_LogicBool* bevk_returnNoMatch) {
struct bes { BEC_2_6_6_SystemObject* beva_value; BEC_2_5_4_LogicBool* beva_returnNoMatch; BEC_2_4_3_MathInt* bevl_high; BEC_2_4_3_MathInt* bevl_low; BEC_2_4_3_MathInt* bevl_lastMid; BEC_2_4_3_MathInt* bevl_mid; BEC_2_6_6_SystemObject* bevl_aval; BEC_2_5_4_LogicBool* bevt_0_ta_anchor; BEC_2_5_4_LogicBool* bevt_1_ta_anchor; BEC_2_4_3_MathInt* bevt_2_ta_ph; BEC_2_4_3_MathInt* bevt_3_ta_ph; BEC_2_4_3_MathInt* bevt_4_ta_ph; BEC_2_6_6_SystemObject* bevt_5_ta_ph; BEC_2_6_6_SystemObject* bevt_6_ta_ph; BEC_2_6_6_SystemObject* bevt_7_ta_ph; BEC_2_5_4_LogicBool* bevt_8_ta_ph; BEC_2_5_4_LogicBool* bevt_9_ta_ph; BEC_2_6_6_SystemObject* bevt_10_ta_ph; BEC_2_6_6_SystemObject* bevt_11_ta_ph; BEC_2_5_4_LogicBool* bevt_12_ta_ph; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->beva_value = bevk_value;
beq->beva_returnNoMatch = bevk_returnNoMatch;
beq->bevl_high = nullptr;
beq->bevl_low = nullptr;
beq->bevl_lastMid = nullptr;
beq->bevl_mid = nullptr;
beq->bevl_aval = nullptr;
beq->bevt_0_ta_anchor = nullptr;
beq->bevt_1_ta_anchor = nullptr;
beq->bevt_2_ta_ph = nullptr;
beq->bevt_3_ta_ph = nullptr;
beq->bevt_4_ta_ph = nullptr;
beq->bevt_5_ta_ph = nullptr;
beq->bevt_6_ta_ph = nullptr;
beq->bevt_7_ta_ph = nullptr;
beq->bevt_8_ta_ph = nullptr;
beq->bevt_9_ta_ph = nullptr;
beq->bevt_10_ta_ph = nullptr;
beq->bevt_11_ta_ph = nullptr;
beq->bevt_12_ta_ph = nullptr;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(21);
beq->bevl_high = bevp_length;
beq->bevl_low = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(0))));
while (true)
 {
beq->bevt_3_ta_ph = beq->bevl_high->bem_subtract_1(beq->bevl_low);
beq->bevt_4_ta_ph = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(2))));
beq->bevt_2_ta_ph = beq->bevt_3_ta_ph->bem_divide_1(beq->bevt_4_ta_ph);
beq->bevl_mid = beq->bevt_2_ta_ph->bem_add_1(beq->bevl_low);
beq->bevl_aval = bem_get_1(beq->bevl_mid);
beq->bevt_5_ta_ph = beq->beva_value->bemd_1(643138569, beq->bevl_aval);
if ((static_cast<BEC_2_5_4_LogicBool*>(beq->bevt_5_ta_ph))->bevi_bool) {
return beq->bevl_mid;
} 
 else  {
beq->bevt_6_ta_ph = beq->beva_value->bemd_1(-206108566, beq->bevl_aval);
if ((static_cast<BEC_2_5_4_LogicBool*>(beq->bevt_6_ta_ph))->bevi_bool) {
beq->bevl_low = beq->bevl_mid;
} 
 else  {
beq->bevt_7_ta_ph = beq->beva_value->bemd_1(1911891644, beq->bevl_aval);
if ((static_cast<BEC_2_5_4_LogicBool*>(beq->bevt_7_ta_ph))->bevi_bool) {
beq->bevl_high = beq->bevl_mid;
} 
} 
} 
if (beq->bevl_lastMid == nullptr) {
beq->bevt_8_ta_ph = BECS_Runtime::boolFalse;
 } else { 
beq->bevt_8_ta_ph = BECS_Runtime::boolTrue;
}
if (beq->bevt_8_ta_ph->bevi_bool) {
if (beq->bevl_lastMid->bevi_int == beq->bevl_mid->bevi_int) {
beq->bevt_9_ta_ph = BECS_Runtime::boolTrue;
 } else { 
beq->bevt_9_ta_ph = BECS_Runtime::boolFalse;
}
if (beq->bevt_9_ta_ph->bevi_bool) {
beq->bevt_0_ta_anchor = BECS_Runtime::boolTrue;
} 
 else  {
beq->bevt_0_ta_anchor = BECS_Runtime::boolFalse;
} 
} 
 else  {
beq->bevt_0_ta_anchor = BECS_Runtime::boolFalse;
} 
if (beq->bevt_0_ta_anchor->bevi_bool) {
if (beq->beva_returnNoMatch->bevi_bool) {
beq->bevt_11_ta_ph = bem_get_1(beq->bevl_low);
beq->bevt_10_ta_ph = beq->bevt_11_ta_ph->bemd_1(1911891644, beq->beva_value);
if ((static_cast<BEC_2_5_4_LogicBool*>(beq->bevt_10_ta_ph))->bevi_bool) {
beq->bevt_1_ta_anchor = BECS_Runtime::boolTrue;
} 
 else  {
beq->bevt_1_ta_anchor = BECS_Runtime::boolFalse;
} 
} 
 else  {
beq->bevt_1_ta_anchor = BECS_Runtime::boolFalse;
} 
if (beq->bevt_1_ta_anchor->bevi_bool) {
return beq->bevl_low;
} 
return nullptr;
} 
beq->bevl_lastMid = beq->bevl_mid;
beq->bevt_12_ta_ph = static_cast<BEC_2_5_4_LogicBool*>(BECS_Runtime::boolFalse);
if (beq->bevt_12_ta_ph->bevi_bool) {
return nullptr;
} 
} 
}
BEC_2_4_3_MathInt* BEC_2_9_4_ContainerList::bem_lengthGet_0() {
struct bes {  BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(1);
return bevp_length;
}
BEC_2_4_3_MathInt* BEC_2_9_4_ContainerList::bem_capacityGet_0() {
struct bes {  BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(1);
return bevp_capacity;
}
BEC_2_4_3_MathInt* BEC_2_9_4_ContainerList::bem_multiplierGet_0() {
struct bes {  BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(1);
return bevp_multiplier;
}
BEC_2_9_4_ContainerList* BEC_2_9_4_ContainerList::bem_multiplierSet_1(BEC_2_6_6_SystemObject* bevt_0_ta_SET) {
struct bes { BEC_2_6_6_SystemObject* bevt_0_ta_SET; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->bevt_0_ta_SET = bevt_0_ta_SET;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(2);
bevp_multiplier = static_cast<BEC_2_4_3_MathInt*>(beq->bevt_0_ta_SET);
return this;
}
BEC_2_6_6_SystemObject* BEC_2_9_4_ContainerList::bemd_0(int32_t callId) {
switch (callId) {
case 2077526026: return bem_sortValue_0();
case -443788785: return bem_sizeGet_0();
case -1785532669: return bem_new_0();
case 1386267774: return bem_anyrayGet_0();
case 585053990: return bem_sort_0();
case 950712084: return bem_serializeToString_0();
case 2053303229: return bem_isEmptyGet_0();
case -1445610842: return bem_capacityGet_0();
case 1312387167: return bem_create_0();
case 1712845556: return bem_mergeSort_0();
case -396144181: return bem_anyraySet_0();
case 2142500088: return bem_copy_0();
case 1582143508: return bem_firstGet_0();
case 1551129214: return bem_clear_0();
case 1006859886: return bem_multiplierGet_0();
case -964484953: return bem_lastGet_0();
case -1428269309: return bem_iteratorGet_0();
case -854846150: return bem_arrayIteratorGet_0();
case -1710416221: return bem_lengthGet_0();
}
return bevs_super::bemd_0(callId);
}
BEC_2_6_6_SystemObject* BEC_2_9_4_ContainerList::bemd_1(int32_t callId, BEC_2_6_6_SystemObject* bevd_0) {
switch (callId) {
case -2039128300: return bem_multiplierSet_1(bevd_0);
case -842994802: return bem_capacitySet_1(static_cast<BEC_2_4_3_MathInt*>(bevd_0));
case 995642277: return bem_lengthSet_1(static_cast<BEC_2_4_3_MathInt*>(bevd_0));
case 1899676304: return bem_new_1(static_cast<BEC_2_4_3_MathInt*>(bevd_0));
case -693120404: return bem_addAll_1(bevd_0);
case -1618488206: return bem_deserializeFromStringNew_1(static_cast<BEC_2_4_6_TextString*>(bevd_0));
case -1462694209: return bem_sortedFind_1(bevd_0);
case 1526434160: return bem_addValueWhole_1(bevd_0);
case 2106856436: return bem_delete_1(static_cast<BEC_2_4_3_MathInt*>(bevd_0));
case 202420412: return bem_add_1(static_cast<BEC_2_9_4_ContainerList*>(bevd_0));
case 1325848887: return bem_addValue_1(bevd_0);
case 262380141: return bem_has_1(bevd_0);
case 415584667: return bem_find_1(bevd_0);
case -1362425993: return bem_get_1(static_cast<BEC_2_4_3_MathInt*>(bevd_0));
case -670751744: return bem_iterateAdd_1(bevd_0);
case -504553897: return bem_sizeSet_1(static_cast<BEC_2_4_3_MathInt*>(bevd_0));
case 1631253074: return bem_create_1(static_cast<BEC_2_4_3_MathInt*>(bevd_0));
}
return bevs_super::bemd_1(callId, bevd_0);
}
BEC_2_6_6_SystemObject* BEC_2_9_4_ContainerList::bemd_2(int32_t callId, BEC_2_6_6_SystemObject* bevd_0, BEC_2_6_6_SystemObject* bevd_1) {
switch (callId) {
case 878900077: return bem_new_2(static_cast<BEC_2_4_3_MathInt*>(bevd_0), static_cast<BEC_2_4_3_MathInt*>(bevd_1));
case -521989051: return bem_mergeIn_2(static_cast<BEC_2_9_4_ContainerList*>(bevd_0), static_cast<BEC_2_9_4_ContainerList*>(bevd_1));
case -1764267367: return bem_put_2(static_cast<BEC_2_4_3_MathInt*>(bevd_0), bevd_1);
case -1358097746: return bem_sortValue_2(static_cast<BEC_2_4_3_MathInt*>(bevd_0), static_cast<BEC_2_4_3_MathInt*>(bevd_1));
case 747118314: return bem_mergeSort_2(static_cast<BEC_2_4_3_MathInt*>(bevd_0), static_cast<BEC_2_4_3_MathInt*>(bevd_1));
case -883936369: return bem_sortedFind_2(bevd_0, static_cast<BEC_2_5_4_LogicBool*>(bevd_1));
}
return bevs_super::bemd_2(callId, bevd_0, bevd_1);
}
BEC_2_6_6_SystemObject* BEC_2_9_4_ContainerList::bemc_create() {
return new BEC_2_9_4_ContainerList();
}
void BEC_2_9_4_ContainerList::bemc_setInitial(BEC_2_6_6_SystemObject* becc_inst) {
BEC_2_9_4_ContainerList::bece_BEC_2_9_4_ContainerList_bevs_inst = static_cast<BEC_2_9_4_ContainerList*>(becc_inst);
}
BEC_2_6_6_SystemObject* BEC_2_9_4_ContainerList::bemc_getInitial() {
return BEC_2_9_4_ContainerList::bece_BEC_2_9_4_ContainerList_bevs_inst;
}
void BEC_2_9_4_ContainerList::bemg_doMark() {
bevg_gcMark = BECS_Runtime::bevg_currentGcMark;
if (bevp_length != nullptr && bevp_length->bevg_gcMark != BECS_Runtime::bevg_currentGcMark) {
bevp_length->bemg_doMark();
}
if (bevp_capacity != nullptr && bevp_capacity->bevg_gcMark != BECS_Runtime::bevg_currentGcMark) {
bevp_capacity->bemg_doMark();
}
if (bevp_multiplier != nullptr && bevp_multiplier->bevg_gcMark != BECS_Runtime::bevg_currentGcMark) {
bevp_multiplier->bemg_doMark();
}
this->bemg_markContent();
}
size_t BEC_2_9_4_ContainerList::bemg_getSize() {
return sizeof(*this);
}
BETS_Object* BEC_2_9_4_ContainerList::bemc_getType() {
return &BEC_2_9_4_ContainerList::bece_BEC_2_9_4_ContainerList_bevs_type;
}
BET_2_9_5_ContainerLists::BET_2_9_5_ContainerLists() {
std::vector<std::string> bevs_mtnames = {  };
bevs_fieldNames = {  };
}
BEC_2_6_6_SystemObject* BET_2_9_5_ContainerLists::bems_createInstance() {
return new BEC_2_9_5_ContainerLists();
}
void BET_2_9_5_ContainerLists::bemgt_doMark() {
BEC_2_6_6_SystemObject* bevsl_inst_ref = *bevs_inst_ref;
if (bevsl_inst_ref != nullptr && bevsl_inst_ref->bevg_gcMark != BECS_Runtime::bevg_currentGcMark) {
bevsl_inst_ref->bemg_doMark();
}
}
BEC_2_9_5_ContainerLists* BEC_2_9_5_ContainerLists::bece_BEC_2_9_5_ContainerLists_bevs_inst;

BET_2_9_5_ContainerLists BEC_2_9_5_ContainerLists::bece_BEC_2_9_5_ContainerLists_bevs_type;
BEC_2_6_6_SystemObject** BET_2_9_5_ContainerLists::bevs_inst_ref = (BEC_2_6_6_SystemObject**) &BEC_2_9_5_ContainerLists::bece_BEC_2_9_5_ContainerLists_bevs_inst;

BEC_2_9_5_ContainerLists* BEC_2_9_5_ContainerLists::bem_default_0() {
struct bes {  BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(1);
return this;
}
BEC_2_6_6_SystemObject* BEC_2_9_5_ContainerLists::bem_forwardCall_2(BEC_2_4_6_TextString* bevk_name, BEC_2_9_4_ContainerList* bevk_args) {
struct bes { BEC_2_4_6_TextString* beva_name; BEC_2_9_4_ContainerList* beva_args; BEC_2_9_4_ContainerList* bevl_varargs; BEC_2_6_6_SystemObject* bevl_result; BEC_2_4_6_TextString* bevt_0_ta_ph; BEC_2_5_4_LogicBool* bevt_1_ta_ph; BEC_2_4_3_MathInt* bevt_2_ta_ph; BEC_2_4_3_MathInt* bevt_3_ta_ph; BEC_2_4_3_MathInt* bevt_4_ta_ph; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->beva_name = bevk_name;
beq->beva_args = bevk_args;
beq->bevl_varargs = nullptr;
beq->bevl_result = nullptr;
beq->bevt_0_ta_ph = nullptr;
beq->bevt_1_ta_ph = nullptr;
beq->bevt_2_ta_ph = nullptr;
beq->bevt_3_ta_ph = nullptr;
beq->bevt_4_ta_ph = nullptr;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(10);
beq->bevt_0_ta_ph = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString(7, {0x48,0x61,0x6E,0x64,0x6C,0x65,0x72}))));
beq->beva_name = beq->beva_name->bem_add_1(beq->bevt_0_ta_ph);
beq->bevt_2_ta_ph = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(1))));
beq->bevt_1_ta_ph = bem_can_2(beq->beva_name, beq->bevt_2_ta_ph);
if (beq->bevt_1_ta_ph->bevi_bool) {
beq->bevt_3_ta_ph = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(1))));
beq->bevl_varargs = static_cast<BEC_2_9_4_ContainerList*>(((BEC_2_9_4_ContainerList*) (new BEC_2_9_4_ContainerList()))->bem_new_1(beq->bevt_3_ta_ph));
beq->bevt_4_ta_ph = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(0))));
beq->bevl_varargs->bem_put_2(beq->bevt_4_ta_ph, beq->beva_args);
beq->bevl_result = bem_invoke_2(beq->beva_name, beq->bevl_varargs);
} 
return beq->bevl_result;
}
BEC_2_6_6_SystemObject* BEC_2_9_5_ContainerLists::bem_fromHandler_1(BEC_2_9_4_ContainerList* bevk_list) {
struct bes { BEC_2_9_4_ContainerList* beva_list; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->beva_list = bevk_list;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(2);
return beq->beva_list;
}
BEC_2_6_6_SystemObject* BEC_2_9_5_ContainerLists::bemd_0(int32_t callId) {
switch (callId) {
case 1188815194: return bem_default_0();
}
return bevs_super::bemd_0(callId);
}
BEC_2_6_6_SystemObject* BEC_2_9_5_ContainerLists::bemd_1(int32_t callId, BEC_2_6_6_SystemObject* bevd_0) {
switch (callId) {
case -1247507963: return bem_fromHandler_1(static_cast<BEC_2_9_4_ContainerList*>(bevd_0));
}
return bevs_super::bemd_1(callId, bevd_0);
}
BEC_2_6_6_SystemObject* BEC_2_9_5_ContainerLists::bemd_2(int32_t callId, BEC_2_6_6_SystemObject* bevd_0, BEC_2_6_6_SystemObject* bevd_1) {
switch (callId) {
case 1600280145: return bem_forwardCall_2(static_cast<BEC_2_4_6_TextString*>(bevd_0), static_cast<BEC_2_9_4_ContainerList*>(bevd_1));
}
return bevs_super::bemd_2(callId, bevd_0, bevd_1);
}
BEC_2_6_6_SystemObject* BEC_2_9_5_ContainerLists::bemc_create() {
return new BEC_2_9_5_ContainerLists();
}
void BEC_2_9_5_ContainerLists::bemc_setInitial(BEC_2_6_6_SystemObject* becc_inst) {
BEC_2_9_5_ContainerLists::bece_BEC_2_9_5_ContainerLists_bevs_inst = static_cast<BEC_2_9_5_ContainerLists*>(becc_inst);
}
BEC_2_6_6_SystemObject* BEC_2_9_5_ContainerLists::bemc_getInitial() {
return BEC_2_9_5_ContainerLists::bece_BEC_2_9_5_ContainerLists_bevs_inst;
}
void BEC_2_9_5_ContainerLists::bemg_doMark() {
bevg_gcMark = BECS_Runtime::bevg_currentGcMark;
}
size_t BEC_2_9_5_ContainerLists::bemg_getSize() {
return sizeof(*this);
}
BETS_Object* BEC_2_9_5_ContainerLists::bemc_getType() {
return &BEC_2_9_5_ContainerLists::bece_BEC_2_9_5_ContainerLists_bevs_type;
}
BET_2_6_11_SystemInitializer::BET_2_6_11_SystemInitializer() {
std::vector<std::string> bevs_mtnames = {  };
bevs_fieldNames = {  };
}
BEC_2_6_6_SystemObject* BET_2_6_11_SystemInitializer::bems_createInstance() {
return new BEC_2_6_11_SystemInitializer();
}
void BET_2_6_11_SystemInitializer::bemgt_doMark() {
BEC_2_6_6_SystemObject* bevsl_inst_ref = *bevs_inst_ref;
if (bevsl_inst_ref != nullptr && bevsl_inst_ref->bevg_gcMark != BECS_Runtime::bevg_currentGcMark) {
bevsl_inst_ref->bemg_doMark();
}
}
BEC_2_6_11_SystemInitializer* BEC_2_6_11_SystemInitializer::bece_BEC_2_6_11_SystemInitializer_bevs_inst;

BET_2_6_11_SystemInitializer BEC_2_6_11_SystemInitializer::bece_BEC_2_6_11_SystemInitializer_bevs_type;
BEC_2_6_6_SystemObject** BET_2_6_11_SystemInitializer::bevs_inst_ref = (BEC_2_6_6_SystemObject**) &BEC_2_6_11_SystemInitializer::bece_BEC_2_6_11_SystemInitializer_bevs_inst;

BEC_2_6_6_SystemObject* BEC_2_6_11_SystemInitializer::bem_initializeIfShould_1(BEC_2_6_6_SystemObject* bevk_inst) {
struct bes { BEC_2_6_6_SystemObject* beva_inst; BEC_2_6_6_SystemObject* bevt_0_ta_ph; BEC_2_4_6_TextString* bevt_1_ta_ph; BEC_2_4_3_MathInt* bevt_2_ta_ph; BEC_2_6_6_SystemObject* bevt_3_ta_ph; BEC_2_6_6_SystemObject* bevt_4_ta_ph; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->beva_inst = bevk_inst;
beq->bevt_0_ta_ph = nullptr;
beq->bevt_1_ta_ph = nullptr;
beq->bevt_2_ta_ph = nullptr;
beq->bevt_3_ta_ph = nullptr;
beq->bevt_4_ta_ph = nullptr;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(7);
beq->bevt_1_ta_ph = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString(7, {0x64,0x65,0x66,0x61,0x75,0x6C,0x74}))));
beq->bevt_2_ta_ph = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(0))));
beq->bevt_0_ta_ph = beq->beva_inst->bemd_2(-1569524644, beq->bevt_1_ta_ph, beq->bevt_2_ta_ph);
if ((static_cast<BEC_2_5_4_LogicBool*>(beq->bevt_0_ta_ph))->bevi_bool) {
beq->bevt_3_ta_ph = bem_initializeIt_1(beq->beva_inst);
return beq->bevt_3_ta_ph;
} 
beq->bevt_4_ta_ph = beq->beva_inst->bemd_0(-1785532669);
return beq->bevt_4_ta_ph;
}
BEC_2_6_6_SystemObject* BEC_2_6_11_SystemInitializer::bem_notNullInitConstruct_1(BEC_2_6_6_SystemObject* bevk_inst) {
struct bes { BEC_2_6_6_SystemObject* beva_inst; BEC_2_6_6_SystemObject* bevl_init; BEC_2_5_4_LogicBool* bevt_0_ta_ph; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->beva_inst = bevk_inst;
beq->bevl_init = nullptr;
beq->bevt_0_ta_ph = nullptr;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(4);

      beq->bevl_init = beq->beva_inst->bemc_getInitial();
      if (beq->bevl_init == nullptr) {
beq->bevt_0_ta_ph = BECS_Runtime::boolTrue;
 } else { 
beq->bevt_0_ta_ph = BECS_Runtime::boolFalse;
}
if (beq->bevt_0_ta_ph->bevi_bool) {
beq->bevl_init = beq->beva_inst;

          beq->beva_inst->bemc_setInitial(beq->bevl_init);
          } 
return beq->bevl_init;
}
BEC_2_6_11_SystemInitializer* BEC_2_6_11_SystemInitializer::bem_notNullInitDefault_1(BEC_2_6_6_SystemObject* bevk_inst) {
struct bes { BEC_2_6_6_SystemObject* beva_inst; BEC_2_6_6_SystemObject* bevl_init; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->beva_inst = bevk_inst;
beq->bevl_init = nullptr;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(3);

      beq->bevl_init = beq->beva_inst->bemc_getInitial();
      beq->bevl_init->bemd_0(1188815194);
return this;
}
BEC_2_6_6_SystemObject* BEC_2_6_11_SystemInitializer::bem_notNullInitIt_1(BEC_2_6_6_SystemObject* bevk_inst) {
struct bes { BEC_2_6_6_SystemObject* beva_inst; BEC_2_6_6_SystemObject* bevl_init; BEC_2_5_4_LogicBool* bevt_0_ta_ph; BEC_2_6_6_SystemObject* bevt_1_ta_ph; BEC_2_4_6_TextString* bevt_2_ta_ph; BEC_2_4_3_MathInt* bevt_3_ta_ph; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->beva_inst = bevk_inst;
beq->bevl_init = nullptr;
beq->bevt_0_ta_ph = nullptr;
beq->bevt_1_ta_ph = nullptr;
beq->bevt_2_ta_ph = nullptr;
beq->bevt_3_ta_ph = nullptr;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(7);
if (beq->bevl_init == nullptr) {
beq->bevt_0_ta_ph = BECS_Runtime::boolTrue;
 } else { 
beq->bevt_0_ta_ph = BECS_Runtime::boolFalse;
}
if (beq->bevt_0_ta_ph->bevi_bool) {
beq->bevl_init = beq->beva_inst;
beq->bevt_2_ta_ph = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString(7, {0x64,0x65,0x66,0x61,0x75,0x6C,0x74}))));
beq->bevt_3_ta_ph = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(0))));
beq->bevt_1_ta_ph = beq->bevl_init->bemd_2(-1569524644, beq->bevt_2_ta_ph, beq->bevt_3_ta_ph);
if ((static_cast<BEC_2_5_4_LogicBool*>(beq->bevt_1_ta_ph))->bevi_bool) {
beq->bevl_init->bemd_0(1188815194);
} 
} 
return beq->bevl_init;
}
BEC_2_6_6_SystemObject* BEC_2_6_11_SystemInitializer::bem_initializeIt_1(BEC_2_6_6_SystemObject* bevk_inst) {
struct bes { BEC_2_6_6_SystemObject* beva_inst; BEC_2_6_6_SystemObject* bevl_init; BEC_2_5_4_LogicBool* bevt_0_ta_ph; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->beva_inst = bevk_inst;
beq->bevl_init = nullptr;
beq->bevt_0_ta_ph = nullptr;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(4);
if (beq->bevl_init == nullptr) {
beq->bevt_0_ta_ph = BECS_Runtime::boolTrue;
 } else { 
beq->bevt_0_ta_ph = BECS_Runtime::boolFalse;
}
if (beq->bevt_0_ta_ph->bevi_bool) {
beq->bevl_init = beq->beva_inst;
beq->bevl_init->bemd_0(1188815194);
} 
return beq->bevl_init;
}
BEC_2_6_6_SystemObject* BEC_2_6_11_SystemInitializer::bemd_1(int32_t callId, BEC_2_6_6_SystemObject* bevd_0) {
switch (callId) {
case 483531829: return bem_initializeIfShould_1(bevd_0);
case 1287810550: return bem_notNullInitDefault_1(bevd_0);
case -1295310823: return bem_notNullInitIt_1(bevd_0);
case -1867670076: return bem_notNullInitConstruct_1(bevd_0);
case -2117477911: return bem_initializeIt_1(bevd_0);
}
return bevs_super::bemd_1(callId, bevd_0);
}
BEC_2_6_6_SystemObject* BEC_2_6_11_SystemInitializer::bemc_create() {
return new BEC_2_6_11_SystemInitializer();
}
void BEC_2_6_11_SystemInitializer::bemc_setInitial(BEC_2_6_6_SystemObject* becc_inst) {
BEC_2_6_11_SystemInitializer::bece_BEC_2_6_11_SystemInitializer_bevs_inst = static_cast<BEC_2_6_11_SystemInitializer*>(becc_inst);
}
BEC_2_6_6_SystemObject* BEC_2_6_11_SystemInitializer::bemc_getInitial() {
return BEC_2_6_11_SystemInitializer::bece_BEC_2_6_11_SystemInitializer_bevs_inst;
}
void BEC_2_6_11_SystemInitializer::bemg_doMark() {
bevg_gcMark = BECS_Runtime::bevg_currentGcMark;
}
size_t BEC_2_6_11_SystemInitializer::bemg_getSize() {
return sizeof(*this);
}
BETS_Object* BEC_2_6_11_SystemInitializer::bemc_getType() {
return &BEC_2_6_11_SystemInitializer::bece_BEC_2_6_11_SystemInitializer_bevs_type;
}
BET_2_6_6_SystemRandom::BET_2_6_6_SystemRandom() {
std::vector<std::string> bevs_mtnames = {  };
bevs_fieldNames = {  };
}
BEC_2_6_6_SystemObject* BET_2_6_6_SystemRandom::bems_createInstance() {
return new BEC_2_6_6_SystemRandom();
}
void BET_2_6_6_SystemRandom::bemgt_doMark() {
BEC_2_6_6_SystemObject* bevsl_inst_ref = *bevs_inst_ref;
if (bevsl_inst_ref != nullptr && bevsl_inst_ref->bevg_gcMark != BECS_Runtime::bevg_currentGcMark) {
bevsl_inst_ref->bemg_doMark();
}
}
BEC_2_6_6_SystemRandom* BEC_2_6_6_SystemRandom::bece_BEC_2_6_6_SystemRandom_bevs_inst;

BET_2_6_6_SystemRandom BEC_2_6_6_SystemRandom::bece_BEC_2_6_6_SystemRandom_bevs_type;
BEC_2_6_6_SystemObject** BET_2_6_6_SystemRandom::bevs_inst_ref = (BEC_2_6_6_SystemObject**) &BEC_2_6_6_SystemRandom::bece_BEC_2_6_6_SystemRandom_bevs_inst;

BEC_2_6_6_SystemObject* BEC_2_6_6_SystemRandom::bem_create_0() {
struct bes {  BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(1);
return this;
}
BEC_2_6_6_SystemRandom* BEC_2_6_6_SystemRandom::bem_default_0() {
struct bes {  BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(1);
bem_seedNow_0();
return this;
}
BEC_2_6_6_SystemRandom* BEC_2_6_6_SystemRandom::bem_seedNow_0() {
struct bes {  BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(1);

      srand(time(0));
      return this;
}
BEC_2_6_6_SystemRandom* BEC_2_6_6_SystemRandom::bem_seed_1(BEC_2_4_3_MathInt* bevk_seed) {
struct bes { BEC_2_4_3_MathInt* beva_seed; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->beva_seed = bevk_seed;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(2);

      srand(beq->beva_seed->bevi_int);
      return this;
}
BEC_2_4_3_MathInt* BEC_2_6_6_SystemRandom::bem_getInt_0() {
struct bes { BEC_2_4_3_MathInt* bevt_0_ta_ph; BEC_2_4_3_MathInt* bevt_1_ta_ph; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->bevt_0_ta_ph = nullptr;
beq->bevt_1_ta_ph = nullptr;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(3);
beq->bevt_1_ta_ph = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt())));
beq->bevt_0_ta_ph = bem_getInt_1(beq->bevt_1_ta_ph);
return beq->bevt_0_ta_ph;
}
BEC_2_4_3_MathInt* BEC_2_6_6_SystemRandom::bem_getInt_1(BEC_2_4_3_MathInt* bevk_value) {
struct bes { BEC_2_4_3_MathInt* beva_value; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->beva_value = bevk_value;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(2);

      beq->beva_value->bevi_int = rand();
      return beq->beva_value;
}
BEC_2_4_3_MathInt* BEC_2_6_6_SystemRandom::bem_getIntMax_1(BEC_2_4_3_MathInt* bevk_max) {
struct bes { BEC_2_4_3_MathInt* beva_max; BEC_2_4_3_MathInt* bevt_0_ta_ph; BEC_2_4_3_MathInt* bevt_1_ta_ph; BEC_2_4_3_MathInt* bevt_2_ta_ph; BEC_2_4_3_MathInt* bevt_3_ta_ph; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->beva_max = bevk_max;
beq->bevt_0_ta_ph = nullptr;
beq->bevt_1_ta_ph = nullptr;
beq->bevt_2_ta_ph = nullptr;
beq->bevt_3_ta_ph = nullptr;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(6);
beq->bevt_3_ta_ph = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt())));
beq->bevt_2_ta_ph = bem_getInt_1(beq->bevt_3_ta_ph);
beq->bevt_1_ta_ph = beq->bevt_2_ta_ph->bem_absValue_0();
beq->bevt_0_ta_ph = beq->bevt_1_ta_ph->bem_modulusValue_1(beq->beva_max);
return beq->bevt_0_ta_ph;
}
BEC_2_4_3_MathInt* BEC_2_6_6_SystemRandom::bem_getIntMax_2(BEC_2_4_3_MathInt* bevk_value, BEC_2_4_3_MathInt* bevk_max) {
struct bes { BEC_2_4_3_MathInt* beva_value; BEC_2_4_3_MathInt* beva_max; BEC_2_4_3_MathInt* bevt_0_ta_ph; BEC_2_4_3_MathInt* bevt_1_ta_ph; BEC_2_4_3_MathInt* bevt_2_ta_ph; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->beva_value = bevk_value;
beq->beva_max = bevk_max;
beq->bevt_0_ta_ph = nullptr;
beq->bevt_1_ta_ph = nullptr;
beq->bevt_2_ta_ph = nullptr;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(6);
beq->bevt_2_ta_ph = bem_getInt_1(beq->beva_value);
beq->bevt_1_ta_ph = beq->bevt_2_ta_ph->bem_absValue_0();
beq->bevt_0_ta_ph = beq->bevt_1_ta_ph->bem_modulusValue_1(beq->beva_max);
return beq->bevt_0_ta_ph;
}
BEC_2_4_6_TextString* BEC_2_6_6_SystemRandom::bem_getString_1(BEC_2_4_3_MathInt* bevk_size) {
struct bes { BEC_2_4_3_MathInt* beva_size; BEC_2_4_6_TextString* bevt_0_ta_ph; BEC_2_4_6_TextString* bevt_1_ta_ph; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->beva_size = bevk_size;
beq->bevt_0_ta_ph = nullptr;
beq->bevt_1_ta_ph = nullptr;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(4);
beq->bevt_1_ta_ph = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString()))->bem_new_1(beq->beva_size));
beq->bevt_0_ta_ph = bem_getString_2(beq->bevt_1_ta_ph, beq->beva_size);
return beq->bevt_0_ta_ph;
}
BEC_2_4_6_TextString* BEC_2_6_6_SystemRandom::bem_getString_2(BEC_2_4_6_TextString* bevk_str, BEC_2_4_3_MathInt* bevk_size) {
struct bes { BEC_2_4_6_TextString* beva_str; BEC_2_4_3_MathInt* beva_size; BEC_2_4_3_MathInt* bevl_value; BEC_2_4_3_MathInt* bevl_i; BEC_2_5_4_LogicBool* bevt_0_ta_ph; BEC_2_4_3_MathInt* bevt_1_ta_ph; BEC_2_4_3_MathInt* bevt_2_ta_ph; BEC_2_5_4_LogicBool* bevt_3_ta_ph; BEC_2_4_3_MathInt* bevt_4_ta_ph; BEC_2_4_3_MathInt* bevt_5_ta_ph; BEC_2_4_3_MathInt* bevt_6_ta_ph; BEC_2_4_3_MathInt* bevt_7_ta_ph; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->beva_str = bevk_str;
beq->beva_size = bevk_size;
beq->bevl_value = nullptr;
beq->bevl_i = nullptr;
beq->bevt_0_ta_ph = nullptr;
beq->bevt_1_ta_ph = nullptr;
beq->bevt_2_ta_ph = nullptr;
beq->bevt_3_ta_ph = nullptr;
beq->bevt_4_ta_ph = nullptr;
beq->bevt_5_ta_ph = nullptr;
beq->bevt_6_ta_ph = nullptr;
beq->bevt_7_ta_ph = nullptr;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(13);
beq->bevt_1_ta_ph = beq->beva_str->bem_capacityGet_0();
if (beq->bevt_1_ta_ph->bevi_int < beq->beva_size->bevi_int) {
beq->bevt_0_ta_ph = BECS_Runtime::boolTrue;
 } else { 
beq->bevt_0_ta_ph = BECS_Runtime::boolFalse;
}
if (beq->bevt_0_ta_ph->bevi_bool) {
beq->beva_str->bem_capacitySet_1(beq->beva_size);
} 
beq->bevt_2_ta_ph = static_cast<BEC_2_4_3_MathInt*>(beq->beva_size->bem_copy_0());
beq->beva_str->bem_sizeSet_1(beq->bevt_2_ta_ph);
beq->bevl_value = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt())));
beq->bevl_i = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(0))));
while (true)
 {
if (beq->bevl_i->bevi_int < beq->beva_size->bevi_int) {
beq->bevt_3_ta_ph = BECS_Runtime::boolTrue;
 } else { 
beq->bevt_3_ta_ph = BECS_Runtime::boolFalse;
}
if (beq->bevt_3_ta_ph->bevi_bool) {
beq->bevt_6_ta_ph = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(26))));
beq->bevt_5_ta_ph = bem_getIntMax_2(beq->bevl_value, beq->bevt_6_ta_ph);
beq->bevt_7_ta_ph = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(65))));
beq->bevt_5_ta_ph->bevi_int += beq->bevt_7_ta_ph->bevi_int;
beq->bevt_4_ta_ph = beq->bevt_5_ta_ph;
beq->beva_str->bem_setIntUnchecked_2(beq->bevl_i, beq->bevt_4_ta_ph);
beq->bevl_i->bevi_int++;
} 
 else  {
break;
} 
} 
return beq->beva_str;
}
BEC_2_6_6_SystemObject* BEC_2_6_6_SystemRandom::bemd_0(int32_t callId) {
switch (callId) {
case -1943177491: return bem_getInt_0();
case 1312387167: return bem_create_0();
case 1188815194: return bem_default_0();
case 616691499: return bem_seedNow_0();
}
return bevs_super::bemd_0(callId);
}
BEC_2_6_6_SystemObject* BEC_2_6_6_SystemRandom::bemd_1(int32_t callId, BEC_2_6_6_SystemObject* bevd_0) {
switch (callId) {
case 1296881153: return bem_getInt_1(static_cast<BEC_2_4_3_MathInt*>(bevd_0));
case -1507396776: return bem_getString_1(static_cast<BEC_2_4_3_MathInt*>(bevd_0));
case 1700867878: return bem_seed_1(static_cast<BEC_2_4_3_MathInt*>(bevd_0));
case 1911055130: return bem_getIntMax_1(static_cast<BEC_2_4_3_MathInt*>(bevd_0));
}
return bevs_super::bemd_1(callId, bevd_0);
}
BEC_2_6_6_SystemObject* BEC_2_6_6_SystemRandom::bemd_2(int32_t callId, BEC_2_6_6_SystemObject* bevd_0, BEC_2_6_6_SystemObject* bevd_1) {
switch (callId) {
case 2042980200: return bem_getIntMax_2(static_cast<BEC_2_4_3_MathInt*>(bevd_0), static_cast<BEC_2_4_3_MathInt*>(bevd_1));
case -1888336788: return bem_getString_2(static_cast<BEC_2_4_6_TextString*>(bevd_0), static_cast<BEC_2_4_3_MathInt*>(bevd_1));
}
return bevs_super::bemd_2(callId, bevd_0, bevd_1);
}
BEC_2_6_6_SystemObject* BEC_2_6_6_SystemRandom::bemc_create() {
return new BEC_2_6_6_SystemRandom();
}
void BEC_2_6_6_SystemRandom::bemc_setInitial(BEC_2_6_6_SystemObject* becc_inst) {
BEC_2_6_6_SystemRandom::bece_BEC_2_6_6_SystemRandom_bevs_inst = static_cast<BEC_2_6_6_SystemRandom*>(becc_inst);
}
BEC_2_6_6_SystemObject* BEC_2_6_6_SystemRandom::bemc_getInitial() {
return BEC_2_6_6_SystemRandom::bece_BEC_2_6_6_SystemRandom_bevs_inst;
}
void BEC_2_6_6_SystemRandom::bemg_doMark() {
bevg_gcMark = BECS_Runtime::bevg_currentGcMark;
}
size_t BEC_2_6_6_SystemRandom::bemg_getSize() {
return sizeof(*this);
}
BETS_Object* BEC_2_6_6_SystemRandom::bemc_getType() {
return &BEC_2_6_6_SystemRandom::bece_BEC_2_6_6_SystemRandom_bevs_type;
}
BET_2_6_19_SystemObjectFieldIterator::BET_2_6_19_SystemObjectFieldIterator() {
std::vector<std::string> bevs_mtnames = {  };
bevs_fieldNames = {  };
}
BEC_2_6_6_SystemObject* BET_2_6_19_SystemObjectFieldIterator::bems_createInstance() {
return new BEC_2_6_19_SystemObjectFieldIterator();
}
void BET_2_6_19_SystemObjectFieldIterator::bemgt_doMark() {
BEC_2_6_6_SystemObject* bevsl_inst_ref = *bevs_inst_ref;
if (bevsl_inst_ref != nullptr && bevsl_inst_ref->bevg_gcMark != BECS_Runtime::bevg_currentGcMark) {
bevsl_inst_ref->bemg_doMark();
}
}
BEC_2_6_19_SystemObjectFieldIterator* BEC_2_6_19_SystemObjectFieldIterator::bece_BEC_2_6_19_SystemObjectFieldIterator_bevs_inst;

BET_2_6_19_SystemObjectFieldIterator BEC_2_6_19_SystemObjectFieldIterator::bece_BEC_2_6_19_SystemObjectFieldIterator_bevs_type;
BEC_2_6_6_SystemObject** BET_2_6_19_SystemObjectFieldIterator::bevs_inst_ref = (BEC_2_6_6_SystemObject**) &BEC_2_6_19_SystemObjectFieldIterator::bece_BEC_2_6_19_SystemObjectFieldIterator_bevs_inst;

BEC_2_6_6_SystemObject* BEC_2_6_19_SystemObjectFieldIterator::bem_new_0() {
struct bes {  BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(1);
return this;
}
BEC_2_6_19_SystemObjectFieldIterator* BEC_2_6_19_SystemObjectFieldIterator::bem_new_1(BEC_2_6_6_SystemObject* bevk__instance) {
struct bes { BEC_2_6_6_SystemObject* beva__instance; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->beva__instance = bevk__instance;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(2);
return this;
}
BEC_2_6_19_SystemObjectFieldIterator* BEC_2_6_19_SystemObjectFieldIterator::bem_new_2(BEC_2_6_6_SystemObject* bevk__instance, BEC_2_5_4_LogicBool* bevk_forceFirstSlot) {
struct bes { BEC_2_6_6_SystemObject* beva__instance; BEC_2_5_4_LogicBool* beva_forceFirstSlot; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->beva__instance = bevk__instance;
beq->beva_forceFirstSlot = bevk_forceFirstSlot;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(3);
return this;
}
BEC_2_5_4_LogicBool* BEC_2_6_19_SystemObjectFieldIterator::bem_hasNextGet_0() {
struct bes { BEC_2_5_4_LogicBool* bevt_0_ta_ph; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->bevt_0_ta_ph = nullptr;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(2);
beq->bevt_0_ta_ph = static_cast<BEC_2_5_4_LogicBool*>(BECS_Runtime::boolFalse);
return beq->bevt_0_ta_ph;
}
BEC_2_6_6_SystemObject* BEC_2_6_19_SystemObjectFieldIterator::bem_nextGet_0() {
struct bes {  BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(1);
return nullptr;
}
BEC_2_6_19_SystemObjectFieldIterator* BEC_2_6_19_SystemObjectFieldIterator::bem_nextSet_1(BEC_2_6_6_SystemObject* bevk_it) {
struct bes { BEC_2_6_6_SystemObject* beva_it; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->beva_it = bevk_it;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(2);
return this;
}
BEC_2_6_6_SystemObject* BEC_2_6_19_SystemObjectFieldIterator::bemd_0(int32_t callId) {
switch (callId) {
case 448214784: return bem_hasNextGet_0();
case -119099042: return bem_nextGet_0();
case -1785532669: return bem_new_0();
}
return bevs_super::bemd_0(callId);
}
BEC_2_6_6_SystemObject* BEC_2_6_19_SystemObjectFieldIterator::bemd_1(int32_t callId, BEC_2_6_6_SystemObject* bevd_0) {
switch (callId) {
case -1206415723: return bem_nextSet_1(bevd_0);
case 1899676304: return bem_new_1(bevd_0);
}
return bevs_super::bemd_1(callId, bevd_0);
}
BEC_2_6_6_SystemObject* BEC_2_6_19_SystemObjectFieldIterator::bemd_2(int32_t callId, BEC_2_6_6_SystemObject* bevd_0, BEC_2_6_6_SystemObject* bevd_1) {
switch (callId) {
case 878900077: return bem_new_2(bevd_0, static_cast<BEC_2_5_4_LogicBool*>(bevd_1));
}
return bevs_super::bemd_2(callId, bevd_0, bevd_1);
}
BEC_2_6_6_SystemObject* BEC_2_6_19_SystemObjectFieldIterator::bemc_create() {
return new BEC_2_6_19_SystemObjectFieldIterator();
}
void BEC_2_6_19_SystemObjectFieldIterator::bemc_setInitial(BEC_2_6_6_SystemObject* becc_inst) {
BEC_2_6_19_SystemObjectFieldIterator::bece_BEC_2_6_19_SystemObjectFieldIterator_bevs_inst = static_cast<BEC_2_6_19_SystemObjectFieldIterator*>(becc_inst);
}
BEC_2_6_6_SystemObject* BEC_2_6_19_SystemObjectFieldIterator::bemc_getInitial() {
return BEC_2_6_19_SystemObjectFieldIterator::bece_BEC_2_6_19_SystemObjectFieldIterator_bevs_inst;
}
void BEC_2_6_19_SystemObjectFieldIterator::bemg_doMark() {
bevg_gcMark = BECS_Runtime::bevg_currentGcMark;
}
size_t BEC_2_6_19_SystemObjectFieldIterator::bemg_getSize() {
return sizeof(*this);
}
BETS_Object* BEC_2_6_19_SystemObjectFieldIterator::bemc_getType() {
return &BEC_2_6_19_SystemObjectFieldIterator::bece_BEC_2_6_19_SystemObjectFieldIterator_bevs_type;
}
BET_2_6_5_SystemTypes::BET_2_6_5_SystemTypes() {
std::vector<std::string> bevs_mtnames = {  };
bevs_fieldNames = {  };
}
BEC_2_6_6_SystemObject* BET_2_6_5_SystemTypes::bems_createInstance() {
return new BEC_2_6_5_SystemTypes();
}
void BET_2_6_5_SystemTypes::bemgt_doMark() {
BEC_2_6_6_SystemObject* bevsl_inst_ref = *bevs_inst_ref;
if (bevsl_inst_ref != nullptr && bevsl_inst_ref->bevg_gcMark != BECS_Runtime::bevg_currentGcMark) {
bevsl_inst_ref->bemg_doMark();
}
}
BEC_2_6_5_SystemTypes* BEC_2_6_5_SystemTypes::bece_BEC_2_6_5_SystemTypes_bevs_inst;

BET_2_6_5_SystemTypes BEC_2_6_5_SystemTypes::bece_BEC_2_6_5_SystemTypes_bevs_type;
BEC_2_6_6_SystemObject** BET_2_6_5_SystemTypes::bevs_inst_ref = (BEC_2_6_6_SystemObject**) &BEC_2_6_5_SystemTypes::bece_BEC_2_6_5_SystemTypes_bevs_inst;

BEC_2_6_6_SystemObject* BEC_2_6_5_SystemTypes::bem_create_0() {
struct bes {  BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(1);
return this;
}
BEC_2_6_5_SystemTypes* BEC_2_6_5_SystemTypes::bem_default_0() {
struct bes {  BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(1);
return this;
}
BEC_2_5_4_LogicBool* BEC_2_6_5_SystemTypes::bem_sameType_2(BEC_2_6_6_SystemObject* bevk_org, BEC_2_6_6_SystemObject* bevk_other) {
struct bes { BEC_2_6_6_SystemObject* beva_org; BEC_2_6_6_SystemObject* beva_other; BEC_2_5_4_LogicBool* bevt_0_ta_ph; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->beva_org = bevk_org;
beq->beva_other = bevk_other;
beq->bevt_0_ta_ph = nullptr;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(4);

      if (beq->beva_other != nullptr) {
        //if the other type is same or parent type of mine
        BETS_Object* bevs_mt = beq->beva_org->bemc_getType();
        BETS_Object* bevs_ot = beq->beva_other->bemc_getType();
        while (bevs_mt != NULL) {
          if (bevs_mt == bevs_ot) {
            return BECS_Runtime::boolTrue;
          } else {
            bevs_mt = bevs_mt->bevs_parentType;
          }
        }
      }
      beq->bevt_0_ta_ph = static_cast<BEC_2_5_4_LogicBool*>(BECS_Runtime::boolFalse);
return beq->bevt_0_ta_ph;
}
BEC_2_5_4_LogicBool* BEC_2_6_5_SystemTypes::bem_otherType_2(BEC_2_6_6_SystemObject* bevk_org, BEC_2_6_6_SystemObject* bevk_other) {
struct bes { BEC_2_6_6_SystemObject* beva_org; BEC_2_6_6_SystemObject* beva_other; BEC_2_5_4_LogicBool* bevt_0_ta_ph; BEC_2_5_4_LogicBool* bevt_1_ta_ph; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->beva_org = bevk_org;
beq->beva_other = bevk_other;
beq->bevt_0_ta_ph = nullptr;
beq->bevt_1_ta_ph = nullptr;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(5);
beq->bevt_1_ta_ph = bem_sameType_2(beq->beva_org, beq->beva_other);
if (beq->bevt_1_ta_ph->bevi_bool) {
beq->bevt_0_ta_ph = BECS_Runtime::boolFalse;
 } else { 
beq->bevt_0_ta_ph = BECS_Runtime::boolTrue;
}
return beq->bevt_0_ta_ph;
}
BEC_2_6_6_SystemObject* BEC_2_6_5_SystemTypes::bemd_0(int32_t callId) {
switch (callId) {
case 1312387167: return bem_create_0();
case 1188815194: return bem_default_0();
}
return bevs_super::bemd_0(callId);
}
BEC_2_6_6_SystemObject* BEC_2_6_5_SystemTypes::bemd_2(int32_t callId, BEC_2_6_6_SystemObject* bevd_0, BEC_2_6_6_SystemObject* bevd_1) {
switch (callId) {
case 1630761147: return bem_otherType_2(bevd_0, bevd_1);
case -742358638: return bem_sameType_2(bevd_0, bevd_1);
}
return bevs_super::bemd_2(callId, bevd_0, bevd_1);
}
BEC_2_6_6_SystemObject* BEC_2_6_5_SystemTypes::bemc_create() {
return new BEC_2_6_5_SystemTypes();
}
void BEC_2_6_5_SystemTypes::bemc_setInitial(BEC_2_6_6_SystemObject* becc_inst) {
BEC_2_6_5_SystemTypes::bece_BEC_2_6_5_SystemTypes_bevs_inst = static_cast<BEC_2_6_5_SystemTypes*>(becc_inst);
}
BEC_2_6_6_SystemObject* BEC_2_6_5_SystemTypes::bemc_getInitial() {
return BEC_2_6_5_SystemTypes::bece_BEC_2_6_5_SystemTypes_bevs_inst;
}
void BEC_2_6_5_SystemTypes::bemg_doMark() {
bevg_gcMark = BECS_Runtime::bevg_currentGcMark;
}
size_t BEC_2_6_5_SystemTypes::bemg_getSize() {
return sizeof(*this);
}
BETS_Object* BEC_2_6_5_SystemTypes::bemc_getType() {
return &BEC_2_6_5_SystemTypes::bece_BEC_2_6_5_SystemTypes_bevs_type;
}
BET_2_6_9_SystemException::BET_2_6_9_SystemException() {
std::vector<std::string> bevs_mtnames = {  };
bevs_fieldNames = {  };
}
BEC_2_6_6_SystemObject* BET_2_6_9_SystemException::bems_createInstance() {
return new BEC_2_6_9_SystemException();
}
void BET_2_6_9_SystemException::bemgt_doMark() {
BEC_2_6_6_SystemObject* bevsl_inst_ref = *bevs_inst_ref;
if (bevsl_inst_ref != nullptr && bevsl_inst_ref->bevg_gcMark != BECS_Runtime::bevg_currentGcMark) {
bevsl_inst_ref->bemg_doMark();
}
}
BEC_2_6_9_SystemException* BEC_2_6_9_SystemException::bece_BEC_2_6_9_SystemException_bevs_inst;

BET_2_6_9_SystemException BEC_2_6_9_SystemException::bece_BEC_2_6_9_SystemException_bevs_type;
BEC_2_6_6_SystemObject** BET_2_6_9_SystemException::bevs_inst_ref = (BEC_2_6_6_SystemObject**) &BEC_2_6_9_SystemException::bece_BEC_2_6_9_SystemException_bevs_inst;

BEC_2_6_9_SystemException* BEC_2_6_9_SystemException::bem_new_1(BEC_2_6_6_SystemObject* bevk_descr) {
struct bes { BEC_2_6_6_SystemObject* beva_descr; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->beva_descr = bevk_descr;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(2);
bevp_description = beq->beva_descr;
return this;
}
BEC_2_4_6_TextString* BEC_2_6_9_SystemException::bem_toString_0() {
struct bes {  BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(1);
return static_cast<BEC_2_4_6_TextString*>(bevp_description);
}
BEC_2_6_6_SystemObject* BEC_2_6_9_SystemException::bem_descriptionGet_0() {
struct bes {  BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(1);
return bevp_description;
}
BEC_2_6_9_SystemException* BEC_2_6_9_SystemException::bem_descriptionSet_1(BEC_2_6_6_SystemObject* bevt_0_ta_SET) {
struct bes { BEC_2_6_6_SystemObject* bevt_0_ta_SET; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->bevt_0_ta_SET = bevt_0_ta_SET;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(2);
bevp_description = beq->bevt_0_ta_SET;
return this;
}
BEC_2_6_6_SystemObject* BEC_2_6_9_SystemException::bemd_0(int32_t callId) {
switch (callId) {
case -1553512291: return bem_toString_0();
case 1605533746: return bem_descriptionGet_0();
}
return bevs_super::bemd_0(callId);
}
BEC_2_6_6_SystemObject* BEC_2_6_9_SystemException::bemd_1(int32_t callId, BEC_2_6_6_SystemObject* bevd_0) {
switch (callId) {
case -1385536841: return bem_descriptionSet_1(bevd_0);
case 1899676304: return bem_new_1(bevd_0);
}
return bevs_super::bemd_1(callId, bevd_0);
}
BEC_2_6_6_SystemObject* BEC_2_6_9_SystemException::bemc_create() {
return new BEC_2_6_9_SystemException();
}
void BEC_2_6_9_SystemException::bemc_setInitial(BEC_2_6_6_SystemObject* becc_inst) {
BEC_2_6_9_SystemException::bece_BEC_2_6_9_SystemException_bevs_inst = static_cast<BEC_2_6_9_SystemException*>(becc_inst);
}
BEC_2_6_6_SystemObject* BEC_2_6_9_SystemException::bemc_getInitial() {
return BEC_2_6_9_SystemException::bece_BEC_2_6_9_SystemException_bevs_inst;
}
void BEC_2_6_9_SystemException::bemg_doMark() {
bevg_gcMark = BECS_Runtime::bevg_currentGcMark;
if (bevp_description != nullptr && bevp_description->bevg_gcMark != BECS_Runtime::bevg_currentGcMark) {
bevp_description->bemg_doMark();
}
}
size_t BEC_2_6_9_SystemException::bemg_getSize() {
return sizeof(*this);
}
BETS_Object* BEC_2_6_9_SystemException::bemc_getType() {
return &BEC_2_6_9_SystemException::bece_BEC_2_6_9_SystemException_bevs_type;
}
BET_2_8_15_EmbeddedSwitchAndDimmer::BET_2_8_15_EmbeddedSwitchAndDimmer() {
std::vector<std::string> bevs_mtnames = {  };
bevs_fieldNames = {  };
}
BEC_2_6_6_SystemObject* BET_2_8_15_EmbeddedSwitchAndDimmer::bems_createInstance() {
return new BEC_2_8_15_EmbeddedSwitchAndDimmer();
}
void BET_2_8_15_EmbeddedSwitchAndDimmer::bemgt_doMark() {
BEC_2_6_6_SystemObject* bevsl_inst_ref = *bevs_inst_ref;
if (bevsl_inst_ref != nullptr && bevsl_inst_ref->bevg_gcMark != BECS_Runtime::bevg_currentGcMark) {
bevsl_inst_ref->bemg_doMark();
}
}
BEC_2_8_15_EmbeddedSwitchAndDimmer* BEC_2_8_15_EmbeddedSwitchAndDimmer::bece_BEC_2_8_15_EmbeddedSwitchAndDimmer_bevs_inst;

BET_2_8_15_EmbeddedSwitchAndDimmer BEC_2_8_15_EmbeddedSwitchAndDimmer::bece_BEC_2_8_15_EmbeddedSwitchAndDimmer_bevs_type;
BEC_2_6_6_SystemObject** BET_2_8_15_EmbeddedSwitchAndDimmer::bevs_inst_ref = (BEC_2_6_6_SystemObject**) &BEC_2_8_15_EmbeddedSwitchAndDimmer::bece_BEC_2_8_15_EmbeddedSwitchAndDimmer_bevs_inst;

BEC_2_6_6_SystemObject* BEC_2_8_15_EmbeddedSwitchAndDimmer::bem_buildControl_3(BEC_2_4_3_MathInt* bevk_conPos, BEC_2_4_6_TextString* bevk_conName, BEC_2_4_6_TextString* bevk_conArgs) {
struct bes { BEC_2_4_3_MathInt* beva_conPos; BEC_2_4_6_TextString* beva_conName; BEC_2_4_6_TextString* beva_conArgs; BEC_2_8_13_EmbeddedSwitchControl* bevl_swc; BEC_2_8_13_EmbeddedDimmerControl* bevl_dimc; BEC_2_5_4_LogicBool* bevt_0_ta_ph; BEC_2_4_6_TextString* bevt_1_ta_ph; BEC_2_5_4_LogicBool* bevt_2_ta_ph; BEC_2_4_6_TextString* bevt_3_ta_ph; BEC_2_4_6_TextString* bevt_4_ta_ph; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->beva_conPos = bevk_conPos;
beq->beva_conName = bevk_conName;
beq->beva_conArgs = bevk_conArgs;
beq->bevl_swc = nullptr;
beq->bevl_dimc = nullptr;
beq->bevt_0_ta_ph = nullptr;
beq->bevt_1_ta_ph = nullptr;
beq->bevt_2_ta_ph = nullptr;
beq->bevt_3_ta_ph = nullptr;
beq->bevt_4_ta_ph = nullptr;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(11);
beq->bevt_1_ta_ph = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString(2, {0x73,0x77}))));
beq->bevt_0_ta_ph = beq->beva_conName->bem_equals_1(beq->bevt_1_ta_ph);
if (beq->bevt_0_ta_ph->bevi_bool) {
beq->bevl_swc = static_cast<BEC_2_8_13_EmbeddedSwitchControl*>(((BEC_2_8_13_EmbeddedSwitchControl*) (new BEC_2_8_13_EmbeddedSwitchControl()))->bem_new_4(this, beq->beva_conPos, beq->beva_conName, beq->beva_conArgs));
return beq->bevl_swc;
} 
 else  {
beq->bevt_3_ta_ph = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString(3, {0x64,0x69,0x6D}))));
beq->bevt_2_ta_ph = beq->beva_conName->bem_equals_1(beq->bevt_3_ta_ph);
if (beq->bevt_2_ta_ph->bevi_bool) {
beq->bevl_dimc = static_cast<BEC_2_8_13_EmbeddedDimmerControl*>(((BEC_2_8_13_EmbeddedDimmerControl*) (new BEC_2_8_13_EmbeddedDimmerControl()))->bem_new_4(this, beq->beva_conPos, beq->beva_conName, beq->beva_conArgs));
return beq->bevl_dimc;
} 
 else  {
beq->bevt_4_ta_ph = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString(42, {0x55,0x6E,0x6B,0x6E,0x6F,0x77,0x6E,0x20,0x63,0x6F,0x6E,0x74,0x72,0x6F,0x6C,0x20,0x63,0x6F,0x6E,0x4E,0x61,0x6D,0x65,0x20,0x69,0x6E,0x20,0x53,0x77,0x69,0x74,0x63,0x68,0x41,0x6E,0x64,0x44,0x69,0x6D,0x6D,0x65,0x72}))));
beq->bevt_4_ta_ph->bem_print_0();
} 
} 
return nullptr;
}
BEC_2_6_6_SystemObject* BEC_2_8_15_EmbeddedSwitchAndDimmer::bemd_3(int32_t callId, BEC_2_6_6_SystemObject* bevd_0, BEC_2_6_6_SystemObject* bevd_1, BEC_2_6_6_SystemObject* bevd_2) {
switch (callId) {
case -638531368: return bem_buildControl_3(static_cast<BEC_2_4_3_MathInt*>(bevd_0), static_cast<BEC_2_4_6_TextString*>(bevd_1), static_cast<BEC_2_4_6_TextString*>(bevd_2));
}
return bevs_super::bemd_3(callId, bevd_0, bevd_1, bevd_2);
}
BEC_2_6_6_SystemObject* BEC_2_8_15_EmbeddedSwitchAndDimmer::bemc_create() {
return new BEC_2_8_15_EmbeddedSwitchAndDimmer();
}
void BEC_2_8_15_EmbeddedSwitchAndDimmer::bemc_setInitial(BEC_2_6_6_SystemObject* becc_inst) {
BEC_2_8_15_EmbeddedSwitchAndDimmer::bece_BEC_2_8_15_EmbeddedSwitchAndDimmer_bevs_inst = static_cast<BEC_2_8_15_EmbeddedSwitchAndDimmer*>(becc_inst);
}
BEC_2_6_6_SystemObject* BEC_2_8_15_EmbeddedSwitchAndDimmer::bemc_getInitial() {
return BEC_2_8_15_EmbeddedSwitchAndDimmer::bece_BEC_2_8_15_EmbeddedSwitchAndDimmer_bevs_inst;
}
void BEC_2_8_15_EmbeddedSwitchAndDimmer::bemg_doMark() {
bevs_super::bemg_doMark();
}
size_t BEC_2_8_15_EmbeddedSwitchAndDimmer::bemg_getSize() {
return sizeof(*this);
}
BETS_Object* BEC_2_8_15_EmbeddedSwitchAndDimmer::bemc_getType() {
return &BEC_2_8_15_EmbeddedSwitchAndDimmer::bece_BEC_2_8_15_EmbeddedSwitchAndDimmer_bevs_type;
}
BET_2_4_17_TextMultiByteIterator::BET_2_4_17_TextMultiByteIterator() {
std::vector<std::string> bevs_mtnames = {  };
bevs_fieldNames = {  };
}
BEC_2_6_6_SystemObject* BET_2_4_17_TextMultiByteIterator::bems_createInstance() {
return new BEC_2_4_17_TextMultiByteIterator();
}
void BET_2_4_17_TextMultiByteIterator::bemgt_doMark() {
BEC_2_6_6_SystemObject* bevsl_inst_ref = *bevs_inst_ref;
if (bevsl_inst_ref != nullptr && bevsl_inst_ref->bevg_gcMark != BECS_Runtime::bevg_currentGcMark) {
bevsl_inst_ref->bemg_doMark();
}
}
BEC_2_4_17_TextMultiByteIterator* BEC_2_4_17_TextMultiByteIterator::bece_BEC_2_4_17_TextMultiByteIterator_bevs_inst;

BET_2_4_17_TextMultiByteIterator BEC_2_4_17_TextMultiByteIterator::bece_BEC_2_4_17_TextMultiByteIterator_bevs_type;
BEC_2_6_6_SystemObject** BET_2_4_17_TextMultiByteIterator::bevs_inst_ref = (BEC_2_6_6_SystemObject**) &BEC_2_4_17_TextMultiByteIterator::bece_BEC_2_4_17_TextMultiByteIterator_bevs_inst;

BEC_2_4_12_TextByteIterator* BEC_2_4_17_TextMultiByteIterator::bem_new_1(BEC_2_4_6_TextString* bevk__str) {
struct bes { BEC_2_4_6_TextString* beva__str; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->beva__str = bevk__str;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(2);
bevp_bcount = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt())));
bevp_ival = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt())));
bevs_super::bem_new_1(beq->beva__str);
return this;
}
BEC_2_4_6_TextString* BEC_2_4_17_TextMultiByteIterator::bem_nextGet_0() {
struct bes { BEC_2_4_6_TextString* bevt_0_ta_ph; BEC_2_4_6_TextString* bevt_1_ta_ph; BEC_2_4_3_MathInt* bevt_2_ta_ph; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->bevt_0_ta_ph = nullptr;
beq->bevt_1_ta_ph = nullptr;
beq->bevt_2_ta_ph = nullptr;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(4);
beq->bevt_2_ta_ph = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(5))));
beq->bevt_1_ta_ph = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString()))->bem_new_1(beq->bevt_2_ta_ph));
beq->bevt_0_ta_ph = bem_next_1(beq->bevt_1_ta_ph);
return beq->bevt_0_ta_ph;
}
BEC_2_4_6_TextString* BEC_2_4_17_TextMultiByteIterator::bem_next_1(BEC_2_4_6_TextString* bevk_buf) {
struct bes { BEC_2_4_6_TextString* beva_buf; BEC_2_5_4_LogicBool* bevt_0_ta_anchor; BEC_2_5_4_LogicBool* bevt_1_ta_ph; BEC_2_4_3_MathInt* bevt_2_ta_ph; BEC_2_5_4_LogicBool* bevt_3_ta_ph; BEC_2_4_3_MathInt* bevt_4_ta_ph; BEC_2_5_4_LogicBool* bevt_5_ta_ph; BEC_2_4_3_MathInt* bevt_6_ta_ph; BEC_2_5_4_LogicBool* bevt_7_ta_ph; BEC_2_4_3_MathInt* bevt_8_ta_ph; BEC_2_4_3_MathInt* bevt_9_ta_ph; BEC_2_4_3_MathInt* bevt_10_ta_ph; BEC_2_5_4_LogicBool* bevt_11_ta_ph; BEC_2_4_3_MathInt* bevt_12_ta_ph; BEC_2_4_3_MathInt* bevt_13_ta_ph; BEC_2_4_3_MathInt* bevt_14_ta_ph; BEC_2_5_4_LogicBool* bevt_15_ta_ph; BEC_2_4_3_MathInt* bevt_16_ta_ph; BEC_2_4_3_MathInt* bevt_17_ta_ph; BEC_2_4_3_MathInt* bevt_18_ta_ph; BEC_2_6_9_SystemException* bevt_19_ta_ph; BEC_2_4_6_TextString* bevt_20_ta_ph; BEC_2_5_4_LogicBool* bevt_21_ta_ph; BEC_2_4_3_MathInt* bevt_22_ta_ph; BEC_2_4_3_MathInt* bevt_23_ta_ph; BEC_2_4_3_MathInt* bevt_24_ta_ph; BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->beva_buf = bevk_buf;
beq->bevt_0_ta_anchor = nullptr;
beq->bevt_1_ta_ph = nullptr;
beq->bevt_2_ta_ph = nullptr;
beq->bevt_3_ta_ph = nullptr;
beq->bevt_4_ta_ph = nullptr;
beq->bevt_5_ta_ph = nullptr;
beq->bevt_6_ta_ph = nullptr;
beq->bevt_7_ta_ph = nullptr;
beq->bevt_8_ta_ph = nullptr;
beq->bevt_9_ta_ph = nullptr;
beq->bevt_10_ta_ph = nullptr;
beq->bevt_11_ta_ph = nullptr;
beq->bevt_12_ta_ph = nullptr;
beq->bevt_13_ta_ph = nullptr;
beq->bevt_14_ta_ph = nullptr;
beq->bevt_15_ta_ph = nullptr;
beq->bevt_16_ta_ph = nullptr;
beq->bevt_17_ta_ph = nullptr;
beq->bevt_18_ta_ph = nullptr;
beq->bevt_19_ta_ph = nullptr;
beq->bevt_20_ta_ph = nullptr;
beq->bevt_21_ta_ph = nullptr;
beq->bevt_22_ta_ph = nullptr;
beq->bevt_23_ta_ph = nullptr;
beq->bevt_24_ta_ph = nullptr;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(27);
beq->bevt_2_ta_ph = bevp_str->bem_sizeGet_0();
if (beq->bevt_2_ta_ph->bevi_int > bevp_pos->bevi_int) {
beq->bevt_1_ta_ph = BECS_Runtime::boolTrue;
 } else { 
beq->bevt_1_ta_ph = BECS_Runtime::boolFalse;
}
if (beq->bevt_1_ta_ph->bevi_bool) {
bevp_str->bem_getInt_2(bevp_pos, bevp_ival);
beq->bevt_4_ta_ph = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(0))));
if (bevp_ival->bevi_int >= beq->bevt_4_ta_ph->bevi_int) {
beq->bevt_3_ta_ph = BECS_Runtime::boolTrue;
 } else { 
beq->bevt_3_ta_ph = BECS_Runtime::boolFalse;
}
if (beq->bevt_3_ta_ph->bevi_bool) {
beq->bevt_6_ta_ph = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(127))));
if (bevp_ival->bevi_int <= beq->bevt_6_ta_ph->bevi_int) {
beq->bevt_5_ta_ph = BECS_Runtime::boolTrue;
 } else { 
beq->bevt_5_ta_ph = BECS_Runtime::boolFalse;
}
if (beq->bevt_5_ta_ph->bevi_bool) {
beq->bevt_0_ta_anchor = BECS_Runtime::boolTrue;
} 
 else  {
beq->bevt_0_ta_anchor = BECS_Runtime::boolFalse;
} 
} 
 else  {
beq->bevt_0_ta_anchor = BECS_Runtime::boolFalse;
} 
if (beq->bevt_0_ta_anchor->bevi_bool) {
bevp_bcount = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(1))));
} 
 else  {
beq->bevt_9_ta_ph = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(-32))));
beq->bevt_8_ta_ph = bevp_ival->bem_and_1(beq->bevt_9_ta_ph);
beq->bevt_10_ta_ph = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(-64))));
if (beq->bevt_8_ta_ph->bevi_int == beq->bevt_10_ta_ph->bevi_int) {
beq->bevt_7_ta_ph = BECS_Runtime::boolTrue;
 } else { 
beq->bevt_7_ta_ph = BECS_Runtime::boolFalse;
}
if (beq->bevt_7_ta_ph->bevi_bool) {
bevp_bcount = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(2))));
} 
 else  {
beq->bevt_13_ta_ph = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(-16))));
beq->bevt_12_ta_ph = bevp_ival->bem_and_1(beq->bevt_13_ta_ph);
beq->bevt_14_ta_ph = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(-32))));
if (beq->bevt_12_ta_ph->bevi_int == beq->bevt_14_ta_ph->bevi_int) {
beq->bevt_11_ta_ph = BECS_Runtime::boolTrue;
 } else { 
beq->bevt_11_ta_ph = BECS_Runtime::boolFalse;
}
if (beq->bevt_11_ta_ph->bevi_bool) {
bevp_bcount = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(3))));
} 
 else  {
beq->bevt_17_ta_ph = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(-8))));
beq->bevt_16_ta_ph = bevp_ival->bem_and_1(beq->bevt_17_ta_ph);
beq->bevt_18_ta_ph = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(-16))));
if (beq->bevt_16_ta_ph->bevi_int == beq->bevt_18_ta_ph->bevi_int) {
beq->bevt_15_ta_ph = BECS_Runtime::boolTrue;
 } else { 
beq->bevt_15_ta_ph = BECS_Runtime::boolFalse;
}
if (beq->bevt_15_ta_ph->bevi_bool) {
bevp_bcount = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(4))));
} 
 else  {
beq->bevt_20_ta_ph = static_cast<BEC_2_4_6_TextString*>(((BEC_2_4_6_TextString*) (new BEC_2_4_6_TextString(66, {0x4D,0x61,0x6C,0x66,0x6F,0x72,0x6D,0x65,0x64,0x20,0x73,0x74,0x72,0x69,0x6E,0x67,0x2C,0x20,0x75,0x74,0x66,0x2D,0x38,0x20,0x6D,0x75,0x6C,0x74,0x69,0x62,0x79,0x74,0x65,0x20,0x73,0x65,0x71,0x75,0x65,0x6E,0x63,0x65,0x20,0x69,0x73,0x20,0x67,0x72,0x65,0x61,0x74,0x65,0x72,0x20,0x74,0x68,0x61,0x6E,0x20,0x34,0x20,0x62,0x79,0x74,0x65,0x73}))));
beq->bevt_19_ta_ph = static_cast<BEC_2_6_9_SystemException*>(((BEC_2_6_9_SystemException*) (new BEC_2_6_9_SystemException()))->bem_new_1(beq->bevt_20_ta_ph));
throw BECS_ThrowBack(beq->bevt_19_ta_ph);
} 
} 
} 
} 
beq->bevt_22_ta_ph = beq->beva_buf->bem_sizeGet_0();
if (beq->bevt_22_ta_ph->bevi_int != bevp_bcount->bevi_int) {
beq->bevt_21_ta_ph = BECS_Runtime::boolTrue;
 } else { 
beq->bevt_21_ta_ph = BECS_Runtime::boolFalse;
}
if (beq->bevt_21_ta_ph->bevi_bool) {
beq->bevt_23_ta_ph = beq->beva_buf->bem_sizeGet_0();
beq->bevt_23_ta_ph->bevi_int = bevp_bcount->bevi_int;
} 
bevp_bcount->bevi_int += bevp_pos->bevi_int;
beq->bevt_24_ta_ph = static_cast<BEC_2_4_3_MathInt*>(((BEC_2_4_3_MathInt*) (new BEC_2_4_3_MathInt(0))));
beq->beva_buf->bem_copyValue_4(bevp_str, bevp_pos, bevp_bcount, beq->bevt_24_ta_ph);
bevp_pos->bevi_int = bevp_bcount->bevi_int;
} 
return beq->beva_buf;
}
BEC_2_4_17_TextMultiByteIterator* BEC_2_4_17_TextMultiByteIterator::bem_multiByteIteratorIteratorGet_0() {
struct bes {  BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(1);
return this;
}
BEC_2_6_6_SystemObject* BEC_2_4_17_TextMultiByteIterator::bem_iteratorGet_0() {
struct bes {  BEC_2_6_6_SystemObject* bevr_this;  };
BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
bes* beq = (bes*) bevs_myStack->bevs_hs;
beq->bevr_this = this;
BECS_StackFrame bevs_stackFrame(1);
return this;
}
BEC_2_6_6_SystemObject* BEC_2_4_17_TextMultiByteIterator::bemd_0(int32_t callId) {
switch (callId) {
case -1428269309: return bem_iteratorGet_0();
case -119099042: return bem_nextGet_0();
case 1944254253: return bem_multiByteIteratorIteratorGet_0();
}
return bevs_super::bemd_0(callId);
}
BEC_2_6_6_SystemObject* BEC_2_4_17_TextMultiByteIterator::bemd_1(int32_t callId, BEC_2_6_6_SystemObject* bevd_0) {
switch (callId) {
case -1793507420: return bem_next_1(static_cast<BEC_2_4_6_TextString*>(bevd_0));
case 1899676304: return bem_new_1(static_cast<BEC_2_4_6_TextString*>(bevd_0));
}
return bevs_super::bemd_1(callId, bevd_0);
}
BEC_2_6_6_SystemObject* BEC_2_4_17_TextMultiByteIterator::bemc_create() {
return new BEC_2_4_17_TextMultiByteIterator();
}
void BEC_2_4_17_TextMultiByteIterator::bemc_setInitial(BEC_2_6_6_SystemObject* becc_inst) {
BEC_2_4_17_TextMultiByteIterator::bece_BEC_2_4_17_TextMultiByteIterator_bevs_inst = static_cast<BEC_2_4_17_TextMultiByteIterator*>(becc_inst);
}
BEC_2_6_6_SystemObject* BEC_2_4_17_TextMultiByteIterator::bemc_getInitial() {
return BEC_2_4_17_TextMultiByteIterator::bece_BEC_2_4_17_TextMultiByteIterator_bevs_inst;
}
void BEC_2_4_17_TextMultiByteIterator::bemg_doMark() {
bevs_super::bemg_doMark();
if (bevp_bcount != nullptr && bevp_bcount->bevg_gcMark != BECS_Runtime::bevg_currentGcMark) {
bevp_bcount->bemg_doMark();
}
if (bevp_ival != nullptr && bevp_ival->bevg_gcMark != BECS_Runtime::bevg_currentGcMark) {
bevp_ival->bemg_doMark();
}
}
size_t BEC_2_4_17_TextMultiByteIterator::bemg_getSize() {
return sizeof(*this);
}
BETS_Object* BEC_2_4_17_TextMultiByteIterator::bemc_getType() {
return &BEC_2_4_17_TextMultiByteIterator::bece_BEC_2_4_17_TextMultiByteIterator_bevs_type;
}
BET_2_6_16_SystemMethodNotDefined::BET_2_6_16_SystemMethodNotDefined() {
std::vector<std::string> bevs_mtnames = {  };
bevs_fieldNames = {  };
}
BEC_2_6_6_SystemObject* BET_2_6_16_SystemMethodNotDefined::bems_createInstance() {
return new BEC_2_6_16_SystemMethodNotDefined();
}
void BET_2_6_16_SystemMethodNotDefined::bemgt_doMark() {
BEC_2_6_6_SystemObject* bevsl_inst_ref = *bevs_inst_ref;
if (bevsl_inst_ref != nullptr && bevsl_inst_ref->bevg_gcMark != BECS_Runtime::bevg_currentGcMark) {
bevsl_inst_ref->bemg_doMark();
}
}
BEC_2_6_16_SystemMethodNotDefined* BEC_2_6_16_SystemMethodNotDefined::bece_BEC_2_6_16_SystemMethodNotDefined_bevs_inst;

BET_2_6_16_SystemMethodNotDefined BEC_2_6_16_SystemMethodNotDefined::bece_BEC_2_6_16_SystemMethodNotDefined_bevs_type;
BEC_2_6_6_SystemObject** BET_2_6_16_SystemMethodNotDefined::bevs_inst_ref = (BEC_2_6_6_SystemObject**) &BEC_2_6_16_SystemMethodNotDefined::bece_BEC_2_6_16_SystemMethodNotDefined_bevs_inst;

BEC_2_6_6_SystemObject* BEC_2_6_16_SystemMethodNotDefined::bemc_create() {
return new BEC_2_6_16_SystemMethodNotDefined();
}
void BEC_2_6_16_SystemMethodNotDefined::bemc_setInitial(BEC_2_6_6_SystemObject* becc_inst) {
BEC_2_6_16_SystemMethodNotDefined::bece_BEC_2_6_16_SystemMethodNotDefined_bevs_inst = static_cast<BEC_2_6_16_SystemMethodNotDefined*>(becc_inst);
}
BEC_2_6_6_SystemObject* BEC_2_6_16_SystemMethodNotDefined::bemc_getInitial() {
return BEC_2_6_16_SystemMethodNotDefined::bece_BEC_2_6_16_SystemMethodNotDefined_bevs_inst;
}
void BEC_2_6_16_SystemMethodNotDefined::bemg_doMark() {
bevs_super::bemg_doMark();
}
size_t BEC_2_6_16_SystemMethodNotDefined::bemg_getSize() {
return sizeof(*this);
}
BETS_Object* BEC_2_6_16_SystemMethodNotDefined::bemc_getType() {
return &BEC_2_6_16_SystemMethodNotDefined::bece_BEC_2_6_16_SystemMethodNotDefined_bevs_type;
}
BET_2_6_19_SystemInvocationException::BET_2_6_19_SystemInvocationException() {
std::vector<std::string> bevs_mtnames = {  };
bevs_fieldNames = {  };
}
BEC_2_6_6_SystemObject* BET_2_6_19_SystemInvocationException::bems_createInstance() {
return new BEC_2_6_19_SystemInvocationException();
}
void BET_2_6_19_SystemInvocationException::bemgt_doMark() {
BEC_2_6_6_SystemObject* bevsl_inst_ref = *bevs_inst_ref;
if (bevsl_inst_ref != nullptr && bevsl_inst_ref->bevg_gcMark != BECS_Runtime::bevg_currentGcMark) {
bevsl_inst_ref->bemg_doMark();
}
}
BEC_2_6_19_SystemInvocationException* BEC_2_6_19_SystemInvocationException::bece_BEC_2_6_19_SystemInvocationException_bevs_inst;

BET_2_6_19_SystemInvocationException BEC_2_6_19_SystemInvocationException::bece_BEC_2_6_19_SystemInvocationException_bevs_type;
BEC_2_6_6_SystemObject** BET_2_6_19_SystemInvocationException::bevs_inst_ref = (BEC_2_6_6_SystemObject**) &BEC_2_6_19_SystemInvocationException::bece_BEC_2_6_19_SystemInvocationException_bevs_inst;

BEC_2_6_6_SystemObject* BEC_2_6_19_SystemInvocationException::bemc_create() {
return new BEC_2_6_19_SystemInvocationException();
}
void BEC_2_6_19_SystemInvocationException::bemc_setInitial(BEC_2_6_6_SystemObject* becc_inst) {
BEC_2_6_19_SystemInvocationException::bece_BEC_2_6_19_SystemInvocationException_bevs_inst = static_cast<BEC_2_6_19_SystemInvocationException*>(becc_inst);
}
BEC_2_6_6_SystemObject* BEC_2_6_19_SystemInvocationException::bemc_getInitial() {
return BEC_2_6_19_SystemInvocationException::bece_BEC_2_6_19_SystemInvocationException_bevs_inst;
}
void BEC_2_6_19_SystemInvocationException::bemg_doMark() {
bevs_super::bemg_doMark();
}
size_t BEC_2_6_19_SystemInvocationException::bemg_getSize() {
return sizeof(*this);
}
BETS_Object* BEC_2_6_19_SystemInvocationException::bemc_getType() {
return &BEC_2_6_19_SystemInvocationException::bece_BEC_2_6_19_SystemInvocationException_bevs_type;
}
void BEL_Base::init() {
if (BECS_Runtime::isInitted) { return; }
BECS_Runtime::init();
BECS_Runtime::initializer->bem_notNullInitConstruct_1(new BEC_2_8_3_EmbeddedApp());
BECS_Runtime::typeRefs["Embedded:App"] = static_cast<BETS_Object*>   (&BEC_2_8_3_EmbeddedApp::bece_BEC_2_8_3_EmbeddedApp_bevs_type);
BEC_2_8_3_EmbeddedApp::bece_BEC_2_8_3_EmbeddedApp_bevs_type.bevs_parentType = &BEC_2_6_6_SystemObject::bece_BEC_2_6_6_SystemObject_bevs_type;
BECS_Runtime::initializer->bem_notNullInitConstruct_1(new BEC_2_8_4_EmbeddedWifi());
BECS_Runtime::typeRefs["Embedded:Wifi"] = static_cast<BETS_Object*>   (&BEC_2_8_4_EmbeddedWifi::bece_BEC_2_8_4_EmbeddedWifi_bevs_type);
BEC_2_8_4_EmbeddedWifi::bece_BEC_2_8_4_EmbeddedWifi_bevs_type.bevs_parentType = &BEC_2_6_6_SystemObject::bece_BEC_2_6_6_SystemObject_bevs_type;
BECS_Runtime::initializer->bem_notNullInitConstruct_1(new BEC_2_4_4_MathInts());
BECS_Runtime::typeRefs["Math:Ints"] = static_cast<BETS_Object*>   (&BEC_2_4_4_MathInts::bece_BEC_2_4_4_MathInts_bevs_type);
BEC_2_4_4_MathInts::bece_BEC_2_4_4_MathInts_bevs_type.bevs_parentType = &BEC_2_6_6_SystemObject::bece_BEC_2_6_6_SystemObject_bevs_type;
BECS_Runtime::initializer->bem_notNullInitConstruct_1(new BEC_2_4_7_TextStrings());
BECS_Runtime::typeRefs["Text:Strings"] = static_cast<BETS_Object*>   (&BEC_2_4_7_TextStrings::bece_BEC_2_4_7_TextStrings_bevs_type);
BEC_2_4_7_TextStrings::bece_BEC_2_4_7_TextStrings_bevs_type.bevs_parentType = &BEC_2_6_6_SystemObject::bece_BEC_2_6_6_SystemObject_bevs_type;
BECS_Runtime::initializer->bem_notNullInitConstruct_1(new BEC_2_5_5_LogicBools());
BECS_Runtime::typeRefs["Logic:Bools"] = static_cast<BETS_Object*>   (&BEC_2_5_5_LogicBools::bece_BEC_2_5_5_LogicBools_bevs_type);
BEC_2_5_5_LogicBools::bece_BEC_2_5_5_LogicBools_bevs_type.bevs_parentType = &BEC_2_6_6_SystemObject::bece_BEC_2_6_6_SystemObject_bevs_type;
BECS_Runtime::initializer->bem_notNullInitConstruct_1(new BEC_2_6_3_EncodeHex());
BECS_Runtime::typeRefs["Encode:Hex"] = static_cast<BETS_Object*>   (&BEC_2_6_3_EncodeHex::bece_BEC_2_6_3_EncodeHex_bevs_type);
BEC_2_6_3_EncodeHex::bece_BEC_2_6_3_EncodeHex_bevs_type.bevs_parentType = &BEC_2_6_6_SystemObject::bece_BEC_2_6_6_SystemObject_bevs_type;
BECS_Runtime::initializer->bem_notNullInitConstruct_1(new BEC_2_6_3_EncodeUrl());
BECS_Runtime::typeRefs["Encode:Url"] = static_cast<BETS_Object*>   (&BEC_2_6_3_EncodeUrl::bece_BEC_2_6_3_EncodeUrl_bevs_type);
BEC_2_6_3_EncodeUrl::bece_BEC_2_6_3_EncodeUrl_bevs_type.bevs_parentType = &BEC_2_6_6_SystemObject::bece_BEC_2_6_6_SystemObject_bevs_type;
BECS_Runtime::initializer->bem_notNullInitConstruct_1(new BEC_2_9_5_ContainerLists());
BECS_Runtime::typeRefs["Container:Lists"] = static_cast<BETS_Object*>   (&BEC_2_9_5_ContainerLists::bece_BEC_2_9_5_ContainerLists_bevs_type);
BEC_2_9_5_ContainerLists::bece_BEC_2_9_5_ContainerLists_bevs_type.bevs_parentType = &BEC_2_6_6_SystemObject::bece_BEC_2_6_6_SystemObject_bevs_type;
BECS_Runtime::initializer->bem_notNullInitConstruct_1(new BEC_2_6_6_SystemRandom());
BECS_Runtime::typeRefs["System:Random"] = static_cast<BETS_Object*>   (&BEC_2_6_6_SystemRandom::bece_BEC_2_6_6_SystemRandom_bevs_type);
BEC_2_6_6_SystemRandom::bece_BEC_2_6_6_SystemRandom_bevs_type.bevs_parentType = &BEC_2_6_6_SystemObject::bece_BEC_2_6_6_SystemObject_bevs_type;
BECS_Runtime::initializer->bem_notNullInitConstruct_1(new BEC_2_6_5_SystemTypes());
BECS_Runtime::typeRefs["System:Types"] = static_cast<BETS_Object*>   (&BEC_2_6_5_SystemTypes::bece_BEC_2_6_5_SystemTypes_bevs_type);
BEC_2_6_5_SystemTypes::bece_BEC_2_6_5_SystemTypes_bevs_type.bevs_parentType = &BEC_2_6_6_SystemObject::bece_BEC_2_6_6_SystemObject_bevs_type;
BECS_Runtime::initializer->bem_notNullInitDefault_1(new BEC_2_8_3_EmbeddedApp());
BECS_Runtime::initializer->bem_notNullInitDefault_1(new BEC_2_8_4_EmbeddedWifi());
BECS_Runtime::initializer->bem_notNullInitDefault_1(new BEC_2_4_4_MathInts());
BECS_Runtime::initializer->bem_notNullInitDefault_1(new BEC_2_4_7_TextStrings());
BECS_Runtime::initializer->bem_notNullInitDefault_1(new BEC_2_5_5_LogicBools());
BECS_Runtime::initializer->bem_notNullInitDefault_1(new BEC_2_6_3_EncodeHex());
BECS_Runtime::initializer->bem_notNullInitDefault_1(new BEC_2_6_3_EncodeUrl());
BECS_Runtime::initializer->bem_notNullInitDefault_1(new BEC_2_9_5_ContainerLists());
BECS_Runtime::initializer->bem_notNullInitDefault_1(new BEC_2_6_6_SystemRandom());
BECS_Runtime::initializer->bem_notNullInitDefault_1(new BEC_2_6_5_SystemTypes());
}
}
int bems_relocMain(int argc, char **argv) {
be::BECS_Runtime::platformName = std::string("linux");
be::BECS_Runtime::argc = argc;
be::BECS_Runtime::argv = argv;
be::BECS_Runtime::bemg_beginThread();
be::BEL_Base::init();
be::BEC_2_8_15_EmbeddedSwitchAndDimmer* mc = new be::BEC_2_8_15_EmbeddedSwitchAndDimmer();
be::BECS_Runtime::maino = mc;
mc->bem_new_0();
mc->bem_main_0();
return 0;
}
