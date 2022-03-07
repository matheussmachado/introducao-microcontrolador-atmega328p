/*
 * fazer com que apareça no display LCD o valor binário no canal 1
 */

#define F_CPU 16000000
#include <avr/io.h>
#include <stdio.h>
#include <util/delay.h>
#include "LCD.h"


int main(void) {
  // CONVERSOR AD
  ADMUX = 0b01000001;
  ADCSRA = 0b10000111;
  
  // LCD
  DDRD = 0xFF;
  inic_LCD_4bits();
  char msg[] = "CANAL 1 = ";
  char buffer[4] = "   ";
  cmd_LCD(0xC0, 0);
  escreve_LCD(msg);
  
  while (1) {
    ADCSRA |= (1 << ADSC);
    while (ADCSRA & (1 << ADSC)) {      
      sprintf(buffer, "%.4d", ADC);
      cmd_LCD(0xC9, 0);
      escreve_LCD(buffer);
    }
  }
}
