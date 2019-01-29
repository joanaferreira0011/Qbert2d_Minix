#pragma once
/**
 * @defgroup Mouse 
 * Series of functions to handle mouse collisions as well as the graphical drawing
 * of the mouse.
 */

#include <lcom/lcf.h>
#include "game.h"
#include "xpm.h"
#include "ps2Mouse.h"


/**
 * @brief - The initialization of all the values of the mouse
 * The mouse must be initialized at the beggining so it can be painted in the screen.
 * 
 */
void mouse_start();

/**
 * @brief - The update of the current mouse position
 * When a packet of the mouse is finished, its position is incremented on this function, in order to
 * be drawn later.
 * 
 * @param pp - The packet carrying the mouse information 
 * @param main_menu - The current information being displayed on the screen
 * @return mouse_pos_t - The position regarding objects on screen.
 */
mouse_pos_t mouse_update(struct packet* pp, bool main_menu);

/**
 * @brief - The check if a mouse button was pushed during this last interrupt
 * 
 * @param pp - The packet carrying the mouse information
 * @return int - 1 if pushed 
 */
int button_pushed(struct packet* pp);

/**
 * @brief - The drawing of the actual mouse on the screen
 * 
 */
void mouse_draw();

