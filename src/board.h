#ifndef _BOARD_H__
#define _BOARD_H__
/**
 * @defgroup Board
 * Functions to handle the boards (Single and Multiplayer) and the movement of the enemies and the Qbert 
 * 
 */


#include "controlSprite.h"

/**
 * @brief initializates the board
 * 
 */
void initialize_board();

/**
 * @brief initializates the multiplayer board
 * 
 */
void initialize_multiplayer_board();

/**
 * @brief Prints the current state of the board to the buffer
 * 
 * @return int - Returns 0 if OK
 */
int print_board();

/**
 * @brief Checks the possibility of a movement
 * 
 * @param character -The character that is going to move
 * @param movement - The direction of the movement
 * @return val_mov - Returns NORMAL if the movement is acceptable, OUT_OF_BOUNDARIES if the character leaves the board, QBERT_COLLISION if there is a collision that envolves Qbert or ENEMY_COLLISION if the collision is between enemies
 */
val_mov is_mov_possible(character_t* character, mov movement);

/**
 * @brief Moves Qbert in the board
 * 
 * @param movement - The direction of the movement
 * @param qbert - Qbert
 * @return int - Returns 0 if movement is done
 */
int qbert_mov(mov movement, character_t* qbert);

/**
 * @brief Checks if board is fully painted with the same color
 * 
 * @return true - If the board is fully painted with one color
 * @return false - If the board is not yet completly painted
 */
bool is_board_full();

/**
 * @brief - Repaints the board with a random color
 * 
 */
void reset_board();

/**
 * @brief Moves enemy in the board
 * 
 * @param movement - The direction of the movement
 * @param enemy - The enemy
 * @return int - Returns 0 if nothing wrong
 */
int move_enemy(mov movement, character_t* enemy);

/**
 * @brief Adds a nem enemy to the board
 * 
 * @param enemy - The enemy to be added
 * @return int - Returns 0 if OK
 */
int add_enemy_to_board(character_t* enemy);

/**
 * @brief Deletes an enemy from the board
 * 
 * @param enemy - The enemy to be deleted
 */
void delete_enemy_from_board(character_t* enemy);

/**
 * @brief Prints the current state of the Player 2's board to the buffer
 * 
 * @return int - Returns 0 if OK
 */
int print_multiplayer_board();

/**
 * @brief - Moves the selected square in the Player 2's board 
 * 
 * @param movement - The direction of the movement of the square to be selected
 * @return int - Returns 0 if OK, 1 if out of boundaries
 */
int multiplayer_mov(mov movement);

/**
 * @brief Get the next_enemy X position
 * 
 * @return int - The x position of the selected square where the next enemy should be thrown
 */
int get_next_player_x();

/**
 * @brief Get the next_enemy Y position
 * 
 * @return int - The y position of the selected square where the next enemy should be thrown
 */
int get_next_player_y();

/**
 * @brief Update the position of the next enemy to be thrown
 * 
 * @param movement - The direction of the movement of the square to be selected
 * @return int - Returns 0 if OK, 1 if out of boundaries
 */
int update_next_enemy_position(char movement);

#endif
