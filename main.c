// 功能:流水灯
#include "uart.h"
#include "stdio.h"
void delay(int loop)
{

	int k;
	for(k = 0;k<=loop;k++)
	{
	volatile int j = 0x10000;
	while (j--);
	}
}

int main()
{
	int i = 0x10;

	volatile unsigned long *gpkcon0 = (volatile unsigned long *)0x7F008800;
	volatile unsigned long *gpkdat = (volatile unsigned long *)0x7F008808;
	uart_init();

	*gpkcon0 = 0x11110000;
	while (1)
	{

		*gpkdat = i;
		i++;
		if (i == 0x100)
			i = 0x10;
		printf("hello\r\n");
		delay(3);
	}

	return 0;
}

