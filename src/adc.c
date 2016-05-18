/*
adc.c for ADC-related functions
10/10 Absolute masterpiece
    - IGN

pins to note:
pc0 - analogue input
*/

// initialize registers etc
void adc_init(void)
{
    DDRC = DDRC | 0x1; // set PC0 to input
    ADMUX = 0x0; // select ADC0
    ADCSRA = 0b11001111; //ADC enabled,/128 divisor, interrupt unmask, conv started
}

// do perverted things to the data
void adc_process(uint16_t *data, *n, *r, *s, *h, *f, *w)
{
    *n = 0;
    *r = 1;
    *s = 2;
    *h = 3;
    *f = *data; // just for testing
    *w = 5678;
}