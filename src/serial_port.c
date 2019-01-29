#include "serial_port.h"

int com1_hook_id = 4;
uint32_t ser_char = 0x70;
static uint8_t sending_info = NO_MSG;
static bool thr_empty = true;

int start_communication()
{
  if(sys_outb(COM1_BASE_ADRESS + FCR, ENABlE_2_FIFO | CLR_RCVR_FIFO | CLR_XMIT_FIFO | TRIGGER_LEVEL_8) != OK)
  {
    printf("Failed to start up the fifo\n");
    return 1;
  }

  if(sys_outb(COM1_BASE_ADRESS + IER, RECEIVED_DATA_AVAILABLE_INT | THR_EMPTY_INT | RCVR_LINE_ST_INT) != OK)
  {
    printf("Failed to enable interrupts\n");
    return 2;
  }
  return 0;
}


int ser_subscribe_int(uint8_t * bit_no)
{
  *bit_no = com1_hook_id;
  if(sys_irqsetpolicy(com1_hook_id, IRQ_REENABLE | IRQ_EXCLUSIVE, &com1_hook_id) != OK)
  {
    printf("Failed to subscribe interruptions\n");
    return 1;
  }
  return 0;
}

int ser_lcr_set()
{
  uint32_t lcr;
  if(sys_inb(COM1_BASE_ADRESS + LCR, &lcr) != OK)
  {
    printf("Failed to read the lcr\n");
    return 1; 
  }

  lcr |= STOP_BIT_1 | PARITY_BIT_1;
  if(sys_outb(COM1_BASE_ADRESS + LCR, lcr) != OK)
  {
    printf("Failed to write the lcr\n");
    return 2;
  }
  return 0;
}

int send_char(uint8_t byte)
{
  if(thr_empty)
  {
    if(sys_outb(COM1_BASE_ADRESS + THR, byte) != OK)
    {
      printf("Failed to write to THR\n");
      return 1;
    }
    thr_empty = false;
    sending_info = NO_MSG;
  }
  else
  {
    printf("THR not empty, holding information for next iteration\n");
    sending_info = byte;
  }
  return 0;
}

int ser_ih()
{
  uint32_t iir;
  if(sys_inb(COM1_BASE_ADRESS + IIR, &iir)!= OK)
  {
    printf("Failed to read IIR register\n");
    return 1;
  }

  if(iir & INT_ID)
  {
    if((iir & RECEIVER_LINE_ST) == RECEIVER_LINE_ST)
    {
      printf("Receiver line status\n");
      return RECEIVER_LINE_ST;
    }
    if((iir & RECEIVED_DATA_RDY) == RECEIVED_DATA_RDY)
    {
      printf("Received data\n");
      sys_inb(COM1_BASE_ADRESS + RBR, &ser_char);
      uint32_t dummy;
      do
      {
        sys_inb(COM1_BASE_ADRESS + RBR, &dummy);
        sys_inb(COM1_BASE_ADRESS + LSR, &dummy);
        tickdelay(3);
        // printf("Clearing receiving data:%x\n", dummy);
      }while(dummy & RECEIVER_DATA);
      
      return RECEIVED_DATA_RDY;
    }
    if((iir & CHAR_TIMEOUT )== CHAR_TIMEOUT)
    {
      printf("Character timeout\n");
      return CHAR_TIMEOUT;
    }
    if((iir & THR_EMPTY )== THR_EMPTY)
    {
      printf("THR empty\n");
      thr_empty = true;
      if(sending_info != NO_MSG)
      {
        printf("Character to be sent found\n");
        send_char(sending_info);
      }
      return THR_EMPTY;
    }
  }
  return 0;
}

int ser_unsubscribe_int()
{
  if(sys_irqrmpolicy(&com1_hook_id) != OK)
  {
    return 1;
  }
  return 0;
}


