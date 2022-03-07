#define F_CPU 16000000UL //frequência de trabalho

#include <avr/io.h> //definições do componente especificado
#include <avr/interrupt.h> //define algumas macros para as interrupções
#include <util/delay.h> //biblioteca para o uso das rotinas de delay

//Protótipo da função de interrupção, obrigatório para sua utilização
ISR(PCINT1_vect);

//Declara variável global ?contador?
volatile int contador=0;

int main() {
  //Vetor para decodificação do display de 7 segmentos
  unsigned char vetor_disp[16]={0xE7,0x84,0xD3,0xD6,0xB4,0x76,0x77,0xC4,0xF7,
  0xF6,0xF5,0x37,0x63,0x97,0x73,0x71};
  
  DDRB = 0b00000001; //PB1 como saída (transistor do display)
  PORTB = 0b00000001; //Liga o display de 7 segmentos
  DDRC = 0b00000000; //PORTC como entrada
  PORTC = 0b00001100; //habilita pull-ups apenas nos botões
  DDRD = 0b11111111; //PORTD definido como saída
  PORTD = 0b00000000; //apaga todos os leds
  
  PCICR = 0b00000010; //hab. interrupção por mudança de sinal no PORTC
  PCMSK1 = 0b00001100; //hab. os pinos PCINT10 e 11 para gerar interrupção
  sei(); //habilita a chave geral das interrupções
  
  while (1) {
    //Envia o valor decodificado para o display de 7 segmentos
    PORTD = vetor_disp[contador];
  }
}

//-----------------------------------------------------------------------------
ISR(PCINT1_vect) {
  //Testa qual o pino que foi acionado
  if (!(PINC&(1<<2))){
    contador++;
    if(contador == 16)
    contador = 0;
  }
  else if (!(PINC&(1<<3))){
    contador--;
    if(contador < 0)
    contador = 15;
  }
  _delay_ms(10);
}
//=============================================================================