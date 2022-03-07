#define F_CPU 16000000UL //frequ�ncia de trabalho

#include <avr/io.h> //defini��es do componente especificado
#include <avr/interrupt.h> //define algumas macros para as interrup��es
#include <util/delay.h> //biblioteca para o uso das rotinas de delay

//Prot�tipo da fun��o de interrup��o, obrigat�rio para sua utiliza��o
ISR(PCINT0_vect);
ISR(PCINT1_vect);

//Declara vari�vel global ?contador?
volatile int contador = 0;
volatile char pause = 0;

int main() {
  //Vetor para decodifica��o do display de 7 segmentos
  unsigned char vetor_disp[16]={0xE7,0x84,0xD3,0xD6,0xB4,0x76,0x77,0xC4,0xF7,
  0xF6,0xF5,0x37,0x63,0x97,0x73,0x71};
  
  DDRB = 0b00000011; //PB1 como sa�da (transistor do display)
  PORTB = 0b0000001; //Liga o display de 7 segmentos
  DDRC = 0b00000000; //PORTC como entrada
  PORTC = 0b00001100; //habilita pull-ups apenas nos bot�es
  DDRD = 0b11111111; //PORTD definido como sa�da
  PORTD = 0b00000000; //apaga todos os leds
  
  PCICR = 0b00000011; //hab. interrup��o por mudan�a de sinal no PORTB e PORTC
  PCMSK0 = 0b00000100; // hab. o pino PCINT2 para gerar interrup��o
  PCMSK1 = 0b00001100; //hab. os pinos PCINT10 e 11 para gerar interrup��o
  sei(); //habilita a chave geral das interrup��es
  
  while (1) {
    //Envia o valor decodificado para o display de 7 segmentos      
    _delay_ms(250);
    PORTD = vetor_disp[contador];
    _delay_ms(500);
    if (!pause) contador++;
    if (contador == 16) contador = 0;
    _delay_ms(250);
  }
}

//-----------------------------------------------------------------------------
ISR(PCINT1_vect) {
  //Testa qual o pino que foi acionado para START/PAUSE e RESET   
  if (!(PINC&(1<<2))) pause = !pause;
  else if (!(PINC&(1<<3))) {
    if (pause) contador = 0;
  }   
}
//=============================================================================