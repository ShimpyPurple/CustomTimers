#ifndef CustomTimers_h
#define CustomTimers_h

#include "Arduino.h"
#include "BaseTimers/BaseTimer16.h"
#include "BaseTimers/BaseTimer8Async.h"
#include "BaseTimers/Constants.h"
#include "Config/Config.h"

#if ( TIMER1_ENABLED != 0 )
extern BaseTimer16 Timer1;
#endif

#if ( TIMER2_ENABLED != 0 )
extern BaseTimer8Async Timer2;
#endif

#if ( TIMER3_ENABLED != 0 ) && defined( __AVR_ATmega2560__ )
extern BaseTimer16 Timer3;
#endif

#if ( TIMER4_ENABLED != 0 ) && defined( __AVR_ATmega2560__ )
extern BaseTimer16 Timer4;
#endif

#if ( TIMER5_ENABLED != 0 ) && defined( __AVR_ATmega2560__ )
extern BaseTimer16 Timer5;
#endif

#endif