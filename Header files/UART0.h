#ifndef uart0
#define uart0
#include "zm_macros.h"
#include "systick_timer.h"
void UART0_init(uint32 baudrate,uint8 frame);
void UART0_Trans_char(uint8 data);
void UART0_Trans_string(char *data);
uint8 UART0_Recieve_char();
#endif