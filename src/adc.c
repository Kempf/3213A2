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

#define ARR 64

// initialize registers etc
void adc_init(void)
{
    DDRC = DDRC | 0x1; // set PC0 to input
    ADMUX = 0b01000000; // select ADC0
    ADCSRA = 0b11001100; //ADC enabled,/128 divisor, interrupt unmask, conv started
}

// do perverted things to the data
void adc_test(uint16_t *data, uint16_t *n, uint16_t *r, uint16_t *s, uint16_t *h, uint16_t *f, uint16_t *w, uint16_t *ts, uint16_t *te, uint16_t tms)
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

void adc_process(uint16_t *sample, uint8_t *th_latch, uint16_t *count, uint16_t *pa /*This is an array. Go figure.*/, uint16_t *r, uint16_t *s, uint16_t *h, uint16_t *n, uint16_t *time, uint16_t *time_start, uint16_t *time_end, uint16_t *f, uint16_t *w, uint16_t *td)
{
	//Using a 32 term moving average at the moment. Might be too large.
	if (count == ARR - 1){count = 0;}
	for (uint8_t n = 0; n<count; n++){				//Sets the pointer to the 'oldest' item in the array
		pa++;
	}		
	*pa = (*sample);								//Calculate the 'power' of the current input time, place in array
	int moving_avg = sum_arr((pa - count));			//Calculate the 32 term moving average (this is the previous 32 terms)

	if (moving_avg > 740){							//Need to find *ACTUAL* threshold values. Or calculate them.
	if(*th_latch < 3){
		*th_latch = 3;
		*r += 1;
		*n += 1;
	}
    }
    else if (moving_avg > 675){
        if(*th_latch < 2){
            *th_latch = 2;
            *s += 1;
            *n += 1;
        }
    }
    else if (moving_avg > 624){
        if(*th_latch < 1){
            *th_latch = 1;
            *h += 1;
            *n += 1;
			*time_start = *time;
        }
    }
    //Resets if drops below the lower threshold.
    //Setup like this to allow for power calculations
    else if(moving_avg < 625){
        if(*th_latch == 3){
            //finish = n;
            *th_latch = 0;
			*time_end = *time;
			*td = *time_end - *time_start - 9;
			*w = (((*n - 1)* *w) + *td) * *n;
			*td = 0;
			*time_start = 0;
			*time_end = 0;
        }
        if(*th_latch == 2){
            //finish = n;
            *th_latch = 0;
			*time_end = *time;
			*td = *time_end - *time_start - 9;
			*w = (((*n - 1) * *w) + *td) * *n;
			*td = 0;
			*time_start = 0;
			*time_end = 0;
        }
        if(*th_latch == 1){
            //finish = n;
            *th_latch = 0;
			*time_end = *time;
			*td = *time_end - *time_start - 9;
			*w = (((*n - 1) * *w) + *td) * *n;
			*td = 0;
			*time_start = 0;
			*time_end = 0;
        }
    }
}

uint16_t sum_arr(uint16_t *pa){
	uint16_t sum = 0;
	for(uint8_t i = 0; i<ARR; i++){
		/*if (*pa > 600000){*oneOver = 1;}*/
		sum = sum + *pa;
		pa++;
	}
	return (sum/ARR);
}
