#include <lcom/lcf.h>
#include "vbe.h"  
#include "video.h"
vbe_mode_info_t vbe_info;

int vbe_get_info_mode(uint16_t mode)
{
  void * virtual_address= lm_init(true); // Initializes the low memory area
  mmap_t map;
  phys_bytes buf;
  struct reg86u r; 
  memset(&r, 0, sizeof(r));
  if(virtual_address == NULL) // Tests if it was to able initialize it
  {
    printf("Failed to initialize the low memory area\n");
    return 1;
  }

  vbe_mode_info_t* 	vmi_p;
  vmi_p = lm_alloc(sizeof(vbe_mode_info_t), &map); // Allocs memory for the Bios Call

  if(vmi_p == NULL)
  {
    printf("Failed to allocate the low memory area\n");
    return 2;
  }
  

  buf = map.phys;
  r.u.w.ax = VBE_GET_MODE_INFO; /* VBE get mode info */
  /* translate the buffer linear address to a far pointer */
  r.u.w.es = PB2BASE(buf); /* set a segment base */
  r.u.w.di = PB2OFF(buf); /* set the offset accordingly */
  r.u.w.cx = mode; // Set the mode of the call
  r.u.b.intno = BIOS_VIDEO; 
  
  if( sys_int86(&r) != OK ) { /* call BIOS */
    printf("Failed to call BIOS!|\n");
    return 3;
  }
  //Saves the information to the struct and frees the low memory
  vmi_p =  map.virt;
  vbe_info = * vmi_p;
  lm_free(&map);

  return 0;
}


int vbe_controller_info(vg_vbe_contr_info_t  * vbe_contr_info)
{
  // As required in the handout, the signature is changed to VBE2
  struct VbeInfoBlock controller_info;
  memcpy(controller_info.VbeSignature, "VBE2", 4);

  void * virtual_address= lm_init(false); // Intiliazes the low memory area

  mmap_t map;
  phys_bytes buf;
  struct reg86u r; 

  
  memset(&r, 0, sizeof(r));
  if(virtual_address == NULL) // Checks if it was to initialize it 
  {
    printf("Failed to initialize the low memory area\n");
    return 1;
  }
  // struct VbeInfoBlock info_block;
  struct VbeInfoBlock * vbe;
  vbe = lm_alloc(sizeof(struct VbeInfoBlock), &map); //allocates the memory for the struct VbeInfoBlock

  if(vbe == NULL) // Check if it was able to allocate
  {
    printf("Failed to allocate the low memory area\n");
    return 2;
  }
 

  buf = map.phys;
  r.u.w.ax = VBE_CTRL_INFO; /* VBE get mode info */
  /* translate the buffer linear address to a far pointer */
  r.u.w.es = PB2BASE(buf); /* set a segment base */
  r.u.w.di = PB2OFF(buf); /* set the offset accordingly */
  r.u.b.intno = BIOS_VIDEO; 
  
  if( sys_int86(&r) != OK ) { /* call BIOS */
    printf("Failed to call BIOS!|\n");
    return 3;
  }
  // Saves all the parameter, converting all far pointers into virtual addresses
  uint32_t phys = (uint32_t) vbe->OemStringPtr;
  vbe_contr_info->OEMString = (char *) ((uint32_t)virtual_address +  SEGMENT(phys) + OFFSET(phys));
  phys = (uint32_t) vbe->OemVendorNamePtr;;
  vbe_contr_info->OEMVendorNamePtr = (char *) ((uint32_t)virtual_address +  SEGMENT(phys) + OFFSET(phys));
  phys = (uint32_t) vbe->OemProductNamePt;
  vbe_contr_info->OEMProductNamePtr = (char *) ((uint32_t)virtual_address +  SEGMENT(phys) + OFFSET(phys));
  phys = (uint32_t) vbe->OemProductRevPtr;;
  vbe_contr_info->OEMProductRevPtr = (char *) ((uint32_t)virtual_address +  SEGMENT(phys) + OFFSET(phys));
  phys = (uint32_t) vbe->VideoModePtr;;
  vbe_contr_info->VideoModeList = (uint16_t *) ((uint32_t)virtual_address +  SEGMENT(phys) + OFFSET(phys));
  memcpy(vbe_contr_info->VBESignature, vbe->VbeSignature, 4);
  vbe_contr_info->VBEVersion[0] = vbe->VbeVersion;
  vbe_contr_info->VBEVersion[1] = vbe->VbeVersion >> 8;
  vbe_contr_info->TotalMemory = vbe->TotalMemory * 64; 
  
  lm_free(&map);

  return 0;
}
