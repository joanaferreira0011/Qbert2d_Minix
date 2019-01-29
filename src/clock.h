#pragma once
/**
 * @defgroup Clock
 * Series of functions to the rtc information and parse it to be written into the video memory.
 * They're to display the time to the user.
 * 
 */
#include <lcom/lcf.h>
#include "rtc.h"
#include "game.h"
#include "xpm.h"

/**
 * @brief Initialize the font numbers sprites in order to print them in the screen
 * The time sprites must be initialized with their respective images in order to 
 * create a display of time. 
 * 
 */
void initialize_time();


/**
 * @brief The displaying of the actual time on the screen
 * The time is displayed on the screen using this function.
 * 
 */
void display_time();
