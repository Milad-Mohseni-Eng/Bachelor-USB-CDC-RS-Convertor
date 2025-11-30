
//******************************************************************************
//! @file timer8_drv.h,v
//!
//! Copyright (c) 2006 Atmel.
//!
//! Use of this program is subject to Atmel's End User License Agreement.
//! Please read file license.txt for copyright notice.
//!
//! @brief This file contains the prototypes and the macros of the
//!        low level functions (drivers) of:
//!             - 8-bit timer(s)
//!             - for AT90USB162, AT90USB128x
//!
//! This file can be parsed by Doxygen for automatic documentation generation.
//!
//! @version 1.1 at90usb162-cdc-1_0_1
//!
//! @todo
//! @bug
//******************************************************************************

#ifndef _TIMER8_DRV_H_
#define _TIMER8_DRV_H_

//_____ I N C L U D E S ________________________________________________________

#include "config.h"

//_____ G E N E R A L    D E F I N I T I O N S _________________________________

#       define Timer8_select(timer8_num)       __no_operation() // for compatibility with others MCUs (2 timers)
    // ---------- Macros
#       define Timer8_clear()                  ( TCCR0A=0, TCCR0B=0, TCNT0=0, OCR0A=0, OCR0B=0)
        // ----------
#       define Timer8_set_counter(value)       ( TCNT0 = value )
#       define Timer8_get_counter()            ( TCNT0 )
        // ----------
#       define Timer8_set_compare_a(value)     ( OCR0A = value )
#       define Timer8_set_compare_b(value)     ( OCR0B = value )
#       define Timer8_set_compare(value)       ( Timer8_set_compare_a(value) )          // default : module A is used
#       define Timer8_get_compare_a()          ( OCR0A )
#       define Timer8_get_compare_b()          ( OCR0B )
#       define Timer8_get_compare()            ( Timer8_get_compare_a() )               // default : module A is used
        // ----------
#       define Timer8_force_output_compare_a() ( TCCR0B |= (1<FOC0A)  )
#       define Timer8_clear_output_compare_a() ( TCCR0B &= ~(1<FOC0A) )
#       define Timer8_force_output_compare_b() ( TCCR0B |= (1<FOC0B)  )
#       define Timer8_clear_output_compare_b() ( TCCR0B &= ~(1<FOC0B) )
#       define Timer8_force_output_compare()   ( Timer8_force_output_compare_a() )
#       define Timer8_clear_output_compare()   ( Timer8_clear_output_compare_a() )
        // ----------
#       define Timer8_set_mode_output_a(conf)  ( TCCR0A = (TCCR0A & (~TIMER8_COMP_MODE_MASK_A)) | (conf << COM0A0) )
#       define Timer8_set_mode_output_b(conf)  ( TCCR0A = (TCCR0A & (~TIMER8_COMP_MODE_MASK_B)) | (conf << COM0B0) )
#       define Timer8_set_mode_output(conf)    ( Timer8_set_mode_output_a(conf) )       // default : module A is used
#       define Timer8_get_mode_output_a()      ((TCCR0A & TIMER8_COMP_MODE_MASK_A) >> COM0A0 )
#       define Timer8_get_mode_output_b()      ((TCCR0A & TIMER8_COMP_MODE_MASK_B) >> COM0B0 )
#       define Timer8_get_mode_output()        ( Timer8_get_mode_output_a() )           // default : module A is used
        // ----------
#       define Timer8_set_waveform_mode(conf)  ( TCCR0A = (TCCR0A&(~TIMER8_WGM_01_MASK)) | ((conf&0x03) << WGM00), \
                                               ( TCCR0B = (TCCR0B&(~TIMER8_WGM_2_MASK)) | (((conf&0x04)>>2) << WGM02)) )
#       define Timer8_get_waveform_mode()      ( ((TCCR0A & TIMER8_WGM_01_MASK) >> WGM00) |  \
                                               ( ((TCCR0A & TIMER8_WGM_2_MASK) >> WGM02) << 0x2) )
        // ----------
#       define Timer8_set_clock(value)        ( TCCR0B = (TCCR0B & (~TIMER8_CLK_MASK)) | (value << CS00) )
#       define Timer8_get_clock()             ( (TCCR0B & TIMER8_CLK_MASK) >> CS00 )
        // ----------
#       define Timer8_overflow_it_enable()    ( TIMSK0 |=  (1<<TOIE0)  )
#       define Timer8_overflow_it_disable()   ( TIMSK0 &= ~(1<<TOIE0)  )
#       define Timer8_compare_a_it_enable()   ( TIMSK0 |=  (1<<OCIE0A) )
#       define Timer8_compare_a_it_disable()  ( TIMSK0 &= ~(1<<OCIE0A) )
#       define Timer8_compare_b_it_enable()   ( TIMSK0 |=  (1<<OCIE0B) )
#       define Timer8_compare_b_it_disable()  ( TIMSK0 &= ~(1<<OCIE0B) )
#       define Timer8_compare_it_enable()     ( Timer8_compare_a_it_enable()  )     // default : module A is used
#       define Timer8_compare_it_disable()    ( Timer8_compare_a_it_disable() )     // default : module A is used
#       define Timer8_get_overflow_it_mask()  ((TIMSK0  &  (1<<TOIE0) ) >> TOIE0  )
#       define Timer8_get_compare_a_it_mask() ((TIMSK0  &  (1<<OCIE0A)) >> OCIE0A )
#       define Timer8_get_compare_b_it_mask() ((TIMSK0  &  (1<<OCIE0B)) >> OCIE0B )
#       define Timer8_get_compare_it_mask()   ( Timer8_get_compare_a_it_mask() )    // default : module A is used
        // ----------
#       define Timer8_clear_overflow_it()     ( TIFR0 |=  (1<<TOV0)  )
#       define Timer8_clear_compare_a_it()    ( TIFR0 |=  (1<<OCF0A) )
#       define Timer8_clear_compare_b_it()    ( TIFR0 |=  (1<<OCF0B) )
#       define Timer8_clear_compare_it()      ( Timer8_clear_compare_a_it() )       // default : module A is used
#       define Timer8_get_overflow_it()       ((TIFR0  &  (1<<TOV0) ) >> TOV0  )
#       define Timer8_get_compare_a_it()      ((TIFR0  &  (1<<OCF0A)) >> OCF0A )
#       define Timer8_get_compare_b_it()      ((TIFR0  &  (1<<OCF0B)) >> OCF0B )
#       define Timer8_get_compare_it()        ( Timer8_get_compare_a_it() )         // default : module A is used



//_____ T I M E R   D E F I N I T I O N S ______________________________________
// Please refer to the device datasheet to get precisions about timer capabilities

    // ---------- Pre-definitions for "conf" field for Timer8_set(get)_mode_output_x(conf) macros
#define TIMER8_COMP_MODE_NORMAL    (0)
#define TIMER8_COMP_MODE_TOGGLE    (1)
#define TIMER8_COMP_MODE_CLEAR_OC  (2)
#define TIMER8_COMP_MODE_SET_OC    (3)
#define TIMER8_COMP_MODE_MASK_A    (3<<COM0A0)
#define TIMER8_COMP_MODE_MASK_B    (3<<COM0B0)
    // ---------- Pre-definitions for "conf" field for Timer8_set_waveform_mode(conf) macro
#define TIMER8_WGM_NORMAL          (0)
#define TIMER8_WGM_PWM_PC8         (1)
#define TIMER8_WGM_CTC_OCR         (2)
#define TIMER8_WGM_FAST_PWM8       (3)
#define TIMER8_WGM_PWM_PC_OCRA     (5)
#define TIMER8_WGM_PWM_FAST_OCRA   (7)
#define TIMER8_WGM_01_MASK         ((1<<WGM00) | (1<<WGM01))
#define TIMER8_WGM_2_MASK          (1<<WGM02)
    // ---------- Pre-definitions for "value" field for Timer8_set_clock(value) macro
#define TIMER8_CLK_MASK                   (7<<CS00)
#define TIMER8_NO_CLOCK                   (0)
#define TIMER8_CLKIO_BY_1                 (1)
#define TIMER8_CLKIO_BY_8                 (2)
#define TIMER8_CLKIO_BY_64                (3)
#define TIMER8_CLKIO_BY_256               (4)
#define TIMER8_CLKIO_BY_1024              (5)
#define TIMER8_EXT_CLOCK_FALLING_EDGE     (6)
#define TIMER8_EXT_CLOCK_RISING_EDGE      (7)




//_____ D E C L A R A T I O N S ________________________________________________

//------------------------------------------------------------------------------
//  @fn timer8_get_counter
//!
//! This function READ the 8-bit TIMER counter.
//!
//! @warning
//!
//! @param
//!
//! @return 8-bit counter value
//!
extern  U8 timer8_get_counter(void);

//______________________________________________________________________________

#endif  // _TIMER8_DRV_H_


