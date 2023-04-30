#include "BaseTimer16.h"

// --------------------------------- //
//            Constructor            //
// --------------------------------- //

BaseTimer16::BaseTimer16(
    volatile uint16_t *TCNTn ,
    volatile uint8_t *TCCRnA , volatile uint8_t *TCCRnB , volatile uint8_t *TCCRnC ,
    uint8_t COMnA1 , uint8_t COMnA0 , uint8_t COMnB1 , uint8_t COMnB0 ,
    uint8_t WGMn3 , uint8_t WGMn2 , uint8_t WGMn1 , uint8_t WGMn0 ,
    uint8_t CSn2 , uint8_t CSn1 , uint8_t CSn0 ,
    uint8_t ICNCn , uint8_t ICESn ,
    uint8_t FOCnA , uint8_t FOCnB ,
    volatile uint16_t *OCRnA , volatile uint16_t *OCRnB , volatile uint16_t *ICRn ,
    volatile uint8_t *TIMSKn , uint8_t OCIEnA , uint8_t OCIEnB , uint8_t ICIEn , uint8_t TOIEn ,
    volatile uint8_t *TIFRn , uint8_t OCFnA , uint8_t OCFnB , uint8_t ICFn , uint8_t TOVn ,
    TimerInt *compAInt , TimerInt *compBInt , TimerInt *captInt , TimerInt *ovfInt
#if defined( __AVR_ATmega2560__ )
    ,
    uint8_t COMnC1 , uint8_t COMnC0 ,
    uint8_t FOCnC ,
    volatile uint16_t *OCRnC ,
    uint8_t OCIEnC ,
    uint8_t OCFnC ,
    TimerInt *compCInt
#endif
):
    TCNTn(TCNTn) ,
    TCCRnA(TCCRnA) , TCCRnB(TCCRnB) , TCCRnC(TCCRnC) ,
    COMnA1(COMnA1) , COMnA0(COMnA0) , COMnB1(COMnB1) , COMnB0(COMnB0) ,
    WGMn3(WGMn3) , WGMn2(WGMn2) , WGMn1(WGMn1) , WGMn0(WGMn0) ,
    CSn2(CSn2) , CSn1(CSn1) , CSn0(CSn0) ,
    ICNCn(ICNCn) , ICESn(ICESn) ,
    FOCnA(FOCnA) , FOCnB(FOCnB) ,
    OCRnA(OCRnA) , OCRnB(OCRnB) , ICRn(ICRn) ,
    TIMSKn(TIMSKn) , OCIEnA(OCIEnA) , OCIEnB(OCIEnB) , ICIEn(ICIEn) , TOIEn(TOIEn) ,
    TIFRn(TIFRn) , OCFnA(OCFnA) , OCFnB(OCFnB) , ICFn(ICFn) , TOVn(TOVn) ,
    compAInt(compAInt) , compBInt(compBInt) , captInt(captInt) , ovfInt(ovfInt) ,
#if defined( __AVR_ATmega2560__ )
    COMnC1(COMnC1) , COMnC0(COMnC0) ,
    FOCnC(FOCnC) ,
    OCRnC(OCRnC) ,
    OCIEnC(OCIEnC) ,
    OCFnC(OCFnC) ,
    compCInt(compCInt) ,
#endif
    reserved( false ) ,
    extTickRate( 0 )
{}

// ------------------------------------------- //
//            Mode and Clock Source            //
// ------------------------------------------- //

void BaseTimer16::setMode( uint8_t mode ) {
    uint8_t oldSREG = SREG;
    cli();
    
    *TCCRnA &= ~( (1<<WGMn1) | (1<<WGMn0) );
    *TCCRnB &= ~( (1<<WGMn3) | (1<<WGMn2) );
    switch ( mode ) {
        case NORMAL:                                                                                          break;
        case PWM_PC_8_BIT:                                            *TCCRnA |=                ( 1<<WGMn0 ); break;
        case PWM_PC_9_BIT:                                            *TCCRnA |= ( 1<<WGMn1 );                break;
        case PWM_PC_10_BIT:                                           *TCCRnA |= ( 1<<WGMn1 ) | ( 1<<WGMn0 ); break;
        case CTC_OCA:         *TCCRnB |=                ( 1<<WGMn2 );                                         break;
        case PWM_FAST_8_BIT:  *TCCRnB |=                ( 1<<WGMn2 ); *TCCRnA |=                ( 1<<WGMn0 ); break;
        case PWM_FAST_9_BIT:  *TCCRnB |=                ( 1<<WGMn2 ); *TCCRnA |= ( 1<<WGMn1 );                break;
        case PWM_FAST_10_BIT: *TCCRnB |=                ( 1<<WGMn2 ); *TCCRnA |= ( 1<<WGMn1 ) | ( 1<<WGMn0 ); break;
        case PWM_PFC_IC:      *TCCRnB |= ( 1<<WGMn3 );                                                        break;
        case PWM_PFC_OCA:     *TCCRnB |= ( 1<<WGMn3 );                *TCCRnA |=                ( 1<<WGMn0 ); break;
        case PWM_PC_IC:       *TCCRnB |= ( 1<<WGMn3 );                *TCCRnA |= ( 1<<WGMn1 );                break;
        case PWM_PC_OCA:      *TCCRnB |= ( 1<<WGMn3 );                *TCCRnA |= ( 1<<WGMn1 ) | ( 1<<WGMn0 ); break;
        case CTC_IC:          *TCCRnB |= ( 1<<WGMn3 ) | ( 1<<WGMn2 );                                         break;
        // Reserved           
        case PWM_FAST_IC:     *TCCRnB |= ( 1<<WGMn3 ) | ( 1<<WGMn2 ); *TCCRnA |= ( 1<<WGMn1 );                break;
        case PWM_FAST_OCA:    *TCCRnB |= ( 1<<WGMn3 ) | ( 1<<WGMn2 ); *TCCRnA |= ( 1<<WGMn1 ) | ( 1<<WGMn0 ); break;
    }
    
    SREG = oldSREG;
}

uint8_t BaseTimer16::getMode() {
    uint8_t wgma = *TCCRnB & ( (1<<WGMn1) | (1<<WGMn0) );
    uint8_t wgmb = *TCCRnB & ( (1<<WGMn3) | (1<<WGMn2) );
    if ( wgmb & (( 1<<WGMn3 ) | ( 1<<WGMn2 )) ) {
        if ( wgma & (( 1<<WGMn1 ) | ( 1<<WGMn0 )) ) {
            return PWM_FAST_OCA;
        } else if ( wgma & (1<<WGMn1) ) {
            return PWM_FAST_IC;
        } else if ( wgma & (1<<WGMn0) ) {
            return UINT8_MAX;
        } else {
            return CTC_IC;
        }
    } else if ( wgmb & (1<<WGMn3) ) {
        if ( wgma & (( 1<<WGMn1 ) | ( 1<<WGMn0 )) ) {
            return PWM_PC_OCA;
        } else if ( wgma & (1<<WGMn1) ) {
            return PWM_PC_IC;
        } else if ( wgma & (1<<WGMn0) ) {
            return PWM_PFC_OCA;
        } else {
            return PWM_PFC_IC;
        }
    } else if ( wgmb & (1<<WGMn2) ) {
        if ( wgma & (( 1<<WGMn1 ) | ( 1<<WGMn0 )) ) {
            return PWM_FAST_10_BIT;
        } else if ( wgma & (1<<WGMn1) ) {
            return PWM_FAST_9_BIT;
        } else if ( wgma & (1<<WGMn0) ) {
            return PWM_FAST_8_BIT;
        } else {
            return CTC_OCA;
        }
    } else {
        if ( wgma & (( 1<<WGMn1 ) | ( 1<<WGMn0 )) ) {
            return PWM_PC_10_BIT;
        } else if ( wgma & (1<<WGMn1) ) {
            return PWM_PC_9_BIT;
        } else if ( wgma & (1<<WGMn0) ) {
            return PWM_PC_8_BIT;
        } else {
            return NORMAL;
        }
    }
}

void BaseTimer16::setClockSource( uint8_t source ) {
    uint8_t oldSREG = SREG;
    cli();
    
    *TCCRnB &= ~( (1<<CSn2) | (1<<CSn1) | (1<<CSn0) );
    switch ( source ) {
        case NO_CLOCK:                                                        break;
        case CLOCK_1:     *TCCRnB |=                             ( 1<<CSn0 ); break;
        case CLOCK_8:     *TCCRnB |=               ( 1<<CSn1 )              ; break;
        case CLOCK_64:    *TCCRnB |=               ( 1<<CSn1 ) | ( 1<<CSn0 ); break;
        case CLOCK_256:   *TCCRnB |= ( 1<<CSn2 )                            ; break;
        case CLOCK_1024:  *TCCRnB |= ( 1<<CSn2 ) |               ( 1<<CSn0 ); break;
        case EXT_FALLING: *TCCRnB |= ( 1<<CSn2 ) | ( 1<<CSn1 )              ; break;
        case EXT_RISING:  *TCCRnB |= ( 1<<CSn2 ) | ( 1<<CSn1 ) | ( 1<<CSn0 ); break;
    }
    
    SREG = oldSREG;
}

uint8_t BaseTimer16::getClockSource() {
    uint8_t cs = *TCCRnB & ( (1<<CSn2) | (1<<CSn1) | (1<<CSn0) );
    if ( cs & (( 1<<CSn2 ) | ( 1<<CSn1 ) | ( 1<<CSn0 )) ) {
        return EXT_RISING;
    } else if ( cs & (( 1<<CSn2 ) | ( 1<<CSn1 )) ) {
        return EXT_FALLING;
    } else if ( cs & (( 1<<CSn2 ) | ( 1<<CSn0 )) ) {
        return CLOCK_1024;
    } else if ( cs & (1<<CSn2) ) {
        return CLOCK_256;
    } else if ( cs & (( 1<<CSn1 ) | ( 1<<CSn0 )) ) {
        return CLOCK_64;
    } else if ( cs & (1<<CSn1) ) {
        return CLOCK_8;
    } else if ( cs & (1<<CSn0) ) {
        return CLOCK_1;
    } else {
        return NO_CLOCK;
    }
}

// ------------------------------- //
//            Tick Rate            //
// ------------------------------- //

void BaseTimer16::setExternalTickRate( float tickRate ) {
    extTickRate = tickRate;
}

float BaseTimer16::getTickRate() {
    switch ( getClockSource() ) {
        case NO_CLOCK:    return 0;
        case CLOCK_1:     return F_CPU;
        case CLOCK_8:     return F_CPU /    8;
        case CLOCK_64:    return F_CPU /   64;
        case CLOCK_256:   return F_CPU /  256;
        case CLOCK_1024:  return F_CPU / 1024;
        case EXT_FALLING: return extTickRate;
        case EXT_RISING:  return extTickRate;
    }
    return 0;
}

// --------------------------------------- //
//            Set and Get TCNTn            //
// --------------------------------------- //

void BaseTimer16::setCounter( uint16_t value ) { *TCNTn = value; }
uint16_t BaseTimer16::getCounter() { return *TCNTn; }

// --------------------------------------- //
//            Compare A Methods            //
// --------------------------------------- //

void BaseTimer16::setOutputCompareA( uint16_t value ) { *OCRnA = value; }
uint16_t BaseTimer16::getOutputCompareA() { return *OCRnA; }
void BaseTimer16::setCompareOutputModeA( uint8_t mode ) {
    uint8_t oldSREG = SREG;
    cli();
    
    *TCCRnA &= ~( (1<<COMnA1) | (1<<COMnA0) );
    switch ( mode ) {
        case NORMAL:                                                    break;
        case TOGGLE_ON_MATCH: *TCCRnA |=                 ( 1<<COMnA0 ); break;
        case CLEAR_ON_MATCH:  *TCCRnA |= ( 1<<COMnA1 );                 break;
        case SET_ON_MATCH:    *TCCRnA |= ( 1<<COMnA1 ) | ( 1<<COMnA0 ); break;
    }
    
    SREG = oldSREG;
}
void BaseTimer16::forceOutputCompareA() { *TCCRnC |= ( 1<<FOCnA ); }
bool BaseTimer16::getOutputCompareAFlag() { return ( *TIFRn & (1<<OCFnA) ); }
void BaseTimer16::clearOutputCompareAFlag() { *TIFRn |= ( 1<<OCFnA ); }

// --------------------------------------- //
//            Compare B Methods            //
// --------------------------------------- //

void BaseTimer16::setOutputCompareB( uint16_t value ) { *OCRnB = value; }
uint16_t BaseTimer16::getOutputCompareB() { return *OCRnB; }
void BaseTimer16::setCompareOutputModeB( uint8_t mode ) {
    uint8_t oldSREG = SREG;
    cli();
    
    *TCCRnB &= ~( (1<<COMnB1) | (1<<COMnB0) );
    switch ( mode ) {
        case NORMAL:                                                    break;
        case TOGGLE_ON_MATCH: *TCCRnB |=                 ( 1<<COMnB0 ); break;
        case CLEAR_ON_MATCH:  *TCCRnB |= ( 1<<COMnB1 );                 break;
        case SET_ON_MATCH:    *TCCRnB |= ( 1<<COMnB1 ) | ( 1<<COMnB0 ); break;
    }
    
    SREG = oldSREG;
}
void BaseTimer16::forceOutputCompareB() { *TCCRnC |= ( 1<<FOCnB ); }
bool BaseTimer16::getOutputCompareBFlag() { return ( *TIFRn & (1<<OCFnB) ); }
void BaseTimer16::clearOutputCompareBFlag() { *TIFRn |= ( 1<<OCFnB ); }

// --------------------------------------- //
//            Compare C Methods            //
// --------------------------------------- //

#if defined( __AVR_ATmega2560__ )
void BaseTimer16::setOutputCompareC( uint16_t value ) { *OCRnC = value; }
uint16_t BaseTimer16::getOutputCompareC() { return *OCRnC; }
void BaseTimer16::setCompareOutputModeC( uint8_t mode ) {
    uint8_t oldSREG = SREG;
    cli();
    
    *TCCRnC &= ~( (1<<COMnC1) | (1<<COMnC0) );
    switch ( mode ) {
        case NORMAL:                                                    break;
        case TOGGLE_ON_MATCH: *TCCRnC |=                 ( 1<<COMnC0 ); break;
        case CLEAR_ON_MATCH:  *TCCRnC |= ( 1<<COMnC1 );                 break;
        case SET_ON_MATCH:    *TCCRnC |= ( 1<<COMnC1 ) | ( 1<<COMnC0 ); break;
    }
    
    SREG = oldSREG;
}
void BaseTimer16::forceOutputCompareC() { *TCCRnC |= ( 1<<FOCnC ); }
bool BaseTimer16::getOutputCompareCFlag() { return ( *TIFRn & (1<<OCFnC) ); }
void BaseTimer16::clearOutputCompareCFlag() { *TIFRn |= ( 1<<OCFnC ); }
#endif

// ------------------------------------------- //
//            Input Capture Methods            //
// ------------------------------------------- //

void BaseTimer16::setInputCapture( uint16_t value ) { *ICRn = value; }
uint16_t BaseTimer16::getInputCapture() { return *ICRn; }
bool BaseTimer16::getInputCaptureFlag() { return ( *TIFRn & (1<<ICFn) ); }
void BaseTimer16::clearInputCaptureFlag() { *TIFRn |= ( 1<<ICFn ); }
void BaseTimer16::configureInputCapture( uint8_t edgeMode , bool noiseCanceller ) {
    uint8_t oldSREG = SREG;
    cli();
    
    switch ( edgeMode ) {
        case RISING:  *TCCRnB |=  ( 1<<ICESn ); break;
        case FALLING: *TCCRnB &= ~( 1<<ICESn ); break;
    }
    if ( noiseCanceller ) *TCCRnB |=  ( 1<<ICNCn );
    else                  *TCCRnB &= ~( 1<<ICNCn );
    
    SREG = oldSREG;
}

// ----------------------------------- //
//            Overflow Flag            //
// ----------------------------------- //

bool BaseTimer16::getOverflowFlag() { return ( *TIFRn & (1<<TOVn) ); }
void BaseTimer16::clearOverflowFlag() { *TIFRn |= ( 1<<TOVn ); }

// -------------------------------- //
//            Interrupts            //
// -------------------------------- //

void BaseTimer16::attachInterrupt( uint8_t mode , void (*func)() ) {
    uint8_t oldSREG = SREG;
    cli();
    
    switch ( mode ) {
        case COMPARE_MATCH_A: compAInt->func = func; compAInt->arg = nullptr; *TIMSKn |= ( 1<<OCIEnA ); break;
        case COMPARE_MATCH_B: compBInt->func = func; compBInt->arg = nullptr; *TIMSKn |= ( 1<<OCIEnB ); break;
        case INPUT_CAPTURE:   captInt->func  = func; captInt->arg  = nullptr; *TIMSKn |= ( 1<<ICIEn  ); break;
        case OVERFLOW:        ovfInt->func   = func; ovfInt->arg   = nullptr; *TIMSKn |= ( 1<<TOIEn  ); break;
#if defined( __AVR_ATmega2560__ )
        case COMPARE_MATCH_C: compCInt->func = func; compCInt->arg = nullptr; *TIMSKn |= ( 1<<OCIEnC ); break;
#endif
    }
    
    SREG = oldSREG;
}

void BaseTimer16::attachInterrupt( uint8_t mode , void (*func)(void*) , void *arg ) {
    uint8_t oldSREG = SREG;
    cli();
    
    switch ( mode ) {
        case COMPARE_MATCH_A: compAInt->funcArg = func; compAInt->arg = arg; *TIMSKn |= ( 1<<OCIEnA ); break;
        case COMPARE_MATCH_B: compBInt->funcArg = func; compBInt->arg = arg; *TIMSKn |= ( 1<<OCIEnB ); break;
        case INPUT_CAPTURE:   captInt->funcArg  = func; captInt->arg  = arg; *TIMSKn |= ( 1<<ICIEn  ); break;
        case OVERFLOW:        ovfInt->funcArg   = func; ovfInt->arg   = arg; *TIMSKn |= ( 1<<TOIEn  ); break;
#if defined( __AVR_ATmega2560__ )
        case COMPARE_MATCH_C: compCInt->funcArg = func; compCInt->arg = arg; *TIMSKn |= ( 1<<OCIEnC ); break;
#endif
    }
    
    SREG = oldSREG;
}

void BaseTimer16::enableInterrupt( uint8_t mode ) {
    switch ( mode ) {
        case COMPARE_MATCH_A: *TIMSKn |= ( 1<<OCIEnA ); break;
        case COMPARE_MATCH_B: *TIMSKn |= ( 1<<OCIEnB ); break;
        case INPUT_CAPTURE:   *TIMSKn |= ( 1<<ICIEn  ); break;
        case OVERFLOW:        *TIMSKn |= ( 1<<TOIEn  ); break;
#if defined( __AVR_ATmega2560__ )
        case COMPARE_MATCH_C: *TIMSKn |= ( 1<<OCIEnC ); break;
#endif
    }
}

void BaseTimer16::disableInterrupt( uint8_t mode ) {
    switch ( mode ) {
        case COMPARE_MATCH_A: *TIMSKn &= ~( 1<<OCIEnA ); break;
        case COMPARE_MATCH_B: *TIMSKn &= ~( 1<<OCIEnB ); break;
        case INPUT_CAPTURE:   *TIMSKn &= ~( 1<<ICIEn  ); break;
        case OVERFLOW:        *TIMSKn &= ~( 1<<TOIEn  ); break;
#if defined( __AVR_ATmega2560__ )
        case COMPARE_MATCH_C: *TIMSKn &= ~( 1<<OCIEnC ); break;
#endif
    }
}

bool BaseTimer16::interruptEnabled( uint8_t mode ) {
    switch ( mode ) {
        case COMPARE_MATCH_A: return *TIMSKn & ( 1<<OCIEnA );
        case COMPARE_MATCH_B: return *TIMSKn & ( 1<<OCIEnB );
        case INPUT_CAPTURE:   return *TIMSKn & ( 1<<ICIEn  );
        case OVERFLOW:        return *TIMSKn & ( 1<<TOIEn  );
#if defined( __AVR_ATmega2560__ )
        case COMPARE_MATCH_C: return *TIMSKn & ( 1<<OCIEnC );
#endif
    }
    return false;
}
