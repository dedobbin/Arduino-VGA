#include <SPI.h>
#include "sram.h"

void initRam()
{
  /* setup SPI */
  SPI.begin();
  pinMode(SS_PIN,OUTPUT);
  digitalWrite(SS_PIN, HIGH);
  SPI.setClockDivider(SPI_CLOCK_DIV4);  
}

void readRam(char* output, long addr, long len)
{
  /* Set mode (STREAM)*/
  digitalWrite(SS_PIN, LOW); 
  SPI.transfer(WRSR);
  SPI.transfer(0x40 | 1);
  digitalWrite(SS_PIN, HIGH);

  /* This does Status Register Read OP, but we don't really need to know mode etc */
//  digitalWrite(SS_PIN, LOW); 
//  SPI.transfer(RDSR);
//  int mode = SPI.transfer(0xFF);
//  digitalWrite(SS_PIN, HIGH); 

  /* set type of action + address */
  digitalWrite(SS_PIN, LOW);
  // first set type of action
  SPI.transfer(READ); 
  // using 23LC1024 so i think address is 3 bytes, not 2, otherwise should skip first line
  SPI.transfer((char)(addr >> 16));
  SPI.transfer((char)(addr >> 8));
  SPI.transfer((char)addr);

  /* now we can do the reading */
  int i;
  for (i = 0; i < len; i++) {
    output[i] = SPI.transfer(0xFF);
  }
  digitalWrite(SS_PIN, HIGH); 
}

void witeRam(char* input, long addr, long len)
{
  /* Set mode (STREAM)*/
  digitalWrite(SS_PIN, LOW);
  SPI.transfer(WRSR);
  SPI.transfer(0x40 | 1);
  digitalWrite(SS_PIN, HIGH);

  
//  digitalWrite(SS_PIN, LOW); 
//  SPI.transfer(RDSR);
//  int mode = SPI.transfer(0xFF);
//  digitalWrite(SS_PIN, HIGH); 

  digitalWrite(SS_PIN, LOW); //enable()
  SPI.transfer(READ);
  // using 23LC1024 so i think address is 3 bytes, not 2
  SPI.transfer((char)(addr >> 16));//true
  SPI.transfer((char)(addr >> 8));
  SPI.transfer((char)addr);

  int i;
  for (i = 0; i < len; i++) {
    SPI.transfer(input[i]);
  }
  digitalWrite(SS_PIN, HIGH);  
}


/****** test functions ******/

void fillRam(long addr, long len)
{
  char buffer[len];
  int i = 0;
  while (i <= len) {
    buffer[i] = 255;
    buffer[i + 1] = 123;
    i += 1;
  }
  witeRam(buffer, addr, len);
}

void testRam()
{
  /* some address, doesn't really matter */
  long addr = 32;
  char buffer[] = "test";
  char buffer2[] = "";
  long len = 4;
  long i = 0;
  witeRam(buffer, addr, len);
  delay(100);
  readRam(buffer2, addr, len);
  delay(100);
}
