// ============================================
// = AT90USB162 REFERENCE DESIGN
// = Wired mouse with philips PNL2021 sensor
// ********************************************
// = Driver file for basic peripherals
// =============================================


// USB
// Used if VBUS_SENSING_IO is defined as "ENABLED"
#define   VBUS_SENSE_PORT     PORTC   // PORTx
#define   VBUS_SENSE_PIN      PINC    // PINx
#define   VBUS_SENSE_DDR      DDRC    // DDRx
#define   VBUS_SENSE_IO       4       // 0...7


// LEDs
// ****
#define   Leds_init()          (DDRD |= 0x33, PORTD &= ~0x33)

#define   Led0_on()            (PORTD |= 0x01)                  // PD0
#define   Led0_off()           (PORTD &= ~0x01)
#define   Led0_toggle()        (PORTD ^= 0x01)
#define   Led1_on()            (PORTD |= 0x02)                  // PD1
#define   Led1_off()           (PORTD &= ~0x02)
#define   Led1_toggle()        (PORTD ^= 0x02)
#define   Led2_on()            (PORTD |= 0x10)                  // PD4
#define   Led2_off()           (PORTD &= ~0x10)
#define   Led2_toggle()        (PORTD ^= 0x10)
#define   Led3_on()            (PORTD |= 0x20)                  // PD5
#define   Led3_off()           (PORTD &= ~0x20)
#define   Led3_toggle()        (PORTD ^= 0x20)

#define   Leds_set_val(c)      (Leds_off(),PORTD |= (c&0x03)+((c&0x0C)<<2))
#define   Leds_get_val()       ((PORTD&0x30)>>2+(PORTD&0x03))
#define   Leds_off()           (PORTD &= ~0x33)

// PUSHBUTTONS
// ***********

#define   Joy_init()                (DDRB &= ~0xF1, PORTB |= 0xF1)
#define   Push_button_init()        Joy_init()

#define   Is_joy_left()             (((PINB&0x10) == 0) ? TRUE : FALSE)    // PB4
#define   Is_joy_not_left()         (((PINB&0x10) == 0) ? FALSE : TRUE)
#define   Is_button_left()          Is_joy_left()
#define   Is_button_not_left()      Is_joy_not_left()

#define   Is_joy_middle()           (((PINB&0x01) == 0) ? TRUE : FALSE)    // PB0
#define   Is_joy_not_middle()       (((PINB&0x01) == 0) ? FALSE : TRUE)
#define   Is_joy_select()           Is_joy_middle()
#define   Is_joy_not_select()       Is_joy_not_middle()
#define   Is_button_middle()        Is_joy_middle()
#define   Is_button_not_middle()    Is_joy_not_middle()

#define   Is_joy_right()            (((PINB&0x40) == 0) ? TRUE : FALSE)    // PB6
#define   Is_joy_not_right()        (((PINB&0x40) == 0) ? FALSE : TRUE)
#define   Is_button_right()         Is_joy_right()
#define   Is_button_not_right()     Is_joy_not_right()

#define   Is_joy_down()             (((PINB&0x80) == 0) ? TRUE : FALSE)    // PB7
#define   Is_joy_not_down()         (((PINB&0x80) == 0) ? FALSE : TRUE)
#define   Is_button_down()          Is_joy_down()
#define   Is_button_not_down()      Is_joy_not_down()

#define   Is_joy_up()               (((PINB&0x20) == 0) ? TRUE : FALSE)    // PB5
#define   Is_joy_not_up()           (((PINB&0x20) == 0) ? FALSE : TRUE)
#define   Is_button_up()            Is_joy_up()
#define   Is_button_not_up()        Is_joy_not_up()


#define   Hwb_button_init()         (DDRD &= ~0x80)
#define   Is_hwb()                  (((PIND&0x80) == 0) ? TRUE : FALSE)   // PD7

//! @defgroup Philips Wired mouse ATMEL Hardware data flash configuration
      //! Macros to init the environnement for DF on Philips Wired mouse board
      //! @{

#define DF_8_MB   // Type of DF implemented.


#define DF_SELECT_MEM        0
#define DF_UNSELECT_MEM      1
#define DF_NB_MEM            1

#ifndef AVRGCC
   // PORTB_Bit0=1,DDRB_Bit0=0: SPI Slave Select Input. The data direction of the
   //    NOT(SS) is INPUT and the pull-up resistor is activated.
   // DDRB_Bit1=1: the SCK signal direction is OUTPUT.
   // DDRB_Bit2=1: the SI signal direction is OUTPUT.
   // DDRB_Bit3=0: the SO signal direction is INPUT.
   // PORTB_Bit4=1,DDRB_Bit4=1: CS driven high
   //    and both CS are OUTPUT.

   #define Init_df_stk526()   (DDRC_Bit2=1,PORTC_Bit2=1,DDRB_Bit0=1)
   #define DF_CS_PIN          PORTC_Bit2
   #define DF_CS0             DF_CS_PIN
   #define DF_CS1             DF_CS0
   #define DF_CS2             DF_CS0
   #define DF_CS3             DF_CS0
   #define Df_select_df(i, val) (DF_CS##i = val)
   #define Df_desel_all()       (DF_CS0=DF_UNSELECT_MEM)     // set CS# dataflash memories
#else //! for AVRGCC
   #define Init_df_stk526()   (DDRC |=(1<<DF_CS0), PORTC|=(1<<DF_CS0), PORTB |= (1<<0))
   #define DF_CS_PORT         PORTC
   #define DF_CS0             2
   #define DF_CS1             DF_CS0
   #define DF_CS2             DF_CS0
   #define DF_CS3             DF_CS0
   #define Df_desel_all()     (DF_CS_PORT|=(1<<DF_CS0)) // set CS# dataflash memories (unselect).
#endif
#define df_init_spi()      Init_df_stk526()
      //! @}


