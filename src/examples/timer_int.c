static unsigned int time_count; //0.5sec counter
ISR(TIMER0_OVF_vect)
{
    TCNT0 = 207; //each count to 256 takes 50ms
    time_count++;
    if (time_count==10) {
        PORTC = (PORTC ^ 0x01); //switch logic level on pin
        time_count = 0;
    }
}
void main ()
{
    DDRC = 0x01; //set lsb of port C for output
    TCCR0 = 0x05; //set prescaler to clk/1024
    TCNT0=0; //set count to 0
    TIMSK=0x01; //unmask timer0 overflow interrupt
    asm("sei"); //enable interrupts
    while(1); //do nothing
}
