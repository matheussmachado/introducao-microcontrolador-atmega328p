#define F_CPU 16000000
#include <avr/io.h>
#include <util/delay.h>

int main(void) {
    char flag = 0;
    int contador = 0;
    
    DDRC = 0b00000000;
    PORTC = 0b00001100;   
    DDRD = 0xFF;
    DDRB = 0b00000001; 
    PORTB = 0b00000001;
    
    while (1) {
        if (!(PINC & (1 << 2))) {
            _delay_ms(10);
            flag = 1;        
        }
        if ((PINC & (1 << 2)) && flag == 1) {
            _delay_ms(10);
            flag = 0;
            contador++;
            if (contador == 10) {
                contador = 0;
            }
        }
        
        switch(contador) {
            case 0:  PORTD = 0b11100111; break;
            case 1:  PORTD = 0b10000100; break;
            case 2:  PORTD = 0b11010011; break;
            case 3:  PORTD = 0b11010110; break;
            case 4:  PORTD = 0b10110100; break;
            case 5:  PORTD = 0b01110110; break;
            case 6:  PORTD = 0b01110111; break;
            case 7:  PORTD = 0b11000100; break;
            case 8:  PORTD = 0b11110111; break;
            case 9:  PORTD = 0b11110110; break;
            default: break;
                    
        }
        
    }
}
