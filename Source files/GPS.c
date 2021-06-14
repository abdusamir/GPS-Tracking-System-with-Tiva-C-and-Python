#include "GPS.h"
#include "stdlib.h"
#include "UART7.h"

void read_location(float logg[],float lat[],int *counter)
{
char input;
char log_c[15];
char lat_c[15];
int i=0;
int j=0;
float logg_deg;
float lat_deg;
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
        while(input!=',')  // skip first no (time)
        {
            input=UART7_Recieve_char();
        }
        input=UART7_Recieve_char();
        for(i=0;input!=',';i++){
            lat_c[i]=input;
            input=UART7_Recieve_char();
        }
        input=UART7_Recieve_char();
        while(input!=',')
        {
            input=UART7_Recieve_char();
        }
        input=UART7_Recieve_char();
        for(j=0;input!=',';j++){
            log_c[j]=input;
            input=UART7_Recieve_char();
        }
        break;
    }
    logg[*counter]=(float)(atof(log_c));
    lat[*counter]=(float)(atof(lat_c));
    logg[*counter]=logg[*counter]/100.00;
		logg_deg =logg[*counter]-((int)logg[*counter]);
    logg[*counter]=(int) logg[*counter];
    logg_deg/=0.6;
    logg[*counter]+=logg_deg;
    lat[*counter]=lat[*counter]/100.00;
		lat_deg=lat[*counter]-((int)lat[*counter]);
    lat[*counter]=(int) lat[*counter];
    lat_deg/=0.6;
    lat[*counter]+=lat_deg;
    *counter+=1;
}
void get_distance(float logg[],float lat[],int counter,float *distance){
float abs_log=0;
    float abs_lat=0;
    if(counter ==1){
        *distance =0;
    }
    else{
    abs_log=abs(logg[counter-1])-abs(logg[counter-2]);
    abs_lat=abs(lat[counter-1])-abs(logg[counter-2]);
    *distance+=(float)(sqrt(pow(abs_log,2)+pow(abs_lat,2)));
    }


}
