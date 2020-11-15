#include <SPI.h>
#include "sram.h"

void initRam()
{
  /* setup SPI */
  SPI.begin();
  SPI.setClockDivider(SPI_CLOCK_DIV4);
  pinMode(SS_PIN, OUTPUT);

  /* set mode */
  digitalWrite(SS_PIN, LOW);
  SPI.transfer(WRSR);
  /* STREAM MODE, TODO: PAGE MODE (0x80), BYTE MODE (0X00) */
  SPI.transfer(0x00);
  digitalWrite(SS_PIN, HIGH);
  digitalWrite(SS_PIN, LOW);
  SPI.transfer(RDSR);
  //SPI.transfer(0xFF); //???
  digitalWrite(SS_PIN, HIGH);
}

void readRam(char* output, long addr, long len)
{
  digitalWrite(SS_PIN, HIGH);

  digitalWrite(SS_PIN, LOW);
  /* first byte is type rw */
  SPI.transfer(READ);

  /* using 23LC1024 so i think address is next 3 bytes, not 2? */
  SPI.transfer((char)(addr >> 16));
  SPI.transfer((char)(addr >> 8));
  SPI.transfer((char)addr);


  digitalWrite(SS_PIN, LOW);
  long i = 0;
  for (i = 0; i < len; i++) {
    output[i] = SPI.transfer(0xFF);
  }git
  digitalWrite(SS_PIN, HIGH);
}

void witeRam(char* input, long addr, long len)
{
  digitalWrite(SS_PIN, LOW);
  /* first byte is type rw */
  SPI.transfer(WRITE);

  /* using 23LC1024 so i think address is next 3 bytes, not 2? */
  SPI.transfer((char)(addr >> 16));
  SPI.transfer((char)(addr >> 8));
  SPI.transfer((char)addr);

  /* write */
  long i = 0;
  for (i = 0; i < len; i++) {
    SPI.transfer(input[i]);
    Serial.println("test");
  }
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
  witeRam(addr, buffer, len);
}

void testRam()
{
  /* some address, doesn't really matter */
  long addr = 32;
  char* buffer = "test";
  char* buffer2 = "";
  long len = 10;
  long i = 0;
  witeRam(buffer, addr, len);
  delay(100);
  readRam(buffer2, addr, len);
  delay(100);
  Serial.println(buffer2);
}
