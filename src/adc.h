#ifndef _ADC_H_
#define _ADC_H_

void adc_init(void);
void adc_process(uint16_t *data, uint16_t *n, uint16_t *r, uint16_t *s, uint16_t *h, uint16_t *f, uint16_t *w, uint16_t *ts, uint16_t *te, uint16_t tms);
uint16_t sum_arr(uint16_t *pa, uint8_t *oneOver);
void movingAverage(uint16_t *sample, uint8_t *th_latch, uint16_t *count, uint16_t *pa, uint16_t *circles, uint16_t *triangles, uint16_t *horns, uint16_t *time, uint8_t *oneOver, uint16_t *time_start, uint16_t* time_end);

#endif
