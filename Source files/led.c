#include "led.h"
void is_distance_equal_100(float distance){
	portF_init();
	if(distance>=100) setbit(GPIO_PORTF_DATA_R,1);//turn on red led
	else clrbit(GPIO_PORTF_DATA_R,1);
}
