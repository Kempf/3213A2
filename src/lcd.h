#ifndef _LCD_H_
#define _LCD_H_

void lcd_init(void);
void lcd_clear(void);
void lcd_send(unsigned char rs, unsigned char data);
void lcd_test(void);

#endif