#include "event_handlers.h"
static uint8_t packetCounter = 0;
extern uint8_t byte;
extern uint32_t ser_char;
static struct packet pp;
mouse_pos_t mouse_pos = NOT;
static bool credits = false;
static bool sp_game = false;
static bool mp_game_menu = false;
static bool main_menu = true;
static bool player_1 = false;
static bool player_2 = false;
static bool waiting_menu = false;
static bool game_over =false;
static unsigned chars_tries = 0;
extern unsigned intCounter;
extern unsigned h_square_size;
extern unsigned v_square_size;
static character_t* qbert;
//static character_t* enemy;
static bool button_click;
static uint h_rectangles;
static uint v_rectangles;
static bool enemy_movement = false;
static uint rtc_int = 0;
static bool enemy_transition = false;
static bool qbert_movement = false;
static unsigned qbert_counter = 0;
char next_mov;

void init_board_values()
{
  h_rectangles = 68;
  v_rectangles = 76;
  qbert = create_xpm(XPM_8_8_8_8, 205, 10, 0,0, 0, 0, 0);
}

int read_mouse()
{
  mouse_ih(); // The information from the interrupt handler is read

  if(packetCounter == 0) //The first byte from the packet is read
  {
    if(byte & PS2_BIT_THREE) // If bit 3 is not set to 1, the information is invalid
    {
      packetCounter++; //The counter of bytes is incremented
      pp.bytes[0] = byte; //The byte is stored
    }
  }
  else if(packetCounter == 1) // The second byte is read
  {
    packetCounter++; //The counter of bytes is incremented
    pp.bytes[1] = byte; //The byte is stored
  }
  else if (packetCounter == 2) // The third byte is read
  {
    packetCounter = 0; // The counter of bytes is set to 0
    pp.bytes[2] = byte; // The last byte is stored
    ps2_parse_packet(&pp); // The information of the packet is now parsed
    mouse_pos = mouse_update(&pp, main_menu);
    button_click = button_pushed(&pp);
    if(button_click)
    {
      if(credits)
      {
        switch(mouse_pos)
        {
          case CR_EX:
            credits = false;
            break;
          default:
            break;
        }
      }
      else if (main_menu)
      {
        switch(mouse_pos)
        {
          case NOT:
            break;
          case SP:
            clear_buffer();
            init_board_values();
            initialize_board();
            sp_game = true;
            main_menu = false;
            return SP_GAME;
          case MP:
            main_menu = false;
            mp_game_menu = true;
            send_char(UART_PING);
            chars_tries++;
            break;
          case CR:
            credits = true;
            return CREDITS;
          case EX:
            byte = ESC_BREAK;
            return EXIT;
          default:
            break;
        }
      }
      else if(mp_game_menu)
      {
        switch(mouse_pos)
        {
          case PLAYER_1:
            mp_game_menu = false;
            waiting_menu = true;
            player_1 = true;
            break;
          case PLAYER_2:
            mp_game_menu = false;
            waiting_menu = true;
            player_2 = true;
            break;
          default:
            break;
        }
        
      }
      else if(player_2)
      {
        switch(mouse_pos)
        {
          case R_ARROW:
            next_mov=RIGHT;
            send_char(RIGHT_ARROW);
            chars_tries++;
          
            break;
          case L_ARROW:
            next_mov=LEFT;
            send_char(LEFT_ARROW);
            chars_tries++;
          
            break;
          case U_ARROW:
            next_mov=UP;
            send_char(UP_ARROW);
            chars_tries++;
          
            break;
          case D_ARROW:
            next_mov=DOWN;
            send_char(DOWN_ARROW);
            chars_tries++;
          
            break;
          default:
            break;
        }
      }
    }
  }
  return CONTINUE;
}

int timer_IH()
{
  if(intCounter % 2 == 0)
  {
    if(game_over){
      clear_buffer();
      draw_game_over();
      draw_screen();
      kbc_mov_IH();
    }
    else if(!sp_game && !mp_game_menu)
    {
      if(credits)
      {
        draw_credits(mouse_pos);
        mouse_draw();
        draw_screen();
      }
      else if(main_menu)
      {
        menu_draw(mouse_pos);
        mouse_draw();
        draw_screen();
      }
      else if(waiting_menu)
      {
        draw_waiting_menu();
        draw_screen();
      }
      else if(player_2)
      {
        draw_mp(mouse_pos, button_click);
        print_multiplayer_board();
        mouse_draw();
        draw_screen();
        button_click = false;
      }
    }
    
    else if(sp_game)
    {
      clear_buffer();
      qbert_counter++;
      if(is_board_full())
      {
        reset_board();
      }
      print_board();
       if(enemy_movement){
        if(player_1)
          new_enemy_with_pos(get_next_player_x(), get_next_player_y());
        else
          new_enemy();
        if(enemies_mov_hd()==1)
        {
          game_over=true;
        }
        enemy_movement = false;
        enemy_transition = true;
       }
       if(enemy_transition && (intCounter % 15 == 0))
       {
         transition_all_enemies();
         enemy_transition = false;
       }
       if(qbert_movement && (qbert_counter % 15 == 0))
       {
        qbert->transitioning = false;
        qbert_movement = false;
        animate_xpm(qbert);
        clear_qbert_movement(qbert);
       }
      display_time();
      draw_xpm(qbert);
      draw_all_enemies();
      draw_screen();
    }
    

    else
    {
      clear_buffer();
      draw_mp_menu(mouse_pos);
      mouse_draw();
      draw_screen();
    }
  }


  return 0;
}

int kbc_mov_IH()
{
  if((sp_game || player_1) && !qbert_movement)
  {
    qbert_movement = true;
    qbert_counter = 0;
    if(byte== RIGHT_ARROW){ 
      if(is_mov_possible(qbert, RIGHT)== NORMAL){
      qbert_mov(RIGHT, qbert);
      qbert->transitioning = true;
      animate_xpm(qbert);
      }
    }
    else if (byte==UP_ARROW){
      if(is_mov_possible(qbert, UP)== NORMAL){
      qbert_mov(UP, qbert);
      qbert->transitioning = true;
      animate_xpm(qbert);;}}
    else if (byte== DOWN_ARROW){
      if(is_mov_possible(qbert, DOWN)== NORMAL){
      qbert_mov(DOWN, qbert);
      qbert->transitioning = true;
      animate_xpm(qbert);}}
    else if (byte==LEFT_ARROW){
      if(is_mov_possible(qbert, LEFT)== NORMAL){
      qbert_mov(LEFT, qbert);
      qbert->transitioning = true;
      animate_xpm(qbert);}
    }
  }
  else if(game_over && is_scancode_make(byte)){
    delete_all_enemies();
    tickdelay(100);
    qbert->x = 205;
    qbert->y = 10;
    qbert->x_board = 0;
    qbert->y_board = 0;
    credits = false;
    sp_game = false;
    mp_game_menu = false;
    main_menu = true;
    player_1 = false;
    player_2 = false;
    waiting_menu = false;
    game_over =false;
    send_char(UART_EXIT);
    printf("Game over\n");
    }
  return 0;
}

int new_enemy(){
  int x_board, y_board, x_real, y_real;
  x_board= rand()%10;
  y_board = rand()%10;
  x_real= 205+h_rectangles*x_board;
  y_real = v_rectangles*y_board;
  character_t* enemy = create_xpm(XPM_8_8_8_8, x_real,y_real, 0,0, rand()%4+1, y_board, x_board);
  //printf("enemy first ptr: %p\n", enemy);
  if(add_enemy_to_array(enemy)==0)
    add_enemy_to_board(enemy);
  else{
  free(enemy->img.bytes);
  free(enemy->transition_img.bytes);
  free(enemy);
  }
  return 0;
}

int new_enemy_with_pos(int x_board, int y_board){
  int x_real, y_real;
  x_real= 205+h_rectangles*x_board;
  y_real = v_rectangles*y_board;
  character_t* enemy = create_xpm(XPM_8_8_8_8, x_real,y_real, 0,0, rand()%4+1, y_board, x_board);
  //printf("enemy first ptr: %p\n", enemy);
  if(add_enemy_to_array(enemy)==0)
    add_enemy_to_board(enemy);
  else{
  free(enemy->img.bytes);
  free(enemy->transition_img.bytes);
  free(enemy);
  }
  return 0;
}


int read_serial()
{
  int int_indentity = ser_ih();
  if(int_indentity == THR_EMPTY)
  {
    chars_tries = 0;
  }
  else if(int_indentity == RECEIVED_DATA_RDY)
  {
    switch(ser_char)
    {
      case UART_ACK_P1:
        player_2 = true;
        waiting_menu = false;
        mp_game_menu = false;
        clear_buffer();
        initialize_multiplayer_board();
        printf("Received ack player 2, starting game\n");
        break;
      case UART_ACK_P2:
        player_1 = true;
        waiting_menu = false;
        clear_buffer();
        init_board_values();
        initialize_board();
        printf("Received ack player 1, starting game\n");
        break;
      case UART_PING:
        if(player_1)
        {
          send_char(UART_ACK_P1);
          chars_tries++;
          init_board_values();
          initialize_board();
          player_1 = true;
          mp_game_menu = false;
          sp_game = true;
          clear_buffer();
        }
        else if(player_2)
        {
          send_char(UART_ACK_P2);
          chars_tries++;
          initialize_multiplayer_board();
          mp_game_menu = false;
          sp_game = false;
          waiting_menu = false;
          player_2 = true;
        }
        else
        waiting_menu = false;
        printf("Received ping, sending ACK\n");
        break;
      case UART_EXIT:
        clear_buffer();
        credits = false;
        sp_game = false;
        mp_game_menu = false;
        main_menu = true;
        player_1 = false;
        player_2 = false;
        waiting_menu = false;
        game_over =false;
        printf("Exit character received, exiting\n");
        break;
      case LEFT_ARROW:
        printf("Received left, sending ACK\n");
        if(update_next_enemy_position(LEFT_ARROW)==OK)
          send_char(UART_ACK);
        chars_tries++;
      
        break;
      case RIGHT_ARROW:
        printf("Received right, sending ACK\n");
        if(update_next_enemy_position(RIGHT_ARROW)==OK)
          send_char(UART_ACK);
        chars_tries++;
      
        break;
      case UP_ARROW:
        printf("Received UP, sending ACK\n");
        if(update_next_enemy_position(UP_ARROW)==OK)
          send_char(UART_ACK);
        chars_tries++;
      
        break;
      case DOWN_ARROW:
        printf("Received DOWN, sending ACK\n");
        if(update_next_enemy_position(DOWN_ARROW)==OK)
          send_char(UART_ACK);
        chars_tries++;
      
        break;
      case UART_ACK:
        multiplayer_mov(next_mov);
        printf("Acking movement\n");
        break;
      default:
        printf("Unknown char received: %x\n", ser_char);
        break;
    }
  }
  return 0;
}

int rtc_ev()
{
  int ih_indentity = rtc_ih();
  if(ih_indentity == UPDATE_INTERRUPTS)
  {
    printf("Update interrupts\n");
  }
  else if(ih_indentity == PERIODIC_INTERRUPTS && sp_game)
  {
    rtc_int++;
    if(rtc_int % 2 == 0)
    {
      enemy_movement = true;
    }
  }
  return 0;
}
