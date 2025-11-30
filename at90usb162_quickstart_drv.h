

// ***** WATCHDOG *****
// see "wdt_drv.h", updated and placed into at90usb162/lib_mcu directory

// ***** CLOCK *****
// see "power_drv.h" and "power_drv.c", placed into at90usb162/lib_mcu directory

// ***** USB *****
// -> see "usb_drv.h" and "pll_drv.h", placed into at90usb162/lib_mcu directory

// ***** USART *****
#define   Usart_spi_hard_init()           (PORTD |= 0x2C, DDRD |= 0x28, DDRD &= ~0x04)
#define   Usart_hard_init_without_ctrl()  (PORTD |= 0x0C, DDRD |= 0x08, DDRD &= ~0x04)
#define   Usart_hard_init_with_ctrl()     (PORTD |= 0xCC, DDRD |= 0x48, DDRD &= ~0x84)


#define   Usart_spi_soft_init()           (UBRR1  = 0, \
                                          UCSR1C = (1<<7)|(1<<6)|(1<<1)|(1<<0), \
                                          UCSR1B = (1<<3)|(1<<4), \
                                          UBRR1 = 4)  // baudrate = 800kbits/s
#define   Usart_soft_init_with_ctrl()     (UBRR1 = 0, \
                                          UCSR1C = (1<<UCSZ11) | (1<<UCSZ10), \
                                          UCSR1D = (1<<CTSEN) | (1<<RTSEN), \
                                          UCSR1B = (1<<RXEN1) | (1<<TXEN1), \
                                          UBRR1 = 9)  // baudrate = 50kbits/s
//                                          UBRR1 = 4)  // baudrate = 100kbits/s

#define   Usart_soft_init_without_ctrl()  (UBRR1 = 0, \
                                          UCSR1C = (1<<UCSZ11) | (1<<UCSZ10), \
                                          UCSR1D &= ~((1<<CTSEN) | (1<<RTSEN)), \
                                          UCSR1B = (1<<RXEN1) | (1<<TXEN1), \
                                          UBRR1 = 4)  // baudrate = 100kbits/s

#define   Usart_write_byte(dt)            (UDR1 = dt)
#define   Usart_read_byte()               (UDR1)
#define   Is_usart_byte_sent()            (((UCSR1A&(1<<TXC1)) != 0) ? TRUE : FALSE)
#define   Usart_clear_flag_send()         (UCSR1A |= (1<<TXC1))
#define   Is_usart_byte_received()        (((UCSR1A&(1<<RXC1)) != 0) ? TRUE : FALSE)
#define   Usart_clear_flag_receive()      (UCSR1A |= (1<<RXC1))
#define   Is_usart_data_reg_empty()       (((UCSR1A&(1<<UDRE1)) != 0) ? TRUE : FALSE)

// ***** TIMERS *****
// 1. User can use Timer1 to generate DELAY (multiple of 1ms or 1µs @ Fosc=8MHz)
// Max delay : 2100 ms/µs
#define   Delay_config_ms(ms)     (Timer16_set_clock(TIMER16_CLKIO_BY_256), \
                                  Timer16_set_mode_output_a(TIMER16_COMP_MODE_NORMAL), \
                                  Timer16_set_waveform_mode(TIMER16_WGM_CTC_OCR), \
                                  Timer16_set_compare_a((U16)(31)*(U16)(ms)))
#define   Delay_config_us(us)     (Timer16_set_clock(TIMER16_CLKIO_BY_8), \
                                  Timer16_set_mode_output_a(TIMER16_COMP_MODE_NORMAL), \
                                  Timer16_set_waveform_mode(TIMER16_WGM_CTC_OCR), \
                                  Timer16_set_compare_a((U16)(us)))

#define   Delay_reset()           (Timer16_set_counter(0x0000), Timer16_clear_compare_a_it())
#define   Is_delay_end()          (Timer16_get_compare_a_it())
#define   Is_not_delay_end()      (!(Timer16_get_compare_a_it()))



// Macro defined to simplify pushbutton debouncing
#define   Bp_delay_debounce()     { Delay_config_ms(20); Delay_reset(); while (Is_not_delay_end());}















