/*
utilizar Timer 1para que ele gere uma interrupção e inverta o estado de um LED a cada 2 segundos;
 */

// tempo = 2 seg -> inicio_cont = 65536 - (2 * 16*10?)/prescaler
// para prescaler de 1024 -> inicio_cont = 34286

#define cpl_bit(y, bit)   (y ^= (1 << bit))
#include <avr/io.h>
#include <avr/interrupt.h>

ISR(TIMER1_OVF_vect) {
  TCNT1 = 34286;
  cpl_bit(PORTD, PD2);  
}

int main(void) {
  // LEDS
  DDRD = 0xFF;
  PORTD = 0x00;
  
  //TIMER
  TCCR1B = 0b00000101; // prescaler de 1024
  TIMSK1 = 0b00000001; // acionando o bit de interrupção por overflow
  TCNT1 = 34286; // contagem inicial para gerar overflow em 2 seg
  sei();
  
  while (1) {
  }
}
