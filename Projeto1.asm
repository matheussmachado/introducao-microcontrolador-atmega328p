
.ORG	0x0000
    
    LDI	    R16, 0B11111111
    OUT	    DDRD, R16
    
    LDI	    R17, 0B00010000
    OUT	    PORTD, R17
  
LOOP:
    RJMP    LOOP

