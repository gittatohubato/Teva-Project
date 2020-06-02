#ifndef UART_INT_H_
#define UART_INT_H_

#define u8 unsigned char

#define UART0 0
#define UART1 1
#define UART2 2
#define UART3 3
#define UART4 4
#define UART5 5
#define UART6 6
#define UART7 7

#define DISABLED 0
#define RESERVED 1
#define EVEN_PARITY 2
#define ODD_PARITY 3

#define STOP_1_BIT 0
#define STOP_2_BITS 1

#define DATA_5_BITS 0
#define DATA_6_BITS 1
#define DATA_7_BITS 2
#define DATA_8_BITS 3
#define DATA_9_BITS 7

void UART_Init(u8 UART);
/*void UART_ParityMode(u8 parity);
void UART_StopBit(u8 stopBit);
void UART_CharcterSize(u8 size);*/
void UART_SetUDR(u8 UART , u8 value);
void UART_SetUDRString(u8 UART , u8* value);
u8 UART_getUDR(u8 UART);
void UART_getUDRString(u8 UART , char* string);
u8 UART_FIFOFullFlag(u8 UART);
u8 UART_FIFOEmptyFlag(u8 UART);


#endif /* UART_INT_H_ */
