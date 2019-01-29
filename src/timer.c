#include <lcom/lcf.h>
#include <lcom/timer.h>
#include <minix/drivers.h>
#include <stdint.h>

#include "i8254.h"

// Sets the counter to be incremented and the variable to the save the hook id
int hookID = 0;
unsigned intCounter = 0;

int (timer_set_frequency)(uint8_t timer, uint32_t freq) {

  /* Only timers from 0 to 2 are defined */

  if(timer < 0 || timer > 2)
  {
    printf("The timer selected does not exist!\n");
    return 1;
  }

  /* Since the clock frequency is a 16 bit register, the highest number it can receive
   * is 65535. Therefore, the minimum frequency is (clock/div) 1193182/65535 ≃ 18,2068Hz.
   * Since we are working with integers, the lowest frequency is 19 */


  if(freq < 19)
  {
    printf("Frequency too low for clock to function\n");
    return 6;
  }

  // It is now needed to read the current configuration of the timer
  uint8_t config;
  if (timer_get_conf(timer, &config) != 0)
   {
    printf("Error reading timer configuration!\n");
    return 2;
  }

  uint32_t control_word;
  /* Creation of the Control Word */
  switch (timer) {
    case 0:
      control_word = TIMER_SEL0;
      break;
    case 1:
      control_word = TIMER_SEL1;
      break;
    case 2:
      control_word = TIMER_SEL2;
      break;
    }
 // The configuration must be ran through a mask so that it loses the information we want to change 
  control_word|= (TIMER_LSB_MSB)|(config & (BIT(3) | BIT(2) | BIT(1) | BIT(0)));

  // The control word must now be loaded to the control register 

  if (sys_outb(TIMER_CTRL, control_word)!= OK)
  {
    printf("The control word could not be loaded\n");
    return 3;
  }

  /* As explained in the lab handout, in order to load the timer with a different frequency it is needed to divide the timer's frequency and the value used given as a frequency */
  uint16_t frequency = TIMER_FREQ / freq;

 // Since its not possible to load both bytes of the timer at the same time, the value must be separated 

  uint8_t lsb, msb;
  util_get_LSB(frequency, &lsb);
  util_get_MSB(frequency, &msb);
  uint32_t lsb_freq = (uint32_t)lsb;
  uint32_t msb_freq = (uint32_t)msb;
  /* Loading LSB first as specified
  The use of TIMER_0 + timer, prevents the use of a switch statement to select the timer, since the addresses
  are sequential */

  if(sys_outb(TIMER_0 + timer, lsb_freq)!= OK)
  {
    printf("LSB could not be loaded into the timer");
    return 4;
  }

  // The same process is now repeated for MSB
  if(sys_outb (TIMER_0 + timer, msb_freq)!= OK)
  {
    printf("LSB could not be loaded into the timer");
    return 5;
  }
  //The values were loaded as expected
  return 0;

}



int (timer_subscribe_int)(uint8_t *bit_no) {

  //The bit number to be set in the mask is now stored
  *bit_no = BIT(hookID);
  //The policy is now subscribed
  if(sys_irqsetpolicy(TIMER0_IRQ, IRQ_REENABLE, &hookID) != OK)
  {
    printf("Failed to set IRQ policy\n");
    return 1;
  }
  return 0;
}



int (timer_unsubscribe_int)() {

  //The policy is unsubscribed
  if(sys_irqrmpolicy(&hookID) != OK)
  {
    printf("Failed to unsubscribe last irq policy\n");
    return 1;
  }
  return 0;
}



void (timer_int_handler)() {
  //The counter of interruptions is incremented
  intCounter++;
}



int (timer_get_conf)(uint8_t timer, uint8_t *st) {
  uint32_t mask = TIMER_RB_CMD | TIMER_RB_COUNT_ | TIMER_RB_SEL(timer);
  if(sys_outb(TIMER_CTRL, mask) != OK) //CHECK NEEDS TO BE 32
  {
    printf("Error acessing Control\n");
    return 1;
  }

  unsigned int data;

  if(sys_inb(TIMER_0+ timer, &data) != OK)
  {
    printf("Error getting data\n");
    return 2;
  }

  *st =(unsigned char) data;
  return 0;
}


int (timer_display_conf)(uint8_t timer, uint8_t st, enum timer_status_field field) {

timer_get_conf(timer, &st);
union timer_status_field_val val; //@val to be filled dependind on the field and sent to timer_print_config
uint8_t mask; //@mask to be used afterwards to get the desirable bits

  switch(field) // fill the union depending on the field
  {
      case all:
        val.byte =st;
        break;

      case mode:
        mask = BIT(1)| BIT(2) | BIT(3);
        mask &= st;
        mask= mask >> 1;
        val.count_mode = mask;
        break;

      case base:
        st = st & BIT(0); //get LSB
        val.bcd= st;
        break;

      case initial:
        mask = BIT(4)| BIT(5);
        mask &= st;
        mask = mask >> 4;
        val.in_mode = mask;
        break;

    }

    if(timer_print_config(timer, field, val) == OK)
      return 0;
    else
      return -1;
}
