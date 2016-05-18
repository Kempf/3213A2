#include <stdio.h>
#include <avr/io.h>
#include <util/delay.h>
#include "lcd.h"

//Need to create a 32 entry point_array in main file.
//Will need corresponding data.

void movingAverage(int sample, int *th_latch, int *count, int *pa /*This is an array. Go figure.*/, int *circles, int *triangles, int *horns, int *time,int *oneOver, int *time_start, int* time_end)
{
    //Using a 32 term moving average at the moment. Might be too large.
    int td = (1/9375);
    if (couunt == 32){count = 0};
    pa = pa + count;                            //Sets the pointer to the 'oldest' item in the array
    *pa = (sample * sample) / (td);             //Calculate the 'power' of the current input time, place in array
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
    if(oneOver == 0){
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
    return;
}

int sum_arr(int *pa, int *oneOver){
    int sum = 0;
    for(int i = 0; i<32; i++){
        if (*pa > 600000){*oneOver = 1;}
        sum = sum + *pa;
        pa++;
    }
    return (sum/32);
}

/* Matlab code for reference and adaptation


data(1) = [];
    %disp(size(data));
    for p = 10:10:200
            q = n - p;
            w4_int(n) = w4_int(n) + (d(q, 2)^2/(50*td));
    end    
    data(70) = w4_int(n);
    %disp(data)
    if (w4_int(n) > 10000000) 
        th = 3;
        if(th_latch < 3)
            th_latch = 3;
        end
    elseif (w4_int(n) > 5000000)
            th = 2;
            if(th_latch < 2)
                th_latch = 2;
            end
    elseif (w4_int(n) > 600000)
            th = 1;
            if(th_latch < 1)
                th_latch = 1;
                start(length(start) + 1) = n;
            end
            
    elseif((data(1) < 600000) &&   (data(11) < 600000) &&  (data(21) < 600000) &&  (data(31) < 600000) &&  (data(41) < 600000) &&  (data(51) < 600000) &&  (data(61) < 600000))
        th = 0;
        if(th_latch == 3)
           finish = n;
           th_latch = 0;
           circles = circles + 1;
        end
        
        if(th_latch == 2)
           finish = n;
           th_latch = 0;
           triangles = triangles + 1;
        end
        
        if(th_latch == 1)
           finish = n;
           th_latch = 0;
           horns = horns + 1;
        end
    end    /*
