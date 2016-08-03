/*
 * Header file for led_patterns
 *
 */
 
extern volatile int breakWait;
 
void led_wait_ms(int);
void led_wait_us(int);
void knightRider(void);
void redEyes(void);
void strobeEyes(void);
void showBatteryStat(uint8_t);
void alternateOrange(void);
void seizureMode(void);

#define OFF			0
#define RED			1
#define BLUE		2
#define GREEN		3
#define	AQUA		4
#define	PURPLE	5
#define YELLOW	6
#define	WHITE		7
