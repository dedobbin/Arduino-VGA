//#define FILL_RAM

#include "sram.h"
#ifndef FILL_RAM
#include "automaton.h"
#include <VGAX.h>
#endif

#ifndef FILL_RAM
VGAX vga;
#endif

int n_entries = 30;
int addr = 0;

#ifdef FILL_RAM
void fill_ram()
{
  initRam();

  byte data[n_entries * 3]; 
  
  int y = 0;
  for (int i = 0; i < n_entries * 3; i+=3){
    data[i] = 10;
    data[i + 1] = y++;
    data[i + 2] = 1;
  }

  writeRam((char*)pixel_data, addr, n_entries * 3);
}
#endif

void setup()   
{  
#ifndef FILL_RAM
  vga.begin();
  
  automaton automatons[n_entries];

  automaton* a_ptr = automatons;
  for (int i=0;i<n_entries;i++){
    automaton a;
    a.x = rand()%VGAX_WIDTH;
    a.y = rand()%VGAX_HEIGHT;
    a.type =  (i%3)+1;
    *a_ptr = a;
    //*a_ptr = {rand()%VGAX_WIDTH, rand()%VGAX_HEIGHT, (i%3)+1, i*sizeof(automaton)};
    a_ptr++;
  }

  byte* vga_ptr = vgaxfb;
  for (int i=0;i<n_entries;i++){
    //vga.putpixel(automatons[i].x, automatons[i].y, automatons[i].type);
    byte *p=vga_ptr +  automatons[i].y*VGAX_BWIDTH + (automatons[i].x>>2);
    byte bitpos=6-(automatons[i].x & 3)*2;
    *p=(*p & ~(3 <<bitpos)) | automatons[i].type <<bitpos;
  }

   

//  initRam();
//  int buffer_size = n_pix * 3;
//  char buffer [buffer_size];
//  readRam(buffer, addr, buffer_size);
//
//  for (int i =0; i < buffer_size; i+=3){
//      vga.putpixel(buffer[i], buffer[i+1], buffer[i+2]);
//  }
  
#else
  fill_ram();
#endif    
}

void loop()                    
{
    
}
