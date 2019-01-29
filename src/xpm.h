#ifndef _XPM_H__
#define _XPM_H__
/**
 * @defgroup XPM 
 * Series of functions to parse the information coming from an image
 * of the standard XPM as well as handling the writing of them and their animations
 */

#include <lcom/lcf.h>
#include <lcom/pixmap.h>
#include <lcom/read_xpm.h>
#include "video_graphics.h"
#include "video.h"
#include "game.h"

extern xpm_string_t qbert_xpm[];
extern xpm_string_t walking_qbert_xpm[];
extern xpm_string_t ugg_xpm[];
extern xpm_string_t sam_xpm[];
extern xpm_string_t coily_xpm[];
extern xpm_string_t slick_xpm[];
extern xpm_string_t walking_ugg_xpm[];
extern xpm_string_t walking_sam_xpm[];
extern xpm_string_t walking_coily_xpm[];
extern xpm_string_t walking_slick_xpm[];

/**
 * @brief Create a xpm object
 * The creation of the characters used on the game
 * 
 * @param xpm_image_type - the type of image wanted
 * @param x - the x coordinate
 * @param y - the y coordinate
 * @param xspeed - their speed on x
 * @param yspeed - their speed on y
 * @param type - the type of image they are
 * @param x_board - their x position on the board
 * @param y_board - their y position on the board
 * @return character_t* the actual character
 */
character_t * create_xpm(enum xpm_image_type img_type, int x, int y, int xspeed, int yspeed, int type, int x_board, int y_board);

/**
 * @brief The drawing of the xpm itself
 * 
 * @param xpm - the character to be drawn.
 */
void draw_xpm(character_t *xpm);

/**
 * @brief The clear of the character of the screen
 * 
 * @param xpm - the character to clear
 */
void clear_xpm(character_t * xpm);

/**
 * @brief The check of the next enemy movement before it happens
 * In order to check for collisions and such, the enemy movement must be checked in order to 
 * act upon collisions and falling out of the map.
 * 
 * @param enemy - the enemy to check 
 * @return mov - where will the enemy go
 */
mov check_enemy_movement(character_t * enemy);


/**
 * @brief The animation of the movement of a xpm
 * The movement of a character provided with their xspeed and yspeed values
 * 
 * @param xpm - the actual character
 */
void animate_xpm(character_t * xpm);


/**
 * @brief The drawing of the current time number
 * Each number is drawn separatedly using this function
 * 
 * @param time - the number sprite to be drawn
 */
void draw_time(time_number_t * time);

/**
 * @brief Create a menu object
 * The creation of a menu
 * 
 * @param menu - the current menu to be created
 * @param xpm_image_type - the type of image wanted
 * @return menu_t* - the menu itself
 */
menu_t* create_menu(xpm_string_t menu[], enum xpm_image_type img_type);

/**
 * @brief Drawing of the menu
 * The drawing of the menu provided
 * 
 * @param xpm - the current menu being used
 */
void draw_menu(menu_t * xpm);

/**
 * @brief The drawing of the mouse sprite
 * 
 * @param xpm - the mouse sprite
 */
void draw_mouse(mouse_t * xpm);

/**
 * @brief Create a mouse object
 * 
 * @param map - The image wanted to be used as a mouse during the execution of the process
 * @param xpm_image_type - The type of image wanted
 * @return mouse_t* - the mouse itself
 */
mouse_t* create_mouse(xpm_string_t map[], enum xpm_image_type img_type);

/**
 * @brief The drawing of the button
 * The drawing of the button provided to it
 * 
 * @param xpm - the button to be drawn
 * @param hover - if it is being hovered or not 
 * 
 */
void draw_buttons(button_t* xpm, bool hover);

/**
 * @brief Create a button object
 * The creation of the button image 
 * 
 * @param button - the button image
 * @param button_hover - the image when it is being hovered
 * @param xpm_image_type - the type of image being used
 * @return button_t* - the button itself
 */
button_t * create_button(xpm_string_t button[], xpm_string_t button_hover[], enum xpm_image_type img_type);

/**
 * @brief Create a time object
 * The creation of each time number with the given font
 * 
 * @param time - The current font number 
 * @param xpm_image_type - The type of image wanted
 * @return time_number_t* - The actual number
 */
time_number_t * create_time(xpm_string_t time[], enum xpm_image_type img_type);

// mov check_movement(character_t * xpm);

#endif
