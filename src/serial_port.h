#pragma once  
/**
 * @defgroup Serial Port
 * The definition of all functions to handle the reading, parsing, analyzing and using the serial
 * port communication method with another computer.
 */

#include <lcom/lcf.h>
#include"uart.h"


/**
 * @brief Starting the communication as wanted
 * In order to engage on communication with other computers, it is needed
 * to firstly initialize the interruptions wanted to handle the serial port 
 * as well as the use of the FIFO's.
 * 
 * @return int - 0 if successful
 */
int start_communication();

/**
 * @brief - Subscription of the serial port irq line
 * In order for interruptions of the serial port to be used, it is firstly needed to subscribe the
 * interrupts for the wanted COM. In our case it is always use COM1, since it is the only 
 * one needed.
 * 
 * @param bit_no - the irq line of COM1 
 * @return int - 0 if successful
 */
int ser_subscribe_int(uint8_t * bit_no);

/**
 * @brief - Unsubscription of the serial port irq line
 * At the end of the process, the serial port must be put back into its original state,
 * by unsubscribing the irq line of the selected COM. Once again, only COM1 is used
 * during our process.
 * 
 * @return int 
 */
int ser_unsubscribe_int();

/**
 * @brief - Setting the communication as we wanted
 * Through this function, it is declared how we want to handle the communication coming from the
 * serial port. In our case, it is used 1 as a Parity Bit, and using always 1 stop bit.
 * 
 * @return int 
 */
int ser_lcr_set();

/**
 * @brief - The serial port interrupt handler
 * When an interrupt by the serial port is launched, this function has the job to parse
 * which kind of interruption it is, as well as declaring what to do knowing that information.
 * 
 * @return int - the kind of interrupt it is
 */
int ser_ih();

/**
 * @brief - Sending a char through the UART
 * During our communication protocol, information is always sent as 8 bits, being
 * sent to the Transmitter Holding Register to be sent to the other computer's
 * serial port.
 * 
 * @param byte 
 * @return int 
 */
int send_char(uint8_t byte);
