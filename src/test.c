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

static unsigned int time_ms;

// timer interrupt
ISR(TIMER0_OVF_vect)
{
    time_ms ++; // 1MHz/1024 is almost 1 ms
}

// initialize registers
void init(void)
{
    // leds
    DDRB = 0x3; // pb0 pb1 output
    
    // timer stuff
    TCCR0 = 0x05; // set prescaler to clk/1024
    TCNT0 = 0; // set timer count to 0
    TIMSK = 0x01; // unmask timer0 overflow interrupt
    
    asm("sei"); // enable interrupts
}

int main(void)
{
    /*int i = 0, t = 0;
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
        /*i ++;
        f += 0.1;
        t = time_ms * 1000;
        lcd_screen1(t,i,f);*/
        // lcd_screen2(i, i, i, i);
        // lcd_screen3(i, f);
        
    }
}