#include "stdint.h"
#include <string.h>
#include "GPIO_Int.h"
#include "KPD_Int.h"
#include "UART_Int.h"
#include "F:/Keil/EE319Kware/inc/tm4c123gh6pm.h"
 
typedef struct Room{
	
char* roomNumber;	//hotel room number
char roomStatus; 	//1->occupied, 2->cleaning, 3->free
char* roomPassword;    //4-digit password
u8 RoomSolonoidPort, RoomSolonoidPin; //setting room solonoid port&pin
u8 KPDPort;	//setting room KPD port
}Room;
  
void SystemInit(){}
	
void init(void){
 
  uint8_t delay;
//setting clock for all ports to use as GPIO. All solenoids connected to port A and Uart uses PA0 & PA1 and the rest of ports used for KeyPads.
  SYSCTL_RCGCGPIO_R = 0x3F;
  delay =1;
 
  GPIO_init(Port_A); //initialize port A as GPIO for solonids 
//set port A data register direction output pins (2->7) and pin(0,1) is used for UART
  GPIO_setPortDirection(Port_A , 0xFC); 
  //Initialize UART0
  UART_Init(UART0);
}
/*port(A->F) represented as (0->5) like this #define Port_A 0 and so on for the rest Ports and the same for pins like this->#define pin0 0
Note: if we say that every room has a keypad then you can add up to 5 rooms in one tiva, why?
as every room needs 8 pins for keypad and one solonoid then 5 rooms needs 5 ports for keypad and 5 pins for solonoid.
So i made the max rooms to add is 5 rooms, as i made port A pin (0,1) for UART1 and the rest 6 pins for solonoids and the rest 5 ports for KPDs. 
Note: every string entered in pc must end with $ to make the UART_getUDRString API work properly. */
int main(){
Room room[5]; //setting max room numbers is 5
init();
//KPDPortCounter used for specifying every room KPD connected Port.
//pinCounter used for specifying every room solenoid.
u8 k=0, KPDCount=0, KPDPortCounter=1, pinCounter=2;
char *roomNumber="-1";	//room number to set status for it
//setup mode
UART_getUDRString(UART0 , room[0].roomNumber); //get first room number
//pinCounter initialized as PA2 at line (35) and we increment it at line (52) then pinCounter will equal 3 which represents pin3 in port A Then, room2 solenoid is must connected to PA3 and so on.
//KPDPortCounter initialized to Port B at line (35) which used for room 1 so we increment it in if at line (53) to use another port for another room. Here for Example: For room 2 KPDPortCounter will equal 2 which represents port D then room 2 KPD must connected to port D and so on.
//as here we test functionality of one room then I commented the lines which increment pinCounter and KPDPortCounter so if you have KPD & solenoid for every room then connect them to tiva in order as explained above and just uncomment Line from (52 to 62)	
//configure room KPD (Port) and solonoid (pin and port) that connected by the room lock
room[0].RoomSolonoidPort = Port_A;	//set solonoid port to port b 
room[0].RoomSolonoidPin =  pinCounter;	//set solenoid pin to PA2
room[0].KPDPort=KPDPortCounter;//SET KPD port of first room. 	
//here you can enter up to 5 rooms every room number seperated by $ and if you finished type # then $. For Exmaple 55$66$#$ here you input 2 rooms.
while(room[k].roomNumber[0]!='#' && k<=4){//enter rest of rooms.
  k++;
  UART_getUDRString(UART0 , room[k].roomNumber);//save new room number
 //initialize KPD_port for KeyPad
  GPIO_init(KPDPortCounter); 
//set KPD_port data register direction(input pins(pin 0,1,2,3) & output pins (set pin 4,5,6->output)
  GPIO_setPortDirection(KPDPortCounter, 0xF0);
  //input pins(0->4) is setted pull up in GPIO_init()
/*pinCounter++; 
if(KPDPortCounter==0)
//avoid using port b for the keypad as we use it for UART & solenoids.
  KPDPortCounter+=2;
else
  KPDPortCounter++;
 
room[k].RoomSolonoidPort = Port_A;//set solenoid port for room[k]
room[k].RoomSolonoidPin =  pinCounter;//set solenoid pin for room[k]
room[k].KPDPort = KPDPortCounter; //set key pad port of the room[k]
*/
}
k--; //as the last input contain # and this isn't room.
while(1){	
  u8 i=0; //for counter
  u8 KPD_Array[3][4];	//used to get the input from keypad
  char enteredPassword[4]; //gotten Password from the Key pad
  u8 inputStatus = UART_getUDR(UART0); //input M to change room status 
  if(inputStatus=='M'){
    UART_getUDRString(UART0 , roomNumber);//input room number by UART
    KPDCount=0;
  } 
  if(KPDCount==4)//to detect number of digits entered by keypad
     KPDCount=0;  
  for(; i<=k ; i++){
//strcmp()compares between 2 string if equal then returns 0
    if(strcmp(room[i].roomNumber,roomNumber)==0){
    if(inputStatus=='M')
      room[i].roomStatus = UART_getUDR(UART0)-'0';
    switch(room[i].roomStatus){
      case '1':	 //represent occupied state
	if(inputStatus=='M')
          //getting the room password from pc by uart
          UART_getUDRString(UART0 , room[i].roomPassword);
        //getting the password from keypad
 	enteredPassword[KPDCount] = KPD_getNumber(KPD_Array); 
	KPDCount++;		
	if(strcmp(room[i].roomPassword , enteredPassword) == 0)
         //open the solonoid of this room (Open the door)
         GPIO_setPinValue(room[i].RoomSolonoidPort ,    room[i].RoomSolonoidPin , HIGH);
 	else
          //lock the solonoid of this room (Lock the door)
	  GPIO_setPinValue(room[i].RoomSolonoidPort , room[i].RoomSolonoidPin , LOW);				
	break;
      case '2':	//represents cleaning state
        //open the solonoid (Open the door)
	GPIO_setPinValue(room[i].RoomSolonoidPort , room[i].RoomSolonoidPin , HIGH); 
	break;
      case '3':	//represents free state
	GPIO_setPinValue(room[i].RoomSolonoidPort , room[i].RoomSolonoidPin , LOW);						    
        break;
      }
     break;
   }		
  }
 }
}
