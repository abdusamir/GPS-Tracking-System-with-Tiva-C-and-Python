
#ifndef macro
#define macro
#include <stdint.h>
#include "C:/Keil/EE319Kware/inc/tm4c123gh6pm.h"

#define setbit(reg,bit) (reg|=(1<<bit)) 
#define clrbit(reg,bit) (reg&=~(1<<bit))
#define togbit(reg,bit) (reg^=(1<<bit))
#define readbit(reg,bit) ((reg>>bit)&1)

typedef unsigned char uint8 ;
typedef unsigned short uint16 ;
typedef unsigned int uint32 ;
typedef unsigned long long uint64 ;

#endif