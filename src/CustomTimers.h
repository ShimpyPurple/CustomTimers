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

class GenericTimer {
    public:
        // Constructors
        GenericTimer( BaseTimer16 *timer16 );
        GenericTimer( BaseTimer8Async *timer8Async , bool emulate16bits );
        
        // Generic Timer Methods
        uint8_t getTimerType();
        BaseTimer16 *getTimer16();
        BaseTimer8Async *getTimer8Async();
        
        // Timer Reservation
        bool reserve();
        bool isFree();
        void release();
        
        // Mode and Clock Source
        void setMode( uint8_t mode );
        uint8_t getMode();
        void setClockSource( uint8_t source );
        uint8_t getClockSource();
        
        // Tick Rate
        void setExternalTickRate( float tickRate );
        void setClockRate( float clockRate );
        float getTickRate();
        
        // Set and Get TCNTn
        void setCounter( uint16_t value );
        uint16_t getCounter();
        
        // Compare A Methods
        void setOutputCompareA( uint16_t value );
        uint16_t getOutputCompareA();
        void setCompareOutputModeA( uint8_t mode );
        void forceOutputCompareA();
        bool getOutputCompareAFlag();
        void clearOutputCompareAFlag();
        
        // Compare B Methods
        void setOutputCompareB( uint16_t value );
        uint16_t getOutputCompareB();
        void setCompareOutputModeB( uint8_t mode );
        void forceOutputCompareB();
        bool getOutputCompareBFlag();
        void clearOutputCompareBFlag();
        
        // Compare C Methods
#if defined( __AVR_ATmega2560__ )
        void setOutputCompareC( uint16_t value );
        uint16_t getOutputCompareC();
        void setCompareOutputModeC( uint8_t mode );
        void forceOutputCompareC();
        bool getOutputCompareCFlag();
        void clearOutputCompareCFlag();
#endif
        
        // Input Capture Methods
        void setInputCapture( uint16_t value );
        uint16_t getInputCapture();
        bool getInputCaptureFlag();
        void clearInputCaptureFlag();
        void configureInputCapture( uint8_t edgeMode , bool noiseCanceller );
        
        // Overflow Flag
        bool getOverflowFlag();
        void clearOverflowFlag();
        
        // Interrupts
        void attachInterrupt( uint8_t mode , void (*func)() );
        void attachInterrupt( uint8_t mode , void (*func)(void*) , void *arg );
        void enableInterrupt( uint8_t mode );
        void disableInterrupt( uint8_t mode );
        bool interruptEnabled( uint8_t mode );
    
    private:
        uint8_t timerType;
        BaseTimer16 *timer16;
        BaseTimer8Async *timer8Async;
        bool emulate16bits;
        volatile uint8_t TCNTnExtraByte;
        volatile uint8_t OCRnAExtraByte;
        volatile uint8_t OCRnBExtraByte;
        bool ctcMode;
        void (*compAFunc)();
        void (*compAFuncArg)( void* );
        void *compAArg;
        static void compAISR( void *object );
        void (*compBFunc)();
        void (*compBFuncArg)( void* );
        void *compBArg;
        static void compBISR( void *object );
        void (*ovfFunc)();
        void (*ovfFuncArg)( void* );
        void *ovfArg;
        static void ovfISR( void *object );
    
};

#endif