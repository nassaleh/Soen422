#define F_CPU 16000000
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

void main()
{
    DDRB = (1 << 7); //turn on port PB7 and set it to HIGH
    TCCR0A = 0b10000011; //set up timer0 on 0C0A on PB7
    TCCR0B = 0b10000011; //not connected port
    OCR0A = 255;
    TIMSK0 = 0;
    while(1)
    {
        _delay_ms(500);
        cli(); 
        OCR0A = 0;
        sei();
        _delay_ms(500);
        cli();
        OCR0A = 255;
        sei();
    }

}
