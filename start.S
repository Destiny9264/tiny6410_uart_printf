// 启动代码
.global _start

_start:

	// 设置外设基地址以及外设大小
	ldr r0,=0x70000000
	orr r0,r0,#0x13
	mcr p15,0,r0,c15,c2,4


	//关看门狗
	ldr r0,=0x7E004000
	mov r1,#0
	str r1,[r0]

	//设置堆栈
	ldr sp,=0x0C002000

	// 开启icaches(这有什么用?)
#ifdef  CONFIG_SYS_ICACHE_OFF
	bic r0, r0, #0x00001000 				@ clear bit 12 (I) I-cache
#else
	orr r0, r0, #0x00001000 				@ set bit 12 (I) I-cache
#endif
	mcr p15, 0, r0, c1, c0, 0

	bl clock_init
	bl sdram_init
	//重定向
	adr r0,_start //_start当前地址
	ldr r1,=_start //_start链接地址
	ldr r2,=bss_start//bss起始地址
	cmp r0,r1
	beq clean_bss
//将当前地址的代码复制到链接地址处
copy_loop:
	ldr r3,[r0],#4
	str r3,[r1],#4
	mov r3,#0
	cmp r1,r2  //r2-r1是程序长度
	bne copy_loop

clean_bss:
	ldr r0,=bss_start
	ldr r1,=bss_end
	mov r3,#0
	cmp r0,r1
	beq load_main
clean_loop:
	str r3,[r0],#4
	cmp r0,r1
	bne clean_loop

load_main:
	ldr pc,=main

halt:
	b halt
