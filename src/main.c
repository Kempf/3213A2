/*
test.c tests lcd functions
pinout:
    
    pb0 red LED
    pb1 green LED
    
    pc0 anal input ( ?° ?? ?°)
    
*/

//#define F_CPU 16000000UL

#include <avr/io.h>
#include <stdio.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "lcd.h"
#include "adc.h"

#define ARR 16

uint32_t w = 0, f = 0, int_total = 0, peak = 0, total_samples = 0;
uint16_t time_ms = 0, time_s = 0, lcd_tick = 0, td = 0, adc_data = 0;
uint16_t n = 0, r = 0, s = 0, h = 0, ts = 0, te = 0, count = 0, adc_array[ARR], zero = 0;
uint8_t adc_flag = 0, overtime = 0, th_latch = 0, oneOver = 0, toggle = 1;

// timer interrupt
ISR(TIMER0_OVF_vect)
{
	TCNT0 = 240;
	time_ms ++;
    
    lcd_tick ++; // 1 sec tick
    if(lcd_tick == 999)
        lcd_tick = 0;
    
	time_s = time_ms/1000; // time in sec
	if(time_s > 30)
		overtime = 1;
}

// adc interrupt
ISR(ADC_vect)
{
    if(adc_flag){
        PORTB = PORTB | 0x1;
	}		
    adc_data = ADCW; // save data
    adc_flag = 1; // set processing flag
    ADCSRA = ADCSRA | 0x40; // ADSC to 1 to start conv
}

// initialize registers
void init(void)
{
    // leds
    DDRB = 0x3; // pb0 pb1 output
    
    PORTB = 0x2;
    
    // timer stuff
    TCCR0 = 0x05; // set prescaler to 1024
    TCNT0 = 0; // set timer count to 0
    TIMSK = 0x01; // unmask timer0 overflow interrupt
    
    asm("sei"); // enable interrupts
}

int main(void)
{
    init();
    adc_init();
    lcd_init();
	while(1)
    {
        // run lcd update every 1 sec
		if(!lcd_tick)
        {
			lcd_screen(time_s,n,f,r,s,h,w,overtime);
			PORTB = PORTB^0x2; // flip led
        }
        // do adc data processing if there's new data
        if(adc_flag && (!overtime))
        {
            adc_process(&adc_data, &th_latch, &count, adc_array, &r, &s, &h, &n, &time_ms, &ts, &te, &f, &w, &td, &zero, &toggle, &int_total, &peak, &total_samples);
            //adc_test(&adc_data, &n, &r, &s, &h, &f, &w, &ts, &te, time_ms);
            adc_flag = 0;
        }
    }
}
