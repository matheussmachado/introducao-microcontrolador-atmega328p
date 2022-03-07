/*
 * File:   newavr-main.c
 * Author: matheus
 *
 * Created on 5 de Janeiro de 2022, 15:15
 */

#define F_CPU 16000000
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdio.h>
#include "LCD.h"

volatile char buffer[3] = "  ";

ISR(ADC_vect) {
  float val = 0;
  val = (ADC*5/1023.0);
  sprintf(buffer, "%.2f", val);
  cmd_LCD(0xC9, 0);
  escreve_LCD(buffer);
}

int main(void) {
  // CONVERSOR
  ADMUX = 0b01000001;
  ADCSRA = 0b10001111;
  sei();
  
  // DISPLAY LCD
  DDRD = 0xFF;
  inic_LCD_4bits();
  char msg1[] = "MED. DE TENSAO";
  char msg2[] = "CANAL 1: ";    
  cmd_LCD(0x80, 0);
  escreve_LCD(msg1);
  cmd_LCD(0xC0, 0);
  escreve_LCD(msg2);  
  
  while (1) {
    ADCSRA |= (1 << ADSC);   
  }
}
 