#include <avr/interrupt.h>
ISR(ADC_vect)
{
    uint16_t adc_data; //look at this data type for unsigned int!
    adc_data=ADCW; //ADCW is a short-hand code way to read the full 10 bit
    //result from ADCH/L
    if (adc_data > 1024*2/3)
        PORTC = 0b11111011; //LED on 3rd pin of port C goes on (active low)
    else if (adc_data > 1024/3)
        PORTC = 0b11111101; //LED on 2nd pin of port C goes on (active low)
    else PORTC = 0b11111110; //LED on 1st pin of port C goes on (active low)
        ADCSRA = ADCSRA | 0x40; //set ADSC bit to 1 again to star next conv.
}
void main ()
{
    DDRC = 0x07; //set bottom 3 bits of port C for output
    ADMUX = 0x3; //select to read only from ADC3
    ADCSRA = 0xCD; //ADC enabled,/8 divisor, interrupt unmask, conv started
    asm (“sei”); //enable interrupts
    while(1); //do nothing (ADC interrupt does it all)
}
