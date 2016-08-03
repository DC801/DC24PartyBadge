/**
 *
 * Headerfile for the bluetooth functions
 */
 
 #define IS_SRVC_CHANGED_CHARACT_PRESENT 0                                 /**< Include the service changed characteristic. If not enabled, the server's database cannot be changed for the lifetime of the device. */

#define CENTRAL_LINK_COUNT              0                                 /**<number of central links used by the application. When changing this number remember to adjust the RAM settings*/
#define PERIPHERAL_LINK_COUNT           0                                 /**<number of peripheral links used by the application. When changing this number remember to adjust the RAM settings*/

#define APP_CFG_NON_CONN_ADV_TIMEOUT    0                                 /**< Time for which the device must be advertising in non-connectable mode (in seconds). 0 disables the time-out. */
#define NON_CONNECTABLE_ADV_INTERVAL    MSEC_TO_UNITS(100, UNIT_0_625_MS) /**< The advertising interval for non-connectable advertisement (100 ms). This value can vary between 100 ms and 10.24 s). */

// Eddystone common data
#define APP_EDDYSTONE_UUID              0xFEAA                            /**< UUID for Eddystone beacons according to specification. */
#define APP_EDDYSTONE_RSSI              0xEE                              /**< 0xEE = -18 dB is the approximate signal strength at 0 m. */

// Eddystone UID data
#define APP_EDDYSTONE_UID_FRAME_TYPE    0x00                              /**< UID frame type is fixed at 0x00. */
#define APP_EDDYSTONE_UID_RFU           0x00, 0x00                        /**< Reserved for future use according to specification. */
#define APP_EDDYSTONE_UID_ID            0x01, 0x02, 0x03, 0x04, \
                                        0x05, 0x06                        /**< Mock values for 6-byte Eddystone UID ID instance.  */
#define APP_EDDYSTONE_UID_NAMESPACE     0xAA, 0xAA, 0xBB, 0xBB, \
                                        0xCC, 0xCC, 0xDD, 0xDD, \
                                        0xEE, 0xEE                        /**< Mock values for 10-byte Eddystone UID ID namespace. */

// Eddystone URL data
#define APP_EDDYSTONE_URL_FRAME_TYPE    0x10                              /**< URL Frame type is fixed at 0x10. */
#define APP_EDDYSTONE_URL_SCHEME        0x03                              /**< 0x03 = "https://" 0x01 = "https://www."0x00 = "http://www" URL prefix scheme according to specification. */
#define APP_EDDYSTONE_URL1_URL  'd','c','8','0','1','.','o','r','g'
#define APP_EDDYSTONE_URL2_URL  'g','o','o','.','g','l','/','C','3','o','O','c','7'
#define APP_EDDYSTONE_URL3_URL  '5','z','8',0x04,'w','o','r','m','_','z','l','g','g'
#define APP_EDDYSTONE_URL4_URL  '0','0','0'

//// Eddystone TLM data
//#define APP_EDDYSTONE_TLM_FRAME_TYPE    0x20                              /**< TLM frame type is fixed at 0x20. */
//#define APP_EDDYSTONE_TLM_VERSION       0x00                              /**< TLM version might change in the future to accommodate other data according to specification. */
//#define APP_EDDYSTONE_TLM_BATTERY       0x00, 0xF0                        /**< Mock value. Battery voltage in 1 mV per bit. */
//#define APP_EDDYSTONE_TLM_TEMPERATURE   0x0F, 0x00                        /**< Mock value. Temperature [C]. Signed 8.8 fixed-point notation. */
//#define APP_EDDYSTONE_TLM_ADV_COUNT     0x00, 0x00, 0x00, 0x00            /**< Running count of advertisements of all types since power-up or reboot. */
//#define APP_EDDYSTONE_TLM_SEC_COUNT     0x00, 0x00, 0x00, 0x00            /**< Running count in 0.1 s resolution since power-up or reboot. */

//#define GPIOTE_CHANNEL_0 0  //set button to zero?

//#define DEAD_BEEF                       0xDEADBEEF                        /**< Value used as error code on stack dump, can be used to identify stack location on stack unwind. */

#define APP_TIMER_PRESCALER             0                                 /**< Value of the RTC1 PRESCALER register. */
#define APP_TIMER_OP_QUEUE_SIZE         4                                 /**< Size of timer operation queues. */

static uint8_t eddystone_url_data1[] =  /**< Information advertised by the Eddystone URL frame type. */
{
    APP_EDDYSTONE_URL_FRAME_TYPE,   // Eddystone URL frame type.
    APP_EDDYSTONE_RSSI,             // RSSI value at 0 m.
    APP_EDDYSTONE_URL_SCHEME,       // Scheme or prefix for URL ("http", "http://www", etc.)
    APP_EDDYSTONE_URL1_URL           // URL with a maximum length of 17 bytes. Last byte is suffix (".com", ".org", etc.)
};
#define URL1_SIZE sizeof(eddystone_url_data1)

static uint8_t eddystone_url_data2[] =  /**< Information advertised by the Eddystone URL frame type. */
{
    APP_EDDYSTONE_URL_FRAME_TYPE,   // Eddystone URL frame type.
    APP_EDDYSTONE_RSSI,             // RSSI value at 0 m.
    APP_EDDYSTONE_URL_SCHEME,       // Scheme or prefix for URL ("http", "http://www", etc.)
    APP_EDDYSTONE_URL2_URL           // URL with a maximum length of 17 bytes. Last byte is suffix (".com", ".org", etc.)
};
#define URL2_SIZE sizeof(eddystone_url_data2)
	
static uint8_t eddystone_url_data3[] =  /**< Information advertised by the Eddystone URL frame type. */
{
    APP_EDDYSTONE_URL_FRAME_TYPE,   // Eddystone URL frame type.
    APP_EDDYSTONE_RSSI,             // RSSI value at 0 m.
    APP_EDDYSTONE_URL_SCHEME,       // Scheme or prefix for URL ("http", "http://www", etc.)
    APP_EDDYSTONE_URL3_URL           // URL with a maximum length of 17 bytes. Last byte is suffix (".com", ".org", etc.)
};
#define URL3_SIZE sizeof(eddystone_url_data3)
	
static uint8_t eddystone_url_data4[] =  /**< Information advertised by the Eddystone URL frame type. */
{
    APP_EDDYSTONE_URL_FRAME_TYPE,   // Eddystone URL frame type.
    APP_EDDYSTONE_RSSI,             // RSSI value at 0 m.
    APP_EDDYSTONE_URL_SCHEME,       // Scheme or prefix for URL ("http", "http://www", etc.)
    APP_EDDYSTONE_URL4_URL           // URL with a maximum length of 17 bytes. Last byte is suffix (".com", ".org", etc.)
};
#define URL4_SIZE sizeof(eddystone_url_data4)

void advertising_init(uint8_t *, int);
void advertising_start(void);
void ble_stack_init(void);

