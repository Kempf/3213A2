/*
adc.c for ADC-related functions
10/10 Absolute masterpiece
    - IGN

pins to note:
pc0 - analogue input
*/

#include <stdio.h>
#include <avr/io.h>
#include <util/delay.h>
#include "adc.h"

// initialize registers etc
void adc_init(void)
{
    DDRC = DDRC | 0x1; // set PC0 to input
    ADMUX = 0b01000000; // select ADC0
    ADCSRA = 0b11001100; //ADC enabled,/128 divisor, interrupt unmask, conv started
}

// do perverted things to the data
void adc_process(uint16_t *data, uint16_t *n, uint16_t *r, uint16_t *s, uint16_t *h, uint16_t *f, uint16_t *w, uint16_t *ts, uint16_t *te, uint16_t tms)
{
    if(*ts)
		*te = tms;
	if(!*ts)
		*ts = tms;
	*r = 88;
	*n = *te-*ts;
    *s = *data;
    *h = 69;
    *f = 1377; // just for testing
	*w = 1488;
}

void movingAverage(uint16_t *sample, uint8_t *th_latch, uint16_t *count, uint16_t *pa /*This is an array. Go figure.*/, uint16_t *circles, uint16_t *triangles, uint16_t *horns, uint16_t *time, uint8_t *oneOver, uint16_t *time_start, uint16_t* time_end)
{
	//Using a 32 term moving average at the moment. Might be too large.
	if (count == 32){count = 0;}
	pa = pa + count;                                        //Sets the pointer to the 'oldest' item in the array
	*pa = (*sample * *sample);                             //Calculate the 'power' of the current input time, place in array
	int moving_avg = sum_arr((pa - count), oneOver);       //Calculate the 32 term moving average (this is the previous 32 terms)

	if (moving_avg > 10000000){                 //Need to find *ACTUAL* threshold values. Or calculate them.
	if(*th_latch < 3){
		*th_latch = 3;
		*circles += 1;
	}
    }
    else if (moving_avg > 5000000){
        if(*th_latch < 2){
            *th_latch = 2;
            *triangles += 1;
        }
    }
    else if (moving_avg > 600000){
        if(*th_latch < 1){
            *th_latch = 1;
            *horns += 1;
        }
    }
    
    
    //Resets if drops below the lower threshold.
    if(*oneOver == 0){
        if(*th_latch == 3){
            //finish = n;
            *th_latch = 0;
        }        
        if(*th_latch == 2){
            //finish = n;
            *th_latch = 0;
        }
        if(*th_latch == 1){
            //finish = n;
            *th_latch = 0;
        }
    }
    *oneOver = 0;
}

uint16_t sum_arr(uint16_t *pa, uint8_t *oneOver){
	uint16_t sum = 0;
	for(uint8_t i = 0; i<32; i++){
		if (*pa > 600000){*oneOver = 1;}
		sum = sum + *pa;
		pa++;
	}
	return (sum/32);
}
