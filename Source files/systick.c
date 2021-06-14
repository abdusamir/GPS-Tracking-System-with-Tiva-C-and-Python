#include "F:/mpproject/zm_macros.h"
void wait_ms(uint64 delay){
	uint64 i;
	NVIC_ST_RELOAD_R =15999;
	NVIC_ST_CURRENT_R =0;
	NVIC_ST_CTRL_R |=0x5;
	if (delay!=0)
	while(readbit(NVIC_ST_CTRL_R,16)==0);
	for ( i=1;i<delay;i++){
		while(readbit(NVIC_ST_CTRL_R,16)==0);
	}
	NVIC_ST_CTRL_R &=~(0x5);
}
void systic_init(uint32 value){
	NVIC_ST_RELOAD_R =value;
	NVIC_ST_CURRENT_R =0;
	NVIC_ST_CTRL_R |=0x5;
}