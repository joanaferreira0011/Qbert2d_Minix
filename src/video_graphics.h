#pragma once
/**
 * @defgroup Video Graphics
 * Functions to handle the Video Card of the Operating system, providings methods to write to the
 * video memory, information.
 *  
 */

/**
 * @brief - Changing the current VBE mode of the video card
 * In order to further use the properties of the video card, the 
 * mode used must be changed.
 * 
 * @param mode - the desired mode
 * @return int - 0 if successful
 */
int vbe_changemode(uint16_t mode);

/**
 * @brief Get the horizontal resolution
 * 
 * @return unsigned - the horizontal resolution
 */
unsigned get_h_res();

/**
 * @brief Get the horizontal resolution
 * 
 * @return unsigned - the horizontal resolution
 */
unsigned get_v_res();

/**
 * @brief Get the Red Screen Mask 
 * 
 * @return unsigned - the red screen mask
 */
unsigned getRedScreenMask();

/**
 * @brief Get the Green Screen Mask 
 * 
 * @return unsigned - the green screen mask
 */
unsigned getGreenScreenMask();

/**
 * @brief Get the Blue Screen Mask 
 * 
 * @return unsigned - the blue screen mask
 */
unsigned getBlueScreenMask();

/**
 * @brief Get the Bits Per Pixel 
 * 
 * @return unsigned - the number of bits per pixel
 */
unsigned getBitsPerPixel();

/**
 * @brief - Filling a pixel into the memory
 * In order to actually paint information in the video memory, it is needed to provide their 
 * coordinates and actually write it. This function however does not write to the 
 * actual video memory, but to a secondary buffer, since we are using a double
 * buffering technique.
 * 
 * @param x - the x coordinate of the pixel
 * @param y - the y coordinate of the pixel
 * @param color - the actual color of the pixel
 */
void sprite_fill_pixel(int x, int y, uint32_t color);

/**
 * @brief - The clear of the whole screen
 * 
 */
void sprite_clear_screen();

/**
 * @brief Drawing of a rectangle
 * In order to draw the full board where the Q*bert is, it is needed to provide 
 * a method to write rectangles with the same size between themselves.
 * 
 * @param x - the x coordinate of the rectangle
 * @param y - the y coordinate of the rectangle
 * @param width - the width of said rectangle
 * @param height - the height of said rectangle
 * @param color - the color of the rectangles
 */
void drawRectangle(uint16_t x,uint16_t y,uint16_t width,uint16_t height, uint32_t color);

/**
 * @brief Coloring a single pixel
 * The coloring of a single pixel position with a given color
 * 
 * @param pixel - the memory position of said pixel
 * @param color - the actual color
 */
void color_pixel(char *pixel, uint32_t color);

/**
 * @brief Drawing a full horizontal line of pixels
 * In order to ease the drawing of each single pixel, it was implemented a secondary function
 * who would first draw each horizontal line
 * 
 * @param x - the x coordinate 
 * @param y - the y coordinate
 * @param len - the length of the line
 * @param color - the color of the line
 * @return int - 0 if sucessful
 */
int draw_hline(uint16_t x, uint16_t y, uint16_t len, uint32_t color);

/**
 * @brief Copying the buffer to the video memory
 * Since we are using a double buffering technique, all pixel information is firstly written 
 * to a secondary buffer, then being called this function in order to copy that information
 * into the video memory itself
 * 
 */
void draw_screen();

/**
 * @brief Clear the secondary of all information
 * 
 */
void clear_buffer();
