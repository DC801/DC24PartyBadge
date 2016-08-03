/**
 * dc801 coin badge for defcon 24
 *
 * You can use the button on your badge to cycle through a few modes and broadcast
 * some interesting Eddystone beacons
 */

#include <stdbool.h>
#include <stdint.h>
#include "nrf_drv_gpiote.h"
#include "nordic_common.h"
#include "softdevice_handler.h"
#include "bsp.h"
#include "app_timer.h"
#include "nrf_delay.h"
#include "bluetooth.h"
#include "led_patterns.h"


// Which pattern to show
int PrettyPattern = 0;


#define VBAT_MAX_IN_MV                  3700

uint8_t battery_level_get(void){
	// Configure ADC
	NRF_ADC->CONFIG     = (ADC_CONFIG_RES_8bit                        << ADC_CONFIG_RES_Pos)     |
												(ADC_CONFIG_INPSEL_SupplyOneThirdPrescaling << ADC_CONFIG_INPSEL_Pos)  |
												(ADC_CONFIG_REFSEL_VBG                      << ADC_CONFIG_REFSEL_Pos)  |
												(ADC_CONFIG_PSEL_Disabled                   << ADC_CONFIG_PSEL_Pos)    |
												(ADC_CONFIG_EXTREFSEL_None                  << ADC_CONFIG_EXTREFSEL_Pos);
	NRF_ADC->EVENTS_END = 0;
	NRF_ADC->ENABLE     = ADC_ENABLE_ENABLE_Enabled;

	NRF_ADC->EVENTS_END  = 0;    // Stop any running conversions.
	NRF_ADC->TASKS_START = 1;

	while (!NRF_ADC->EVENTS_END)
	{
	}

	uint16_t vbg_in_mv = 1200;
	uint8_t adc_max = 255;
	uint16_t vbat_current_in_mv = (NRF_ADC->RESULT * 3 * vbg_in_mv) / adc_max;

	NRF_ADC->EVENTS_END     = 0;
	NRF_ADC->TASKS_STOP     = 1;

	return (uint8_t) ((vbat_current_in_mv * 100) / VBAT_MAX_IN_MV);
}

/**@brief Make the LEDs do something pretty
 */
static void prettyLEDs(int pattern){

	switch(pattern){
		case 0:
			advertising_init(eddystone_url_data1, URL1_SIZE);
			knightRider();
			break;
		case 1:
			advertising_init(eddystone_url_data1, URL1_SIZE);
			redEyes();
			break;
		case 2:
			advertising_init(eddystone_url_data1, URL1_SIZE);
			strobeEyes();
			break;
		case 3:
			//sprintf(&eddystone_url_data4[3], "%03d", battery_level_get());
			//advertising_init(eddystone_url_data4, URL4_SIZE);
			advertising_init(eddystone_url_data1, URL1_SIZE);
			showBatteryStat(battery_level_get());
			break;
		case 4:
			advertising_init(eddystone_url_data2, URL2_SIZE);
			alternateOrange();
			break;
		case 5:
			advertising_init(eddystone_url_data3, URL3_SIZE);
			seizureMode();
			break;
		default:
			LED_OFF(ALL_LED_BITS);
			break;
	}
	
	breakWait = 0;
				
}


/**
 *  Handler for the button input change
 *
 */
void in_pin_handler(nrf_drv_gpiote_pin_t pin, nrf_gpiote_polarity_t action){
	
	const uint32_t orange_leds_list[ORANGE_LEDS_NUMBER] = ORANGE_LEDS_LIST;
	static int currMode = 0;
	
	// Debounce the pushbutton by delaying for 15ms and re-sampling the 
	// GPIO.  If it is still set, it's likely not a bouncing contact
	nrf_delay_ms(15);
	
	if(!nrf_drv_gpiote_in_is_set(pin)){
		
		// Break whatever is currently running
		breakWait = 1;
		nrf_delay_ms(5);
		
		// Button is still pressed!
		// Do something useful with it.
		
		int longPress = 0;
		while(!nrf_drv_gpiote_in_is_set(pin)){
			nrf_delay_ms(5);
			longPress++;
			if(longPress == 200){
				// Long press!  Siezure mode!!
				PrettyPattern = 5;
				currMode = 0;
				return;
			}
		}
		
		// Increment the current mode
		currMode++;
		
		// Loop back around on overflow
		if(currMode == ORANGE_LEDS_NUMBER){
			currMode = 0;
		}
		
		// Clear all the LEDs, then light just the orange for a tick
		LED_OFF(ALL_LED_BITS);
		LED_ON(ALL_ORANGE_BITS);
		nrf_delay_ms(100);
		
		// Flash the current mode LED
		for(int i = 0; i < 3; i++){
			LED_OFF(ALL_ORANGE_BITS);
			nrf_delay_ms(100);
			LED_ON(LED_BIT(orange_leds_list[currMode]));
			nrf_delay_ms(100);
		}
		
		// Turn them all off
		LED_OFF(ALL_ORANGE_BITS);
		
		// Set the pretty pattern to show
		PrettyPattern = currMode;
	}
}

/**
 *  Initialize the GPIOs
 *  We configure the LEDs as outputs, and the button as an input
 *  Additionally, we setup an interrupt event for when the button is pressed
 */
static void gpio_init(void){
	
	const uint32_t leds_list[LEDS_NUMBER] = LEDS_LIST;
	
	nrf_drv_gpiote_init();
	
	nrf_drv_gpiote_out_config_t out_config = GPIOTE_CONFIG_OUT_SIMPLE(true);
	
	// Configure the LED ports as outputs
	for(int i = 0; i < LEDS_NUMBER; i++){
		nrf_drv_gpiote_out_init(leds_list[i], &out_config);
	}

	// Fire the event whenever the button goes from high to low
	// We need to pullup the input, as the button will pull to ground when
	// pressed
  nrf_drv_gpiote_in_config_t in_config = GPIOTE_CONFIG_IN_SENSE_HITOLO(true);
  in_config.pull = NRF_GPIO_PIN_PULLUP;
  
	// Set the handler function and enable it
  nrf_drv_gpiote_in_init(BUTTON, &in_config, in_pin_handler);
  nrf_drv_gpiote_in_event_enable(BUTTON, true);

}

/**
 * @brief Function for application main entry.
 */
int main(void){
    
	// Initialize the device
	APP_TIMER_INIT(APP_TIMER_PRESCALER, APP_TIMER_OP_QUEUE_SIZE, false);
	ble_stack_init();
	advertising_init(eddystone_url_data1, URL1_SIZE);
	gpio_init();
	
	// Start broadcasting the eddystone
	advertising_start();
	
	// Enter main loop: show the pretty LED patterns
  for ( ; ; ){
		prettyLEDs(PrettyPattern);
  }
}

/**
 * @}
 */
