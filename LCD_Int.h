/*
 * LCD_Int.h
 *
 *  Created on: Aug 27, 2019
 *      Author: Mohamed Amr
 */

#ifndef LCD_INT_H_
#define LCD_INT_H_

/*
-Notes:
*******
	1.You must initialize the port you will use and configure it's direction as O/P.
	2.Configure the Ports & Pins you used by writing it in the (RS_pin , ......) this configuration from line(32 to 41) 
	3.you must useLCD_init() function first
*/

#define u8 unsigned char

//deh y3ny 34an el user law ktab f el function bta3t t7did el mkan(writeStringLocation) el htktb feh 7aga b el hexa

#define A 10
#define B 11
#define C 12
#define D 13
#define E 14
#define F 15

#define Data_Port Port_F

#define RS_Pin Pin2
#define RS_Port Port_D

#define RW_Pin Pin1
#define RW_Port Port_D

#define Enable_Pin Pin0
#define Enable_Port Port_D


#define Fun_Set 0x38
#define Disp_Set 0x0c
#define clear 0x01

void LCD_Init(void);
void LCD_writeData(u8 data);
void LCD_writeString(u8* str);
void LCD_clearScreen(void);
void LCD_writeStringLocation(u8* str , u8 x , u8 y);



#endif /* LCD_INT_H_ */
