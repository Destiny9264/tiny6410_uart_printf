#include "uart.h"

#define GPBCON (*((volatile unsigned long *)0x7F008020))
#define ULCON3 (*((volatile unsigned long *)0x7F005C00)) //UART channel 3 line control register
#define UCON3 (*((volatile unsigned long *)0x7F005C04)) //UART channel 3 control register
#define UFCON3 (*((volatile unsigned long *)0x7F005C08)) //UART channel 3 FIFO control register
#define UTRSTAT3 (*((volatile unsigned long *)0x7F005C10)) //UART channel 3 Tx/Rx status register
#define UFSTAT3 (*((volatile unsigned long *)0x7F005C18)) //UART channel 3 FIFO status register
#define UTXH3 (*((volatile unsigned long *)0x7F005C20)) //UART channel 3 transmit buffer register
#define URXH3 (*((volatile unsigned long *)0x7F005C24))  //UART channel 3 receive buffer register
#define UBRDIV3 (*((volatile unsigned long *)0x7F005C28)) //UART channel 3 Baud rate divisior register
#define UDIVSLOT3 (*((volatile unsigned long *)0x7F005C2C)) //UART channel 3 Dividing slot register

void uart_init()
{
	GPBCON &= ~0xff;
	GPBCON |= 0x2200;
	ULCON3 = 0x3;
	UCON3 = 0x5;
	UFCON3 = 0x01;

	UBRDIV3   = 35;
	UDIVSLOT3 = 0x1;

}

char getc(void)
{
	while((UFSTAT3 & 0x7f) == 0);
	return URXH3;
}

void putc(char string)
{
	while(UFSTAT3 & (1<<14));
	UTXH3 = string;
}
