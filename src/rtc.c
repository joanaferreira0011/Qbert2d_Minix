#include "rtc.h"

int rtc_hook_id = 8;

uint8_t seconds, minutes, hours, day_week, day, month, year;
static bool bcd = false;
static bool hours_24 = true;

int rtc_subscribe_int(uint8_t * bit_no)
{
  *bit_no = rtc_hook_id;
  if(sys_irqsetpolicy(8, IRQ_REENABLE, &rtc_hook_id) != OK)
  {
    return 1;
  }
  return 0;
}

int rtc_unsubscribe_int()
{
  if(sys_irqrmpolicy(&rtc_hook_id) != OK)
  {
    return 1;
  }
  return 0;
}

int rtc_read_reg(uint32_t reg, uint8_t * data)
{
  if(sys_outb(RTC_ADDR_REG, reg) != OK)
  {
    printf("Failed to write rtc address register\n");
    return 1;
  }
  uint32_t reg_info;
  if(sys_inb(RTC_DATA_REG, &reg_info) != OK)
  {
    printf("Failed to read rtc data register\n");
    return 2;
  }
  *data = (uint8_t) reg_info;
  return 0;
}

int rtc_write_cmd(uint8_t arg)
{
  if(sys_outb(RTC_DATA_REG, arg) != OK)
  {
    printf("Failed to write rtc data register\n");
    return 3;
  }
  return 0;
  
}

int rtc_period_ints_enable()
{
  uint8_t reg_data;
  if(rtc_read_reg(REG_A, &reg_data) != OK)
  {
    return 3;
  }

  reg_data |= HALF_SECOND_WAVE;

  if(rtc_write_cmd(reg_data) != OK)
  {
    return 1;
  }  


  if(rtc_read_reg(REG_B, &reg_data) != OK)
  {
    return 4;
  }

  reg_data |= PERIODIC_INTERRUPTS;

  if(rtc_write_cmd(reg_data) != OK)
  {
    return 2;
  }  
  return 0;
}

int rtc_update_ints_enable()
{
  uint8_t reg_data;
  if(rtc_read_reg(REG_B, &reg_data) != OK)
  {
    return 1;
  }
  reg_data |= BIT(4);
  if(rtc_write_cmd(reg_data) != OK)
  {
    return 2;
  }
  if((DM_FLAG & reg_data) == 0)
    bcd = true;
  if((HOURS_FLAG & reg_data) == 0)
    hours_24 = false;
  return 0;
}

int rtc_ih()
{
  uint8_t data;
  if(rtc_read_reg(REG_C, &data) != OK)
  {
    printf("Failed to read the address register\n");
    return 1;
  }
  data &= INT_BITS; 
  switch(data)
  {
    case UPDATE_INTERRUPTS:
      read_date();
      return UPDATE_INTERRUPTS;
      break;
    case PERIODIC_INTERRUPTS:
      return PERIODIC_INTERRUPTS;
      return 2;
  }
  return 0;
}

int flush_rtc()
{
  uint8_t data;
  rtc_read_reg(REG_C, &data);
  printf("Rtc flushed\n");
  return 0;
}


int rtc_period_ints_disable()
{
  uint8_t reg_data;
  if(rtc_read_reg(REG_B, &reg_data) != OK)
  {
    return 1;
  }

  reg_data &= STOP_PERIODIC;

  if(rtc_write_cmd(reg_data) != OK)
  {
    return 2;
  }  

  return 0;
}

int rtc_update_ints_disable()
{
  uint8_t reg_data;
  if(rtc_read_reg(REG_B, &reg_data) != OK)
  {
    return 1;
  }

  reg_data &= STOP_UPDATES;

  if(rtc_write_cmd(reg_data) != OK)
  {
    return 2;
  }  

  return 0;
}

void bcd_to_binary(uint8_t *data)
{
  *data = (((*data) & 0xF0 ) >> 4 ) *10 + ((*data) & 0x0F);
}

void read_date()
{
  rtc_read_reg(SECONDS, &seconds);
  rtc_read_reg(MINUTES, &minutes);
  rtc_read_reg(HOUR, &hours);
  rtc_read_reg(DAY_WEEK, &day_week);
  rtc_read_reg(DAY, &day);
  rtc_read_reg(MONTH, &month);
  rtc_read_reg(YEAR, &year);
  if(bcd)
  {
    bcd_to_binary(&seconds);
    bcd_to_binary(&minutes);
    bcd_to_binary(&hours);
    bcd_to_binary(&day_week);
    bcd_to_binary(&day);
    bcd_to_binary(&month);
    bcd_to_binary(&year);
  }
}
