/*
adc.c ADC-related functions

Group 42

pinout:
	pc0 - analogue input

waves:
	1: 90R         90T
	2: 27R 58S 52H 137T
	3: 22R 37S 33H 92T
	4: 22R 27S 33H 82T
*/

#include <stdio.h>
#include <avr/io.h>
#include <util/delay.h>
#include "adc.h"
#include "main.h"

// initialize registers etc
void adc_init(void)
{
    ADMUX = 0b01000000; // select ADC0, Vcc
    ADCSRA = 0b11001111; //ADC enabled, /128 divisor, interrupt unmask, conv started
}

// ADC data processing and pattern detection
void adc_process(uint16_t *pa)
{	
	if(th_latch > 0)
        total_samples += 1;
    else
        total_samples = 0;
	
	uint32_t comparator = 0;														
	pa += count; // sets the pointer to the 'oldest' item in the array
	*pa = adc_data;	// calculate the 'power' of the current input time, place in array
	int moving_avg = sum_arr((pa - count))/ARR;	// calculate the 32 term moving average (this is the previous 32 terms)					
	if (moving_avg < zero){
		moving_avg = 0;
		comparator = 0;
	} else {
		moving_avg = moving_avg - zero;
		comparator = (uint16_t)((moving_avg/2) * (moving_avg/2));
	}
	
	// threshold latches
    if ((comparator > 20000) && (zero != 0)){
        th_latch = 2;
    }
    else if ((comparator > 2000) && (zero != 0)){
        if(th_latch < 1){
            th_latch = 1;
			time_start = time_ms;
        }
	}  
	
	// peak detection
	if (th_latch > 0){
		int_total += comparator;
		if(comparator > peak)
		{
			peak = comparator;
		}
	}	
		
    // resets if drops below the lower threshold
    if(comparator < 2000){
		// choose between S and R shapes
        if(th_latch == 2){
			time_end = time_ms;
			td = (time_end - time_start);
			if(ideal_tri(peak, total_samples) > int_total){
				s += 1;
			} else{
				r+=1;
			}
            n += 1;
        }
		// H shape
        if(th_latch == 1){
			if(toggle == 1){
				h += 1;
				n += 1;
				toggle = 0;
				time_end = time_ms;
			    td = (time_end - time_start);	
			} else {
				toggle = 1;
			}			
        }
		// reset everything
		if(th_latch){
			th_latch = 0;
			peak = 0;
			int_total = 0;
			// calculate avg width
			w = ((((n - 1) * w) + (td * 100)) / n);
			td = 0;
			time_start = 0;
			time_end = 0;	
		}
		f = n * 100000 / time_ms;
    }

	// reset count if at the end of the array
	if (count == ARR - 1){
		if(zero == 0){
			zero = moving_avg;
		} // set threshold value on first runthrough
		count = 0;
	} else{
		count = count + 1;	//DON'T SET IT TO COUNT++. THIS WILL BREAK EVERYTHING.
	}
	
			
}

// returns sum of array
uint16_t sum_arr(uint16_t a[]){
	int i, sum=0;
	for (i=0; i<ARR; i++)
	{
		sum = sum + a[i];
	}
	return (uint16_t)(sum);
}


// computes the area of an ideal triangle based on width and height
uint32_t ideal_tri(uint32_t peak, uint32_t counts){
	return (uint32_t)((peak * counts)*113 / 200);
}
