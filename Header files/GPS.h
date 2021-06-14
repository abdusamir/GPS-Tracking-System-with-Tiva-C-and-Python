#ifndef GPS_H
#define GPS_H
#include "math.h"
#include "UART7.h"

void read_location(float logg[],float lat[],int *counter);
void get_distance(float logg[],float lat[],int counter,float *distance);
#endif // GPS_H
