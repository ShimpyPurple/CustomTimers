#include "BaseTimer8Async.h"

// --------------------------------- //
//            Constructor            //
// --------------------------------- //

BaseTimer8Async::BaseTimer8Async(
    volatile uint8_t *TCNTn ,
    volatile uint8_t *TCCRnA , volatile uint8_t *TCCRnB ,
    uint8_t COMnA1 , uint8_t COMnA0 , uint8_t COMnB1 , uint8_t COMnB0 ,
    uint8_t WGMn2 , uint8_t WGMn1 , uint8_t WGMn0 ,
    uint8_t CSn2 , uint8_t CSn1 , uint8_t CSn0 ,
    uint8_t FOCnA , uint8_t FOCnB ,
    volatile uint8_t *OCRnA , volatile uint8_t *OCRnB ,
    volatile uint8_t *TIMSKn , uint8_t OCIEnA , uint8_t OCIEnB , uint8_t TOIEn ,
    volatile uint8_t *TIFRn , uint8_t OCFnA , uint8_t OCFnB , uint8_t TOVn ,
    TimerInt *compAInt , TimerInt *compBInt , TimerInt *ovfInt
):
    TCNTn(TCNTn) ,
    TCCRnA(TCCRnA) , TCCRnB(TCCRnB) ,
    COMnA1(COMnA1) , COMnA0(COMnA0) , COMnB1(COMnB1) , COMnB0(COMnB0) ,
    WGMn2(WGMn2) , WGMn1(WGMn1) , WGMn0(WGMn0) ,
    CSn2(CSn2) , CSn1(CSn1) , CSn0(CSn0) ,
    FOCnA(FOCnA) , FOCnB(FOCnB) ,
    OCRnA(OCRnA) , OCRnB(OCRnB) ,
    TIMSKn(TIMSKn) , OCIEnA(OCIEnA) , OCIEnB(OCIEnB) , TOIEn(TOIEn) ,
    TIFRn(TIFRn) , OCFnA(OCFnA) , OCFnB(OCFnB) , TOVn(TOVn) ,
    compAInt(compAInt) , compBInt(compBInt) , ovfInt(ovfInt) ,
    reserved( false ) ,
    clockRate( F_CPU )
{}

// ------------------------------------------- //
//            Mode and Clock Source            //
// ------------------------------------------- //

void BaseTimer8Async::setMode( uint8_t mode ) {
    uint8_t oldSREG = SREG;
    cli();
    
    *TCCRnA &= ~( (1<<WGMn1) | (1<<WGMn0) );
    *TCCRnB &= ~( 1<<WGMn2 );
    switch ( mode ) {
        case WGM_NORMAL:                                                                      break;
        case PWM_PC_8_BIT:                            *TCCRnA |=                ( 1<<WGMn0 ); break;
        case CTC_OCA:                                 *TCCRnA |= ( 1<<WGMn1 );                break;
        case PWM_FAST_8_BIT:                          *TCCRnA |= ( 1<<WGMn1 ) | ( 1<<WGMn0 ); break;
        // Reserved
        case PWM_PC_OCA:     *TCCRnB |= ( 1<<WGMn2 ); *TCCRnA |=                ( 1<<WGMn0 ); break;
        // Reserved
        case PWM_FAST_OCA:   *TCCRnB |= ( 1<<WGMn2 ); *TCCRnA |= ( 1<<WGMn1 ) | ( 1<<WGMn0 ); break;
    }
    
    SREG = oldSREG;
}

uint8_t BaseTimer8Async::getMode() {
    switch ( (*TCCRnB>>WGMn2 & 1)<<2 | (*TCCRnA>>WGMn1 & 1)<<1 | (*TCCRnA>>WGMn0 & 1) ) {
        case 0: return WGM_NORMAL;
        case 1: return PWM_PC_8_BIT;
        case 2: return CTC_OCA;
        case 3: return PWM_FAST_8_BIT;
        case 5: return PWM_PC_OCA;
        case 7: return PWM_FAST_OCA;
        default: return WGM_NORMAL;
    }
}

void BaseTimer8Async::setClockSource( uint8_t source ) {
    uint8_t oldSREG = SREG;
    cli();
    
    *TCCRnB &= ~( (1<<CSn2) | (1<<CSn1) | (1<<CSn0) );
    switch ( source ) {
        case NO_CLOCK:                                                       break;
        case CLOCK_1:    *TCCRnB |=                             ( 1<<CSn0 ); break;
        case CLOCK_8:    *TCCRnB |=               ( 1<<CSn1 )              ; break;
        case CLOCK_32:   *TCCRnB |=               ( 1<<CSn1 ) | ( 1<<CSn0 ); break;
        case CLOCK_64:   *TCCRnB |= ( 1<<CSn2 )                            ; break;
        case CLOCK_128:  *TCCRnB |= ( 1<<CSn2 ) |               ( 1<<CSn0 ); break;
        case CLOCK_256:  *TCCRnB |= ( 1<<CSn2 ) | ( 1<<CSn1 )              ; break;
        case CLOCK_1024: *TCCRnB |= ( 1<<CSn2 ) | ( 1<<CSn1 ) | ( 1<<CSn0 ); break;
    }
    
    SREG = oldSREG;
}

uint8_t BaseTimer8Async::getClockSource() {
    switch ( (*TCCRnB>>CSn2 & 1)<<2 | (*TCCRnB>>CSn1 & 1)<<1 | (*TCCRnB>>CSn0 & 1) ) {
        case 0: return NO_CLOCK;
        case 1: return CLOCK_1;
        case 2: return CLOCK_8;
        case 3: return CLOCK_32;
        case 4: return CLOCK_64;
        case 5: return CLOCK_128;
        case 6: return CLOCK_256;
        case 7: return CLOCK_1024;
        default: return NO_CLOCK;
    }
}

// ------------------------------- //
//            Tick Rate            //
// ------------------------------- //

void BaseTimer8Async::setClockRate( float clockRate ) {
    this->clockRate = clockRate;
}

float BaseTimer8Async::getTickRate() {
    switch ( getClockSource() ) {
        case NO_CLOCK:   return 0;
        case CLOCK_1:    return F_CPU;
        case CLOCK_8:    return F_CPU /    8;
        case CLOCK_32:   return F_CPU /   32;
        case CLOCK_64:   return F_CPU /   64;
        case CLOCK_128:  return F_CPU /  128;
        case CLOCK_256:  return F_CPU /  256;
        case CLOCK_1024: return F_CPU / 1024;
    }
    return 0;
}

// --------------------------------------- //
//            Set and Get TCNTn            //
// --------------------------------------- //

void BaseTimer8Async::setCounter( uint8_t value ) { *TCNTn = value; }
uint8_t BaseTimer8Async::getCounter() { return *TCNTn; }

// --------------------------------------- //
//            Compare A Methods            //
// --------------------------------------- //

void BaseTimer8Async::setOutputCompareA( uint8_t value ) { *OCRnA = value; }
uint8_t BaseTimer8Async::getOutputCompareA() { return *OCRnA; }
void BaseTimer8Async::setCompareOutputModeA( uint8_t mode ) {
    uint8_t oldSREG = SREG;
    cli();
    
    *TCCRnA &= ~( (1<<COMnA1) | (1<<COMnA0) );
    switch ( mode ) {
        case NORMAL_PIN_OP:                                             break;
        case TOGGLE_ON_MATCH: *TCCRnA |=                 ( 1<<COMnA0 ); break;
        case CLEAR_ON_MATCH:  *TCCRnA |= ( 1<<COMnA1 );                 break;
        case SET_ON_MATCH:    *TCCRnA |= ( 1<<COMnA1 ) | ( 1<<COMnA0 ); break;
    }
    
    SREG = oldSREG;
}
void BaseTimer8Async::forceOutputCompareA() { *TCCRnB |= ( 1<<FOCnA ); }
bool BaseTimer8Async::getOutputCompareAFlag() { return ( *TIFRn & (1<<OCFnA) ); }
void BaseTimer8Async::clearOutputCompareAFlag() { *TIFRn |= ( 1<<OCFnA ); }

// --------------------------------------- //
//            Compare B Methods            //
// --------------------------------------- //

void BaseTimer8Async::setOutputCompareB( uint8_t value ) { *OCRnB = value; }
uint8_t BaseTimer8Async::getOutputCompareB() { return *OCRnB; }
void BaseTimer8Async::setCompareOutputModeB( uint8_t mode ) {
    uint8_t oldSREG = SREG;
    cli();
    
    *TCCRnB &= ~( (1<<COMnB1) | (1<<COMnB0) );
    switch ( mode ) {
        case NORMAL_PIN_OP:                                             break;
        case TOGGLE_ON_MATCH: *TCCRnB |=                 ( 1<<COMnB0 ); break;
        case CLEAR_ON_MATCH:  *TCCRnB |= ( 1<<COMnB1 );                 break;
        case SET_ON_MATCH:    *TCCRnB |= ( 1<<COMnB1 ) | ( 1<<COMnB0 ); break;
    }
    
    SREG = oldSREG;
}
void BaseTimer8Async::forceOutputCompareB() { *TCCRnB |= ( 1<<FOCnB ); }
bool BaseTimer8Async::getOutputCompareBFlag() { return ( *TIFRn & (1<<OCFnB) ); }
void BaseTimer8Async::clearOutputCompareBFlag() { *TIFRn |= ( 1<<OCFnB ); }

// ----------------------------------- //
//            Overflow Flag            //
// ----------------------------------- //

bool BaseTimer8Async::getOverflowFlag() { return ( *TIFRn & (1<<TOVn) ); }
void BaseTimer8Async::clearOverflowFlag() { *TIFRn |= ( 1<<TOVn ); }

// -------------------------------- //
//            Interrupts            //
// -------------------------------- //

void BaseTimer8Async::attachInterrupt( uint8_t mode , void (*func)() ) {
    uint8_t oldSREG = SREG;
    cli();
    
    switch ( mode ) {
        case COMPARE_MATCH_A: compAInt->func = func; compAInt->arg = nullptr; *TIMSKn |= ( 1<<OCIEnA ); break;
        case COMPARE_MATCH_B: compBInt->func = func; compBInt->arg = nullptr; *TIMSKn |= ( 1<<OCIEnB ); break;
        case OVERFLOW:        ovfInt->func   = func; ovfInt->arg   = nullptr; *TIMSKn |= ( 1<<TOIEn  ); break;
    }
    
    SREG = oldSREG;
}

void BaseTimer8Async::attachInterrupt( uint8_t mode , void (*func)(void*) , void *arg ) {
    uint8_t oldSREG = SREG;
    cli();
    
    switch ( mode ) {
        case COMPARE_MATCH_A: compAInt->funcArg = func; compAInt->arg = arg; *TIMSKn |= ( 1<<OCIEnA ); break;
        case COMPARE_MATCH_B: compBInt->funcArg = func; compBInt->arg = arg; *TIMSKn |= ( 1<<OCIEnB ); break;
        case OVERFLOW:        ovfInt->funcArg   = func; ovfInt->arg   = arg; *TIMSKn |= ( 1<<TOIEn  ); break;
    }
    
    SREG = oldSREG;
}

void BaseTimer8Async::enableInterrupt( uint8_t mode ) {
    switch ( mode ) {
        case COMPARE_MATCH_A: *TIMSKn |= ( 1<<OCIEnA ); break;
        case COMPARE_MATCH_B: *TIMSKn |= ( 1<<OCIEnB ); break;
        case OVERFLOW:        *TIMSKn |= ( 1<<TOIEn  ); break;
    }
}

void BaseTimer8Async::disableInterrupt( uint8_t mode ) {
    switch ( mode ) {
        case COMPARE_MATCH_A: *TIMSKn &= ~( 1<<OCIEnA ); break;
        case COMPARE_MATCH_B: *TIMSKn &= ~( 1<<OCIEnB ); break;
        case OVERFLOW:        *TIMSKn &= ~( 1<<TOIEn  ); break;
    }
}

bool BaseTimer8Async::interruptEnabled( uint8_t mode ) {
    switch ( mode ) {
        case COMPARE_MATCH_A: return *TIMSKn & ( 1<<OCIEnA );
        case COMPARE_MATCH_B: return *TIMSKn & ( 1<<OCIEnB );
        case OVERFLOW:        return *TIMSKn & ( 1<<TOIEn  );
    }
    return false;
}
