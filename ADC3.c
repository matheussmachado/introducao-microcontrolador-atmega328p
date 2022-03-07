/*
 Desenvolva um bargraph nos LEDs do PORTD. Os LEDs devem acender e apagar a cada 625mV;
 */


#include <avr/io.h>
#include <avr/interrupt.h>

ISR(ADC_vect) {
  float tensao = 0;
  int barras, valor;
  barras = valor = 0;
  tensao = (ADC>>2)*5/255.0;
  barras = tensao/0.625;  
  for (int i = 0; i < barras; i++) {
    valor |= (1 << i);
  }
  PORTD = valor;
}

int main(void) {
  // LEDS
  DDRD = 0xFF;
  
  // CONVERSOR AD
  ADMUX = (1 << REFS0);
  ADCSRA = (1 << ADEN) | (1 << ADIE) | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);
  sei();
  
  while (1) {
    ADCSRA |= (1 << ADSC);
  }
}
