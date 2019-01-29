#pragma once
/**
 * @defgroup VBE
 * Functions to handle reading the current information of the VBE mode being used, as well as 
 * additional information about the VBE controller driver.
 */
#include <lcom/lcf.h>

int vbe_get_info_mode(uint16_t mode);

int vbe_controller_info(vg_vbe_contr_info_t * vbe);

#define SEGMENT(x) ((x >> 16) << 4) 
#define OFFSET(x)  (x & 0x0FFFF)

struct VbeInfoBlock{
  char VbeSignature[4];
  uint16_t VbeVersion;
  char*   OemStringPtr;
  char * Capabilities;
  char * VideoModePtr;
  uint16_t TotalMemory;
  uint16_t OemSoftwareRev;
  char * OemVendorNamePtr;
  char * OemProductNamePt;
  char * OemProductRevPtr;

  uint8_t Reserved[222];
  uint8_t OemData[256]; 
}__attribute__ ((packed));
