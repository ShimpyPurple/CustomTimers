#ifndef Constants_h
#define Constants_h

#define NO_TIMER 0
#define TIMER_16_BIT 1
#define TIMER_8_BIT_ASYNC 2

#define TIMER_1 1
#define TIMER_2 2
#if defined( __AVR_ATmega2560__ )
#define TIMER_3 3
#define TIMER_4 4
#define TIMER_5 5
#endif

#define WGM_NORMAL       0
#define PWM_PC_8_BIT     1
#define PWM_PC_9_BIT     2
#define PWM_PC_10_BIT    3
#define CTC_OCA          4
#define PWM_FAST_8_BIT   5
#define PWM_FAST_9_BIT   6
#define PWM_FAST_10_BIT  7
#define PWM_PFC_IC       8
#define PWM_PFC_OCA      9
#define PWM_PC_IC       10
#define PWM_PC_OCA      11
#define CTC_IC          12
#define PWM_FAST_IC     14
#define PWM_FAST_OCA    15

#define NO_CLOCK    0
#define CLOCK_1     1
#define CLOCK_8     2
#define CLOCK_32    3
#define CLOCK_64    4
#define CLOCK_128   5
#define CLOCK_256   6
#define CLOCK_1024  7
#define EXT_FALLING 8
#define EXT_RISING  9

#define COMPARE_MATCH_A 0
#define COMPARE_MATCH_B 1
#define INPUT_CAPTURE   3
#define OVERFLOW        4
#if defined( __AVR_ATmega2560__ )
#define COMPARE_MATCH_C 2
#endif

#define NORMAL_PIN_OP   0
#define TOGGLE_ON_MATCH 1
#define CLEAR_ON_MATCH  2
#define SET_ON_MATCH    3
#define NON_INVERTING   CLEAR_ON_MATCH
#define INVERTING       SET_ON_MATCH

struct TimerInt {
    void (*func)() = []{};
    void (*funcArg)(void*) = [](void*){};
    void *arg = nullptr;
};

#endif