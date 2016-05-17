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

#include <stdio.h>
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
	lcd_send(0,0b00110000); // Blink OFF, underline OFF, Display ON
	lcd_send(0,0b01100000); // character entry mode with increment and display shift OFF
	lcd_send(0,0b10000000); // clear screen
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
	lcd_send(1,0b01100011);
	lcd_send(1,0b00110101);
	lcd_send(1,0b00001101);
	lcd_send(1,0b00000100);
	lcd_send(1,0b01111010);
	lcd_send(1,0b11111010);
	lcd_send(1,0b01111010);
}

// returns character code
unsigned char lcd_lookup(char symb)
{
    switch(symb)
    {
		case '0': return 0b00001100;
		case '1': return 0b10001100;
		case '2': return 0b01001100;
		case '3': return 0b11001100;
		case '4': return 0b00101100;
		case '5': return 0b10101100;
		case '6': return 0b01101100;
		case '7': return 0b11101100;
		case '8': return 0b00011100;
		case '9': return 0b10011100;
		case '.': return 0b01110100;
		case 'T': return 0b00101010;
		case 'N': return 0b01110010;
		case 'F': return 0b01100010;
		case 'H': return 0b00010010;
		case 'W': return 0b11101010;
		case 'a': return 0b10000110;
		case 'v': return 0b01101110;
		case 'g': return 0b11100110;
		case 'm': return 0b10110110;
		case 'z': return 0b01011110;
		case 's': return 0b11001110;
		case 'e': return 0b10100110;
		case 'c': return 0b11000110;
		case '/': return 0b11110100;
		case ':': return 0b01011100;
		case ' ': return 0b00000100;
		default: return 0b11111111;
    }
}

// outputs first stat screen
void lcd_screen(int t, int n, float f, int r, int s, int h, float w)
{
    char buffer[5];
	t = (int)(t/1000);
    unsigned char screen = t % 9;
	switch(screen)
	{
		case 0:
			// output time
			lcd_send(0,0b00000001);
			//lcd_clear();
			lcd_send(1,lcd_lookup('T'));
			lcd_send(1,lcd_lookup(':'));
			sprintf(buffer,"%5d",t);
			for(int c = 0; c < 5; c++)
			lcd_send(1,lcd_lookup(buffer[c]));
			lcd_send(1,lcd_lookup('s'));
			lcd_send(1,lcd_lookup(' '));
			// output no. of waveforms
			lcd_send(1,lcd_lookup('N'));
			lcd_send(1,lcd_lookup(':'));
			sprintf(buffer,"%5d",n);
			for(int c = 0; c < 5; c++)
				lcd_send(1,lcd_lookup(buffer[c]));
			lcd_send(1,lcd_lookup(' '));
			// freq
			lcd_send(0,0b00000011);
			lcd_send(1,lcd_lookup('F'));
			lcd_send(1,lcd_lookup(':'));
			sprintf(buffer,"%5d",(int)(f*100));
			for(int c = 0; c < 3; c++)
				lcd_send(1,lcd_lookup(buffer[c]));
			lcd_send(1,lcd_lookup('.'));
			lcd_send(1,lcd_lookup(buffer[3]));
			lcd_send(1,lcd_lookup(buffer[4]));
			lcd_send(1,lcd_lookup('H'));
			lcd_send(1,lcd_lookup('z'));
			break;
		case 3:
			// output time
			lcd_send(0,0b00000001);
			//lcd_clear();
			lcd_send(1,lcd_lookup('T'));
			lcd_send(1,lcd_lookup(':'));
			sprintf(buffer,"%5d",t);
			for(int c = 0; c < 5; c++)
			lcd_send(1,lcd_lookup(buffer[c]));
			lcd_send(1,lcd_lookup('s'));
			lcd_send(1,lcd_lookup(' '));
			// round
			lcd_send(1,lcd_lookup('R'));
			lcd_send(1,lcd_lookup(':'));
			sprintf(buffer,"%5d",r);
			for(int c = 0; c < 5; c++)
				lcd_send(1,lcd_lookup(buffer[c]));
			lcd_send(1,lcd_lookup(' '));
			// sharp
			lcd_send(0,0b00000011);
			lcd_send(1,lcd_lookup('S'));
			lcd_send(1,lcd_lookup(':'));
			sprintf(buffer,"%5d",s);
			for(int c = 0; c < 5; c++)
				lcd_send(1,lcd_lookup(buffer[c]));
			lcd_send(1,lcd_lookup(' '));
			// horny
			lcd_send(1,lcd_lookup('H'));
			lcd_send(1,lcd_lookup(':'));
			sprintf(buffer,"%5d",h);
			for(int c = 0; c < 5; c++)
				lcd_send(1,lcd_lookup(buffer[c]));
			lcd_send(1,lcd_lookup(' '));
			break;
		case 6:
			// output time
			lcd_send(0,0b00000001);
			//lcd_clear();
			lcd_send(1,lcd_lookup('T'));
			lcd_send(1,lcd_lookup(':'));
			sprintf(buffer,"%5d",t);
			for(int c = 0; c < 5; c++)
			lcd_send(1,lcd_lookup(buffer[c]));
			lcd_send(1,lcd_lookup('s'));
			lcd_send(1,lcd_lookup(' '));
			// width
			lcd_send(0,0b00000011);
			lcd_send(1,lcd_lookup('a'));
			lcd_send(1,lcd_lookup('v'));
			lcd_send(1,lcd_lookup('g'));
			lcd_send(1,lcd_lookup('W'));
			lcd_send(1,lcd_lookup(':'));
			sprintf(buffer,"%5d",(int)(w*100));
			for(int c = 0; c < 3; c++)
				lcd_send(1,lcd_lookup(buffer[c]));
			lcd_send(1,lcd_lookup('.'));
			lcd_send(1,lcd_lookup(buffer[3]));
			lcd_send(1,lcd_lookup(buffer[4]));
			lcd_send(1,lcd_lookup('m'));
			lcd_send(1,lcd_lookup('s'));
			break;
		default:
			// output time
			lcd_send(0,0b00000001);
			lcd_send(1,lcd_lookup('T'));
			lcd_send(1,lcd_lookup(':'));
			sprintf(buffer,"%5d",t);
			for(int c = 0; c < 5; c++)
			lcd_send(1,lcd_lookup(buffer[c]));
			lcd_send(1,lcd_lookup('s'));
			lcd_send(1,lcd_lookup(' '));
			break;
	}	
}
