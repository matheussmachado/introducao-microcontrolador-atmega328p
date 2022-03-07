/*
Utilizando as macros de manipulação de bits, desenvolva um contador de 0 a 100 com os
botões PC2 e PC3 e apresente o valor da contagem na segunda linha do display LCD;
O incremento e decremento da variável deve realizada dentro das interrupções externas.
 */

#define F_CPU 16000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdio.h>
#include "LCD.h"

//Definições de macros para o trabalho com bits
#define set_bit(y,bit) (y|=(1<<bit)) //coloca em 1 o bit x da variável Y
#define clr_bit(y,bit) (y&=~(1<<bit)) //coloca em 0 o bit x da variável Y
#define cpl_bit(y,bit) (y^=(1<<bit)) //troca o estado lógico do bit x da variável Y
#define tst_bit(y,bit) (y&(1<<bit)) //retorna 0 ou 1 conforme leitura do bit

// VARIÁVEIS GLOBAIS PARA MANIPULAÇÃO E EXIBIÇÃO DA CONTAGEM
volatile int contador = 0;
volatile char buffer[4] = "   ";

// PROTÓTIPO DA INTERRUPÇÃO
ISR(PCINT1_vect);

int main(void) {    
    // PUSH BUTTONS
  DDRC = 0x00;
  PORTC = 0b00001100; //hab. pull up dos pinos PC2 e PC3  
  
  // INTERRUPÇÕES
  PCICR = 0b00000010; // hab. interrupção do PORTC
  PCMSK1 = 0b00001100; // hab. interrupção dos pinos PC2 e PC3
  sei();
  
  // TRANSISTORES
  DDRB = 0b00101000;
  
  // DISPLAY LCD
  DDRD = 0xFF;
  PORTD = 0x00;
  char contagem[] = "CONTAGEM:";
  contador = 0;
  inic_LCD_4bits();  
  
  escreve_LCD(contagem);  
  
  while (1) {
    sprintf(buffer, "%3d", contador);
    cmd_LCD(0xC0, 0);
    escreve_LCD(buffer);
  }
}

ISR(PCINT1_vect) {  
  if (!tst_bit(PINC, PC2) && contador < 100) contador++;
  else if (!tst_bit(PINC, PC3) && contador > 0) contador--;    
}