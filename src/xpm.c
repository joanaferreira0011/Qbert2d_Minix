#include "xpm.h"

void draw_xpm(character_t *xpm)
{
  int x;
  int y; 
  // Fills the pixels
  uint32_t * colors = NULL;
  if(xpm->transitioning)
    colors = (uint32_t *)xpm->transition_img.bytes;
  else
    colors = (uint32_t * )xpm->img.bytes;
  for(y = xpm->y; y < (xpm->y + xpm->img.height); y++)
  {
    for(x = xpm->x; x < (xpm->x + xpm->img.width); x++)
    {
      sprite_fill_pixel(x, y, *colors);
      colors++;
    }
  }
}

void draw_menu(menu_t * xpm)
{
  int x;
  int y; 
  // Fills the pixels
  uint32_t * colors = (uint32_t * )xpm->menu.bytes;
  for(y = 0; y < (xpm->menu.height); y++)
  {
    for(x = 0; x < (xpm->menu.width); x++)
    {
      sprite_fill_pixel(x, y, *colors);
      colors++;
    }
  }
}

void draw_buttons(button_t* xpm, bool hover)
{
  int x;
  int y; 
  // Fills the pixels
  uint32_t * colors = NULL;
  if(hover)
    colors = (uint32_t * )xpm->button_hover.bytes;

  else
    colors = (uint32_t * )xpm->button.bytes;

  for(y = xpm->y; y < (xpm->y + xpm->button.height); y++)
  {
    for(x = xpm->x; x < (xpm->x + xpm->button.width); x++)
    {
      sprite_fill_pixel(x, y, *colors);
      colors++;
    }
  }
}

void draw_time(time_number_t * time)
{
  int x;
  int y; 
  // Fills the pixels
  uint32_t * colors = (uint32_t * )time->number.bytes;
  for(y = time->y; y < (time->y + time->number.height); y++)
  {
    for(x = time->x; x < (time->x + time->number.width); x++)
    {
      sprite_fill_pixel(x, y, *colors);
      colors++;
    }
  }
}

void draw_mouse(mouse_t * xpm)
{
  int x;
  int y; 
  // Fills the pixels
  uint32_t * colors = (uint32_t * )xpm->mouse.bytes;
  for(y = xpm->y; y < (xpm->y + xpm->mouse.height); y++)
  {
    for(x = xpm->x; x < (xpm->x + xpm->mouse.width); x++)
    {
      sprite_fill_pixel(x, y, *colors);
      colors++;
    }
  }
}


button_t * create_button(xpm_string_t button[], xpm_string_t button_hover[], enum xpm_image_type img_type)
{
  xpm_image_t button_img, button_hover_img;
  if(xpm_load(button, img_type, &button_img) == NULL)
  {
    printf("Failed to read image");
    return NULL;
  }

  if(xpm_load(button_hover, img_type, &button_hover_img) == NULL)
  {
    printf("Failed to read image");
    return NULL;
  }

  button_t * button_st = (button_t *) malloc(sizeof(button_t));
  button_st->button = button_img;
  button_st->button_hover = button_hover_img;
  return button_st;
}
menu_t* create_menu(xpm_string_t map[], enum xpm_image_type img_type)
{
  xpm_image_t menu_img;
  if(xpm_load(map, img_type, &menu_img) == NULL)
  {
    printf("Failed to read image");
    return NULL;
  }

  menu_t * menu = (menu_t *) malloc(sizeof(menu_t));
  menu->menu = menu_img;
  return menu;
}

mouse_t* create_mouse(xpm_string_t map[], enum xpm_image_type img_type)
{
  xpm_image_t mouse_img;
  if(xpm_load(map, img_type, &mouse_img) == NULL)
  {
    printf("Failed to read image");
    return NULL;
  }

  mouse_t * created_mouse = (mouse_t * ) malloc(sizeof(mouse_t));
  created_mouse->mouse = mouse_img;
  created_mouse->x = H_SIZE/2;
  created_mouse->y = V_SIZE/2;
  return created_mouse;
}

time_number_t * create_time(xpm_string_t time[], enum xpm_image_type img_type)
{
  xpm_image_t time_img;
  if(xpm_load(time, img_type, &time_img) == NULL)
  {
    printf("Failed to read time image\n");
    return NULL;
  }
  time_number_t * created_time = (time_number_t *) malloc(sizeof(time_number_t));
  created_time->number = time_img;
  return created_time;
}


character_t * create_xpm(enum xpm_image_type img_type, int x, int y, int xspeed, int yspeed, int type, int x_board, int y_board)
{
  xpm_image_t img, transition_img;
  switch(type)
  {
    case 0:
    if(xpm_load(qbert_xpm, img_type, &img) == NULL)
    {
      printf("Failed to read image qbert");
      return NULL;
    }
    if(xpm_load(walking_qbert_xpm, img_type, &transition_img) == NULL)
    {
      printf("Failed to read image walking qbert");
      return NULL;
    }
    break;
    case 1:
    if(xpm_load(ugg_xpm, img_type, &img) == NULL)
    {
      printf("Failed to read image ugg");
      return NULL;
    }
    if(xpm_load(walking_ugg_xpm, img_type, &transition_img) == NULL)
    {
      printf("Failed to read image walking ugg");
      return NULL;
    }
    break;
    case 2:
    if(xpm_load(sam_xpm, img_type, &img) == NULL)
    {
      printf("Failed to read image same");
      return NULL;
    }
    if(xpm_load(walking_sam_xpm, img_type, &transition_img) == NULL)
    {
      printf("Failed to read image walking sam");
      return NULL;
    }
    break;
    case 3:
    if(xpm_load(coily_xpm, img_type, &img) == NULL)
    {
      printf("Failed to read image coily");
      return NULL;
    }
    if(xpm_load(walking_coily_xpm, img_type, &transition_img) == NULL)
    {
      printf("Failed to read image walking coily");
      return NULL;
    }
    break;
    case 4:
    if(xpm_load(slick_xpm, img_type, &img) == NULL)
    {
      printf("Failed to read image slick");
      return NULL;
    }
    if(xpm_load(walking_slick_xpm, img_type, &transition_img) == NULL)
    {
      printf("Failed to read image walking slick");
      return NULL;
    }
    break;
      
  }
  character_t *xpm = (character_t *) malloc( sizeof(character_t));
  xpm->transition_img = transition_img;
  xpm->img = img;
  xpm->x = x;
  xpm->y = y;
  xpm->xspeed = xspeed;
  xpm->yspeed = yspeed;
  xpm->x_board= x_board;
  xpm->y_board=y_board;
  xpm->type = type;
  xpm->transitioning = false;
  return xpm;
}

void clear_xpm(character_t *xpm)
{
  int x;
  int y; 
  // Fills the pixels
  for(y = xpm->y; y < (xpm->y + xpm->img.height); y++)
  {
    for(x = xpm->x; x < (xpm->x + xpm->img.width); x++)
    {
      sprite_fill_pixel(x, y, 0);
    }
  }
}

void animate_xpm(character_t * xpm)
{
  xpm->x += xpm->xspeed/2;
  xpm->y += xpm->yspeed/2;
  // draw_xpm(xpm);
}

mov check_movement(character_t * xpm)
{
  // clear_xpm(xpm);
  if(xpm->xspeed > 0 && xpm->yspeed == 0)
  {
    return RIGHT;
  }
  else if(xpm->xspeed < 0 && xpm->yspeed == 0)
  {
    return LEFT;
  }
  else if(xpm->yspeed > 0 && xpm->xspeed == 0)
  {
    return DOWN;
  }
  else if(xpm->yspeed < 0 && xpm->xspeed == 0)
  {
    return UP;
  }
  else if(xpm->xspeed > 0 && xpm->yspeed > 0)
  {
    return DIAGONAL_DOWN_RIGHT;
  }
  else if(xpm->xspeed < 0 && xpm->yspeed > 0)
  {
    return DIAGONAL_DOWN_LEFT;
  }
  else if(xpm->xspeed < 0 && xpm->yspeed < 0)
  {
    return DIAGONAL_UP_LEFT;
  }
  else if(xpm->xspeed > 0 && xpm->yspeed < 0)
  {
    return DIAGONAL_UP_RIGHT;
  }
  else
  {
    return STOPPED;
  }
}

mov check_enemy_movement(character_t * enemy)
{
  srand(time(NULL));
  int flag = rand()%2;
  switch(enemy->type)
  {
    case 1:
    case 2:
      return check_movement(enemy);
    case 3:

      if(flag)
        enemy->xspeed = - enemy->xspeed;
      return check_movement(enemy);
    case 4:
      if(flag)
        enemy->yspeed = - enemy->yspeed;
      return check_movement(enemy);
      
  }
  return STOPPED;
}

