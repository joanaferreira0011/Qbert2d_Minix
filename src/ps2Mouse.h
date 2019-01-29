#pragma once
/**
 * @defgroup PS2MOUSE
 * Series of functions to interact with the mouse registers, analyzing and parsing the data
 * coming from a mouse.
 *  
 */

/**
 * @brief - Subscribing the mouse irq line
 * In order for interrupts of the mouse to be sent, it is firstly
 * needed to subscribe their interrupts.
 * 
 * @param bit_no - the number of the irq line of the mouse
 * @return int - 0 if successful
 */
int ps2_subscribe_int(uint8_t *bit_no);

/**
 * @brief - Unsubscribing the mouse irq line
 * At the end of the need of the mouse, the mouse interrupt line 
 * should be unsubscribed.
 * 
 * @return int  - 0 if successful
 */
int ps2_unsubscribe_int();

/**
 * @brief - Parsing a Mouse packet
 * When the information of the mouse is fully read from the kbc, it is needed to interpret
 * those three bytes in order to know what to do.
 * 
 * @param pp - the packet itself
 */
void ps2_parse_packet(struct packet *pp);

/**
 * @brief - Issuing a mouse command to the kbc
 * Mouse commands are also written to the kbc, with the proper first indication that it is indeed 
 * a mouse command
 * 
 * @param cmd - the command itself
 * @return uint8_t - the data referring to the how the issuing went
 */
uint8_t ps2_issue_cmd(uint8_t cmd);

/**
 * @brief - Issuing a command plus its argument to the kbc
 * In order to further provide information of a command, it is also possible
 * to send an argument in some of the commands, thus the need for 
 * this function.
 * 
 * @param cmd - the command itself
 * @param arg - the argument itself
 * @return int - 0 if successful.
 */
int issue_command_with_arg_KBC(uint32_t cmd, uint32_t arg); 

