#pragma once
#define BIT(n)      (0x01<<(n))

#define COM1_BASE_ADRESS     0x3F8

/* UART REGISTERS */
#define RBR       0
#define THR       0
#define IER       1
#define IIR       2
#define FCR       2
#define LCR       3
#define MCR       4
#define LSR       5
#define MSR       6
#define SR        7

/* LCR INFO */

#define BIT_PER_CHAR_5 0
#define BIT_PER_CHAR_6 BIT(0)
#define BIT_PER_CHAR_7 BIT(1)
#define BIT_PER_CHAR_8 (BIT(1) | BIT(0))
#define STOP_BIT_1     0
#define STOP_BIT_2     BIT(2)
#define NO_PARITY      0
#define ODD_PARITY     BIT(3)
#define EVEN_PARITY    (BIT(4) | BIT(3))
#define PARITY_BIT_1   (BIT(4) | BIT(3))
#define PARITY_BIT_0   (BIT(5) | BIT(4) | BIT(3))
#define BREAK_CONTROL  BIT(6) 
#define DLAB           BIT(7) 

/* LSR INFO */
#define RECEIVER_DATA   BIT(0)
#define OVERRUN_ERROR   BIT(1)
#define PARITY_ERROR    BIT(2)
#define FRAMING_ERROR   BIT(3)
#define BREAK_INTERRUPT BIT(4)
#define THR_EMPTY_LSR   BIT(5)
#define THR_TSR_EMPY    BIT(6)
#define FIFO_ERROR      BIT(7)

/* IER INFO */
#define RECEIVED_DATA_AVAILABLE_INT BIT(0)
#define THR_EMPTY_INT               BIT(1)
#define RCVR_LINE_ST_INT            BIT(2)

/* IIR INFO */
#define NO_INTERRUPT_PENDING  BIT(0)
#define RECEIVER_LINE_ST      (BIT(2) | BIT(1))
#define RECEIVED_DATA_RDY     BIT(2)
#define CHAR_TIMEOUT          (BIT(3) | BIT(2))
#define THR_EMPTY             BIT(1)
#define INT_ID                (BIT(3) | BIT(2) | BIT(1))

/* UART FIFO */
#define ENABlE_2_FIFO       BIT(0)
#define CLR_RCVR_FIFO       BIT(1)
#define CLR_XMIT_FIFO       BIT(2)
#define TRIGGER_LEVEL_1     0
#define TRIGGER_LEVEL_4     BIT(6)
#define TRIGGER_LEVEL_8     BIT(7)
#define TRIGGER_LEVEL_14    (BIT(7) | BIT(6))

#define DELAY_US    20000


#define UART_ACK_P1      0xFA
#define UART_ACK_P2      0xFD
#define UART_ACK         0xFF
#define UART_PING        0xFB
#define UART_NACK        0xFE
#define UART_EXIT        0xFC
#define NO_MSG           0x00
#define LEFT_ARROW       0x1E
#define RIGHT_ARROW      0x20
#define UP_ARROW         0x11
#define DOWN_ARROW       0x1F
