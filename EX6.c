/*
Configure a interrupção das duas chaves ligadas na placa (PB2 e PB4). Cada uma delas
deve inverter o estado de dois LEDs;
 */


#include <avr/io.h>
#include <avr/interrupt.h>

ISR(PCINT0_vect);

int main(void) {  
  DDRD = 0xFF;  // LEDS  
  DDRB = 0x00;  // CHAVES    
  
  // INTERRUPÇÕES
  PCICR = 0b00000001; // PORTB e PORTD
  PCMSK0 = 0b00010100; // PB2 e PB4
  sei();
  
  while (1) {
    // NADA AQUI
  }
}

//==============================================================================

ISR(PCINT0_vect) {
  // CHAVE PB2
  if (!(PINB & (1 << 2))) PORTD |= 0b00000011;
  else PORTD &= 0b11111100;
  
  // CHAVE PB4
  if (!(PINB & (1 << 4))) PORTD |= 0b11000000;
  else PORTD &= 0b00111111;
}
