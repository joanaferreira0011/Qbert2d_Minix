#include <lcom/lcf.h>
#include "board.h"
#include <string.h>
//#include "video_graphics.h"
//#include "video.h"
#include "keyboard.h"
#include "i8042.h"
#include <limits.h> 
#include "uart.h"

extern uint8_t byte;
static board game_board;
static board multiplayer_game_board;
unsigned h_square_size;
unsigned v_square_size;
static uint32_t color_true, color_false;
//static xpm_enemy_t* enemies[ENEMY_SIZE];
uint h_rectangles = 68;
uint v_rectangles = 76;
uint number_squares_board =100;


void generate_random_colors(){
  uint32_t x;
  x = rand() & 0xff;
  x |= (rand() & 0xff) << 8;
  x |= (rand() & 0xff) << 16;
  x |= (rand() & 0xff) << 24;

  color_true = x;

  color_false = color_true ^ 0xffffffff ;
}

bool is_board_full(){
  return (game_board.number_squares_painted== number_squares_board);
}

void reset_board(){
  uint32_t x;
  x = rand() & 0xff;
  x |= (rand() & 0xff) << 8;
  x |= (rand() & 0xff) << 16;
  x |= (rand() & 0xff) << 24;
  color_false= color_true;
  color_true= x;
  game_board.number_squares_painted = 1;
  for(size_t col=0; col <game_board.number_horizontal_squares; col++){ /* set colors to false */
       for(size_t row=0; row < game_board.number_vertical_squares; row++){
        if (game_board.matrix[col][row].name== QBERT)
          game_board.matrix[col][row].color=true;  
        else
          game_board.matrix[col][row].color=false;  }
    }

}


int add_enemy_to_board(character_t* enemy){
  if(game_board.matrix[enemy->x_board][enemy->y_board].name==EMPTY){
    game_board.matrix[enemy->x_board][enemy->y_board].name= ENEMY1;
    //printf("%d", game_board.matrix[enemy->x_board][enemy->y_board].name);
    return 0;}
  else
    return 1; //in case the space is already occupied
}

void initialize_board(){
    generate_random_colors();
    game_board.qbert_position.x=0;
    game_board.qbert_position.y=0;
    game_board.number_squares_painted = 1;
    game_board.number_horizontal_squares= sizeof(game_board.matrix) / sizeof(game_board.matrix[0]);
    game_board.number_vertical_squares= sizeof(game_board.matrix[0])/sizeof(game_board.matrix[0][0]);
    for(size_t col=0; col <game_board.number_horizontal_squares; col++){ /* set colors to false */
       for(size_t row=0; row < game_board.number_vertical_squares; row++){
          game_board.matrix[col][row].name=EMPTY; 
          game_board.matrix[col][row].color=false;  
       }
    }
    game_board.matrix[0][0].color=true;  
    game_board.matrix[0][0].name=QBERT;  
    h_square_size = game_board.number_horizontal_squares;
    v_square_size = game_board.number_vertical_squares;
    game_board.next_enemy.x=0;
    game_board.next_enemy.y=0;
   
}

void initialize_multiplayer_board(){
    generate_random_colors();
    multiplayer_game_board.next_enemy.x=0;
    multiplayer_game_board.next_enemy.y=0;   
    multiplayer_game_board.number_horizontal_squares= sizeof(multiplayer_game_board.matrix) / sizeof(multiplayer_game_board.matrix[0]);
    multiplayer_game_board.number_vertical_squares= sizeof(multiplayer_game_board.matrix[0])/sizeof(multiplayer_game_board.matrix[0][0]);
    for(size_t col=0; col <multiplayer_game_board.number_horizontal_squares; col++){ /* set colors to false */
       for(size_t row=0; row < multiplayer_game_board.number_vertical_squares; row++){
          multiplayer_game_board.matrix[col][row].name=EMPTY; 
          multiplayer_game_board.matrix[col][row].color=false;  
       }
    }
    multiplayer_game_board.matrix[0][0].color=true;  
    multiplayer_game_board.matrix[0][0].name=NEXT_ENEMY; 
    game_board.next_enemy.x=0;
    game_board.next_enemy.y=0;
   
}

val_mov is_mov_possible(character_t* character, mov movement){
  character_name op_char, self_char;
  if(character->type==0){
    op_char= ENEMY1;
    self_char = QBERT;
  }
  else{
    op_char= QBERT;
    self_char = ENEMY1;
  }
  //printf("x: %d, y: %d\n",character->x_board, character->y_board );
  switch (movement){
    case UP:
      if (character->x_board-1 < 0){
        //printf("out up:%d\n", (character->x_board - 1));
        return OUT_OF_BONDARIES;
        }
      else if(game_board.matrix[character->x_board-1][character->y_board].name == op_char)
      {
        //printf("col up\n");
        return QBERT_COLLISION;}
      else if(game_board.matrix[character->x_board-1][character->y_board].name == self_char && self_char != QBERT)
        return ENEMY_COLLISION;
      else
        return NORMAL;

    case DOWN:
      if((uint)character->x_board+1 >= game_board.number_horizontal_squares){
        //printf("outx\n");
        return OUT_OF_BONDARIES;
        }
      else if(game_board.matrix[character->x_board+1][character->y_board].name == op_char){
        //printf("cold\n");
        return QBERT_COLLISION;}
      else if(game_board.matrix[character->x_board+1][character->y_board].name == self_char && self_char != QBERT)
        return ENEMY_COLLISION;  
      else
      {
        //printf("normald\n");
        return NORMAL;}
    
    case LEFT:
      if(character->y_board-1 <0)
        return OUT_OF_BONDARIES;
      else if(game_board.matrix[character->x_board][character->y_board-1].name == op_char)
        return QBERT_COLLISION;
      else if(game_board.matrix[character->x_board][character->y_board-1].name == self_char && self_char != QBERT)
        return ENEMY_COLLISION;
      else
        return NORMAL;
    
    case RIGHT:
      if((uint)character->y_board+1 >= game_board.number_vertical_squares)
      {
        return OUT_OF_BONDARIES;
      }
      else if(game_board.matrix[character->x_board][character->y_board+1].name == op_char)
      {
        return QBERT_COLLISION;
      }
      else if(game_board.matrix[character->x_board][character->y_board+1].name == self_char && self_char != QBERT)
        return ENEMY_COLLISION;
      else
        return NORMAL;
    
    case DIAGONAL_UP_LEFT:
      if(character->y_board-1 <0 || character->x_board-1 < 0)
        return OUT_OF_BONDARIES;
      else if(game_board.matrix[character->x_board-1][character->y_board-1].name == op_char)
        return QBERT_COLLISION;
      else if(game_board.matrix[character->x_board-1][character->y_board-1].name == self_char && self_char != QBERT)
        return ENEMY_COLLISION;
      else
        return NORMAL;
    
    case DIAGONAL_UP_RIGHT:
      if(character->x_board-1 < 0 || (uint)character->y_board+1 >= game_board.number_vertical_squares)
        return OUT_OF_BONDARIES;
      else if(game_board.matrix[character->x_board-1][character->y_board+1].name == op_char)
        return QBERT_COLLISION;
      else if(game_board.matrix[character->x_board-1][character->y_board+1].name == self_char && self_char != QBERT)
        return ENEMY_COLLISION;
      else
        return NORMAL;
    
    case DIAGONAL_DOWN_LEFT:
      if(character->y_board-1 <0 || (uint)character->x_board+1 >= game_board.number_horizontal_squares)
        return OUT_OF_BONDARIES;
      else if(game_board.matrix[character->x_board+1][character->y_board-1].name == op_char)
        return QBERT_COLLISION;
      else if(game_board.matrix[character->x_board+1][character->y_board-1].name == self_char && self_char != QBERT)
        return ENEMY_COLLISION;
      else
        return NORMAL;
    
    case DIAGONAL_DOWN_RIGHT:
      if((uint)character->x_board+1 >= game_board.number_horizontal_squares || (uint)character->y_board+1 >= game_board.number_vertical_squares)
        return OUT_OF_BONDARIES;
      else if(game_board.matrix[character->x_board+1][character->y_board+1].name == op_char)
        return QBERT_COLLISION;
      else if(game_board.matrix[character->x_board+1][character->y_board+1].name == self_char && self_char != QBERT)
        return ENEMY_COLLISION;
      else
        return NORMAL;
    
    case STOPPED: //When the Qbert does not 
      printf("Stopped\n");
      return STOP;
  }
}


void delete_enemy_from_board(character_t* enemy){
  game_board.matrix[enemy->x_board][enemy->y_board].name = EMPTY;
}

int qbert_mov(mov movement, character_t* qbert){
  switch (movement){
    case UP:
      qbert->yspeed = - MOVEMENT_SIZE_Y; 
      game_board.matrix[game_board.qbert_position.x][game_board.qbert_position.y].name = EMPTY;
      game_board.qbert_position.x-=1;
      qbert->x_board-=1;
      if(game_board.matrix[game_board.qbert_position.x][game_board.qbert_position.y].color==false){
        game_board.matrix[game_board.qbert_position.x][game_board.qbert_position.y].color=true; 
        game_board.number_squares_painted ++;}

      game_board.matrix[game_board.qbert_position.x][game_board.qbert_position.y].name = QBERT;
      break;

    case DOWN:
      qbert->yspeed = MOVEMENT_SIZE_Y; 
      game_board.matrix[game_board.qbert_position.x][game_board.qbert_position.y].name = EMPTY;
      game_board.qbert_position.x+=1;
      qbert->x_board+=1;
      game_board.matrix[game_board.qbert_position.x][game_board.qbert_position.y].name = QBERT;
      if(game_board.matrix[game_board.qbert_position.x][game_board.qbert_position.y].color==false){
        game_board.matrix[game_board.qbert_position.x][game_board.qbert_position.y].color=true; 
        game_board.number_squares_painted ++;}
      break;
    
    case LEFT:
      qbert->xspeed = - MOVEMENT_SIZE_X;
      game_board.matrix[game_board.qbert_position.x][game_board.qbert_position.y].name = EMPTY;
      game_board.qbert_position.y-=1;
      qbert->y_board-=1;
      game_board.matrix[game_board.qbert_position.x][game_board.qbert_position.y].name = QBERT;
      if(game_board.matrix[game_board.qbert_position.x][game_board.qbert_position.y].color== false){
        game_board.matrix[game_board.qbert_position.x][game_board.qbert_position.y].color=true; 
        game_board.number_squares_painted ++;}
      break;

    case RIGHT:
      qbert->xspeed = MOVEMENT_SIZE_X;
      game_board.matrix[game_board.qbert_position.x][game_board.qbert_position.y].name = EMPTY;
      game_board.qbert_position.y+=1;
      qbert->y_board+=1;
      game_board.matrix[game_board.qbert_position.x][game_board.qbert_position.y].name = QBERT;
      if(game_board.matrix[game_board.qbert_position.x][game_board.qbert_position.y].color==false){ 
        game_board.matrix[game_board.qbert_position.x][game_board.qbert_position.y].color=true; 
        game_board.number_squares_painted ++;}
      break;

    default:
      return 0;

  }
  return 0;

}

int move_enemy(mov movement, character_t* enemy){
  switch (movement){
    case UP:
      game_board.matrix[enemy->x_board][enemy->y_board].name = EMPTY;
      enemy->x_board-=1;
      enemy->transitioning = true;
      animate_xpm(enemy);
      game_board.matrix[enemy->x_board][enemy->y_board].name = ENEMY1;
      break;

    case DOWN:
      game_board.matrix[enemy->x_board][enemy->y_board].name = EMPTY;
      enemy->x_board+=1;
      enemy->transitioning = true;
      animate_xpm(enemy);
      game_board.matrix[enemy->x_board][enemy->y_board].name = ENEMY1;
      break;
    
    case LEFT:
      game_board.matrix[enemy->x_board][enemy->y_board].name = EMPTY;
      enemy->y_board-=1;
      enemy->transitioning = true;
      animate_xpm(enemy);
      game_board.matrix[enemy->x_board][enemy->y_board].name = ENEMY1;
      break;

    case RIGHT:
      game_board.matrix[enemy->x_board][enemy->y_board].name = EMPTY;
      enemy->y_board+=1;
      enemy->transitioning = true;
      animate_xpm(enemy);
      game_board.matrix[enemy->x_board][enemy->y_board].name = ENEMY1;
      break;

    case DIAGONAL_UP_LEFT:
      game_board.matrix[enemy->x_board][enemy->y_board].name = EMPTY;
      enemy->y_board-=1;
      enemy->x_board -=1;
      enemy->transitioning = true;
      animate_xpm(enemy);
      game_board.matrix[enemy->x_board][enemy->y_board].name = ENEMY1;
      break;
    
    case DIAGONAL_UP_RIGHT:
      game_board.matrix[enemy->x_board][enemy->y_board].name = EMPTY;
      enemy->y_board+=1;
      enemy->x_board -=1;
      enemy->transitioning = true;
      animate_xpm(enemy);
      game_board.matrix[enemy->x_board][enemy->y_board].name = ENEMY1;
      break;
    
    case DIAGONAL_DOWN_LEFT:
      game_board.matrix[enemy->x_board][enemy->y_board].name = EMPTY;
      enemy->y_board-=1;
      enemy->x_board +=1;
      enemy->transitioning = true;
      animate_xpm(enemy);
      game_board.matrix[enemy->x_board][enemy->y_board].name = ENEMY1;
      break;
    
    case DIAGONAL_DOWN_RIGHT:
      game_board.matrix[enemy->x_board][enemy->y_board].name = EMPTY;
      enemy->y_board+=1;
      enemy->x_board +=1;
      enemy->transitioning = true;
      animate_xpm(enemy);
      game_board.matrix[enemy->x_board][enemy->y_board].name = ENEMY1;
      break;

    default:
      return 0;

  }
  return 0;

}


int print_board() {
  uint32_t color;
  //uint h_rectangles = get_h_res()/game_board.number_horizontal_squares;
  //uint v_rectangles = get_v_res()/game_board.number_vertical_squares;
  uint h_rectangles = 68; //calculated for 10 /15 with the comment above
  uint v_rectangles = 76;
  /* PRINT RECTANGLES */
    for(size_t row=0; row < game_board.number_horizontal_squares; row++){
      for(size_t col=0; col<game_board.number_vertical_squares; col++){
        if(game_board.matrix[row][col].color==true)
            color = color_true;
        else 
            color = color_false;
        
        
        drawRectangle(200+ col*h_rectangles, row*v_rectangles, h_rectangles-2, v_rectangles-2, color);  
      }
    }


return 0;
}

int print_multiplayer_board() {
  uint32_t color;
  uint h_rectangles = 68/2; //calculated for 10 /15 with the comment above
  uint v_rectangles = 76/2;
  /* PRINT RECTANGLES */
    for(size_t row=0; row < multiplayer_game_board.number_horizontal_squares; row++){
      for(size_t col=0; col<multiplayer_game_board.number_vertical_squares; col++){
        if(multiplayer_game_board.matrix[row][col].color==true)
            color = color_true;
        else 
            color = color_false;
        
        
        drawRectangle(360+ col*h_rectangles, row*v_rectangles, h_rectangles-2, v_rectangles-2, color);  
      }
    }


return 0;
}

int multiplayer_mov(mov movement){
  switch (movement){
    case UP:
      multiplayer_game_board.matrix[multiplayer_game_board.next_enemy.x][multiplayer_game_board.next_enemy.y].name = EMPTY;
      multiplayer_game_board.matrix[multiplayer_game_board.next_enemy.x][multiplayer_game_board.next_enemy.y].color = false;
      multiplayer_game_board.next_enemy.x-=1;
      multiplayer_game_board.matrix[multiplayer_game_board.next_enemy.x][multiplayer_game_board.next_enemy.y].color=true; 
      multiplayer_game_board.matrix[multiplayer_game_board.next_enemy.x][multiplayer_game_board.next_enemy.y].name = NEXT_ENEMY;
      break;

    case DOWN:
      multiplayer_game_board.matrix[multiplayer_game_board.next_enemy.x][multiplayer_game_board.next_enemy.y].name = EMPTY;
      multiplayer_game_board.matrix[multiplayer_game_board.next_enemy.x][multiplayer_game_board.next_enemy.y].color = false;
      multiplayer_game_board.next_enemy.x+=1;
      multiplayer_game_board.matrix[multiplayer_game_board.next_enemy.x][multiplayer_game_board.next_enemy.y].name = NEXT_ENEMY;
      multiplayer_game_board.matrix[multiplayer_game_board.next_enemy.x][multiplayer_game_board.next_enemy.y].color=true; 
      break;
    
    case LEFT:
      multiplayer_game_board.matrix[multiplayer_game_board.next_enemy.x][multiplayer_game_board.next_enemy.y].name = EMPTY;
      multiplayer_game_board.matrix[multiplayer_game_board.next_enemy.x][multiplayer_game_board.next_enemy.y].color = false;
      multiplayer_game_board.next_enemy.y-=1;
      multiplayer_game_board.matrix[multiplayer_game_board.next_enemy.x][multiplayer_game_board.next_enemy.y].name = NEXT_ENEMY;
      multiplayer_game_board.matrix[multiplayer_game_board.next_enemy.x][multiplayer_game_board.next_enemy.y].color=true; 
      break;

    case RIGHT:
      multiplayer_game_board.matrix[multiplayer_game_board.next_enemy.x][multiplayer_game_board.next_enemy.y].name = EMPTY;
      multiplayer_game_board.matrix[multiplayer_game_board.next_enemy.x][multiplayer_game_board.next_enemy.y].color = false;
      multiplayer_game_board.next_enemy.y+=1;
      multiplayer_game_board.matrix[multiplayer_game_board.next_enemy.x][multiplayer_game_board.next_enemy.y].name = NEXT_ENEMY; 
      multiplayer_game_board.matrix[multiplayer_game_board.next_enemy.x][multiplayer_game_board.next_enemy.y].color=true; 
      break;

    default:
      return 0;

  }
  return 0;

}


int get_next_player_x(){
  return game_board.next_enemy.y;
}

int get_next_player_y(){
  return game_board.next_enemy.x;
}

int update_next_enemy_position(char movement){
  switch (movement){
    case UP_ARROW:
      if(game_board.next_enemy.x-1<0)
        return 1;
      game_board.next_enemy.x-=1;
      break;

    case DOWN_ARROW:
      if((uint)game_board.next_enemy.x+1>=game_board.number_horizontal_squares)
        return 1;
      game_board.next_enemy.x+=1;
      break;
    
    case LEFT_ARROW:
      if(game_board.next_enemy.y-1<0)
        return 1;
      game_board.next_enemy.y-=1;
      break;

    case RIGHT_ARROW:
      if((uint)game_board.next_enemy.y+1>=game_board.number_vertical_squares)
        return 1;
      game_board.next_enemy.y+=1;
      break;

    default:
      return 0;

  }
  return 0;
}
