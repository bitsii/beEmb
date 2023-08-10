// CONFIGURATION OPTIONS HERE
// pick one set of BESPEC_SW and BESPEC_CON to correspond to your device
// and configtype/pin use
// ard/BEH_4_Base.hpp secion is regenerated from system/cc/be/BEAR_Conf.hpp during bebuild, so
// keep this section in sync between both files
// BESPEC_SW and BESPEC_CON can also be overridden on the device later
// via commands (suggest starting with "supergeneric" options below)
//
// SW - name (type) and version of the device.  Typename 10 char max ssid rules (no spaces)
// swconfver.DeviceTypeName.DeviceVersion
//
//#define BESPEC_SW "0.GEN.22"  //supergeneric
#define BESPEC_SW "0.N.26"  //nodemcu
//#define BESPEC_SW "0.NU.26"  //nodemcu unk name
//#define BESPEC_SW  "0.DL.20" //dollatek 2mb 1led
//#define BESPEC_SW "0.AP2.29" //Athom Plug V2 US THE REAL ONE
//#define BESPEC_SW "0.NT.28"  //nodemcu like athsw
//#define BESPEC_SW "0.NTU.28"  //nodemcu like athsw but unk name
//
// CON - definition of device's controls
// ctlconfver.control.ctlconf,args.control.ctlconf,args
//
//#define BESPEC_CON "" //supergeneric
#define BESPEC_CON "0.sw.16.dim.2" //nodemcu
//#define BESPEC_CON "0.sw.16"  //dollatek - one sw on 16
//#define BESPEC_CON "0.dim.16"  //dollatek - one dim on 16
//#define BESPEC_CON "0.sw.12,1.bu.5,0,30,0,30000"  //12 is switch, 13 is led, 5 button - athom plug v2 us - esp8266ex 2mb THE REAL ONE sic look unnecessary led does on it's own
//#define BESPEC_CON "0.sw.12,1" //Athom Plug V2 US - sw on 12, 13 is led, default - same for martin jerry
//#define BESPEC_CON "0.sw.12.sw.13"  //12 is switch, 13 is led - athom plug v2 us - esp8266ex 2mb
//#define BESPEC_CON "0.sw.2.bu.5,0,0,0,0" //nodemcu like athsw
//#define BESPEC_CON "0.sw.2.bu.5,0,30,0,10000.sic.16,0,0" //nodemcu like athsw
//#define BESPEC_CON "0.sw.2.sic.16,0,0" //nodemcu like athsw
//
//pinposes //16, 2 nodemcu - Athom 16A US 13 LED 14 RELAY, SONOFF BASIC R2 13 LED 12 RELAY, 16 for dollatek 8285
//
// Is Reset by Pin supported - when not on network can use pin to reset device (clear all config, prep for
// re-setup).  For most (and secure) devices a physical option (button) is instead recommended, but for
// things like bulbs/less sensitive devices w/out another reasonable choice, it should be enabled.  device
// waits a bit for the wifi to come up when configured  to avoid power losses leading to entering this mode
//
#define BE_RESETBYPIN "on" //enabled
//#define BE_RESETBYPIN "off" //disabled
//
// tcpconsole - if you want to enable a debugish tcp port on the device (all be prints will be echoed there)
// turn BE_TCPCONSOLE on, otherwise leave off.  only for development, really only useful if serial connection
// not available.  You can telnet to the device's ip port 32259 to see the messages.  output only, no input
//
#define BE_TCPCONSOLE "on" //enabled
//#define BE_TCPCONSOLE "off" //disabled
//
// END OF CONFIGURATION OPTIONS
//
#define BEDCC_SGC
#define BEDCC_NORTTI
#define BEAR_ESP8266
#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <ESP8266httpUpdate.h>
#include <EEPROM.h>
#include <Hash.h>
//for Mqtt.be
//in BEAR_Imports.hpp
#include <MQTT.h>
#include <iostream>
#include <string>
#include <vector>
#include <cstdint>
//started 500 2 500 16
//esp32 2000, esp8266 500
#define BEDCC_GCAPERGC 200
//how many marks before a sweep
#define BEDCC_GCMPERS 1
#define BED_GCNOREUSE
//sync count sometimes
//#define BEDCC_GCSHASYNC 8192
#define BEDCC_GCSHASYNC 100
//sync do gc moretimes 2 4 8 16 32 64 128
#define BEDCC_GCSSCHECK 16
#define BEDCC_GCRWM 30000
//#define BEDCC_GCRWM 10
//size for heap stack
#define BEDCC_GCHSS 500
//#define BED_GCSTATS
#include "BED_4_Base.hpp"
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

class BECS_Ids {
    public:
    static std::unordered_map<std::string, int32_t> callIds;
    static std::unordered_map<int32_t, std::string> idCalls;
    
};

class BECS_Lib {
    public:
    static void putCallId(std::string name, int32_t iid);
    
    static int32_t getCallId(std::string name);
    
    static void putNlcSourceMap(std::string clname, std::vector<int32_t>& vals);
    
    static void putNlecSourceMap(std::string clname, std::vector<int32_t>& vals);
};

class BECS_FrameStack {
  public:
  uint_fast32_t bevs_allocsSinceGc = 0;
  BECS_Object* bevs_lastInst = nullptr;//last inst, for appending new allocs
  BECS_Object* bevs_nextReuse = nullptr;
  uint_fast16_t bevg_stackGcState = 0;
  //new for heap stack
  BECS_Object** bevs_ohs;
  BECS_Object** bevs_hs;
};

class BECS_Runtime {
    public:
    static bool isInitted;
    
    static BEC_2_5_4_LogicBool* boolTrue;
    static BEC_2_5_4_LogicBool* boolFalse;
    
    static std::unordered_map<std::string, BETS_Object*> typeRefs;
    
    //for setting up initial instances
    static BEC_2_6_11_SystemInitializer* initializer;
    
    //the main instance
    static BEC_2_6_6_SystemObject* maino;
    
    static std::string platformName;
    
    static int argc;
    static char** argv;
    
    static std::unordered_map<std::string, std::vector<int32_t>> smnlcs;
    static std::unordered_map<std::string, std::vector<int32_t>> smnlecs;

#ifdef BEDCC_PT
    static thread_local BECS_FrameStack bevs_currentStack;
#endif

#ifndef BEDCC_PT
    static BECS_FrameStack bevs_currentStack;
#endif

    static uint_fast16_t bevg_currentGcMark;
#ifdef BEDCC_PT
    static std::atomic<uint_fast16_t> bevg_gcState;
      //0 don't do gc now, 1 do gc now
    static std::atomic<uint_fast32_t> bevg_sharedAllocsSinceGc;
#endif
    
#ifdef BEDCC_PT    
    static std::map<std::thread::id, BECS_FrameStack*> bevg_frameStacks;
#endif
    
    static BECS_FrameStack bevg_oldInstsStack;

#ifdef BEDCC_PT    
    static std::recursive_mutex bevs_initLock;
#endif

#ifdef BEDCC_PT   
    static std::mutex bevg_gcLock;
    static std::condition_variable bevg_gcWaiter;
#endif
    
    static uint_fast64_t bevg_countGcs;
    static uint_fast64_t bevg_countSweeps;
    static uint_fast64_t bevg_countDeletes;
    static uint_fast64_t bevg_countRecycles;
    static uint_fast64_t bevg_countAllocs;
    static uint_fast64_t bevg_maxHs;
    
    static void init();
    
    static void doGc();
    
    static int32_t getNlcForNlec(std::string clname, int32_t val);
    
    static void bemg_markAll();
    static void bemg_markStack(BECS_FrameStack* bevs_myStack);
    static void bemg_sweep();
    static void bemg_sweepStack(BECS_FrameStack* bevs_myStack);
    static void bemg_zero();
    static void bemg_zeroStack(BECS_FrameStack* bevs_myStack);
    
    static void bemg_addMyFrameStack();
    static void bemg_deleteMyFrameStack();
    
    static void bemg_beginThread();
    static void bemg_endThread();
    
    static void bemg_enterBlocking();
    static void bemg_exitBlocking();
    
    static void bemg_checkDoGc();
    static bool bemg_readyForGc();
    
};

class BECS_StackFrame {
  public:
  size_t bevs_numVars;
  
  inline BECS_StackFrame(size_t beva_numVars) {
    bevs_numVars = beva_numVars;
    BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
    bevs_myStack->bevs_hs += bevs_numVars;
  }
  
  inline ~BECS_StackFrame() {
    BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
    bevs_myStack->bevs_hs -= bevs_numVars;
  }
  
};

class BECS_Object {
  public:
    uint_fast16_t bevg_gcMark = 0;
    BECS_Object* bevg_priorInst = nullptr;
    
    void* operator new(size_t size) {

#ifdef BEDCC_SGC  

      BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;   
      bevs_myStack->bevs_allocsSinceGc++;

      //should I do gc
      bool doGc = false;

#ifdef BEDCC_PT
      //sync count sometimes
      if (bevs_myStack->bevs_allocsSinceGc % BEDCC_GCSHASYNC == 0) {
        bevs_myStack->bevs_allocsSinceGc = BECS_Runtime::bevg_sharedAllocsSinceGc += BEDCC_GCSHASYNC;
      }
#endif

      //allocsPerGc 0-4,294,967,295 :: 10000000 >>6000000<< OKish bld, 1000000 extec, diff is 1 0
      if (bevs_myStack->bevs_allocsSinceGc > BEDCC_GCAPERGC) {
#ifdef BEDCC_PT
        BECS_Runtime::bevg_gcState.store(1, std::memory_order_release);
#endif
        doGc = true;
      }

#ifdef BEDCC_PT      
      //sync do gc moretimes 2 4 8 16 32 64 128
      if (bevs_myStack->bevs_allocsSinceGc % BEDCC_GCSSCHECK == 0 && BECS_Runtime::bevg_gcState.load(std::memory_order_acquire) == 1) {
        doGc = true;
      }
#endif

      //https://www.arangodb.com/2015/02/comparing-atomic-mutex-rwlocks/
      //#include <atomic>
      //std::atomic<uint64_t> atomic_uint;
      //atomic_uint.store(i, std::memory_order_release);
      //current = atomic_uint.load(std::memory_order_acquire);

      if (doGc) {
        BECS_Runtime::bemg_checkDoGc();
      }
      
      uint_fast16_t bevg_currentGcMark = BECS_Runtime::bevg_currentGcMark;
      
      BECS_Object* bevs_lastInst = bevs_myStack->bevs_nextReuse;

#ifndef BED_GCNOREUSE      
      if (bevs_lastInst != nullptr) {
        BECS_Object* bevs_currInst = bevs_lastInst->bevg_priorInst;
        int tries = 0;
        while (tries < 2 && bevs_currInst != nullptr && bevs_currInst->bevg_priorInst != nullptr) {
          tries++;
          if (bevs_currInst->bevg_gcMark != bevg_currentGcMark) {
            bevs_lastInst->bevg_priorInst = bevs_currInst->bevg_priorInst;
            if (bevs_currInst->bemg_getSize() == size) {
#ifdef BED_GCSTATS
              BECS_Runtime::bevg_countRecycles++;
#endif
              bevs_currInst->~BECS_Object();
              bevs_myStack->bevs_nextReuse = bevs_lastInst;
              return bevs_currInst;
            } else {
              delete bevs_currInst;
              bevs_currInst = bevs_lastInst->bevg_priorInst; 
            }
          } else {
            bevs_lastInst = bevs_currInst;
            bevs_currInst = bevs_currInst->bevg_priorInst;
          }
        }
        bevs_myStack->bevs_nextReuse = bevs_lastInst;
      }
#endif
#ifdef BED_GCSTATS
      BECS_Runtime::bevg_countAllocs++;
#endif
      return malloc(size);
#endif
    }
    
    void operator delete(void* theinst, size_t size) {
#ifdef BED_GCSTATS
      BECS_Runtime::bevg_countDeletes++;
#endif
      free(theinst);
    }
    BECS_Object() {
      
#ifdef BEDCC_SGC
      BEC_2_6_6_SystemObject* thisoo = (BEC_2_6_6_SystemObject*) this;

      struct bes {  BEC_2_6_6_SystemObject* bevr_this;  };
      BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
      bes* beq = (bes*) bevs_myStack->bevs_hs;
      beq->bevr_this = thisoo;
      BECS_StackFrame bevs_stackFrame(1);
#endif

#ifdef BEDCC_SGC
      bevg_gcMark = 0;
      this->bevg_priorInst = bevs_myStack->bevs_lastInst;
      bevs_myStack->bevs_lastInst = this;
#endif
      
    }
    virtual ~BECS_Object() = default;
    virtual BEC_2_4_6_TextString* bemc_clnames();
    virtual BEC_2_4_6_TextString* bemc_clfiles();
    virtual BEC_2_6_6_SystemObject* bemc_create();
    virtual void bemc_setInitial(BEC_2_6_6_SystemObject* becc_inst);
    virtual BEC_2_6_6_SystemObject* bemc_getInitial();
    virtual void bemg_doMark();
    virtual size_t bemg_getSize();
    //bemds, to 7 then x
    virtual BEC_2_6_6_SystemObject* bemd_0(int32_t callId);
    virtual BEC_2_6_6_SystemObject* bemd_1(int32_t callId, BEC_2_6_6_SystemObject* bevd_0);
    virtual BEC_2_6_6_SystemObject* bemd_2(int32_t callId, BEC_2_6_6_SystemObject* bevd_0, BEC_2_6_6_SystemObject* bevd_1);
    virtual BEC_2_6_6_SystemObject* bemd_3(int32_t callId, BEC_2_6_6_SystemObject* bevd_0, BEC_2_6_6_SystemObject* bevd_1, BEC_2_6_6_SystemObject* bevd_2);
    virtual BEC_2_6_6_SystemObject* bemd_4(int32_t callId, BEC_2_6_6_SystemObject* bevd_0, BEC_2_6_6_SystemObject* bevd_1, BEC_2_6_6_SystemObject* bevd_2, BEC_2_6_6_SystemObject* bevd_3);
    virtual BEC_2_6_6_SystemObject* bemd_5(int32_t callId, BEC_2_6_6_SystemObject* bevd_0, BEC_2_6_6_SystemObject* bevd_1, BEC_2_6_6_SystemObject* bevd_2, BEC_2_6_6_SystemObject* bevd_3, BEC_2_6_6_SystemObject* bevd_4);
    virtual BEC_2_6_6_SystemObject* bemd_6(int32_t callId, BEC_2_6_6_SystemObject* bevd_0, BEC_2_6_6_SystemObject* bevd_1, BEC_2_6_6_SystemObject* bevd_2, BEC_2_6_6_SystemObject* bevd_3, BEC_2_6_6_SystemObject* bevd_4, BEC_2_6_6_SystemObject* bevd_5);
    virtual BEC_2_6_6_SystemObject* bemd_7(int32_t callId, BEC_2_6_6_SystemObject* bevd_0, BEC_2_6_6_SystemObject* bevd_1, BEC_2_6_6_SystemObject* bevd_2, BEC_2_6_6_SystemObject* bevd_3, BEC_2_6_6_SystemObject* bevd_4, BEC_2_6_6_SystemObject* bevd_5, BEC_2_6_6_SystemObject* bevd_6);

#ifdef BEDCC_SGC
    virtual BEC_2_6_6_SystemObject* bemd_x(int32_t callId, BEC_2_6_6_SystemObject* bevd_0, BEC_2_6_6_SystemObject* bevd_1, BEC_2_6_6_SystemObject* bevd_2, BEC_2_6_6_SystemObject* bevd_3, BEC_2_6_6_SystemObject* bevd_4, BEC_2_6_6_SystemObject* bevd_5, BEC_2_6_6_SystemObject* bevd_6, std::vector<BEC_2_6_6_SystemObject*> bevd_x);
#endif 

#ifdef BEDCC_SGC
  virtual BEC_2_6_6_SystemObject* bems_forwardCall(std::string mname, std::vector<BEC_2_6_6_SystemObject*> bevd_x, int32_t numargs);
#endif

#ifdef BEDCC_SGC
    virtual BEC_2_6_6_SystemObject* bems_methodNotDefined(int32_t callId, std::vector<BEC_2_6_6_SystemObject*> args);
#endif      

};

class BECS_ThrowBack {
public:
    BEC_2_6_6_SystemObject* wasThrown;
    BECS_ThrowBack();
    BECS_ThrowBack(BEC_2_6_6_SystemObject* thrown);
    static BEC_2_6_6_SystemObject* handleThrow(BECS_ThrowBack thrown);
};
        
class BETS_Object {
  public:
    BETS_Object* bevs_parentType;
    std::unordered_map<std::string, bool> bevs_methodNames;
    std::vector<std::string> bevs_fieldNames;
    virtual void bems_buildMethodNames(std::vector<std::string> names);
    virtual BEC_2_6_6_SystemObject* bems_createInstance();
    virtual void bemgt_doMark();
};


class BET_2_6_6_SystemObject : public BETS_Object {
public:
BET_2_6_6_SystemObject();
virtual BEC_2_6_6_SystemObject* bems_createInstance();
virtual void bemgt_doMark();
static BEC_2_6_6_SystemObject** bevs_inst_ref;
};
class BEC_2_6_6_SystemObject : public BECS_Object {
private:
typedef BECS_Object bevs_super;

public:
virtual BEC_2_6_6_SystemObject* bem_new_0();
virtual BEC_2_5_4_LogicBool* bem_undef_1(BEC_2_6_6_SystemObject* bevk_ref);
virtual BEC_2_5_4_LogicBool* bem_def_1(BEC_2_6_6_SystemObject* bevk_ref);
virtual BEC_2_6_6_SystemObject* bem_methodNotDefined_2(BEC_2_4_6_TextString* bevk_name, BEC_2_9_4_ContainerList* bevk_args);
virtual BEC_2_6_6_SystemObject* bem_forwardCall_2(BEC_2_4_6_TextString* bevk_name, BEC_2_9_4_ContainerList* bevk_args);
virtual BEC_2_6_6_SystemObject* bem_invoke_2(BEC_2_4_6_TextString* bevk_name, BEC_2_9_4_ContainerList* bevk_args);
virtual BEC_2_5_4_LogicBool* bem_can_2(BEC_2_4_6_TextString* bevk_name, BEC_2_4_3_MathInt* bevk_numargs);
virtual BEC_2_5_4_LogicBool* bem_equals_1(BEC_2_6_6_SystemObject* bevk_x);
virtual BEC_2_4_3_MathInt* bem_hashGet_0();
virtual BEC_2_5_4_LogicBool* bem_notEquals_1(BEC_2_6_6_SystemObject* bevk_x);
virtual BEC_2_4_6_TextString* bem_toString_0();
virtual BEC_2_6_6_SystemObject* bem_print_0();
virtual BEC_2_6_6_SystemObject* bem_copy_0();
virtual BEC_2_6_6_SystemObject* bem_copyTo_1(BEC_2_6_6_SystemObject* bevk_copy);
virtual BEC_2_6_6_SystemObject* bem_iteratorGet_0();
virtual BEC_2_6_6_SystemObject* bem_create_0();
virtual BEC_2_6_6_SystemObject* bemc_create();
static BEC_2_6_6_SystemObject* bece_BEC_2_6_6_SystemObject_bevs_inst;
virtual void bemc_setInitial(BEC_2_6_6_SystemObject* becc_inst);
virtual BEC_2_6_6_SystemObject* bemc_getInitial();
virtual void bemg_doMark();
virtual size_t bemg_getSize();
virtual BETS_Object* bemc_getType();
virtual ~BEC_2_6_6_SystemObject() = default;


#ifdef BEDCC_SGC
   virtual BEC_2_6_6_SystemObject* bems_forwardCall(std::string mname, std::vector<BEC_2_6_6_SystemObject*> bevd_x, int32_t numargs);
#endif 
  virtual BEC_2_6_6_SystemObject* bemd_0(int32_t callId);
virtual BEC_2_6_6_SystemObject* bemd_1(int32_t callId, BEC_2_6_6_SystemObject* bevd_0);
virtual BEC_2_6_6_SystemObject* bemd_2(int32_t callId, BEC_2_6_6_SystemObject* bevd_0, BEC_2_6_6_SystemObject* bevd_1);
static BET_2_6_6_SystemObject bece_BEC_2_6_6_SystemObject_bevs_type;
};

class BET_2_8_3_EmbeddedApp : public BETS_Object {
public:
BET_2_8_3_EmbeddedApp();
virtual BEC_2_6_6_SystemObject* bems_createInstance();
virtual void bemgt_doMark();
static BEC_2_6_6_SystemObject** bevs_inst_ref;
};
class BEC_2_8_3_EmbeddedApp : public BEC_2_6_6_SystemObject {
private:
typedef BEC_2_6_6_SystemObject bevs_super;

public:
BEC_2_6_6_SystemObject* bevp_plugin = nullptr;
BEC_2_4_3_MathInt* bevp_hlCount = nullptr;
BEC_2_4_3_MathInt* bevp_zero = nullptr;
virtual BEC_2_8_3_EmbeddedApp* bem_default_0();
virtual BEC_2_8_3_EmbeddedApp* bem_handleWeb_1(BEC_2_6_6_SystemObject* bevk_request);
virtual BEC_2_8_3_EmbeddedApp* bem_startLoop_0();
virtual BEC_2_8_3_EmbeddedApp* bem_handleLoop_0();
virtual BEC_2_8_3_EmbeddedApp* bem_delay_1(BEC_2_4_3_MathInt* bevk_millis);
virtual BEC_2_8_3_EmbeddedApp* bem_wdtFeed_0();
virtual BEC_2_8_3_EmbeddedApp* bem_wdtDisable_0();
virtual BEC_2_8_3_EmbeddedApp* bem_wdtEnable_1(BEC_2_4_3_MathInt* bevk_timeout);
virtual BEC_2_8_3_EmbeddedApp* bem_yield_0();
virtual BEC_2_4_3_MathInt* bem_uptime_0();
virtual BEC_2_4_3_MathInt* bem_uptime_1(BEC_2_4_3_MathInt* bevk_millis);
virtual BEC_2_8_3_EmbeddedApp* bem_pinModeOutput_1(BEC_2_4_3_MathInt* bevk_pin);
virtual BEC_2_8_3_EmbeddedApp* bem_analogWrite_2(BEC_2_4_3_MathInt* bevk_pin, BEC_2_4_3_MathInt* bevk_value);
virtual BEC_2_8_3_EmbeddedApp* bem_pinModeInputPullup_1(BEC_2_4_3_MathInt* bevk_pin);
virtual BEC_2_4_3_MathInt* bem_analogRead_2(BEC_2_4_3_MathInt* bevk_pin, BEC_2_4_3_MathInt* bevk_value);
virtual BEC_2_8_3_EmbeddedApp* bem_restart_0();
virtual BEC_2_4_3_MathInt* bem_strToInt_1(BEC_2_4_6_TextString* bevk_str);
virtual BEC_2_4_6_TextString* bem_intToStr_1(BEC_2_4_3_MathInt* bevk_int);
virtual BEC_2_8_3_EmbeddedApp* bem_maybeGc_0();
virtual BEC_2_6_6_SystemObject* bem_pluginGet_0();
virtual BEC_2_8_3_EmbeddedApp* bem_pluginSet_1(BEC_2_6_6_SystemObject* bevt_0_ta_SET);
virtual BEC_2_4_3_MathInt* bem_hlCountGet_0();
virtual BEC_2_8_3_EmbeddedApp* bem_hlCountSet_1(BEC_2_6_6_SystemObject* bevt_0_ta_SET);
virtual BEC_2_4_3_MathInt* bem_zeroGet_0();
virtual BEC_2_8_3_EmbeddedApp* bem_zeroSet_1(BEC_2_6_6_SystemObject* bevt_0_ta_SET);
virtual BEC_2_6_6_SystemObject* bemc_create();
static BEC_2_8_3_EmbeddedApp* bece_BEC_2_8_3_EmbeddedApp_bevs_inst;
virtual void bemc_setInitial(BEC_2_6_6_SystemObject* becc_inst);
virtual BEC_2_6_6_SystemObject* bemc_getInitial();
virtual void bemg_doMark();
virtual size_t bemg_getSize();
virtual BETS_Object* bemc_getType();
virtual ~BEC_2_8_3_EmbeddedApp() = default;
virtual BEC_2_6_6_SystemObject* bemd_0(int32_t callId);
virtual BEC_2_6_6_SystemObject* bemd_1(int32_t callId, BEC_2_6_6_SystemObject* bevd_0);
virtual BEC_2_6_6_SystemObject* bemd_2(int32_t callId, BEC_2_6_6_SystemObject* bevd_0, BEC_2_6_6_SystemObject* bevd_1);
static BET_2_8_3_EmbeddedApp bece_BEC_2_8_3_EmbeddedApp_bevs_type;
};

class BET_2_8_6_EmbeddedConfig : public BETS_Object {
public:
BET_2_8_6_EmbeddedConfig();
virtual BEC_2_6_6_SystemObject* bems_createInstance();
virtual void bemgt_doMark();
static BEC_2_6_6_SystemObject** bevs_inst_ref;
};
class BEC_2_8_6_EmbeddedConfig : public BEC_2_6_6_SystemObject {
private:
typedef BEC_2_6_6_SystemObject bevs_super;

public:
BEC_2_4_3_MathInt* bevp_eesize = nullptr;
BEC_2_4_3_MathInt* bevp_maxsz = nullptr;
BEC_2_9_4_ContainerList* bevp_names = nullptr;
BEC_2_9_4_ContainerList* bevp_values = nullptr;
BEC_2_5_4_LogicBool* bevp_changed = nullptr;
BEC_2_4_6_TextString* bevp_magic = nullptr;
BEC_2_4_3_MathInt* bevp_zero = nullptr;
BEC_2_4_3_MathInt* bevp_one = nullptr;
BEC_2_4_3_MathInt* bevp_es = nullptr;
BEC_2_4_6_TextString* bevp_ess = nullptr;
BEC_2_4_3_MathInt* bevp_gs = nullptr;
BEC_2_4_6_TextString* bevp_gss = nullptr;
BEC_2_4_3_MathInt* bevp_us = nullptr;
BEC_2_4_6_TextString* bevp_uss = nullptr;
BEC_2_4_3_MathInt* bevp_rs = nullptr;
BEC_2_4_6_TextString* bevp_rss = nullptr;
virtual BEC_2_6_6_SystemObject* bem_new_0();
virtual BEC_2_6_6_SystemObject* bem_getPos_1(BEC_2_4_6_TextString* bevk_name);
virtual BEC_2_4_6_TextString* bem_get_1(BEC_2_4_3_MathInt* bevk_pos);
virtual BEC_2_8_6_EmbeddedConfig* bem_put_2(BEC_2_4_3_MathInt* bevk_pos, BEC_2_4_6_TextString* bevk_value);
virtual BEC_2_8_6_EmbeddedConfig* bem_maybeSave_0();
virtual BEC_2_8_6_EmbeddedConfig* bem_load_0();
virtual BEC_2_4_3_MathInt* bem_epread_5(BEC_2_4_6_TextString* bevk_lbuf, BEC_2_4_3_MathInt* bevk_ps, BEC_2_4_3_MathInt* bevk_pe, BEC_2_4_3_MathInt* bevk_code, BEC_2_4_3_MathInt* bevk_rsize);
virtual BEC_2_8_6_EmbeddedConfig* bem_save_0();
virtual BEC_2_8_6_EmbeddedConfig* bem_epwrite_6(BEC_2_4_6_TextString* bevk_ws, BEC_2_4_3_MathInt* bevk_css, BEC_2_4_3_MathInt* bevk_ps, BEC_2_4_3_MathInt* bevk_pe, BEC_2_4_3_MathInt* bevk_code, BEC_2_5_4_LogicBool* bevk_noes);
virtual BEC_2_4_3_MathInt* bem_eesizeGet_0();
virtual BEC_2_8_6_EmbeddedConfig* bem_eesizeSet_1(BEC_2_6_6_SystemObject* bevt_0_ta_SET);
virtual BEC_2_4_3_MathInt* bem_maxszGet_0();
virtual BEC_2_8_6_EmbeddedConfig* bem_maxszSet_1(BEC_2_6_6_SystemObject* bevt_0_ta_SET);
virtual BEC_2_9_4_ContainerList* bem_namesGet_0();
virtual BEC_2_8_6_EmbeddedConfig* bem_namesSet_1(BEC_2_6_6_SystemObject* bevt_0_ta_SET);
virtual BEC_2_9_4_ContainerList* bem_valuesGet_0();
virtual BEC_2_8_6_EmbeddedConfig* bem_valuesSet_1(BEC_2_6_6_SystemObject* bevt_0_ta_SET);
virtual BEC_2_5_4_LogicBool* bem_changedGet_0();
virtual BEC_2_8_6_EmbeddedConfig* bem_changedSet_1(BEC_2_6_6_SystemObject* bevt_0_ta_SET);
virtual BEC_2_4_6_TextString* bem_magicGet_0();
virtual BEC_2_8_6_EmbeddedConfig* bem_magicSet_1(BEC_2_6_6_SystemObject* bevt_0_ta_SET);
virtual BEC_2_6_6_SystemObject* bemc_create();
static BEC_2_8_6_EmbeddedConfig* bece_BEC_2_8_6_EmbeddedConfig_bevs_inst;
virtual void bemc_setInitial(BEC_2_6_6_SystemObject* becc_inst);
virtual BEC_2_6_6_SystemObject* bemc_getInitial();
virtual void bemg_doMark();
virtual size_t bemg_getSize();
virtual BETS_Object* bemc_getType();
virtual ~BEC_2_8_6_EmbeddedConfig() = default;
virtual BEC_2_6_6_SystemObject* bemd_0(int32_t callId);
virtual BEC_2_6_6_SystemObject* bemd_1(int32_t callId, BEC_2_6_6_SystemObject* bevd_0);
virtual BEC_2_6_6_SystemObject* bemd_2(int32_t callId, BEC_2_6_6_SystemObject* bevd_0, BEC_2_6_6_SystemObject* bevd_1);
virtual BEC_2_6_6_SystemObject* bemd_5(int32_t callId, BEC_2_6_6_SystemObject* bevd_0, BEC_2_6_6_SystemObject* bevd_1, BEC_2_6_6_SystemObject* bevd_2, BEC_2_6_6_SystemObject* bevd_3, BEC_2_6_6_SystemObject* bevd_4);
virtual BEC_2_6_6_SystemObject* bemd_6(int32_t callId, BEC_2_6_6_SystemObject* bevd_0, BEC_2_6_6_SystemObject* bevd_1, BEC_2_6_6_SystemObject* bevd_2, BEC_2_6_6_SystemObject* bevd_3, BEC_2_6_6_SystemObject* bevd_4, BEC_2_6_6_SystemObject* bevd_5);
static BET_2_8_6_EmbeddedConfig bece_BEC_2_8_6_EmbeddedConfig_bevs_type;
};

class BET_2_8_4_EmbeddedWifi : public BETS_Object {
public:
BET_2_8_4_EmbeddedWifi();
virtual BEC_2_6_6_SystemObject* bems_createInstance();
virtual void bemgt_doMark();
static BEC_2_6_6_SystemObject** bevs_inst_ref;
};
class BEC_2_8_4_EmbeddedWifi : public BEC_2_6_6_SystemObject {
private:
typedef BEC_2_6_6_SystemObject bevs_super;

public:
BEC_2_4_6_TextString* bevp_mode = nullptr;
BEC_2_4_6_TextString* bevp_ssid = nullptr;
BEC_2_4_6_TextString* bevp_password = nullptr;
BEC_2_5_4_LogicBool* bevp_up = nullptr;
BEC_2_4_6_TextString* bevp_localIP = nullptr;
virtual BEC_2_8_4_EmbeddedWifi* bem_default_0();
virtual BEC_2_8_4_EmbeddedWifi* bem_clear_0();
virtual BEC_2_8_4_EmbeddedWifi* bem_clearAll_0();
virtual BEC_2_8_4_EmbeddedWifi* bem_new_2(BEC_2_4_6_TextString* bevk__ssid, BEC_2_4_6_TextString* bevk__password);
virtual BEC_2_4_6_TextString* bem_macAddressGet_0();
virtual BEC_2_9_4_ContainerList* bem_scanNetworks_0();
virtual BEC_2_8_4_EmbeddedWifi* bem_startAp_0();
virtual BEC_2_8_4_EmbeddedWifi* bem_start_0();
virtual BEC_2_5_4_LogicBool* bem_isConnectedGet_0();
virtual BEC_2_8_4_EmbeddedWifi* bem_stop_0();
virtual BEC_2_4_6_TextString* bem_modeGet_0();
virtual BEC_2_8_4_EmbeddedWifi* bem_modeSet_1(BEC_2_6_6_SystemObject* bevt_0_ta_SET);
virtual BEC_2_4_6_TextString* bem_ssidGet_0();
virtual BEC_2_8_4_EmbeddedWifi* bem_ssidSet_1(BEC_2_6_6_SystemObject* bevt_0_ta_SET);
virtual BEC_2_4_6_TextString* bem_passwordGet_0();
virtual BEC_2_8_4_EmbeddedWifi* bem_passwordSet_1(BEC_2_6_6_SystemObject* bevt_0_ta_SET);
virtual BEC_2_5_4_LogicBool* bem_upGet_0();
virtual BEC_2_8_4_EmbeddedWifi* bem_upSet_1(BEC_2_6_6_SystemObject* bevt_0_ta_SET);
virtual BEC_2_4_6_TextString* bem_localIPGet_0();
virtual BEC_2_8_4_EmbeddedWifi* bem_localIPSet_1(BEC_2_6_6_SystemObject* bevt_0_ta_SET);
virtual BEC_2_6_6_SystemObject* bemc_create();
static BEC_2_8_4_EmbeddedWifi* bece_BEC_2_8_4_EmbeddedWifi_bevs_inst;
virtual void bemc_setInitial(BEC_2_6_6_SystemObject* becc_inst);
virtual BEC_2_6_6_SystemObject* bemc_getInitial();
virtual void bemg_doMark();
virtual size_t bemg_getSize();
virtual BETS_Object* bemc_getType();
virtual ~BEC_2_8_4_EmbeddedWifi() = default;
virtual BEC_2_6_6_SystemObject* bemd_0(int32_t callId);
virtual BEC_2_6_6_SystemObject* bemd_1(int32_t callId, BEC_2_6_6_SystemObject* bevd_0);
virtual BEC_2_6_6_SystemObject* bemd_2(int32_t callId, BEC_2_6_6_SystemObject* bevd_0, BEC_2_6_6_SystemObject* bevd_1);
static BET_2_8_4_EmbeddedWifi bece_BEC_2_8_4_EmbeddedWifi_bevs_type;
};

class BET_2_8_9_EmbeddedTCPServer : public BETS_Object {
public:
BET_2_8_9_EmbeddedTCPServer();
virtual BEC_2_6_6_SystemObject* bems_createInstance();
virtual void bemgt_doMark();
static BEC_2_6_6_SystemObject** bevs_inst_ref;
};
class BEC_2_8_9_EmbeddedTCPServer : public BEC_2_6_6_SystemObject {
private:
typedef BEC_2_6_6_SystemObject bevs_super;

public:
BEC_2_4_3_MathInt* bevp_port = nullptr;
virtual BEC_2_8_9_EmbeddedTCPServer* bem_new_1(BEC_2_4_3_MathInt* bevk__port);
virtual BEC_2_8_9_EmbeddedTCPServer* bem_start_0();
virtual BEC_2_8_9_EmbeddedTCPClient* bem_checkGetClient_0();
virtual BEC_2_4_3_MathInt* bem_portGet_0();
virtual BEC_2_8_9_EmbeddedTCPServer* bem_portSet_1(BEC_2_6_6_SystemObject* bevt_0_ta_SET);
virtual BEC_2_6_6_SystemObject* bemc_create();
static BEC_2_8_9_EmbeddedTCPServer* bece_BEC_2_8_9_EmbeddedTCPServer_bevs_inst;
virtual void bemc_setInitial(BEC_2_6_6_SystemObject* becc_inst);
virtual BEC_2_6_6_SystemObject* bemc_getInitial();
virtual void bemg_doMark();
virtual size_t bemg_getSize();
virtual BETS_Object* bemc_getType();
virtual ~BEC_2_8_9_EmbeddedTCPServer() = default;

   std::unique_ptr<WiFiServer> server;
   virtual BEC_2_6_6_SystemObject* bemd_0(int32_t callId);
virtual BEC_2_6_6_SystemObject* bemd_1(int32_t callId, BEC_2_6_6_SystemObject* bevd_0);
static BET_2_8_9_EmbeddedTCPServer bece_BEC_2_8_9_EmbeddedTCPServer_bevs_type;
};

class BET_2_8_9_EmbeddedTCPClient : public BETS_Object {
public:
BET_2_8_9_EmbeddedTCPClient();
virtual BEC_2_6_6_SystemObject* bems_createInstance();
virtual void bemgt_doMark();
static BEC_2_6_6_SystemObject** bevs_inst_ref;
};
class BEC_2_8_9_EmbeddedTCPClient : public BEC_2_6_6_SystemObject {
private:
typedef BEC_2_6_6_SystemObject bevs_super;

public:
BEC_2_4_6_TextString* bevp_host = nullptr;
BEC_2_4_3_MathInt* bevp_port = nullptr;
BEC_2_5_4_LogicBool* bevp_opened = nullptr;
BEC_2_4_3_MathInt* bevp_connectTimeout = nullptr;
BEC_2_4_3_MathInt* bevp_streamTimeout = nullptr;
virtual BEC_2_6_6_SystemObject* bem_new_0();
virtual BEC_2_8_9_EmbeddedTCPClient* bem_new_2(BEC_2_4_6_TextString* bevk__host, BEC_2_4_3_MathInt* bevk__port);
virtual BEC_2_8_9_EmbeddedTCPClient* bem_open_0();
virtual BEC_2_8_9_EmbeddedTCPClient* bem_write_1(BEC_2_4_6_TextString* bevk_line);
virtual BEC_2_4_6_TextString* bem_checkGetPayload_2(BEC_2_4_6_TextString* bevk_payload, BEC_2_4_6_TextString* bevk_endmark);
virtual BEC_2_5_4_LogicBool* bem_connectedGet_0();
virtual BEC_2_5_4_LogicBool* bem_availableGet_0();
virtual BEC_2_4_6_TextString* bem_remoteIpGet_0();
virtual BEC_2_8_9_EmbeddedTCPClient* bem_close_0();
virtual BEC_2_4_6_TextString* bem_hostGet_0();
virtual BEC_2_8_9_EmbeddedTCPClient* bem_hostSet_1(BEC_2_6_6_SystemObject* bevt_0_ta_SET);
virtual BEC_2_4_3_MathInt* bem_portGet_0();
virtual BEC_2_8_9_EmbeddedTCPClient* bem_portSet_1(BEC_2_6_6_SystemObject* bevt_0_ta_SET);
virtual BEC_2_5_4_LogicBool* bem_openedGet_0();
virtual BEC_2_8_9_EmbeddedTCPClient* bem_openedSet_1(BEC_2_6_6_SystemObject* bevt_0_ta_SET);
virtual BEC_2_4_3_MathInt* bem_connectTimeoutGet_0();
virtual BEC_2_8_9_EmbeddedTCPClient* bem_connectTimeoutSet_1(BEC_2_6_6_SystemObject* bevt_0_ta_SET);
virtual BEC_2_4_3_MathInt* bem_streamTimeoutGet_0();
virtual BEC_2_8_9_EmbeddedTCPClient* bem_streamTimeoutSet_1(BEC_2_6_6_SystemObject* bevt_0_ta_SET);
virtual BEC_2_6_6_SystemObject* bemc_create();
static BEC_2_8_9_EmbeddedTCPClient* bece_BEC_2_8_9_EmbeddedTCPClient_bevs_inst;
virtual void bemc_setInitial(BEC_2_6_6_SystemObject* becc_inst);
virtual BEC_2_6_6_SystemObject* bemc_getInitial();
virtual void bemg_doMark();
virtual size_t bemg_getSize();
virtual BETS_Object* bemc_getType();
virtual ~BEC_2_8_9_EmbeddedTCPClient() = default;


WiFiClient client;

virtual BEC_2_6_6_SystemObject* bemd_0(int32_t callId);
virtual BEC_2_6_6_SystemObject* bemd_1(int32_t callId, BEC_2_6_6_SystemObject* bevd_0);
virtual BEC_2_6_6_SystemObject* bemd_2(int32_t callId, BEC_2_6_6_SystemObject* bevd_0, BEC_2_6_6_SystemObject* bevd_1);
static BET_2_8_9_EmbeddedTCPClient bece_BEC_2_8_9_EmbeddedTCPClient_bevs_type;
};

class BET_2_8_4_EmbeddedMdns : public BETS_Object {
public:
BET_2_8_4_EmbeddedMdns();
virtual BEC_2_6_6_SystemObject* bems_createInstance();
virtual void bemgt_doMark();
static BEC_2_6_6_SystemObject** bevs_inst_ref;
};
class BEC_2_8_4_EmbeddedMdns : public BEC_2_6_6_SystemObject {
private:
typedef BEC_2_6_6_SystemObject bevs_super;

public:
BEC_2_4_6_TextString* bevp_name = nullptr;
BEC_2_4_6_TextString* bevp_service = nullptr;
BEC_2_4_3_MathInt* bevp_port = nullptr;
BEC_2_4_6_TextString* bevp_protocol = nullptr;
virtual BEC_2_6_6_SystemObject* bem_new_0();
virtual BEC_2_8_4_EmbeddedMdns* bem_start_0();
virtual BEC_2_8_4_EmbeddedMdns* bem_update_0();
virtual BEC_2_4_6_TextString* bem_nameGet_0();
virtual BEC_2_8_4_EmbeddedMdns* bem_nameSet_1(BEC_2_6_6_SystemObject* bevt_0_ta_SET);
virtual BEC_2_4_6_TextString* bem_serviceGet_0();
virtual BEC_2_8_4_EmbeddedMdns* bem_serviceSet_1(BEC_2_6_6_SystemObject* bevt_0_ta_SET);
virtual BEC_2_4_3_MathInt* bem_portGet_0();
virtual BEC_2_8_4_EmbeddedMdns* bem_portSet_1(BEC_2_6_6_SystemObject* bevt_0_ta_SET);
virtual BEC_2_4_6_TextString* bem_protocolGet_0();
virtual BEC_2_8_4_EmbeddedMdns* bem_protocolSet_1(BEC_2_6_6_SystemObject* bevt_0_ta_SET);
virtual BEC_2_6_6_SystemObject* bemc_create();
static BEC_2_8_4_EmbeddedMdns* bece_BEC_2_8_4_EmbeddedMdns_bevs_inst;
virtual void bemc_setInitial(BEC_2_6_6_SystemObject* becc_inst);
virtual BEC_2_6_6_SystemObject* bemc_getInitial();
virtual void bemg_doMark();
virtual size_t bemg_getSize();
virtual BETS_Object* bemc_getType();
virtual ~BEC_2_8_4_EmbeddedMdns() = default;
virtual BEC_2_6_6_SystemObject* bemd_0(int32_t callId);
virtual BEC_2_6_6_SystemObject* bemd_1(int32_t callId, BEC_2_6_6_SystemObject* bevd_0);
static BET_2_8_4_EmbeddedMdns bece_BEC_2_8_4_EmbeddedMdns_bevs_type;
};

class BET_2_8_4_EmbeddedMqtt : public BETS_Object {
public:
BET_2_8_4_EmbeddedMqtt();
virtual BEC_2_6_6_SystemObject* bems_createInstance();
virtual void bemgt_doMark();
static BEC_2_6_6_SystemObject** bevs_inst_ref;
};
class BEC_2_8_4_EmbeddedMqtt : public BEC_2_6_6_SystemObject {
private:
typedef BEC_2_6_6_SystemObject bevs_super;

public:
BEC_2_4_6_TextString* bevp_mqttServer = nullptr;
BEC_2_4_6_TextString* bevp_user = nullptr;
BEC_2_4_6_TextString* bevp_pass = nullptr;
BEC_2_4_3_MathInt* bevp_mqttPort = nullptr;
BEC_2_4_6_TextString* bevp_id = nullptr;
BEC_2_9_4_ContainerList* bevp_mqsubl = nullptr;
BEC_3_9_4_8_ContainerListIterator* bevp_mqsubi = nullptr;
BEC_2_8_11_EmbeddedMqttMessage* bevp_mqpubm = nullptr;
BEC_2_9_4_ContainerList* bevp_mqpubl = nullptr;
BEC_3_9_4_8_ContainerListIterator* bevp_mqpubi = nullptr;
BEC_2_4_3_MathInt* bevp_mqpublmax = nullptr;
BEC_2_8_11_EmbeddedMqttMessage* bevp_mqrcm = nullptr;
BEC_2_9_4_ContainerList* bevp_mqrcl = nullptr;
BEC_3_9_4_8_ContainerListIterator* bevp_mqrci = nullptr;
BEC_2_4_3_MathInt* bevp_mqrcmax = nullptr;
BEC_2_4_3_MathInt* bevp_zero = nullptr;
virtual BEC_2_6_6_SystemObject* bem_new_0();
virtual BEC_2_8_4_EmbeddedMqtt* bem_new_3(BEC_2_4_6_TextString* bevk__mqttServer, BEC_2_4_6_TextString* bevk__user, BEC_2_4_6_TextString* bevk__pass);
virtual BEC_2_8_4_EmbeddedMqtt* bem_minAsyncCapacitySet_1(BEC_2_4_3_MathInt* bevk_size);
virtual BEC_2_5_4_LogicBool* bem_hasAsyncCapacity_1(BEC_2_4_3_MathInt* bevk_amount);
virtual BEC_2_5_4_LogicBool* bem_publishAsync_2(BEC_2_4_6_TextString* bevk_pt, BEC_2_4_6_TextString* bevk_cf);
virtual BEC_2_5_4_LogicBool* bem_publishAsync_1(BEC_2_8_11_EmbeddedMqttMessage* bevk_msg);
virtual BEC_2_5_4_LogicBool* bem_subscribeAsync_1(BEC_2_4_6_TextString* bevk_topic);
virtual BEC_2_5_4_LogicBool* bem_isOpenGet_0();
virtual BEC_2_5_4_LogicBool* bem_close_0();
virtual BEC_2_5_4_LogicBool* bem_open_0();
virtual BEC_2_5_4_LogicBool* bem_publish_2(BEC_2_4_6_TextString* bevk_topic, BEC_2_4_6_TextString* bevk_payload);
virtual BEC_2_5_4_LogicBool* bem_publish_1(BEC_2_8_11_EmbeddedMqttMessage* bevk_msg);
virtual BEC_2_5_4_LogicBool* bem_handleAsync_1(BEC_2_6_6_SystemObject* bevk_mqttHandler);
virtual BEC_2_8_4_EmbeddedMqtt* bem_subscribe_1(BEC_2_4_6_TextString* bevk_topic);
virtual BEC_2_4_6_TextString* bem_mqttServerGet_0();
virtual BEC_2_8_4_EmbeddedMqtt* bem_mqttServerSet_1(BEC_2_6_6_SystemObject* bevt_0_ta_SET);
virtual BEC_2_4_6_TextString* bem_userGet_0();
virtual BEC_2_8_4_EmbeddedMqtt* bem_userSet_1(BEC_2_6_6_SystemObject* bevt_0_ta_SET);
virtual BEC_2_4_6_TextString* bem_passGet_0();
virtual BEC_2_8_4_EmbeddedMqtt* bem_passSet_1(BEC_2_6_6_SystemObject* bevt_0_ta_SET);
virtual BEC_2_4_3_MathInt* bem_mqttPortGet_0();
virtual BEC_2_8_4_EmbeddedMqtt* bem_mqttPortSet_1(BEC_2_6_6_SystemObject* bevt_0_ta_SET);
virtual BEC_2_4_6_TextString* bem_idGet_0();
virtual BEC_2_8_4_EmbeddedMqtt* bem_idSet_1(BEC_2_6_6_SystemObject* bevt_0_ta_SET);
virtual BEC_2_9_4_ContainerList* bem_mqsublGet_0();
virtual BEC_2_8_4_EmbeddedMqtt* bem_mqsublSet_1(BEC_2_6_6_SystemObject* bevt_0_ta_SET);
virtual BEC_3_9_4_8_ContainerListIterator* bem_mqsubiGet_0();
virtual BEC_2_8_4_EmbeddedMqtt* bem_mqsubiSet_1(BEC_2_6_6_SystemObject* bevt_0_ta_SET);
virtual BEC_2_8_11_EmbeddedMqttMessage* bem_mqpubmGet_0();
virtual BEC_2_8_4_EmbeddedMqtt* bem_mqpubmSet_1(BEC_2_6_6_SystemObject* bevt_0_ta_SET);
virtual BEC_2_9_4_ContainerList* bem_mqpublGet_0();
virtual BEC_2_8_4_EmbeddedMqtt* bem_mqpublSet_1(BEC_2_6_6_SystemObject* bevt_0_ta_SET);
virtual BEC_3_9_4_8_ContainerListIterator* bem_mqpubiGet_0();
virtual BEC_2_8_4_EmbeddedMqtt* bem_mqpubiSet_1(BEC_2_6_6_SystemObject* bevt_0_ta_SET);
virtual BEC_2_4_3_MathInt* bem_mqpublmaxGet_0();
virtual BEC_2_8_4_EmbeddedMqtt* bem_mqpublmaxSet_1(BEC_2_6_6_SystemObject* bevt_0_ta_SET);
virtual BEC_2_8_11_EmbeddedMqttMessage* bem_mqrcmGet_0();
virtual BEC_2_8_4_EmbeddedMqtt* bem_mqrcmSet_1(BEC_2_6_6_SystemObject* bevt_0_ta_SET);
virtual BEC_2_9_4_ContainerList* bem_mqrclGet_0();
virtual BEC_2_8_4_EmbeddedMqtt* bem_mqrclSet_1(BEC_2_6_6_SystemObject* bevt_0_ta_SET);
virtual BEC_3_9_4_8_ContainerListIterator* bem_mqrciGet_0();
virtual BEC_2_8_4_EmbeddedMqtt* bem_mqrciSet_1(BEC_2_6_6_SystemObject* bevt_0_ta_SET);
virtual BEC_2_4_3_MathInt* bem_mqrcmaxGet_0();
virtual BEC_2_8_4_EmbeddedMqtt* bem_mqrcmaxSet_1(BEC_2_6_6_SystemObject* bevt_0_ta_SET);
virtual BEC_2_4_3_MathInt* bem_zeroGet_0();
virtual BEC_2_8_4_EmbeddedMqtt* bem_zeroSet_1(BEC_2_6_6_SystemObject* bevt_0_ta_SET);
virtual BEC_2_6_6_SystemObject* bemc_create();
static BEC_2_8_4_EmbeddedMqtt* bece_BEC_2_8_4_EmbeddedMqtt_bevs_inst;
virtual void bemc_setInitial(BEC_2_6_6_SystemObject* becc_inst);
virtual BEC_2_6_6_SystemObject* bemc_getInitial();
virtual void bemg_doMark();
virtual size_t bemg_getSize();
virtual BETS_Object* bemc_getType();
virtual ~BEC_2_8_4_EmbeddedMqtt() = default;

std::unique_ptr<MQTTClient> client;
WiFiClient net;
static std::string gotTopic;
static std::string gotPayload;
virtual BEC_2_6_6_SystemObject* bemd_0(int32_t callId);
virtual BEC_2_6_6_SystemObject* bemd_1(int32_t callId, BEC_2_6_6_SystemObject* bevd_0);
virtual BEC_2_6_6_SystemObject* bemd_2(int32_t callId, BEC_2_6_6_SystemObject* bevd_0, BEC_2_6_6_SystemObject* bevd_1);
virtual BEC_2_6_6_SystemObject* bemd_3(int32_t callId, BEC_2_6_6_SystemObject* bevd_0, BEC_2_6_6_SystemObject* bevd_1, BEC_2_6_6_SystemObject* bevd_2);
static BET_2_8_4_EmbeddedMqtt bece_BEC_2_8_4_EmbeddedMqtt_bevs_type;
};

class BET_2_8_11_EmbeddedMqttMessage : public BETS_Object {
public:
BET_2_8_11_EmbeddedMqttMessage();
virtual BEC_2_6_6_SystemObject* bems_createInstance();
virtual void bemgt_doMark();
static BEC_2_6_6_SystemObject** bevs_inst_ref;
};
class BEC_2_8_11_EmbeddedMqttMessage : public BEC_2_6_6_SystemObject {
private:
typedef BEC_2_6_6_SystemObject bevs_super;

public:
BEC_2_4_6_TextString* bevp_topic = nullptr;
BEC_2_4_6_TextString* bevp_payload = nullptr;
virtual BEC_2_8_11_EmbeddedMqttMessage* bem_new_2(BEC_2_4_6_TextString* bevk__topic, BEC_2_4_6_TextString* bevk__payload);
virtual BEC_2_4_6_TextString* bem_toString_0();
virtual BEC_2_4_6_TextString* bem_topicGet_0();
virtual BEC_2_8_11_EmbeddedMqttMessage* bem_topicSet_1(BEC_2_6_6_SystemObject* bevt_0_ta_SET);
virtual BEC_2_4_6_TextString* bem_payloadGet_0();
virtual BEC_2_8_11_EmbeddedMqttMessage* bem_payloadSet_1(BEC_2_6_6_SystemObject* bevt_0_ta_SET);
virtual BEC_2_6_6_SystemObject* bemc_create();
static BEC_2_8_11_EmbeddedMqttMessage* bece_BEC_2_8_11_EmbeddedMqttMessage_bevs_inst;
virtual void bemc_setInitial(BEC_2_6_6_SystemObject* becc_inst);
virtual BEC_2_6_6_SystemObject* bemc_getInitial();
virtual void bemg_doMark();
virtual size_t bemg_getSize();
virtual BETS_Object* bemc_getType();
virtual ~BEC_2_8_11_EmbeddedMqttMessage() = default;
virtual BEC_2_6_6_SystemObject* bemd_0(int32_t callId);
virtual BEC_2_6_6_SystemObject* bemd_1(int32_t callId, BEC_2_6_6_SystemObject* bevd_0);
virtual BEC_2_6_6_SystemObject* bemd_2(int32_t callId, BEC_2_6_6_SystemObject* bevd_0, BEC_2_6_6_SystemObject* bevd_1);
static BET_2_8_11_EmbeddedMqttMessage bece_BEC_2_8_11_EmbeddedMqttMessage_bevs_type;
};

class BET_2_8_6_EmbeddedUpdate : public BETS_Object {
public:
BET_2_8_6_EmbeddedUpdate();
virtual BEC_2_6_6_SystemObject* bems_createInstance();
virtual void bemgt_doMark();
static BEC_2_6_6_SystemObject** bevs_inst_ref;
};
class BEC_2_8_6_EmbeddedUpdate : public BEC_2_6_6_SystemObject {
private:
typedef BEC_2_6_6_SystemObject bevs_super;

public:
virtual BEC_2_8_6_EmbeddedUpdate* bem_updateFromUrl_1(BEC_2_4_6_TextString* bevk_url);
virtual BEC_2_6_6_SystemObject* bemc_create();
static BEC_2_8_6_EmbeddedUpdate* bece_BEC_2_8_6_EmbeddedUpdate_bevs_inst;
virtual void bemc_setInitial(BEC_2_6_6_SystemObject* becc_inst);
virtual BEC_2_6_6_SystemObject* bemc_getInitial();
virtual void bemg_doMark();
virtual size_t bemg_getSize();
virtual BETS_Object* bemc_getType();
virtual ~BEC_2_8_6_EmbeddedUpdate() = default;
virtual BEC_2_6_6_SystemObject* bemd_1(int32_t callId, BEC_2_6_6_SystemObject* bevd_0);
static BET_2_8_6_EmbeddedUpdate bece_BEC_2_8_6_EmbeddedUpdate_bevs_type;
};

class BET_2_8_8_EmbeddedAppShell : public BETS_Object {
public:
BET_2_8_8_EmbeddedAppShell();
virtual BEC_2_6_6_SystemObject* bems_createInstance();
virtual void bemgt_doMark();
static BEC_2_6_6_SystemObject** bevs_inst_ref;
};
class BEC_2_8_8_EmbeddedAppShell : public BEC_2_6_6_SystemObject {
private:
typedef BEC_2_6_6_SystemObject bevs_super;

public:
BEC_2_8_3_EmbeddedApp* bevp_app = nullptr;
BEC_2_8_6_EmbeddedConfig* bevp_config = nullptr;
BEC_2_4_3_MathInt* bevp_nowup = nullptr;
BEC_2_4_6_TextString* bevp_lastEventsRes = nullptr;
BEC_2_5_4_LogicBool* bevp_needsStateUp = nullptr;
BEC_2_5_4_LogicBool* bevp_needsStateUpSoon = nullptr;
BEC_2_9_4_ContainerList* bevp_controls = nullptr;
BEC_2_9_4_ContainerList* bevp_loopers = nullptr;
BEC_2_8_9_EmbeddedTCPClient* bevp_concon = nullptr;
BEC_2_4_3_MathInt* bevp_shpini = nullptr;
BEC_2_4_3_MathInt* bevp_shpassi = nullptr;
BEC_2_4_3_MathInt* bevp_shspassi = nullptr;
BEC_2_4_3_MathInt* bevp_shssidi = nullptr;
BEC_2_4_3_MathInt* bevp_shseci = nullptr;
BEC_2_4_3_MathInt* bevp_shdidi = nullptr;
BEC_2_4_3_MathInt* bevp_zero = nullptr;
BEC_2_4_3_MathInt* bevp_nextUpdateCheck = nullptr;
BEC_2_4_3_MathInt* bevp_nextMq = nullptr;
BEC_2_4_3_MathInt* bevp_nextSwInfo = nullptr;
BEC_2_4_3_MathInt* bevp_nextRestart = nullptr;
BEC_2_4_3_MathInt* bevp_nextMaybeSave = nullptr;
BEC_2_4_3_MathInt* bevp_nextApCheck = nullptr;
BEC_2_4_3_MathInt* bevp_nextWifiCheck = nullptr;
BEC_2_4_6_TextString* bevp_slashn = nullptr;
BEC_2_4_6_TextString* bevp_slashr = nullptr;
BEC_2_4_6_TextString* bevp_htmlHead = nullptr;
BEC_2_5_4_LogicBool* bevp_needsFsRestart = nullptr;
BEC_2_5_4_LogicBool* bevp_needsRestart = nullptr;
BEC_2_4_6_TextString* bevp_did = nullptr;
BEC_2_4_6_TextString* bevp_swSpec = nullptr;
BEC_2_4_6_TextString* bevp_devCode = nullptr;
BEC_2_4_3_MathInt* bevp_version = nullptr;
BEC_2_4_6_TextString* bevp_swInfo = nullptr;
BEC_2_5_4_LogicBool* bevp_resetByPin = nullptr;
BEC_2_4_6_TextString* bevp_readBuf = nullptr;
BEC_2_4_6_TextString* bevp_supurl = nullptr;
BEC_2_4_6_TextString* bevp_controlSpec = nullptr;
BEC_2_4_6_TextString* bevp_controlDef = nullptr;
BEC_2_5_4_LogicBool* bevp_needsNetworkInit = nullptr;
BEC_2_5_4_LogicBool* bevp_readyForAp = nullptr;
BEC_2_5_4_LogicBool* bevp_needsBuildControls = nullptr;
BEC_2_5_4_LogicBool* bevp_needsInitControls = nullptr;
BEC_2_5_4_LogicBool* bevp_needsGc = nullptr;
BEC_2_5_4_LogicBool* bevp_needsMqConfUp = nullptr;
BEC_2_4_3_MathInt* bevp_looperI = nullptr;
BEC_2_4_6_TextString* bevp_pin = nullptr;
BEC_2_4_6_TextString* bevp_pass = nullptr;
BEC_2_4_6_TextString* bevp_spass = nullptr;
BEC_2_8_4_EmbeddedMdns* bevp_mdserver = nullptr;
BEC_2_8_4_EmbeddedMqtt* bevp_mqtt = nullptr;
BEC_2_8_9_EmbeddedTCPServer* bevp_tcpserver = nullptr;
BEC_2_8_9_EmbeddedTCPServer* bevp_conserver = nullptr;
BEC_2_4_6_TextString* bevp_apSsid = nullptr;
BEC_2_4_6_TextString* bevp_apType = nullptr;
BEC_2_4_6_TextString* bevp_ssid = nullptr;
BEC_2_4_6_TextString* bevp_sec = nullptr;
virtual BEC_2_8_8_EmbeddedAppShell* bem_main_0();
virtual BEC_2_8_8_EmbeddedAppShell* bem_sendWebPage_1(BEC_2_6_6_SystemObject* bevk_treq);
virtual BEC_2_8_8_EmbeddedAppShell* bem_initControls_0();
virtual BEC_2_4_6_TextString* bem_doState_1(BEC_2_9_4_ContainerList* bevk_cmdl);
virtual BEC_2_4_6_TextString* bem_getLastEvents_1(BEC_2_9_4_ContainerList* bevk_cmdl);
virtual BEC_2_8_8_EmbeddedAppShell* bem_clearStates_0();
virtual BEC_2_8_8_EmbeddedAppShell* bem_checkMakeIds_0();
virtual BEC_2_8_8_EmbeddedAppShell* bem_loadPasses_0();
virtual BEC_2_8_8_EmbeddedAppShell* bem_buildSwInfoIn_0();
virtual BEC_2_8_8_EmbeddedAppShell* bem_buildSwInfo_0();
virtual BEC_2_6_6_SystemObject* bem_buildControl_3(BEC_2_4_3_MathInt* bevk_conPos, BEC_2_4_6_TextString* bevk_conName, BEC_2_4_6_TextString* bevk_conArgs);
virtual BEC_2_8_8_EmbeddedAppShell* bem_buildControlsIn_0();
virtual BEC_2_8_8_EmbeddedAppShell* bem_buildControls_0();
virtual BEC_2_8_8_EmbeddedAppShell* bem_initRandom_0();
virtual BEC_2_8_8_EmbeddedAppShell* bem_startLoop_0();
virtual BEC_2_8_8_EmbeddedAppShell* bem_networkInit_0();
virtual BEC_2_8_8_EmbeddedAppShell* bem_initMq_0();
virtual BEC_2_8_8_EmbeddedAppShell* bem_mqConfUp_1(BEC_2_5_4_LogicBool* bevk_doSubs);
virtual BEC_2_8_8_EmbeddedAppShell* bem_mqStateUp_0();
virtual BEC_2_8_8_EmbeddedAppShell* bem_checkWifiAp_0();
virtual BEC_2_8_8_EmbeddedAppShell* bem_initAp_0();
virtual BEC_2_8_8_EmbeddedAppShell* bem_startWifi_0();
virtual BEC_2_8_8_EmbeddedAppShell* bem_checkWifiUp_0();
virtual BEC_2_8_8_EmbeddedAppShell* bem_sysupdate_1(BEC_2_4_6_TextString* bevk_upurl);
virtual BEC_2_8_8_EmbeddedAppShell* bem_handleLoop_0();
virtual BEC_2_8_8_EmbeddedAppShell* bem_handleMqtt_2(BEC_2_4_6_TextString* bevk_topic, BEC_2_4_6_TextString* bevk_payload);
virtual BEC_2_4_6_TextString* bem_doCmd_3(BEC_2_4_6_TextString* bevk_channel, BEC_2_4_6_TextString* bevk_origin, BEC_2_4_6_TextString* bevk_cmdline);
virtual BEC_2_4_6_TextString* bem_doCmdlSec_3(BEC_2_4_6_TextString* bevk_channel, BEC_2_4_6_TextString* bevk_origin, BEC_2_9_4_ContainerList* bevk_cmdl);
virtual BEC_2_4_6_TextString* bem_doCmdl_3(BEC_2_4_6_TextString* bevk_channel, BEC_2_4_6_TextString* bevk_origin, BEC_2_9_4_ContainerList* bevk_cmdl);
virtual BEC_2_8_8_EmbeddedAppShell* bem_reset_0();
virtual BEC_2_6_6_SystemObject* bem_appGet_0();
virtual BEC_2_8_8_EmbeddedAppShell* bem_appSet_1(BEC_2_6_6_SystemObject* bevt_0_ta_SET);
virtual BEC_2_8_6_EmbeddedConfig* bem_configGet_0();
virtual BEC_2_8_8_EmbeddedAppShell* bem_configSet_1(BEC_2_6_6_SystemObject* bevt_0_ta_SET);
virtual BEC_2_4_3_MathInt* bem_nowupGet_0();
virtual BEC_2_8_8_EmbeddedAppShell* bem_nowupSet_1(BEC_2_6_6_SystemObject* bevt_0_ta_SET);
virtual BEC_2_4_6_TextString* bem_lastEventsResGet_0();
virtual BEC_2_8_8_EmbeddedAppShell* bem_lastEventsResSet_1(BEC_2_6_6_SystemObject* bevt_0_ta_SET);
virtual BEC_2_5_4_LogicBool* bem_needsStateUpGet_0();
virtual BEC_2_8_8_EmbeddedAppShell* bem_needsStateUpSet_1(BEC_2_6_6_SystemObject* bevt_0_ta_SET);
virtual BEC_2_5_4_LogicBool* bem_needsStateUpSoonGet_0();
virtual BEC_2_8_8_EmbeddedAppShell* bem_needsStateUpSoonSet_1(BEC_2_6_6_SystemObject* bevt_0_ta_SET);
virtual BEC_2_9_4_ContainerList* bem_controlsGet_0();
virtual BEC_2_8_8_EmbeddedAppShell* bem_controlsSet_1(BEC_2_6_6_SystemObject* bevt_0_ta_SET);
virtual BEC_2_9_4_ContainerList* bem_loopersGet_0();
virtual BEC_2_8_8_EmbeddedAppShell* bem_loopersSet_1(BEC_2_6_6_SystemObject* bevt_0_ta_SET);
virtual BEC_2_8_9_EmbeddedTCPClient* bem_conconGet_0();
virtual BEC_2_8_8_EmbeddedAppShell* bem_conconSet_1(BEC_2_6_6_SystemObject* bevt_0_ta_SET);
virtual BEC_2_4_6_TextString* bem_pinGet_0();
virtual BEC_2_8_8_EmbeddedAppShell* bem_pinSet_1(BEC_2_6_6_SystemObject* bevt_0_ta_SET);
virtual BEC_2_8_4_EmbeddedMdns* bem_mdserverGet_0();
virtual BEC_2_8_8_EmbeddedAppShell* bem_mdserverSet_1(BEC_2_6_6_SystemObject* bevt_0_ta_SET);
virtual BEC_2_8_4_EmbeddedMqtt* bem_mqttGet_0();
virtual BEC_2_8_8_EmbeddedAppShell* bem_mqttSet_1(BEC_2_6_6_SystemObject* bevt_0_ta_SET);
virtual BEC_2_8_9_EmbeddedTCPServer* bem_tcpserverGet_0();
virtual BEC_2_8_8_EmbeddedAppShell* bem_tcpserverSet_1(BEC_2_6_6_SystemObject* bevt_0_ta_SET);
virtual BEC_2_8_9_EmbeddedTCPServer* bem_conserverGet_0();
virtual BEC_2_8_8_EmbeddedAppShell* bem_conserverSet_1(BEC_2_6_6_SystemObject* bevt_0_ta_SET);
virtual BEC_2_6_6_SystemObject* bemc_create();
static BEC_2_8_8_EmbeddedAppShell* bece_BEC_2_8_8_EmbeddedAppShell_bevs_inst;
virtual void bemc_setInitial(BEC_2_6_6_SystemObject* becc_inst);
virtual BEC_2_6_6_SystemObject* bemc_getInitial();
virtual void bemg_doMark();
virtual size_t bemg_getSize();
virtual BETS_Object* bemc_getType();
virtual ~BEC_2_8_8_EmbeddedAppShell() = default;
virtual BEC_2_6_6_SystemObject* bemd_0(int32_t callId);
virtual BEC_2_6_6_SystemObject* bemd_1(int32_t callId, BEC_2_6_6_SystemObject* bevd_0);
virtual BEC_2_6_6_SystemObject* bemd_2(int32_t callId, BEC_2_6_6_SystemObject* bevd_0, BEC_2_6_6_SystemObject* bevd_1);
virtual BEC_2_6_6_SystemObject* bemd_3(int32_t callId, BEC_2_6_6_SystemObject* bevd_0, BEC_2_6_6_SystemObject* bevd_1, BEC_2_6_6_SystemObject* bevd_2);
static BET_2_8_8_EmbeddedAppShell bece_BEC_2_8_8_EmbeddedAppShell_bevs_type;
};

class BET_2_8_13_EmbeddedSwitchControl : public BETS_Object {
public:
BET_2_8_13_EmbeddedSwitchControl();
virtual BEC_2_6_6_SystemObject* bems_createInstance();
virtual void bemgt_doMark();
static BEC_2_6_6_SystemObject** bevs_inst_ref;
};
class BEC_2_8_13_EmbeddedSwitchControl : public BEC_2_6_6_SystemObject {
private:
typedef BEC_2_6_6_SystemObject bevs_super;

public:
BEC_2_8_8_EmbeddedAppShell* bevp_ash = nullptr;
BEC_2_4_3_MathInt* bevp_pini = nullptr;
BEC_2_4_3_MathInt* bevp_diri = nullptr;
BEC_2_8_6_EmbeddedConfig* bevp_config = nullptr;
BEC_2_8_3_EmbeddedApp* bevp_app = nullptr;
BEC_2_4_3_MathInt* bevp_conPos = nullptr;
BEC_2_4_3_MathInt* bevp_lastEvent = nullptr;
BEC_2_4_6_TextString* bevp_conName = nullptr;
BEC_2_4_3_MathInt* bevp_scswi = nullptr;
BEC_2_4_6_TextString* bevp_getsw = nullptr;
BEC_2_4_6_TextString* bevp_on = nullptr;
BEC_2_4_6_TextString* bevp_off = nullptr;
BEC_2_4_6_TextString* bevp_setsw = nullptr;
BEC_2_4_6_TextString* bevp_sw = nullptr;
virtual BEC_2_8_13_EmbeddedSwitchControl* bem_new_4(BEC_2_6_6_SystemObject* bevk__ash, BEC_2_4_3_MathInt* bevk__conPos, BEC_2_4_6_TextString* bevk__conName, BEC_2_4_6_TextString* bevk__conArgs);
virtual BEC_2_8_13_EmbeddedSwitchControl* bem_initControl_0();
virtual BEC_2_4_6_TextString* bem_doStateMq_2(BEC_2_4_6_TextString* bevk_topic, BEC_2_4_6_TextString* bevk_payload);
virtual BEC_2_4_6_TextString* bem_doState_1(BEC_2_9_4_ContainerList* bevk_cmdl);
virtual BEC_2_8_13_EmbeddedSwitchControl* bem_clearStates_0();
virtual BEC_2_4_3_MathInt* bem_conPosGet_0();
virtual BEC_2_8_13_EmbeddedSwitchControl* bem_conPosSet_1(BEC_2_6_6_SystemObject* bevt_0_ta_SET);
virtual BEC_2_4_3_MathInt* bem_lastEventGet_0();
virtual BEC_2_8_13_EmbeddedSwitchControl* bem_lastEventSet_1(BEC_2_6_6_SystemObject* bevt_0_ta_SET);
virtual BEC_2_4_6_TextString* bem_conNameGet_0();
virtual BEC_2_8_13_EmbeddedSwitchControl* bem_conNameSet_1(BEC_2_6_6_SystemObject* bevt_0_ta_SET);
virtual BEC_2_4_6_TextString* bem_onGet_0();
virtual BEC_2_8_13_EmbeddedSwitchControl* bem_onSet_1(BEC_2_6_6_SystemObject* bevt_0_ta_SET);
virtual BEC_2_4_6_TextString* bem_offGet_0();
virtual BEC_2_8_13_EmbeddedSwitchControl* bem_offSet_1(BEC_2_6_6_SystemObject* bevt_0_ta_SET);
virtual BEC_2_4_6_TextString* bem_setswGet_0();
virtual BEC_2_8_13_EmbeddedSwitchControl* bem_setswSet_1(BEC_2_6_6_SystemObject* bevt_0_ta_SET);
virtual BEC_2_4_6_TextString* bem_swGet_0();
virtual BEC_2_8_13_EmbeddedSwitchControl* bem_swSet_1(BEC_2_6_6_SystemObject* bevt_0_ta_SET);
virtual BEC_2_6_6_SystemObject* bemc_create();
static BEC_2_8_13_EmbeddedSwitchControl* bece_BEC_2_8_13_EmbeddedSwitchControl_bevs_inst;
virtual void bemc_setInitial(BEC_2_6_6_SystemObject* becc_inst);
virtual BEC_2_6_6_SystemObject* bemc_getInitial();
virtual void bemg_doMark();
virtual size_t bemg_getSize();
virtual BETS_Object* bemc_getType();
virtual ~BEC_2_8_13_EmbeddedSwitchControl() = default;
virtual BEC_2_6_6_SystemObject* bemd_0(int32_t callId);
virtual BEC_2_6_6_SystemObject* bemd_1(int32_t callId, BEC_2_6_6_SystemObject* bevd_0);
virtual BEC_2_6_6_SystemObject* bemd_2(int32_t callId, BEC_2_6_6_SystemObject* bevd_0, BEC_2_6_6_SystemObject* bevd_1);
virtual BEC_2_6_6_SystemObject* bemd_4(int32_t callId, BEC_2_6_6_SystemObject* bevd_0, BEC_2_6_6_SystemObject* bevd_1, BEC_2_6_6_SystemObject* bevd_2, BEC_2_6_6_SystemObject* bevd_3);
static BET_2_8_13_EmbeddedSwitchControl bece_BEC_2_8_13_EmbeddedSwitchControl_bevs_type;
};

class BET_2_8_13_EmbeddedButtonControl : public BETS_Object {
public:
BET_2_8_13_EmbeddedButtonControl();
virtual BEC_2_6_6_SystemObject* bems_createInstance();
virtual void bemgt_doMark();
static BEC_2_6_6_SystemObject** bevs_inst_ref;
};
class BEC_2_8_13_EmbeddedButtonControl : public BEC_2_6_6_SystemObject {
private:
typedef BEC_2_6_6_SystemObject bevs_super;

public:
BEC_2_8_8_EmbeddedAppShell* bevp_ash = nullptr;
BEC_2_4_3_MathInt* bevp_pini = nullptr;
BEC_2_4_3_MathInt* bevp_diri = nullptr;
BEC_2_8_6_EmbeddedConfig* bevp_config = nullptr;
BEC_2_8_3_EmbeddedApp* bevp_app = nullptr;
BEC_2_4_3_MathInt* bevp_onStart = nullptr;
BEC_2_4_3_MathInt* bevp_pushTime = nullptr;
BEC_2_4_3_MathInt* bevp_swPos = nullptr;
BEC_2_4_3_MathInt* bevp_resetPushTime = nullptr;
BEC_2_4_3_MathInt* bevp_conPos = nullptr;
BEC_2_4_3_MathInt* bevp_lastEvent = nullptr;
BEC_2_4_6_TextString* bevp_conName = nullptr;
BEC_2_4_3_MathInt* bevp_butVal = nullptr;
BEC_2_4_3_MathInt* bevp_lastButVal = nullptr;
BEC_2_4_3_MathInt* bevp_lastTrans = nullptr;
virtual BEC_2_8_13_EmbeddedButtonControl* bem_new_4(BEC_2_6_6_SystemObject* bevk__ash, BEC_2_4_3_MathInt* bevk__conPos, BEC_2_4_6_TextString* bevk__conName, BEC_2_4_6_TextString* bevk__conArgs);
virtual BEC_2_8_13_EmbeddedButtonControl* bem_initControl_0();
virtual BEC_2_4_6_TextString* bem_doStateMq_2(BEC_2_4_6_TextString* bevk_topic, BEC_2_4_6_TextString* bevk_payload);
virtual BEC_2_4_6_TextString* bem_doState_1(BEC_2_9_4_ContainerList* bevk_cmdl);
virtual BEC_2_8_13_EmbeddedButtonControl* bem_clearStates_0();
virtual BEC_2_8_13_EmbeddedButtonControl* bem_handleLoop_0();
virtual BEC_2_4_3_MathInt* bem_conPosGet_0();
virtual BEC_2_8_13_EmbeddedButtonControl* bem_conPosSet_1(BEC_2_6_6_SystemObject* bevt_0_ta_SET);
virtual BEC_2_4_3_MathInt* bem_lastEventGet_0();
virtual BEC_2_8_13_EmbeddedButtonControl* bem_lastEventSet_1(BEC_2_6_6_SystemObject* bevt_0_ta_SET);
virtual BEC_2_4_6_TextString* bem_conNameGet_0();
virtual BEC_2_8_13_EmbeddedButtonControl* bem_conNameSet_1(BEC_2_6_6_SystemObject* bevt_0_ta_SET);
virtual BEC_2_4_3_MathInt* bem_butValGet_0();
virtual BEC_2_8_13_EmbeddedButtonControl* bem_butValSet_1(BEC_2_6_6_SystemObject* bevt_0_ta_SET);
virtual BEC_2_4_3_MathInt* bem_lastButValGet_0();
virtual BEC_2_8_13_EmbeddedButtonControl* bem_lastButValSet_1(BEC_2_6_6_SystemObject* bevt_0_ta_SET);
virtual BEC_2_4_3_MathInt* bem_lastTransGet_0();
virtual BEC_2_8_13_EmbeddedButtonControl* bem_lastTransSet_1(BEC_2_6_6_SystemObject* bevt_0_ta_SET);
virtual BEC_2_6_6_SystemObject* bemc_create();
static BEC_2_8_13_EmbeddedButtonControl* bece_BEC_2_8_13_EmbeddedButtonControl_bevs_inst;
virtual void bemc_setInitial(BEC_2_6_6_SystemObject* becc_inst);
virtual BEC_2_6_6_SystemObject* bemc_getInitial();
virtual void bemg_doMark();
virtual size_t bemg_getSize();
virtual BETS_Object* bemc_getType();
virtual ~BEC_2_8_13_EmbeddedButtonControl() = default;
virtual BEC_2_6_6_SystemObject* bemd_0(int32_t callId);
virtual BEC_2_6_6_SystemObject* bemd_1(int32_t callId, BEC_2_6_6_SystemObject* bevd_0);
virtual BEC_2_6_6_SystemObject* bemd_2(int32_t callId, BEC_2_6_6_SystemObject* bevd_0, BEC_2_6_6_SystemObject* bevd_1);
virtual BEC_2_6_6_SystemObject* bemd_4(int32_t callId, BEC_2_6_6_SystemObject* bevd_0, BEC_2_6_6_SystemObject* bevd_1, BEC_2_6_6_SystemObject* bevd_2, BEC_2_6_6_SystemObject* bevd_3);
static BET_2_8_13_EmbeddedButtonControl bece_BEC_2_8_13_EmbeddedButtonControl_bevs_type;
};

class BET_2_8_22_EmbeddedSwitchIndicatorControl : public BETS_Object {
public:
BET_2_8_22_EmbeddedSwitchIndicatorControl();
virtual BEC_2_6_6_SystemObject* bems_createInstance();
virtual void bemgt_doMark();
static BEC_2_6_6_SystemObject** bevs_inst_ref;
};
class BEC_2_8_22_EmbeddedSwitchIndicatorControl : public BEC_2_6_6_SystemObject {
private:
typedef BEC_2_6_6_SystemObject bevs_super;

public:
BEC_2_8_8_EmbeddedAppShell* bevp_ash = nullptr;
BEC_2_4_3_MathInt* bevp_pini = nullptr;
BEC_2_4_3_MathInt* bevp_diri = nullptr;
BEC_2_8_6_EmbeddedConfig* bevp_config = nullptr;
BEC_2_8_3_EmbeddedApp* bevp_app = nullptr;
BEC_2_4_3_MathInt* bevp_ic = nullptr;
BEC_2_4_3_MathInt* bevp_lastSwEvent = nullptr;
BEC_2_4_3_MathInt* bevp_conPos = nullptr;
BEC_2_4_3_MathInt* bevp_lastEvent = nullptr;
BEC_2_4_6_TextString* bevp_conName = nullptr;
BEC_2_4_6_TextString* bevp_on = nullptr;
BEC_2_4_6_TextString* bevp_off = nullptr;
BEC_2_8_13_EmbeddedSwitchControl* bevp_sc = nullptr;
BEC_2_4_6_TextString* bevp_sw = nullptr;
virtual BEC_2_8_22_EmbeddedSwitchIndicatorControl* bem_new_4(BEC_2_6_6_SystemObject* bevk__ash, BEC_2_4_3_MathInt* bevk__conPos, BEC_2_4_6_TextString* bevk__conName, BEC_2_4_6_TextString* bevk__conArgs);
virtual BEC_2_8_22_EmbeddedSwitchIndicatorControl* bem_initControl_0();
virtual BEC_2_4_6_TextString* bem_doStateMq_2(BEC_2_4_6_TextString* bevk_topic, BEC_2_4_6_TextString* bevk_payload);
virtual BEC_2_4_6_TextString* bem_doState_1(BEC_2_9_4_ContainerList* bevk_cmdl);
virtual BEC_2_8_22_EmbeddedSwitchIndicatorControl* bem_clearStates_0();
virtual BEC_2_8_22_EmbeddedSwitchIndicatorControl* bem_handleLoop_0();
virtual BEC_2_8_22_EmbeddedSwitchIndicatorControl* bem_doSwitch_1(BEC_2_4_6_TextString* bevk_insw);
virtual BEC_2_4_3_MathInt* bem_conPosGet_0();
virtual BEC_2_8_22_EmbeddedSwitchIndicatorControl* bem_conPosSet_1(BEC_2_6_6_SystemObject* bevt_0_ta_SET);
virtual BEC_2_4_3_MathInt* bem_lastEventGet_0();
virtual BEC_2_8_22_EmbeddedSwitchIndicatorControl* bem_lastEventSet_1(BEC_2_6_6_SystemObject* bevt_0_ta_SET);
virtual BEC_2_4_6_TextString* bem_conNameGet_0();
virtual BEC_2_8_22_EmbeddedSwitchIndicatorControl* bem_conNameSet_1(BEC_2_6_6_SystemObject* bevt_0_ta_SET);
virtual BEC_2_4_6_TextString* bem_swGet_0();
virtual BEC_2_8_22_EmbeddedSwitchIndicatorControl* bem_swSet_1(BEC_2_6_6_SystemObject* bevt_0_ta_SET);
virtual BEC_2_6_6_SystemObject* bemc_create();
static BEC_2_8_22_EmbeddedSwitchIndicatorControl* bece_BEC_2_8_22_EmbeddedSwitchIndicatorControl_bevs_inst;
virtual void bemc_setInitial(BEC_2_6_6_SystemObject* becc_inst);
virtual BEC_2_6_6_SystemObject* bemc_getInitial();
virtual void bemg_doMark();
virtual size_t bemg_getSize();
virtual BETS_Object* bemc_getType();
virtual ~BEC_2_8_22_EmbeddedSwitchIndicatorControl() = default;
virtual BEC_2_6_6_SystemObject* bemd_0(int32_t callId);
virtual BEC_2_6_6_SystemObject* bemd_1(int32_t callId, BEC_2_6_6_SystemObject* bevd_0);
virtual BEC_2_6_6_SystemObject* bemd_2(int32_t callId, BEC_2_6_6_SystemObject* bevd_0, BEC_2_6_6_SystemObject* bevd_1);
virtual BEC_2_6_6_SystemObject* bemd_4(int32_t callId, BEC_2_6_6_SystemObject* bevd_0, BEC_2_6_6_SystemObject* bevd_1, BEC_2_6_6_SystemObject* bevd_2, BEC_2_6_6_SystemObject* bevd_3);
static BET_2_8_22_EmbeddedSwitchIndicatorControl bece_BEC_2_8_22_EmbeddedSwitchIndicatorControl_bevs_type;
};

class BET_2_4_3_MathInt : public BETS_Object {
public:
BET_2_4_3_MathInt();
virtual BEC_2_6_6_SystemObject* bems_createInstance();
virtual void bemgt_doMark();
static BEC_2_6_6_SystemObject** bevs_inst_ref;
};
class BEC_2_4_3_MathInt : public BEC_2_6_6_SystemObject {
private:
typedef BEC_2_6_6_SystemObject bevs_super;

public:
virtual BEC_2_4_3_MathInt* bem_vintGet_0();
virtual BEC_2_4_3_MathInt* bem_vintSet_0();
virtual BEC_2_6_6_SystemObject* bem_new_0();
virtual BEC_2_6_6_SystemObject* bem_create_0();
virtual BEC_2_4_3_MathInt* bem_new_1(BEC_2_6_6_SystemObject* bevk_str);
virtual BEC_2_4_3_MathInt* bem_hexNew_1(BEC_2_4_6_TextString* bevk_str);
virtual BEC_2_4_3_MathInt* bem_setStringValueDec_1(BEC_2_4_6_TextString* bevk_str);
virtual BEC_2_4_3_MathInt* bem_setStringValueHex_1(BEC_2_4_6_TextString* bevk_str);
virtual BEC_2_4_3_MathInt* bem_setStringValue_2(BEC_2_4_6_TextString* bevk_str, BEC_2_4_3_MathInt* bevk_radix);
virtual BEC_2_4_3_MathInt* bem_setStringValue_5(BEC_2_4_6_TextString* bevk_str, BEC_2_4_3_MathInt* bevk_radix, BEC_2_4_3_MathInt* bevk_max0, BEC_2_4_3_MathInt* bevk_maxA, BEC_2_4_3_MathInt* bevk_maxa);
virtual BEC_2_4_6_TextString* bem_serializeToString_0();
virtual BEC_2_4_3_MathInt* bem_deserializeFromStringNew_1(BEC_2_4_6_TextString* bevk_snw);
virtual BEC_2_5_4_LogicBool* bem_serializeContentsGet_0();
virtual BEC_2_4_3_MathInt* bem_hashGet_0();
virtual BEC_2_4_6_TextString* bem_toString_0();
virtual BEC_2_4_6_TextString* bem_toHexString_0();
virtual BEC_2_4_6_TextString* bem_toHexString_1(BEC_2_4_6_TextString* bevk_res);
virtual BEC_2_4_6_TextString* bem_toString_2(BEC_2_4_3_MathInt* bevk_zeroPad, BEC_2_4_3_MathInt* bevk_radix);
virtual BEC_2_4_6_TextString* bem_toString_3(BEC_2_4_6_TextString* bevk_res, BEC_2_4_3_MathInt* bevk_zeroPad, BEC_2_4_3_MathInt* bevk_radix);
virtual BEC_2_4_6_TextString* bem_toString_4(BEC_2_4_6_TextString* bevk_res, BEC_2_4_3_MathInt* bevk_zeroPad, BEC_2_4_3_MathInt* bevk_radix, BEC_2_4_3_MathInt* bevk_alphaStart);
virtual BEC_2_6_6_SystemObject* bem_copy_0();
virtual BEC_2_4_3_MathInt* bem_abs_0();
virtual BEC_2_4_3_MathInt* bem_absValue_0();
virtual BEC_2_4_3_MathInt* bem_setValue_1(BEC_2_4_3_MathInt* bevk_xi);
virtual BEC_2_4_3_MathInt* bem_increment_0();
virtual BEC_2_4_3_MathInt* bem_decrement_0();
virtual BEC_2_4_3_MathInt* bem_incrementValue_0();
virtual BEC_2_4_3_MathInt* bem_decrementValue_0();
virtual BEC_2_4_3_MathInt* bem_add_1(BEC_2_4_3_MathInt* bevk_xi);
virtual BEC_2_4_3_MathInt* bem_addValue_1(BEC_2_4_3_MathInt* bevk_xi);
virtual BEC_2_4_3_MathInt* bem_subtract_1(BEC_2_4_3_MathInt* bevk_xi);
virtual BEC_2_4_3_MathInt* bem_subtractValue_1(BEC_2_4_3_MathInt* bevk_xi);
virtual BEC_2_4_3_MathInt* bem_multiply_1(BEC_2_4_3_MathInt* bevk_xi);
virtual BEC_2_4_3_MathInt* bem_multiplyValue_1(BEC_2_4_3_MathInt* bevk_xi);
virtual BEC_2_4_3_MathInt* bem_divide_1(BEC_2_4_3_MathInt* bevk_xi);
virtual BEC_2_4_3_MathInt* bem_divideValue_1(BEC_2_4_3_MathInt* bevk_xi);
virtual BEC_2_4_3_MathInt* bem_modulus_1(BEC_2_4_3_MathInt* bevk_xi);
virtual BEC_2_4_3_MathInt* bem_modulusValue_1(BEC_2_4_3_MathInt* bevk_xi);
virtual BEC_2_4_3_MathInt* bem_and_1(BEC_2_4_3_MathInt* bevk_xi);
virtual BEC_2_4_3_MathInt* bem_andValue_1(BEC_2_4_3_MathInt* bevk_xi);
virtual BEC_2_4_3_MathInt* bem_or_1(BEC_2_4_3_MathInt* bevk_xi);
virtual BEC_2_4_3_MathInt* bem_orValue_1(BEC_2_4_3_MathInt* bevk_xi);
virtual BEC_2_4_3_MathInt* bem_shiftLeft_1(BEC_2_4_3_MathInt* bevk_xi);
virtual BEC_2_4_3_MathInt* bem_shiftLeftValue_1(BEC_2_4_3_MathInt* bevk_xi);
virtual BEC_2_4_3_MathInt* bem_shiftRight_1(BEC_2_4_3_MathInt* bevk_xi);
virtual BEC_2_4_3_MathInt* bem_shiftRightValue_1(BEC_2_4_3_MathInt* bevk_xi);
virtual BEC_2_4_3_MathInt* bem_power_1(BEC_2_4_3_MathInt* bevk_other);
virtual BEC_2_5_4_LogicBool* bem_equals_1(BEC_2_6_6_SystemObject* bevk_xi);
virtual BEC_2_5_4_LogicBool* bem_notEquals_1(BEC_2_6_6_SystemObject* bevk_xi);
virtual BEC_2_5_4_LogicBool* bem_greater_1(BEC_2_4_3_MathInt* bevk_xi);
virtual BEC_2_5_4_LogicBool* bem_lesser_1(BEC_2_4_3_MathInt* bevk_xi);
virtual BEC_2_5_4_LogicBool* bem_greaterEquals_1(BEC_2_4_3_MathInt* bevk_xi);
virtual BEC_2_5_4_LogicBool* bem_lesserEquals_1(BEC_2_4_3_MathInt* bevk_xi);
virtual BEC_2_6_6_SystemObject* bemc_create();
static BEC_2_4_3_MathInt* bece_BEC_2_4_3_MathInt_bevs_inst;
virtual void bemc_setInitial(BEC_2_6_6_SystemObject* becc_inst);
virtual BEC_2_6_6_SystemObject* bemc_getInitial();
virtual void bemg_doMark();
virtual size_t bemg_getSize();
virtual BETS_Object* bemc_getType();
virtual ~BEC_2_4_3_MathInt() = default;

    int32_t bevi_int = 0;
    BEC_2_4_3_MathInt() { 
    #ifdef BEDCC_SGC
        struct bes {  BEC_2_6_6_SystemObject* bevr_this;  };
        BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
        bes* beq = (bes*) bevs_myStack->bevs_hs;
        beq->bevr_this = this;
        BECS_StackFrame bevs_stackFrame(1);
    #endif
    }
    BEC_2_4_3_MathInt(int32_t a_bevi_int) { 
    #ifdef BEDCC_SGC
        struct bes {  BEC_2_6_6_SystemObject* bevr_this;  };
        BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
        bes* beq = (bes*) bevs_myStack->bevs_hs;
        beq->bevr_this = this;
        BECS_StackFrame bevs_stackFrame(1);
    #endif
      bevi_int = a_bevi_int; 
    }
  virtual BEC_2_6_6_SystemObject* bemd_0(int32_t callId);
virtual BEC_2_6_6_SystemObject* bemd_1(int32_t callId, BEC_2_6_6_SystemObject* bevd_0);
virtual BEC_2_6_6_SystemObject* bemd_2(int32_t callId, BEC_2_6_6_SystemObject* bevd_0, BEC_2_6_6_SystemObject* bevd_1);
virtual BEC_2_6_6_SystemObject* bemd_3(int32_t callId, BEC_2_6_6_SystemObject* bevd_0, BEC_2_6_6_SystemObject* bevd_1, BEC_2_6_6_SystemObject* bevd_2);
virtual BEC_2_6_6_SystemObject* bemd_4(int32_t callId, BEC_2_6_6_SystemObject* bevd_0, BEC_2_6_6_SystemObject* bevd_1, BEC_2_6_6_SystemObject* bevd_2, BEC_2_6_6_SystemObject* bevd_3);
virtual BEC_2_6_6_SystemObject* bemd_5(int32_t callId, BEC_2_6_6_SystemObject* bevd_0, BEC_2_6_6_SystemObject* bevd_1, BEC_2_6_6_SystemObject* bevd_2, BEC_2_6_6_SystemObject* bevd_3, BEC_2_6_6_SystemObject* bevd_4);
static BET_2_4_3_MathInt bece_BEC_2_4_3_MathInt_bevs_type;
};

class BET_2_4_4_MathInts : public BETS_Object {
public:
BET_2_4_4_MathInts();
virtual BEC_2_6_6_SystemObject* bems_createInstance();
virtual void bemgt_doMark();
static BEC_2_6_6_SystemObject** bevs_inst_ref;
};
class BEC_2_4_4_MathInts : public BEC_2_6_6_SystemObject {
private:
typedef BEC_2_6_6_SystemObject bevs_super;

public:
BEC_2_4_3_MathInt* bevp_max = nullptr;
BEC_2_4_3_MathInt* bevp_min = nullptr;
BEC_2_4_3_MathInt* bevp_zero = nullptr;
BEC_2_4_3_MathInt* bevp_one = nullptr;
virtual BEC_2_6_6_SystemObject* bem_create_0();
virtual BEC_2_4_4_MathInts* bem_default_0();
virtual BEC_2_6_6_SystemObject* bem_min_2(BEC_2_4_3_MathInt* bevk_a, BEC_2_4_3_MathInt* bevk_b);
virtual BEC_2_6_6_SystemObject* bem_max_2(BEC_2_4_3_MathInt* bevk_a, BEC_2_4_3_MathInt* bevk_b);
virtual BEC_2_4_3_MathInt* bem_maxGet_0();
virtual BEC_2_4_4_MathInts* bem_maxSet_1(BEC_2_6_6_SystemObject* bevt_0_ta_SET);
virtual BEC_2_4_3_MathInt* bem_minGet_0();
virtual BEC_2_4_4_MathInts* bem_minSet_1(BEC_2_6_6_SystemObject* bevt_0_ta_SET);
virtual BEC_2_4_3_MathInt* bem_zeroGet_0();
virtual BEC_2_4_4_MathInts* bem_zeroSet_1(BEC_2_6_6_SystemObject* bevt_0_ta_SET);
virtual BEC_2_4_3_MathInt* bem_oneGet_0();
virtual BEC_2_4_4_MathInts* bem_oneSet_1(BEC_2_6_6_SystemObject* bevt_0_ta_SET);
virtual BEC_2_6_6_SystemObject* bemc_create();
static BEC_2_4_4_MathInts* bece_BEC_2_4_4_MathInts_bevs_inst;
virtual void bemc_setInitial(BEC_2_6_6_SystemObject* becc_inst);
virtual BEC_2_6_6_SystemObject* bemc_getInitial();
virtual void bemg_doMark();
virtual size_t bemg_getSize();
virtual BETS_Object* bemc_getType();
virtual ~BEC_2_4_4_MathInts() = default;
virtual BEC_2_6_6_SystemObject* bemd_0(int32_t callId);
virtual BEC_2_6_6_SystemObject* bemd_1(int32_t callId, BEC_2_6_6_SystemObject* bevd_0);
virtual BEC_2_6_6_SystemObject* bemd_2(int32_t callId, BEC_2_6_6_SystemObject* bevd_0, BEC_2_6_6_SystemObject* bevd_1);
static BET_2_4_4_MathInts bece_BEC_2_4_4_MathInts_bevs_type;
};

class BET_2_4_6_TextString : public BETS_Object {
public:
BET_2_4_6_TextString();
virtual BEC_2_6_6_SystemObject* bems_createInstance();
virtual void bemgt_doMark();
static BEC_2_6_6_SystemObject** bevs_inst_ref;
};
class BEC_2_4_6_TextString : public BEC_2_6_6_SystemObject {
private:
typedef BEC_2_6_6_SystemObject bevs_super;

public:
BEC_2_4_3_MathInt* bevp_size = nullptr;
BEC_2_4_3_MathInt* bevp_capacity = nullptr;
virtual BEC_2_4_6_TextString* bem_vstringGet_0();
virtual BEC_2_4_6_TextString* bem_vstringSet_0();
virtual BEC_2_4_6_TextString* bem_new_1(BEC_2_4_3_MathInt* bevk__capacity);
virtual BEC_2_6_6_SystemObject* bem_new_0();
virtual BEC_2_4_6_TextString* bem_capacitySet_1(BEC_2_4_3_MathInt* bevk_ncap);
virtual BEC_2_4_6_TextString* bem_hexNew_1(BEC_2_4_6_TextString* bevk_val);
virtual BEC_2_4_6_TextString* bem_getHex_1(BEC_2_4_3_MathInt* bevk_pos);
virtual BEC_2_4_6_TextString* bem_setHex_2(BEC_2_4_3_MathInt* bevk_pos, BEC_2_4_6_TextString* bevk_hval);
virtual BEC_2_4_6_TextString* bem_addValue_1(BEC_2_6_6_SystemObject* bevk_astr);
virtual BEC_2_4_6_TextString* bem_readBuffer_0();
virtual BEC_2_4_6_TextString* bem_readString_0();
virtual BEC_2_4_6_TextString* bem_write_1(BEC_2_6_6_SystemObject* bevk_stri);
virtual BEC_2_4_6_TextString* bem_writeTo_1(BEC_2_6_6_SystemObject* bevk_w);
virtual BEC_2_4_6_TextString* bem_open_0();
virtual BEC_2_4_6_TextString* bem_close_0();
virtual BEC_2_4_6_TextString* bem_extractString_0();
virtual BEC_2_4_6_TextString* bem_clear_0();
virtual BEC_2_4_6_TextString* bem_codeNew_1(BEC_2_6_6_SystemObject* bevk_codei);
virtual BEC_2_4_6_TextString* bem_chomp_0();
virtual BEC_2_6_6_SystemObject* bem_copy_0();
virtual BEC_2_5_4_LogicBool* bem_begins_1(BEC_2_4_6_TextString* bevk_str);
virtual BEC_2_5_4_LogicBool* bem_ends_1(BEC_2_4_6_TextString* bevk_str);
virtual BEC_2_5_4_LogicBool* bem_has_1(BEC_2_4_6_TextString* bevk_str);
virtual BEC_2_5_4_LogicBool* bem_isIntegerGet_0();
virtual BEC_2_5_4_LogicBool* bem_isInteger_0();
virtual BEC_2_5_4_LogicBool* bem_isAlphaNumGet_0();
virtual BEC_2_5_4_LogicBool* bem_isAlphaNumericGet_0();
virtual BEC_2_4_6_TextString* bem_lowerValue_0();
virtual BEC_2_4_6_TextString* bem_lower_0();
virtual BEC_2_4_6_TextString* bem_upperValue_0();
virtual BEC_2_4_6_TextString* bem_upper_0();
virtual BEC_2_6_6_SystemObject* bem_swapFirst_2(BEC_2_4_6_TextString* bevk_from, BEC_2_4_6_TextString* bevk_to);
virtual BEC_2_6_6_SystemObject* bem_swap_2(BEC_2_4_6_TextString* bevk_from, BEC_2_4_6_TextString* bevk_to);
virtual BEC_2_4_6_TextString* bem_getPoint_1(BEC_2_4_3_MathInt* bevk_posi);
virtual BEC_2_4_3_MathInt* bem_hashValue_1(BEC_2_4_3_MathInt* bevk_into);
virtual BEC_2_4_3_MathInt* bem_hashGet_0();
virtual BEC_2_4_3_MathInt* bem_getCode_1(BEC_2_4_3_MathInt* bevk_pos);
virtual BEC_2_4_3_MathInt* bem_getInt_2(BEC_2_4_3_MathInt* bevk_pos, BEC_2_4_3_MathInt* bevk_into);
virtual BEC_2_4_3_MathInt* bem_getCode_2(BEC_2_4_3_MathInt* bevk_pos, BEC_2_4_3_MathInt* bevk_into);
virtual BEC_2_4_6_TextString* bem_setInt_2(BEC_2_4_3_MathInt* bevk_pos, BEC_2_4_3_MathInt* bevk_into);
virtual BEC_2_4_6_TextString* bem_setCode_2(BEC_2_4_3_MathInt* bevk_pos, BEC_2_4_3_MathInt* bevk_into);
virtual BEC_2_4_6_TextString* bem_toAlphaNum_0();
virtual BEC_2_5_4_LogicBool* bem_isEmptyGet_0();
virtual BEC_2_4_6_TextString* bem_setIntUnchecked_2(BEC_2_4_3_MathInt* bevk_pos, BEC_2_4_3_MathInt* bevk_into);
virtual BEC_2_4_6_TextString* bem_setCodeUnchecked_2(BEC_2_4_3_MathInt* bevk_pos, BEC_2_4_3_MathInt* bevk_into);
virtual BEC_2_4_3_MathInt* bem_reverseFind_1(BEC_2_4_6_TextString* bevk_str);
virtual BEC_2_4_3_MathInt* bem_rfind_1(BEC_2_4_6_TextString* bevk_str);
virtual BEC_2_4_3_MathInt* bem_find_1(BEC_2_4_6_TextString* bevk_str);
virtual BEC_2_4_3_MathInt* bem_find_2(BEC_2_4_6_TextString* bevk_str, BEC_2_4_3_MathInt* bevk_start);
virtual BEC_2_9_4_ContainerList* bem_split_1(BEC_2_4_6_TextString* bevk_delim);
virtual BEC_2_4_6_TextString* bem_join_2(BEC_2_4_6_TextString* bevk_delim, BEC_2_6_6_SystemObject* bevk_splits);
virtual BEC_2_4_6_TextString* bem_toString_0();
virtual BEC_2_4_3_MathInt* bem_compare_1(BEC_2_6_6_SystemObject* bevk_stri);
virtual BEC_2_5_4_LogicBool* bem_lesser_1(BEC_2_4_6_TextString* bevk_stri);
virtual BEC_2_5_4_LogicBool* bem_greater_1(BEC_2_4_6_TextString* bevk_stri);
virtual BEC_2_5_4_LogicBool* bem_equals_1(BEC_2_6_6_SystemObject* bevk_stri);
virtual BEC_2_5_4_LogicBool* bem_notEquals_1(BEC_2_6_6_SystemObject* bevk_str);
virtual BEC_2_4_6_TextString* bem_add_1(BEC_2_6_6_SystemObject* bevk_astr);
virtual BEC_2_6_6_SystemObject* bem_create_0();
virtual BEC_2_4_6_TextString* bem_copyValue_4(BEC_2_4_6_TextString* bevk_org, BEC_2_4_3_MathInt* bevk_starti, BEC_2_4_3_MathInt* bevk_endi, BEC_2_4_3_MathInt* bevk_dstarti);
virtual BEC_2_4_6_TextString* bem_substring_1(BEC_2_4_3_MathInt* bevk_starti);
virtual BEC_2_4_6_TextString* bem_substring_2(BEC_2_4_3_MathInt* bevk_starti, BEC_2_4_3_MathInt* bevk_endi);
virtual BEC_2_4_6_TextString* bem_output_0();
virtual BEC_2_6_6_SystemObject* bem_print_0();
virtual BEC_2_4_6_TextString* bem_echo_0();
virtual BEC_2_6_6_SystemObject* bem_iteratorGet_0();
virtual BEC_2_4_12_TextByteIterator* bem_byteIteratorGet_0();
virtual BEC_2_4_17_TextMultiByteIterator* bem_multiByteIteratorGet_0();
virtual BEC_2_4_12_TextByteIterator* bem_biterGet_0();
virtual BEC_2_4_17_TextMultiByteIterator* bem_mbiterGet_0();
virtual BEC_2_4_17_TextMultiByteIterator* bem_stringIteratorGet_0();
virtual BEC_2_4_6_TextString* bem_serializeToString_0();
virtual BEC_2_4_6_TextString* bem_deserializeFromStringNew_1(BEC_2_4_6_TextString* bevk_snw);
virtual BEC_2_5_4_LogicBool* bem_serializeContentsGet_0();
virtual BEC_2_6_6_SystemObject* bem_strip_0();
virtual BEC_2_4_6_TextString* bem_reverseBytes_0();
virtual BEC_2_4_3_MathInt* bem_sizeGet_0();
virtual BEC_2_4_6_TextString* bem_sizeSet_1(BEC_2_6_6_SystemObject* bevt_0_ta_SET);
virtual BEC_2_4_3_MathInt* bem_capacityGet_0();
virtual BEC_2_6_6_SystemObject* bemc_create();
static BEC_2_4_6_TextString* bece_BEC_2_4_6_TextString_bevs_inst;
virtual void bemc_setInitial(BEC_2_6_6_SystemObject* becc_inst);
virtual BEC_2_6_6_SystemObject* bemc_getInitial();
virtual void bemg_doMark();
virtual size_t bemg_getSize();
virtual BETS_Object* bemc_getType();
virtual ~BEC_2_4_6_TextString() = default;


#ifdef BEDCC_SGC
    std::vector<unsigned char> bevi_bytes;
#endif

   BEC_2_4_6_TextString() {  
#ifdef BEDCC_SGC
   struct bes {  BEC_2_6_6_SystemObject* bevr_this;  };
   BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
   bes* beq = (bes*) bevs_myStack->bevs_hs;
   beq->bevr_this = this;
   BECS_StackFrame bevs_stackFrame(1);
#endif
   }

#ifdef BEDCC_SGC
    BEC_2_4_6_TextString(int32_t bevi_length, std::vector<unsigned char>& a_bevi_bytes) { 
#endif 
#ifdef BEDCC_SGC
      struct bes {  BEC_2_6_6_SystemObject* bevr_this;  };
      BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
      bes* beq = (bes*) bevs_myStack->bevs_hs;
      beq->bevr_this = this;
      BECS_StackFrame bevs_stackFrame(1);
#endif
      bevi_bytes = a_bevi_bytes;
      bevp_size = nullptr;
      bevp_capacity = nullptr;
      bevp_size = new BEC_2_4_3_MathInt(bevi_length);
      bevp_capacity = new BEC_2_4_3_MathInt(bevi_length);
    } //}
    
    #ifdef BEDCC_SGC
        BEC_2_4_6_TextString(int32_t bevi_length, std::initializer_list<unsigned char> a_bevi_bytes) { 
    #endif 
    #ifdef BEDCC_SGC
      struct bes {  BEC_2_6_6_SystemObject* bevr_this;  };
      BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
      bes* beq = (bes*) bevs_myStack->bevs_hs;
      beq->bevr_this = this;
      BECS_StackFrame bevs_stackFrame(1);
    #endif
          bevi_bytes = a_bevi_bytes;
          bevp_size = nullptr;
          bevp_capacity = nullptr;
          bevp_size = new BEC_2_4_3_MathInt(bevi_length);
          bevp_capacity = new BEC_2_4_3_MathInt(bevi_length);
        } //}
    
    BEC_2_4_6_TextString(std::string bevi_string) {
    #ifdef BEDCC_SGC
      struct bes {  BEC_2_6_6_SystemObject* bevr_this;  };
      BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
      bes* beq = (bes*) bevs_myStack->bevs_hs;
      beq->bevr_this = this;
      BECS_StackFrame bevs_stackFrame(1);
    #endif
      bevi_bytes.insert(bevi_bytes.begin(), bevi_string.begin(), bevi_string.end());
      bevp_size = nullptr;
      bevp_capacity = nullptr;
      bevp_size = new BEC_2_4_3_MathInt(bevi_bytes.size());
      bevp_capacity = new BEC_2_4_3_MathInt(bevi_bytes.size());
    }
    
    std::string bems_toCcString();
    char* bems_c_str(char* buf, int mxlen);
    
   virtual BEC_2_6_6_SystemObject* bemd_0(int32_t callId);
virtual BEC_2_6_6_SystemObject* bemd_1(int32_t callId, BEC_2_6_6_SystemObject* bevd_0);
virtual BEC_2_6_6_SystemObject* bemd_2(int32_t callId, BEC_2_6_6_SystemObject* bevd_0, BEC_2_6_6_SystemObject* bevd_1);
virtual BEC_2_6_6_SystemObject* bemd_4(int32_t callId, BEC_2_6_6_SystemObject* bevd_0, BEC_2_6_6_SystemObject* bevd_1, BEC_2_6_6_SystemObject* bevd_2, BEC_2_6_6_SystemObject* bevd_3);
static BET_2_4_6_TextString bece_BEC_2_4_6_TextString_bevs_type;
};

class BET_2_4_7_TextStrings : public BETS_Object {
public:
BET_2_4_7_TextStrings();
virtual BEC_2_6_6_SystemObject* bems_createInstance();
virtual void bemgt_doMark();
static BEC_2_6_6_SystemObject** bevs_inst_ref;
};
class BEC_2_4_7_TextStrings : public BEC_2_6_6_SystemObject {
private:
typedef BEC_2_6_6_SystemObject bevs_super;

public:
BEC_2_4_3_MathInt* bevp_zero = nullptr;
BEC_2_4_3_MathInt* bevp_one = nullptr;
BEC_2_4_6_TextString* bevp_space = nullptr;
BEC_2_4_6_TextString* bevp_empty = nullptr;
BEC_2_4_6_TextString* bevp_quote = nullptr;
BEC_2_4_6_TextString* bevp_tab = nullptr;
BEC_2_4_6_TextString* bevp_dosNewline = nullptr;
BEC_2_4_6_TextString* bevp_unixNewline = nullptr;
BEC_2_4_6_TextString* bevp_newline = nullptr;
BEC_2_4_6_TextString* bevp_cr = nullptr;
BEC_2_4_6_TextString* bevp_lf = nullptr;
BEC_2_4_6_TextString* bevp_colon = nullptr;
virtual BEC_2_6_6_SystemObject* bem_create_0();
virtual BEC_2_4_7_TextStrings* bem_default_0();
virtual BEC_2_4_6_TextString* bem_join_2(BEC_2_4_6_TextString* bevk_delim, BEC_2_6_6_SystemObject* bevk_splits);
virtual BEC_2_4_6_TextString* bem_joinBuffer_2(BEC_2_4_6_TextString* bevk_delim, BEC_2_6_6_SystemObject* bevk_splits);
virtual BEC_2_6_6_SystemObject* bem_strip_1(BEC_2_4_6_TextString* bevk_str);
virtual BEC_2_4_6_TextString* bem_commonPrefix_2(BEC_2_4_6_TextString* bevk_a, BEC_2_4_6_TextString* bevk_b);
virtual BEC_2_5_4_LogicBool* bem_anyEmpty_1(BEC_2_6_6_SystemObject* bevk_strs);
virtual BEC_2_5_4_LogicBool* bem_isEmpty_1(BEC_2_4_6_TextString* bevk_value);
virtual BEC_2_5_4_LogicBool* bem_notEmpty_1(BEC_2_4_6_TextString* bevk_value);
virtual BEC_2_4_3_MathInt* bem_zeroGet_0();
virtual BEC_2_4_7_TextStrings* bem_zeroSet_1(BEC_2_6_6_SystemObject* bevt_0_ta_SET);
virtual BEC_2_4_3_MathInt* bem_oneGet_0();
virtual BEC_2_4_7_TextStrings* bem_oneSet_1(BEC_2_6_6_SystemObject* bevt_0_ta_SET);
virtual BEC_2_4_6_TextString* bem_spaceGet_0();
virtual BEC_2_4_7_TextStrings* bem_spaceSet_1(BEC_2_6_6_SystemObject* bevt_0_ta_SET);
virtual BEC_2_4_6_TextString* bem_emptyGet_0();
virtual BEC_2_4_7_TextStrings* bem_emptySet_1(BEC_2_6_6_SystemObject* bevt_0_ta_SET);
virtual BEC_2_4_6_TextString* bem_quoteGet_0();
virtual BEC_2_4_7_TextStrings* bem_quoteSet_1(BEC_2_6_6_SystemObject* bevt_0_ta_SET);
virtual BEC_2_4_6_TextString* bem_tabGet_0();
virtual BEC_2_4_7_TextStrings* bem_tabSet_1(BEC_2_6_6_SystemObject* bevt_0_ta_SET);
virtual BEC_2_4_6_TextString* bem_dosNewlineGet_0();
virtual BEC_2_4_7_TextStrings* bem_dosNewlineSet_1(BEC_2_6_6_SystemObject* bevt_0_ta_SET);
virtual BEC_2_4_6_TextString* bem_unixNewlineGet_0();
virtual BEC_2_4_7_TextStrings* bem_unixNewlineSet_1(BEC_2_6_6_SystemObject* bevt_0_ta_SET);
virtual BEC_2_4_6_TextString* bem_newlineGet_0();
virtual BEC_2_4_7_TextStrings* bem_newlineSet_1(BEC_2_6_6_SystemObject* bevt_0_ta_SET);
virtual BEC_2_4_6_TextString* bem_crGet_0();
virtual BEC_2_4_7_TextStrings* bem_crSet_1(BEC_2_6_6_SystemObject* bevt_0_ta_SET);
virtual BEC_2_4_6_TextString* bem_lfGet_0();
virtual BEC_2_4_7_TextStrings* bem_lfSet_1(BEC_2_6_6_SystemObject* bevt_0_ta_SET);
virtual BEC_2_4_6_TextString* bem_colonGet_0();
virtual BEC_2_4_7_TextStrings* bem_colonSet_1(BEC_2_6_6_SystemObject* bevt_0_ta_SET);
virtual BEC_2_6_6_SystemObject* bemc_create();
static BEC_2_4_7_TextStrings* bece_BEC_2_4_7_TextStrings_bevs_inst;
virtual void bemc_setInitial(BEC_2_6_6_SystemObject* becc_inst);
virtual BEC_2_6_6_SystemObject* bemc_getInitial();
virtual void bemg_doMark();
virtual size_t bemg_getSize();
virtual BETS_Object* bemc_getType();
virtual ~BEC_2_4_7_TextStrings() = default;
virtual BEC_2_6_6_SystemObject* bemd_0(int32_t callId);
virtual BEC_2_6_6_SystemObject* bemd_1(int32_t callId, BEC_2_6_6_SystemObject* bevd_0);
virtual BEC_2_6_6_SystemObject* bemd_2(int32_t callId, BEC_2_6_6_SystemObject* bevd_0, BEC_2_6_6_SystemObject* bevd_1);
static BET_2_4_7_TextStrings bece_BEC_2_4_7_TextStrings_bevs_type;
};

class BET_2_4_12_TextByteIterator : public BETS_Object {
public:
BET_2_4_12_TextByteIterator();
virtual BEC_2_6_6_SystemObject* bems_createInstance();
virtual void bemgt_doMark();
static BEC_2_6_6_SystemObject** bevs_inst_ref;
};
class BEC_2_4_12_TextByteIterator : public BEC_2_6_6_SystemObject {
private:
typedef BEC_2_6_6_SystemObject bevs_super;

public:
BEC_2_4_3_MathInt* bevp_pos = nullptr;
BEC_2_4_6_TextString* bevp_str = nullptr;
BEC_2_4_3_MathInt* bevp_vcopy = nullptr;
virtual BEC_2_6_6_SystemObject* bem_new_0();
virtual BEC_2_4_6_TextString* bem_containerGet_0();
virtual BEC_2_4_6_TextString* bem_serializeToString_0();
virtual BEC_2_4_12_TextByteIterator* bem_deserializeFromStringNew_1(BEC_2_4_6_TextString* bevk_str);
virtual BEC_2_4_12_TextByteIterator* bem_new_1(BEC_2_4_6_TextString* bevk__str);
virtual BEC_2_5_4_LogicBool* bem_hasNextGet_0();
virtual BEC_2_4_6_TextString* bem_nextGet_0();
virtual BEC_2_4_6_TextString* bem_next_1(BEC_2_4_6_TextString* bevk_buf);
virtual BEC_2_4_3_MathInt* bem_nextInt_1(BEC_2_4_3_MathInt* bevk_into);
virtual BEC_2_4_3_MathInt* bem_currentInt_1(BEC_2_4_3_MathInt* bevk_into);
virtual BEC_2_4_12_TextByteIterator* bem_currentIntSet_1(BEC_2_4_3_MathInt* bevk_into);
virtual BEC_2_6_6_SystemObject* bem_iteratorGet_0();
virtual BEC_2_4_12_TextByteIterator* bem_byteIteratorIteratorGet_0();
virtual BEC_2_4_3_MathInt* bem_posGet_0();
virtual BEC_2_4_12_TextByteIterator* bem_posSet_1(BEC_2_6_6_SystemObject* bevt_0_ta_SET);
virtual BEC_2_6_6_SystemObject* bemc_create();
static BEC_2_4_12_TextByteIterator* bece_BEC_2_4_12_TextByteIterator_bevs_inst;
virtual void bemc_setInitial(BEC_2_6_6_SystemObject* becc_inst);
virtual BEC_2_6_6_SystemObject* bemc_getInitial();
virtual void bemg_doMark();
virtual size_t bemg_getSize();
virtual BETS_Object* bemc_getType();
virtual ~BEC_2_4_12_TextByteIterator() = default;
virtual BEC_2_6_6_SystemObject* bemd_0(int32_t callId);
virtual BEC_2_6_6_SystemObject* bemd_1(int32_t callId, BEC_2_6_6_SystemObject* bevd_0);
static BET_2_4_12_TextByteIterator bece_BEC_2_4_12_TextByteIterator_bevs_type;
};

class BET_2_5_4_LogicBool : public BETS_Object {
public:
BET_2_5_4_LogicBool();
virtual BEC_2_6_6_SystemObject* bems_createInstance();
virtual void bemgt_doMark();
static BEC_2_6_6_SystemObject** bevs_inst_ref;
};
class BEC_2_5_4_LogicBool : public BEC_2_6_6_SystemObject {
private:
typedef BEC_2_6_6_SystemObject bevs_super;

public:
virtual BEC_2_6_6_SystemObject* bem_new_0();
virtual BEC_2_5_4_LogicBool* bem_new_1(BEC_2_6_6_SystemObject* bevk_str);
virtual BEC_2_5_4_LogicBool* bem_checkDefNew_1(BEC_2_6_6_SystemObject* bevk_str);
virtual BEC_2_5_4_LogicBool* bem_serializeContentsGet_0();
virtual BEC_2_4_6_TextString* bem_serializeToString_0();
virtual BEC_2_4_6_TextString* bem_deserializeClassNameGet_0();
virtual BEC_2_4_3_MathInt* bem_hashGet_0();
virtual BEC_2_5_4_LogicBool* bem_increment_0();
virtual BEC_2_5_4_LogicBool* bem_decrement_0();
virtual BEC_2_5_4_LogicBool* bem_not_0();
virtual BEC_2_4_6_TextString* bem_toString_0();
virtual BEC_2_6_6_SystemObject* bem_copy_0();
virtual BEC_2_6_6_SystemObject* bemc_create();
static BEC_2_5_4_LogicBool* bece_BEC_2_5_4_LogicBool_bevs_inst;
virtual void bemc_setInitial(BEC_2_6_6_SystemObject* becc_inst);
virtual BEC_2_6_6_SystemObject* bemc_getInitial();
virtual void bemg_doMark();
virtual size_t bemg_getSize();
virtual BETS_Object* bemc_getType();
virtual ~BEC_2_5_4_LogicBool() = default;

    bool bevi_bool;
    BEC_2_5_4_LogicBool() { bevi_bool = false; }
    BEC_2_5_4_LogicBool(bool a_bevi_bool) { bevi_bool = a_bevi_bool; }
  virtual BEC_2_6_6_SystemObject* bemd_0(int32_t callId);
virtual BEC_2_6_6_SystemObject* bemd_1(int32_t callId, BEC_2_6_6_SystemObject* bevd_0);
static BET_2_5_4_LogicBool bece_BEC_2_5_4_LogicBool_bevs_type;
};

class BET_2_5_5_LogicBools : public BETS_Object {
public:
BET_2_5_5_LogicBools();
virtual BEC_2_6_6_SystemObject* bems_createInstance();
virtual void bemgt_doMark();
static BEC_2_6_6_SystemObject** bevs_inst_ref;
};
class BEC_2_5_5_LogicBools : public BEC_2_6_6_SystemObject {
private:
typedef BEC_2_6_6_SystemObject bevs_super;

public:
virtual BEC_2_6_6_SystemObject* bem_create_0();
virtual BEC_2_5_5_LogicBools* bem_default_0();
virtual BEC_2_5_4_LogicBool* bem_forString_1(BEC_2_6_6_SystemObject* bevk_str);
virtual BEC_2_5_4_LogicBool* bem_fromString_1(BEC_2_6_6_SystemObject* bevk_str);
virtual BEC_2_6_6_SystemObject* bem_deserializeFromString_1(BEC_2_4_6_TextString* bevk_str);
virtual BEC_2_6_6_SystemObject* bem_isTrue_1(BEC_2_5_4_LogicBool* bevk_val);
virtual BEC_2_6_6_SystemObject* bemc_create();
static BEC_2_5_5_LogicBools* bece_BEC_2_5_5_LogicBools_bevs_inst;
virtual void bemc_setInitial(BEC_2_6_6_SystemObject* becc_inst);
virtual BEC_2_6_6_SystemObject* bemc_getInitial();
virtual void bemg_doMark();
virtual size_t bemg_getSize();
virtual BETS_Object* bemc_getType();
virtual ~BEC_2_5_5_LogicBools() = default;
virtual BEC_2_6_6_SystemObject* bemd_0(int32_t callId);
virtual BEC_2_6_6_SystemObject* bemd_1(int32_t callId, BEC_2_6_6_SystemObject* bevd_0);
static BET_2_5_5_LogicBools bece_BEC_2_5_5_LogicBools_bevs_type;
};

class BET_2_6_3_EncodeHex : public BETS_Object {
public:
BET_2_6_3_EncodeHex();
virtual BEC_2_6_6_SystemObject* bems_createInstance();
virtual void bemgt_doMark();
static BEC_2_6_6_SystemObject** bevs_inst_ref;
};
class BEC_2_6_3_EncodeHex : public BEC_2_6_6_SystemObject {
private:
typedef BEC_2_6_6_SystemObject bevs_super;

public:
virtual BEC_2_6_6_SystemObject* bem_create_0();
virtual BEC_2_6_3_EncodeHex* bem_default_0();
virtual BEC_2_4_6_TextString* bem_encode_1(BEC_2_4_6_TextString* bevk_str);
virtual BEC_2_4_6_TextString* bem_decode_1(BEC_2_4_6_TextString* bevk_str);
virtual BEC_2_6_6_SystemObject* bemc_create();
static BEC_2_6_3_EncodeHex* bece_BEC_2_6_3_EncodeHex_bevs_inst;
virtual void bemc_setInitial(BEC_2_6_6_SystemObject* becc_inst);
virtual BEC_2_6_6_SystemObject* bemc_getInitial();
virtual void bemg_doMark();
virtual size_t bemg_getSize();
virtual BETS_Object* bemc_getType();
virtual ~BEC_2_6_3_EncodeHex() = default;
virtual BEC_2_6_6_SystemObject* bemd_0(int32_t callId);
virtual BEC_2_6_6_SystemObject* bemd_1(int32_t callId, BEC_2_6_6_SystemObject* bevd_0);
static BET_2_6_3_EncodeHex bece_BEC_2_6_3_EncodeHex_bevs_type;
};

class BET_2_6_3_EncodeUrl : public BETS_Object {
public:
BET_2_6_3_EncodeUrl();
virtual BEC_2_6_6_SystemObject* bems_createInstance();
virtual void bemgt_doMark();
static BEC_2_6_6_SystemObject** bevs_inst_ref;
};
class BEC_2_6_3_EncodeUrl : public BEC_2_6_6_SystemObject {
private:
typedef BEC_2_6_6_SystemObject bevs_super;

public:
virtual BEC_2_6_6_SystemObject* bem_create_0();
virtual BEC_2_6_3_EncodeUrl* bem_default_0();
virtual BEC_2_4_6_TextString* bem_encode_1(BEC_2_4_6_TextString* bevk_str);
virtual BEC_2_4_6_TextString* bem_decode_1(BEC_2_4_6_TextString* bevk_str);
virtual BEC_2_6_6_SystemObject* bemc_create();
static BEC_2_6_3_EncodeUrl* bece_BEC_2_6_3_EncodeUrl_bevs_inst;
virtual void bemc_setInitial(BEC_2_6_6_SystemObject* becc_inst);
virtual BEC_2_6_6_SystemObject* bemc_getInitial();
virtual void bemg_doMark();
virtual size_t bemg_getSize();
virtual BETS_Object* bemc_getType();
virtual ~BEC_2_6_3_EncodeUrl() = default;
virtual BEC_2_6_6_SystemObject* bemd_0(int32_t callId);
virtual BEC_2_6_6_SystemObject* bemd_1(int32_t callId, BEC_2_6_6_SystemObject* bevd_0);
static BET_2_6_3_EncodeUrl bece_BEC_2_6_3_EncodeUrl_bevs_type;
};

class BET_3_9_4_8_ContainerListIterator : public BETS_Object {
public:
BET_3_9_4_8_ContainerListIterator();
virtual BEC_2_6_6_SystemObject* bems_createInstance();
virtual void bemgt_doMark();
static BEC_2_6_6_SystemObject** bevs_inst_ref;
};
class BEC_3_9_4_8_ContainerListIterator : public BEC_2_6_6_SystemObject {
private:
typedef BEC_2_6_6_SystemObject bevs_super;

public:
BEC_2_4_3_MathInt* bevp_pos = nullptr;
BEC_2_9_4_ContainerList* bevp_list = nullptr;
BEC_2_4_3_MathInt* bevp_npos = nullptr;
BEC_2_4_3_MathInt* bevp_none = nullptr;
BEC_2_4_3_MathInt* bevp_zero = nullptr;
virtual BEC_2_6_6_SystemObject* bem_new_0();
virtual BEC_3_9_4_8_ContainerListIterator* bem_new_1(BEC_2_6_6_SystemObject* bevk_a);
virtual BEC_2_9_4_ContainerList* bem_containerGet_0();
virtual BEC_2_5_4_LogicBool* bem_hasCurrentGet_0();
virtual BEC_2_5_4_LogicBool* bem_currentGet_0();
virtual BEC_2_6_6_SystemObject* bem_currentSet_1(BEC_2_6_6_SystemObject* bevk_toSet);
virtual BEC_2_5_4_LogicBool* bem_hasNextGet_0();
virtual BEC_2_6_6_SystemObject* bem_nextGet_0();
virtual BEC_2_6_6_SystemObject* bem_nextSet_1(BEC_2_6_6_SystemObject* bevk_toSet);
virtual BEC_3_9_4_8_ContainerListIterator* bem_skip_1(BEC_2_4_3_MathInt* bevk_multiNullCount);
virtual BEC_2_6_6_SystemObject* bemc_create();
static BEC_3_9_4_8_ContainerListIterator* bece_BEC_3_9_4_8_ContainerListIterator_bevs_inst;
virtual void bemc_setInitial(BEC_2_6_6_SystemObject* becc_inst);
virtual BEC_2_6_6_SystemObject* bemc_getInitial();
virtual void bemg_doMark();
virtual size_t bemg_getSize();
virtual BETS_Object* bemc_getType();
virtual ~BEC_3_9_4_8_ContainerListIterator() = default;
virtual BEC_2_6_6_SystemObject* bemd_0(int32_t callId);
virtual BEC_2_6_6_SystemObject* bemd_1(int32_t callId, BEC_2_6_6_SystemObject* bevd_0);
static BET_3_9_4_8_ContainerListIterator bece_BEC_3_9_4_8_ContainerListIterator_bevs_type;
};

class BET_2_9_4_ContainerList : public BETS_Object {
public:
BET_2_9_4_ContainerList();
virtual BEC_2_6_6_SystemObject* bems_createInstance();
virtual void bemgt_doMark();
static BEC_2_6_6_SystemObject** bevs_inst_ref;
};
class BEC_2_9_4_ContainerList : public BEC_2_6_6_SystemObject {
private:
typedef BEC_2_6_6_SystemObject bevs_super;

public:
BEC_2_4_3_MathInt* bevp_length = nullptr;
BEC_2_4_3_MathInt* bevp_capacity = nullptr;
BEC_2_4_3_MathInt* bevp_multiplier = nullptr;
virtual BEC_2_6_6_SystemObject* bem_new_0();
virtual BEC_2_9_4_ContainerList* bem_new_1(BEC_2_4_3_MathInt* bevk_leni);
virtual BEC_2_9_4_ContainerList* bem_new_2(BEC_2_4_3_MathInt* bevk_leni, BEC_2_4_3_MathInt* bevk_capi);
virtual BEC_2_4_3_MathInt* bem_sizeGet_0();
virtual BEC_2_9_4_ContainerList* bem_sizeSet_1(BEC_2_4_3_MathInt* bevk_val);
virtual BEC_2_5_4_LogicBool* bem_isEmptyGet_0();
virtual BEC_2_9_4_ContainerList* bem_anyrayGet_0();
virtual BEC_2_9_4_ContainerList* bem_anyraySet_0();
virtual BEC_2_4_6_TextString* bem_serializeToString_0();
virtual BEC_2_9_4_ContainerList* bem_deserializeFromStringNew_1(BEC_2_4_6_TextString* bevk_snw);
virtual BEC_2_6_6_SystemObject* bem_firstGet_0();
virtual BEC_2_6_6_SystemObject* bem_lastGet_0();
virtual BEC_2_9_4_ContainerList* bem_put_2(BEC_2_4_3_MathInt* bevk_posi, BEC_2_6_6_SystemObject* bevk_val);
virtual BEC_2_6_6_SystemObject* bem_get_1(BEC_2_4_3_MathInt* bevk_posi);
virtual BEC_2_6_6_SystemObject* bem_delete_1(BEC_2_4_3_MathInt* bevk_pos);
virtual BEC_2_6_6_SystemObject* bem_iteratorGet_0();
virtual BEC_3_9_4_8_ContainerListIterator* bem_arrayIteratorGet_0();
virtual BEC_2_9_4_ContainerList* bem_clear_0();
virtual BEC_2_6_6_SystemObject* bem_copy_0();
virtual BEC_2_6_6_SystemObject* bem_create_1(BEC_2_4_3_MathInt* bevk_len);
virtual BEC_2_6_6_SystemObject* bem_create_0();
virtual BEC_2_9_4_ContainerList* bem_add_1(BEC_2_9_4_ContainerList* bevk_xi);
virtual BEC_2_9_4_ContainerList* bem_sort_0();
virtual BEC_2_9_4_ContainerList* bem_sortValue_0();
virtual BEC_2_9_4_ContainerList* bem_sortValue_2(BEC_2_4_3_MathInt* bevk_start, BEC_2_4_3_MathInt* bevk_end);
virtual BEC_2_9_4_ContainerList* bem_mergeIn_2(BEC_2_9_4_ContainerList* bevk_first, BEC_2_9_4_ContainerList* bevk_second);
virtual BEC_2_9_4_ContainerList* bem_mergeSort_0();
virtual BEC_2_9_4_ContainerList* bem_mergeSort_2(BEC_2_4_3_MathInt* bevk_start, BEC_2_4_3_MathInt* bevk_end);
virtual BEC_2_9_4_ContainerList* bem_capacitySet_1(BEC_2_4_3_MathInt* bevk_newcap);
virtual BEC_2_9_4_ContainerList* bem_lengthSet_1(BEC_2_4_3_MathInt* bevk_newlen);
virtual BEC_2_9_4_ContainerList* bem_iterateAdd_1(BEC_2_6_6_SystemObject* bevk_val);
virtual BEC_2_9_4_ContainerList* bem_addAll_1(BEC_2_6_6_SystemObject* bevk_val);
virtual BEC_2_9_4_ContainerList* bem_addValueWhole_1(BEC_2_6_6_SystemObject* bevk_val);
virtual BEC_2_9_4_ContainerList* bem_addValue_1(BEC_2_6_6_SystemObject* bevk_val);
virtual BEC_2_4_3_MathInt* bem_find_1(BEC_2_6_6_SystemObject* bevk_value);
virtual BEC_2_5_4_LogicBool* bem_has_1(BEC_2_6_6_SystemObject* bevk_value);
virtual BEC_2_4_3_MathInt* bem_sortedFind_1(BEC_2_6_6_SystemObject* bevk_value);
virtual BEC_2_4_3_MathInt* bem_sortedFind_2(BEC_2_6_6_SystemObject* bevk_value, BEC_2_5_4_LogicBool* bevk_returnNoMatch);
virtual BEC_2_4_3_MathInt* bem_lengthGet_0();
virtual BEC_2_4_3_MathInt* bem_capacityGet_0();
virtual BEC_2_4_3_MathInt* bem_multiplierGet_0();
virtual BEC_2_9_4_ContainerList* bem_multiplierSet_1(BEC_2_6_6_SystemObject* bevt_0_ta_SET);
virtual BEC_2_6_6_SystemObject* bemc_create();
static BEC_2_9_4_ContainerList* bece_BEC_2_9_4_ContainerList_bevs_inst;
virtual void bemc_setInitial(BEC_2_6_6_SystemObject* becc_inst);
virtual BEC_2_6_6_SystemObject* bemc_getInitial();
virtual void bemg_doMark();
virtual size_t bemg_getSize();
virtual BETS_Object* bemc_getType();
virtual ~BEC_2_9_4_ContainerList() = default;


#ifdef BEDCC_SGC
    std::vector<BEC_2_6_6_SystemObject*> bevi_list;
#endif

   BEC_2_9_4_ContainerList() {  
#ifdef BEDCC_SGC
      struct bes {  BEC_2_6_6_SystemObject* bevr_this;  };
      BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
      bes* beq = (bes*) bevs_myStack->bevs_hs;
      beq->bevr_this = this;
      BECS_StackFrame bevs_stackFrame(1);
#endif
   }

#ifdef BEDCC_SGC
    BEC_2_9_4_ContainerList(std::vector<BEC_2_6_6_SystemObject*> a_bevi_list) {
#endif    
#ifdef BEDCC_SGC
      struct bes {  BEC_2_6_6_SystemObject* bevr_this;  };
      BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
      bes* beq = (bes*) bevs_myStack->bevs_hs;
      beq->bevr_this = this;
      BECS_StackFrame bevs_stackFrame(1);
#endif
        bevi_list = a_bevi_list;
        bevp_length = nullptr;
        bevp_capacity = nullptr;
        bevp_multiplier = nullptr;
        bevp_length = new BEC_2_4_3_MathInt(bevi_list.size());
        bevp_capacity = new BEC_2_4_3_MathInt(bevi_list.size());
        bevp_multiplier = new BEC_2_4_3_MathInt(2);
    } //}

#ifdef BEDCC_SGC
    BEC_2_9_4_ContainerList(std::vector<BEC_2_6_6_SystemObject*> a_bevi_list, int32_t len) {
#endif
#ifdef BEDCC_SGC
      struct bes {  BEC_2_6_6_SystemObject* bevr_this;  };
      BECS_FrameStack* bevs_myStack = &BECS_Runtime::bevs_currentStack;
      bes* beq = (bes*) bevs_myStack->bevs_hs;
      beq->bevr_this = this;
      BECS_StackFrame bevs_stackFrame(1);
#endif
        bevi_list = a_bevi_list;
        bevp_length = nullptr;
        bevp_capacity = nullptr;
        bevp_multiplier = nullptr;
        bevp_length = new BEC_2_4_3_MathInt(len);
        bevp_capacity = new BEC_2_4_3_MathInt(bevi_list.size());
        bevp_multiplier = new BEC_2_4_3_MathInt(2);
    } //}
    
    void bemg_markContent() {
      for (size_t i = 0; i < bevi_list.size(); i++) {
        BEC_2_6_6_SystemObject* bevg_le = bevi_list[i];
        if (bevg_le != nullptr && bevg_le->bevg_gcMark != BECS_Runtime::bevg_currentGcMark) {
          bevg_le->bemg_doMark();
        }
      }
    }
    
  virtual BEC_2_6_6_SystemObject* bemd_0(int32_t callId);
virtual BEC_2_6_6_SystemObject* bemd_1(int32_t callId, BEC_2_6_6_SystemObject* bevd_0);
virtual BEC_2_6_6_SystemObject* bemd_2(int32_t callId, BEC_2_6_6_SystemObject* bevd_0, BEC_2_6_6_SystemObject* bevd_1);
static BET_2_9_4_ContainerList bece_BEC_2_9_4_ContainerList_bevs_type;
};

class BET_2_9_5_ContainerLists : public BETS_Object {
public:
BET_2_9_5_ContainerLists();
virtual BEC_2_6_6_SystemObject* bems_createInstance();
virtual void bemgt_doMark();
static BEC_2_6_6_SystemObject** bevs_inst_ref;
};
class BEC_2_9_5_ContainerLists : public BEC_2_6_6_SystemObject {
private:
typedef BEC_2_6_6_SystemObject bevs_super;

public:
virtual BEC_2_9_5_ContainerLists* bem_default_0();
virtual BEC_2_6_6_SystemObject* bem_forwardCall_2(BEC_2_4_6_TextString* bevk_name, BEC_2_9_4_ContainerList* bevk_args);
virtual BEC_2_6_6_SystemObject* bem_fromHandler_1(BEC_2_9_4_ContainerList* bevk_list);
virtual BEC_2_6_6_SystemObject* bemc_create();
static BEC_2_9_5_ContainerLists* bece_BEC_2_9_5_ContainerLists_bevs_inst;
virtual void bemc_setInitial(BEC_2_6_6_SystemObject* becc_inst);
virtual BEC_2_6_6_SystemObject* bemc_getInitial();
virtual void bemg_doMark();
virtual size_t bemg_getSize();
virtual BETS_Object* bemc_getType();
virtual ~BEC_2_9_5_ContainerLists() = default;
virtual BEC_2_6_6_SystemObject* bemd_0(int32_t callId);
virtual BEC_2_6_6_SystemObject* bemd_1(int32_t callId, BEC_2_6_6_SystemObject* bevd_0);
virtual BEC_2_6_6_SystemObject* bemd_2(int32_t callId, BEC_2_6_6_SystemObject* bevd_0, BEC_2_6_6_SystemObject* bevd_1);
static BET_2_9_5_ContainerLists bece_BEC_2_9_5_ContainerLists_bevs_type;
};

class BET_2_6_11_SystemInitializer : public BETS_Object {
public:
BET_2_6_11_SystemInitializer();
virtual BEC_2_6_6_SystemObject* bems_createInstance();
virtual void bemgt_doMark();
static BEC_2_6_6_SystemObject** bevs_inst_ref;
};
class BEC_2_6_11_SystemInitializer : public BEC_2_6_6_SystemObject {
private:
typedef BEC_2_6_6_SystemObject bevs_super;

public:
virtual BEC_2_6_6_SystemObject* bem_initializeIfShould_1(BEC_2_6_6_SystemObject* bevk_inst);
virtual BEC_2_6_6_SystemObject* bem_notNullInitConstruct_1(BEC_2_6_6_SystemObject* bevk_inst);
virtual BEC_2_6_11_SystemInitializer* bem_notNullInitDefault_1(BEC_2_6_6_SystemObject* bevk_inst);
virtual BEC_2_6_6_SystemObject* bem_notNullInitIt_1(BEC_2_6_6_SystemObject* bevk_inst);
virtual BEC_2_6_6_SystemObject* bem_initializeIt_1(BEC_2_6_6_SystemObject* bevk_inst);
virtual BEC_2_6_6_SystemObject* bemc_create();
static BEC_2_6_11_SystemInitializer* bece_BEC_2_6_11_SystemInitializer_bevs_inst;
virtual void bemc_setInitial(BEC_2_6_6_SystemObject* becc_inst);
virtual BEC_2_6_6_SystemObject* bemc_getInitial();
virtual void bemg_doMark();
virtual size_t bemg_getSize();
virtual BETS_Object* bemc_getType();
virtual ~BEC_2_6_11_SystemInitializer() = default;
virtual BEC_2_6_6_SystemObject* bemd_1(int32_t callId, BEC_2_6_6_SystemObject* bevd_0);
static BET_2_6_11_SystemInitializer bece_BEC_2_6_11_SystemInitializer_bevs_type;
};

class BET_2_6_6_SystemRandom : public BETS_Object {
public:
BET_2_6_6_SystemRandom();
virtual BEC_2_6_6_SystemObject* bems_createInstance();
virtual void bemgt_doMark();
static BEC_2_6_6_SystemObject** bevs_inst_ref;
};
class BEC_2_6_6_SystemRandom : public BEC_2_6_6_SystemObject {
private:
typedef BEC_2_6_6_SystemObject bevs_super;

public:
virtual BEC_2_6_6_SystemObject* bem_create_0();
virtual BEC_2_6_6_SystemRandom* bem_default_0();
virtual BEC_2_6_6_SystemRandom* bem_seedNow_0();
virtual BEC_2_6_6_SystemRandom* bem_seed_1(BEC_2_4_3_MathInt* bevk_seed);
virtual BEC_2_4_3_MathInt* bem_getInt_0();
virtual BEC_2_4_3_MathInt* bem_getInt_1(BEC_2_4_3_MathInt* bevk_value);
virtual BEC_2_4_3_MathInt* bem_getIntMax_1(BEC_2_4_3_MathInt* bevk_max);
virtual BEC_2_4_3_MathInt* bem_getIntMax_2(BEC_2_4_3_MathInt* bevk_value, BEC_2_4_3_MathInt* bevk_max);
virtual BEC_2_4_6_TextString* bem_getString_1(BEC_2_4_3_MathInt* bevk_size);
virtual BEC_2_4_6_TextString* bem_getString_2(BEC_2_4_6_TextString* bevk_str, BEC_2_4_3_MathInt* bevk_size);
virtual BEC_2_6_6_SystemObject* bemc_create();
static BEC_2_6_6_SystemRandom* bece_BEC_2_6_6_SystemRandom_bevs_inst;
virtual void bemc_setInitial(BEC_2_6_6_SystemObject* becc_inst);
virtual BEC_2_6_6_SystemObject* bemc_getInitial();
virtual void bemg_doMark();
virtual size_t bemg_getSize();
virtual BETS_Object* bemc_getType();
virtual ~BEC_2_6_6_SystemRandom() = default;
virtual BEC_2_6_6_SystemObject* bemd_0(int32_t callId);
virtual BEC_2_6_6_SystemObject* bemd_1(int32_t callId, BEC_2_6_6_SystemObject* bevd_0);
virtual BEC_2_6_6_SystemObject* bemd_2(int32_t callId, BEC_2_6_6_SystemObject* bevd_0, BEC_2_6_6_SystemObject* bevd_1);
static BET_2_6_6_SystemRandom bece_BEC_2_6_6_SystemRandom_bevs_type;
};

class BET_2_6_19_SystemObjectFieldIterator : public BETS_Object {
public:
BET_2_6_19_SystemObjectFieldIterator();
virtual BEC_2_6_6_SystemObject* bems_createInstance();
virtual void bemgt_doMark();
static BEC_2_6_6_SystemObject** bevs_inst_ref;
};
class BEC_2_6_19_SystemObjectFieldIterator : public BEC_2_6_6_SystemObject {
private:
typedef BEC_2_6_6_SystemObject bevs_super;

public:
virtual BEC_2_6_6_SystemObject* bem_new_0();
virtual BEC_2_6_19_SystemObjectFieldIterator* bem_new_1(BEC_2_6_6_SystemObject* bevk__instance);
virtual BEC_2_6_19_SystemObjectFieldIterator* bem_new_2(BEC_2_6_6_SystemObject* bevk__instance, BEC_2_5_4_LogicBool* bevk_forceFirstSlot);
virtual BEC_2_5_4_LogicBool* bem_hasNextGet_0();
virtual BEC_2_6_6_SystemObject* bem_nextGet_0();
virtual BEC_2_6_19_SystemObjectFieldIterator* bem_nextSet_1(BEC_2_6_6_SystemObject* bevk_it);
virtual BEC_2_6_6_SystemObject* bemc_create();
static BEC_2_6_19_SystemObjectFieldIterator* bece_BEC_2_6_19_SystemObjectFieldIterator_bevs_inst;
virtual void bemc_setInitial(BEC_2_6_6_SystemObject* becc_inst);
virtual BEC_2_6_6_SystemObject* bemc_getInitial();
virtual void bemg_doMark();
virtual size_t bemg_getSize();
virtual BETS_Object* bemc_getType();
virtual ~BEC_2_6_19_SystemObjectFieldIterator() = default;
virtual BEC_2_6_6_SystemObject* bemd_0(int32_t callId);
virtual BEC_2_6_6_SystemObject* bemd_1(int32_t callId, BEC_2_6_6_SystemObject* bevd_0);
virtual BEC_2_6_6_SystemObject* bemd_2(int32_t callId, BEC_2_6_6_SystemObject* bevd_0, BEC_2_6_6_SystemObject* bevd_1);
static BET_2_6_19_SystemObjectFieldIterator bece_BEC_2_6_19_SystemObjectFieldIterator_bevs_type;
};

class BET_2_6_5_SystemTypes : public BETS_Object {
public:
BET_2_6_5_SystemTypes();
virtual BEC_2_6_6_SystemObject* bems_createInstance();
virtual void bemgt_doMark();
static BEC_2_6_6_SystemObject** bevs_inst_ref;
};
class BEC_2_6_5_SystemTypes : public BEC_2_6_6_SystemObject {
private:
typedef BEC_2_6_6_SystemObject bevs_super;

public:
virtual BEC_2_6_6_SystemObject* bem_create_0();
virtual BEC_2_6_5_SystemTypes* bem_default_0();
virtual BEC_2_5_4_LogicBool* bem_sameType_2(BEC_2_6_6_SystemObject* bevk_org, BEC_2_6_6_SystemObject* bevk_other);
virtual BEC_2_5_4_LogicBool* bem_otherType_2(BEC_2_6_6_SystemObject* bevk_org, BEC_2_6_6_SystemObject* bevk_other);
virtual BEC_2_6_6_SystemObject* bemc_create();
static BEC_2_6_5_SystemTypes* bece_BEC_2_6_5_SystemTypes_bevs_inst;
virtual void bemc_setInitial(BEC_2_6_6_SystemObject* becc_inst);
virtual BEC_2_6_6_SystemObject* bemc_getInitial();
virtual void bemg_doMark();
virtual size_t bemg_getSize();
virtual BETS_Object* bemc_getType();
virtual ~BEC_2_6_5_SystemTypes() = default;
virtual BEC_2_6_6_SystemObject* bemd_0(int32_t callId);
virtual BEC_2_6_6_SystemObject* bemd_2(int32_t callId, BEC_2_6_6_SystemObject* bevd_0, BEC_2_6_6_SystemObject* bevd_1);
static BET_2_6_5_SystemTypes bece_BEC_2_6_5_SystemTypes_bevs_type;
};

class BET_2_6_9_SystemException : public BETS_Object {
public:
BET_2_6_9_SystemException();
virtual BEC_2_6_6_SystemObject* bems_createInstance();
virtual void bemgt_doMark();
static BEC_2_6_6_SystemObject** bevs_inst_ref;
};
class BEC_2_6_9_SystemException : public BEC_2_6_6_SystemObject {
private:
typedef BEC_2_6_6_SystemObject bevs_super;

public:
BEC_2_6_6_SystemObject* bevp_description = nullptr;
virtual BEC_2_6_9_SystemException* bem_new_1(BEC_2_6_6_SystemObject* bevk_descr);
virtual BEC_2_4_6_TextString* bem_toString_0();
virtual BEC_2_6_6_SystemObject* bem_descriptionGet_0();
virtual BEC_2_6_9_SystemException* bem_descriptionSet_1(BEC_2_6_6_SystemObject* bevt_0_ta_SET);
virtual BEC_2_6_6_SystemObject* bemc_create();
static BEC_2_6_9_SystemException* bece_BEC_2_6_9_SystemException_bevs_inst;
virtual void bemc_setInitial(BEC_2_6_6_SystemObject* becc_inst);
virtual BEC_2_6_6_SystemObject* bemc_getInitial();
virtual void bemg_doMark();
virtual size_t bemg_getSize();
virtual BETS_Object* bemc_getType();
virtual ~BEC_2_6_9_SystemException() = default;
virtual BEC_2_6_6_SystemObject* bemd_0(int32_t callId);
virtual BEC_2_6_6_SystemObject* bemd_1(int32_t callId, BEC_2_6_6_SystemObject* bevd_0);
static BET_2_6_9_SystemException bece_BEC_2_6_9_SystemException_bevs_type;
};

class BET_2_8_21_EmbeddedSwitchButtonIndicator : public BETS_Object {
public:
BET_2_8_21_EmbeddedSwitchButtonIndicator();
virtual BEC_2_6_6_SystemObject* bems_createInstance();
virtual void bemgt_doMark();
static BEC_2_6_6_SystemObject** bevs_inst_ref;
};
class BEC_2_8_21_EmbeddedSwitchButtonIndicator : public BEC_2_8_8_EmbeddedAppShell {
private:
typedef BEC_2_8_8_EmbeddedAppShell bevs_super;

public:
virtual BEC_2_6_6_SystemObject* bem_buildControl_3(BEC_2_4_3_MathInt* bevk_conPos, BEC_2_4_6_TextString* bevk_conName, BEC_2_4_6_TextString* bevk_conArgs);
virtual BEC_2_6_6_SystemObject* bemc_create();
static BEC_2_8_21_EmbeddedSwitchButtonIndicator* bece_BEC_2_8_21_EmbeddedSwitchButtonIndicator_bevs_inst;
virtual void bemc_setInitial(BEC_2_6_6_SystemObject* becc_inst);
virtual BEC_2_6_6_SystemObject* bemc_getInitial();
virtual void bemg_doMark();
virtual size_t bemg_getSize();
virtual BETS_Object* bemc_getType();
virtual ~BEC_2_8_21_EmbeddedSwitchButtonIndicator() = default;
virtual BEC_2_6_6_SystemObject* bemd_3(int32_t callId, BEC_2_6_6_SystemObject* bevd_0, BEC_2_6_6_SystemObject* bevd_1, BEC_2_6_6_SystemObject* bevd_2);
static BET_2_8_21_EmbeddedSwitchButtonIndicator bece_BEC_2_8_21_EmbeddedSwitchButtonIndicator_bevs_type;
};

class BET_2_4_17_TextMultiByteIterator : public BETS_Object {
public:
BET_2_4_17_TextMultiByteIterator();
virtual BEC_2_6_6_SystemObject* bems_createInstance();
virtual void bemgt_doMark();
static BEC_2_6_6_SystemObject** bevs_inst_ref;
};
class BEC_2_4_17_TextMultiByteIterator : public BEC_2_4_12_TextByteIterator {
private:
typedef BEC_2_4_12_TextByteIterator bevs_super;

public:
BEC_2_4_3_MathInt* bevp_bcount = nullptr;
BEC_2_4_3_MathInt* bevp_ival = nullptr;
virtual BEC_2_4_12_TextByteIterator* bem_new_1(BEC_2_4_6_TextString* bevk__str);
virtual BEC_2_4_6_TextString* bem_nextGet_0();
virtual BEC_2_4_6_TextString* bem_next_1(BEC_2_4_6_TextString* bevk_buf);
virtual BEC_2_4_17_TextMultiByteIterator* bem_multiByteIteratorIteratorGet_0();
virtual BEC_2_6_6_SystemObject* bem_iteratorGet_0();
virtual BEC_2_6_6_SystemObject* bemc_create();
static BEC_2_4_17_TextMultiByteIterator* bece_BEC_2_4_17_TextMultiByteIterator_bevs_inst;
virtual void bemc_setInitial(BEC_2_6_6_SystemObject* becc_inst);
virtual BEC_2_6_6_SystemObject* bemc_getInitial();
virtual void bemg_doMark();
virtual size_t bemg_getSize();
virtual BETS_Object* bemc_getType();
virtual ~BEC_2_4_17_TextMultiByteIterator() = default;
virtual BEC_2_6_6_SystemObject* bemd_0(int32_t callId);
virtual BEC_2_6_6_SystemObject* bemd_1(int32_t callId, BEC_2_6_6_SystemObject* bevd_0);
static BET_2_4_17_TextMultiByteIterator bece_BEC_2_4_17_TextMultiByteIterator_bevs_type;
};

class BET_2_6_16_SystemMethodNotDefined : public BETS_Object {
public:
BET_2_6_16_SystemMethodNotDefined();
virtual BEC_2_6_6_SystemObject* bems_createInstance();
virtual void bemgt_doMark();
static BEC_2_6_6_SystemObject** bevs_inst_ref;
};
class BEC_2_6_16_SystemMethodNotDefined : public BEC_2_6_9_SystemException {
private:
typedef BEC_2_6_9_SystemException bevs_super;

public:
virtual BEC_2_6_6_SystemObject* bemc_create();
static BEC_2_6_16_SystemMethodNotDefined* bece_BEC_2_6_16_SystemMethodNotDefined_bevs_inst;
virtual void bemc_setInitial(BEC_2_6_6_SystemObject* becc_inst);
virtual BEC_2_6_6_SystemObject* bemc_getInitial();
virtual void bemg_doMark();
virtual size_t bemg_getSize();
virtual BETS_Object* bemc_getType();
virtual ~BEC_2_6_16_SystemMethodNotDefined() = default;
static BET_2_6_16_SystemMethodNotDefined bece_BEC_2_6_16_SystemMethodNotDefined_bevs_type;
};

class BET_2_6_19_SystemInvocationException : public BETS_Object {
public:
BET_2_6_19_SystemInvocationException();
virtual BEC_2_6_6_SystemObject* bems_createInstance();
virtual void bemgt_doMark();
static BEC_2_6_6_SystemObject** bevs_inst_ref;
};
class BEC_2_6_19_SystemInvocationException : public BEC_2_6_9_SystemException {
private:
typedef BEC_2_6_9_SystemException bevs_super;

public:
virtual BEC_2_6_6_SystemObject* bemc_create();
static BEC_2_6_19_SystemInvocationException* bece_BEC_2_6_19_SystemInvocationException_bevs_inst;
virtual void bemc_setInitial(BEC_2_6_6_SystemObject* becc_inst);
virtual BEC_2_6_6_SystemObject* bemc_getInitial();
virtual void bemg_doMark();
virtual size_t bemg_getSize();
virtual BETS_Object* bemc_getType();
virtual ~BEC_2_6_19_SystemInvocationException() = default;
static BET_2_6_19_SystemInvocationException bece_BEC_2_6_19_SystemInvocationException_bevs_type;
};

class BEL_Base : public BECS_Lib {
public:
static void init();
};
}
int bems_relocMain(int argc, char **argv);
