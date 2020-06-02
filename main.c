#include "stdint.h"
#include <string.h>
#include "GPIO_Int.h"
#include "KPD_Int.h"
#include "UART_Int.h"
#include "F:/Keil/EE319Kware/inc/tm4c123gh6pm.h"

typedef struct Room{
	
	char* roomNumber;			//hotel room number
	char roomStatus; 			//1->occupied , 2->cleaning , 3->free
	char* roomPassword;		//4-digit password
	u8 RoomSolonoidPort, RoomSolonoidPin;	//setting the port and the pin that the solonoid connected to
	u8 KPDPort;	//as we use several room so you want several keypads so you can define it here as we do with solonoids. Note: i initialize KPD port to port_D in the interface
}Room;


void SystemInit(){}
	
void init(void){

	uint8_t delay;
	SYSCTL_RCGCGPIO_R = 0x3F;		//setting clock for all ports to use as GPIO for solonoid and keypad and Port b first 2 pins to use in uart					
	delay =1;
	
	GPIO_init(Port_B);  //initialize port D for KeyPad
	GPIO_setPortDirection(Port_D , 0xFC); //set port B data register direction output pins (2->7) and pin(0,1) is used for UART

	//GPIO_init(Port_F);	//initialize port F	
	//GPIO_setPortDirection(Port_F , 0x0E); //set port f data register direction(input pins & output pins (set pin 1,2,3->output)
	//GPIO_setPullUpResistor(Port_F , 0x11);	//set port f pins(0,4) to pull up resistor

	UART_Init(UART1);
}
/*
Note: if we say that every room has a keypad then you can add up to 5 rooms in one tiva why?
	as every room needs 8 pins for keypad and one solonoid then 5 rooms needs 5 ports for keypad and 5 pins for solonoid.

So i made the max rooms to add is 5 rooms, as i made port b pin (0,1) for UART1 and the rest 6 pins for solonoids and the rest 5 ports for KPDs 
*/

//note evrey string entered in pc must end with $ to make the UART_getUDRString API work properly 
int main(){
	
	Room room[5];
	init();	
	u8 k=0, KPDCount=0, portCounter=0 , pinCounter=2;
	char *roomNumber="-1";	//the variable that use to get room number to set status for it

	//setup mode
	UART_getUDRString(UART1 , room[0].roomNumber); //get the first room number
	
	//configuere room port and solonoid pin that connected by the room lock
	room[0].RoomSolonoidPort = Port_B;	//set solonoid port to port b as explained above
	room[0].RoomSolonoidPin =  pinCounter;	//assign the used pin for solonoid of first room
	room[0].KPDPort=portCounter;	//assign the used port for KPD of first room
	
	
	//enter the rest room numbers, For Exmaple 55$66$#$  here you input 2 rooms
	while(room[k].roomNumber[0]!='#' && k<=4){	//here you can enter up to 10 rooms every room number seperated by $ and if you finished type # then $
		k++;
		UART_getUDRString(UART1 , room[k].roomNumber);	//save the new room number
		
		GPIO_init(portCounter);  //initialize port D for KeyPad
		GPIO_setPortDirection(portCounter , 0xF0); //set port d data register direction(input pins(pin 0,1,2,3) & output pins (set pin 4,5,6->output)
		GPIO_setPullUpResistor(portCounter , 0x0F);	//set pull up for input pins(0->3)
		
		room[k].RoomSolonoidPort = Port_B;	//set the solonoid connected port for the room[k]
		room[k].RoomSolonoidPin =  pinCounter;	//set the solonoid connected pin for the room[k]
		room[k].KPDPort = portCounter; 	//set the key pad connected port of the room[k]
		
		pinCounter++;
		if(portCounter==0)
			portCounter+=2;	//to avoid setting port b for the keypad as we use it for UART and solonids.
		else
			portCounter++;
	}
	
	while(1){
		u8 i=0;	//for counter
		u8 KPD_Array[3][4];		//get current pressed button from keypad and save it in opposite index in array
		char enteredPassword[4];	//the password that is gotten fom the Key pad
		u8 inputStatus = UART_getUDR(UART1);
		if(inputStatus=='M'){
			UART_getUDRString(UART1 , roomNumber);	//input the room number by using UART
			KPDCount=0;
		}
		if(KPDCount==4)
			KPDCount=0;
		for(; i<=k ; i++){
			if(strcmp(room[i].roomNumber,roomNumber)==0){	//strcmp() this function compares between 2 string if equal then returns 0
				if(inputStatus=='M')
					room[i].roomStatus = UART_getUDR(UART1)-48; //getting the room staus by uart. Note: we subtract from 48 as getting char is in ascii and 0 represented in ascii by 48
				switch(room[i].roomStatus){
					case '1':	//represent occupied state
						if(inputStatus=='M')
							UART_getUDRString(UART1 , room[i].roomPassword); //getting the room password from pc by uart
						enteredPassword[KPDCount] = KPD_getNumber(KPD_Array); //getting the password from keypad
						KPDCount++;
						if(strcmp(room[i].roomPassword , enteredPassword) == 0)
							GPIO_setPinValue(room[i].RoomSolonoidPort , room[i].RoomSolonoidPin , HIGH); //open the solonoid of this room (Open the door)
							//GPIO_setDataRegValue(Port_F , 0x08);	//turn on green led indicates that the door is openend(right password)
						else
							GPIO_setPinValue(room[i].RoomSolonoidPort , room[i].RoomSolonoidPin , LOW);	//lock the solonoid of this room (Lock the door)
							//GPIO_setDataRegValue(Port_F , 0x00);	//all leds is off indicates the door is locked
						break;
					case '2':	//represents cleaning state
						GPIO_setPinValue(room[i].RoomSolonoidPort , room[i].RoomSolonoidPin , HIGH); //open the solonoid (Open the door)
						//GPIO_setDataRegValue(Port_F , 0x0E);   //turning on the three leds indicates cleaning(the door opened for cleaning)
						break;
					case '3':	//represents free state
						GPIO_setPinValue(room[i].RoomSolonoidPort , room[i].RoomSolonoidPin , LOW);	//close the solonoid (Lock the door)
						//GPIO_setDataRegValue(Port_F , 0x00);	//all leds is off indicates the door is locked
						break;
				}
				break;
			}		
		}
	}
}
