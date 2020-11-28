#include <SPI.h>
#include "sram.h"

void initRam()
{
  SPI.begin();
  pinMode(SS_PIN, OUTPUT);
  SPI.setClockDivider(SPI_CLOCK_DIV4);
}

void readRam(char* output, long addr, long len)
{
  digitalWrite(SS_PIN, LOW); 
  SPI.transfer(WRSR);
  SPI.transfer(0x40 | 1); // Stream mode, hold line disabled
  digitalWrite(SS_PIN, HIGH);  
      
  digitalWrite(SS_PIN, LOW); 
  SPI.transfer(RDSR);
  int mode=SPI.transfer(0xFF);
  digitalWrite(SS_PIN, HIGH);  

  digitalWrite(SS_PIN, LOW);
  SPI.transfer(READ);
  SPI.transfer((char)(addr >> 16)); // Should be skipped for some other chips, not CHIP_23LCV1024
  SPI.transfer((char)(addr >> 8));
  SPI.transfer((char)addr);
      
  long i = 0;
  for (i = 0; i < len; i++) {
    output[i] = SPI.transfer(0xFF);
  }
  digitalWrite(SS_PIN, HIGH); // disable
}

void witeRam(char* input, long addr, long len)
{
  digitalWrite(SS_PIN, LOW);  
  SPI.transfer(WRSR);
  SPI.transfer(0x40 | 1); // Stream mode, hold line disabled
  digitalWrite(SS_PIN, HIGH);  
  
  digitalWrite(SS_PIN, LOW); 
  SPI.transfer(RDSR);
  int mode = SPI.transfer(0xFF); 
  digitalWrite(SS_PIN, HIGH);  

  digitalWrite(SS_PIN, LOW); 
  SPI.transfer(WRITE);
  SPI.transfer((char)(addr >> 16)); // Should be skipped for some other chips, not CHIP_23LCV1024
  SPI.transfer((char)(addr >> 8));
  SPI.transfer((char)addr);
  long i;
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
  char buffer2[] = "    ";
  long len = 4;
  long i = 0;
  witeRam(buffer, addr, len);
  delay(100);
  readRam(buffer2, addr, len);
  delay(100);
  Serial.println(buffer2);
}
