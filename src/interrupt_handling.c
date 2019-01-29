#include "interrupt_handling.h"

extern uint8_t byte;

int start_game()
{
  launch_menu();
  menu_draw(NOT);
  draw_screen();
  start_communication();
  ser_lcr_set();
  rtc_update_ints_enable();
  rtc_period_ints_enable();
  initialize_time();
  uint8_t ack_byte;
  uint8_t mouse_irq_set, timer_irq_set, kbc_irq_set, ser_irq_set, rtc_irq_set;
  // Before enabling interrupts, data reporting is enabled
  do
  {
    ack_byte = ps2_issue_cmd(PS2_ENABLE_REPORT_CMD);

  }while(ack_byte != PS2_ACK);

  // The mouse interruptions are subscribed
  if(ps2_subscribe_int(&mouse_irq_set) != OK)
  {
      return 1;
  }
  // The timer interruptions are subscribed
  if(timer_subscribe_int(&timer_irq_set) != OK)
  {
    return 1;
  }

  if(kdb_subscribe_int(&kbc_irq_set) != OK)
  {
    return 1;
  }

  if(ser_subscribe_int(&ser_irq_set) != OK)
  {
    return 1;
  }

  if(rtc_subscribe_int(&rtc_irq_set) != OK)
  {
    return 1;
  }
  mouse_start();
  draw_screen();
  int r;
  int ipc_status;
  message msg;

   while(byte != ESC_BREAK) {
  /* Get a request message. */
      if ( (r = driver_receive(ANY, &msg, &ipc_status)) != 0 ) {
        printf("driver_receive failed with: %d", r);
        continue;
      }
      if (is_ipc_notify(ipc_status)) { /* received notification */
        switch (_ENDPOINT_P(msg.m_source)) {
          case HARDWARE: /* hardware interrupt notification */
            if (msg.m_notify.interrupts & BIT(mouse_irq_set)) { /* subscribed interrupt */
              read_mouse();
            }
            if(msg.m_notify.interrupts & kbc_irq_set)
            {
              kbc_ih();
              kbc_mov_IH();
            }
            if(msg.m_notify.interrupts & timer_irq_set)
            {
              timer_int_handler();
              timer_IH();
            }
            if(msg.m_notify.interrupts & BIT(ser_irq_set))
            {
              read_serial();
            }
            if(msg.m_notify.interrupts & BIT(rtc_irq_set))
            {
              rtc_ev();
            }
          
            break;
          default:
            break; /* no other notifications expected: do nothing */
        }
      }
      else { /* received a standard message, not a notification */
        /* no standard messages expected: do nothing */
      }
    }
  kdb_unsubscribe_int();
  timer_unsubscribe_int();
  ps2_unsubscribe_int();
  flush_rtc();
  rtc_update_ints_disable();
  rtc_period_ints_disable();
  rtc_unsubscribe_int();
  ser_unsubscribe_int();


  do
  {
    ack_byte = ps2_issue_cmd(PS2_DISABLE_REPORT_CMD);

  }while(ack_byte != PS2_ACK);

  return 0;
}

