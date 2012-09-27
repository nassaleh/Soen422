#define F_CPU 16000000
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdint.h>
#include <stdio.h>
#include "usb_serial.h"
#include <avr/pgmspace.h>

void send_str(const char *s);


int main(void)
{
    // initialize the USB, and then wait for the host
    // to set configuration.  If the Teensy is powered
    // without a PC connected to the USB port, this 
    // will wait forever.
    usb_init();
    while (!usb_configured()) /* wait */ ;
    _delay_ms(1000);                       
   
   
    char buf[100];
    uint8_t n;
    
    DDRB = (1 << 7); //turn on port PB7 and set it to HIGH
    TCCR0A = 0b10000011; //set up timer0 on 0C0A on PB7
    TCCR0B = 0b10000011; //not connected port
    OCR0A = 0; //setting duty cycle to 0% on 0C0A
   
    while(1)
    {
        _delay_ms(500); 
        OCR0A += 64;
        _delay_ms(500);
        sprintf(buf,"%d",OCR0A);

        
        while (!(usb_serial_get_control() & USB_SERIAL_DTR)); /* wait */ 
        usb_serial_flush_input();

        //Prints OCR0A aka brightness
        //send_str(OCR0A);
        send_str(strcat(buf, "\n"));
    }

}

//TODO; Changee method. does not actually send
void send_str(const char *s)
{
        char c;
        while (1) {
            c = *(s++);
            if (!c) break;
            usb_serial_putchar(c);
        }
}

