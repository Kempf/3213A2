#ifndef _ADC_H_
#define _ADC_H_

void adc_init(void);
uint16_t sum_arr(uint16_t a[]);
void adc_process(uint16_t *pa);
uint32_t ideal_tri(uint32_t peak, uint32_t counts);

#endif
