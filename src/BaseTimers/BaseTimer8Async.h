#ifndef BaseTimer8Async_h
#define BaseTimer8Async_h

#include "Arduino.h"
#include "Constants.h"

#if !defined( __AVR_ATmega328P__ ) && !defined( __AVR_ATmega2560__ )
#warning "BaseTimer8Async is only tested for ATmega328P and ATmega2560"
#endif

class BaseTimer8Async {
    public:
        // Constructor
        BaseTimer8Async(
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
        );
        
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
        void setClockRate( float clockRate );
        float getTickRate();
        
        // Set and Get TCNTn
        void setCounter( uint8_t value );
        uint8_t getCounter();
        
        // Compare A Methods
        void setOutputCompareA( uint8_t value );
        uint8_t getOutputCompareA();
        void setCompareOutputModeA( uint8_t mode );
        void forceOutputCompareA();
        bool getOutputCompareAFlag();
        void clearOutputCompareAFlag();
        
        // Compare B Methods
        void setOutputCompareB( uint8_t value );
        uint8_t getOutputCompareB();
        void setCompareOutputModeB( uint8_t mode );
        void forceOutputCompareB();
        bool getOutputCompareBFlag();
        void clearOutputCompareBFlag();
    
        // Overflow Flag
        bool getOverflowFlag();
        void clearOverflowFlag();
        
        // Interrupts
        void attachInterrupt( uint8_t mode , void (*func)() );
        void attachInterrupt( uint8_t mode , void (*func)(void*) , void *arg );
        void enableInterrupt( uint8_t mode );
        void disableInterrupt( uint8_t mode );
        bool interruptEnabled( uint8_t mode );
    
        // Async
        // ASSR Methods not implimented, because UNO and MEGA2560 boards use TOSC pins for main clock ...I think
    
    private:
        volatile uint8_t *TCNTn;
        volatile uint8_t *TCCRnA; volatile uint8_t *TCCRnB;
        uint8_t COMnA1; uint8_t COMnA0; uint8_t COMnB1; uint8_t COMnB0;
        uint8_t WGMn2; uint8_t WGMn1; uint8_t WGMn0;
        uint8_t CSn2; uint8_t CSn1; uint8_t CSn0;
        uint8_t FOCnA; uint8_t FOCnB;
        volatile uint8_t *OCRnA; volatile uint8_t *OCRnB;
        volatile uint8_t *TIMSKn; uint8_t OCIEnA; uint8_t OCIEnB; uint8_t TOIEn;
        volatile uint8_t *TIFRn; uint8_t OCFnA; uint8_t OCFnB; uint8_t TOVn;
        TimerInt *compAInt; TimerInt *compBInt; TimerInt *ovfInt;
        bool reserved;
        float clockRate;

};

#endif