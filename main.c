#include <REG8051_H.h>
//
#define RS_lcd P3_7
#define RW_lcd P3_6
#define E_lcd P3_5
#define DATA_lcd P2
//
static unsigned char  lcd_num;
static char lcd_line; //bit
//
void lcd_wait();
void set_lcd();
void lcd_setup();
void lcd_clear();
void lcd_write();
void lcd_home();
void lcd_line2();
//
void main() {
	lcd_setup();
	char helloWorld[] = ["Hello World"];
	char index;
  for(index = 0;index<11;index++) {
     lcd_write(helloWorld[index]);
}
	while(1);

}
//
void lcd_write(unsigned char lcd_data) {
    set_lcd(1,lcd_data);

    if(lcd_num == 0x0f) {
        if(lcd_line)
        lcd_home();
        else
        lcd_line2();

    }
    else
        lcd_num++;

}
//
void lcd_wait() {
	unsigned short lcd_t1;
	for(lcd_t1=300;lcd_t1 != 0;lcd_t1--);
}
//
void set_lcd(char char_command,unsigned char lcd_d) {
	RW_lcd = 0;
	E_lcd = 1;
	RS_lcd = char_command; 
	DATA_lcd = lcd_d;
	E_lcd = 0;
	lcd_wait();
	E_lcd = 1;
	lcd_wait();

}
//
void lcd_setup() {
	unsigned char lcd_i;
	lcd_line = 0;
	lcd_num = 0;
	for(lcd_i = 0;lcd_i<10;lcd_i++);
	lcd_wait();
}
//
void lcd_clear() {
	set_lcd(0,0x01);
}
//
void lcd_home() {
    lcd_num = 0;
    lcd_line = 0;
    set_lcd(0,0x02);
}
//
void lcd_line2(){
    lcd_num = 0;
    lcd_line = 1;
    set_lcd(0,0xc0);

}
//