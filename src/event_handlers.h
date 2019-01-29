#pragma once
/**
 * @file defgroup Event Handlers
 * Series of functions to handle events coming from interrupts. Through them, all comunication
 * with the devices is done.
 * 
 */

#include <lcom/lcf.h>
#include "game.h"
#include "ps2Mouse.h"
#include "i8042.h"
#include "mouse.h"
#include "menu.h"
#include "video.h"
#include "xpm.h"
#include "board.h"
#include "serial_port.h"
#include "clock.h"
#include "rtc.h"

/**
 * @brief - Reading the mouse information
 * Function to parse the information coming from the mouse and handle it 
 * according to the current situation
 * 
 * @return int - 0 if successful
 */
int read_mouse();

/**
 * @brief - Event handler for the timer
 * Mostly used to control frame rate and animations, the timer handles all communication
 * with the video memory itself.
 * 
 * @return int - 0 if successful
 */
int timer_IH();

/**
 * @brief - Event handler for the Keyboard
 * Mainly used to parse movement of the Q*bert, this event handler parsers which character
 * is pressed as well what to do with that information.
 * 
 * @return int - 0 if successful
 */
int kbc_mov_IH();

/**
 * @brief - Initializing board values
 * Initializes some key variables about the board as well creating the character of the Q*bert
 * 
 */
void init_board_values();

/**
 * @brief - Event handler of the serial port
 * Reads the information coming from the serial port and parses what to do with that information
 * and the importance of it as well.
 * 
 * @return int - 0 if successful
 */
int read_serial();

/**
 * @brief - Event Handler for the rtc
 * Handling both the periodic interrupts as well as update interrupts from the rtc.
 * 
 * @return int - 0 if successful
 */
int rtc_ev();

/**
 * @brief - Launching a new enemy on the map event
 * Handling the creation of the enemy as well as its positioning on the board,
 * which is random.
 * 
 * @return int - 0 if successful
 */
int new_enemy();

/**
 * @brief - Launching an enemy given a position
 * For the multiplayer option, an enemy is launched at a position chosen by Player 2.
 * 
 * @param x_board - the board x
 * @param y_board - the board y
 * @return int - 0 if successful
 */
int new_enemy_with_pos(int x_board, int y_board);
