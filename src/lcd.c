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
	DDRC = DDRC | 0b00110000; // pc4 rs, pc5 enable
	DDRD = DDRD | 0xFF; // data
	_delay_ms(15); //wait for power up
	
	//initialisation of LCD screen
	lcd_send(0,0b00011100); // function set (5x7 dot format, 2 line mode, 8-bit data)
	lcd_send(0,0b00110000); // Blink OFF, underline OFF, Display ON
	lcd_send(0,0b01100000); // character entry mode with increment and display shift OFF
    lcd_clear();
    lcd_return();
}

// clear screen
void lcd_clear(void)
{
    lcd_send(0,0b10000000); // clear screen
}

// return cursor
void lcd_return(void)
{
    lcd_send(0,0b01000000); // cursor return
}

// first row
void lcd_goto(uint8_t addr)
{
    lcd_send(0,0b00000001 | reverse[addr]); // this contraption reverses address and adds command bit
}

// sends data to LCD
void lcd_send(uint8_t rs, uint8_t data)
{
    // set enable and rs, send command
    PORTC = (rs << 4) | 0b00100000;
    PORTD = data;
	_delay_ms(1);
    // unset enable, wait
	PORTC = (rs << 4);
    PORTD = data;
	_delay_ms(1);
}

// outputs test string
void lcd_test(void)
{
    lcd_goto(0);
	lcd_send(1,0b01100011);
	lcd_send(1,0b00110101);
	lcd_send(1,0b00001101);
	lcd_send(1,0b00000100);
    lcd_goto(64);
	lcd_send(1,0b01111010);
	lcd_send(1,0b11111010);
	lcd_send(1,0b01111010);
}

// returns character code
uint8_t lcd_lookup(char symb)
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
void lcd_screen(int t, int n, int f, int r, int s, int h, int w)
{
    char buffer[5];
    uint8_t screen = t % 9;
	switch(screen)
	{
		case 0:
		case 1:
		case 2:
			// output time
			lcd_goto(0);
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
			lcd_goto(64);
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
		case 4:
		case 5:
			// output time
			lcd_goto(0);
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
			lcd_goto(64);
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
		case 7:
		case 8:
			// output time
			lcd_goto(0);
			//lcd_clear();
			lcd_send(1,lcd_lookup('T'));
			lcd_send(1,lcd_lookup(':'));
			sprintf(buffer,"%5d",t);
			for(int c = 0; c < 5; c++)
                lcd_send(1,lcd_lookup(buffer[c]));
			lcd_send(1,lcd_lookup('s'));
			lcd_send(1,lcd_lookup(' '));
			// width
			lcd_goto(64);
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
			break;
    }
}

// really, fuck the guy who wired the data bus backwards
static const uint8_t reverse[] = 
{
  0x00, 0x80, 0x40, 0xC0, 0x20, 0xA0, 0x60, 0xE0, 0x10, 0x90, 0x50, 0xD0, 0x30, 0xB0, 0x70, 0xF0, 
  0x08, 0x88, 0x48, 0xC8, 0x28, 0xA8, 0x68, 0xE8, 0x18, 0x98, 0x58, 0xD8, 0x38, 0xB8, 0x78, 0xF8, 
  0x04, 0x84, 0x44, 0xC4, 0x24, 0xA4, 0x64, 0xE4, 0x14, 0x94, 0x54, 0xD4, 0x34, 0xB4, 0x74, 0xF4, 
  0x0C, 0x8C, 0x4C, 0xCC, 0x2C, 0xAC, 0x6C, 0xEC, 0x1C, 0x9C, 0x5C, 0xDC, 0x3C, 0xBC, 0x7C, 0xFC, 
  0x02, 0x82, 0x42, 0xC2, 0x22, 0xA2, 0x62, 0xE2, 0x12, 0x92, 0x52, 0xD2, 0x32, 0xB2, 0x72, 0xF2, 
  0x0A, 0x8A, 0x4A, 0xCA, 0x2A, 0xAA, 0x6A, 0xEA, 0x1A, 0x9A, 0x5A, 0xDA, 0x3A, 0xBA, 0x7A, 0xFA,
  0x06, 0x86, 0x46, 0xC6, 0x26, 0xA6, 0x66, 0xE6, 0x16, 0x96, 0x56, 0xD6, 0x36, 0xB6, 0x76, 0xF6, 
  0x0E, 0x8E, 0x4E, 0xCE, 0x2E, 0xAE, 0x6E, 0xEE, 0x1E, 0x9E, 0x5E, 0xDE, 0x3E, 0xBE, 0x7E, 0xFE,
  0x01, 0x81, 0x41, 0xC1, 0x21, 0xA1, 0x61, 0xE1, 0x11, 0x91, 0x51, 0xD1, 0x31, 0xB1, 0x71, 0xF1,
  0x09, 0x89, 0x49, 0xC9, 0x29, 0xA9, 0x69, 0xE9, 0x19, 0x99, 0x59, 0xD9, 0x39, 0xB9, 0x79, 0xF9, 
  0x05, 0x85, 0x45, 0xC5, 0x25, 0xA5, 0x65, 0xE5, 0x15, 0x95, 0x55, 0xD5, 0x35, 0xB5, 0x75, 0xF5,
  0x0D, 0x8D, 0x4D, 0xCD, 0x2D, 0xAD, 0x6D, 0xED, 0x1D, 0x9D, 0x5D, 0xDD, 0x3D, 0xBD, 0x7D, 0xFD,
  0x03, 0x83, 0x43, 0xC3, 0x23, 0xA3, 0x63, 0xE3, 0x13, 0x93, 0x53, 0xD3, 0x33, 0xB3, 0x73, 0xF3, 
  0x0B, 0x8B, 0x4B, 0xCB, 0x2B, 0xAB, 0x6B, 0xEB, 0x1B, 0x9B, 0x5B, 0xDB, 0x3B, 0xBB, 0x7B, 0xFB,
  0x07, 0x87, 0x47, 0xC7, 0x27, 0xA7, 0x67, 0xE7, 0x17, 0x97, 0x57, 0xD7, 0x37, 0xB7, 0x77, 0xF7, 
  0x0F, 0x8F, 0x4F, 0xCF, 0x2F, 0xAF, 0x6F, 0xEF, 0x1F, 0x9F, 0x5F, 0xDF, 0x3F, 0xBF, 0x7F, 0xFF
};
