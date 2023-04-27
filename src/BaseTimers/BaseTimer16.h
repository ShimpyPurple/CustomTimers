#ifndef BaseTimer16_h
#define BaseTimer16_h

#include "Arduino.h"
#include "Constants.h"

#if !defined( __AVR_ATmega328P__ ) && !defined( __AVR_ATmega2560__ )
#warning "BaseTimer16 is only tested for ATmega328P and ATmega2560"
#endif

class BaseTimer16 {
    public:
        // Constructor
        BaseTimer16(
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
        );
        
        // Timer Reservation
        bool reserve();
        bool isFree();
        void release();
        
        // Mode and Clock Source
        void setMode( uint8_t mode );
        void setClockSource( uint8_t source );
		
		// Tick Rate
		void setExternalTickRate( float tickRate );
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
        volatile uint16_t *TCNTn;
        volatile uint8_t *TCCRnA; volatile uint8_t *TCCRnB; volatile uint8_t *TCCRnC;
        uint8_t COMnA1; uint8_t COMnA0; uint8_t COMnB1; uint8_t COMnB0;
        uint8_t WGMn3; uint8_t WGMn2; uint8_t WGMn1; uint8_t WGMn0;
        uint8_t CSn2; uint8_t CSn1; uint8_t CSn0;
        uint8_t ICNCn; uint8_t ICESn;
        uint8_t FOCnA; uint8_t FOCnB;
        volatile uint16_t *OCRnA; volatile uint16_t *OCRnB; volatile uint16_t *ICRn;
        volatile uint8_t *TIMSKn; uint8_t OCIEnA; uint8_t OCIEnB; uint8_t ICIEn; uint8_t TOIEn;
        volatile uint8_t *TIFRn; uint8_t OCFnA; uint8_t OCFnB; uint8_t ICFn; uint8_t TOVn;
        TimerInt *compAInt; TimerInt *compBInt; TimerInt *captInt; TimerInt *ovfInt;
#if defined( __AVR_ATmega2560__ )
        uint8_t COMnC1; uint8_t COMnC0;
        uint8_t FOCnC;
        volatile uint16_t *OCRnC;
        uint8_t OCIEnC;
        uint8_t OCFnC;
        TimerInt *compCInt;
#endif
        bool reserved;
		float extTickRate;

};

#endif