#include "ports.h"
void portF_init(void){
	SYSCTL_RCGCGPIO_R|=0x20;
	while((SYSCTL_PRGPIO_R & 0x20)==0){}
	GPIO_PORTF_LOCK_R=0x4C4F434B;
	GPIO_PORTF_CR_R|=0x1F;
	//////////////////////////////
	GPIO_PORTF_AFSEL_R&=~(0x1F);
	GPIO_PORTF_PCTL_R&=~(0x1F);
	GPIO_PORTF_DEN_R|=0x1F;
	GPIO_PORTF_AMSEL_R&=~(0x1F);
	GPIO_PORTF_DIR_R|=0x0E;
	GPIO_PORTF_PUR_R|=0x11;
}
void portB_init(void){
	// i will use this port for lcd and i configure the direction of pins in lcd driver
	SYSCTL_RCGCGPIO_R|=0x02;
	while((SYSCTL_PRGPIO_R & 0x02)==0){}
	GPIO_PORTB_LOCK_R=0x4C4F434B;//unlock commit register
	GPIO_PORTB_CR_R|=0xFF;//we will use all pins of this port
	//////////////////////////////
	GPIO_PORTB_AFSEL_R&=~(0xFF);//clear all bits we will use it as GPIO
	GPIO_PORTB_PCTL_R&=~(0xFF);//clear all bits because we will use the pins of this port as digital pins
	GPIO_PORTB_DEN_R|=0xFF;//enable all bits as digital pins
	GPIO_PORTB_AMSEL_R&=~(0xFF);//clear all bits we don't want analog pins
	GPIO_PORTB_DIR_R|=0xFF;//fc
	GPIO_PORTB_PUR_R&=~(0xFF);
}