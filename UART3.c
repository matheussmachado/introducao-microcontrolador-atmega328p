/*
Desenvolva um programa que, a cada 1 segundo, envie pela serial o valor dos canais 0 e 1 do
ADC. Ao pressionar qualquer o botão PC2 deverá ser enviada uma mensagem para o computador que o pino foi acionado;
 */


#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdio.h>

#define set_bit(r, bit)   r|=(1<<bit);
#define clr_bit(r, bit)   r&=~(1<<bit);
#define botao_apertado(r, pin)    !(r&(1<<pin))

void UART_escrever_char(volatile char c) {
  UDR0 = c;
  while (!(UCSR0A & (1<<UDRE0))) continue;
}

void UART_escrever_string(volatile char *s) {
  for (int i = 0; s[i] != '\x0'; i++) {
    UART_escrever_char(s[i]);
  }
}

void ADC_enviar_conversao(int canal) {
  if (canal == 0) clr_bit(ADMUX, 0)
  else if (canal == 1) set_bit(ADMUX, 0);
  ADCSRA |= (1<<ADSC);
  while (ADCSRA & (1<<ADSC)) continue;
}

volatile int valor_adc = 0;
volatile char buffer[4];
char separacao_extremo[] = "==========================================\n";
char separacao_meio[] = "-----------------------------------------";
char canal_1[] = "CANAL 1: ";
char canal_0[] = "CANAL 0: ";
char acionado[] = "PC2 FOI ACIONADO";

ISR(TIMER1_OVF_vect) {
  TCNT1 = 49911;
  UART_escrever_string(separacao_extremo);    
  ADC_enviar_conversao(0);  
  sprintf(buffer, "%4d\n", ADC);  
  UART_escrever_string(canal_0);
  UART_escrever_string(buffer);
  
  UART_escrever_string(separacao_meio);
    
  ADC_enviar_conversao(1);
  sprintf(buffer, "%4d\n", ADC);
  UART_escrever_string(canal_1);
  UART_escrever_string(buffer);
  UART_escrever_string(separacao_extremo);
//   
}

ISR(PCINT1_vect) {
  if (botao_apertado(PINC, PC2)) {
    UART_escrever_string(separacao_extremo);
    UART_escrever_string(acionado);
    UART_escrever_string(separacao_extremo);
  }
    
  
  
}

int main(void) {
  // CANAIS
  DDRC = 0x00;
  PORTC = 0b00000100; 
  
  // CONVERSOR AD
  ADMUX = (1 << REFS0) | 0x00;
  ADCSRA = 0b10000111;
  
  // TIMER
  TCNT1 = 49911;
  TCCR1B = 0b00000101;
  TIMSK1 = 0b00000001;
  
  // UART
  UBRR0 = 103; // setar o baud rate 9600
  UCSR0B = (1<<RXCIE0) | (1<<RXEN0) | (1<<TXEN0); // habilitar interrupção e pinos RX e TX
  UCSR0C = (1<<UCSZ01) | (1<<UCSZ02); // setar modo do UART e o tamanho do caractere
  
  // INTERRUPÇÃO EXTERNA
  PCICR = 0b00000010;
  PCMSK1 = 0b00000100;
  
  sei();
  while (1) {
  }
}
