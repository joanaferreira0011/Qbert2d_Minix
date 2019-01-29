#include<lcom/lcf.h>
#include <math.h>
#include"video.h"
#include "vbe.h"

static char *video_mem;		/* Process (virtual) address to which VRAM is mapped */
static char *buffer;
static unsigned h_res;	        /* Horizontal resolution in pixels */
static unsigned v_res;	        /* Vertical resolution in pixels */
static unsigned bits_per_pixel; /* Number of VRAM bits per pixel */
static unsigned RedScreenMask, GreenScreenMask, BlueScreenMask; /* Masks for pattern */
extern vbe_mode_info_t vmi, vbe_info; // external structs


unsigned get_h_res(){return h_res;}
unsigned get_v_res(){return v_res;}
unsigned getRedScreenMask(){return RedScreenMask;}
unsigned getGreenScreenMask(){return GreenScreenMask;}
unsigned getBlueScreenMask(){return BlueScreenMask;}
unsigned getBitsPerPixel() {return bits_per_pixel;}

void sprite_fill_pixel(int x, int y, uint32_t color)
{
  if(color == 0xFFFFFF)
    return;
  if(x < (int)h_res && y < (int)v_res && x > 0 && y >0) // Fill pixel with the color for sprites
  {
    unsigned int bytes = (int) ceil((float)bits_per_pixel/8); /* number of bytes per pixel */
    char *pixel= buffer + (x +y*h_res)*bytes;  /* start of line */
    
    memcpy(pixel, &color, bytes);
  }
}

void sprite_clear_screen()
{
  memset(video_mem, 0, h_res*v_res*bits_per_pixel/8); // clear the whole screen
}

void clear_buffer()
{
  memset(buffer, 0, h_res*v_res*bits_per_pixel/8); // clear the whole screen
}

void draw_screen()
{
  memcpy(video_mem, buffer, h_res*v_res*bits_per_pixel/8);
}

int vbe_changemode(uint16_t mode)
{
  struct reg86u reg86;

  memset(&reg86, 0, sizeof(reg86));
  
  reg86.u.b.intno = BIOS_VIDEO; /* BIOS video services */
  reg86.u.b.ah = VBE_MODE;  // Set the mode
  reg86.u.b.al = SET_VBE_MODE; // Set the mode
  reg86.u.w.bx = mode | LINEAR_MODE; // As required in handout set BIT(14) to 1

  if( sys_int86(&reg86) != OK ) {
    printf("\tvg_exit(): sys_int86() failed \n");
    return 1;
  }

  return 0;
}


void* (vg_init) (uint16_t mode)
{
 //lm_init(false);
  if(vbe_get_info_mode(mode) != OK)
  {
    printf("Failed to fetch vbe information!\n");
    return NULL;
  }

  // Saves all the necessary information from the struct
  h_res = vbe_info.XResolution; 
  v_res = vbe_info.YResolution; 
  bits_per_pixel = vbe_info.BitsPerPixel; 
  RedScreenMask=vbe_info.RedMaskSize;
  GreenScreenMask=vbe_info.GreenMaskSize;
  BlueScreenMask=vbe_info.BlueMaskSize;
 // Calculates the vram
  uint32_t vram_size = h_res * v_res * bits_per_pixel;

  int r;
  struct minix_mem_range mr;

  mr.mr_base = (phys_bytes) vbe_info.PhysBasePtr;
  mr.mr_limit = mr.mr_base + vram_size;
  
  if( OK != (r = sys_privctl(SELF, SYS_PRIV_ADD_MEM, &mr)))
   panic("sys_privctl (ADD_MEM) failed: %d\n", r);

  /* Map memory */

  video_mem = vm_map_phys(SELF, (void *)mr.mr_base, vram_size);

  if(video_mem == MAP_FAILED)
   panic("couldn't map video memory");

  if(vbe_changemode(mode) != OK) // Changes the video mode afterwards
  {
    return NULL;
  }
  buffer = malloc(vram_size);
  printf("%u\n%u\n", h_res, v_res);
  return video_mem;
}

void color_pixel(char *pixel, uint32_t color)
{ // Colors the pixel
  unsigned int bytes = (int) ceil((float)bits_per_pixel/8); /* number of bytes per pixel */
  memcpy(pixel, &color, bytes);
}

int (vg_draw_hline)(uint16_t x, uint16_t y, uint16_t len, uint32_t color)	
{
  unsigned int bytes = (int) ceil((float)bits_per_pixel/8); /* number of bytes per pixel */
  char *pixel= buffer + (x +y*h_res)*bytes;  /* start of line */

 for(size_t i =0; i<len && (x+i)<h_res; i++) /* iterate pixels */
  {
    color_pixel(pixel+i*bytes, color); /* color each pixel */
  }

  return 0;
}

int draw_hline(uint16_t x, uint16_t y, uint16_t len, uint32_t color)	
{
  unsigned int bytes = (int) ceil((float)bits_per_pixel/8); /* number of bytes per pixel */
  char *pixel= buffer + (x +y*h_res)*bytes;  /* start of line */

 for(size_t i =0; i<len && (x+i)<h_res; i++) /* iterate pixels */
  {
    color_pixel(pixel+i*bytes, color); /* color each pixel */
  }

  return 0;
}

void drawRectangle(uint16_t x,uint16_t y,uint16_t width,uint16_t height, uint32_t color)
{
  for(size_t i=0; i<height; i++) /* draws each line from the top to the bottom of the rectangle */
    draw_hline(x, y+i, width, color); 
}
