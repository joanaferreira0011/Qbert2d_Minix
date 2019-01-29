#include "mouse.h"
#include "mouse.xpm"

static mouse_t* mouse;

void mouse_start()
{
  mouse = create_mouse(mouse_xpm, XPM_8_8_8_8);
  draw_mouse(mouse);
  draw_screen();
}

mouse_pos_t mouse_update(struct packet* pp,bool main_menu)
{
  if(mouse->x + pp->delta_x < H_SIZE && mouse->x + pp->delta_x > 0)
  {
    mouse->x += pp->delta_x;
  }
  
  if(mouse->y - pp->delta_y < V_SIZE && mouse->y - pp->delta_y > 0)
  {
    mouse->y -= pp->delta_y;
  }
  if(main_menu)
  {
    if(mouse->x >= 130 && mouse->y >= 300 && mouse->x <= 130 + 318 && mouse->y <= 300 + 59)
      return SP;
    if(mouse->x >= 500 && mouse->y >= 300 && mouse->x <= 500 + 318 && mouse->y <= 300 + 59)
      return MP;
    if(mouse->x >= 130 && mouse->y >= 400 && mouse->x <= 130 + 318 && mouse->y <= 400 + 59)
      return CR;
    if(mouse->x >= 500 && mouse->y >= 400 && mouse->x <= 500 + 318 && mouse->y <= 400 + 59)
      return EX;
    if(mouse->x >= 50 && mouse->y >= 700 && mouse->x <= 50 + 223 && mouse->y <= 700 + 85)
      return CR_EX;
  }
  else
  {
    if(mouse->x >= 500 && mouse->y >= 400 && mouse->x <= 500 + 70 && mouse->y <= 400 + 70)
      return U_ARROW;
    if(mouse->x >= 500 && mouse->y >= 550 && mouse->x <= 500 + 70 && mouse->y <= 550 + 70)
      return D_ARROW;
    if(mouse->x >= 350 && mouse->y >= 550 && mouse->x <= 350 + 70 && mouse->y <= 550 + 70)
      return L_ARROW;
    if(mouse->x >= 650 && mouse->y >= 550 && mouse->x <= 650 + 70 && mouse->y <= 550 + 70)
      return R_ARROW;
    if(mouse->x >= 130 && mouse->y >= 350 && mouse->x <= 130 + 318 && mouse->y <= 350 + 70)
      return PLAYER_1;
    if(mouse->x >= 500 && mouse->y >= 350 && mouse->x <= 500 + 318 && mouse->y <= 350 + 70)
      return PLAYER_2;
    
  }
  
  
  return NOT;
}

void mouse_draw()
{
  draw_mouse(mouse);
}

int button_pushed(struct packet* pp)
{
  return pp->lb;
}
