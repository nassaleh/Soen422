#include <avr/io.h>

void main()
{
	PORTD = (1 << 3) | (1 << 5) | (1 << 6);
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
