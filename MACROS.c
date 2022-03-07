#define F_CPU 16000000
#include <avr/io.h>
#include <util/delay.h>

// Definição de macros para trabalhar com bits
#define set_bit(y, bit)         (y |= (1 << bit))
#define clear_bit(y, bit)       (y &= ~(1 << bit))   
#define complement_bit(y, bit)  (y ^= (1 << bit))
#define test_bit(y, bit)        (y & (1 << bit))

int main(void) {
  
  DDRC = 0x00;
  PORTC = 0b00001100; //hab. pull up dos push button em PC2 e PC3
  DDRD = 0xFF; // configurando leds
  PORTD = 0x00;
  
  while (1) {
    if (!test_bit(PINC, PC2)) set_bit(PORTD, PD0);
    else clear_bit(PORTD, PD0);
    if (!test_bit(PINC, PC3)) {
      while (!test_bit(PINC, PC3)) {
        _delay_ms(10);
        complement_bit(PORTD, PD2);
      }
    }
  }
}
