#include "F:/Keil/EE319Kware/inc/tm4c123gh6pm.h"
#include "GPIO_Int.h"

#define u8 	unsigned char

#define assignBits(var,Bno,val) do{if(val==1) ((var)|= (1 << (Bno))); \
								else if(val==0) ((var)&= ~(1 << (Bno))); \
								}while(0)

#define getBit(DATA_R,Pin,level)	(level=(DATA_R & (1<<Pin)))		

void GPIO_init(u8 Port){		//doesn't contains clk enable
	
	switch(Port){

		case Port_A:
			
			GPIO_PORTA_LOCK_R = 0x4C4F434B;
      GPIO_PORTA_CR_R=0xFF; //enable registers writing
      GPIO_PORTA_AFSEL_R = 0; //no alternative functions
      GPIO_PORTA_PCTL_R = 0; // no alternative functions
      GPIO_PORTA_AMSEL_R = 0; // analog function disabled
      GPIO_PORTA_DEN_R= 0xFF; // digital enable
			GPIO_PORTA_PUR_R = 255; //set all pins as pull up resistor
			break;

		case Port_B:

			GPIO_PORTB_LOCK_R = 0x4C4F434B;
      GPIO_PORTB_CR_R=0xFF; //enable registers writing
      GPIO_PORTB_AFSEL_R = 0; //no alternative functions
      GPIO_PORTB_PCTL_R = 0; // no alternative functions
      GPIO_PORTB_AMSEL_R = 0; // analog function disabled
      GPIO_PORTB_DEN_R= 0xFF; // digital enable
			GPIO_PORTB_PUR_R = 255;
			break;

		case Port_D:

			GPIO_PORTD_LOCK_R = 0x4C4F434B;
      GPIO_PORTD_CR_R=0xFF; //enable registers writing
      GPIO_PORTD_AFSEL_R = 0; //no alternative functions
      GPIO_PORTD_PCTL_R = 0; // no alternative functions
      GPIO_PORTD_AMSEL_R = 0; // analog function disabled
      GPIO_PORTD_DEN_R= 0xFF; // digital enable	
			GPIO_PORTD_PUR_R = 255;
			break;
		
		case Port_E:

			GPIO_PORTE_LOCK_R = 0x4C4F434B;
      GPIO_PORTE_CR_R=0xFF; //enable registers writing
      GPIO_PORTE_AFSEL_R = 0; //no alternative functions
      GPIO_PORTE_PCTL_R = 0; // no alternative functions
      GPIO_PORTE_AMSEL_R = 0; // analog function disabled
      GPIO_PORTE_DEN_R= 0xFF; // digital enable	
			GPIO_PORTE_PUR_R = 255;
			break;

		case Port_F:

			GPIO_PORTF_LOCK_R = 0x4C4F434B;
      GPIO_PORTF_CR_R=0xFF; //enable registers writing
      GPIO_PORTF_AFSEL_R = 0; //no alternative functions
      GPIO_PORTF_PCTL_R = 0; // no alternative functions
      GPIO_PORTF_AMSEL_R = 0; // analog function disabled
      GPIO_PORTF_DEN_R= 0xFF; // digital enable	
			GPIO_PORTF_PUR_R = 255;
			break;
		}
	
}



u8 GPIO_setPinValue(u8 Port , u8 Pin , u8 value){

	if(Port>=0 && Port<=5 && Pin>=0 && Pin<=7){

		switch(Port){

		case Port_A:

			assignBits(GPIO_PORTA_DATA_R,Pin,value);
			break;

		case Port_B:

			assignBits(GPIO_PORTB_DATA_R,Pin,value);
			break;

		case Port_C:

			assignBits(GPIO_PORTC_DATA_R,Pin,value);
			break;

		case Port_D:

			assignBits(GPIO_PORTD_DATA_R,Pin,value);
			break;
		
		case Port_E:

			assignBits(GPIO_PORTE_DATA_R,Pin,value);
			break;

		case Port_F:

			assignBits(GPIO_PORTF_DATA_R,Pin,value);
			break;
		}
		return 0;
	}
	return 1;
}

u8 GPIO_setPullUpResistor(u8 Port , u8 value){

	if(Port>=0 && Port<=5){

		switch(Port){

		case Port_A:

			GPIO_PORTA_PUR_R = value;
			break;

		case Port_B:

			GPIO_PORTB_PUR_R = value;
			break;

		case Port_C:

			GPIO_PORTC_PUR_R = value;
			break;

		case Port_D:

			GPIO_PORTD_PUR_R = value;
			break;
		
		case Port_E:

			GPIO_PORTE_PUR_R = value;
			break;

		case Port_F:

			GPIO_PORTF_PUR_R = value;
			break;
		}
		return 0;
	}
	return 1;
}

u8 GPIO_setDataRegValue(u8 Port , u8 value){

	if(Port>=0 && Port<=5){

		switch(Port){

		case Port_A:

			GPIO_PORTA_DATA_R = value;
			break;
		
		case Port_B:

			GPIO_PORTB_DATA_R = value;
			break;
		
		case Port_C:

			GPIO_PORTC_DATA_R = value;
			break; 
		
		case Port_D:

			GPIO_PORTD_DATA_R = value;
			break;
		
		case Port_E:

			GPIO_PORTE_DATA_R = value;
			break;
		
		case Port_F:

			GPIO_PORTF_DATA_R = value;
			break;
		}
	}
	return -1;
}

u8 GPIO_getDataRegValue(u8 Port){

	if(Port>=0 && Port<=5){

		switch(Port){

		case Port_A:

			return GPIO_PORTA_DATA_R;

		case Port_B:

			return GPIO_PORTB_DATA_R;

		case Port_C:

			return GPIO_PORTC_DATA_R;

		case Port_D:

			return GPIO_PORTD_DATA_R;
		
		case Port_E:

			return GPIO_PORTE_DATA_R;

		case Port_F:

			return GPIO_PORTF_DATA_R;
		}
	}
	return -1;
}

u8 GPIO_getPinValue(u8 Port , u8 Pin , u8* level){

	if(Port>=0 && Port<=5 && Pin>=0 && Pin<=7){

		switch(Port){

		case Port_A:

			getBit(GPIO_PORTA_DATA_R,Pin,*level);
			*level = (*level==0)? 0:1;
			break;

		case Port_B:

			getBit(GPIO_PORTB_DATA_R,Pin,*level);
			*level = (*level==0)? 0:1;
			break;

		case Port_C:

			getBit(GPIO_PORTC_DATA_R,Pin,*level);
			*level = (*level==0)? 0:1;
			break;

		case Port_D:

			getBit(GPIO_PORTD_DATA_R,Pin,*level);
			*level = (*level==0)? 0:1;
			break;
		
		case Port_E:

			getBit(GPIO_PORTE_DATA_R,Pin,*level);
			*level = (*level==0)? 0:1;
			break;

		case Port_F:

			getBit(GPIO_PORTF_DATA_R,Pin,*level);
			*level = (*level==0)? 0:1;
			break;
		}
		return 0;
	}
	return 1;
}


u8 GPIO_setPinDirection(u8 Port , u8 Pin , u8 direction){

	if(Port>=0 && Port<=5 && Pin>=0 && Pin<=7){

		switch(Port){

		case Port_A:

			assignBits(GPIO_PORTA_DIR_R,Pin,direction);
			break;

		case Port_B:

			assignBits(GPIO_PORTB_DIR_R,Pin,direction);
			break;

		case Port_C:

			assignBits(GPIO_PORTC_DIR_R,Pin,direction);
			break;

		case Port_D:

			assignBits(GPIO_PORTD_DIR_R,Pin,direction);
			break;
		
		case Port_E:

			assignBits(GPIO_PORTE_DIR_R,Pin,direction);
			break;

		case Port_F:

			assignBits(GPIO_PORTF_DIR_R,Pin,direction);
			break;
		}

		return 0;
	}
	return 1;
}


u8 GPIO_setPortDirection(u8 Port , u8 directions){

	if(Port>=0 && Port<=5){

		switch(Port){

		case Port_A:

			GPIO_PORTA_DIR_R = directions;
			break;

		case Port_B:

			GPIO_PORTB_DIR_R = directions;
			break;

		case Port_C:

			GPIO_PORTC_DIR_R = directions;
			break;

		case Port_D:

			GPIO_PORTD_DIR_R = directions;
			break;
		
			case Port_E:

			GPIO_PORTE_DIR_R = directions;
			break;

		case Port_F:

			GPIO_PORTF_DIR_R = directions;
			break;
		}
		return 0;
	}
	return 1;
}


u8 GPIO_setPortValue(u8 Port , u8 value){

	if(Port>=0 && Port<=5){

		switch(Port){

		case Port_A:

			GPIO_PORTA_DATA_R = value;
			break;

		case Port_B:

			GPIO_PORTB_DATA_R = value;
			break;

		case Port_C:

			GPIO_PORTC_DATA_R = value;
			break;

		case Port_D:

			GPIO_PORTD_DATA_R = value;
			break;
		
		case Port_E:

			GPIO_PORTE_DATA_R = value;
			break;

		case Port_F:

			GPIO_PORTF_DATA_R = value;
			break;
		}
		return 0;
	}
	return 1;
}

u8 GPIO_clkEnable(u8 Port){
	
		if(Port>=0 && Port<=5){

		switch(Port){

		case Port_A:

				SYSCTL_RCGCGPIO_R = 0x01;
			break;

		case Port_B:

				SYSCTL_RCGCGPIO_R = 0x02;
			break;

		case Port_C:

				SYSCTL_RCGCGPIO_R = 0x04;
			break;

		case Port_D:

				SYSCTL_RCGCGPIO_R = 0x08;
			break;
		
		case Port_E:

				SYSCTL_RCGCGPIO_R = 0x10;
			break;

		case Port_F:

				SYSCTL_RCGCGPIO_R = 0x20;
			break;
		}
		return 0;
	}
	return 1;
	
	
}



