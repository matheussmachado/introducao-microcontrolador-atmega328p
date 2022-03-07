#define F_CPU 16000000UL //define a frequência do microcontrolador - 16MHz
#include <avr/io.h> //definições do componente especificado
#include <util/delay.h> //biblioteca para o uso das rotinas de _delay_ms e _delay_us()
#include <stdio.h> //biblioteca para o uso da função sprintf
#include "LCD.h"
//Definições de macros para o trabalho com bits
#define set_bit(y,bit) (y|=(1<<bit)) //coloca em 1 o bit x da variável Y
#define clr_bit(y,bit) (y&=~(1<<bit)) //coloca em 0 o bit x da variável Y
#define cpl_bit(y,bit) (y^=(1<<bit)) //troca o estado lógico do bit x da variável Y
#define tst_bit(y,bit) (y&(1<<bit)) //retorna 0 ou 1 conforme leitura do bit
//definiçao para acessar a memória flash
char msg1[] = "CONTAGEM = ";
char buffer[4] = " "; //Buffer para armazenamento da variável convertida
//--------------------------------------------------------------------------------------

int main() {
  DDRD = 0b11111111; //PORTD inteiro como saída
  DDRB = 0b00101000; //PB3 e PB5 como saída
  inic_LCD_4bits(); //inicializa o LCD
  escreve_LCD(msg1); //string armazenada na RAM
  while (1) {
    for (int i = 0; i < 999; i++) {
      _delay_ms(500);
      sprintf(buffer, "%.3d", i); //Converte a variável em uma string
      cmd_LCD(0x8B, 0); //Retorna o cursor para o início do número
      escreve_LCD(buffer); //Escreve a variável no display
    }
  }
}