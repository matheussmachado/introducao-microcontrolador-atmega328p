/*
Supondo um sensor de temperatura analógico que fornece uma tensão de 0 a 5V e possua uma
faixa de 0 a 100°C, apresente no display LCD o valor do canal 0 convertido em temperatura com
duas casas decimais;
 */

#define F_CPU 16000000
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdio.h>
#include "LCD.h"

volatile char buffer[5] = "   ";
ISR(ADC_vect) {
  
  char celsius[] = " C";
  sprintf(buffer, "%.2f", (float)ADC*100/1023);
  cmd_LCD(0x87, 0);
  escreve_LCD(buffer);
  cmd_LCD(0x8D, 0);
  escreve_LCD(celsius);
  
}

int main(void) {
  // LCD
  DDRD = 0xFF;
  char msg[] = "TEMP.: ";
  inic_LCD_4bits();
  cmd_LCD(0x80, 0);
  escreve_LCD(msg);
  
  // CONVERSOR AD
  ADMUX = (1 << REFS0);
  ADCSRA = (1 << ADEN) | (1 << ADIE) | 0b00000111;
  sei();
  
  while (1) {
    ADCSRA |= (1 << ADSC);
  }
}
