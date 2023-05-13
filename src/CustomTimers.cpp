#include "CustomTimers.h"

// ----------------------------- //
//            Timer 1            //
// ----------------------------- //

#if ( TIMER1_ENABLED != 0 )
TimerInt timer1CompAInt;
TimerInt timer1CompBInt;
TimerInt timer1CaptInt;
TimerInt timer1OvfInt;

ISR( TIMER1_COMPA_vect ) { if (timer1CompAInt.arg == nullptr) timer1CompAInt.func(); else timer1CompAInt.funcArg( timer1CompAInt.arg ); }
ISR( TIMER1_COMPB_vect ) { if (timer1CompBInt.arg == nullptr) timer1CompBInt.func(); else timer1CompBInt.funcArg( timer1CompBInt.arg ); }
ISR( TIMER1_CAPT_vect  ) { if (timer1CaptInt.arg  == nullptr) timer1CaptInt.func();  else timer1CaptInt.funcArg(  timer1CaptInt.arg  ); }
ISR( TIMER1_OVF_vect   ) { if (timer1OvfInt.arg   == nullptr) timer1OvfInt.func();   else timer1OvfInt.funcArg(   timer1OvfInt.arg   ); }

#if defined( __AVR_ATmega2560__ )
TimerInt timer1CompCInt;
ISR( TIMER1_COMPC_vect ) { if (timer1CompCInt.arg == nullptr) timer1CompCInt.funcArg( timer1CompCInt.arg ); else timer1CompCInt.func(); }
#endif

BaseTimer16 Timer1(
    &TCNT1 ,
    &TCCR1A , &TCCR1B , &TCCR1C ,
    COM1A1 , COM1A0 , COM1B1 , COM1B0 ,
    WGM13 , WGM12 , WGM11 , WGM10 ,
    CS12 , CS11 , CS10 ,
    ICNC1 , ICES1 ,
    FOC1A , FOC1B ,
    &OCR1A , &OCR1B , &ICR1 ,
    &TIMSK1 , OCIE1A , OCIE1B , ICIE1 , TOIE1 ,
    &TIFR1 , OCF1A , OCF1B , ICF1 , TOV1 ,
    &timer1CompAInt , &timer1CompBInt , &timer1CaptInt , &timer1OvfInt
#if defined( __AVR_ATmega2560__ )
    ,
    COM1C1 , COM1C0 ,
    FOC1C ,
    &OCR1C ,
    OCIE1C ,
    OCF1C ,
    &timer1CompCInt
#endif
);
#endif

// ----------------------------- //
//            Timer 2            //
// ----------------------------- //

#if ( TIMER2_ENABLED != 0 )
TimerInt timer2CompAInt;
TimerInt timer2CompBInt;
TimerInt timer2OvfInt;

ISR( TIMER2_COMPA_vect ) { if (timer2CompAInt.arg == nullptr) timer2CompAInt.func(); else timer2CompAInt.funcArg( timer2CompAInt.arg ); }
ISR( TIMER2_COMPB_vect ) { if (timer2CompBInt.arg == nullptr) timer2CompBInt.func(); else timer2CompBInt.funcArg( timer2CompBInt.arg ); }
ISR( TIMER2_OVF_vect   ) { if (timer2OvfInt.arg   == nullptr) timer2OvfInt.func();   else timer2OvfInt.funcArg(   timer2OvfInt.arg   ); }

BaseTimer8Async Timer2(
    &TCNT2 ,
    &TCCR2A , &TCCR2B ,
    COM2A1 , COM2A0 , COM2B1 , COM2B0 ,
    WGM22 , WGM21 , WGM20 ,
    CS22 , CS21 , CS20 ,
    FOC2A , FOC2B ,
    &OCR2A , &OCR2B ,
    &TIMSK2 , OCIE2A , OCIE2B , TOIE2 ,
    &TIFR2 , OCF2A , OCF2B , TOV2 ,
    &timer2CompAInt , &timer2CompBInt , &timer2OvfInt
);
#endif

// ----------------------------- //
//            Timer 3            //
// ----------------------------- //

#if ( TIMER3_ENABLED != 0 ) && defined( __AVR_ATmega2560__ )
TimerInt timer3CompAInt;
TimerInt timer3CompBInt;
TimerInt timer3CompCInt;
TimerInt timer3CaptInt;
TimerInt timer3OvfInt;

ISR( TIMER3_COMPA_vect ) { if (timer3CompAInt.arg == nullptr) timer3CompAInt.func(); else timer3CompAInt.funcArg( timer3CompAInt.arg ); }
ISR( TIMER3_COMPB_vect ) { if (timer3CompBInt.arg == nullptr) timer3CompBInt.func(); else timer3CompBInt.funcArg( timer3CompBInt.arg ); }
ISR( TIMER3_COMPC_vect ) { if (timer3CompCInt.arg == nullptr) timer3CompCInt.func(); else timer3CompCInt.funcArg( timer3CompCInt.arg ); }
ISR( TIMER3_CAPT_vect  ) { if (timer3CaptInt.arg  == nullptr) timer3CaptInt.func();  else timer3CaptInt.funcArg(  timer3CaptInt.arg  ); }
ISR( TIMER3_OVF_vect   ) { if (timer3OvfInt.arg   == nullptr) timer3OvfInt.func();   else timer3OvfInt.funcArg(   timer3OvfInt.arg   ); }

BaseTimer16 Timer3(
    &TCNT3 ,
    &TCCR3A , &TCCR3B , &TCCR3C ,
    COM3A1 , COM3A0 , COM3B1 , COM3B0 ,
    WGM33 , WGM32 , WGM31 , WGM30 ,
    CS32 , CS31 , CS30 ,
    ICNC3 , ICES3 ,
    FOC3A , FOC3B ,
    &OCR3A , &OCR3B , &ICR3 ,
    &TIMSK3 , OCIE3A , OCIE3B , ICIE3 , TOIE3 ,
    &TIFR3 , OCF3A , OCF3B , ICF3 , TOV3 ,
    &timer3CompAInt , &timer3CompBInt , &timer3CaptInt , &timer3OvfInt ,
    COM3C1 , COM3C0 ,
    FOC3C ,
    &OCR3C ,
    OCIE3C ,
    OCF3C ,
    &timer3CompCInt
);
#endif

// ----------------------------- //
//            Timer 4            //
// ----------------------------- //

#if ( TIMER4_ENABLED != 0 ) && defined( __AVR_ATmega2560__ )
TimerInt timer4CompAInt;
TimerInt timer4CompBInt;
TimerInt timer4CompCInt;
TimerInt timer4CaptInt;
TimerInt timer4OvfInt;

ISR( TIMER4_COMPA_vect ) { if (timer4CompAInt.arg == nullptr) timer4CompAInt.func(); else timer4CompAInt.funcArg( timer4CompAInt.arg ); }
ISR( TIMER4_COMPB_vect ) { if (timer4CompBInt.arg == nullptr) timer4CompBInt.func(); else timer4CompBInt.funcArg( timer4CompBInt.arg ); }
ISR( TIMER4_COMPC_vect ) { if (timer4CompCInt.arg == nullptr) timer4CompCInt.func(); else timer4CompCInt.funcArg( timer4CompCInt.arg ); }
ISR( TIMER4_CAPT_vect  ) { if (timer4CaptInt.arg  == nullptr) timer4CaptInt.func();  else timer4CaptInt.funcArg(  timer4CaptInt.arg  ); }
ISR( TIMER4_OVF_vect   ) { if (timer4OvfInt.arg   == nullptr) timer4OvfInt.func();   else timer4OvfInt.funcArg(   timer4OvfInt.arg   ); }

BaseTimer16 Timer4(
    &TCNT4 ,
    &TCCR4A , &TCCR4B , &TCCR4C ,
    COM4A1 , COM4A0 , COM4B1 , COM4B0 ,
    WGM43 , WGM42 , WGM41 , WGM40 ,
    CS42 , CS41 , CS40 ,
    ICNC4 , ICES4 ,
    FOC4A , FOC4B ,
    &OCR4A , &OCR4B , &ICR4 ,
    &TIMSK4 , OCIE4A , OCIE4B , ICIE4 , TOIE4 ,
    &TIFR4 , OCF4A , OCF4B , ICF4 , TOV4 ,
    &timer4CompAInt , &timer4CompBInt , &timer4CaptInt , &timer4OvfInt ,
    COM4C1 , COM4C0 ,
    FOC4C ,
    &OCR4C ,
    OCIE4C ,
    OCF4C ,
    &timer4CompCInt
);
#endif

// ----------------------------- //
//            Timer 5            //
// ----------------------------- //

#if ( TIMER5_ENABLED != 0 ) && defined( __AVR_ATmega2560__ )
TimerInt timer5CompAInt;
TimerInt timer5CompBInt;
TimerInt timer5CompCInt;
TimerInt timer5CaptInt;
TimerInt timer5OvfInt;

ISR( TIMER5_COMPA_vect ) { if (timer5CompAInt.arg == nullptr) timer5CompAInt.func(); else timer5CompAInt.funcArg( timer5CompAInt.arg ); }
ISR( TIMER5_COMPB_vect ) { if (timer5CompBInt.arg == nullptr) timer5CompBInt.func(); else timer5CompBInt.funcArg( timer5CompBInt.arg ); }
ISR( TIMER5_COMPC_vect ) { if (timer5CompCInt.arg == nullptr) timer5CompCInt.func(); else timer5CompCInt.funcArg( timer5CompCInt.arg ); }
ISR( TIMER5_CAPT_vect  ) { if (timer5CaptInt.arg  == nullptr) timer5CaptInt.func();  else timer5CaptInt.funcArg(  timer5CaptInt.arg  ); }
ISR( TIMER5_OVF_vect   ) { if (timer5OvfInt.arg   == nullptr) timer5OvfInt.func();   else timer5OvfInt.funcArg(   timer5OvfInt.arg   ); }

BaseTimer16 Timer5(
    &TCNT5 ,
    &TCCR5A , &TCCR5B , &TCCR5C ,
    COM5A1 , COM5A0 , COM5B1 , COM5B0 ,
    WGM53 , WGM52 , WGM51 , WGM50 ,
    CS52 , CS51 , CS50 ,
    ICNC5 , ICES5 ,
    FOC5A , FOC5B ,
    &OCR5A , &OCR5B , &ICR5 ,
    &TIMSK5 , OCIE5A , OCIE5B , ICIE5 , TOIE5 ,
    &TIFR5 , OCF5A , OCF5B , ICF5 , TOV5 ,
    &timer5CompAInt , &timer5CompBInt , &timer5CaptInt , &timer5OvfInt ,
    COM5C1 , COM5C0 ,
    FOC5C ,
    &OCR5C ,
    OCIE5C ,
    OCF5C ,
    &timer5CompCInt
);
#endif

// ----------------------------------- //
//            Generic Timer            //
// ----------------------------------- //

GenericTimer::GenericTimer( uint8_t timer , bool emulate16bits=false ):
    emulate16bits( emulate16bits ) ,
    TCNTnExtraByte( 0 ) ,
    OCRnAExtraByte( 0 ) ,
    OCRnBExtraByte( 0 ) ,
    ctcMode( false ) ,
    ovfFunc( []{} ) ,
    ovfArg( nullptr )
{
    switch ( timer ) {
        case TIMER_1: this->timer16 = &Timer1; this->timer8Async = nullptr; timerType = TIMER_16_BIT; emulate16bits = false; break;
        case TIMER_2: this->timer16 = nullptr; this->timer8Async = &Timer2; timerType = TIMER_8_BIT_ASYNC;                   break;
#if defined( __AVR_ATmega2560__ )
        case TIMER_3: this->timer16 = &Timer3; this->timer8Async = nullptr; timerType = TIMER_16_BIT; emulate16bits = false; break;
        case TIMER_4: this->timer16 = &Timer4; this->timer8Async = nullptr; timerType = TIMER_16_BIT; emulate16bits = false; break;
        case TIMER_5: this->timer16 = &Timer5; this->timer8Async = nullptr; timerType = TIMER_16_BIT; emulate16bits = false; break;
#endif
        default: timerType = NO_TIMER; break;
    }
    if ( emulate16bits ) {
        timer8Async->attachInterrupt( OVERFLOW , ovfISR , this );
    }
}

GenericTimer::GenericTimer( BaseTimer16 *timer16 ):
    timerType( TIMER_16_BIT ) ,
    timer16( timer16 ) ,
    timer8Async( nullptr ) ,
    emulate16bits( false )
{}

GenericTimer::GenericTimer( BaseTimer8Async *timer8Async , bool emulate16bits ):
    timerType( TIMER_8_BIT_ASYNC ) ,
    timer16( nullptr ) ,
    timer8Async( timer8Async ) ,
    emulate16bits( emulate16bits ) ,
    TCNTnExtraByte( 0 ) ,
    OCRnAExtraByte( 0 ) ,
    OCRnBExtraByte( 0 ) ,
    ctcMode( false ) ,
    ovfFunc( []{} ) ,
    ovfArg( nullptr )
{
    if ( emulate16bits ) {
        timer8Async->attachInterrupt( OVERFLOW , ovfISR , this );
    }
}

uint8_t GenericTimer::getTimerType() { return timerType; }
BaseTimer16 *GenericTimer::getTimer16() { return timer16; }
BaseTimer8Async *GenericTimer::getTimer8Async() { return timer8Async; }

// ------------------------------------------- //
//            Mode and Clock Source            //
// ------------------------------------------- //

void GenericTimer::setMode( uint8_t mode ) {
    switch ( timerType ) {
        case TIMER_16_BIT: timer16->setMode( mode ); break;
        case TIMER_8_BIT_ASYNC:
            if ( emulate16bits ) {
                if ( mode == CTC_OCA ) {
                    ctcMode = true;
                }
                timer8Async->setMode( WGM_NORMAL ); break;
            } else {
                timer8Async->setMode( mode ); break;
            }
    }
}

uint8_t GenericTimer::getMode() {
    switch ( timerType ) {
        case TIMER_16_BIT: return timer16->getMode();
        case TIMER_8_BIT_ASYNC: return timer8Async->getMode();
        default: return UINT8_MAX;
    }
}

void GenericTimer::setClockSource( uint8_t source ) {
    switch ( timerType ) {
        case TIMER_16_BIT: timer16->setClockSource( source ); break;
        case TIMER_8_BIT_ASYNC: timer8Async->setClockSource( source ); break;
    }
}

uint8_t GenericTimer::getClockSource() {
    switch ( timerType ) {
        case TIMER_16_BIT: return timer16->getClockSource();
        case TIMER_8_BIT_ASYNC: return timer8Async->getClockSource();
        default: return UINT8_MAX;
    }
}

// ------------------------------- //
//            Tick Rate            //
// ------------------------------- //

void GenericTimer::setExternalTickRate( float tickRate ) {
    switch ( timerType ) {
        case TIMER_16_BIT: timer16->setExternalTickRate( tickRate ); break;
    }
}

void GenericTimer::setClockRate( float clockRate ) {
    switch ( timerType ) {
        case TIMER_8_BIT_ASYNC: timer8Async->setClockRate( clockRate ); break;
    }
}

float GenericTimer::getTickRate() {
    switch ( timerType ) {
        case TIMER_16_BIT: return timer16->getTickRate();
        case TIMER_8_BIT_ASYNC: return timer8Async->getTickRate();
        default: return 0;
    }
}

// --------------------------------------- //
//            Set and Get TCNTn            //
// --------------------------------------- //

void GenericTimer::setCounter( uint16_t value ) {
    switch ( timerType ) {
        case TIMER_16_BIT: timer16->setCounter( value ); break;
        case TIMER_8_BIT_ASYNC:
            if ( emulate16bits ) {
                TCNTnExtraByte = value >> 8;
                timer8Async->setCounter( value & 0xFF );
            } else {
                timer8Async->setCounter( value );
            }
            break;
    }
}

uint16_t GenericTimer::getCounter() {
    switch ( timerType ) {
        case TIMER_16_BIT: return timer16->getCounter();
        case TIMER_8_BIT_ASYNC:
            if ( emulate16bits ) {
                return timer8Async->getCounter() | ( (uint16_t)TCNTnExtraByte << 8 );
            } else {
                return timer8Async->getCounter();
            }
        default: return 0;
    }
}

// --------------------------------------- //
//            Compare A Methods            //
// --------------------------------------- //

void GenericTimer::setOutputCompareA( uint16_t value ) {
    switch ( timerType ) {
        case TIMER_16_BIT: timer16->setOutputCompareA( value ); break;
        case TIMER_8_BIT_ASYNC:
            if ( emulate16bits ) {
                OCRnAExtraByte = value >> 8;
                timer8Async->setOutputCompareA( value & 0xFF );
            } else {
                timer8Async->setOutputCompareA( value );
            }
            break;
    }
}

uint16_t GenericTimer::getOutputCompareA() {
    switch ( timerType ) {
        case TIMER_16_BIT: return timer16->getOutputCompareA();
        case TIMER_8_BIT_ASYNC:
            if ( emulate16bits ) {
                return timer8Async->getOutputCompareA() | ( (uint16_t)OCRnAExtraByte << 8 );
            } else {
                return timer8Async->getOutputCompareA();
            }
        default: return 0;
    }
}

void GenericTimer::setCompareOutputModeA( uint8_t mode ) {
    switch ( timerType ) {
        case TIMER_16_BIT: timer16->setCompareOutputModeA( mode ); break;
        case TIMER_8_BIT_ASYNC: timer8Async->setCompareOutputModeA( mode ); break;
    }
}

void GenericTimer::forceOutputCompareA() {
    switch ( timerType ) {
        case TIMER_16_BIT: timer16->forceOutputCompareA(); break;
        case TIMER_8_BIT_ASYNC: timer8Async->forceOutputCompareA(); break;
    }
}

bool GenericTimer::getOutputCompareAFlag() {
    switch ( timerType ) {
        case TIMER_16_BIT: return timer16->getOutputCompareAFlag();
        case TIMER_8_BIT_ASYNC: return timer8Async->getOutputCompareAFlag();
        default: return false;
    }
}

void GenericTimer::clearOutputCompareAFlag() {
    switch ( timerType ) {
        case TIMER_16_BIT: timer16->clearOutputCompareAFlag(); break;
        case TIMER_8_BIT_ASYNC: timer8Async->clearOutputCompareAFlag(); break;
    }
}

// --------------------------------------- //
//            Compare B Methods            //
// --------------------------------------- //

void GenericTimer::setOutputCompareB( uint16_t value ) {
    switch ( timerType ) {
        case TIMER_16_BIT: timer16->setOutputCompareB( value ); break;
        case TIMER_8_BIT_ASYNC:
            if ( emulate16bits ) {
                OCRnBExtraByte = value >> 8;
                timer8Async->setOutputCompareB( value & 0xFF );
            } else {
                timer8Async->setOutputCompareB( value );
            }
            break;
    }
}

uint16_t GenericTimer::getOutputCompareB() {
    switch ( timerType ) {
        case TIMER_16_BIT: return timer16->getOutputCompareB();
        case TIMER_8_BIT_ASYNC:
            if ( emulate16bits ) {
                return timer8Async->getOutputCompareB() | ( (uint16_t)OCRnBExtraByte << 8 );
            } else {
                return timer8Async->getOutputCompareB();
            }
        default: return 0;
    }
}

void GenericTimer::setCompareOutputModeB( uint8_t mode ) {
    switch ( timerType ) {
        case TIMER_16_BIT: timer16->setCompareOutputModeB( mode ); break;
        case TIMER_8_BIT_ASYNC: timer8Async->setCompareOutputModeB( mode ); break;
    }
}

void GenericTimer::forceOutputCompareB() {
    switch ( timerType ) {
        case TIMER_16_BIT: timer16->forceOutputCompareB(); break;
        case TIMER_8_BIT_ASYNC: timer8Async->forceOutputCompareB(); break;
    }
}

bool GenericTimer::getOutputCompareBFlag() {
    switch ( timerType ) {
        case TIMER_16_BIT: return timer16->getOutputCompareBFlag();
        case TIMER_8_BIT_ASYNC: return timer8Async->getOutputCompareBFlag();
        default: return false;
    }
}

void GenericTimer::clearOutputCompareBFlag() {
    switch ( timerType ) {
        case TIMER_16_BIT: timer16->clearOutputCompareBFlag(); break;
        case TIMER_8_BIT_ASYNC: timer8Async->clearOutputCompareBFlag(); break;
    }
}

// --------------------------------------- //
//            Compare C Methods            //
// --------------------------------------- //

#if defined( __AVR_ATmega2560__ )
void GenericTimer::setOutputCompareC( uint16_t value ) {
    switch ( timerType ) {
        case TIMER_16_BIT: timer16->setOutputCompareC( value ); break;
    }
}

uint16_t GenericTimer::getOutputCompareC() {
    switch ( timerType ) {
        case TIMER_16_BIT: return timer16->getOutputCompareC();
        default: return 0;
    }
}

void GenericTimer::setCompareOutputModeC( uint8_t mode ) {
    switch ( timerType ) {
        case TIMER_16_BIT: timer16->setCompareOutputModeC( mode ); break;
    }
}

void GenericTimer::forceOutputCompareC() {
    switch ( timerType ) {
        case TIMER_16_BIT: timer16->forceOutputCompareC(); break;
    }
}

bool GenericTimer::getOutputCompareCFlag() {
    switch ( timerType ) {
        case TIMER_16_BIT: return timer16->getOutputCompareCFlag();
        default: return false;
    }
}

void GenericTimer::clearOutputCompareCFlag() {
    switch ( timerType ) {
        case TIMER_16_BIT: timer16->clearOutputCompareCFlag(); break;
    }
}
#endif

// ------------------------------------------- //
//            Input Capture Methods            //
// ------------------------------------------- //

void GenericTimer::setInputCapture( uint16_t value ) {
    switch ( timerType ) {
        case TIMER_16_BIT: timer16->setInputCapture( value ); break;
    }
}

uint16_t GenericTimer::getInputCapture() {
    switch ( timerType ) {
        case TIMER_16_BIT: return timer16->getInputCapture();
        default: return 0;
    }
}

bool GenericTimer::getInputCaptureFlag() {
    switch ( timerType ) {
        case TIMER_16_BIT: return timer16->getInputCaptureFlag();
        default: return false;
    }
}

void GenericTimer::clearInputCaptureFlag() {
    switch ( timerType ) {
        case TIMER_16_BIT: timer16->clearInputCaptureFlag(); break;
    }
}

void GenericTimer::configureInputCapture( uint8_t edgeMode , bool noiseCanceller ) {
    switch ( timerType ) {
        case TIMER_16_BIT: timer16->configureInputCapture( edgeMode , noiseCanceller ); break;
    }
}

// ----------------------------------- //
//            Overflow Flag            //
// ----------------------------------- //

bool GenericTimer::getOverflowFlag() {
    switch ( timerType ) {
        case TIMER_16_BIT: return timer16->getOverflowFlag();
        case TIMER_8_BIT_ASYNC: return timer8Async->getOverflowFlag();
        default: return false;
    }
}

void GenericTimer::clearOverflowFlag() {
    switch ( timerType ) {
        case TIMER_16_BIT: timer16->clearOverflowFlag(); break;
        case TIMER_8_BIT_ASYNC: timer8Async->clearOverflowFlag(); break;
    }
}

// -------------------------------- //
//            Interrupts            //
// -------------------------------- //

void GenericTimer::attachInterrupt( uint8_t mode , void (*func)() ) {
    switch ( timerType ) {
        case TIMER_16_BIT: timer16->attachInterrupt( mode , func ); break;
        case TIMER_8_BIT_ASYNC:
            if ( emulate16bits ) {
                switch ( mode ) {
                    case COMPARE_MATCH_A:
                        compAFunc = func;
                        compAArg = nullptr;
                        timer8Async->attachInterrupt( COMPARE_MATCH_A , compAISR , this );
                        break;
                    case COMPARE_MATCH_B:
                        compBFunc = func;
                        compBArg = nullptr;
                        timer8Async->attachInterrupt( COMPARE_MATCH_B , compBISR , this );
                        break;
                    case OVERFLOW:
                        ovfFunc = func;
                        ovfArg = nullptr;
                        timer8Async->attachInterrupt( OVERFLOW , ovfISR , this );
                        break;
                }
            }
            break;
    }
}

void GenericTimer::attachInterrupt( uint8_t mode , void (*func)(void*) , void *arg ) {
    switch ( timerType ) {
        case TIMER_16_BIT: timer16->attachInterrupt( mode , func , arg ); break;
        case TIMER_8_BIT_ASYNC:
            if ( emulate16bits ) {
                switch ( mode ) {
                    case COMPARE_MATCH_A:
                        compAFuncArg = func;
                        compAArg = arg;
                        timer8Async->attachInterrupt( COMPARE_MATCH_A , compAISR , this );
                        break;
                    case COMPARE_MATCH_B:
                        compBFuncArg = func;
                        compBArg = arg;
                        timer8Async->attachInterrupt( COMPARE_MATCH_B , compBISR , this );
                        break;
                    case OVERFLOW:
                        ovfFuncArg = func;
                        ovfArg = arg;
                        timer8Async->attachInterrupt( OVERFLOW , ovfISR , this );
                        break;
                }
            }
            break;
    }
}

void GenericTimer::enableInterrupt( uint8_t mode ) {
    switch ( timerType ) {
        case TIMER_16_BIT: timer16->enableInterrupt( mode ); break;
        case TIMER_8_BIT_ASYNC: timer8Async->enableInterrupt( mode ); break;
    }
}

void GenericTimer::disableInterrupt( uint8_t mode ) {
    switch ( timerType ) {
        case TIMER_16_BIT: timer16->disableInterrupt( mode ); break;
        case TIMER_8_BIT_ASYNC: timer8Async->disableInterrupt( mode ); break;
    }
}

bool GenericTimer::interruptEnabled( uint8_t mode ) {
    switch ( timerType ) {
        case TIMER_16_BIT: return timer16->interruptEnabled( mode );
        case TIMER_8_BIT_ASYNC: return timer8Async->interruptEnabled( mode );
        default: return false;
    }
}

static void GenericTimer::compAISR( void *object ) {
    GenericTimer *genTimer = ( GenericTimer* )( object );
    if ( genTimer->OCRnAExtraByte != genTimer->TCNTnExtraByte ) return;
    if ( genTimer->ctcMode ) genTimer->setCounter( 0 );
    if ( genTimer->compAArg == nullptr ) {
        genTimer->compAFunc();
    } else {
        genTimer->compAFuncArg( genTimer->compAArg );
    }
}

static void GenericTimer::compBISR( void *object ) {
    GenericTimer *genTimer = ( GenericTimer* )( object );
    if ( genTimer->OCRnBExtraByte != genTimer->TCNTnExtraByte ) return;
    if ( genTimer->compBArg == nullptr ) {
        genTimer->compBFunc();
    } else {
        genTimer->compBFuncArg( genTimer->compBArg );
    }
}

static void GenericTimer::ovfISR( void *object ) {
    GenericTimer *genTimer = ( GenericTimer* )( object );
    genTimer->TCNTnExtraByte += 1;
    if ( genTimer->TCNTnExtraByte != 0 ) return;
    if ( genTimer->ovfArg == nullptr ) {
        genTimer->ovfFunc();
    } else {
        genTimer->ovfFuncArg( genTimer->ovfArg );
    }
}
