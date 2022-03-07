#define F_CPU 16000000
#include <avr/io.h>
#include <util/delay.h>


int main(void) {
    //fazer a contagem do display seja de 0 � 9 e, tamb�m, possua um segundo bot�o para decremento
    
    //DISPLAY � DIREITA: DISP. 1
    DDRD = 0b11111111;
    DDRB = 0b00000011;
    PORTB = 0b00000011;
    
    //PUSH BUTTON 3 e 2:   BOT�O 2 -> INCREMENTO    BOT�O 3 -> DECREMENTO
    DDRC = 0b00000000;
    PORTC = 0b00001100; //PULL UP 
    
    //FLAGS PARA DEBOUNCE DOS PUSH BUTTONS
    char flag_a = 0;
    char flag_b = 0;
    
    unsigned int contador = 0;
    unsigned char display[9] = {0b11100111, 0b10000100, 0b11010011, 0b11010110, 0b10110100, 0b01110110, 0b11000100, 0b11110111, 0b11110110}; 
    
    PORTD = display[0];
    
    while (1) {
        //INCREMENTO DA CONTAGEM DO DISPLAY
        if (!(PINC & (1 << 2))) {
            _delay_ms(10);
            flag_a = 1;
        }
        else if ((PINC & (1 << 2)) && flag_a == 1) {
            _delay_ms(10);
            flag_a = 0;
            contador++;
            if (contador == 9) {
                contador = 0;
            }
        }
        //DECREMENTO DA CONTAGEM DO DISPLAY
        if (!(PINC & (1 << 3))) {
            _delay_ms(10);
            flag_b = 1;
        }
        else if ((PINC & (1 << 3)) && flag_b == 1) {
            _delay_ms(10);
            flag_b = 0;
            if (contador == 0) {                
                contador = 9;                
            }
            contador--;
        }
        PORTD = display[contador];        
    }
}
