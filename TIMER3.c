/*
Apresente no display LCD um relógio simples no formato HH:MM:SS. O incremento 
dos segundos deve ser feito a partir da interrupção do Timer 1;
Dica: Pode ser utilizada a função sprintf(buffer, ?%d:%d:%d?, hora, minuto, segundo).
 */

#define F_CPU 16000000
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h> //pois é dependencia para a lib LCD
#include <stdio.h>
#include "LCD.h"

volatile unsigned int hora = 0;
volatile unsigned int minuto = 0;
volatile unsigned int segundo = 0;
volatile char buffer[9] = "        ";

ISR(TIMER1_OVF_vect) {
  TCNT1 = 49911;
  sprintf(buffer, "%.2d:%.2d:%.2d", hora, minuto, segundo);
  cmd_LCD(0x80, 0);
  escreve_LCD(buffer);
  segundo++;
  if (segundo == 60) {
    segundo = 0;
    minuto++;
    if (minuto == 60) {
      minuto = 0;
      hora++;
      if (hora == 60) {
        hora = 0;
      }
    }    
  }
  
}

int main(void) {
  
  
  // DISPLAY LCD
  DDRD = 0xFF;
  PORTD = 0x00;
  
  // TIMER 1
  TCCR1B = 0b00000101; // prescaler 1024
  TIMSK1 = 0b00000001;
  TCNT1 = 49911; // contagem para overflow em 1 seg.
  sei();
  
  // LCD    
  inic_LCD_4bits();
  
  segundo = 55;
  minuto = 59;
  while (1) {
    
  }
}
