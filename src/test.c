/*
test.c tests lcd functions
pinout:
    
    pb0 red LED
    pb1 green LED
    
    pc0 anal input ( ?° ?? ?°)
    
*/

//#define F_CPU 1000000UL

#include <avr/io.h>
#include <stdio.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "lcd.h"

static unsigned int time_ms;

// timer interrupt
ISR(TIMER0_OVF_vect)
{
    TCNT0 = 255;
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
    init();
    lcd_init();
    //lcd_test();
	PORTB = 0x2;
	while(1)
    {
		lcd_screen(time_ms,5,1.1,1,2,3,5.5);
		PORTB = ~PORTB;			
    }
}
