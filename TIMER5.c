/*
 adicione um alarme fixo neste relógio. Quando as horas e os minutos atingirem um
valor pré-determinado, o LED 3 deve ser ligado. Ele será desligado após passar 1 minuto do
horário definido. Os testes condicionais para acionamento do alarme deverão ser feitos no
loop infinito do programa principal.
 */

/* TO-DO's:
 * inserir mensagem de modo
 * 
 * utilizar o PB4 para mudar para a tela de configurar alarme
 * utilizar PB2 para mudar para tela de mudança de horário
 * 
 */


#define F_CPU 16000000
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h> //pois é dependencia para a lib LCD
#include <stdio.h>
#include "LCD.h"

#define test_bit(y, bit)    (y & (1 << bit))
#define set_bit(y, bit)     (y |= (1 << bit))
#define clear_bit(y, bit)   (y &= ~(1 << bit))

volatile unsigned int hora = 0;
volatile unsigned int minuto = 0;
volatile unsigned int segundo = 0;
volatile unsigned int hora_alarme = 12;
volatile unsigned int minuto_alarme = 30;
volatile char buffer[9] = "        ";
volatile unsigned char config_alarme = 0;

ISR(TIMER1_OVF_vect);
ISR(PCINT1_vect);
ISR(PCINT0_vect);


int main(void) {    
  // DISPLAY LCD
  DDRD = 0xFF;
  PORTD = 0x00;
  
  // PUSH BUTTONS
  DDRC = 0b00000000;
  PORTC = 0b00001100; // habilitando pull up dos push buttons
  
  // INTERRUPÇÕES 
  PCICR = 0b00000011; // habilitando interrupção do PORTC e PORTB
  PCMSK0 = 0b00010000; // habilitando interrupção do pino PB4
  PCMSK1 = 0b00001100; // habilitando interrupção dos pinos PC2 e PC3    
  TCCR1B = 0b00000101; // prescaler 1024
  TIMSK1 = 0b00000001; // habilitando interrupção do timer por overflow
  TCNT1 = 49911; // contagem para overflow em 1 seg.
  sei();
  
  // LCD    
  inic_LCD_4bits();
  
  hora = 12;
  minuto = 29;
  segundo = 55;     
  
  while (1) {
    if (hora == hora_alarme && minuto == minuto_alarme) set_bit(PORTD, PD3);
    else clear_bit(PORTD, PD3);
  }
}

ISR(PCINT0_vect) {
  if (test_bit(PINB, PB4)) config_alarme = 1;
  else {
    config_alarme = 0;
    return;
  }
  
}

ISR(PCINT1_vect) {
  // ALTERAR HORA E MINUTO
  unsigned int hora_tmp, minuto_tmp;
  //unsigned char alterar_hora = 1;
  if (config_alarme) {
    hora_tmp = 0;
    minuto_tmp = 0;
  }
  
  if (!test_bit(PINC, PC2)) {
    minuto_tmp++;
    if (minuto_tmp == 60) minuto_tmp = 0;
  }
  if (!test_bit(PINC, PC3)) {
    hora_tmp++;
    if (hora_tmp == 24) hora_tmp = 0;
  }
  if (config_alarme) {
    hora_alarme = hora_tmp;
    minuto_alarme = minuto_tmp;
  }
  else {
    hora++;
    minuto++;
  }
}

ISR(TIMER1_OVF_vect) {
  // ATUALIZAÇÃO E EXIBIÇÃO DO HORÁRIO
  TCNT1 = 49911;
  if (!config_alarme) {
    sprintf(buffer, "%.2d:%.2d:%.2d", hora, minuto, segundo);
    cmd_LCD(0x80, 0);
    escreve_LCD(buffer);
  }  
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