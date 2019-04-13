#ifndef __NAND_H
#define __NAND_H
void nand_init(void);
int nandll_read_page (unsigned char *buf, unsigned long addr);
int nand_write_one_byte(unsigned long addr,unsigned char data);
int nand_erase_block(unsigned long addr);
#endif
