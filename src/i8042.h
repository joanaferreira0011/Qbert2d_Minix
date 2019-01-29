#pragma once

/** @defgroup i8042
 * @{
 *
 * Constants for programming the i8042 KBC
 */


#define BIT(n)               (0x01<<(n))

#define KBD_IRQ                     1 
#define PS2_IRQ                     12
#define TWO_COMPLEMENT          0xFF

/***********************
 *** STATUS REGISTER ***
 **********************/

#define KBC_PARITY_STATUS       BIT(7)
#define KBC_TIMEOUT_STATUS      BIT(6)
#define KBC_AUX_STATUS          BIT(5)
#define KBC_INHIBIT_STATUS      BIT(4)
#define KBC_A2_STATUS           BIT(3)
#define KBC_SYS_STATUS          BIT(2)
#define KBC_IBF_STATUS          BIT(1)
#define KBC_OBF_STATUS          BIT(0)


/***********************
 **** KBC COMMANDS *****
 **********************/

#define KBC_READ_COMMAND        0x20
#define KBC_WRITE_COMMAND       0X60
#define KBC_CHECK_COMMAND       0XAA
#define KBC_CHECK_INTERFACE     0XAB
#define KBC_DISABLE_INTERFACE   0xAD
#define KBC_ENABLE_INTERFACE    0xAE
#define KBC_ENABLE_INTERRUPTS   0x47
#define KBC_WRITE_BYTE_MOUSE    0xD4



/***********************
 *** KBC COMMAND BYTE **
 **********************/

#define KBC_CMD_DIS_MOUS        BIT(5)
#define KBC_CMD_DIS_KBD         BIT(4)
#define KBC_CMD_EN_MOUS_INT     BIT(1)
#define KBC_CMD_EN_KBD_INT      BIT(0)



/**********************
 *** I/O ADDRESSES ****
 *********************/

#define STAT_REG                0x64
#define KBC_CMD_REG             0x64
#define OUT_BUF                 0x60
#define KBC_COMMAND_REG         0x60


#define DELAY_US    20000


/**********************
 ***** SCANCODES ******
 *********************/

#define SCANCODE_2_BYTES       0xE0
#define MAKE                   BIT(7)
#define ESC_BREAK              0x41
#define READ_ERROR             0xFF
#define W_MAKE                 0x11
#define S_MAKE                 0x1F
#define A_MAKE                 0x1e
#define D_MAKE                 0x20                                 


/****************************
 **** PS/2 INTERPRETARION ****
 ***************************/

#define PS2_Y_OVF               BIT(7)
#define PS2_X_OVF               BIT(6)
#define PS2_Y_SIGN              BIT(5)
#define PS2_X_SIGN              BIT(4)
#define PS2_BIT_THREE           BIT(3)           
#define PS2_MB                  BIT(2)
#define PS2_RB                  BIT(1)
#define PS2_LB                  BIT(0)

/***********************
 ***** PS/2 COMMANDS****
 **********************/

#define PS2_RESET_CMD           0xFF
#define PS2_RESEND_CMD          0xFE
#define PS2_DEFAULTS_CMD        0xF6
#define PS2_DISABLE_REPORT_CMD  0xF5
#define PS2_ENABLE_REPORT_CMD   0xF4
#define PS2_SET_SAMPLE_RATE_CMD 0xF3
#define PS2_SET_REMOTE_MODE_CMD 0xF0
#define PS2_READ_DATA_CMD       0xEB
#define PS2_STREAM_MODE_CMD     0xEA
#define PS2_STATUS_REQUEST_CMD  0xE9
#define PS2_SET_RESOLUTION_CMD  0xE8
#define PS2_SCALING_2_1_CMD     0xE7
#define PS2_SCALING_1_1_CMD     0xE6
#define PS2_ACK                 0xFA
#define PS2_NACK                0xFE
#define PS2_ERROR               0xFC


/***********************
 ***** VG COMMANDS *****
 **********************/

#define INDEXED                 0x105
