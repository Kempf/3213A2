#ifndef _ADC_H_
#define _ADC_H_

void adc_init(void);
void adc_test(uint16_t *data, uint16_t *n, uint16_t *r, uint16_t *s, uint16_t *h, uint16_t *f, uint16_t *w, uint16_t *ts, uint16_t *te, uint16_t tms);
uint16_t sum_arr(uint16_t a[], uint16_t x);
void adc_process(uint16_t *sample, uint8_t *th_latch, uint16_t *count, uint16_t *pa, uint16_t *r, uint16_t *s, uint16_t *h, uint16_t *n, uint16_t *time, uint16_t *time_start, uint16_t *time_end, uint32_t *f, uint32_t *w, uint16_t *td, uint16_t *zero, uint8_t *toggle, uint16_t *diff_arr, uint16_t *count2, int16_t *last_avg, uint8_t *df_latch);

#endif
