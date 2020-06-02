#include "F:/Keil/EE319Kware/inc/tm4c123gh6pm.h"
#include "UART_Int.h"
#include "stdint.h"

void UART_Init(u8 UART){
	
	switch(UART){

		case UART0:
			
			SYSCTL_RCGCUART_R |= 0x0001;
			UART0_CTL_R &= ~0x0001;
			UART0_IBRD_R = 43;
			UART0_FBRD_R = 26;
			UART0_LCRH_R = 0x0070;
			UART0_CTL_R = 0x0301;
		
			GPIO_PORTA_LOCK_R = 0x4C4F434B;
      GPIO_PORTA_CR_R=0xFF; //enable registers writing
		
			GPIO_PORTA_AFSEL_R |= 0x03;
			GPIO_PORTA_PCTL_R |= (GPIO_PORTB_PCTL_R & 0xFFFFFF00)+0x00000011;
		
			GPIO_PORTA_DEN_R |= 0x03;
			GPIO_PORTA_AMSEL_R &= ~0x03;
			break;

		case UART1:

			SYSCTL_RCGCUART_R |= 0x0002;
			UART1_CTL_R &= ~0x0001;
			UART1_IBRD_R = 43;
			UART1_FBRD_R = 26;
			UART1_LCRH_R = 0x0070;
			UART1_CTL_R = 0x0301;
		
			GPIO_PORTB_LOCK_R = 0x4C4F434B;
      GPIO_PORTB_CR_R=0xFF; //enable registers writing
		
			GPIO_PORTB_AFSEL_R |= 0x03;
			GPIO_PORTB_PCTL_R |= (GPIO_PORTB_PCTL_R & 0xFFFFFF00)+0x00000011;
		
			GPIO_PORTB_DEN_R |= 0x03;
			GPIO_PORTB_AMSEL_R &= ~0x03;
			break;

		case UART2:

			SYSCTL_RCGCUART_R |= 0x0004;
			UART2_CTL_R &= ~0x0002;
			UART2_IBRD_R = 43;
			UART2_FBRD_R = 26;
			UART2_LCRH_R = 0x0070;
			UART2_CTL_R = 0x0301;
		
			GPIO_PORTD_LOCK_R = 0x4C4F434B;
      GPIO_PORTD_CR_R=0xFF; //enable registers writing
		
			GPIO_PORTD_AFSEL_R |= 0xC0; //pin 6 , 7
			GPIO_PORTD_PCTL_R |= (GPIO_PORTB_PCTL_R & 0xFFFFFF00)+0x00000011;
		
			GPIO_PORTD_DEN_R |= 0xC0;
			GPIO_PORTD_AMSEL_R &= ~0xC0;
			break;
		
		case UART3:

			SYSCTL_RCGCUART_R |= 0x0008;
			UART3_CTL_R &= ~0x0002;
			UART3_IBRD_R = 43;
			UART3_FBRD_R = 26;
			UART3_LCRH_R = 0x0070;
			UART3_CTL_R = 0x0301;
		
			GPIO_PORTC_LOCK_R = 0x4C4F434B;
      GPIO_PORTC_CR_R=0xFF; //enable registers writing
		
			GPIO_PORTC_AFSEL_R |= 0xC0; //pin 6 , 7
			GPIO_PORTC_PCTL_R |= (GPIO_PORTB_PCTL_R & 0xFFFFFF00)+0x00000011;
		
			GPIO_PORTC_DEN_R |= 0xC0;
			GPIO_PORTC_AMSEL_R &= ~0xC0;
			break;
		
		case UART4:

			SYSCTL_RCGCUART_R |= 0x0010;
			UART4_CTL_R &= ~0x0002;
			UART4_IBRD_R = 43;
			UART4_FBRD_R = 26;
			UART4_LCRH_R = 0x0070;
			UART4_CTL_R = 0x0301;
		
			GPIO_PORTC_LOCK_R = 0x4C4F434B;
      GPIO_PORTC_CR_R=0xFF; //enable registers writing
		
			GPIO_PORTC_AFSEL_R |= 0x30; //pin 4,5
			GPIO_PORTC_PCTL_R |= (GPIO_PORTB_PCTL_R & 0xFFFFFF00)+0x00000011;
		
			GPIO_PORTC_DEN_R |= 0x30;
			GPIO_PORTC_AMSEL_R &= ~0x30;
			break;
		
		case UART5:

			SYSCTL_RCGCUART_R |= 0x0020;
			UART5_CTL_R &= ~0x0002;
			UART5_IBRD_R = 43;
			UART5_FBRD_R = 26;
			UART5_LCRH_R = 0x0070;
			UART5_CTL_R = 0x0301;
		
			GPIO_PORTE_LOCK_R = 0x4C4F434B;
      GPIO_PORTE_CR_R=0xFF; //enable registers writing
		
			GPIO_PORTE_AFSEL_R |= 0x30; //pin 4,5
			GPIO_PORTE_PCTL_R |= (GPIO_PORTB_PCTL_R & 0xFFFFFF00)+0x00000011;
		
			GPIO_PORTE_DEN_R |= 0x30;
			GPIO_PORTE_AMSEL_R &= ~0x30;
			break;
		
		case UART6:

			SYSCTL_RCGCUART_R |= 0x0040;
			UART6_CTL_R &= ~0x0002;
			UART6_IBRD_R = 43;
			UART6_FBRD_R = 26;
			UART6_LCRH_R = 0x0070;
			UART6_CTL_R = 0x0301;
		
			GPIO_PORTD_LOCK_R = 0x4C4F434B;
      GPIO_PORTD_CR_R=0xFF; //enable registers writing
		
			GPIO_PORTD_AFSEL_R |= 0x30; //pin 4,5
			GPIO_PORTD_PCTL_R |= (GPIO_PORTB_PCTL_R & 0xFFFFFF00)+0x00000011;
		
			GPIO_PORTD_DEN_R |= 0x30;
			GPIO_PORTD_AMSEL_R &= ~0x30;
			break;
		
		case UART7:

			SYSCTL_RCGCUART_R |= 0x0080;
			UART7_CTL_R &= ~0x0002;
			UART7_IBRD_R = 43;
			UART7_FBRD_R = 26;
			UART7_LCRH_R = 0x0070;
			UART7_CTL_R = 0x0301;
		
			GPIO_PORTE_LOCK_R = 0x4C4F434B;
      GPIO_PORTE_CR_R=0xFF; //enable registers writing
		
			GPIO_PORTE_AFSEL_R |= 0x03; //pin 0,1
			GPIO_PORTE_PCTL_R |= (GPIO_PORTB_PCTL_R & 0xFFFFFF00)+0x00000011;
		
			GPIO_PORTE_DEN_R |= 0x03;
			GPIO_PORTE_AMSEL_R &= ~0x03;
			break;
		}

		
}



/*void UART_ParityMode(u8 parity){

	parity = parity << 4;
	UCSRC &= 0xCF;
	UCSRC |= parity;

}

void UART_StopBit(u8 stopBit){

	stopBit = stopBit << 3;
	UCSRC &= 0xF7;
	UCSRC |= stopBit;

}

void UART_CharcterSize(u8 size){

	switch(size){

	case DATA_9_BITS:

		UCSRC |= 0x06;
		UCSRB |= 0x04;
		break;

	default:

		size = size << 1;
		UCSRC &= 0xF9;
		UCSRC |= size;
		break;
	}
}*/


u8 UART_FIFOFullFlag(u8 UART){

			switch(UART){

		case UART0:
			
			if((UART0_FR_R & 0x0020) !=0)	return 1;
			else return 0;
		
		case UART1:

			if((UART1_FR_R & 0x0020) !=0)	return 1;
			else return 0;

		case UART2:

			if((UART2_FR_R & 0x0020) !=0)	return 1;
			else return 0;
		
		case UART3:

			if((UART3_FR_R & 0x0020) !=0)	return 1;
			else return 0;
		
		case UART4:

			if((UART4_FR_R & 0x0020) !=0)	return 1;
			else return 0;
		
		case UART5:

			if((UART5_FR_R & 0x0020) !=0)	return 1;
			else return 0;
		
		case UART6:

			if((UART6_FR_R & 0x0020) !=0)	return 1;
			else return 0;
		
		case UART7:

			if((UART7_FR_R & 0x0020) !=0)	return 1;
			else return 0;		
		}
	return 2;
}


u8 UART_FIFOEmptyFlag(u8 UART){

			switch(UART){

		case UART0:
			
			if((UART0_FR_R & 0x0010) !=0)	return 1;
			else return 0;

		case UART1:

			if((UART1_FR_R & 0x0010) !=0)	return 1;
			else return 0;

		case UART2:

			if((UART2_FR_R & 0x0010) !=0)	return 1;
			else return 0;
		
		case UART3:

			if((UART3_FR_R & 0x0010) !=0)	return 1;
			else return 0;
		
		case UART4:

			if((UART4_FR_R & 0x0010) !=0)	return 1;
			else return 0;
		
		case UART5:

			if((UART5_FR_R & 0x0010) !=0)	return 1;
			else return 0;
		
		case UART6:

			if((UART6_FR_R & 0x0010) !=0)	return 1;
			else return 0;
		
		case UART7:

			if((UART7_FR_R & 0x0010) !=0)	return 1;
			else return 0;		
		}
	return 2;
}

void UART_SetUDR(u8 UART , u8 value){

		switch(UART){

		case UART0:
			while(UART_FIFOFullFlag(UART));
			UART0_DR_R = value;
			break;

		case UART1:
			while(UART_FIFOFullFlag(UART));
			UART1_DR_R = value;
			break;

		case UART2:
			while(UART_FIFOFullFlag(UART));
			UART2_DR_R = value;
			break;
		
		case UART3:
			while(UART_FIFOFullFlag(UART));
			UART3_DR_R = value;
			break;
		
		case UART4:
			while(UART_FIFOFullFlag(UART));
			UART4_DR_R = value;
			break;
		
		case UART5:
			while(UART_FIFOFullFlag(UART));
			UART5_DR_R = value;
			break;
		
		case UART6:
			while(UART_FIFOFullFlag(UART));
			UART6_DR_R = value;
			break;
		
		case UART7:
			while(UART_FIFOFullFlag(UART));
			UART7_DR_R = value;
			break;
		}
}


void UART_SetUDRString(u8 UART , u8* value){

		u8 i=0;
		while(value[i] != '\0')
			UART_SetUDR(UART , value[i]);
}


u8 UART_getUDR(u8 UART){

		switch(UART){

		case UART0:
			while(UART_FIFOEmptyFlag(UART));
			return UART0_DR_R;

		case UART1:
			while(UART_FIFOEmptyFlag(UART));
			return UART1_DR_R;

		case UART2:
			while(UART_FIFOEmptyFlag(UART));
			return UART2_DR_R;
		
		case UART3:
			while(UART_FIFOEmptyFlag(UART));
			return UART3_DR_R;
		
		case UART4:
			while(UART_FIFOEmptyFlag(UART));
			return UART4_DR_R;
		
		case UART5:
			while(UART_FIFOEmptyFlag(UART));
			return UART5_DR_R;
		
		case UART6:
			while(UART_FIFOEmptyFlag(UART));
			return UART6_DR_R;
		
		case UART7:
			while(UART_FIFOEmptyFlag(UART));
			return UART7_DR_R;
		}
		return 0;
}

void UART_getUDRString(u8 UART , char* string){
	
	u8 i=0;
	string[i] = UART_getUDR(UART);
	while(string[i] != '$'){
		i++;
		string[i] = UART_getUDR(UART);
	}
	string[i]='\0';
}

