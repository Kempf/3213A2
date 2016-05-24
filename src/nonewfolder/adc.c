/*
adc.c for ADC-related functions
10/10 Absolute masterpiece
    - IGN
This code: 9/10
This code with rice: 10/10
Thankyou for your suggestion
	-  DO_U_EVN_SPAGHETTI
    
pins to note:
pc0 - analogue input
*/

//One term
// 91 roundies detected from wave 1 random start
// 87 Consistent

//Moving Average
//82
//84
//86

//Peak around 869
//Baseline 420


// I made line 122 references to zero -> *zero

// Wave 1 : 90R - 90
//Wave 2: 27R 57S 52H -136
// Wave 3: 22R 37S 33H  - 92
//Wave 4: 22R 27S 33H - T82

#include <stdio.h>
#include <avr/io.h>
#include <util/delay.h>
#include "adc.h"

#define ARR 16
#define DIF 1

// initialize registers etc
void adc_init(void)
{
    //DDRC = DDRC | 0x1; // set PC0 to input
    ADMUX = 0b01000000; // select ADC0, Vcc
    ADCSRA = 0b11001111; //ADC enabled,/128 divisor, interrupt unmask, conv started
}

// do perverted things to the data
void adc_test(uint16_t *data, uint16_t *n, uint16_t *r, uint16_t *s, uint16_t *h, uint16_t *f, uint16_t *w, uint16_t *ts, uint16_t *te, uint16_t tms)
{
	*r = 88;
	*n = *data;
    *s = *data;
    *h = 69;
    *f = 1377; // just for testing
	*w = *data;
}

void adc_process(uint16_t *sample, uint8_t *th_latch, uint16_t *count, uint16_t *pa, uint16_t *r, uint16_t *s, uint16_t *h, uint16_t *n, uint16_t *time, uint16_t *time_start, uint16_t *time_end, uint32_t *f, uint32_t *w, uint16_t *td, uint16_t *zero, uint8_t *toggle, uint16_t *diff_arr, uint16_t *count2, int16_t *last_avg, uint8_t *df_latch)
{	
	uint16_t comparator = 0;
	int16_t differentiation = 0;
    // TODO: add integration
    //       recalculate thresholds for offset zero levels
    // offset zero:
	//Using a 32 term moving average at the moment. Might be too large.																//I removed a 2* multiplier here
	pa += *count;											//Sets the pointer to the 'oldest' item in the array
	*pa = (*sample);									//Calculate the 'power' of the current input time, place in array
	diff_arr += *count2;
	*diff_arr = (*sample);
	int moving_avg = sum_arr((pa - *count), ARR)/ARR;						//Calculate the 32 term moving average (this is the previous 32 terms)					//Work out why having this as 2 doesn't work. (Multiplied by)
	int dif_mv_avg = sum_arr((diff_arr - *count2), DIF)/DIF;
	if (moving_avg < *zero){
		moving_avg = 0;
		comparator = 0;
	} else {
		moving_avg = moving_avg - *zero;
		comparator = (uint16_t)((moving_avg/2) * (moving_avg/2));
	}
	if (dif_mv_avg < *zero){
		dif_mv_avg = 0;
		differentiation = 0;
	} else {
		dif_mv_avg = dif_mv_avg- *zero;
		differentiation = dif_mv_avg - *last_avg;
		*last_avg = differentiation;		
	}
										// temporary average output
	if ((comparator > 25000) && (*zero != 0)){							//Need to find *ACTUAL* threshold values. Or calculate them.
		if(*th_latch < 2){
			*th_latch = 2;
		}
    }
    else if ((comparator > 2000) && (*zero != 0)){
        if(*th_latch < 1){
            *th_latch = 1;
        }
    }
	
	if ((differentiation > 200) && (*zero != 0)){							//Need to find *ACTUAL* threshold values. Or calculate them.
		if(*df_latch < 2){
			*df_latch = 2;
		}
	}
	else if ((differentiation > 15) && (*zero != 0)){
		if(*df_latch < 1){
			*df_latch = 1;
		}
	}
	
	
    //Resets if drops below the lower threshold.
    //Setup like this to allow for power calculations
    else if((comparator < 2000)){
        if((*th_latch == 2)&&(*df_latch ==2)){
            //finish = n;
			*r += 1;
			*n += 1;
            *th_latch = 0;
			df_latch = 0;
			*time_end = *time;
			*td = (*time_end - *time_start)*100;
			*w = ((((*n - 1)* *w) + *td) / *n);
			*td = 0;
			*time_start = 0;
			*time_end = 0;
        }
        if((*th_latch == 2)&&(*df_latch ==1)){
            //finish = n;
			*s += 1;
            *n += 1;
            *th_latch = 0;
			*df_latch = 0;
			*time_end = *time;
			*td = (*time_end - *time_start)*100;
			*w = ((((*n - 1) * *w) + *td) / *n);
			*td = 0;
			*time_start = 0;
			*time_end = 0;
        }
        if((*th_latch == 1)&&(*df_latch ==2)){
            //finish = n;
			if(*toggle == 1){
				*h += 1;
				*n += 1;
				*toggle = 0;	
			} else {
				*toggle = 1;
			}			
            *th_latch = 0;
			df_latch = 0;
			*time_end = *time;
			*td = (*time_end - *time_start)*100;
			*w = ((((*n - 1) * *w) + *td) / *n);
			*td = 0;
			*time_start = 0;
			*time_end = 0;
			
        }
		*f = *n * 100000 / *time;
    }

		    // reset count if at the end of the array
	if (*count == ARR - 1){
		if(*zero == 0){
			*zero = moving_avg;
		} // set threshold value on first runthrough
		*count = 0;
	}else{
		*count = *count + 1;	//DON'T SET IT TO COUNT++. THIS WILL BREAK EVERYTHING.
	}
	
	
	if (*count2 == DIF -1){
		*count2 = 0;
	} else {
		*count2 = *count2 + 1;
	}
	
	
			
}

uint16_t sum_arr(uint16_t a[], uint16_t x)
{
	int i, sum=0;
	for (i=0; i<x; i++)
	{
		sum = sum + a[i];
	}
	return (uint16_t)(sum);
}
