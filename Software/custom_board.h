/* The information contained herein is for use of the DC801 DEFCON 24 badge using a BMD-200.
 *  *
 * Licensees are granted free, non-transferable use of the information. NO
 * WARRANTY of ANY KIND is provided. This heading must NOT be removed from
 * the file.
 *
 * USING THIS FILE
 * For use with the Nordic Semiconductor SDK and Keil.
 * Install Nordic Semiconductor libraries via the Pack Installer, and place
 * custom_board.h in <Keil Install Folder>\ARM\Pack\NordicSemiconductor\nRF_
 * Examples\X.X.X\bsp. Set compiler define BOARD_CUSTOM, removing any other
 * BOARD_* define.
 */
#ifndef __CUSTOM_BOARD_H__
#define __CUSTOM_BOARD_H__

#define LEDS_NUMBER    11
#define ORANGE_LEDS_NUMBER	5

#define LED_RED        0
#define LED_GREEN      1
#define LED_BLUE       2
#define LED_RED1       3
#define LED_GREEN1     6
#define LED_BLUE1      10
#define LED_ORANGE     11
#define LED_ORANGE1    24
#define LED_ORANGE2    25
#define LED_ORANGE3    26
#define LED_ORANGE4    27

#define LEDS_LIST     { LED_RED, LED_GREEN, LED_BLUE, LED_RED1, LED_GREEN1, LED_BLUE1, LED_ORANGE, LED_ORANGE1, LED_ORANGE2, LED_ORANGE3, LED_ORANGE4}
#define ORANGE_LEDS_LIST	{LED_ORANGE, LED_ORANGE1, LED_ORANGE2, LED_ORANGE3, LED_ORANGE4}

#define BSP_LED_0      LED_RED
#define BSP_LED_1      LED_GREEN
#define BSP_LED_2      LED_BLUE
#define BSP_LED_3      LED_RED1
#define BSP_LED_4      LED_GREEN1
#define BSP_LED_5      LED_BLUE1
#define BSP_LED_6      LED_ORANGE
#define BSP_LED_7      LED_ORANGE1
#define BSP_LED_8      LED_ORANGE2
#define BSP_LED_9      LED_ORANGE3
#define BSP_LED_10     LED_ORANGE4

#define BSP_LED_0_MASK  (1<<BSP_LED_0)
#define BSP_LED_1_MASK  (1<<BSP_LED_1)
#define BSP_LED_2_MASK  (1<<BSP_LED_2)
#define BSP_LED_3_MASK  (1<<BSP_LED_3)
#define BSP_LED_4_MASK  (1<<BSP_LED_4)
#define BSP_LED_5_MASK  (1<<BSP_LED_5)
#define BSP_LED_6_MASK  (1<<BSP_LED_6)
#define BSP_LED_7_MASK  (1<<BSP_LED_7)
#define BSP_LED_8_MASK  (1<<BSP_LED_8)
#define BSP_LED_9_MASK  (1<<BSP_LED_9)
#define BSP_LED_10_MASK (1<<BSP_LED_10)

#define LEDS_MASK      (BSP_LED_0_MASK | BSP_LED_1_MASK | BSP_LED_2_MASK | BSP_LED_3_MASK | BSP_LED_4_MASK | BSP_LED_5_MASK | BSP_LED_6_MASK | BSP_LED_7_MASK | BSP_LED_8_MASK | BSP_LED_9_MASK | BSP_LED_10_MASK)
#define ORANGE_LEDS			(BSP_LED_6_MASK | BSP_LED_7_MASK | BSP_LED_8_MASK | BSP_LED_9_MASK | BSP_LED_10_MASK)
#define ALL_RIGHT				(BSP_LED_0_MASK | BSP_LED_1_MASK | BSP_LED_2_MASK)
#define ALL_LEFT				(BSP_LED_3_MASK | BSP_LED_4_MASK | BSP_LED_5_MASK)

/* all LEDs are lit when GPIO is low */
#define LEDS_INV_MASK  LEDS_MASK



#define LEDS_OFF(leds_mask) do {  NRF_GPIO->OUTSET = (leds_mask) & (LEDS_MASK & LEDS_INV_MASK); \
                            NRF_GPIO->OUTCLR = (leds_mask) & (LEDS_MASK & ~LEDS_INV_MASK); } while (0)

#define LEDS_ON(leds_mask) do {  NRF_GPIO->OUTCLR = (leds_mask) & (LEDS_MASK & LEDS_INV_MASK); \
                           NRF_GPIO->OUTSET = (leds_mask) & (LEDS_MASK & ~LEDS_INV_MASK); } while (0)

#define LED_IS_ON(leds_mask) ((leds_mask) & (NRF_GPIO->OUT ^ LEDS_INV_MASK) )

#define LEDS_INVERT(leds_mask) do { uint32_t gpio_state = NRF_GPIO->OUT;      \
                              NRF_GPIO->OUTSET = ((leds_mask) & ~gpio_state); \
                              NRF_GPIO->OUTCLR = ((leds_mask) & gpio_state); } while (0)

#define LEDS_CONFIGURE(leds_mask) do { uint32_t pin;                  \
                                  for (pin = 0; pin < 32; pin++) \
                                      if ( (leds_mask) & (1 << pin) )   \
                                          nrf_gpio_cfg_output(pin); } while (0)


#define OFF			0
#define RED			1
#define BLUE		2
#define GREEN		3
#define	AQUA		4
#define	PURPLE	5
#define YELLOW	6
#define	WHITE		7


#define BUTTONS_NUMBER 1

#define BUTTON_1       9

#define BUTTON_PULL    NRF_GPIO_PIN_PULLUP

#define BUTTONS_LIST { BUTTON_1 }

#define BSP_BUTTON_0   BUTTON_1

#define BSP_BUTTON_0_MASK (1<<BSP_BUTTON_0)

#define BUTTONS_MASK   0x00000801

//#define HWFC           true

//#define SPIM0_SCK_PIN       0     /**< SPI clock GPIO pin number ...**/
#endif // __CUSTOM_BOARD_H__
