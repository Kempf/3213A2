/*

lcd.c for all things LCD-related

pinout:

    pc4 rs
    pc5 enable

    pd0 d7
    pd1 d6
    ...
    pd7 d0

commands: http://goo.gl/WheZ8n
charset: http://goo.gl/872aBz

*/

#include <avr/io.h>
#include <util/delay.h>
#include "lcd.h"

// initialize LCD
void lcd_init(void)
{
    // set up registers
	DDRC = 0b00110000; // pc4 rs, pc5 enable
	DDRD = 0xFF; // data
	_delay_ms(15); //wait for power up
	
	//initialisation of LCD screen
	lcd_send(0,0b00011100); // function set (5x7 dot format, 2 line mode, 8-bit data)
	lcd_send(0,0b11110000); // Blink ON, underline ON, Display ON
	lcd_send(0,0b01100000); // character entry mode with increment and display shift OFF
	lcd_send(0,0b10000000; // clear screen
    lcd_clear();
}

// clear screen and return cursor
void lcd_clear(void)
{
    lcd_send(0,0b10000000); // clear screen
    lcd_send(0,0b01000000); // cursor return
}

// sends data to LCD
void lcd_send(unsigned char rs, unsigned char data)
{
    // set enable and rs, send command
    PORTC = (rs << 4) | 0b00100000;
    PORTD = data;
	_delay_ms(2);
    // unset enable, wait
	PORTC = (rs << 4);
    PORTD = data;
	_delay_ms(2);
}

// outputs test string
void lcd_test(void)
{
    lcd_send(1,0b11000110);
    lcd_send(1,0b10101100);
    lcd_send(1,0b10110000);
    lcd_send(1,0b00100000);
    lcd_send(1,0b01011110);
    lcd_send(1,0b01011111);
    lcd_send(1,0b01011110);
}

// returns character code
unsigned char lcd_lookup(char symb)
{
    switch(symb)
    {
        case '0': return 0b00110000;
        case '1': return 0b00110001;
        case '2': return 0b00110010;
        case '3': return 0b00110011;
        case '4': return 0b00110100;
        case '5': return 0b00110101;
        case '6': return 0b00110110;
        case '7': return 0b00110111;
        case '8': return 0b00111000;
        case '9': return 0b00111001;
        case '.': return 0b00101110;
        case 'T': return 0b01010100;
        case 'N': return 0b01001110;
        case 'F': return 0b01000110;
        case 'H': return 0b01001000;
        case 'W': return 0b01010111;
        case 'a': return 0b01100001;
        case 'v': return 0b01110110;
        case 'g': return 0b01100111;
        case 'm': return 0b01101101;
        case 'z': return 0b01111010;
        case 's': return 0b01110011;
        case 'e': return 0b01100101;
        case 'c': return 0b01100011;
        case '/': return 0b00101111;
        case ':': return 0b00111010;
        case ' ': return 0b00100000;
        default: return 0b11111111;
    }
}

// outputs first stat screen
void lcd_screen1(int t, int n, int f)
{
    char buffer[5];
    lcd_clear();
    // output time
    lcd_send(1,lcd_lookup('T'));
    lcd_send(1,lcd_lookup(':'));
    sprintf(buffer,"%4d",t);
    for(c = 0; c < 5; c++)
        lcd_send(1,lcd_lookup(buffer[c]);
    lcd_send(1,lcd_lookup('s'));
    lcd_send(1,lcd_lookup(' '));
    // output no. of waveforms
    lcd_send(1,lcd_lookup('N'));
    lcd_send(1,lcd_lookup(':'));
    sprintf(buffer,"%5d",n);
    for(c = 0; c < 5; c++)
        lcd_send(1,lcd_lookup(buffer[c]);
    lcd_send(1,lcd_lookup(' '));
    // freq
    lcd_send(1,lcd_lookup('F'));
    lcd_send(1,lcd_lookup(':'));
    sprintf(buffer,"%5.2f",f);
    for(c = 0; c < 5; c++)
        lcd_send(1,lcd_lookup(buffer[c]);
    lcd_send(1,lcd_lookup('H'));
    lcd_send(1,lcd_lookup('z'));
}

// second stat screen
void lcd_screen2(int t, int r, int s, int h)
{
    char buffer[5];
    lcd_clear();
    // output time
    lcd_send(1,lcd_lookup('T'));
    lcd_send(1,lcd_lookup(':'));
    sprintf(buffer,"%4d",t);
    for(c = 0; c < 5; c++)
        lcd_send(1,lcd_lookup(buffer[c]);
    lcd_send(1,lcd_lookup('s'));
    lcd_send(1,lcd_lookup(' '));
    // round
    lcd_send(1,lcd_lookup('R'));
    lcd_send(1,lcd_lookup(':'));
    sprintf(buffer,"%5d",r);
    for(c = 0; c < 5; c++)
        lcd_send(1,lcd_lookup(buffer[c]);
    lcd_send(1,lcd_lookup(' '));
    // sharp
    lcd_send(1,lcd_lookup('S'));
    lcd_send(1,lcd_lookup(':'));
    sprintf(buffer,"%5d",s);
    for(c = 0; c < 5; c++)
        lcd_send(1,lcd_lookup(buffer[c]);
    lcd_send(1,lcd_lookup(' '));
    // horny
    lcd_send(1,lcd_lookup('H'));
    lcd_send(1,lcd_lookup(':'));
    sprintf(buffer,"%5d",h);
    for(c = 0; c < 5; c++)
        lcd_send(1,lcd_lookup(buffer[c]);
    lcd_send(1,lcd_lookup(' '));
}

// outputs third stat screen
void lcd_screen3(int t, int w)
{
    char buffer[5];
    lcd_clear();
    // output time
    lcd_send(1,lcd_lookup('T'));
    lcd_send(1,lcd_lookup(':'));
    sprintf(buffer,"%4d",t);
    for(c = 0; c < 5; c++)
        lcd_send(1,lcd_lookup(buffer[c]);
    lcd_send(1,lcd_lookup('a'));
    lcd_send(1,lcd_lookup('v'));
    lcd_send(1,lcd_lookup('g'));
    lcd_send(1,lcd_lookup('W'));
    lcd_send(1,lcd_lookup(' '));
    // width
    lcd_send(1,lcd_lookup('F'));
    lcd_send(1,lcd_lookup(':'));
    sprintf(buffer,"%5.2f",f);
    for(c = 0; c < 5; c++)
        lcd_send(1,lcd_lookup(buffer[c]);
    lcd_send(1,lcd_lookup('m'));
    lcd_send(1,lcd_lookup('s'));
}