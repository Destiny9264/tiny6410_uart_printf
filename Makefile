SHELL=C:/Windows/System32/cmd.exe
CC      = arm-elf-gcc
LD      = arm-elf-ld
AR      = arm-elf-ar
OBJCOPY = arm-elf-objcopy
OBJDUMP = arm-elf-objdump

CURDIR := D:/eclipse_projects/uart_lib

INCLUDEDIR 	:= $(CURDIR)/include
CFLAGS 		:= -Wall -Os -fno-builtin  #-Wall 开启警告 -Os优化  不使用__builtin_函数
CPPFLAGS   	:= -nostdinc -I$(INCLUDEDIR) #不要在标准系统目录中搜索头文件  在指定目录下搜索头文件
LIBSDIR := D:/eclipse_projects/uart_lib/lib

export 	CC AR LD OBJCOPY OBJDUMP INCLUDEDIR CFLAGS CPPFLAGS 

objs := start.o clock.o sdram.o  main.o uart.o  lib/libc.a

all : uart.bin
uart.bin: $(objs)
	$(LD) -T uart.lds -o uart.elf $^
	$(OBJCOPY) -O binary uart.elf $@
	$(OBJDUMP) -D uart.elf > uart.dis

.PHONY : lib/libc.a
lib/libc.a:
	make -C $(LIBSDIR)

%.o : %.c
	$(CC) $(CPPFLAGS) $(CFLAGS) -c -o $@ $<
	
%.o : %.S
	$(CC) $(CPPFLAGS) $(CFLAGS) -c -o $@ $<
	
clean:
	del *.bin *.o *.dis *.elf
	make clean -C $(LIBSDIR)