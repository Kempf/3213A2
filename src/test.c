/*

test.c tests lcd functions

pinout:
    
    pb0 red LED
    pb1 green LED
    
    pc0 anal input (waves go here)
    
*/

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "lcd.h"

void init(void)
{
    DDRB = 0x3; // pb0 pb1
}

int main(void)
{
    init();
    lcd_init();
    lcd_test();
	while(1)
    {
        // blink some leds
        PORTB = 0x1;
        _delay_ms(250);
        PORTB = 0x2;
        _delay_ms(250);
    }
}