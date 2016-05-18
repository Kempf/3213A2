#ifndef _LCD_H_
#define _LCD_H_

void lcd_init(void);
void lcd_clear(void);
void lcd_send(unsigned char rs, unsigned char data);
void lcd_test(void);
unsigned char lcd_lookup(char symb);
void lcd_screen(int tms, int n, float f, int r, int s, int h, float w);

#endif
