// 功能:流水灯
#include "uart.h"
#include "stdio.h"
#include "nand.h"
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
	unsigned char buff = 0xcc;
	unsigned long addr;

	volatile unsigned long *gpkcon0 = (volatile unsigned long *)0x7F008800;
	volatile unsigned long *gpkdat = (volatile unsigned long *)0x7F008808;
	uart_init();
	nand_init();
	*gpkcon0 = 0x11110000;
	*gpkdat = i;



	for(addr = 0;addr<=100;addr++)
	{
		nandll_read_page(&buff,addr);
		delay(1);
		printf("addr:%x data:%x\r\n",addr, buff);

		i++;
		if (i == 0x100)
			i = 0x10;
		*gpkdat = i;
	}
	*gpkdat = 0;
	while(1);


	return 0;
}

