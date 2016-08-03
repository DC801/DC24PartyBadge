/**
 *
 *  This file contains the LED patterns
 *
 */
 
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include "bsp.h"
#include "nrf_delay.h"
#include "led_patterns.h"
 
volatile int breakWait;
 
 /*
  * Wait for a specified time in milliseconds.
	* This function checks a global var every millisecond so that a wait loop
	* will break if a new mode is selected
	*/
void led_wait_ms(int milliseconds){
 
 for(int i = 0; i < milliseconds; i++){
	 if(breakWait){
		 // Time to go!
		 return;
	 }
	 nrf_delay_ms(1);
 }
 
}

void led_wait_us(int microseconds){
 
 for(int i = 0; i < microseconds; i++){
	 if(breakWait){
		 // Time to go!
		 break;
	 }
	 nrf_delay_us(1);
 }
 
}



/**
 * @brief Function for lighting LEDs.
 */
static void eyes(uint32_t LEFT_EYE, uint32_t RIGHT_EYE){
	
	switch(LEFT_EYE){
		case RED :
			LED_OFF(ALL_LEFT_BITS);				// turn off all LEDs
			LED_ON(LED_BIT(LED_LEFT_EYE_RED));	// turn on red LED
			break;
		case BLUE :
			LED_OFF(ALL_LEFT_BITS);				// turn off all LEDs
			LED_ON(LED_BIT(LED_LEFT_EYE_BLUE));	// turn on blue LED
			break;
		case GREEN :
			LED_OFF(ALL_LEFT_BITS);				// turn off all LEDs
			LED_ON(LED_BIT(LED_LEFT_EYE_GREEN));	// turn on green LED
			break;
		case AQUA :
			LED_ON(ALL_LEFT_BITS);				// turn on all LEDs
			LED_OFF(LED_BIT(LED_LEFT_EYE_RED));	// turn off red LED
			break;
		case PURPLE :
			LED_ON(ALL_LEFT_BITS);				// turn on all LEDs
			LED_OFF(LED_BIT(LED_LEFT_EYE_GREEN));	// turn off green LED
			break;
		case YELLOW :
			LED_ON(ALL_LEFT_BITS);				// turn on all LEDs
			LED_OFF(LED_BIT(LED_LEFT_EYE_BLUE));	// turn off blue LED
			break;
		case WHITE :
			LED_ON(ALL_LEFT_BITS);				// turn on all LEDs
			break;
		default :
			LED_OFF(ALL_LEFT_BITS);				// turn off all LEDs
	}
	
	switch(RIGHT_EYE){
		case RED :
			LED_OFF(ALL_RIGHT_BITS);				// turn off all LEDs
			LED_ON(LED_BIT(LED_RIGHT_EYE_RED));	// turn on red LED
			break;
		case BLUE :
			LED_OFF(ALL_RIGHT_BITS);				// turn off all LEDs
			LED_ON(LED_BIT(LED_RIGHT_EYE_BLUE));	// turn on blue LED
			break;
		case GREEN :
			LED_OFF(ALL_RIGHT_BITS);				// turn off all LEDs
			LED_ON(LED_BIT(LED_RIGHT_EYE_GREEN));	// turn on green LED
			break;
		case AQUA :
			LED_ON(ALL_RIGHT_BITS);				// turn on all LEDs
			LED_OFF(LED_BIT(LED_RIGHT_EYE_RED));	// turn off red LED
			break;
		case PURPLE :
			LED_ON(ALL_RIGHT_BITS);				// turn on all LEDs
			LED_OFF(LED_BIT(LED_RIGHT_EYE_GREEN));	// turn off green LED
			break;
		case YELLOW :
			LED_ON(ALL_RIGHT_BITS);				// turn on all LEDs
			LED_OFF(LED_BIT(LED_RIGHT_EYE_BLUE));	// turn off blue LED
			break;
		case WHITE :
			LED_ON(ALL_RIGHT_BITS);				// turn on all LEDs
			break;
		default :
			LED_OFF(ALL_RIGHT_BITS);				// turn off all LEDs
	}
}

void knightRider(void){
	
	const uint32_t orange_leds_list[ORANGE_LEDS_NUMBER] = ORANGE_LEDS_LIST;
	
	// Turn on all the orange LEDs one at a time and leave them on CW
	for (int i = 0; i < ORANGE_LEDS_NUMBER; i++){
			LED_ON(1 << orange_leds_list[i]);	
			led_wait_ms(100);		
			if(breakWait) return;
	}
	
	// Turn off all the orange LEDs one at a time and leave them on CW
	for (int i = 0; i < ORANGE_LEDS_NUMBER; i++){
			LED_OFF(1 << orange_leds_list[i]);	
			led_wait_ms(100);	
			if(breakWait) return;		
	}
	
	led_wait_ms(300);
	if(breakWait) return;
	
	// Turn on all the orange LEDs one at a time and leave them on CCW
	for (int i = ORANGE_LEDS_NUMBER - 1; i >= 0; i--){
			LED_ON(1 << orange_leds_list[i]);		
			led_wait_ms(100);
			if(breakWait) return;
	}
	
	// Turn off all the orange LEDs one at a time and leave them on CCW
	for (int i = ORANGE_LEDS_NUMBER - 1; i >= 0; i--){
			LED_OFF(1 << orange_leds_list[i]);		
			led_wait_ms(100);
			if(breakWait) return;		
	}
	
	led_wait_ms(300);
	if(breakWait) return;
	
}

void redEyes(void){

	eyes(RED, OFF);
	led_wait_ms(250);
	if(breakWait) return;
	eyes(OFF, RED);
	led_wait_ms(250);
	if(breakWait) return;
	
}

void strobeEyes(void){
	
	for(int i = 0; i < 1024; i++){
		eyes(BLUE, BLUE);
		led_wait_us(i);
		eyes(OFF, OFF);
		led_wait_us(1024 - i);
		
		if(breakWait) return;
	}
	
	for(int i = 0; i < 1024; i++){
		eyes(OFF, OFF);
		led_wait_us(i);
		eyes(BLUE, BLUE);
		led_wait_us(1024 - i);
		
		if(breakWait) return;
	}
	
		for(int i = 0; i < 1024; i++){
		eyes(RED, RED);
		led_wait_us(i);
		eyes(OFF, OFF);
		led_wait_us(1024 - i);
			
		if(breakWait) return;
	}
	
	for(int i = 0; i < 1024; i++){
		eyes(OFF, OFF);
		led_wait_us(i);
		eyes(RED, RED);
		led_wait_us(1024 - i);
		
		if(breakWait) return;
	}
	
	for(int i = 0; i < 1024; i++){
		eyes(GREEN, GREEN);
		led_wait_us(i);
		eyes(OFF, OFF);
		led_wait_us(1024 - i);
		
		if(breakWait) return;
	}
	
	for(int i = 0; i < 1024; i++){
		eyes(OFF, OFF);
		led_wait_us(i);
		eyes(GREEN, GREEN);
		led_wait_us(1024 - i);
		
		if(breakWait) return;
	}
	
}


void showBatteryStat(uint8_t level){
	
	int blinky = 0;
	
	LED_OFF(ALL_LED_BITS);
	
	blinky = LED_ORANGE_S;
	
	if(level > 10){
		LED_ON(LED_BIT(LED_ORANGE_S));
		blinky = 0;
	}
	if(level > 20){
		blinky = LED_ORANGE_SW;
	}
	if(level > 30){
		LED_ON(LED_BIT(LED_ORANGE_SW));
		blinky = 0;
	}
	if(level > 40){
		blinky = LED_ORANGE_NW;
	}
	if(level > 50){
		LED_ON(LED_BIT(LED_ORANGE_NW));
		blinky = 0;
	}
	if(level > 60){
		blinky = LED_ORANGE_NE;
	}
	if(level > 70){
		LED_ON(LED_BIT(LED_ORANGE_NE));
		blinky = 0;
	}
	if(level > 80){
		blinky = LED_ORANGE_SE;
	}
	if(level > 90){
		LED_ON(LED_BIT(LED_ORANGE_SE));
		blinky = 0;
	}
	
	while(!breakWait){
	
		if(blinky > 0){
			// We have a blinky LED to show, so blink it, forever
			LED_ON(LED_BIT(blinky));
			led_wait_ms(250);
			if(breakWait) return;
			LED_OFF(LED_BIT(blinky));
			led_wait_ms(250);
			if(breakWait) return;
		}
		else{
			// Just stay here forever
			led_wait_ms(500);
		}
		
	}
	
}

void alternateOrange(void){
	
	const uint32_t orange_leds_list[ORANGE_LEDS_NUMBER] = ORANGE_LEDS_LIST;
	
	LED_OFF(ALL_LED_BITS);
	
	while(!breakWait){
		for(int i = 0; i < (rand() % 5); i++){
			LED_ON(1 << orange_leds_list[rand() % ORANGE_LEDS_NUMBER]);
		}
		led_wait_ms(50);
		LED_OFF(ALL_ORANGE_BITS);
		led_wait_ms(50);
	}
	
}

void seizureMode(void){
	
	while(!breakWait){
		
		eyes(WHITE,WHITE);				
		LED_OFF(ALL_ORANGE_BITS);
		led_wait_ms(50);
		if(breakWait) return;
		
		eyes(OFF,OFF);
		LED_ON(ALL_ORANGE_BITS);
		led_wait_ms(50);
		if(breakWait) return;

	}  
	
}

