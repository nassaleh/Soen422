#include <avr/io.h>
#include <util/delay.h>

void main()
{
	PORTD = (1 << 1) | (1 << 5) | (1 << 6);
 //   TCCR0A;
 //   TCCR0B;
 //   OCR0A;

	while(1)
	{
        DDRD |= (1 << 5);
        DDRD &=~ (1 << 6);

        if(PIND & (1<<4))
        {
            DDRD &=~ (1 << 3);
        }
        else
        {
            DDRD |= (1<<3);
        }
    }
}
