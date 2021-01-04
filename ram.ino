//#define FILL_RAM

#include "sram.h"
#ifndef FILL_RAM
#include <VGAX.h>
#endif

#ifndef FILL_RAM
VGAX vga;
#endif

int n_pix = 30;
int addr = 0;

#ifdef FILL_RAM
void fill_ram()
{
  initRam();

  byte pixel_data[n_pix * 3]; 
  
  int y = 0;
  for (int i = 0; i < n_pix * 3; i+=3){
    pixel_data[i] = 10;
    pixel_data[i + 1] = y++;
    pixel_data[i + 2] = 3;
  }

  writeRam((char*)pixel_data, addr, n_pix * 3);
}
#endif

void setup()   
{  
#ifndef FILL_RAM
  vga.begin();
  initRam();
  int buffer_size = n_pix * 3;
  char buffer [buffer_size];
  readRam(buffer, addr, buffer_size);

  for (int i =0; i < buffer_size; i+=3){
      vga.putpixel(buffer[i], buffer[i+1], buffer[i+2]);
  }
  
#else
  fill_ram();
#endif    
}

void loop()                    
{
    
}
