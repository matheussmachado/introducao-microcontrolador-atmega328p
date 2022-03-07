#define F_CPU 16000000
#define cpl_bit(y, bit)   (y ^= (1 << bit))

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

volatile unsigned int contador = 0;

ISR(TIMER0_OVF_vect) {
  contador++;
  if (contador == 10) { // irá executar a cada 160ms, aproximadamente
    cpl_bit(PORTD, PD2); // inverte o estado do LED a cada overflow do timer
    contador = 0;
  }
}

ISR(TIMER1_OVF_vect) {
  TCNT1 = 49911; // recarregando o timer para preservar o tempo de 1 seg para o overflow
  cpl_bit(PORTD, PD6);
}

int main(void) {
  
  //LEDS
  DDRD = 0xFF;
  PORTD = 0x00;
  
  //TIMER 0
  TCCR0B = 0b00000101;  // acionando prescaler 1/1024
  TIMSK0 = 0b00000001; // habilitando a interrupção do overflow do timer
  
  //TIMER 1
  TCCR1B = 0b00000101;  // acionando prescaler 1/1024
  TIMSK1 = 0b00000001; // habilitando a interrupção do overflow do timer
  TCNT1 = 49911;
  sei();
  
  while (1) {
    cpl_bit(PORTD, PD4);
    _delay_ms(500);
  }
}
