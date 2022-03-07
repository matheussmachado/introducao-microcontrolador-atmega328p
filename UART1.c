/*
 * 0 à 7 - Liga um dos 8 LEDs
 * ?C? ? Retorna o status do botão PC2
 * ?D? ? Retorna o valor do conversor AD - canal 0
 * 'F' - Retorna o valor do conversor AD - canal 1
 * 'Q' - Retorna o status do PB2
 * 
 */

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdio.h>
//#include "UART.h"

#define set_bit(y,bit) (y|=(1<<bit)) //coloca em 1 o bit x da variável Y
#define clr_bit(y,bit) (y&=~(1<<bit)) //coloca em 0 o bit x da variável Y
#define cpl_bit(y,bit) (y^=(1<<bit)) //troca o estado lógico do bit x da variável Y
#define tst_bit(y,bit) (y&(1<<bit)) //retorna 0 ou 1 conforme leitura do bit

void controlar_led(int indice_led);

char s[] = "Comunicacao SERIAL\n";
char bt_press[] = "BOTAO PRESSIONADO\n";
char bt_solto[] = "BOTAO SOLTO\n";
char sw_press[] = "SWITCH PRESSIONADO\n";
char sw_solto[] = "SWITCH SOLTO\n";
char buffer[5];
volatile char ch; //armazena o caractere lido
volatile char flag_com = 0; //flag que indica se houve recepção de dado
int controle_led[] = {1, 1, 1, 1, 1, 1, 1, 1};


ISR(USART_RX_vect) {
  ch = UDR0; //Faz a leitura do buffer da serial
  while (!(UCSR0A & (1 << UDRIE0))) continue;
  flag_com = 1; //Aciona o flag de comunicação
}


int main() {
  int valor_adc = 0;
  // PUSH BUTTONS
  DDRC = 0b00000000;
  PORTC = 0b00001100;
  
  // SWITCHES
  DDRB = 0x00;
  
  // LEDS
  DDRD = 0b11111111;
  PORTD = 0b00000000;
  
  // UART
  UBRR0 = 103;
  UCSR0B = 0b10011000;
  UCSR0C = 0b00000110;
  
  // CONVERSOR AD
  ADMUX = 0x00 | (1 << REFS0);
  ADCSRA = 0b10000111;
  
  
  //UART_enviaString(s); //Envia um texto para o computador
  for (int i = 0; s[i] != '\x0'; i++) {
    UDR0 = s[i];
    while (!(UCSR0A & (1 << UDRE0))) continue;
  }
  sei(); //Habilita as interrupções
  
  while (1) {
    //Se houve comunicação, testa o caractere recebido
    if (flag_com == 1) {
      switch (ch) {
        case 'C':
          if (tst_bit(PINC, PINC2) == 0) //Testa o botão PC2
            for (int i = 0; bt_press[i] != '\x0'; i++) {
              UDR0 = bt_press[i];
              while (!(UCSR0A & (1<<UDRE0))) continue;
            }
          else
            for (int i = 0; bt_solto[i] != '\x0'; i++) {
              UDR0 = bt_solto[i];
              while (!(UCSR0A & (1<<UDRE0))) continue;
            }
          break;
        case 'D':
          //ADMUX = 0x00 | (1 << REFS0);
          clr_bit(ADMUX, 0);
          ADCSRA |= (1 << ADSC);
          while (ADCSRA & (1 << ADSC)) continue;            
          valor_adc = ADC;
          sprintf(buffer, "%4d\n", valor_adc); //Converte para string
          for (int i = 0; buffer[i] != '\x0'; i++) {
            UDR0 = buffer[i];
            while (!(UCSR0A & (1<<UDRE0))) continue;
          }
          break;
        case 'F':
          //ADMUX = 0b00000001 | (1 << REFS0);
          set_bit(ADMUX, 0);
          ADCSRA |= (1 << ADSC);
          while (ADCSRA & (1 << ADSC)) continue;
          valor_adc = ADC;
          sprintf(buffer, "%4d\n", valor_adc);
          for (int i = 0; buffer[i] != '\x0'; i++) {
            UDR0 = buffer[i];
            while (!(UCSR0A & (1 << UDRE0))) continue;
          }
          break;
        case 'Q':
          if (!tst_bit(PINB, PB2)) {
            for (int i = 0; sw_press[i] != '\x0'; i++) {
              UDR0 = sw_press[i];
              while (!(UCSR0A & (1<<UDRE0))) continue;
            }
          }
          else {
            for (int i = 0; sw_solto[i] != '\x0'; i++) {
              UDR0 = sw_solto[i];
              while (!(UCSR0A & (1<<UDRE0))) continue;
            }
          }
          break;
      }      
      for (int i = 0; i <= 7; i++) {
        if (i == ch - '0') {
          controlar_led(ch - '0');
          break;
        }
      }      
      //Apaga o flag de comunicação
      flag_com = 0;
    }
  }
}

void controlar_led(int indice_led) {
  if (controle_led[indice_led] == 1) {
    set_bit(PORTD, indice_led);    
  }
  else {
    clr_bit(PORTD, indice_led);    
  }
  controle_led[indice_led] = !controle_led[indice_led];
}
