#ifndef _MAIN_H_
#define _MAIN_H_

#define F_CPU 16000000UL

#define ARR 16

extern uint32_t w, f, int_total, peak, total_samples;
extern uint16_t time_ms, time_s, lcd_tick, td, adc_data;
extern uint16_t n, r, s, h, time_start, time_end, count, adc_array[ARR], zero;
extern uint8_t adc_flag, overtime, th_latch, oneOver, toggle;

#endif
