#pragma once
/**
 * @defgroup Video Settings 
 * Function to initialize the current video settings wanted for this process.
 */
#include <lcom/lcf.h>
#include "video_graphics.h"
#include "video.h"

/**
 * @brief The starting of the wanted video setting for the course of the process
 * 
 * @return void* - Pointer to the video memory itself
 */
void * start_video();

