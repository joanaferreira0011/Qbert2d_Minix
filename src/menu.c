#include "menu.h"
#include "menu_xpm/menu.xpm"
#include "menu_xpm/Singleplayer.xpm"
#include "menu_xpm/Multiplayer.xpm"
#include "menu_xpm/Credits.xpm"
#include "menu_xpm/Exit.xpm"
#include "menu_xpm/Singleplayer_hover.xpm"
#include "menu_xpm/Multiplayer_hover.xpm"
#include "menu_xpm/Credits_hover.xpm"
#include "menu_xpm/Exit_hover.xpm"
#include "menu_xpm/credits.xpm"
#include "menu_xpm/credits_exit.xpm"
#include "menu_xpm/credits_exit_hover.xpm"
#include "menu_xpm/up_arrow.xpm"
#include "menu_xpm/down_arrow.xpm"
#include "menu_xpm/left_arrow.xpm"
#include "menu_xpm/right_arrow.xpm"
#include "menu_xpm/up_arrow_click.xpm"
#include "menu_xpm/down_arrow_click.xpm"
#include "menu_xpm/left_arrow_click.xpm"
#include "menu_xpm/right_arrow_click.xpm"
#include "menu_xpm/mp_menu.xpm"
#include "menu_xpm/player_1.xpm"
#include "menu_xpm/player_2.xpm"
#include "menu_xpm/player_1_hover.xpm"
#include "menu_xpm/player_2_hover.xpm"
#include "menu_xpm/waiting_menu.xpm"
#include "menu_xpm/game_over.xpm"

static menu_t * menu;
static menu_t * credits;
static menu_t * mp_menu;
static menu_t * waiting_menu;
static menu_t * game_over_menu;
static button_t * credits_ex, *sp, *mp, *cr, *ex, *u_arrow, *d_arrow, *l_arrow, *r_arrow, *p_1, *p_2;


void launch_menu()
{
  printf("Loading main\n");
  menu = create_menu(menu_xpm, XPM_8_8_8_8);
  printf("Loading credits\n");
  credits = create_menu(credits_xpm, XPM_8_8_8_8);
  printf("Loading mp menu\n");
  mp_menu = create_menu(mp_menu_xpm, XPM_8_8_8_8);
  printf("Loading mp waiting menu\n");
  waiting_menu = create_menu(waiting_menu_xpm, XPM_8_8_8_8);
  printf("Loading mp game over menu\n");
  game_over_menu = create_menu(game_over_xpm, XPM_8_8_8_8);
  sp = create_button(Singeplayer_xpm, Singeplayer_hover_xpm, XPM_8_8_8_8);
  sp->x = 130;
  sp->y = 300;
  mp = create_button(Multiplayer_xpm, Multiplayer_hover_xpm, XPM_8_8_8_8);
  mp->x = 500;
  mp->y = 300;
  cr = create_button(Credits_xpm, Credits_hover_xpm, XPM_8_8_8_8);
  cr->x = 130;
  cr->y = 400;
  ex = create_button(Exit_xpm, Exit_hover_xpm, XPM_8_8_8_8);
  ex->x = 500;
  ex->y = 400;
  credits_ex = create_button(credits_exit_xpm, credits_exit_hover_xpm, XPM_8_8_8_8);
  credits_ex->x = 50;
  credits_ex->y = 700;
  u_arrow = create_button(up_arrow_xpm, up_arrow_click_xpm, XPM_8_8_8_8);
  u_arrow->x = 500;
  u_arrow->y = 400;
  d_arrow = create_button(down_arrow_xpm, down_arrow_click_xpm, XPM_8_8_8_8);
  d_arrow->x = 500;
  d_arrow->y = 550;
  l_arrow = create_button(left_arrow_xpm, left_arrow_click_xpm, XPM_8_8_8_8);
  l_arrow->x = 350;
  l_arrow->y = 550;
  r_arrow = create_button(right_arrow_xpm, right_arrow_click_xpm, XPM_8_8_8_8);
  r_arrow->x = 650;
  r_arrow->y = 550;
  p_1 = create_button(player_1_xpm, player_1_hover_xpm, XPM_8_8_8_8);
  p_1->x = 130;
  p_1->y = 350;
  p_2 = create_button(player_2_xpm, player_2_hover_xpm, XPM_8_8_8_8);
  p_2->x = 500;
  p_2->y = 350;
}

void menu_draw(mouse_pos_t mouse_pos)
{
  switch(mouse_pos)
  {
    case SP:
    draw_menu(menu);
    draw_buttons(sp, true);
    draw_buttons(mp, false);
    draw_buttons(cr, false);
    draw_buttons(ex, false);
    break;
    case MP:
    draw_menu(menu);
    draw_buttons(sp, false);
    draw_buttons(mp, true);
    draw_buttons(cr, false);
    draw_buttons(ex, false);
    break;
    case CR:
    draw_menu(menu);
    draw_buttons(sp, false);
    draw_buttons(mp, false);
    draw_buttons(cr, true);
    draw_buttons(ex, false);
    break;
    case EX:
    draw_menu(menu);
    draw_buttons(sp, false);
    draw_buttons(mp, false);
    draw_buttons(cr, false);
    draw_buttons(ex, true);
    break;
    case NOT:
    default:
    draw_menu(menu);
    draw_buttons(sp, false);
    draw_buttons(mp, false);
    draw_buttons(cr, false);
    draw_buttons(ex, false);
    break;
  }
}

void draw_credits(mouse_pos_t mouse_pos)
{
  switch(mouse_pos)
  {
    case CR_EX:
      draw_menu(credits);
      draw_buttons(credits_ex, true);
      break;
    default:
      draw_menu(credits);
      draw_buttons(credits_ex, false);
      break;
  }
}

void draw_mp_menu(mouse_pos_t mouse_pos)
{
  switch(mouse_pos)
  {
    case PLAYER_1:
      draw_buttons(p_1, true);
      draw_buttons(p_2, false);
      break;

    case PLAYER_2:
      draw_buttons(p_1, false);
      draw_buttons(p_2, true);
      break;

    default:
      draw_buttons(p_1, false);
      draw_buttons(p_2, false);
      break;
  }
}

void draw_mp(mouse_pos_t mouse_pos, bool click)
{
  switch(mouse_pos)
  {
    case R_ARROW:
      draw_menu(mp_menu);
      if(click)
        draw_buttons(r_arrow, true);
      else
        draw_buttons(r_arrow, false);
      
      draw_buttons(l_arrow, false);
      draw_buttons(u_arrow, false);
      draw_buttons(d_arrow, false);
      break;
    case L_ARROW:
      draw_menu(mp_menu);
      draw_buttons(r_arrow, false);
      if(click)
        draw_buttons(l_arrow, true);
      else
        draw_buttons(l_arrow, false);
      
      draw_buttons(u_arrow, false);
      draw_buttons(d_arrow, false);
      break;
    case U_ARROW:
      draw_menu(mp_menu);
      draw_buttons(r_arrow, false);
      draw_buttons(l_arrow, false);
      if(click)
        draw_buttons(u_arrow, true);
      else
        draw_buttons(u_arrow, false);

      draw_buttons(d_arrow, false);
      break;
    case D_ARROW:
      draw_menu(mp_menu);
      draw_buttons(r_arrow, false);
      draw_buttons(l_arrow, false);
      draw_buttons(u_arrow, false);
      if(click)
        draw_buttons(d_arrow, true);
      else
        draw_buttons(d_arrow, false);
        
      break;
    default:
      draw_menu(mp_menu);
      draw_buttons(r_arrow, false);
      draw_buttons(l_arrow, false);
      draw_buttons(u_arrow, false);
      draw_buttons(d_arrow, false);
  }
}

void draw_waiting_menu()
{
  draw_menu(waiting_menu);
}

void draw_game_over()
{
  draw_menu(game_over_menu);
}
