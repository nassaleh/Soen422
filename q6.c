#define F_CPU 16000000
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdint.h>
#include <stdio.h>
#include "usb_serial.h"
#include <avr/pgmspace.h>

void send_str(const char*s);

int main(void)
{
    DDRF = (1 << 7);
    ADCSRA = (1 << 7) | (1 << 6) | (1 << 5) | (1 << 2) | (1 << 1);
    ADCSRA &=~(1<<0); //Set last bit to 0
    // Setting Admux Register
    ADMUX = (1<<5);
    ADMUX &=~ (1<<1) | (1<<0);// Sets MUX to use ADC0
    uint8_t status;
    status = ADCH;
    
    usb_init();
    while(!usb_configured());
    _delay_ms(1000);
    
    char buf[100];
    uint8_t n;
    
    DDRB = (1 << 7);
    TCCR0A = 0b10000011;
    TCCR0B = 0b10000011;
    OCR0A = 0;
    
    while(1)
     {
         _delay_ms(500);
         sprintf(buf,"%d",status);

         while(!(usb_serial_get_control() & USB_SERIAL_DTR)); /* wait */
               usb_serial_flush_input();

         send_str(strcat(buf, "\n"));
    }
    return 0;
}

void send_str(const char *s)
{
    char c;
    while (1) {
        c = *(s++);
        if (!c) break;
            usb_serial_putchar(c);
    }
}
