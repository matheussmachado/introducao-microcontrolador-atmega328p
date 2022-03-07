#define F_CPU 16000000

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

ISR(PCINT1_vect);
ISR(PCINT0_vect);


int main(void) {   
  // LEDS
  DDRD = 0xFF;
  
  // PUSH BUTTONS
  DDRC = 0x00;
  PORTC = 0b00001100;
  
  // CHAVES
  DDRB = 0x00;
  
  // INTERRUPÇÕES
  PCICR = 0b00000011; // PCINT0 e PCINT1 -> interrupções PORTB e PORTC
  PCMSK0 = 0b00010100; // PB2 e PB4
  PCMSK1 = 0b00001100; // PC2 e PC3
  sei();
  
  while (1) {
    PORTD ^= (1 << 3);
    _delay_ms(200);
  }
}

ISR(PCINT1_vect) {
  if (!(PINC & (1 << 2))) PORTD |= 0b00100000;
  else if (!(PINC & (1 << 3))) PORTD &= ~(1 << 5);
}

ISR(PCINT0_vect) {
  if (!(PINB & (1 << 2))) PORTD |= 0b10000000;
  else if (!(PINB & (1 << 4))) PORTD &= ~(1 << 7);
}