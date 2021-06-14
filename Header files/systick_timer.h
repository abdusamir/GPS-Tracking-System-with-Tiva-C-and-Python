#ifndef systick_timer
#define systick_timer
#include "zm_macros.h"
void wait_ms(uint64 delay);
void systic_init(uint32 value);
#endif