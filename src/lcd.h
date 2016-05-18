#ifndef _LCD_H_
#define _LCD_H_

void lcd_init(void);
void lcd_clear(void);
void lcd_return(void);
void lcd_goto(uint8_t addr);
void lcd_send(uint8_t rs, uint8_t data);
void lcd_test(void);
uint8_t lcd_lookup(char symb);
void lcd_screen(int s, int n, int f, int r, int s, int h, int w);

#endif
