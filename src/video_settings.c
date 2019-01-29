#include "video_settings.h"

void * start_video()
{
  char * video_mem =  vg_init(DIRECT_32_BITS);

  if(video_mem == NULL)
  {
    printf("Failed to allocate video memory!\n");
    return NULL;
  }
  return video_mem; 
}

