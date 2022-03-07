/*
 Com a função ?_delay_ms?, crie um programa que altere a velocidade em que um LED pisca.
Começando com 500ms, cada vez que PC2 receber um pulso o tempo diminui 100ms, até chegar ao
limite de 0ms e, toda vez que PC3 receber um pulso, o tempo aumenta em 100ms, até o limite de 1s.
 */

#define F_CPU 16000000
#define __DELAY_BACKWARD_COMPATIBLE__
#include <avr/io.h>
#include <util/delay.h>


int main(void) {
    //LED
    DDRD = 0x02;
    PORTD = 0x02;
    unsigned int tempo_oscilacao = 500; //ms
    
    
    //PUSH BUTTONS
    DDRC = 0x00;
    PORTC = 0x0C; //habilitando pull up de PC2 e PC3    
    unsigned char flag_a, flag_b;
    flag_a = flag_b = 0;
    
    while (1) {
        //INCREMENTO DO TEMPO DE OSCILAÇÃO DO LED
        if (!(PINC & (1 << 2))) {
            _delay_ms(10);
            flag_a = 1;
        }
        if ((PINC & (1 << 2)) && flag_a == 1 && tempo_oscilacao < 1000) {
            flag_a = 0;
            _delay_ms(10);
            tempo_oscilacao += 100;
        }
        
        //DECREMENTO DO TEMPO DE OSCILAÇÃO DO LED
        if (!(PINC & (1 << 3))) {
            _delay_ms(10);
            flag_b = 1;
        }
        if ((PINC & (1 << 2)) && flag_b == 1 && tempo_oscilacao > 0) {
            flag_b = 0;
            _delay_ms(10);
            tempo_oscilacao -= 100;
        }
        _delay_ms(tempo_oscilacao);
        PORTD ^= (1 << 1);
    }
}
