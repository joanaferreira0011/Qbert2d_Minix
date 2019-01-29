#include <lcom/lcf.h>
#include "keyboard.h"
#include "i8042.h"
#include <minix/drivers.h>
#include <stdio.h>

//Global Variables
#ifdef LAB3
uint32_t sys_inb_counter = 0;
#endif
int hook_id = 1;
uint8_t byte;



#ifdef LAB3
int sys_inb_cnt(port_t port, uint32_t *data)
{
  sys_inb_counter++;
  return sys_inb(port, data);
}
#endif

int (kdb_subscribe_int) (uint8_t *bit_no)
{
  *bit_no = BIT(hook_id); //Saves the keyboard irq_set
  if(sys_irqsetpolicy(1, (IRQ_ENABLE | IRQ_EXCLUSIVE), &hook_id) != OK) //Sets the policy for the keyboard
  {
    printf("Failed to set the keyboard policy\n");
    return 1;
  } 
  return 0;
}


int (kdb_unsubscribe_int)()
{
  if(sys_irqrmpolicy(&hook_id) != OK) //Removes the policy for the keyboard
  {
    printf("Failed to unsubscribe policy\n");
    return 1;
  }
  return 0;
}

int (kdb_read_status)(uint8_t *stat)
{
  uint32_t status;  //Variable to store the value
  if(sys_inb_cnt(KBC_CMD_REG, &status) != OK)
  {
    printf("kbd_read_status::Failed to read the status register");
    return 1;
  }
  *stat = (uint8_t)status; //The variable is casted into a byte and stored
  return 0;
}

int (kbd_read_output_buff) (uint8_t *data)
{
  uint32_t data_buffer;  //Variable to store the value
  if(sys_inb_cnt(OUT_BUF, &data_buffer) != OK) // Reads the variable
  {
    printf("kbd_read_output_buff::Failed to read the output buffer");
    return 1;
  }
  *data = (uint8_t)data_buffer; //The variable is casted into a byte and stored
  return 0;
}

void (kbc_ih)(void)
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

int (issue_command_KBC) (uint32_t cmd)
{
  uint32_t stat;
  
  /* FIRSTLY: WRITE THE "WRITE COMMAND" IN THE COMMAND REGISTER */
  while( 1 ) {
    if(sys_inb_cnt(STAT_REG, &stat) != OK)
      {
        printf("Error reading Status REG\n");
        return 1;
      }
    else
    /* loop while 8042 input buffer is not empty */
      if( (stat & KBC_IBF_STATUS) == 0 ) {
        sys_outb(KBC_CMD_REG, KBC_WRITE_COMMAND); /* no args command */
        break;
      }
      tickdelay(micros_to_ticks(DELAY_US));
  }

  /* SECONDLY: WRITE THE ACTUAL COMMAND AS AN ARGUMENT */
  while( 1 ) {
    if(sys_inb_cnt(STAT_REG, &stat) != OK)
      {
        printf("Error reading Status REG\n");
        return 1;
      }
    else
    /* loop while 8042 input buffer is not empty */
      if( (stat & KBC_IBF_STATUS) == 0 ) {
        sys_outb(KBC_COMMAND_REG, cmd); /* no args command */
        return 0;
      }
      tickdelay(micros_to_ticks(DELAY_US));
  }
}


void kbd_flush_buffer()
{
  uint8_t* data = NULL;
  do
  {
    kbd_read_output_buff(data);
    kdb_read_status(data);
  }while(*data & KBC_OBF_STATUS);

}

void mouse_flush_buffer()
{
  uint8_t* data = NULL;
  do
  {
    kbd_read_output_buff(data);
    kdb_read_status(data);
  }while(*data & KBC_OBF_STATUS && *data & KBC_AUX_STATUS);

}


bool (is_scancode_make)(uint8_t scancode) /*returns true if scancode is make, false if it's brake */
{
  scancode = scancode & MAKE;
  if(scancode == 0)
    return true;
  else
    return false;
}


bool (extra_byte)(uint8_t data)
{
  if(data == SCANCODE_2_BYTES) //Checks whether another byte is coming or not
    return true;
  else
    return false;
}
