#include <avr/io.h>

int main(void) {
  DDRD = 0b11111111; //PORTD inteiro como sa�da
  //Habilita a refer�ncia de tens�o interna do ADC e ativa o canal 0
  //ADMUX = (1<<REFS0); //Outra maneira de manipular o registrador
  ADMUX = 0b01000000;
  //Habilita o ADC e configura o prescaler para 128
  //ADCSRA = (1<<ADEN) | (1<<ADPS2) | (1<<ADPS1) | (1<<ADPS0);
  ADCSRA |= 0b10000111;
  while (1) {
    //ADCSRA |= (1<<ADSC);
    ADCSRA |= 0b01000000; //Inicia a convers�o
    //Aguarda o t�rmino da convers�o
    //while ( (ADCSRA & (1<<ADSC)));
    while ((ADCSRA & 0b01000000));
    //Descarta os dois bits menos significativos e apresenta o resultado no PORTD
    PORTD = (ADC >> 2);
  }
}
