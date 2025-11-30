
///******************************************************************************
//! @file timer16_drv.h,v
//!
//! Copyright (c) 2006 Atmel.
//!
//! Use of this program is subject to Atmel's End User License Agreement.
//! Please read file license.txt for copyright notice.
//!
//! @brief This file contains the prototypes and the macros of the
//!        low level functions (drivers) of:
//!             - 16-bit timer(s)
//!             - for AT90USB162
//!
//! This file can be parsed by Doxygen for automatic documentation generation.
//! This file has been validated with AVRStudio-412462/WinAVR-20060125.
//!
//! @version 1.3 at90usb162-cdc-1_0_1
//!
//! @todo
//! @bug
//******************************************************************************

#ifndef _TIMER16_DRV_H_
#define _TIMER16_DRV_H_

//_____ I N C L U D E S ________________________________________________________

#include "config.h"

//_____ G E N E R A L    D E F I N I T I O N S _________________________________


//_____ M A C R O S ____________________________________________________________

    // ---------- To order the loading (reading) of 16-bit registers
#define Timer16_get_counter()       ( timer16_get_counter() )        // c.f. "timer16_drv.c" file
#define Timer16_get_capture()       ( timer16_get_capture() )        // c.f. "timer16_drv.c" file
    // ---------- Two ways to have a look on the things
#define Timer16_set_pwm_a(value)    ( Timer16_set_compare_a(value) ) // c.f. above !
#define Timer16_set_pwm_b(value)    ( Timer16_set_compare_b(value) ) // c.f. above !
#define Timer16_set_pwm_c(value)    ( Timer16_set_compare_c(value) ) // c.f. above !
#define Timer16_get_pwm_a()         ( Timer16_get_compare_a() )      // c.f. above !
#define Timer16_get_pwm_b()         ( Timer16_get_compare_b() )      // c.f. above !
#define Timer16_get_pwm_c()         ( Timer16_get_compare_c() )      // c.f. above !
    // ---------- If no clock, the timer is off !
#define Timer16_off()                 Timer16_set_clock(TIMER16_NO_CLOCK)

//_____ D E F .  &   M A C R O S   for   H W   C O N F . _______________________

    //----- CARE WITH THE ORDER WHEN 16-BIT REGISTERS ARE READ
    //      ==================================================
    //----- For sensitive 16-bit registers (c.f. temporary reg), the macros are:
    //-----     *  Timer16_get_nnn_low()
    //-----     *  Timer16_get_nnn_high()
    //----- For instance, in your main, do not write:
    //-----     short_temp = ((Timer16_get_nnn_high())<<8) | (Timer16_get_nnn_low());
    //-----   or
    //-----     short_temp = (Timer16_get_nnn_low()) | ((Timer16_get_nnn_high())<<8);
    //-----   because IAR and ImageCraft doesn't evaluate the operandes in the same order!
    //-----
    //----- The good way to write a READ (load) sequence is in 2 times:
    //-----     short_temp  =  Timer16_get_nnn_low();
    //-----     short_temp |= (Timer16_get_nnn_high() << 8 );
    //-----
    //----- Otherwise a macro "Timer16_get_nnn()" exits and call "timer16_get_counter()" function

#       define Timer16_select(timer16_num)     __no_operation()    // for compatibility with MCU with 2 timers
    // ---------- Macros
#       define Timer16_clear()  ( TCCR1B=0, TCCR1A=0, TCCR1C=0, TCNT1H=0, TCNT1L= 0, OCR1AH=0, OCR1AL=0, \
                                  OCR1BH=0, OCR1BL=0, OCR1CH=0, OCR1CL=0, ICR1H=0, ICR1L=0              )
        // ----------
#       define Timer16_set_counter(value)       ( TCNT1H = ((U8)(value>>8)), TCNT1L = ((U8)(value)))
#       define Timer16_get_counter_low()        ((U16)(TCNT1L))
#       define Timer16_get_counter_high()       ((U16)(TCNT1H))
        // ----------
#       define Timer16_set_compare_a(value)     ( OCR1AH = ((U8)(value>>8)), OCR1AL = ((U8)(value)))
#       define Timer16_set_compare_b(value)     ( OCR1BH = ((U8)(value>>8)), OCR1BL = ((U8)(value)))
#       define Timer16_set_compare_c(value)     ( OCR1CH = ((U8)(value>>8)), OCR1CL = ((U8)(value)))
#       define Timer16_get_compare_a()          ( OCR1A )      // The temporary register is not used
#       define Timer16_get_compare_b()          ( OCR1B )      // The temporary register is not used
#       define Timer16_get_compare_c()          ( OCR1C )      // The temporary register is not used
        // ----------
#       define Timer16_set_capture(value)       ( ICR1H = ((U8)(value>>8)), ICR1L = ((U8)(value)) )
#       define Timer16_get_capture_low()        ((U16)(ICR1L))
#       define Timer16_get_capture_high()       ((U16)(ICR1H))
        // ----------
#       define Timer16_set_mode_output_a(conf)  ( TCCR1A = (TCCR1A & (~TIMER16_COMP_MODE_MASK_A)) | (conf << COM1A0) )
#       define Timer16_set_mode_output_b(conf)  ( TCCR1A = (TCCR1A & (~TIMER16_COMP_MODE_MASK_B)) | (conf << COM1B0) )
#       define Timer16_set_mode_output_c(conf)  ( TCCR1A = (TCCR1A & (~TIMER16_COMP_MODE_MASK_C)) | (conf << COM1C0) )
#       define Timer16_get_mode_output_a()      ((TCCR1A & TIMER16_COMP_MODE_MASK_A) >> COM1A0 )
#       define Timer16_get_mode_output_b()      ((TCCR1A & TIMER16_COMP_MODE_MASK_B) >> COM1B0 )
#       define Timer16_get_mode_output_c()      ((TCCR1A & TIMER16_COMP_MODE_MASK_C) >> COM1C0 )
        // ----------
#       define Timer16_set_waveform_mode(conf)  ( TCCR1A = (TCCR1A & (~TIMER16_WGM_RA_MASK)) | ((conf &  0x3) << WGM10), \
                                                  TCCR1B = (TCCR1B & (~TIMER16_WGM_RB_MASK)) | ((conf >> 0x2) << WGM12)  )
#       define Timer16_get_waveform_mode()     (((TCCR1A & TIMER16_WGM_RA_MASK) >> WGM10) |         \
                                               (((TCCR1B & TIMER16_WGM_RB_MASK) >> WGM12) << 0x2)   )
        // ----------
#       define Timer16_set_clock(value)        ( TCCR1B = (TCCR1B & (~TIMER16_CLK_MASK)) | (value << CS10) )
#       define Timer16_get_clock()            (((TCCR1B & TIMER16_CLK_MASK) >> CS10) )
        // ----------
#       define Timer16_set_input_filter()      ( TCCR1B |=  (1<<ICNC1) )
#       define Timer16_clear_input_filter()    ( TCCR1B &= ~(1<<ICNC1) )
#       define Timer16_get_input_filter()      ((TCCR1B  &  (1<<ICNC1)) >> ICNC1 )
    // ----------
#       define Timer16_set_input_rising_edge() ( TCCR1B |=  (1<<ICES1) )
#       define Timer16_set_input_falling_edge()( TCCR1B &= ~(1<<ICES1) )
#       define Timer16_get_input_capture_edge()((TCCR1B &   (1<<ICES1)) >> ICES1 )
    // ----------
#       define Timer16_set_compare_force_a()   ( TCCR1C |=  (1<<FOC1A) )
#       define Timer16_set_compare_force_b()   ( TCCR1C |=  (1<<FOC1B) )
#       define Timer16_set_compare_force_c()   ( TCCR1C |=  (1<<FOC1C) )
#       define Timer16_clear_compare_force_a() ( TCCR1C &= ~(1<<FOC1A) )
#       define Timer16_clear_compare_force_b() ( TCCR1C &= ~(1<<FOC1B) )
#       define Timer16_clear_compare_force_c() ( TCCR1C &= ~(1<<FOC1C) )
#       define Timer16_get_compare_force_a()   ((TCCR1C  &  (1<<FOC1A)) >> FOC1A )
#       define Timer16_get_compare_force_b()   ((TCCR1C  &  (1<<FOC1B)) >> FOC1B )
#       define Timer16_get_compare_force_c()   ((TCCR1C  &  (1<<FOC1C)) >> FOC1C )
    // ----------
#       define Timer16_overflow_it_enable()    ( TIMSK1 |=  (1<<TOIE1)  )
#       define Timer16_overflow_it_disable()   ( TIMSK1 &= ~(1<<TOIE1)  )
#       define Timer16_compare_a_it_enable()   ( TIMSK1 |=  (1<<OCIE1A) )
#       define Timer16_compare_a_it_disable()  ( TIMSK1 &= ~(1<<OCIE1A) )
#       define Timer16_compare_b_it_enable()   ( TIMSK1 |=  (1<<OCIE1B) )
#       define Timer16_compare_b_it_disable()  ( TIMSK1 &= ~(1<<OCIE1B) )
#       define Timer16_compare_c_it_enable()   ( TIMSK1 |=  (1<<OCIE1C) )
#       define Timer16_compare_c_it_disable()  ( TIMSK1 &= ~(1<<OCIE1C) )
#       define Timer16_capture_it_enable()     ( TIMSK1 |=  (1<<ICIE1)  )
#       define Timer16_capture_it_disable()    ( TIMSK1 &= ~(1<<ICIE1)  )
#       define Timer16_get_overflow_it_mask()  ((TIMSK1  &  (1<<TOIE1) ) >> TOIE1  )
#       define Timer16_get_compare_a_it_mask() ((TIMSK1  &  (1<<OCIE1A)) >> OCIE1A )
#       define Timer16_get_compare_b_it_mask() ((TIMSK1  &  (1<<OCIE1B)) >> OCIE1B )
#       define Timer16_get_compare_c_it_mask() ((TIMSK1  &  (1<<OCIE1C)) >> OCIE1C )
#       define Timer16_get_capture_it_mask()   ((TIMSK1  &  (1<<ICIE1) ) >> ICIE1  )
    // ----------
#       define Timer16_clear_overflow_it()     ( TIFR1 |=  (1<<TOV1)  )
#       define Timer16_clear_compare_a_it()    ( TIFR1 |=  (1<<OCF1A) )
#       define Timer16_clear_compare_b_it()    ( TIFR1 |=  (1<<OCF1B) )
#       define Timer16_clear_compare_c_it()    ( TIFR1 |=  (1<<OCF1C) )
#       define Timer16_clear_capture_it()      ( TIFR1 |=  (1<<ICF1)  )
#       define Timer16_get_overflow_it()       ((TIFR1  &  (1<<TOV1) ) >> TOV1  )
#       define Timer16_get_compare_a_it()      ((TIFR1  &  (1<<OCF1A)) >> OCF1A )
#       define Timer16_get_compare_b_it()      ((TIFR1  &  (1<<OCF1B)) >> OCF1B )
#       define Timer16_get_compare_c_it()      ((TIFR1  &  (1<<OCF1C)) >> OCF1C )
#       define Timer16_get_capture_it()        ((TIFR1  &  (1<<ICF1) ) >> ICF1  )


//_____ T I M E R   D E F I N I T I O N S ______________________________________

    // ---------- Pre-definitions for "conf" field for Timer16_set(get)_mode_output_x(conf) macros
#define TIMER16_COMP_MODE_NORMAL    (0)
#define TIMER16_COMP_MODE_TOGGLE    (1)
#define TIMER16_COMP_MODE_CLEAR_OC  (2)
#define TIMER16_COMP_MODE_SET_OC    (3)
#define TIMER16_COMP_MODE_MASK_A    (3<<COM1A0)
#define TIMER16_COMP_MODE_MASK_B    (3<<COM1B0)
#define TIMER16_COMP_MODE_MASK_C    (3<<COM1C0)
    // ---------- Pre-definitions for "conf" field for Timer16_set_waveform_mode(conf) macro
#define TIMER16_WGM_NORMAL          (0)
#define TIMER16_WGM_CTC_OCR         (4)
#define TIMER16_WGM_CTC_ICR         (12)
#define TIMER16_WGM_PWM_PC8         (1)
#define TIMER16_WGM_PWM_PC9         (2)
#define TIMER16_WGM_PWM_PC10        (3)
#define TIMER16_WGM_PWM_PC_ICR      (10)
#define TIMER16_WGM_PWM_PC_OCR      (11)
#define TIMER16_WGM_PWM_PFC_ICR     (8)
#define TIMER16_WGM_PWM_PFC_OCR     (9)
#define TIMER16_WGM_FAST_PWM8       (5)
#define TIMER16_WGM_FAST_PWM9       (6)
#define TIMER16_WGM_FAST_PWM10      (7)
#define TIMER16_WGM_FAST_PWM_ICR    (14)
#define TIMER16_WGM_FAST_PWM_OCR    (15)
#define TIMER16_WGM_RA_MASK         (3<<WGM10)
#define TIMER16_WGM_RB_MASK         (3<<WGM12)
    // ---------- Pre-definitions for "value" field for Timer16_set_clock(value) macro
#define TIMER16_NO_CLOCK                 (0)
#define TIMER16_CLKIO_BY_1               (1)
#define TIMER16_CLKIO_BY_8               (2)
#define TIMER16_CLKIO_BY_64              (3)
#define TIMER16_CLKIO_BY_256             (4)
#define TIMER16_CLKIO_BY_1024            (5)
#define TIMER16_EXT_CLOCK_FALLING_EDGE   (6)
#define TIMER16_EXT_CLOCK_RISING_EDGE    (7)
#define TIMER16_CLK_MASK                 (7<<CS10)


//_____ D E C L A R A T I O N S ________________________________________________

//------------------------------------------------------------------------------
//  @fn timer16_get_counter
//!
//! This function READ the 16-bit TIMER counter.
//!
//! @warning
//!
//! @param
//!
//! @return 16-bit counter value
//!
extern  U16 timer16_get_counter(void);

//------------------------------------------------------------------------------
//  @fn timer16_get_capture
//!
//! This function READ the 16-bit TIMER capture register.
//!
//! @warning
//!
//! @param
//!
//! @return 16-bit capture value
//!
extern  U16 timer16_get_capture(void);

//______________________________________________________________________________

#endif  // _TIMER16_DRV_H_






























