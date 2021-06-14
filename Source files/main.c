#include "zm_macros.h"
#include "systick_timer.h"
#include "ports.h"
#include "lcd.h"
#include "UART0.h"
#include "UART7.h"
#include "led.h"
#include "cmath"
#include "GPS.h"
#include "stdlib.h"
#include "math.h"
#include "stdio.h"
#include "rtl.h"
#include "led.h"
#define MAX_SIZE 1000
#define My_PI 3.14159265358979323864

void SystemInit(){}
int counter =0;
uint8 flag=0;
float distance=0;
float logg[1000];
float lat[1000];
char data;
char lat_c[15];
char log_c[15];
char input;
int read_data();
int i=0;
int j=0;
int k=0;
int  dd;
float ss;
float abs_log=0;
float abs_lat=0;
float d_lat=0;
float d_log=0;
double R=6731;
float a=0;
float d=0;
float c=0;
float logg_f1=0;
float lat_f1=0;
float logg_f2=0;
float lat_f2=0;
//FILE *fptr;
float deg_to_rad(float deg){
	return deg*(My_PI/180);
}
void reverse(char* str, int len)
{
    int i = 0, j = len - 1, temp;
    while (i < j) {
        temp = str[i];
        str[i] = str[j];
        str[j] = temp;
        i++;
        j--;
    }
}
int intToStr(int x, char str[], int d)
{
    int i = 0;
    while (x) {
        str[i++] = (x % 10) + '0';
        x = x / 10;
    }
  
    // If number of digits required is more, then
    // add 0s at the beginning
    while (i < d)
        str[i++] = '0';
  
    reverse(str, i);
    str[i] = '\0';
    return i;
}
void ftoa(float n, char* res, int afterpoint)
{
    // Extract integer part
    int ipart = (int)n;
  
    // Extract floating part
    float fpart = n - (float)ipart;
  
    // convert integer part to string
    int i = intToStr(ipart, res, 0);
  
    // check for display option after point
    if (afterpoint != 0) {
        res[i] = '.'; // add dot
  
        // Get the value of fraction part upto given no.
        // of points after dot. The third parameter 
        // is needed to handle cases like 233.007
        fpart = fpart * pow(10, afterpoint);
  
        intToStr((int)fpart, res + i + 1, afterpoint);
    }
}
float get_distance_meters(){
	if(counter==1)
		return 0;
	lat_f2=lat[counter-1];
	lat_f1=lat[counter-2];
	logg_f2=logg[counter-1];
	logg_f1=logg[counter-2];
	lat_f2=deg_to_rad(lat_f2);
	lat_f1=deg_to_rad(lat_f1);
	logg_f2=deg_to_rad(logg_f2);
	logg_f1=deg_to_rad(lat_f1);
	
	R=6731;
	d_lat=lat_f2-lat_f1;
	d_log=logg_f2-logg_f1;
	a=pow(sin(d_lat/2),2)*cos(lat_f1)*cos(lat_f2)*pow(sin(d_log/2),2);
	c=2*asin(sqrt(a));
	d=R*c;
	return d*1000.0;
}
	
int main(){
//fptr= fopen("locations.csv","w+");
//if (fptr!=NULL) {fprintf(fptr,"Latitude,Longitude\n");
portB_init();
lcd_init();
UART0_init(9600,8);
UART7_init(9600,8);
lcd_comm(0x80);
lcd_string("Distance= ");
UART0_Trans_string("Latitude,Longitude\n");
wait_ms(2000);
	while(1){
		input=UART7_Recieve_char();
		
		if(input!='$')
			continue;
		input=UART7_Recieve_char();
		
		if(input!='G')
			continue;
		input=UART7_Recieve_char();
		
		if(input!='P')
			continue;
		input=UART7_Recieve_char();
		
		if(input!='G')
			continue;
		input=UART7_Recieve_char();
		
		if(input!='G')
			continue;
		input=UART7_Recieve_char();
		
		if(input!='A')
			continue;
		input=UART7_Recieve_char();
		
		if(input!=',')
			continue;
		input=UART7_Recieve_char();
		
		while(input!=',')
			input=UART7_Recieve_char();
		
		input=UART7_Recieve_char();
		
		for(i=0;input!=',';i++){
			lat_c[i]=input;
			input=UART7_Recieve_char();
			
		}
		input=UART7_Recieve_char();
		
		input=UART7_Recieve_char();
		
		input=UART7_Recieve_char();
		
		for(k=0;input!=',';k++){
			log_c[k]=input;
			input=UART7_Recieve_char();
			
		}
		logg[counter]=(float)atof(log_c);
		logg[counter]/=100;
		ss=logg[counter];
		logg[counter]=(int) logg[counter];
		ss=ss-logg[counter];
		ss/=0.6;
		logg[counter]+=ss;
		lat[counter]=(float) atof(lat_c);
		lat[counter]/=100;
		ss=lat[counter];
		lat[counter]=(int) lat[counter];
		ss=ss-lat[counter];
		ss/=0.6;
		lat[counter]+=ss;
		if(j==0||j%5==0){
		counter++;
		distance+=get_distance_meters();
		lcd_comm(0xC0);
		lcd_num(distance);
		ftoa(lat[counter-1],lat_c,8);
		ftoa(logg[counter-1],log_c,8);
		UART0_Trans_string(lat_c);
		UART0_Trans_char(',');
		UART0_Trans_string(log_c);
		UART0_Trans_char('\n');
		}
		j++;
		
		is_distance_equal_100(distance);
		//if(distance>=10&&!flag){
		//	for(j=0;j<counter;j++)
		//	{
		//		fprintf(fptr,"%f,%f",lat[j],logg[j]);
		//		fclose(fptr);
		//	}}
		//	flag=1;
		//}
		//if (counter>=20)
				//fclose(fptr);
		//lcd_comm(0x80);
		//lcd_string("Lat:");
		//lcd_num(lat[counter-1]);
		//lcd_comm(0xC0);
		//lcd_string("Long:");
		//lcd_num(logg[counter-1]);
		
	}
}
	
	
	
	
	
	
	
	
	
	
	
	
	
	/*int main(){

	portB_init();
	lcd_init();
	UART0_init(9600,8);
	UART7_init(9600,8);
	lcd_comm(0x80);

	//lcd_string("The distance is ");
  //UART0_Trans_string("The Distance = ");
	//wait_ms(2000);
	UART7_Trans_char('c');
	lcd_num(distance);
	wait_ms(4000);
	while (1){
		//data=UART7_Recieve_char();
		//UART0_Trans_char(data);
		//read_location(logg,lat,&counter);
		//lcd_comm(0xC0);
		//get_distance(logg,lat,counter,&distance);
		//lcd_num(distance);
		//lcd_comm(0xC0);
		//lcd_char(data);
		
	}
}*/

/*uint8 i=1;
	portF_init();
	while(1){
		for (i=1;i<4;i++){
			setbit(GPIO_PORTF_DATA_R,i);
			wait_ms(1000);
			clrbit(GPIO_PORTF_DATA_R,i);
		}
		for (i=1;i<4;i++){
			clrbit(GPIO_PORTF_DATA_R,i);
		}
	}*/

/*
portF_init();
	lcd_init();
	UART0_init(9600,8);
	UART7_init(9600,8);
	while(1){
	wait_ms(1000);
	lcd_char('z');
	lcd_string("manga");
	uint8 c=UART7_Recieve_char();
	UART0_Trans_char('g');
	UART0_Trans_string("hello");
	}
*/
	/*
		//lcd_char('c');
		//lcd_char('A');
		uint8 i=0;
		for (i=0;i<60;i++){
		lcd_comm(0xC0);
		//lcd_num((16.5+15));
			lcd_num(i);
			wait_ms(1000);
		}*/
		
		/*	uint8 distance=100;
	portB_init();
	lcd_init();
	lcd_comm(0x80);
	lcd_string("The Distance Is");
	lcd_comm(0xC0);
	lcd_num(15.5);*/
	