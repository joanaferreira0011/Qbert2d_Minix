
#include "controlSprite.h"

uint8_t data[2] = {0 , 0};
extern uint8_t byte;
extern unsigned intCounter;
static character_t *enemies[ENEMY_SIZE];

int add_enemy_to_array(character_t *enemy)
{
  for(unsigned i = 0; i < ENEMY_SIZE; i++)
  {
    if(enemies[i] == NULL)
    {
      pattern_movement(enemy); 
      enemies[i] = enemy;
      return 0;
    }
  }
  return 1;
}

void delete_enemy(int index)
{
  if(enemies[index] == NULL)
    return;
  free(enemies[index]->img.bytes);
  free(enemies[index]->transition_img.bytes);
  free(enemies[index]);
  enemies[index] = NULL;
}

void delete_all_enemies(){
  for(unsigned i = 0; i < ENEMY_SIZE; i++){
      delete_enemy(i);
  }
}

int enemies_mov_hd(){
  mov movement;
  val_mov stat_mov;
  for(unsigned i = 0; i < ENEMY_SIZE; i++){
    if(enemies[i] != NULL){
      movement = check_enemy_movement(enemies[i]);
      stat_mov =is_mov_possible(enemies[i], movement);
      if(stat_mov== NORMAL)
          move_enemy(movement, enemies[i]);
      else if(stat_mov== OUT_OF_BONDARIES || stat_mov == ENEMY_COLLISION){
          delete_enemy_from_board(enemies[i]);
          delete_enemy(i);
      }
      else if(stat_mov== QBERT_COLLISION) //game over
      {
        printf("Qbert collision\n");
        return 1;
      }
    }
  }
  return 0;
}

void draw_all_enemies(){
  for(unsigned i = 0; i < ENEMY_SIZE; i++)
  {
    if(enemies[i] != NULL)
    {
      draw_xpm(enemies[i]);
    }
  }
}

void pattern_movement(character_t * xpm)
{
  switch(xpm->type)
  {
    case 1:
      if(xpm->y <= V_SIZE/2)
      {
        xpm->yspeed = MOVEMENT_SIZE_Y;
      }
      else
      {
        xpm->yspeed = - MOVEMENT_SIZE_Y;
      }
      break;
    case 2:
      if(xpm->x <= H_SIZE/2)
        xpm->xspeed = MOVEMENT_SIZE_X;
      else
        xpm->xspeed = - MOVEMENT_SIZE_X;
      break;
    case 3:
    case 4:
      if(xpm->y <= V_SIZE/2)
        xpm->yspeed = MOVEMENT_SIZE_Y;
      else
        xpm->yspeed = - MOVEMENT_SIZE_Y;
      if(xpm->x <= H_SIZE/2)
        xpm->xspeed = MOVEMENT_SIZE_X;
      else
        xpm->xspeed = - MOVEMENT_SIZE_X;
      break;

  }
}

void clear_qbert_movement(character_t * qbert)
{
  qbert->xspeed = 0;
  qbert->yspeed = 0;
}


void transition_all_enemies()
{
  for(unsigned i = 0; i < ENEMY_SIZE; i++)
  {
    if(enemies[i] != NULL)
    {
      enemies[i]->transitioning = false;
      animate_xpm(enemies[i]);
    }
  }
}
