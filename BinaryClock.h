
#ifndef BinaryClock_h
#define BinaryClock_h
#include <Arduino.h>
// LED_pin <--reflect-->Arduino_pin
enum PIN
{
	H8 = 0, H4, H2, H1, // hour
	M32, M16, M8, M4, M2, M1, // minute
	S32, S16, S8, S4, S2, S1 = 15, // seconds
	SET, ADD // button
};

// initial ports pinmode output
void BinaryClock_Port();
// method
void BinaryClock_Set(); // SET TIME as you need
void BinaryClock_Hour(int Hr); // receive hour-value from Time.h, Display binary on leds.
void BinaryClock_Minute(int Min); // receive minute-value from Time.h, Display binary on leds.
void BinaryClock_Seconds(int Sec); // receive seconds-value from Time.h, Display binary on leds.
#endif
