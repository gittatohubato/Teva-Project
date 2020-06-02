#include "GPIO_Int.h"
#include "LCD_Int.h"


//FUNCTIONS

void delay(int n){
	
	int i,k;
	for(i=0 ; i<n ; i++){
		
		for(k=0 ; k<1000 ; k++){}
	}
}

void writeCommand(u8 command){

	//set RS Low
	GPIO_setPinValue(RS_Port , RS_Pin , LOW);

	//set RW Low
	GPIO_setPinValue(RW_Port , RW_Pin , LOW);

	//set Enable Low
	GPIO_setPinValue(Enable_Port , Enable_Pin , LOW);

	//The command output to LCD
	GPIO_setPortValue(Data_Port , command);

	//making value executed by LCD by controlling Enable
	GPIO_setPinValue(Enable_Port , Enable_Pin , HIGH);
	//_delay_ms(2);
	GPIO_setPinValue(Enable_Port , Enable_Pin , LOW);
}

void writeData(u8 data){

	//set RS High
	GPIO_setPinValue(RS_Port , RS_Pin , HIGH);

	//set RW Low
	GPIO_setPinValue(RW_Port , RW_Pin , LOW);

	//set Enable Low
	GPIO_setPinValue(Enable_Port , Enable_Pin , LOW);

	//The command output to LCD
	GPIO_setPortValue(Data_Port , data);

	//making value executed by LCD by controlling Enable
	GPIO_setPinValue(Enable_Port , Enable_Pin , HIGH);
	//_delay_ms(2);
	GPIO_setPinValue(Enable_Port , Enable_Pin , LOW);
}

//API

void LCD_Init(void){

	//_delay_ms(40);

	writeCommand(Fun_Set);		//function set command
	//_delay_ms(2);

	writeCommand(Disp_Set);		//display on/off
	//_delay_ms(2);

	writeCommand(clear);	//clear display
	//_delay_ms(2);
}

void LCD_writeData(u8 data){

	writeData(data);
}

void LCD_writeString(u8* str){

	u8 i;
	for(i=0 ; str[i]!='\0' ; i++){

		writeData(str[i]);
	}
}

void LCD_clearScreen(void){

	writeCommand(clear);
}

void LCD_writeStringLocation(u8* str , u8 x , u8 y){

	/*let x value is F
	 *
	 * NOTE:
	 *
	 * Here Y variable controls the row of writing which is 0 Or 4 so we shifted by 6 as if y=0 the it will be
	 * shifted by 6 then the left cell will be zero (0x0F) but if Y=1 then the left cell(5ana) will be 4 (0x4F) and we
	 * got the value of x by summing them or by making OR operation to them.
	 *
	 * NOTE:
	 *
	 * the command of writing in specific address must have the DB7(data bus 7) has value of 1 but here the DB7=0
	 * so we must make OR operation with the result address of X & Y with (0x80 OR 0b10000000) to make DB7=1
	 */

	u8 address = x+(y<<6);
	address |= 0x80;

	writeCommand(address);
	LCD_writeString(str);

}

