#ifndef __SRAM_H__
#define __SRAM_H__

#define SS_PIN 10

/* SRAM operation */
#define WRSR  1
#define WRITE 2
#define READ  3
#define RDSR  5

void initRam();
void writeRam(char* input, long addr, long len);
void readRam(char* output, long addr, long len);

#endif
