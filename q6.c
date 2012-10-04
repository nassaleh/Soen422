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
    usb_init();
    DDRF = 0xFF; //Setting in to HIGH
    PORTF = 0x00; //Input on port PF0
    //TODO
    ADMUX = 0x00; //Selecting Channel 0
    ADMUX = ADMUX | 0x40; //Selecting Voltage reference
    ADMUX = ADMUX | 0x20; //ADLAR = 1
    ADCSRA = 0x07; //Clock frequency
    ADCSRA = ADCSRA | 0x80; //Enabling ADC
    //TODO ADCSRAB
    

    while(1)
    {
        ADCSRA = ADCSRA | 0x40; //Start the conversion
        while ((ADCSRA & 0x10) == 0); //Waiting for conversion to be completed

        //status = (uint8_t)ADCH; //Reading ADCH
        unsigned char status;
        status = ADCH; //Reading ADCH
        ADCSRA = ADCSRA | 0x10; //Clear flag
    
        uint8_t n;

        while(!usb_configured());
        _delay_ms(100);
    
        DDRB = (1 << 7);
        TCCR0A = 0b10000011;
        TCCR0B = 0b10000011;
        OCR0A = 0;
        _delay_ms(100);
        
        unsigned char buf[100];
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