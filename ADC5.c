/*
Realize a comparação entre o canal 0 e 1 do ADC e:
a) Acenda o LED 0 caso CH0 > CH1;
b) Acenda o LED 1 caso CH1 > CH0;
c) Acenda o LED 2 caso CH1 = CH0.
 */
#define F_CPU 16000000
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

volatile char canal = 0;
volatile int canal_0 = 0; 
volatile int canal_1 = 0;


ISR(ADC_vect) {   
  if (!canal) { // como ADMUX inicia no canal 0, então é conveniente iniciar a 
                // comparação no caso em que a variável canal é igual a zero
    canal_0 = ADC;
    ADMUX = (1 << REFS0) | (1 << MUX0);
  }
  else {
    canal_1 = ADC;
    ADMUX = (1 << REFS0);
  }
  if (canal_0 > canal_1) {
    PORTD = 0b00000001;
  }
  else if (canal_0 < canal_1) {
    PORTD = 0b00000010;
  }
  else if (canal_0 == canal_1) {
    PORTD = 0b00000100; // no simulide a precisão precisa de ser de 2 casas decimais para serem iguais    
  }
  canal = !canal;
}

int main(void) {
  // LEDS
  DDRD = 0xFF;
  
  // CONVERSOR AD
  ADMUX = (1 << REFS0); //iniciar com o canal 0
  ADCSRA = 0b10001111;
  sei();
  while (1) {
    ADCSRA |= (1 << ADSC);
  }
}
