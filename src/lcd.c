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
#include <avr/delay.h>
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