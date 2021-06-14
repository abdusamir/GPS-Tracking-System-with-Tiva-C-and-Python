#ifndef lcd
#define lcd

#include "zm_macros.h"
#include "systick_timer.h"
#include "ports.h"
//we will use portb to be the lcd port and to make .c file doesn't depend on the hardware configuration just change the port name in .h file

#define lcd_port GPIO_PORTB_DIR_R|=0xFF;//to make bits from 2 to 7 as output

/*
VCC>>5V
VSS>>GND
ANODE>>5V
CATHOD>>0V
RW>>always 0 so GND
RS>>b2
EN>>b3
D4>>b4
D5>>b5
D6>>b6
D7>>b7
*/

#define RS(x) if(1==x) setbit(GPIO_PORTB_DATA_R,2); else clrbit(GPIO_PORTB_DATA_R,2);
//#define RW(x) if(1==x) setbit(GPIO_PORTB_DATA_R,2); else clrbit(GPIO_PORTB_DATA_R,2);
#define EN(x) if(1==x) setbit(GPIO_PORTB_DATA_R,3); else clrbit(GPIO_PORTB_DATA_R,3);
#define D4(x) if(1==x) setbit(GPIO_PORTB_DATA_R,4); else clrbit(GPIO_PORTB_DATA_R,4);
#define D5(x) if(1==x) setbit(GPIO_PORTB_DATA_R,5); else clrbit(GPIO_PORTB_DATA_R,5);
#define D6(x) if(1==x) setbit(GPIO_PORTB_DATA_R,6); else clrbit(GPIO_PORTB_DATA_R,6);
#define D7(x) if(1==x) setbit(GPIO_PORTB_DATA_R,7); else clrbit(GPIO_PORTB_DATA_R,7);

//lcd functions
void lcd_init(void);
void lcd_comm(unsigned char com);
void lcd_char(unsigned char data);
void lcd_num(float num);
void lcd_string(char *c);


#endif