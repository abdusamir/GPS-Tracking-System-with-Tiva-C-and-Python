#include "UART0.h"
void UART0_init(uint32 baudrate,uint8 frame){
	double br;// we will use it for baud rate calculation
	SYSCTL_RCGCUART_R|=0x1;//clock of the uart 
	SYSCTL_RCGCGPIO_R|=0x01;//clock of the port
	while((SYSCTL_PRGPIO_R & 0x01)==0){}
		
	UART0_CTL_R=0;//to make sure uart is disabled & flush the fifo in case the uart was enabled and we want to change any thing in the configuration
	
	//now we will configure the port A pins 0 & 1 to be UART
	GPIO_PORTA_LOCK_R=0x4C4F434B;// to lock the port 
	GPIO_PORTA_CR_R|=0xFF;// to confirm 
	GPIO_PORTA_DEN_R|=0x03;
	GPIO_PORTA_AMSEL_R&=~(0x03);
	GPIO_PORTA_AFSEL_R|=0x03;
	GPIO_PORTA_PCTL_R=0x11;//put 1 in the 4 bits of A0 & A1
	
	//to configure the baud rate
	/*br=(16*10^6)/(16*baudrate);
	UART0_IBRD_R=(uint32)br;
	br-=(uint32)br;
	br=(br*64)+0.5;
	UART0_FBRD_R=(uint32)br;*/
		UART0_IBRD_R=	104;
		UART0_FBRD_R=11;
		
		
	UART0_CC_R=0;//just to make sure we use the system clock
	
	// to configure the frame 
	// we will allow the function to change the number of bits fron 5to8 but not nine
	// we will use 1stop bit and no parity and we will use the fifo
	setbit(UART0_LCRH_R,4);//to enable fifi which is bit 4
	if (5==frame){
		//5 bits means WLEN=00;
		clrbit(UART0_LCRH_R,5);//bit 5
		clrbit(UART0_LCRH_R,6);// bit 6
	}
	else if(6==frame){
		setbit(UART0_LCRH_R,5);
		clrbit(UART0_LCRH_R,6);
	}
	else if(7==frame){
		clrbit(UART0_LCRH_R,5);
		setbit(UART0_LCRH_R,6);
	}
	else{
		// we will make the default to be 8 bits
		setbit(UART0_LCRH_R,5);
		setbit(UART0_LCRH_R,6);
	}
	
	//now to enable the uart and enable TX & RX
	setbit(UART0_CTL_R,8);// to enable TX
	setbit(UART0_CTL_R,9);// to enable RX
	setbit(UART0_CTL_R,0);//to enable uart
}

void UART0_Trans_char(uint8 data){
	while (readbit(UART0_FR_R,5)==1){}
	UART0_DR_R=data;
}

void UART0_Trans_string(char *data){
	uint64 i=0;
	for(i=0;data[i]!=0;i++){
	while (readbit(UART0_FR_R,5)==1){}// if TXFF not = 1 or not full we will continue
	UART0_DR_R=data[i];
	}
	/*while ((*data)!=0){
		while (readbit(UART0_FR_R,5)==1){}// if TXFF not = 1 or not full we will continue
		UART0_DR_R=*data;
		(*data)++;
	}*/
}

uint8 UART0_Recieve_char(){
	while (readbit(UART0_FR_R,4)!=0){}// if RXFE not = 0 this means there is a data need to be read
	return (char) UART0_DR_R;
}
/*char* UART0_Revieve_string(char* data){
	char *data_recieved;
	while(*data!=0){
		while (readbit(UART0_FR_R,4)==0){}
		 *data_recieved=UART0_DR_R;
			data++;
			data_recieved++;
	}
	return data_recieved;
}*/
