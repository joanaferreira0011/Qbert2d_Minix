#ifndef _GAME_H_
#define _GAME_H_
/**
 * @defgroup Game
 * @{
 * 
 * The definition of all the objects designed for this game itself
 * 
 */

#define SP_GAME         0
#define MP_GAME         1
#define CREDITS         2
#define EXIT            3
#define CONTINUE        4

/**
 * @brief Characters type
 * 
 */
typedef enum {
    QBERT,
    ENEMY1,
    EMPTY,
    NEXT_ENEMY
} character_name;


/**
 * @brief Validation of the movements
 * 
 */
typedef enum {
    NORMAL, /**< The movement is acceptable */
    ENEMY_COLLISION, /**< Collision between enemies */
    QBERT_COLLISION, /**< Collision that envolves Qbert */
    OUT_OF_BONDARIES, /**< The character leaves the board */
    STOP /**< The character stops */
} val_mov;

/**
 * @brief Each square that will make the board
 * 
 */
typedef struct square
{
    bool color; /**< True if the square was painted by the Qbert */
    character_name name; /**< The character that is in the square */
} square;

/**
 * @brief Position
 * 
 */
typedef struct position {
    int x;
    int y;
} position;

/**
 * @brief The games board
 * 
 */
typedef struct board
{
    position qbert_position; /**< Qbert's position in the board */
    position next_enemy; /**< Next enemy position for multilayer game */
    square matrix[10][10]; /**< The boards structure */
    uint number_squares_painted; /**< Number of squares already painted by the Qbert in the current round */
    uint number_horizontal_squares; /**< Number of horizontal squares in the board */
    uint number_vertical_squares; /**< Number of vertical squares in the board */

} board;

/**
 * @brief Character
 * 
 */
typedef struct{
  xpm_image_t img; /**< The image of the character */
  int x, y; /**< The x and y position of the character in the buffer */
  int x_board, y_board; /**< The x and y position of the character in the board*/
  int xspeed, yspeed; /**< The x and y speed of the character*/
  int type; /**< The type of the character*/
  xpm_image_t transition_img; /**< The animated image of the character */
  bool transitioning; /**< True if the character is current in the middle of an animation*/
}character_t;


/**
 * @brief Definition of current mouse positions, according to screen
 * 
 * This definition is used to keep track exactly where the mouse during the menus, in order to know
 * what is necessary to graphically and logically in terms of the game.
 */
typedef enum{
    SP, /**< Indicates the Singeplayer button. */
    MP, /**< Indicates the Multiplayer button. */
    CR, /**< Indicates the Credits button. */
    EX, /**< Indicates the Exit button. */
    NOT, /**< Indicates when the Mouse is nowhere in particular. */
    CR_EX, /**< Indicates the exit button the credits. */
    R_ARROW, /**< Indicates the right arrow on the multiplayer mode of the game. */
    L_ARROW, /**< Indicates the left arrow on the multiplayer mode of the game. */
    U_ARROW, /**< Indicates the upper arrow on the multiplayer mode of the game. */
    D_ARROW, /**< Indicates the down arrow on the multiplayer mode of the game. */
    PLAYER_1, /**< Indicates the selection of player 1 on the multiplayer menu. */
    PLAYER_2 /** < Indicates the selection of player 2 on the multiplayer menu. */
} mouse_pos_t;


/**
 * @brief Movements in the board
 * 
 */
typedef enum{
    UP,
    DOWN,
    LEFT,
    RIGHT,
    DIAGONAL_UP_RIGHT,
    DIAGONAL_UP_LEFT,
    DIAGONAL_DOWN_RIGHT,
    DIAGONAL_DOWN_LEFT,
    STOPPED
} mov;

/**
 * @brief Definition of the sprite of each menu image
 * This images represent the background of each menu during the execution of the process
 * 
 */
typedef struct
{
  xpm_image_t menu;/**< The image container itself.*/
}menu_t;


/**
 * @brief The definition of the sprite of each button image
 * During the execution of the program, there are several buttons which are clickable and hoverable
 * 
 */
typedef struct
{
    xpm_image_t button; /**< The image of the button itself*/
    xpm_image_t button_hover; /**< The image of the button when it is being hovered*/
    int x, y;/**< Coordinates of the button */
}button_t;


/**
 * @brief The definition of the mouse sprite
 * The execution of several tasks require the use of the mouse, thus being provided a visual aid in
 * order to make that happen.
 * 
 */
typedef struct
{
  xpm_image_t mouse; /**< The image of the mouse. */
  int x, y; /**< The current coordinates of the cursor */
}mouse_t;


/**
 * @brief The definition of the time sprite
 * During the playthrough of the actual game, a time is being displayed at the corner of the 
 * screen. This was necessary to define the font used for those numbers.
 * 
 */
typedef struct
{
    xpm_image_t number;
    int x, y;
}time_number_t;
#endif
