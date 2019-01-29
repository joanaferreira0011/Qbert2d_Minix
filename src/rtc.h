#include <lcom/lcf.h>
/**
 * @defgroup RTC
 * Series of functions to handle reading, parsing and analyzing the information coming from
 * the rtc related registers.
 * 
 */


#define BIT(n)              (0x01<<(n))
#define RTC_ADDR_REG        0x70
#define RTC_DATA_REG        0x71
#define SECONDS             0x00
#define SECONDS_Alarm       0x01
#define MINUTES             0x02
#define MINUTES_ALARM       0x03
#define HOUR                0x04
#define HOUR_ALARM          0x05
#define DAY_WEEK            0x06
#define DAY                 0x07
#define MONTH               0x08
#define YEAR                0x09
#define REG_A               0x0A
#define REG_B               0x0B
#define REG_C               0x0C
#define REG_D               0x0D

#define PERIODIC_INTERRUPTS BIT(6)
#define UPDATE_INTERRUPTS   BIT(4)
#define DM_FLAG             BIT(2)
#define HOURS_FLAG          BIT(1)
#define STOP_PERIODIC       0xBF
#define STOP_UPDATES        0xEF
#define HALF_SECOND_WAVE (BIT(3) | BIT(2) | BIT(0))
#define INT_BITS            0X7f

/**
 * @brief Writing a command to the RTC Data Register
 * In order to activate several interrupts, commands must be written to the rtc.
 * 
 * @param arg - Argument to write to the RTC
 * @return int - 0 if successful
 */
int rtc_write_cmd(uint8_t arg);

/**
 * @brief The subscription of the RTC IRQ line
 * For interrupts to be sent to the process, the irq line interrupts must be subscribed first
 * 
 * @param bit_no - The irq line number associated to the rtc
 * @return int 
 */
int rtc_subscribe_int(uint8_t * bit_no);

/**
 * @brief The unsubscription of the RTC IRQ line
 * At the end of the procress, the irq line interrupts must be unsubscribed.
 * 
 * @return int - 0 if successful
 */
int rtc_unsubscribe_int();


/**
 * @brief - Enabling Periodic Interrups
 * This functions enables the periodic interrupts of the rtc.
 * 
 * @return int - 0 if successful
 */
int rtc_period_ints_enable();


/**
 * @brief - Enabling Update Interrupts
 * This functions unables the update interrups of the rtc
 * 
 * @return int - 0 if successful
 */
int rtc_update_ints_enable();


/**
 * @brief - Disabling Periodic Interrupts
 * Periodic interrupts must be disabled after the end of the process
 *
 * @return int - 0 if successful 
 */
int rtc_period_ints_disable();

/**
 * @brief - Disabling Update Interrupts
 * Update interrupts must be disabled after the end of the process
 * 
 * @return int - 0 if successful 
 */

int rtc_update_ints_disable();

/**
 * @brief - The RTC interrupt handler.
 * The handler of all the different interrupts coming from the rtc
 * 
 * @return int 
 */
int rtc_ih();

/**
 * @brief - Flushing the RTC.
 * At the end of the process, the C register is flushed, in order for new interrups in a new
 * process to be properly handled. 
 * 
 * @return int - 0 if successful 
 */
int flush_rtc();

/**
 * @brief - BCD to Binary converter
 * The conversion of the information coming from the rtc registers from BCD to binary,
 * to be properly read.
 * 
 * @param data - the register information to change
 */
void bcd_to_binary(uint8_t *data);


/**
 * @brief - Reading the date registers
 * The proper reading of all date registers in order to keep them updated
 * as time passes.
 * 
 */
void read_date();

