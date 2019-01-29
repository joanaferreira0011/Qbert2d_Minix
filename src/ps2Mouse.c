#include <lcom/lcf.h>
#include "ps2Mouse.h"
#include "keyboard.h"
#include "i8042.h"

int ps2_hook_id = 12;
uint8_t byte;


int ps2_subscribe_int(uint8_t *bit_no)
{
  *bit_no = ps2_hook_id;
  if(sys_irqsetpolicy(PS2_IRQ, (IRQ_REENABLE | IRQ_EXCLUSIVE), &ps2_hook_id) != OK)
  {
    printf("ps2_subscribe_int:: Failed to subscribe policy!\n");
    return 1;
  }
  return 0;
}

int ps2_unsubscribe_int()
{
  if(sys_irqrmpolicy(&ps2_hook_id) != OK)
  {
    printf("ps2_unsubscribe_int:: Failed to unsubscribe policy!\n");
    return 1;
  }
  return 0;
}



void ps2_parse_packet(struct packet *pp)
{
  if((pp->bytes[0] & PS2_RB) == PS2_RB)
  {
    pp->rb= true;
  }
  else
  {
    pp->rb = false;
  }

  if((pp->bytes[0] & PS2_MB) == PS2_MB)
  {
    pp->mb = true;
  }
  else
  {
    pp->mb = false;
  }

  if((pp->bytes[0] & PS2_LB) == PS2_LB)
  {
    pp->lb = true;
  }
  else
  {
    pp->lb = false;
  }

  if((pp->bytes[0] & PS2_X_OVF) == PS2_X_OVF)
  {
    pp->x_ov = true;
  }
  else
  {
    pp->x_ov = false;
  }

  if((pp->bytes[0] & PS2_Y_OVF) == PS2_Y_OVF)
  {
    pp->y_ov = true;
  }
  else
  {
    pp->y_ov = false;
  }

  if((pp->bytes[0] & PS2_X_SIGN) == 0)
  {
    pp->delta_x = pp->bytes[1];
  }
  else
  {
    pp->delta_x = pp->bytes[1];
    pp->delta_x-=256;
  }

  if((pp->bytes[0] & PS2_Y_SIGN) == 0)
  {
    pp->delta_y = pp->bytes[2];
  }
  else
  {
    pp->delta_y = pp->bytes[2];
    pp->delta_y-=256;
  }
}


void (mouse_ih)(void)
{
  uint8_t stat, data_buffer;
  kdb_read_status(&stat); // Reads the satus register
  if(stat & KBC_OBF_STATUS)
  {
    kbd_read_output_buff(&data_buffer); //Reads the output buffer
    if ((stat & (KBC_PARITY_STATUS | KBC_TIMEOUT_STATUS)) == OK)
    {
      byte = data_buffer; //Stores the data in the global variable
    }
    else
      byte = READ_ERROR;
  }
  else
    byte = READ_ERROR;
}


int issue_command_with_arg_KBC(uint32_t cmd, uint32_t arg)
{

  uint32_t stat;
  /* FIRSTLY: WRITE THE COMMAND*/
  while( 1 ) {
    if(sys_inb(STAT_REG, &stat) != OK)
      {
        printf("Error reading Status REG\n");
        return 1;
      }
    else
    /* loop while 8042 input buffer is not empty */
      if( (stat & KBC_IBF_STATUS) == 0 ) {
        sys_outb(KBC_CMD_REG, cmd); /* no args command */
        break;
      }
      tickdelay(micros_to_ticks(DELAY_US));
  }

  /* SECONDLY: WRITE THE ARGUMENT */
  while( 1 ) {
    if(sys_inb(STAT_REG, &stat) != OK)
      {
        printf("Error reading Status REG\n");
        return 1;
      }
    else
    /* loop while 8042 input buffer is not empty */
      if( (stat & KBC_IBF_STATUS) == 0 ) {
        sys_outb(OUT_BUF, arg); /* no args command */
        return 0;
      }
      tickdelay(micros_to_ticks(DELAY_US));
  }
}

uint8_t ps2_issue_cmd(uint8_t cmd)
{
  uint8_t data, stat;
  // The command with an argument is written to the KBC 
  if(issue_command_with_arg_KBC(KBC_WRITE_BYTE_MOUSE,(uint32_t)cmd) != OK)
  {
    return -1;
  }
  else
  {
  while( 1 ) {
    // The information from the kbd status register is read
    if(kdb_read_status(&stat) != OK)
    {
      printf("Error reading Status REG\n");
      return 1;
    }
    else
    {
      if((stat & KBC_IBF_STATUS ) == OK)
      // If the information is now ready 
      { // The KBD output buffer is read
        if(kbd_read_output_buff(&data) != OK)
        {
          return 1;
        }
        else
        {

          if(data == PS2_ACK || data == PS2_NACK || data == PS2_ERROR)
          {
            // If the data is how we want it, it is returned to be handled by the function 
            return data;
          }
        }
      }
      else
      {
        tickdelay(micros_to_ticks(DELAY_US));
      }
    }
  }
  }
}


/*************** BUTTONS STATE MACHINE*****************/

typedef enum {INIT, RIGHT, LEFT, BOTH} mouse_button_state_t;
static mouse_button_state_t state = INIT; // initial state- no buttons pressed


int mouse_check_buttons_after_event(struct packet* pp, struct mouse_ev* event) /* define type of event comparing to last event (state machine) - returns 0 if event is not a movement*/
{
  switch(state){
    case INIT: /* no buttons pressed */
      if(pp->rb){
        event->type= RB_PRESSED;
        state = RIGHT;
        return 1;}
      else if(pp->lb){
        event->type= LB_PRESSED;
        state = LEFT;
        return 1;}
      break;
    case RIGHT:
      if(!pp->rb){
        event->type= RB_RELEASED;
        state = INIT;
        return 1;}
      else if(pp->lb){
        event->type= LB_PRESSED;
        state = BOTH;
        return 1;}
      break;
    case LEFT:
      if(!pp->lb){
        event->type= LB_RELEASED;
        state = INIT;
        return 1;}
      else if(pp->rb){
        event->type= RB_PRESSED;
        state = BOTH;
        return 1;}
      break;
    case BOTH:
      if(!pp->rb){
        event->type= RB_RELEASED;
        state = LEFT;
        return 1;}
      if(!pp->lb){
        event->type= LB_RELEASED;
        state = RIGHT;
        return 1;}
      break;
  }
  event->type=MOUSE_MOV; /* if it was a movement and not a button*/
  return 0;
  }


struct mouse_ev mouse_event	(	struct packet * 	pp	)	/* turn packet into event */
{
  struct mouse_ev event = {.type=MOUSE_MOV, .delta_x=0, .delta_y=0};
  if(!mouse_check_buttons_after_event(pp, &event)) /* check for button activity - buttons state machine */
  {
    if(!pp->x_ov) /* check if there's overflow */
    event.delta_x = pp->delta_x;
    if(!pp->y_ov) /* check if there's overflow */
    event.delta_y = pp->delta_y;
  }

  return event;
}
