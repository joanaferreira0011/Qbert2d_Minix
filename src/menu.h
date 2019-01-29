#pragma once
/**
 * @defgroup Menu
 * Series of functions to handle the writing of several different menus throughout the process
 * 
 */

#include <lcom/lcf.h>
#include "game.h"
#include "mouse.h"
#include "keyboard.h"
#include "i8042.h"


/**
 * @brief Initiliaziatin of all menus
 * All menus and their buttons are firstly initialized in order to be ready from the start
 * to be used when called
 * 
 */
void launch_menu();

/**
 * @brief - Drawing the main menu
 * The drawing of the main menu, with its mouse position
 * 
 * @param mouse_pos - the current position of the mouse, in order to check if any button is being used 
 */
void menu_draw(mouse_pos_t mouse_pos);


/**
 * @brief - Drawing of the credits menu
 * The drawing of a small credits menu
 * 
 * @param mouse_pos - the current position of the mouse, in order to check if it is over the exit button
 */
void draw_credits(mouse_pos_t mouse_pos);

/**
 * @brief - Drawing of the Player 2 multiplayer menu
 * The drawing of all the buttons associated with the multiplayer game mode.
 * 
 * @param mouse_pos - the current position of the mouse
 * @param click - if there was a click of the mouse for a graphical update.
 */
void draw_mp(mouse_pos_t mouse_pos, bool click);

/**
 * @brief - Drawing of the menu where you choose your Player
 * The purpose of this menu serves to give the first player the opportunity to choose which player 
 * he wants to be.
 * 
 * @param mouse_pos - the current position of the mouse
 */

void draw_mp_menu(mouse_pos_t mouse_pos);

/**
 * @brief - Drawing of the waiting menu
 * After the first player chooses a Player option, he has now to wait for the other
 * player to connect, giving him this menu
 * 
 */

void draw_waiting_menu();

/**
 * @brief - Drawing the game over menu
 * When the player collides with a enemy, he loses the game, making this 
 * menu show up.
 * 
 */
void draw_game_over();
