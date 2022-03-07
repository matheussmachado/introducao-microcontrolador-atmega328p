/*
 Apresente no display o status dos botões PC2 e PC3 (Pressionado ou Solto). O status do botão
PC2 deve ser apresentado na primeira linha do display, enquanto do botão PC3, na segunda
linha.
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

// Protótipo da interrupção
ISR(PCINT1_vect);

// VARIÁVEIS GLOBAIS DE ESTADO DOS BOTÕES
volatile char solto[] = "SOLTO      ";
volatile char pressionado[] = "PRESSIONADO";


int main(void) {
  // PUSH BUTTONS
  DDRC = 0x00;
  PORTC = 0b00001100; // hab. pull up dos pinos PC2 e PC3
  
  // DISPLAY LCD
  DDRD = 0xFF;
  PORTD = 0x00; // inicializando display apagado;
  char msg2[] = "PC2: ";
  char msg3[] = "PC3: ";    
  inic_LCD_4bits();
  escreve_LCD(msg2);
  escreve_LCD(solto);
  cmd_LCD(0xC0, 0);
  escreve_LCD(msg3);
  escreve_LCD(solto);    
  
  // TRANSISTORES
  DDRB = 0b00101000;
  
  // INTERRUPÇÕES
  PCICR = 0b00000010; // hab. a interrupção do PORTC
  PCMSK1 = 0b00001100; // hab. a interrupção dos pinos PC2 e PC3
  sei(); 
  
  while (1) {
    
  }
}

ISR(PCINT1_vect) {
  cmd_LCD(0x85, 0);
  if (!tst_bit(PINC, PC2)) escreve_LCD(pressionado);
  else escreve_LCD(solto);
  cmd_LCD(0xC5, 0);
  if (!tst_bit(PINC, PC3)) escreve_LCD(pressionado);
  else escreve_LCD(solto);
}
