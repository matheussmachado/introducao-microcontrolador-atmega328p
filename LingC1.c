#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>

void main() 
{
    DDRD = 0b11111111;
    
    while (1)
    {
        /*
        PORTD = 0xAA;
        _delay_ms(500);
        PORTD = 0x55;
        _delay_ms(500);
        */        
        PORTD ^= 0b00001000;
        _delay_ms(500);
        
        
    }
}