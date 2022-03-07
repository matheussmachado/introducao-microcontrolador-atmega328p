#define F_CPU 16000000
#include <avr/io.h>
#include <util/delay.h>

int main(void) {
    // INVERTER O ESTADO DE 2 LEDS (2 E 3) AO ACIONAR SEUS RESPECTIVOS BOTÕES
    
    //LEDS - SAÍDA
    DDRD = 0b00001100;
    
    //BOTÕES - ENTRADA
    DDRC = 0b00000000;
    PORTC = 0b00001100; // PULL UP
    
    char flag_a = 0;
    char flag_b = 0;
    
    while (1) {
        //BOTÃO 2 -> LED 2
        if (!(PINC & (1 << 2))) {
            _delay_ms(10);
            flag_a = 1;
        }
        else if ((PINC & (1 << 2) && flag_a == 1)) {
            _delay_ms(10);
            flag_a = 0;
            PORTD ^= (1 << 2);
        }
        //if (0b1100 & 0b1000) {
        //    PORTD |= (1 << 3);
        //}
        
        //BOTÃO 3 -> LED 3
        if (!(PINC & (1 << 3))) {
            _delay_ms(10);
            flag_b = 1;            
        }
        else if ((PINC & (1 << 3)) && flag_b == 1) {
            _delay_ms(10);
            flag_b = 0;
            PORTD ^= (1 << 3);
        }        
    }
}
