SECTIONS {
    . = 0x50000000;
    
	.text : {
			start.o
			clock.o
			sdram.o
			* (.text)
	}

	.rodata : {
			* (.rodata)
	}

	.data : {
			* (.data)
	}

    bss_start = .;
    .bss ALIGN(4)  : { *(.bss)  *(common) }
    bss_end = .;
}
