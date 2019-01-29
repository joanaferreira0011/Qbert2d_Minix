#pragma once
/**
 * @defgroup Keyboard
 * Series of functions to handle with the interaction with the 
 * Keyboard.
 *  
 */


/**
 * @brief - The subscription of the kbd IRQ Line
 * In order for interrupts about the keyboard to be launched, its irq line must first be subscribed
 * 
 * @param bit_no - the irq set associated with the keyboard
 * @return int - 0 if successful
 */
int kdb_subscribe_int(uint8_t *bit_no);

/**
 * @brief - The unsubscription of the KBD IRQ line
 * Before the exit of the program, its irq line must be unsubscribed in order for the OS to return
 * to its original state
 * 
 * @return int 
 */
int kdb_unsubscribe_int();

/**
 * @brief - Reading the status register of the KBC
 * In order to have information about how the KBC is currently, it is constantly needed to read its
 * information, in order to know exactly what is sent from the output buffer
 * 
 * @param stat - where to write the KBC status
 * @return int - 0 if successfull
 */
int kdb_read_status(uint8_t *stat);

/**
 * @brief - Reading the output buffer register of the KBC
 * When a interrupt is launched with information of the keyboard, it is needed to read its content
 * from the output buffer
 * 
 * @param data - the data from the data output buffer 
 * @return int - 0 if successful
 */
int kbd_read_output_buff(uint8_t *data);

/**
 * @brief - Checking if there's an extra byte
 * The scan codes of the keyboard could eventually be two.
 * In order to know this information, it is necessary to check first scan
 * code if more information is to come
 * 
 * @param data - the first scan code
 * @return true - if more information is to come
 * @return false - if it's a single byte scan code
 */
bool extra_byte(uint8_t data);

/**
 * @brief - Issuing a command to the KBC
 * In order initiate certain types of communication in the KBC, it is needed
 * to send a command to it.
 * @param cmd - the command itself
 * @return int - 0 if successful
 */
int issue_command_KBC(uint32_t cmd);

/**
 * @brief - Detecting if a scan code is make
 * A scan code can be a make or a break, to make said this distinction it is needed 
 * to read the byte of the first scan code sent.
 * 
 * @param scancode  - the scan code itself
 * @return true - if make
 * @return false - if break
 */
bool is_scancode_make(uint8_t scancode);

void kbd_flush_buffer();

void mouse_flush_buffer();


#ifdef LAB3
int sys_inb_cnt(port_t port, uint32_t *data);
#else
#define sys_inb_cnt(p,q) sys_inb(p,q)
#endif
