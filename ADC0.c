#include <avr/io.h>

int main(void) {
  DDRD = 0b11111111; //PORTD inteiro como saída
  //Habilita a referência de tensão interna do ADC e ativa o canal 0
  //ADMUX = (1<<REFS0); //Outra maneira de manipular o registrador
  ADMUX = 0b01000000;
  //Habilita o ADC e configura o prescaler para 128
  //ADCSRA = (1<<ADEN) | (1<<ADPS2) | (1<<ADPS1) | (1<<ADPS0);
  ADCSRA |= 0b10000111;
  while (1) {
    //ADCSRA |= (1<<ADSC);
    ADCSRA |= 0b01000000; //Inicia a conversão
    //Aguarda o término da conversão
    //while ( (ADCSRA & (1<<ADSC)));
    while ((ADCSRA & 0b01000000));
    //Descarta os dois bits menos significativos e apresenta o resultado no PORTD
    PORTD = (ADC >> 2);
  }
}
