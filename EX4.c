#define F_CPU 160000000
#include <avr/io.h>
#include <util/delay.h>

/*
realizar deslocamento de leds de maneira que funcione com apenas um botão de pulso (PC2) e um
botão com trava (PB2). Caso o botão com trava esteja em nível ?1?, o deslocamento do LED ao dar
um pulso em PC2 deve ser para a esquerda. Caso o botão com trava esteja em nível ?0?, o
deslocamento do LED a cada pulso em PC2 deve ser para a direita.
 */

void increment_led_position(volatile unsigned char *led_position) {
    if (PIND & (1 << 7)) {
        *led_position = 1;
    }
    else {
        *led_position <<= 1;
    }    
}


void decrement_led_position(volatile unsigned char *led_position) {
    if (PIND & 1) {
        *led_position <<= 7;
        return;
    }
    *led_position >>= 1;    
}

int main(void) {
    //BOTÃO PUSH BUTTON
    DDRC = 0x00;
    PORTC = 0b00000100; // habilitando pull up de PC2 e PC3
    char flag = 0;
    
    //CHAVE SWITCH
    DDRB = 0x00;
    
    //LEDS
    DDRD = 0xFF;
    PORTD = 0x01;        
    
    while (1) {
        if (!(PINC & (1 << 2))) {
            _delay_ms(10);
            flag = 1;
        }
        else if ((PINC & (1 << 2)) && flag == 1) {
            _delay_ms(10);
            flag = 0;
            if ((PINB & (1 << 2))) increment_led_position(&PORTD);
            else decrement_led_position(&PORTD);                        
        }        
    }
}
