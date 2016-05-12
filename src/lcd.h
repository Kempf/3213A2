#ifndef _LCD_H_
#define _LCD_H_

void lcd_init(void);
void lcd_clear(void);
void lcd_send(unsigned char rs, unsigned char data);
void lcd_test(void);
unsigned char lcd_lookup(char symb);
void lcd_screen1(int t, int n, int f);
void lcd_screen2(int t, int r, int s, int h);
void lcd_screen3(int t, int w);

#endif