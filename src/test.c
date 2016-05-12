/*

test.c tests lcd functions

pinout:
    
    pb0 red LED
    pb1 green LED
    
    pc0 anal input ( ͡° ͜ʖ ͡°)
    
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
    /*int i = 0;
    float f = 0.0;*/
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
        /*i++;
        f+=0.1;
        lcd_screen1(i,i,f);*/
        // lcd_screen2(i, i, i, i);
        // lcd_screen3(i, f);
        
    }
}