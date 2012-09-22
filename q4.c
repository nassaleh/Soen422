#define F_CPU 16000000
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdio.h>

void main()
{
    DDRB = (1 << 7); //turn on port PB7 and set it to HIGH
    TCCR0A = 0b10000011; //set up timer0 on 0C0A on PB7
    TCCR0B = 0b10000011; //not connected port
    OCR0A = 0; //setting duty cycle to 0% on 0C0A
    Serial.begin(9600);
    while(1)
    {
        _delay_ms(500); 
        OCR0A += 64;
        Serial.println(0CR0A);
        _delay_ms(500);
    }

}
