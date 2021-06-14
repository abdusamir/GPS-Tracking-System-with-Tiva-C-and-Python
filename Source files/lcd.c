#include "lcd.h"
void lcd_init(void){
	lcd_port;
	/*wait_ms(5000);
	lcd_comm(0x03);
	lcd_comm(0x02);//enable 4 bit mode
		wait_ms(50);
	lcd_comm(0x28);//to write on 2 lines
	wait_ms(50);
	lcd_comm(0x06);//increment cursor
	wait_ms(50);
	lcd_comm(0x0E);//display on and cursor on
	wait_ms(50);
	lcd_comm(0x01);//to clear the display //tbd2 3la ndafa
	wait_ms(50);*/
	wait_ms(50);
	lcd_comm(0x03);
	wait_ms(1);
	lcd_comm(0x06);//increment cursor
	wait_ms(1);
	lcd_comm(0x02);//enable 4 bit mode
	wait_ms(1);
	lcd_comm(0x28);//to write on 2 lines
	wait_ms(1);
	//lcd_comm(0x8);
	//wait_ms(1);
	lcd_comm(0x0E);//display on and cursor on
	wait_ms(1);
	lcd_comm(0x01);//to clear the display //tbd2 3la ndafa
	wait_ms(1);
}
void lcd_comm(unsigned char com){
	RS(0);
	D4(readbit(com,4));
	D5(readbit(com,5));
	D6(readbit(com,6));
	D7(readbit(com,7));
	EN(1);
	wait_ms(1);
	EN(0);
	wait_ms(1);
	D4(readbit(com,0));
	D5(readbit(com,1));
	D6(readbit(com,2));
	D7(readbit(com,3));
	EN(1);
	wait_ms(1);
	EN(0);
	wait_ms(1);
}
void lcd_char(unsigned char data){
	RS(1);
	D4(readbit(data,4));
	D5(readbit(data,5));
	D6(readbit(data,6));
	D7(readbit(data,7));
	EN(1);
	wait_ms(1);
	EN(0);
	wait_ms(1);
	D4(readbit(data,0));
	D5(readbit(data,1));
	D6(readbit(data,2));
	D7(readbit(data,3));
	EN(1);
	wait_ms(1);
	EN(0);
	wait_ms(1);
}

void lcd_string(char *c){
	uint64 i=0;
	for (i=0;c[i]!='\0';i++)
	{
		RS(1);
		//RW(0);
		D7(readbit(c[i],7));
		D6(readbit(c[i],6));
		D5(readbit(c[i],5));
		D4(readbit(c[i],4));
		EN(1);
		wait_ms(1);
		EN(0);
		wait_ms(1);
		D7(readbit(c[i],3));
		D6(readbit(c[i],2));
		D5(readbit(c[i],1));
		D4(readbit(c[i],0));
		EN(1);
		wait_ms(1);
		EN(0);
		wait_ms(1);
	}
}

void lcd_num(float num){
	
	signed int ar[16];//equal to the number of columns
	signed char i=0;
	uint32 a=(uint32)num;
	float b=num-a;
//for the integer par
    if (a==0)
    {
	    lcd_char('0');
    }
	else{
	for (i=0;a!=0;i++)
	{
		ar[i]=a%10;
		a/=10;
	}
	i--;
	//showing the integer part
	for ( ;i>=0;i--)
	{
		RS(1);
		//RW(0);
		D7(readbit((ar[i]+48),7));
		D6(readbit((ar[i]+48),6));
		D5(readbit((ar[i]+48),5));
		D4(readbit((ar[i]+48),4));
		EN(1);
		wait_ms(1);
		EN(0);
		wait_ms(1);
		D7(readbit((ar[i]+48),3));
		D6(readbit((ar[i]+48),2));
		D5(readbit((ar[i]+48),1));
		D4(readbit((ar[i]+48),0));
		EN(1);
		wait_ms(1);
		EN(0);
		wait_ms(1);
	}		
//for the float part
	if(b!=0){
	a=b*100000;
	i=0;
	for( ;a!=0;i++){
	ar[i]=a%10;
	a/=10;
	}	
	}	
	ar[i]=-2;//for the '.' dot
//showing the float part
	for ( ;i>=0;i--)
	{
		RS(1);
		//RW(0);
		D7(readbit((ar[i]+48),7));
		D6(readbit((ar[i]+48),6));
		D5(readbit((ar[i]+48),5));
		D4(readbit((ar[i]+48),4));
		EN(1);
		wait_ms(1);
		EN(0);
		wait_ms(1);
		D7(readbit((ar[i]+48),3));
		D6(readbit((ar[i]+48),2));
		D5(readbit((ar[i]+48),1));
		D4(readbit((ar[i]+48),0));
		EN(1);
		wait_ms(1);
		EN(0);
		wait_ms(1);
	}
	}	
}	
