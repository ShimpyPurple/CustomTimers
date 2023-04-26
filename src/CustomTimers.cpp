#include "CustomTimers.h"

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
