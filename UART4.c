/*
Crie um programa onde o usuário altere o ciclo do PWM pela serial. O ciclo deverá ser divido
em 10 faixas, por exemplo: ?0? ? 10%, ?1? ? 20%, ?2? ? 30%, ?9? ? 100%, ?A? ? 0%. Utilize o LED
de PD4 para mostrar o funcionamento do PWM.
 */


#include <avr/io.h>
#include <avr/interrupt.h>

#define RESOLUCAO_PWM   100


volatile unsigned int ciclo_ativo;
volatile unsigned int passo_pwm = 0;

ISR(USART_RX_vect) {
  char ch = 0;
  ch = UDR0;
  switch (ch) {
    case '0': ciclo_ativo = 10; break;
    case '1': ciclo_ativo = 20; break;
    case '2': ciclo_ativo = 30; break;
    case '9': ciclo_ativo = 100; break;
    case 'A': ciclo_ativo = 0; break;
  }
}

ISR(TIMER0_OVF_vect) {
  TCNT0 = 96;
  passo_pwm++;  
  if (passo_pwm == RESOLUCAO_PWM) {
    passo_pwm = 0;
    PORTD |= (1<<4);
  }
  else if (passo_pwm == ciclo_ativo) PORTD &= ~(1<<4);
}

int main(void) {
  // LEDS
  DDRD = 0xFF;
  PORTD = 0b00010000;
  
  // TIMER
  TCNT0 = 96;
  TCCR0B = 0b00000001;  
  TIMSK0 = 0b00000001;
  
  // UART
  UBRR0 = 103;
  UCSR0B = (1<<7) | (1<<4) | (1<<3);  
  UCSR0C = 0x00 | (1<<UCSZ01) | (1<<UCSZ00);  
  
  ciclo_ativo = 5;
  sei();
  while (1) {
  }
}
