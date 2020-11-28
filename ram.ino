
#include <VGAX.h>
#include "sram.h"

#define RAM_DATA_LEN 900
#define RAM_ADR 0

VGAX vga;

void setup()   
{  
    Serial.begin(115200);
    Serial.println("-----------------------");
    initRam();
    testRam();  
      
    //vga.begin();
    
    //fillRam(RAM_ADR, RAM_DATA_LEN);
    //testVga();

    // memorySnapshot(0);
    // toScreen(0, RAM_DATA_LEN);
}

void loop()                    
{}


int memorySnapshot(int addr)
{
  #if defined(ARDUINO_AVR_UNO)
  int len = 32000;
  #else 
  Serial.println("Unsupported board");
  #endif
  char buffer[] = "aaa";
  witeRam(buffer, 0, len);
  return len;
}


void toScreen(long addr, int len)
{
  /* Rather than using putpixel, just use vga buffer directly  */
  readRam((char*)vgaxfb, addr, len);
}

void testVga()
{
  int i = 0;
  long len = 600;
  while(i < len){
    vgaxfb[i] = 100;
    vgaxfb[i+1] = 100;
    vgaxfb[i+2] = 100;
    vgaxfb[i+3] = 255;
    i += 4;
  }
}
