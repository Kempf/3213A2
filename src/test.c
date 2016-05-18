/*
test.c tests lcd functions
pinout:
    
    pb0 red LED
    pb1 green LED
    
    pc0 anal input ( ?° ?? ?°)
    
*/

#define F_CPU 16000000UL

#include <avr/io.h>
#include <stdio.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "lcd.h"

static unsigned int time_ms = 0, time_s = 0, lcd_tick = 0;

// timer interrupt
ISR(TIMER0_OVF_vect)
{
    TCNT0 = 255;
	time_ms ++; // 16MHz/64 is almost 1 ms
    
    lcd_tick ++; // 1 sec tick
    if(lcd_tick == 999)
        lcd_tick = 0;
    
    time_s = time_ms/1000; // time in sec
}

// initialize registers
void init(void)
{
    // leds
    DDRB = 0x3; // pb0 pb1 output
    
    PORTB = 0x2;
    
    // timer stuff
    TCCR0 = 0x03; // set prescaler to 64
    TCNT0 = 0; // set timer count to 0
    TIMSK = 0x01; // unmask timer0 overflow interrupt
    
    asm("sei"); // enable interrupts
}

int main(void)
{
    init();
    lcd_init();
    //lcd_test();
	while(1)
    {
        // run lcd update every 1 sec
		if(!lcd_tick)
        {
            lcd_screen(time_s,time_ms,11,1,2,3,551);
            PORTB = ~PORTB;
        }
    }
}
