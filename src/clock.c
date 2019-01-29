#include "clock.h"
#include "font_xpm/0.xpm"
#include "font_xpm/1.xpm"
#include "font_xpm/2.xpm"
#include "font_xpm/3.xpm"
#include "font_xpm/4.xpm"
#include "font_xpm/5.xpm"
#include "font_xpm/6.xpm"
#include "font_xpm/7.xpm"
#include "font_xpm/8.xpm"
#include "font_xpm/9.xpm"
#include "font_xpm/two_point.xpm"
extern uint8_t seconds, minutes, hours;
static time_number_t *zero, *one, *two, *three, *four, *five, *six, *seven, *eight, *nine, *two_points;
static int hours_x = 880, minutes_x = 930, seconds_x = 980;
static int y = 700;

void initialize_time()
{
  zero = create_time(zero_xpm, XPM_8_8_8_8);
  zero->y = y;
  one = create_time(one_xpm, XPM_8_8_8_8);
  one->y = y;
  two = create_time(two_xpm, XPM_8_8_8_8);
  two->y = y;
  three = create_time(three_xpm, XPM_8_8_8_8);
  three->y = y;
  four = create_time(four_xpm, XPM_8_8_8_8);
  four->y = y;
  five = create_time(five_xpm, XPM_8_8_8_8);
  five->y = y;
  six = create_time(six_xpm, XPM_8_8_8_8);
  six->y = y;
  seven = create_time(seven_xpm, XPM_8_8_8_8);
  seven->y = y;
  eight = create_time(eight_xpm, XPM_8_8_8_8);
  eight->y = y;
  nine = create_time(nine_xpm, XPM_8_8_8_8);
  nine->y = y;
  two_points = create_time(two_point_xpm, XPM_8_8_8_8);
  two_points->y = y;
}

void draw_number(uint8_t time, int x)
{
  switch(time)
  {
    case 0:
      zero->x = x;
      draw_time(zero);
      break;
    case 1:
      one->x = x;
      draw_time(one);
      break;
    case 2:
      two->x = x;
      draw_time(two);
      break;
    case 3:
      three->x = x;
      draw_time(three);
      break;
    case 4:
      four->x = x;
      draw_time(four);
      break;
    case 5:
      five->x = x;
      draw_time(five);
      break;
    case 6:
      six->x = x;
      draw_time(six);
      break;
    case 7:
      seven->x = x;
      draw_time(seven);
      break;
    case 8:
      eight->x = x;
      draw_time(eight);
      break;
    case 9:
      nine->x = x;
      draw_time(nine);
      break;
  }
}

void display_part(uint8_t time, int x_init)
{
  if(time < 10)
  {
    zero->x = x_init;
    draw_time(zero);
    draw_number(time, x_init + 20);
  }
  else
  {
    draw_number(time/10, x_init);
    draw_number(time%10, x_init + 20);
  }

}

void display_time()
{
  read_date();
  display_part(seconds, seconds_x); 
  display_part(minutes, minutes_x); 
  two_points->x = minutes_x + 40;
  draw_time(two_points);
  display_part(hours, hours_x); 
  two_points->x = hours_x + 40;
  draw_time(two_points);
}
