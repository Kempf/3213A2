#ifndef _LCD_H_
#define _LCD_H_

void lcd_init(void);
void lcd_clear(void);
void lcd_return(void);
void lcd_goto(unsigned char addr);
void lcd_send(unsigned char rs, unsigned char data);
void lcd_test(void);
unsigned char lcd_lookup(char symb);
void lcd_screen(int s, int n, int f, int r, int s, int h, int w);

#endif
