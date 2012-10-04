#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>

#define F_CPU 160000000
#define BOARD_ON (PORTD |= (1<<6))
#define BOARD_OFF (PORTD &= ~(1<<6))
#define BOARD_CONFIG (DDRD |= (1<<6))
#define CPU_PRESCALE(n) (CLKPR = 0x80, CLKPR = (n))
#define LED_ON (PORTB |= (1<<7))
#define LED_OFF (PORTB &= ~(1<<7))
#define LED_CONFIG (DDRB |= (1<<7))

ISR(TIMER1_COMPA_vect) {
  static uint8_t ledon;
  if (ledon) {
    ledon = 0;
    LED_OFF;
    BOARD_ON;
  } else {
    ledon = 1;
    LED_ON;
    BOARD_OFF;
  }
}

int main(void) {
  BOARD_CONFIG;
  BOARD_OFF;
  LED_CONFIG;
  LED_ON;
  CPU_PRESCALE(0);
  cli();
  TIMSK1 = _BV(OCIE1A); //COMPARE A match interrupts are enabled.
  TCCR1B |= (_BV(CS12) | _BV(CS10)) | _BV(WGM12); //Prescaler divides the clock rate by 1024
  //Also set the WGM12 bit to clear timer on compare with the OCR1A register
  OCR1A = 15625;
  sei();
  set_sleep_mode(SLEEP_MODE_IDLE);
  while (1) {
    // Go to sleep. When the interrupt happens the sleep returns
    // but the while loops just puts us to sleep again.
    sleep_mode();
  }
}