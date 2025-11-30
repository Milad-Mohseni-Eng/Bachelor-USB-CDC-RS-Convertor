//! @file config.h,v
//!
//! Copyright (c) 2006 Atmel.
//!
//! Please read file license.txt for copyright notice.
//!
//! This file contains the system configuration definition
//!
//! @version 1.1 at90usb162-cdc-1_0_1 $Id: config.h,v 1.1 2006/09/08 10:55:12 rletendu Exp $
//!
//! @todo
//! @bug

#ifndef _CONFIG_H_
#define _CONFIG_H_

//! @defgroup global_config Application configuration
//! @{

//_____ I N C L U D E S ____________________________________________________


#ifdef AVRGCC
   #define __AVR_AT90USB162__
#endif

#include "compiler.h" //!< Compiler definitions


#ifdef AVRGCC
   #include <avr/io.h>
#else
   #include "mcu.h" //!< Register declaration
#endif
#include "conf_scheduler.h" //!< Scheduler tasks declaration

#define  STK525   0
#define  USBKEY   1
#define  SPIDER     2
#define  WRD_PHLPS  3
#define  STK526     4
#define  WRD_LGTEC  5

//! Enable or not the ADC usage
#undef  USE_ADC
//! To include proper target hardware definitions, select
//! target board (USBKEY or STK525)
#define TARGET_BOARD STK526

#if (TARGET_BOARD==USBKEY)
   //! @warning for #define USBKEY_HAS_321_DF, only first prototypes versions have AT45DB321C memories
   //! should be undefined for std series
   #define USBKEY_HAS_321_DF
   #include "usb_key.h"
#elif (TARGET_BOARD==STK525)
   #include "stk_525.h"
#elif (TARGET_BOARD==SPIDER)
   #include "spider_drv.h"
#elif (TARGET_BOARD==WRD_PHLPS)
   #include "mouse_wired_philips_drv.h"
#elif (TARGET_BOARD==STK526)
   #include "stk_526.h"
#elif (TARGET_BOARD==WRD_LGTEC)
   #include "mouse_wired_logitech_drv.h"
#else
   #error TARGET_BOARD must be defined somewhere
#endif


#define BYPASS_USB_AUTOBAUD
//! CPU core frequency in kHz
#define FOSC 8000


// -------- END Generic Configuration -------------------------------------

// UART Sample configuration, if we have one ... __________________________
#define BAUDRATE        38400
#define USE_UART2
#define UART_U2

//#define uart_putchar putchar
#ifndef AVRGCC
   #define uart_usb_putchar putchar
#endif
#define r_uart_ptchar int
#define p_uart_ptchar int

#define NB_MS_BEFORE_FLUSH			50
#define REPEAT_KEY_PRESSED       100

//! @}

#endif // _CONFIG_H_

