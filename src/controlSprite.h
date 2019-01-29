#pragma once
/**
 * @file controlSprite
 * Series of functions to control the enemies on the board. Mostly used in order to parse handle
 * their animations as well as what happens on the board.
 * 
 */

#include <lcom/lcf.h>
#include <stdint.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <lcom/read_xpm.h>
#include "video_graphics.h"
#include "keyboard.h"
#include "video.h"
#include "i8042.h"
#include "rtc.h"
#include "game.h"
#include "board.h"
#include "xpm.h"
/**
 * @brief - The Determination of what pattern is related to a specific movement
 * In the creation of a enemy sprite, its movement must be assigned, thus the significance
 * of this function
 * 
 * @param sprite 
 */
void pattern_movement(character_t * sprite);

/**
 * @brief Adds an enemy to the array of enemies
 * 
 * @param enemy - The enemy to be added
 * @return int - Returns 0 if the enemy is succesfully added and 1 if the array is full
 */
int add_enemy_to_array(character_t* enemy);

/**
 * @brief - Moves all the enemies in the 'enemies' array
 * 
 * @return int - Returns 0 if all the movements are OK and 1 if there is a Qbert Collision (Game over)
 */
int enemies_mov_hd();

/**
 * @brief - Draws all enemies of the 'enemies' array in the buffer
 * 
 */
void draw_all_enemies();

/**
 * @brief Deletes all enemies of the 'enemies' array
 * 
 */
void delete_all_enemies();

/**
 * @brief Makes all the enemies transition from the animation stage to the final stage of the movement
 * 
 */
void transition_all_enemies();

/**
 * @brief Set Qbert speed to 0
 * 
 * @param qbert - The Qbert
 */
void clear_qbert_movement(character_t * qbert);



