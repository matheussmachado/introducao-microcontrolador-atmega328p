#define F_CPU 16000000

#include <avr/io.h>
#include <util/delay.h>


int main(void) {        
    //PUSH BUTTON 
    DDRC = 0b00000000;
    PORTC = 0b00001100; //habilitando pull up            
    
    //LEDS
    DDRD = 0b11111111;
    PORTD = 0b00000001;
    
    unsigned char flag_a = 0;
    unsigned char flag_b = 0;
    
    while (1) {
        //INCREMENTO DA POSIÇÃO DO LED ACESSO
        if (!(PINC & (1 << 2))) {
            _delay_ms(10);
            flag_a = 1;
        }
        else if ((PINC & (1 << 2)) && flag_a == 1) {
            _delay_ms(10);
            flag_a = 0;
            if ((PIND & (1 << 7))) {
                PORTD >>= 7;
                continue;
            }
            PORTD <<= 1;
        }
        //DECREMENTO DA POSIÇÃO DO LED ACESSO
        if (!(PINC & (1 << 3))) {
            _delay_ms(10);
            flag_b = 1;            
        }        
        else if ((PINC & (1 << 3)) && flag_b == 1) {
            _delay_ms(10);
            flag_b = 0;
            if ((PIND & (1))) {
                PORTD <<= 7;
                continue;
            }
            PORTD >>= 1;
        }
    }
}
